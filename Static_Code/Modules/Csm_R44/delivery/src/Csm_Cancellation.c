/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_Cancellation.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Cancellation service of Csm                                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0.0   15-Jan-2021   JH Lim       Initial version                       **
** 1.0.1.0   10-Mar-2021   TamTV6       Fix #17725, Add trace SUD             **
** 1.0.3.0   12-Aug-2022   DienTC1      #594                                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_IntFunc.h"

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Csm_CancelJob                                       **
**                                                                            **
** Service ID           : 0x6f                                                **
**                                                                            **
** Description          : Cancels the job processing from asynchronous or     **
**                        streaming jobs                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : job : Holds the indentifier of the job              **
**                              to be canceled                                **
**                        mode : Not used, just for interface                 **
**                               compatibility provided                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Request successful. Job removed from any queue**
**                              and potentially from crypto driver hardware   **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_JOB_CANCELED: Immediate cancelation not    **
**                          possible. The cancelation willbe done at next     **
**                          suitable processing step and notified via a       **
**                          negative finish callback.                         **
** Preconditions        : Csm module should be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Csm_Initialisation                                  **
**                        Csm_ApplicationCallback                             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     (CSM_PROCESSING_MODE_ASYNC_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_CancelJob
(
  VAR(uint32, AUTOMATIC) job,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode
)
{
  Std_ReturnType retVal;
  Csm_JobType *ptrCsmJob;
  Csm_QueueType *ptrCsmQueue;
  Crypto_JobType *ptrCryptoJob;
  #if (CSM_APPLICATION_CALLBACK_ENABLE == STD_ON)
  uint32 callbackId;
  #endif
  retVal = E_NOT_OK;
  CSM_UNUSED(mode);

  if (FALSE == Csm_Initialisation)
  {
    /* @Trace: Csm_SUD_FUNC_140 */
    #if CSM_DEV_ERROR_DETECT == STD_ON
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
    CSM_CANCEL_JOB_SID, CSM_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: Csm_SUD_FUNC_141 */
    /* Get corresponding Csm Job from listed
    of configured Csm Job by using job Id */
    ptrCsmJob = Csm_PrvGetCsmJobPtr(job);
    if (NULL_PTR != ptrCsmJob)
    {
      ptrCryptoJob = ptrCsmJob->CryptoJob;
      if (CRYPTO_PROCESSING_ASYNC == \
          ptrCryptoJob->jobPrimitiveInfo->processingType)
      {
        /* @Trace: Csm_SUD_FUNC_143 */
        ptrCsmQueue = Csm_PrvGetQueueByChannelId(ptrCsmJob->JobCryIfChannelId);
        /* Only asynchronous job can be canceled */
        /* Remove job from CSM queue if any */
        Csm_PrvJobQueueRemove(ptrCsmQueue, ptrCsmJob);
        /* Cancel job in driver if any */
        retVal = CryIf_CancelJob(ptrCsmJob->JobCryIfChannelId, ptrCryptoJob);
        if (E_OK == retVal)
        {
          SchM_Enter_Csm_GLOBALVAR_PROTECTION();
          ptrCsmJob->InDriver = FALSE;
          SchM_Exit_Csm_GLOBALVAR_PROTECTION();
          if (CRYPTO_USE_FNC == ptrCsmJob->PortType)
          {
            #if (CSM_APPLICATION_CALLBACK_ENABLE == STD_ON)
            callbackId = ptrCryptoJob->jobPrimitiveInfo->callbackId;
            /* call configured application callback */
            Csm_ApplicationCallback[callbackId](job, E_JOB_CANCELED);
            #endif
          }
          else if (CRYPTO_USE_PORT_OPTIMIZED == ptrCsmJob->PortType)
          {
            /* call rte callback notification */
            if (NULL_PTR != ptrCsmJob->RteCallbackNotification)
            {
              ptrCsmJob->RteCallbackNotification(E_JOB_CANCELED);
            }
          }
          else
          {
            /* To make polyspace happy */
          }
        }
        /* If retVal is CRYPTO_E_JOB_CANCELED then
          postpone the call to application notification callback.
          The application callback will be called later in
          Csm_CallbackNotification()
        */
      }
      else
      {
        /* @Trace: Csm_SUD_FUNC_142 */
        /* service failed because it is called with synchronous job */
        #if CSM_DEV_ERROR_DETECT == STD_ON
        (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_CANCEL_JOB_SID, CSM_E_PROCESSING_MODE);
        #endif
      }
    }
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
