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
**  SRC-MODULE: Dcm_DspReadDTCInfo.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the implementation of the Read DTC         **
**              subfunctions  0x02, 0x0A, 0x0F, 0x13, 0x15, ,0x14, 0x08       **
**              and 0x09                                                      **
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
** 0.0.1     31-Dec-2019   LamNV10        AR440 Implementation                **
** 0.0.2     05-May-2019   LamNV10        Change to correct DEM returned type **
** 0.0.3     16-Aug-2020   HueKM          Fix defect and coding rules         **
** 0.0.4     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.5     02-Nov-2020   HueKM          Changes made as per #16832          **
** 0.0.6     04-Dec-2020   LanhLT         Polyspace fixing as per #15175      **
** 0.0.7     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
** 1.3.0     31-Dcm-2023   EK Kim         Refer #CP44-1515                    **
** 1.4.0     29-Mar-2024   EK Kim         Refer #CP44-3850                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_DspReadDTCInfo.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dem.h"
#endif

#include "Dcm_Ram.h"
#include "Dcm_DspMain.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Config.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dcm_DemInterfaces.h"
#endif
#include "Dcm_Utils.h"

/*******************************************************************************
**                      Function Definitions
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

#if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
static FUNC(void, DCM_CODE) Dcm_DspUpdDTCBySeverityMaskInfo(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_DspRptDTC                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for the service Read DTC      **
**                        information (service 0x19) to list the DTCs and the **
**                        associated status information matching a specific   **
**                        status mask, severity mask, memory location and DTC **
**                        type. It will be invoked for sub-function values    **
**                        0x02, 0x0A, 0x0F, 0x13 0x15, 0x17, 0x55             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GpMsgContext, Dcm_DspSerPgStatus,               **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_PrtclTxBufStatus, Dcm_GucReadGlobal,            **
**                        Dcm_GucAvailableDTCStatusMask                       **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Dcm_DemGetNumberOfReportedDTC,                      **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if(DCM_RPT_DTC == STD_ON)
/* polyspace-begin MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(void, DCM_CODE) Dcm_DspRptDTC(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
/* polyspace-end MISRA2012:8.13 [Justified:Low] Justify with annotations */
{
  Dcm_MsgType LpReqResData;

  Dem_DTCOriginType LddDTCOrigin;
  Dem_DTCFormatType LddDTCFormat;
  Std_ReturnType LddReturnValue;
  uint8 LucDTCStatusMask = (uint8) DCM_ZERO;
  boolean LblDTCFormatIDSupport = DCM_FALSE;
  boolean LblFunctionalGroupIdentifierSupport = DCM_FALSE;

   /* Update variable as DCM_POS_RESP */
  Dcm_GddNegRespError = DCM_POS_RESP;
  Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_FALSE;

  if ((pMsgContext == NULL_PTR) || 
      (pMsgContext->resData == NULL_PTR) ||
      (pMsgContext->reqData == NULL_PTR))
  {
    /* @Trace: Dcm_SUD_API_31261 */
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31262 */
    LpReqResData = pMsgContext->reqData;
    Dcm_GucReadGlobal = DCM_TRUE;

    /* Update DTCStatusMask for 0x0A and 0x15 and 0x55 */
    if((Dcm_GucSubFunction == DCM_UDS_READ_DTC_INFO_0A) ||
       (Dcm_GucSubFunction == DCM_UDS_READ_DTC_INFO_15) ||
       (Dcm_GucSubFunction == DCM_UDS_READ_DTC_INFO_55) 
       #if (DCM_J1979_2_SUPPORT == STD_ON)
       /* Trace: DCM_19792_56_01 */
       || (Dcm_GucSubFunction == DCM_UDS_READ_DTC_INFO_56) 
       /* Trace: DCM_19792_1A_01 */
       || (Dcm_GucSubFunction == DCM_UDS_READ_DTC_INFO_1A)
       #endif /* DCM_J1979_2_SUPPORT == STD_ON */
      )
    {
      /* @SWS_Dem_00208
        Status-byte mask for DTC status-byte filtering Val-
        ues: 0x00: Autosar-specific value to deactivate the
        status-byte filtering (different meaning than in ISO
        14229-1) to report all supported DTCs (used for
        service 0x19 subfunctions 0x0A/0x15) 0x01..0xFF:
        Status-byte mask according to ISO 14229-1 DTC-
        StatusMask (handed over by Dcm from service re-
        quest directly) to filter for DTCs with at least one sta-
        tus bit set matching this status-byte mask
      */
      /* @Trace: Dcm_SUD_API_31264 */
      /* Update status mask */
      LucDTCStatusMask = DCM_STATUS_MASK_ALL;

      /* Update FunctionalGroupIdentifier and 
       * DTCFormatIdentifier in case of subservice 0x55 */
      if (DCM_UDS_READ_DTC_INFO_55 == Dcm_GucSubFunction)
      {
        /* @Trace: Dcm_SUD_API_31267 */
        Dcm_GucTranslationType = IDem_GetTranslationType();
        Dcm_GucFunctionalGroupIdentifier = LpReqResData[DCM_ONE];
      }
      #if (DCM_J1979_2_SUPPORT == STD_ON)
      /* Trace: DCM_19792_56_02 */
      else if (DCM_UDS_READ_DTC_INFO_56 == Dcm_GucSubFunction)
      {
        /* @Trace: Dcm_SUD_API_31267 */
        Dcm_GucTranslationType = IDem_GetTranslationType();
        Dcm_GucFunctionalGroupIdentifier = LpReqResData[DCM_ONE];
        Dcm_GucReadinessGroupIdentifier = LpReqResData[DCM_TWO];
      }
      else if(Dcm_GucSubFunction == DCM_UDS_READ_DTC_INFO_1A)
      {
        Dcm_GucExtendedDataRecordNumber = LpReqResData[DCM_ONE];
      }
      #endif /* (DCM_J1979_2_SUPPORT == STD_ON) */
      else 
      {
        /* No action */
      }
    }
    else
    {
      /* Update status mask from the request */
      LucDTCStatusMask = LpReqResData[DCM_ONE];

      /* @Trace: Dcm_SUD_API_31265 Dcm_SUD_API_31266 */
      /* Update MemorySelection for subservice 0x17 */
      Dcm_GucMemorySelection = 
        (DCM_UDS_READ_DTC_INFO_17 == Dcm_GucSubFunction) ? \
        LpReqResData[DCM_TWO] : DCM_ZERO;
    }

    /* Assign Origin parameter */
    switch (Dcm_GucSubFunction)
    {
      /* Sub function 0x0F */
      case DCM_UDS_READ_DTC_INFO_0F:
        /* @Trace: Dcm_SUD_API_31269 */
        LddDTCOrigin = DEM_DTC_ORIGIN_MIRROR_MEMORY;
        break;

      /* Sub function 0x15 0x55 */
      case DCM_UDS_READ_DTC_INFO_15:
      case DCM_UDS_READ_DTC_INFO_55:
        /* @Trace: Dcm_SUD_API_31270 */
        LddDTCOrigin = DEM_DTC_ORIGIN_PERMANENT_MEMORY;
        break;

      /* Sub function 0x13 */
      case DCM_UDS_READ_DTC_INFO_13:
        /* @Trace: Dcm_SUD_API_31271 */
        LddDTCOrigin = DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY;
        break;

      /* @Trace: SWS_Dcm_01334 */
      /* Sub function 0x17 */  
      case DCM_UDS_READ_DTC_INFO_17:
        /* @Trace: Dcm_SUD_API_31272 */
        LddDTCOrigin = 
          (uint16) Dcm_GucMemorySelection | DCM_USER_DEFINED_FAULT_MEMORY;
        break;

      /* Sub function 0x02 0x0A */
      default:
        /* @Trace: Dcm_SUD_API_31273 */
        LddDTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
        break;
    }

    /* Get the DTC status information supported by the DEM */
    LddReturnValue = IDem_GetDTCStatusAvailabilityMask(
      &Dcm_GucAvailableDTCStatusMask);

    #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
    if (DCM_TRUE == Dcm_InternalTroubleCodeService)
    {
      /* @Trace: Dcm_SUD_API_31275 */
      Dcm_GucAvailableDTCStatusMask = 
        DCM_ITC_STATUS_MASK & Dcm_GucAvailableDTCStatusMask;
    }
    #endif
    
    LddDTCFormat = DEM_DTC_FORMAT_UDS;

    if((DCM_UDS_READ_DTC_INFO_55 == Dcm_GucSubFunction)
    #if (DCM_J1979_2_SUPPORT == STD_ON)  
       || (DCM_UDS_READ_DTC_INFO_56 == Dcm_GucSubFunction) 
       || (DCM_UDS_READ_DTC_INFO_1A == Dcm_GucSubFunction)
    #endif
    )
    {

      #if ((DCM_J1979_2_SUPPORT == STD_ON)  \
      && (DCM_OBD_UDS_DTC_SEPARATION_SUPPORT == STD_ON))
      {
        LddDTCFormat = DEM_DTC_FORMAT_OBD_3BYTE;
      }
      #endif
		
	  /* polyspace-begin MISRA2012:14.3 [Not a defect: Justified] "The value depend on configuration." */
      /* 19 55 FGID / 19 56 FGID RGID / 19 1A ExDataRecNum */  
      if((DCM_UDS_READ_DTC_INFO_55 == Dcm_GucSubFunction)
      #if (DCM_J1979_2_SUPPORT == STD_ON)  
         || (DCM_UDS_READ_DTC_INFO_56 == Dcm_GucSubFunction) 
      #endif
      )
      {
        if(DCM_UDS_DTC_FGID_LIMITATION == Dcm_GucFunctionalGroupIdentifier)
        {
        /* @Trace: Dcm_SUD_API_31276 */
          LblFunctionalGroupIdentifierSupport = DCM_TRUE;
        }

        if((DEM_DTC_TRANSLATION_SAEJ1939_73 == Dcm_GucTranslationType) ||
          (DEM_DTC_TRANSLATION_J2012DA_FORMAT_04 == Dcm_GucTranslationType))
        {
          /* @Trace: Dcm_SUD_API_31277 */
          LblDTCFormatIDSupport = DCM_TRUE;
        }

        if((DCM_FALSE == LblFunctionalGroupIdentifierSupport) || 
          (DCM_FALSE == LblDTCFormatIDSupport))
        {

          Dcm_GddNegRespError = (DCM_FALSE == LblFunctionalGroupIdentifierSupport) \
            ? DCM_E_REQUESTOUTOFRANGE : DCM_E_GENERALREJECT;
        }
      }
	  /* polyspace-end MISRA2012:14.3 [Not a defect: Justified] "The value depend on configuration." */

    }
    
  
    if((LddReturnValue == E_OK) && (DCM_POS_RESP == Dcm_GddNegRespError))
    {  
      /* @Trace: SWS_Dcm_00008 */
      if (((LucDTCStatusMask & Dcm_GucAvailableDTCStatusMask) == DCM_ZERO) &&
          ((DCM_UDS_READ_DTC_INFO_02 == Dcm_GucSubFunction) || 
           (DCM_UDS_READ_DTC_INFO_0F == Dcm_GucSubFunction) || 
           (DCM_UDS_READ_DTC_INFO_13 == Dcm_GucSubFunction)))
      {
        /* @Trace: Dcm_SUD_API_31280 */
        Dcm_GstMsgContext.resDataLen = DCM_TWO;

        Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
  
        Dcm_GpReqResData[DCM_ONE] = Dcm_GucAvailableDTCStatusMask;
      
        /* Update the global variable to indicate that no NRC has occurred */
        Dcm_GddNegRespError = DCM_POS_RESP;
      }
      else
      {
         #if (DCM_J1979_2_SUPPORT == STD_ON)
        /* Trace: DCM_19792_1A_02 */
        if (DCM_UDS_READ_DTC_INFO_1A == Dcm_GucSubFunction)
        {    
          LddReturnValue = IDem_SetDTCFilterByExtendedDataRecordNumber(
            LddDTCFormat, Dcm_GucExtendedDataRecordNumber, &Dcm_GddNegRespError);
        }        
        /* Trace: DCM_19792_56_06 */
        else if (DCM_UDS_READ_DTC_INFO_56 == Dcm_GucSubFunction)
        {
          LddReturnValue = IDem_SetDTCFilterByReadinessGroup(
            LddDTCFormat, Dcm_GucReadinessGroupIdentifier, &Dcm_GddNegRespError);
        }
        else
        #endif /* J19792 */
        {
          /* @Trace: SRS_Diag_04067 */
          /* @Trace: SWS_Dcm_00378 SWS_Dcm_00835 */
          /* @Trace: Dcm_SUD_API_31281 */
          LddReturnValue = IDem_SetDTCFilter(
            (Dcm_GucAvailableDTCStatusMask & LucDTCStatusMask),
            LddDTCFormat, LddDTCOrigin, DCM_FALSE,
            DEM_SEVERITY_NO_SEVERITY, DCM_FALSE, &Dcm_GddNegRespError);
        }

        if(LddReturnValue == E_OK)
        {
          /* @Trace: Dcm_SUD_API_31282 */
          Dcm_DemGetNumberOfReportedDTC();
        }
      }
    }
    else
    {
      /* @Trace: Dcm_SUD_API_31283 Dcm_SUD_API_31284 */
      /* For QAC Check */
      Dcm_GddNegRespError = (DCM_POS_RESP != Dcm_GddNegRespError) ? \
                            Dcm_GddNegRespError : DCM_E_CONDITIONSNOTCORRECT;
    }
  }
  
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
  #endif
  {
    /* Dcm_PrtclTxBufStatus.ReportNumOfDtc set to true
     * when reporting is pending */
    if(Dcm_PrtclTxBufStatus.ReportNumOfDtc == DCM_FALSE)
    {
      /* @Trace: Dcm_SUD_API_31285 */
      #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
      Dcm_InternalTroubleCodeService = DCM_FALSE;
      #endif

      /* Send response from main function */
      Dcm_GblSendResponse = DCM_TRUE;
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DemGetNumberOfReportedDTC                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function of the service Read   **
**                        DTC information (service 0x19) to list the number   **
**                        of Reported DTcs.It will be invoked for             **
**                        sub-function values 0x02, 0x0A, 0x0F, 0x13          **
**                        and 0x15                                            **
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
** Remarks              : Global Variable(s) :                                **
**                        Dcm_PrtclTxBufStatus, Dcm_GucRecordNumber,          **
**                        Dcm_TxRespStatus, Dcm_DspSerPgStatus,               **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_GpMsgContext, Dcm_GucAvailableDTCStatusMask     **
**                        Function(s) invoked : Dcm_DspReadReqdDTCInfo        **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DemGetNumberOfReportedDTC(void)
{
  Std_ReturnType LddNumFilteredDTCType;
  uint32 LulRespLength;
  uint16 LusNumberOfFilteredDTC = (uint16)DCM_ZERO;
  Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_FALSE;

  if (Dcm_GpReqResData == NULL_PTR)
  {
    /* @Trace: Dcm_SUD_API_31202 */
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31201 */
    /* Get the number of DTC matching the defined status mask */
    LddNumFilteredDTCType = IDem_GetNumberOfFilteredDTC(
      &LusNumberOfFilteredDTC);

    /* Check whether getting number of DTC was successful */
    if(LddNumFilteredDTCType == E_OK)
    {
      #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
      if (DCM_TRUE == Dcm_InternalTroubleCodeService)
      {
        /* @Trace: Dcm_SUD_API_31205 */
        /* DTCHighByte + DTCLowByte + DTCStatus = 3 for every
         * DTC + 2(DTCAvailableMask and subfunction */
        LulRespLength = (LusNumberOfFilteredDTC * DCM_THREE) + DCM_TWO;
      }
      else
      #endif
      {
        /* @Trace: SWS_Dcm_00377 */
        if (DCM_UDS_READ_DTC_INFO_17 == Dcm_GucSubFunction)
        {
          /* @Trace: Dcm_SUD_API_31206 */
          /* DTCHighByte + DTCMiddleByte  + DTCLowByte + DTCStatus = 4 for
           * every DTC + 3(DTCAvailableMask - subfunction - MemorySelection) */
          LulRespLength = (uint32) \
            (((uint32) LusNumberOfFilteredDTC << (uint32) DCM_TWO) + DCM_THREE);
        }
        else if (DCM_UDS_READ_DTC_INFO_55 == Dcm_GucSubFunction)
        {
          /* @Trace: Dcm_SUD_API_31208 */
          /* DTCHighByte + DTCMiddleByte  + DTCLowByte + DTCStatus = 4 for
           * every DTC + 4(Subfunction + FGID + DTCSAM + DTCFID) */
          LulRespLength = (uint32) \
            (((uint32) LusNumberOfFilteredDTC << (uint32) DCM_TWO) + DCM_FOUR);
        }
        #if (DCM_J1979_2_SUPPORT == STD_ON) 
        /* Trace: DCM_19792_56_07 */
        else if (DCM_UDS_READ_DTC_INFO_56 == Dcm_GucSubFunction)
        {
          /* DTCHighByte + DTCMiddleByte  + DTCLowByte + DTCStatus = 4 for
           * every DTC + 5(Subfunction + FGID + DTCSAM + DTCFID + RGID) */
          LulRespLength = (uint32) \
            (((uint32) LusNumberOfFilteredDTC << (uint32) DCM_TWO) + DCM_FIVE);
        }
        /* Trace: DCM_19792_1A_03 */
        else if (DCM_UDS_READ_DTC_INFO_1A == Dcm_GucSubFunction)
        {
          /* DTCHighByte + DTCMiddleByte  + DTCLowByte + DTCStatus = 4 for
           * every DTC + 3(Subfunction + DTCAvailableMask + DTCExtenedRecordNumber) */
          LulRespLength = (uint32) \
            (((uint32) LusNumberOfFilteredDTC << (uint32) DCM_TWO) + DCM_THREE);
        }
        #endif /* (DCM_J1979_2_SUPPORT == STD_ON) */
        else
        {
          /* @Trace: Dcm_SUD_API_31207 */
          /* DTCHighByte + DTCMiddleByte  + DTCLowByte + DTCStatus = 4 for
           * every DTC + 2(DTCAvailableMask and subfunction) */
          LulRespLength = (uint32) \
            (((uint32) LusNumberOfFilteredDTC << (uint32) DCM_TWO) + DCM_TWO);
        }
      }

      /* Update the complete response length that is to be transmitted */
      Dcm_GstMsgContext.resDataLen = LulRespLength;

      /* Check if the response buffer is capable of accommodating the
        * complete response at once */
      if(LulRespLength <= (Dcm_GstMsgContext.resMaxDataLen))
      {
        /* Update the sub function */
        Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;

        if (DCM_UDS_READ_DTC_INFO_17 == Dcm_GucSubFunction)
        {
          /* @Trace: Dcm_SUD_API_31214 */
          /* Update MemorySelection */
          Dcm_GpReqResData[DCM_ONE] = Dcm_GucMemorySelection;

          /* Update DTC status availabilityMask */
          Dcm_GpReqResData[DCM_TWO] = Dcm_GucAvailableDTCStatusMask;

          /* Reset the pointer to the response data buffer */
          Dcm_GpReqResData = &Dcm_GpReqResData[DCM_THREE];

          /* Pass the buffer size with three values less since sub function
           * and availabilityMask and MemorySelection is already updated */
          LulRespLength = LulRespLength - DCM_THREE;
        }
        /* @Trace: SWS_Dcm_01345 */
        else if (DCM_UDS_READ_DTC_INFO_55 == Dcm_GucSubFunction)
        {
          /* @Trace: Dcm_SUD_API_31215 */
          /* Update FunctionalGroupIdentifier */
          Dcm_GpReqResData[DCM_ONE] = Dcm_GucFunctionalGroupIdentifier;

          /* Update DTC status availabilityMask */
          Dcm_GpReqResData[DCM_TWO] = Dcm_GucAvailableDTCStatusMask;

          /* Update DTCFormatIdentifier */
          Dcm_GpReqResData[DCM_THREE] = Dcm_GucTranslationType;

          /* Reset the pointer to the response data buffer */
          Dcm_GpReqResData = &Dcm_GpReqResData[DCM_FOUR];

          /* Pass the buffer size with three values less since sub function and
           * availabilityMask FunctionalGroupIdentifier and DTCFormatIdentifier
           * is already updated */
          LulRespLength = LulRespLength - DCM_FOUR;
        }
        #if (DCM_J1979_2_SUPPORT == STD_ON) 
        /* Trace: DCM_19792_56_08 */
        else if (DCM_UDS_READ_DTC_INFO_56 == Dcm_GucSubFunction)
        {
          /* @Trace: Dcm_SUD_API_31215 */
          /* Update FunctionalGroupIdentifier */
          Dcm_GpReqResData[DCM_ONE] = Dcm_GucFunctionalGroupIdentifier;

          /* Update DTC status availabilityMask */
          Dcm_GpReqResData[DCM_TWO] = Dcm_GucAvailableDTCStatusMask;

          /* Update DTCFormatIdentifier */
          Dcm_GpReqResData[DCM_THREE] = Dcm_GucTranslationType;

          /* Update DTCReadinessGroupIdentifier */
          Dcm_GpReqResData[DCM_FOUR] = Dcm_GucReadinessGroupIdentifier;

          /* Reset the pointer to the response data buffer */
          Dcm_GpReqResData = &Dcm_GpReqResData[DCM_FIVE];

          /* Pass the buffer size with three values less since sub function and
           * availabilityMask FunctionalGroupIdentifier and DTCFormatIdentifier
           * is already updated */
          LulRespLength = LulRespLength - DCM_FIVE;
        }
        /* Trace: DCM_19792_1A_04 */
        else if (DCM_UDS_READ_DTC_INFO_1A == Dcm_GucSubFunction)
        {
          /* @Trace: Dcm_SUD_API_31215 */
          /* Update FunctionalGroupIdentifier */
          Dcm_GpReqResData[DCM_ONE] = Dcm_GucAvailableDTCStatusMask;

          /* Update DTCExtendedDataRecordNumber */
          Dcm_GpReqResData[DCM_TWO] = Dcm_GucExtendedDataRecordNumber;

          /* Reset the pointer to the response data buffer */
          Dcm_GpReqResData = &Dcm_GpReqResData[DCM_THREE];

          /* Pass the buffer size with three values less since sub function and
           * availabilityMask FunctionalGroupIdentifier and DTCFormatIdentifier
           * is already updated */
          LulRespLength = LulRespLength - DCM_THREE;
        }
        #endif /* (DCM_J1979_2_SUPPORT == STD_ON)  */
        else
        {
          /* @Trace: Dcm_SUD_API_31216 */
          /* Update DTC status availabilityMask */
          Dcm_GpReqResData[DCM_ONE] = Dcm_GucAvailableDTCStatusMask;

          /* Reset the pointer to the response data buffer */
          Dcm_GpReqResData = &Dcm_GpReqResData[DCM_TWO];

          /* Pass the buffer size with three values less since sub function and
           * availabilityMask is already updated */
          LulRespLength = LulRespLength - DCM_TWO;
        }

        (void)Dcm_DspReadReqdDTCInfo(LulRespLength);
      }
      else
      {
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON) /* 0x0A */
        uint32 maxResLen = Dcm_PagedBuffer_GetMaxRespLen(&Dcm_GstMsgContext);
        if (LulRespLength <= maxResLen)
        {
          /* @Trace: Dcm_SUD_API_31213 */
          /* This variable is re used to store DTC Mask */
          Dcm_GucRecordNumber = Dcm_GucAvailableDTCStatusMask;

          /* Start the paged processing */
          Dcm_DsdStartPagedProcessing(&Dcm_GstMsgContext);
        }
        else
        #endif
        {
          /* @Trace: Dcm_SUD_API_31212 */
          Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
        }
      }
    }
    else if(LddNumFilteredDTCType == DEM_PENDING)
    {
      /* @Trace: Dcm_SUD_API_31203 */
      /* Set the Flag for returning of DCM_E_PENDING */
      Dcm_PrtclTxBufStatus.ReportNumOfDtc = DCM_TRUE;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_31204 */
      /* For QAC Check */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspRptDTCFltDetCtr                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for the service Read DTC      **
**                        information (service 0x19) to list the Fault        **
**                        Detection Counter for all the DTCs with Prefailed   **
**                        Status It will be invoked for sub-function value    **
**                        0x14 0x42                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GucReadGlobal, Dcm_GblFaultDetcetionCounter     **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_DspSerPgStatus                                  **
**                        Function(s) invoked :                               **
**                        Dcm_DspReadReqdDTCFDC                               **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04139 SRS_Diag_04157 */
#if (DCM_RPT_DTC_FLT_DET_CTR == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptDTCFltDetCtr(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  uint32 LulRespLength;
  uint16 LusNumberOfFilteredDTC = (uint16) DCM_ZERO;

  Std_ReturnType LucReturnRes;
  Std_ReturnType LddNumFilteredDTCType;

  Dem_DTCOriginType LucDTCOrigin;
  Dem_DTCSeverityType LucDTCSeverityMask;
  static Dem_DTCSeverityType LucDTCSeverityAvailabilityMask;
  Dem_DTCFormatType LucDTCFormat;

  uint8 LucDTCStatusMask;
  
  boolean LblFilterWithSeverity;
  boolean LblFilterForFaultDetectionCounter;
  
  Dcm_GucReadGlobal = DCM_TRUE;
  
  if ((pMsgContext == NULL_PTR) || (Dcm_GpReqResData == NULL_PTR))
  {
    /* @Trace: Dcm_SUD_API_31307 */
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31306 */
    LucReturnRes = E_OK;
    Dcm_GddNegRespError = DCM_POS_RESP;

    
    /*
    * Set the filter mask over all DTCs for the API Dem_GetNextFilteredDTC
    * and reset the internal counter to the first event that matches the
    * filter settings
    */
    if(Dcm_GblFaultDetectionCounter != DCM_TRUE)
    {
      if (DCM_UDS_READ_DTC_INFO_14 == Dcm_GucSubFunction)
      {
        /* @Trace: Dcm_SUD_API_31310 */
        LucDTCStatusMask = DCM_ZERO;
        LucDTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
        LucDTCFormat = DEM_DTC_FORMAT_UDS;

        LblFilterWithSeverity = DCM_FALSE;
        LucDTCSeverityMask = DEM_SEVERITY_NO_SEVERITY;
        LblFilterForFaultDetectionCounter = DCM_TRUE;
      }
      /* 0x19 0x42  */
      else
      {
        /* @Trace: Dcm_SUD_API_31311 */
        Dcm_GucFunctionalGroupIdentifier = pMsgContext->reqData[DCM_ONE];
        LucDTCStatusMask = pMsgContext->reqData[DCM_TWO];
        LucDTCSeverityMask = pMsgContext->reqData[DCM_THREE];
        
        Dcm_GucTranslationType = IDem_GetTranslationType();
        LucDTCOrigin = DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY;
        LblFilterWithSeverity = DCM_TRUE;
        LblFilterForFaultDetectionCounter = DCM_FALSE;

        #if((DCM_J1979_2_SUPPORT == STD_ON) && \
           (DCM_OBD_UDS_DTC_SEPARATION_SUPPORT == STD_ON))
        {
          LucDTCFormat = DEM_DTC_FORMAT_OBD_3BYTE;
        }
		#else
        {       
          LucDTCFormat = DEM_DTC_FORMAT_UDS;
        }		     
        #endif

        if(DCM_UDS_DTC_FGID_LIMITATION != Dcm_GucFunctionalGroupIdentifier)
        {
          Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
        }
        /* Check the supported translation type */
        else if((DEM_DTC_TRANSLATION_SAEJ1939_73 != Dcm_GucTranslationType) &&
          (DEM_DTC_TRANSLATION_J2012DA_FORMAT_04 != Dcm_GucTranslationType))

        {
          Dcm_GddNegRespError = DCM_E_GENERALREJECT;
        }
		    /* Get status availability mask */
        else if(IDem_GetDTCSeverityAvailabilityMask(&LucDTCSeverityAvailabilityMask) != E_OK)
        {
          Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
        }
        else if(IDem_GetDTCStatusAvailabilityMask(&Dcm_GucAvailableDTCStatusMask) != E_OK)
        {
          Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
        }
        else
        {
          /*  Nothing */
        }
       
      }

      if(Dcm_GddNegRespError == DCM_POS_RESP)
      {
        /* @Trace: SWS_Dcm_00700 */
        if ((DCM_UDS_READ_DTC_INFO_14 == Dcm_GucSubFunction) || 
        ((LucDTCSeverityMask != DCM_ZERO) && 
		((LucDTCStatusMask & Dcm_GucAvailableDTCStatusMask) != DCM_ZERO)))
        {
          /* @Trace: SWS_Dcm_00465 SWS_Dcm_01130 */
          /* @Trace: Dcm_SUD_API_31312 */
          LucReturnRes = IDem_SetDTCFilter(
            LucDTCStatusMask, LucDTCFormat, LucDTCOrigin,
            LblFilterWithSeverity, LucDTCSeverityMask,
            LblFilterForFaultDetectionCounter, &Dcm_GddNegRespError);

            
          /* [SWS_Dcm_01043]
           * If DEM_WRONG_FILTER value is returned from 
           * Dem_ReturnSetFilterType, the Dcm module shall send a negative response with 
           * NRC 0x31 (Request out of range). */           
          if(LucReturnRes != E_OK)
          {
             Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
          }
        }
        else
        {
          /*@Trace: SWS_Dcm_01160 */
          Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
          Dcm_GpReqResData[DCM_ONE] = DCM_UDS_DTC_FGID_LIMITATION;
          Dcm_GpReqResData[DCM_TWO] = Dcm_GucAvailableDTCStatusMask;
          Dcm_GpReqResData[DCM_THREE] = LucDTCSeverityAvailabilityMask;
          Dcm_GpReqResData[DCM_FOUR] = Dcm_GucTranslationType;

          Dcm_GstMsgContext.resDataLen = DCM_FIVE;

          Dcm_GblDTCFDCPending = DCM_FALSE;
          LucReturnRes = E_NOT_OK;
        }
      }
      else
      {
        /*Nothing */
      }
    }
    else
    {
      /* @Trace: Dcm_SUD_API_31309 */
      Dcm_GblFaultDetectionCounter = DCM_FALSE;
    }
    
    /* Check if the filter was accepted */
    if ((LucReturnRes == E_OK) && (DCM_POS_RESP == Dcm_GddNegRespError))
    {
      /* @Trace: Dcm_SUD_API_31314 */
      /* Get the number of DTC matching the defined status mask */
      LddNumFilteredDTCType = IDem_GetNumberOfFilteredDTC(
        &LusNumberOfFilteredDTC);

      /* Check whether getting number of DTC was successful */
      if(LddNumFilteredDTCType == E_OK)
      {
        if (DCM_UDS_READ_DTC_INFO_14 == Dcm_GucSubFunction)
        {
          /* @Trace: Dcm_SUD_API_31317 */
          /* (3DTC + FDC counter)*counter + Sub functions */
          LulRespLength = (uint32) ((uint32) LusNumberOfFilteredDTC * DCM_FOUR) + DCM_ONE;
        }
        else
        {
          /* @Trace: Dcm_SUD_API_31318 */
          /* 5Bytes[SubService + FGID + DTCSAM + DTCSVAM + DTCFID]
           * + 5Bytes[3DTC + DTCS + SODTC]*counter */
          LulRespLength = (uint32) ((uint32) LusNumberOfFilteredDTC * DCM_FIVE) + DCM_FIVE;
        }

        /* Update the complete response length that is to be transmitted */
        pMsgContext->resDataLen = LulRespLength;

        if(LulRespLength <= (pMsgContext->resMaxDataLen))
        {
          /* @Trace: Dcm_SUD_API_31320 */
          /* Update the sub function */
          Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;

          /* Update fixed value for subservice 0x14 and 0x42 */
          if (DCM_UDS_READ_DTC_INFO_14 == Dcm_GucSubFunction)
          {
            /* @Trace: Dcm_SUD_API_31324 */
            Dcm_GpReqResData = &Dcm_GpReqResData[DCM_ONE];
            LulRespLength = LulRespLength - DCM_ONE;
          }
          else
          {
            /* @Trace: SWS_Dcm_00464 SWS_Dcm_01129 SWS_Dcm_01131 */
            /* @Trace: Dcm_SUD_API_31370 */
            Dcm_GpReqResData[DCM_ONE] = DCM_UDS_DTC_FGID_LIMITATION;
            Dcm_GpReqResData[DCM_TWO] = Dcm_GucAvailableDTCStatusMask;
            Dcm_GpReqResData[DCM_THREE] = LucDTCSeverityAvailabilityMask;
            Dcm_GpReqResData[DCM_FOUR] = Dcm_GucTranslationType;

            Dcm_GpReqResData = &Dcm_GpReqResData[DCM_FIVE];
            LulRespLength = LulRespLength - DCM_FIVE;

          }

          if (DCM_POS_RESP == Dcm_GddNegRespError)
          {
            /* @Trace: SWS_Dcm_00681 */
            /* @Trace: Dcm_SUD_API_31372 */
            (void)Dcm_DspReadReqdDTCFDC(LulRespLength);
          }
        }
        else
        {
          #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
          uint32 maxResLen = Dcm_PagedBuffer_GetMaxRespLen(pMsgContext);

          if (LulRespLength <= maxResLen)
          {
            /* @Trace: Dcm_SUD_API_31323 */
            /* Start the paged processing */
            Dcm_DsdStartPagedProcessing(pMsgContext);
          }
          else
          #endif
          {
            /* @Trace: Dcm_SUD_API_31322 */
            Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
          }
        }
      }
      else if(LddNumFilteredDTCType == DEM_PENDING)
      {
        /* @Trace: Dcm_SUD_API_31315 */
        /* Set the Flag for returning of DCM_E_PENDING */
        Dcm_GblFaultDetectionCounter = DCM_TRUE;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_31316 */
        /* For QAC Check */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }
    }
    else
    {
      /* Nothing  */
    }
  }
  
  if((Dcm_GblFaultDetectionCounter == DCM_FALSE) &&
  (Dcm_GblDTCFDCPending == DCM_FALSE))
  {
    /* @Trace: Dcm_SUD_API_31373 */
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspReadReqdDTCInfo                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function of the service Read   **
**                        DTC information (service 0x19) to list the filtered **
**                        DTcs.It will be invoked for sub-function values     **
**                        0x02, 0x0A, 0x0F, 0x13 and 0x15                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LulBufferSize                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GddNegRespError, Dcm_GpReqResData,              **
**                        Dcm_GunDTC, Dcm_GddCurrentLength, Dcm_GpMsgContext  **
**                        Function(s) invoked : Dem_GetNextFilteredDTC        **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTC == STD_ON)
FUNC(uint32, DCM_CODE) Dcm_DspReadReqdDTCInfo(uint32 LulBufferSize)
{
  uint32 LulRespBufferSize = DCM_ZERO;

  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint32 LulRemainingLength = DCM_ZERO;
  uint8 LucCount = DCM_ZERO;
  #endif

  uint8 DTCAndStatusRecordLength = DCM_ZERO;
  Std_ReturnType LucReturnRes;
  uint8 LucDTCStatus = DCM_ZERO;

  if (Dcm_GpReqResData == NULL_PTR)
  {
    /* @Trace: Dcm_SUD_API_31241 */
    /* Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT; */
  }
  else
  {
    #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
    if (DCM_TRUE == Dcm_InternalTroubleCodeService)
    {
      /* @Trace: Dcm_SUD_API_31243 */
      DTCAndStatusRecordLength = DCM_THREE;
    }
    else
    #endif
    {
      /* @Trace: Dcm_SUD_API_31244 */
      DTCAndStatusRecordLength = DCM_FOUR;
    }

    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    /* @Trace: Dcm_SUD_API_31245 */
    LulRemainingLength = DCM_ZERO;
    #endif

    /* If paging is enabled load the filtered DTC from stored */
    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    /* Check if paged transmission is in progress */
    if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
    {
      /* Check if it is the first page that is to be updated */
      if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
      {
        /* @Trace: Dcm_SUD_API_31246 */
        /* Reset the global bit flag to indicate that it is other than the first
         * page which is to be processed */
        Dcm_DspSerPgStatus.ucFirstPage = DCM_TRUE;
      }

      /* @Trace: Dcm_SUD_API_31247 */
      LulRemainingLength = Dcm_GddCurrentLength;
    }
    #endif
    /* Initialize with the configured buffer size */
    LulRespBufferSize = LulBufferSize;

    /* Initialize the global variable to indicate that no NRC as occurred */
    Dcm_GddNegRespError = DCM_POS_RESP;

    LucReturnRes = E_OK;

    #if (DCM_J1979_2_SUPPORT == STD_ON)
    /* Trace: DCM_19792_56_09 */
    /* Trace: DCM_19792_1A_05 */
    /* @Trace: [SWS_Dcm_01612 in R21-11] */
    /* If no DTC supports the requested DTC readiness group, the Dcm shall 
      send a negative response with NRC 0x31 (requestOutOfRange) */ 

    /* @Trace: [SWS_Dcm_01609 in R21-11] */
    /* If no extended data record is supported for the requested DTCExtDatarecord-Number, the Dcm shall 
      send a negative response with NRC 0x31 (requestOutOfRange) */ 
    if( ((Dcm_GucSubFunction == DCM_UDS_READ_DTC_INFO_56) || (Dcm_GucSubFunction == DCM_UDS_READ_DTC_INFO_1A)) && 
        (LulRespBufferSize == DCM_ZERO))
    {
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
    #endif /* (DCM_J1979_2_SUPPORT == STD_ON */
    
    while(
      (LulRespBufferSize >= DTCAndStatusRecordLength) &&

      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      (
        (
          (Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE) &&
          (LulRemainingLength != DCM_ZERO)
        ) 
        ||
        (
          (Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
        )
      ) &&
      #endif
      
      (LucReturnRes != DEM_NO_SUCH_ELEMENT) &&
      (Dcm_GddNegRespError == DCM_POS_RESP)
    )
    {
      /* @Trace: Dcm_SUD_API_31249 */
      LucReturnRes = IDem_GetNextFilteredDTC(&Dcm_GunDTC.ulLongReg32, &LucDTCStatus);

      if(LucReturnRes == E_OK)
      {
        #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
        if (DCM_TRUE == Dcm_InternalTroubleCodeService)
        {
          /* @Trace: Dcm_SUD_API_31251 */
          /* DTC Hight Byte */
          Dcm_GpReqResData[DCM_ZERO] = Dcm_GunDTC.ddByte.ucMidLowByte;

          /* DTC Low Byte */
          Dcm_GpReqResData[DCM_ONE] = Dcm_GunDTC.ddByte.ucLsByte;

          /* DTC Status Mask */
          Dcm_GpReqResData[DCM_TWO] = LucDTCStatus;
        }
        else
        #endif
        {
          /* @Trace: Dcm_SUD_API_31250 */
          /* DTC High Byte */
          Dcm_GpReqResData[DCM_ZERO] = Dcm_GunDTC.ddByte.ucMidHiByte;

          /* DTC Middle Byte */
          Dcm_GpReqResData[DCM_ONE] = Dcm_GunDTC.ddByte.ucMidLowByte;

          /* DTC Low Byte */
          Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucLsByte;

          /* DTC Status Mask */
          Dcm_GpReqResData[DCM_THREE] = LucDTCStatus;
        }

        /* Increment pointer by DTCAndStatusRecordLength bytes */
        Dcm_GpReqResData = &Dcm_GpReqResData[DTCAndStatusRecordLength];

        /* Update the response buffer size */
        LulRespBufferSize = LulRespBufferSize - DTCAndStatusRecordLength;

        /* Update the Temporary length of response buffer */
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
        {
          /* @Trace: Dcm_SUD_API_31255 */
          LulRemainingLength = LulRemainingLength - DTCAndStatusRecordLength;
        }
        #endif
      }
      /* @Trace: SWS_Dcm_01229 SWS_Dcm_01230 */
      else if (LucReturnRes == DEM_NO_SUCH_ELEMENT)
      {
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
        {
          /* @Trace: Dcm_SUD_API_31252 */
          Dcm_GstMsgContext.resDataLen =
          Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
        }
        #else
        /* @Trace: Dcm_SUD_API_31253 */
        /* Decrease the response length by DTCAndStatusRecordLength bytes */
        Dcm_GstMsgContext.resDataLen =
        Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
        #endif
      }
      else
      {
        /* To avoid QAC warning */
      }
    }
    
    if(LucReturnRes == DEM_NO_SUCH_ELEMENT)
    {
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)&&
        (LulRemainingLength != DCM_ZERO) &&
        (LulRespBufferSize >= DTCAndStatusRecordLength))
      {
        do
        {
          for(LucCount = DCM_ZERO; LucCount < DTCAndStatusRecordLength; LucCount++)
          {
            /* @Trace: Dcm_SUD_API_31257 */
            *Dcm_GpReqResData = DCM_ZERO;
            
            Dcm_GpReqResData++;
          }

          /* @Trace: Dcm_SUD_API_31258 */
          LulRespBufferSize = LulRespBufferSize - DTCAndStatusRecordLength;
          LulRemainingLength  = LulRemainingLength - DTCAndStatusRecordLength;

        }
        while((LulRespBufferSize >= DTCAndStatusRecordLength) &&
               (LulRemainingLength != DCM_ZERO));
      }
      #endif
    }
  }
  
  return(LulBufferSize - LulRespBufferSize);
}
#endif /* (DCM_RPT_DTC == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DspReadReqdDTCFDC                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function of the service Read   **
**                        DTC information (service 0x19) to list the Fault    **
**                        Detection Counter for all the DTCs with prefailed   **
**                        Status .It will be invoked for sub-function value   **
**                        0x14 0x42                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LulBufferSize                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GunDTC,                    **
**                        Dcm_GblDTCFDCPending, Dcm_GulFDCRespSize,           **
**                        Dcm_DspSerPgStatus, Dcm_GpMsgContext                **
**                        Dcm_GddNegRespError, Dcm_GpReqResData,              **
**                        Dcm_GddCurrentLength                                **
**                        Function(s) invoked :                               **
**                        Dem_GetNextFilteredDTCAndFDC                        **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTC_FLT_DET_CTR == STD_ON)
FUNC(uint32, DCM_CODE) Dcm_DspReadReqdDTCFDC(uint32 LulBufferSize)
{
  uint32 LulRespBufferSize = DCM_ZERO;

  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint32 LulRemainingLength = DCM_ZERO;
  #endif

  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint8 LucCount = DCM_ZERO;
  #endif

  Std_ReturnType LucReturnRes;
  sint8 LscDTCFaultDetectionCounter;
  uint8 LucDTCStatus;
  Dem_DTCSeverityType LddDTCSeverity;
  uint8 DTCFunctionalUnit;

  Dcm_GblDTCFDCPending = DCM_FALSE;
  Dcm_GulFDCRespSize = LulBufferSize;

  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  LulRemainingLength = DCM_ZERO;
  #endif

  if ((Dcm_GpReqResData == NULL_PTR))
  {
    /* @Trace: Dcm_SUD_API_31222 */
    /* Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT; */
  }
  else
  {
    /* If paging is enabled load the filtered DTC from stored */
    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    /* Check if paged transmission is in progress */
    if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
    {
      /* Check if it is the first page that is to be updated */
      if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
      {
        /* @Trace: Dcm_SUD_API_31223 */
        /* Reset the global bit flag to indicate that it is other than the first
         * page which is to be processed */
        Dcm_DspSerPgStatus.ucFirstPage = DCM_TRUE;
      }

      /* @Trace: Dcm_SUD_API_31224 */
      LulRemainingLength = Dcm_GddCurrentLength;
    }
    #endif

    /* Initialize with the configured buffer size */
    LulRespBufferSize = LulBufferSize;

    /* Initialize the global variable to indicate that no NRC as occurred */
    Dcm_GddNegRespError = DCM_POS_RESP;

    LucReturnRes = E_OK;

    while ((LulRespBufferSize > DCM_THREE) &&
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      (
        ((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE) &&
         (LulRemainingLength != DCM_ZERO)) ||
         ((Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE))
      ) &&
      #endif
      /* @Trace: SWS_Dcm_01234*/
      (LucReturnRes != DEM_NO_SUCH_ELEMENT))
    {
      /* @Trace: Dcm_SUD_API_31226 Dcm_SUD_API_31227 */
      LucReturnRes = (DCM_UDS_READ_DTC_INFO_14 == Dcm_GucSubFunction) ? \
        IDem_GetNextFilteredDTCAndFDC(&Dcm_GunDTC.ulLongReg32,
          &LscDTCFaultDetectionCounter) :
        IDem_GetNextFilteredDTCAndSeverity(&Dcm_GunDTC.ulLongReg32, 
          &LucDTCStatus, &LddDTCSeverity, &DTCFunctionalUnit);

      if (LucReturnRes == E_OK)
      {
        /* Assemble respond msg for subservice 0x14 */
        if (DCM_UDS_READ_DTC_INFO_14 == Dcm_GucSubFunction)
        {
          /* @Trace: Dcm_SUD_API_31231 */
          /* DTC High Byte */
          Dcm_GpReqResData[DCM_ZERO] = Dcm_GunDTC.ddByte.ucMidHiByte;
         
          /* DTC Middle Byte */
          Dcm_GpReqResData[DCM_ONE] = Dcm_GunDTC.ddByte.ucMidLowByte;
      
          /* DTC Low Byte */
          Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucLsByte;
      
          /* DTC Status Mask */
          Dcm_GpReqResData[DCM_THREE] = (uint8)LscDTCFaultDetectionCounter;

          Dcm_GpReqResData =  &Dcm_GpReqResData[DCM_FOUR];
      
          /* Update the response buffer size */
          LulRespBufferSize = LulRespBufferSize - DCM_FOUR;

          /* Update the Temporary length of response buffer */
          #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
          if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
          {
            /* @Trace: Dcm_SUD_API_31233 */
            LulRemainingLength = LulRemainingLength - DCM_FOUR;
          }
          #endif
        }
        /* Assemble respond msg for subservice 0x42 */
        else
        {
          /* @Trace: Dcm_SUD_API_31232 */
          /* DTC Severity */
          Dcm_GpReqResData[DCM_ZERO] = LddDTCSeverity;

          /* DTC High Byte */
          Dcm_GpReqResData[DCM_ONE] = Dcm_GunDTC.ddByte.ucMidHiByte;
         
          /* DTC Middle Byte */
          Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucMidLowByte;
      
          /* DTC Low Byte */
          Dcm_GpReqResData[DCM_THREE] = Dcm_GunDTC.ddByte.ucLsByte;
      
          /* DTC Status Mask */
          Dcm_GpReqResData[DCM_FOUR] = LucDTCStatus;

          Dcm_GpReqResData =  &Dcm_GpReqResData[DCM_FIVE];
      
          /* Update the response buffer size */
          LulRespBufferSize = LulRespBufferSize - DCM_FIVE;

          /* Update the Temporary length of response buffer */
          #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
          if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
          {
            /* @Trace: Dcm_SUD_API_31234 */
            LulRemainingLength = LulRemainingLength - DCM_FIVE;
          }
          #endif
        }
      }
      /* @Trace: SWS_Dcm_01232 SWS_Dcm_01233 SWS_Dcm_01235 */
      else if(LucReturnRes == DEM_NO_SUCH_ELEMENT)
      {
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
        {
          /* @Trace: Dcm_SUD_API_31230 */
          Dcm_GstMsgContext.resDataLen =
          Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
        }
        #else
        /* @Trace: Dcm_SUD_API_31229 */
        /* Decrease the response length by 4 bytes */
        Dcm_GstMsgContext.resDataLen =
        Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
        #endif
      }
      else
      {
        /* @Trace: Dcm_SUD_API_31228 */
        Dcm_GblDTCFDCPending = DCM_TRUE;
      }
    }

    if(LucReturnRes == DEM_NO_SUCH_ELEMENT)
    {
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)&&
        (LulRemainingLength != DCM_ZERO) && (LulRespBufferSize > DCM_THREE))
      {
        do
        {
          for(LucCount = DCM_ZERO; LucCount < DCM_FOUR; LucCount++)
          {
            /* @Trace: Dcm_SUD_API_31236 */
            *Dcm_GpReqResData = DCM_ZERO;

            /* MISRA Rule        : 17.4
              Message            : Increment or decrement operation
                                   performed on pointer
              Reason             : Increment operator not used
                                   to achieve better throughput.
              Verification       : However, part of the code
                                   is verified manually and
                                   it is not having any impact.
            */
            Dcm_GpReqResData++;
          }

          /* @Trace: Dcm_SUD_API_31237 */
          LulRespBufferSize = LulRespBufferSize - DCM_FOUR;
          LulRemainingLength  = LulRemainingLength - DCM_FOUR;

        }
        while((LulRespBufferSize > DCM_THREE) &&
        (LulRemainingLength != DCM_ZERO));
      }
      #endif

      /* @Trace: SWS_Dcm_01233 */
      if (LulRespBufferSize == LulBufferSize)
      {
        /* @Trace: SWS_Dcm_01235 */
        /* @Trace: Dcm_SUD_API_31235 Dcm_SUD_API_31238 */
        Dcm_GstMsgContext.resDataLen = (DCM_UDS_READ_DTC_INFO_14 == Dcm_GucSubFunction) 
         ? DCM_ONE : DCM_FIVE;
      }
    }
  }

  return(LulBufferSize - LulRespBufferSize);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspRptDTCBySeverityInfo                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is sub-function of the service Read DTC        **
**                        information (service 0x19) to read the DTC and      **
**                        associated severity and status information matching **
**                        a specific severity mask. It will be invoked for    **
**                        sub-function value 0x08                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_GblNumFilterDTCStatusBySevirtMask               **
**                        Dcm_GusMaxNoOfRespPend, Dcm_DspSerPgStatus,         **
**                        Dcm_GucReadGlobal, Dcm_GucAvailableDTCStatusMask    **
**                        Function(s) invoked :                               **
**                        Dcm_GetNumberOfFilteredDtcBySeverityInfo            **
**                        Dcm_ExternalSetNegResponse                          **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptDTCBySeverityInfo(
 P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dem_DTCSeverityType LddSeverityMask = (Dem_DTCSeverityType) DCM_ZERO;
  Std_ReturnType LucReturnRes;
  uint8 LucDTCStatusMask = (uint8) DCM_ZERO;

  Dcm_GddNegRespError = DCM_POS_RESP;
  Dcm_GusMaxNoOfRespPend = DCM_ZERO;
  Dcm_GblNumFilterDTCStatusBySevirtMask = DCM_FALSE;
  Dcm_GucReadGlobal = DCM_TRUE;

  if ((pMsgContext == NULL_PTR) || 
    (pMsgContext->resData == NULL_PTR) ||
    (pMsgContext->reqData == NULL_PTR)
  )
  {
    /* @Trace: Dcm_SUD_API_31287 */
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31288 */
    /* Get the DTC status information supported by the DEM */
    LucReturnRes = IDem_GetDTCStatusAvailabilityMask(
      &Dcm_GucAvailableDTCStatusMask);
    
    /* Check whether the DTC status mask was successful */
    if(LucReturnRes == E_OK)
    {
      /* @Trace: Dcm_SUD_API_31290 */
      /* Get information of DTC Status Mask */
      LddSeverityMask = pMsgContext->reqData[DCM_ONE];

      /* Get information of DTC Status Mask */
      LucDTCStatusMask = pMsgContext->reqData[DCM_TWO];

      /*
       * Set the filter mask over all DTCs for the API Dem_GetNextFilteredDTC
       * and reset the internal counter to the first event that matches the
       * filter settings
       */
      /* @Trace: SWS_Dcm_01160 */
      if ((LddSeverityMask != DCM_ZERO) &&
         (LucDTCStatusMask != DCM_ZERO) &&
         ((LucDTCStatusMask & Dcm_GucAvailableDTCStatusMask) != DCM_ZERO))
      {
        /* @Trace: Dcm_SUD_API_31291 */
        LucReturnRes = IDem_SetDTCFilter(
          (Dcm_GucAvailableDTCStatusMask & LucDTCStatusMask),
          DEM_DTC_FORMAT_UDS, DEM_DTC_ORIGIN_PRIMARY_MEMORY,
          DCM_TRUE, LddSeverityMask, DCM_FALSE, &Dcm_GddNegRespError);
        
        /* Check if the filter was accepted */
        if(LucReturnRes == E_OK)
        {
          /* @Trace: Dcm_SUD_API_31292 */
          Dcm_GetNumberOfFilteredDtcBySeverityInfo();
        }
      }
      else
      {
        /* @Trace: Dcm_SUD_API_31293 */
        /* Update the response data length */
        pMsgContext->resDataLen = DCM_TWO;

        pMsgContext->resData[DCM_ZERO] = Dcm_GucSubFunction;

        /* Update DTC status availabilityMask */
        pMsgContext->resData[DCM_ONE] = Dcm_GucAvailableDTCStatusMask;

        /* Update the global variable to indicate that no NRC has occurred */
        Dcm_GddNegRespError = DCM_POS_RESP;
      }
    }
    else
    {
      /* @Trace: Dcm_SUD_API_31289 */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
  
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
  #endif
  {
    if(Dcm_GblNumFilterDTCStatusBySevirtMask == DCM_FALSE)
    {
      /* @Trace: Dcm_SUD_API_31294 */
      /* Send response from main function */
      Dcm_GblSendResponse = DCM_TRUE;
    }
  }
}
#endif

/*******************************************************************************
** Function Name        :Dcm_GetNumberOfFilteredDtcBySeverityInfo             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          :  This is the internal function of the service Read  **
**                         DTC information (service 0x19) to list the number  **
**                         of Reported Filtered DTcs by Severity Information. **
**                         It will be invoked for sub-function value          **
**                         0x08                                               **
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
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_GblNumFilterDTCStatusBySevirtMask,              **
**                        Dcm_GpMsgContext, Dcm_GucAvailableDTCStatusMask,    **
**                        Dcm_GucRecordNumber, Dcm_DspSerPgStatus,            **
**                        Function(s) invoked :                               **
**                        Dcm_DspUpdDTCBySeverityMask                         **
**                        Dcm_DsdStartPagedProcessing                         **
**                                                                            **
*******************************************************************************/
#if (DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
FUNC(void, DCM_CODE) Dcm_GetNumberOfFilteredDtcBySeverityInfo(void)
{
  Std_ReturnType LddNumFilteredDTCType;
  uint32 LulRespLength;
  uint16 LusNumberOfFilteredDTC = (uint16) DCM_ZERO;
  Dcm_GblNumFilterDTCStatusBySevirtMask = DCM_FALSE;

  if (Dcm_GpReqResData == NULL_PTR)
  {
    /* @Trace: Dcm_SUD_API_31361 */
    /* For Misra-C Check */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31360 */
    /* Get the number of DTC matching the defined status mask */
    LddNumFilteredDTCType = IDem_GetNumberOfFilteredDTC(&LusNumberOfFilteredDTC);

    /* Check if the response buffer is to be updated */
    if(LddNumFilteredDTCType == E_OK)
    {
      /* @Trace: Dcm_SUD_API_31362 */
      /* DTCHighByte + DTCLiddleByte  + DTCLowByte + DTCStatus +
       * DTCFunctionalUnit + DTCSeverity = 6 for every DTC + 2 */
      LulRespLength = (uint32) \
        (((uint32)LusNumberOfFilteredDTC << (uint32)DCM_TWO) + \
        ((uint32)LusNumberOfFilteredDTC << (uint32)DCM_ONE) + (uint32)DCM_TWO);

      Dcm_GstMsgContext.resDataLen = LulRespLength;
            
      if(LulRespLength <= (Dcm_GstMsgContext.resMaxDataLen))
      {
        /* @Trace: Dcm_SUD_API_31365 */
        /* Update the sub function */
        Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;

        /* Update DTC status availabilityMask */
        Dcm_GpReqResData[DCM_ONE] = Dcm_GucAvailableDTCStatusMask;

        /* Reset the pointer to the response data buffer */
        Dcm_GpReqResData = &Dcm_GpReqResData[DCM_TWO];

        /*
        * Pass the buffer size with two values less since sub function and
        * availabilityMask is already updated
        */
        LulRespLength = LulRespLength - DCM_TWO;

        (void)Dcm_DspUpdDTCBySeverityMask(LulRespLength);
      }
      else
      {
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        uint32 maxResLen = Dcm_PagedBuffer_GetMaxRespLen(&Dcm_GstMsgContext);

        if (LulRespLength <= maxResLen)
        {
          /* @Trace: Dcm_SUD_API_31367 */
          /* This variable is re used to store DTC Mask */
          Dcm_GucRecordNumber = Dcm_GucAvailableDTCStatusMask;

          /* Start the paged processing */
          Dcm_DsdStartPagedProcessing(&Dcm_GstMsgContext);
        }
        else
        #endif
        {
          /* @Trace: Dcm_SUD_API_31368 */
          Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
        }
      }
    }
    else if(LddNumFilteredDTCType == DEM_PENDING)
    {
      /* @Trace: Dcm_SUD_API_31363 */
      /* Set the Flag for returning of DCM_E_PENDING */
      Dcm_GblNumFilterDTCStatusBySevirtMask = DCM_TRUE;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_31364 */
      /* For QAC Check */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspUpdDTCBySeverityMask                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function used for sub-functions**
**                        0x08 to read the DTC and associated severity Record **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LulBufferSize                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GddNegRespError, Dcm_GddCurrentLength,          **
**                        Dcm_GpReqResData, Dcm_GunDTC, Dcm_GpMsgContext.     **
**                        Function(s) invoked :                               **
**                        Dem_GetStatusOfDTC,                                 **
**                        Dem_GetNextFilteredDTCAndSeverity                   **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
FUNC(uint32, DCM_CODE) Dcm_DspUpdDTCBySeverityMask(
  uint32 LulBufferSize)
{
  Std_ReturnType LddGetNextFilteredDTC;
  Dem_DTCSeverityType LddDTCSeverity = (Dem_DTCSeverityType) DCM_ZERO;

  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint32 LulRemainingLength = DCM_ZERO;
  #endif

  uint32 LulRespBufferSize = DCM_ZERO;

  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint8 LucCount = DCM_ZERO;
  #endif

  uint8 LucDTCStatus = (uint8) DCM_ZERO;
  uint8 DTCFunctionalUnit = DCM_ZERO;

  LddGetNextFilteredDTC = E_OK;

  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  LulRemainingLength = DCM_ZERO;
  #endif

  if (Dcm_GpReqResData == NULL_PTR)
  {
    /* @Trace: Dcm_SUD_API_31339 */
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* If paging is enabled load the filtered DTC from stored */
    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    /* Check if paged transmission is in progress */
    if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
    {
      /* Check if it is the first page that is to be updated */
      if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
      {
        /* @Trace: Dcm_SUD_API_31340 */
        /* Reset the global bit flag to indicate that it is other than the first
         * page which is to be processed */
        Dcm_DspSerPgStatus.ucFirstPage = DCM_TRUE;
      }

      /* @Trace: Dcm_SUD_API_31341 */
      LulRemainingLength = Dcm_GddCurrentLength;
    }
    #endif

    LulRespBufferSize = LulBufferSize;

    /* Set the global variable indicating NRC occurred to FALSE */
    Dcm_GddNegRespError = DCM_POS_RESP;

    /* Check if the response buffer is available and the filled
     * length is not greater than the remaining length to be transmitted */
    while (
      (LulRespBufferSize > DCM_FIVE) &&
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      (((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE) && 
        (LulRemainingLength != DCM_ZERO)) ||
       (Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE))
      &&
      #endif
      /* @Trace: SWS_Dcm_01234 */
      (LddGetNextFilteredDTC != DEM_NO_SUCH_ELEMENT)
    )
    {
      /* @Trace: SWS_Dcm_00380 */
      /* @Trace: Dcm_SUD_API_31343 */
      LddGetNextFilteredDTC =  IDem_GetNextFilteredDTCAndSeverity(
        &Dcm_GunDTC.ulLongReg32, &LucDTCStatus, 
        &LddDTCSeverity, &DTCFunctionalUnit);

      /* @Trace: SWS_Dcm_00379 */
      if(LddGetNextFilteredDTC == E_OK)
      {
        /* @Trace: Dcm_SUD_API_31344 */
        /* Update severity */
        Dcm_GpReqResData[DCM_ZERO] = LddDTCSeverity;
        /* FunctionalUnit */
        Dcm_GpReqResData[DCM_ONE] = DTCFunctionalUnit;
        /* DTC High Byte */
        Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucMidHiByte;
        /* DTC Middle Byte */
        Dcm_GpReqResData[DCM_THREE] = Dcm_GunDTC.ddByte.ucMidLowByte;
        /* DTC Low Byte */
        Dcm_GpReqResData[DCM_FOUR] = Dcm_GunDTC.ddByte.ucLsByte;
        /* DTC Status Mask */
        Dcm_GpReqResData[DCM_FIVE] = LucDTCStatus;

        /* Increment pointer by six bytes */
        Dcm_GpReqResData = &Dcm_GpReqResData[DCM_SIX];
        /* Update the response buffer size */
        LulRespBufferSize = LulRespBufferSize - DCM_SIX;

        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
        {
          /* @Trace: Dcm_SUD_API_31347 */
          LulRemainingLength = LulRemainingLength - DCM_SIX;
        }
        #endif
      }
      /* @Trace: SWS_Dcm_01235 */
      else if(LddGetNextFilteredDTC == DEM_NO_SUCH_ELEMENT)
      {
        #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
        {
          /* @Trace: Dcm_SUD_API_31345 */
          Dcm_GstMsgContext.resDataLen =
            Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
        }
        #else
        /* @Trace: Dcm_SUD_API_31346 */
        /* To exit from while loop */
        /* Decrease the response length by 4 bytes */
        Dcm_GstMsgContext.resDataLen =
          Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
        #endif
      }
      else
      {
        /* To avoid QAC warning */
      }
    }

    if(LddGetNextFilteredDTC == DEM_NO_SUCH_ELEMENT)
    {
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)&&
        (LulRemainingLength != DCM_ZERO) && (LulRespBufferSize > DCM_FIVE))
      {
        do
        {
          for(LucCount = DCM_ZERO; LucCount < DCM_SIX; LucCount++)
          {
            /* @Trace: Dcm_SUD_API_31349 */
            *Dcm_GpReqResData = DCM_ZERO;

            /* MISRA Rule        : 17.4
              Message            : Increment or decrement operation
                                   performed on pointer
              Reason             : Increment operator not used
                                   to achieve better throughput.
              Verification       : However, part of the code
                                   is verified manually and
                                   it is not having any impact.
            */
            Dcm_GpReqResData++;
          }

          /* @Trace: Dcm_SUD_API_31350 */
          LulRespBufferSize = LulRespBufferSize - DCM_SIX;
          LulRemainingLength  = LulRemainingLength - DCM_SIX;

        }
        while((LulRespBufferSize > DCM_FIVE) &&
        (LulRemainingLength != DCM_ZERO));
      }
      #endif
    }

    /* @Trace: Dcm_SUD_API_31351 */
    LulRespBufferSize = (LulBufferSize - LulRespBufferSize);
  }

  return LulRespBufferSize;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspRptDTCBySeverityInfoOfDTC                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the function used for the service Read DTC  **
**                        information (service 0x19) to read the DTC and      **
**                        associated severity and status information matching **
**                        a specific severity mask. It will be invoked for    **
**                        sub-function values 0x09                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_GucRecordNumber, Dcm_DspSerPgStatus,            **
**                        Dcm_GucReadGlobal                                   **
**                        Function(s) invoked :                               **
**                        Dcm_DsdStartPagedProcessing,                        **
**                        Dcm_DspUpdDTCBySeverityMaskInfo,                    **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04156 */
#if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptDTCBySeverityInfoOfDTC(
 P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  uint8 LucAvailableDTCStatusMask = (uint8) DCM_ZERO;
  Std_ReturnType LucReturnRes;
  Dcm_GucReadGlobal = DCM_TRUE;

  if ((pMsgContext == NULL_PTR) || 
    (pMsgContext->resData == NULL_PTR) ||
    (pMsgContext->reqData == NULL_PTR))
  {
    /* @Trace: Dcm_SUD_API_31296 */
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31297 */
    /* Initialize the pointer to the request data buffer */
    /* Get the DTC status information supported by the DEM */
    LucReturnRes = IDem_GetDTCStatusAvailabilityMask(&LucAvailableDTCStatusMask);

    /* Check whether the DTC status mask was successful */
    if(LucReturnRes == E_OK)
    {
      /* @Trace: Dcm_SUD_API_31299 */
      /*
      * Update the local variable for response length.
      * Response bytes -> Subfunction + DTCStatusAvailabilityMask + DTCHighByte
      * + DTCLiddleByte + DTCLowByte + DTCStatus + DTCFunctionalUnit +
      * DTCSeverity
      */
      /* Get the DTC for the input request */
      Dcm_GunDTC.ddByte.ucLsByte      = pMsgContext->reqData[DCM_THREE];
      Dcm_GunDTC.ddByte.ucMidLowByte  = pMsgContext->reqData[DCM_TWO];
      Dcm_GunDTC.ddByte.ucMidHiByte   = pMsgContext->reqData[DCM_ONE];
      Dcm_GunDTC.ddByte.ucMsByte      = DCM_ZERO;
      

      /* Initialize the global pointer with response data buffer address */
      Dcm_GpReqResData = pMsgContext->resData;

      /* Update the response data length in the pMsgContext */
      // pMsgContext->resDataLen = DCM_EIGHT;
      /*
      * Check if the response buffer is capable of accommodating the complete
      * response at once
      */
      if(DCM_EIGHT <= (pMsgContext->resMaxDataLen))
      {
        /* @Trace: Dcm_SUD_API_31300 */
        /* Update the sub function */
        Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
        /* Update DTC status availabilityMask */
        Dcm_GpReqResData[DCM_ONE] = LucAvailableDTCStatusMask;
        /* Reset the pointer to the response data buffer */
        Dcm_GpReqResData = &Dcm_GpReqResData[DCM_TWO];

        /* @Trace: SWS_Dcm_01402 SWS_Dcm_00381 */
        if (E_OK == IDem_SelectDTC(Dcm_GunDTC.ulLongReg32, DEM_DTC_FORMAT_UDS,
                      DEM_DTC_ORIGIN_PRIMARY_MEMORY))
        {
          /* @Trace: Dcm_SUD_API_31302 */
          Dcm_DspUpdDTCBySeverityMaskInfo(pMsgContext);
        }
        else
        {
          /* @Trace: Dcm_SUD_API_31303 */
          /* Update NRC to 0x22 */
          Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
        }
      }
      else
      {
        /* @Trace: Dcm_SUD_API_31301 */
        /* This variable is reused to store DTCMask */
        /* Set the global bit flag for paging started to TRUE */
        /* Start the paged processing */
        /*
        * Update the NRC if the response length is greater than the
        * response buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled
        */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
      }
    }
    else
    {
      /* @Trace: Dcm_SUD_API_31298 */
      /* Update Negative response as condition not correct  */
      Dcm_GddNegRespError  =  DCM_E_CONDITIONSNOTCORRECT;
    }
  }
  
  /* Send response from main function */
  Dcm_GblSendResponse = DCM_TRUE;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspUpdDTCBySeverityMaskInfo                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is internal function for sub-functions 0x09    **
**                        used to read the DTC and associated severity and    **
**                        status information matching a specific severity mask**
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
** Remarks              : Global Variable(s) : Dcm_GunDTC,                    **
**                        Dcm_GddNegRespError, Dcm_GpReqResData,              **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
static FUNC(void, DCM_CODE) Dcm_DspUpdDTCBySeverityMaskInfo(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType LddReturnValue;
  Std_ReturnType LddDTCSeverity = E_NOT_OK;
  uint8 LddFunctionalUnit;
  uint8 LddDTCStatus;
  Dem_DTCSeverityType LucSvtyStatus;

  if (Dcm_GpReqResData == NULL_PTR)
  {
    /* @Trace: Dcm_SUD_API_31353 */
    /* For Misra-C Check */   
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31354 */
    /* If paging is enabled load the filtered DTC from stored */
    /* Check if paged transmission is in progress */

    /* Check if it is the first page that is to be updated */
    /*
     * Reset the global bit flag to indicate that it is other than the first
     * page which is to be processed
    */

    /* @Trace: SWS_Dcm_01405 */
    /* Get the status of the DTC */
    LddReturnValue = IDem_GetStatusOfDTC(&LddDTCStatus);

    /* @Trace: SWS_Dcm_01403 */
    /* Read the severity of the DTC */
    CHK_RET_VAL(LddReturnValue == E_OK, LddDTCSeverity, IDem_GetSeverityOfDTC(&LucSvtyStatus));

    /* @Trace: SWS_Dcm_01404 */
    CHK_RET_VAL(LddDTCSeverity == E_OK, LddReturnValue , IDem_GetFunctionalUnitOfDTC(&LddFunctionalUnit));

    /* @Trace: SWS_Dcm_01409*/
    if ((LddReturnValue == E_OK) && (LddDTCSeverity == E_OK))
    {
      /* @Trace: Dcm_SUD_API_31355 */
      pMsgContext->resDataLen = DCM_EIGHT;
      /* Update severity */
      Dcm_GpReqResData[DCM_ZERO] = LucSvtyStatus;
      /* FunctionalUnit */
      Dcm_GpReqResData[DCM_ONE] = LddFunctionalUnit;
      /* DTC High Byte */
      Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucMidHiByte;
      /* DTC Middle Byte */
      Dcm_GpReqResData[DCM_THREE] = Dcm_GunDTC.ddByte.ucMidLowByte;
      /* DTC Low Byte */
      Dcm_GpReqResData[DCM_FOUR] = Dcm_GunDTC.ddByte.ucLsByte;
      /* DTC Status Mask */
      Dcm_GpReqResData[DCM_FIVE] = LddDTCStatus;
    }
    else if (LddReturnValue == DEM_NO_SUCH_ELEMENT)
    {
      /* @Trace: Dcm_SUD_API_31356 */
      pMsgContext->resDataLen = DCM_TWO;
    }
    /* @Trace: SWS_Dcm_01226 SWS_Dcm_01240 SWS_Dcm_01406  SWS_Dcm_01250*/
    else if ((LddReturnValue == DEM_WRONG_DTC) ||
        (LddReturnValue == DEM_WRONG_DTCORIGIN) ||
        (LddDTCSeverity == DEM_WRONG_DTC))
    {
      /* @Trace: Dcm_SUD_API_31357 */
      /* Update NRC to 0x31 */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_31358 */
      /* Update NRC to 0x22 */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
