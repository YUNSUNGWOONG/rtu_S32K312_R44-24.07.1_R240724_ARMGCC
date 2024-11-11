/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_KeyExchange.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Key exchange interface of Csm                                 **
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
** Function Name        : Csm_KeyExchangeCalcPubVal                           **
**                                                                            **
** Service ID           : 0x6c                                                **
**                                                                            **
** Description          : Calculates the public value of the current user for **
**                        the key exchange and stores the public key in the   **
**                        memory location pointed by the public value pointer **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant, but not for same keyId                   **
**                                                                            **
** Input Parameters     : keyId: Holds the identifier of the key which shall  **
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
**                        CRYPTO_E_BUSY: Request failed, Crypto Driver Object **
**                        is busy                                             **
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
**                        CryIf_KeyExchangeCalcPubVal                         **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00028 SRS_CryptoStack_00006 */
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcPubVal
(
  VAR(uint32, AUTOMATIC) keyId,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) publicValuePtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr
)
{
  /* Return variable */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* CryIf key ID */
  VAR(uint32, AUTOMATIC) cryIfKeyId;
  /* @Trace: Csm_SUD_FUNC_110 */
  /* CSM key management common development error checking. Target CryIf key ID
    set to 0. Input pointer set to NULL_PTR */
  retVal = Csm_PrvKeyManComDevErrCheck(CSM_KEY_EXCHANGE_CALC_PUB_VAL_SID, \
                                        keyId, 0U, NULL_PTR, publicValuePtr, \
                                        publicValueLengthPtr);
  if (E_OK == retVal)
  {
    /* @Trace: Csm_SUD_FUNC_111 */
    cryIfKeyId = Csm_KeyList[keyId].CryIfKeyId;
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Exchange Pub Val to 1 */
    Csm_KeyManIsProcessing ^= CSM_KEYEXCHANGEPUBVAL_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    retVal = CryIf_KeyExchangeCalcPubVal(cryIfKeyId, publicValuePtr, \
                                          publicValueLengthPtr);
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Exchange Pub Val to 0 */
    Csm_KeyManIsProcessing ^= CSM_KEYEXCHANGEPUBVAL_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_KeyExchangeCalcSecret                           **
**                                                                            **
** Service ID           : 0x6d                                                **
**                                                                            **
** Description          : Calculates the shared secret key for the key        **
**                        exchange with the key material of the key           **
**                        identified by the keyId and the partner public key. **
**                        The shared secret key is stored as a key element in **
**                        the same key                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant, but not for same keyId                   **
**                                                                            **
** Input Parameters     : keyId: Holds the identifier of the key which shall  **
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
**                        CryIf_KeyExchangeCalcSecret                         **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00007 */
#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00028 SRS_CryptoStack_00006 */
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcSecret
(
  VAR(uint32, AUTOMATIC) keyId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) partnerPublicValuePtr,
  VAR(uint32, AUTOMATIC) partnerPublicValueLength
)
{
  /* Return variable */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* CryIf key ID */
  VAR(uint32, AUTOMATIC) cryIfKeyId;
  /* @Trace: Csm_SUD_FUNC_120 */
  /* CSM key management common development error checking. Target CryIf key ID
    set to 0. Output pointer and output length pointer set to NULL_PTR */
  retVal = Csm_PrvKeyManComDevErrCheck(CSM_KEY_EXCHANGE_CALC_SECRET_SID, \
                                        keyId, 0U, partnerPublicValuePtr, \
                                        NULL_PTR, NULL_PTR);
  if (E_OK == retVal)
  {
    /* @Trace: Csm_SUD_FUNC_121 */
    cryIfKeyId = Csm_KeyList[keyId].CryIfKeyId;
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    Csm_KeyManIsProcessing ^= CSM_KEYEXCHANGECALCSECRET_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    retVal = CryIf_KeyExchangeCalcSecret(cryIfKeyId, \
      partnerPublicValuePtr, partnerPublicValueLength);
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    Csm_KeyManIsProcessing ^= CSM_KEYEXCHANGECALCSECRET_ISPROCESSING;
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
