/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_Cipher.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Cipher service of Csm                                         **
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
** 1.0.1.0   10-Mar-2021   TamTV6       Add trace SUD                         **
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
** Function Name        : Csm_Encrypt                                         **
**                                                                            **
** Service ID           : 0x5E                                                **
**                                                                            **
** Description          : Encrypts the given data and store the ciphertext in **
**                        the memory location pointed by the result pointer   **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId : Holds the identifier of the job using the   **
**                                CSM service                                 **
**                        mode : Indicates which operation mode(s) to perfom  **
**                        dataPtr : Contains the pointer to the data to be    **
**                                  encrypted                                 **
**                        dataLength : Contains the number of bytes to encrypt**
**                                                                            **
** InOut parameter      : resultLengthPtr : Holds a pointer to the memory     **
**                          location in which the output length in bytes is   **
**                          stored. On calling this function, this parameter  **
**                          shall contain the size of the buffer provided by  **
**                          resultPtr. When the request has finished, the     **
**                          actual length of the returned value shall be      **
**                          stored                                            **
**                                                                            **
** Output Parameters    : resultPtr : Contains the pointer to the data where  **
**                                    the encrypted data shall be stored      **
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
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_PrvServiceGenerate                              **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00007 */
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     (CSM_PRIMITIVE_ENCRYPT_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00020 SRS_CryptoStack_00021 SRS_CryptoStack_00006 */
FUNC(Std_ReturnType, CSM_CODE) Csm_Encrypt
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) dataPtr,
  VAR(uint32, AUTOMATIC) dataLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  /* @Trace: Csm_SUD_FUNC_008 */
  Std_ReturnType retVal;
  retVal = Csm_PrvServiceGenerate(jobId, mode, dataPtr, dataLength, resultPtr,
                          resultLengthPtr, CSM_ENCRYPT_SID);
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_Decrypt                                         **
**                                                                            **
** Service ID           : 0x5F                                                **
**                                                                            **
** Description          : Decrypts the given encrypted data and store the     **
**                        decrypted plaintext in the memory location pointed  **
**                        by the result pointer.                              **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId : Holds the identifier of the job using the   **
**                                CSM service                                 **
**                        mode : Indicates which operation mode(s) to perfom  **
**                        dataPtr : Contains the pointer to the data to be    **
**                                  decrypted                                 **
**                        dataLength : Contains the number of bytes to decrypt**
**                                                                            **
** InOut parameter      : resultLengthPtr : Holds a pointer to the memory     **
**                          location in which the output length in bytes is   **
**                          stored. On calling this function, this parameter  **
**                          shall contain the size of the buffer provided by  **
**                          resultPtr. When the request has finished, the     **
**                          actual length of the returned value shall be      **
**                          stored                                            **
**                                                                            **
** Output Parameters    : resultPtr : Contains the pointer to the data where  **
**                                    the decrypted data shall be stored      **
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
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_PrvServiceGenerate                              **
*******************************************************************************/
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     (CSM_PRIMITIVE_DECRYPT_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00020 SRS_CryptoStack_00021 */
FUNC(Std_ReturnType, CSM_CODE) Csm_Decrypt
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) dataPtr,
  VAR(uint32, AUTOMATIC) dataLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  /* @Trace: Csm_SUD_FUNC_009 */
  Std_ReturnType retVal;
  retVal = Csm_PrvServiceGenerate(jobId, mode, dataPtr, dataLength, resultPtr,
                          resultLengthPtr, CSM_DECRYPT_SID);
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
