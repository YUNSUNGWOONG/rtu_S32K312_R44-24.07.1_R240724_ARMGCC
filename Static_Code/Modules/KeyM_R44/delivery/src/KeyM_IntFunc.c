/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_IntFunc.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key Manager internal API Functionality                        **
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
** 1.0.1.0   27-Mar-2021   TamTV6       Fix defect #18205, #18379, Trace SUD  **
** 1.0.2     08-Nov-2021   TamTV6       Implement #20971                      **
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
** 1.0.7.0   07-Apr-2023   PhuocLH9     #CP44-1636,#CP44-1664                 **
** 1.0.9.0   21-Feb-2024   JS Kang      #CP44-3633,#CP44-3635				  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:11.5 CERT-C:EXP36-C [Justified:Low] 
   "It uses casting from void* to object(struct) pointer in order to read a raw 
   memory by the specific format. If using working around like memory copy to 
   pass over this violation, the source code becomes very complex, hard to read 
   and take time to fix testing failed cases." */
/* polyspace-begin MISRA-C3:11.8 [Justified:Low] 
   "PtrCertData pointer is used for both reading and updating(when storing to NvM) 
   certificate data. So, it must be a non-constant pointer." */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* RTE KeyM header file */
#include "Rte_KeyM.h"
/* KeyM header file */
#include "KeyM.h"
/* KeyM internal function prototype */
#include "KeyM_IntFunc.h"
/* KeyM Ram variables header file */
#include "KeyM_Ram.h"
/* KeyM X509 Ctr header file */
#include "KeyM_X509_Crt.h"
/* KeyM X509 Ctr header file */
#include "KeyM_X509_Crl.h"
/* KeyM CVC header file */
#include "KeyM_Cvc.h"
/* For callback function */
#include "KeyM_Externals.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
#if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_ResultType KeyM_PrvPerformUpdateOperation(\
  P2VAR(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_DATA) ptrKey, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrData, \
  const uint16 dataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static void KeyM_PrvProcessUpdateResult(\
  const KeyM_ResultType operationResult);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */
/*******************************************************************************
** Function Name      : KeyM_PrvMemCmp                                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Compare two data arrays                               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrSrcData, ptrDesData, dataLength                    **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvMemCmp(\
  P2CONST(void, AUTOMATIC, KEYM_APPL_CONST) ptrSrcData, \
  P2CONST(void, AUTOMATIC, KEYM_APPL_CONST) ptrDesData, \
  CONST(uint32, KEYM_CONST) dataLen)
{
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrSrc;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrDes;
  uint32 indexCnt;
  Std_ReturnType retVal;

  if ((NULL_PTR != ptrSrcData) && (NULL_PTR != ptrDesData) && \
    (KEYM_ZERO != dataLen))
  {
    retVal = E_OK;
    /* @Trace: KeyM_SUD_FUNC_206 */
    ptrSrc = (const uint8*)ptrSrcData;
    ptrDes = (const uint8*)ptrDesData;
    /* polyspace-begin DEFECT:TAINTED_SIGN_CHANGE MISRA-C3:D4.14 CERT-C:INT31-C [Justified:Low] "It checks that dataLen must be 
      a positive value before passing to this loop." */
    for (indexCnt = KEYM_ZERO; indexCnt < dataLen; indexCnt++)
    {
      if (ptrSrc[indexCnt] != ptrDes[indexCnt])
      {
        retVal = E_NOT_OK;
        break;
      }
    }
    /* polyspace-end DEFECT:TAINTED_SIGN_CHANGE MISRA-C3:D4.14 CERT-C:INT31-C */
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_205 */
    retVal = E_NOT_OK;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvMemCopy                                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Copy data between two arrays                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrSrcData, dataLength                                **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrDesData                                            **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvMemCopy(\
  P2CONST(void, AUTOMATIC, KEYM_APPL_CONST) ptrSrcData, \
  P2VAR(void, AUTOMATIC, KEYM_APPL_DATA) ptrDesData, \
  CONST(uint32, KEYM_CONST) dataLen)
{
  Std_ReturnType retVal;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrSrc;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrDes;
  uint32 indexCnt;

  retVal = E_OK;
  if ((NULL_PTR != ptrSrcData) && (NULL_PTR != ptrDesData))
  {
    /* @Trace: KeyM_SUD_FUNC_208 */
    ptrSrc = (const uint8*)ptrSrcData;
    ptrDes = (uint8*)ptrDesData;
    if (KEYM_ZERO != dataLen)
    {
      /* polyspace-begin DEFECT:TAINTED_SIGN_CHANGE MISRA-C3:D4.14 CERT-C:INT31-C [Justified:Low] "It checks that dataLen must be 
      a positive value before passing to this loop." */
      for (indexCnt = KEYM_ZERO; indexCnt < dataLen; indexCnt++)
      {
        ptrDes[indexCnt] = ptrSrc[indexCnt];
      }
      /* polyspace-end DEFECT:TAINTED_SIGN_CHANGE MISRA-C3:D4.14 CERT-C:INT31-C */
    }   
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_207 */
    retVal = E_NOT_OK;
  }
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvMemClear                                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Clear data of an array                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : dataLength                                            **
**                                                                            **
** InOut Parameters   : ptrSrcData                                            **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvMemClear(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSrcData, \
  CONST(uint32, KEYM_CONST) dataLen)
{
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData;
  uint32 indexCnt;

  /* @Trace: KeyM_SUD_FUNC_229 */
  if (NULL_PTR != ptrSrcData)
  {
    ptrData = ptrSrcData;

    for (indexCnt = 0u; indexCnt < dataLen; indexCnt++)
    {
      ptrData[indexCnt] = KEYM_ZERO;
    }
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)

#if (KEYM_CRYPTO_KEY_ADDITIONAL_HINT_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvGetKeyIndexByExtractedSHEKeyId                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get index of key in the array by extracted SHE key ID **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrKey, keyArrayLength, extractedSHEKeyId             **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrKeyIndex                                           **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvGetKeyIndexByExtractedSHEKeyId(\
  P2CONST(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_DATA) ptrKey, \
  const uint16 keyArrayLength, \
  const uint8 extractedSHEKeyId, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrKeyIndex)
{
  uint16 index;
  Std_ReturnType retVal;

  /* @Trace: KeyM_SUD_FUNC_230 */
  retVal = E_NOT_OK;
  for (index = KEYM_ZERO; index < keyArrayLength; index++)
  {
    if (ptrKey[index].KeyCryptoProps == extractedSHEKeyId)
    {
      retVal = E_OK;
      *ptrKeyIndex = index;
      break;
    }
  }
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CRYPTO_KEY_ADDITIONAL_HINT_ENABLED == STD_ON) */
#endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */

#if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)

/*******************************************************************************
** Function Name      : KeyM_PrvGetKeyIndexByName                             **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get index of key in the array by name                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrKeyArray, keyArrayLength, ptrKeyName, nameLength   **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrKeyIndex                                           **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvMemCmp                                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType,  KEYM_CODE) KeyM_PrvGetKeyIndexByName(\
  P2VAR(void, AUTOMATIC, KEYM_APPL_DATA) ptrKeyArray, \
  const uint16 keyArrayLength, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrKeyName, \
  const uint16 nameLength, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrKeyIndex)
{
  P2CONST(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_CONST) ptrKey;
  uint16 indexCnt;
  Std_ReturnType retVal;

  /* @Trace: KeyM_SUD_FUNC_231 */
  retVal = E_NOT_OK;
  ptrKey = (KeyM_CryptoKeyType*)ptrKeyArray;

  for (indexCnt = KEYM_ZERO; indexCnt < keyArrayLength; indexCnt++)
  {
    if (nameLength == ptrKey[indexCnt].KeyNameLength)
    {
      retVal = KeyM_PrvMemCmp(ptrKeyName, ptrKey[indexCnt].PtrKeyName, nameLength);
      if (E_OK == retVal)
      {
        *ptrKeyIndex = indexCnt;
        break;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPartOfPerformUpdateOperation                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvPerformUpdateOperation,     **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvPerformUpdateOperation                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrKeyData, dataLength, keyMaxLength, keyStorageType, **
**                      targetKeyId                                           **
**                                                                            **
** InOut Parameters   : ptrKey                                                **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Csm_KeyElementSet, KeyM_PrvMemCopy, Csm_KeySetValid,  **
**                      Csm_KeyDerive, Csm_KeyElementGet                      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvPartOfPerformUpdateOperation(\
  P2VAR(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_DATA) ptrKey, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrKeyData, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrData, \
  const uint16 dataLength, \
  const uint32 keyMaxLength, \
  const KeyM_KeyCertStorageType keyStorageType, \
  const uint32 targetKeyId)
{
  Std_ReturnType retVal;
  uint32 sourceKeyId;

  if (KEYM_STORED_KEY == ptrKey->KeyGenerationType)
  {
    /* @Trace: KeyM_SUD_FUNC_334 */
    /* Store request data to the key element 1 of target key */
    retVal = Csm_KeyElementSet(targetKeyId, KEYM_KEY_ELEMENT1_ID, \
      ptrData, dataLength);

    if (E_OK == retVal)
    {
      ptrKey->KeyLength = dataLength;

      if (KEYM_STORAGE_IN_RAM == keyStorageType)
      {
        /* Copy key data to key buffer in RAM */
        (void)KeyM_PrvMemCopy(ptrData, &ptrKeyData[0u], dataLength);
      }
      #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
      else if (KEYM_STORAGE_IN_NVM == keyStorageType)
      {
        /* The NvM stored data includes 1 byte of state, \
          2 bytes of key data length, and key data, so
          the key data length must not be bigger than the key max length - 3 */
        if (dataLength > (keyMaxLength - 3u))
        {
          retVal = E_NOT_OK;
        }
        else
        {
          /* Copy key data to buffer */
          (void)KeyM_PrvMemCopy(ptrData, &ptrKeyData[0u], dataLength);
        }
      }
      #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */
      else
      {
        /* The key is stored to CSM with all storage types */
      }
    } /* @if (E_OK == retVal) */
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_335 */
    sourceKeyId = ptrKey->CsmSourceKeyId;
    /* Set request data to the key element id 1 of the source key
       (the element name is CRYPTO_KE_KEYDERIVATION_PASSWORD) */
    retVal = Csm_KeyElementSet(sourceKeyId, KEYM_KEY_ELEMENT1_ID, \
      ptrData, dataLength);

    if (E_OK == retVal)
    {
      /* Set generationInfor to the key element id 13 of the source key
         (the element name is CRYPTO_KE_KEYDERIVATION_SALT) */
      if ((NULL_PTR != ptrKey->PtrKeyGenerationInfo) && \
        (0u < ptrKey->KeyGenerationInfoLength))
      {
        retVal = Csm_KeyElementSet(sourceKeyId, KEYM_KEY_ELEMENT13_ID, \
          ptrKey->PtrKeyGenerationInfo, ptrKey->KeyGenerationInfoLength);
      }

      if (E_OK == retVal)
      {
        /* Validate the alternated source key */
        retVal = Csm_KeySetValid(sourceKeyId);

        if (E_OK == retVal)
        {
          /* Derive the TargetKey from the SourceKey */
          retVal = Csm_KeyDerive(sourceKeyId, targetKeyId);

          if (KEYM_STORAGE_IN_CSM != keyStorageType)
          {

            if (KEYM_STORAGE_IN_RAM == keyStorageType)
            {
              ptrKey->KeyLength = keyMaxLength;
            }
            #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
            else
            {
              /* The key length is maximum length minus 3,
                because the last 3 bytes are used to store state
                and key length information */
              ptrKey->KeyLength = keyMaxLength - 3u;
            }
            #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */
            /* Get the derived key data */
            retVal = Csm_KeyElementGet(targetKeyId, KEYM_KEY_ELEMENT1_ID, \
              &ptrKeyData[0u], &(ptrKey->KeyLength));
          } /* @if (KEYM_STORAGE_IN_CSM != keyStorageType) */
        } /* @if (E_OK == retVal) */
      } /* @if (E_OK == retVal) */
    } /* @if (E_OK == retVal) */
  } /* @if (KEYM_STORED_KEY == ptrKey->KeyGenerationType) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvPerformUpdateOperation                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform key update operation                          **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrData, dataLength                                   **
**                                                                            **
** InOut Parameters   : ptrKey                                                **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvPartOfPerformUpdateOperation                  **
**                      NvM_WriteBlock, Csm_KeySetValid                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_ResultType KeyM_PrvPerformUpdateOperation(\
  P2VAR(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_DATA) ptrKey, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrData, \
  const uint16 dataLength)
{
  Std_ReturnType retVal;
  KeyM_ResultType operationResult;
  uint32 targetKeyId;
  KeyM_KeyCertStorageType keyStorageType;
  uint32 keyMaxLength;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrKeyData;

  keyMaxLength = ptrKey->KeyMaxLength;

  if (dataLength > keyMaxLength)
  {
    /* @Trace: KeyM_SUD_FUNC_338 */
    operationResult = KEYM_RT_NOT_OK;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_339 */
    targetKeyId = ptrKey->CsmTargetKeyId;
    keyStorageType = ptrKey->KeyStorageType;
    ptrKeyData = ptrKey->PtrKeyData;

    retVal = KeyM_PrvPartOfPerformUpdateOperation(ptrKey, ptrKeyData, ptrData, \
      dataLength, keyMaxLength, keyStorageType, targetKeyId);
    if (E_OK == retVal)
    {
      #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
      if (KEYM_STORAGE_IN_NVM == keyStorageType)
      {
        /* The third byte from the last is upper byte of key data length */
        ptrKeyData[keyMaxLength - 3u] = \
          (uint8)((ptrKey->KeyLength & KEYM_UPPER_BYTE_MASK) >> \
          KEYM_UPPER_BYTE_SHIFT);
        /* The second byte from the last is lower byte of key data length */
        ptrKeyData[keyMaxLength - 2u] = \
          (uint8)(ptrKey->KeyLength & KEYM_LOWER_BYTE_MASK);
        /* The last byte is state byte of 1 */
        ptrKeyData[keyMaxLength - 1u] = KEYM_ONE;
        /* Write to NvM */
        retVal = NvM_WriteBlock(ptrKey->NvmBlockId, &ptrKeyData[0u]);
        if (E_OK != retVal)
        {
          retVal = CRYPTO_E_KEY_WRITE_FAIL;
        }
      } /* @if (KEYM_STORAGE_IN_RAM == keyStorageType) */

      /* @Trace: KeyM_SUD_FUNC_340 */
      if (E_OK == retVal)
      #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */
      {
        #if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
        /* Mark the key has alternated, the alternated key shall be validated
           in the KeyM_Finalize function */
        ptrKey->HasAlternated = KEYM_TRUE;
        #else
        /* Validate the alternated target key */
        retVal = Csm_KeySetValid(targetKeyId);
        if (E_OK == retVal)
        {
          /* Set key state is valid */
          ptrKey->KeyState = KEYM_ONE;
        }
        #endif /* KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */
      }
    } /* @if (E_OK == retVal) */

    /* @Trace: KeyM_SUD_FUNC_341 */
    if (E_OK == retVal)
    {
      operationResult = KEYM_RT_OK;
    }
    else if (CRYPTO_E_KEY_WRITE_FAIL == retVal)
    {
      operationResult = KEYM_RT_KEY_CERT_WRITE_FAIL;
    }
    else if ((CRYPTO_E_KEY_NOT_VALID == retVal) || \
      (CRYPTO_E_KEY_EMPTY == retVal) || \
      (CRYPTO_E_KEY_NOT_AVAILABLE == retVal))
    {
      operationResult = KEYM_RT_KEY_CERT_INVALID;
    }
    else
    {
      operationResult = KEYM_RT_KEY_CERT_UPDATE_FAIL;
    } /* @if (E_OK == retVal) */

    if (E_OK != retVal)
    {
      /* Set key state is invalid */
      ptrKey->KeyState = KEYM_ZERO;
    }
  } /* @if (ptrKey->KeyMaxLength < dataLength) */

  return operationResult;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvProcessUpdateResult                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Process result of update operation                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : operationResult                                       **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_JobState, KeyM_CryptoKey, KeyM_BackGroundDone,   **
**                      KeyM_HandlerUpdateNextKey                             **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static void KeyM_PrvProcessUpdateResult(\
  const KeyM_ResultType operationResult)
{
  /* Update job state base on the operation result */

  if (KEYM_RT_OK == operationResult)
  {
    #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
    if (KEYM_REQUEST_JOB == KeyM_JobState)
    #endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON */
    {
      SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
      #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
      if (KEYM_STORAGE_IN_NVM == KeyM_CryptoKey[KeyM_KeyId].KeyStorageType)
      {
        /* @Trace: KeyM_SUD_FUNC_345 */
        #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
          /* The NvM write request may not completed , so this flag is TRUE
            to prevent KeyM_KH_Update calling in the MainBackGround function,
            thus the next key update request will not be created until the
            current NvM write request has finished */
          KeyM_BackGroundDone = KEYM_TRUE;
        #else
          /* At here, the job is completed */
          KeyM_JobState = KEYM_IN_PROGRESS;
        #endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON */
      }
      else
      #endif /* KEYM_STORAGE_IN_NVM == STD_ON */
      {
        /* @Trace: KeyM_SUD_FUNC_344 */
        #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
          /* The NvM write request has finished, so set this flag to FALSE
            to allow KeyM_KH_Update calling in the MainBackGround function to
            prepare for next key updating */
          KeyM_BackGroundDone = KEYM_FALSE;
        #else
          /* At here, the job is completed */
          KeyM_JobState = KEYM_COMPLETE;
        #endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON */
      }
      /* @Trace: KeyM_SUD_FUNC_346 */
      #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
        KeyM_JobState = KEYM_KH_IN_PROGRESS;
        /* Set this flag to false to indicate that the next key update
          request has processed */
        KeyM_HandlerUpdateNextKey = KEYM_FALSE;
      #endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON */
      SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
    }
    #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
    else
    {
      /* @Trace: KeyM_SUD_FUNC_343 */
      /* Set this flag to false to indicate that the next key update
        request has processed */
      KeyM_HandlerUpdateNextKey = KEYM_FALSE;
    } /* @if (KEYM_REQUEST_JOB == KeyM_JobState) */
    #endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON */
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_342 */
    /* At here, the job is completed */
    SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
    KeyM_JobState = KEYM_COMPLETE;
    SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvProcessUpdateOperation                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Process key update operation                          **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_CryptoKey, KeyM_PtrRequestData, KeyM_DataBuffer, **
**                      KeyM_RequestDataLength, KeyM_DataBufferLength,        **
**                      KeyM_JobState, KeyM_BackGroundDone,                   **
**                      KeyM_OperationResult, KeyM_HandlerUpdateNextKey,      **
**                      KeyM_CurrentJob, KeyM_HandlerUpdateOperation,         **
**                      KeyM_ModuleState                                      **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      NvM_GetErrorStatus, KeyM_PrvPerformUpdateOperation,   **
**                      KeyM_PrvProcessUpdateResult, KeyM_PrvMemCopy,         **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvProcessUpdateOperation(void)
{
  P2VAR(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_DATA) ptrKey;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData;
  uint16 dataLength;
  KeyM_ResultType operationResult;
  KeyM_JobStateType jobState;
  /* @Trace: KeyM_SUD_FUNC_232 */
  #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
    KeyM_KeyCertStorageType keyStorageType;
    NvM_RequestResultType nvMRequestResult;
    nvMRequestResult = NVM_REQ_OK;
  #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */

  /* Refer to the key by its index */
  ptrKey = &KeyM_CryptoKey[KeyM_KeyId];

  #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_OFF)
    /* If update handler is not used, the request data will be
      used to update the key */
    ptrData = KeyM_PtrRequestData;
    dataLength = KeyM_RequestDataLength;
  #else
    /* If update handler is used, the response data of key handler will be
      used to update the key */
    ptrData = KeyM_DataBuffer;
    dataLength = KeyM_DataBufferLength;
  #endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_OFF */

  #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
    keyStorageType = ptrKey->KeyStorageType;
    if (KEYM_STORAGE_IN_NVM == keyStorageType)
    {
      /* Get the NvM block status to check if the write request has finished */
      (void)NvM_GetErrorStatus(ptrKey->NvmBlockId, &nvMRequestResult);
    }
  #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */
  
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  jobState = KeyM_JobState;
  SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  if (KEYM_REQUEST_JOB == jobState)
  {
    /* @Trace: KeyM_SUD_FUNC_233 */
    #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
    if ((KEYM_TRUE == KeyM_BackGroundDone) && \
      (KEYM_TRUE == KeyM_HandlerUpdateNextKey))
    #endif
    {
      operationResult = KeyM_PrvPerformUpdateOperation(ptrKey, \
        ptrData, dataLength);
      /* Update job state base on the operation result */
      KeyM_PrvProcessUpdateResult(operationResult);
      SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
      KeyM_OperationResult = operationResult;
      SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
    }
  }
  #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
  else if (KEYM_KH_IN_PROGRESS == jobState)
  {
    /* @Trace: KeyM_SUD_FUNC_236 */
    if (KEYM_TRUE == KeyM_BackGroundDone)
    {
      operationResult = KEYM_RT_OK;

      #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
      if (KEYM_STORAGE_IN_NVM == keyStorageType)
      {
        /* Check if the update operation has done and the
           NvM write request still in progress */
        if (KEYM_FALSE == KeyM_HandlerUpdateNextKey)
        {
          /* @Trace: KeyM_SUD_FUNC_237 */
          /* Check if the NvM write request has finished */
          if (NVM_REQ_PENDING != nvMRequestResult)
          {
            if (NVM_REQ_OK == nvMRequestResult)
            {
              /* The NvM write request has finished and OK */
              operationResult = KEYM_RT_OK;
            }
            else
            {
              /* The NvM write request has finished and NOT OK,
                so set job state to be COMPLETE in this case */
              operationResult = KEYM_RT_NOT_OK;
              KeyM_JobState = KEYM_COMPLETE;
            }
            /* The NvM write request has finished, so set this flag to FALSE
              to allow KeyM_KH_Update calling in the MainBackGround function to
              prepare for next key updating */
            SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
            KeyM_BackGroundDone = KEYM_FALSE;
            SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
          } /* @if (NVM_REQ_PENDING != nvMRequestResult) */
        }
        else
        {
          operationResult = KeyM_PrvPerformUpdateOperation(ptrKey, \
            ptrData, dataLength);
        } /* @if (KEYM_FALSE == KeyM_HandlerUpdateNextKey) */
      }
      else
      #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */
      {
        /* @Trace: KeyM_SUD_FUNC_238 */
        /* Perform next key update request */
        operationResult = KeyM_PrvPerformUpdateOperation(ptrKey, \
          ptrData, dataLength);
        /* Set this flag to FALSE to allow KeyM_KH_Update calling in the
           MainBackGround function */
        SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
        KeyM_BackGroundDone = KEYM_FALSE;
        SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
      } /* @if (KEYM_STORAGE_IN_NVM == keyStorageType) */

      /* Update job state base on the operation result */
      KeyM_PrvProcessUpdateResult(operationResult);
      KeyM_OperationResult = operationResult;
    } /* @if (KEYM_TRUE == KeyM_BackGroundDone) */
  }
  #endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON */
  #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_OFF)
  else if (KEYM_IN_PROGRESS == jobState)
  {
    /* @Trace: KeyM_SUD_FUNC_235 */
    #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
      /* Check the NvM request result */
      if (KEYM_STORAGE_IN_NVM == keyStorageType)
      {
        /* Check the NvM request is completed */
        if (NVM_REQ_PENDING != nvMRequestResult)
        {
          if (NVM_REQ_OK == nvMRequestResult)
          {
            /* The NvM request result is OK */
            operationResult = KEYM_RT_OK;
          }
          else
          {
            /* The NvM request result is NOT OK */
            operationResult = KEYM_RT_KEY_CERT_WRITE_FAIL;
          }
          /* At here, the job is completed */
          SchM_Enter_KeyM_GLOBALVAR_PROTECTION();          
          KeyM_JobState = KEYM_COMPLETE;
          KeyM_OperationResult = operationResult;
          SchM_Exit_KeyM_GLOBALVAR_PROTECTION();          
        }
      } /* @if (KEYM_STORAGE_IN_NVM == keyStorageType) */
    #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */
  }
  #endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_OFF */
  else
  {
    /* Do nothing */
  }
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  jobState = KeyM_JobState;
  SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  if (KEYM_COMPLETE == jobState)
  {
    #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
      /* @Trace: KeyM_SUD_FUNC_239 */
      /* Copy the returned date of KeyM_KH_Update to result data
        buffer of KeyM_Update */
      if (KEYM_KH_UPDATE_FINISH == KeyM_HandlerUpdateOperation)
      {
        if (dataLength <= KeyM_ResultDataMaxLength)
        {
          (void)KeyM_PrvMemCopy(ptrData, KeyM_PtrResultData, dataLength);
        }
        else
        {
          SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
          KeyM_OperationResult = KEYM_RT_NOT_OK;
          SchM_Exit_KeyM_GLOBALVAR_PROTECTION();          
          #if (KEYM_DEV_ERROR_DETECT == STD_ON)
            /* Report error to Det in case output buffer length is small */
            KEYM_REPORT_ERROR(KEYM_UPDATE_SID, KEYM_E_SMALL_BUFFER);
          #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
        }
      }
    #else
      /* @Trace: KeyM_SUD_FUNC_240 */
      /* There is no response data */
      dataLength = KEYM_ZERO;
    #endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON */

    /* After update operation has finished, call callback function to notify
       to application */
    SchM_Enter_KeyM_GLOBALVAR_PROTECTION();       
    (void)Rte_Call_KeyMCryptoKeyNotification_CryptoKeyUpdateCallbackNotification(\
    KeyM_OperationResult, dataLength, KeyM_PtrResultData);
    /* Reset current job */
    KeyM_CurrentJob = KEYM_NO_JOB;
    /* Set module state to idle */
    KeyM_ModuleState = KEYM_IDLE;
    /* Reset internal flags */
    KeyM_BackGroundDone = KEYM_FALSE;
    KeyM_HandlerUpdateNextKey = KEYM_FALSE;
    SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvProcessFinalizeOperation                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Process finalize operation                            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_CryptoKey, KeyM_PtrResultData, KeyM_CurrentJob,  **
**                      KeyM_ResultDataMaxLength, KeyM_BackGroundDone,        **
**                      KeyM_SessionState, KeyM_HandlerRetVal,                **
**                      KeyM_ModuleState                                      **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Csm_KeySetValid                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvProcessFinalizeOperation(void)
{
  P2VAR(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_DATA) ptrKey;
  uint16 keyIndex;
  Std_ReturnType retVal;
  KeyM_ResultType operationResult;
  uint16 respondDataLen;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrResponseData;

  /* @Trace: KeyM_SUD_FUNC_241 */
  #if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
  if (KEYM_TRUE == KeyM_BackGroundDone)
  #endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */
  {
    #if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
    if (E_OK == KeyM_HandlerRetVal)
    #endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */
    {
      operationResult = KEYM_RT_OK;
      for (keyIndex = KEYM_ZERO; KEYM_TOTAL_KEY > keyIndex; keyIndex++)
      {
        ptrKey = &KeyM_CryptoKey[keyIndex];
        if (KEYM_TRUE == ptrKey->HasAlternated)
        {
          /* Validate the alternated target key */
          retVal = Csm_KeySetValid(ptrKey->CsmTargetKeyId);

          if (E_OK != retVal)
          {
            operationResult = KEYM_RT_NOT_OK;
            /* Set key state is invalid */
            ptrKey->KeyState = KEYM_ZERO;
          }
          else
          {
            /* Set key state is valid */
            ptrKey->KeyState = KEYM_ONE;
          }
          /* Clear flag */
          ptrKey->HasAlternated = KEYM_FALSE;
        } /* @if (KEYM_TRUE == ptrKey->HasAlternated) */
      } /* @for (keyIndex = KEYM_ZERO; KEYM_TOTAL_KEY > keyIndex; keyIndex++) */
    }
    #if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
    else
    {
      /* @Trace: KeyM_SUD_FUNC_242 */
      /* Update operation result base on returned value of key handler
         of finalize */
      if (KEYM_E_PARAMETER_MISMATCH == KeyM_HandlerRetVal)
      {
        operationResult = KEYM_RT_PARAMETER_MISMATCH;
      }
      else if (KEYM_E_KEY_CERT_SIZE_MISMATCH == KeyM_HandlerRetVal)
      {
        operationResult = KEYM_RT_KEY_CERT_SIZE_MISMATCH;
      }
      else
      {
        operationResult = KEYM_RT_NOT_OK;
      }

      /* All flags for key validation have to be cleared */
      for (keyIndex = KEYM_ZERO; KEYM_TOTAL_KEY > keyIndex; keyIndex++)
      {
        ptrKey = &KeyM_CryptoKey[keyIndex];
        ptrKey->HasAlternated = KEYM_FALSE;
        /* Set key state is invalid */
        ptrKey->KeyState = KEYM_ZERO;
      }
    } /* @if (E_OK == KeyM_HandlerRetVal) */
    #endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */

    /* @Trace: KeyM_SUD_FUNC_243 */
    #if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_OFF)
      respondDataLen = 0u;
      ptrResponseData = NULL_PTR;
    #else
      respondDataLen = KeyM_ResultDataMaxLength;
      ptrResponseData = KeyM_PtrResultData;
    #endif

    (void)Rte_Call_KeyMCryptoKeyNotification_CryptoKeyFinalizeCallbackNotification(\
      operationResult, respondDataLen, ptrResponseData);
    SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
    /* Set the session state to be in De-activated */
    KeyM_SessionState = KEYM_SESSION_DEACTIVATED;
    /* Set current job to be no job */
    KeyM_CurrentJob = KEYM_NO_JOB;
    /* Set module state to be idle */
    KeyM_ModuleState = KEYM_IDLE;
    /* Set back ground state to be idle */
    KeyM_BackGroundDone = KEYM_FALSE;
    SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  } /* @if (KEYM_TRUE == KeyM_BackGroundDone) */
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */

#if (KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF)
/*******************************************************************************
** Function Name      : KeyM_PrvPerformVerifyOperation                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform key verify operation                          **
**                                                                            **
** Sync/Async         : Asynchronous/synchronous                              **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrKey, ptrRequestData, ptrRequestDataLength,         **
**                                                                            **
** InOut Parameters   : ptrResponseDataLength                                 **
**                                                                            **
** Output Parameters  : ptrResponseData,                                      **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_VerifyRespondDataLength                          **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Csm_MacGenerate, Csm_Encrypt, Csm_Decrypt             **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvPerformVerifyOperation(\
  P2CONST(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_DATA) ptrKey, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrRequestData, \
  VAR(uint16, AUTOMATIC) reqDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrResponseData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrResponseDataLength)
{
  Std_ReturnType retVal;
  uint32 requestDataLen;
  uint32 csmJobId;
  KeyM_CryptoCsmVerifyJobType csmVerifyJobType;

  /* @Trace: KeyM_SUD_FUNC_244 */
  csmJobId = ptrKey->CsmVerifyJob.CsmJobId;
  csmVerifyJobType = ptrKey->CsmVerifyJobType;
  requestDataLen = reqDataLength;

  /* Identify which Csm job shall be called */
  if (KEYM_VERIFY_MACGENERATE == csmVerifyJobType)
  {
    retVal = Csm_MacGenerate(csmJobId, CRYPTO_OPERATIONMODE_SINGLECALL, \
      ptrRequestData, requestDataLen, \
      ptrResponseData, &KeyM_VerifyRespondDataLength);
  }
  else if (KEYM_VERIFY_ENCRYPT == csmVerifyJobType)
  {
    retVal = Csm_Encrypt(csmJobId, CRYPTO_OPERATIONMODE_SINGLECALL, \
      ptrRequestData, requestDataLen, \
      ptrResponseData, &KeyM_VerifyRespondDataLength);
  }
  else if (KEYM_VERIFY_DECRYPT == csmVerifyJobType)
  {
    retVal = Csm_Decrypt(csmJobId, CRYPTO_OPERATIONMODE_SINGLECALL, \
      ptrRequestData, requestDataLen, \
      ptrResponseData, &KeyM_VerifyRespondDataLength);
  }
  else
  {
    /* Other operations such as AEAD encrypt/decrypt or MAC verify
       need to be done by key handler verification function */
    retVal = E_NOT_OK;
  } /* @if (KEYM_VERIFY_MACGENERATE == csmVerifyJobType) */

  if (E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_245 */
    *ptrResponseDataLength = (uint16)KeyM_VerifyRespondDataLength;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF) */

#if (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvCsmCallback                                   **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This callback is used by Csm to notify KeyM that Csm  **
**                      job has finished                                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : jobID, result                                         **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_CsmRequestDone, KeyM_CsmRequestResult            **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvCsmCallback(\
  const uint32 jobID, Csm_ResultType result)
{
  /* @Trace: KeyM_SUD_FUNC_248 */
  (void)jobID;
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  KeyM_CsmRequestDone = KEYM_TRUE;
  KeyM_CsmRequestResult = result;
  SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvProcessVerifyOperation                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Process verify operation                              **
**                                                                            **
** Sync/Async         : Asynchronous/synchronous                              **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_CryptoKey, KeyM_PtrRequestData, KeyM_JobState,   **
**                      KeyM_CsmRequestDone, KeyM_CsmRequestResult,           **
**                      KeyM_OperationResult, KeyM_BackGroundDone,            **
**                      KeyM_CurrentJob, KeyM_PtrResultDataLength, KeyM_KeyId,**
**                      KeyM_VerifyRespondDataLength, KeyM_PtrResultData,     **
**                      KeyM_ModuleState                                      **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvPerformVerifyOperation                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvProcessVerifyOperation(void)
{
  #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF)
  Std_ReturnType retVal;
  KeyM_ResultType verifyResult;
  boolean csmAsyncJob;
  P2VAR(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_DATA) ptrKey;

  /* @Trace: KeyM_SUD_FUNC_249 */
  ptrKey = &KeyM_CryptoKey[KeyM_KeyId];
  csmAsyncJob = ptrKey->CsmVerifyJob.AsyncJob;
  verifyResult = KEYM_RT_OK;
  retVal = E_OK;
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  if (KEYM_REQUEST_JOB == KeyM_JobState)
  {
    SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
    /* Perform verify operation */
    retVal = KeyM_PrvPerformVerifyOperation(ptrKey, KeyM_PtrRequestData, \
      KeyM_RequestDataLength, \
      KeyM_PtrResultData, \
      KeyM_PtrResultDataLength);
  }
  else
  {
    SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  }
  /* Change the job state to be in progress */
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  KeyM_JobState = KEYM_IN_PROGRESS;
  SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  /* Check if the verify service is synchronous or asynchronous */
  if (KEYM_FALSE == csmAsyncJob)
  {
    /* @Trace: KeyM_SUD_FUNC_251 */
    /* Process return value of Csm services */
    if (E_OK == retVal)
    {
      verifyResult = KEYM_RT_OK;
    }
    else
    {
      verifyResult = KEYM_RT_NOT_OK;
    }

    /* If Csm verify job is synchronous, the verify operation has finished, \
       so update job state to be complete */
    SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
    KeyM_JobState = KEYM_COMPLETE;
    SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_252 */
    if (E_OK == retVal)
    {
      /* Csm verify job is asynchronous, so check the Csm verify job has
       finished */
      SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
      if (KEYM_TRUE == KeyM_CsmRequestDone)
      {
        if (E_OK == KeyM_CsmRequestResult)
        {
          verifyResult = KEYM_RT_OK;
        }
        else
        {
          verifyResult = KEYM_RT_NOT_OK;
        }
        /* After Csm job has finished, change job state to be complete */
        KeyM_JobState = KEYM_COMPLETE;
      }
      SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
    }
    else
    {
      SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
      /* The csm request is not accepted, change job state to be complete */
      KeyM_JobState = KEYM_COMPLETE;
      SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
      /* Verify operation result is NOT OK */
      verifyResult = KEYM_RT_NOT_OK;
    } /* @if (E_OK == retVal) */

  } /* @if (KEYM_FALSE == csmAsyncJob) */
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  KeyM_OperationResult = verifyResult;
  SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  #endif /* KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF */

  #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON)
  /* @Trace: KeyM_SUD_FUNC_253 */
  if (KEYM_TRUE == KeyM_BackGroundDone)
  {
  #endif /* #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON) */
    SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
    if (KEYM_COMPLETE == KeyM_JobState)
    {    
      #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF)
        *KeyM_PtrResultDataLength = (uint16)KeyM_VerifyRespondDataLength;
      #endif /* #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON) */
      /* Call callback to notify the verify operation has finished */
      (void)Rte_Call_KeyMCryptoKeyNotification_CryptoKeyVerifyCallbackNotification(\
        KeyM_OperationResult, KeyM_KeyId, *KeyM_PtrResultDataLength, \
        KeyM_PtrResultData);
      /* Set current job to be no job */
      KeyM_CurrentJob = KEYM_NO_JOB;
      /* Set module state to be idle */
      KeyM_ModuleState = KEYM_IDLE;
      /* Set back ground state to be idle */
      KeyM_BackGroundDone = KEYM_FALSE;
      SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
    }
    else
    {
      SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
    }
  #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON)
  }
  #endif /* #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON) */

}

#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON */
#endif /* KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON */

#endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */

#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)

#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)

#if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
    (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON))

static KeyM_ResultType KeyM_PrvPerformRequestCsrOperation(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_CONST) ptrCert);

static KeyM_ResultType KeyM_PrvPerformUpdateSignCsrOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);

static KeyM_ResultType KeyM_PrvPerformSetRootCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);

static KeyM_ResultType KeyM_PrvPerformUpdateRootCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);

static KeyM_ResultType KeyM_PrvPerformSetIntermediateCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);

static KeyM_ResultType KeyM_PrvPerformUpdateIntermediateCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);

#if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
static KeyM_ResultType KeyM_PrvPerformUpdateRootX509CertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);

static KeyM_ResultType KeyM_PrvPerformUpdateIntermediateX509CertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);

#endif

#if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
static KeyM_ResultType KeyM_PrvPerformUpdateRootCvcCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);

static KeyM_ResultType KeyM_PrvPerformUpdateIntermediateCvcCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);
#endif

#if ((KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) && \
    (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON))
static Std_ReturnType KeyM_PrvEccKeyPairGenerate(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);
#if (KEYM_CERT_RSA_KEY_GENERATE_ENABLED == STD_ON)
static Std_ReturnType KeyM_PrvRsaKeyPairGenerate(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);
#endif /* #if (KEYM_CERT_RSA_KEY_GENERATE_ENABLED == STD_ON) */
#endif /* #if ((KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) &&
  (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON)) */

#endif /* ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) ||
  (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)) */

#if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
static KeyM_ResultType KeyM_PrvPerformUpdateCrlOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);
#endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */

#endif /* #if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED ==
  STD_OFF) */

#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

#if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON)
static boolean KeyM_PrvElementCheckRule(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementRuleType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementRule);

static boolean KeyM_PrvElementCheckCondition(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion);

static boolean KeyM_PrvElementLessThanCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion);

static boolean KeyM_PrvElementLessOrEqualCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion);

static boolean KeyM_PrvElementGreaterOrEqualCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion);

static boolean KeyM_PrvElementEqualNotCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion);

static boolean KeyM_PrvElementEqualCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion);

static uint64 KeyM_PrvConvertArrayToInteger(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrArray, \
  const uint32 length);

#endif /* #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON) */

static uint32 KeyM_PrvGetDayBetweenDates(\
  P2CONST(KeyM_DateType, AUTOMATIC, KEYM_APPL_CONST) ptrDate1, \
  P2CONST(KeyM_DateType, AUTOMATIC, KEYM_APPL_CONST) ptrDate2);

static uint16 KeyM_PrvCountLeapYear(\
  P2CONST(KeyM_DateType, AUTOMATIC, KEYM_APPL_DATA) ptrDate);

/*******************************************************************************
** Function Name      : KeyM_PrvCheckCertificateElement                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check an element of the certificate base on tag,      **
**                      object identifier                                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrCert, elementStruct, tag                           **
**                                                                            **
** InOut Parameters   : ptrElementIndex                                       **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvMemCmp                                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvCheckCertificateElement(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  const uint16 elementIndex, \
  const uint8 tag, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  const uint16 objectIdLength)
{
  uint16 retVal;
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement;

  /* @Trace: KeyM_SUD_FUNC_209 */
  retVal = KEYM_E_INVALID_FORMAT;
  #if (KEYM_CERT_ELEMENT_OBJECT_TYPE_ENABLED == STD_OFF)
    (void)tag;
  #endif
  if ((ptrCert->NumberOfCertElement > elementIndex) && \
    (NULL_PTR != ptrCert->PtrCertElement))
  {
    /* Check element is suitable */
    ptrCertElement = &ptrCert->PtrCertElement[elementIndex];

    if ((NULL_PTR == ptrCertElement->PtrElement)
    #if (KEYM_CERT_ELEMENT_OBJECT_TYPE_ENABLED == STD_ON)
      && ((tag == ptrCertElement->ObjectType) || \
      (0xFFu == ptrCertElement->ObjectType))
    #endif
    )
    {
      if ((NULL_PTR != ptrObjectId) && \
        (NULL_PTR != ptrCertElement->PtrElementObjectId))
      {
        /* @Trace: KeyM_SUD_FUNC_210 */
        if (objectIdLength == ptrCertElement->ObjectIdLength)
        {
          retVal = KeyM_PrvMemCmp(ptrObjectId, \
            ptrCertElement->PtrElementObjectId, \
            objectIdLength);
        }
      }
      else
      {
        retVal = KEYM_E_OK;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvCountLeapYear                                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get number of leap year before given date             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrDate                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCountLeapYear(\
  P2CONST(KeyM_DateType, AUTOMATIC, KEYM_APPL_DATA) ptrDate)
{
  uint16 years;
  uint16 leapYears;

  /* @Trace: KeyM_SUD_FUNC_298 */
  years = ptrDate->Year;
  /* Check if the current year needs to be considered
     for the count of leap years or not */
  if (ptrDate->Mon <= 2u)
  {
    years--;
  }

  /* An year is a leap year if it is a multiple of 4, \
   multiple of 400 and not a multiple of 100. */
  leapYears = (years / 4u) - (years / 100u) + (years / 400u);

  return leapYears;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvGetDayBetweenDates                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get number of days between two given dates            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrDate1, ptrDate2                                    **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvCountLeapYear                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint32 KeyM_PrvGetDayBetweenDates(\
  P2CONST(KeyM_DateType, AUTOMATIC, KEYM_APPL_CONST) ptrDate1, \
  P2CONST(KeyM_DateType, AUTOMATIC, KEYM_APPL_CONST) ptrDate2)
{
  uint8 indexCnt;
  uint32 diff;
  /* Variable to store number of days from 00/00/0000 to Date1 */
  uint32 dayNum1;
  /* Variable to store number of days from 00/00/0000 to Date2 */
  uint32 dayNum2;
  /* Array to store number of days in all months from January to Dec. */
  uint8 monthDays[KEYM_NUM_MONTH];

  /* @Trace: KeyM_SUD_FUNC_297 */
  /* Initialize the monthDays array */
  monthDays[0u] = 31u;
  monthDays[1u] = 28u;
  monthDays[2u] = 31u;
  monthDays[3u] = 30u;
  monthDays[4u] = 31u;
  monthDays[5u] = 30u;
  monthDays[6u] = 31u;
  monthDays[7u] = 31u;
  monthDays[8u] = 30u;
  monthDays[9u] = 31u;
  monthDays[10u] = 30u;
  monthDays[11u] = 31u;

  /* Calculate dayNum1 using year and day of Date1 */
  dayNum1 = (uint32)(((uint32)(ptrDate1->Year) * ((uint32)365u)) + \
    (uint32)(ptrDate1->Day));
  /* Counts number of leap years before the Date1 */
  dayNum1 += KeyM_PrvCountLeapYear(ptrDate1);

  /* Calculate dayNum2 using year and day of Date2 */
  dayNum2 = (uint32)(((uint32)(ptrDate2->Year) * ((uint32)365u)) + \
    (uint32)(ptrDate2->Day));
  /* Add days for months in Date2 */
  for (indexCnt = 0u; indexCnt < (ptrDate2->Mon - 1u); indexCnt++)
  {
    dayNum2 += monthDays[indexCnt];
  }
  /* Counts number of leap years before the Date2 */
  dayNum2 += KeyM_PrvCountLeapYear(ptrDate2);

  /* Calculate days between dates */
  diff = dayNum2 - dayNum1;

  return diff;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#if (KEYM_USE_STBM == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvGetCurrentTime                                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get current time in seconds from StbM timebase        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : stbMTimeBaseId                                        **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrCurrentTime                                        **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      StbM_GetCurrentTime                                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvGetCurrentTime(\
  StbM_SynchronizedTimeBaseType stbMTimeBaseId, \
  P2VAR(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrCurrentTime)
{
  Std_ReturnType retVal;
  StbM_TimeStampType curTimeStamp;
  StbM_UserDataType userData;

  /* @Trace: KeyM_SUD_FUNC_219 */
  /* Initialize variables */
  curTimeStamp.timeBaseStatus = 0u;
  curTimeStamp.nanoseconds = 0u;
  curTimeStamp.seconds = 0u;
  curTimeStamp.secondsHi = 0u;
  userData.userDataLength = 0u;
  userData.userByte0 = 0u;
  userData.userByte1 = 0u;
  userData.userByte2 = 0u;

  /* polyspace+3 MISRA-C3:10.3 [Justified:Low] "This violation is caused by KeyM. It occurs because StbM_GetCurrentTime invoked here is a dummy code." */
  /* polyspace+2 CERT-C:DCL39-C [Justified:Low] "This violation is caused by KeyM. It occurs because StbM_GetCurrentTime invoked here is a dummy code." */
  /* polyspace+1 MISRA-C3:17.3 [Justified:Low] "This violation is caused by KeyM. It occurs because StbM_GetCurrentTime invoked here is a dummy code." */
  retVal = StbM_GetCurrentTime(stbMTimeBaseId, &curTimeStamp, &userData);

  if (E_OK == retVal)
  {
    /* Get the 16 bits MSB of curTime */
    *ptrCurrentTime = curTimeStamp.secondsHi;
    *ptrCurrentTime = *ptrCurrentTime << 32u;
    /* Get the 32 bits LSB of curTime */
    *ptrCurrentTime += curTimeStamp.seconds;
  }

  (void)userData;
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : KeyM_PrvParseInt                                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse a integer                                       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : length                                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : result                                                **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvParseInt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  const uint8 length, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) resultInt)
{
  Std_ReturnType retVal;
  uint8 indexCnt;
  /* Initialize variables */
  retVal = E_OK;

  *resultInt = 0U;
  /* @Trace: KeyM_SUD_FUNC_211 */
  for (indexCnt = length; 0U < indexCnt; --indexCnt)
  {
    if ((48U > **ptrPosition) || (57U < **ptrPosition))
    {
      /* In the ASCII code , a digits has encoded value from 48 to 57 */
      retVal = E_NOT_OK;
      break;
    }
    else
    {
      *resultInt *= 10U;
      *resultInt += (uint16)((uint16)(**ptrPosition) - ((uint16)48U));
      (*ptrPosition)++;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvCheckDateValid                                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check a date is valid                                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrDate                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCheckDateValid(\
  P2CONST(KeyM_DateType, AUTOMATIC, KEYM_APPL_CONST) ptrDate, \
  const uint16 yearMax, \
  const uint16 yearMin)
{
  Std_ReturnType retVal;
  uint8 monthLength;

  retVal = E_OK;

  /* Check the year value is valid */
  if ((ptrDate->Year > yearMax) || (ptrDate->Year < yearMin))
  {
    /* @Trace: KeyM_SUD_FUNC_212 */
    retVal = E_NOT_OK;
  }
  else
  {
    /* Check month value */
    switch(ptrDate->Mon)
    {
      case 1U:
      case 3U:
      case 5U:
      case 7U:
      case 8U:
      case 10U:
      case 12U:
        /* @Trace: KeyM_SUD_FUNC_213 */
        monthLength = 31U;
        break;
      case 4U:
      case 6U:
      case 9U:
      case 11U:
        /* @Trace: KeyM_SUD_FUNC_214 */
        monthLength = 30U;
        break;
      case 2U:
        /* @Trace: KeyM_SUD_FUNC_215 */
        /* Check leap year */
        if (((0U == (ptrDate->Year % 4U)) && \
          (0U != (ptrDate->Year % 100U))) || \
          (0U == (ptrDate->Year % 400U)))
        {
          monthLength = 29U;
        }
        else
        {
          monthLength = 28U;
        }
        break;
      default:
        /* @Trace: KeyM_SUD_FUNC_216 */
        retVal = E_NOT_OK;
        monthLength = 0u;
        break;
    }
    /* @Trace: KeyM_SUD_FUNC_217 */
    if ((E_OK == retVal) && \
      ((1U > ptrDate->Day) || (ptrDate->Day > monthLength)))
    {
      /* Check day value */
      retVal = E_NOT_OK;
    }
  }
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvConvertDateToSecond                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Convert date time to seconds                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrDate                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrSeconds                                            **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvGetDayBetweenDates                            **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvConvertDateToSecond(\
  P2CONST(KeyM_DateType, AUTOMATIC, KEYM_APPL_CONST) ptrDate, \
  P2VAR(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrSeconds)
{
  uint32 days;
  KeyM_DateType date1970;

  /* @Trace: KeyM_SUD_FUNC_218 */
  /* Initialize date1970: 01/01/1970 */
  date1970.Year = 1970u;
  date1970.Mon = 1u;
  date1970.Day = 1u;
  /* Get days between 01/01/1970 and the input date */
  days = KeyM_PrvGetDayBetweenDates(&date1970, ptrDate);
  /* Convert days to seconds */
  (*ptrSeconds) = (uint64)((uint64)days * (uint64)24u * (uint64)3600u);
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvProcessVerifyCertOperation                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Process Verify Certificate operations                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_JobState, KeyM_CryptoCert, KeyM_CertId,          **
**                      KeyM_CurrentJob, KeyM_ModuleState, KeyM_BackGroundDone**
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvProcessVerifyCertOperation(void)
{
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  Std_ReturnType retVal;

  /* @Trace: KeyM_SUD_FUNC_254 */
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  if ((KEYM_COMPLETE == KeyM_JobState) && \
    (KEYM_TOTAL_CERTIFICATE > KeyM_CertId))
  {
    SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
    /* Get the pointer the certificate */
    ptrCert = &KeyM_CryptoCert[KeyM_CertId];

    /* @Trace: KeyM_SUD_FUNC_255 */
    if (NULL_PTR != ptrCert->RteCertVerifyCallback)
    {
      /* Call the Rte callback */
      retVal = (ptrCert->RteCertVerifyCallback)(ptrCert->CertStatus);
      /* Avoid the returned value because its value always be E_OK */
      KEYM_UNUSED(retVal);
    }
    #if (KEYM_CERT_VERIFY_APPLICATION_CALLBACK_ENABLE == STD_ON)
    else if (NULL_PTR != ptrCert->CertVerifyCallback)
    {
      /* Call the application callback */
      retVal = (ptrCert->CertVerifyCallback)(KeyM_CertId, ptrCert->CertStatus);

      /* Avoid the returned value because its value always be E_OK */
      KEYM_UNUSED(retVal);
    }
    #endif
    else
    {
      /* Do nothing */
    }
    SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
    /* Set current job to be no job */
    KeyM_CurrentJob = KEYM_NO_JOB;
    /* Set module state to be idle */
    KeyM_ModuleState = KEYM_IDLE;
    /* The certificate progress is finished */
    ptrCert->InProgress = KEYM_ZERO;
    /* Set back ground state to be idle */
    KeyM_BackGroundDone = KEYM_FALSE;
    SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  }
  else
  {
    SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPerformVerifyCertPairOperation                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform VerifyCertificates operation                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : certId, upperCertId                                   **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvParseCertificate, KeyM_PrvX509CrlVerify,      **
**                      KeyM_PrvX509CertificatePairVerify,                    **
**                      KeyM_PrvCvcCertificatePairVerify                      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvPerformVerifyCertPairOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrUpperCert)
{
  /* @Trace: KeyM_SUD_FUNC_257 */
  if (KEYM_CERTIFICATE_NOT_PARSED == ptrCert->CertStatus)
  {
    /* If the certificate is not parsed, we do parsing it */
    KeyM_PrvParseCertificate(ptrCert, ptrCert->PtrCertData, \
      ptrCert->CertLength);
  }

  if ((KEYM_E_CERTIFICATE_INVALID_TYPE != ptrCert->CertStatus) && \
    (KEYM_E_CERTIFICATE_INVALID_FORMAT != ptrCert->CertStatus))
  {
    /* @Trace: KeyM_SUD_FUNC_258 */
    switch (ptrCert->CertFormat)
    {
      #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
      case KEYM_CERT_FORMAT_X509:
        KeyM_PrvX509CertificatePairVerify(ptrCert, ptrUpperCert);
        break;
      #endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
      #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
      case KEYM_CERT_FORMAT_CRL:
        KeyM_PrvX509CrlVerify(ptrCert, ptrUpperCert);
        break;
      #endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
      #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
      case KEYM_CERT_FORMAT_CVC:
        KeyM_PrvCvcCertificatePairVerify(ptrCert, ptrUpperCert);
        break;
      #endif /* (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */
      default:
        /* Should not enter here */
        break;
    }
  } /* @if ((KEYM_E_CERTIFICATE_INVALID_TYPE != ptrCert->CertStatus) && \
      (KEYM_E_CERTIFICATE_INVALID_FORMAT != ptrCert->CertStatus)) */
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPerformVerifyCertOperation                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform VerifyCertificate operation                   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_CertChain, KeyM_CryptoCert                       **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvPerformVerifyCertPairOperation                **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvPerformVerifyCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrVerifiedCert)
{
  uint8 indexCnt;
  uint16 upperCertId;
  uint16 curCertId;
  uint16 verifiedCertId;
  uint8 certChainLength;
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrUpperCert;

  /* @Trace: KeyM_SUD_FUNC_266 */
  certChainLength = KeyM_CertChainLength;
  verifiedCertId = ptrVerifiedCert->CertId;

  if ((0u < certChainLength) && \
    (KEYM_CERTIFICATE_CHAIN_MAX_DEPTH >= certChainLength))
  {
    /* Get the root certificate */
    curCertId = KeyM_CertChain[certChainLength - 1u];
    ptrCert = &KeyM_CryptoCert[curCertId];
    /* Verify the root certificate */
    KeyM_PrvPerformVerifyCertPairOperation(ptrCert, ptrCert);
    /* The chain has many certificates */
    if (1u < certChainLength)
    {
      /* @Trace: KeyM_SUD_FUNC_267 */
      for (indexCnt = certChainLength - 1u; 0u < indexCnt; indexCnt--)
      {
        /* Get id of upper certificate */
        upperCertId = KeyM_CertChain[indexCnt];
        /* Get id of lower certificate */
        curCertId = KeyM_CertChain[indexCnt - 1u];
        /* Get the pointer to upper certificate */
        ptrUpperCert = &KeyM_CryptoCert[upperCertId];
        /* Get the pointer to lower certificate */
        ptrCert = &KeyM_CryptoCert[curCertId];

        if (KEYM_CERTIFICATE_VALID == ptrUpperCert->CertStatus)
        {
          /* Verify the lower certificate */
          KeyM_PrvPerformVerifyCertPairOperation(ptrCert, ptrUpperCert);
        }
        else
        {
          ptrVerifiedCert->CertStatus = \
            KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST;
        }
        if ((verifiedCertId == curCertId) || \
          (KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST == \
          ptrVerifiedCert->CertStatus))
        {
          break;
        }
      } /* @for (indexCnt = certChainLength - 1u; indexCnt >= 0u; indexCnt--) */
    }
    else
    {
      /* The chain has only one certificate which is root and
         the root has verified, thus do not thing at here */
    }
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPartTwoOfPerformVerifyCertChainOperation      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of                                     **
**                      KeyM_PrvPerformVerifyCertChainOperation. This function**
**                      is created to reduce code metric of                   **
**                      KeyM_PrvPerformVerifyCertChainOperation               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrPermanentCert, ptrFirstCert                        **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrCertStatus                                         **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_CryptoCert, KeyM_NumberOfCertificates,           **
**                      KeyM_CertChainData                                    **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvConstructCertChain,                           **
**                      KeyM_PrvPerformVerifyCertOperation,                   **
**                      KeyM_PrvPerformVerifyCertPairOperation,               **
**                      KeyM_PrvCopyParsedX509Certificate,                    **
**                      KeyM_PrvCopyParsedCVCCertificate,                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static void KeyM_PrvPartTwoOfPerformVerifyCertChainOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrPermanentCert, \
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrFirstCert, \
  P2VAR(KeyM_CertificateStatusType, AUTOMATIC, KEYM_APPL_DATA) ptrCertStatus)
{
  uint16 retVal;
  uint8 certIndex;
  uint8 numberOfCerts;
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrInterCert;
  P2CONST(KeyM_CertDataType, AUTOMATIC, KEYM_APPL_CONST) ptrCertChainData;
  P2VAR(void, AUTOMATIC, KEYM_APPL_DATA) ptrTmp;
  P2VAR(void, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCertData;
  uint16 certLength;
  #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON)
    P2CONST(KeyM_CertificateElementRuleType, AUTOMATIC, KEYM_APPL_DATA) \
    *ptrCertElementRule;
  #endif

  /* @Trace: KeyM_SUD_FUNC_347 */
  /* Construct the chain from the found permanently stored certificate
    to the root */
  retVal = KeyM_PrvConstructCertChain(ptrPermanentCert);

  if (KEYM_E_OK == retVal)
  {
    /* Verify the constructed chain of permanently stored certificate*/
    KeyM_PrvPerformVerifyCertOperation(ptrPermanentCert);
    if (KEYM_CERTIFICATE_VALID == ptrPermanentCert->CertStatus)
    {
      /* @Trace: KeyM_SUD_FUNC_348 */
      ptrInterCert = ptrFirstCert;
      #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON)
        /* Set the element condition rule of certificate in the chain
          to be NULL, so the certificate verify process shall not
          check the element condition rule */
        ptrInterCert->PtrCertElementRule = NULL_PTR;
      #endif
        /* Verify the first certificate of chain with
          permanently stored certificate */
        KeyM_PrvPerformVerifyCertPairOperation(ptrInterCert, ptrPermanentCert);

      if (KEYM_CERTIFICATE_VALID == ptrInterCert->CertStatus)
      {
        ptrCert = &KeyM_CryptoCert[KeyM_CertId];
        numberOfCerts = KeyM_NumberOfCertificates - 1u;
        if (0u < numberOfCerts)
        {
          /* @Trace: KeyM_SUD_FUNC_350 */
          /* Save the information of the target certificate
            which shall be used later */
          ptrCertData = ptrCert->PtrCertData;
          certLength = ptrCert->CertLength;
          ptrParsedCert = ptrCert->PtrParsedCert;
          #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON)
            ptrCertElementRule = ptrCert->PtrCertElementRule;
            ptrCert->PtrCertElementRule = NULL_PTR;
          #endif
          ptrTmp = ptrParsedCert;
          ptrCertChainData = KeyM_CertChainData;
          /* Verify the intermediate certificate chain */
          for (certIndex = 0u; certIndex < numberOfCerts; certIndex++)
          {
            ptrInterCert->PtrCertData = \
            (uint8*)(ptrCertChainData[certIndex].certData);
            ptrInterCert->CertLength = \
            (uint16)ptrCertChainData[certIndex].certDataLength;

            ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;
            ptrCert->PtrCertData = \
            (uint8*)(ptrCertChainData[certIndex + 1u].certData);
            ptrCert->CertLength = \
            (uint16)ptrCertChainData[certIndex + 1u].certDataLength;
            /* Verify the lower certificate */
            KeyM_PrvPerformVerifyCertPairOperation(ptrCert, ptrInterCert);

            if ((KEYM_CERTIFICATE_VALID == ptrCert->CertStatus) && \
              (certIndex < (numberOfCerts - 1u)))
            {
              /* The lower certificate shall be upper certificate, so exchange
                parsed lower certificate and upper certificate */
              ptrTmp = ptrInterCert->PtrParsedCert;
              ptrInterCert->PtrParsedCert = ptrCert->PtrParsedCert;
              ptrCert->PtrParsedCert = ptrTmp;
            }
            else if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
            {
              break;
            }
            else
            {
              /* code */
            }
          } /* @for (certIndex = 0u; certIndex < numberOfCerts; certIndex++) */

          if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus)
          {
            ptrInterCert->PtrCertData = ptrCert->PtrCertData;
            ptrInterCert->CertLength = ptrCert->CertLength;

            if (ptrTmp == ptrParsedCert)
            {
              #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
              if (KEYM_CERT_FORMAT_X509 == ptrCert->CertFormat)
              {
                /* @Trace: KeyM_SUD_FUNC_354 */
                KeyM_PrvCopyParsedX509Certificate(\
                  (KeyM_X509CertificateType*)ptrCert->PtrParsedCert, \
                  (KeyM_X509CertificateType*)ptrInterCert->PtrParsedCert);
              }
              else
              #endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
              {
                #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
                  /* @Trace: KeyM_SUD_FUNC_355 */
                  KeyM_PrvCopyParsedCVCCertificate(\
                    (KeyM_CvcCertificateType*)ptrCert->PtrParsedCert, \
                    (KeyM_CvcCertificateType*)ptrInterCert->PtrParsedCert);
                #endif /* (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */
              }
            }
            else
            {
              /* @Trace: KeyM_SUD_FUNC_353 */
              ptrInterCert->PtrParsedCert = ptrCert->PtrParsedCert;
              ptrCert->PtrParsedCert = ptrParsedCert;
            }
            /* @Trace: KeyM_SUD_FUNC_356 */
            /* Restore target certificate information */
            ptrCert->PtrCertData = ptrCertData;
            ptrCert->CertLength = certLength;
            ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;
            #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON)
              ptrCert->PtrCertElementRule = ptrCertElementRule;
            #endif
            /* Verify the target certificate */
            KeyM_PrvPerformVerifyCertPairOperation(ptrCert, ptrInterCert);
            *ptrCertStatus = ptrCert->CertStatus;
          }
        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_349 */
          /* Verify the target certificate */
          KeyM_PrvPerformVerifyCertPairOperation(ptrCert, ptrInterCert);
          *ptrCertStatus = ptrCert->CertStatus;
        }
      } /* @if (KEYM_CERTIFICATE_VALID == ptrInterCert->CertStatus) */
    } /* @if (KEYM_CERTIFICATE_VALID == ptrPermanentCert->CertStatus) */
  } /* @if (KEYM_E_OK == retVal) */
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvPartOneOfPerformVerifyCertChainOperation      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of                                     **
**                      KeyM_PrvPerformVerifyCertChainOperation. This function**
**                      is created to reduce code metric of                   **
**                      KeyM_PrvPerformVerifyCertChainOperation               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrInterCert                                          **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrCertStatus                                         **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_CryptoCert                                       **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvX509CertCheckParent, KeyM_PrvCvcCheckParent,  **
**                      KeyM_PrvPartTwoOfPerformVerifyCertChainOperation      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static void KeyM_PrvPartOneOfPerformVerifyCertChainOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrInterCert, \
  P2VAR(KeyM_CertificateStatusType, AUTOMATIC, KEYM_APPL_DATA) ptrCertStatus)
{
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  uint8 certIndex;
  uint16 retVal = KEYM_E_OK;

  /* @Trace: KeyM_SUD_FUNC_357 */
  /* Find the root and intermediate certificates which are permanently stored
    to construct the complete chain */
  for (certIndex = 0; KEYM_TOTAL_CERTIFICATE > certIndex; certIndex++)
  {
    ptrCert = &KeyM_CryptoCert[certIndex];
    if (((KEYM_CERTIFICATE_VALID == ptrCert->CertStatus) || \
      (KEYM_CERTIFICATE_PARSED_NOT_VALIDATED == ptrCert->CertStatus)) && \
      (ptrInterCert->CertFormat == ptrCert->CertFormat))
    {
      #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
      if (KEYM_CERT_FORMAT_X509 == ptrInterCert->CertFormat)
      {
        /* @Trace: KeyM_SUD_FUNC_358 */
        retVal = KeyM_PrvX509CertCheckParent(\
          (KeyM_X509CertificateType*)ptrInterCert->PtrParsedCert, \
          (KeyM_X509CertificateType*)ptrCert->PtrParsedCert);
      }
      else
      #endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
      {
        #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
          /* @Trace: KeyM_SUD_FUNC_359 */
          retVal = KeyM_PrvCvcCheckParent(\
            (KeyM_CvcCertificateType*)ptrInterCert->PtrParsedCert, \
            (KeyM_CvcCertificateType*)ptrCert->PtrParsedCert);
        #endif /* (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */
      }

      if (KEYM_E_OK == retVal)
      {
        /* @Trace: KeyM_SUD_FUNC_360 */
        KeyM_PrvPartTwoOfPerformVerifyCertChainOperation(ptrCert, \
          ptrInterCert, ptrCertStatus);
        break;
      }
    }
  } /* @for (certIndex = 0; certIndex < KEYM_TOTAL_CERTIFICATE; certIndex++) */
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvPerformVerifyCertChainOperation               **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform VerifyCertificateChain operation              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_CryptoCert, KeyM_CertId                          **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvMemCopy, KeyM_PrvCopyParsedX509Certificate,   **
**                      KeyM_PrvCopyParsedCVCCertificate,                     **
**                      KeyM_PrvParseCertificate,                             **
**                      KeyM_PrvPartOneOfPerformVerifyCertChainOperation      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvPerformVerifyCertChainOperation(void)
{
  uint16 retVal;
  KeyM_CertificateStatusType certStatus;
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrInterCert;
  P2VAR(void, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert;
  KeyM_CertType interCert;
  /* Internal buffers used for parsed certificate */
  KeyM_ElementType certIssuerUniqueID;
  KeyM_ElementType certSubjectUniqueID;
  KeyM_ElementType certPublicKeyAlgorithm;
  KeyM_ElementType certVersion;
  KeyM_ElementType certNotBefore;
  KeyM_ElementType certNotAfter;
  KeyM_ElementType certSignatureValue;
  #if (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U)
    /* Internal extensions used for certificate service */
    KeyM_ElementType certExtensions[KEYM_CERT_MAX_EXTENSION_NUMBER];
  #endif /* (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U) */

  #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
    /* Internal buffers used for parsed X509 certificate */
    KeyM_ElementType certSubject[KEYM_CERT_MAX_NAME_NUMBER];
    KeyM_ElementType certSerial;
    KeyM_ElementType certSubjectPublicKey;
    KeyM_ElementType certIssuer[KEYM_CERT_MAX_NAME_NUMBER];
    KeyM_ElementType certSignature;
    KeyM_ElementType certSignatureAlgorithm;
    KeyM_X509CertificateType parsedX509Cert;

  #endif /*(KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */

  #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
    /* Internal buffers used for parsed CVC */
    KeyM_CvcCertificateType parsedCvcCert;
    KeyM_ElementType certDomainParams[KEYM_CERT_MAX_DOMAIN_PARAM_NUMBER];
    KeyM_ElementType certHolderAuthorTemplate;
  #endif /*(KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */

  /* @Trace: KeyM_SUD_FUNC_273 */
  certStatus = KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST;

  if (KEYM_TOTAL_CERTIFICATE > KeyM_CertId)
  {
    retVal = KEYM_E_OK;
    ptrCert = &KeyM_CryptoCert[KeyM_CertId];
    ptrInterCert = &interCert;
    /* Initialize the internal certificates */
    (void)KeyM_PrvMemCopy(ptrCert, ptrInterCert, sizeof(KeyM_CertType));

    #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
    if (KEYM_CERT_FORMAT_X509 == ptrCert->CertFormat)
    {
      /* @Trace: KeyM_SUD_FUNC_274 */
      ptrInterCert->PtrParsedCert = (void*)(&parsedX509Cert);
      ptrParsedCert = (void*)(&parsedX509Cert);

      ((KeyM_X509CertificateType*)ptrParsedCert)->PtrSerialNumber = \
        &certSerial;
      ((KeyM_X509CertificateType*)ptrParsedCert)->PtrRawSignature = \
        &certSignature;
      ((KeyM_X509CertificateType*)ptrParsedCert)->PtrRawNotBefore = \
        &certNotBefore;
      ((KeyM_X509CertificateType*)ptrParsedCert)->PtrRawNotAfter = \
        &certNotAfter;
      ((KeyM_X509CertificateType*)ptrParsedCert)->PtrPublicKeyAlgorithm = \
        &certPublicKeyAlgorithm;
      ((KeyM_X509CertificateType*)ptrParsedCert)->PtrSubjectPublicKey = \
        &certSubjectPublicKey;
      ((KeyM_X509CertificateType*)ptrParsedCert)->PtrSignatureAlgorithm = \
        &certSignatureAlgorithm;
      ((KeyM_X509CertificateType*)ptrParsedCert)->PtrSignatureValue = \
        &certSignatureValue;

      #if (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U)
        ((KeyM_X509CertificateType*)ptrParsedCert)->PtrExtensions = \
          &certExtensions[0u];
        ((KeyM_X509CertificateType*)ptrParsedCert)->ExtensionNum = \
          ((KeyM_X509CertificateType*)ptrCert->PtrParsedCert)->ExtensionNum;
      #endif /* (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U) */

      ((KeyM_X509CertificateType*)ptrParsedCert)->PtrIssuer = &certIssuer[0u];
      ((KeyM_X509CertificateType*)ptrParsedCert)->PtrSubject = &certSubject[0u];
      ((KeyM_X509CertificateType*)ptrParsedCert)->IssuerNum = \
        ((KeyM_X509CertificateType*)ptrCert->PtrParsedCert)->IssuerNum;
      ((KeyM_X509CertificateType*)ptrParsedCert)->SubjectNum = \
        ((KeyM_X509CertificateType*)ptrCert->PtrParsedCert)->SubjectNum;

      if (NULL_PTR == \
        ((KeyM_X509CertificateType*)ptrCert->PtrParsedCert)->PtrRawVersion)
      {
        ((KeyM_X509CertificateType*)ptrParsedCert)->PtrRawVersion = NULL_PTR;
      }
      else
      {
        ((KeyM_X509CertificateType*)ptrParsedCert)->PtrRawVersion = \
          &certVersion;
      }

      if (NULL_PTR == \
        ((KeyM_X509CertificateType*)ptrCert->PtrParsedCert)->PtrIssuerUniqueID)
      {
        ((KeyM_X509CertificateType*)ptrParsedCert)->PtrIssuerUniqueID = \
          NULL_PTR;
      }
      else
      {
        ((KeyM_X509CertificateType*)ptrParsedCert)->PtrIssuerUniqueID = \
          &certIssuerUniqueID;
      }

      if (NULL_PTR == \
        ((KeyM_X509CertificateType*)ptrCert->PtrParsedCert)->PtrSubjectUniqueID)
      {
        ((KeyM_X509CertificateType*)ptrParsedCert)->PtrSubjectUniqueID = \
          NULL_PTR;
      }
      else
      {
        ((KeyM_X509CertificateType*)ptrParsedCert)->PtrSubjectUniqueID = \
          &certSubjectUniqueID;
      }

      KeyM_PrvCopyParsedX509Certificate(\
        (KeyM_X509CertificateType*)ptrCert->PtrParsedCert, \
        (KeyM_X509CertificateType*)ptrInterCert->PtrParsedCert);
    }
    else
    #endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
    {
      #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
      if (KEYM_CERT_FORMAT_CVC == ptrCert->CertFormat)
      {
        /* @Trace: KeyM_SUD_FUNC_275 */
        ptrInterCert->PtrParsedCert = (void*)(&parsedCvcCert);
        ptrParsedCert = (void*)(&parsedCvcCert);

        ((KeyM_CvcCertificateType*)ptrParsedCert)->PtrRawProfileId = \
          &certVersion;
        ((KeyM_CvcCertificateType*)ptrParsedCert)->PtrRawAuthorityRefer = \
          &certIssuerUniqueID;
        ((KeyM_CvcCertificateType*)ptrParsedCert)->PtrRawEffectiveDate = \
          &certNotBefore;
        ((KeyM_CvcCertificateType*)ptrParsedCert)->PtrRawExpirationDate = \
          &certNotAfter;
        ((KeyM_CvcCertificateType*)ptrParsedCert)->PtrRawPublicKeyObjectId = \
          &certPublicKeyAlgorithm;
        ((KeyM_CvcCertificateType*)ptrParsedCert)->PtrSignatureValue = \
          &certSignatureValue;
        ((KeyM_CvcCertificateType*)ptrParsedCert)->PtrRawHolderRefer = \
          &certSubjectUniqueID;
        ((KeyM_CvcCertificateType*)ptrParsedCert)->PtrRawHolderAuthorTemplate =\
          &certHolderAuthorTemplate;

        #if (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U)
        ((KeyM_CvcCertificateType*)ptrParsedCert)->PtrExtensions = \
          &certExtensions[0u];
        ((KeyM_CvcCertificateType*)ptrParsedCert)->ExtensionNum = \
          ((KeyM_CvcCertificateType*)ptrCert->PtrParsedCert)->ExtensionNum;
        #endif /* (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U) */

        ((KeyM_CvcCertificateType*)ptrParsedCert)->PtrPublicKeyDomainParams = \
          &certDomainParams[0u];
        ((KeyM_CvcCertificateType*)ptrParsedCert)->DomainParamNum = \
          ((KeyM_CvcCertificateType*)ptrCert->PtrParsedCert)->DomainParamNum;

        KeyM_PrvCopyParsedCVCCertificate(\
          (KeyM_CvcCertificateType*)ptrCert->PtrParsedCert, \
          (KeyM_CvcCertificateType*)ptrInterCert->PtrParsedCert);
      }
      else
      #endif /* (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */
      {
        /* @Trace: KeyM_SUD_FUNC_276 */
        retVal = E_NOT_OK;
      }
    }

    if (KEYM_E_OK == retVal)
    {
      /* @Trace: KeyM_SUD_FUNC_277 */
      /* Set the certificate status is not parsed to allow parsing
        new certificate */
      ptrInterCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;
      /* Parse the first certificate in the intermediate certificate chain */
      ptrInterCert->PtrCertData = (uint8*)(KeyM_CertChainData[0u].certData);
      ptrInterCert->CertLength = \
        (uint16)(KeyM_CertChainData[0u].certDataLength);

      KeyM_PrvParseCertificate(ptrInterCert, ptrInterCert->PtrCertData, \
        ptrInterCert->CertLength);

      if (KEYM_CERTIFICATE_PARSED_NOT_VALIDATED == ptrInterCert->CertStatus)
      {
        KeyM_PrvPartOneOfPerformVerifyCertChainOperation(ptrInterCert, \
          &certStatus);
      } /* @if (KEYM_CERTIFICATE_PARSED_NOT_VALIDATED ==
        ptrInterUpperCert->CertStatus) */
    }
    KeyM_CryptoCert[KeyM_CertId].CertStatus = certStatus;
  }
  (void)retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (((KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) && \
      (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) && \
      (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON) && \
      (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)) || \
      (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON))
/*******************************************************************************
** Function Name      : KeyM_PrvConvertRsaPublicKeyFormat                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Convert RSA public key according                      **
**                      CRYPTO_KE_FORMAT_BIN_RSA_PUBLICKEY format             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrModulus, modulusLen, ptrExponent, exponentLen      **
**                                                                            **
** InOut Parameters   : ptrPublicKeyLength                                    **
**                                                                            **
** Output Parameters  : ptrPublicKeyData                                      **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1WriteBuffer, KeyM_Asn1WriteLength,           **
**                      KeyM_Asn1WriteTag                                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvConvertRsaPublicKeyFormat(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrModulus, \
  const uint16 modulusLen, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExponent, \
  const uint16 exponentLen, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPublicKeyData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKeyLength)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  uint8 bytesToStoreLen;
  uint16 length;

  /* @Trace: KeyM_SUD_FUNC_224 */
  bytesToStoreLen = 0u;
  length = 0u;
  ptrStart = *ptrPublicKeyData;
  ptrPosition = &ptrStart[*ptrPublicKeyLength];
  /* Write data of publicExponent */
  retVal = KeyM_Asn1WriteBuffer(&ptrPosition, (const uint8*)ptrStart, \
    ptrExponent, exponentLen);

  if (E_OK == retVal)
  {
    length += exponentLen;
    /* Write length of publicExponent data */
    retVal = KeyM_Asn1WriteLength(&ptrPosition, ptrStart, \
      exponentLen, &bytesToStoreLen);
    /* @Trace: KeyM_SUD_FUNC_225 */
    if (E_OK == retVal)
    {
      length += bytesToStoreLen;
      /* Write tag of publicExponent */
      retVal = KeyM_Asn1WriteTag(&ptrPosition, ptrStart, \
        KEYM_ASN1_INTEGER, &bytesToStoreLen);

      if (E_OK == retVal)
      {
        length += bytesToStoreLen;
        /* Write data of modulus */
        retVal = KeyM_Asn1WriteBuffer(&ptrPosition, ptrStart,\
          ptrModulus, modulusLen);
        /* @Trace: KeyM_SUD_FUNC_226 */
        if (E_OK == retVal)
        {
          length += modulusLen;
          /* Write length of modulus data */
          retVal = KeyM_Asn1WriteLength(&ptrPosition, ptrStart,\
            modulusLen, &bytesToStoreLen);
          /* @Trace: KeyM_SUD_FUNC_227 */
          if (E_OK == retVal)
          {
            length += bytesToStoreLen;
            /* Write tag of modulus */
            retVal = KeyM_Asn1WriteTag(&ptrPosition, ptrStart, \
              KEYM_ASN1_INTEGER, &bytesToStoreLen);

            if (E_OK == retVal)
            {
              length += bytesToStoreLen;
              /* Write length of RSAPublicKey */
              retVal = KeyM_Asn1WriteLength(&ptrPosition, ptrStart,\
                length, &bytesToStoreLen);
              /* @Trace: KeyM_SUD_FUNC_228 */
              if (E_OK == retVal)
              {
                length += bytesToStoreLen;
                /* Write tag of RSAPublicKey */
                retVal = KeyM_Asn1WriteTag(&ptrPosition, ptrStart, \
                  KEYM_ASN1_SEQUENCE | KEYM_ASN1_PC_CONSTRUCTED,\
                  &bytesToStoreLen);

                if (E_OK == retVal)
                {
                  length += bytesToStoreLen;
                  *ptrPublicKeyData = ptrPosition;
                  *ptrPublicKeyLength = length;
                }
              }
            } /* @if (KEYM_E_OK == retVal) */
          } /* @if (KEYM_E_OK == retVal) */
        } /* @if (KEYM_E_OK == retVal) */
      } /* @if (KEYM_E_OK == retVal) */
    } /* @if (KEYM_E_OK == retVal) */
  } /* @if (KEYM_E_OK == retVal) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (((KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) && \
  (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) && \
  (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON) && \
  (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)) || \
  (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)) */

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)

#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)

#if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
     (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON))
/*******************************************************************************
** Function Name      : KeyM_PrvPerformSetRootCertOperation                   **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform set root certificate operation                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : ptrCert                                               **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : KeyM_ResultType                                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_RequestDataLength, KeyM_PtrRequestData           **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvMemCopy,KeyM_PrvPerformVerifyCertPairOperation**
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_ResultType KeyM_PrvPerformSetRootCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  KeyM_ResultType operationResult;
  operationResult = KEYM_RT_KEY_CERT_UPDATE_FAIL;

  if ((KEYM_TRUE == ptrCert->IsRoot) && \
    (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus))
  {
    /* @Trace: KeyM_SUD_FUNC_362 */
    /* Copy certificate data to data slot of the certificate */
    ptrCert->CertLength = KeyM_RequestDataLength;

    (void)KeyM_PrvMemCopy(KeyM_PtrRequestData, \
      &ptrCert->PtrCertData[0u], KeyM_RequestDataLength);
    /* Set the certificate status is not parsed to allow parsing
      new root certificate */
    ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;
    /* Verify the root certificate */
    KeyM_PrvPerformVerifyCertPairOperation(ptrCert, ptrCert);

    if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus)
    {
      /* @Trace: KeyM_SUD_FUNC_363 */
      operationResult = KEYM_RT_OK;
    }
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_361 */
    operationResult = KEYM_RT_KEY_CERT_INVALID;
  }
  return operationResult;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPerformUpdateRootCertOperation                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform update root certificate operation             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : ptrCert                                               **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : KeyM_ResultType                                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvPerformUpdateRootX509CertOperation,           **
**                      KeyM_PrvPerformUpdateRootCvcCertOperation             **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_ResultType KeyM_PrvPerformUpdateRootCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  KeyM_ResultType operationResult;
  #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_OFF)
    /* @Trace: KeyM_SUD_FUNC_364 */
    operationResult = KEYM_RT_KEY_CERT_INVALID;
  #endif /* (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_OFF) */

  if ((KEYM_TRUE == ptrCert->IsRoot) && \
    (KEYM_CERTIFICATE_NOT_PARSED != ptrCert->CertStatus) && \
    (KEYM_CERTIFICATE_PARSED_NOT_VALIDATED != ptrCert->CertStatus) && \
    (KEYM_CERTIFICATE_NOT_AVAILABLE != ptrCert->CertStatus) && \
    (KEYM_E_CERTIFICATE_INVALID_TYPE != ptrCert->CertStatus) && \
    (KEYM_E_CERTIFICATE_INVALID_FORMAT != ptrCert->CertStatus))
  {
    #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
    if (KEYM_CERT_FORMAT_X509 == ptrCert->CertFormat)
    {
      /* @Trace: KeyM_SUD_FUNC_366 */
      operationResult = KeyM_PrvPerformUpdateRootX509CertOperation(ptrCert);
    }
    else
    #endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
    {
      /* @Trace: KeyM_SUD_FUNC_367 */
      #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
        operationResult = KeyM_PrvPerformUpdateRootCvcCertOperation(ptrCert);
      #endif /* (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */
    }
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_365 */
    operationResult = KEYM_RT_KEY_CERT_INVALID;
  }

  return operationResult;

}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPerformUpdateIntermediateCertOperation        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform update intermediate certificate operation     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : ptrCert                                               **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : KeyM_ResultType                                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvPerformUpdateIntermediateX509CertOperation,   **
**                      KeyM_PrvPerformUpdateIntermediateCvcCertOperation     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_ResultType KeyM_PrvPerformUpdateIntermediateCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  KeyM_ResultType operationResult;

  #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_OFF)
    /* @Trace: KeyM_SUD_FUNC_368 */
    operationResult = KEYM_RT_KEY_CERT_INVALID;
  #endif /* (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_OFF) */

  if ((KEYM_FALSE == ptrCert->IsRoot) && \
    (KEYM_CERT_FORMAT_CRL != ptrCert->CertFormat) && \
    (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus))
  {
    #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
    if (KEYM_CERT_FORMAT_X509 == ptrCert->CertFormat)
    {
      /* @Trace: KeyM_SUD_FUNC_370 */
      operationResult = \
        KeyM_PrvPerformUpdateIntermediateX509CertOperation(ptrCert);
    }
    else
    #endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
    {
      #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
      /* @Trace: KeyM_SUD_FUNC_371 */
        operationResult = \
          KeyM_PrvPerformUpdateIntermediateCvcCertOperation(ptrCert);
      #endif /* (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */
    }
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_369 */
    operationResult = KEYM_RT_KEY_CERT_INVALID;
  }

  return operationResult;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"


#if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvPerformUpdateRootX509CertOperation            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform update X509 root certificate operation        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : ptrCert                                               **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : KeyM_ResultType                                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_PtrRequestData, KeyM_RequestDataLength           **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvCopyParsedX509Certificate, KeyM_PrvMemCmp,    **
**                      KeyM_PrvPerformVerifyCertPairOperation,               **
**                      KeyM_PrvAdjustX509Certificate, KeyM_PrvX509NameCmp    **
**                      KeyM_PrvRecoverX509Certificate                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_ResultType KeyM_PrvPerformUpdateRootX509CertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_DATA) ptrCertData;
  uint16 certDataLength;
  KeyM_ResultType operationResult;
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrX509Cert;
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrInterX509Cert;
  /* Internal buffers used for parsed certificate */
  KeyM_X509CertificateType parsedX509Cert;
  KeyM_ElementType certIssuerUniqueID;
  KeyM_ElementType certSubjectUniqueID;
  KeyM_ElementType certPublicKeyAlgorithm;
  KeyM_ElementType certVersion;
  KeyM_ElementType certNotBefore;
  KeyM_ElementType certNotAfter;
  KeyM_ElementType certSignatureValue;
  KeyM_ElementType certSubject[KEYM_CERT_MAX_NAME_NUMBER];
  KeyM_ElementType certSerial;
  KeyM_ElementType certSubjectPublicKey;
  KeyM_ElementType certIssuer[KEYM_CERT_MAX_NAME_NUMBER];
  KeyM_ElementType certSignature;
  KeyM_ElementType certSignatureAlgorithm;
  #if (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U)
    /* Internal extensions used for certificate service */
    KeyM_ElementType certExtensions[KEYM_CERT_MAX_EXTENSION_NUMBER];
  #endif /* (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U) */

  /* @Trace: KeyM_SUD_FUNC_372 */
  operationResult = KEYM_RT_KEY_CERT_UPDATE_FAIL;
  ptrX509Cert = (KeyM_X509CertificateType*)ptrCert->PtrParsedCert;
  ptrInterX509Cert = &parsedX509Cert;

  ptrInterX509Cert->PtrSerialNumber = &certSerial;
  ptrInterX509Cert->PtrRawSignature = &certSignature;
  ptrInterX509Cert->PtrRawNotBefore = &certNotBefore;
  ptrInterX509Cert->PtrRawNotAfter = &certNotAfter;
  ptrInterX509Cert->PtrPublicKeyAlgorithm = &certPublicKeyAlgorithm;
  ptrInterX509Cert->PtrSubjectPublicKey = &certSubjectPublicKey;
  ptrInterX509Cert->PtrSignatureAlgorithm = &certSignatureAlgorithm;
  ptrInterX509Cert->PtrSignatureValue = &certSignatureValue;
  ptrInterX509Cert->PtrIssuer = &certIssuer[0u];
  ptrInterX509Cert->PtrSubject = &certSubject[0u];
  ptrInterX509Cert->IssuerNum = ptrX509Cert->IssuerNum;
  ptrInterX509Cert->SubjectNum = ptrX509Cert->SubjectNum;

  #if (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U)
    ptrInterX509Cert->PtrExtensions = &certExtensions[0u];
    ptrInterX509Cert->ExtensionNum = ptrX509Cert->ExtensionNum;
  #endif /* (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U) */

  if (NULL_PTR == ptrX509Cert->PtrRawVersion)
  {
    ptrInterX509Cert->PtrRawVersion = NULL_PTR;
  }
  else
  {
    ptrInterX509Cert->PtrRawVersion = &certVersion;
  }

  if (NULL_PTR == ptrX509Cert->PtrIssuerUniqueID)
  {
    ptrInterX509Cert->PtrIssuerUniqueID = NULL_PTR;
  }
  else
  {
    ptrInterX509Cert->PtrIssuerUniqueID = &certIssuerUniqueID;
  }

  if (NULL_PTR == ptrX509Cert->PtrSubjectUniqueID)
  {
    ptrInterX509Cert->PtrSubjectUniqueID = NULL_PTR;
  }
  else
  {
    ptrInterX509Cert->PtrSubjectUniqueID = &certSubjectUniqueID;
  }

  KeyM_PrvCopyParsedX509Certificate(ptrX509Cert, ptrInterX509Cert);

  /* Save the pointer of data of root certificate */
  ptrCertData = ptrCert->PtrCertData;
  certDataLength = ptrCert->CertLength;
  /* Update the pointer to new certificate data  */
  ptrCert->PtrCertData = (uint8*)KeyM_PtrRequestData;
  ptrCert->CertLength = KeyM_RequestDataLength;
  /* Set the certificate status is not parsed to allow parsing
    new root certificate */
  ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;
  /* Verify the new root certificate */
  KeyM_PrvPerformVerifyCertPairOperation(ptrCert, ptrCert);

  /* Check the new root certificate with the current root certificate:
    - The new root and current root must have the same subject name and
    the same public key */
  if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus)
  {
    /* @Trace: KeyM_SUD_FUNC_376 */
    /* Check subject name 
     * Support Universal cert configuration
     */
    retVal = KeyM_PrvX509NameCmp(ptrX509Cert->PtrSubject, \
                                 ptrInterX509Cert->PtrSubject, 
                                 ptrX509Cert->SubjectNum, 
                                 ptrInterX509Cert->SubjectNum);

    if ((E_OK == retVal) && \
      (ptrX509Cert->PtrPublicKeyAlgorithm->Element.Length == \
      ptrInterX509Cert->PtrPublicKeyAlgorithm->Element.Length))
    {
      /* Check public key algorithm */
      retVal = KeyM_PrvMemCmp(\
        ptrX509Cert->PtrPublicKeyAlgorithm->Element.PtrData, \
        ptrInterX509Cert->PtrPublicKeyAlgorithm->Element.PtrData, \
        ptrInterX509Cert->PtrPublicKeyAlgorithm->Element.Length);

      if ((E_OK == retVal) && \
        (ptrX509Cert->PtrSubjectPublicKey->Element.Length == \
        ptrInterX509Cert->PtrSubjectPublicKey->Element.Length))
      {
        /* Check public key value */
        retVal = KeyM_PrvMemCmp(\
          ptrX509Cert->PtrSubjectPublicKey->Element.PtrData, \
          ptrInterX509Cert->PtrSubjectPublicKey->Element.PtrData, \
          ptrInterX509Cert->PtrSubjectPublicKey->Element.Length);
        /* @Trace: KeyM_SUD_FUNC_377 */
        if (E_OK == retVal)
        {
          operationResult = KEYM_RT_OK;
          /* Copy new certificate data to certificate data buffer */
          (void)KeyM_PrvMemCopy(KeyM_PtrRequestData, ptrCertData,\
            KeyM_RequestDataLength);
          /* Adjust the parsed certificate */
          KeyM_PrvAdjustX509Certificate(ptrX509Cert, KeyM_PtrRequestData, \
            ptrCertData);
        }
      } /* @if (E_OK == retVal) */
    } /* @if (E_OK == retVal) */
  } /* @if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus) */

  if (KEYM_RT_OK != operationResult)
  {
    /* @Trace: KeyM_SUD_FUNC_378 */
    /* Restore the parsed certificate */
    KeyM_PrvCopyParsedX509Certificate(ptrInterX509Cert, ptrX509Cert);

    KeyM_PrvRecoverX509Certificate(ptrCert);

    /* Restore the length of data of current certificate */
    ptrCert->CertLength = certDataLength;
    /* Reset the status of current certificate to be valid */
    ptrCert->CertStatus = KEYM_CERTIFICATE_VALID;
  }
  /* Restore the pointer to data buffer of current certificate */
  ptrCert->PtrCertData = ptrCertData;

  return operationResult;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPerformUpdateIntermediateX509CertOperation    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform update X509 intermediate certificate operation**
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : ptrCert                                               **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_PtrRequestData, KeyM_RequestDataLength           **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvConstructCertChain, KeyM_PrvMemCopy,          **
**                      KeyM_PrvCopyParsedX509Certificate,                    **
**                      KeyM_PrvPerformVerifyCertOperation,                   **
**                      KeyM_PrvAdjustX509Certificate,                        **
**                      KeyM_PrvCopyParsedX509Certificate,                    **
**                      KeyM_PrvRecoverX509Certificate                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_ResultType KeyM_PrvPerformUpdateIntermediateX509CertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  P2VAR(uint8, AUTOMATIC, KEYM_DATA) ptrCertData;
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrX509Cert;
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrInterX509Cert;
  uint16 certDataLength;
  Std_ReturnType retVal;
  KeyM_ResultType operationResult;
  /* Internal buffers used for parsed certificate */
  KeyM_X509CertificateType parsedX509Cert;
  KeyM_ElementType certIssuerUniqueID;
  KeyM_ElementType certSubjectUniqueID;
  KeyM_ElementType certPublicKeyAlgorithm;
  KeyM_ElementType certVersion;
  KeyM_ElementType certNotBefore;
  KeyM_ElementType certNotAfter;
  KeyM_ElementType certSignatureValue;
  KeyM_ElementType certSubject[KEYM_CERT_MAX_NAME_NUMBER];
  KeyM_ElementType certSerial;
  KeyM_ElementType certSubjectPublicKey;
  KeyM_ElementType certIssuer[KEYM_CERT_MAX_NAME_NUMBER];
  KeyM_ElementType certSignature;
  KeyM_ElementType certSignatureAlgorithm;
  #if (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U)
    /* Internal extensions used for certificate service */
    KeyM_ElementType certExtensions[KEYM_CERT_MAX_EXTENSION_NUMBER];
  #endif /* (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U) */

  /* @Trace: KeyM_SUD_FUNC_379 */
  operationResult = KEYM_RT_KEY_CERT_UPDATE_FAIL;
  /* Construct the certificate chain to validate the certificate */
  retVal = KeyM_PrvConstructCertChain(ptrCert);

  if (E_OK == retVal)
  {
    ptrX509Cert = (KeyM_X509CertificateType*)ptrCert->PtrParsedCert;
    ptrInterX509Cert = &parsedX509Cert;

    ptrInterX509Cert->PtrSerialNumber = &certSerial;
    ptrInterX509Cert->PtrRawSignature = &certSignature;
    ptrInterX509Cert->PtrRawNotBefore = &certNotBefore;
    ptrInterX509Cert->PtrRawNotAfter = &certNotAfter;
    ptrInterX509Cert->PtrPublicKeyAlgorithm = &certPublicKeyAlgorithm;
    ptrInterX509Cert->PtrSubjectPublicKey = &certSubjectPublicKey;
    ptrInterX509Cert->PtrSignatureAlgorithm = &certSignatureAlgorithm;
    ptrInterX509Cert->PtrSignatureValue = &certSignatureValue;
    ptrInterX509Cert->PtrIssuer = &certIssuer[0u];
    ptrInterX509Cert->PtrSubject = &certSubject[0u];
    ptrInterX509Cert->IssuerNum = ptrX509Cert->IssuerNum;
    ptrInterX509Cert->SubjectNum = ptrX509Cert->SubjectNum;

    #if (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U)
      ptrInterX509Cert->PtrExtensions = &certExtensions[0u];
      ptrInterX509Cert->ExtensionNum = ptrX509Cert->ExtensionNum;
    #endif /* (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U) */

    if (NULL_PTR == ptrX509Cert->PtrRawVersion)
    {
      ptrInterX509Cert->PtrRawVersion = NULL_PTR;
    }
    else
    {
      ptrInterX509Cert->PtrRawVersion = &certVersion;
    }

    if (NULL_PTR == ptrX509Cert->PtrIssuerUniqueID)
    {
      ptrInterX509Cert->PtrIssuerUniqueID = NULL_PTR;
    }
    else
    {
      ptrInterX509Cert->PtrIssuerUniqueID = &certIssuerUniqueID;
    }

    if (NULL_PTR == ptrX509Cert->PtrSubjectUniqueID)
    {
      ptrInterX509Cert->PtrSubjectUniqueID = NULL_PTR;
    }
    else
    {
      ptrInterX509Cert->PtrSubjectUniqueID = &certSubjectUniqueID;
    }
    /* Save the parsed certificate */
    KeyM_PrvCopyParsedX509Certificate(ptrX509Cert, ptrInterX509Cert);

    /* Save the pointer of data of certificate */
    ptrCertData = ptrCert->PtrCertData;
    certDataLength = ptrCert->CertLength;
    /* Update the pointer to new certificate data  */
    ptrCert->PtrCertData = (uint8*)KeyM_PtrRequestData;
    ptrCert->CertLength = KeyM_RequestDataLength;
    /* Set the certificate status is not parsed to allow parsing
     new certificate */
    ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;

    /* Verify the intermediate certificate */
    KeyM_PrvPerformVerifyCertOperation(ptrCert);

    if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus)
    {
      /* @Trace: KeyM_SUD_FUNC_380 */
      /* Copy new certificate data to certificate data buffer */
      (void)KeyM_PrvMemCopy(KeyM_PtrRequestData, ptrCertData,\
        KeyM_RequestDataLength);
      /* Adjust the parsed certificate */
      KeyM_PrvAdjustX509Certificate(ptrX509Cert, KeyM_PtrRequestData, \
        ptrCertData);
      operationResult = KEYM_RT_OK;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_381 */
      if (KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST != ptrCert->CertStatus)
      {
        /* Restore the parsed certificate */
        KeyM_PrvCopyParsedX509Certificate(ptrInterX509Cert, ptrX509Cert);

        KeyM_PrvRecoverX509Certificate(ptrCert);
      }

      /* Restore the length of data of current certificate */
      ptrCert->CertLength = certDataLength;
      /* Restore the cetificate status  */
      ptrCert->CertStatus = KEYM_CERTIFICATE_VALID;
    } /* @if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus) */

    /* Restore the pointer to data buffer of current certificate */
    ptrCert->PtrCertData = ptrCertData;
  } /* @if (E_OK == retVal) */

  return operationResult;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */

#if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvPerformUpdateRootCvcCertOperation             **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform update CVC root certificate operation         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : ptrCert                                               **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : KeyM_ResultType                                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_PtrRequestData, KeyM_RequestDataLength           **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvCopyParsedCVCCertificate, KeyM_PrvMemCmp,     **
**                      KeyM_PrvPerformVerifyCertPairOperation,               **
**                      KeyM_PrvMemCopy, KeyM_PrvAdjustCvcCertificate,        **
**                      KeyM_PrvCopyParsedCVCCertificate,                     **
**                      KeyM_PrvRecoverCvcCertificate                         **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_ResultType KeyM_PrvPerformUpdateRootCvcCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_DATA) ptrCertData;
  uint16 certDataLength;
  KeyM_ResultType operationResult;
  uint8 indexCnt;
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrCvcCert;
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrInterCvcCert;
  /* Internal buffers used for parsed certificate */
  KeyM_CvcCertificateType parsedCvcCert;
  KeyM_ElementType certIssuerUniqueID;
  KeyM_ElementType certSubjectUniqueID;
  KeyM_ElementType certPublicKeyAlgorithm;
  KeyM_ElementType certVersion;
  KeyM_ElementType certNotBefore;
  KeyM_ElementType certNotAfter;
  KeyM_ElementType certSignatureValue;
  KeyM_ElementType certDomainParams[KEYM_CERT_MAX_DOMAIN_PARAM_NUMBER];
  KeyM_ElementType certHolderAuthorTemplate;
  #if (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U)
    /* Internal extensions used for certificate service */
    KeyM_ElementType certExtensions[KEYM_CERT_MAX_EXTENSION_NUMBER];
  #endif /* (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U) */

  /* @Trace: KeyM_SUD_FUNC_385 */
  operationResult = KEYM_RT_KEY_CERT_UPDATE_FAIL;
  ptrCvcCert = (KeyM_CvcCertificateType*)ptrCert->PtrParsedCert;
  ptrInterCvcCert = &parsedCvcCert;

  ptrInterCvcCert->PtrRawProfileId = &certVersion;
  ptrInterCvcCert->PtrRawAuthorityRefer = &certIssuerUniqueID;
  ptrInterCvcCert->PtrRawEffectiveDate = &certNotBefore;
  ptrInterCvcCert->PtrRawExpirationDate = &certNotAfter;
  ptrInterCvcCert->PtrRawPublicKeyObjectId = &certPublicKeyAlgorithm;
  ptrInterCvcCert->PtrSignatureValue = &certSignatureValue;
  ptrInterCvcCert->PtrRawHolderRefer = &certSubjectUniqueID;
  ptrInterCvcCert->PtrRawHolderAuthorTemplate = &certHolderAuthorTemplate;
  #if (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U)
    ptrInterCvcCert->PtrExtensions = &certExtensions[0u];
    ptrInterCvcCert->ExtensionNum = ptrCvcCert->ExtensionNum;
  #endif /* (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U) */

  ptrInterCvcCert->PtrPublicKeyDomainParams = &certDomainParams[0u];
  ptrInterCvcCert->DomainParamNum = ptrCvcCert->DomainParamNum;

  KeyM_PrvCopyParsedCVCCertificate(ptrCvcCert, ptrInterCvcCert);

  /* Save the pointer of data of root certificate */
  ptrCertData = ptrCert->PtrCertData;
  certDataLength = ptrCert->CertLength;
  /* Update the pointer to new certificate data  */
  ptrCert->PtrCertData = (uint8*)KeyM_PtrRequestData;
  ptrCert->CertLength = KeyM_RequestDataLength;
  /* Set the certificate status is not parsed to allow parsing
    new root certificate */
  ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;
  /* Verify the new root certificate */
  KeyM_PrvPerformVerifyCertPairOperation(ptrCert, ptrCert);

  /* Check the new root certificate with the current root certificate:
    - The new root and current root must have the same subject name and
    the same public key */
  if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus)
  {
    /* @Trace: KeyM_SUD_FUNC_386 */
    /* Check subject name */
    if (ptrCvcCert->PtrRawHolderRefer->Element.Length == \
      ptrInterCvcCert->PtrRawHolderRefer->Element.Length)
    {
      retVal = KeyM_PrvMemCmp(\
        ptrCvcCert->PtrRawHolderRefer->Element.PtrData, \
        ptrInterCvcCert->PtrRawHolderRefer->Element.PtrData, \
        ptrInterCvcCert->PtrRawHolderRefer->Element.Length);

      if (E_OK == retVal)
      {
        /* Check public key algorithm */
        if (ptrCvcCert->PtrRawPublicKeyObjectId->Element.Length == \
          ptrInterCvcCert->PtrRawPublicKeyObjectId->Element.Length)
        {

          retVal = KeyM_PrvMemCmp(\
            ptrCvcCert->PtrRawPublicKeyObjectId->Element.PtrData, \
            ptrInterCvcCert->PtrRawPublicKeyObjectId->Element.PtrData, \
            ptrInterCvcCert->PtrRawPublicKeyObjectId->Element.Length);

          if (E_OK == retVal)
          {
            /* @Trace: KeyM_SUD_FUNC_387 */
            /* Check public key value */
            for (indexCnt = 0u; indexCnt < ptrCvcCert->DomainParamNum; indexCnt++)
            {
              retVal = KeyM_PrvMemCmp(\
                ptrCvcCert->PtrPublicKeyDomainParams[indexCnt].Element.PtrData, \
                ptrInterCvcCert->\
                  PtrPublicKeyDomainParams[indexCnt].Element.PtrData, \
                ptrCvcCert->PtrPublicKeyDomainParams[indexCnt].Element.Length);

              if (E_OK != retVal)
              {
                break;
              }
            }

            if (E_OK == retVal)
            {
              operationResult = KEYM_RT_OK;
              /* Copy new certificate data to certificate data buffer */
              (void)KeyM_PrvMemCopy(KeyM_PtrRequestData, ptrCertData,\
                KeyM_RequestDataLength);
              /* Adjust the parsed certificate */
              KeyM_PrvAdjustCvcCertificate(ptrCvcCert, KeyM_PtrRequestData, \
                ptrCertData);
            }
          } /* @if (E_OK == retVal) */
        } /* @if (ptrCvcCert->PtrRawPublicKeyObjectId->Element.Length == \
            ptrInterCvcCert->PtrRawPublicKeyObjectId->Element.Length) */
      } /* @if (E_OK == retVal) */
    } /* @if (ptrCvcCert->PtrRawHolderRefer->Element.Length == \
        ptrInterCvcCert->PtrRawHolderRefer->Element.Length) */
  } /* @if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus) */

  if (KEYM_RT_OK != operationResult)
  {
    /* @Trace: KeyM_SUD_FUNC_388 */
    /* Restore the parsed certificate */
    KeyM_PrvCopyParsedCVCCertificate(ptrInterCvcCert, ptrCvcCert);

    KeyM_PrvRecoverCvcCertificate(ptrCert);

    /* Restore the length of data of current certificate */
    ptrCert->CertLength = certDataLength;
    /* Reset the status of current certificate to be valid */
    ptrCert->CertStatus = KEYM_CERTIFICATE_VALID;
  }
  /* Restore the pointer to data buffer of current certificate */
  ptrCert->PtrCertData = ptrCertData;

  return operationResult;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPerformUpdateIntermediateCvcCertOperation     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform update CVC intermediate certificate operation **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : ptrCert                                               **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_PtrRequestData, KeyM_RequestDataLength           **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvConstructCertChain, KeyM_PrvMemCopy,          **
**                      KeyM_PrvCopyParsedCVCCertificate,                     **
**                      KeyM_PrvPerformVerifyCertOperation,                   **
**                      KeyM_PrvAdjustCvcCertificate,                         **
**                      KeyM_PrvRecoverCvcCertificate                         **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_ResultType KeyM_PrvPerformUpdateIntermediateCvcCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  P2VAR(uint8, AUTOMATIC, KEYM_DATA) ptrCertData;
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrCvcCert;
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrInterCvcCert;
  uint16 certDataLength;
  Std_ReturnType retVal;
  KeyM_ResultType operationResult;
  /* Internal buffers used for parsed certificate */
  KeyM_CvcCertificateType parsedCvcCert;
  KeyM_ElementType certIssuerUniqueID;
  KeyM_ElementType certSubjectUniqueID;
  KeyM_ElementType certPublicKeyAlgorithm;
  KeyM_ElementType certVersion;
  KeyM_ElementType certNotBefore;
  KeyM_ElementType certNotAfter;
  KeyM_ElementType certSignatureValue;
  KeyM_ElementType certDomainParams[KEYM_CERT_MAX_DOMAIN_PARAM_NUMBER];
  KeyM_ElementType certHolderAuthorTemplate;
  #if (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U)
    /* Internal extensions used for certificate service */
    KeyM_ElementType certExtensions[KEYM_CERT_MAX_EXTENSION_NUMBER];
  #endif /* (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U) */

  /* @Trace: KeyM_SUD_FUNC_391 */
  operationResult = KEYM_RT_KEY_CERT_UPDATE_FAIL;

  /* Construct the certificate chain to validate the certificate */
  retVal = KeyM_PrvConstructCertChain(ptrCert);
  if (E_OK == retVal)
  {
    ptrCvcCert = (KeyM_CvcCertificateType*)ptrCert->PtrParsedCert;
    ptrInterCvcCert = &parsedCvcCert;

    ptrInterCvcCert->PtrRawProfileId = &certVersion;
    ptrInterCvcCert->PtrRawAuthorityRefer = &certIssuerUniqueID;
    ptrInterCvcCert->PtrRawEffectiveDate = &certNotBefore;
    ptrInterCvcCert->PtrRawExpirationDate = &certNotAfter;
    ptrInterCvcCert->PtrRawPublicKeyObjectId = &certPublicKeyAlgorithm;
    ptrInterCvcCert->PtrSignatureValue = &certSignatureValue;
    ptrInterCvcCert->PtrRawHolderRefer = &certSubjectUniqueID;
    ptrInterCvcCert->PtrRawHolderAuthorTemplate = &certHolderAuthorTemplate;
    #if (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U)
      ptrInterCvcCert->PtrExtensions = &certExtensions[0u];
      ptrInterCvcCert->ExtensionNum = ptrCvcCert->ExtensionNum;
    #endif /* (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U) */

    ptrInterCvcCert->PtrPublicKeyDomainParams = &certDomainParams[0u];
    ptrInterCvcCert->DomainParamNum = ptrCvcCert->DomainParamNum;

    KeyM_PrvCopyParsedCVCCertificate(ptrCvcCert, ptrInterCvcCert);

    /* Save the pointer of data of certificate */
    ptrCertData = ptrCert->PtrCertData;
    certDataLength = ptrCert->CertLength;
    /* Update the pointer to new certificate data  */
    ptrCert->PtrCertData = (uint8*)KeyM_PtrRequestData;
    ptrCert->CertLength = KeyM_RequestDataLength;
    /* Set the certificate status is not parsed to allow parsing
      new certificate */
    ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;
    /* Verify the intermediate certificate */
    KeyM_PrvPerformVerifyCertOperation(ptrCert);

    if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus)
    {
      /* @Trace: KeyM_SUD_FUNC_392 */
      /* Copy new certificate data to certificate data buffer */
      (void)KeyM_PrvMemCopy(KeyM_PtrRequestData, ptrCertData,\
        KeyM_RequestDataLength);
      /* Adjust the parsed certificate */
      KeyM_PrvAdjustCvcCertificate(ptrCvcCert, KeyM_PtrRequestData, \
        ptrCertData);

      operationResult = KEYM_RT_OK;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_393 */
      if (KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST != ptrCert->CertStatus)
      {
        /* Restore the parsed certificate */
        KeyM_PrvCopyParsedCVCCertificate(ptrInterCvcCert, ptrCvcCert);

        KeyM_PrvRecoverCvcCertificate(ptrCert);
      }
      /* Restore the length of data of current certificate */
      ptrCert->CertLength = certDataLength;
      /* Restore the cetificate status  */
      ptrCert->CertStatus = KEYM_CERTIFICATE_VALID;
    } /* @if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus) */

    /* Restore the pointer to data buffer of current certificate */
    ptrCert->PtrCertData = ptrCertData;
  } /* @if (E_OK == retVal) */

  return operationResult;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name      : KeyM_PrvPerformSetIntermediateCertOperation           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform set intermediate certificate operation        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : ptrCert                                               **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : KeyM_ResultType                                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_PtrRequestData, KeyM_RequestDataLength           **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvConstructCertChain, KeyM_PrvMemCopy,          **
**                      KeyM_PrvPerformVerifyCertOperation                    **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_ResultType KeyM_PrvPerformSetIntermediateCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  Std_ReturnType retVal;
  KeyM_ResultType operationResult;

  operationResult = KEYM_RT_KEY_CERT_UPDATE_FAIL;

  if ((KEYM_FALSE == ptrCert->IsRoot) && \
    (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus) &&
    (KEYM_CERT_FORMAT_CRL != ptrCert->CertFormat))
  {
    /* @Trace: KeyM_SUD_FUNC_394 */
    /* Construct the certificate chain to validate the certificate */
    retVal = KeyM_PrvConstructCertChain(ptrCert);

    if (E_OK == retVal)
    {
      /* @Trace: KeyM_SUD_FUNC_395 */
      /* Copy certificate data to data slot of the certificate */
      ptrCert->CertLength = KeyM_RequestDataLength;

      (void)KeyM_PrvMemCopy(KeyM_PtrRequestData, \
        &ptrCert->PtrCertData[0u], \
        KeyM_RequestDataLength);
      /* Set the certificate status is not parsed to allow parsing
        new certificate */
      ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;
      /* Verify the intermediate certificate */
      KeyM_PrvPerformVerifyCertOperation(ptrCert);

      if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus)
      {
        /* @Trace: KeyM_SUD_FUNC_396 */
        operationResult = KEYM_RT_OK;
      }
    }
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_397 */
    operationResult = KEYM_RT_KEY_CERT_INVALID;
  }
  return operationResult;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) ||
  (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)) */

#if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvPerformUpdateCrlOperation                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform update Crl operation                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : ptrCert                                               **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : KeyM_ResultType                                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_PtrRequestData, KeyM_RequestDataLength           **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvConstructCertChain, KeyM_PrvMemCopy,          **
**                      KeyM_PrvPerformVerifyCertOperation,                   **
**                      KeyM_PrvCopyParsedCRL, KeyM_PrvAdjustX509Clr,         **
**                      KeyM_PrvRecoverX509Crl                                **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_ResultType KeyM_PrvPerformUpdateCrlOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  P2VAR(uint8, AUTOMATIC, KEYM_DATA) ptrCertData;
  P2VAR(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrCrl;
  P2VAR(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrInterCrl;
  uint16 certDataLength;
  Std_ReturnType retVal;
  KeyM_ResultType operationResult;
  /* Internal buffers used for parsed certificate */
  KeyM_X509CrlType parsedCrl;
  KeyM_ElementType certVersion;
  KeyM_ElementType certNotBefore;
  KeyM_ElementType certNotAfter;
  KeyM_ElementType certSignatureValue;
  KeyM_ElementType certIssuer[KEYM_CERT_MAX_NAME_NUMBER];
  KeyM_ElementType certSignature;
  KeyM_ElementType certSignatureAlgorithm;
  KeyM_X509CrlEntryType crlEntry[KEYM_CERT_MAX_REVOK_ENTRY];
  #if (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U)
    /* Internal extensions used for certificate service */
    KeyM_ElementType certExtensions[KEYM_CERT_MAX_EXTENSION_NUMBER];
  #endif /* (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U) */

  operationResult = KEYM_RT_KEY_CERT_UPDATE_FAIL;

  if (KEYM_CERT_FORMAT_CRL == ptrCert->CertFormat)
  {
    /* @Trace: KeyM_SUD_FUNC_399 */
    /* Construct the certificate chain to validate the certificate */
    retVal = KeyM_PrvConstructCertChain(ptrCert);

    if (E_OK == retVal)
    {
      if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus)
      {
        /* @Trace: KeyM_SUD_FUNC_400 */
        /* Copy certificate data to data slot of the certificate */
        ptrCert->CertLength = KeyM_RequestDataLength;

        (void)KeyM_PrvMemCopy(KeyM_PtrRequestData, &ptrCert->PtrCertData[0u], \
          KeyM_RequestDataLength);
        /* Set the certificate status is not parsed to allow parsing
           new certificate */
        ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;
        /* Verify the intermediate certificate */
        KeyM_PrvPerformVerifyCertOperation(ptrCert);

        if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus)
        {
          operationResult = KEYM_RT_OK;
        }
      }
      else if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus)
      {
        /* @Trace: KeyM_SUD_FUNC_402 */
        ptrCrl = (KeyM_X509CrlType*)ptrCert->PtrParsedCert;
        ptrInterCrl = &parsedCrl;

        ptrInterCrl->PtrRawSignature = &certSignature;
        ptrInterCrl->PtrRawThisUpdate = &certNotBefore;
        ptrInterCrl->PtrRawNextUpdate = &certNotAfter;
        ptrInterCrl->PtrSignatureAlgorithm = &certSignatureAlgorithm;
        ptrInterCrl->PtrSignatureValue = &certSignatureValue;
        ptrInterCrl->PtrIssuer = &certIssuer[0u];
        ptrInterCrl->IssuerNum = ptrCrl->IssuerNum;

        #if (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U)
          ptrInterCrl->PtrExtensions = &certExtensions[0u];
          ptrInterCrl->ExtensionNum = ptrCrl->ExtensionNum;
        #endif /* (KEYM_CERT_MAX_EXTENSION_NUMBER > 0U) */

        if (NULL_PTR == ptrCrl->PtrRawVersion)
        {
          ptrInterCrl->PtrRawVersion = NULL_PTR;
        }
        else
        {
          ptrInterCrl->PtrRawVersion = &certVersion;
        }

        ptrInterCrl->PtrEntryList = &crlEntry[0u];
        ptrInterCrl->EntryNum = ptrCrl->EntryNum;

        /* Save the parsed crl */
        KeyM_PrvCopyParsedCRL(ptrCrl, ptrInterCrl);
        /* Save the pointer of data of certificate */
        ptrCertData = ptrCert->PtrCertData;
        certDataLength = ptrCert->CertLength;
        /* Update the pointer to new certificate data  */
        ptrCert->PtrCertData = (uint8*)KeyM_PtrRequestData;
        ptrCert->CertLength = KeyM_RequestDataLength;
        /* Set the certificate status is not parsed to allow parsing
           new certificate */
        ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;
        /* Verify the intermediate certificate */
        KeyM_PrvPerformVerifyCertOperation(ptrCert);

        if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus)
        {
          /* @Trace: KeyM_SUD_FUNC_403 */
          /* Copy new certificate data to certificate data buffer */
          (void)KeyM_PrvMemCopy(KeyM_PtrRequestData, ptrCertData, \
            KeyM_RequestDataLength);
          /* Adjust the parsed Crl */
          KeyM_PrvAdjustX509Clr(ptrCrl, KeyM_PtrRequestData, ptrCertData);

          operationResult = KEYM_RT_OK;
        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_404 */
          if (KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST != ptrCert->CertStatus)
          {
            /* Restore the parsed crl */
            KeyM_PrvCopyParsedCRL(ptrInterCrl, ptrCrl);

            KeyM_PrvRecoverX509Crl(ptrCert);
          }
          /* Restore the length of data of current certificate */
          ptrCert->CertLength = certDataLength;
          /* Reset the status of current certificate to be NOT PARSE, \
            it allows the current certificate re-parsing */
          ptrCert->CertStatus = KEYM_CERTIFICATE_VALID;
        } /* @if (KEYM_CERTIFICATE_VALID == ptrCert->CertStatus) */

        /* Restore the pointer to data buffer of current certificate */
        ptrCert->PtrCertData = ptrCertData;
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_401 */
        operationResult = KEYM_RT_KEY_CERT_INVALID;
      } /* @if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus) */

    } /* @if (E_OK == retVal) */
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_398 */
    operationResult = KEYM_RT_KEY_CERT_INVALID;
  } /* @if (KEYM_CERT_FORMAT_CRL != ptrCert->CertFormat) */

  return operationResult;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */

#if ((KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) && \
    (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON) && \
    ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
    (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)))

/*******************************************************************************
** Function Name      : KeyM_PrvEccKeyPairGenerate                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Generate ECC key pair                                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrCert                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Csm_KeyElementSet, Csm_KeyGenerate, Csm_KeySetValid,  **
**                      Csm_KeyElementCopy                                    **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvEccKeyPairGenerate(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  Std_ReturnType retVal;
  uint32 csmSignGenerateKeyId;
  uint32 csmSignVerifyKeyId;
  uint8 algorithm;

  /* @Trace: KeyM_SUD_FUNC_405 */
  csmSignGenerateKeyId = ptrCert->PtrCertPrvKeyStorageKey->CsmTargetKeyId;
  csmSignVerifyKeyId = ptrCert->CsmSignVerifyKeyId;

  algorithm = CRYPTO_ALGOFAM_RNG;
  /* Set algorithm to random number generation */
  retVal = Csm_KeyElementSet(csmSignGenerateKeyId, KEYM_KEY_ELEMENT17_ID, \
    &algorithm, 1u);
  if (E_OK == retVal)
  {
    /* Generate private key as random number */
    retVal = Csm_KeyGenerate(csmSignGenerateKeyId);
    if (E_OK == retVal)
    {
      /* @Trace: KeyM_SUD_FUNC_406 */
      /* Valid the private key */
      retVal = Csm_KeySetValid(csmSignGenerateKeyId);
      if (E_OK == retVal)
      {
        /* Copy ECC private key to key element of CRYPTO_KE_KEYGENERATE_SEED of
          verify key */
        retVal = Csm_KeyElementCopy(csmSignGenerateKeyId, \
          KEYM_KEY_ELEMENT1_ID, csmSignVerifyKeyId, KEYM_KEY_ELEMENT16_ID);
        if (E_OK == retVal)
        {
          /* @Trace: KeyM_SUD_FUNC_407 */
          algorithm = CRYPTO_ALGOFAM_ECCNIST;
          /* Set algorithm to ECC key generation */
          retVal = Csm_KeyElementSet(csmSignVerifyKeyId, \
            KEYM_KEY_ELEMENT17_ID, &algorithm, 1u);
          if (E_OK == retVal)
          {
            /* Generate ECC public key */
            retVal = Csm_KeyGenerate(csmSignVerifyKeyId);
            if (E_OK == retVal)
            {
              /* Valid the public key */
              retVal = Csm_KeySetValid(csmSignVerifyKeyId);
            }
          }
        }
      } /* @if (KEYM_E_OK == retVal) */
    } /* @if (KEYM_E_OK == retVal) */
  } /* @if (KEYM_E_OK == retVal) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#if (KEYM_CERT_RSA_KEY_GENERATE_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvRsaKeyPairGenerate                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Generate RSA key pair                                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrCert                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Csm_KeyElementSet, Csm_KeyGenerate, Csm_KeySetValid,  **
**                      Csm_KeyElementGet, KeyM_Asn1GetTag,                   **
**                      KeyM_PrvConvertRsaPublicKeyFormat                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvRsaKeyPairGenerate(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  uint16 length;
  uint32 csmSignGenerateKeyId;
  uint32 csmSignVerifyKeyId;
  uint8 algorithm;
  uint8 publicKeyData[KEYM_PUBLIC_KEY_VALUE_MAX_LENGTH];
  uint8 privateKeyData[KEYM_PRIVATE_KEY_VALUE_MAX_LENGTH];
  uint32 keyLength;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrModulus;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExponent;
  uint16 modulusLen;
  uint16 exponentLen;

  /* @Trace: KeyM_SUD_FUNC_411 */
  publicKeyData[0u] = 0u;
  privateKeyData[0u] = 0u;
  csmSignGenerateKeyId = ptrCert->PtrCertPrvKeyStorageKey->CsmTargetKeyId;
  csmSignVerifyKeyId = ptrCert->CsmSignVerifyKeyId;
  keyLength = KEYM_PRIVATE_KEY_VALUE_MAX_LENGTH;

  /* Set algorithm to RSA key generation */
  algorithm = CRYPTO_ALGOFAM_RSA;
  retVal = Csm_KeyElementSet(csmSignGenerateKeyId, KEYM_KEY_ELEMENT17_ID, \
    &algorithm, 1u);
  if (E_OK == retVal)
  {
    /* Generate RSA key pair */
    retVal = Csm_KeyGenerate(csmSignGenerateKeyId);

    if (E_OK == retVal)
    {
      /* @Trace: KeyM_SUD_FUNC_412 */
      /* Valid the private key */
      retVal = Csm_KeySetValid(csmSignGenerateKeyId);

      if (E_OK == retVal)
      {
        retVal = Csm_KeyElementGet(csmSignGenerateKeyId, KEYM_KEY_ELEMENT1_ID, \
          &privateKeyData[0u], &keyLength);

        if (E_OK == retVal)
        {
          /* @Trace: KeyM_SUD_FUNC_413 */
          /*
           * Because format of generated key is
           *   CRYPTO_KE_FORMAT_BIN_RSA_PRIVATEKEY:
           *
           *   RSAPrivateKey ::= SEQUENCE {
           *   version Version, \
           *   modulus INTEGER, -- n
           *   publicExponent INTEGER, -- e
           *   privateExponent INTEGER, -- d
           *   prime1 INTEGER, -- p
           *   prime2 INTEGER, -- q
           *   exponent1 INTEGER, -- d mod (p-1)
           *   exponent2 INTEGER, -- d mod (q-1)
           *   coefficient INTEGER -- (inverse of q) mod p }
           *
           * So we need to parse this key to get public key that has
           * CRYPTO_KE_FORMAT_BIN_RSA_PUBLICKEY format:
           *
           *   RSAPublicKey ::= SEQUENCE {
           *   modulus INTEGER, -- n
           *   publicExponent INTEGER, -- e}
           */

          ptrPosition = &privateKeyData[0u];
          ptrEnd = &ptrPosition[keyLength];
          length = 0u;

          retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, \
            KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

          if (E_OK == retVal)
          {
            /* Get version */
            retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, \
              &length, KEYM_ASN1_INTEGER);

            if (E_OK == retVal)
            {
              /* @Trace: KeyM_SUD_FUNC_414 */
              /* Go to modulus */
              ptrPosition = &ptrPosition[length];
              /* Get modulus */
              retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, \
                &length, KEYM_ASN1_INTEGER);

              if (E_OK == retVal)
              {
                ptrModulus = ptrPosition;
                modulusLen = length;
                /* Go to publicExponent */
                ptrPosition = &ptrPosition[length];
                /* Get publicExponent */
                retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, \
                  &length, KEYM_ASN1_INTEGER);

                if (E_OK == retVal)
                {
                  /* @Trace: KeyM_SUD_FUNC_415 */
                  ptrExponent = ptrPosition;
                  exponentLen = length;
                  /* Convert public key to
                    CRYPTO_KE_FORMAT_BIN_RSA_PUBLICKEY format */
                  length = KEYM_PUBLIC_KEY_VALUE_MAX_LENGTH;
                  ptrPosition = &publicKeyData[0u];
                  retVal = KeyM_PrvConvertRsaPublicKeyFormat(ptrModulus, \
                    modulusLen, ptrExponent, exponentLen,\
                    &ptrPosition, &length);

                  if (E_OK == retVal)
                  {
                    retVal = Csm_KeyElementSet(csmSignVerifyKeyId, \
                      KEYM_KEY_ELEMENT1_ID, ptrPosition, length);

                    if (E_OK == retVal)
                    {
                      /* Valid the public key */
                      retVal = Csm_KeySetValid(csmSignVerifyKeyId);
                    }
                  }
                } /* @if (KEYM_E_OK == retVal) */
              } /* @if (KEYM_E_OK == retVal) */
            } /* @if (KEYM_E_OK == retVal) */
          } /* @if (KEYM_E_OK == retVal) */
        } /* @if (KEYM_E_OK == retVal) */
      } /* @if (KEYM_E_OK == retVal) */
    } /* @if (KEYM_E_OK == retVal) */
  } /* @if (KEYM_E_OK == retVal) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CERT_RSA_KEY_GENERATE_ENABLED == STD_ON) */
#endif /* #if ((KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON)
  && (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON) && \
  ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
  (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON))) */

/*******************************************************************************
** Function Name      : KeyM_PrvPerformRequestCsrOperation                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform certificate signing request generating        **
**                      operation                                             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : ptrCert                                               **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : KeyM_ResultType                                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_DataBuffer, KeyM_PtrResultData,                  **
**                      KeyM_ResultDataMaxLength                              **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvEccKeyPairGenerate,KeyM_PrvRsaKeyPairGenerate,**
**                      KeyM_PrvX509CertificateGenerate,                      **
**                      KeyM_PrvCvcCertificateGenerate,                       **
**                      KeyM_PrvMemClear, KeyM_PrvX509CrlGenerate             **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_ResultType KeyM_PrvPerformRequestCsrOperation(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_CONST) ptrCert)
{
  KeyM_ResultType operationResult;

  /* @Trace: KeyM_SUD_FUNC_421 */
  #if (((KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) && \
    (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON) && \
    ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
    (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON))) || \
    (KEYM_CERT_X509_CRL_ENABLED == STD_ON))
  Std_ReturnType retVal;
  retVal = E_NOT_OK;
  #endif
  operationResult = KEYM_RT_NOT_OK;

  #if ((KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) && \
    (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON) && \
    ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
    (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)))
  if (KEYM_CERT_FORMAT_CRL != ptrCert->CertFormat)
  {
    /* @Trace: KeyM_SUD_FUNC_422 */
    if (NULL_PTR != ptrCert->PtrCertPrvKeyStorageKey)
    {
      /* Generate key pair */
      if (KEYM_CERT_ALGORITHM_ECC == ptrCert->CertAlgorithm)
      {
        retVal = KeyM_PrvEccKeyPairGenerate(ptrCert);
      }
      else
      {
        #if (KEYM_CERT_RSA_KEY_GENERATE_ENABLED == STD_ON)
          retVal = KeyM_PrvRsaKeyPairGenerate(ptrCert);
        #endif
      }

      if (E_OK == retVal)
      {
        /* Clear internal buffer */
        KeyM_PrvMemClear(&KeyM_DataBuffer[0u], KEYM_INTERAL_BUFFER_LENGTH);

        #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
        if (KEYM_CERT_FORMAT_X509 == ptrCert->CertFormat)
        {
          /* @Trace: KeyM_SUD_FUNC_423 */
          retVal = KeyM_PrvX509CertificateGenerate(ptrCert, \
            KeyM_PtrResultData, &KeyM_ResultDataMaxLength);
        }
        else
        #endif /* #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
        {
          #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
            /* @Trace: KeyM_SUD_FUNC_424 */
            retVal = KeyM_PrvCvcCertificateGenerate(ptrCert, \
              KeyM_PtrResultData, \
              &KeyM_ResultDataMaxLength);
          #endif /* #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */
        }
      } /* @if (KEYM_E_OK == retVal) */
    } /* @if (NULL_PTR != ptrCert->PtrCertPrvKeyStorageKey) */
  } /* @if (KEYM_CERT_FORMAT_CRL != ptrCert->CertFormat) */
  else
  #endif /* #if ((KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) && \
    (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON) && \
    ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
    (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON))) */
  {
    #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
      /* @Trace: KeyM_SUD_FUNC_425 */
      /* Clear result buffer */
      KeyM_PrvMemClear(&KeyM_PtrResultData[0u], KeyM_ResultDataMaxLength);

      retVal = KeyM_PrvX509CrlGenerate(ptrCert, KeyM_PtrResultData, \
        &KeyM_ResultDataMaxLength);
    #endif /* #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
  }

  #if (((KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) && \
    (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON) && \
    ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
    (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON))) || \
    (KEYM_CERT_X509_CRL_ENABLED == STD_ON))
  /* @Trace: KeyM_SUD_FUNC_426 */
  if (E_OK == retVal)
  {
    operationResult = KEYM_RT_OK;
  }
  else
  {
    if (KEYM_E_ASN1_BUF_TOO_SMALL == retVal)
    {
      #if (KEYM_DEV_ERROR_DETECT == STD_ON)
        /* Report error to Det in case buffer length is small */
        KEYM_REPORT_ERROR(KEYM_SERVICECERTIFICATE_SID, KEYM_E_SMALL_BUFFER);
      #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
    }
  }
  #endif /* #if (((KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) && \
    (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON) && \
    ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
    (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON))) || \
    (KEYM_CERT_X509_CRL_ENABLED == STD_ON)) */

  (void)ptrCert;
  return operationResult;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPerformUpdateSignCsrOperation                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform certificate signing request generating        **
**                      operation                                             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : ptrCert                                               **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : KeyM_ResultType                                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvPerformSetIntermediateCertOperation,          **
**                      KeyM_PrvPerformUpdateIntermediateCertOperation,       **
**                      KeyM_PrvPerformUpdateCrlOperation,                    **
**                      KeyM_PrvPerformSetRootCertOperation                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_ResultType KeyM_PrvPerformUpdateSignCsrOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  KeyM_ResultType operationResult;

  /* @Trace: KeyM_SUD_FUNC_429 */
  #if (KEYM_CERT_X509_CRL_ENABLED == STD_OFF)
    operationResult = KEYM_RT_KEY_CERT_INVALID;
  #endif

  if (KEYM_FALSE == ptrCert->IsRoot)
  {
    #if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
      (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON))
    if (KEYM_CERT_FORMAT_CRL != ptrCert->CertFormat)
    {
      if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus)
      {
        /* @Trace: KeyM_SUD_FUNC_430 */
        operationResult = KeyM_PrvPerformSetIntermediateCertOperation(ptrCert);
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_431 */
        operationResult = KeyM_PrvPerformUpdateIntermediateCertOperation(\
          ptrCert);
      }
    }
    else
    #endif
    {
      #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_432 */
        operationResult = KeyM_PrvPerformUpdateCrlOperation(ptrCert);
      #endif
    }
  }
  else
  {
    #if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
      (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON))
      /* @Trace: KeyM_SUD_FUNC_433 */
      /* For root certificate, update operation must be done by
        PerformUpdateRootCertOperation*/
      operationResult = KeyM_PrvPerformSetRootCertOperation(ptrCert);
    #endif
  }

  return operationResult;

}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPerformServiceCertificateOperation            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Perform ServiceCertificate operation                  **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_CertId, KeyM_CryptoCert, KeyM_JobState,          **
**                      KeyM_OperationResult                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvPerformRequestCsrOperation,                   **
**                      KeyM_PrvPerformUpdateSignCsrOperation,                **
**                      KeyM_PrvPerformUpdateRootCertOperation,               **
**                      KeyM_PrvPerformSetRootCertOperation,                  **
**                      KeyM_PrvPerformSetIntermediateCertOperation ,         **
**                      KeyM_PrvPerformUpdateIntermediateCertOperation,       **
**                      KeyM_PrvPerformUpdateCrlOperation,                    **
**                      Csm_KeyElementSet, Csm_KeySetValid, NvM_WriteBlock    **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvPerformServiceCertificateOperation(void)
{
  Std_ReturnType retVal;
  KeyM_ResultType operationResult;
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  KeyM_KeyCertStorageType certStorageType;
  KeyM_JobStateType jobState = KEYM_COMPLETE;
  /* @Trace: KeyM_SUD_FUNC_281 */
  operationResult = KEYM_RT_NOT_OK;
  if (KEYM_TOTAL_CERTIFICATE > KeyM_CertId)
  {
    /* Get the pointer the certificate */
    ptrCert = &KeyM_CryptoCert[KeyM_CertId];

    switch (KeyM_CertService)
    {
      case KEYM_SERVICE_CERT_REQUEST_CSR:
        /* @Trace: KeyM_SUD_FUNC_282 */
        operationResult = KeyM_PrvPerformRequestCsrOperation(ptrCert);
        break;
      case KEYM_SERVICE_CERT_UPDATE_SIGNED_CSR:
        /* @Trace: KeyM_SUD_FUNC_283 */
        operationResult = KeyM_PrvPerformUpdateSignCsrOperation(ptrCert);
        break;
      #if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
           (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON))
      case KEYM_SERVICE_CERT_SET_ROOT:
        /* @Trace: KeyM_SUD_FUNC_284 */
        operationResult = KeyM_PrvPerformSetRootCertOperation(ptrCert);
        break;
      case KEYM_SERVICE_CERT_UPDATE_ROOT:
        /* @Trace: KeyM_SUD_FUNC_285 */
        operationResult = KeyM_PrvPerformUpdateRootCertOperation(ptrCert);
        break;
      case KEYM_SERVICE_CERT_SET_INTERMEDIATE:
        /* @Trace: KeyM_SUD_FUNC_286 */
        operationResult = KeyM_PrvPerformSetIntermediateCertOperation(ptrCert);
        break;
      case KEYM_SERVICE_CERT_UPDATE_INTERMEDIATE:
        /* @Trace: KeyM_SUD_FUNC_287 */
        operationResult = KeyM_PrvPerformUpdateIntermediateCertOperation(\
          ptrCert);
        break;
      #endif /* ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
        (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)) */
      #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
      case KEYM_SERVICE_CERT_UPDATE_CRL:
        /* @Trace: KeyM_SUD_FUNC_288 */
        operationResult = KeyM_PrvPerformUpdateCrlOperation(ptrCert);
        break;
      #endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
      default:
        /* Do nothing */
        break;
    }

    if ((KEYM_RT_OK == operationResult) && \
      (KEYM_SERVICE_CERT_REQUEST_CSR != KeyM_CertService))
    {
      certStorageType = ptrCert->CertStorageType;

      if (KEYM_STORAGE_IN_CSM == certStorageType)
      {
        /* @Trace: KeyM_SUD_FUNC_290 */
        /* Store the certificate data to CSM */
        retVal = Csm_KeyElementSet(ptrCert->CsmTargetKeyId, \
          KEYM_KEY_ELEMENT1_ID, \
          ptrCert->PtrCertData, \
          ptrCert->CertLength);

        if (E_OK == retVal)
        {
          retVal = Csm_KeySetValid(ptrCert->CsmTargetKeyId);
        }

        if (E_OK == retVal)
        {
          operationResult = KEYM_RT_OK;
        }
        else
        {
          operationResult = KEYM_RT_KEY_CERT_WRITE_FAIL;
        } /* @if (E_OK == retVal) */

        /* At here the ServiceCertificate operation is completed, \
           so update the job state to complete */
        jobState = KEYM_COMPLETE;
      }
      #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
      else if (KEYM_STORAGE_IN_NVM == certStorageType)
      {
        /* @Trace: KeyM_SUD_FUNC_292 */
        /* The third byte from the last is upper byte of cert data length */
        ptrCert->PtrCertData[ptrCert->CertMaxLength - 3u] = \
          (uint8)((ptrCert->CertLength & KEYM_UPPER_BYTE_MASK) >> \
          KEYM_UPPER_BYTE_SHIFT);
        /* The second byte from the last is lower byte of cert data length */
        ptrCert->PtrCertData[ptrCert->CertMaxLength - 2u] = \
          (uint8)(ptrCert->CertLength & KEYM_LOWER_BYTE_MASK);
        /* The last byte is state byte of 1 */
        ptrCert->PtrCertData[ptrCert->CertMaxLength - 1u] = KEYM_ONE;
        /* Write cert data to NvM */
        retVal = NvM_WriteBlock(ptrCert->NvmBlockId, &ptrCert->PtrCertData[0u]);
        if (E_OK != retVal)
        {
          operationResult = KEYM_RT_KEY_CERT_WRITE_FAIL;
          /* Because NvM write request is not accepted, the ServiceCertificate
            operation is fail, so update the job state to Complete */
          jobState = KEYM_COMPLETE;
        }
        else
        {
          operationResult = KEYM_RT_OK;
          /* At here the ServiceCertificate operation is waiting for
            NvM write request completed,
            so update the job state to in-progress */
          jobState = KEYM_IN_PROGRESS;
        }
      }
      #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */
      else /* for KEYM_STORAGE_IN_RAM == certStorageType*/
      {
        /* @Trace: KeyM_SUD_FUNC_291 */
        /* Update job state to complete */
        jobState = KEYM_COMPLETE;
      } /* @if (KEYM_STORAGE_IN_CSM == certStorageType)*/

    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_289 */
      /* The ServiceCertificate operation is fail,
        so update the job state to Complete */
      jobState = KEYM_COMPLETE;
    } /* @if (KEYM_RT_OK == operationResult) */
  }
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  KeyM_JobState = jobState;
  KeyM_OperationResult = operationResult;
  SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF) */

/*******************************************************************************
** Function Name      : KeyM_PrvProcessServiceCertificateOperation            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Process ServiceCertificate operations                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_BackGroundDone, KeyM_JobState, KeyM_CertId,      **
**                      KeyM_CryptoCert, KeyM_OperationResult,                **
**                      KeyM_ResultDataMaxLength, KeyM_PtrResultData,         **
**                      KeyM_CurrentJob, KeyM_ModuleState                     **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      NvM_GetErrorStatus                                    **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvProcessServiceCertificateOperation(void)
{
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  #if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
  #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
    NvM_RequestResultType nvMRequestResult;
    nvMRequestResult = NVM_REQ_OK;
  #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */
  #endif /* KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF */
  boolean backGroundDone;
  KeyM_JobStateType jobState;
  /* @Trace: KeyM_SUD_FUNC_293 */
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  backGroundDone = KeyM_BackGroundDone;
  SchM_Exit_KeyM_GLOBALVAR_PROTECTION();  
  if ((KEYM_TRUE == backGroundDone) && \
    (KEYM_TOTAL_CERTIFICATE > KeyM_CertId))
  {
    /* Get the pointer the certificate */
    ptrCert = &KeyM_CryptoCert[KeyM_CertId];
    #if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
      SchM_Enter_KeyM_GLOBALVAR_PROTECTION();  
      jobState = KeyM_JobState;
      SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
      if (KEYM_IN_PROGRESS == jobState)
      {
        /* @Trace: KeyM_SUD_FUNC_294 */
        /* If the job state is in-progress, it means that the job is waiting for
          NvM write request completed */
        #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
          if (KEYM_STORAGE_IN_NVM == ptrCert->CertStorageType)
          {
            /* Get the NvM block status to check
              if the write request has finished */
            (void)NvM_GetErrorStatus(ptrCert->NvmBlockId, &nvMRequestResult);

            /* Check the NvM request is completed */
            if (NVM_REQ_PENDING != nvMRequestResult)
            {
              SchM_Enter_KeyM_GLOBALVAR_PROTECTION();              
              if (NVM_REQ_OK == nvMRequestResult)
              {
                /* The NvM request result is OK */
                KeyM_OperationResult = KEYM_RT_OK;
              }
              else
              {
                /* The NvM request result is NOT OK */
                KeyM_OperationResult = KEYM_RT_KEY_CERT_WRITE_FAIL;
              }
              /* After NvM request has finished, the job is completed */
              KeyM_JobState = KEYM_COMPLETE;
              SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
            }
          }
        #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */
      } /* @if (KEYM_IN_PROGRESS == KeyM_JobState) */
    #endif /* KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF */
    SchM_Enter_KeyM_GLOBALVAR_PROTECTION();  
    jobState = KeyM_JobState;
    SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
    if (KEYM_COMPLETE == jobState)
    {
      /* @Trace: KeyM_SUD_FUNC_295 */
      if (NULL_PTR != ptrCert->RteCertServiceCallback)
      {
        SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
        /* Call the Rte callback with respond data */
        (void)((ptrCert->RteCertServiceCallback)(KeyM_OperationResult, \
          KeyM_ResultDataMaxLength, \
          KeyM_PtrResultData));
        SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
      }
      #if (KEYM_CERT_SERVICE_APPLICATION_CALLBACK_ENABLE == STD_ON)
      else if (NULL_PTR != ptrCert->CertServiceCallback)
      {
        /* Call the application callback with respond data */
        (ptrCert->CertServiceCallback)(KeyM_CertId, KeyM_OperationResult, \
          KeyM_ResultDataMaxLength, \
          KeyM_PtrResultData);
      }
      #endif
      else
      {
        /* Do nothing */
      }
      SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
      /* Set current job to be no job */
      KeyM_CurrentJob = KEYM_NO_JOB;
      /* Set module state to be idle */
      KeyM_ModuleState = KEYM_IDLE;
      /* The progress is finished */
      ptrCert->InProgress = KEYM_ZERO;
      /* Set back ground state to be idle */
      KeyM_BackGroundDone = KEYM_FALSE;
      SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
    } /* @if (KEYM_COMPLETE == KeyM_JobState) */
  } /* @if (KEYM_TRUE == KeyM_BackGroundDone) */
  KEYM_UNUSED(backGroundDone);
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */


/*******************************************************************************
** Function Name      : KeyM_PrvParseCertificate                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse information of certificate                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrData, dataLength                                   **
**                                                                            **
** InOut Parameters   : ptrCert                                               **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvX509CertificateParseDer,                      **
**                      KeyM_PrvX509CrlParseDer,                              **
**                      KeyM_PrvCvcCertificateParseDer                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvParseCertificate(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  const uint16 dataLength)
{
  uint16 indexCnt;
  uint16 retVal;

  retVal = E_NOT_OK;
  /* @Trace: KeyM_SUD_FUNC_261 */
  /* Initialize certificate elements */
  if (NULL_PTR != ptrCert->PtrCertElement)
  {
    for (indexCnt = 0u; indexCnt < ptrCert->NumberOfCertElement; indexCnt++)
    {
      ptrCert->PtrCertElement[indexCnt].PtrElement = NULL_PTR;
    }
  }

  switch (ptrCert->CertFormat)
  {
    #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
    case KEYM_CERT_FORMAT_X509:
      retVal = KeyM_PrvX509CertificateParseDer(ptrCert, ptrData, dataLength);
    break;
    #endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
    #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
    case KEYM_CERT_FORMAT_CRL:
      retVal = KeyM_PrvX509CrlParseDer(ptrCert, ptrData, dataLength);
    break;
    #endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
    #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
    case KEYM_CERT_FORMAT_CVC:
      retVal = KeyM_PrvCvcCertificateParseDer(ptrCert, ptrData, dataLength);
    break;
    #endif /* (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */
    default:
    /* Shall not enter here */
    break;
  }

  /* Update certificate status after parsing */
  if (0U != (retVal & KEYM_LOWER_BYTE_MASK))
  {
    /* @Trace: KeyM_SUD_FUNC_262 */
    ptrCert->CertStatus = KEYM_E_CERTIFICATE_INVALID_FORMAT;
  }
  else if (0U != (retVal & KEYM_UPPER_BYTE_MASK))
  {
    /* @Trace: KeyM_SUD_FUNC_263 */
    ptrCert->CertStatus = KEYM_E_CERTIFICATE_INVALID_TYPE;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_264 */
    ptrCert->CertStatus = KEYM_CERTIFICATE_PARSED_NOT_VALIDATED;
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name      : KeyM_PrvConstructCertChain                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Construct certificate chain                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCert                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_CertChain, KeyM_CryptoCert, KeyM_CertChainLength **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvConstructCertChain(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCurrentCert;
  uint8 length;
  uint16 currentCertId;
  Std_ReturnType retVal;
  boolean buildFinished;

  /* @Trace: KeyM_SUD_FUNC_268 */
  retVal = E_OK;
  currentCertId = ptrCert->CertId;
  buildFinished = KEYM_FALSE;
  /* Get the pointer to the certificates */
  ptrCurrentCert = ptrCert;
  length = 0u;
  /* Save the first cert id to the chain */
  KeyM_CertChain[length] = currentCertId;

  while (KEYM_FALSE == buildFinished)
  {
    if (KEYM_TRUE != ptrCurrentCert->IsRoot)
    {
      currentCertId = ptrCurrentCert->UpperHierarchicalCert;

      if (KEYM_TOTAL_CERTIFICATE <= currentCertId)
      {
        /* @Trace: KeyM_SUD_FUNC_270 */
        /* The upper certificate id is out of range */
        retVal = E_NOT_OK;
        /* Finish chain building */
        buildFinished = KEYM_TRUE;
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_271 */
        ptrCurrentCert = &KeyM_CryptoCert[currentCertId];

        if ((KEYM_CERTIFICATE_NOT_PARSED != ptrCurrentCert->CertStatus) && \
          (KEYM_CERTIFICATE_PARSED_NOT_VALIDATED != \
            ptrCurrentCert->CertStatus) && \
          (KEYM_CERTIFICATE_VALID != ptrCurrentCert->CertStatus))
        {
          /* Finish chain building */
          buildFinished = KEYM_TRUE;
          if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCurrentCert->CertStatus)
          {
            retVal = KEYM_E_KEY_CERT_EMPTY;
          }
          else
          {
            retVal = KEYM_E_CERT_INVALID_CHAIN_OF_TRUST;
          }
        }
        else
        {
          /* Increment length */
          length++;
          if (KEYM_CERTIFICATE_CHAIN_MAX_DEPTH <= length)
          {
            /* The certificate chain length exceeds
              the maximum length of chain */
            retVal = E_NOT_OK;
            /* Finish chain building */
            buildFinished = KEYM_TRUE;
          }
          else
          {
            /* Save the upper cert id to the chain */
            KeyM_CertChain[length] = currentCertId;
          }
        } /* @if ((ptrCurrentCert->CertStatus !=
            KEYM_CERTIFICATE_NOT_PARSED) && \
            (ptrCurrentCert->CertStatus !=
            KEYM_CERTIFICATE_PARSED_NOT_VALIDATED) &&\
            (ptrCurrentCert->CertStatus != KEYM_CERTIFICATE_VALID)) */
      } /* @if (currentCertId >= KEYM_TOTAL_CERTIFICATE) */
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_269 */
      /* Increment length */
      length++;
      /* Finish chain building */
      buildFinished = KEYM_TRUE;
    } /* @if (KEYM_TRUE != ptrCurrentCert->IsRoot) */
  } /* @while (KEYM_FALSE == buildFinished) */

  if (E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_272 */
    KeyM_CertChainLength = length;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if ((KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON) && \
  ((KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) || \
  (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON)))
/*******************************************************************************
** Function Name      : KeyM_PrvConvertArrayToInteger                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Convert an octet array to uint64 number               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrArray, length                                      **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : uint64                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint64 KeyM_PrvConvertArrayToInteger(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrArray, \
  const uint32 length)
{
  uint32 indexCnt;
  uint64 resultInteger;

  /* @Trace: KeyM_SUD_FUNC_311 */
  resultInteger = 0u;

  if (NULL_PTR != ptrArray)
  {
	  for (indexCnt = 0u; indexCnt < length; indexCnt++)
    {
      resultInteger = (resultInteger << 8u);
      resultInteger |= ptrArray[indexCnt];
    }
  }

  return resultInteger;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if ((KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON) && \
  ((KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) || \
  (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON))) */

/*******************************************************************************
** Function Name      : KeyM_PrvElementGetByIndex                             **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get certificate element data by index                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrCert, ptrCertElement, indexCnt,                    **
**                                                                            **
** InOut Parameters   : ptrCertElementDataLen                                 **
**                                                                            **
** Output Parameters  : ptrCertElementData                                    **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvX509ElementGetByIndex,                        **
**                      KeyM_PrvCvcElementGetByIndex                          **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvElementGetByIndex(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  VAR(uint32, AUTOMATIC) indexCnt, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen)
{
  Std_ReturnType retVal;

  retVal = E_OK;
  /* @Trace: KeyM_SUD_FUNC_221 */
  switch (ptrCert->CertFormat)
  {
    #if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
      (KEYM_CERT_X509_CRL_ENABLED == STD_ON))
    case KEYM_CERT_FORMAT_X509:
    case KEYM_CERT_FORMAT_CRL:
      retVal = KeyM_PrvX509ElementGetByIndex(ptrCert, ptrCertElement, indexCnt,\
        ptrCertElementData, ptrCertElementDataLen);
      break;
    #endif /* ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) ||
      (KEYM_CERT_X509_CRL_ENABLED == STD_ON)) */

    #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
    case KEYM_CERT_FORMAT_CVC:
      retVal = KeyM_PrvCvcElementGetByIndex(ptrCertElement, indexCnt,\
        ptrCertElementData, ptrCertElementDataLen);
      break;
    #endif /* (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */
    default:
      /* Should not enter here */
      break;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON)

#if ((KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) || \
  (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON))
/*******************************************************************************
** Function Name      : KeyM_PrvPartOfElementEqualCompare                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvElementEqualCompare         **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvElementEqualCompare                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrElementCondtion, ptrCert                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvMemCmp, KeyM_PrvConvertArrayToInteger         **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvPartOfElementEqualCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion)
{
  Std_ReturnType retVal;
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementValue;
  boolean resultCmp;

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON)
    P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) \
    ptrComparedCertElement;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON)
    KeyMCertificateElementConditionSenderReceiverFnType senderReceiverFunc;
    uint32 senderReceiverData;
    uint32 value;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_OFF)
    (void)ptrCert;
  #endif

  resultCmp = KEYM_TRUE;
  ptrCertElementValue = ptrElementCondtion->PtrCertElement->PtrElement;

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON)
  /* @Trace: KeyM_SUD_FUNC_312 */
  if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
  {
    /* Compare element value with another element value */
    ptrComparedCertElement = \
      ptrElementCondtion->ElementConditionValue.PtrCondCertElement;

    if (NULL_PTR != ptrComparedCertElement)
    {
      resultCmp = KEYM_FALSE;
      if (NULL_PTR != ptrComparedCertElement->PtrElement)
      {
        if (ptrCertElementValue->Element.Length == \
          ptrComparedCertElement->PtrElement->Element.Length)
        {
          retVal = KeyM_PrvMemCmp(ptrCertElementValue->Element.PtrData, \
            ptrComparedCertElement->PtrElement->Element.PtrData, \
            ptrCertElementValue->Element.Length);

          if (E_OK == retVal)
          {
            resultCmp = KEYM_TRUE;
          }
        }
      }
    }
  } /* @if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus) */

  if (KEYM_TRUE == resultCmp)
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON) */
  {
    /* @Trace: KeyM_SUD_FUNC_313 */
    #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON)
      /* Compare element value with senderReceiver value */
      senderReceiverFunc = \
        ptrElementCondtion->ElementConditionValue.CondSenderReceiverFunc;
      if (NULL_PTR != senderReceiverFunc)
      {
        resultCmp = KEYM_FALSE;
        senderReceiverData = 0u;
        /* Get the senderReceiver value */
        retVal = senderReceiverFunc(&senderReceiverData);
        KEYM_UNUSED(retVal)
        /* The element data length must not be bigger than 4, because the
          value received from sender-receiver port is uint32 type */
        if (4u >= ptrCertElementValue->Element.Length)
        {
          value = (uint32)KeyM_PrvConvertArrayToInteger(\
            ptrCertElementValue->Element.PtrData, \
            ptrCertElementValue->Element.Length);

          if (value == senderReceiverData)
          {
            resultCmp = KEYM_TRUE;
          }
        }
      }
    #endif /* #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) */
  }

  return resultCmp;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvPartOfElementEqualNotCompare                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvElementEqualNotCompare      **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvElementEqualNotCompare                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrElementCondtion, ptrCert                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvMemCmp, KeyM_PrvConvertArrayToInteger         **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvPartOfElementEqualNotCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion)
{
  Std_ReturnType retVal;
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementValue;
  boolean resultCmp;

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON)
    const KeyM_CertElementType *ptrComparedCertElement;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON)
    KeyMCertificateElementConditionSenderReceiverFnType senderReceiverFunc;
    uint32 senderReceiverData;
    uint32 value;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) */
  
  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_OFF)
    (void)ptrCert;
  #endif

  resultCmp = KEYM_TRUE;
  ptrCertElementValue = ptrElementCondtion->PtrCertElement->PtrElement;

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON)
  /* @Trace: KeyM_SUD_FUNC_317 */
  if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
  {
    /* Compare element value with another element value */
    ptrComparedCertElement = \
      ptrElementCondtion->ElementConditionValue.PtrCondCertElement;

    if (NULL_PTR != ptrComparedCertElement)
    {
      if (NULL_PTR != ptrComparedCertElement->PtrElement)
      {
        if (ptrCertElementValue->Element.Length == \
          ptrComparedCertElement->PtrElement->Element.Length)
        {
          retVal = KeyM_PrvMemCmp(ptrCertElementValue->Element.PtrData,\
            ptrComparedCertElement->PtrElement->Element.PtrData,\
            ptrCertElementValue->Element.Length);

          if (E_OK == retVal)
          {
            resultCmp = KEYM_FALSE;
          }
        }
      }
      else
      {
        resultCmp = KEYM_FALSE;
      }
    }
  } /* @if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus) */

  if (KEYM_TRUE == resultCmp)
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON) */
  {
    /* @Trace: KeyM_SUD_FUNC_318 */
    #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON)
      /* Compare element value with senderReceiver value */
      senderReceiverFunc = \
        ptrElementCondtion->ElementConditionValue.CondSenderReceiverFunc;
      if (NULL_PTR != senderReceiverFunc)
      {
        senderReceiverData = 0u;
        /* Get the senderReceiver value */
        retVal = senderReceiverFunc(&senderReceiverData);
        KEYM_UNUSED(retVal)
        /* The element data length must not be bigger than 4, because the
          value received from sender-receiver port is uint32 type */
        if (4u >= ptrCertElementValue->Element.Length)
        {
          value = (uint32)KeyM_PrvConvertArrayToInteger(\
            ptrCertElementValue->Element.PtrData, \
            ptrCertElementValue->Element.Length);
          if (value == senderReceiverData)
          {
            resultCmp = KEYM_FALSE;
          }
        }
      }
    #endif /* #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) */
  }

  return resultCmp;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvPartOfElementGreaterOrEqualCompare            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvElementGreaterOrEqualCompare**
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvElementGreaterOrEqualCompare                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrElementCondtion, ptrCert                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvConvertArrayToInteger                         **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvPartOfElementGreaterOrEqualCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion)
{
  boolean resultCmp;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrComparedData;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementValue;
  uint16 length;
  uint16 index;

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON)
    const KeyM_CertElementType *ptrComparedCertElement;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON)
    KeyMCertificateElementConditionSenderReceiverFnType senderReceiverFunc;
    uint32 senderReceiverData;
    uint32 value;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_OFF)
    (void)ptrCert;
  #endif

  resultCmp = KEYM_TRUE;
  ptrCertElementValue = ptrElementCondtion->PtrCertElement->PtrElement;

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON)
  /* @Trace: KeyM_SUD_FUNC_322 */
  if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
  {
    /* Compare element value with another element value */
    ptrComparedCertElement = \
      ptrElementCondtion->ElementConditionValue.PtrCondCertElement;

    if (NULL_PTR != ptrComparedCertElement)
    {
      if (NULL_PTR != ptrComparedCertElement->PtrElement)
      {
        length = ptrCertElementValue->Element.Length;

        if (length < ptrComparedCertElement->PtrElement->Element.Length)
        {
          resultCmp = KEYM_FALSE;
        }
        else if (length == ptrComparedCertElement->PtrElement->Element.Length)
        {
          ptrElementData = ptrCertElementValue->Element.PtrData;
          ptrComparedData = ptrComparedCertElement->PtrElement->Element.PtrData;
          for (index = 0u; index < length; index++)
          {
            if (ptrElementData[index] < ptrComparedData[index])
            {
              resultCmp = KEYM_FALSE;
              break;
            }
          }
        }
        else
        {
          /* resultCmp is true */
        }
      }
      else
      {
        resultCmp = KEYM_FALSE;
      }
    }
  } /* @if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus) */

  if (KEYM_TRUE == resultCmp)
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON) */
  {
    /* @Trace: KeyM_SUD_FUNC_323 */
    #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON)
      /* Compare element value with senderReceiver value */
      senderReceiverFunc = \
        ptrElementCondtion->ElementConditionValue.CondSenderReceiverFunc;
      if (NULL_PTR != senderReceiverFunc)
      {
        senderReceiverData = 0u;
        /* Get the senderReceiver value */
        (void)(senderReceiverFunc(&senderReceiverData));

        length = ptrCertElementValue->Element.Length;
        /* The element data length must not be bigger than 4, because the
          value received from sender-receiver port is uint32 type */
        if (4u >= length)
        {
          value = (uint32)KeyM_PrvConvertArrayToInteger(\
            ptrCertElementValue->Element.PtrData, length);
          if (value < senderReceiverData)
          {
            resultCmp = KEYM_FALSE;
          }
        }
      }
    #endif /* #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) */
  }

  return resultCmp;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvPartOfElementLessOrEqualCompare               **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvElementLessOrEqualCompare   **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvElementLessOrEqualCompare                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrElementCondtion, ptrCert                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvConvertArrayToInteger                         **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvPartOfElementLessOrEqualCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion)
{
  boolean resultCmp;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrComparedData;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementValue;
  uint16 length;
  uint16 index;

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON)
    const KeyM_CertElementType *ptrComparedCertElement;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON)
    KeyMCertificateElementConditionSenderReceiverFnType senderReceiverFunc;
    uint32 senderReceiverData;
    uint32 value;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_OFF)
    (void)ptrCert;
  #endif

  resultCmp = KEYM_TRUE;
  ptrCertElementValue = ptrElementCondtion->PtrCertElement->PtrElement;

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON)
  /* @Trace: KeyM_SUD_FUNC_327 */
  if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
  {
    /* Compare element value with another element value */
    ptrComparedCertElement = \
      ptrElementCondtion->ElementConditionValue.PtrCondCertElement;

    if (NULL_PTR != ptrComparedCertElement)
    {
      if (NULL_PTR != ptrComparedCertElement->PtrElement)
      {
        length = ptrCertElementValue->Element.Length;
        if (length > ptrComparedCertElement->PtrElement->Element.Length)
        {
          resultCmp = KEYM_FALSE;
        }
        else if (length == ptrComparedCertElement->PtrElement->Element.Length)
        {
          ptrElementData = ptrCertElementValue->Element.PtrData;
          ptrComparedData = ptrComparedCertElement->PtrElement->Element.PtrData;
          for (index = 0u; index < length; index++)
          {
            if (ptrElementData[index] > ptrComparedData[index])
            {
              resultCmp = KEYM_FALSE;
              break;
            }
          }
        }
        else
        {
          /* resultCmp is true */
        }
      }
      else
      {
        resultCmp = KEYM_FALSE;
      }
    }
  } /* @if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus) */

  if (KEYM_TRUE == resultCmp)
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON) */
  {
    /* @Trace: KeyM_SUD_FUNC_328 */
    #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON)
      /* Compare element value with senderReceiver value */
      senderReceiverFunc = \
        ptrElementCondtion->ElementConditionValue.CondSenderReceiverFunc;
      if (NULL_PTR != senderReceiverFunc)
      {
        senderReceiverData = 0u;
        /* Get the senderReceiver value */
        (void)(senderReceiverFunc(&senderReceiverData));

        length = ptrCertElementValue->Element.Length;
        /* The element data length must not be bigger than 4, because the
          value received from sender-receiver port is uint32 type */
        if (4u < length)
        {
          resultCmp = KEYM_FALSE;
        }
        else
        {
          value = (uint32)KeyM_PrvConvertArrayToInteger(\
            ptrCertElementValue->Element.PtrData, length);
          if (value > senderReceiverData)
          {
            resultCmp = KEYM_FALSE;
          }
        }
      }
    #endif /* #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) */
  }

  return resultCmp;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvPartOfElementLessThanCompare                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvElementLessThanCompare      **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvElementLessThanCompare                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrElementCondtion, ptrCert                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvConvertArrayToInteger                         **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvPartOfElementLessThanCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion)
{
  boolean resultCmp;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrComparedData;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementValue;
  uint16 length;
  uint16 index;

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON)
    const KeyM_CertElementType *ptrComparedCertElement;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON)
    KeyMCertificateElementConditionSenderReceiverFnType senderReceiverFunc;
    uint32 senderReceiverData;
    uint32 value;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_OFF)
    (void)ptrCert;
  #endif

  resultCmp = KEYM_TRUE;
  ptrCertElementValue = ptrElementCondtion->PtrCertElement->PtrElement;

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON)
  /* @Trace: KeyM_SUD_FUNC_332 */
  if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
  {
    /* Compare element value with another element value */
    ptrComparedCertElement = \
      ptrElementCondtion->ElementConditionValue.PtrCondCertElement;

    if (NULL_PTR != ptrComparedCertElement)
    {
      if (NULL_PTR != ptrComparedCertElement->PtrElement)
      {
        length = ptrCertElementValue->Element.Length;
        if (length > ptrComparedCertElement->PtrElement->Element.Length)
        {
          resultCmp = KEYM_FALSE;
        }
        else if (length == ptrComparedCertElement->PtrElement->Element.Length)
        {
          ptrElementData = ptrCertElementValue->Element.PtrData;
          ptrComparedData = ptrComparedCertElement->PtrElement->Element.PtrData;
          for (index = 0u; index < length; index++)
          {
            if (ptrElementData[index] >= ptrComparedData[index])
            {
              resultCmp = KEYM_FALSE;
              break;
            }
          }
        }
        else
        {
          /* resultCmp is true */
        }
      }
      else
      {
        resultCmp = KEYM_FALSE;
      }
    }
  } /* @if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus) */

  if (KEYM_TRUE == resultCmp)
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON) */
  {
    /* @Trace: KeyM_SUD_FUNC_333 */
    #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON)
      /* Compare element value with senderReceiver value */
      senderReceiverFunc = \
        ptrElementCondtion->ElementConditionValue.CondSenderReceiverFunc;
      if (NULL_PTR != senderReceiverFunc)
      {
        senderReceiverData = 0u;
        /* Get the senderReceiver value */
        (void)(senderReceiverFunc(&senderReceiverData));

        length = ptrCertElementValue->Element.Length;
        /* The element data length must not be bigger than 4, because the
          value received from sender-receiver port is uint32 type */
        if (4u < length)
        {
          resultCmp = KEYM_FALSE;
        }
        else
        {
          value = (uint32)KeyM_PrvConvertArrayToInteger(\
            ptrCertElementValue->Element.PtrData, length);
          if (value >= senderReceiverData)
          {
            resultCmp = KEYM_FALSE;
          }
        }
      }
    #endif /* #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) */
  }

  return resultCmp;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if ((KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) || \
        (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON)) */

/*******************************************************************************
** Function Name      : KeyM_PrvElementEqualCompare                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check element equals condition value                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrCert, ptrElementCondtion                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvElementGetByIndex,                            **
**                      KeyM_PrvConvertArrayToInteger,                        **
**                      KeyM_PrvPartOfElementEqualCompare                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvElementEqualCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion)
{
  boolean resultCmp;
  #if ((KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) || \
    (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON))
    uint64 value;
  #endif

  #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON)
    const KeyM_CertElementConditionArrayElementType *ptrPrimitive;
    uint16 primitiveArrayLength;
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
    uint32 elementDataLength;
    uint16 index;
    Std_ReturnType retVal;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON)
    P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementValue;
    P2CONST(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrPrimitiveValue;
  #endif

  /* @Trace: KeyM_SUD_FUNC_307 */
  #if ((KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) || \
    (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON))

  resultCmp = KEYM_TRUE;
  if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
  {
    /* @Trace: KeyM_SUD_FUNC_308 */
    #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON)
    ptrCertElementValue = ptrElementCondtion->PtrCertElement->PtrElement;
    ptrPrimitiveValue = \
      ptrElementCondtion->ElementConditionValue.PtrConditionPrimitive;
    if (NULL_PTR != ptrPrimitiveValue)
    {
      resultCmp = KEYM_FALSE;
      /* The element data length must not be bigger than 8, because the
         primitive value is uint64 type */
      if (ptrCertElementValue->Element.Length <= 8u)
      {
        value = KeyM_PrvConvertArrayToInteger(\
          ptrCertElementValue->Element.PtrData, \
          ptrCertElementValue->Element.Length);
        if (value == *ptrPrimitiveValue)
        {
          resultCmp = KEYM_TRUE;
        }
      }
    }

    if (KEYM_TRUE == resultCmp)
    #endif /* #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) */
    {
      #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_309 */
        /* Compare element with a primitive value array */
        if (NULL_PTR != \
          ptrElementCondtion->ElementConditionValue.PtrCondPrimitiveArray)
        {
          primitiveArrayLength = \
            ptrElementCondtion->ElementConditionValue.CondPrimitiveArrayLength;

          /* The element data length must not be bigger than 8, because the
            primitive value is uint64 type */
          for (index = 0u; ((index < primitiveArrayLength) && \
            (KEYM_TRUE == resultCmp)); index++)
          {
            ptrElementData = NULL_PTR;
            elementDataLength = 8u;
            ptrPrimitive = &ptrElementCondtion->\
              ElementConditionValue.PtrCondPrimitiveArray[index];
            /* Get the element data of the element by index */
            retVal = KeyM_PrvElementGetByIndex(ptrCert, \
              ptrElementCondtion->PtrCertElement, \
              ptrPrimitive->ConditionArrayElementIndex, \
              &ptrElementData, &elementDataLength);

            if (E_OK == retVal)
            {
              value = KeyM_PrvConvertArrayToInteger(ptrElementData, \
                elementDataLength);

              if (value == ptrPrimitive->ConditionArrayElementValue)
              {
                resultCmp = KEYM_TRUE;
              }
              else
              {
                resultCmp = KEYM_FALSE;
              }
            }
            else
            {
              resultCmp = KEYM_FALSE;
            }
          }
        }
      #endif /* #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON) */
    }
  } /* @if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus) */

  if (KEYM_TRUE == resultCmp)
  #endif
  {
    /* @Trace: KeyM_SUD_FUNC_310 */
    #if ((KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) || \
      (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON))
      resultCmp = KeyM_PrvPartOfElementEqualCompare(ptrCert, \
        ptrElementCondtion);
    #endif
  }

  return resultCmp;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvElementEqualNotCompare                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check element is not equals condition value           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrCert, ptrElementCondtion                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvElementGetByIndex,                            **
**                      KeyM_PrvConvertArrayToInteger,                        **
**                      KeyM_PrvPartOfElementEqualNotCompare                  **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvElementEqualNotCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion)
{
  boolean resultCmp;
  #if ((KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) || \
    (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON))
    uint64 value;
  #endif

  #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON)
    const KeyM_CertElementConditionArrayElementType *ptrPrimitive;
    uint16 primitiveArrayLength;
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
    uint32 elementDataLength;
    uint16 index;
    Std_ReturnType retVal;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON)
    P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementValue;
    P2CONST(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrPrimitiveValue;
  #endif

  #if ((KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) || \
    (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON))
  /* @Trace: KeyM_SUD_FUNC_314 */
  resultCmp = KEYM_TRUE;
  if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
  {
    #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON)
    ptrCertElementValue = ptrElementCondtion->PtrCertElement->PtrElement;
    /* Compare element value with a primitive value */
    ptrPrimitiveValue = \
      ptrElementCondtion->ElementConditionValue.PtrConditionPrimitive;

    if (NULL_PTR != ptrPrimitiveValue)
    {
      /* The element data length must not be bigger than 8, because the
         primitive value is uint64 type */
      if (8u >= ptrCertElementValue->Element.Length)
      {
        value = KeyM_PrvConvertArrayToInteger(\
          ptrCertElementValue->Element.PtrData, \
          ptrCertElementValue->Element.Length);
        if (value == *ptrPrimitiveValue)
        {
          resultCmp = KEYM_FALSE;
        }
      }
    }

    if (KEYM_TRUE == resultCmp)
    #endif /* #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) */
    {
      #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_315 */
        /* Compare element with a primitive value array */
        if (NULL_PTR != \
          ptrElementCondtion->ElementConditionValue.PtrCondPrimitiveArray)
        {
          primitiveArrayLength = \
            ptrElementCondtion->ElementConditionValue.CondPrimitiveArrayLength;

          /* The element data length must not be bigger than 8, because the
            primitive value is uint64 type */
          for (index = 0u; ((index < primitiveArrayLength) && \
            (KEYM_TRUE == resultCmp)); index++)
          {
            ptrElementData = NULL_PTR;
            elementDataLength = 8u;
            ptrPrimitive = &ptrElementCondtion->\
              ElementConditionValue.PtrCondPrimitiveArray[index];
            /* Get the element data of the element by index */
            retVal = KeyM_PrvElementGetByIndex(ptrCert, \
              ptrElementCondtion->PtrCertElement, \
              ptrPrimitive->ConditionArrayElementIndex, \
              &ptrElementData, &elementDataLength);
            if (E_OK == retVal)
            {
              value = KeyM_PrvConvertArrayToInteger(ptrElementData, \
                elementDataLength);

              if (value == ptrPrimitive->ConditionArrayElementValue)
              {
                resultCmp = KEYM_FALSE;
              }
            }
            else if (E_NOT_OK == retVal)
            {
              /* The element data was not found */
              resultCmp = KEYM_FALSE;
            }
            else
            {
              /* In the case retval is KEYM_E_KEY_CERT_SIZE_MISMATCH, \
                the element data length is bigger than 8, so the element
                data value is not equal to the primitive value */
            }
          }
        }
      #endif /* #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON) */
    }
  } /* @if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus) */

  if (KEYM_TRUE == resultCmp)
  #endif
  {
    /* @Trace: KeyM_SUD_FUNC_316 */
    #if ((KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) || \
      (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON))
      resultCmp = KeyM_PrvPartOfElementEqualNotCompare(ptrCert, \
        ptrElementCondtion);
    #endif
  }

  return resultCmp;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvElementGreaterOrEqualCompare                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check element is greater or equals condition value    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrCert, ptrElementCondtion                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvElementGetByIndex,                            **
**                      KeyM_PrvConvertArrayToInteger,                        **
**                      KeyM_PrvPartOfElementGreaterOrEqualCompare            **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvElementGreaterOrEqualCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion)
{
  boolean resultCmp;
  #if ((KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) || \
    (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON))
    uint64 value;
  #endif

  #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON)
    const KeyM_CertElementConditionArrayElementType *ptrPrimitive;
    uint16 primitiveArrayLength;
    uint32 elementDataLength;
    Std_ReturnType retVal;
    uint16 index;
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON)
    P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementValue;
    P2CONST(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrPrimitiveValue;
  #endif

  #if ((KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) || \
    (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON))
  /* @Trace: KeyM_SUD_FUNC_319 */
  resultCmp = KEYM_TRUE;
  if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
  {
    #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON)
    ptrCertElementValue = ptrElementCondtion->PtrCertElement->PtrElement;
    /* Compare element value with a primitive value */
    ptrPrimitiveValue = \
      ptrElementCondtion->ElementConditionValue.PtrConditionPrimitive;

    if (NULL_PTR != ptrPrimitiveValue)
    {
      if (8u >= ptrCertElementValue->Element.Length)
      {
        value = KeyM_PrvConvertArrayToInteger(\
          ptrCertElementValue->Element.PtrData, \
          ptrCertElementValue->Element.Length);
        if (value < *ptrPrimitiveValue)
        {
          resultCmp = KEYM_FALSE;
        }
      }
    }

    if (KEYM_TRUE == resultCmp)
    #endif /* #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) */
    {
      #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_320 */
        /* Compare element with a primitive value array */
        if (NULL_PTR != \
          ptrElementCondtion->ElementConditionValue.PtrCondPrimitiveArray)
        {
          primitiveArrayLength = \
            ptrElementCondtion->ElementConditionValue.CondPrimitiveArrayLength;

          /* The element data length must not be bigger than 8, because the
            primitive value is uint64 type */
          for (index = 0u; ((index < primitiveArrayLength) && \
            (KEYM_TRUE == resultCmp)); index++)
          {
            ptrElementData = NULL_PTR;
            elementDataLength = 8u;
            ptrPrimitive = &ptrElementCondtion->\
              ElementConditionValue.PtrCondPrimitiveArray[index];
            /* Get the element data of the element by index */
            retVal = KeyM_PrvElementGetByIndex(ptrCert, \
              ptrElementCondtion->PtrCertElement, \
              ptrPrimitive->ConditionArrayElementIndex, \
              &ptrElementData, &elementDataLength);

            if (E_OK == retVal)
            {
              value = KeyM_PrvConvertArrayToInteger(ptrElementData, \
                elementDataLength);

              if (value < ptrPrimitive->ConditionArrayElementValue)
              {
                resultCmp = KEYM_FALSE;
              }
            }
            else if (E_NOT_OK == retVal)
            {
              /* The element data was not found */
              resultCmp = KEYM_FALSE;
            }
            else
            {
              /* In the case retval is KEYM_E_KEY_CERT_SIZE_MISMATCH, \
                the element data length is bigger than 8, so the element
                data value is bigger than the primitive value */
            }
          }
        }
      #endif /* #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON) */
    }
  } /* @if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus) */

  if (KEYM_TRUE == resultCmp)
  #endif
  {
    /* @Trace: KeyM_SUD_FUNC_321 */
    #if ((KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) || \
      (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON))
    resultCmp = KeyM_PrvPartOfElementGreaterOrEqualCompare(ptrCert, \
      ptrElementCondtion);
    #endif
  }

  return resultCmp;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvElementLessOrEqualCompare                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check element is less or equals condition value       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrCert, ptrElementCondtion                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvElementGetByIndex,                            **
**                      KeyM_PrvConvertArrayToInteger,                        **
**                      KeyM_PrvPartOfElementLessOrEqualCompare               **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvElementLessOrEqualCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion)
{
  boolean resultCmp;
  #if ((KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) || \
    (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON))
    uint64 value;
  #endif

  #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON)
    const KeyM_CertElementConditionArrayElementType *ptrPrimitive;
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
    uint16 primitiveArrayLength;
    uint32 elementDataLength;
    Std_ReturnType retVal;
    uint16 index;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON)
    P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementValue;
    P2CONST(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrPrimitiveValue;
  #endif

  #if ((KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) || \
    (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON))
  /* @Trace: KeyM_SUD_FUNC_324 */
  resultCmp = KEYM_TRUE;
  if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
  {
    #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON)
    ptrCertElementValue = ptrElementCondtion->PtrCertElement->PtrElement;
    /* Compare element value with a primitive value */
    ptrPrimitiveValue = \
      ptrElementCondtion->ElementConditionValue.PtrConditionPrimitive;

    if (NULL_PTR != ptrPrimitiveValue)
    {
      if (8u < ptrCertElementValue->Element.Length)
      {
        resultCmp = KEYM_FALSE;
      }
      else
      {
        value = KeyM_PrvConvertArrayToInteger(\
          ptrCertElementValue->Element.PtrData, \
          ptrCertElementValue->Element.Length);
        if (value > *ptrPrimitiveValue)
        {
          resultCmp = KEYM_FALSE;
        }
      }
    }

    if (KEYM_TRUE == resultCmp)
    #endif /* #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) */
    {
      #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_325 */
        /* Compare element with a primitive value array */
        if (NULL_PTR != \
          ptrElementCondtion->ElementConditionValue.PtrCondPrimitiveArray)
        {
          primitiveArrayLength = \
            ptrElementCondtion->ElementConditionValue.CondPrimitiveArrayLength;

          /* The element data length must not be bigger than 8, because the
            primitive value is uint64 type */
          for (index = 0u; ((index < primitiveArrayLength) && \
            (KEYM_TRUE == resultCmp)); index++)
          {
            ptrElementData = NULL_PTR;
            elementDataLength = 8u;
            ptrPrimitive = &ptrElementCondtion->\
              ElementConditionValue.PtrCondPrimitiveArray[index];
            /* Get the element data of the element by index */
            retVal = KeyM_PrvElementGetByIndex(ptrCert, \
              ptrElementCondtion->PtrCertElement, \
              ptrPrimitive->ConditionArrayElementIndex, \
              &ptrElementData, &elementDataLength);

            if (E_OK == retVal)
            {
              value = KeyM_PrvConvertArrayToInteger(ptrElementData, \
                elementDataLength);

              if (value > ptrPrimitive->ConditionArrayElementValue)
              {
                resultCmp = KEYM_FALSE;
              }
            }
            else
            {
              /* In the case retval is KEYM_E_KEY_CERT_SIZE_MISMATCH, \
                the element data length is bigger than 8, so the element
                data value is bigger than the primitive value */
              resultCmp = KEYM_FALSE;
            }
          }
        }
      #endif /* #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON) */
    }
  } /* @if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus) */

  if (KEYM_TRUE == resultCmp)
  #endif
  {
    /* @Trace: KeyM_SUD_FUNC_326 */
    #if ((KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) || \
      (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON))
      resultCmp = KeyM_PrvPartOfElementLessOrEqualCompare(ptrCert, \
        ptrElementCondtion);
    #endif
  }

  return resultCmp;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvElementLessThanCompare                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check element is less than condition value            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrCert, ptrElementCondtion                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvElementGetByIndex,                            **
**                      KeyM_PrvConvertArrayToInteger,                        **
**                      KeyM_PrvPartOfElementLessThanCompare                  **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvElementLessThanCompare(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion)
{
  boolean resultCmp;

  #if ((KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) || \
    (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON))
    uint64 value;
  #endif

  #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON)
    const KeyM_CertElementConditionArrayElementType *ptrPrimitive;
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
    uint16 primitiveArrayLength;
    uint32 elementDataLength;
    Std_ReturnType retVal;
    uint16 index;
  #endif /* #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON) */

  #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON)
    P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementValue;
    P2CONST(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrPrimitiveValue;
  #endif

  #if ((KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) || \
    (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON))
  /* @Trace: KeyM_SUD_FUNC_329 */
    resultCmp = KEYM_TRUE;
  if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
  {
    #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON)
    ptrCertElementValue = ptrElementCondtion->PtrCertElement->PtrElement;
    /* Compare element value with a primitive value */
    ptrPrimitiveValue = \
      ptrElementCondtion->ElementConditionValue.PtrConditionPrimitive;

    if (NULL_PTR != ptrPrimitiveValue)
    {
      if (8u < ptrCertElementValue->Element.Length)
      {
        resultCmp = KEYM_FALSE;
      }
      else
      {

        value = KeyM_PrvConvertArrayToInteger(\
          ptrCertElementValue->Element.PtrData, \
          ptrCertElementValue->Element.Length);
        if (value >= *ptrPrimitiveValue)
        {
          resultCmp = KEYM_FALSE;
        }
      }
    }

    if (KEYM_TRUE == resultCmp)
    #endif /* #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON) */
    {
      #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_330 */
        /* Compare element with a primitive value array */
        if (NULL_PTR != \
          ptrElementCondtion->ElementConditionValue.PtrCondPrimitiveArray)
        {
          primitiveArrayLength = ptrElementCondtion->\
            ElementConditionValue.CondPrimitiveArrayLength;

          /* The element data length must not be bigger than 8, because the
            primitive value is uint64 type */
          for (index = 0u; ((index < primitiveArrayLength) && \
            (KEYM_TRUE == resultCmp)); index++)
          {
            ptrElementData = NULL_PTR;
            elementDataLength = 8u;
            ptrPrimitive = &ptrElementCondtion->\
              ElementConditionValue.PtrCondPrimitiveArray[index];
            /* Get the element data of the element by index */
            retVal = KeyM_PrvElementGetByIndex(ptrCert, \
              ptrElementCondtion->PtrCertElement, \
              ptrPrimitive->ConditionArrayElementIndex, \
              &ptrElementData, &elementDataLength);

            if (E_OK == retVal)
            {
              value = KeyM_PrvConvertArrayToInteger(ptrElementData, \
                      elementDataLength);

              if (value >= ptrPrimitive->ConditionArrayElementValue)
              {
                resultCmp = KEYM_FALSE;
              }
            }
            else
            {
              /* In the case retval is KEYM_E_KEY_CERT_SIZE_MISMATCH, \
                the element data length is bigger than 8, so the element
                data value is bigger than the primitive value */
              resultCmp = KEYM_FALSE;
            }
          }
        }
      #endif /* #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON) */
    }
  } /* @if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus) */

  if (KEYM_TRUE == resultCmp)
  #endif
  {
    /* @Trace: KeyM_SUD_FUNC_331 */
    #if ((KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON) || \
      (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON))
      resultCmp = KeyM_PrvPartOfElementLessThanCompare(ptrCert, \
        ptrElementCondtion);
    #endif
  }

  return resultCmp;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvElementCheckCondition                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check the element condition                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrCert, ptrElementCondtion                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvElementEqualCompare,                          **
**                      KeyM_PrvElementEqualNotCompare,                       **
**                      KeyM_PrvElementGreaterOrEqualCompare,                 **
**                      KeyM_PrvElementLessOrEqualCompare,                    **
**                      KeyM_PrvElementLessThanCompare                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvElementCheckCondition(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementConditionType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementCondtion)
{
  boolean resultCmp = KEYM_FALSE;
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement;

  /* @Trace: KeyM_SUD_FUNC_301 */
  ptrCertElement = ptrElementCondtion->PtrCertElement;

  if (NULL_PTR != ptrCertElement)
  {
    if (NULL_PTR != ptrCertElement->PtrElement)
    {
      switch (ptrElementCondtion->ConditionType)
      {
        case KEYM_EQUALS:
          /* @Trace: KeyM_SUD_FUNC_302 */
          resultCmp = KeyM_PrvElementEqualCompare(ptrCert, ptrElementCondtion);
          break;
        case KEYM_EQUALS_NOT:
          /* @Trace: KeyM_SUD_FUNC_303 */
          resultCmp = KeyM_PrvElementEqualNotCompare(ptrCert, \
            ptrElementCondtion);
          break;
        case KEYM_GREATER_OR_EQUAL:
          /* @Trace: KeyM_SUD_FUNC_304 */
          resultCmp = KeyM_PrvElementGreaterOrEqualCompare(ptrCert, \
            ptrElementCondtion);
          break;
        case KEYM_LESS_OR_EQUAL:
          /* @Trace: KeyM_SUD_FUNC_305 */
          resultCmp = KeyM_PrvElementLessOrEqualCompare(ptrCert, \
            ptrElementCondtion);
          break;
        case KEYM_LESS_THAN:
          /* @Trace: KeyM_SUD_FUNC_306 */
          resultCmp = KeyM_PrvElementLessThanCompare(ptrCert, \
            ptrElementCondtion);
          break;
        default:
          /* Do nothing */
          break;
      }
    } /* @if (NULL_PTR != ptrCertElement->PtrElement) */
  } /* @if (NULL_PTR != ptrCertElement) */

  return resultCmp;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvElementCheckRule                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check the element verification rule                   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrCert, ptrElementRule                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvElementCheckCondition                         **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvElementCheckRule(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertificateElementRuleType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrElementRule)
{
  boolean resultCmp;
  boolean condResult;
  uint8 indexCnt;
  const KeyM_CertificateElementConditionType *ptrCondition;

  if (KEYM_AND == ptrElementRule->LogicalOperator)
  {
    /* @Trace: KeyM_SUD_FUNC_299 */
    resultCmp = KEYM_TRUE;
    for (indexCnt = 0u; indexCnt < ptrElementRule->NumberOfCondition; indexCnt++)
    {
      ptrCondition = ptrElementRule->PtrElementCondArgument[indexCnt];
      condResult = KeyM_PrvElementCheckCondition(ptrCert, ptrCondition);

      resultCmp = resultCmp & condResult;
      if (resultCmp == KEYM_FALSE)
      {
        break;
      }
    }
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_300 */
    resultCmp = KEYM_FALSE;
    for (indexCnt = 0u; indexCnt < ptrElementRule->NumberOfCondition; indexCnt++)
    {
      ptrCondition = ptrElementRule->PtrElementCondArgument[indexCnt];
      condResult = KeyM_PrvElementCheckCondition(ptrCert, ptrCondition);

      resultCmp = resultCmp | condResult;
      if (resultCmp == KEYM_TRUE)
      {
        break;
      }
    }
  }

  return resultCmp;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvElementRuleVerify                             **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Verify the certificate element according to element   **
**                      verification rules                                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrCert                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvElementCheckRule                              **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvElementRuleVerify(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  uint16 retVal;
  boolean resultCmp;
  uint8 indexCnt;

  /* @Trace: KeyM_SUD_FUNC_220 */
  retVal = KEYM_E_OK;
  if (NULL_PTR != ptrCert->PtrCertElementRule)
  {
    for (indexCnt = 0u; indexCnt < ptrCert->NumberOfElementRule; indexCnt++)
    {
      resultCmp = KeyM_PrvElementCheckRule(ptrCert, \
        ptrCert->PtrCertElementRule[indexCnt]);
      if (resultCmp == KEYM_FALSE)
      {
        retVal = KEYM_E_NOT_OK;
        break;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON) */
/*******************************************************************************
** Function Name      : KeyM_PrvElementCopy                                   **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Copy data form source element to destination element  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrSrcElement                                         **
**                                                                            **
** InOut Parameters   : ptrDesElement                                         **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvElementCopy(\
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrSrcElement, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrDesElement)
{
  /* @Trace: KeyM_SUD_FUNC_223 */
  if ((NULL_PTR != ptrSrcElement) && (NULL_PTR != ptrDesElement))
  {
    ptrDesElement->Element.PtrData = ptrSrcElement->Element.PtrData;
    ptrDesElement->Element.Length = ptrSrcElement->Element.Length;
    ptrDesElement->Element.Tag = ptrSrcElement->Element.Tag;
    ptrDesElement->ElementIndex = ptrSrcElement->ElementIndex;
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvGetPublicKeyAlgorithmCount                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get element algorithm of public key count             **
**in configuration                                                            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrCert                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  :                                                       **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, KEYM_CODE) KeyM_PrvGetPublicKeyAlgorithmCount(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert \
  )
{
  uint8 numberOfPubkeyAlgo = 0;
  uint16 count;
  uint16 maxelementcount;
  P2VAR(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrElement;
  P2VAR(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) currentptrElement;
  KeyM_CertificateElementTypeOfStructure elementOfStruct;
  /*Get element pointer and element maximumbumber*/
  maxelementcount = ptrCert->NumberOfCertElement;
  ptrElement = ptrCert->PtrCertElement;
/* @Trace: KeyM_SUD_FUNC_964 */
  for (count = 0; count < maxelementcount; count++)
  {
    currentptrElement = &ptrElement[count];
    elementOfStruct = currentptrElement->ElementOfStruct;
    if (elementOfStruct == KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_PUBLIC_KEY_ALGORITHM)
    {
      numberOfPubkeyAlgo++;
    }
  }
  return numberOfPubkeyAlgo;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"


#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:11.8 */
/* polyspace-end MISRA-C3:11.5 CERT-C:EXP36-C */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
