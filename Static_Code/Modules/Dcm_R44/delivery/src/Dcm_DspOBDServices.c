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
**  SRC-MODULE: Dcm_DspOBDServices.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions for OBD services           **
**              implemented by DSP layer of Dcm module                        **
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
** 0.0.2     16-Aug-2020   HueKM          Fix defect and coding rules         **
** 0.0.3     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.4     02-Nov-2020   LanhLT         Changes made as per #16832          **
** 0.0.5     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.6     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
** 1.3.0     31-Dcm-2023   EK Kim         Refer #CP44-3198                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm.h"
#include "Dcm_PCTypes.h"
#include "Dcm_DspServices.h"
#include "Rte_Dcm.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dem.h"
#include "Dem_Dcm.h"
#endif
#include "Dcm_Ram.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_DspOBDInternals.h"
#include "Dcm_Version.h"
#include "Dcm_DspOBDServices.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dcm_DemInterfaces.h"
#endif
#include "Dcm_Utils.h"

#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_DcmOBDReqCurrentPowerTrainDiagData              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is internal function that provides OBD service **
**                        0x01                                                **
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
** Remarks              : Global Variable(s) : Dcm_GddNegRespError            **
**                        Function(s) invoked : Dcm_DspGetAvailibiltyIDStatus **
**                        Dcm_DspReadOBD_AvlInfo, Dcm_DspReadOBD_1_DemInfo    **
**                        Dcm_DspGetSizeOfIDS                                 **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04129 SRS_Diag_04136 SRS_Diag_04161 */
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDReqCurrentPowerTrainDiagData(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_30348 */
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqData = pMsgContext->reqData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer;
  Std_ReturnType RetVal = E_OK;
  uint16 LusRespLength = DCM_ZERO;
  uint16 LusRespLengthRcvd = DCM_ZERO;
  uint16 LusPidLength = DCM_ZERO;
  uint8 PIDCount = DCM_ZERO;
  uint8 IDStatus;

  Dcm_GblAvailabilityPIDFlag = DCM_TRUE;

  /* Check for the validity of length */
  if ((pMsgContext->reqDataLen < DCM_ONE) || 
      (pMsgContext->reqDataLen > DCM_SIX))
  {
    /* @Trace: Dcm_SUD_API_30349 */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }

  /* Validate PIDs range */
  if ((pMsgContext->reqDataLen > DCM_ZERO) && 
      (pMsgContext->reqDataLen < DCM_SEVEN))
  {
    /* @Trace: Dcm_SUD_API_30350 */
    PIDCount = (uint8)pMsgContext->reqDataLen;
  }

  if (DCM_ZERO < PIDCount)
  {
    /* @Trace: Dcm_SUD_API_30351 */
    /* To find whether the PIDs belongs to Availability PIDs or Dem or RPort */
    IDStatus = Dcm_DspGetAvailibiltyIDStatus(
      DCM_GET_PID, LpReqData, PIDCount, DCM_ONE);

    if (IDStatus == DCM_AVAIL_ID)
    {
      /* @Trace: Dcm_SUD_API_30352 */
      /* Total response = Number of PIDs + (Number of PIDs) * four */
      LusRespLength = (uint16) ((uint16) PIDCount * DCM_FIVE);
    }
    else if ((IDStatus == DCM_DEM_PID) || (IDStatus == DCM_R_PORT_PID))
    {
      /* @Trace: Dcm_SUD_API_30353 */
      /* Get the response length of requested PIDs */
      RetVal = Dcm_DspGetSizeOfIDS(
        DCM_GET_PID, PIDCount, &LusRespLength, LpReqData, DCM_ONE);
    }
    else
    {  /* not configured or mixed AVAILID and PID */
      /* @Trace: SWS_Dcm_00943 */
      /* @Trace: Dcm_SUD_API_30441 */
	  /* in case AVAIL_ID + PID no response */ 
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
      RetVal = E_NOT_OK;
    }

    /* Validate ID */
    if ((IDStatus != DCM_NOT_CONFIG_ID) && (RetVal == E_OK))
    {
      if (LusRespLength <= pMsgContext->resMaxDataLen)
      {
        /* @Trace: Dcm_SUD_API_30355 */
        RetVal = E_OK;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_30354 */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
        RetVal = E_NOT_OK;
      }

      /* For non paged response */
      if (RetVal == E_OK)
      {
        /* @Trace: Dcm_SUD_API_30356 */
        LpTxBuffer = pMsgContext->resData;

        if (IDStatus == DCM_AVAIL_ID)
        {
          /* @Trace: SWS_Dcm_00407 */
          /* @Trace: Dcm_SUD_API_30357 */
          LusRespLengthRcvd = (uint16)Dcm_DspReadOBD_AvlInfo(
            LpReqData, LpTxBuffer, LusRespLength, PIDCount, DCM_GET_PID);
        }

        if ((IDStatus == DCM_R_PORT_PID) || (IDStatus == DCM_DEM_PID))
        {
          /* @Trace: SWS_Dcm_00408 */
          /* @Trace: Dcm_SUD_API_30358 */
          RetVal = (uint8)Dcm_DspReadOBD_1_DemInfo(
            LpReqData, LpTxBuffer, &LusPidLength, PIDCount);

          LusRespLengthRcvd = LusRespLength;
        }

        if (RetVal != E_NOT_OK)
        {
          /* @Trace: Dcm_SUD_API_30359 */
          Dcm_GddNegRespError = DCM_POS_RESP;
          pMsgContext->resDataLen = LusRespLengthRcvd;

          if (Dcm_GblAvailabilityPIDFlag == DCM_FALSE)
          {
            /* @Trace: Dcm_SUD_API_30360 */
            Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_TRUE;
          }
        }
      }
    }
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmOBDReqPowerTrainFreezeFrameData              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is internal function that provides OBD service **
**                        0x02                                                **
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
** Remarks              : Global Variable(s) : Dcm_GunDTC,                    **
**                        Dcm_GddNegRespError                                 **
**                        Function(s) invoked : Dcm_DspGetAvailibiltyIDStatus **
**                        Dcm_DspGetSizeOfIDS, Dcm_GaaPIDConfig,              **
**                        Dcm_GetIDIndex,                                     **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04024 SRS_Diag_04129 SRS_Diag_04161 */
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDReqPowerTrainFreezeFrameData(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  P2CONST(Dcm_DspPidData, AUTOMATIC, DCM_APPL_CONST) LpDcmDspPidData;

  uint32 LulCount2;
  uint16 LusRespLength;
  uint16 LucBufferSize;

  Std_ReturnType LddReturnValue;
  Std_ReturnType requestResult = E_OK;

  uint8 LucPIDValue;
  uint8 LucPIDIndex;
  uint8 LucPIDIndex_1;
  uint8 LucPIDCount;
  uint8 LucFreezeFrameRecord;
  uint8 LucSID;
  uint8 LucMix_DemRPort;
  uint8 LucNumofData;
  
  uint8 LucCount;
  uint8 LucSizeOfPID;
  uint8 LucDataElementIndex;
  uint8 LucIDIndex;
  uint8 LddAvlValueID;
  uint8 LucDestBuffer[DCM_MAXVALUE];

  boolean isAtleastOnePIDSp;
  boolean isNoSendResp;
  uint32 LpTxBufferIndex;

  LusRespLength = DCM_ZERO;
  isAtleastOnePIDSp = DCM_FALSE;
  isNoSendResp = DCM_FALSE;

  /* Initialize the global variable to indicate that no NRC as occurred */
  Dcm_GddNegRespError = DCM_POS_RESP;
  Dcm_GblAvailabilityPIDFlag = DCM_TRUE;

  /* Get the pointer to the request data buffer */
  LpReqResData = pMsgContext->reqData;

  /* Update return value E_OK */
  LddReturnValue = E_OK;

  /* Update PIDCount with zero */
  LucPIDCount = DCM_ZERO;

  /* Check for the validity of length */
  if(pMsgContext->reqDataLen < DCM_TWO)
  {
    /* @Trace: Dcm_SUD_API_30390 */
    /* Report the Condition not correct NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }

  /* Validate PIDs + Freeze Frame range */
  if((pMsgContext->reqDataLen > DCM_ZERO) &&
    (pMsgContext->reqDataLen < DCM_SEVEN))
  {
    /* @Trace: Dcm_SUD_API_30391 */
    /* Update the PIDs are exist in the request buffer */
    LucPIDCount = (uint8)pMsgContext->reqDataLen/DCM_TWO;
  }

  /* @Trace: SWS_Dcm_00409 */
  /* To validate Freeze Frame record number */
  for (LucPIDIndex = DCM_ONE; 
       LucPIDIndex < pMsgContext->reqDataLen; 
       LucPIDIndex += DCM_TWO)
  {
    /* @Trace: Dcm_SUD_API_30393 */
    /* Validate whether the FF zero */
    if(LpReqResData[LucPIDIndex] != DCM_ZERO )
    {
      /* @Trace: Dcm_SUD_API_30394 */
      LucPIDCount = DCM_ZERO;
      break;
    }
  }

  /* Check PID count */
  if(LucPIDCount > DCM_ZERO)
  {
    /* @Trace: Dcm_SUD_API_30396 */
    LucMix_DemRPort = DCM_TWO;

    /* It scans for all PIDs */
    /* To find whether the PIDs belongs to Availability PIDs or Dem or RPort */
    LddAvlValueID = Dcm_DspGetAvailibiltyIDStatus(
      DCM_GET_PID, LpReqResData, LucPIDCount, LucMix_DemRPort);

    /* Validate DCM_AVAIL_ID for response length */
    if(LddAvlValueID == DCM_AVAIL_ID)
    {
      /* @Trace: Dcm_SUD_API_30397 */
      /* Total response = Num of PIDs + Number of FF + (Number of PIDs) * 4 */
      LusRespLength = 
        (((uint16) LucPIDCount << DCM_ONE) + ((uint16) LucPIDCount << DCM_TWO));

      pMsgContext->resDataLen = LusRespLength;
      Dcm_GblAvailabilityPIDFlag = DCM_FALSE;
    }
    /* Validate DCM_DEM_PID for response length */
    else if((LddAvlValueID == DCM_OTHER_PID) || (LddAvlValueID == DCM_TWO_PID))
    {
      /* @Trace: Dcm_SUD_API_30398 */
      LucSID = DCM_TWO;

      /* Get the response length of requested PIDs */
      LddReturnValue = Dcm_DspGetSizeOfIDS(DCM_GET_PID, LucPIDCount,
        &LusRespLength, LpReqResData, LucSID);

      /* Update Response length */
      pMsgContext->resDataLen = LusRespLength;
    }
    else
    {
      /* @Trace: SWS_Dcm_00972 */
      /* @Trace: Dcm_SUD_API_30442 */
	  /* AVAIL_ID + PID no response */ 
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
      LddReturnValue = E_NOT_OK;
    }

    /*
     Check if the response buffer is capable of accommodating the
     complete response at once
    */
    if((LddAvlValueID != DCM_NOT_CONFIG_ID) && (LddReturnValue == E_OK))
    {
      /* Check Response length */
      if(LusRespLength <= (pMsgContext->resMaxDataLen))
      {
        /* @Trace: Dcm_SUD_API_30400 */
        LddReturnValue = E_OK;

        /* @Trace: SWS_Dcm_00973 SWS_Dcm_00974 */
        /* Set the fill bytes to 0x00 */
        for (uint8 idx = DCM_ZERO; idx < LusRespLength; idx++)
        {
          pMsgContext->resData[idx] = DCM_ZERO;
        }
      }
      else
      {
        /* @Trace: Dcm_SUD_API_30402 */
        /* Update the NRC if the response length is greater than the response
         * buffer size and DCM_PAGEDBUFFER_ENABLED is not enabled */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;

        /* Set flag to go to end */
        LddReturnValue = E_NOT_OK;
      }

      /* For non paged response */
      if(LddReturnValue == E_OK)
      {
        /* @Trace: Dcm_SUD_API_30403 */
        LpTxBuffer = pMsgContext->resData;
        LpTxBufferIndex = DCM_ZERO;

        /* Load with zero */
        LucPIDIndex_1 = DCM_ZERO;

        for(LucPIDIndex = DCM_ZERO;
          ((LucPIDIndex < LucPIDCount) && (LddReturnValue == E_OK));
            LucPIDIndex++)
        {
          /* @Trace: Dcm_SUD_API_30404 */
          /* Get the PID value from the request buffer */
          LucPIDValue = LpReqResData[LucPIDIndex_1];

          /* Get the IDIndex for the PID */
          (void) Dcm_GetIDIndex(DCM_GET_PID, LucPIDValue, &LucIDIndex);

          /* For DCM_AVAIL_ID */
          if(LddAvlValueID == DCM_AVAIL_ID)
          {
            /* @Trace: Dcm_SUD_API_30405 */
            /* Update PID value to TX buffer*/
            LpTxBuffer[LpTxBufferIndex] = LucPIDValue;

            /* update Freezeframe Record number */
            LpTxBuffer[LpTxBufferIndex + 1U] = LpReqResData[LucPIDIndex_1 + DCM_ONE];


            /* @Trace: SWS_Dcm_00284 */
            /* Get All Availability list of 4 bytes */
            LddReturnValue = Dcm_DspGetConfigIDS(
              LucPIDValue, DCM_GET_PID, &LpTxBuffer[LpTxBufferIndex + 2U], &LucSizeOfPID);

            /* Check return value */
            if(LddReturnValue == E_OK)
            {
              /* @Trace: Dcm_SUD_API_30407 */
              LpTxBufferIndex = LpTxBufferIndex + 6U;

              /* update response length 6 = PID + FF + 4 Data */
              Dcm_GblAvailabilityPIDFlag = DCM_TRUE;
            }
            else
            {
              /* @Trace: Dcm_SUD_API_30406 */
              LpTxBufferIndex = LpTxBufferIndex + 2U;

              /* Update Response length */
              LusRespLength = LusRespLength - DCM_SIX;
              pMsgContext->resDataLen = LusRespLength;
            }
          }
          else if((LddAvlValueID == DCM_OTHER_PID) ||
            (LddAvlValueID == DCM_TWO_PID))
          {
            if((LucPIDValue == DCM_TWO) &&
               (Dcm_GaaPIDConfig[LucIDIndex].ucPidService == DCM_SERVICE_02))
            {
              /* @Trace: Dcm_SUD_API_30408 */
              /* Get Freezeframe Record number */
              LucFreezeFrameRecord = LpReqResData[LucPIDIndex_1 + DCM_ONE];

              /* @Trace: SWS_Dcm_00279 */
              LddReturnValue = IDem_DcmGetDTCOfOBDFreezeFrame(
                LucFreezeFrameRecord, 
              &Dcm_GunDTC.ulLongReg32, DEM_DTC_FORMAT_OBD);

              if(LddReturnValue == E_OK)
              {
                /* @Trace: Dcm_SUD_API_30409 */
                /* Update PID value to TX buffer*/
                LpTxBuffer[LpTxBufferIndex] = LucPIDValue;

                LpTxBufferIndex++;
                /* update Freezeframe Record number */
                LpTxBuffer[LpTxBufferIndex] = LucFreezeFrameRecord;

                /* Increment pointer */
                LpTxBufferIndex++;
                /* DTC High Byte */
                LpTxBuffer[LpTxBufferIndex] = Dcm_GunDTC.ddByte.ucMidHiByte;

                /* Increment pointer */
                LpTxBufferIndex++;

                /* DTC Middle Byte */
                LpTxBuffer[LpTxBufferIndex] = Dcm_GunDTC.ddByte.ucMidLowByte;

                /* Increment pointer */
                LpTxBuffer = &LpTxBuffer[1u];
                LpTxBufferIndex++;
              }
              /* @Trace: SWS_Dcm_01061 */
              else
              {
                /* @Trace: Dcm_SUD_API_30410 */
                /* Update PID value to TX buffer*/
                LpTxBuffer[LpTxBufferIndex] = LucPIDValue;

                /* Increment pointer */
                LpTxBufferIndex ++;

                 /* Update Freezeframe Record number */
                LpTxBuffer[LpTxBufferIndex] = LucFreezeFrameRecord;

                /* Increment pointer */
                LpTxBufferIndex ++;

                /* DTC High Byte */
                LpTxBuffer[LpTxBufferIndex] = DCM_ZERO;

                /* Increment pointer */
                LpTxBufferIndex ++;

                /* DTC Middle Byte */
                LpTxBuffer[LpTxBufferIndex] = DCM_ZERO;

                /* Increment pointer */
                LpTxBufferIndex++;
              }
            }
            else /* OTHER PIDS */
            {
              if((Dcm_GaaPIDConfig[LucIDIndex].ucPidService == DCM_SERVICE_02) ||
                (Dcm_GaaPIDConfig[LucIDIndex].ucPidService == DCM_SERVICE_01_02))
              {
                /* @Trace: Dcm_SUD_API_30411 */
                /* Get the Number of PID Data Configured */
                LucNumofData = Dcm_GaaPIDConfig[LucIDIndex].ucNumofPIDData;

                /* Get the PID Buffer Size */
                LucBufferSize = Dcm_GaaPIDConfig[LucIDIndex].ucPidBufferSize;

                LpDcmDspPidData = Dcm_GaaPIDConfig[LucIDIndex].pDcmDspPidData;

                /* Update PID value to TX buffer*/
                 LpTxBuffer[LpTxBufferIndex] = LucPIDValue;

                /* Increment pointer */
                LpTxBufferIndex++;

                /* update Freezeframe Record number */
                LpTxBuffer[LpTxBufferIndex] = LpReqResData[LucPIDIndex_1 + DCM_ONE];

                /* Increment pointer */
                LpTxBufferIndex++;

                for(LucCount = DCM_ZERO;LucCount < LucNumofData;LucCount++)
                {
                  /* @Trace: Dcm_SUD_API_30412 */
                  LucDataElementIndex = LpDcmDspPidData->ucPIDDataElementIndex;

                  /* @Trace: SWS_Dcm_00286 */
                  LddReturnValue = IDem_DcmReadDataOfOBDFreezeFrame(
                    LucPIDValue, LucDataElementIndex,
                    &LucDestBuffer[DCM_ZERO], &LucBufferSize);

                  /* Increment pointer */
                  LpDcmDspPidData = &LpDcmDspPidData[1u];

                  if(LddReturnValue == E_OK)
                  {
                    /* @Trace: SWS_Dcm_00287 */
                    /* @Trace: Dcm_SUD_API_30413 */
                    for(LulCount2 = DCM_ZERO;LulCount2 < LucBufferSize; LulCount2++)
                    {
                      /* @Trace: Dcm_SUD_API_30416 */
                      LpTxBuffer[LpTxBufferIndex] = LucDestBuffer[LulCount2];

                      /* Increment pointer */
                      LpTxBufferIndex++;
                    }
                  }
                  else
                  {
                    /* @Trace: Dcm_SUD_API_30414 */
                    /* Reset pointer to initial position before reading PID value */
                    LddReturnValue = E_OK;
                    break;
                  }

                  /* Checking if reading whole PID is finish completely */
                  if ((LucCount == (LucNumofData - DCM_ONE)) &&
                      (LulCount2 == LucBufferSize))
                  {
                    /* @Trace: Dcm_SUD_API_30417 */
                    isAtleastOnePIDSp = DCM_TRUE;
                  }
                }
              }

              /* @Trace: SWS_Dcm_01252 SWS_Dcm_01253 SWS_Dcm_01254 */
              if ((DCM_FALSE == isAtleastOnePIDSp) && 
                (LucPIDIndex == (LucPIDCount - DCM_ONE)))
              {
                /* @Trace: Dcm_SUD_API_30419 */
                isNoSendResp = DCM_TRUE;
              }
            }
          }
          else
          {
            /* To avoid QAC warning */
          }

          /* Increment by two */
          LucPIDIndex_1 += DCM_TWO;
        }

        if(Dcm_GblAvailabilityPIDFlag == DCM_FALSE)
        {
          /* @Trace: Dcm_SUD_API_30421 */
          Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_TRUE;
        }
      } /* End of non paged response */
    }
    else
    {
      /* @Trace: Dcm_SUD_API_30399 */
      Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30395 */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }

  /* @Trace: Dcm_SUD_API_30423 Dcm_SUD_API_30424 */
  /* Send response from main function */
  Dcm_GblSendResponse = (DCM_TRUE == isNoSendResp) ? DCM_FALSE : DCM_TRUE;

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return requestResult;
}
#endif /* (DCM_OBDREGPOWERTRAINFREEZEFRAMEDATA_SERVICE == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DcmOBDGetDTC                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is internal function that provides OBD service **
**                        0x03, 0x07, 0x0A                                    **
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
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GddNegRespError, Dcm_GpMsgContext,              **
**                        Dcm_GpReqResData, Dcm_PrtclTxBufStatus.             **
**                        Function(s) invoked : Dcm_DemGetNumberOfOBDDTC      **
**                        Dcm_ExternalProcessingDone,                         **
**                        Dcm_ExternalSetNegResponse                          **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04129 SRS_Diag_04161 */
/* polyspace-begin MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if ((DCM_OBD_GETDTC_03_SERVICE == STD_ON) \
     || (DCM_OBD_GETDTC_07_SERVICE == STD_ON) \
     || (DCM_OBD_GETDTC_0A_SERVICE == STD_ON))
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDGetDTC(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
/* polyspace-end MISRA2012:8.13 [Justified:Low] Justify with annotations */
{
  Dem_DTCOriginType LddDTCOrigin;
  Std_ReturnType LddRetrunSetFilter;
  uint8 LucSID;
  uint8 LucStatusMask;

  /* Initialize variable with DCM_ZERO*/
  LucStatusMask = DCM_ZERO;

  /* MISRA Rule         : 12.7
     Message            : Bitwise operators shall not be applied to operands
                          whose underlying type is signed.
     Reason             : Bitwise operators used to achieve better
                          throughput.
     Verification       : However, part of the code is verified
                          manually and it is not having any impact.
  */
  /* Get SID */
  LucSID = ((Dcm_GstMsgContext.idContext) & ~(DCM_RESPONSE_ID));

  /* Check for the validity of length */
  if(pMsgContext->reqDataLen > DCM_ZERO)
  {
    /* @Trace: Dcm_SUD_API_30277 */
    /* Report the Condition not correct NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }

  if(Dcm_GddNegRespError != DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT)
  {
    /* @Trace: SWS_Dcm_00077 */
    /* @Trace: Dcm_SUD_API_30278 */
    /* Update DTC origin for 03 and 07 */
    LddDTCOrigin = DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY;

    switch(LucSID)
    {
      /* Check if the sub function requested is 0x08 */
      case DCM_OBD_GETDTC_03:
          /* @Trace: Dcm_SUD_API_30279 */
          /* Status Mask update as eight for OBD service 01 */
          LucStatusMask = DCM_EIGHT;
          break;

      case DCM_OBD_GETDTC_07:
          /* @Trace: Dcm_SUD_API_30280 */
          /* Status Mask update as eight for OBD service 07 */
          LucStatusMask = DCM_FOUR;
          break;

      case  DCM_OBD_GETDTC_0A:
          /* @Trace: Dcm_SUD_API_30281 */
          /* Status Mask update as eight for OBD service 0A */
          LucStatusMask = DCM_ZERO;

          /* Update DTC origin for  0A */
          /* @Trace: SWS_Dcm_00077 */
          LddDTCOrigin = DEM_DTC_ORIGIN_PERMANENT_MEMORY;
          break;

      default:
        /* No action in this case */
        break;
    }

    /* @Trace: SWS_Dcm_00835 */
    /* Invoke Dem API to set DTC filter */
    LddRetrunSetFilter = IDem_SetDTCFilter(
      LucStatusMask, DEM_DTC_FORMAT_OBD, LddDTCOrigin, 
      DCM_FALSE, DEM_SEVERITY_NO_SEVERITY, DCM_FALSE, &Dcm_GddNegRespError);

    /* Check return value */
    if(LddRetrunSetFilter == E_OK)
    {
      /* @Trace: Dcm_SUD_API_30284 */
      Dcm_GpReqResData = pMsgContext->resData;

      /* @Trace: SWS_Dcm_00289 SWS_Dcm_00330 SWS_Dcm_00412 */
      Dcm_DemGetNumberOfOBDDTC();
    }
  }

  #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
  if(Dcm_DspSerPgStatus.ucPagingStarted == DCM_FALSE)
  #endif
  {
    if(Dcm_PrtclTxBufStatus.ucReportOBDDtc == DCM_FALSE)
    {
      /* @Trace: Dcm_SUD_API_30285 */
      /* Send response from main function */
      Dcm_GblSendResponse = DCM_TRUE;
    }
  }

  /* @Trace: Dcm_SUD_API_30286 */
  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return E_OK;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmOBDClrResetEmissionDiagInfo                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is internal function that provides OBD service **
**                        0x04                                                **
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
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_PrtclTxBufStatus                                **
**                        Function(s) invoked : Dcm_ExternalSetNegResponse,   **
**                        Dem_ClearDTC, Dcm_ExternalProcessingDone            **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04058 SRS_Diag_04129 SRS_Diag_04161 SRS_Diag_04222 */
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_OBD_CLRRESET_EMISSION_DIAGINFO_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDClrResetEmissionDiagInfo(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_00246 */
  Std_ReturnType LddReturnValue = E_OK;
  Dcm_GddNegRespError = DCM_POS_RESP;

  Dcm_PrtclTxBufStatus.ucOBDClearDTCStatus = DCM_FALSE;
  Dcm_GblSendResponse = DCM_TRUE;

  /* Check for the validity of length */
  if (DCM_ZERO != pMsgContext->reqDataLen)
  {
    /* @Trace: Dcm_SUD_API_30269 */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    LddReturnValue = E_NOT_OK;
  }

  if (E_OK == LddReturnValue)
  {
    /* @Trace: SWS_Dcm_00004 */
    /* @Trace: Dcm_SUD_API_30270 */
    (void) IDem_SelectDTC(DEM_DTC_GROUP_EMISSION_REL_DTCS_WWH_OBD, 
      DEM_DTC_FORMAT_OBD, DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY);

    /* @Trace: SWS_Dcm_01401 */
    LddReturnValue = IDem_ClearDTC();

    switch (LddReturnValue)
    {
      /* @Trace: SWS_Dcm_00413 */
      case E_OK:
        /* @Trace: Dcm_SUD_API_30271 */
        pMsgContext->resDataLen = DCM_ZERO;
        break;

      /* @Trace: SWS_Dcm_00703 */
      case DEM_PENDING:
        /* @Trace: Dcm_SUD_API_30272 */
        Dcm_PrtclTxBufStatus.ucOBDClearDTCStatus = DCM_TRUE;
        Dcm_GblSendResponse = DCM_FALSE;
        break;

      /* @Trace: SWS_Dcm_00704 SWS_Dcm_00967 SWS_Dcm_01067 */
      case DEM_CLEAR_BUSY:
      case DEM_CLEAR_FAILED:
      case DEM_CLEAR_MEMORY_ERROR:
        /* @Trace: Dcm_SUD_API_30273 */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
        break;

      default:
        /* @Trace: Dcm_SUD_API_30274 */
        Dcm_GddNegRespError = DCM_E_GENERALPROGRAMMINGFAILURE;
        break;
    }
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return LddReturnValue;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmOBDReqOnboadMonitorResult                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to provide Request On-Board   **
**                        Monitoring Test-results for Specific Monitored      **
**                        Systems i.e. OBD service 0x06                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError            **
**                        Functions Invoked : None                            **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04129 SRS_Diag_04161 */
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDReqOnboadMonitorResult(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer;
  uint16 LusRespLength;
  uint8 LucOBDMIDCount;

  /* Get the pointer to the request data buffer */
  LpReqResData = pMsgContext->reqData;
  LpTxBuffer = pMsgContext->resData;
  LusRespLength = DCM_ZERO;

  /* Update PIDCount with zero */
  LucOBDMIDCount = DCM_ZERO;

  /* Check for the validity of length */
  if(pMsgContext->reqDataLen < DCM_ONE)
  {
    /* @Trace: Dcm_SUD_API_30363 */
    /* Report the Condition not correct NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }

  /* @Trace: SWS_Dcm_00414 */
  /* equest for supported OBDMIDs may contain up to 6 'availability OBDMIDs' */
  if((pMsgContext->reqDataLen > DCM_ZERO) &&
    (pMsgContext->reqDataLen < DCM_SEVEN))
  {
    /* @Trace: Dcm_SUD_API_30364 */
    /* Update the PIDs are exist in the request buffer */
    LucOBDMIDCount = (uint8)pMsgContext->reqDataLen;
  }

  if(LucOBDMIDCount > DCM_ZERO)
  {
    /* @Trace: Dcm_SUD_API_30365 */
    Dcm_InternalOBDReqOnboadMonitorResultCall(
      LpReqResData, LpTxBuffer, LucOBDMIDCount, &LusRespLength);

    pMsgContext->resDataLen = LusRespLength;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30366 */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return E_OK;
}

/*******************************************************************************
** Function Name        : Dcm_InternalOBDReqOnboadMonitorResultCall           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to provide Request On-Board   **
**                        Monitoring Test-results for Specific Monitored      **
**                        Systems i.e. OBD service 0x06. This function is     **
**                        accessed from OBD and ReaddatabyID service          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GpMsgContext,              **
**                        Dcm_GddNegRespError, Dcm_DspSerPgStatus,            **
**                        Dcm_GucPIDCount, Dcm_GaaTidUaSid.                   **
**                        Function(s) invoked : Dcm_DspGetAvailibiltyIDStatus,**
**                        Dcm_DspGetSizeOfIDS, Dcm_DsdStartPagedProcessing,   **
**                        Dcm_DspReadOBD_AvlInfo, Dcm_GetIDIndex,             **
**                        Dcm_GaaTidUaSid                                     **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(void, DCM_CODE) Dcm_InternalOBDReqOnboadMonitorResultCall(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer, uint8 LucOBDMIDCount,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpResLength)
{
  /* MISRA Rule         : 18.4
     Message            : Unions shall not be used.
     Reason             : For optimization.
     Verification       : However, part of the code is verified
                          manually and it is not having any impact.
  */
  Tun_DcmWord16 LunDcmWord16;
  Std_ReturnType LddReturnValue;
  uint16 LusTestval;
  uint16 LusMinlimit;
  uint16 LusMaxlimit;
  uint16 LusRespLength;
  uint16 LusRespLengthRcvd;
  uint8 LucOBDMIDValue;
  uint8 LucTID;
  uint8 LucUaSid;
  uint8 LucMix_DemRPort;
  uint8 LucIndex;
  uint8 LddReturnStatusValue;
  uint8 LucNumberOfTIDs = DCM_ZERO;
  LusRespLength = DCM_ZERO;

  /* Update return value E_OK */
  LddReturnValue = E_OK;
  LucMix_DemRPort = DCM_SIX;
  Dcm_GblAvailabilityPIDFlag = DCM_TRUE;

  /* Get the PID value from the request buffer */
  LucOBDMIDValue = LpReqResData[DCM_ZERO];

  /* To find whether the PIDs belongs to Availability PIDs or Dem or RPort */
  LddReturnStatusValue = Dcm_DspGetAvailibiltyIDStatus(DCM_GET_OBDMID,
    LpReqResData, LucOBDMIDCount, LucMix_DemRPort);

  /* Validate DCM_AVAIL_ID for response length */
  if(LddReturnStatusValue == DCM_AVAIL_ID)
  {
    /* @Trace: Dcm_SUD_API_30369 */
    /* Total response = Number of PIDs(subfunction) + (Number of PIDs) * four */
    LusRespLength = (uint16) ((uint16) LucOBDMIDCount * DCM_FIVE);
  }
  /* @Trace: SWS_Dcm_00956 */
  /* For DCM_R_PORT_PID and  DCM_DEM_PID, 
   * not allowed multiple non-availability OBDMIDs */
  else if((LddReturnStatusValue == DCM_OTHER_PID) && (DCM_ONE == LucOBDMIDCount))
  {
    /* @Trace: SWS_Dcm_00958 */
    /* @Trace: Dcm_SUD_API_30370 */
    LddReturnValue = Dem_DcmGetNumTIDsOfOBDMID(LucOBDMIDValue, &LucNumberOfTIDs);
    LusRespLength = DCM_ONE + (DCM_EIGHT * (uint16) LucNumberOfTIDs);
  }
  else
  {
    /* @Trace: SWS_Dcm_00945 */
    LddReturnValue = E_NOT_OK;
  }

  if((LddReturnStatusValue != DCM_NOT_CONFIG_ID) && (LddReturnValue == E_OK))
  {
    /* Check if the response buffer is capable of accommodating the complete
     * response at once */
    if(LusRespLength <= (Dcm_GstMsgContext.resMaxDataLen))
    {
      /* @Trace: Dcm_SUD_API_30373 */
      LddReturnValue = E_OK;
    }
    else
    {
      /* Update Response length */
      *LpResLength = LusRespLength;

      /* Check Page buffer enabled */
      #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
      /* Application not supported Paging */
      if(LddReturnStatusValue == DCM_AVAIL_ID)
      {
        uint32 maxRespLen = Dcm_PagedBuffer_GetMaxRespLen(&Dcm_GstMsgContext);

        if (LusRespLength <= maxRespLen)
        {
          /* @Trace: Dcm_SUD_API_30377 */
          /* Start the paged processing */
          Dcm_DsdStartPagedProcessing(&Dcm_GstMsgContext);
          /* Update PID count */
          Dcm_GucPIDCount = LucOBDMIDCount;
        }
        else
        {
          /* @Trace: Dcm_SUD_API_30378 */
          Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
        }
      }
      else
      #endif
      {
        /* @Trace: Dcm_SUD_API_30375 */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
      }

      /* Set flag to go to end */
      LddReturnValue = E_NOT_OK;
    }

    /* For non paged response */
    if(LddReturnValue == E_OK)
    {
      /* For DCM_AVAIL_ID */
      if(LddReturnStatusValue == DCM_AVAIL_ID)
      {
        /* @Trace: Dcm_SUD_API_30379 */
        LusRespLengthRcvd = (uint16)Dcm_DspReadOBD_AvlInfo(LpReqResData,
          LpTxBuffer, LusRespLength, LucOBDMIDCount, DCM_GET_OBDMID);
      }
      else
      {
        /* @Trace: SWS_Dcm_00958 */
        /* @Trace: Dcm_SUD_API_30380 */
        LddReturnValue = Dem_DcmGetNumTIDsOfOBDMID(
          LucOBDMIDValue, &LucNumberOfTIDs);

        /* Trace: DEM_OBD_06_02 */
        if (LucNumberOfTIDs == DCM_ZERO)
        {
          LddReturnValue = E_NOT_OK;
          /* Update NRC */
          Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
        }

        /* Update PID value to TX buffer*/
        /* polyspace +2 MISRA-C3:17.8 [Justified:Low] Justify with annotations */
        LpTxBuffer[DCM_ZERO] = LucOBDMIDValue;
        LpTxBuffer = &LpTxBuffer[DCM_ONE];

        if((LddReturnValue == E_OK) &&
           (LucNumberOfTIDs > DCM_ZERO) && (LucNumberOfTIDs < DCM_MAXVALUE))
        {
          /* @Trace: Dcm_SUD_API_30381 */
          /* After remove availability ids, the maximum value of LucNumberOfTIDs is 248 */
          for(LucIndex = DCM_ZERO; LucIndex < LucNumberOfTIDs; LucIndex++)
          {
            /* @Trace: Dcm_SUD_API_30383 */
            LddReturnValue = Dem_DcmGetDTRData(
              LucOBDMIDValue, LucIndex, &LucTID, &LucUaSid, 
              &LusTestval, &LusMinlimit, &LusMaxlimit);
            /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
            if(LddReturnValue == E_OK)
            {
              /* @Trace: Dcm_SUD_API_30384 */
              /* update TID */
              LpTxBuffer[DCM_ZERO] = LucTID;
              /* update UaSid */
              LpTxBuffer[DCM_ONE] = LucUaSid;

              /* Update Test value */
              LunDcmWord16.usWordReg16 = LusTestval;
              /* update Test Value Hi byte */
              LpTxBuffer[DCM_TWO] = LunDcmWord16.ddByte.ucMsByte;
              /* update Test Value Lo byte */
              LpTxBuffer[DCM_THREE] = LunDcmWord16.ddByte.ucLsByte;

              /* Update Min Limit */
              LunDcmWord16.usWordReg16 = LusMinlimit;
              /* update Test Value Hi byte */
              LpTxBuffer[DCM_FOUR] = LunDcmWord16.ddByte.ucMsByte;
              /* update Test Value Lo byte */
              LpTxBuffer[DCM_FIVE] = LunDcmWord16.ddByte.ucLsByte;

              /* Update Max Limit */
              LunDcmWord16.usWordReg16 = LusMaxlimit;
              /* update Test Value Hi byte */
              LpTxBuffer[DCM_SIX] = LunDcmWord16.ddByte.ucMsByte;
              /* update Test Value Lo byte */
              LpTxBuffer[DCM_SEVEN] = LunDcmWord16.ddByte.ucLsByte;

              /* polyspace +1 MISRA-C3:17.8 [Justified:Low] Justify with annotations */
              LpTxBuffer = &LpTxBuffer[DCM_EIGHT];

              /* To indicate No NRC */
              Dcm_GddNegRespError = DCM_POS_RESP;
            }
            else if(LddReturnValue == DEM_PENDING)
            {
              /* @Trace: Dcm_SUD_API_30385 */
              Dcm_GddNegRespError = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
            }
            else
            {
              /* @Trace: Dcm_SUD_API_30386 */
              /* Update NRC */
              Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
            }
            /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */

            /* Break the loop if error occur */
            if (DCM_POS_RESP != Dcm_GddNegRespError)
            {
              /* @Trace: Dcm_SUD_API_30450 */
              break;
            }
          }
        }

        LusRespLengthRcvd = LusRespLength;
      }

      if((LddReturnValue  != E_NOT_OK) && (LddReturnValue  != DEM_PENDING))
      {
        /* @Trace: Dcm_SUD_API_30387 */
        /* To indicate No NRC */
        Dcm_GddNegRespError = DCM_POS_RESP;
        /* Update Response length */
        *LpResLength = LusRespLengthRcvd;

        if(Dcm_GblAvailabilityPIDFlag == DCM_FALSE)
        {
          /* @Trace: Dcm_SUD_API_30388 */
           Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_TRUE;
        }
      }
    } /* End of non paged response */
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30372 */
    /* Update NRC */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmOBDReqCtlrOnboadSystem                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function used to Request Control of On-Board   **
**                        System, Test or Component i.e. provide OBD service  **
**                        0x08                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_DspSerPgStatus,            **
**                        Dcm_GddNegRespError, Dcm_GucPIDCount,               **
**                        Dcm_GaaRequestControlConfig.                        **
**                        Function(s) invoked : Dcm_DspGetAvailibiltyIDStatus,**
**                        Dcm_DsdStartPagedProcessing,                        **
**                        Dcm_DspReadOBD_AvlInfo, Dcm_GetIDIndex,             **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04129 SRS_Diag_04161 */
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDReqCtlrOnboadSystem(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpTxBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpOutBuffer;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpInBuffer;

  uint16 LusRespLength = DCM_ZERO;
  uint8 LucTIDCount = DCM_ZERO;
  uint8 LucTIDIndex1 = DCM_ZERO;

  uint8 LucIndex;
  uint8 LucTIDValue;
  uint8 LucMix_DemRPort;
  uint8 LddReturnStatusValue;
  Std_ReturnType LddReturnValue;

  /* Get the pointer to the request data buffer */
  LpReqResData = pMsgContext->reqData;

  /* Reset error code and set OBD flag */
  Dcm_GblAvailabilityPIDFlag = DCM_TRUE;
  Dcm_GddNegRespError = DCM_POS_RESP;

  /* Check for the validity of length */
  if(pMsgContext->reqDataLen < DCM_ONE)
  {
    /* @Trace: Dcm_SUD_API_30319 */
    /* Report the Condition not correct NRC */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30320 */
    LucTIDCount = DCM_ONE;
    LucMix_DemRPort = DCM_EIGHT;

    /* To find whether the PIDs belongs to Availability PIDs or Dem or RPort */
    LddReturnStatusValue = Dcm_DspGetAvailibiltyIDStatus(
      DCM_GET_TID, LpReqResData, LucTIDCount, LucMix_DemRPort);

    if (LddReturnStatusValue == DCM_OTHER_PID)
    {
      /* @Trace: Dcm_SUD_API_30321 */
      LucTIDValue = LpReqResData[DCM_ZERO];
      LddReturnValue = Dcm_GetIDIndex(DCM_GET_TID, LucTIDValue, &LucTIDIndex1);

      if(LddReturnValue == E_OK)
      {
        if (pMsgContext->reqDataLen != (uint32) (DCM_ONE + \
          (uint32) Dcm_GaaRequestControlConfig[LucTIDIndex1].ucRequestControlInBufferSize))
        {
          /* @Trace: Dcm_SUD_API_30322 */
          /* Report the invalid length NRC */
          Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        else
        {
          /* @Trace: Dcm_SUD_API_30323 */
          LucTIDCount = DCM_ONE;
        }
      }
    }
    else
    {
      if(pMsgContext->reqDataLen > DCM_SIX)
      {
        /* @Trace: Dcm_SUD_API_30325 */
        /* Report the invalid length NRC */
        Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_30324 */
        LucTIDCount = (uint8) pMsgContext->reqDataLen;
      }
    }

    /* Validate PIDs range */
    if(Dcm_GddNegRespError == DCM_POS_RESP)
    {
      /* @Trace: Dcm_SUD_API_30327 */
      LucMix_DemRPort = DCM_EIGHT;

      /* To find whether the PIDs belongs to Availability PIDs or Dem or RPort */
      LddReturnStatusValue = Dcm_DspGetAvailibiltyIDStatus(
        DCM_GET_TID, LpReqResData, LucTIDCount, LucMix_DemRPort);

      /* Validate DCM_AVAIL_ID for response length */
      if(LddReturnStatusValue == DCM_AVAIL_ID)
      {
        /* @Trace: Dcm_SUD_API_30328 */
        /* Total response = Number of PIDs + (Number of PIDs) * four
         * four: Each response supported TIDs is 
         * [supported TID, Data A, Data B, Data C, Data D]
         */
        LusRespLength = (uint16) ((uint16) LucTIDCount * DCM_FIVE);
      }
      /* Validate DCM_DEM_PID for response length */
      else if(LddReturnStatusValue == DCM_OTHER_PID)
      {
        /* @Trace: Dcm_SUD_API_30329 */
        /* Total response = NPID */
        LusRespLength = (uint16) ((uint16) LucTIDCount + \
          Dcm_GaaRequestControlConfig[LucTIDIndex1].ucRequestControlOutBufferSize);
      }
      else
      {
        /* To avoid QAC warning */
      }

      /* @Trace: SWS_Dcm_00947 */
      if((LddReturnStatusValue != DCM_NOT_CONFIG_ID))
      {
        /*
         * Check if the response buffer is capable of accommodating the
         * complete response at once
         */
        if(LusRespLength <= (pMsgContext->resMaxDataLen))
        {
          /* @Trace: Dcm_SUD_API_30331 */
          LddReturnValue = E_OK;
        }
        else
        {
          #if(DCM_PAGEDBUFFER_ENABLED == STD_ON)
          /* Application not supported Paging */
          if (LddReturnStatusValue == DCM_AVAIL_ID)
          {
            uint32 maxRespLen = Dcm_PagedBuffer_GetMaxRespLen(pMsgContext);

            if (LusRespLength <= maxRespLen)
            {
              /* @Trace: Dcm_SUD_API_30334 */
              /* Start the paged processing */
              Dcm_DsdStartPagedProcessing(pMsgContext);

              /* Update PID count */
              Dcm_GucPIDCount = LucTIDCount;
            }
            else
            {
              /* @Trace: Dcm_SUD_API_30335 */
              Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
            }
          }
          else
          #endif
          {
            /* @Trace: Dcm_SUD_API_30332 */
            Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
          }

          /* Set flag to go to end */
          LddReturnValue = E_NOT_OK;
        }

        /* For non paged response */
        if(LddReturnValue == E_OK)
        {
          /* @Trace: Dcm_SUD_API_30337 */
          LpTxBuffer = pMsgContext->resData;

          /* @Trace: SWS_Dcm_00948 */
          for(LucIndex = DCM_ZERO;LucIndex < LusRespLength; LucIndex++)
          {
            /* @Trace: Dcm_SUD_API_30338 */
            LpTxBuffer[LucIndex] = DCM_ZERO;
          }

          /* @Trace: SWS_Dcm_00418 */
          if(LddReturnStatusValue == DCM_AVAIL_ID)
          {
            /* @Trace: Dcm_SUD_API_30339 */
            LusRespLength = (uint16) Dcm_DspReadOBD_AvlInfo(
              LpReqResData, LpTxBuffer, LusRespLength, LucTIDCount, DCM_GET_TID);
          }
          /* @Trace: SWS_Dcm_00419 */
          else if(LddReturnStatusValue == DCM_OTHER_PID)
          {
            if(LucTIDCount == DCM_ONE)
            {
              /* @Trace: Dcm_SUD_API_30341 */
              /* Get the PID value from the request buffer */
              LucTIDValue = LpReqResData[DCM_ZERO];

              /* Update PID value to TX buffer*/
              LpTxBuffer[DCM_ZERO] = LucTIDValue;

              LddReturnValue = Dcm_GetIDIndex(
                DCM_GET_TID, LucTIDValue, &LucTIDIndex1);

              if(LddReturnValue == E_OK)
              {
                /* @Trace: SWS_Dcm_00420 */
                /* @Trace: Dcm_SUD_API_30342 */
                /* Initialize buffer */
                LpOutBuffer = &LpTxBuffer[DCM_ONE];
                LpInBuffer = pMsgContext->reqData;
                LddReturnValue = Dcm_GaaRequestControlConfig[LucTIDIndex1].
                  pReqControlFnc(LpOutBuffer, LpInBuffer);

                /* @Trace: SWS_Dcm_01192 */
                if (LddReturnValue != E_OK)
                {
                  /* @Trace: Dcm_SUD_API_30343 */
                  /* Update NRC */
                  /* polyspace +1 MISRA2012:2.2 [Justified:Low] Justify with annotations */
                  Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
                }
              }
            }
            else
            {
              /* @Trace: Dcm_SUD_API_30340 */
              /* For Condition not correct */
              LddReturnValue  = E_NOT_OK;
            }
          }
          else
          {
            /* To avoid QAC warning */
          }

          if (E_OK == LddReturnValue)
          {
            /* @Trace: Dcm_SUD_API_30344 */
            /* To indicate No NRC */
            Dcm_GddNegRespError = DCM_POS_RESP;
            pMsgContext->resDataLen = LusRespLength;

            if(Dcm_GblAvailabilityPIDFlag == DCM_FALSE)
            {
              /* @Trace: Dcm_SUD_API_30345 */
               Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_TRUE;
            }
          }
          else
          {
            /* @Trace: Dcm_SUD_API_30346 */
            /* Update NRC */
            Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
          }
        } /* End of non paged response */
      }
      else
      {
        /* @Trace: Dcm_SUD_API_30330 */
        /* Update NRC :not configured or mixed AVAIL ID and PID */
        Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
      }
    }
    else
    {
      /* @Trace: Dcm_SUD_API_30326 */
      /* Update NRC */
      /* Do Nothing */
    }
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return E_OK;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmOBDRegVehicleInfo                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to get Vehicle information    **
**                          i.e. provides OBD service 0x09                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GddNegRespError           **
**                        Function(s) invoked :                               **
**                        Dcm_DcmOBDRegVehicleInfoCall                        **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04129 SRS_Diag_04161 */
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmOBDRegVehicleInfo(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pReqData = pMsgContext->reqData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer = pMsgContext->resData;
  Dcm_MsgLenType ReqLen = pMsgContext->reqDataLen;
  uint16 RespLen = DCM_ZERO;
  uint8 RespMaxLen = (uint8) pMsgContext->resMaxDataLen;
  uint8 VIDCount = DCM_ZERO;

  if (ReqLen < DCM_ONE)
  {
    /* @Trace: Dcm_SUD_API_30288 */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }

  if ((DCM_ZERO < ReqLen) && (ReqLen < DCM_SEVEN))
  {
    /* @Trace: Dcm_SUD_API_30289 */
    VIDCount = (uint8)pMsgContext->reqDataLen;
  }

  if (DCM_ZERO < VIDCount)
  {
    /* @Trace: Dcm_SUD_API_30291 */
    Dcm_DcmOBDRegVehicleInfoCall(
      pReqData, pTxBuffer, RespMaxLen, VIDCount, &RespLen);

    pMsgContext->resDataLen = RespLen;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30290 */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return E_OK;
}

/*******************************************************************************
** Function Name        : Dcm_DcmOBDRegVehicleInfoCall                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to get Vehicle information    **
**                        i.e. provides OBD service 0x09. This function is    **
**                        accessed from OBD service and ReaddatabyID service  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GpMsgContext               **
**                        Dcm_GddNegRespError, Dcm_DspSerPgStatus,            **
**                        Dcm_GucPIDCount, Dcm_GaaVehInfoConfig               **
**                        Function(s) invoked : Dcm_DspGetAvailibiltyIDStatus,**
**                        Dcm_DspGetSizeOfIDS, Dcm_DsdStartPagedProcessing,   **
**                        Dcm_DspReadOBD_AvlInfo, Dcm_GetIDIndex.             **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(void, DCM_CODE) Dcm_DcmOBDRegVehicleInfoCall(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pReqData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxBuffer,
  uint8 TxBufferSize,
  uint8 VIDCount,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) pRespLength)
{
  P2CONST(Dcm_VehInfoConfigType, AUTOMATIC, DCM_APPL_CONST) pVehInfoCfg;
  P2CONST(Dcm_VehInfoData, AUTOMATIC, DCM_APPL_CONST) pVehInfoDataCfg;

  Std_ReturnType RetVal = E_OK;
  uint16 RespLen;
  uint16 RespLenRcvd = DCM_ZERO;
  uint8 VIDValue;
  uint8 VIDIndex;
  uint8 VIDSize;
  uint8 idx;
  uint8 NODI;
  uint8 NowBufferSize;

  Dcm_GblAvailabilityPIDFlag = DCM_TRUE;

  /* It scans for all PIDs */
  /* To find whether the PIDs belongs to Availability PIDs or Dem or RPort */
  uint8 LucIdStatus = Dcm_DspGetAvailibiltyIDStatus(
    DCM_GET_VID, pReqData, VIDCount, DCM_NINE);

  if (LucIdStatus == DCM_AVAIL_ID)
  {
    /* @Trace: Dcm_SUD_API_30294 */
    /* Total response = Number of InfoTypes + (Number of InfoTypes) * four */
    RespLen = (uint16) VIDCount * DCM_FIVE;
  }
  else if (LucIdStatus == DCM_OTHER_PID)
  {
    /* @Trace: Dcm_SUD_API_30295 */
    /* Get the response length of requested InfoTypes */
    RetVal = Dcm_DspGetSizeOfIDS(
      DCM_GET_VID, VIDCount, &RespLen, pReqData, DCM_NINE);
  }
  else
  {
      /* AVAIL_ID + PID no response , nor configrued or mixed avail id and pid*/ 
      Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    /* To avoid QAC warning */
  }

  /* @Trace: SWS_Dcm_00949 */
  if ((LucIdStatus != DCM_NOT_CONFIG_ID) && (RetVal == E_OK))
  {
    if (RespLen <= Dcm_GstMsgContext.resMaxDataLen)
    {
      /* @Trace: Dcm_SUD_API_30297 */
      RetVal = E_OK;
    }
    else
    {
      *pRespLength = RespLen;

      #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if (LucIdStatus == DCM_AVAIL_ID)
      {
        uint32 maxRespLen = Dcm_PagedBuffer_GetMaxRespLen(&Dcm_GstMsgContext);

        if (RespLen <= maxRespLen)
        {
          /* @Trace: Dcm_SUD_API_30302 */
          Dcm_DsdStartPagedProcessing(&Dcm_GstMsgContext);
          Dcm_GucPIDCount = VIDCount;
        }
        else
        {
          /* @Trace: Dcm_SUD_API_30301 */
          Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
        }
      }
      else
      #endif
      {
        /* @Trace: Dcm_SUD_API_30299 */
        Dcm_GddNegRespError = DCM_E_RESPONSETOOLONG;
      }

      /* Set flag to go to end */
      RetVal = E_NOT_OK;
    }

    /* For non paged response */
    if (RetVal == E_OK)
    {
      /* @Trace: SWS_Dcm_00422 */
      if (LucIdStatus == DCM_AVAIL_ID)
      {
        /* @Trace: Dcm_SUD_API_30304 */
        RespLenRcvd = (uint16)Dcm_DspReadOBD_AvlInfo(
        pReqData, pTxBuffer, RespLen, VIDCount, DCM_GET_VID);
      }
      /* @Trace: SWS_Dcm_00423 */
      else if (LucIdStatus == DCM_OTHER_PID)
      {
        if (VIDCount == DCM_ONE)
        {
          /* @Trace: Dcm_SUD_API_30305 */
          VIDValue = pReqData[DCM_ZERO];
          RetVal = Dcm_GetIDIndex(DCM_GET_VID, VIDValue, &VIDIndex);

          if (RetVal == E_OK)
          {
            /* @Trace: Dcm_SUD_API_30307 */
            pVehInfoCfg = &Dcm_GaaVehInfoConfig[VIDIndex];
            pVehInfoDataCfg = pVehInfoCfg->pDcmVehInfoData;

            /* polyspace +1 MISRA-C3:13.3 MISRA-C3:17.8 [Justified:Low] Justify with annotations */
            (*pTxBuffer++) = VIDValue;

            NODI = pVehInfoCfg->ucNoOfVehInfoData;

            /* @Trace: SWS_Dcm_00684 */
            if (DCM_FALSE == pVehInfoCfg->blVehInfoNODIProvResp)
            {
              /* @Trace: Dcm_SUD_API_30308 */
              /* polyspace-begin MISRA-C3:17.8 [Justified:Low] Justify with annotations */
              /* polyspace +1 MISRA-C3:13.3 [Justified:Low] Justify with annotations */
              (*pTxBuffer++) = NODI;
              TxBufferSize -= DCM_TWO;
              /* polyspace-end MISRA-C3:17.8 [Justified:Low] Justify with annotations */
            }
            /* @Trace: SWS_Dcm_01167 */
            else
            {
              /* @Trace: Dcm_SUD_API_30309 */
              /* polyspace +1 MISRA-C3:17.8 [Justified:Low] Justify with annotations */
              TxBufferSize -= DCM_ONE;
            }

            for (idx = DCM_ZERO; idx < NODI; idx++)
            {
              /* @Trace: Dcm_SUD_API_30311 */
              NowBufferSize = TxBufferSize;
              RetVal = pVehInfoDataCfg->pGetVehInfoDataReadFun(
                DCM_INITIAL, pTxBuffer, &NowBufferSize);

              if (RetVal == E_OK)
              {
                /* @Trace: Dcm_SUD_API_30312 */
                /* polyspace +3 MISRA-C3:17.8 [Justified:Low] Justify with annotations */
                VIDSize = pVehInfoDataCfg->ucVehInfoBufSize;
                TxBufferSize -= VIDSize;
                pTxBuffer = &pTxBuffer[VIDSize];
                Dcm_GddNegRespError = DCM_POS_RESP;
              }
              else if (RetVal == DCM_E_PENDING)
              {
                /* @Trace: Dcm_SUD_API_30313 */
                Dcm_GddNegRespError = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
              }
              /* @Trace: SWS_Dcm_01191 */
              else
              {
                /* @Trace: Dcm_SUD_API_30314 */
                Dcm_GddNegRespError = DCM_E_SUBFUNCTIONNOTSUPPORTED;
              }

              if (DCM_POS_RESP != Dcm_GddNegRespError)
              {
                break;
              }

              pVehInfoDataCfg++;
            }
          }
        }
        else
        {
          /* @Trace: Dcm_SUD_API_30306 */
          RetVal = E_NOT_OK;
          Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
        }

        RespLenRcvd = RespLen;
      }
      else
      {
        /* To avoid QAC warning */
      }

      if ((E_NOT_OK != RetVal) && (RetVal != DCM_E_PENDING))
      {
        /* @Trace: Dcm_SUD_API_30316 */
        Dcm_GddNegRespError = DCM_POS_RESP;
        *pRespLength = RespLenRcvd;

        if (Dcm_GblAvailabilityPIDFlag == DCM_FALSE)
        {
          /* @Trace: Dcm_SUD_API_30317 */
          Dcm_GstMsgContext.msgAddInfo.suppressPosResponse = DCM_TRUE;
        }
      }
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_30296 */
    Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
  }
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
