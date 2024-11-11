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
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions of the Read DTC            **
**              subfunctions  0x01, 0x07, 0x11, 0x12, 0x0B, 0x0C, 0x0D, 0x0E, **
**              and 0x05 that do not require paged processing                 **
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
** 0.0.2     05-May-2019   LamNV10        Change page buffer machanism for    **
**                                        service 0x19 sub 04 06 10 18 19     **
** 0.0.3     20-Aug-2020   HueKM          Fix defect and coding rules         **
** 0.0.4     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.5     02-Nov-2020   LanhLT         Changes made as per #16832          **
** 0.0.6     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.7     21-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_DspNonPagedDTCSubFct.h"
#include "Dcm_Ram.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DspServices.h"
#include "Dcm_Config.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dem.h"
#include "Dcm_DemInterfaces.h"
#include "Dcm_DspOBDInternals.h"
#endif
#include "Dcm_Utils.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dcm_DspRptNoOfDTC                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for the service Read DTC      **
**                        information (service 0x19) to read the number of    **
**                        DTC matching a specific status mask, severity mask, **
**                        memory location and DTC type. It will be invoked    **
**                        for sub-function values 0x01, 0x07, 0x11 and 0x12   **
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
**                        Dcm_PrtclTxBufStatus, Dcm_GucReadGlobal,            **
**                        Dcm_GucAvailableDTCStatusMask, Dcm_GpReqResData,    **
**                        Dcm_GddNegRespError, Dcm_GucAvailableDTCStatusMask, **
**                        Dcm_GucTranslationType, Dcm_GpMsgContext            **
**                                                                            **
**                        Function(s) invoked : Dcm_ExternalSetNegResponse    **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if(DCM_RPT_NOOFDTC == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptNoOfDTC 
  (P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)pMsgContext)
{
  Dem_DTCSeverityType LddDTCSeverityMask = (Dem_DTCSeverityType) DCM_ZERO;
  Dem_DTCOriginType LddDTCOrigin;

  boolean LddFilterWithSeverity;
  Std_ReturnType LddReturnValue;
  uint8 LucDTCStatusMask = (uint8) DCM_ZERO;

  Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_FALSE;
  Dcm_GucReadGlobal = DCM_TRUE;
    
  if ((pMsgContext == NULL_PTR)
   || (pMsgContext->resData == NULL_PTR)
   || (pMsgContext->reqData == NULL_PTR))
  {
    /* @Trace: Dcm_SUD_API_50200 */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* Clear error variable */
    Dcm_GddNegRespError = DCM_POS_RESP;

    /* Check whether sub function requested is 0x07 */
    if(Dcm_GucSubFunction == DCM_UDS_READ_DTC_INFO_07)
    {
      /* @Trace: Dcm_SUD_API_50201 */
      LddFilterWithSeverity = DCM_TRUE;
      LddDTCSeverityMask = pMsgContext->reqData[DCM_ONE];
      LucDTCStatusMask = pMsgContext->reqData[DCM_TWO];
    }
    /* Without severity, For Sub function 0x01, 0x11, 0x12 */
    else
    {
      /* @Trace: Dcm_SUD_API_50202 */
      LddFilterWithSeverity = DCM_FALSE;
      LddDTCSeverityMask = DEM_SEVERITY_NO_SEVERITY; // Not relevant

      /* Get information of DTC StatusMask */
      LucDTCStatusMask = pMsgContext->reqData[DCM_ONE];
    }

    /* Update the origin to Primary Memory */
    if(Dcm_GucSubFunction == DCM_UDS_READ_DTC_INFO_11)
    {
      /* @Trace: Dcm_SUD_API_50203 */
      /* Update origin as primary for service 0x11 */
      LddDTCOrigin = DEM_DTC_ORIGIN_MIRROR_MEMORY;
    }
    else if (Dcm_GucSubFunction == DCM_UDS_READ_DTC_INFO_12)
    {
      /* @Trace: SWS_Dcm_00293 */
      /* @Trace: SRS_Diag_04067 */
      /* @Trace: Dcm_SUD_API_50204 */
      /* Update origin as obd reveant memory for service 0x12 */
      LddDTCOrigin = DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_50205 */
      /* Update origin as primary for service 0x01, 0x07 */
      LddDTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
    }

    LddReturnValue = IDem_GetDTCStatusAvailabilityMask(
      &Dcm_GucAvailableDTCStatusMask);
    
    /* @Trace: SWS_Dcm_00376 */
    if (LddReturnValue == E_OK)
    {
      /* Get the Translation type */
      Dcm_GucTranslationType = IDem_GetTranslationType();

      /* Check Whether Transalation type supported or not */
      if((Dcm_GucTranslationType == DEM_DTC_TRANSLATION_ISO15031_6)  ||
        (Dcm_GucTranslationType == DEM_DTC_TRANSLATION_ISO14229_1)  ||
        (Dcm_GucTranslationType == DEM_DTC_TRANSLATION_SAEJ1939_73) ||
        (Dcm_GucTranslationType == DEM_DTC_TRANSLATION_ISO11992_4)  ||
        (Dcm_GucTranslationType == DEM_DTC_TRANSLATION_J2012DA_FORMAT_04) ) 
      {
        /* @Trace: SWS_Dcm_01160 SWS_Dcm_00700 */
        if((LucDTCStatusMask != DCM_ZERO) &&
           ((Dcm_GucSubFunction != DCM_UDS_READ_DTC_INFO_07) || (LddDTCSeverityMask != DCM_ZERO)) &&
           ((Dcm_GucAvailableDTCStatusMask & LucDTCStatusMask) != DCM_ZERO))
        {
          /* @Trace: SWS_Dcm_00835 */
          /* @Trace: Dcm_SUD_API_50206 */
          LddReturnValue = IDem_SetDTCFilter(
            (Dcm_GucAvailableDTCStatusMask & LucDTCStatusMask),
            DEM_DTC_FORMAT_UDS, LddDTCOrigin, LddFilterWithSeverity,
            LddDTCSeverityMask, DCM_FALSE, &Dcm_GddNegRespError);

          /* Check if the filter was accepted */
          if(LddReturnValue == E_OK)
          {
            /* @Trace: Dcm_SUD_API_50207 */
            Dcm_DemGetNumberOfFilteredDtc(pMsgContext);
          }
        }
        else
        {
          /* @Trace: Dcm_SUD_API_50208 */
          /* Update the response data length */
          pMsgContext->resDataLen = DCM_FIVE;

          /* Update sub-function number */
          pMsgContext->resData[0U] = Dcm_GucSubFunction;

          /* Update DTC status availabilityMask */
          pMsgContext->resData[1U] = Dcm_GucAvailableDTCStatusMask;

          /* Get Format Identifier */
          pMsgContext->resData[2U] = Dcm_GucTranslationType;

          /* Update DTC CountHighByte */
          pMsgContext->resData[3U] = DCM_ZERO;

          /* Update DTC CountLowByte */
          pMsgContext->resData[4U] = DCM_ZERO;
        
          /* Update the global variable to indicate that no NRC has occurred */
          Dcm_GddNegRespError = DCM_POS_RESP;
        }
      }
      else
      {
        /* @Trace: Dcm_SUD_API_50209 */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }
    }
    else 
    {
      /* @Trace: Dcm_SUD_API_50210 */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }

  if(Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus == DCM_FALSE)
  {
    /* @Trace: Dcm_SUD_API_50211 */
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_DemGetNumberOfFilteredDtc                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is a internal function for sub-function of the **
**                        service 0x19 to get the number of filtered DTC      **
**                        It will be invoked for sub-function values          **
**                        0x01, 0x07, 0x11 and 0x12                           **
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
**                        Dcm_PrtclTxBufStatus, Dcm_GpMsgContext,             **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_GucAvailableDTCStatusMask, Dcm_TxRespStatus     **
**                        Dcm_GucTranslationType                              **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DemGetNumberOfFilteredDtc
  (P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType LddNumFilteredDTCType;

  /* MISRA Rule : 18.4
   * Message : Unions shall not be used.
   * Reason : For optimization.
   * Verification : Iit is not having any impact */
  Tun_DcmWord16 LunDcmWord16;
  uint16 LusNumberOfFilteredDTC = (uint16) DCM_ZERO;

  Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_FALSE;

  if ((pMsgContext == NULL_PTR)
   || (pMsgContext->resData == NULL_PTR)
   || (pMsgContext->reqData == NULL_PTR))
  {
    /* @Trace: Dcm_SUD_API_50212 */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* Get the number of DTC matching the defined status mask */
    LddNumFilteredDTCType = IDem_GetNumberOfFilteredDTC(&LusNumberOfFilteredDTC);  
    
     /* Check whether getting number of DTC was successful */
    if(LddNumFilteredDTCType == E_OK)
    {
      /* @Trace: Dcm_SUD_API_50213 */
      /* Update the response data length */
      pMsgContext->resDataLen = DCM_FIVE;
      
      /* Response for the service 0x01, 0x07, 0x11 Subfunction +
       * DTCStatusAvailabilityMask + DTCFormatIdentifier + DTC count */
      /* Update number of DTC matching the defined status mask */
      LunDcmWord16.usWordReg16 = LusNumberOfFilteredDTC;

      /* Update sub-function number */
      pMsgContext->resData[0U] = Dcm_GucSubFunction;
  
      /* Update DTC status availabilityMask */
      pMsgContext->resData[1U] = Dcm_GucAvailableDTCStatusMask;
  
      /* Get Format Identifier */
      pMsgContext->resData[2U] = Dcm_GucTranslationType;
  
      /* Update DTC CountHighByte */
      pMsgContext->resData[3U] = LunDcmWord16.ddByte.ucMsByte;
  
      /* Update DTC CountLowByte */
      pMsgContext->resData[4U] =  LunDcmWord16.ddByte.ucLsByte;
  
      /* Update the global variable to indicate that no NRC has occurred */
      Dcm_GddNegRespError = DCM_POS_RESP;
    }
    else if(LddNumFilteredDTCType == DEM_PENDING)
    {
      /* @Trace: Dcm_SUD_API_50214 */
      /* Set the Flag for returning of DCM_E_PENDING */
      Dcm_PrtclTxBufStatus.ucNumFilterDTCStatus = DCM_TRUE;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_50215 */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspRptFailedConfirmedDTCInfo                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for service Read DTC          **
**                        information (service 0x19) to read the DTCs and the **
**                        associated status information for the first test    **
**                        failed, first test confirmed, most recent test      **
**                        failed, most recent confirmed DTCs. It will be      **
**                        invoked for sub-function values 0x0B, 0x0C, 0x0D    **
**                        and 0x0E                                            **
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
**                        Dcm_GucReadGlobal, Dcm_GddNegRespError, Dcm_GunDTC  **
**                                                                            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_FAILEDCONFIRMEDDTCINFO == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptFailedConfirmedDTCInfo(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType LddReturnValue;

  /* Initialize the array with request type for Dem_GetDTCByOccurrenceTime */
  Dem_DTCRequestType LaaDTCType[DCM_FOUR] = 
  {
    DEM_FIRST_FAILED_DTC,
    DEM_FIRST_DET_CONFIRMED_DTC,
    DEM_MOST_RECENT_FAILED_DTC,
    DEM_MOST_REC_DET_CONFIRMED_DTC
  };

  uint8 LucDTCReqTypeIndex;
  uint8 LucDTCStatus = (uint8)DCM_ZERO;
  uint8 LucDTCStatusMask = (uint8)DCM_ZERO;

  Dcm_GucReadGlobal = DCM_TRUE;

  if ((pMsgContext == NULL_PTR) || 
      (pMsgContext->resData == NULL_PTR) ||
      (pMsgContext->reqData == NULL_PTR))
  {
    /* @Trace: Dcm_SUD_API_50216 */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* Check whether the DTC status mask was successful */
    if (E_OK == IDem_GetDTCStatusAvailabilityMask(&LucDTCStatusMask))
    {
      LucDTCReqTypeIndex = Dcm_GucSubFunction - DCM_UDS_READ_DTC_INFO_0B;

      /* @Trace: SWS_Dcm_00466 */
      LddReturnValue = IDem_GetDTCByOccurrenceTime(
        LaaDTCType[LucDTCReqTypeIndex], &Dcm_GunDTC.ulLongReg32);

      CHK_RET_VAL(LddReturnValue == E_OK, LddReturnValue, IDem_SelectDTC( \
        Dcm_GunDTC.ulLongReg32, DEM_DTC_FORMAT_UDS, DEM_DTC_ORIGIN_PRIMARY_MEMORY));

      /* @Trace: SWS_Dcm_00393 */
      CHK_RET_VAL(LddReturnValue == E_OK, LddReturnValue, IDem_GetStatusOfDTC( \
        &LucDTCStatus));

      /* @Trace: SWS_Dcm_00392 */
      if (LddReturnValue == E_OK)
      {
        /* @Trace: Dcm_SUD_API_50217 */
        /* Update the response data length to the pMsgContext */
        pMsgContext->resDataLen = DCM_SIX;

        /* update sub-function number */
        pMsgContext->resData[DCM_ZERO] = Dcm_GucSubFunction;

        /* DTCStatusAvailabilityMask */
        pMsgContext->resData[DCM_ONE] = LucDTCStatusMask;

        /* DTCHighByte */
        pMsgContext->resData[DCM_TWO] = Dcm_GunDTC.ddByte.ucMidHiByte;

        /* DTCMiddleByte */
        pMsgContext->resData[DCM_THREE] = Dcm_GunDTC.ddByte.ucMidLowByte;

        /* DTCLowByte */
        pMsgContext->resData[DCM_FOUR] = Dcm_GunDTC.ddByte.ucLsByte;

        /* DTCStatusMask */
        pMsgContext->resData[DCM_FIVE] = LucDTCStatus;
        
        /* Update the global variable indicating no NRC is reported */
        Dcm_GddNegRespError = DCM_POS_RESP;
      }
      /* @Trace: SWS_Dcm_01409 SWS_Dcm_00766 */
      else if (LddReturnValue == DEM_NO_SUCH_ELEMENT)
      {
        /* @Trace: Dcm_SUD_API_50218 */
        pMsgContext->resDataLen = DCM_TWO;
        pMsgContext->resData[DCM_ZERO] = Dcm_GucSubFunction;
        pMsgContext->resData[DCM_ONE] = LucDTCStatusMask;
      }
      else
      {
        /* @Trace: SWS_Dcm_01250 */
        /* @Trace: Dcm_SUD_API_50219 */
        Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
      }
    }
    else
    {
      /* @Trace: Dcm_SUD_API_50220 */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
  
  /* Send response from main function */
  Dcm_GblSendResponse = DCM_TRUE;
}
#endif /* (DCM_RPT_FAILEDCONFIRMEDDTCINFO == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DspRptDTCSnapshotRecByRecordNum                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used for service Read DTC          **
**                        information (service 0x19) to read the snapshot     **
**                        records and extended records for a particular DTC   **
**                        or a particular record. This service will be        **
**                        invoked for sub-function value 0x05                 **
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
**                        Dcm_GpReqResData, Dcm_GucReadGlobal,                **
**                        Dcm_GddNegRespError, Dcm_GunDTC                     **
**                                                                            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#if (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON)
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
/* polyspace +1 MISRA-C:8.3 [Justified:Low] Justify with annotations */
FUNC(void, DCM_CODE) Dcm_DspRptDTCSnapshotRecByRecordNum(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpPreBuffer;
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) LpIDBuffer;
  P2CONST(Dcm_DspPidData, AUTOMATIC, DCM_APPL_CONST) LpDcmDspPidData;

  uint16 LusMoveOffSet;
  uint16 LusBufferSize;
  uint16 LusMaxBufferSize;

  uint8 LusTableInx;
  uint8 LucRecordNumber;
  uint8 LddDTCStatus;
  uint8 LucDIDIndex;
  uint8 LucNumofData;
  uint8 LucCount;
  Std_ReturnType LddRetVal;

  Dcm_GucReadGlobal = DCM_TRUE;

  if ((pMsgContext == NULL_PTR) || 
      (pMsgContext->resData == NULL_PTR) ||
      (pMsgContext->reqData == NULL_PTR) ||
      (Dcm_GpReqResData == NULL_PTR))
  {
    /* @Trace: Dcm_SUD_API_50221 */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    Dcm_GddNegRespError = DCM_POS_RESP;

    /* Get the record number from the request message */
    LucRecordNumber = pMsgContext->reqData[DCM_ONE]; 

    /* Check If Requested Record Number Other than 0x00 */
    if(LucRecordNumber == DCM_ZERO)
    {
      /* @Trace: Dcm_SUD_API_50222 */
      /* Update DTC status availabilityMask */
      Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
      Dcm_GpReqResData = &Dcm_GpReqResData[DCM_ONE];

      /* Update respond data length */
      Dcm_GstMsgContext.resDataLen = DCM_ONE;
      LusMaxBufferSize = (uint16)(pMsgContext->resMaxDataLen - DCM_ONE);

      #if (0 < DCM_TOTAL_NUM_OF_PIDS)
      LucDIDIndex = DCM_ZERO;
      LpIDBuffer = Dcm_GpOBDBaseAddress[DCM_GET_PID];

      while ((LucDIDIndex < DCM_TOTAL_NUM_OF_PIDS) && (LusMaxBufferSize > DCM_FIVE))
      {
        (void) Dcm_GetIDIndex(DCM_GET_PID, LpIDBuffer[LucDIDIndex], &LusTableInx);

        LddRetVal = IDem_DcmGetDTCOfOBDFreezeFrame(
          DCM_ZERO, &Dcm_GunDTC.ulLongReg32, DEM_DTC_FORMAT_UDS);

        CHK_RET_VAL(E_OK == LddRetVal, LddRetVal, IDem_SelectDTC( \
          Dcm_GunDTC.ulLongReg32, DEM_DTC_FORMAT_UDS, DEM_DTC_ORIGIN_PRIMARY_MEMORY));

        CHK_RET_VAL(E_OK == LddRetVal, LddRetVal, IDem_GetStatusOfDTC( \
          &LddDTCStatus));

        if (E_OK == LddRetVal)
        {
          /* @Trace: SWS_Dcm_00574 */
          /* @Trace: Dcm_SUD_API_50223 */
          /* Update DTCStoredDataRecordNumber from request */
          Dcm_GpReqResData[DCM_ZERO] = LucRecordNumber;

          /* @Trace: SWS_Dcm_01193 */
          /* Update DTCAndStatusRecord */
          Dcm_GpReqResData[DCM_ONE] = Dcm_GunDTC.ddByte.ucMidHiByte;
          Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucMidLowByte;
          Dcm_GpReqResData[DCM_THREE] = Dcm_GunDTC.ddByte.ucLsByte;

          /* @Trace: SWS_Dcm_00389 */
          /* Update Status of DTC */
          Dcm_GpReqResData[DCM_FOUR] = LddDTCStatus;

          Dcm_GpReqResData = &Dcm_GpReqResData[DCM_FIVE];

          /* Update respond data length */
          Dcm_GstMsgContext.resDataLen += DCM_FIVE;
          LusMaxBufferSize -= DCM_FIVE;

          /* Check if service $02 OBD was supported yet */
          if((Dcm_GaaPIDConfig[LusTableInx].ucPidService == DCM_SERVICE_02) ||
             (Dcm_GaaPIDConfig[LusTableInx].ucPidService == DCM_SERVICE_01_02))
          {
            /* @Trace: Dcm_SUD_API_50224 */
            /* Get the Number of PID Data Configured */
            LucNumofData = Dcm_GaaPIDConfig[LusTableInx].ucNumofPIDData;

            /* Get the PID Buffer Size */
            LusBufferSize = Dcm_GaaPIDConfig[LusTableInx].ucPidBufferSize;

            /* Get the DcmDspPidData */
            LpDcmDspPidData = Dcm_GaaPIDConfig[LusTableInx].pDcmDspPidData;

            /* Reset the offset value */
            LusMoveOffSet = DCM_ZERO;

            /* Keep the pointer to initial position */
            LpPreBuffer = Dcm_GpReqResData;

            for(LucCount = DCM_ZERO; LucCount < LucNumofData; LucCount++)
            {
              /* @Trace: SWS_Dcm_00388 */
              LddRetVal = IDem_DcmReadDataOfOBDFreezeFrame(
                LpIDBuffer[LucDIDIndex],
                LpDcmDspPidData->ucPIDDataElementIndex,
                Dcm_GpReqResData, &LusBufferSize);
              
              if((E_OK == LddRetVal) && (LusMaxBufferSize >= LusBufferSize))
              {
                /* @Trace: Dcm_SUD_API_50225 */
                LpDcmDspPidData = &LpDcmDspPidData[DCM_ONE];
                Dcm_GpReqResData = &Dcm_GpReqResData[LusBufferSize];

                /* Update respond data length */
                Dcm_GstMsgContext.resDataLen += LusBufferSize;
                LusMaxBufferSize -= LusBufferSize;
                LusMoveOffSet += LusBufferSize;
              }
              else
              {
                /* @Trace: Dcm_SUD_API_50226 */
                /* Reset pointer to initial position before reading PID value */
                Dcm_GpReqResData = LpPreBuffer;
                
                /* Update respond data length */
                Dcm_GstMsgContext.resDataLen -= LusBufferSize;
                LusMaxBufferSize += LusMoveOffSet;
                break;
              }
            }
          }
        }
        else if(DEM_NO_SUCH_ELEMENT == LddRetVal)
        {
          /* @Trace: SWS_Dcm_01409 */
          /* @Trace: Dcm_SUD_API_50227 */
          Dcm_GpReqResData[DCM_ZERO] = LucRecordNumber;
          Dcm_GstMsgContext.resDataLen = DCM_TWO;
          break;
        }
        else
        {
          /* @Trace: SWS_Dcm_01250 */
          /* @Trace: Dcm_SUD_API_50228 */
          /* polyspace +2 MISRA2012:15.4 [Justified:Low] Justify with annotations */
          Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
          break;
        }

        LucDIDIndex++;
      }
      #else
      /* Response NRC in case number of PIDs not correct */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;

      DCM_UNUSED(LusMaxBufferSize);
      DCM_UNUSED(LddDTCStatus);
      DCM_UNUSED(LucDIDIndex);
      DCM_UNUSED(LpIDBuffer);
      DCM_UNUSED(LusTableInx);
      DCM_UNUSED(LpDcmDspPidData);
      DCM_UNUSED(LucNumofData);
      DCM_UNUSED(LusBufferSize);
      DCM_UNUSED(LucCount);
      DCM_UNUSED(LusMoveOffSet);
      DCM_UNUSED(LpPreBuffer);
      DCM_UNUSED(LddRetVal);
      #endif
    }
    else
    {
      /* @Trace: SWS_Dcm_00632 */
      /* @Trace: Dcm_SUD_API_50229 */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
  }

  /* Send response from main function */
  Dcm_GblSendResponse = DCM_TRUE;
}
#endif /* (DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON) */

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
