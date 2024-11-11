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
**  SRC-MODULE: Dcm_Lib.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Libraries for specific service                                **
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
** 0.0.1     31-Dec-2019   SonDT1         AR440 Implementation                **
** 0.0.2     16-Aug-2020   HueKM          Fix defect and coding rules         **
** 0.0.3     13-Oct-2020   HueKM          Changes made as per #15766          **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_PCTypes.h"
#include "Dcm_Types.h"
#include "Dcm_Ram.h"
#include "Rte_Dcm_Type.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Config.h"
#include "Dcm_DspServices.h"
#include "Dcm_Lib.h"
#include "Dcm_Utils.h"

/*******************************************************************************
**                EXTERNAL FUNCTION DEFINITIONS                               **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_ChkSuppressPosResponse                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if need to suppress positive response in case **
**                        related communication control service is received   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : pRxData, MsgDataLen                                 **
**                                                                            **
** InOut Parameters     : None                                                **
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
/* @Trace: SWS_Dcm_00202 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_ChkSuppressPosResponse(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxData
  , Dcm_MsgLenType MsgDataLen)
{
  Std_ReturnType ret = E_NOT_OK;

  if (NULL_PTR != pRxData)
  {
    /* For ES95485 support  */
    /* noResponseRequired : Subfunction 0x02 */
    /* @Trace: SWS_ES95486_00002 */
    if ((pRxData[0U] == DCM_COMMUNICATIONCONTROL) &&
        (1U == MsgDataLen) &&
        (DCM_CC_DIABLE_NM_TRANS_NORESP == pRxData[1U]))
    {
      ret = E_OK;
    }
    /* noResponseRequired : Subfunction 0x02 */
    else if ((pRxData[0U] == DCM_ENABLENORMALMESSAGETRANSMISSION) &&
             (1U == MsgDataLen) &&
             (2U == pRxData[1U]))
    {
      ret = E_OK;
    }
    else
    {
      /* No action in this case */
    }
  }

  return ret;
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_DcmEnableNormalMsgTransmission      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for ES95486 0x29 service      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspInternal_DcmEnableNormalMsgTransmission(
  Dcm_MsgContextPtrType pMsgContext)
{
  /*The length of the message is wrong*/
  /* #6341 Jin 161028 */
  if(pMsgContext->reqDataLen != 1U)
  {
    /* As per ES95486, conditionsNotCorrect: 
     * wrong diagnosticService length or not supported LID */
    Dcm_InternalSetNegResponse(pMsgContext, 
      DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
  }
  else
  {
    /*
     * responseRequired of ES95486
     * 01: responseRequired,
     * 02: noResponseRequired 
     */
    Dcm_GucSubNetValue = 0U;

    /* Update Communication mode type for DCM_ENABLE_RX_TX_NORM_NM */
    Dcm_GucCommunicationModeType = DCM_COMM_TYPE_NM_AND_NORMAL;

    /* The entire response data is only Response Service Id #69 as per ES95486 */
    /* Will be incremented as 1 when response is transmitted */
    pMsgContext->resDataLen = 0; 
  }

  Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ChkSessionLevel                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the session is programming session or not  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : SessionLevel                                        **
**                                                                            **
** InOut Parameters     : None                                                **
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
#if (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_ChkSessionLevel(
  Dcm_SesCtrlType SessionLevel)
{
  Std_ReturnType retVal = E_NOT_OK;

  if ((SessionLevel == DCM_PROGRAMMING_SESSION) || 
      (SessionLevel == DCM_ECU_PROGRAMMING_MODE_05H)) 
  {
    retVal = E_OK;
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_DcmStopDiagnosticSession            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for ES95486 0x20 service      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_DSP_STOP_DIAG_SESSION_SERVICE == STD_ON)   
FUNC(void, DCM_CODE) Dcm_DspInternal_DcmStopDiagnosticSession(
  Dcm_MsgContextPtrType pMsgContext)
{
  if (NULL_PTR != pMsgContext)
  {
    /* Get session config and store the index to static variable */
    Dcm_SessionConfigConstPtrType LpSessionCfg;
    LpSessionCfg = Dcm_GetSesCtrlConfigByType(DCM_DEFAULT_SESSION);

    if (NULL_PTR == LpSessionCfg)
    {
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    }
    else
    {
      /*
       * [ES95486 4.11.2 StopDiagnosticSession positive Response]
       * Even if there would have been sent further parameters (#2 etc.) 
       * in the request, the positive response would just include them 
       * (and have the same length as the request)  
       */
      if (pMsgContext->reqDataLen > DCM_ZERO)
      {
        if (pMsgContext->resMaxDataLen < pMsgContext->reqDataLen)
        {
          pMsgContext->resDataLen = pMsgContext->resMaxDataLen;
        }
        else
        {
          pMsgContext->resDataLen = pMsgContext->reqDataLen;
        }

        Dcm_MemCopy(
          pMsgContext->resData, pMsgContext->reqData, pMsgContext->resDataLen);
      }
      else
      {
        /* Response: only SID #60 */
        pMsgContext->resDataLen = DCM_ZERO;
      }
    }

    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
