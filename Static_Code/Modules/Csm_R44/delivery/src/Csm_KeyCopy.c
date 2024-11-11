/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_KeyCopy.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Key copying interface of Csm                                  **
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
** Function Name        : Csm_KeyElementCopy                                  **
**                                                                            **
** Service ID           : 0x71                                                **
**                                                                            **
** Description          : This function shall copy a key elements from one    **
**                        key to a target key                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant, but not for the same keyId               **
**                                                                            **
** Input Parameters     : keyId: Holds the identifier of the key whose key    **
**                               element shall be the source element          **
**                        keyElementId: Holds the identifier of the key       **
**                                      element which shall be the source for **
**                                      the copy operation                    **
**                        targetKeyId: Holds the identifier of the key whose  **
**                                     key element shall be the destination   **
**                                     element                                **
**                        targetKeyElementId: Holds the identifier of the key **
**                                            element which shall be the      **
**                                            destination for the copy        **
**                                            operation                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Request successful                            **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, Crypto Driver Object **
**                                       is busy                              **
**                        CRYPTO_E_KEY_NOT_AVAILABLE: Request failed, the     **
**                                                    requested key element   **
**                                                    is not available        **
**                        CRYPTO_E_KEY_READ_FAIL: Request failed, not allowed **
**                                                to extract key element      **
**                        CRYPTO_E_KEY_WRITE_FAIL: Request failed, not        **
**                                                 allowed to write key       **
**                                                 element                    **
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
**                        CryIf_KeyElementCopy                                **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopy
(
  VAR(uint32, CSM_CONST) keyId,
  VAR(uint32, CSM_CONST) keyElementId,
  VAR(uint32, CSM_CONST) targetKeyId,
  VAR(uint32, CSM_CONST) targetKeyElementId
)
{
  /* Return variable */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Source CryIf key ID */
  VAR(uint32, AUTOMATIC) cryIfKeyId;
  /* Target CryIf key ID */
  VAR(uint32, AUTOMATIC) targetCryIfKeyId;
  /* @Trace: Csm_SUD_FUNC_050 */
  /* CSM key management common development error checking. Input pointer, output
    pointer and output length pointer set to NULL_PTR */
  retVal = Csm_PrvKeyManComDevErrCheck(CSM_KEY_ELEMENT_COPY_SID, keyId, \
    targetKeyId, NULL_PTR, NULL_PTR, NULL_PTR);
  if (E_OK == retVal)
  {
    /* @Trace: Csm_SUD_FUNC_051 */
    cryIfKeyId = Csm_KeyList[keyId].CryIfKeyId;
    targetCryIfKeyId = Csm_KeyList[targetKeyId].CryIfKeyId;
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Element Copy to 1 */
    Csm_KeyManIsProcessing ^= CSM_KEYELEMENTCOPY_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    retVal = CryIf_KeyElementCopy(cryIfKeyId, keyElementId, \
      targetCryIfKeyId, targetKeyElementId);
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Element Copy to 0 */
    Csm_KeyManIsProcessing ^= CSM_KEYELEMENTCOPY_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_KeyCopy                                         **
**                                                                            **
** Service ID           : 0x73                                                **
**                                                                            **
** Description          : This function shall copy all key elements from the  **
**                        source key to a target key                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant, but not for same keyId                   **
**                                                                            **
** Input Parameters     : keyId: Holds the identifier of the key whose key    **
**                               element shall be the source element          **
**                        targetKeyId: Holds the identifier of the key whose  **
**                                     key element shall be the destination   **
**                                     element                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Request successful                            **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, Crypto Driver Object **
**                                       is busy                              **
**                        CRYPTO_E_KEY_NOT_AVAILABLE: Request failed, the     **
**                                                    requested key element   **
**                                     is not available                       **
**                        CRYPTO_E_KEY_READ_FAIL: Request failed, not allowed **
**                                                to extract key element      **
**                        CRYPTO_E_KEY_WRITE_FAIL: Request failed, not        **
**                                                 allowed to write key       **
**                                                 element                    **
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
**                        CryIf_KeyCopy                                       **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyCopy
(
  VAR(uint32, CSM_CONST) keyId,
  VAR(uint32, CSM_CONST) targetKeyId
)
{
  /* Return variable */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Source CryIf key ID */
  VAR(uint32, AUTOMATIC) cryIfKeyId;
  /* Target CryIf key ID */
  VAR(uint32, AUTOMATIC) targetCryIfKeyId;
  /* @Trace: Csm_SUD_FUNC_060 */
  /* CSM key management common development error checking. Input pointer, output
    pointer and output length pointer set to NULL_PTR */
  retVal = Csm_PrvKeyManComDevErrCheck(CSM_KEY_COPY_SID, keyId, targetKeyId, \
    NULL_PTR, NULL_PTR, NULL_PTR);  
  if (E_OK == retVal)
  {
	/* @Trace: Csm_SUD_FUNC_061 */
    cryIfKeyId = Csm_KeyList[keyId].CryIfKeyId;
    targetCryIfKeyId = Csm_KeyList[targetKeyId].CryIfKeyId;
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Copy to 1 */
    Csm_KeyManIsProcessing ^= CSM_KEYCOPY_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    retVal = CryIf_KeyCopy(cryIfKeyId, targetCryIfKeyId);
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Copy to 0 */
    Csm_KeyManIsProcessing ^= CSM_KEYCOPY_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
  }
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_KeyElementCopyPartial                           **
**                                                                            **
** Service ID           : 0x79                                                **
**                                                                            **
** Description          : Copies a key element to another key element in the  **
**                        same crypto driver. The keyElementSourceOffset and  **
**                        keyElementCopyLength allows to copy just a part of  **
**                        the source key element into the destination. The    **
**                        offset into the target key is also specified with   **
**                        this function                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant, but not for the same keyId               **
**                                                                            **
** Input Parameters     : keyId: Holds the identifier of the key whose key    **
**                               element shall be the source element for copy **
**                               operation                                    **
**                        keyElementId: Holds the identifier of the key       **
**                                      element which shall be the source for **
**                                      the copy operation                    **
**                        keyElementSourceOffset: This is the offset of the   **
**                                                source key element          **
**                                                indicating the start index  **
**                                                of the copy operation       **
**                        keyElementTargetOffset: This is the offset of the   **
**                                                destination key element     **
**                                                indicating the start index  **
**                                                of the copy operation       **
**                        keyElementCopyLength: Specifies the number of bytes **
**                                              that shall be copied          **
**                        targetKeyId: Holds the identifier of the key whose  **
**                                     key element shall be the destination   **
**                                     element                                **
**                        targetKeyElementId: Holds the identifier of the key **
**                                            element which shall be the      **
**                                            destination for the copy        **
**                                            operation                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Request successful                            **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, Crypto Driver Object **
**                                       is busy                              **
**                        CRYPTO_E_KEY_NOT_AVAILABLE: Request failed, the     **
**                                                    requested key element   **
**                                                    is not available        **
**                        CRYPTO_E_KEY_READ_FAIL: Request failed, not allowed **
**                                                to extract key element      **
**                        CRYPTO_E_KEY_WRITE_FAIL: Request failed, not        **
**                                                 allowed to write key       **
**                                                 element                    **
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
**                        CryIf_KeyElementCopyPartial                         **
**                        SchM_Enter_Csm_GLOBALVAR_PROTECTION                 **
**                        SchM_Exit_Csm_GLOBALVAR_PROTECTION                  **
**                                                                            **
*******************************************************************************/
#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopyPartial
(
  VAR(uint32, AUTOMATIC) keyId,
  VAR(uint32, AUTOMATIC) keyElementId,
  VAR(uint32, AUTOMATIC) keyElementSourceOffset,
  VAR(uint32, AUTOMATIC) keyElementTargetOffset,
  VAR(uint32, AUTOMATIC) keyElementCopyLength,
  VAR(uint32, AUTOMATIC) targetKeyId,
  VAR(uint32, AUTOMATIC) targetKeyElementId
)
{
  /* Return variable */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Source CryIf key ID */
  VAR(uint32, AUTOMATIC) cryIfKeyId;
  /* Target CryIf key ID */
  VAR(uint32, AUTOMATIC) targetCryIfKeyId;
  /* @Trace: Csm_SUD_FUNC_070 */
  /* CSM key management common development error checking. Input pointer, output
    pointer and output length pointer set to NULL_PTR */
  retVal = Csm_PrvKeyManComDevErrCheck(CSM_KEY_ELEMENT_COPY_PARTIAL_SID, \
                                        keyId, targetKeyId, NULL_PTR, \
                                        NULL_PTR, NULL_PTR);
  if (E_OK == retVal)
  {
    /* @Trace: Csm_SUD_FUNC_071 */
    cryIfKeyId = Csm_KeyList[keyId].CryIfKeyId;
    targetCryIfKeyId = Csm_KeyList[targetKeyId].CryIfKeyId;
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Element Copy Partial to 1 */
    Csm_KeyManIsProcessing ^= CSM_KEYELEMENTCOPYPARTIAL_ISPROCESSING;
    SchM_Exit_Csm_GLOBALVAR_PROTECTION();
    retVal = CryIf_KeyElementCopyPartial(cryIfKeyId, keyElementId, \
      keyElementSourceOffset, keyElementTargetOffset, \
      keyElementCopyLength, targetCryIfKeyId, targetKeyElementId);
    SchM_Enter_Csm_GLOBALVAR_PROTECTION();
    /* Set bit represent for Csm Key Element Copy Partial to 0 */
    Csm_KeyManIsProcessing ^= CSM_KEYELEMENTCOPYPARTIAL_ISPROCESSING;
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
