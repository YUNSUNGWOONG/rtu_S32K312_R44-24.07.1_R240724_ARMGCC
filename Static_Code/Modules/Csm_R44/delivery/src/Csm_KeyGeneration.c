/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_KeyGeneration.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Key generation interface of Csm                               **
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
** 1.0.1.0   10-Mar-2021   TamTV6       Fix #17942, Add trace SUD             **
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
** Function Name        : Csm_RandomSeed                                      **
**                                                                            **
** Service ID           : 0x69                                                **
**                                                                            **
** Description          : Feeds the key element CRYPTO_KE_RANDOM_SEED with a  **
**                        random seed                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant, but not for same keyId                   **
**                                                                            **
** Input Parameters     : keyId: Holds the identifier of the key for which a  **
**                               new seed shall be generated                  **
**                        seedPtr: Holds a pointer to the memory location     **
**                                 which contains the data to feed the seed   **
**                                 seedLength Contains the length of the seed **
**                                 in bytes                                   **
**                        seedLength: Contains the length of the seed in      **
**                                    bytes                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Request successful                            **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, Crypto Driver Object **
**                                       is busy                              **
**                        CRYPTO_E_KEY_NOT_VALID: Request failed, the key's   **
**                        state is "invalid"                                  **
**                                                                            **
** Preconditions        : Csm module should be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_PrvKeyManComDevErrCheck                         **
**                        CryIf_RandomSeed                                    **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00007 */
#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_RandomSeed
(
  VAR(uint32, AUTOMATIC) keyId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) seedPtr,
  VAR(uint32, AUTOMATIC) seedLength
)
{
  /* Return variable */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* CryIf key ID */
  VAR(uint32, AUTOMATIC) cryIfKeyId;
  /* @Trace: Csm_SUD_FUNC_080 */
  /* CSM key management common development error checking. Target CryIf key ID
    set to 0. Output pointer and output length pointer set to NULL_PTR */
  retVal = Csm_PrvKeyManComDevErrCheck(CSM_RANDOM_SEED_SID, keyId, 0U, \
    seedPtr, NULL_PTR, NULL_PTR);
  if (E_OK == retVal)
  {
	/* @Trace: Csm_SUD_FUNC_081 */
    cryIfKeyId = Csm_KeyList[keyId].CryIfKeyId;
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Random Seed to 1 */
    Csm_KeyManIsProcessing ^= CSM_RANDOMSEED_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    retVal = CryIf_RandomSeed(cryIfKeyId, seedPtr, seedLength);
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Random Seed to 0 */
    Csm_KeyManIsProcessing ^= CSM_RANDOMSEED_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_KeyGenerate                                     **
**                                                                            **
** Service ID           : 0x6a                                                **
**                                                                            **
** Description          : Generates new key material and store it in the key  **
**                        identified by keyId                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant, but not for same keyId                   **
**                                                                            **
** Input Parameters     : keyId: Holds the identifier of the key for which a  **
**                               new material shall be generated              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Request successful                            **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, Crypto Driver Object **
**                                       is busy                              **
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
**                        Csm_PrvKeyManComDevErrCheck                         **
**                        CryIf_KeyGenerate                                   **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00007 */
#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00026 SRS_CryptoStack_00027 SRS_CryptoStack_00006 */
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyGenerate
(
  VAR(uint32, AUTOMATIC) keyId
)
{
  /* Return variable */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* CryIf key ID */
  VAR(uint32, AUTOMATIC) cryIfKeyId;
  /* @Trace: Csm_SUD_FUNC_090 */
  /* CSM key management common development error checking. Target CryIf key ID
    set to 0. Input pointer, output pointer and output length pointer set to
    NULL_PTR */
  retVal = Csm_PrvKeyManComDevErrCheck(CSM_KEY_GENERATE_SID, keyId, 0U, \
    NULL_PTR, NULL_PTR, NULL_PTR);
  
  if (E_OK == retVal)
  {
    /* @Trace: Csm_SUD_FUNC_091 */
    cryIfKeyId = Csm_KeyList[keyId].CryIfKeyId;
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Generate to 1 */
    Csm_KeyManIsProcessing ^= CSM_KEYGENERATE_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    retVal = CryIf_KeyGenerate(cryIfKeyId);
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Generate to 0 */
    Csm_KeyManIsProcessing ^= CSM_KEYGENERATE_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();    
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
