/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_KeySetting.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Key setting interface of Csm                                  **
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
** Function Name        : Csm_KeyElementSet                                   **
**                                                                            **
** Service ID           : 0x78                                                **
**                                                                            **
** Description          : Sets the given key element bytes to the key         **
**                        identified by keyId                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : keyId: Holds the identifier of the key for which a  **
**                                new material shall be set                   **
**                        keyElementId: Holds the identifier of the key       **
**                                       element to be written                **
**                        keyPtr: Holds the pointer to the key element bytes  **
**                                  to be processed                           **
**                        keyLength: Contains the number of key element bytes **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Request successful                            **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, Crypto Driver Object **
**                                       is busy                              **
**                        CRYPTO_E_KEY_WRITE_FAIL: Request failed because     **
**                                                 write access was denied    **
**                        CRYPTO_E_KEY_NOT_AVAILABLE: Request failed because  **
**                                                    the key is not          **
**                                                    available               **
**                        CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, key     **
**                                                    element size does not   **
**                                                    match size of provided  **
**                                                    data                    **
**                                                                            **
** Preconditions        : Csm module should be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_PrvKeyManComDevErrCheck                         **
**                        CryIf_KeyElementSet                                 **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementSet
(
  VAR(uint32, AUTOMATIC) keyId,
  VAR(uint32, AUTOMATIC) keyElementId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) keyPtr,
  VAR(uint32, AUTOMATIC) keyLength
)
{
  /* Return variable */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* CryIf key ID */
  VAR(uint32, AUTOMATIC) cryIfKeyId;
  /* @Trace: Csm_SUD_FUNC_020 */
  /* CSM key management common development error checking. Target CryIf key ID
    set to 0. Output pointer and output length pointer set to NULL_PTR */
  retVal = Csm_PrvKeyManComDevErrCheck(CSM_KEY_ELEMENT_SET_SID, keyId, 0U, \
                                        keyPtr, NULL_PTR, NULL_PTR);
  
  if (E_OK == retVal)
  {
    /* @Trace: Csm_SUD_FUNC_021 */
    cryIfKeyId = Csm_KeyList[keyId].CryIfKeyId;
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Element Setting to 1 */
    Csm_KeyManIsProcessing ^= CSM_KEYELEMENTSET_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    retVal = CryIf_KeyElementSet(cryIfKeyId, keyElementId, keyPtr, \
                                  keyLength);
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Element Setting to 0 */
    Csm_KeyManIsProcessing ^= CSM_KEYELEMENTSET_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();    
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_KeySetValid                                     **
**                                                                            **
** Service ID           : 0x67                                                **
**                                                                            **
** Description          : Sets the key state of the key identified by keyId   **
**                        to valid                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : keyId : Holds the identifier of the key for which a **
**                                new material shall be validated             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Request successful                            **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, Crypto Driver Object **
**                                       is busy                              **
**                                                                            **
** Preconditions        : Csm module should be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_PrvKeyManComDevErrCheck                         **
**                        CryIf_KeySetValid                                   **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_KeySetValid
(
  VAR(uint32, AUTOMATIC) keyId
)
{
  /* Return variable */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* CryIf key ID */
  VAR(uint32, AUTOMATIC) cryIfKeyId;
  /* @Trace: Csm_SUD_FUNC_030 */
  /* CSM key management common development error checking. Target CryIf key ID
    set to 0. Input pointer, output pointer and output length pointer set to
    NULL_PTR */
  retVal = Csm_PrvKeyManComDevErrCheck(CSM_KEY_SET_VALID_SID, keyId, 0U, \
                                        NULL_PTR, NULL_PTR, NULL_PTR);
  if (E_OK == retVal)
  {
    /* @Trace: Csm_SUD_FUNC_031 */
    cryIfKeyId = Csm_KeyList[keyId].CryIfKeyId;
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Set Valid to 1 */
    Csm_KeyManIsProcessing ^= CSM_KEYSETVALID_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    retVal = CryIf_KeySetValid(cryIfKeyId);
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Set Valid to 0 */
    Csm_KeyManIsProcessing ^= CSM_KEYSETVALID_ISPROCESSING;
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
