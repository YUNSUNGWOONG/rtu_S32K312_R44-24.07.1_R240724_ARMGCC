/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_KeyExtraction.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Key extraction interface of Csm                               **
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
** Function Name        : Csm_KeyElementGet                                   **
**                                                                            **
** Service ID           : 0x68                                                **
**                                                                            **
** Description          : Retrieves the key element bytes from a specific key **
**                        element of the key identified by the keyId and      **
**                        stores the key element in the memory location       **
**                        pointed by the key pointer                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : keyId: Holds the identifier of the key from which a **
**                               key element shall be extracted               **
**                        keyElementId: Holds the identifier of the key       **
**                                      element to be extracted               **
**                                                                            **
** InOut parameter      : keyLengthPtr: Holds a pointer to the memory         **
**                                      location in which the output buffer   **
**                                      length in bytes is stored. On calling **
**                                      this function, this parameter shall   **
**                                      contain the buffer length in bytes of **
**                                      the keyPtr. When the request has      **
**                                      finished, the actual size of the      **
**                                      written input bytes shall be stored   **
**                                                                            **
** Output Parameters    : keyPtr: Holds the pointer to the memory location    **
**                                where the key shall be copied to            **
**                                                                            **
** Return parameter     : E_OK: Request successful                            **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, Crypto Driver Object **
**                                       is busy                              **
**                        CRYPTO_E_KEY_NOT_AVAILABLE: Request failed, the     **
**                                                    requested key element   **
**                                                    is not available        **
**                        CRYPTO_E_KEY_READ_FAIL: Request failed because read **
**                                                access was denied           **
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
**                        CryIf_KeyElementGet                                 **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00029 SRS_CryptoStack_00010 SRS_CryptoStack_00011 */
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementGet
(
  VAR(uint32, AUTOMATIC) keyId,
  VAR(uint32, AUTOMATIC) keyElementId,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) keyPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) keyLengthPtr
)
{
  /* Return variable */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* CryIf key ID */
  VAR(uint32, AUTOMATIC) cryIfKeyId;
  /* @Trace: Csm_SUD_FUNC_040 */
  /* CSM key management common development error checking. Target CryIf key ID
    set to 0. Input pointer set to NULL_PTR */
  retVal = Csm_PrvKeyManComDevErrCheck(CSM_KEY_ELEMENT_GET_SID, keyId, 0U, \
    NULL_PTR, keyPtr, keyLengthPtr);
  if (E_OK == retVal)
  {
    /* @Trace: Csm_SUD_FUNC_041 */
    cryIfKeyId = Csm_KeyList[keyId].CryIfKeyId;
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Element Get to 1 */
    Csm_KeyManIsProcessing ^= CSM_KEYELEMENTGET_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    retVal = CryIf_KeyElementGet(cryIfKeyId, keyElementId, keyPtr, \
      keyLengthPtr);
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Element Get to 0 */
    Csm_KeyManIsProcessing ^= CSM_KEYELEMENTGET_ISPROCESSING;
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
