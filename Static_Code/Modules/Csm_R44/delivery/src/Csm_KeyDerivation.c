/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_KeyDerivation.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Key derivation interface of Csm                               **
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
** Function Name        : Csm_KeyDerive                                       **
**                                                                            **
** Service ID           : 0x6b                                                **
**                                                                            **
** Description          : Derives a new key by using the key elements in the  **
**                        given key identified by the keyId. The given key    **
**                        contains the key elements for the password and      **
**                        salt. The derived key is stored in the key element  **
**                        with the id 1 of the key identified by              **
**                        targetCryptoKeyId                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant, but not for same keyId                   **
**                                                                            **
** Input Parameters     : keyId: Holds the identifier of the key which is     **
**                               used for key derivation                      **
**                        targetKeyId: Holds the identifier of the key which  **
**                                     is used to store the derived key       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Request successful                            **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, Crypto Driver Object **
**                                       is busy                              **
**                        CRYPTO_E_KEY_READ_FAIL: Request failed, not allowed **
**                                                to extract key element      **
**                        CRYPTO_E_KEY_WRITE_FAIL: Request failed, not        **
**                                                 allowed to write key       **
**                                                 element                    **
**                        CRYPTO_E_KEY_NOT_VALID: Request failed, the key's   **
**                                                state is "invalid"          **
**                        CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, key     **
**                                                    element sizes are not   **
**                                                    compatible              **
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
**                        CryIf_KeyDerive                                     **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00103 */
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyDerive
(
  VAR(uint32, AUTOMATIC) keyId,
  VAR(uint32, AUTOMATIC) targetKeyId
)
{
  /* Return variable */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Source CryIf key ID */
  VAR(uint32, AUTOMATIC) cryIfKeyId;
  /* Target CryIf key ID */
  VAR(uint32, AUTOMATIC) targetCryIfKeyId;
  /* @Trace: Csm_SUD_FUNC_100 */
  /* CSM key management common development error checking. Input pointer, output
    pointer and output length pointer set to NULL_PTR */
  retVal = Csm_PrvKeyManComDevErrCheck(CSM_KEY_DERIVE_SID, keyId, targetKeyId, \
    NULL_PTR, NULL_PTR, NULL_PTR);
  
  if (E_OK == retVal)
  {
    /* @Trace: Csm_SUD_FUNC_101 */
    cryIfKeyId = Csm_KeyList[keyId].CryIfKeyId;
    targetCryIfKeyId = Csm_KeyList[targetKeyId].CryIfKeyId;
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Derive to 1 */
    Csm_KeyManIsProcessing ^= CSM_KEYDERIVE_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    retVal = CryIf_KeyDerive(cryIfKeyId, targetCryIfKeyId);
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Derive to 0 */
    Csm_KeyManIsProcessing ^= CSM_KEYDERIVE_ISPROCESSING;
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
