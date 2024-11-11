/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_JobKeyExchange.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Job key exchange interface of Csm                             **
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
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Csm_JobKeyExchangeCalcPubVal                        **
**                                                                            **
** Service ID           : 0x7e                                                **
**                                                                            **
** Description          : Calculates the public value of the current user for **
**                        the key exchange and stores the public key in the   **
**                        memory location pointed by the public value pointer **
**                                                                            **
** Sync/Async           : Sync or Async, depending on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId: Holds the identifier of the job using the    **
**                               CSM service                                  **
**                        keyId: Holds the identifier of the key which shall  **
**                               be used for the key exchange protocol        **
**                                                                            **
** InOut parameter      : publicValueLengthPtr: Holds a pointer to the memory **
**                                              location in which the public  **
**                                              value length information is   **
**                                              stored. On calling this       **
**                                              function, this parameter      **
**                                              shall contain the size of the **
**                                              buffer provided by            **
**                                              publicValuePtr. When the      **
**                                              request has finished, the     **
**                                              actual length of the returned **
**                                              value shall be stored         **
**                                                                            **
** Output Parameters    : publicValuePtr: Contains the pointer to the data    **
**                                        where the public value shall be     **
**                                        stored                              **
**                                                                            **
** Return parameter     : E_OK: Request successful                            **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, service is still     **
**                                       busy                                 **
**                        CRYPTO_E_QUEUE_FULL: Request failed, the queue is   **
**                                             full                           **
**                        CRYPTO_E_KEY_NOT_VALID: Request failed, the key's   **
**                                                state is "invalid"          **
**                        CRYPTO_E_KEY_EMPTY: Request failed because of       **
**                                            uninitialized source key        **
**                                            element                         **
**                                                                            **
** Preconditions        : Csm module should be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_PrvJobKeyManComProcess                          **
**                                                                            **
*******************************************************************************/
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     (CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_PUB_VAL_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcPubVal
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(uint32, AUTOMATIC) keyId,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) publicValuePtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr
)
{
  /* @Trace: Csm_SUD_FUNC_134 */
  Std_ReturnType retVal;
  /* Target CryIf key ID set to 0. Input pointer and input length set to
    NULL_PTR and 0 respectively */
  retVal = Csm_PrvJobKeyManComProcess(CSM_JOB_KEY_EXCHANGE_CALC_PUB_VAL_SID, \
                                      jobId, keyId, 0U, NULL_PTR, 0U, \
                                      publicValuePtr, publicValueLengthPtr);
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_JobKeyExchangeCalcSecret                        **
**                                                                            **
** Service ID           : 0x7f                                                **
**                                                                            **
** Description          : Calculates the shared secret key for the key        **
**                        exchange with the key material of the key           **
**                        identified by the keyId and the partner public key. **
**                        The shared secret key is stored as a key element in **
**                        the same key                                        **
**                                                                            **
** Sync/Async           : Sync or Async, depending on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId: Holds the identifier of the job using the    **
**                               CSM service                                  **
**                        keyId: Holds the identifier of the key which shall  **
**                               be used for the key exchange protocol        **
**                        partnerPublicValuePtr: Holds the pointer to the     **
**                                               memory location which        **
**                                               contains the partner's       **
**                                               public value                 **
**                        partnerPublicValueLength: Contains the length of    **
**                                                  the partner's public      **
**                                                  value in bytes            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Request successful                            **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, Crypto Driver Object **
**                                       is busy                              **
**                        CRYPTO_E_QUEUE_FULL: Request failed, the queue is   **
**                                             full                           **
**                        CRYPTO_E_KEY_NOT_VALID: Request failed, the key's   **
**                                                state is "invalid"          **
**                        CRYPTO_E_KEY_EMPTY: Request failed because of       **
**                                            uninitialized source key        **
**                                            element                         **
**                                                                            **
** Preconditions        : Csm module should be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_PrvJobKeyManComProcess                          **
**                                                                            **
*******************************************************************************/
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     (CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_SECRET_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcSecret
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(uint32, AUTOMATIC) keyId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) partnerPublicValuePtr,
  VAR(uint32, AUTOMATIC) partnerPublicValueLength
)
{
  /* @Trace: Csm_SUD_FUNC_135 */
  Std_ReturnType retVal;
  /* Target CryIf key ID set to 0. Output pointer and output length pointer set
    to NULL_PTR */
  retVal = Csm_PrvJobKeyManComProcess(CSM_JOB_KEY_EXCHANGE_CALC_SECRET_SID, \
    jobId, keyId, 0U, partnerPublicValuePtr, \
    partnerPublicValueLength, NULL_PTR, NULL_PTR);
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
