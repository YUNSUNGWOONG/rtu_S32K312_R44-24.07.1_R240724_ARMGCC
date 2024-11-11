/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_MainFunction.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Scheduled function of Csm                                     **
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
** 1.0.1.0   10-Mar-2021   TamTV6       Fix #17942, #17725, Add trace SUD     **
** 1.0.2     09-Nov-2021   TamTV6       Implement #20990                      **
** 1.0.3.0   12-Aug-2022   DienTC1      #594                                  **
** 1.0.9.0   22-Dec-2023   YH Eum       #CP44-3613                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_IntFunc.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global variable to indicate that a key management function is processing */
VAR(uint16, CSM_VAR_INIT) Csm_KeyManIsProcessing = CSM_KEYMANFNC_ISNOTPROCESSING;
#define CSM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Csm_MainFunction                                    **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : API to be called cyclically to process the          **
**                        requested jobs. The Csm_MainFunction shall check    **
**                        the queues for jobs to pass to the underlying CRYIF **
**                                                                            **
** Sync/Async           : N/A                                                 **
**                                                                            **
** Re-entrancy          : N/A                                                 **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Csm module should be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Csm_Initialisation                                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00101 SRS_BSW_00373 */
FUNC(void, CSM_CODE) Csm_MainFunction
(
  void
)
{
  #if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
    (CSM_PROCESSING_MODE_ASYNC_ENABLE == STD_ON))
  Std_ReturnType retVal;
  uint32 idx;
  Csm_JobType *ptrCsmJob;
  Csm_QueueType *ptrCsmQueue;
  #endif
  if (FALSE == Csm_Initialisation)
  {
	/* @Trace: Csm_SUD_FUNC_160 */
    /* Csm hasn't been initialised */
    #if CSM_DEV_ERROR_DETECT == STD_ON
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
    CSM_MAIN_FUNCTION_SID, CSM_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: Csm_SUD_FUNC_161 */
    #if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     (CSM_PROCESSING_MODE_ASYNC_ENABLE == STD_ON))
    #if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
    /* SWS_Csm_00974: Disable processing main function when a key management
      function is in process */
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Check if is there any key management function is processing */
    if (CSM_KEYMANFNC_ISNOTPROCESSING == (Csm_KeyManIsProcessing ^ \
      CSM_KEYMANFNC_ISNOTPROCESSING))
    {
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    #endif /* CSM_KEY_MANAGEMENT_ENABLE == STD_ON */
      for (idx = 0U; idx < CSM_TOTAL_CONFIGURED_QUEUE; idx++)
      {
        ptrCsmQueue = &Csm_QueueList[idx];
        /* Get a job from CSM queue, if queue is empty, NULL_PTR is returned */
        ptrCsmJob = Csm_PrvDequeue(ptrCsmQueue);
        if (NULL_PTR != ptrCsmJob)
        {
          SchM_Enter_Csm_GLOBALVAR_PROTECTION();
          ptrCsmJob->InDriver = TRUE;
          SchM_Exit_Csm_GLOBALVAR_PROTECTION();
          retVal = CryIf_ProcessJob(ptrCsmJob->JobCryIfChannelId,
            ptrCsmJob->CryptoJob);
          if (E_OK != retVal)
          {
            SchM_Enter_Csm_GLOBALVAR_PROTECTION();
            ptrCsmJob->InDriver = FALSE;
            SchM_Exit_Csm_GLOBALVAR_PROTECTION();
          }
          if ((CRYPTO_E_BUSY == retVal) || (CRYPTO_E_QUEUE_FULL == retVal))
          {
            /* If a CDO is busy or its CDO queue is full, job shall be put to CSM queue */
            retVal = Csm_PrvEnqueue(ptrCsmQueue, ptrCsmJob);
            if (CRYPTO_E_QUEUE_FULL == retVal)
            {
              #if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04) && \
                  (DET_AR_RELEASE_MINOR_VERSION >= 0x02)) || \
                  (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
                /* Report runtime error to Det */
                (void)Det_ReportRuntimeError(CSM_MODULE_ID, CSM_INSTANCE_ID,
                  CSM_MAIN_FUNCTION_SID, CSM_E_QUEUE_FULL);
              #else
              #if (CSM_DEV_ERROR_DETECT == STD_ON)
              /* Report error to Det */
                (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
                  CSM_MAIN_FUNCTION_SID, CSM_E_QUEUE_FULL);
              #endif /* #if (CSM_DEV_ERROR_DETECT == STD_ON) */
              #endif
            }
          }
          if (E_OK != retVal)
          {
            /* we need to notify application about the failure of the job */
            Csm_PrvCallbackNotification(CSM_MAIN_FUNCTION_SID, \
              ptrCsmJob->CryptoJob, E_NOT_OK);
          }
        }
      }
    #if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
    }
    else
    {
      SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    }
    #endif /* CSM_KEY_MANAGEMENT_ENABLE == STD_ON */
    #endif /*(CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
              (CSM_PROCESSING_MODE_ASYNC_ENABLE == STD_ON)*/
  }
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
