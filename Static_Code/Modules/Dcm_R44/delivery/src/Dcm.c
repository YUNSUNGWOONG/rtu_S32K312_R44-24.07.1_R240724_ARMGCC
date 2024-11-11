/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Dcm.c                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Main implementation of Dcm                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 0.0.1     31-Dec-2019   SonDT1        AR440 Implementation                 **
** 0.0.2     06-May-2020   LanhLT        Remove Dcm_GetVin, add Dcm_FetchVin  **
** 0.0.3     14-Aug-2020   HueKM         Update SID2A scheduler as per #14836 **
** 0.0.4     13-Oct-2020   HueKM         Changes made as per #15766           **
** 0.0.5     02-Nov-2020   HueKM         Changes made as per #16832           **
** 0.0.6     04-Dec-2020   HueKM         Polyspace fixing as per #15175       **
** 0.0.7     16-Dec-2020   HueKM         Mapping SUD API ID as per #17448     **
** 1.0.2     18-May-2022   LanhLT        Changes made as per #26479           **
** 1.0.9     31-Mar-2023   LanhLT        Refer #CP44-1637, #CP44-1558:        **
**                                       #CP44-1551, #CP44-1819               **
** 1.0.11    28-Apr-2023   SY Kim        Refer #CP44-1933                     **
** 1.0.12    30-Jun-2023   SY Kim        Refer #CP44-2255                     **
** 1.1.0     12-Oct-2023   SY Kim        Refer #CP44-2768, #CP44-2676         **
** 1.1.1     30-Oct-2023   DanhTQ1       Refer #CP44-2730, #CP44-3035         **
** 1.2.0     13-Nov-2023   DH Kwak       Refer #CP44-3122                     **
** 1.3.0     31-Dec-2023   DH Kwak       Refer #CP44-4455, #CP44-1515         **
** 1.4.0     29-Mar-2024   EK Kim        Refer #CP44-3850                     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Types.h"
#include "Rte_Dcm.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dem.h"
#endif
#if (DCM_NVM_CONFIGURED == STD_ON)
#include "NvM.h"
#endif
#include "SchM_Dcm.h"
#include "Dcm_Externals.h"
#include "BswM_Dcm.h"
#include "ComM_Dcm.h"
#include "PduR_Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_Dsl.h"
#include "Dcm_DspMain.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DslInternal.h"
#include "Dcm_DspServices.h"
#include "Dcm_DspMemoryServices.h"
#include "Dcm_DspNonPagedDTCSubFct.h"
#include "Dcm_DspReadDTCInfo.h"
#include "Dcm_DspOBDInternals.h"
#include "Dcm_DspOBDServices.h"
#include "Dcm_DslManageSecurity.h"
#include "Dcm_DspEcuReset.h"
#include "Dcm_DspUploadDownload.h"
#include "Dcm_RoutineControl.h"

#if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
#include "Dcm_DspResponseOnEvent.h"
#endif

#include "Dcm_Config.h"
#include "Dcm_Lib.h"
#include "Dcm_Utils.h"
#include "Dcm_Validate.h"
#include "Dcm_ActiveDiag.h"
#include "Dcm_Timer.h"
#include "Dcm_SessionControl.h"
#include "Dcm_ReqRespHandling.h"
#include "Dcm_GenericConnection.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dcm_DemInterfaces.h"
#endif
#include "Dcm_Authentication.h"

/* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */

/*******************************************************************************
**                     Types and Variables definition                         **
*******************************************************************************/
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

static Dcm_InitFunType InitFunList[INIT_FUN_MAX_NUM] =
{
  Dcm_InitActiveDiagnostic
  , Dcm_InitTimers
  , Dcm_InitManageSecurity
  , Dcm_InitSessionControl
  , Dcm_InitReqRespHandling
  , Dcm_InitGenericConnection
  #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
  , Dcm_InitAuthentication
  #else
  , NULL_PTR
  #endif
};

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

static FUNC(void, DCM_CODE) Dcm_Internal_UpdateTime(void);

static FUNC(void, DCM_CODE) Dcm_Internal_TransmitResponse(void);

static FUNC(void, DCM_CODE) Dcm_Internal_ProcessRequest(void);

static FUNC(void, DCM_CODE) Dcm_Internal_ServicesPending(void);

#if ((DCM_PAGEDBUFFER_ENABLED == STD_ON) && \
    ((DCM_READDTC_SUPPORT == STD_ON) || (DCM_OBD_SUPPORT == STD_ON)))
static FUNC(void, DCM_CODE) Dcm_Internal_ChkUpdatePage (void);
#endif

static FUNC(void, DCM_CODE) Dcm_Internal_GblFirstCallToMain(void);

#if((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) && \
      (DCM_MODE_RULE == STD_ON) && (DCM_DSP_COMM_CONTROL_CONFIGURED == STD_ON))
static FUNC(void, DCM_CODE) Dcm_Internal_ChkCommunicationMode (void);
#endif

static FUNC(void, DCM_CODE) Dcm_Internal_ChkResponseTime (void);

static FUNC(void, DCM_CODE) Dcm_Internal_ChkS3ServerTime (void);

#if((DCM_DSP_CONTROL_DTC_SERVICE == STD_ON) && \
     (DCM_MODE_RULE == STD_ON) && (DCM_DSP_CONTROL_DTC_CONFIGURED == STD_ON))

static FUNC(void, DCM_CODE) Dcm_Internal_ChkControlDTCSetting (void);
#endif

#if ((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) || \
     (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_MemoryServicesMainFunction(
  Dcm_IdContextType IdContext);
#endif

#if ((DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_DidServicesMainFunction(void);
#endif

#if ((DCM_RPT_DTC == STD_ON) || \
     (DCM_RPT_NOOFDTC == STD_ON) || \
     (DCM_RPT_DTC_FLT_DET_CTR == STD_ON) || \
     (DCM_DSP_CLR_DIAG_SERVICE == STD_ON) || \
     (DCM_FAULT_DETECTION_COUNTER == STD_ON) || \
     (DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON))
static FUNC(void, DCM_CODE) Dcm_DtcServicesMainFunction(
  Dcm_IdContextType IdContext);
#endif

#if ((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
     (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || \
     (DCM_OBD_GETDTC_0A_SERVICE == STD_ON) || \
     (DCM_OBD_CLRRESET_EMISSION_DIAGINFO_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_ObdServicesMainFunction(
  Dcm_IdContextType IdContext);
#endif

#if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
       (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_InternalValidateRoeEventId(
  uint8 RoeEventId
  , Dcm_Uint8PtrType pIndex);
#endif

#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_Periodic_Did_FirstResponse(
  Dcm_Uint8PtrType pTimerUpdated);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_Internal_UpdateTime                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function updates internal timer                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, DCM_CODE) Dcm_Internal_UpdateTime (void)
{
  /* @Trace: Dcm_SUD_API_00172 */
  Dcm_UpdateTimers();

}

/*******************************************************************************
** Function Name        : Dcm_Internal_TransmitResponse                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function transmits response message from       **
**                        main function.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Internal_TransmitResponse(void)
{
  /* @Trace: Dcm_SUD_API_00166 */
  if (Dcm_GblProcessNewRequest != DCM_TRUE)
  {
    if (Dcm_GblSendResponse == DCM_TRUE)
    {
      /* @Trace: Dcm_SUD_API_00167 */
      Dcm_GblSendResponse = DCM_FALSE;

      if (Dcm_GddNegRespError != DCM_POS_RESP)
      {
        /* @Trace: Dcm_SUD_API_00168 */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }

      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
    }
    /* TODO: plz redesign .. Direct transmission shall be removed */
    else if (Dcm_GblPduRTransmitResponse == DCM_TRUE)
    {
      /* @Trace: Dcm_SUD_API_00170 */
      Dcm_GblPduRTransmitResponse = DCM_FALSE;
      Dcm_DslPduRTransmit();
    }
    else
    {
      /* @Trace: Dcm_SUD_API_00171 */
      /* No action in this case */
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_Internal_ProcessRequest                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function processes request message from        **
**                        main function.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Internal_ProcessRequest(void)
{
  /* @Trace: Dcm_SUD_API_00143 */
  if (Dcm_GblProcessNewRequest == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_00142 */
    Dcm_GblProcessNewRequest = DCM_FALSE;
    Dcm_DslCheckPrtclStatus();
  }
}

/*******************************************************************************
** Function Name        : Dcm_Internal_ServicesPending                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal processing for pending services            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00529 SWS_Dcm_00530 SWS_Dcm_00760 */
static FUNC(void, DCM_CODE) Dcm_Internal_ServicesPending(void)
{
  /* @Trace: Dcm_SUD_API_00145 */
  if (DCM_FALSE == Dcm_IsNegRespReady())
  {
    /* Enter critical section protection */
    SchM_Enter_Dcm_RxPduIdProtection();

    /* Check whether need to cancel pending operation */
    #if(DCM_DEM_CONFIGURED == STD_ON)
    if (DCM_TRUE == Dcm_TriggerCancelPendingOperation)
    {
      /* @Trace: Dcm_SUD_API_00146 */
      Dcm_TriggerCancelPendingOperation = DCM_FALSE;

      /* Exit critical section protection */
      SchM_Exit_Dcm_RxPduIdProtection();

      /* To stop processing active diagnostic request */
      Dcm_DsdCancelOperation();

      Dcm_ServicePendingStatus.ucReadDataPendingStatus = DCM_FALSE;
      Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_FALSE;
      Dcm_PrtclTxBufStatus.ucOBDClearDTCStatus = DCM_FALSE;
      Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_FALSE;
      Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_FALSE;
      Dcm_PrtclTxBufStatus.ucReportOBDDtc = DCM_FALSE;
      Dcm_GblFaultDetectionCounter = DCM_FALSE;
    }
    else
    #endif
    {
      /* Exit critical section protection */
      SchM_Exit_Dcm_RxPduIdProtection();

      Dcm_RequestContextPtrType pReqCtx;
      pReqCtx = Dcm_GetRequestContextPtr(Dcm_GddRxPduId);

      if (NULL_PTR == pReqCtx)
      {
        /* @Trace: Dcm_SUD_API_00150 */
        /* Should report DET error */
      }
      else if (DCM_E_PENDING == pReqCtx->rct_RequestResult)
      {
        /* @Trace: Dcm_SUD_API_00151 */
        Dcm_DiagnosticServiceDispatch(DCM_PENDING, pReqCtx);
      }
      #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
      /* @Trace: Dcm_SUD_API_00154 */
      else if (DCM_TRUE == Dcm_GblProcessPendingRequest)
      #else
      else
      #endif
      {
        /* @Trace: Dcm_SUD_API_00153 */
        /* TODO input & check id context before 
         * process pending service in parallel processing */
        Dcm_IdContextType IdContext = Dcm_GstMsgContext.idContext;

        #if ((DCM_RPT_DTC == STD_ON) || \
             (DCM_RPT_NOOFDTC == STD_ON) || \
            (DCM_RPT_DTC_FLT_DET_CTR == STD_ON) || \
            (DCM_DSP_CLR_DIAG_SERVICE == STD_ON) || \
            (DCM_FAULT_DETECTION_COUNTER == STD_ON) || \
            (DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON))
        Dcm_DtcServicesMainFunction(IdContext);
        #endif

        #if ((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
             (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || \
             (DCM_OBD_GETDTC_0A_SERVICE == STD_ON) || \
             (DCM_OBD_CLRRESET_EMISSION_DIAGINFO_SERVICE == STD_ON))
        Dcm_ObdServicesMainFunction(IdContext);
        #endif

        #if ((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) \
             || (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON))
        Dcm_MemoryServicesMainFunction(IdContext);
        #endif

        /* Pending process for upload download services */
        Dcm_UploadDownloadServicesPending(
          Dcm_GblRespPendConfirmation, &Dcm_GstMsgContext);
      
        #if ((DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
             (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
             (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) || \
             (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
             (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON))
        Dcm_DidServicesMainFunction();
        #endif

        #if (DCM_ROUTINECONTROL_SERVICE == STD_ON)
        Dcm_RidCtrl_PendingOperation(&Dcm_GstMsgContext);
        #endif

        #if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
        Dcm_ROE_MainFunction();
        #endif

        #if (DCM_DSP_SECURITY_SERVICE == STD_ON)
        Dcm_SecurityAccess_PendingOperation(&Dcm_GstMsgContext);
        #endif

        #if (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
        Dcm_SesCtrl_ProcessProgPending(&Dcm_GstMsgContext);
        #endif

        #if (DCM_ECURESET_SERVICE == STD_ON)
        Dcm_EcuReset_ProcessProgPending(&Dcm_GstMsgContext);
        #endif

        #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
        Dcm_GblProcessPendingRequest = DCM_FALSE;
        Dcm_TriggerAddPendingRequestToQueue();
        #endif

        DCM_UNUSED(IdContext);
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_Internal_ChkUpdatePage                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function updates page for paged buffer from    **
**                        main function                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_PAGEDBUFFER_ENABLED == STD_ON) && \
    ((DCM_READDTC_SUPPORT == STD_ON) || (DCM_OBD_SUPPORT == STD_ON)))
static FUNC(void, DCM_CODE) Dcm_Internal_ChkUpdatePage (void)
{
  /* @Trace: Dcm_SUD_API_00128 */
  /* Check whether the Update page was invoked during paged processing */
  if (Dcm_DspSerPgStatus.ucUpdatePageStarted == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_00127 */
    Dcm_DspSerPgStatus.ucUpdatePageStarted = DCM_FALSE;

    /* Perform the update page processing */
    Dcm_DspProcessUpdatePage();
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_Internal_GblFirstCallToMain                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function processes data at first after         **
**                        MCU is reset                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Internal_GblFirstCallToMain(void)
{
    /* @Trace: Dcm_SUD_API_00133 */
    static P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) LpPduIdTable;

    if (Dcm_GblFirstCallToMain == DCM_FIRST_CALL_TO_MAIN_INIT)
    {
      /* @Trace: SWS_Dcm_01154 */
      /* @Trace: Dcm_SUD_API_00129 */
      /* polyspace +1 MISRA2012:2.2 [Not a defect:Low] Justify with annotations */
      Dcm_StartRestoreSecurityAttemptCounters();

      /* @Trace: SWS_Dcm_01174 */
      #if (DCM_VIN_REF_CONFIGURED == STD_ON)
      Dcm_FetchVin();
      #endif

      /* @Trace: SWS_Dcm_01481 */
      #if (DCM_AUTHENTICATION_PERSIST_STATE_MODE_RULE == STD_ON)
      Dcm_StartRestorePersistedAuthenticationState();
      #endif


      /* Check whether the ECU start from a bootloader jump or not */
      if (Dcm_EcuStartMode == DCM_WARM_START)
      {
        LpPduIdTable = Dcm_Internal_GetPduIdOnReset(
          Dcm_GddProgConditions.TesterAddress,
          &(Dcm_GstMsgContext.dcmRxPduId));

        if (LpPduIdTable != NULL_PTR)
        {
          /* @Trace: Dcm_SUD_API_00136 */
          Dcm_GulChannelIdentifier = LpPduIdTable->ComMChannelId;

          /* @Trace: SWS_Dcm_00537 */
          /* Inform ComM about the change in diagnostic session */
          Dcm_TriggerEventActivationDiagnostic(AD_TE_FIRST_CALLED);

          Dcm_GblFirstCallToMain = DCM_FIRST_CALL_TO_MAIN_WAIT;
          /* trigger timer (waiting full com 5s), DCM_TIMSTR_P2_SERVER_MAX is 5s */
          Dcm_StartTimer(DCM_WAIT_FULL_COM_TIMER, DCM_TIMSTR_P2_SERVER_MAX);
        }
        else
        {
          Dcm_GblFirstCallToMain = DCM_FIRST_CALL_TO_MAIN_DONE;
        }
      }
      else
      {
        Dcm_GblFirstCallToMain = DCM_FIRST_CALL_TO_MAIN_DONE;
      }
    }
    /* @Trace: Dcm_SUD_API_00130 */
    if (Dcm_GblFirstCallToMain == DCM_FIRST_CALL_TO_MAIN_WAIT)
    {
      uint8 LucIndex;
      uint8 LucConnectionId = (uint8)Dcm_GddProgConditions.ConnectionId;
      boolean LblFullComMode = DCM_FALSE;
      
      for (LucIndex = 0; LucIndex < DCM_NUM_OF_PDUIDTABLECONFIG; LucIndex++)
      {
        if (LucConnectionId == Dcm_GaaPduIdTableConfig[LucIndex].RxConnectionId)
        {
          LblFullComMode = Dcm_IsInFullComMode(
            Dcm_GaaPduIdTableConfig[LucIndex].ComMChannelId);
          break;
        }
      }
      if (LblFullComMode == DCM_TRUE)
      {
        Dcm_GblFirstCallToMain = DCM_FIRST_CALL_TO_MAIN_EXECUTE;
      }
    }
	  
    /* check time-out in NO_COMMUNICATION */
    if (Dcm_GblFirstCallToMain == DCM_FIRST_CALL_TO_MAIN_EXECUTE)
    {
      Dcm_GblFirstCallToMain = DCM_FIRST_CALL_TO_MAIN_DONE;

      /* the variable LpPduIdTable is static type. */
      uint8 LucProtocolIDIndex = Dcm_GetProtocolTypeIndex(
      LpPduIdTable->ProtocolType);

      /* @Trace: SWS_Dcm_00767 */
      if( (LpPduIdTable->ucRxBufferId < DCM_NUM_OF_BUFFER_CONFIG) &&
          (LpPduIdTable->ucTxBufferId < DCM_NUM_OF_BUFFER_CONFIG) &&
          (LucProtocolIDIndex < DCM_NUM_OF_PROTOCOLCONFIG))
      {
        /* @Trace: Dcm_SUD_API_00137 */
        Dcm_MsgType LpRxBufferId;
        Dcm_MsgType LpTxBufferId;
        P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_APPL_CONST) LpProtocolCfg;

        Dcm_GddRxPduId = Dcm_GstMsgContext.dcmRxPduId;
        Dcm_GddDcmTxConfPduId = (uint8) LpPduIdTable->usTxConfirmationPduId;

        LpProtocolCfg = &Dcm_GaaProtocolConfig[LucProtocolIDIndex];
        Dcm_GucPrtclPriority = LpProtocolCfg->ucProtocolPrio;

        LpRxBufferId = Dcm_GaaBufferConfig[LpPduIdTable->ucRxBufferId].pBufferArea;
        LpTxBufferId = Dcm_GaaBufferConfig[LpPduIdTable->ucTxBufferId].pBufferArea;

        Dcm_GstMsgContext.resData = &LpTxBufferId[DCM_ONE];
        Dcm_GstMsgContext.reqData = &LpRxBufferId[DCM_ONE];
        Dcm_GstMsgContext.idContext = (Dcm_GddProgConditions.Sid | DCM_RESPONSE_ID);
        Dcm_GstMsgContext.resData[0U] = Dcm_GddProgConditions.Sid;
        Dcm_GstMsgContext.resDataLen = DCM_ONE;
        Dcm_GstMsgContext.msgAddInfo.reqType = (uint8) DCM_PHYSICAL_TYPE;

        /* If DCM_OEM/SYS_BOOT_RESPAPP is set in RTSW, bootloader shall not send positive response */
        if (Dcm_GddProgConditions.ResponseRequired == DCM_TRUE)
        {
          Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_FALSE;
        }
        else
        {
          Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_TRUE;
        }

        if(Dcm_GddProgConditions.Sid == DCM_DIAGNOSTICSESSIONCONTROL)
        {
          #if (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
          /* @Trace: Dcm_SUD_API_00138 */
          Dcm_SesCtrl_UpdateRespOnReset(
            &Dcm_GstMsgContext, Dcm_GddProgConditions.SubFncId);
          #endif
        }
        else
        {
          #if (DCM_ECURESET_SERVICE == STD_ON)
          /* @Trace: Dcm_SUD_API_00140 */
          Dcm_EcuReset_UpdateRespOnReset(
            &Dcm_GstMsgContext, Dcm_GddProgConditions.SubFncId);
          #endif
        }

        /* We must set the NormalRequest flag to send a response */
        Dcm_GblNormalReq = DCM_TRUE;

        /* This varibale will be cleared in DspConfirmation function */
        Dcm_GblSendResOnReset = DCM_TRUE;

        /* Initialize TxPduId configured for the RxPduId */
        Dcm_GddDcmTxPduId = LpPduIdTable->ddTxPduId;

        SchM_Enter_Dcm_RxPduIdProtection();
        DCM_SET_PDU_STATUS(LpPduIdTable);
        SchM_Exit_Dcm_RxPduIdProtection();

        Dcm_PrtclTxBufStatus.ucProtclStatus = DCM_TRUE;
        Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);

        /* Clear response required flag */
        Dcm_GddProgConditions.ResponseRequired = DCM_FALSE;

        Dcm_StopTimer(DCM_WAIT_FULL_COM_TIMER);
      }
    }
    else
    {
        /*if timer expired, Dcm is not in FULL_COMMUNICATION, Det error report*/
        if (Dcm_IsTimerExpired(DCM_WAIT_FULL_COM_TIMER) == DCM_TRUE)
        {
          DCM_REPORT_ERROR(DCM_COMM_FULL_COM_MODE_ENTERED_SID,
                          DCM_E_FORCE_RCRRP_IN_SILENT_COMM);
        }
    }
}

/*******************************************************************************
** Function Name        : Dcm_Internal_ChkCommunicationMode                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function checks communication mode in          **
**                        main function                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) \
     && (DCM_MODE_RULE == STD_ON) \
     && (DCM_DSP_COMM_CONTROL_CONFIGURED == STD_ON))
static FUNC(void, DCM_CODE) Dcm_Internal_ChkCommunicationMode(void)
{
  /* @Trace: Dcm_SUD_API_00100 */
  if (Dcm_GucComCtrlMode != DCM_ENABLE_RX_TX_NORM_NM)
  {
    /* @Trace: SWS_Dcm_00753 */
    /* @Trace: Dcm_SUD_API_00099 */
    Dcm_NegativeResponseCodeType ChkVal = Dcm_CheckModeRule(
      DCM_TRUE, DCM_DSP_COMM_CONTROL_REENABLE_MODE_RULE);

    if (DCM_POS_RESP != ChkVal)
    {
      /* @Trace: Dcm_SUD_API_00102 */
      Dcm_GucComCtrlMode = DCM_ENABLE_RX_TX_NORM_NM;
      Dcm_SwitchCommMode_AllChannel(Dcm_GucComCtrlMode);
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_Internal_ChkResponseTime                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function checks response time in main function **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04016 */
static FUNC(void, DCM_CODE) Dcm_Internal_ChkResponseTime(void)
{
  /* Check if the Min response timer is enabled and it is expired
   * Check if the Max response timer is enabled and timer has reached
   * half its Initialized value to send NRC RCRRP */
  boolean LblActiveProtocol = DCM_IS_ACTIVE_PROTOCOL_STATUS();
  boolean LblP2TimerExpired = Dcm_IsTimerExpired(DCM_P2SERVERMAX_TIMER);

  /* @Trace: SWS_Dcm_01142 */
  /* @Trace: Dcm_SUD_API_00107 */
  if ((DCM_TRUE == LblActiveProtocol)
      /* @Trace: SWS_Dcm_00024 */
      && (DCM_TRUE == LblP2TimerExpired)
      /* @Trace: SWS_Dcm_01105 */
      /* Do not check P2 timing in case periodic response running */
      #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
      && (Dcm_GddPerStatus.blOnResTrans == DCM_FALSE)
      #endif
     )
  {
    /* In case of responsePending, suppressPosRspMsgIndicationBit
     * should be cleared. Since final response (negative /positive)
     * is required then */
    /* @Trace: SWS_Dcm_00203 */
    Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_FALSE;

    /* @Trace: Dcm_SUD_API_00109 */
    if (((Dcm_TxRespStatus.ucNormResponse == DCM_FALSE)
         && (Dcm_TxRespStatus.ucDslPagedTrans == DCM_FALSE)
         && (Dcm_TxRespStatus.ucNegResp == DCM_FALSE))
         #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
         || (Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE)
         #endif
       )
    {
      /* @Trace: Dcm_SUD_API_00113 */
      Dcm_SetNegResp(Dcm_GstMsgContext.idContext & DCM_BIT6_AND_MASK
        , DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING);

      Dcm_GusMaxNoOfRespPend++;

      if (DCM_FALSE == Dcm_ChkNumRespPend(DCM_MAIN_FUNCTION_SID, 
        Dcm_GusMaxNoOfRespPend))
      {
        /* @Trace: Dcm_SUD_API_00117 */
        Dcm_GusMaxNoOfRespPend = 0U;

        /* To Stop processing active diagnostic request */
        Dcm_DsdCancelOperation();
        Dcm_ServicePendingStatus.ucReadDataPendingStatus = DCM_FALSE;

        #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if (Dcm_TxRespStatus.ucPagedTrans == DCM_TRUE)
        {
          /* @Trace: Dcm_SUD_API_00121 */
          Dcm_DspCancelPagedBufferProcessing();

          /* Update the bit flag for response failed to TRUE */
          Dcm_TxRespStatus.ucRespFailed = DCM_TRUE;
          Dcm_TxRespStatus.ucPagedTrans = DCM_FALSE;
        }
        #endif

        #if(DCM_DEM_CONFIGURED == STD_ON)
        if ((Dcm_PrtclTxBufStatus.ucClearDTCStatus == DCM_TRUE)
            || (Dcm_PrtclTxBufStatus.ucOBDClearDTCStatus == DCM_TRUE)
            || (Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus == DCM_TRUE)
            || (Dcm_PrtclTxBufStatus.ReportNumOfDtc == DCM_TRUE)
            || (Dcm_GblDTCFDCPending == DCM_TRUE)
            || (Dcm_PrtclTxBufStatus.ucReportOBDDtc == DCM_TRUE)
            || (Dcm_GblFaultDetectionCounter == DCM_TRUE))
        {
          /* @Trace: Dcm_SUD_API_00122 */
          Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_FALSE;
          Dcm_PrtclTxBufStatus.ucOBDClearDTCStatus = DCM_FALSE;
          Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_FALSE;
          Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_FALSE;
          Dcm_PrtclTxBufStatus.ucReportOBDDtc = DCM_FALSE;
          Dcm_GblFaultDetectionCounter = DCM_FALSE;

          #if ((DCM_CLEAR_ITC_SERVICE_SUPPRT == STD_ON) \
               || (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON))
          Dcm_InternalTroubleCodeService = DCM_FALSE;
          #endif
        }
        #endif

        Dcm_GddOpStatus = DCM_INITIAL;
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, DCM_E_GENERALREJECT);
        Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
      }
      else
      {
        uint8 NetworkId = Dcm_GaaPduIdTableConfig[
          Dcm_GstMsgContext.dcmRxPduId].ComMChannelId;

        if (Dcm_GaaCommMode[NetworkId] != DCM_FULL_COMMUNICATION)
        {
          /* @Trace: SWS_Dcm_01143 */
          /* @Trace: Dcm_SUD_API_00119 */
          DCM_REPORT_RUNTIME_ERROR(
            DCM_COMM_FULL_COM_MODE_ENTERED_SID
            , DCM_E_FORCE_RCRRP_IN_SILENT_COMM);
        }
        else
        {
          /* @Trace: Dcm_SUD_API_00120 */
          Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
          Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;

          Dcm_DslPduRTransmit();
        }
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_Internal_ChkS3ServerTime                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function checks S3Server time in main function **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Internal_ChkS3ServerTime(void)
{
  /* @Trace: Dcm_SUD_API_00126 */
  if (DCM_TRUE == Dcm_IsTimerExpired(DCM_S3SERVER_TIMER))
  {
    /* @Trace: SWS_Dcm_00140 */
    /* @Trace: Dcm_SUD_API_00125 */
    DslInternal_SetSesCtrlType(DCM_DEFAULT_SESSION);

    /* @Trace: SRS_Diag_04208 */
    (void) SchM_Switch_Dcm_DcmDiagnosticSessionControl(DCM_DEFAULT_SESSION);

    /* @Trace: SWS_Dcm_01375 */
    Dcm_TriggerEventActivationDiagnostic(AD_TE_TIMER_S3_EXPIRED);

    /* @Trace: SWS_Dcm_01483 */
    /* polyspace +1 MISRA2012:2.2 [Not a defect:Low] Justify with annotations */
    #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
    Dcm_FallbackToDeauthenticatedState();
    #endif

    Dcm_StopTimer(DCM_S3SERVER_TIMER);
  }
}

/*******************************************************************************
** Function Name        : Dcm_Internal_ChkControlDTCSetting                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function checks control DTC settinging in      **
**                        main function                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_DSP_CONTROL_DTC_SERVICE == STD_ON) \
     && (DCM_MODE_RULE == STD_ON) \
     && (DCM_DSP_CONTROL_DTC_CONFIGURED == STD_ON) \
     && (DCM_DEM_CONFIGURED == STD_ON))
static FUNC(void, DCM_CODE) Dcm_Internal_ChkControlDTCSetting(void)
{
  /* @Trace: Dcm_SUD_API_00104 */
  if (DCM_TRUE == Dcm_GblDTCSettingDisabled)
  {
    /* @Trace: Dcm_SUD_API_00103 */
    Dcm_NegativeResponseCodeType ChkVal = Dcm_CheckModeRule(
      DCM_TRUE, DCM_DSP_CONTROL_DTC_REENABLE_MODE_RULE);

    if (DCM_POS_RESP != ChkVal)
    {
      /* @Trace: SWS_Dcm_00751 SWS_Dcm_00752 */
      /* @Trace: Dcm_SUD_API_00106 */
      (void)IDem_EnableDTCSetting();
      (void)SchM_Switch_Dcm_DcmControlDTCSetting(DCM_ENABLEDTCSETTING);

      Dcm_GblDTCSettingDisabled = DCM_FALSE;
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_Init                                            **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : The Initialization function will initialize all     **
**                        DCM global variables with the values of the         **
**                        configuration                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00101 SRS_BSW_00438 */
/* @Trace: SWS_Dcm_00334 SWS_Dcm_00037 */
FUNC(void, DCM_CODE) Dcm_Init(
  Dcm_ConfigConstPtrType ConfigPtr)
{
  /* @Trace: Dcm_SUD_API_00065 */
  #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* Initialize variable to store pending length of paged transmission */
  Dcm_GddCurrentLength = DCM_ZERO;
  #endif

  /* Clear request contect and cancel pending flag */
  Dcm_InitRequestContext();
  Dcm_TriggerCancelPendingOperation = DCM_FALSE;

  /* Initialize variable that contains the bit field to store the
   * status of paged transmission in DSP */
  DCM_CLEAR_ALL_DSP_FLAGS();

  /* Clear the response length and reset flag */
  Dcm_GblReset = DCM_FALSE;
  Dcm_GddTxResponseLen = DCM_ZERO;

  /* Init data for response in event service */
  #if(DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
  Dcm_InitROE();
  #endif

  /* Initialize variable to store current active communication mode */
  for (uint8 NetworkId = 0U; NetworkId < DCM_NO_OF_COMM_CHANNELS; NetworkId++)
  {
    /* @Trace: Dcm_SUD_API_00069 */
    Dcm_GaaCommMode[NetworkId] = DCM_NO_COMMUNICATION;
  }

  /* @Trace: SWS_Dcm_00034 */
  Dcm_GddOldSession = DCM_DEFAULT_SESSION;
  Dcm_GddCurrentSession = DCM_DEFAULT_SESSION;

  /* Initialize variable to store status of normal request */
  Dcm_GblNormalReq = DCM_FALSE;

  /* Update the flag to the first call to Dcm_main function */
  Dcm_GblFirstCallToMain = DCM_FIRST_CALL_TO_MAIN_INIT;
  Dcm_GblSendResOnReset = DCM_FALSE;

  /* Initialize variable to store the number of response pending transmitted */
  Dcm_GusMaxNoOfRespPend = DCM_ZERO;
  Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;

  /* @Trace: SWS_Dcm_00536 */
  Dcm_EcuStartMode = Dcm_GetProgConditions(&Dcm_GddProgConditions);
  

  /* Inform BswM module in case application updated */
  
  /* polyspace +2 DEFECT:DEAD_CODE [Justified:Low] "Because of SWS_Dcm_00987 
   So, Returned value Dcm_EcuStartMode equal DCM_WARM_START must be checked." */
  if ((DCM_WARM_START == Dcm_EcuStartMode) &&
    (DCM_TRUE == Dcm_GddProgConditions.ApplUpdated))
  {
    /* @Trace: SWS_Dcm_00768 */
    /* @Trace: Dcm_SUD_API_00071 */
    (void) BswM_Dcm_ApplicationUpdated();
    Dcm_GddProgConditions.ApplUpdated = DCM_FALSE;
  }

  /* Prepare programming condition value to clear */
  Dcm_ProgConditionsType LstProgConditions;
  LstProgConditions.ConnectionId = DCM_ZERO;
  LstProgConditions.TesterAddress = ADDRESS_UNSET;
  LstProgConditions.Sid = DCM_ZERO;
  LstProgConditions.SubFncId = DCM_ZERO;
  LstProgConditions.ReprogramingRequest = DCM_FALSE;
  LstProgConditions.ApplUpdated = DCM_FALSE;
  LstProgConditions.ResponseRequired = DCM_FALSE;
  LstProgConditions.SecurityLevel = DCM_SEC_LEV_LOCKED;

  /* #6985 Clear PROG_CONDITIONS */
  /* polyspace +1 CERT-C:DCL39-C [Justified:Low] "This is Autosar structure. No Impact" */
  (void) Dcm_SetProgConditions(DCM_INITIAL, &LstProgConditions);

  /* Initialize variable for msgcontext Dcm_GstMsgContext */
  Dcm_GstMsgContext.reqData = &Dcm_GaaBufferArea[0];
  Dcm_GstMsgContext.reqDataLen = (Dcm_MsgLenType)0x00;
  Dcm_GstMsgContext.resData = &Dcm_GaaBufferArea[0];
  Dcm_GstMsgContext.resDataLen = (Dcm_MsgLenType)0x00;
  Dcm_GstMsgContext.msgAddInfo.reqType = (uint8)0x00;
  Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = (uint8)0x00;
  Dcm_GstMsgContext.resMaxDataLen = (Dcm_MsgLenType)0x00;
  Dcm_GstMsgContext.idContext = (Dcm_IdContextType)0x00;
  Dcm_GstMsgContext.dcmRxPduId = (PduIdType)0x00;

  /* Initialize variable that store the status of transmission */
  Dcm_TxRespStatus.ucNormResponse = DCM_FALSE;
  Dcm_TxRespStatus.ucNegResp = DCM_FALSE;
  Dcm_TxRespStatus.ucRespFailed = DCM_FALSE;
  Dcm_TxRespStatus.ucRespPending = DCM_FALSE;
  Dcm_TxRespStatus.ucFirstPageTrans = DCM_FALSE;
  Dcm_TxRespStatus.ucPagedTrans = DCM_FALSE;
  Dcm_TxRespStatus.ucFailedInd = DCM_FALSE;
  Dcm_TxRespStatus.ucDslPagedTrans = DCM_FALSE;

  /* Initialize variable for the negative response error */
  Dcm_GddNegRespError = DCM_POS_RESP;

  /* Initialize variable to store the subfunction of the service */
  Dcm_GucSubFunction = DCM_ZERO;

  /* Clear the bit flag for protocol status and provide transmit buffer */
  Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucOBDClearDTCStatus = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucProtclStatus = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucBufferProvided = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucPeriodicIdStatus = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucReportOBDDtc = DCM_FALSE;
  Dcm_PrtclTxBufStatus.ucCopyTxRejected = DCM_FALSE;

  /* Set the initial protocol priority to least value */
  Dcm_GucPrtclPriority = 0U;

  #if(DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
  Dcm_GucComCtrlMode = DCM_ENABLE_RX_TX_NORM_NM;
  #endif

  /* Clear the Status of the Protocol Priority array */
  Dcm_GaaProtclStatus[DCM_ZERO] = DCM_ZERO;

  Dcm_GblSendResponse = DCM_FALSE;
  Dcm_GblPduRTransmitResponse = DCM_FALSE;

  /* sg.baek 022305 - Task #2163 in redmine */
  Dcm_GblProcessNewRequest = DCM_FALSE;

  #if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
          (DCM_RESPONSE_ONEVENT_BLOCKID > 0))
  Dcm_GblNvMReadBlock = DCM_FALSE;
  #endif
  for (uint8 idx = 0U; idx < DCM_NUM_OF_PDUIDTABLECONFIG; idx++)
  {
    /* modified by youngjin.yun */
    if (NULL_PTR != Dcm_GaaPduIdTableConfig[idx].pPduIdStatus)
    {
      /* @Trace: Dcm_SUD_API_00075 */
      /* polyspace +1 RTE:IDP [Justified:Low] "Size of Dcm_GaaPduIdTableConfig is DCM_NUM_OF_PDUIDTABLECONFIG, so this pointer never outside its bounds" */
      *(Dcm_GaaPduIdTableConfig[idx].pPduIdStatus) = 0U;
    }
  }

  for (uint8 idx = 0U; idx < DCM_NUM_OF_PROTOCOLCONFIG; idx++)
  {
    /* modified by youngjin.yun */
    if (NULL_PTR != Dcm_GaaProtocolConfig[idx].pProtocolStatus)
    {
      /* @Trace:  Dcm_SUD_API_00079 */
      *(Dcm_GaaProtocolConfig[idx].pProtocolStatus) = 0U;
    }
  }

  #if (DCM_DSP_SECURITY_SERVICE == STD_ON)
  Dcm_GucSecurSequChk = 0u;
  #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
  Dcm_GaaCRLLength = 0U;
  #endif
  #endif

  /* @Trace: SWS_Dcm_01069 SWS_Dcm_00033 */
  for (uint16 idx = 0U; idx < (uint16) INIT_FUN_MAX_NUM; idx++)
  {
    /* @Trace: Dcm_SUD_API_00083 */
    Dcm_InitFunType InitFun = InitFunList[idx];

    if (InitFun != NULL_PTR)
    {
      /* @Trace: Dcm_SUD_API_00084 */
      InitFun(ConfigPtr);
    }
  }

  #if ((DCM_ECURESET_SERVICE == STD_ON) || \
      (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON))
  Dcm_GblExecuteECUReset = DCM_FALSE;
  #endif

  #if (DCM_ECURESET_SERVICE == STD_ON)
  Dcm_EcuReset_InitData();
  #endif

  #if (DCM_ROUTINECONTROL_SERVICE == STD_ON)
  Dcm_RidCtrl_InitData();
  #endif

  #if (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
  /* @Trace: SWS_Dcm_00866 SWS_Dcm_00867 */
  Dcm_DynDid_InitData(ConfigPtr);
  #endif

  #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  Dcm_Pdid_InitData();
  #endif

  /* Data init for upload download services */
  Dcm_InitUploadDownloadServices();

  /* Update the module status has Initialized */
  Dcm_GblInitStatus = DCM_INITIALIZED;
}

/*******************************************************************************
** Function Name        : Dcm_GetVersionInfo                                  **
**                                                                            **
** Service ID           : 0x24                                                **
**                                                                            **
** Description          : This service returns the version information of     **
**                        this module                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00003 SRS_BSW_00407 SRS_BSW_00482 */
/* @Trace: SWS_Dcm_00065 */
#if (DCM_VERSION_INFO_API == STD_ON)
FUNC(void, DCM_CODE) Dcm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DCM_APPL_DATA) VersionInfo)
{
  #if (DCM_DEV_ERROR_DETECT == STD_ON)
  /* @Trace: Dcm_SUD_API_00063 */
  uint8 ApiId = DCM_GET_VERSION_INFO_SID;

  /* Check init status and input argument */
  boolean ChkVal = Dcm_ChkInit(ApiId);
  CHK_NEXT(ChkVal, Dcm_ChkP2Var(ApiId, VersionInfo));

  if (DCM_TRUE == ChkVal)
  #endif
  {
    /* @Trace: Dcm_SUD_API_00064 */
    VersionInfo->vendorID = DCM_VENDOR_ID;
    VersionInfo->moduleID = DCM_MODULE_ID;
    VersionInfo->sw_major_version = DCM_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = DCM_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = DCM_SW_PATCH_VERSION;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_GetSesCtrlType                                  **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : This API provides the active session level value.   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : SesCtrlType                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddCurrentSession,         **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04011 */
/* @Trace: SWS_Dcm_00339 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType(
  P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SesCtrlType)
{
  /* @Trace: Dcm_SUD_API_00062 */
  Std_ReturnType RetVal = E_OK;

  uint8 ApiId = DCM_GET_SES_CTRL_TYPE_SID;
  boolean ChkVal = Dcm_ChkInit(ApiId);
  CHK_NEXT(ChkVal, Dcm_ChkP2Var(ApiId, SesCtrlType));

  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: Dcm_SUD_API_00061 */
    *SesCtrlType = Dcm_GddCurrentSession;
  }

  return RetVal;
}
#if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)
static FUNC(uint8, DCM_CODE) Dcm_InteralControlDTCCheckSession(
  Dcm_SesCtrlType SesCtrlType)
{
  uint8 RetVal = DCM_TRUE;
  Dcm_ServiceIdConfigConstPtrType pSidCfg = Dcm_GetServiceConfigPtr(DCM_CONTROLDTCSETTING);

  if (NULL_PTR != pSidCfg)
  {
    for (uint8 SesCtrlIdx = 0U; 
         SesCtrlIdx < pSidCfg->ucSessionCount; 
         SesCtrlIdx++)
    {
      if (SesCtrlType == pSidCfg->pSession[SesCtrlIdx])
      {
        RetVal = DCM_FALSE;
        break;
      }
    }
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : DslInternal_SetSesCtrlType                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API is to set the session level in the Dcm     **
**                        module                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : SesCtrlType                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) DslInternal_SetSesCtrlType
  (Dcm_SesCtrlType NewSesCtrlType)
{
  #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
  boolean resetIOControl = DCM_FALSE;
  #endif

  #if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
  boolean resetCommState = DCM_FALSE;
  #endif

  #if (DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)
  boolean resetDTCSetting = DCM_FALSE;
  #endif

  #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
  boolean resetSecurity = DCM_FALSE;
  #endif

  #if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_GblInitStatus == DCM_UNINITIALIZED)
  {
    /* @Trace: Dcm_SUD_API_00236 */
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_UNINIT);
  }
  else
  #endif
  {
    /* @Trace: Dcm_SUD_API_00235 */
    Dcm_GddOldSession = Dcm_GddCurrentSession;
    Dcm_GddCurrentSession = NewSesCtrlType;

    /* Refer to Figure 4-1 - Server diagnostic session state diagram of ES95486 */
    if (CHECK_DEFAULT_SESSION(Dcm_GddOldSession))
    {
      /* 1) default->default :
       *  server shall  re-initialize  the  defaultSession  completely.
       *  The  server  shall  reset  all activated/initiated/changed settings/
       *  controls during the activated session.
       *
       *  Note: This does not include long term changes programmed
       *  into non-volatile memory.
       */
      if (CHECK_DEFAULT_SESSION(NewSesCtrlType))
      {
        /* @Trace: Dcm_SUD_API_00238 */
        #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
        resetIOControl = DCM_TRUE;
        #endif

        #if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
        resetCommState = DCM_TRUE;
        #endif

        #if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)
        resetDTCSetting = DCM_TRUE;
        #endif

        #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
        resetSecurity = DCM_TRUE;
        #endif
      }
      /* 2) default-> any other session
       *  -. stop ROE
       */
      else
      {
        /* @Trace: Dcm_SUD_API_00237 */
        #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
        resetIOControl = DCM_FALSE;
        #endif

        #if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
        resetCommState = DCM_FALSE;
        #endif

        #if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)
        resetDTCSetting = DCM_FALSE;
        #endif

        #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
        resetSecurity = DCM_FALSE;
        #endif
      }
    }
    /* any other session(non-default session) */
    else
    {
      /* 3) any other session->any other session(or same session). 
       * The sever shall be:
       * -. initialize the diagnostic session
       * -. stop ROE
       * -. security relocked.
       * -. remain periodic scheduler
       * -. remain Communication state
       * -. remain ControlDTCSetting
       */
      if (CHECK_NONDEFAULT_SESSION(NewSesCtrlType))
      {
        /* @Trace: Dcm_SUD_API_00254 */
        #if (DCM_DSP_SECURITY_SERVICE == STD_ON)
        #if (DCM_REMAIN_UNLOCK_CONDITION == STD_ON)
        if (Dcm_GddOldSession == DCM_EXTENDED_DIAGNOSTIC_SESSION)
        {
          /* @Trace: Dcm_SUD_API_00252 */
          resetSecurity = DCM_FALSE;
        }
        else
        {
          /* @Trace: Dcm_SUD_API_00253 */
          resetSecurity = DCM_TRUE;
        }
        #else
        /* @Trace: Dcm_SUD_API_00251 */
        resetSecurity = DCM_TRUE;
        #endif
        #endif

        #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
        resetIOControl = DCM_FALSE;
        #endif

        #if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
        resetCommState = DCM_FALSE;
        #endif

        #if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)

        resetDTCSetting = Dcm_InteralControlDTCCheckSession(NewSesCtrlType);
        #endif
      }
      /* 4) any other session -> default session. The server shall
       * -. stop ROE.
       * -. security relocked.
       * -. stop periodic scheduler
       * -. reset CommunicationControl state
       * -. reset ControlDTCSetting
       * -. reset all activated/initiated/changed settings/controls
       *    during the activated session.
       *
       * Note: This does not include long
       *   term changes programmed into non-volatile memory.
       */
      else
      {
        /* @Trace: Dcm_SUD_API_00249 */
        #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
        resetIOControl = DCM_TRUE;
        #endif

        #if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
        resetCommState = DCM_TRUE;
        #endif

        #if(DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)
        resetDTCSetting = DCM_TRUE;
        #endif

        #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
        resetSecurity = DCM_TRUE;
        #endif
      }
    }

    #if(DCM_DSP_SECURITY_SERVICE == STD_ON)
    if (resetSecurity == DCM_TRUE)
    {
      /* @Trace: Dcm_SUD_API_00262 */
      /* If session is changed, we must send requestSeed again */
      Dcm_GucSecurSequChk = DCM_ZERO;

      /* Set global bit flag indicating the security seed request to FALSE */
      Dcm_DspServiceProcessingSts.ucSecSeedReq = DCM_FALSE;

      /* Cancel security access operation */
      Dcm_SecurityAccess_CancelOperation(&Dcm_GstMsgContext);

      /* @Trace: SWS_Dcm_00139 */
      DslInternal_SetSecurityLevel(DCM_SEC_LEV_LOCKED);

      /* @Trace: SRS_Diag_04208 */
      /* @Trace: SWS_Dcm_01329 */
      (void) SchM_Switch_Dcm_DcmSecurityAccess(DCM_SEC_LEV_LOCKED);
    }
    #endif

    /* Enable DTC Setting */
    #if (DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)
    if ((resetDTCSetting == DCM_TRUE)
        && (Dcm_GblDTCSettingDisabled == DCM_TRUE))
    {
      /* @Trace: SWS_Dcm_00751 */
      /* @Trace: Dcm_SUD_API_00266 */
      #if (DCM_DEM_CONFIGURED == STD_ON)
      (void)IDem_EnableDTCSetting();
      (void)SchM_Switch_Dcm_DcmControlDTCSetting(DCM_ENABLEDTCSETTING);
      Dcm_GblDTCSettingDisabled = DCM_FALSE;
      #endif
    }
    #endif

    /* Communucation State */
    #if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
    /* @Trace: SWS_Dcm_00860 */
    if (resetCommState == DCM_TRUE)
    {
      /* @Trace: Dcm_SUD_API_00269 */
      Dcm_GucComCtrlMode = DCM_ENABLE_RX_TX_NORM_NM;
      Dcm_SwitchCommMode_AllChannel(Dcm_GucComCtrlMode);
    }
    #endif

    /* Periodic sheduler */
    #if(DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
    Dcm_Pdid_HandleSessionOrSecurityChange();
    #endif

    /* IOControl */
    #if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
    if(resetIOControl == DCM_TRUE)
    {
      /* @Trace: SRS_Diag_04119 */
      /* @Trace: SWS_Dcm_00858 SWS_Dcm_00628 SWS_Dcm_00859 SWS_Dcm_01435 */
      /* @Trace: Dcm_SUD_API_00273 */
      Dcm_DspReturnControlToEcu();
    }
    #endif

    /* Handle for response on event (0x86) when session change */
    #if((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON))
    Dcm_DspROEProcessSessionChange();
    #endif
  }
}

/*******************************************************************************
** Function Name        : Dcm_ResetToDefaultSession                           **
**                                                                            **
** Service ID           : 0x2A                                                **
**                                                                            **
** Description          : allows the application to reset the current session **
**                        to Default session                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00520 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_ResetToDefaultSession(void)
{
  /* @Trace: Dcm_SUD_API_00221 */
  Std_ReturnType RetVal = E_OK;

  /* @Trace: SWS_Dcm_01062 */
  DslInternal_SetSesCtrlType(DCM_DEFAULT_SESSION);

  /* @Trace: SRS_Diag_04208 */
  (void) SchM_Switch_Dcm_DcmDiagnosticSessionControl(DCM_DEFAULT_SESSION);

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_GetActiveProtocol                               **
**                                                                            **
** Service ID           : 0x0F                                                **
**                                                                            **
** Description          : returns the active UDS protocol details             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ActiveProtocol, ConnectionId, TesterSourceAddress   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04011 */
/* @Trace: SWS_Dcm_00340 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetActiveProtocol(
  Dcm_ProtocolTypePtrType pActiveProtocolType
  , Dcm_Uint16PtrType pConnectionId
  , Dcm_Uint16PtrType pSourceTesterAddress)
{
  Std_ReturnType RetVal = E_OK;

  /* @Trace: Dcm_SUD_API_00059 */
  uint8 ApiId = DCM_GET_ACTIVE_PROTOCOL_SID;
  boolean ChkVal = Dcm_ChkInit(ApiId);
  CHK_NEXT(ChkVal, Dcm_ChkP2Var(ApiId, pActiveProtocolType));
  CHK_NEXT(ChkVal, Dcm_ChkP2Var(ApiId, pConnectionId));
  CHK_NEXT(ChkVal, Dcm_ChkP2Var(ApiId, pSourceTesterAddress));

  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: Dcm_SUD_API_00058 */
    Dcm_GetUdsActiveProtocolInfo(
      pActiveProtocolType, pConnectionId, pSourceTesterAddress);
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_GetObdProtocolId                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This API provides the current protocol Id           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Protocol Id                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this API.  **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblInitStatus,             **
**                        Dcm_GucObdProtocolIdentification                    **
**                        Function(s) invoked : (void)Det_ReportError         **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetObdProtocolId 
  (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ProtocolId)
{

  /* @Trace: Dcm_SUD_API_00062 */
  Std_ReturnType RetVal = E_OK;

  uint8 ApiId = DCM_GET_OBD_PROTOCOL_ID_SID;
  boolean ChkVal = Dcm_ChkInit(ApiId);
  CHK_NEXT(ChkVal, Dcm_ChkP2Var(ApiId, ProtocolId));

  if (DCM_TRUE == ChkVal)
  {
    /* Return the Protocol Id value which is currently active */
    if((Dcm_GddProtocolType == DCM_OBD_ON_UDS) || (Dcm_GddProtocolType == DCM_ZEV_ON_UDS))
    {
      *ProtocolId = DCM_PROTOCOLID_J1979_2_OBD_ON_UDS;
    }
    else if((Dcm_GddProtocolType == DCM_OBD_ON_CAN) || (Dcm_GddProtocolType == DCM_OBD_ON_FLEXRAY) 
         || (Dcm_GddProtocolType == DCM_OBD_ON_IP) )
    {
      *ProtocolId = DCM_PROTOCOLID_J1979_OBD2;
    }
    else
    {
      *ProtocolId = DCM_PROTOCOLID_OBD_NONE;
    }

  }
  else
  {
    RetVal = E_NOT_OK;
  }
  
  return RetVal;
}

/*******************************************************************************
** Function Name       : Dcm_MainFunction                                     **
**                                                                            **
** Service ID          : 0x25                                                 **
**                                                                            **
** Description         : This service is used for processing the tasks of     **
**                        the main loop. It is called periodically as cyclic  **
**                        task by the software system. In this function all   **
**                        scheduled functions will be integrated              **
**                                                                            **
** Sync/Async          : Synchronous                                          **
**                                                                            **
** Re-entrancy         : Non-Reentrant                                        **
**                                                                            **
** Input Parameters    : None                                                 **
**                                                                            **
** InOut parameter     : None                                                 **
**                                                                            **
** Output Parameters   : None                                                 **
**                                                                            **
** Return parameter    : void                                                 **
**                                                                            **
** Preconditions       : Dcm_Init should be called before calling this API.   **
**                                                                            **
** Remarks             : Global Variable(s) : Dcm_GblInitStatus               **
**                                                                            **
**                       Function(s) invoked:                                 **
**                       Dcm_GetNextRequestFromQueue,                         **
**                       Dcm_Internal_UpdateTime,                             **
**                       Dcm_Internal_ChkResponseTime,                        **
**                       Dcm_Internal_ChkS3ServerTime,                        **
**                       Dcm_Internal_ChkUpdatePage,                          **
**                       Dcm_Internal_ServicesPending,                        **
**                       Dcm_Internal_TransmitResponse,                       **
**                       Dcm_Internal_ProcessRequest,                         **
**                       Dcm_Internal_GblFirstCallToMain,                     **
**                       Dcm_Internal_ChkCommunicationMode,                   **
**                       Dcm_Periodic_Did_MainFunction,                       **
**                       Dcm_Internal_ChkControlDTCSetting,                   **
**                       Dcm_AddCurrentPendingRequestToQueue                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00373 SRS_BSW_00424 */
/* @Trace: SWS_Dcm_00053 */
FUNC(void, DCM_CODE) Dcm_MainFunction(void)
{
  /* Check whether the module is Initialized */
  if (Dcm_GblInitStatus != DCM_UNINITIALIZED)
  {
    /* @Trace: SRS_Diag_04021 SRS_Diag_04032 SRS_Diag_04209 */
    /* @Trace: Dcm_SUD_API_00174 */
    #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
    Dcm_GetNextRequestFromQueue();
    #endif

    /* Process sequence:
     *
     * 1. P2Server timing : if P2Service timer is expired, 
     *    Dcm shall response the 0x78 immediately
     * 2. S3Server timimg : if S3 Service timer is expired, 
     *    Dcm shall be initialized according to specification
     * 3. Process of the pended request
     * 4. Tx transmission: response of normal request or pended request
     * 5. New request's process
     */

    /* This function have the highest priority in Dcm_MainFunction(). */
    Dcm_Internal_UpdateTime();

    /* P2 Server time : 0x78 */
    Dcm_Internal_ChkResponseTime();

    /* if S3 Service timing timeout, session will be default session */
    Dcm_Internal_ChkS3ServerTime();

    /* Also consider paged services UDS + OBD remaining */
    #if ((DCM_PAGEDBUFFER_ENABLED == STD_ON) \
         && ((DCM_READDTC_SUPPORT == STD_ON) \
             || (DCM_OBD_SUPPORT == STD_ON)))
    /* This function shoud be above Dcm_Internal_ProcessTxRx(). */
    Dcm_Internal_ChkUpdatePage();
    #endif

    /* To process pending services (include Tx transmission) */
    /* This function should be above Rx request  */
    Dcm_Internal_ServicesPending();

    /* Tx shall be processed before Request is processed */
    Dcm_Internal_TransmitResponse();

    Dcm_Internal_ProcessRequest();

    #if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
        (DCM_RESPONSE_ONEVENT_BLOCKID > 0))
    if (Dcm_GblNvMReadBlock == DCM_FALSE)
    {
      Dcm_ReadRoeNonVolatileData(); 
    }
    #endif
    Dcm_Internal_GblFirstCallToMain();

    #if ((DCM_ECURESET_SERVICE == STD_ON) || \
         (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON))
    if(Dcm_GblExecuteECUReset == DCM_TRUE)
    {
      Dcm_GblExecuteECUReset = DCM_FALSE;
      (void)SchM_Switch_Dcm_DcmEcuReset(DCM_EXECUTE);
    }
    #endif

    #if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) \
         && (DCM_MODE_RULE == STD_ON) \
         && (DCM_DSP_COMM_CONTROL_CONFIGURED == STD_ON))
    Dcm_Internal_ChkCommunicationMode();
    #endif

    #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
    Dcm_Periodic_Did_MainFunction();
    #endif

    /* This routine shall be execute at the end of mainfunction
      modified by youngjin.yun*/
    #if ((DCM_DSP_CONTROL_DTC_SERVICE == STD_ON) \
         && (DCM_MODE_RULE == STD_ON) \
         && (DCM_DSP_CONTROL_DTC_CONFIGURED == STD_ON))
    Dcm_Internal_ChkControlDTCSetting();
    #endif

    #if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
    Dcm_AddCurrentPendingRequestToQueue();
    #endif
  }
  else
  {
    /* @Trace: Dcm_SUD_API_00173 */
    /* Do no thing in this case */
  }
}

/*******************************************************************************
** Function Name        : Dcm_MemoryServicesMainFunction                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used for processing the tasks of    **
**                        the main loop for Memory related  services          **
**                        It is called periodically as cyclic task by the     **
**                        software system.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) \
     || (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_MemoryServicesMainFunction(
  Dcm_IdContextType IdContext)
{
  /* @Trace: Dcm_SUD_API_00182 */
  if (Dcm_TxRespStatus.ucNegResp == DCM_FALSE)
  {
    /* @Trace: Dcm_SUD_API_00185 */
    #if (DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
    /* @Trace: SWS_Dcm_00840 */
    if ((DCM_UDS_READ_MEMORY_BY_ADDRESS == IdContext)
        && ((DCM_TRUE == Dcm_MemServicePendingStatus.ucReadMemPendingStatus)
        || ((DCM_TRUE == Dcm_ServiceForcePendingStatus.ucReadMemForcePendingStatus)
        && (DCM_TRUE == Dcm_GblRespPendConfirmation))))
    {
      /* @Trace: Dcm_SUD_API_00184 */
      Dcm_GblRespPendConfirmation = DCM_FALSE;
      Dcm_DcmReadMemoryCall(&Dcm_GstMsgContext);
    }
    #endif

    #if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
    /* @Trace: SWS_Dcm_00838 */
    if ((DCM_UDS_WRITE_MEMORY_BY_ADDRESS == IdContext)
        && ((DCM_TRUE == Dcm_MemServicePendingStatus.ucWriteMemPendingStatus)
        || ((DCM_TRUE == Dcm_ServiceForcePendingStatus.ucWriteMemForcePendingStatus)
        && (DCM_TRUE == Dcm_GblRespPendConfirmation))))
    {
      /* @Trace: Dcm_SUD_API_00187 */
      Dcm_GblRespPendConfirmation = DCM_FALSE;
      Dcm_DcmWriteMemoryCall(&Dcm_GstMsgContext);
    }
    #endif
  }

  DCM_UNUSED(IdContext);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DIDServicesMainFunction                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used for processing the tasks of    **
**                        the main loop for DID related services.             **
**                        It is called periodically as cyclic task by the     **
**                        software system.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_DidServicesMainFunction(void)
{
  /* @Trace: Dcm_SUD_API_00001 */
  #if (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_ReadScalingInfo_PendingOperation(&Dcm_GstMsgContext);
  #endif

  #if (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_DspIOCtrl_PendingOperation(&Dcm_GstMsgContext);
  #endif

  #if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_WriteDid_PendingOperation(&Dcm_GstMsgContext);
  #endif

  #if(DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
  if (Dcm_ServicePendingStatus.ucReadDataPendingStatus == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_00010 */
    /* TODO: if Periodic DID is running, periodic context shall be used */
    Dcm_DspInternal_DcmReadDataByIdentifier(DCM_PENDING, &Dcm_GstMsgContext);

    /* Dcm_ServicePendingStatus.ucReadDataPendingStatus is changed
     * in the Dcm_DspInternal_DcmReadDataByIdentifier */
    if (Dcm_ServicePendingStatus.ucReadDataPendingStatus != DCM_TRUE)
    {
      /* Check if the negative response needs to be updated here */
      if (Dcm_GddNegRespError != DCM_POS_RESP)
      {
        /* @Trace: Dcm_SUD_API_00013 */
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }

      /* @Trace: Dcm_SUD_API_00014 */
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
    }
  }
  #endif

  #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  Dcm_Pdid_PendingOperation(&Dcm_GstMsgContext);
  #endif
}
#endif


/*******************************************************************************
** Function Name        : Dcm_DtcServicesMainFunction                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Main function to process pending operation for      **
**                        DTC services                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : IdContext                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_RPT_DTC == STD_ON) || \
     (DCM_RPT_NOOFDTC == STD_ON) || \
     (DCM_RPT_DTC_FLT_DET_CTR == STD_ON) || \
     (DCM_DSP_CLR_DIAG_SERVICE == STD_ON) || \
     (DCM_FAULT_DETECTION_COUNTER == STD_ON) || \
     (DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON))
static FUNC(void, DCM_CODE) Dcm_DtcServicesMainFunction(
  Dcm_IdContextType IdContext)
{
  /* @Trace: Dcm_SUD_API_00019 */
  #if (DCM_DSP_CLR_DIAG_SERVICE == STD_ON)
  if ((DCM_UDS_CLEAR_DIAG_INFO == IdContext)
      && (DCM_TRUE == Dcm_PrtclTxBufStatus.ucClearDTCStatus))
  {
    /* @Trace: Dcm_SUD_API_00020 */
    (void) Dcm_DspClearDiagInfo(Dcm_GulDTCValue, &Dcm_GstMsgContext);
  }
  #endif

  #if (DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
  if (Dcm_GblNumFilterDTCStatusBySevirtMask == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_00024 */
    /* Invoke internal function */
    Dcm_GetNumberOfFilteredDtcBySeverityInfo();

    if (Dcm_GblNumFilterDTCStatusBySevirtMask == DCM_FALSE)
    {
      /* Check if the negative response needs to be updated here */
      if (Dcm_GddNegRespError != DCM_POS_RESP)
      {
        /* @Trace: Dcm_SUD_API_00027 */
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }

      /* @Trace: Dcm_SUD_API_00028 */
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
    }
  }
  #endif

  #if(DCM_RPT_NOOFDTC == STD_ON)
  if (Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_00031 */
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext;

    #if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
      (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
    uint8 IsPrtclType2 = Dcm_IsProtocolType2(Dcm_GddRxPduId);

    if ((Dcm_GucResOnEventStatus == DCM_ROEONGOING) && 
      (DCM_TRUE == IsPrtclType2))
    {
      /* @Trace: Dcm_SUD_API_00036 */
      pMsgContext = Dcm_GpRoeMsgContext;
    }
    else
    #endif
    {
      /* @Trace: Dcm_SUD_API_00037 */
      pMsgContext = &Dcm_GstMsgContext;
    }

    /* Invoke internal function */
    Dcm_DemGetNumberOfFilteredDtc(pMsgContext);

    if (Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus == DCM_FALSE)
    {
      /* Check if the negative response needs to be updated here */
      if (Dcm_GddNegRespError != DCM_POS_RESP)
      {
        /* @Trace: Dcm_SUD_API_00040 */
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(pMsgContext, Dcm_GddNegRespError);
      }

      /* @Trace: Dcm_SUD_API_00041 */
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(pMsgContext);
    }
  }
  #endif

  #if(DCM_RPT_DTC == STD_ON)
  if (Dcm_PrtclTxBufStatus.ReportNumOfDtc == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_00043 */
    /* Invoke internal function */
    Dcm_DemGetNumberOfReportedDTC();

    if ((Dcm_PrtclTxBufStatus.ReportNumOfDtc == DCM_FALSE) &&
      (Dcm_DspSerPgStatus.ucPagingStarted != DCM_TRUE))
    {
      #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
      Dcm_InternalTroubleCodeService = DCM_FALSE;
      #endif

      /* Check if the negative response needs to be updated here */
      if (Dcm_GddNegRespError != DCM_POS_RESP)
      {
        /* @Trace: Dcm_SUD_API_00047 */
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }

      /* @Trace: Dcm_SUD_API_00048 */
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
    }
  }
  #endif

  #if ((DCM_FAULT_DETECTION_COUNTER == STD_ON) || \
    (DCM_RPT_DTC_FLT_DET_CTR == STD_ON))
  if ((Dcm_GblFaultDetectionCounter == DCM_TRUE) || 
    (Dcm_GblDTCFDCPending == DCM_TRUE))
  {
    if(Dcm_GblFaultDetectionCounter == DCM_TRUE)
    {
      /* @Trace: Dcm_SUD_API_00051 */
      Dcm_DspRptDTCFltDetCtr(&Dcm_GstMsgContext);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_00052 */
      (void) Dcm_DspReadReqdDTCFDC(Dcm_GulFDCRespSize);

      if(Dcm_GblDTCFDCPending == DCM_FALSE)
      {
        /* Check if the negative response needs to be updated here */
        if(Dcm_GddNegRespError != DCM_POS_RESP)
        {
          /* @Trace: Dcm_SUD_API_00054 */
          /* Report the NRC to the DSD layer */
          Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
        }

        /* @Trace: Dcm_SUD_API_00055 */
        /* Transmit the response to the DSD layer */
        Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
      }
    }
  }
  #endif

  DCM_UNUSED(IdContext);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ObdServicesMainFunction                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Main function to process pending operation for      **
**                        OBD services                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : IdContext                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
     (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || \
     (DCM_OBD_GETDTC_0A_SERVICE == STD_ON) || \
     (DCM_OBD_CLRRESET_EMISSION_DIAGINFO_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_ObdServicesMainFunction(
  Dcm_IdContextType IdContext)
{
  /* @Trace: Dcm_SUD_API_00191 */
  #if (DCM_OBD_CLRRESET_EMISSION_DIAGINFO_SERVICE == STD_ON)
  if ((DCM_OBD_CLEAR_DIAG_INFO == IdContext)
      && (DCM_TRUE == Dcm_PrtclTxBufStatus.ucOBDClearDTCStatus))
  {
    /* @Trace: Dcm_SUD_API_00190 */
    (void) Dcm_DcmOBDClrResetEmissionDiagInfo(
      DCM_PENDING, &Dcm_GstMsgContext, NULL_PTR);
  }
  #endif

  #if ((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
    (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || \
    (DCM_OBD_GETDTC_0A_SERVICE == STD_ON))
  if(Dcm_PrtclTxBufStatus.ucReportOBDDtc == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_00192 */
    /* Invoke internal function */
    Dcm_DemGetNumberOfOBDDTC();

    if((Dcm_PrtclTxBufStatus.ucReportOBDDtc == DCM_FALSE) &&
      (Dcm_DspSerPgStatus.ucPagingStarted != DCM_TRUE))
    {
      /* Check if the negative response needs to be updated here */
      if (Dcm_GddNegRespError != DCM_POS_RESP)
      {
        /* @Trace: Dcm_SUD_API_00195 */
        /* Report the NRC to the DSD layer */
        Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);
      }

      /* @Trace: Dcm_SUD_API_00196 */
      /* Transmit the response to the DSD layer */
      Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
    }
  }
  #endif

  DCM_UNUSED(IdContext);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_Periodic_Did_MainFunction                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used for processing the tasks of    **
**                        the main loop for read Periodic DID service.        **
**                        It is called periodically as cyclic task by the     **
**                        software system.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_Periodic_Did_MainFunction (void)
{
  /* @Trace: Dcm_SUD_API_00199 */
  if (DCM_TRUE == Dcm_GddPerStatus.blOnResTrans)
  {
    /* @Trace: Dcm_SUD_API_00198 */
    boolean LblTimerExpired;
    uint16 LusTimerIdx = DCM_ZERO;
    uint8 LucTimerFlag = DCM_FALSE;

    uint16 LusIdx = DCM_ZERO;
    uint16 LusDid = DCM_ZERO;
    uint32 LaaTimerRate[DCM_PDID_NUM_OF_TIMER] =
    {
      DCM_PDID_SLOW_RATE, DCM_PDID_MEDIUM_RATE, DCM_PDID_FAST_RATE
    };

    Dcm_Periodic_Did_FirstResponse(&LucTimerFlag);

    /* Determine if timer is expired and put PDID to scheduled queue */
    for (LusIdx = DCM_ZERO; LusIdx < (uint16) DCM_PDID_NUM_OF_TIMER; LusIdx++)
    {
      /* @Trace: Dcm_SUD_API_00202 */
      /* polyspace +2 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
      LusTimerIdx = LusIdx + (uint16) DCM_PDID_SLOW_TIMER;
      LblTimerExpired = Dcm_IsTimerExpired((Dcm_TimerType) LusTimerIdx);

      if ((DCM_TRUE == LblTimerExpired) &&
          (DCM_ZERO != Dcm_GddPerSchInfo.pTimerCount[LusIdx]))
      {
        /* @Trace: Dcm_SUD_API_00201 */
        /* Return E_NOT_OK in case the queue is full */
        (void) Dcm_Pdid_EnqueueDataByMode((uint8) LusIdx + DCM_ONE);

        /* @Trace: SWS_Dcm_01102 */
        /* polyspace +1 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
        Dcm_StartTimer((Dcm_TimerType) LusTimerIdx, LaaTimerRate[LusIdx]);
      } 
      else if ((DCM_TRUE == LucTimerFlag) 
          && (DCM_ZERO != Dcm_GddPerSchInfo.pTimerCount[LusIdx]))
      {
        /* polyspace +1 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
        Dcm_StartTimer((Dcm_TimerType) LusTimerIdx, LaaTimerRate[LusIdx]);
      }
      else 
      {
        // Do Nothing
      }
    }

    /* Get periodic tx connection reference */
    Dcm_PeriodicTxPduPtrType LpPerTxPdu = Dcm_GetPeriodicTxPduInfo(
      Dcm_GddPerStatus.ddRxPduId, Dcm_GddPerStatus.ucTxPduIdx);

    /* @Trace: SWS_Dcm_01103 */
    if ((NULL_PTR != LpPerTxPdu) &&
        (DCM_FALSE == LpPerTxPdu->blBusyStatus))
    {
      /* Return E_NOT_OK in case the queue is empty
       * Waiting for next timer expired event to retrieve data */
      if (E_OK == Dcm_Pdid_DequeueData(&LusDid))
      {
        /* @Trace: Dcm_SUD_API_00205 */
        LpPerTxPdu->blBusyStatus = DCM_TRUE;

        /* Set index for data info */
        Dcm_GddPerStatus.ucDataInfoIdx = LpPerTxPdu->ucDataBufferId;

        /* Remove high byte of PDID */
        LusDid = (uint8) (LusDid & DCM_MAXVALUE);

        /* @Trace: SWS_Dcm_01106 */
        (void) DslInternal_ResponseOnOneDataByPeriodicId((uint8) LusDid);
      }
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ROE_MainFunction                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used for processing the tasks of    **
**                        the main loop for Response on Event service.        **
**                        It is called periodically as cyclic task by the     **
**                        software system.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_ROE_MainFunction(void)
{
  #if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_CONST) LpRoeInternalBuffer;
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_PRIVATE_CONST)LpPduIdTable;
  uint16 LusDIDSize;
  uint8 LucRoeTempBuffer[DCM_ROE_DID_MAX_DATA_LENGTH];
  uint8 LucIndexCount;
  uint8 LucNetworkId;
  Std_ReturnType LddReturnValue;
  boolean LblCompareResult;
  #endif  
  /* @Trace: Dcm_SUD_API_00206 */
  Std_ReturnType ROEEventTriggered;
  uint8 InterMessageTimerExpired;
  uint8 InterMessageTimerStarted;
  InterMessageTimerExpired = Dcm_IsTimerExpired(DCM_ROE_INTERMESSAGE_TIMER);
  InterMessageTimerStarted = Dcm_IsTimerStarted(DCM_ROE_INTERMESSAGE_TIMER);

  /* @Trace: SWS_Dcm_00601 */
  if ((DCM_TRUE == InterMessageTimerExpired)
      ||(DCM_FALSE == InterMessageTimerStarted))
  {
    ROEEventTriggered = Dcm_CheckRoeEventTriggered();
    if (ROEEventTriggered == E_OK)
    {
      Dcm_StartTimer(DCM_ROE_INTERMESSAGE_TIMER, DCM_ROE_INTER_MESSAGE_TIME);
      Dcm_SetFirstActivatedEvent();
    }
  }

  /*Only excute this task once no one was excuting */
  /* @Trace: SWS_Dcm_00558 */
  if ((DCM_FALSE == Dcm_GblNormalReq) && 
      (DCM_ROE_IDLE == Dcm_GucResOnEventStatus))
  {
    /* @Trace: Dcm_SUD_API_00209 */
    uint8 Dcm_CurrentROEEventIdx = Dcm_GetCurrentROEEventIndex();

    if (Dcm_CurrentROEEventIdx < DCM_NUM_OF_ROE_EVENT_CONFIG) 
    {
      /* Previous triggered event flag */
      uint8 Dcm_ROE_EventTriggerd = Dcm_GetROEEventTriggerdFlag(Dcm_CurrentROEEventIdx);
      if (Dcm_ROE_EventTriggerd == DCM_TRUE)
      {
        /* @Trace: Dcm_SUD_API_00211 */
        uint16 ConnectionId;
        PduIdType RxPduId;
        RxPduId = Dcm_GddRoeRequestInfo[Dcm_CurrentROEEventIdx].ddRoeRxPduId;
        ConnectionId = Dcm_GaaPduIdTableConfig[RxPduId].RxConnectionId;

        (void) DslInternal_ResponseOnOneEvent(
          &Dcm_GddRoeRequestInfo[Dcm_CurrentROEEventIdx].RoeReqData[DCM_ZERO]
          , Dcm_GddRoeRequestInfo[Dcm_CurrentROEEventIdx].ddRoeReqDataLen
          , ConnectionId);
      }
      Dcm_SetNextActivatedEvent();
    }
  }
  
  #if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
  /* ROE - DID internal management */
  /* @Trace: Dcm_SUD_API_00214 */
  LusDIDSize = DCM_ZERO;
  Dcm_MemClear(LucRoeTempBuffer, DCM_ROE_DID_MAX_DATA_LENGTH);
  LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GpRoeMsgContext->dcmRxPduId];
  LucNetworkId = LpPduIdTable->ComMChannelId;

  if (Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION)
  {
    for(LucIndexCount = DCM_ZERO; LucIndexCount < DCM_NUM_OF_ROE_EVENT_CONFIG; LucIndexCount++)
    {
      if((Dcm_GddRoeRequestInfo[LucIndexCount].ucCurrentState == DCM_ROE_STARTED) &&
         (Dcm_GddRoeRequestInfo[LucIndexCount].RoeConfig.blIsOnChngOfDIDRxed == DCM_TRUE))
      {
        /* @Trace: Dcm_SUD_API_00217 */
        LpRoeInternalBuffer = &Dcm_GddRoeRequestInfo[LucIndexCount].ucInternalBuffer[DCM_ZERO];

        /* Get the DID Data Value to the temp buffer */
        LddReturnValue = Dcm_DspReadROEDIDValue(
                          *(Dcm_GddRoeRequestInfo[LucIndexCount].RoeConfig.pRoeDidRef),
                            &LusDIDSize, &LucRoeTempBuffer[DCM_ZERO]);

        if (E_OK == LddReturnValue)
        {
          /* @Trace: Dcm_SUD_API_00218 */
          LblCompareResult = Dcm_MemCompare(
            &LucRoeTempBuffer[DCM_ZERO]
            , LpRoeInternalBuffer
            , LusDIDSize, DCM_EQUALS_NOT);

          /* Update DID value size */
          Dcm_GddRoeRequestInfo[LucIndexCount].usDIDValueSize = LusDIDSize;

          /* If the new value of the DID is different from the previous value
           copy the data to the buffer used to store the DID value during
           ROE execution */
          if (LblCompareResult == DCM_TRUE)
          {
            /* @Trace: Dcm_SUD_API_00219 */
            Dcm_StoreRoeEventTriggeredInfo(LucIndexCount);
          }
        }
      }
    }
  }
  #endif // End of DCM_DIDSERVICE_SUPPORT_ENABLE
}
#endif //DCM_RESPONSE_ON_EVENT_SERVICE

/*******************************************************************************
** Function Name        : Dcm_TriggerOnEvent                                  **
**                                                                            **
** Service ID           : 0x2D                                                **
**                                                                            **
** Description          : This API function allows to trigger an event linked **
**                        to a ResponseOnEvent request.                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : RoeEventId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_TriggerOnEvent(uint8 RoeEventId)
{
  /* @Trace: Dcm_SUD_API_00222 */
  Std_ReturnType LddReturnValue = E_NOT_OK;

  #if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
       (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON))
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_PRIVATE_CONST) LpPduIdTable;
  uint8 LucNetworkId;
  uint8 LucIndex = DCM_MAXVALUE;

  /* Initialize pointer to PduId table corresponding to the RxPduId */
  LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GpRoeMsgContext->dcmRxPduId];
  LucNetworkId = LpPduIdTable->ComMChannelId;

  /* @Trace: SWS_Dcm_00135 */
  if (Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION)
  {
    /* @Trace: Dcm_SUD_API_00225 */
    LddReturnValue = Dcm_InternalValidateRoeEventId(RoeEventId, &LucIndex);
    if ((E_OK == LddReturnValue) && (LucIndex < DCM_NUM_OF_ROE_EVENT_CONFIG))
    {
      /* @Trace: SWS_Dcm_00920 */
      /* @Trace: Dcm_SUD_API_00226 */
      Dcm_StoreRoeEventTriggeredInfo(LucIndex);
    }
  }
  #else
  DCM_UNUSED(RoeEventId);
  #endif

  return LddReturnValue;
}

/*******************************************************************************
** Function Name        : Dcm_InternalValidateRoeEventId                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal validate roe event identifier              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RoeEventId                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pIndex                                              **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
       (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_InternalValidateRoeEventId(
  uint8 RoeEventId
  , Dcm_Uint8PtrType pIndex)
{
  /* @Trace: Dcm_SUD_API_00094 */
  Std_ReturnType RetVal = E_NOT_OK;

  if (pIndex != NULL_PTR)
  {
    /* @Trace: Dcm_SUD_API_00095 */
    for (uint8 idx = DCM_ZERO; idx < DCM_NUM_OF_ROE_EVENT_CONFIG; idx++)
    {
      if ((Dcm_GddRoeRequestInfo[idx].ucCurrentState == DCM_ROE_STARTED) &&
          (Dcm_GddRoeRequestInfo[idx].RoeConfig.blIsOnChngOfDIDRxed == DCM_TRUE) &&
          (RoeEventId == Dcm_GddRoeRequestInfo[idx].RoeConfig.ucRoeEventId))
      {
        /* @Trace: Dcm_SUD_API_00096 */
        RetVal = E_OK;
        *pIndex = idx;
        break;
      }
    }
  }

  return RetVal;
}
#endif

#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_Periodic_Did_FirstResponse(
  Dcm_Uint8PtrType pTimerUpdated)
{
  uint16 LusIndex = DCM_ZERO;
  Dcm_PeriodicDidInfoPtrType LpPerDidInfo = NULL_PTR;
  Std_ReturnType LddRetVal = E_OK;

  while ((LusIndex < DCM_TOTAL_NUM_OF_PDID) && (E_OK == LddRetVal))
  {
    LpPerDidInfo = Dcm_CfgInternal_GetPdidInfo(LusIndex);
    /* immediately response in first time */
    if ((DCM_TRUE == LpPerDidInfo->blActive) 
       && (DCM_PDID_FIRST_RESPONSE == LpPerDidInfo->ucStatus))
    {
      LpPerDidInfo->ucStatus = DCM_PDID_SCHEDULER_RESPONSE;
      LddRetVal = Dcm_Pdid_EnqueueData(LpPerDidInfo->usDid);
      if ((NULL_PTR != pTimerUpdated) && (E_OK == LddRetVal))
      {
        *pTimerUpdated = DCM_TRUE;
      }
    }
    LusIndex++;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_GetGblReset                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Return value of Dcm_GblReset for EthDiag            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_GblReset                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/

FUNC(boolean, DCM_CODE) Dcm_GetGblReset(void)
{
  return Dcm_GblReset;
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"


/* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
