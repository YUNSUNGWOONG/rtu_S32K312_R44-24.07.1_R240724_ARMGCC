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
**  SRC-MODULE: Dcm_DspMain.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Contain the Paged Buffer processing and the Confirmation      **
**              at DSP level                                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     31-Dec-2019   HueKM          AR440 Implementation                **
** 0.0.2     05-May-2019   LamNV10        Change page buffer machanism for    **
**                                        service 0x19 sub 04 06 10 18 19     **
** 0.0.3     16-Aug-2020   HueKM          Fix defect and coding rules         **
** 0.0.4     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.5     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.1     23-Mar-2022   LanhLT         Change code as per #22736           **
** 1.0.7     16-Dec-2022   LanhLT         Fix UNECE                           **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Types.h"
#include "Dcm_Ram.h"
#include "Dcm_DspMain.h"
#include "Dcm_DslInternal.h"
#include "Dcm_DspReadDTCInfo.h"
#include "Dcm_DspReadSSDTCInfo.h"
#include "Rte_Dcm.h"

#include "Dcm_DspEcuReset.h"

#include "SchM_Dcm.h"
#include "BswM_Dcm.h"
#include "Dcm_Externals.h"
#if(DCM_DEM_CONFIGURED == STD_ON)
#include "Dem.h"
#endif
#include "Dcm_DspOBDInternals.h"
#include "Dcm_DspServices.h"
#include "Dcm_DslManageSecurity.h"

#include "Dcm_DsdInternal.h"
#include "ComM_Dcm.h"
#include "Dcm_Config.h"
#include "Dcm_Utils.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dcm_DemInterfaces.h"
#endif

/*******************************************************************************
**                      Function Definitions
*******************************************************************************/
#if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) \
     || (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))

#define DCM_START_SEC_CODE
#include "MemMap.h"

static FUNC(void, DCM_CODE) DcmCommControlConfirmation(
  Dcm_IdContextType IdContext
  , Dcm_ConfirmationStatusType ConfirmStatus);

#if (DCM_STANDARD_SUPPORT == DCM_ISO14229_SUPPORT)
typedef P2FUNC(uint8, DCM_CODE, Dcm_JudgeComCtrlModeFunType)(
  uint8 ControlType);

static FUNC(uint8, DCM_CODE) DcmJudgeComCtrlMode(
  uint8 ControlType,
  uint8 communicationType);

static FUNC(uint8, DCM_CODE) DcmJudgeEnableRxAndTx(
  uint8 communicationType);

static FUNC(uint8, DCM_CODE) DcmJudgeEnableRxAndDisableTx(
  uint8 communicationType);

static FUNC(uint8, DCM_CODE) DcmJudgeDisableRxAndEnableTx(
  uint8 communicationType);

static FUNC(uint8, DCM_CODE) DcmJudgeDisableRxAndTx(
  uint8 communicationType);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
** Function Name        : Dcm_DspUpdatePage                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function that provides the page **
**                        buffering handling for the sub functions 0x02,      **
**                        0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x0f, 0x10 and  **
**                        0x13 in DSP sub module                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PageBufPtr, PageLen                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_DspSerPgStatus, Dcm_GpReqResData,               **
**                        Dcm_GulBufferSize                                   **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspUpdatePage(
  Dcm_MsgType PageBufPtr, Dcm_MsgLenType PageLen)
{
  /* @Trace: Dcm_SUD_API_01605 */
  /* Reset the error code variable */
  Dcm_GddNegRespError = DCM_POS_RESP;

  /* polyspace +2 MISRA2012:18.6 [Justified:Low] Justify with annotations */
  /* Update the global pointer to the response buffer */
  Dcm_GpReqResData = PageBufPtr;

  /* Update the response buffer size */
  Dcm_GulBufferSize = PageLen;

  /* Set the global bit flag indicating that DSP update page is called */
  Dcm_DspSerPgStatus.ucUpdatePageStarted = DCM_TRUE;
}
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DspProcessUpdatePage                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function that provides the page **
**                        buffering handling for the sub functions            **
**                        0x04, 0x05, 0x06, 0x08, 0x09, 0x0A, 0x10 and        **
**                        in DSP sub module                                   **
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
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_DspSerPgStatus,                                 **
**                        Dcm_GpReqResData, Dcm_GulBufferSize,Dcm_GucPIDCount **
**                        Dcm_GucRecordNumber, Dcm_GpMsgContext,              **
**                        Dcm_DspSerPgStatus , Dcm_GucNumofDTC                **
**                        Dcm_GaaPduIdTableConfig , Dcm_GddRxPduId            **
**                        Dcm_GaaBufferConfig                                 **
**                        Function(s) invoked : Dcm_DspReadReqdDTCInfo,       **
**                        Dcm_DspUpdDTCBySeverityMask,                        **
**                        Dcm_DspProcessSubFFDataOrExtData,                   **
**                        Dcm_DspUpdtBasicsOfFreezeFrame,                     **
**                        Dcm_ProcessPage, Dcm_SetNegResponse,                **
**                        Dcm_ProcessingDone, Dcm_DspReadOBD_AvlInfo,         **
**                        Dcm_DspReadOBD_1_DemInfo                            **
*******************************************************************************/
#if ((DCM_PAGEDBUFFER_ENABLED == STD_ON) && \
    ((DCM_READDTC_SUPPORT == STD_ON) || (DCM_OBD_SUPPORT == STD_ON)))
FUNC(void, DCM_CODE) Dcm_DspProcessUpdatePage(void)
{
  /* @Trace: Dcm_SUD_API_01520 */
  uint32 LulFilledPgLen = DCM_ZERO;

  #if ((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
       (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || \
       (DCM_OBD_GETDTC_0A_SERVICE == STD_ON) || \
       (DCM_RPT_DTC == STD_ON) || \
       (DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON) || \
       (DCM_RPT_DTCBYSEVERITYINFOFDTC == STD_ON))
  uint8 LucFixedFilledPgLen;
  #endif

  #if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
       (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
       (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
       (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))
  P2VAR (uint8, AUTOMATIC, DCM_APPL_DATA) LpRxBuffer;
  P2VAR (uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer;
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) LpDcmPduIdTable;

  uint8 LucRxTxBufferId;
  uint8 LucPIDCount;
  uint8 LucIDType = DCM_ZERO;
  #endif

  #if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
       (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
       (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
       (DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
       (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || \
       (DCM_OBD_GETDTC_0A_SERVICE == STD_ON) || \
       (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))

  uint8 LucSID = Dcm_GstMsgContext.idContext & DCM_SID_MASK;

  /* Check whether if it is the first page that is to be transmitted */
  if ((LucSID == DCM_THREE) || (LucSID == DCM_SEVEN) || (LucSID == DCM_TEN))
  {
    #if ((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
         (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || \
         (DCM_OBD_GETDTC_0A_SERVICE == STD_ON))
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpNumOfDTCs;
    LpNumOfDTCs = &Dcm_GpReqResData[DCM_ZERO];

    if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
    {
      /* @Trace: Dcm_SUD_API_01529 */
      /* Common response for services: SubFunction + DTCStatusavailabilityMask */
      /* Update the Number of filtered DTCs to the response buffer */
      Dcm_GpReqResData[DCM_ZERO] = Dcm_GucNumofDTC;

      /* Re-Initialize the response buffer pointer */
      Dcm_GpReqResData = &Dcm_GpReqResData[DCM_ONE];

      /* Decrement the response buffer size by One */
      Dcm_GulBufferSize--;

      /* Indicate how many bytes are filled in the page */
      LucFixedFilledPgLen = DCM_ONE;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_01530 */
      LucFixedFilledPgLen = DCM_ZERO;
    }

    /* Process the subfunction to update the buffer with response
     * data containing the DTC and Status information and update
     * the filled page length */
    LulFilledPgLen = Dcm_DspReadOBDDTCInfo(Dcm_GulBufferSize, LpNumOfDTCs);

    /* Update the final number of bytes that is filled in the page
     * that is to be processed */
    LulFilledPgLen += LucFixedFilledPgLen;
    #endif
  }
  else if ((LucSID == DCM_ONE) || (LucSID == DCM_SIX) || 
    (LucSID == DCM_EIGHT) || (LucSID == DCM_NINE))
  {
    #if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
         (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
         (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
         (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))
    if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
    {
      /* @Trace: Dcm_SUD_API_01535 */
      /* Request buffer */
      LpRxBuffer = Dcm_GstMsgContext.reqData;

      /* Response buffer */
      LpTxBuffer = Dcm_GstMsgContext.resData;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_01536 */
      /* Request buffer */
      LpRxBuffer = &Dcm_GstMsgContext.reqData[
        Dcm_GstMsgContext.reqDataLen - Dcm_GucPIDCount];

      /* Update Pdu table */
      LpDcmPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];

      /* Get the buffer Id of the TxPduId */
      LucRxTxBufferId = LpDcmPduIdTable->ucTxBufferId;

      /* Response buffer */
      LpTxBuffer = Dcm_GaaBufferConfig[LucRxTxBufferId].pBufferArea;
    }

    /* Update local variable with PID count */
    LucPIDCount = Dcm_GucPIDCount;

    switch (LucSID)
    {
      #if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON))
      case DCM_ONE :
        /* @Trace: Dcm_SUD_API_01539 */
           LucIDType = DCM_GET_PID;
      break;
      #endif

      #if((DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON))
      case DCM_SIX :
        /* @Trace: Dcm_SUD_API_01543 */
           LucIDType = DCM_GET_OBDMID;
      break;
      #endif

      #if((DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON))
      case DCM_EIGHT :
        /* @Trace: Dcm_SUD_API_01544 */
           LucIDType = DCM_GET_TID;
      break;
      #endif

      #if((DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON))
      case DCM_NINE :
        /* @Trace: Dcm_SUD_API_01541 */
           LucIDType = DCM_GET_VID;
      break;
      #endif

      default:
      /* @Trace: Dcm_SUD_API_01545 */
      /* No action in this case */
      break;
    }

    #if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
    if ((LucSID == DCM_ONE) && (Dcm_GucAvlState != DCM_AVAIL_ID))
    {
      /* @Trace: Dcm_SUD_API_01547 */
      /* Do nothing in this case */
    }
    else
    #endif
    {
      /* @Trace: Dcm_SUD_API_01546 */
      LulFilledPgLen = Dcm_DspReadOBD_AvlInfo(
        LpRxBuffer, LpTxBuffer, Dcm_GulBufferSize, LucPIDCount, LucIDType);
    }
    #endif
  }
  else
  #endif
  {
    /* @Trace: SWS_Dcm_00587 SWS_Dcm_00588 */
    switch(Dcm_GucSubFunction)
    {
      #if ((DCM_RPT_DTC == STD_ON) || \
           (DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON) || \
           (DCM_RPT_DTCBYSEVERITYINFOFDTC == STD_ON))
      /* Check if the requested sub function 
       * is either 0x08, 0x09, 0x0A or 0x0F */
      case DCM_UDS_READ_DTC_INFO_02:
      case DCM_UDS_READ_DTC_INFO_08:
      case DCM_UDS_READ_DTC_INFO_09:
      case DCM_UDS_READ_DTC_INFO_0A:
      case DCM_UDS_READ_DTC_INFO_0F:
      case DCM_UDS_READ_DTC_INFO_13:
      case DCM_UDS_READ_DTC_INFO_15:
      case DCM_UDS_READ_DTC_INFO_17:
      case DCM_UDS_READ_DTC_INFO_55:
        /* Check whether if it is the first page that is to be transmitted */
        if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
        {
          /* @Trace: Dcm_SUD_API_01552 */
          /* Common response for services: SubFunction + DTCStatusavailabilityMask */
          /* Update the sub function to the response buffer */
          Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;

          if (DCM_UDS_READ_DTC_INFO_17 == Dcm_GucSubFunction)
          {
            /* @Trace: Dcm_SUD_API_01572 */
            Dcm_GpReqResData[DCM_ONE] = Dcm_GucMemorySelection;

            /*
            * The variable Dcm_GucRecordNumber contains the
            * availability mask
            */
            Dcm_GpReqResData[DCM_TWO] = Dcm_GucRecordNumber;

            /* Re-Initialize the response buffer pointer */
            Dcm_GpReqResData = &Dcm_GpReqResData[DCM_THREE];

            /* Decrement the response buffer size by Two */
            Dcm_GulBufferSize -= DCM_THREE;

            /* Indicate how many bytes are filled in the page */
            LucFixedFilledPgLen = DCM_THREE;
          }
          else if (DCM_UDS_READ_DTC_INFO_55 == Dcm_GucSubFunction)
          {
            /* @Trace: Dcm_SUD_API_01573 */
            /* Update FunctionalGroupIdentifier */
            Dcm_GpReqResData[DCM_ONE] = Dcm_GucFunctionalGroupIdentifier;

            /* Update DTC status availabilityMask */
            Dcm_GpReqResData[DCM_TWO] = Dcm_GucRecordNumber;

            /* Update DTCFormatIdentifier */
            Dcm_GpReqResData[DCM_THREE] = Dcm_GucTranslationType;

            /* Reset the pointer to the response data buffer */
            Dcm_GpReqResData = &Dcm_GpReqResData[DCM_FOUR];

            /* Decrement the response buffer size by Two */
            Dcm_GulBufferSize -= DCM_FOUR;

            /* Indicate how many bytes are filled in the page */
            LucFixedFilledPgLen = DCM_FOUR;
          }
          else
          {
            /* @Trace: Dcm_SUD_API_01574 */
            Dcm_GpReqResData[DCM_ONE]  = Dcm_GucRecordNumber;

            /* Re-Initialize the response buffer pointer */
            Dcm_GpReqResData = &Dcm_GpReqResData[DCM_TWO];

            /* Decrement the response buffer size by Two */
            Dcm_GulBufferSize -= DCM_TWO;

            /* Indicate how many bytes are filled in the page */
            LucFixedFilledPgLen = DCM_TWO;
          }
        }
        else
        {
          /* @Trace: Dcm_SUD_API_01571 */
          LucFixedFilledPgLen = DCM_ZERO;
        }

        #if(DCM_RPT_DTC == STD_ON)
        /* If the sub functions are 0x02, 0x0A, 0x0F */
        if (((Dcm_GucSubFunction & DCM_UDS_READ_DTC_INFO_02) == DCM_UDS_READ_DTC_INFO_02) ||
             (Dcm_GucSubFunction == DCM_UDS_READ_DTC_INFO_15) ||
             (Dcm_GucSubFunction == DCM_UDS_READ_DTC_INFO_55))
        {
          /* @Trace: Dcm_SUD_API_01576 */
          /* If the sub functions is 0x0A*/
          /*
           * Process the subfunction to update the buffer with response
           * data containing the DTC and Status information and update
           * the filled page length
          */
          LulFilledPgLen = Dcm_DspReadReqdDTCInfo(Dcm_GulBufferSize);
        }
        else
        #endif
        {
          #if ((DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON) || \
               (DCM_RPT_DTCBYSEVERITYINFOFDTC == STD_ON))
           /* @Trace: Dcm_SUD_API_01577 */
           /*
            * If the sub functions are 0x08 or 0x09, process the
            * subfunction to update the buffer with response
            * data containing the Severity, Functional unit, DTC and
            * Status information and update the filled page length
           */
          LulFilledPgLen = Dcm_DspUpdDTCBySeverityMask(Dcm_GulBufferSize);
          #endif
        }
         /*
          * Update the final number of bytes that is filled in the page
          * that is to be processed
         */
        LulFilledPgLen += LucFixedFilledPgLen;
      break;

      #endif
      #if ((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
           (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
      /* Check if the requested sub function is 
       * either 0x04, 0x06, 0x10, x018, 0x19 */
      case DCM_UDS_READ_DTC_INFO_04:
      case DCM_UDS_READ_DTC_INFO_06:
      case DCM_UDS_READ_DTC_INFO_10:
      case DCM_UDS_READ_DTC_INFO_18:
      case DCM_UDS_READ_DTC_INFO_19:
        /* @Trace: Dcm_SUD_API_01561 */
        LulFilledPgLen = Dcm_DspProcessSubFFDataOrExtData(
          Dcm_GucRecordNumber, &Dcm_GstMsgContext);
      break;
      #endif /* ((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) ||
                          (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM)) */

      #if((DCM_RPT_DTC_FLT_DET_CTR == STD_ON) || \
          (DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON))
      case DCM_UDS_READ_DTC_INFO_14:
      case DCM_UDS_READ_DTC_INFO_42:
      case DCM_UDS_READ_DTC_INFO_03:
        /*
        * Check whether if it is the first page that is to be
        * transmitted
        */
        if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
        {
          /* @Trace: Dcm_SUD_API_01580 */
          /* Update the sub function */
          Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;

          /* MISRA Rule        : 17.4
            Message            : Increment or decrement operation
                                 performed on pointer
            Reason             : Increment operator not used
                                 to achieve better throughput.
            Verification       : However, part of the code
                                 is verified manually and
                                 it is not having any impact.
          */
          /* Reset the pointer to the response data buffer */
          Dcm_GpReqResData++;

          /* Decrement the response buffer size by Two */
          Dcm_GulBufferSize -= DCM_ONE;

          if (DCM_UDS_READ_DTC_INFO_14 == Dcm_GucSubFunction)
          {
            /* @Trace: Dcm_SUD_API_01584 */
            #if(DCM_RPT_DTC_FLT_DET_CTR == STD_ON)
            LulFilledPgLen = Dcm_DspReadReqdDTCFDC(Dcm_GulBufferSize);
            #endif
          }
          else
          {
            /* @Trace: Dcm_SUD_API_01581 */
            #if(DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON)
            LulFilledPgLen = Dcm_DspRepDTCSnapRecID(Dcm_GulBufferSize);
            #endif
          }
          LulFilledPgLen += DCM_ONE;
        }
      break;
      #endif

      default:
      /* @Trace: Dcm_SUD_API_01570 */
      /* No action in this case */
      break;
    }
  }

  /* Check if no NRC was reported */
  if (Dcm_GddNegRespError == DCM_POS_RESP)
  {
    /* @Trace: Dcm_SUD_API_01585 */
    /* Request DSD to process the page that was updated previously */
    Dcm_DsdProcessPage(LulFilledPgLen);

    /* Check if the process page was called for the last page */
    if(Dcm_DspSerPgStatus.ucLastPage == DCM_TRUE)
    {
      /* @Trace: Dcm_SUD_API_01588 */
      #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
      Dcm_InternalTroubleCodeService = DCM_FALSE;
      #endif

      #if(DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON)
      /*
       * Release the data contained in this record so has to access
       * or manipulate by the external application
       */
      if ((DCM_UDS_READ_DTC_INFO_04 == Dcm_GucSubFunction) ||
          (DCM_UDS_READ_DTC_INFO_18 == Dcm_GucSubFunction))
      {
        /* @Trace: Dcm_SUD_API_01591 */
        /* To enable DTC record update */
        (void) IDem_EnableDTCRecordUpdate();
      }
      #endif

      /* Clear the last page bit flag */
      Dcm_DspSerPgStatus.ucLastPage = DCM_FALSE;
    }
  }
  /* If any NRC occurred during paged transmission */
  else
  {
    /* @Trace: Dcm_SUD_API_01587 */
    #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
    Dcm_InternalTroubleCodeService = DCM_FALSE;
    #endif

    /* Set the negative response */
    Dcm_ExternalSetNegResponse(&Dcm_GstMsgContext, Dcm_GddNegRespError);

    /* Indicate DSD to transmit the negative response to the DSL layer */
    Dcm_ExternalProcessingDone(&Dcm_GstMsgContext);
  }
}
#endif /* (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name        : DspInternal_DcmConfirmation                         **
**                                                                            **
** Service ID           : 0x15                                                **
**                                                                            **
** Description          : This is an internal function that clears the        **
**                        appropriate variable based on the requested         **
**                        service. This service confirms the successful       **
**                        transmission or a transmission error of a           **
**                        diagnostic service                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : IdContext, DcmRxPduId, ConfirmStatus                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) DspInternal_DcmConfirmation(
  Dcm_IdContextType IdContext
  , PduIdType RxPduId
  // , uint16 ConnectionId // TODO update later
  , Dcm_ConfirmationStatusType ConfirmStatus)
{
  if ((NULL_PTR != Dcm_GstMsgContext.reqData)
      && (Dcm_GstMsgContext.dcmRxPduId == RxPduId))
  {
    switch (IdContext)
    {
      case DCM_UDS_DIAG_SESSION_CONTROL:
        #if (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
        /* @Trace: Dcm_SUD_API_01593 */
        Dcm_SesCtrl_TxConfirmation(&Dcm_GstMsgContext, ConfirmStatus);
        #endif
        break;

      case DCM_STOP_DIAGNOSTIC_SESSION:
        #if (DCM_DSP_STOP_DIAG_SESSION_SERVICE == STD_ON)
        /* @Trace: Dcm_SUD_API_01596 */
        Dcm_StopSession_TxConfirmation(&Dcm_GstMsgContext, ConfirmStatus);
        #endif
        break;

      case DCM_UDS_READ_DTC:
        /* @Trace: Dcm_SUD_API_01597 */
        DCM_CLEAR_ALL_DSP_FLAGS();
        break;

      case DCM_UDS_ECU_RESET:
        #if (DCM_ECURESET_SERVICE == STD_ON)
        /* @Trace: Dcm_SUD_API_01599 */
        Dcm_EcuReset_TxConfirmation(ConfirmStatus, &Dcm_GstMsgContext);
        #endif
        break;

      case DCM_UDS_COMMUNICATION_CONTROL:
      case DCM_UDS_ENABLE_NORMAL_MSG_TRANSMISSION:
        #if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) \
             || (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))
        /* @Trace: Dcm_SUD_API_01602 */
        if (ConfirmStatus == DCM_RES_POS_OK)
        {
          /* @Trace: Dcm_SUD_API_01603 */
          DcmCommControlConfirmation(IdContext, ConfirmStatus);
        }
        #endif
        break;

      default:
        /* @Trace: Dcm_SUD_API_01604 */
        /* No action in this case */
        break;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_01592 */
    DCM_CLEAR_ALL_DSP_FLAGS();
  }

  /* TODO: Need to verify this context carefully */
  DCM_UNUSED(ConfirmStatus);
}

/*******************************************************************************
** Function Name        : DcmCommControlConfirmation                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function that clears the        **
**                        appropriate variable based on the requested         **
**                        Communication Control service.                      **
**                        This service confirms the successful transmission   **
**                        or a transmission error of a diagnostic service     **
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
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_DspSerPgStatus                                  **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) \
     || (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))
/* Fixed by youngjin.yun, 2014-12-12,
 * shall be processed when suppressed bit is true */
static FUNC(void, DCM_CODE) DcmCommControlConfirmation(
  Dcm_IdContextType IdContext
  , Dcm_ConfirmationStatusType ConfirmStatus)
{
  /* @Trace: Dcm_SUD_API_01500 */
  CONST(uint8, DCM_CONST) commCtrlTypeList[
    DCM_COMM_TYPE_MAX_NUM][DCM_CC_MAX_NUM] =
  {
    /*The range of Dcm_GucCommunicationModeType is between 0x01 and 0x03, so
      the entity 0 is dummy set. */
    {
      DCM_COMMUNICATIONMODETYPE_UNDEFINED,
      DCM_COMMUNICATIONMODETYPE_UNDEFINED,
      DCM_COMMUNICATIONMODETYPE_UNDEFINED,
      DCM_COMMUNICATIONMODETYPE_UNDEFINED
    },
  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT)
    /* ES95486 only support communicationType which is DCM_COMM_TYPE_NORMAL  */
    /* DCM_COMM_TYPE_NORMAL = 1 */
    {
      DCM_ENABLE_RX_TX_NORM,       /* DCM_CC_ENABLE_RX_AND_TX = 0 */
      DCM_DISABLE_RX_TX_NORM_NM,   /* DCM_CC_DISABLE_RX_AND_TX = 1 */
      DCM_DISABLE_RX_TX_NORM_NM,   /* DCM_CC_DISABLE_RX_AND_TX_NORESP = 2 */
      DCM_DISABLE_RX_TX_NORM       /* DCM_CC_DISABLE_RX_AND_TX_COMM_TYPE = 3 */
    },
    /* DCM_COMM_TYPE_NM = 2 */
    {
      DCM_ENABLE_RX_TX_NM,
      DCM_DISABLE_RX_TX_NORMAL,
      DCM_DISABLE_RX_TX_NORMAL,
      DCM_DISABLE_RX_TX_NM
    },
    /* DCM_COMM_TYPE_NM_AND_NORMAL = 3 */
    {
      DCM_ENABLE_RX_TX_NORM_NM,
      DCM_DISABLE_RX_TX_NORMAL,
      DCM_DISABLE_RX_TX_NORMAL,
      DCM_DISABLE_RX_TX_NORM_NM
    }
  };
  #else /*if(DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) */
    /* DCM_COMM_TYPE_NORMAL = 1 */
    {
      DCM_ENABLE_RX_TX_NORM,              /* enableRxAndTx        0 */
      DCM_ENABLE_RX_DISABLE_TX_NORM,      /* enableRxAndDisableTx 1 */
      DCM_DISABLE_RX_ENABLE_TX_NORM,      /* disableRxAndEnableTx 2 */
      DCM_DISABLE_RX_TX_NORMAL            /* disableRxAndTx       3 */
    },
    /* DCM_COMM_TYPE_NM = 2 */
    {
      DCM_ENABLE_RX_TX_NM,                /* enableRxAndTx        0 */
      DCM_ENABLE_RX_DISABLE_TX_NM,        /* enableRxAndDisableTx 1 */
      DCM_DISABLE_RX_ENABLE_TX_NM,        /* disableRxAndEnableTx 2 */
      DCM_DISABLE_RX_TX_NM,               /* disableRxAndTx       3 */
    },
    /* DCM_COMM_TYPE_NM_AND_NORMAL = 3 */
    {
      DCM_ENABLE_RX_TX_NORM_NM,           /* enableRxAndTx        0 */
      DCM_ENABLE_RX_DISABLE_TX_NORM_NM,   /* enableRxAndDisableTx 1 */
      DCM_DISABLE_RX_ENABLE_TX_NORM_NM,   /* disableRxAndEnableTx 2 */
      DCM_DISABLE_RX_TX_NORM_NM           /* disableRxAndTx       3 */
    }
  };
  #endif

  /* Fixed by youngjin.yun, 2014-12-07,
   * DCM_RES_POS_NOT_OK : when suppression mask is true : By yj.yun */
  if ((IdContext == DCM_UDS_COMMUNICATION_CONTROL) &&
      (Dcm_GucCommunicationModeType <= DCM_COMM_TYPE_NM_AND_NORMAL) &&
      (Dcm_GucSubFunction < DCM_LOCAL_NUM_OF_SUBREQ))
  {
    /* @Trace: Dcm_SUD_API_01507 */
    #if (DCM_STANDARD_SUPPORT == DCM_ISO14229_SUPPORT)
    Dcm_GucComCtrlMode = DcmJudgeComCtrlMode(
      Dcm_GucSubFunction, Dcm_GucCommunicationModeType);
    #else
    Dcm_GucComCtrlMode = commCtrlTypeList[
      Dcm_GucCommunicationModeType][Dcm_GucSubFunction];
    #endif

    if (DCM_COMMUNICATIONMODETYPE_UNDEFINED != Dcm_GucComCtrlMode)
    {
      #if (DCM_STANDARD_SUPPORT == DCM_ISO14229_SUPPORT)
      if ((Dcm_GucSubFunction == 0x04u) || (Dcm_GucSubFunction == 0x05u))
      {
        /* @Trace: Dcm_SUD_API_01512 */
        Dcm_SwitchCommMode_SubNode(Dcm_GucComCtrlMode);
      }
      #endif

      #if (0 < DCM_TOTAL_NUM_OF_ALL_CHANNEL)
      /* @Trace: SWS_Dcm_00512 */
      if(Dcm_GucSubNetValue == DCM_ZERO)
      {
        /* @Trace: Dcm_SUD_API_01516 */
        Dcm_SwitchCommMode_AllChannel(Dcm_GucComCtrlMode);
      }
      #endif

      /* @Trace: SWS_Dcm_00785 */
      if (Dcm_GucSubNetValue == DCM_FIFTEEN)
      {
        /* @Trace: Dcm_SUD_API_01519 */
        Dcm_SwitchCommMode_ReceivedOnChannel(Dcm_GucComCtrlMode);
      }
      else
      {
        /* @Trace: Dcm_SUD_API_01518 */
        Dcm_SwitchCommMode_SpecificChannel(Dcm_GucComCtrlMode);
      }
    }
  }
  #if (DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT)
  /* Fixed by youngjin.yun, 2014-12-09, suppressed bit is true,
   * For Enable normal message transmission Service */
  else if (IdContext == DCM_UDS_ENABLE_NORMAL_MSG_TRANSMISSION)
  {
    /* @Trace: Dcm_SUD_API_01504 */
    /* Bug #6217 : Modified by Jin, 161019 */
    Dcm_GucComCtrlMode = commCtrlTypeList[
      Dcm_GucCommunicationModeType][DCM_CC_ENABLE_RX_AND_TX];
    Dcm_SwitchCommMode_AllChannel(Dcm_GucComCtrlMode);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_01505 */
    /* Do nothing */
  }
  #else
  DCM_UNUSED(commCtrlTypeList);
  #endif

  DCM_UNUSED(ConfirmStatus);
}

/*******************************************************************************
** Function Name        : DcmJudgeComCtrlMode                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge Com Ctrl Mode                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : ControlType, communicationType                      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_STANDARD_SUPPORT == DCM_ISO14229_SUPPORT)
static FUNC(uint8, DCM_CODE) DcmJudgeComCtrlMode(
  uint8 ControlType,
  uint8 communicationType)
{
  /* @Trace: Dcm_SUD_API_01606 */
  Dcm_JudgeComCtrlModeFunType Dcm_JudgeComCtrlModeFun[DCM_LOCAL_NUM_OF_SUBREQ] = 
  {
    DcmJudgeEnableRxAndTx
    , DcmJudgeEnableRxAndDisableTx
    , DcmJudgeDisableRxAndEnableTx
    , DcmJudgeDisableRxAndTx
    , DcmJudgeEnableRxAndDisableTx
    , DcmJudgeEnableRxAndTx
  };

  return Dcm_JudgeComCtrlModeFun[ControlType](communicationType);
}

/*******************************************************************************
** Function Name        : DcmJudgeEnableRxAndTx                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge Enable Rx And Tx                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : communicationType                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(uint8, DCM_CODE) DcmJudgeEnableRxAndTx(
  uint8 communicationType)
{
  /* @Trace: Dcm_SUD_API_01607 */
  Dcm_CommunicationModeType ComControlTypeAddr[DCM_CC_MAX_NUM]=
  {
    DCM_COMMUNICATIONMODETYPE_UNDEFINED
    , DCM_ENABLE_RX_TX_NORM
    , DCM_ENABLE_RX_TX_NM
    , DCM_ENABLE_RX_TX_NORM_NM
  };

  return ComControlTypeAddr[communicationType];
}

/*******************************************************************************
** Function Name        : DcmJudgeEnableRxAndDisableTx                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge Enable Rx And Disable Tx                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : communicationType                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(uint8, DCM_CODE) DcmJudgeEnableRxAndDisableTx(
  uint8 communicationType)
{
  /* @Trace: Dcm_SUD_API_01608 */
  Dcm_CommunicationModeType ComControlTypeAddr[DCM_CC_MAX_NUM] =
  {
    DCM_COMMUNICATIONMODETYPE_UNDEFINED
    , DCM_ENABLE_RX_DISABLE_TX_NORM
    , DCM_ENABLE_RX_DISABLE_TX_NM
    , DCM_ENABLE_RX_DISABLE_TX_NORM_NM
  };

  return ComControlTypeAddr[communicationType];
}

/*******************************************************************************
** Function Name        : DcmJudgeDisableRxAndEnableTx                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge Disable Rx And Enable Tx                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : communicationType                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(uint8, DCM_CODE) DcmJudgeDisableRxAndEnableTx(
  uint8 communicationType)
{
  /* @Trace: Dcm_SUD_API_01609 */
  Dcm_CommunicationModeType ComControlTypeAddr[DCM_CC_MAX_NUM] =
  {
    DCM_COMMUNICATIONMODETYPE_UNDEFINED
    , DCM_DISABLE_RX_ENABLE_TX_NORM
    , DCM_DISABLE_RX_ENABLE_TX_NM
    , DCM_DISABLE_RX_ENABLE_TX_NORM_NM
  };

  return ComControlTypeAddr[communicationType];
}

/*******************************************************************************
** Function Name        : DcmJudgeDisableRxAndTx                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Judge Disable Rx And Tx                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : communicationType                                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(uint8, DCM_CODE) DcmJudgeDisableRxAndTx(
  uint8 communicationType)
{
  /* @Trace: Dcm_SUD_API_01610 */
  Dcm_CommunicationModeType ComControlTypeAddr[DCM_CC_MAX_NUM] =
  {
    DCM_COMMUNICATIONMODETYPE_UNDEFINED
    , DCM_DISABLE_RX_TX_NORM
    , DCM_DISABLE_RX_TX_NM
    , DCM_DISABLE_RX_TX_NORM_NM
  };

  return ComControlTypeAddr[communicationType];
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dcm_DspCancelPagedBufferProcessing                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function to stop processing of  **
**                        the diagnostic service and to clear the internal    **
**                        variables if the page buffer processing was         **
**                        cancelled due to time out                           **
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
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_DspSerPgStatus                                  **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspCancelPagedBufferProcessing(void)
{
  /* @Trace: Dcm_SUD_API_01611 */
  /* Clear all read DTC service flags */
  Dcm_GddNegRespError = DCM_POS_RESP;
  Dcm_GucSubFunction = DCM_ZERO;

  DCM_CLEAR_ALL_DSP_FLAGS();
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
