/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_IntFunc.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Internal function of CSM                                      **
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
** 1.0.2     09-Nov-2021   TamTV6       Implement #20990                      **
** 1.0.3.0   12-Aug-2022   DienTC1      #594                                  **
** 1.0.9.0   23-Dec-2023   YH Eum       #CP44-3331                            **
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
** Function Name        : Csm_PrvValidateInputPtr                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : To validate inputPtr, inputLength,                  **
**                        secondaryInputPtr, secondaryInputLength,            **
**                        tertiaryInputPtr, tertiaryInputLength of            **
**                        Crypto_JobPrimitiveInputOutputType depending on job **
**                        redirection configuration                           **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrJobRedirectionInfoRef : Holds the pointer of the **
**                          job redirection info                              **
**                        ptrInput : input pointer to validate                **
**                        inputLength : input length to validate              **
**                        serviceId : service id of Csm published api         **
**                        inOutRedirectionConfig : to chose which redirection **
**                          input to be validated                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK : Validation success                           **
**                        E_NOT_OK: Validation failed                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     ((CSM_PRIMITIVE_HASH_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_MAC_GENERATE_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_MAC_VERIFY_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_ENCRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_DECRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_AEADENCRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_AEADDECRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_SIGNATURE_GENERATE_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_SIGNATURE_VERIFY_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_JOB_RANDOM_SEED_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_SECRET_ENABLE == STD_ON)))
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_PrvValidateInputPtr
(
  P2CONST(Crypto_JobRedirectionInfoType, AUTOMATIC, CSM_APPL_DATA) \
                                                       ptrJobRedirectionInfoRef,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ptrInput, 
  VAR(uint32, AUTOMATIC) inputLength,
  VAR(uint8, AUTOMATIC) serviceId, 
  VAR(Crypto_InputOutputRedirectionConfigType, AUTOMATIC) inOutRedirectionConfig
)
{
  Std_ReturnType retVal;
  retVal = E_OK;
  #if CSM_DEV_ERROR_DETECT == STD_OFF
  CSM_UNUSED(serviceId);
  #endif
  if (NULL_PTR == ptrJobRedirectionInfoRef)
  {
    /* @Trace: Csm_SUD_FUNC_400 */
    /* Job redirection is not used */
    if (NULL_PTR == ptrInput)
    {
      /* No Job Redirection configured but there is NULL_PTR in
         input paramater */
      retVal = E_NOT_OK;
      #if CSM_INPUT_DATA_NO_VALIDATION == STD_ON
      if (0x0U == inputLength)
      {
        retVal = E_OK;
      }
      #else
      #if CSM_DEV_ERROR_DETECT == STD_ON
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
          serviceId, CSM_E_PARAM_POINTER);
      #endif
      #endif
      
    }
    else if (0x0U == inputLength)
    {
      retVal = E_NOT_OK;

      #if CSM_PRIMITIVE_HASH_ENABLE == STD_ON
      if (CSM_HASH_SID == serviceId)
      {
        retVal = E_OK;
      }
      #endif
    }
    else
    {
      /* To make polyspace happy */
    }
  }
  else
  {
    if ((ptrJobRedirectionInfoRef->redirectionConfig & 
          inOutRedirectionConfig) != inOutRedirectionConfig)
    {
      /* @Trace: Csm_SUD_FUNC_401 */
      if (NULL_PTR == ptrInput)
      {
        /* Job redirection isn't configured. However ptrInput is NULL_PTR */
        retVal = E_NOT_OK;

        #if CSM_INPUT_DATA_NO_VALIDATION == STD_ON
        if (0x0U == inputLength)
        {
          retVal = E_OK;
        }
        #else
        #if CSM_DEV_ERROR_DETECT == STD_ON
        (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        serviceId, CSM_E_PARAM_POINTER);
        #endif
        #endif
      }
      else if (0x0U == inputLength)
      {
        retVal = E_NOT_OK;
        
        #if CSM_PRIMITIVE_HASH_ENABLE == STD_ON
        if (CSM_HASH_SID == serviceId)
        {
          retVal = E_OK;
        }
        #endif
      }
      else
      {
        /* To make polyspace happy */
      }
    }
    else if ((NULL_PTR != ptrInput) || (0x0U != inputLength))
    {
      /* @Trace: Csm_SUD_FUNC_402 */
      /* If an input or output value of a job is re-directed to a key
         element and the corresponding input or output length value is
         not set to 0, the job shall not be processed and E_NOT_OK shall
         be returned. */
      retVal = E_NOT_OK;
    }
    else
    {
      /* To make polyspace happy */
    }
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_PrvValidateOutputPtr                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : To validate outputPtr, outputLengthPtr,             **
**                        secondaryOutputPtr, secondaryOutputLengthPtr of     **
**                        Crypto_JobPrimitiveInputOutputType depending on job **
**                        redirection configuration                           **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrJobRedirectionInfoRef : Holds the pointer of the **
**                          job redirection info                              **
**                        ptrOutput : output pointer to validate              **
**                        ptrOutputLength : output length pointer to validate **
**                        serviceId : service id of Csm published api         **
**                        inOutRedirectionConfig : to chose which redirection **
**                          output to be validated                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK : Validation success                           **
**                        E_NOT_OK: Validation failed                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     ((CSM_PRIMITIVE_HASH_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_MAC_GENERATE_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_ENCRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_DECRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_AEADENCRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_AEADDECRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_SIGNATURE_GENERATE_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_RANDOM_GENERATE_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_PUB_VAL_ENABLE == STD_ON)))
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_PrvValidateOutputPtr
(
  P2CONST(Crypto_JobRedirectionInfoType, AUTOMATIC, CSM_APPL_DATA) \
                                                       ptrJobRedirectionInfoRef,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) ptrOutput,
  P2CONST(uint32, AUTOMATIC, CSM_APPL_DATA) ptrOutputLength, 
  VAR(uint8, AUTOMATIC) serviceId,
  VAR(Crypto_InputOutputRedirectionConfigType, AUTOMATIC) inOutRedirectionConfig
)
{
  Std_ReturnType retVal;
  retVal = E_OK;
  #if CSM_DEV_ERROR_DETECT == STD_OFF
  CSM_UNUSED(serviceId);
  #endif
  if (NULL_PTR == ptrJobRedirectionInfoRef)
  {
    /* @Trace: Csm_SUD_FUNC_410 */
    /* Job redirection is not used */
    if ((NULL_PTR == ptrOutput) || (NULL_PTR == ptrOutputLength))
    {
      /* No Job Redirection configured but there is NULL_PTR in
         input paramater */
      retVal = E_NOT_OK;
      #if CSM_DEV_ERROR_DETECT == STD_ON
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
          serviceId, CSM_E_PARAM_POINTER);
      #endif
    }
    else if (0x0U == *ptrOutputLength)
    {
      retVal = E_NOT_OK;
    }
    else
    {
      /* To make polyspace happy */
    }
  }
  else
  {
    if ((ptrJobRedirectionInfoRef->redirectionConfig & 
    inOutRedirectionConfig) != inOutRedirectionConfig)
    {
      /* @Trace: Csm_SUD_FUNC_411 */
      if ((NULL_PTR == ptrOutput) || (NULL_PTR == ptrOutputLength))
      {
        /* Job redirection isn't configured. However ptrOutput and
           ptrOutputLength is NULL_PTR */
        retVal = E_NOT_OK;
        #if CSM_DEV_ERROR_DETECT == STD_ON
        (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        serviceId, CSM_E_PARAM_POINTER);
        #endif
      }
      else if (0x0U == *ptrOutputLength)
      {
        retVal = E_NOT_OK;
      }
      else
      {
        /* To make polyspace happy */
      }
    }
    else if (NULL_PTR == ptrOutputLength)
    {
      /* @Trace: Csm_SUD_FUNC_412 */
      /* Job redirection is configured. However ptrOutputLength is NULL_PTR */
      retVal = E_NOT_OK;
      #if CSM_DEV_ERROR_DETECT == STD_ON
      (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
      serviceId, CSM_E_PARAM_POINTER);
      #endif
    }
    else if ((NULL_PTR != ptrOutput) || (0x0U != *ptrOutputLength))
    {
      /* @Trace: Csm_SUD_FUNC_413 */
       /* If an input or output value of a job is re-directed to a key
       element and the corresponding input or output length value is
       not set to 0, the job shall not be processed and E_NOT_OK shall
       be returned. */
      retVal = E_NOT_OK;
    }
    else
    {
      /* To make polyspace happy */
    }
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_PrvJobModeValidate                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate mode paramameter before passing to         **
**                        Crypto_JobPrimitiveInputOutputType                  **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrCryptoJob : Holds the pointer of the job         **
**                        mode : Indicates which operation mode(s) to validate**
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK : Validation success                           **
**                        E_NOT_OK: Validation failed                         **
**                        CRYPTO_E_BUSY: Job is being processed by driver     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     ((CSM_PRIMITIVE_HASH_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_MAC_GENERATE_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_MAC_VERIFY_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_ENCRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_DECRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_AEADENCRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_AEADDECRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_SIGNATURE_GENERATE_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_SIGNATURE_VERIFY_ENABLE == STD_ON)))
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_PrvJobModeValidate
(
  CONSTP2CONST(Csm_JobType, AUTOMATIC, CSM_APPL_CONST) ptrCsmJob,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode
)
{
  Std_ReturnType retVal;
  Crypto_JobType* ptrCryptoJob;
  boolean localInDriver;
  Crypto_OperationModeType localMode;

  retVal = E_NOT_OK;

  SchM_Enter_Csm_GLOBALVAR_PROTECTION();
  localInDriver = ptrCsmJob->InDriver;
  SchM_Exit_Csm_GLOBALVAR_PROTECTION();
  if (TRUE == localInDriver)
  {
    /* @Trace: Csm_SUD_FUNC_420 */
    /* When a job is handed to driver, Csm has to wait for driver release the
       job first. After that Csm can update job */
    retVal = CRYPTO_E_BUSY;
  }
  else
  {
    ptrCryptoJob = ptrCsmJob->CryptoJob;
    /* If a job isn't being processed by driver, then it can contain operation
       mode CRYPTO_OPERATIONMODE_START with following condition*/
    if (CRYPTO_OPERATIONMODE_START == (mode & CRYPTO_OPERATIONMODE_START))
    {
      /* @Trace: Csm_SUD_FUNC_421 */
      if ((CRYPTO_OPERATIONMODE_FINISH == \
          (mode & CRYPTO_OPERATIONMODE_FINISH)) && \
          (CRYPTO_OPERATIONMODE_UPDATE != \
          (mode & CRYPTO_OPERATIONMODE_UPDATE)))
      {
        /* CRYPTO_OPERATIONMODE_START and CRYPTO_OPERATIONMODE_FINISH
           cannot be combined without CRYPTO_OPERATIONMODE_UPDATE */
        retVal = E_NOT_OK;
      }
      else
      {
        retVal = E_OK;
      }
    }
    else if (CRYPTO_JOBSTATE_ACTIVE == ptrCryptoJob->jobState)
    {
      /* @Trace: Csm_SUD_FUNC_422 */
      SchM_Enter_Csm_GLOBALVAR_PROTECTION();
      localMode = ptrCryptoJob->jobPrimitiveInputOutput.mode;
      SchM_Exit_Csm_GLOBALVAR_PROTECTION();
      if (CRYPTO_OPERATIONMODE_FINISH == \
          (localMode & CRYPTO_OPERATIONMODE_FINISH))
      {
        retVal = E_NOT_OK;
      }
      else if (CRYPTO_OPERATIONMODE_UPDATE == \
              (localMode & CRYPTO_OPERATIONMODE_UPDATE))
      {
        /* @Trace: Csm_SUD_FUNC_423 */
        /* if previous mode is UPDATE then the next mode can be
           either UPDATE or FINISH */
        if ((CRYPTO_OPERATIONMODE_UPDATE == \
            (mode & CRYPTO_OPERATIONMODE_UPDATE)) || \
            (CRYPTO_OPERATIONMODE_FINISH == \
            (mode & CRYPTO_OPERATIONMODE_FINISH)))
        {
          retVal = E_OK;
        }
        else
        {
          retVal = E_NOT_OK;
        }
      }
      else if (CRYPTO_OPERATIONMODE_START == \
              (localMode & CRYPTO_OPERATIONMODE_START))
      {
        /* @Trace: Csm_SUD_FUNC_424 */
        if (CRYPTO_OPERATIONMODE_UPDATE == \
           (mode & CRYPTO_OPERATIONMODE_UPDATE))
        {
          retVal = E_OK;
        }
        else
        {
          retVal = E_NOT_OK;
        }
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
    else
    {
      /* To make polyspace happy */
    }
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_PrvClearJobState                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Clear job state (buffer, length, etc...) in         **
**                        Crypto_JobPrimitiveInputOutputType                  **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrCryptoJob : Holds the pointer of the job         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if (CSM_JOB_PROCESSING_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CSM_CODE) Csm_PrvClearJobState
(
  CONSTP2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) ptrCryptoJob
)
{
  /* @Trace: Csm_SUD_FUNC_430 */
  SchM_Enter_Csm_GLOBALVAR_PROTECTION();
  ptrCryptoJob->jobPrimitiveInputOutput.inputPtr = NULL_PTR;
  ptrCryptoJob->jobPrimitiveInputOutput.inputLength = 0;
  ptrCryptoJob->jobPrimitiveInputOutput.secondaryInputPtr = NULL_PTR;
  ptrCryptoJob->jobPrimitiveInputOutput.secondaryInputLength = 0;
  ptrCryptoJob->jobPrimitiveInputOutput.tertiaryInputPtr = NULL_PTR;
  ptrCryptoJob->jobPrimitiveInputOutput.tertiaryInputLength = 0;
  ptrCryptoJob->jobPrimitiveInputOutput.outputPtr = NULL_PTR;
  ptrCryptoJob->jobPrimitiveInputOutput.outputLengthPtr = NULL_PTR;
  ptrCryptoJob->jobPrimitiveInputOutput.secondaryOutputPtr = NULL_PTR;
  ptrCryptoJob->jobPrimitiveInputOutput.secondaryOutputLengthPtr = NULL_PTR;
  ptrCryptoJob->jobPrimitiveInputOutput.verifyPtr = NULL_PTR;
  ptrCryptoJob->jobPrimitiveInputOutput.mode = 0x0U;
  ptrCryptoJob->jobPrimitiveInputOutput.cryIfKeyId = 0x0U;
  ptrCryptoJob->jobPrimitiveInputOutput.targetCryIfKeyId = 0x0U;
  SchM_Exit_Csm_GLOBALVAR_PROTECTION();
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Csm_PrvProcessService                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : To provide general behaviour for all Csm_<Service>  **
**                        function                                            **
**                                                                            **
** Sync/Async           : Sync / Async depends on job configuration           **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrCsmJob : Holds the pointer of the Csm job        **
**                        serviceId : service id of the caller                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK : Request successful                           **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, service is still busy**
**                        CRYPTO_E_KEY_NOT_VALID: Request failed,             **
**                          the key's state is "invalid"                      **
**                        CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key   **
**                          element has the wrong size                        **
**                        CRYPTO_E_KEY_EMPTY: Request failed because of       **
**                          uninitialized source key element                  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_PrvGetQueueByChannelId                          **
**                        CryIf_ProcessJob                                    **
**                        Csm_PrvIsHighestPrio                                **
**                        Csm_PrvIsQueueEmpty                                 **
**                        Csm_PrvEnqueue                                      **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if (CSM_JOB_PROCESSING_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
 FUNC(Std_ReturnType, CSM_CODE) Csm_PrvProcessService
(
  CONSTP2VAR(Csm_JobType, AUTOMATIC, CSM_APPL_DATA) ptrCsmJob,
  VAR(uint8, AUTOMATIC) serviceId
)
{
  Crypto_JobType *ptrCryptoJob;
  Csm_QueueType *ptrCsmQueue;
  Std_ReturnType retVal;
  Crypto_ProcessingType processingType;
  boolean isHighestJobPriority;
  boolean isQueueEmpty;

  ptrCryptoJob = ptrCsmJob->CryptoJob;
  processingType = ptrCryptoJob->jobPrimitiveInfo->processingType;
  ptrCsmQueue = Csm_PrvGetQueueByChannelId(ptrCsmJob->JobCryIfChannelId);
  /* jobState is being managed by CRY,
     therefore we need to prevent modifying
     jobState while checking for its current value.*/
  SchM_Enter_Csm_GLOBALVAR_PROTECTION();
  if (CRYPTO_JOBSTATE_ACTIVE == ptrCryptoJob->jobState)
  {
    /* @Trace: Csm_SUD_FUNC_440 */
    ptrCsmJob->InDriver = TRUE;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    if (CRYPTO_PROCESSING_SYNC == processingType)
    {
      /* By entering to critical section, we can ensure that synchronous
         job can be processed in a row without having to wait for
         asynchronous jobs in between */
      retVal = CryIf_ProcessJob(ptrCsmJob->JobCryIfChannelId, ptrCryptoJob);
    }
    else
    {
      retVal = CryIf_ProcessJob(ptrCsmJob->JobCryIfChannelId, ptrCryptoJob);
    }
    if ((CRYPTO_PROCESSING_SYNC == processingType) || (E_OK != retVal))
    {
      SchM_Enter_Csm_GLOBALVAR_PROTECTION();
      /* job is synchronous or (asynchronous and service request failed) */
      ptrCsmJob->InDriver = FALSE;
      SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    }
  }
  else
  {
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    if (CRYPTO_PROCESSING_SYNC == processingType)
    {
      /* @Trace: Csm_SUD_FUNC_441 */
      /* check job priority */
      isHighestJobPriority = Csm_PrvIsHighestPrio(ptrCsmQueue, ptrCsmJob);
      if (TRUE == isHighestJobPriority)
      {
        SchM_Enter_Csm_GLOBALVAR_PROTECTION();
        ptrCsmJob->InDriver = TRUE;
        SchM_Exit_Csm_GLOBALVAR_PROTECTION();
        retVal = CryIf_ProcessJob(ptrCsmJob->JobCryIfChannelId, ptrCryptoJob);
        SchM_Enter_Csm_GLOBALVAR_PROTECTION();
        ptrCsmJob->InDriver = FALSE;
        SchM_Exit_Csm_GLOBALVAR_PROTECTION();
      }
      else
      {
        retVal = CRYPTO_E_BUSY;
      }
    }
    else
    {
      /* @Trace: Csm_SUD_FUNC_442 */
      isQueueEmpty = Csm_PrvIsQueueEmpty(ptrCsmQueue);
      if (TRUE == isQueueEmpty)
      {
        SchM_Enter_Csm_GLOBALVAR_PROTECTION();
        ptrCsmJob->InDriver = TRUE;
        SchM_Exit_Csm_GLOBALVAR_PROTECTION();
        retVal = CryIf_ProcessJob(ptrCsmJob->JobCryIfChannelId, ptrCryptoJob);
        if (E_OK != retVal)
        {
          SchM_Enter_Csm_GLOBALVAR_PROTECTION();
          ptrCsmJob->InDriver = FALSE;
          SchM_Exit_Csm_GLOBALVAR_PROTECTION();
        }
        if ((CRYPTO_E_BUSY == retVal) || (CRYPTO_E_QUEUE_FULL == retVal))
        {
          /* In case queue is not empty, we can try to enqueue.
          If the operation return E_OK then everything is fine,
          or CRYPTO_E_QUEUE_FULL, otherwise it means that there is
          something wrong when enqueue */
          retVal = Csm_PrvEnqueue(ptrCsmQueue, ptrCsmJob);
        }
      }
      else
      {
        retVal = Csm_PrvEnqueue(ptrCsmQueue, ptrCsmJob);
      }
      if (CRYPTO_E_QUEUE_FULL == retVal)
      {
        #if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04) && \
            (DET_AR_RELEASE_MINOR_VERSION >= 0x02)) || \
            (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
          /* Report runtime error to Det */
          (void)Det_ReportRuntimeError(CSM_MODULE_ID, CSM_INSTANCE_ID,
            serviceId, CSM_E_QUEUE_FULL);
        #else
        #if (CSM_DEV_ERROR_DETECT == STD_ON)
        /* Report error to Det */
          (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
            serviceId, CSM_E_QUEUE_FULL);
        #endif /* #if (CSM_DEV_ERROR_DETECT == STD_ON) */
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
** Function Name        : Csm_PrvGetCsmJobPtr                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : To get Job Pointer from list of configured jobs     **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId : Holds the indentifier of the job            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Csm_JobType* : pointer to Csm_JobType               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#if (CSM_JOB_PROCESSING_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Marco P2VAR is defined in Generic source. It is out of scope." */
FUNC(P2VAR(Csm_JobType, AUTOMATIC, CSM_APPL_DATA), CSM_CODE) Csm_PrvGetCsmJobPtr
(
  VAR(uint32, AUTOMATIC) jobId
)
/* polyspace-end MISRA-C3:20.7 */
{
  /* @Trace: Csm_SUD_FUNC_450 */
  Csm_JobType *ptrJobLocal;
  ptrJobLocal = NULL_PTR;
  /* Since jobId is consecutive and gapless, we can consider that jobId is an
     array index of Csm_JobList. Generation tool must make sure that Csm Job is
     generated in a manner order */
  if (CSM_TOTAL_CONFIGURED_JOB > jobId)
  {
    /* @Trace: Csm_SUD_FUNC_451 */
    ptrJobLocal = &Csm_JobList[jobId];
  }
  return ptrJobLocal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_PrvServiceGenerate                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Common function for Csm_Hash, Csm_MacGenerate,      **
**                        Csm_Encrypt, Csm_Decrypt, Csm_SignatureGenerate     **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId : Holds the identifier of the job using the   **
**                                CSM service                                 **
**                        mode : Indicates which operation mode(s) to perfom  **
**                        ptrInput : Contains the pointer to the input data   **
**                        inputLength: Contains the number of bytes of        **
**                                     input data                             **
**                        serviceId : service id of the caller                **
**                                                                            **
** InOut parameter      : ptrOutputLength : Holds a pointer to the memory     **
**                          location in which the output length in bytes is   **
**                          stored. On calling this function, this parameter  **
**                          shall contain the size of the buffer provided by  **
**                          ptrInput. When the request has finished, the      **
**                          actual length of the returned output data shall   **
**                          be stored                                         **
**                                                                            **
** Output Parameters    : ptrOutput : Contains the pointer to the output      **
**                                    buffer                                  **
**                                                                            **
** Return parameter     : E_OK : Request successful                           **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, service is still busy**
**                        CRYPTO_E_KEY_NOT_VALID: Request failed,             **
**                          the key's state is "invalid"                      **
**                        CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key   **
**                          element has the wrong size                        **
**                        CRYPTO_E_KEY_EMPTY: Request failed because of       **
**                          uninitialized source key element                  **
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
**                        Csm_PrvJobModeValidate                              **
**                        Csm_PrvClearJobState                                **
**                        Csm_PrvValidateInputPtr                             **
**                        Csm_PrvValidateOutputPtr                            **
**                        Csm_PrvProcessService                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     ((CSM_PRIMITIVE_HASH_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_MAC_GENERATE_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_ENCRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_DECRYPT_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_SIGNATURE_GENERATE_ENABLE == STD_ON)))
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_PrvServiceGenerate
(
  uint32 jobId, Crypto_OperationModeType mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ptrInput, 
  VAR(uint32, AUTOMATIC) inputLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) ptrOutput,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) ptrOutputLength,
  VAR(uint8, AUTOMATIC) serviceId
)
{
  Csm_JobType *ptrCsmJob;
  Csm_QueueType *ptrCsmQueue;
  Crypto_JobType *ptrCryptoJob;
  Std_ReturnType retVal;
  boolean jobExist;

  /* To check module initialisation */
  if (FALSE == Csm_Initialisation)
  {
    /* @Trace: Csm_SUD_FUNC_460 */
    retVal = E_NOT_OK;
    #if CSM_DEV_ERROR_DETECT == STD_ON
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
    serviceId, CSM_E_UNINIT);
    #endif
  }
  else
  {
    /* Get corresponding Csm Job from listed of configured Csm Job by using
      job Id */
    ptrCsmJob = Csm_PrvGetCsmJobPtr(jobId);
    if (NULL_PTR != ptrCsmJob)
    {
      /* @Trace: Csm_SUD_FUNC_462 */
      retVal = Csm_PrvJobModeValidate(ptrCsmJob, mode);
      if (E_OK == retVal)
      {
        /* @Trace: Csm_SUD_FUNC_463 */
        ptrCsmQueue = Csm_PrvGetQueueByChannelId(ptrCsmJob->JobCryIfChannelId);
        jobExist = Csm_PrvJobQueueExist(ptrCsmQueue, ptrCsmJob, NULL_PTR);
        /* a job should not be enqueued or updated if it's already presence in
          queue except when the service is called with operation mode
          CRYPTO_OPERATIONMODE_START */
        if (TRUE == jobExist)
        {
          if ((mode & CRYPTO_OPERATIONMODE_START) == CRYPTO_OPERATIONMODE_START)
          {
            Csm_PrvJobQueueRemove(ptrCsmQueue, ptrCsmJob);
            retVal = E_OK;
          }
          else
          {
            retVal = CRYPTO_E_BUSY;
          }
        }
        else
        {
          retVal = E_OK;
        }
      }
    }
    else
    {
      /* @Trace: Csm_SUD_FUNC_461 */
      retVal = E_NOT_OK;
    }

    if (E_OK == retVal)
    {
      ptrCryptoJob = ptrCsmJob->CryptoJob;
      /* Clear job state when mode is CRYPTO_OPERATIONMODE_START */
      if ((mode & CRYPTO_OPERATIONMODE_START) == CRYPTO_OPERATIONMODE_START)
      {
        /* @Trace: Csm_SUD_FUNC_464 */
        Csm_PrvClearJobState(ptrCryptoJob);
      }
      /* Prepare jobRedirectionInfo buffer */
      Csm_PrvCopyJobRedirectionInfo(ptrCryptoJob->jobRedirectionInfoRef,
        ptrCsmJob->PtrJobRedirectionInfoRef);
      if ((mode & CRYPTO_OPERATIONMODE_UPDATE) == CRYPTO_OPERATIONMODE_UPDATE)
      {
        /* @Trace: Csm_SUD_FUNC_465 */
        /* To validate inputPtr parameter */
        retVal = Csm_PrvValidateInputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                    ptrInput, inputLength, serviceId,
                    CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT);
      }

      if (E_OK == retVal)
      {
        /* @Trace: Csm_SUD_FUNC_466 */
        if ((CRYPTO_OPERATIONMODE_FINISH == \
            (mode & CRYPTO_OPERATIONMODE_FINISH)) || \
            ((CRYPTO_OPERATIONMODE_UPDATE == \
            (mode & CRYPTO_OPERATIONMODE_UPDATE)) \
            && ((CSM_ENCRYPT_SID == serviceId) || \
            (CSM_DECRYPT_SID == serviceId))))
        {
          /* In case of ENCRYPT and DECRYPT, we also need to check outputPtr and
            outputLengthPtr in UPDATE mode. refer to SWS_Crypto_00071 */
          retVal = Csm_PrvValidateOutputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                      ptrOutput, ptrOutputLength, serviceId,
                      CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT);
        }
      }
      if (E_OK == retVal)
      {
        /* @Trace: Csm_SUD_FUNC_467 */
        SchM_Enter_Csm_GLOBALVAR_PROTECTION();
        /* mode is already checked before, no need to re-check again */
        ptrCryptoJob->jobPrimitiveInputOutput.mode = mode;
        ptrCryptoJob->jobPrimitiveInputOutput.inputPtr = ptrInput;
        ptrCryptoJob->jobPrimitiveInputOutput.inputLength = inputLength;
        ptrCryptoJob->jobPrimitiveInputOutput.outputPtr = ptrOutput;
        ptrCryptoJob->jobPrimitiveInputOutput.outputLengthPtr = ptrOutputLength;
        SchM_Exit_Csm_GLOBALVAR_PROTECTION();
        retVal = Csm_PrvProcessService(ptrCsmJob, serviceId);
      }
    }
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Csm_PrvServiceVerify                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Common function for Csm_MacVerify,                  **
**                        Csm_SignatureVerify                                 **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId : Holds the identifier of the job using the   **
**                                CSM service                                 **
**                        mode : Indicates which operation mode(s) to perfom  **
**                        ptrInput : Contains the pointer to the input data   **
**                        inputLength: Contains the number of bytes of        **
**                                     input data                             **
**                        ptrSecondaryInput: Holds a pointer to the secondary **
**                                           input data                       **
**                        secondaryInputLength: Contains length of            **
**                                              secondary input               **
**                        serviceId : service id of the caller                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ptrVerify : Holds a pointer to the memory location, **
**                                    which will hold the result of the       **
**                                    verification                            **
**                                                                            **
** Return parameter     : E_OK : Request successful                           **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, service is still busy**
**                        CRYPTO_E_KEY_NOT_VALID: Request failed,             **
**                          the key's state is "invalid"                      **
**                        CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key   **
**                          element has the wrong size                        **
**                        CRYPTO_E_KEY_EMPTY: Request failed because of       **
**                          uninitialized source key element                  **
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
**                        Csm_PrvJobModeValidate                              **
**                        Csm_PrvClearJobState                                **
**                        Csm_PrvValidateInputPtr                             **
**                        Csm_PrvProcessService                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     ((CSM_PRIMITIVE_MAC_VERIFY_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_SIGNATURE_VERIFY_ENABLE == STD_ON)))
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_PrvServiceVerify
(
  uint32 jobId, Crypto_OperationModeType mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ptrInput, 
  VAR(uint32, AUTOMATIC) inputLength,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ptrSecondaryInput, 
  CONST(uint32, AUTOMATIC) secondaryInputLength,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) ptrVerify,
  VAR(uint8, AUTOMATIC) serviceId
)
{
  Csm_JobType *ptrCsmJob;
  Csm_QueueType *ptrCsmQueue;
  Crypto_JobType *ptrCryptoJob;
  Std_ReturnType retVal;
  boolean jobExist;

  /* To check module initialisation */
  if (FALSE == Csm_Initialisation)
  {
    /* @Trace: Csm_SUD_FUNC_470 */
    retVal = E_NOT_OK;
    #if CSM_DEV_ERROR_DETECT == STD_ON
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
    serviceId, CSM_E_UNINIT);
    #endif
  }
  else
  {
    /* Get corresponding Csm Job from listed of configured Csm Job by using
      job Id */
    ptrCsmJob = Csm_PrvGetCsmJobPtr(jobId);
    if (NULL_PTR != ptrCsmJob)
    {
      /* @Trace: Csm_SUD_FUNC_472 */
      retVal = Csm_PrvJobModeValidate(ptrCsmJob, mode);
      if (E_OK == retVal)
      {
        /* @Trace: Csm_SUD_FUNC_473 */
        ptrCsmQueue = Csm_PrvGetQueueByChannelId(ptrCsmJob->JobCryIfChannelId);
        jobExist = Csm_PrvJobQueueExist(ptrCsmQueue, ptrCsmJob, NULL_PTR);
        /* a job should not be enqueued or updated if it's already presence in
          queue except when the service is called with operation mode
          CRYPTO_OPERATIONMODE_START */
        if (TRUE == jobExist)
        {
          if (CRYPTO_OPERATIONMODE_START == (mode & CRYPTO_OPERATIONMODE_START))
          {
            Csm_PrvJobQueueRemove(ptrCsmQueue, ptrCsmJob);
            retVal = E_OK;
          }
          else
          {
            retVal = CRYPTO_E_BUSY;
          }
        }
        else
        {
          retVal = E_OK;
        }
      }
    }
    else
    {
      /* @Trace: Csm_SUD_FUNC_471 */
      retVal = E_NOT_OK;
    }
    
    if (E_OK == retVal)
    {
      ptrCryptoJob = ptrCsmJob->CryptoJob;
      /* Clear job state when mode is CRYPTO_OPERATIONMODE_START */
      if ((mode & CRYPTO_OPERATIONMODE_START) == CRYPTO_OPERATIONMODE_START)
      {
        /* @Trace: Csm_SUD_FUNC_474 */
        Csm_PrvClearJobState(ptrCryptoJob);
      }
      /* Prepare jobRedirectionInfo buffer */
      Csm_PrvCopyJobRedirectionInfo(ptrCryptoJob->jobRedirectionInfoRef,
        ptrCsmJob->PtrJobRedirectionInfoRef);
      if (CRYPTO_OPERATIONMODE_UPDATE == (mode & CRYPTO_OPERATIONMODE_UPDATE))
      {
        /* @Trace: Csm_SUD_FUNC_475 */
        /* To validate inputPtr parameter */
        retVal = Csm_PrvValidateInputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                    ptrInput, inputLength, serviceId,
                    CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT);
      }
      if ((E_OK == retVal) &&
        (CRYPTO_OPERATIONMODE_FINISH == (mode & CRYPTO_OPERATIONMODE_FINISH)))
      {
        /* @Trace: Csm_SUD_FUNC_476 */
        /* To validate secondaryInputPtr parameter */
        retVal = Csm_PrvValidateInputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                    ptrSecondaryInput, secondaryInputLength, serviceId,
                    CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT);
        if ((E_OK == retVal) && (NULL_PTR == ptrVerify))
        {
          retVal = E_NOT_OK;
          #if CSM_DEV_ERROR_DETECT == STD_ON
          (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
          serviceId, CSM_E_PARAM_POINTER);
          #endif
        }
      }
      if (E_OK == retVal)
      {
        /* @Trace: Csm_SUD_FUNC_477 */
        SchM_Enter_Csm_GLOBALVAR_PROTECTION();
        /* mode is already checked before, no need to re-check again */
        ptrCryptoJob->jobPrimitiveInputOutput.mode = mode;
        ptrCryptoJob->jobPrimitiveInputOutput.verifyPtr = ptrVerify;
        ptrCryptoJob->jobPrimitiveInputOutput.inputPtr = ptrInput;
        ptrCryptoJob->jobPrimitiveInputOutput.inputLength = inputLength;
        ptrCryptoJob->jobPrimitiveInputOutput.secondaryInputPtr = \
                                                        ptrSecondaryInput;
        ptrCryptoJob->jobPrimitiveInputOutput.secondaryInputLength = \
                                                        secondaryInputLength;
        SchM_Exit_Csm_GLOBALVAR_PROTECTION();
        retVal = Csm_PrvProcessService(ptrCsmJob, serviceId);
      }
    }
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Csm_PrvKeyManComDevErrCheck                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Common development error checking for key           **
**                        management interface                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : serviceId : The service ID of caller (CSM API)      **
**                        keyId : The identifier of key to be checked         **
**                        targetKeyId : The identifier of target key to be    **
**                                      checked                               **
**                        ptrInput : Input pointer to be checked              **
**                        ptrOutput : Output pointer to be checked            **
**                        ptrOutputLength : Output length pointer to be       **
**                                          checked                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: No error                                      **
**                        E_NOT_OK: Error occurred                            **
**                                                                            **
** Preconditions        : Csm module should be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Csm_Initialisation                                  **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                                                                            **
*******************************************************************************/
#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_PrvKeyManComDevErrCheck
(
  VAR(uint8, AUTOMATIC) serviceId,
  VAR(uint32, AUTOMATIC) keyId,
  VAR(uint32, AUTOMATIC) targetKeyId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ptrInput,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) ptrOutput,
  P2CONST(uint32, AUTOMATIC, CSM_APPL_DATA) ptrOutputLength
)
{
  /* Return variable */
  VAR(Std_ReturnType, AUTOMATIC) retVal;

  /* Check if module is uninitialized */
  if (TRUE != Csm_Initialisation)
  {
    /* @Trace: Csm_SUD_FUNC_480 */
    retVal = E_NOT_OK;
    #if CSM_DEV_ERROR_DETECT == STD_ON
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
    serviceId, CSM_E_UNINIT);
    #endif
  }
  /* Check if key ID is out of range. If service IDs are
    CSM_KEY_ELEMENT_COPY_SID, CSM_KEY_COPY_SID,
    CSM_KEY_ELEMENT_COPY_PARTIAL_SID, CSM_KEY_DERIVE_SID and
    CSM_JOB_KEY_DERIVE_SID, targetKeyId is also checked */
  else if ((CSM_TOTAL_CONFIGURED_KEY <= keyId) || \
           (((CSM_KEY_ELEMENT_COPY_SID == serviceId) || \
             (CSM_KEY_COPY_SID == serviceId) || \
             (CSM_KEY_ELEMENT_COPY_PARTIAL_SID == serviceId) || \
             (CSM_KEY_DERIVE_SID == serviceId) || \
             (CSM_JOB_KEY_DERIVE_SID == serviceId)) && \
            (CSM_TOTAL_CONFIGURED_KEY <= targetKeyId)))
  {
    /* @Trace: Csm_SUD_FUNC_481 */
    retVal = E_NOT_OK;
    #if CSM_DEV_ERROR_DETECT == STD_ON
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
    serviceId, CSM_E_PARAM_HANDLE);
    #endif
  }
  /* Check if pointer parameters are NULL_PTR. If service IDs are
    CSM_KEY_ELEMENT_SET_SID, CSM_RANDOM_SEED_SID and
    CSM_KEY_EXCHANGE_CALC_SECRET_SID, input pointer is checked. If service IDs
    are CSM_KEY_ELEMENT_GET_SID and CSM_KEY_EXCHANGE_CALC_PUB_VAL_SID, output
    pointer and output length pointer are checked */
  else if ((((CSM_KEY_ELEMENT_SET_SID == serviceId) || \
             (CSM_RANDOM_SEED_SID == serviceId) || \
             (CSM_KEY_EXCHANGE_CALC_SECRET_SID == serviceId)) && \
            (NULL_PTR == ptrInput)) || \
           (((CSM_KEY_ELEMENT_GET_SID == serviceId) || \
             (CSM_KEY_EXCHANGE_CALC_PUB_VAL_SID == serviceId)) && \
            ((NULL_PTR == ptrOutput) || \
             (NULL_PTR == ptrOutputLength))))
  {
    /* @Trace: Csm_SUD_FUNC_482 */
    retVal = E_NOT_OK;
    #if CSM_DEV_ERROR_DETECT == STD_ON
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
    serviceId, CSM_E_PARAM_POINTER);
    #endif
  }
  else
  {
    /* @Trace: Csm_SUD_FUNC_483 */
    retVal = E_OK;
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_PrvJobKeyManComProcess                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Common development error checking for key copy and  **
**                        derive interface                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : serviceId : The service ID of caller (CSM API)      **
**                        jobId : The identifier of job                       **
**                        keyId : The identifier of key                       **
**                        targetKeyId : The identifier of target key          **
**                        ptrInput : Input pointer                            **
**                        inputLength : Input length                          **
**                                                                            **
** InOut parameter      : ptrOutputLength : Output length pointer             **
**                                                                            **
** Output Parameters    : ptrOutput : Output pointer                          **
**                                                                            **
** Return parameter     : E_OK: No error                                      **
**                        E_NOT_OK: Error occurred                            **
**                                                                            **
** Preconditions        : Csm module should be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_PrvKeyManComDevErrCheck                         **
**                        Csm_PrvGetCsmJobPtr                                 **
**                        Csm_PrvGetQueueByChannelId                          **
**                        Csm_PrvJobQueueExist                                **
**                        Csm_PrvValidateInputPtr                             **
**                        Csm_PrvValidateOutputPtr                            **
**                        Csm_PrvProcessService                               **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     ((CSM_PRIMITIVE_JOB_RANDOM_SEED_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_JOB_KEY_SET_VALID_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_JOB_KEY_GENERATE_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_JOB_KEY_DERIVE_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_PUB_VAL_ENABLE == STD_ON) || \
      (CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_SECRET_ENABLE == STD_ON)))
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_PrvJobKeyManComProcess
(
  VAR(uint8, AUTOMATIC) serviceId,
  VAR(uint32, AUTOMATIC) jobId,
  VAR(uint32, AUTOMATIC) keyId,
  VAR(uint32, AUTOMATIC) targetKeyId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ptrInput,
  VAR(uint32, AUTOMATIC) inputLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) ptrOutput,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) ptrOutputLength
)
{
  Csm_JobType *ptrCsmJob;
  Csm_QueueType *ptrCsmQueue;
  Crypto_JobType *ptrCryptoJob;
  Std_ReturnType retVal;
  boolean jobExist;
  boolean localInDriver;
  /* CSM key management common development error checking */
  retVal = Csm_PrvKeyManComDevErrCheck(serviceId, keyId, targetKeyId, \
                                        ptrInput, ptrOutput, ptrOutputLength);
  if (E_OK == retVal)
  {
    /* @Trace: Csm_SUD_FUNC_490 */
    /* Get corresponding Csm Job from listed of configured Csm Job by using
      job Id */
    ptrCsmJob = Csm_PrvGetCsmJobPtr(jobId);
    if (NULL_PTR != ptrCsmJob)
    {
      /* @Trace: Csm_SUD_FUNC_491 */
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
        /* A job should not be enqueued or updated if it's already in queue */
        jobExist = Csm_PrvJobQueueExist(ptrCsmQueue, ptrCsmJob, NULL_PTR);
        if (TRUE == jobExist)
        {
          retVal = CRYPTO_E_BUSY;
        }
      }
    }
    else
    {
      /* @Trace: Csm_SUD_FUNC_495 */
      retVal = E_NOT_OK;
    }
    if (E_OK == retVal)
    {
      /* @Trace: Csm_SUD_FUNC_492 */
      ptrCryptoJob = ptrCsmJob->CryptoJob;
      /* If service IDs are CSM_JOB_RANDOM_SEED_SID,
        CSM_JOB_KEY_EXCHANGE_CALC_PUB_VAL_SID and
        CSM_JOB_KEY_EXCHANGE_CALC_SECRET_SID,
        prepare jobRedirectionInfo buffer */
      if ((CSM_JOB_RANDOM_SEED_SID == serviceId) || \
          (CSM_JOB_KEY_EXCHANGE_CALC_PUB_VAL_SID == serviceId) || \
          (CSM_JOB_KEY_EXCHANGE_CALC_SECRET_SID == serviceId))
      {
        Csm_PrvCopyJobRedirectionInfo(ptrCryptoJob->jobRedirectionInfoRef, \
                                      ptrCsmJob->PtrJobRedirectionInfoRef);
      }
      /* There is no mode parameter in API so we need to check input and output
        regardless of operation mode */
      /* If service IDs are CSM_JOB_RANDOM_SEED_SID and
        CSM_JOB_KEY_EXCHANGE_CALC_SECRET_SID, input parameters shall be
        validated */
      #if ((CSM_PRIMITIVE_JOB_RANDOM_SEED_ENABLE == STD_ON) || \
          (CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_SECRET_ENABLE == STD_ON))
      if ((CSM_JOB_RANDOM_SEED_SID == serviceId) || \
          (CSM_JOB_KEY_EXCHANGE_CALC_SECRET_SID == serviceId))
      {
        
        retVal = Csm_PrvValidateInputPtr(ptrCryptoJob->jobRedirectionInfoRef, \
                                          ptrInput, inputLength, serviceId, \
                                          CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT);
      }
      #endif
      /* If service ID is CSM_JOB_KEY_EXCHANGE_CALC_PUB_VAL_SID, output
        parameters shall be validated */
      #if (CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_PUB_VAL_ENABLE == STD_ON)
      if (CSM_JOB_KEY_EXCHANGE_CALC_PUB_VAL_SID == serviceId)
      {
        retVal = Csm_PrvValidateOutputPtr(ptrCryptoJob->jobRedirectionInfoRef, \
                                        ptrOutput, ptrOutputLength, serviceId, \
                                        CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT);
      }
      #endif
	#if ((CSM_PRIMITIVE_JOB_RANDOM_SEED_ENABLE == STD_ON) || \
		(CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_SECRET_ENABLE == STD_ON) || \
      	  (CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_PUB_VAL_ENABLE == STD_ON))
      if (E_OK == retVal)
      {
	#endif
        /* @Trace: Csm_SUD_FUNC_494 */
        SchM_Enter_Csm_GLOBALVAR_PROTECTION();
        /* The operation mode of job shall be set to
          CRYPTO_OPERATIONMODE_SINGLECALL */
        ptrCryptoJob->jobPrimitiveInputOutput.mode = \
                                  CRYPTO_OPERATIONMODE_SINGLECALL;
        /* Key ID shall be mapped to CryIf key ID */
        ptrCryptoJob->jobPrimitiveInputOutput.cryIfKeyId = \
                                  Csm_KeyList[keyId].CryIfKeyId;
        SchM_Exit_Csm_GLOBALVAR_PROTECTION();
        /* If service ID is CSM_JOB_KEY_DERIVE_SID, target key ID shall be
          mapped to target CryIf key ID */
        if (CSM_JOB_KEY_DERIVE_SID == serviceId)
        {
          SchM_Enter_Csm_GLOBALVAR_PROTECTION();
          ptrCryptoJob->jobPrimitiveInputOutput.targetCryIfKeyId = \
                                  Csm_KeyList[targetKeyId].CryIfKeyId;
          SchM_Exit_Csm_GLOBALVAR_PROTECTION();
        }
        /* If service IDs are CSM_JOB_RANDOM_SEED_SID and
          CSM_JOB_KEY_EXCHANGE_CALC_SECRET_SID, input parameters shall be updated */
        else if ((CSM_JOB_RANDOM_SEED_SID == serviceId) || \
                 (CSM_JOB_KEY_EXCHANGE_CALC_SECRET_SID == serviceId))
        {
          SchM_Enter_Csm_GLOBALVAR_PROTECTION();
          ptrCryptoJob->jobPrimitiveInputOutput.inputPtr = ptrInput;
          ptrCryptoJob->jobPrimitiveInputOutput.inputLength = inputLength;
          SchM_Exit_Csm_GLOBALVAR_PROTECTION();
        }
        /* If service ID is CSM_JOB_KEY_EXCHANGE_CALC_PUB_VAL_SID, output
          parameters shall be updated */
        else if (CSM_JOB_KEY_EXCHANGE_CALC_PUB_VAL_SID == serviceId)
        {
          SchM_Enter_Csm_GLOBALVAR_PROTECTION();
          ptrCryptoJob->jobPrimitiveInputOutput.outputPtr = ptrOutput;
          ptrCryptoJob->jobPrimitiveInputOutput.outputLengthPtr = \
                                                         ptrOutputLength;
          SchM_Exit_Csm_GLOBALVAR_PROTECTION();
        }
        else
        {
          /* MISRA compliant */
        }
        retVal = Csm_PrvProcessService(ptrCsmJob, serviceId);
	#if ((CSM_PRIMITIVE_JOB_RANDOM_SEED_ENABLE == STD_ON) || \
		(CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_SECRET_ENABLE == STD_ON) || \
      	  (CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_PUB_VAL_ENABLE == STD_ON))
      }
	#endif
    }
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_PrvCopyJobRedirectionInfo                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Copy JobRedirectionInfo from ROM to RAM             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrDest : destination to copy JobRedirectionInfo to **
**                                  (RAM)                                     **
**                        ptrSource : source to copy JobRedirectionInfo from  **
**                                    (ROM)                                   **
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
**                                                                            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#if (CSM_JOB_PROCESSING_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CSM_CODE) Csm_PrvCopyJobRedirectionInfo
(
  P2VAR(Crypto_JobRedirectionInfoType, AUTOMATIC, CSM_APPL_DATA) ptrDest,
  P2CONST(Crypto_JobRedirectionInfoType, AUTOMATIC, CSM_APPL_CONST) ptrSource
)
{
  /* @Trace: Csm_SUD_FUNC_500 */
  if (NULL_PTR != ptrDest)
  {
    ptrDest->redirectionConfig = ptrSource->redirectionConfig;
    ptrDest->inputKeyId = ptrSource->inputKeyId;
    ptrDest->inputKeyElementId = ptrSource->inputKeyElementId;
    ptrDest->secondaryInputKeyId = ptrSource->secondaryInputKeyId;
    ptrDest->secondaryInputKeyElementId = ptrSource->secondaryInputKeyElementId;
    ptrDest->tertiaryInputKeyId = ptrSource->tertiaryInputKeyId;
    ptrDest->tertiaryInputKeyElementId = ptrSource->tertiaryInputKeyElementId;
    ptrDest->outputKeyId = ptrSource->outputKeyId;
    ptrDest->outputKeyElementId = ptrSource->outputKeyElementId;
    ptrDest->secondaryOutputKeyId = ptrSource->secondaryOutputKeyId;
    ptrDest->secondaryOutputKeyElementId = \
                                   ptrSource->secondaryOutputKeyElementId;
  }
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_PrvCallbackNotification                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This service provides callback notification to a    **
**                        pre-comfigured callback function                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : job : Holds the indentifier of the job              **
**                              to be canceled                                **
**                        result : Contains the result of the cryptographic   **
**                                 operation.                                 **
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
FUNC(void, CSM_CODE) Csm_PrvCallbackNotification
(
  VAR(uint8, AUTOMATIC) serviceId,
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
  VAR(Csm_ResultType, AUTOMATIC) result
)
{
  Csm_JobType *ptrCsmJob;
  Crypto_JobType *ptrCryptoJob;
  #if (CSM_APPLICATION_CALLBACK_ENABLE == STD_ON)
  uint32 callbackId;
  #endif

#if CSM_DEV_ERROR_DETECT == STD_OFF
  CSM_UNUSED(serviceId);
#endif
  if (NULL_PTR != job)
  {
    /* @Trace: Csm_SUD_FUNC_511 */
    ptrCsmJob = Csm_PrvGetCsmJobPtr(job->jobId);
    if (NULL_PTR != ptrCsmJob)
    {
      SchM_Enter_Csm_GLOBALVAR_PROTECTION();
      ptrCsmJob->InDriver = FALSE;
      SchM_Exit_Csm_GLOBALVAR_PROTECTION();
      /* To use this service, a job must be asynchronous */
      ptrCryptoJob = ptrCsmJob->CryptoJob;
      /* @Trace: Csm_SUD_FUNC_512 */
      if (CRYPTO_PROCESSING_ASYNC == \
                 ptrCryptoJob->jobPrimitiveInfo->processingType)
      {
        /* @Trace: Csm_SUD_FUNC_513 */
        if (CRYPTO_USE_FNC == ptrCsmJob->PortType)
        {
          #if (CSM_APPLICATION_CALLBACK_ENABLE == STD_ON)
          callbackId = ptrCryptoJob->jobPrimitiveInfo->callbackId;
          /* call configured application callback */
          Csm_ApplicationCallback[callbackId](ptrCryptoJob->jobId, result);
          #endif
        }
        else if (CRYPTO_USE_PORT_OPTIMIZED == ptrCsmJob->PortType)
        {
          /* @Trace: Csm_SUD_FUNC_514 */
          /* call rte callback notification */
          if (NULL_PTR != ptrCsmJob->RteCallbackNotification)
          {
            ptrCsmJob->RteCallbackNotification(result);
          }
        }
        else
        {
          /* To make polyspace happy */
        }
      }
      else
      {
        /* service failed because it is called with synchronous job */
        #if CSM_DEV_ERROR_DETECT == STD_ON
        (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        serviceId, CSM_E_PROCESSING_MODE);
        #endif
      }
    }
  }
  else
  {
    /* @Trace: Csm_SUD_FUNC_510 */
    #if CSM_DEV_ERROR_DETECT == STD_ON
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
    serviceId, CSM_E_PARAM_POINTER);
    #endif
  }
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
