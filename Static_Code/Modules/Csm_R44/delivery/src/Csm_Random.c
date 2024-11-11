/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_Random.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Random generate service of Csm                                **
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
**                       Global Data                                          **
*******************************************************************************/

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Csm_RandomGenerate                                  **
**                                                                            **
** Service ID           : 0x72                                                **
**                                                                            **
** Description          : Generate a random number and stores it in the memory**
**                        location pointed by the result pointer              **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId : Holds the identifier of the job using the   **
**                                CSM service                                 **
**                        dataPtr : Contains the pointer to the data to be    **
**                                  encrypted                                 **
**                        dataLength : Contains the number of bytes to encrypt**
**                                                                            **
** InOut parameter      : resultLengthPtr :Holds a pointer to the memory      **
**                          location in which the result length in bytes is   **
**                          stored. On calling this function, this parameter  **
**                          shall contain the number of random bytes, which   **
**                          shall be stored to the buffer provided by         **
**                          resultPtr. When the request has finished, the     **
**                          actual length of the returned value shall be      **
**                          stored.                                           **
**                                                                            **
** Output Parameters    : resultPtr : Holds a pointer to the memory location  **
**                          which will hold the result of the random number   **
                            generation                                        **
**                                                                            **
** Return parameter     : E_OK : Request successful                           **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, service is still busy**
**                        CRYPTO_E_ENTROPY_EXHAUSTION: Request failed, entropy**
**                          of random number generator is exhausted           **
**                                                                            **
** Preconditions        : Csm module should be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Csm_Initialisation                                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        Csm_PrvGetCsmJobPtr                                 **
**                        Csm_PrvJobQueueExist                                **
**                        Csm_PrvValidateOutputPtr                            **
**                        Csm_PrvProcessService                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00007 */
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     (CSM_PRIMITIVE_RANDOM_GENERATE_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00019 SRS_CryptoStack_00006 */
FUNC(Std_ReturnType, CSM_CODE) Csm_RandomGenerate
(
  VAR(uint32, AUTOMATIC) jobId,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  Csm_JobType *ptrCsmJob;
  Csm_QueueType *ptrCsmQueue;
  Crypto_JobType *ptrCryptoJob;
  Std_ReturnType retVal;
  boolean jobExist;
  boolean localInDriver;

  retVal = E_OK;

  /* To check module initialisation */
  if (FALSE == Csm_Initialisation)
  {
    /* @Trace: Csm_SUD_FUNC_190 */
    retVal = E_NOT_OK;
    #if CSM_DEV_ERROR_DETECT == STD_ON
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
    CSM_RANDOM_GENERATE_SID, CSM_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: Csm_SUD_FUNC_191 */
    /* Get corresponding Csm Job from listed of configured Csm Job by using
      job Id */
    ptrCsmJob = Csm_PrvGetCsmJobPtr(jobId);
    if (NULL_PTR != ptrCsmJob)
    {
      /* @Trace: Csm_SUD_FUNC_192 */
      SchM_Enter_Csm_GLOBALVAR_PROTECTION();
      localInDriver = ptrCsmJob->InDriver;
      SchM_Exit_Csm_GLOBALVAR_PROTECTION();
      if (TRUE == localInDriver)
      {
        retVal = CRYPTO_E_BUSY;
      }

      if (E_OK == retVal)
      {
        ptrCsmQueue = Csm_PrvGetQueueByChannelId(ptrCsmJob->JobCryIfChannelId);
        /* a job should not be enqueued or updated if it's already presence in
          queue */
        jobExist = Csm_PrvJobQueueExist(ptrCsmQueue, ptrCsmJob, NULL_PTR);
        if (TRUE == jobExist)
        {
          retVal = CRYPTO_E_BUSY;
        }
      }
    }
    else
    {
      /* @Trace: Csm_SUD_FUNC_194 */
      retVal = E_NOT_OK;
    }

    if (E_OK == retVal)
    {
      /* @Trace: Csm_SUD_FUNC_193 */
      ptrCryptoJob = ptrCsmJob->CryptoJob;
      /* Prepare jobRedirectionInfo buffer */
      Csm_PrvCopyJobRedirectionInfo(ptrCryptoJob->jobRedirectionInfoRef,
        ptrCsmJob->PtrJobRedirectionInfoRef);
      /* Since outputPtr and outputLengthPtr are only required in FINISH mode.
        However there is no mode provided as parameter in the API then we need
        to check it regardless of operation mode */
      retVal = Csm_PrvValidateOutputPtr(ptrCryptoJob->jobRedirectionInfoRef,
        resultPtr, resultLengthPtr, CSM_RANDOM_GENERATE_SID,
        CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT);
      if (E_OK == retVal)
      {
        SchM_Enter_Csm_GLOBALVAR_PROTECTION();
        /* The operation mode of Csm_RandomGenerate shall be set to
          CRYPTO_OPERATIONMODE_SINGLECALL */
        ptrCryptoJob->jobPrimitiveInputOutput.mode = \
          CRYPTO_OPERATIONMODE_SINGLECALL;
        ptrCryptoJob->jobPrimitiveInputOutput.outputPtr = resultPtr;
        ptrCryptoJob->jobPrimitiveInputOutput.outputLengthPtr = resultLengthPtr;
        SchM_Exit_Csm_GLOBALVAR_PROTECTION();
        retVal = Csm_PrvProcessService(ptrCsmJob, CSM_RANDOM_GENERATE_SID);
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
