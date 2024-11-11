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
**  SRC-MODULE: Dcm_DspReadSSDTCInfo.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the implementation of the Read DTC         **
**              subfunctions  0x03, 0x04, 0x06, 0x10, 0x18, 0x19              **
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
** 0.0.2     05-May-2019   LamNV10        Change mechanism call DEM API for   **
**                                        0x19 service 0x04 0x06 0x18 0x19 sub**
** 0.0.3     16-Aug-2020   HueKM          Fix defect and coding rules         **
** 0.0.4     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.5     17-Nov-2020   HueKM          Changes made as per #17035          **
** 0.0.6     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.7     21-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
** 1.3.0     31-Dcm-2023   EK Kim         Refer #CP44-1515                    **
** 1.4.0     29-Mar-2024   EK Kim         Refer #CP44-4473                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_DspReadSSDTCInfo.h"
#include "Dcm_DspMain.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DspNonPagedDTCSubFct.h"
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

#if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
    (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
static FUNC(void, DCM_CODE) Dcm_DspGetSizeOfData(
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) LpRespLenOfData);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_DspRptDTCSnapshotRecByDTCNum                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is sub-function of the service Read DTC        **
**                        information (service 0x19) to read the snapshot     **
**                        records and extended records for a particular DTC   **
**                        or a particular record. This service will be        **
**                        invoked for sub-function values 0x04, 0x06          **
**                        and 0x10, 0x18, 0x19                                **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
#if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
    (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
FUNC(void, DCM_CODE) Dcm_DspRptDTCSnapshotRecByDTCNum(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;

  uint8 LucRecordNumber;
  Std_ReturnType LddRetVal;

  Dcm_GddNegRespError = DCM_POS_RESP;
  Dcm_GucReadGlobal = DCM_TRUE;

  if ((pMsgContext == NULL_PTR) || 
      (pMsgContext->resData == NULL_PTR) ||
      (pMsgContext->reqData == NULL_PTR))
  {
    /* @Trace: Dcm_SUD_API_50300 */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_50303 */
    /* Update the record number from the request buffer */
    LpReqResData = pMsgContext->reqData;
    LucRecordNumber = LpReqResData[DCM_FOUR];

    /* Get the DTC for the input request */
    /* Update the DTC info to LddDTC from the request from the 3rd position */
    Dcm_GunDTC.ddByte.ucLsByte      = LpReqResData[DCM_THREE];
    Dcm_GunDTC.ddByte.ucMidLowByte  = LpReqResData[DCM_TWO];
    Dcm_GunDTC.ddByte.ucMidHiByte   = LpReqResData[DCM_ONE];
    Dcm_GunDTC.ddByte.ucMsByte      = DCM_ZERO;

    /* Update MemorySelection */
    if ((DCM_UDS_READ_DTC_INFO_18 == Dcm_GucSubFunction) ||
        (DCM_UDS_READ_DTC_INFO_19 == Dcm_GucSubFunction))
    {
      /* @Trace: Dcm_SUD_API_50301 */
      Dcm_GucMemorySelection = LpReqResData[DCM_FIVE];
    }

    /* Initialize the global pointer to the response data buffer */
    Dcm_GpReqResData = pMsgContext->resData;

    /* Assemble the initial response message */
    LddRetVal = Dcm_DspUpdateBasicsOfEventData(pMsgContext);

    if ((DCM_POS_RESP == Dcm_GddNegRespError) && (E_OK == LddRetVal))
    {
      /* @Trace: Dcm_SUD_API_50302 */
      /* @Trace: SWS_Dcm_00302 SWS_Dcm_00384 SWS_Dcm_01430 */
      /* @Trace: SWS_Dcm_00386 SWS_Dcm_00441 SWS_Dcm_01224 */
      (void) Dcm_DspProcessSubFFDataOrExtData(LucRecordNumber, pMsgContext);
    }
  }

  #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  if (Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
  #endif
  {
    /* @Trace: Dcm_SUD_API_50304 */
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspGetSizeOfData                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function to calculate the size  **
**                        of a Freeze frame or extended data for a single     **
**                        or multiple records                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpRespLenOfData                                     **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
    (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
static FUNC(void, DCM_CODE) Dcm_DspGetSizeOfData(
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) LpRespLenOfData)
{
  uint16 LusSizeOfData;
  Std_ReturnType LddRetVal;

  LddRetVal = E_OK;
  LusSizeOfData = DCM_ZERO;
  Dcm_GddNegRespError = DCM_POS_RESP;

  switch (Dcm_GucSubFunction)
  {
    case DCM_UDS_READ_DTC_INFO_06:
    case DCM_UDS_READ_DTC_INFO_10:
    case DCM_UDS_READ_DTC_INFO_19:
      #if (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON)
      /* @Trace: SRS_Diag_04127 */
      /* @Trace: Dcm_SUD_API_50305 */
      LddRetVal = IDem_GetSizeOfExtendedDataRecordSelection(&LusSizeOfData);
      #endif
      break;

    case DCM_UDS_READ_DTC_INFO_04:
    case DCM_UDS_READ_DTC_INFO_18:
      #if (DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON)
      /* @Trace: Dcm_SUD_API_50306 */
      LddRetVal = IDem_GetSizeOfFreezeFrameSelection(&LusSizeOfData);
      #endif
      break;

    default:
      /* No action in this case */
      break;
  }

  if (E_OK == LddRetVal)
  {
    /* Update the complete freeze frame size for the output parameter */
    if ((DCM_UDS_READ_DTC_INFO_18 == Dcm_GucSubFunction) || 
        (DCM_UDS_READ_DTC_INFO_19 == Dcm_GucSubFunction))
    {
      /* @Trace: Dcm_SUD_API_50307 */
      *LpRespLenOfData = (uint32) (DCM_SIX + (uint32) LusSizeOfData);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_50308 */
      *LpRespLenOfData = (uint32) (DCM_FIVE + (uint32) LusSizeOfData);
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_50309 */
    /* @Trace: SWS_Dcm_01246 SWS_Dcm_01242 */
    /* Include return DEM_WRONG_DTC, DEM_WRONG_DTCORIGIN, DEM_NO_SUCH_ELEMENT */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspProcessSubFFDataOrExtData                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function to assemble the        **
**                        response of Freeze frame data for a particular DTC  **
**                        or a snap shot number.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucRecordNumber, pMsgContext                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
    (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
FUNC(uint32, DCM_CODE) Dcm_DspProcessSubFFDataOrExtData(
  uint8 LucRecordNumber, 
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType LucReturnRes;

  uint16 LusRespBufferSize;
  uint32 LulRemBufSize = DCM_ZERO;
  uint32 LulRespLenOfData = DCM_ZERO;

  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pSelectDataFunc)(
    uint8 RecordNumber);
  pSelectDataFunc = NULL_PTR;

  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pGetNextDataFunc)(
    uint8* DestBuffer, uint16* BufSize);
  pGetNextDataFunc = NULL_PTR;

  /* Category sub function fype for call back function */
  if ((DCM_UDS_READ_DTC_INFO_04 == Dcm_GucSubFunction) ||
      (DCM_UDS_READ_DTC_INFO_18 == Dcm_GucSubFunction))
  {
    /* @Trace: Dcm_SUD_API_50310 */
    #if (DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON)
    pSelectDataFunc = IDem_SelectFreezeFrameData;
    pGetNextDataFunc = IDem_GetNextFreezeFrameData;
    #endif
  }
  else
  {
    /* @Trace: Dcm_SUD_API_50311 */
    #if (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON)
    pSelectDataFunc = IDem_SelectExtendedDataRecord;
    pGetNextDataFunc = IDem_GetNextExtendedDataRecord;
    #endif
  }

  /* Initialize variables */
  Dcm_GddNegRespError = DCM_POS_RESP;

  /* Check if the paged buffer is enabled */
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  Dcm_GucRecordNumber = LucRecordNumber;

  if(Dcm_DspSerPgStatus.ucFirstPage == DCM_TRUE)
  {
    /* @Trace: Dcm_SUD_API_50312 */
    /* Check whether the global bit flag to indicate that
     * it is other than the first page which is to be processed */
  }
  else
  #endif
  {
    /* @Trace: SWS_Dcm_00371 */
    /* Disable data record update */
    if (E_OK != IDem_DisableDTCRecordUpdate(&Dcm_GddNegRespError))
    {
      /* @Trace: Dcm_SUD_API_50313 */
      /* Update the global variable with the NRC value */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
    /* Disable data record update is successfully */
    else
    {
      /* @Trace: Dcm_SUD_API_50314 */
      /* Set bit flag indicating DTC record update is successfully disabled */
      Dcm_DspSerPgStatus.ucDemDisableInvoked = DCM_TRUE;

      if (E_OK != pSelectDataFunc(LucRecordNumber))
      {
        /* @Trace: Dcm_SUD_API_50315 */
        Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
      }
    }
  }

  if (Dcm_GddNegRespError == DCM_POS_RESP)
  {
    /* @Trace: Dcm_SUD_API_50316 */
    /* Calculate the size of a Freeze frame for a single or multiple records */
    Dcm_DspGetSizeOfData(&LulRespLenOfData);
  }

  /* Check whether any NRC is updated */
  if (Dcm_GddNegRespError == DCM_POS_RESP)
  {
    /* Update total response length to the pMsgContext */
    pMsgContext->resDataLen = LulRespLenOfData;

    if (LulRespLenOfData <= (pMsgContext->resMaxDataLen))
    {
      /* @Trace: Dcm_SUD_API_50317 */
      /* Descrease by 5 bytes = [Sub + 3xDTC + SODTC]  */
      LulRespLenOfData -= DCM_FIVE;

      /* Descrease by 1 byte for MEMYS */
      if ((DCM_UDS_READ_DTC_INFO_18 == Dcm_GucSubFunction) ||
          (DCM_UDS_READ_DTC_INFO_19 == Dcm_GucSubFunction))
      {
        /* @Trace: Dcm_SUD_API_50318 */
        LulRespLenOfData -= DCM_ONE;
      }

      LulRemBufSize = LulRespLenOfData;
      LucReturnRes = E_OK;

      /* Check till all the record numbers are read and no NRC is reported */
      while ((DCM_POS_RESP == Dcm_GddNegRespError) && 
             (DCM_ZERO != LulRemBufSize) && (E_OK == LucReturnRes))
      {
        /* If the remaining buffer size is greater than the maximum
         * Freezeframe Data size for any DataId then update it with 256 */
        LusRespBufferSize = (LulRemBufSize > DCM_MAX_RECDDATA_SIZE) ? \
                            DCM_MAX_RECDDATA_SIZE : (uint16) LulRemBufSize;

        /* @Trace: SWS_Dcm_00382 SWS_Dcm_00841 */
        LucReturnRes = pGetNextDataFunc(Dcm_GpReqResData, &LusRespBufferSize);

        switch (LucReturnRes)
        {
          /* Check whether FreezeFrame data is successfully returned */
          case E_OK:
            /* @Trace: Dcm_SUD_API_50319 */
            /* Update remaining buffer size */
            LulRemBufSize -= (uint32) LusRespBufferSize;

            /* Increment the pointer by BufSize bytes */
            Dcm_GpReqResData = &Dcm_GpReqResData[LusRespBufferSize];

            if (DCM_ZERO == LusRespBufferSize)
            {
              /* @Trace: Dcm_SUD_API_50320 */
              LucReturnRes = DEM_NO_SUCH_ELEMENT;
            }
            break;

          /* Check provided buffer size is too small */
          case DEM_BUFFER_TOO_SMALL:
            /* @Trace: Dcm_SUD_API_50321 */
            Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
            break;

          /* @Trace: SWS_Dcm_01220 */
          case DEM_WRONG_DTC:
          case DEM_WRONG_DTCORIGIN:
            /* @Trace: Dcm_SUD_API_50322 */
            Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
            break;

          case DEM_NO_SUCH_ELEMENT:
            /* @Trace: Dcm_SUD_API_50323 */
            /* This is normal resp so no update error */
            break;

          default:
            /* @Trace: Dcm_SUD_API_50324 */
            /* This is to process for other error code */
            Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
            break;
        }
      }
    }
    else
    {
      #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
      uint32 maxResLen = Dcm_PagedBuffer_GetMaxRespLen(pMsgContext);

      if (LulRespLenOfData <= maxResLen)
      {
        /* @Trace: Dcm_SUD_API_50325 */
        /* Start the paged processing */
        Dcm_DsdStartPagedProcessing(pMsgContext);
      }
      else
      #endif
      {
        /* @Trace: Dcm_SUD_API_50326 */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
      }
    }
  }

  #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
   /* Check if it is the first page is updated */
  if ((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE) &&
      (Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE))
  {
    /* @Trace: Dcm_SUD_API_50327 */
    Dcm_DspSerPgStatus.ucFirstPage = DCM_TRUE;
  }
  #endif

  if ((Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE) &&
      (Dcm_DspSerPgStatus.ucDemDisableInvoked == DCM_TRUE))
  {
    /* @Trace: Dcm_SUD_API_50328 */
    (void) IDem_EnableDTCRecordUpdate();

    /* Clear the bit flag indicating DTC record update is enabled */
    Dcm_DspSerPgStatus.ucDemDisableInvoked = DCM_FALSE;
  }

  /* Return the remaining size of the buffer */
  return (LulRespLenOfData - LulRemBufSize);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspUpdateBasicsOfEventData                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function to assemble the        **
**                        initial response message for sub functions 0x04,    **
**                        0x06 and 0x10, 0x18, 0x19                           **
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
#if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
      (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspUpdateBasicsOfEventData(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dem_DTCOriginType LddDTCOrigin;
  Dem_DTCFormatType LucDTCFormat = DEM_DTC_FORMAT_UDS;

  uint8 LddDTCStatus = DCM_ZERO;
  Std_ReturnType LddReturnRes = E_NOT_OK;

  /* @Trace: Dcm_SUD_API_50329 */
  /* Assign error variable to default NRC value */
  Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;

  if (Dcm_GpReqResData != NULL_PTR)
  {
    switch (Dcm_GucSubFunction)
    {
      case DCM_UDS_READ_DTC_INFO_06:
      case DCM_UDS_READ_DTC_INFO_04:
        /* @Trace: SWS_Dcm_00383 */
        /* @Trace: Dcm_SUD_API_50330 */
        LddDTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
        #if ( (DCM_J1979_2_SUPPORT == STD_ON) \
            && (DCM_OBD_UDS_DTC_SEPARATION_SUPPORT == STD_ON) )
        LucDTCFormat = DEM_DTC_FORMAT_OBD_3BYTE;
        #endif
        
        break;

      case DCM_UDS_READ_DTC_INFO_10:
        /* @Trace: Dcm_SUD_API_50331 */
        LddDTCOrigin = DEM_DTC_ORIGIN_MIRROR_MEMORY;
        break;

      case DCM_UDS_READ_DTC_INFO_19:
      case DCM_UDS_READ_DTC_INFO_18:
        /* @Trace: SWS_Dcm_01147 */
        /* @Trace: Dcm_SUD_API_50332 */
        /* MemorySelection from request + 0x0100 */
        LddDTCOrigin = Dcm_GucMemorySelection | DCM_USER_DEFINED_FAULT_MEMORY;
        break;

      default:
        /* @Trace: Dcm_SUD_API_50333 */
        /* Invalid DTCOrigin in this case */
        LddDTCOrigin = DCM_ZERO;
        break;
    }

    /* @Trace: SWS_Dcm_00295 */
    LddReturnRes = IDem_SelectDTC(
      Dcm_GunDTC.ulLongReg32, LucDTCFormat, LddDTCOrigin);

    CHK_RET_VAL(LddReturnRes == E_OK, LddReturnRes, IDem_GetStatusOfDTC(&LddDTCStatus));

    /* Check whether status of DTC was OK */
    if(LddReturnRes == E_OK)
    {
      /*  Sub-function number */
      Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;

      if ((DCM_UDS_READ_DTC_INFO_18 == Dcm_GucSubFunction) ||
          (DCM_UDS_READ_DTC_INFO_19 == Dcm_GucSubFunction))
      {
        /* @Trace: Dcm_SUD_API_50334 */
        /* Update MemorySelection */
        Dcm_GpReqResData[DCM_ONE] = Dcm_GucMemorySelection;

        /* DTC High Byte */
        Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucMidHiByte;

        /* DTC Middle Byte */
        Dcm_GpReqResData[DCM_THREE] = Dcm_GunDTC.ddByte.ucMidLowByte;

        /* DTC Low Byte */
        Dcm_GpReqResData[DCM_FOUR] = Dcm_GunDTC.ddByte.ucLsByte;

        /* DTC Status Mask */
        Dcm_GpReqResData[DCM_FIVE] = LddDTCStatus;

        /* Re Initialize the response buffer pointer */
        Dcm_GpReqResData = &Dcm_GpReqResData[DCM_SIX];
      }
      else
      {
        /* @Trace: Dcm_SUD_API_50335 */
        /* DTC High Byte */
        Dcm_GpReqResData[DCM_ONE] = Dcm_GunDTC.ddByte.ucMidHiByte;

        /* DTC Middle Byte */
        Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucMidLowByte;

        /* DTC Low Byte */
        Dcm_GpReqResData[DCM_THREE] = Dcm_GunDTC.ddByte.ucLsByte;

        /* DTC Status Mask */
        Dcm_GpReqResData[DCM_FOUR] = LddDTCStatus;

        /* Re Initialize the response buffer pointer */
        Dcm_GpReqResData = &Dcm_GpReqResData[DCM_FIVE];
      }
      
      /* Update the global variable, indicating no NRC as occurred */
      Dcm_GddNegRespError = DCM_POS_RESP;
    }
    /* @Trace: SWS_Dcm_01409*/
    else if (LddReturnRes == DEM_NO_SUCH_ELEMENT)
    {
      Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;
      Dcm_GddNegRespError = DCM_POS_RESP;

      if ((DCM_UDS_READ_DTC_INFO_18 == Dcm_GucSubFunction) ||
          (DCM_UDS_READ_DTC_INFO_19 == Dcm_GucSubFunction))
      {
        /* @Trace: Dcm_SUD_API_50336 */
        Dcm_GpReqResData[DCM_ONE] = Dcm_GucMemorySelection;
        Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucMidHiByte;
        Dcm_GpReqResData[DCM_THREE] = Dcm_GunDTC.ddByte.ucMidLowByte;
        Dcm_GpReqResData[DCM_FOUR] = Dcm_GunDTC.ddByte.ucLsByte;

        pMsgContext->resDataLen = DCM_FIVE;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_50337 */
        Dcm_GpReqResData[DCM_ONE] = Dcm_GunDTC.ddByte.ucMidHiByte;
        Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucMidLowByte;
        Dcm_GpReqResData[DCM_THREE] = Dcm_GunDTC.ddByte.ucLsByte;

        pMsgContext->resDataLen = DCM_FOUR;
      }
    }
    else if((LddReturnRes == DEM_WRONG_DTC) || (LddReturnRes == DEM_WRONG_DTCORIGIN))
    {
      /* @Trace: Dcm_SUD_API_50338 */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_50339 */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }

  return LddReturnRes;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspRptDTCSnapshotRecIdentfn                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the function used for the service Read DTC  **
**                        information (service 0x19) to read all the SnapShot **
**                        record numbers and its associated DTCs.It will be   **
**                        invoked for sub-function value 0x03                 **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspRptDTCSnapshotRecIdentfn(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  uint32 LulResleng;
  uint16 LusNumberOfFilteredRecords;
  Std_ReturnType LddRetVal;

  Dcm_GucReadGlobal = DCM_TRUE;
  LusNumberOfFilteredRecords = DCM_ZERO;

  if ((pMsgContext == NULL_PTR) || 
      (pMsgContext->resData == NULL_PTR) ||
      (pMsgContext->reqData == NULL_PTR) ||
      (Dcm_GpReqResData == NULL_PTR))
  {
    /* @Trace: Dcm_SUD_API_50340 */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_50341 */
    /* @Trace: SWS_Dcm_00298 SWS_Dcm_00836 */
    LddRetVal = IDem_SetFreezeFrameRecordFilter(DEM_DTC_FORMAT_UDS);

    if (E_OK == LddRetVal)
    {
      /* @Trace: Dcm_SUD_API_50342 */
      LddRetVal = IDem_GetNumberOfFreezeFrameRecords(&LusNumberOfFilteredRecords);
    }

    if (E_OK == LddRetVal)
    {
      if (DCM_ZERO == LusNumberOfFilteredRecords)
      {
        /* @Trace: Dcm_SUD_API_50343 */
        /* Update the sub function in the response buffer */
        Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;

        /* Update the response length */
        pMsgContext->resDataLen = DCM_ONE;

        /* Update the NRC value */
        Dcm_GddNegRespError = DCM_POS_RESP;
      }
      else
      {
        /* 3bytes[DTC] + 1byte[RecNum] = 4Bytes on per DTC + 1byte[SubService] */
        LulResleng = (uint32) ((uint32) LusNumberOfFilteredRecords * DCM_FOUR) + DCM_ONE;

        /* Update the complete response length that is to be transmitted */
        Dcm_GstMsgContext.resDataLen = LulResleng;

        /* Check if the response buffer is 
         * capable of accommodating the complete response at once */
        if(LulResleng <= (Dcm_GstMsgContext.resMaxDataLen))
        {
          /* @Trace: Dcm_SUD_API_50344 */
          /* Update the sub function */
          Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;

          /* Reset the pointer to the response data buffer */
          Dcm_GpReqResData = &Dcm_GpReqResData[DCM_ONE];

          /* Pass the buffer size with one value less since
           * sub function is already updated */
          LulResleng = LulResleng - DCM_ONE;

          (void)Dcm_DspRepDTCSnapRecID(LulResleng);
        }
        else
        {
          /* @Trace: Dcm_SUD_API_50345 */
          #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
          /* Set the global bit flag for paging started to TRUE */
          Dcm_DspSerPgStatus.ucPagingStarted = DCM_TRUE;

          /* Start the paged processing */
          Dcm_DsdStartPagedProcessing(&Dcm_GstMsgContext);

          #else
          /* Update the NRC if the response length is greater than the
           * response buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled */
          Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
          #endif
        }
      }
    }
    else
    {
      /* @Trace: SWS_Dcm_01256 */
      /* @Trace: Dcm_SUD_API_50346 */
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    }
  }
  
  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
  #endif
  {
    /* @Trace: Dcm_SUD_API_50347 */
    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspRepDTCSnapRecID                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is internal function for sub-functions 0x03    **
**                        used to list the SnapShot Record Number and the     **
**                        associated DTCs                                     **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if(DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON)
FUNC(uint32, DCM_CODE) Dcm_DspRepDTCSnapRecID(uint32 LulBufferSize)
{
  uint32 LulRespBufferSize;

  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint32 LulRemainingLength;
  uint8 LucCount;
  #endif

  Std_ReturnType LucReturnRes;
  uint8 LucSnapShotrecord = DCM_ZERO;

  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
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
      /* @Trace: Dcm_SUD_API_50349 */
      /* Reset the global bit flag to indicate that it is other than the first
       * page which is to be processed */
      Dcm_DspSerPgStatus.ucFirstPage = DCM_TRUE;
    }

    /* @Trace: Dcm_SUD_API_50348 */
    LulRemainingLength = Dcm_GddCurrentLength;
  }
  #endif

  /* @Trace: Dcm_SUD_API_50350 */
  /* Initialize with the configured buffer size */
  LulRespBufferSize = LulBufferSize;

  /* Initialize the global variable to indicate that no NRC as occurred */
  Dcm_GddNegRespError = DCM_POS_RESP;

  /* Initialize default return value to E_OK */
  LucReturnRes = E_OK;

  while((LulRespBufferSize > DCM_THREE) &&
    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    (((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE) &&
    (LulRemainingLength >= DCM_FOUR)) ||
    ((Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE))) &&
    #endif
    (LucReturnRes == E_OK))
  {
    /* @Trace: SWS_Dcm_00299 */
    LucReturnRes = IDem_GetNextFilteredRecord(
      &Dcm_GunDTC.ulLongReg32, &LucSnapShotrecord);

    /* @Trace: SWS_Dcm_00300 */
    if(LucReturnRes == E_OK)
    {
      /* @Trace: Dcm_SUD_API_50351 */
      /* DTC Hight Byte */
      Dcm_GpReqResData[DCM_ZERO] = Dcm_GunDTC.ddByte.ucMidHiByte;
	
      /* DTC Middle Byte */
      Dcm_GpReqResData[DCM_ONE] = Dcm_GunDTC.ddByte.ucMidLowByte;
	
      /* DTC Low Byte */
      Dcm_GpReqResData[DCM_TWO] = Dcm_GunDTC.ddByte.ucLsByte;
	
      /* DTC Status Mask */
      Dcm_GpReqResData[DCM_THREE] = LucSnapShotrecord;

      Dcm_GpReqResData = &Dcm_GpReqResData[DCM_FOUR];
	
      /* Update the response buffer size */
      LulRespBufferSize = LulRespBufferSize - DCM_FOUR;

      /* Update the Temporary length of response buffer */
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
      {
        /* @Trace: Dcm_SUD_API_50352 */
        LulRemainingLength = LulRemainingLength - DCM_FOUR;
      }
      #endif
    }
    /* @Trace: SWS_Dcm_01237 */
    else if(LucReturnRes == DEM_NO_SUCH_ELEMENT)
    {
      /* @Trace: Dcm_SUD_API_50353 */
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
      {
        /* @Trace: Dcm_SUD_API_50354 */
        Dcm_GstMsgContext.resDataLen =
          Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
      }
      #else
      /* Decrease the response length by 4 bytes */
      Dcm_GstMsgContext.resDataLen =
        Dcm_GstMsgContext.resDataLen - LulRespBufferSize;
      #endif
    }
    else
    {
      /* @Trace: Dcm_SUD_API_50355 */
      /* To avoid QAC warning, do nothing in this case */
    }
  }

  if(LucReturnRes == DEM_NO_SUCH_ELEMENT)
  {
    /* @Trace: Dcm_SUD_API_50356 */
    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    if((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)&&
      (LulRemainingLength != DCM_ZERO) && (LulRespBufferSize > DCM_THREE))
    {
      do
      {
        /* @Trace: Dcm_SUD_API_50357 */
        for(LucCount = DCM_ZERO; LucCount < DCM_FOUR; LucCount++)
        {
          *Dcm_GpReqResData = DCM_ZERO;

          Dcm_GpReqResData = &Dcm_GpReqResData[1u];
        }

        LulRespBufferSize = LulRespBufferSize - DCM_FOUR;
        LulRemainingLength  = LulRemainingLength - DCM_FOUR;

      } while((LulRespBufferSize > DCM_THREE) && (LulRemainingLength != DCM_ZERO));
    }
    #endif

    /* @Trace: SWS_Dcm_01238 */
    if (LulRespBufferSize == LulBufferSize)
    {
      /* @Trace: Dcm_SUD_API_50358 */
      /* Update the sub function in the response buffer */
      Dcm_GpReqResData[DCM_ZERO] = Dcm_GucSubFunction;

      /* Update the response length */
      Dcm_GstMsgContext.resDataLen = DCM_ONE;
    }
  }
  
  return(LulBufferSize - LulRespBufferSize);
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
