/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_JobKeyGeneration.c                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Job key generation interface of Csm                           **
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
** Function Name        : Csm_JobRandomSeed                                   **
**                                                                            **
** Service ID           : 0x7b                                                **
**                                                                            **
** Description          : This function shall dispatch the random seed        **
**                        function to the configured crypto driver object     **
**                                                                            **
** Sync/Async           : Sync or Async, depending on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId: Holds the identifier of the job using the    **
**                               CSM service                                  **
**                        keyId: Holds the identifier of the key for which a  **
**                               new seed shall be generated                  **
**                        seedPtr: Holds a pointer to the memory location     **
**                                 which contains the data to feed the seed   **
**                        seedLength: Contains the length of the seed in      **
**                                    bytes                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Request successful                            **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, service is still     **
**                                       busy                                 **
**                        CRYPTO_E_QUEUE_FULL: Request failed, the queue is   **
**                                             full                           **
**                        CRYPTO_E_KEY_NOT_VALID: Request failed, the key's   **
**                                                state is "invalid"          **
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
     (CSM_PRIMITIVE_JOB_RANDOM_SEED_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_JobRandomSeed
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(uint32, AUTOMATIC) keyId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) seedPtr,
  VAR(uint32, AUTOMATIC) seedLength
)
{
  /* @Trace: Csm_SUD_FUNC_131 */
  Std_ReturnType retVal;
  /* Target CryIf key ID set to 0. Output pointer and output length pointer set
    to NULL_PTR */
  retVal = Csm_PrvJobKeyManComProcess(CSM_JOB_RANDOM_SEED_SID, jobId, keyId, \
    0U, seedPtr, seedLength, NULL_PTR, NULL_PTR);
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_JobKeyGenerate                                  **
**                                                                            **
** Service ID           : 0x7c                                                **
**                                                                            **
** Description          : Generates new key material and stores it in the key **
**                        identified by keyId                                 **
**                                                                            **
** Sync/Async           : Sync or Async, depending on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId: Holds the identifier of the job using the    **
**                               CSM service                                  **
**                        keyId: Holds the identifier of the key for which a  **
**                               new material shall be generated              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
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
     (CSM_PRIMITIVE_JOB_KEY_GENERATE_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyGenerate
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(uint32, AUTOMATIC) keyId
)
{
  /* @Trace: Csm_SUD_FUNC_132 */
  Std_ReturnType retVal;
  /* Target CryIf key ID set to 0. Input pointer and input length set to
    NULL_PTR and 0 respectively. Output pointer and output length pointer set
    to NULL_PTR */
  retVal = Csm_PrvJobKeyManComProcess(CSM_JOB_KEY_GENERATE_SID, jobId, keyId, \
    0U, NULL_PTR, 0U, NULL_PTR, NULL_PTR);
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
