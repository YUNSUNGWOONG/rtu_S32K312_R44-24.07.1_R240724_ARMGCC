/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_AEAD.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Authenticated Encryption with Asociated Data service of Csm   **
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
** Function Name        : Csm_AEADEncrypt                                     **
**                                                                            **
** Service ID           : 0x62                                                **
**                                                                            **
** Description          : Uses the given data to perform an AEAD encryption   **
**                        and stores the ciphertext and the MAC in the memory **
**                        locations pointed by the ciphertext pointer and     **
**                        Tag pointer                                         **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId : Holds the identifier of the job using the   **
**                                CSM service                                 **
**                        mode : Indicates which operation mode(s) to perfom  **
**                        plaintextPtr : Contains the pointer to the data to  **
**                                  be encrypted                              **
**                        plaintextLength : Contains the number of bytes to   **
**                                     encrypt                                **
**                        associatedDataPtr: Contains the pointer to the      **
**                          associated data                                   **
**                        associatedDataLength: Contains the number of bytes  **
**                          of the associated data                            **
**                                                                            **
** InOut parameter      : ciphertextLengthPtr : Holds a pointer to the memory **
**                          location in which the output length in bytes of   **
**                          the ciphertext is stored. On calling this         **
**                          function, this parameter shall contain the size   **
**                          of the buffer in bytes provided by resultPtr. When**
**                          the request has finished, the actual length of the**
**                          returned value shall be stored                    **
**                        tagLengthPtr : Holds a pointer to the memory        **
**                          location in which the output length in bytes of   **
**                          the Tag is stored. On calling this function, this **
**                          parameter shall contain the size of the buffer in **
**                          bytes provided by resultPtr. When the request has **
**                          finished, the actual length of the returned value **
**                          shall be stored                                   **
**                                                                            **
** Output Parameters    : ciphertextPtr : Contains the pointer to the data    **
**                          where the encrypted data shall be stored          **
**                        tagPtr : Contains the pointer to the data where the **
**                          Tag shall be stored                               **
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
/* @Trace: SRS_CryptoStack_00007 */
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     (CSM_PRIMITIVE_AEADENCRYPT_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00006 */
FUNC(Std_ReturnType, CSM_CODE) Csm_AEADEncrypt
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) plaintextPtr,
  VAR(uint32, AUTOMATIC) plaintextLength,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) associatedDataPtr,
  VAR(uint32, AUTOMATIC) associatedDataLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) ciphertextPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) ciphertextLengthPtr,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) tagPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) tagLengthPtr
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
    /* @Trace: Csm_SUD_FUNC_170 */
    retVal = E_NOT_OK;
    #if CSM_DEV_ERROR_DETECT == STD_ON
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
    CSM_AEAD_ENCRYPT_SID, CSM_E_UNINIT);
    #endif
  }
  else
  {
    /* Get corresponding Csm Job from listed of configured Csm Job by using
      job Id */
    ptrCsmJob = Csm_PrvGetCsmJobPtr(jobId);
    if (NULL_PTR != ptrCsmJob)
    {
      /* @Trace: Csm_SUD_FUNC_172 */
      retVal = Csm_PrvJobModeValidate(ptrCsmJob, mode);
      if (E_OK == retVal)
      {
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
      /* @Trace: Csm_SUD_FUNC_171 */
      retVal = E_NOT_OK;
    }

    if (E_OK == retVal)
    {
      /* @Trace: Csm_SUD_FUNC_173 */
      ptrCryptoJob = ptrCsmJob->CryptoJob;
      /* Clear job state when mode is CRYPTO_OPERATIONMODE_START */
      if (CRYPTO_OPERATIONMODE_START == (mode & CRYPTO_OPERATIONMODE_START))
      {
        Csm_PrvClearJobState(ptrCryptoJob);
      }
      /* Prepare jobRedirectionInfo buffer */
      Csm_PrvCopyJobRedirectionInfo(ptrCryptoJob->jobRedirectionInfoRef,
        ptrCsmJob->PtrJobRedirectionInfoRef);
      if (CRYPTO_OPERATIONMODE_UPDATE == (mode & CRYPTO_OPERATIONMODE_UPDATE))
      {
        /* To validate inputPtr parameter */
        retVal = Csm_PrvValidateInputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                    plaintextPtr, plaintextLength, CSM_AEAD_ENCRYPT_SID,
                    CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT);
      }
      if ((E_OK == retVal) &&
        (CRYPTO_OPERATIONMODE_FINISH == (mode & CRYPTO_OPERATIONMODE_FINISH)))
      {
        /* To validate secondaryInputPtr parameter */
        retVal = Csm_PrvValidateInputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                    associatedDataPtr, associatedDataLength,
                    CSM_AEAD_ENCRYPT_SID,
                    CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT);
        if (E_OK == retVal)
        {
          /* To validate outputPtr parameter */
          retVal = Csm_PrvValidateOutputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                      ciphertextPtr, ciphertextLengthPtr, CSM_AEAD_ENCRYPT_SID,
                      CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT);
        }
        if (E_OK == retVal)
        {
          /* To validate secondaryOutputPtr parameter */
          retVal = Csm_PrvValidateOutputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                      tagPtr, tagLengthPtr, CSM_AEAD_ENCRYPT_SID,
                      CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT);
        }
      }
      else if ((E_OK == retVal) &&
        (CRYPTO_OPERATIONMODE_UPDATE == (mode & CRYPTO_OPERATIONMODE_UPDATE)))
      {
        /* To validate outputPtr parameter */
        retVal = Csm_PrvValidateOutputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                    ciphertextPtr, ciphertextLengthPtr, CSM_AEAD_ENCRYPT_SID,
                    CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT);
      }
      else
      {
        /* To make polyspace happy */
      }
      if (E_OK == retVal)
      {
        SchM_Enter_Csm_GLOBALVAR_PROTECTION();
        /* mode is already checked before, no need to re-check again */
        ptrCryptoJob->jobPrimitiveInputOutput.mode = mode;
        ptrCryptoJob->jobPrimitiveInputOutput.inputPtr = plaintextPtr;
        ptrCryptoJob->jobPrimitiveInputOutput.inputLength = plaintextLength;
        ptrCryptoJob->jobPrimitiveInputOutput.secondaryInputPtr \
                                                        = associatedDataPtr;
        ptrCryptoJob->jobPrimitiveInputOutput.secondaryInputLength \
                                                        = associatedDataLength;
        ptrCryptoJob->jobPrimitiveInputOutput.outputPtr = ciphertextPtr;
        ptrCryptoJob->jobPrimitiveInputOutput.outputLengthPtr \
                                                        = ciphertextLengthPtr;
        ptrCryptoJob->jobPrimitiveInputOutput.secondaryOutputPtr = tagPtr;
        ptrCryptoJob->jobPrimitiveInputOutput.secondaryOutputLengthPtr \
                                                        = tagLengthPtr;
        SchM_Exit_Csm_GLOBALVAR_PROTECTION();
        retVal = Csm_PrvProcessService(ptrCsmJob, CSM_AEAD_ENCRYPT_SID);
      }
    }
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : Csm_AEADDecrypt                                     **
**                                                                            **
** Service ID           : 0x63                                                **
**                                                                            **
** Description          : Uses the given data to perform an AEAD encryption   **
**                        and stores the ciphertext and the MAC in the memory **
**                        locations pointed by the ciphertext pointer and Tag **
**                        pointer                                             **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId : Holds the identifier of the job using the   **
**                                CSM service                                 **
**                        mode : Indicates which operation mode(s) to perfom  **
**                        ciphertextPtr : Contains the pointer to the data to **
**                                        be decrypted                        **
**                        ciphertextLength : Contains the number of bytes to  **
**                                           decrypt                          **
**                        associatedDataPtr: Contains the pointer to the      **
**                          associated data                                   **
**                        associatedDataLength: Contains the number of bytes  **
**                          of the associated data                            **
**                        tagPtr : Contains the pointer to the Tag to be      **
**                                 verified                                   **
**                        tagLength : Contains the length in bytes of the Tag **
**                                    to be verified                          **
**                                                                            **
** InOut parameter      : plaintextLengthPtr : Holds a pointer to the memory  **
**                          location in which the output length in bytes of   **
**                          the paintext is stored. On calling this function, **
**                          this parameter shall contain the size of the      **
**                          buffer provided by plaintextPtr. When the request **
**                          has finished, the actual length of the returned   **
**                          value shall be stored                             **
**                                                                            **
** Output Parameters    : plaintextPtr : Contains the pointer to the data     **
**                          where the decrypted data shall be stored          **
**                        verifyPtr : Contains the pointer to the result of   **
**                          the verification                                  **
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
/* @Trace: SRS_CryptoStack_00007 */
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     (CSM_PRIMITIVE_AEADDECRYPT_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00006 */
FUNC(Std_ReturnType, CSM_CODE) Csm_AEADDecrypt
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ciphertextPtr,
  VAR(uint32, AUTOMATIC) ciphertextLength,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) associatedDataPtr,
  VAR(uint32, AUTOMATIC) associatedDataLength,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) tagPtr,
  VAR(uint32, AUTOMATIC) tagLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) plaintextPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) plaintextLengthPtr,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
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
    /* @Trace: Csm_SUD_FUNC_180 */
    retVal = E_NOT_OK;
    #if CSM_DEV_ERROR_DETECT == STD_ON
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
    CSM_AEAD_DECRYPT_SID, CSM_E_UNINIT);
    #endif
  }
  else
  {
    /* Get corresponding Csm Job from listed of configured Csm Job by using
      job Id */
    ptrCsmJob = Csm_PrvGetCsmJobPtr(jobId);
    if (NULL_PTR != ptrCsmJob)
    {
      /* @Trace: Csm_SUD_FUNC_182 */
      retVal = Csm_PrvJobModeValidate(ptrCsmJob, mode);
      if (E_OK == retVal)
      {
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
      /* @Trace: Csm_SUD_FUNC_181 */
      retVal = E_NOT_OK;
    }

    if (E_OK == retVal)
    {
      /* @Trace: Csm_SUD_FUNC_183 */
      ptrCryptoJob = ptrCsmJob->CryptoJob;
      /* Clear job state when mode is CRYPTO_OPERATIONMODE_START */
      if (CRYPTO_OPERATIONMODE_START == (mode & CRYPTO_OPERATIONMODE_START))
      {
        Csm_PrvClearJobState(ptrCryptoJob);
      }
      /* Prepare jobRedirectionInfo buffer */
      Csm_PrvCopyJobRedirectionInfo(ptrCryptoJob->jobRedirectionInfoRef,
        ptrCsmJob->PtrJobRedirectionInfoRef);
      if (CRYPTO_OPERATIONMODE_UPDATE == (mode & CRYPTO_OPERATIONMODE_UPDATE))
      {
        /* To validate inputPtr parameter */
        retVal = Csm_PrvValidateInputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                    ciphertextPtr, ciphertextLength, CSM_AEAD_DECRYPT_SID,
                    CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT);
      }
      if ((E_OK == retVal) &&
        (CRYPTO_OPERATIONMODE_FINISH == (mode & CRYPTO_OPERATIONMODE_FINISH)))
      {
        /* To validate secondaryInputPtr parameter */
        retVal = Csm_PrvValidateInputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                    associatedDataPtr, associatedDataLength,
                    CSM_AEAD_DECRYPT_SID,
                    CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT);
        if (E_OK == retVal)
        {
          /* To validate tertiaryInputPtr parameter */
          retVal = Csm_PrvValidateInputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                      tagPtr, tagLength, CSM_AEAD_DECRYPT_SID,
                      CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT);
        }
        if (E_OK == retVal)
        {
          /* To validate outputPtr parameter */
          retVal = Csm_PrvValidateOutputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                      plaintextPtr, plaintextLengthPtr, CSM_AEAD_DECRYPT_SID,
                      CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT);
        }
        if ((E_OK == retVal) && (NULL_PTR == verifyPtr))
        {
          retVal = E_NOT_OK;
          #if CSM_DEV_ERROR_DETECT == STD_ON
          (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
          CSM_AEAD_DECRYPT_SID, CSM_E_PARAM_POINTER);
          #endif
        }
      }
      else if ((E_OK == retVal) &&
        (CRYPTO_OPERATIONMODE_UPDATE == (mode & CRYPTO_OPERATIONMODE_UPDATE)))
      {
        /* To validate outputPtr parameter */
        retVal = Csm_PrvValidateOutputPtr(ptrCryptoJob->jobRedirectionInfoRef,
                    plaintextPtr, plaintextLengthPtr, CSM_AEAD_DECRYPT_SID,
                    CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT);
      }
      else
      {
        /* To make polyspace happy */
        #if CSM_DEV_ERROR_DETECT == STD_ON
        (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
        CSM_AEAD_DECRYPT_SID, CSM_E_PARAM_POINTER);
        #endif
      }
      if (E_OK == retVal)
      {
        SchM_Enter_Csm_GLOBALVAR_PROTECTION();
        /* mode is already checked before, no need to re-check again */
        ptrCryptoJob->jobPrimitiveInputOutput.mode = mode;
        ptrCryptoJob->jobPrimitiveInputOutput.inputPtr = ciphertextPtr;
        ptrCryptoJob->jobPrimitiveInputOutput.inputLength = ciphertextLength;
        ptrCryptoJob->jobPrimitiveInputOutput.secondaryInputPtr \
                                                       = associatedDataPtr;
        ptrCryptoJob->jobPrimitiveInputOutput.secondaryInputLength \
                                                       = associatedDataLength;
        ptrCryptoJob->jobPrimitiveInputOutput.tertiaryInputPtr = tagPtr;
        ptrCryptoJob->jobPrimitiveInputOutput.tertiaryInputLength = tagLength;
        ptrCryptoJob->jobPrimitiveInputOutput.outputPtr = plaintextPtr;
        ptrCryptoJob->jobPrimitiveInputOutput.outputLengthPtr \
                                                       = plaintextLengthPtr;
        ptrCryptoJob->jobPrimitiveInputOutput.verifyPtr = verifyPtr;
        SchM_Exit_Csm_GLOBALVAR_PROTECTION();
        retVal = Csm_PrvProcessService(ptrCsmJob, CSM_AEAD_DECRYPT_SID);
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
