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
**  SRC-MODULE: Dcm_DspOBDInternals.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions for OBD internal Functions **
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
** 0.0.2     25-Apr-2020   LamNV10        Add pre-compile for Dcm_GetIDIndex()**
** 0.0.3     16-Aug-2020   HueKM          Fix defect and coding rules         **
** 0.0.4     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.5     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.6     18-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
** 1.3.0     31-Dec-2023   DH Kwak        Refer #CP44-1415                    **
** 1.3.0_HF1 13-Jan-2024   SY Kim         Refer #45119                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm.h"
#include "Rte_Dcm.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dem.h"
#include "Dem_Dcm.h"
#endif
#include "Dcm_Ram.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Cfg.h"
#include "Dcm_PackUnPack.h"
#include "Dcm_Config.h"
#include "Dcm_DspOBDInternals.h"

#include "Dcm_Utils.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dcm_DemInterfaces.h"
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#define DCM_START_SEC_CODE
#include "MemMap.h"

#if ((DCM_OBD_GETDTC_03_SERVICE == STD_ON) || \
     (DCM_OBD_GETDTC_07_SERVICE == STD_ON) || \
     (DCM_OBD_GETDTC_0A_SERVICE == STD_ON))
/*******************************************************************************
** Function Name        : Dcm_DemGetNumberOfOBDDTC                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function for the OBDservices   **
**                        (0x03, 0x07, 0x0A) to calculate the number          **
**                        of Filtered DTcs.                                   **
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
**                        Dcm_PrtclTxBufStatus, Dcm_TxRespStatus,             **
**                        Dcm_GpReqResData, Dcm_GddNegRespError,              **
**                        Dcm_GpMsgContext, Dcm_GucNumofDTC,                  **
**                        Dcm_DspSerPgStatus                                  **
**                        Function(s) invoked :None                           **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DemGetNumberOfOBDDTC(void)
{
  Std_ReturnType LddNumFilteredDTCType;
  uint32 LulRespLength;
  uint16 LusNumberOfFilteredDTC;

  Dcm_PrtclTxBufStatus.ucReportOBDDtc = DCM_FALSE;
  Dcm_GddNegRespError = DCM_POS_RESP;

  /* @Trace: SWS_Dcm_01227 SWS_Dcm_01228 */
  /* Local pointer to the number of filter DTC */
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpNumOfDTCs;

  /* @Trace: Dcm_SUD_API_50592 */
  /* Get the number of DTC matching the defined status mask */
  LddNumFilteredDTCType = IDem_GetNumberOfFilteredDTC(&LusNumberOfFilteredDTC);

  /* Check whether getting number of DTC was successful */
  if(LddNumFilteredDTCType == E_OK)
  {
    /* DTCHighByte + DTCLowByte = 2 for every DTC + 1(No.of.DTC) */
    LulRespLength = (uint32) ((uint32) LusNumberOfFilteredDTC * DCM_TWO) + DCM_ONE;

    /* Update the complete response length that is to be transmitted */
    Dcm_GstMsgContext.resDataLen = LulRespLength;

    /* Check if the response buffer is capable of accommodating the
     * complete response at once */
    if(LulRespLength <= (Dcm_GstMsgContext.resMaxDataLen))
    {
      /* @Trace: Dcm_SUD_API_50501 */
      /* @Trace: SWS_Dcm_01227 SWS_Dcm_01228 */
      LpNumOfDTCs = &Dcm_GpReqResData[DCM_ZERO];

      /* Update the Number of Filtered DTC */
      Dcm_GpReqResData[DCM_ZERO] = (uint8)LusNumberOfFilteredDTC;

      /* Reset the pointer to the response data buffer */
      Dcm_GpReqResData = &Dcm_GpReqResData[DCM_ONE];

      /* Pass the buffer size with two values less since sub function and
       * availabilityMask is already updated */
      LulRespLength = LulRespLength - DCM_ONE;
      (void)Dcm_DspReadOBDDTCInfo(LulRespLength, LpNumOfDTCs);
    }
    else
    {
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      uint32 maxRespLen = Dcm_PagedBuffer_GetMaxRespLen(&Dcm_GstMsgContext);

      if (LulRespLength <= maxRespLen)
      {
        /* @Trace: Dcm_SUD_API_50502 */
        /* Store the number of filtered DTCs in this variable to update in page */
        Dcm_GucNumofDTC = (uint8)LusNumberOfFilteredDTC;

        /* Start the paged processing */
        Dcm_DsdStartPagedProcessing(&Dcm_GstMsgContext);
      }
      else
      #endif
      {
        /* @Trace: Dcm_SUD_API_50503 */
        /* @Trace: SWS_Dcm_01059 SWS_Dcm_01058 SWS_Dcm_01075 */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
      }
    }
  }
  else if(LddNumFilteredDTCType == DEM_PENDING)
  {
    /* @Trace: Dcm_SUD_API_50504 */
    /* Set the Flag for returning of DCM_E_PENDING */
    Dcm_PrtclTxBufStatus.ucReportOBDDtc = DCM_TRUE;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_50505 */
    /* Update Negative response code */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspReadOBDDTCInfo                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function for the OBDservices   **
**                        (0x03, 0x07, 0x0A) to report the Filtered DTcs      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LulBufferSize                                       **
**                                                                            **
** Output Parameters    : LpNumOfDTCs                                         **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GddCurrentLength, Dcm_GpMsgContext,             **
**                        Dcm_GddNegRespError, Dcm_GpReqResData,              **
**                        Dcm_GunDTC.                                         **
**                        Function(s) invoked : Dem_GetNextFilteredDTC        **
**                                                                            **
*******************************************************************************/
FUNC(uint32, DCM_CODE) Dcm_DspReadOBDDTCInfo(
  uint32 LulBufferSize,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpNumOfDTCs)
{
  uint32 LulRespBufferSize;

  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint32 LulRemainingLength;
  #endif

  Std_ReturnType LucReturnRes;
  uint8 LucDTCStatus;

  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  uint8 LucCount;
  #endif

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
      /* @Trace: Dcm_SUD_API_50506 */
      /* Reset the global bit flag to indicate that it is other than the first
       * page which is to be processed */
      Dcm_DspSerPgStatus.ucFirstPage = DCM_TRUE;
    }

    /* @Trace: Dcm_SUD_API_50507 */
    LulRemainingLength = Dcm_GddCurrentLength;
  }
  #endif

  /* @Trace: Dcm_SUD_API_50508 */
  /* Initialize with the configured buffer size */
  LulRespBufferSize = LulBufferSize;

  /* Initialize the global variable to indicate that no NRC as occurred */
  Dcm_GddNegRespError = DCM_POS_RESP;

  /* Initialize return value to E_OK */
  LucReturnRes = E_OK;

  while((LulRespBufferSize > DCM_ONE) &&

    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    (((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE) &&
    (LulRemainingLength >= DCM_TWO)) ||
    ((Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE))) &&
    #endif

    /* @Trace: SWS_Dcm_01227 SWS_Dcm_01228 */
    (LucReturnRes == E_OK))
  {
    LucReturnRes = IDem_GetNextFilteredDTC(
      &Dcm_GunDTC.ulLongReg32, &LucDTCStatus);

    if(LucReturnRes == E_OK)
    {
      /* @Trace: Dcm_SUD_API_50509 */
      /* DTC High Byte */
      Dcm_GpReqResData[DCM_ZERO] = Dcm_GunDTC.ddByte.ucMidHiByte;

      /* DTC Middle Byte */
      Dcm_GpReqResData[DCM_ONE] = Dcm_GunDTC.ddByte.ucMidLowByte;

      /* Increment pointer by two bytes */
      Dcm_GpReqResData = &Dcm_GpReqResData[DCM_TWO];

      /* Update the response buffer size */
      LulRespBufferSize = LulRespBufferSize - DCM_TWO;
      
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
      {
        /* @Trace: Dcm_SUD_API_50510 */
        /* Update the Temporary length of response buffer */
        LulRemainingLength = LulRemainingLength - DCM_TWO;
      }
      #endif
    }
    else if(LucReturnRes == DEM_NO_SUCH_ELEMENT)
    {
      /* @Trace: Dcm_SUD_API_50511 */
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
      {
        /* @Trace: Dcm_SUD_API_50512 */
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
      /* @Trace: Dcm_SUD_API_50513 */
      /* To avoid QAC warning, no action in this case */
    }
  }

  if(LucReturnRes == DEM_NO_SUCH_ELEMENT)
  {
    /* @Trace: SWS_Dcm_01227 */
    /* Dcm shall send a positive response including data
     * elements & number of DTCs if at least one matching element */
    if (LulBufferSize > LulRespBufferSize)
    {
      /* @Trace: Dcm_SUD_API_50514 */
      *LpNumOfDTCs = (uint8) ((LulBufferSize - LulRespBufferSize) >> DCM_ONE);
    }
    else
    {
      /* @Trace: SWS_Dcm_01228 */
      /* @Trace: Dcm_SUD_API_50515 */
      /* Dcm send a pos response with number of DTCs set to 0 */
      *LpNumOfDTCs = DCM_ZERO;
    }

    #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
    if((Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)&&
      (LulRemainingLength >= DCM_TWO) && (LulRespBufferSize > DCM_ONE))
    {
      do
      {
        /* @Trace: Dcm_SUD_API_50516 */
        for(LucCount = DCM_ZERO; LucCount < DCM_TWO; LucCount++)
        {
          *Dcm_GpReqResData = DCM_ZERO;
          Dcm_GpReqResData++;
        }

        LulRespBufferSize = LulRespBufferSize - DCM_TWO;
        LulRemainingLength  = LulRemainingLength - DCM_TWO;
      }
      while((LulRespBufferSize > DCM_ONE) && (LulRemainingLength != DCM_ZERO));
    }
    #endif
  }

  return(LulBufferSize - LulRespBufferSize);
}
#endif

#if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
     (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON))
/*******************************************************************************
** Function Name        : Dcm_GetIDIndex                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This will give the index of ID(PID/VID/TID/OBDMID)  **
**                        in DcmDspPid configuration data.                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : IDType, IDValue                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pIDIndex                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GpOBDBaseAddress           **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetIDIndex(
  uint8 IDType,
  uint8 IDValue,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pIDIndex)
{
  /* @Trace: Dcm_SUD_API_50517 */
  Std_ReturnType RetVal = E_NOT_OK;
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pIDBuffer;

  uint8 idx;
  uint8 IDNum = DCM_ZERO;

  /* @Trace: Dcm_SUD_API_50593 */
  IDNum = (DCM_GET_PID == IDType) ? DCM_TOTAL_NUM_OF_PIDS : IDNum;
  IDNum = (DCM_GET_OBDMID == IDType) ? DCM_TOTAL_NUM_OF_OBDMIDS : IDNum;
  IDNum = (DCM_GET_TID == IDType) ? DCM_TOTAL_NUM_OF_TIDS : IDNum;
  IDNum = (DCM_GET_VID == IDType) ? DCM_TOTAL_NUM_OF_VIDS : IDNum;

  /* To get Respective Buffer ID */
  pIDBuffer = Dcm_GpOBDBaseAddress[IDType];

  for(idx = DCM_ZERO; idx < IDNum; idx++)
  {
    if (IDValue == pIDBuffer[idx])
    {
      /* @Trace: Dcm_SUD_API_50518 */
      RetVal = E_OK;
      *pIDIndex = idx;
      break;
    }
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspGetAvailibiltyIDStatus                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function is used to provide the       **
**                        information regarding status of supported Ids       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : IDType, ReqBuffer, IDCount                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : SID                                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GpOBDBaseAddress,          **
**                        Dcm_GaaPIDConfig                                    **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
FUNC(uint8, DCM_CODE) Dcm_DspGetAvailibiltyIDStatus(
  uint8 IDType,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pReqBuffer,
  uint8 IDCount,
  uint8 SID)
{
  /* @Trace: Dcm_SUD_API_50519 */
  #if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
  uint8 LaaDemPID[DCM_EIGHT] = 
  {
    DCM_DEMPID01, DCM_DEMPID1C, DCM_DEMPID21,
    DCM_DEMPID30, DCM_DEMPID31, DCM_DEMPID41,
    DCM_DEMPID4D, DCM_DEMPID4E,
  };
  #endif

  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pIDConfig = Dcm_GpOBDBaseAddress[IDType];
  uint8 IDConfigIdx;
  uint8 IDConfigNum = DCM_ZERO;
  uint8 IDStatus = DCM_NOT_CONFIG_ID;
  uint8 IDValue;

  #if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
  uint8 DemIDIndex;
  #endif

  uint8 AvlCount = DCM_ZERO;
  #if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)  
  uint8 RPortCount = DCM_ZERO;
  uint8 DemCount = DCM_ZERO;
  #endif
  uint8 OtherCount = DCM_ZERO;

  uint8 MaskValue;
  uint8 idx = DCM_ZERO;

  /* @Trace: Dcm_SUD_API_50594 */
  IDConfigNum = (DCM_GET_PID == IDType) ? DCM_TOTAL_NUM_OF_PIDS : IDConfigNum;
  IDConfigNum = (DCM_GET_OBDMID == IDType) ? IDCount : IDConfigNum;
  IDConfigNum = (DCM_GET_TID == IDType) ? DCM_TOTAL_NUM_OF_TIDS : IDConfigNum;
  IDConfigNum = (DCM_GET_VID == IDType) ? DCM_TOTAL_NUM_OF_VIDS : IDConfigNum;

  while (idx < IDCount)
  {
    /* @Trace: Dcm_SUD_API_50521 */
    /* First time its same for all SID */
    if ((idx != DCM_ZERO) && (SID == DCM_TWO))
    {
      /* @Trace: Dcm_SUD_API_50520 */
      idx++;
    }

    IDValue = pReqBuffer[idx];

    /* Search in the configured list */
    for (IDConfigIdx = DCM_ZERO; IDConfigIdx < IDConfigNum; IDConfigIdx++)
    {
      if ((DCM_GET_OBDMID != IDType) && (IDValue == pIDConfig[IDConfigIdx]))
      {
        switch (SID)
        {
          case 1U:
            #if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
            if ((Dcm_GaaPIDConfig[IDConfigIdx].ucPidService == DCM_SERVICE_01) ||
                (Dcm_GaaPIDConfig[IDConfigIdx].ucPidService == DCM_SERVICE_01_02))
            {
              /* @Trace: Dcm_SUD_API_50522 */
              IDStatus = DCM_R_PORT_PID;

              /* Search for configured one belongs to Dem or RPort */
              for (DemIDIndex = 0U; DemIDIndex < DCM_EIGHT; DemIDIndex++)
              {
                if (IDValue == LaaDemPID[DemIDIndex])
                {
                  /* @Trace: Dcm_SUD_API_50523 */
                  IDStatus = DCM_DEM_PID;
                  break;
                }
              }
            }
            #endif
            break;

          case 2U:
            #if (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON)
            if ((Dcm_GaaPIDConfig[IDConfigIdx].ucPidService == DCM_SERVICE_01_02)
                || (Dcm_GaaPIDConfig[IDConfigIdx].ucPidService == DCM_SERVICE_02))
            {
              /* @Trace: Dcm_SUD_API_50524 Dcm_SUD_API_50598 */
              IDStatus = (IDValue == 2U) ? DCM_TWO_PID : DCM_OTHER_PID;
            }
            #endif
            break;

          case 8U:
          case 9U:
            /* @Trace: Dcm_SUD_API_50525 */
            IDStatus = DCM_OTHER_PID;
            break;

          default:
            /* @Trace: Dcm_SUD_API_50526 */
            /* No action in this case */
            break;
        }

        /* To skip the next iterations */
        break;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_50527 */
        IDStatus = DCM_NOT_CONFIG_ID;
      }
    }

    /* when ID not matched in the configured list */
    if (IDStatus == DCM_NOT_CONFIG_ID)
    {
      /* @Trace: Dcm_SUD_API_50528 */
      MaskValue = Dcm_GetMaskValue(IDValue);

      /* @Trace: Dcm_SUD_API_50599 Dcm_SUD_API_50600 */
      IDStatus = (MaskValue != DCM_ZERO) ? DCM_AVAIL_ID : IDStatus;
    }

    /* This process is for OBD service $06 */
    if ((DCM_GET_OBDMID == IDType) && (DCM_NOT_CONFIG_ID == IDStatus))
    {
      /* @Trace: Dcm_SUD_API_50529 */
      IDStatus = DCM_OTHER_PID;
    }

    if (IDStatus != DCM_NOT_CONFIG_ID)
    {
      /* @Trace: Dcm_SUD_API_50530 */
      AvlCount += (IDStatus == DCM_AVAIL_ID) ? 1U : 0U;
      #if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
      RPortCount += (IDStatus == DCM_R_PORT_PID) ? 1U : 0U;
      DemCount += (IDStatus == DCM_DEM_PID) ? 1U : 0U;
      #endif
      OtherCount += (IDStatus == DCM_OTHER_PID) ? 1U : 0U;

      /* combination not allowed */
      if (
        #if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
        ((AvlCount > DCM_ZERO) && (RPortCount > DCM_ZERO)) || 
        ((AvlCount > DCM_ZERO) && (DemCount > DCM_ZERO))   || 
        #endif
        ((AvlCount > DCM_ZERO) && (OtherCount > DCM_ZERO)))
      {
        /* @Trace: Dcm_SUD_API_50531 */
        IDStatus = DCM_NOT_CONFIG_ID;

        /* To terminate next iteration */
        idx = IDCount;
      }
    }

    /* Next element */
    idx++;
  }

  return IDStatus;
}

/*******************************************************************************
** Function Name        : Dcm_DspGetSizeOfIDS                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Internal function is called for the OBD service**
**                        to get size of requested IDs                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : IDType, IDCount, LpRespLenOfConfigPIDS and          **
**                        pReqData, SID                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GaaVehInfoConfig,          **
**                        Dcm_GaaPIDConfig                                    **
**                        Function(s) invoked : Dcm_GetIDIndex                **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetSizeOfIDS(
  uint8 IDType,
  uint8 IDCount,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) pIDsSize,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxBuffer,
  uint8 SID)
{
  /* @Trace: Dcm_SUD_API_50532 */
  Std_ReturnType RetVal = E_OK;

  uint8 IDValue;
  uint8 IDIndex;
  uint8 idx = DCM_ZERO;

  #if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
       (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON))
  P2CONST(Dcm_PIDConfigType, AUTOMATIC, DCM_APPL_CONST) LpPIDCfg;
  #endif

  #if (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
  P2CONST(Dcm_VehInfoConfigType, AUTOMATIC, DCM_APPL_CONST) LpVehInfoCfg;
  P2CONST(Dcm_VehInfoData, AUTOMATIC, DCM_APPL_CONST) LpVehInfoDataCfg;
  uint8 VehIdx;
  #endif

  *pIDsSize = DCM_ZERO;

  /* Calculate size of data related to all PIDs */
  while (idx < IDCount)
  {
    /* First time its same for all SID */
    if ((idx != 0U) && (SID == 2U))
    {
      /* @Trace: Dcm_SUD_API_50533 */
      idx++;
    }

    /* @Trace: Dcm_SUD_API_50539 */
    IDValue = pRxBuffer[idx];
    RetVal = Dcm_GetIDIndex(IDType, IDValue, &IDIndex);

    if (RetVal != E_OK)
    {
      /* @Trace: Dcm_SUD_API_50534 */
      RetVal = E_NOT_OK;
      break;
    }

    #if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
         (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON))
    LpPIDCfg = &Dcm_GaaPIDConfig[IDIndex];
    #endif
    /* polyspace +1 MISRA2012:16.1 MISRA2012:16.6 [Justified:Low] Justify with annotations */
    switch (SID)
    {
      #if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
      case 1U:
        if ((LpPIDCfg->ucPidService == DCM_SERVICE_01)
            || (LpPIDCfg->ucPidService == DCM_SERVICE_01_02))
        {
          /* @Trace: Dcm_SUD_API_50535 */
          /* Total response length is (PID + size of PID) */
          *pIDsSize = *pIDsSize + LpPIDCfg->ucPidBufferSize + DCM_ONE;
        }
        break;
      #endif

      #if (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON)
      case 2U:
        if ((LpPIDCfg->ucPidService == DCM_SERVICE_01_02)
            || (LpPIDCfg->ucPidService == DCM_SERVICE_02))
        {
          /* @Trace: Dcm_SUD_API_50536 */
          /* Total response length is (PID + FF REC NUMBER + size of PID) */
          *pIDsSize = *pIDsSize + LpPIDCfg->ucPidBufferSize + DCM_TWO;
        }
        break;
      #endif

      #if (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
      case 9U:
         /* @Trace: Dcm_SUD_API_50537 */
         LpVehInfoCfg = &Dcm_GaaVehInfoConfig[IDIndex];
         LpVehInfoDataCfg = LpVehInfoCfg->pDcmVehInfoData;

         /* Total response length is PID + size of PID */
         *pIDsSize += (1U + 1U);
         for (VehIdx = 0U; (VehIdx < LpVehInfoCfg->ucNoOfVehInfoData); VehIdx++)
         {
           *pIDsSize += LpVehInfoDataCfg->ucVehInfoBufSize;

           LpVehInfoDataCfg = &LpVehInfoDataCfg[1U];
         }
      break;
      #endif

      default:
        /* @Trace: Dcm_SUD_API_50538 */
        /* No action in this case */
        break;
    }

    /* Next element */
    idx++;
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_GetMaskValue                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the bit mask value of availability IDs          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : IDValue                                             **
**                                                                            **
** InOut parameter      : None                                                **
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
#if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
     (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON) || \
     (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON))
FUNC(uint8, DCM_CODE) Dcm_GetMaskValue(uint8 IDValue)
{
  /* @Trace: Dcm_SUD_API_50603 */
  uint8 MaskValue = DCM_ZERO;

  /* @Trace: Dcm_SUD_API_50595 */
  MaskValue = (IDValue == DCM_ZERO) ? DCM_ONE : MaskValue;
  MaskValue = (IDValue == DCM_THIRTY_TWO) ? DCM_TWO : MaskValue;
  MaskValue = (IDValue == DCM_SIXTY_FOUR) ? DCM_FOUR : MaskValue;
  MaskValue = (IDValue == DCM_NINTY_SIX) ? DCM_EIGHT : MaskValue;
  MaskValue = (IDValue == DCM_ONE_TWO_EIGHT) ? DCM_SIXTEEN : MaskValue;
  MaskValue = (IDValue == DCM_ONE_SIXTY) ? DCM_THIRTY_TWO : MaskValue;
  MaskValue = (IDValue == DCM_ONE_NINE_TWO) ? DCM_SIXTY_FOUR : MaskValue;
  MaskValue = (IDValue == DCM_TWO_TWO_FOUR) ? DCM_ONE_TWO_EIGHT : MaskValue;

  return MaskValue;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspReadOBD_AvlInfo                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function is used to update            **
**                        availability list                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LpRxBuffer,LucPIDCount,IDType and LulBufferSize     **
**                                                                            **
** InOut parameter      : LpTxBuffer                                          **
**                                                                            **
** Output Parameters    : LpTxBuffer                                          **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GucPIDCount                                     **
**                        Function(s) invoked : Dcm_DspGetConfigIDS           **
**                                                                            **
*******************************************************************************/
#if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON))
FUNC(uint32, DCM_CODE) Dcm_DspReadOBD_AvlInfo(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer,
  uint32 BufferSize,
  uint8 IDCount,
  uint8 IDType)
{
  /* @Trace: Dcm_SUD_API_50540 */
  Std_ReturnType RetVal;
  uint32 LulRespBufferSize = BufferSize;
  uint8 IDValue;
  uint8 IDSize;
  uint8 idx = DCM_ZERO;

  /* If paging is enabled load the filtered DTC from stored */
  #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* Check if paged transmission is in progress */
  if (Dcm_DspSerPgStatus.ucPagingStarted == DCM_TRUE)
  {
    /* Check if it is the first page that is to be updated */
    if(Dcm_DspSerPgStatus.ucFirstPage == DCM_FALSE)
    {
      /* @Trace: Dcm_SUD_API_50541 */
      /* Reset the global bit flag to indicate that it is other than the first
       * page which is to be processed */
      Dcm_DspSerPgStatus.ucFirstPage = DCM_TRUE;
    }
  }
  #endif

  Dcm_GblAvailabilityPIDFlag = DCM_FALSE;

  while ((4U < LulRespBufferSize) && (0U < IDCount))
  {
    /* polyspace +3 MISRA-C3:17.8 [Justified:Low] Justify with annotations */
    IDValue = pRxBuffer[idx];
    *pTxBuffer = IDValue;
    pTxBuffer = &pTxBuffer[1U];

    /* Get All Availability list of 4 bytes */
    if (IDType == DCM_GET_PID)
    {
      /* @Trace: Dcm_SUD_API_50542 */
      #if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
      RetVal = Dcm_DspGetConfigIDS1(IDValue, IDType, pTxBuffer, &IDSize);
      #else
      /* @Trace: Dcm_SUD_API_50601 */
      RetVal = E_NOT_OK;
      #endif
    }
    /* @Trace: SWS_Dcm_00957 */
    #if (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON)
    else if (DCM_GET_OBDMID == IDType)
    {
      /* @Trace: Dcm_SUD_API_50543 */
      Dcm_MIdWord_Access LddMidValue;
      LddMidValue.whole_dword = DCM_ZERO;

      /* Invoke function to get available OBD MIDs value */
      RetVal = Dem_DcmGetAvailableOBDMIDs(IDValue, &(LddMidValue.whole_dword));

      /* Copy available OBD MIDs value to response buffer */
      Dcm_MemCopy(pTxBuffer, LddMidValue.byte_val.BO_Byte, DCM_FOUR);
    }
    #endif
    else
    {
      /* @Trace: Dcm_SUD_API_50544 */
      RetVal = Dcm_DspGetConfigIDS(IDValue, IDType, pTxBuffer, &IDSize);
    }

    if (RetVal == E_OK)
    {
      /* @Trace: Dcm_SUD_API_50545 */
      /* polyspace-begin MISRA-C3:17.8 [Justified:Low] Justify with annotations */
      pTxBuffer = &pTxBuffer[4U];
      LulRespBufferSize -= 5U;
      Dcm_GucPIDCount--;

      Dcm_GblAvailabilityPIDFlag = DCM_TRUE;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_50546 */
      pTxBuffer = &pTxBuffer[-1];
    }

    idx++;
    IDCount--;
  }

  BufferSize -= LulRespBufferSize;
  return BufferSize;
  /* polyspace-end MISRA-C3:17.8 [Justified:Low] Justify with annotations */
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspGetConfigIDS                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function is used to get the configured**
**                        Ids supported for the services                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : IDValue, IDType                                     **
**                                                                            **
** InOut parameter      : pTxBuffer                                           **
**                                                                            **
** Output Parameters    : pIDSize                                             **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GpEncodeByte,              **
**                        Dcm_GaaPIDEncodeByte.                               **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON) || \
     (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON) || \
     (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON))
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetConfigIDS(
  uint8 IDValue,
  uint8 IDType,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pIDSize)
{
  P2CONST(Dcm_IDEncodeByteConfig, AUTOMATIC, DCM_APPL_CONST) LpIDEncodeByte;
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 LucRightPosition = DCM_ONE;
  uint8 LucAvalListIndex = DCM_ZERO;

  /* @Trace: Dcm_SUD_API_50547 */
  uint8 LucMaskValue = Dcm_GetMaskValue(IDValue);

  uint8 LucAvalConfigList = DCM_ZERO;

  /* @Trace: Dcm_SUD_API_50596 */
  LucAvalConfigList = (DCM_GET_PID == IDType) ? \
    DCM_PID_AVL_CONFIG_LIST_FREEZE_FRAME : LucAvalConfigList;

  LucAvalConfigList = (DCM_GET_OBDMID == IDType) ? \
    DCM_OBDMID_AVL_CONFIG_LIST : LucAvalConfigList;

  LucAvalConfigList = (DCM_GET_TID == IDType) ? \
    DCM_TID_AVL_CONFIG_LIST : LucAvalConfigList;

  LucAvalConfigList = (DCM_GET_VID == IDType) ? \
    DCM_VID_AVL_CONFIG_LIST : LucAvalConfigList;

  LucAvalConfigList = (DCM_OTHER_DID_OBD_RANGE == IDType) ? \
    DCM_OBD_DID_AVL_CONFIG_LIST : LucAvalConfigList;

  LucAvalConfigList = (DCM_OTHER_DID_INFOTYPE_RANGE == IDType) ? \
    DCM_INFOTYPE_DID_AVL_CONFIG_LIST : LucAvalConfigList;

  /* Generic for all services */
  if ((LucAvalConfigList & LucMaskValue) != DCM_ZERO)
  {
    RetVal = E_OK;

    uint8 idx;

    for (idx = DCM_ZERO; (idx < DCM_EIGHT) && (LucRightPosition <= LucMaskValue); idx++)
    {
      if ((LucAvalConfigList & LucRightPosition) != DCM_ZERO)
      {
        /* @Trace: Dcm_SUD_API_50548 */
        LucAvalListIndex++;

        if (LucRightPosition == LucMaskValue)
        {
          /* @Trace: Dcm_SUD_API_50549 */
          break;
        }
      }

      if (LucRightPosition < DCM_ONE_TWO_EIGHT)
      {
        /* @Trace: Dcm_SUD_API_50550 */
        LucRightPosition <<= DCM_ONE;
      }
    }

    if (LucAvalListIndex > DCM_ZERO) 
    {
      /* @Trace: Dcm_SUD_API_50551 */
      LucAvalListIndex--;
    }
    
    #if (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON)
    if (IDType == DCM_ZERO)
    {
      /* @Trace: Dcm_SUD_API_50552 */
      LpIDEncodeByte = &Dcm_GaaPIDEncodeByte[IDType];
    }
    else
    #endif
    {
      /* @Trace: Dcm_SUD_API_50553 */
      LpIDEncodeByte = Dcm_GpEncodeByte[IDType];
    }

    /* make sure LpIDEncodeByte is not null */
    /* @Trace: Dcm_SUD_API_50554 */
    /* polyspace-begin MISRA-C3:17.8 [Justified:Low] Justify with annotations */
    /* polyspace +2 MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace +1 DEFECT:DEAD_CODE [Justified:Low] "Dcm_GpEncodeByte depend on configuration. No Impact" */
    if (LpIDEncodeByte != NULL_PTR)
    {
      *pTxBuffer = LpIDEncodeByte[LucAvalListIndex].ucEncodeByteA;

      pTxBuffer = &pTxBuffer[1U];
      *pTxBuffer = LpIDEncodeByte[LucAvalListIndex].ucEncodeByteB;

      pTxBuffer = &pTxBuffer[1U];
      *pTxBuffer = LpIDEncodeByte[LucAvalListIndex].ucEncodeByteC;

      pTxBuffer = &pTxBuffer[1U];
      *pTxBuffer = LpIDEncodeByte[LucAvalListIndex].ucEncodeByteD;

      *pIDSize = DCM_FOUR;
    }
    /* polyspace-end MISRA-C3:17.8 [Justified:Low] Justify with annotations */
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspGetConfigIDS1                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Internal function is called for the OBD service**
**                        to get the Configured IDs for service(0x01)         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : IDType, IDValue                                     **
**                                                                            **
** InOut parameter      : pTxBuffer                                           **
**                                                                            **
** Output Parameters    : pIDSize                                             **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GaaPIDEncodeByte1         **
**                        Function(s) invoked : Dcm_GetIDIndex                **
**                                                                            **
*******************************************************************************/
#if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetConfigIDS1(
  uint8 IDValue,
  uint8 IDType,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pIDSize)
{
  P2CONST(Dcm_IDEncodeByteConfig, AUTOMATIC, DCM_APPL_CONST) LpIDEncodeByteCfg;
  Std_ReturnType RetVal = E_NOT_OK;

  uint8 IDIndex = DCM_ZERO;
  uint8 RightPos = DCM_ONE;

  /* @Trace: Dcm_SUD_API_50555 */
  uint8 MaskValue = Dcm_GetMaskValue(IDValue);

  uint8 AvailCfgList = DCM_ZERO;

  /* @Trace: Dcm_SUD_API_50597 */
  AvailCfgList = (DCM_GET_PID == IDType) ? \
    DCM_PID_AVL_CONFIG_LIST : AvailCfgList;

  AvailCfgList = (DCM_GET_OBDMID == IDType) ? \
    DCM_OBDMID_AVL_CONFIG_LIST : AvailCfgList;

  AvailCfgList = (DCM_GET_TID == IDType) ? \
    DCM_TID_AVL_CONFIG_LIST : AvailCfgList;

  AvailCfgList = (DCM_GET_VID == IDType) ? \
    DCM_VID_AVL_CONFIG_LIST : AvailCfgList;

  /* Generic for all services */
  /* Trace: DEM_OBD_01_09 */
  if ((AvailCfgList & MaskValue) != DCM_ZERO) 
  {
    uint8 idx;

    for (idx = DCM_ZERO; (idx < DCM_EIGHT) && (RightPos <= MaskValue); idx++)
    {
      if ((AvailCfgList & RightPos) != DCM_ZERO)
      {
        /* @Trace: Dcm_SUD_API_50556 */
        IDIndex++;

        if (RightPos == MaskValue)
        {
          /* @Trace: Dcm_SUD_API_50557 */
          break;
        }
      }

      if (RightPos < DCM_ONE_TWO_EIGHT)
      {
        /* @Trace: Dcm_SUD_API_50558 */
        RightPos <<= DCM_ONE;
      }
    }

    LpIDEncodeByteCfg = &Dcm_GaaPIDEncodeByte1[IDType];

    if (IDIndex > DCM_ZERO)
    {
      /* @Trace: Dcm_SUD_API_50559 */
      IDIndex--;
    }
    
    /* Update 32 bit information */
    /* polyspace-begin MISRA-C3:17.8 [Justified:Low] Justify with annotations */
    *pTxBuffer = LpIDEncodeByteCfg[IDIndex].ucEncodeByteA;

    pTxBuffer = &pTxBuffer[DCM_ONE];
	  *pTxBuffer= LpIDEncodeByteCfg[IDIndex].ucEncodeByteB;

    pTxBuffer = &pTxBuffer[DCM_ONE];
    *pTxBuffer = LpIDEncodeByteCfg[IDIndex].ucEncodeByteC;

    pTxBuffer = &pTxBuffer[DCM_ONE];
    *pTxBuffer = LpIDEncodeByteCfg[IDIndex].ucEncodeByteD;
    /* polyspace-end MISRA-C3:17.8 [Justified:Low] Justify with annotations */

    *pIDSize = DCM_FOUR;

    RetVal = E_OK;
  }

  return RetVal;
}
#endif

#if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)

/*******************************************************************************
** Function Name        : Dcm_DspReadOBD_1_DemInfo                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function is used to Process the PID   **
**                        request for Service(0x01)                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pRxBuffer, PIDCount                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pTxBuffer, pRespLength                              **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GpMsgContext, Dcm_GaaPidSignalData,             **
**                        Dcm_GaaPIDUint8Func, Dcm_GaaPIDSint32Func,          **
**                        Dcm_GaaPIDConfig, Dcm_GucPIDCount,                  **
**                        Dcm_GaaPIDUint16Func, Dcm_GaaPIDUint32Func,         **
**                        Dcm_GaaPIDSint8Func, Dcm_GaaPIDSint16Func,          **
**                        Dcm_GaaSigWrFuncPtr, Dcm_GddNegRespError.           **
**                        Function(s) invoked : Dcm_DspGetSizeOfIDS,          **
**                        Dcm_GetIDIndex                                      **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(uint16, DCM_CODE) Dcm_DspReadOBD_1_DemInfo(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRxBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) pRespLength,
  uint8 PIDCount)
{
  uint8 PIDValue;
  uint8 PIDIndex = DCM_ZERO;

  P2CONST(Dcm_PIDConfigType, AUTOMATIC, DCM_APPL_CONST) pPIDCfg;
  P2CONST(Dcm_DspPidData, AUTOMATIC, DCM_APPL_CONST) pPIDDataCfg;
  uint8 Mix_DemRPort;
  uint8 PIDDataNum;
  uint8 PIDDataIndex;

  #if (DCM_OBD_PID_SUPPORT_INFO == STD_ON)
  uint8 SuppByte;
  uint8 PIDDataSuppInfoBit;
  uint8 SuppInfoValue;
  #endif

  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxDataBuffer;

  P2CONST(Dcm_PIDPackSignal, AUTOMATIC, DCM_APPL_CONST) pPidPackSignal;

  uint8 LaaDemPID[DCM_EIGHT] = {
                                DCM_DEMPID01, DCM_DEMPID1C, DCM_DEMPID21,
                                DCM_DEMPID30, DCM_DEMPID31, DCM_DEMPID41,
                                DCM_DEMPID4D, DCM_DEMPID4E,
                               };

  /* Get the response length of requested IDs For READ DID */
  uint16 RespLen = 0U;
  Std_ReturnType RetVal = Dcm_DspGetSizeOfIDS(DCM_GET_PID,
    PIDCount, &RespLen, pRxBuffer, 1U);

  *pRespLength = RespLen;

  /* @Trace: Dcm_SUD_API_50561 */
  /* @Trace: SWS_Dcm_00623 SWS_Dcm_00944 */
  /* Set the fill bytes to 0x00 whenever content bytes 
   * are missing in order to fit to the PID size */
  uint8 cnt = DCM_ZERO;
  while (cnt < RespLen)
  {
    pTxBuffer[cnt] = DCM_ZERO;
    cnt++;
  }

  if (RespLen <= Dcm_GstMsgContext.resMaxDataLen)
  {
    uint8 idx;

    for (idx = DCM_ZERO; idx < PIDCount; idx++)
    {
      /* @Trace: Dcm_SUD_API_50602 */
      PIDValue = pRxBuffer[idx];
      Mix_DemRPort = DCM_R_PORT_PID;

      /* Search for configured one belongs to Dem or RPort */
      for (cnt = DCM_ZERO; cnt < DCM_EIGHT; cnt++)
      {
        if (PIDValue == LaaDemPID[cnt])
        {
          /* @Trace: Dcm_SUD_API_50562 */
          Mix_DemRPort = DCM_DEM_PID;
          break;
        }
      }

      /* @Trace: Dcm_SUD_API_50563 */
      (void) Dcm_GetIDIndex(DCM_GET_PID, PIDValue, &PIDIndex);
      pPIDCfg = &Dcm_GaaPIDConfig[PIDIndex];

      if (Mix_DemRPort == DCM_DEM_PID)
      {
        if ((pPIDCfg->ucPidService == DCM_SERVICE_01)
            || (pPIDCfg->ucPidService == DCM_SERVICE_01_02))
        {
          /* @Trace: Dcm_SUD_API_50564 */
          pPIDDataCfg = pPIDCfg->pDcmDspPidData;

          /* Update PID value to TX buffer*/
          /* polyspace-begin MISRA-C3:17.8 [Justified:Low] Justify with annotations */
          *pTxBuffer = PIDValue;
          pTxBuffer = &pTxBuffer[1U];
          /* polyspace-end MISRA-C3:17.8 [Justified:Low] Justify with annotations */

          pPIDDataCfg->pReadPidDataFun(pTxBuffer);
        }
      }
      else
      {
        /* @Trace: Dcm_SUD_API_50565 */
        PIDDataNum = pPIDCfg->ucNumofPIDData;

        #if (DCM_OBD_PID_SUPPORT_INFO == STD_ON)
        SuppInfoValue = 0U;
        if (pPIDCfg->ucNumofPIDSupportInfo != 0U)
        {
          /* @Trace: Dcm_SUD_API_50566 */
          pPIDDataCfg = pPIDCfg->pDcmDspPidData;

          for (PIDDataIndex = 0U; PIDDataIndex < PIDDataNum; PIDDataIndex++)
          {
            /* Check if Support Info is Configured for the signal */
            if (pPIDDataCfg->pDcmDspPidDataSupportInfoRef != NULL_PTR)
            {
              /* @Trace: Dcm_SUD_API_50567 */
              PIDDataSuppInfoBit = pPIDDataCfg->ucDcmDspPidDataSupportInfoBit;
              PIDDataSuppInfoBit %= 8U;
              SuppByte = 1U << PIDDataSuppInfoBit;
              SuppInfoValue |= SuppByte;
            }
            /* polyspace +1 MISRA-C3:17.8 [Justified:Low] Justify with annotations */
            pPIDDataCfg++;
          }
        }
        #endif
        /* polyspace +2 MISRA-C3:17.8 [Justified:Low] Justify with annotations */
        *pTxBuffer = PIDValue;
        pTxBuffer++;

        LpTxDataBuffer = pTxBuffer;

        #if (DCM_OBD_PID_SUPPORT_INFO == STD_ON)
        if (SuppInfoValue != 0U)
        {
          /* @Trace: Dcm_SUD_API_50568 */
          *pTxBuffer = SuppInfoValue;
          pTxBuffer++;
        }
        #endif

        pPIDDataCfg = pPIDCfg->pDcmDspPidData;
        for (PIDDataIndex = 0U; PIDDataIndex < PIDDataNum; PIDDataIndex++)
        {
          /* @Trace: ECUC_Dcm_01107 */
          if (pPIDDataCfg->ucDcmDspPidByteOffset < DCM_ONE)
          {
            /* @Trace: Dcm_SUD_API_50569 */
            break;
          }

          /* @Trace: Dcm_SUD_API_50570 */
          pPIDDataCfg++;
        }

        pPIDDataCfg = pPIDCfg->pDcmDspPidData;
        for (PIDDataIndex = 0U; PIDDataIndex < PIDDataNum; PIDDataIndex++)
        {
          /* @Trace: Dcm_SUD_API_50571 */
          RetVal = Dcm_ReadPIDData(pPIDDataCfg);

          if (RetVal == E_OK)
          {
            /* @Trace: SWS_Dcm_00718 */
            /* @Trace: Dcm_SUD_API_50572 */
            Dcm_PackUnPackType LddPackSignal;
            pPidPackSignal = pPIDDataCfg->pDcmDspPidPackSigRef;

            if (NULL_PTR != pPidPackSignal)
            {
              /* @Trace: Dcm_SUD_API_50573 */
              /* Convert to pack unpack data */
              LddPackSignal.blByteConversion = pPidPackSignal->blByteConversion;
              LddPackSignal.usSignalSize = pPIDDataCfg->ucDcmDspPidDataByteSize;

              /* Pointer to tx buffer based on byte offset */
              /* polyspace +1 MISRA-C3:17.8 [Justified:Low] Justify with annotations */
              pTxBuffer = &LpTxDataBuffer[pPIDDataCfg->ucDcmDspPidByteOffset];

              /* Call pack function with index value */
              uint8 LucPackFuncIdx = pPidPackSignal->ucPackFuncIndex;

              if (LucPackFuncIdx < DCM_NUM_OF_PACK_FUNC_CONFIG)
              {
                /* @Trace: Dcm_SUD_API_50574 */
                Dcm_GaaPackFunc[LucPackFuncIdx].pPackFunc(
                  Dcm_GaaPidSignalData,
                  pTxBuffer,
                  &LddPackSignal);
              }
            }
          }

          pPIDDataCfg++;
        }
      }
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_50575 */
    Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
  }

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ReadPIDData                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function used to read the pid data             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pPIDDataCfg                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_ReadPIDData(
  P2CONST(Dcm_DspPidData, AUTOMATIC, DCM_APPL_CONST) pPIDDataCfg)
{
  Std_ReturnType RetVal = E_NOT_OK;
  Dcm_DataUsePortType PIDDataUsePort = pPIDDataCfg->ucDcmDspPidDataUsePort;

  if ((PIDDataUsePort == USE_DATA_SYNCH_FNC)
      || (PIDDataUsePort == USE_DATA_SYNCH_CLIENT_SERVER))
  {
    /* @Trace: Dcm_SUD_API_50576 */
    RetVal = pPIDDataCfg->pReadPidDataFun(Dcm_GaaPidSignalData);
  }
  #if (DCM_PID_DATA_SENDER_RECEIVER == STD_ON)
  else if ((PIDDataUsePort == USE_DATA_SENDER_RECEIVER)
           || (PIDDataUsePort == USE_DATA_SENDER_RECEIVER_AS_SERVICE))
  {
    Dcm_DataType DataType = pPIDDataCfg->ucDcmPIDDataType;
    uint8 ReadFunIdx = pPIDDataCfg->ucReadFunctionIndex;

    switch (DataType)
    {
      case DCM_DATA_TYPE_BOOLEAN:
        #if (DCM_DSP_PID_BOOLEAN == STD_ON)
        /* @Trace: Dcm_SUD_API_50577 */
        RetVal = Dcm_GaaPIDBooleanFunc[ReadFunIdx].
          pReadPidDataBoolFun((boolean*)Dcm_GaaPidSignalData);
        #endif
        break;

      case DCM_DATA_TYPE_UINT8:
        #if (DCM_DSP_PID_UINT8 == STD_ON)
        /* @Trace: Dcm_SUD_API_50578 */
        RetVal = Dcm_GaaPIDUint8Func[ReadFunIdx].
          pReadPidDataUint8Fun(Dcm_GaaPidSignalData);
        #endif
        break;

      case DCM_DATA_TYPE_UINT8_N:
        #if (DCM_DSP_PID_UINT8_N == STD_ON)
        /* @Trace: Dcm_SUD_API_50579 */
        RetVal = Dcm_GaaPIDUint8NFunc[ReadFunIdx].
          pReadPidDataUint8NFun(Dcm_GaaPidSignalData);
        #endif
        break;

      case DCM_DATA_TYPE_SINT8:
        #if (DCM_DSP_PID_SINT8 == STD_ON)
        /* @Trace: Dcm_SUD_API_50580 */
        RetVal = Dcm_GaaPIDSint8Func[ReadFunIdx].
          pReadPidDataSint8Fun((sint8*)Dcm_GaaPidSignalData);
        #endif
        break;

      case DCM_DATA_TYPE_SINT8_N:
        #if (DCM_DSP_PID_SINT8_N == STD_ON)
        /* @Trace: Dcm_SUD_API_50581 */
        RetVal = Dcm_GaaPIDSint8NFunc[ReadFunIdx].
          pReadPidDataSint8NFun((sint8*)Dcm_GaaPidSignalData);
        #endif
        break;

      case DCM_DATA_TYPE_UINT16:
        #if (DCM_DSP_PID_UINT16 == STD_ON)
        /* @Trace: Dcm_SUD_API_50582 */
        RetVal = Dcm_GaaPIDUint16Func[ReadFunIdx].
          pReadPidDataUint16Fun((uint16*)Dcm_GaaPidSignalData);
        #endif
        break;

      case DCM_DATA_TYPE_UINT16_N:
        #if (DCM_DSP_PID_UINT16_N == STD_ON)
        /* @Trace: Dcm_SUD_API_50583 */
        RetVal = Dcm_GaaPIDUint16NFunc[ReadFunIdx].
          pReadPidDataUint16NFun((uint16*)Dcm_GaaPidSignalData);
        #endif
        break;

      case DCM_DATA_TYPE_SINT16:
        #if (DCM_DSP_PID_SINT16 == STD_ON)
        /* @Trace: Dcm_SUD_API_50584 */
        RetVal = Dcm_GaaPIDSint16Func[ReadFunIdx].
          pReadPidDataSint16Fun((sint16*)Dcm_GaaPidSignalData);
        #endif
        break;

      case DCM_DATA_TYPE_SINT16_N:
        #if (DCM_DSP_PID_SINT16_N == STD_ON)
        /* @Trace: Dcm_SUD_API_50585 */
        RetVal = Dcm_GaaPIDSint16NFunc[ReadFunIdx].
          pReadPidDataSint16NFun((sint16*)Dcm_GaaPidSignalData);
        #endif
        break;

      case DCM_DATA_TYPE_UINT32:
        #if (DCM_DSP_PID_UINT32 == STD_ON)
        /* @Trace: Dcm_SUD_API_50586 */
        RetVal = Dcm_GaaPIDUint32Func[ReadFunIdx].
          pReadPidDataUint32Fun((uint32*)Dcm_GaaPidSignalData);
        #endif
        break;

      case DCM_DATA_TYPE_UINT32_N:
        #if (DCM_DSP_PID_UINT32_N == STD_ON)
        /* @Trace: Dcm_SUD_API_50587 */
        RetVal = Dcm_GaaPIDUint32NFunc[ReadFunIdx].
          pReadPidDataUint32NFun((uint32*)Dcm_GaaPidSignalData);
        #endif
        break;

      case DCM_DATA_TYPE_SINT32:
        #if (DCM_DSP_PID_SINT32 == STD_ON)
        /* @Trace: Dcm_SUD_API_50588 */
        RetVal = Dcm_GaaPIDSint32Func[ReadFunIdx].
          pReadPidDataSint32Fun((sint32*)Dcm_GaaPidSignalData);
        #endif
        break;

      case DCM_DATA_TYPE_SINT32_N:
        #if (DCM_DSP_PID_SINT32_N == STD_ON)
        /* @Trace: Dcm_SUD_API_50589 */
        RetVal = Dcm_GaaPIDSint32NFunc[ReadFunIdx].
          pReadPidDataSint32NFun((sint32*)Dcm_GaaPidSignalData);
        #endif
        break;

      default:
        /* @Trace: Dcm_SUD_API_50590 */
        break;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_50591 */
    /* To avoid QAC, no action in this case */
  }
  #endif

  return RetVal;
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
