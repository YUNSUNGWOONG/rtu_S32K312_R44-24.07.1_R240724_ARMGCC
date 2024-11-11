/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM.c                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key Manager API Functionality                                 **
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
** 1.0.1.0   27-Mar-2021   TamTV6       Add Trace SUD                         **
** 1.0.3.0   13-May-2022   DienTC1      #21524                                **
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
** 1.0.8.0   31-Jul-2023   PhuocLH9     #CP44-2396,#CP44-2394                 **
** 1.0.9.0   21-Feb-2024   JS Kang      #CP44-3633,#CP44-3635				  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM module header file */
#include "KeyM_Ram.h"
/* KeyM IntFunc header file */
#include "KeyM_IntFunc.h"
/* For key handler function */
#include "KeyM_Externals.h"
/* KeyM header file */
#include "KeyM.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
/*******************************************************************************
** Function Name      : KeyM_Init                                             **
**                                                                            **
** Service ID         : 0x01                                                  **
**                                                                            **
** Description        : This function initializes the key management module   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ConfigPtr                                             **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoKey, KeyM_CryptoCert     **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Csm_KeyElementSet, Csm_KeySetValid, Csm_KeyElementGet **
**                      Det_ReportError                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00414 SRS_BSW_00358 SRS_BSW_00101 SRS_BSW_00337 SWS_BSW_00050 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(void, KEYM_CODE) KeyM_Init
  (P2CONST(KeyM_ConfigType, AUTOMATIC, KEYM_APPL_CONST) ConfigPtr)
{
  #if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)
    #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
      P2VAR(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_DATA) ptrKey;
      uint16 keyLength;
      uint32 keyMaxLength;
    #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */
  #endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */

  #if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
    P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
    uint32 certMaxLength;
    #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
      uint16 certLength;
    #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */
  #endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

  #if ((KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON) || \
    ((KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON) && \
    (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)))
    uint16 indexCnt;
  #endif
  Std_ReturnType retVal;

  /* @Trace: KeyM_SUD_FUNC_001 */
  retVal = E_OK;

  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT != KeyM_ModuleState)
  {
    /* Do nothing */
  }
  else if (NULL_PTR != ConfigPtr)
  {
    /* A Configuration of the Key Manager at initialization is
      currently not used and
      shall therefore pass a NULL_PTR to the module */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      KEYM_REPORT_ERROR(KEYM_INIT_SID, KEYM_E_INIT_FAILED);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    /* If the crypto key submodule is active, all keys stored in NVM
      shall be read from and stored to CSM (RAM-) key slots */
    #if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)
    #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
    for (indexCnt = KEYM_ZERO; ((KEYM_TOTAL_KEY > indexCnt) && \
      (E_OK == retVal)); indexCnt++)
    {
      /* @Trace: KeyM_SUD_FUNC_002 */
      ptrKey = &KeyM_CryptoKey[indexCnt];
      keyMaxLength = ptrKey->KeyMaxLength;
      if (KEYM_STORAGE_IN_NVM == ptrKey->KeyStorageType)
      {
        if (KEYM_ONE == ptrKey->PtrKeyData[keyMaxLength - 1u])
        {
          /* @Trace: KeyM_SUD_FUNC_003 */
          keyLength = ptrKey->PtrKeyData[keyMaxLength - 3u];
          keyLength = (keyLength << KEYM_UPPER_BYTE_SHIFT) | \
            (uint16)ptrKey->PtrKeyData[keyMaxLength - 2u];
          ptrKey->KeyLength = keyLength;
          /* Store request data to the key element 1 of target key */
          retVal = Csm_KeyElementSet(ptrKey->CsmTargetKeyId, \
            KEYM_KEY_ELEMENT1_ID, \
            &ptrKey->PtrKeyData[0u], \
            keyLength);

          if (E_OK == retVal)
          {
            /* Validate the alternated source key */
            retVal = Csm_KeySetValid(ptrKey->CsmTargetKeyId);
            if (E_OK == retVal)
            {
              /* Set key state to be valid */
              ptrKey->KeyState = KEYM_ONE;
            }
          }
        } /* @if (ptrKey->PtrKeyData[KEYM_ZERO] == KEY_ONE) */
      } /* @if (ptrKey->KeyStorageType == KEYM_STORAGE_IN_NVM) */
    } /* @for (indexCnt = KEYM_ZERO; KEYM_TOTAL_KEY > indexCnt; indexCnt++) */

    if (E_OK == retVal)
    #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */
    #endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */
    {
      /* If the certificate submodule is active and permanently stored
       certificates are available in unparsed and unverified state, set
       certificate status to be un-parse state to allow background task
       to pre-parse and pre-verify certificates */
      #if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
      /* @Trace: KeyM_SUD_FUNC_004 */
      for (indexCnt = KEYM_ZERO; ((KEYM_TOTAL_CERTIFICATE > indexCnt) && \
        (E_OK == retVal)); indexCnt++)
      {
        ptrCert = &KeyM_CryptoCert[indexCnt];
        certMaxLength = ptrCert->CertMaxLength;

        if (KEYM_STORAGE_IN_CSM == ptrCert->CertStorageType)
        {
          /* @Trace: KeyM_SUD_FUNC_005 */
          retVal = Csm_KeyElementGet(ptrCert->CsmTargetKeyId,\
            KEYM_KEY_ELEMENT1_ID,\
            &ptrCert->PtrCertData[0u],\
            &certMaxLength);
          if ((E_OK == retVal) && (0u < certMaxLength))
          {
            ptrCert->CertLength = (uint16)certMaxLength;
            /* Set certificate status is not parsed to allow parsing certificate
              in the main background function */
            ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;
          }
        }
        #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
        else if (KEYM_STORAGE_IN_NVM == ptrCert->CertStorageType)
        {
          /* @Trace: KeyM_SUD_FUNC_006 */
          if (KEYM_ONE == ptrCert->PtrCertData[certMaxLength - 1u])
          {
            certLength = ptrCert->PtrCertData[certMaxLength - 3u];
            certLength = (certLength << KEYM_UPPER_BYTE_SHIFT) | \
              (uint16)ptrCert->PtrCertData[certMaxLength - 2u];
            ptrCert->CertLength = certLength;
            /* Set certificate status is not parsed to allow parsing certificate
              in the main background function */
            ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;
          } /* @if (ptrCert->PtrCertData[KEYM_ZERO] == KEY_ONE) */
        }
        #endif /* KEYM_STORAGE_IN_NVM_ENABLED == STD_ON */
        else
        {
          /* Do nothing */
        } /* @if (KEYM_STORAGE_IN_CSM == ptrCert->CertStorageType) */
      } /* @for (index = KEYM_ZERO; KEYM_TOTAL_KEY > index; index++) */
      #endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */
    }

    /* If above work are OK, set KeyM_ModuleState = KEYM_IDLE */
    /* else, the error KEYM_E_INIT_FAILED shall be reported to the DET and
       set KeyM_ModuleState = KEYM_UNINIT */
    #if (((KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON) && \
          (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)) || \
        (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON))
    if (E_OK != retVal)
    {
      /* @Trace: KeyM_SUD_FUNC_008 */
	    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
	    /* Report to DET */
	    KEYM_REPORT_ERROR(KEYM_INIT_SID, KEYM_E_INIT_FAILED);
	    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
    }
    else
    #endif
    {
      /* @Trace: KeyM_SUD_FUNC_007 */
      KeyM_ModuleState = KEYM_IDLE;
    }
  } /* @if (KEYM_UNINIT != KeyM_ModuleState) */
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_DeInit                                           **
**                                                                            **
** Service ID         : 0x02                                                  **
**                                                                            **
** Description        : This function resets the key management module to the **
**                      uninitialized state.                                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState                                      **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvMemClear, Det_ReportError                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00120 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(void, KEYM_CODE) KeyM_DeInit(void)
{
  #if ((KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON) || \
    (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON))
    uint16 indexCnt;
  #endif

  #if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)
    P2VAR(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_DATA) ptrKey;
  #endif

  #if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
    P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  #endif

  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_009 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_DEINIT_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    #if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)
      /* @Trace: KeyM_SUD_FUNC_010 */
      #if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
        KeyM_SessionState = KEYM_SESSION_DEACTIVATED;
      #endif /* KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */

      /* Clear the data of all keys */
      for (indexCnt = KEYM_ZERO; KEYM_TOTAL_KEY > indexCnt; indexCnt++)
      {
        ptrKey = &KeyM_CryptoKey[indexCnt];
        ptrKey->KeyState = KEYM_ZERO;
        KeyM_PrvMemClear(ptrKey->PtrKeyData, ptrKey->KeyMaxLength);
      }
    #endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */

    #if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
      /* @Trace: KeyM_SUD_FUNC_011 */
      /* Clear the data of all certificate  */
      for (indexCnt = KEYM_ZERO; indexCnt < KEYM_TOTAL_CERTIFICATE; indexCnt++)
      {
        ptrCert = &KeyM_CryptoCert[indexCnt];
        ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_AVAILABLE;
        KeyM_PrvMemClear(ptrCert->PtrCertData, ptrCert->CertMaxLength);
      }
    #endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

    /* @Trace: KeyM_SUD_FUNC_012 */
    SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
    /* Clear internal flags */
    KeyM_CurrentJob = KEYM_NO_JOB;
    KeyM_JobState = KEYM_COMPLETE;
    #if ((KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON) && \
      (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON))
      KeyM_CsmRequestDone = KEYM_FALSE;
    #endif
    /* Set module state to un-initialize */
    KeyM_ModuleState = KEYM_UNINIT;
    SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
    /* Clear internal buffer */
    KeyM_PrvMemClear(&KeyM_DataBuffer[KEYM_ZERO], KEYM_INTERAL_BUFFER_LENGTH);
  }

}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_GetVersionInfo                                   **
**                                                                            **
** Service ID         : 0x03                                                  **
**                                                                            **
** Description        : Provides the version information of this module.      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : VersionInfo                                           **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00407 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(void, KEYM_CODE) KeyM_GetVersionInfo(\
  P2VAR(Std_VersionInfoType, AUTOMATIC, KEYM_APPL_DATA) VersionInfo)
{

  /* check NULL pointer */
  if (NULL_PTR == VersionInfo)
  {
    /* @Trace: KeyM_SUD_FUNC_013 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      KEYM_REPORT_ERROR(KEYM_GETVERSIONINFO_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_014 */
    /* Load the vendor Id */
    VersionInfo->vendorID = KEYM_VENDOR_ID;
    /* Load the module Id */
    VersionInfo->moduleID = KEYM_MODULE_ID;
    /* Load Software Major Version */
    VersionInfo->sw_major_version = KEYM_SW_MAJOR_VERSION;
    /* Load Software Minor Version */
    VersionInfo->sw_minor_version = KEYM_SW_MINOR_VERSION;
    /* Load Software Patch Version */
    VersionInfo->sw_patch_version = KEYM_SW_PATCH_VERSION;
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_Start                                            **
**                                                                            **
** Service ID         : 0x04                                                  **
**                                                                            **
** Description        : This function is optional and used to allow key       **
**                      update operation.                                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : StartType, RequestData, RequestDataLength             **
**                                                                            **
** InOut parameter    : ResponseDataLength                                    **
**                                                                            **
** Output Parameters  : ResponseData                                          **
**                                                                            **
** Return parameter   : E_OK: Start operation successfully performed. Key     **
**                            update operations are now allowed.              **
**                      E_NOT_OK: Start operation not accepted.               **
**                      KEYM_E_PARAMETER_MISMATCH: Parameter do not match with**
**                                                 expected value.            **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Parameter size doesn't **
**                                                     match.                 **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_SessionState,                  **
**                      KeyM_StartOperationMode, KeyM_StartRequestDataLength, **
**                      KeyM_PtrStartResponseData, KeyM_PtrStartRequestData   **
**                      KeyM_PtrStartResponseDataLength, KeyM_StartDataBuffer **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvMemCmp, KeyM_KH_Start, Det_ReportError        **
**                      KeyM_PrvMemCopy                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_KeyM_00004 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
/* polyspace+10 MISRA-C3:8.13 [Justified:Low] "According AUTOSAR specification, type of pointer parameter must follow In/Out parameter type." */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Start(\
  VAR(KeyM_StartType, AUTOMATIC) StartType, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ResponseDataLength)
{
  Std_ReturnType retVal;
  boolean newSession;
  #if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
    uint16 responseDataLengthValue;
  #else
    /* These parameters are not used if the key handler is not enabled */
    (void)RequestData;
    (void)RequestDataLength;
    (void)ResponseData;
    (void)ResponseDataLength;
  #endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */
  retVal = E_NOT_OK;
  newSession = KEYM_FALSE;

  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_015 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_START_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  #if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
  else if ((NULL_PTR == RequestData) || (NULL_PTR == ResponseData) || \
    (NULL_PTR == ResponseDataLength))
  {
    /* @Trace: KeyM_SUD_FUNC_016 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case request data or
        response data or response data length pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_START_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (KEYM_ZERO == *ResponseDataLength)
  {
    /* @Trace: KeyM_SUD_FUNC_017 */
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case request data length or
      response data length is zero */
      KEYM_REPORT_ERROR(KEYM_START_SID, KEYM_E_SMALL_BUFFER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if ((KEYM_ZERO == RequestDataLength) || \
          (KEYM_INTERAL_BUFFER_LENGTH < RequestDataLength))
  {
    /* @Trace: KeyM_SUD_FUNC_018 */
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case request data length is bigger
        than KeyM internal buffer size */
      KEYM_REPORT_ERROR(KEYM_START_SID, KEYM_E_SMALL_BUFFER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  #endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */
  else
  {
    /* @Trace: KeyM_SUD_FUNC_019 */
    retVal = E_OK;

    if (KEYM_SESSION_ACTIVATED == KeyM_SessionState)
    {
      /* @Trace: KeyM_SUD_FUNC_021 */
      if ((KEYM_START_OEM_PRODUCTIONMODE == KeyM_StartOperationMode) && \
        (KEYM_START_WORKSHOPMODE == StartType))
      {
        /* The OEM production mode provides higher privileges compared
          to workshop mode, so return E_NOT_OK in this case */
        retVal = E_NOT_OK;
      }
      else
      {
        #if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
          if ((StartType == KeyM_StartOperationMode) && \
            (RequestDataLength == KeyM_StartRequestDataLength) && \
            (ResponseData == KeyM_PtrStartResponseData) && \
            (ResponseDataLength == KeyM_PtrStartResponseDataLength) && \
            (*ResponseDataLength == KeyM_StartResponseDataLength) && \
            (RequestData == KeyM_PtrStartRequestData))
          {
            retVal = KeyM_PrvMemCmp(RequestData, \
              &KeyM_StartDataBuffer[KEYM_ZERO], RequestDataLength);
          }
          else
          {
            retVal = E_NOT_OK;
          }
        #else
          KeyM_StartOperationMode = StartType;
        #endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */
      }
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_020 */
      newSession = KEYM_TRUE;
      KeyM_StartOperationMode = StartType;
    }

    /* @Trace: KeyM_SUD_FUNC_022 */
    if (KEYM_TRUE == newSession)
    {
      #if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
      /* Save previous response data length before call start handler */
      responseDataLengthValue = *ResponseDataLength;

      retVal = KeyM_KH_Start(StartType, RequestData, RequestDataLength, \
        ResponseData, ResponseDataLength);
      if (E_OK == retVal)
      #endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */
      {
        #if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
          KeyM_PtrStartRequestData = RequestData;
          KeyM_StartRequestDataLength = RequestDataLength;
          KeyM_PtrStartResponseData = ResponseData;
          KeyM_StartResponseDataLength = responseDataLengthValue;
          KeyM_PtrStartResponseDataLength = ResponseDataLength;
          (void)KeyM_PrvMemCopy(RequestData, \
            &KeyM_StartDataBuffer[KEYM_ZERO], RequestDataLength);
        #endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */

        KeyM_SessionState = KEYM_SESSION_ACTIVATED;
      } /* @if (E_OK == retVal) */
    } /* @if (KEYM_TRUE == newSession) */
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */

#if (KEYM_CRYPTO_KEY_PREPARE_FUNCTION_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_Prepare                                          **
**                                                                            **
** Service ID         : 0x05                                                  **
**                                                                            **
** Description        : This function is used to prepare a key update         **
**                      operation. The main intent is to provide information  **
**                      for the key operation to the key server.              **
**                      Other operations may start the negotiation for a      **
**                      common secret that is used further to derive key      **
**                      material                                              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : RequestData, RequestDataLength                        **
**                                                                            **
** InOut parameter    : ResponseDataLength                                    **
**                                                                            **
** Output Parameters  : ResponseData                                          **
**                                                                            **
** Return parameter   : E_OK: Service has been accepted and will be processed **
**                            internally. Results will be provided through    **
**                            a callback                                      **
**                      E_NOT_OK: Service not accepted due to an internal     **
**                                error                                       **
**                      KEYM_E_PARAMETER_MISMATCH: Parameter do not match with**
**                                                 expected value.            **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Parameter size doesn't **
**                                                     match.                 **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_SessionState                   **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_KH_Prepare, Det_ReportError                      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_KeyM_00004 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
/* polyspace+10 MISRA-C3:8.13 [Justified:Low] "According AUTOSAR specification, type of pointer parameter must follow In/Out parameter type." */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Prepare(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  uint16 RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ResponseDataLength)
{
  Std_ReturnType retVal;
  retVal = E_NOT_OK;
  #if (KEYM_CRYPTO_KEY_HANDLER_PREPARE_ENABLED == STD_OFF)
    /* These parameters are not used if the key handler is not enabled */
    (void)RequestData;
    (void)RequestDataLength;
    (void)ResponseData;
    (void)ResponseDataLength;
  #endif

  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_023 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_PREPARE_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  #if (KEYM_CRYPTO_KEY_HANDLER_PREPARE_ENABLED == STD_ON)
  else if ((NULL_PTR == RequestData) || (NULL_PTR == ResponseData) || \
    (NULL_PTR == ResponseDataLength))
  {
    /* @Trace: KeyM_SUD_FUNC_024 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case request data or
        response data or response data length pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_PREPARE_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (KEYM_ZERO == *ResponseDataLength)
  {
    /* @Trace: KeyM_SUD_FUNC_025 */
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case request data length or
        response data length is zero */
      KEYM_REPORT_ERROR(KEYM_PREPARE_SID, KEYM_E_SMALL_BUFFER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (KEYM_ZERO == RequestDataLength)
  {
    /* @Trace: KeyM_SUD_FUNC_026 */
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
  }
  #endif /* KEYM_CRYPTO_KEY_HANDLER_PREPARE_ENABLED == STD_ON */
  else
  {
    /* @Trace: KeyM_SUD_FUNC_027 */
    #if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
    if (KEYM_SESSION_ACTIVATED == KeyM_SessionState)
    #endif /*KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */
    {
      #if (KEYM_CRYPTO_KEY_HANDLER_PREPARE_ENABLED == STD_ON)
      retVal = KeyM_KH_Prepare(RequestData, RequestDataLength, \
        ResponseData, ResponseDataLength);
      #endif /* KEYM_CRYPTO_KEY_HANDLER_PREPARE_ENABLED == STD_ON */
    }
    #if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
    else
    {
      /* Return E_NOT_OK if the update operation is requested when
        the session is not activated */
      retVal = E_NOT_OK;
    } /* @if (KEYM_SESSION_ACTIVATED == KeyM_SessionState) */
    #endif /*KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_PREPARE_FUNCTION_ENABLED == STD_ON */

/*******************************************************************************
** Function Name      : KeyM_Update                                           **
**                                                                            **
** Service ID         : 0x06                                                  **
**                                                                            **
** Description        : This function is used to initiate the key generation  **
**                      or update process                                     **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : KeyNamePtr, KeyNameLength, RequestDataPtr             **
**                      RequestDataLength, ResultDataMaxLength                **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ResultDataPtr                                         **
**                                                                            **
** Return parameter   : E_OK: Start operation successfully performed. Key     **
**                            update operations are now allowed.              **
**                      E_NOT_OK: Start operation not accepted.               **
**                      KEYM_E_BUSY: Service could not be accepted because    **
**                                   another operation is already ongoing.    **
**                      KEYM_E_PARAMETER_MISMATCH: Parameter do not match with**
**                                                 expected value.            **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Parameter size doesn't **
**                                                     match.                 **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_SessionState,                  **
**                      KeyM_CryptoKey, KeyM_KeyId, KeyM_CurrentJob,          **
**                      KeyM_JobState, KeyM_OperationResult,                  **
**                      KeyM_PtrRequestData, KeyM_RequestDataLength,          **
**                      KeyM_PtrResultData, KeyM_ResultDataMaxLength,         **
**                      KeyM_PtrKeyName, KeyM_KeyNameLength,                  **
**                      KeyM_DataBufferLength, KeyM_BackGroundDone,           **
**                      KeyM_HandlerUpdateOperation                           **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvGetKeyIndexByName, Det_ReportError            **
**                      KeyM_PrvGetKeyIndexByExtractedSHEKeyId                **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_CryptoStack_00107 SRS_CryptoStack_00109 SRS_CryptoStack_00110
SRS_CryptoStack_00118 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Update(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) KeyNamePtr, \
  VAR(uint16, AUTOMATIC) KeyNameLength, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestDataPtr, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResultDataPtr, \
  VAR(uint16, AUTOMATIC) ResultDataMaxLength)
{
  Std_ReturnType retVal;
  #if (KEYM_CRYPTO_KEY_ADDITIONAL_HINT_ENABLED == STD_ON)
    uint8 extractedSHEKeyId;
  #endif
  retVal = E_NOT_OK;

  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_028 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_UPDATE_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (NULL_PTR == RequestDataPtr)
  {
    /* @Trace: KeyM_SUD_FUNC_029 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case request data pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_UPDATE_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
  else if (NULL_PTR == ResultDataPtr)
  {
    /* @Trace: KeyM_SUD_FUNC_030 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case response data pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_UPDATE_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (KEYM_INTERAL_BUFFER_LENGTH < ResultDataMaxLength)
  {
    /* @Trace: KeyM_SUD_FUNC_031 */
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case response data length is bigger than
        KeyM internal buffer size */
      KEYM_REPORT_ERROR(KEYM_UPDATE_SID, KEYM_E_SMALL_BUFFER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  #endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON */
  else if (KEYM_ZERO == RequestDataLength)
  {
    /* @Trace: KeyM_SUD_FUNC_032 */
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_033 */
    #if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
    /* Check if the update sesstion is activated */
    if (KEYM_SESSION_ACTIVATED == KeyM_SessionState)
    #endif /*KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */
    {
      if (KEYM_BUSY == KeyM_ModuleState)
      {
        /* @Trace: KeyM_SUD_FUNC_034 */
        retVal = KEYM_E_BUSY;
      }
      else
      {
        if ((KEYM_ZERO < KeyNameLength) && (NULL_PTR != KeyNamePtr))
        {
          /* @Trace: KeyM_SUD_FUNC_035 */
          /* Get the key which has the name of KeyNamePtr */
          retVal = KeyM_PrvGetKeyIndexByName(&KeyM_CryptoKey[KEYM_ZERO], \
            KEYM_TOTAL_KEY, KeyNamePtr, \
            KeyNameLength, &KeyM_KeyId);
        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_036 */
          #if (KEYM_CRYPTO_KEY_ADDITIONAL_HINT_ENABLED == STD_ON)
            /* When KeyNamePtr is not valid or KeyNameLength is 0, \
              the Key Manager shall interpret the RequestData as M1M2M3 values
              of a SHE key */
            if (KEYM_M1M2M3_LENGTH_IN_BYTE <= RequestDataLength)
            {
              /* KeyId is extracted from bits 121..124 located in RequestDataPtr
                These bits are upper 4 bits of
                the fifth byte of RequestDataPtr */
              extractedSHEKeyId = \
                (RequestDataPtr[KEYM_M1M2M3_BYTE_POSITION_OF_KEYID] & \
                KEYM_M1M2M3_KEYID_BIT_MASK) >> KEYM_M1M2M3_KEYID_BIT_SHIFT;
              /* Get the key has keyCryptoProps value which match
                extractedSHEKeyId value */
              retVal = KeyM_PrvGetKeyIndexByExtractedSHEKeyId(\
                &KeyM_CryptoKey[KEYM_ZERO], \
                KEYM_TOTAL_KEY, extractedSHEKeyId, &KeyM_KeyId);
            }
            else
            {
              retVal = KEYM_E_PARAMETER_MISMATCH;
            }
          #endif /* #if (KEYM_CRYPTO_KEY_ADDITIONAL_HINT_ENABLED == STD_ON) */
        } /* @if ((KeyNameLength > KEYM_ZERO) && (NULL_PTR != KeyNamePtr)) */

        /* @Trace: KeyM_SUD_FUNC_037 */
        if (E_OK == retVal)
        {
          #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_OFF)
            if (KeyM_CryptoKey[KeyM_KeyId].KeyMaxLength < RequestDataLength)
            {
              retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
            }
          #endif
        }
        else
        {
          #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
            KeyM_KeyId = KEYM_INVALID_KEYID;
            retVal = E_OK;
          #else
            retVal = KEYM_E_PARAMETER_MISMATCH;
          #endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON */
        } /* @if (E_OK == retVal) */

        #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_OFF)
        if (E_OK == retVal)
        #endif
        {
          /* @Trace: KeyM_SUD_FUNC_038 */
          SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
          /* Update module state */
          KeyM_ModuleState = KEYM_BUSY;
          /* Update current job name */
          KeyM_CurrentJob = KEYM_UPDATE_JOB;
          /* Update job state */
          KeyM_JobState = KEYM_REQUEST_JOB;
          /* Key Operation result is NOT OK by default */
          KeyM_OperationResult = KEYM_RT_NOT_OK;
          SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
          /* Update internal buffer of key operation, these buffer
            shall be used in the main function */
          /* polyspace-begin MISRA-C3:18.6 [Justified:Low] 
             "Some global data(longer life-time var) is assiged with RequestDataPtr and ResultDataPtr parameters. 
             This API is not invoked while running Crypto stack only, so these parameters are considered to be shorter life-time vars.
             There is no race condition problem." */
          KeyM_PtrRequestData = RequestDataPtr;
          KeyM_RequestDataLength = RequestDataLength;
          KeyM_PtrResultData = ResultDataPtr;
          KeyM_ResultDataMaxLength = ResultDataMaxLength;
          /* polyspace-end MISRA-C3:18.6*/
        }

        #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
          /* Update buffers of key operation, these buffers shall be
            used in the main or main background function */
          KeyM_PtrKeyName = KeyNamePtr;
          KeyM_KeyNameLength = KeyNameLength;
          KeyM_DataBufferLength = ResultDataMaxLength;
          KeyM_BackGroundDone = KEYM_FALSE;
          KeyM_HandlerUpdateOperation = KEYM_KH_UPDATE_KEY_UPDATE_REPEAT;
        #endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON */
      } /* @if (KEYM_BUSY == KeyM_ModuleState) */
    }
    #if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
    else
    {
      /* Return E_NOT_OK if the update operation is requested when
        the session is not activated */
      retVal = E_NOT_OK;
    } /* @if (KEYM_SESSION_ACTIVATED == KeyM_SessionState) */
    #endif /*KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_Finalize                                         **
**                                                                            **
** Service ID         : 0x07                                                  **
**                                                                            **
** Description        : The function is used to finalize key update           **
**                      operations. It is typically used in conjunction with  **
**                      the KeyM_Start operation and returns the key operation**
**                      into the idle mode. Further key prepare or update     **
**                      operations are not accepted until a new KeyM_Start    **
**                      operation has been initialized.                       **
**                      In addition, updated key material will be persisted   **
**                      and set into valid state.                             **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : RequestDataPtr, RequestDataLength                     **
**                                                                            **
** InOut parameter    : ResponseMaxDataLength                                 **
**                                                                            **
** Output Parameters  : ResponseDataPtr                                       **
**                                                                            **
** Return parameter   : E_OK: Operation has been accepted and will be         **
**                            processed internally. Results will be provided  **
**                            through a callback                              **
**                      E_NOT_OK: Start operation not accepted.               **
**                      KEYM_E_BUSY: Service could not be accepted because    **
**                                   another operation is already ongoing     **
**                      KEYM_E_PARAMETER_MISMATCH: Parameter do not match with**
**                                                 expected value.            **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Parameter size doesn't **
**                                                     match.                 **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_SessionState, KeyM_CurrentJob, **
**                      KeyM_OperationResult, KeyM_PtrRequestData,            **
**                      KeyM_RequestDataLength, KeyM_PtrResultData,           **
**                      KeyM_ResultDataMaxLength, KeyM_BackGroundDone         **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_KeyM_00004 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
/* polyspace+10 MISRA-C3:8.13 [Justified:Low] "According AUTOSAR specification, type of pointer parameter must follow In/Out parameter type." */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Finalize(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestDataPtr, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseDataPtr, \
  VAR(uint16, AUTOMATIC) ResponseMaxDataLength)
{
  Std_ReturnType retVal;

  retVal = E_NOT_OK;

  #if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_OFF)
    (void)RequestDataPtr;
    (void)RequestDataLength;
    (void)ResponseDataPtr;
    (void)ResponseMaxDataLength;
  #endif

  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_039 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_FINALIZE_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  #if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
  else if ((NULL_PTR == RequestDataPtr) || (NULL_PTR == ResponseDataPtr))
  {
    /* @Trace: KeyM_SUD_FUNC_040 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case request data or response data
        pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_FINALIZE_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (KEYM_ZERO == ResponseMaxDataLength)
  {
    /* @Trace: KeyM_SUD_FUNC_041 */
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case response data length is bigger than
        KeyM internal buffer size */
      KEYM_REPORT_ERROR(KEYM_FINALIZE_SID, KEYM_E_SMALL_BUFFER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (KEYM_ZERO == RequestDataLength)
  {
    /* @Trace: KeyM_SUD_FUNC_042 */
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
  }
  #endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */
  else
  {
    /* @Trace: KeyM_SUD_FUNC_043 */
    retVal = E_OK;

    /* Check if the update sesstion is activated */
    if (KEYM_SESSION_ACTIVATED == KeyM_SessionState)
    {
      if (KEYM_BUSY == KeyM_ModuleState)
      {
        retVal = KEYM_E_BUSY;
      }
      else
      {
        SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
        /* Update module state */
        KeyM_ModuleState = KEYM_BUSY;
        SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
        /* Update current job name */
        KeyM_CurrentJob = KEYM_FINALIZE_JOB;
        /* Key Operation result is NOT OK by default */
        KeyM_OperationResult = KEYM_RT_NOT_OK;
        #if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
          KeyM_BackGroundDone = KEYM_FALSE;
          /* Update internal buffer of key operation, these buffer shall
            be used in the main function */
          KeyM_PtrRequestData = RequestDataPtr;
          KeyM_RequestDataLength = RequestDataLength;
          KeyM_PtrResultData = ResponseDataPtr;
          KeyM_ResultDataMaxLength = ResponseMaxDataLength;
        #endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */
      } /* @if (KEYM_BUSY == KeyM_ModuleState) */
    }
    else
    {
      /* Return E_NOT_OK if the update operation is requested when
        the session is not activated */
      retVal = E_NOT_OK;
    } /* @if (KEYM_SESSION_ACTIVATED == KeyM_SessionState) */

  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */

#if (KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_Verify                                           **
**                                                                            **
** Service ID         : 0x08                                                  **
**                                                                            **
** Description        : The key server requests to verify the provided keys.  **
**                      The key manager performs operation on the assigned    **
**                      job and returns the result to the key server who      **
**                      verifies if the results was provided with this key    **
**                      as expected                                           **
**                                                                            **
** Sync/Async         : Synchronous/Asynchronous                              **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : KeyNamePtr, KeyNameLength, RequestData,               **
**                      RequestDataLength                                     **
**                                                                            **
** InOut Parameters   : ResultDataPtr                                         **
**                                                                            **
** Output Parameters  : ResponseDataPtr                                       **
**                                                                            **
** Return parameter   : KEYM_E_PENDING: Operation runs in asynchronous mode,  **
**                                      has been accepted and will be         **
**                                      processed internally. Results will be **
**                                      provided through callback             **
**                      E_OK: Start operation successfully performed. Key     **
**                            update operations are now allowed.              **
**                      E_NOT_OK: Start operation not accepted.               **
**                      E_BUSY: Service could not be accepted because another **
**                              operation is already ongoing. Try next time   **
**                      KEYM_E_PARAMETER_MISMATCH: Parameter do not match with**
**                                                 expected value.            **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Parameter size doesn't **
**                                                     match.                 **
**                      KEYM_E_KEY_CERT_INVALID: Key operation cannot be      **
**                                               performed because the key    **
**                                               name is invalid.             **
**                      KEYM_E_KEY_CERT_EMPTY: The key for this slot has      **
**                                             not been set.                  **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_SessionState,                  **
**                      KeyM_CryptoKey, KeyM_KeyId, KeyM_CurrentJob,          **
**                      KeyM_JobState, KeyM_OperationResult,                  **
**                      KeyM_PtrRequestData, KeyM_RequestDataLength,          **
**                      KeyM_PtrResultData, KeyM_ResultDataMaxLength,         **
**                      KeyM_PtrKeyName, KeyM_KeyNameLength,                  **
**                      KeyM_BackGroundDone, KeyM_CsmRequestDone,             **
**                      KeyM_CsmRequestResult                                 **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvGetKeyIndexByName, Det_ReportError            **
**                      KeyM_PrvPerformVerifyOperation, KeyM_KH_Verify        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_CryptoStack_00119 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Verify(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) KeyNamePtr, \
  VAR(uint16, AUTOMATIC) KeyNameLength, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ResponseDataLength)
{
  Std_ReturnType retVal;
  uint16 keyIdent;
  P2VAR(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_DATA) ptrKey;
  #if (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_OFF)
  #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF)
    boolean csmAsyncJob;
  #endif /* KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF */
  #endif /* KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_OFF */

  retVal = E_NOT_OK;
  keyIdent = 0u;

  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_044 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_VERIFY_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if ((NULL_PTR == RequestData) || (NULL_PTR == ResponseData) || \
    (NULL_PTR == ResponseDataLength) || (NULL_PTR == KeyNamePtr))
  {
    /* @Trace: KeyM_SUD_FUNC_045 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case parameter is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_VERIFY_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (KEYM_ZERO == *ResponseDataLength)
  {
    /* @Trace: KeyM_SUD_FUNC_046 */
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case response data length is bigger than
        KeyM internal buffer size */
      KEYM_REPORT_ERROR(KEYM_VERIFY_SID, KEYM_E_SMALL_BUFFER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (KEYM_ZERO == RequestDataLength)
  {
    /* @Trace: KeyM_SUD_FUNC_047 */
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
  }
  else if (KEYM_ZERO == KeyNameLength)
  {
    /* @Trace: KeyM_SUD_FUNC_048 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
  }
  else
  {
    #if (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON)
    if (KEYM_BUSY == KeyM_ModuleState)
    {
      /* @Trace: KeyM_SUD_FUNC_049 */
      retVal = KEYM_E_BUSY;
    }
    else
    #endif /* (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON) */
    {
      /* Get the key which has the name of KeyNamePtr */
      retVal = KeyM_PrvGetKeyIndexByName(&KeyM_CryptoKey[KEYM_ZERO], \
        KEYM_TOTAL_KEY, KeyNamePtr, KeyNameLength, &keyIdent);

      if (E_OK == retVal)
      {
        ptrKey = &KeyM_CryptoKey[keyIdent];
        if (KEYM_ZERO == ptrKey->KeyState)
        {
          /* @Trace: KeyM_SUD_FUNC_051 */
          retVal = KEYM_E_KEY_CERT_EMPTY;
        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_052 */
          #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF)
            KeyM_VerifyRespondDataLength = *ResponseDataLength;
          #endif /* (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF) */

          #if (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_OFF)
          #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF)
            /* If the verify operation is synchronous, the CSM job
              must be synchronous job also */
            csmAsyncJob = ptrKey->CsmVerifyJob.AsyncJob;

            if (KEYM_FALSE == csmAsyncJob)
            {
              retVal = KeyM_PrvPerformVerifyOperation(ptrKey, RequestData, \
                RequestDataLength, ResponseData, ResponseDataLength);
              /* Process return value of Csm services */
              switch(retVal)
              {
                case E_OK:
                case E_NOT_OK:
                  break;
                case CRYPTO_E_BUSY:
                  retVal = E_NOT_OK;
                  break;
                case CRYPTO_E_KEY_NOT_VALID:
                  retVal = KEYM_E_KEY_CERT_INVALID;
                  break;
                case CRYPTO_E_KEY_SIZE_MISMATCH:
                  retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
                  break;
                case CRYPTO_E_KEY_EMPTY:
                  retVal = KEYM_E_KEY_CERT_EMPTY;
                  break;
                default:
                  /* Do nothing */
                  break;
              }
            }
            else
            {
              retVal = E_NOT_OK;
            }
          #else
            retVal = KeyM_KH_Verify(KeyNamePtr, KeyNameLength, \
              RequestData, RequestDataLength, \
              ResponseData, ResponseDataLength);
          #endif /* KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF */
          #endif /* KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_OFF */

          #if (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON)
            /* @Trace: KeyM_SUD_FUNC_053 */
            SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
            /* Update module state */
            KeyM_ModuleState = KEYM_BUSY;
            SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
            /* Update current job name */
            KeyM_CurrentJob = KEYM_VERIFY_JOB;
            /* Update job state */
            KeyM_JobState = KEYM_REQUEST_JOB;
            /* Key Operation result is NOT OK by default */
            KeyM_OperationResult = KEYM_RT_NOT_OK;
            /* Csm request status is not done by default */
            KeyM_CsmRequestDone = KEYM_FALSE;
            /* Csm request result is NOT OK by default */
            KeyM_CsmRequestResult = E_NOT_OK;
            /* Update internal buffer of key operation, this buffer shall
            be used in the main background function */
            /* polyspace-begin MISRA-C3:18.6 [Justified:Low] 
              "Some global data(longer life-time var) is assiged with ResponseData and RequestData parameters. 
              This API is not invoked while running Crypto stack only, so these parameters are considered to be shorter life-time vars.
              There is no race condition problem." */
            KeyM_PtrResultData = ResponseData;
            KeyM_PtrResultDataLength = ResponseDataLength;
            KeyM_PtrRequestData = RequestData;
            KeyM_RequestDataLength = RequestDataLength;
            /* polyspace-end MISRA-C3:18.6*/
            KeyM_KeyId = keyIdent;
            #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON)
              KeyM_PtrKeyName = KeyNamePtr;
              KeyM_KeyNameLength = KeyNameLength;
              /* Background task status is not done by default */
              KeyM_BackGroundDone = KEYM_FALSE;
            #endif /* KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON */
            retVal = KEYM_E_PENDING;
          #endif /* KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON */
        }
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_050 */
        retVal = KEYM_E_KEY_CERT_INVALID;
      } /* @if (keyFound == KEYM_TRUE) */
    } /* @if (KEYM_BUSY == KeyM_ModuleState) */
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON */

#endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */

#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_ServiceCertificate                               **
**                                                                            **
** Service ID         : 0x09                                                  **
**                                                                            **
** Description        : This function is used to request certificate operation**
**                      from the key client.The type of operation is specified**
**                      in the first parameter KeyM_ServiceCertificateType.   **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : Service, CertNamePtr, CertNameLength, RequestData,    **
**                      RequestDataLength, ResponseDataLength                 **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ResponseData                                          **
**                                                                            **
** Return parameter   : E_OK: Service data operation successfully accepted    **
**                      E_NOT_OK: Operation not accepted due to an internal   **
**                                error.                                      **
**                      KEYM_E_PARAMETER_MISMATCH: Parameter do not match with**
**                                                 expected value.            **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Parameter size doesn't **
**                                                     match.                 **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_SessionState,                  **
**                      KeyM_CryptoCert, KeyM_CertId, KeyM_CurrentJob,        **
**                      KeyM_JobState, KeyM_OperationResult,                  **
**                      KeyM_PtrRequestData, KeyM_RequestDataLength,          **
**                      KeyM_PtrResultData, KeyM_ResultDataMaxLength,         **
**                      KeyM_PtrCertName, KeyM_CertNameLength,                **
**                      KeyM_BackGroundDone, KeyM_CertService                 **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError, KeyM_PrvMemCmp                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_KeyM_00003 SRS_CryptoStack_00031 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_ServiceCertificate(\
  VAR(KeyM_ServiceCertificateType, AUTOMATIC) Service, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) CertNamePtr, \
  VAR(uint16, AUTOMATIC) CertNameLength, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseData, \
  VAR(uint16, AUTOMATIC) ResponseDataLength)
{
  Std_ReturnType retVal;
  uint16 certIdent;
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  #if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
    uint16 certLen;
  #endif

  retVal = E_NOT_OK;

  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_055 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_SERVICECERTIFICATE_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if ((NULL_PTR == RequestData) || (NULL_PTR == CertNamePtr))
  {
    /* @Trace: KeyM_SUD_FUNC_056 SRS_BSW_00377 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case request data pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_SERVICECERTIFICATE_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if ((KEYM_ZERO == RequestDataLength) || (KEYM_ZERO == CertNameLength))
  {
    /* @Trace: KeyM_SUD_FUNC_057 */
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
  }
  else if ((NULL_PTR == ResponseData)
    #if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
      && (KEYM_SERVICE_CERT_REQUEST_CSR == Service)
    #endif
  )
  {
    /* @Trace: KeyM_SUD_FUNC_058 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case request data pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_SERVICECERTIFICATE_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if ((KEYM_ZERO == ResponseDataLength)
    #if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
      && (KEYM_SERVICE_CERT_REQUEST_CSR == Service)
    #endif
  )
  {
    /* @Trace: KeyM_SUD_FUNC_059 */
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case request data pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_SERVICECERTIFICATE_SID, KEYM_E_SMALL_BUFFER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    #if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
    /* Check if the update session is activated */
    if (KEYM_SESSION_ACTIVATED == KeyM_SessionState)
    #endif /*KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */
    {
      if (KEYM_BUSY == KeyM_ModuleState)
      {
        /* @Trace: KeyM_SUD_FUNC_061 SRS_BSW_00377 */
        retVal = KEYM_E_BUSY;
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_062 */
        /* Get the certificate which has the name of CertNamePtr */
        for (certIdent = 0u; KEYM_TOTAL_CERTIFICATE > certIdent; certIdent++)
        {
          ptrCert = &KeyM_CryptoCert[certIdent];
          if (CertNameLength == ptrCert->CertNameLength)
          {
            retVal = KeyM_PrvMemCmp(CertNamePtr, ptrCert->PtrCertName, \
              CertNameLength);
            if (E_OK == retVal)
            {
              break;
            }
          }
        }

        if (E_OK == retVal)
        {
          /* @Trace: KeyM_SUD_FUNC_063 */
          #if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)

          if (KEYM_STORAGE_IN_NVM != ptrCert->CertStorageType)
          {
            certLen = ptrCert->CertMaxLength;
          }
          else
          {
            /*
             * The certificate data must be not bigger than the cert buffer
             * length minus 3, because if the certificate is stored to NVM,
             * the last 3 bytes of buffer shall be used to store state and
             * length of certificate. The rest of buffer shall be used to
             * store certificate data
             */
            certLen = ptrCert->CertMaxLength - 3u;
          }

          if (RequestDataLength > certLen)
          {
            retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
          }
          else
          #endif /* KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED ==
            STD_OFF */
          {
            SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
            /* Update module state */
            KeyM_ModuleState = KEYM_BUSY;
            SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
            /* Update current job name */
            KeyM_CurrentJob = KEYM_SERVICE_CERTIFICATE_JOB;
            /* Update job state */
            KeyM_JobState = KEYM_REQUEST_JOB;
            /* Background task status is not done by default */
            KeyM_BackGroundDone = KEYM_FALSE;
            /* Save the input parameters which are passes to the handler in the
              main function */
            #if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_ON)
              KeyM_PtrCertName = CertNamePtr;
              KeyM_CertNameLength = CertNameLength;
            #endif /* KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED ==
              STD_ON */
            /* polyspace-begin MISRA-C3:18.6 [Justified:Low] 
              "Some global data(longer life-time var) is assiged with ResponseData and RequestData parameters. 
              This API is not invoked while running Crypto stack only, so these parameters are considered to be shorter life-time vars.
              There is no race condition problem." */
            KeyM_PtrResultData = ResponseData;
            KeyM_ResultDataMaxLength = ResponseDataLength;
            KeyM_PtrRequestData = RequestData;
            KeyM_RequestDataLength = RequestDataLength;
            /* polyspace-end MISRA-C3:18.6*/
            KeyM_CertService = Service;
            KeyM_CertId = certIdent;
            /* Key Operation result is NOT OK by default */
            KeyM_OperationResult = KEYM_RT_NOT_OK;
            #if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
              /* The certificate is in progress */
              ptrCert->InProgress = KEYM_ONE;
            #endif /* KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED ==
              STD_OFF */
          }
        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_064 */
          retVal = KEYM_E_PARAMETER_MISMATCH;
        } /* @if (E_OK == retVal) */
      } /* @if (KEYM_BUSY == KeyM_ModuleState) */
    }
    #if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
    else
    {
      /* @Trace: KeyM_SUD_FUNC_060 */
      /* Return E_NOT_OK if the update operation is requested when
        the session is not activated */
      retVal = E_NOT_OK;
    } /* @if (KEYM_SESSION_ACTIVATED == KeyM_SessionState) */
    #endif /*KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON */

/*******************************************************************************
** Function Name      : KeyM_SetCertificate                                   **
**                                                                            **
** Service ID         : 0x0a                                                  **
**                                                                            **
** Description        : This function provides the certificate data to the key**
**                      management module to temporarily store the certificate**
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : CertId, CertificateDataPtr                            **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Certificate accepted                            **
**                      E_NOT_OK: Certificate could not be set                **
**                      KEYM_E_PARAMETER_MISMATCH: Parameter do not match with**
**                                                 expected value.            **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Parameter size doesn't **
**                                                     match.                 **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoCert                     **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError, KeyM_PrvMemCopy                      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_KeyM_00003 SRS_BSW_00337 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_SetCertificate(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  P2CONST(KeyM_CertDataType, AUTOMATIC, KEYM_APPL_CONST) CertificateDataPtr)
{
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  Std_ReturnType retVal;
  retVal = E_NOT_OK;

  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_066 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_SETCERTIFICATE_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (NULL_PTR == CertificateDataPtr)
  {
    /* @Trace: KeyM_SUD_FUNC_067 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case request data pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_SETCERTIFICATE_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    retVal = E_OK;

    if (KEYM_TOTAL_CERTIFICATE > CertId)
    {
      ptrCert = &KeyM_CryptoCert[CertId];

      if (1U == ptrCert->InProgress)
      {
        /* @Trace: KeyM_SUD_FUNC_069 */
        /* The certificate is in progress, so return NOT OK in this case */
        retVal = E_NOT_OK;
      }
      else if (0U == CertificateDataPtr->certDataLength)
      {
        /* @Trace: KeyM_SUD_FUNC_070 */
        /* Reset certificate status if the length information is 0 */
        ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_AVAILABLE;
      }
      else if (CertificateDataPtr->certDataLength > ptrCert->CertMaxLength)
      {
        /* @Trace: KeyM_SUD_FUNC_071 */
        retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
      }
      else if (NULL_PTR == CertificateDataPtr->certData)
      {
        /* @Trace: KeyM_SUD_FUNC_072 SRS_BSW_00377 */
        retVal = KEYM_E_PARAMETER_MISMATCH;
        #if (KEYM_DEV_ERROR_DETECT == STD_ON)
          /* Report error to Det in case CertificateDataPtr
            pointer is NULL_PTR */
          KEYM_REPORT_ERROR(KEYM_SETCERTIFICATE_SID, KEYM_E_PARAM_POINTER);
        #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
      }
      else if ((KEYM_STORAGE_IN_CSM == ptrCert->CertStorageType) || \
        (KEYM_STORAGE_IN_NVM == ptrCert->CertStorageType))
      {
        /* @Trace: KeyM_SUD_FUNC_073 */
        retVal = KEYM_E_PARAMETER_MISMATCH;
        #if (KEYM_DEV_ERROR_DETECT == STD_ON)
          /* Report error to Det in case CertificateDataPtr
            pointer is NULL_PTR */
          KEYM_REPORT_ERROR(KEYM_SETCERTIFICATE_SID, KEYM_E_CONFIG_FAILURE);
        #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_074 */
        /* Store information of certificate to buffer */
        ptrCert->CertLength = (uint16)CertificateDataPtr->certDataLength;
        (void)KeyM_PrvMemCopy(CertificateDataPtr->certData, \
          ptrCert->PtrCertData, CertificateDataPtr->certDataLength);
        /* Update certificate status to NOT PARSED */
        ptrCert->CertStatus = KEYM_CERTIFICATE_NOT_PARSED;
      } /* @if (0U == CertificateDataPtr->certDataLength) */
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_068 */
      retVal = KEYM_E_PARAMETER_MISMATCH;
    } /* @if (retVal = E_OK) */
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_GetCertificate                                   **
**                                                                            **
** Service ID         : 0x0b                                                  **
**                                                                            **
** Description        : This function provides the certificate data           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : CertId                                                **
**                                                                            **
** InOut parameter    : CertificateDataPtr                                    **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Certificate data available and provided.        **
**                      E_NOT_OK: Operation not accepted due to an internal   **
**                                error.                                      **
**                      KEYM_E_PARAMETER_MISMATCH: Certificate ID invalid     **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Provided buffer for    **
**                                                     the certificate too    **
**                                                     small.                 **
**                      KEYM_E_KEY_CERT_EMPTY: No certificate data available, **
**                                             the certificate slot is empty  **
**                      KEYM_E_KEY_CERT_READ_FAIL: Certificate cannot be      **
**                                                 provided, access denied    **
**                                                                            **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoCert                     **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError, KeyM_PrvMemCopy                      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_KeyM_00003 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_GetCertificate(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  P2VAR(KeyM_CertDataType, AUTOMATIC, KEYM_APPL_DATA) CertificateDataPtr)
{
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  Std_ReturnType retVal;
  retVal = E_NOT_OK;

  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_075 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_GETCERTIFICATE_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (NULL_PTR == CertificateDataPtr)
  {
    /* @Trace: KeyM_SUD_FUNC_076 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case request data pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_GETCERTIFICATE_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (NULL_PTR == CertificateDataPtr->certData)
  {
    /* @Trace: KeyM_SUD_FUNC_077 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case output buffer pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_GETCERTIFICATE_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    if (KEYM_TOTAL_CERTIFICATE > CertId)
    {
      ptrCert = &KeyM_CryptoCert[CertId];

      if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus)
      {
        /* @Trace: KeyM_SUD_FUNC_079 */
        retVal = KEYM_E_KEY_CERT_EMPTY;
      }
      else if (ptrCert->CertLength > CertificateDataPtr->certDataLength)
      {
        /* @Trace: KeyM_SUD_FUNC_080 */
        retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;

        #if (KEYM_DEV_ERROR_DETECT == STD_ON)
          /* Report error to Det in case output buffer length is not enough */
          KEYM_REPORT_ERROR(KEYM_GETCERTIFICATE_SID, KEYM_E_SMALL_BUFFER);
        #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_081 */
        /* Copy certificate date to output buffer */
        (void)KeyM_PrvMemCopy(ptrCert->PtrCertData,\
          CertificateDataPtr->certData, ptrCert->CertLength);
        /* Adjusts the size of data */
        CertificateDataPtr->certDataLength = ptrCert->CertLength;

        retVal = E_OK;
      }
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_078 */
      retVal = KEYM_E_PARAMETER_MISMATCH;
    } /* @if (E_OK == retVal) */
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_VerifyCertificates                               **
**                                                                            **
** Service ID         : 0x0c                                                  **
**                                                                            **
** Description        : This function verifies two certificates that are      **
**                      stored and parsed internally against each other. The  **
**                      certificate referenced with CertId was signed by the  **
**                      certificate referenced with certUpperId. Only these   **
**                      two certificates are validated against each other.    **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : CertId, CertUpperId                                   **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Certificate verification request accepted.      **
**                            Operation will be performed in the background   **
**                            and response is given through a callback.       **
**                      E_NOT_OK: Operation not accepted due to an internal   **
**                                error.                                      **
**                      KEYM_E_BUSY:Validation cannot be performed yet. KeyM  **
**                                  is currently busy with other jobs         **
**                      KEYM_E_PARAMETER_MISMATCH: Certificate ID invalid     **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Provided buffer for    **
**                                                     the certificate too    **
**                                                     small.                 **
**                      KEYM_E_KEY_CERT_EMPTY: No certificate data available, **
**                                             the certificate slot is empty  **
**                      KEYM_E_CERT_INVALID_CHAIN_OF_TRUST: An upper cert is  **
**                                                          not valid         **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoCert, KeyM_CurrentJob,   **
**                      KeyM_JobState, KeyM_OperationResult, KeyM_CertId,     **
**                      KeyM_BackGroundDone, KeyM_UpperCertId                 **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_CryptoStack_00111 SRS_CryptoStack_00031 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_VerifyCertificates(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertUpperId)
{
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrUpperCert;
  Std_ReturnType retVal;

  retVal = E_NOT_OK;

   /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_082 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_VERIFYCERTIFICATES_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    retVal = E_OK;

    if (KEYM_BUSY == KeyM_ModuleState)
    {
      /* @Trace: KeyM_SUD_FUNC_083 */
      retVal = KEYM_E_BUSY;
    }
    else
    {
      if ((KEYM_TOTAL_CERTIFICATE > CertId) && \
        (KEYM_TOTAL_CERTIFICATE > CertUpperId))
      {
        /* Get the pointer to both certificates */
        ptrCert = &KeyM_CryptoCert[CertId];
        ptrUpperCert = &KeyM_CryptoCert[CertUpperId];

        if ((KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus) || \
          (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrUpperCert->CertStatus))
        {
          /* @Trace: KeyM_SUD_FUNC_085 */
          retVal = KEYM_E_KEY_CERT_EMPTY;
        }
        else if (KEYM_CERTIFICATE_VALID != ptrUpperCert->CertStatus)
        {
          /* @Trace: KeyM_SUD_FUNC_086 */
          retVal = KEYM_E_CERT_INVALID_CHAIN_OF_TRUST;
        }
        else if ((KEYM_E_CERTIFICATE_INVALID_TYPE == ptrCert->CertStatus) || \
          (KEYM_E_CERTIFICATE_INVALID_FORMAT == ptrCert->CertStatus))
        {
          /* @Trace: KeyM_SUD_FUNC_087 */
          /* The certificate can not be verified if parsing fail */
          retVal = E_NOT_OK;
        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_088 */
          SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
          /* Update module state */
          KeyM_ModuleState = KEYM_BUSY;
          SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
          /* Update current job name */
          KeyM_CurrentJob = KEYM_VERIFY_CERTIFICATES_JOB;
          /* Update job state */
          KeyM_JobState = KEYM_REQUEST_JOB;
          /* Key Operation result is NOT OK by default */
          KeyM_OperationResult = KEYM_RT_NOT_OK;
          /* Background task status is not done by default */
          KeyM_BackGroundDone = KEYM_FALSE;
          /* Hold the id of certificates to use in the main function */
          KeyM_CertId = CertId;
          KeyM_UpperCertId = CertUpperId;
          /* The certificate is in progress */
          ptrCert->InProgress = KEYM_ONE;
        } /* @if ((KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus) || \
          (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrUpperCert->CertStatus)) */
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_084 */
        retVal = KEYM_E_PARAMETER_MISMATCH;
      } /* @if ((KEYM_TOTAL_CERTIFICATE > CertId) && \
          (CertUpperId < KEYM_TOTAL_CERTIFICATE)) */
    } /* @if (KEYM_BUSY == KeyM_ModuleState) */
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_VerifyCertificate                                **
**                                                                            **
** Service ID         : 0x0d                                                  **
**                                                                            **
** Description        : This function verifies a certificate that was         **
**                      previously provided with KeyM_SetCertificate() against**
**                      already stored and provided certificates stored with  **
**                      other certificate IDs.                                **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : CertId                                                **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Certificate verification request accepted.      **
**                            Operation will be performed in the background   **
**                            and response is given through a callback.       **
**                      E_NOT_OK: Operation not accepted due to an internal   **
**                                error.                                      **
**                      KEYM_E_BUSY:Validation cannot be performed yet. KeyM  **
**                                  is currently busy with other jobs         **
**                      KEYM_E_PARAMETER_MISMATCH: Certificate ID invalid     **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Provided buffer for    **
**                                                     the certificate too    **
**                                                     small.                 **
**                      KEYM_E_KEY_CERT_EMPTY: One of the certificate slots   **
**                                             are empty                      **
**                      KEYM_E_CERT_INVALID_CHAIN_OF_TRUST: An upper cert is  **
**                                                          not valid         **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoCert, KeyM_CurrentJob,   **
**                      KeyM_JobState, KeyM_OperationResult, KeyM_CertId,     **
**                      KeyM_BackGroundDone                                   **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError, KeyM_PrvConstructCertChain           **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_CryptoStack_00111 SRS_CryptoStack_00031 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_VerifyCertificate(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId)
{
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  Std_ReturnType retVal;

  retVal = E_NOT_OK;
   /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_089 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_VERIFYCERTIFICATE_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    if (KEYM_BUSY == KeyM_ModuleState)
    {
      /* @Trace: KeyM_SUD_FUNC_090 */
      retVal = KEYM_E_BUSY;
    }
    else
    {
      if (KEYM_TOTAL_CERTIFICATE > CertId)
      {
        /* Get the pointer to the certificates */
        ptrCert = &KeyM_CryptoCert[CertId];

        if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus)
        {
          /* @Trace: KeyM_SUD_FUNC_092 */
          retVal = KEYM_E_KEY_CERT_EMPTY;
        }
        else if ((KEYM_E_CERTIFICATE_INVALID_TYPE == ptrCert->CertStatus) || \
          (KEYM_E_CERTIFICATE_INVALID_FORMAT == ptrCert->CertStatus))
        {
          /* @Trace: KeyM_SUD_FUNC_093 */
          /* The certificate can not be verified if parsing fail */
          retVal = E_NOT_OK;
        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_094 */
          retVal = KeyM_PrvConstructCertChain(ptrCert);

          if (E_OK == retVal)
          {
            SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
            /* Update module state */
            KeyM_ModuleState = KEYM_BUSY;
            SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
            /* Update current job name */
            KeyM_CurrentJob = KEYM_VERIFY_CERTIFICATE_JOB;
            /* Update job state */
            KeyM_JobState = KEYM_REQUEST_JOB;
            /* Key Operation result is NOT OK by default */
            KeyM_OperationResult = KEYM_RT_NOT_OK;
            /* Background task status is not done by default */
            KeyM_BackGroundDone = KEYM_FALSE;
            /* Hold the id of certificates to use in the main function */
            KeyM_CertId = CertId;
            /* The certificate is in progress */
            ptrCert->InProgress = KEYM_ONE;
          } /* @if (E_OK == retVal) */
        } /* @if ((KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus) */
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_091 */
        retVal = KEYM_E_PARAMETER_MISMATCH;
      } /* @if ((KEYM_TOTAL_CERTIFICATE > CertId) */
    } /* @if (KEYM_BUSY == KeyM_ModuleState) */
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_VerifyCertificateChain                           **
**                                                                            **
** Service ID         : 0x0e                                                  **
**                                                                            **
** Description        : This function performs a certificate verification     **
**                      against a list of certificates. It is a pre-requisite **
**                      that the certificate that shall be checked has already**
**                      been written with KeyM_SetCertificate() and that the  **
**                      root certificate is either in the list or is already  **
**                      assigned to one of the other certificates.            **
**                                                                            **
** Sync/Async         : Asynchronous                                          **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : CertId, CertChainData, NumberOfCertificates           **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: Certificate verification request accepted.      **
**                            Operation will be performed in the background   **
**                            and response is given through a callback.       **
**                      E_NOT_OK: Operation not accepted due to an internal   **
**                                error.                                      **
**                      KEYM_E_BUSY:Validation cannot be performed yet. KeyM  **
**                                  is currently busy with other jobs         **
**                      KEYM_E_PARAMETER_MISMATCH: Certificate ID invalid     **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Provided buffer for    **
**                                                     the certificate too    **
**                                                     small.                 **
**                      KEYM_E_KEY_CERT_EMPTY: One of the certificate slots   **
**                                             are empty                      **
**                      KEYM_E_CERT_INVALID_CHAIN_OF_TRUST: An upper cert is  **
**                                                          not valid         **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoCert, KeyM_CurrentJob,   **
**                      KeyM_JobState, KeyM_OperationResult, KeyM_CertId,     **
**                      KeyM_BackGroundDone, KeyM_CertChainData,              **
**                      KeyM_NumberOfCertificates                             **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_CryptoStack_00111 SRS_CryptoStack_00031 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_VerifyCertificateChain(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  P2CONST(KeyM_CertDataType, AUTOMATIC, KEYM_APPL_CONST) certChainData, \
  VAR(uint8, AUTOMATIC) NumberOfCertificates)
{
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  Std_ReturnType retVal;
  uint8 certIndex;

  retVal = E_NOT_OK;
   /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_095 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_VERIFYCERTIFICATECHAIN_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (NULL_PTR == certChainData)
  {
    /* @Trace: KeyM_SUD_FUNC_096 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case input buffer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_VERIFYCERTIFICATECHAIN_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (KEYM_ZERO == NumberOfCertificates)
  {
    /* @Trace: KeyM_SUD_FUNC_097 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case input buffer length is zero */
      KEYM_REPORT_ERROR(KEYM_VERIFYCERTIFICATECHAIN_SID, KEYM_E_SMALL_BUFFER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    retVal = E_OK;

    if (KEYM_BUSY == KeyM_ModuleState)
    {
      /* @Trace: KeyM_SUD_FUNC_098 */
      retVal = KEYM_E_BUSY;
    }
    else
    {
      if (KEYM_TOTAL_CERTIFICATE > CertId)
      {
        /* Get the pointer to the certificates */
        ptrCert = &KeyM_CryptoCert[CertId];

        if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus)
        {
          /* @Trace: KeyM_SUD_FUNC_100 */
          retVal = KEYM_E_KEY_CERT_EMPTY;
        }
        else if ((KEYM_E_CERTIFICATE_INVALID_TYPE == ptrCert->CertStatus) || \
          (KEYM_E_CERTIFICATE_INVALID_FORMAT == ptrCert->CertStatus) ||
          (KEYM_CERT_FORMAT_CRL == ptrCert->CertFormat) || \
          (KEYM_TRUE == ptrCert->IsRoot))
        {
          /* @Trace: KeyM_SUD_FUNC_101 */
          /* The certificate must not be parsed fail and must
            not be root or CRL */
          retVal = E_NOT_OK;
        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_102 */
          for (certIndex = 0u; certIndex < NumberOfCertificates; certIndex++)
          {
            if ((0u == certChainData[certIndex].certDataLength) || \
              (NULL_PTR == certChainData[certIndex].certData))
            {
              retVal = KEYM_E_KEY_CERT_EMPTY;
              break;
            }
          }

          if (E_OK == retVal)
          {
            SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
            /* Update module state */
            KeyM_ModuleState = KEYM_BUSY;
            SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
            /* Update current job name */
            KeyM_CurrentJob = KEYM_VERIFY_CERTIFICATECHAIN_JOB;
            /* Update job state */
            KeyM_JobState = KEYM_REQUEST_JOB;
            /* Key Operation result is NOT OK by default */
            KeyM_OperationResult = KEYM_RT_NOT_OK;
            /* Background task status is not done by default */
            KeyM_BackGroundDone = KEYM_FALSE;
            /* Hold the id of certificates to use in the main function */
            KeyM_CertId = CertId;
            /* Save the input parameters */
            /* polyspace-begin MISRA-C3:18.6 [Justified:Low] 
              "Some global data(longer life-time var) is assiged with certChainData parameter. 
              This API is not invoked while running Crypto stack only, so these parameters are considered to be shorter life-time vars.
              There is no race condition problem." */
            KeyM_CertChainData = certChainData;
            KeyM_NumberOfCertificates = NumberOfCertificates;
            /* The certificate is in progress */
            ptrCert->InProgress = KEYM_ONE;
          }

        } /* @if ((KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus) */
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_099 */
        retVal = KEYM_E_PARAMETER_MISMATCH;
      } /* @if ((KEYM_TOTAL_CERTIFICATE > CertId) */
    } /* @if (KEYM_BUSY == KeyM_ModuleState) */
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_CertElementGet                                   **
**                                                                            **
** Service ID         : 0x0f                                                  **
**                                                                            **
** Description        : This function provides the content of a specific      **
**                      certificate element. The certificate configuration    **
**                      defines how the certificate submodule can find the    **
**                      element, e.g. by providing the object identifier(OID) **
**                      This function is used to retrieve this information if **
**                      only one element is assigned to the respective OID    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : CertId, CertElementId                                 **
**                                                                            **
** InOut parameter    : CertElementDataLength                                 **
**                                                                            **
** Output Parameters  : CertElementData                                       **
**                                                                            **
** Return parameter   : E_OK: Element found and data provided in the buffer.  **
**                      E_NOT_OK:  Element data not found.                    **
**                      KEYM_E_PARAMETER_MISMATCH: Certificate ID or          **
**                                                 certificate element ID     **
**                                                 invalid                    **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Provided buffer for    **
**                                                     the certificate too    **
**                                                     small.                 **
**                      KEYM_E_KEY_CERT_EMPTY: No certificate data available, **
**                                             the certificate slot is empty  **
**                      KEYM_E_KEY_CERT_INVALID: The certificate is not valid **
**                                               or has not yet been verified **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoCert                     **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError, KeyM_PrvX509ElementGet,              **
**                      KeyM_PrvCvcElementGet, KeyM_PrvMemCopy                **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_CryptoStack_00112 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertElementGet(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  VAR(KeyM_CertElementIdType, AUTOMATIC) CertElementId, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) CertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) CertElementDataLength)
{
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  Std_ReturnType retVal;

  retVal = E_NOT_OK;
  ptrElementData = NULL_PTR;
  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_104 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_CERTELEMENTGET_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if ((NULL_PTR == CertElementData) || (NULL_PTR == CertElementDataLength))
  {
    /* @Trace: KeyM_SUD_FUNC_105 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case output buffer pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_CERTELEMENTGET_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    if (KEYM_TOTAL_CERTIFICATE > CertId)
    {
      ptrCert = &KeyM_CryptoCert[CertId];

      if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus)
      {
        /* @Trace: KeyM_SUD_FUNC_108 */
        retVal = KEYM_E_KEY_CERT_EMPTY;
      }
      else if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
      {
        /* @Trace: KeyM_SUD_FUNC_109 */
        retVal = KEYM_E_KEY_CERT_INVALID;
      }
      else
      {
        if (ptrCert->NumberOfCertElement > CertElementId)
        {
          /* @Trace: KeyM_SUD_FUNC_111 */
          ptrCertElement = &ptrCert->PtrCertElement[CertElementId];

          #if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
            (KEYM_CERT_X509_CRL_ENABLED == STD_ON))
          if ((KEYM_CERT_FORMAT_X509 == ptrCert->CertFormat) || \
            (KEYM_CERT_FORMAT_CRL == ptrCert->CertFormat))
          {
            retVal = KeyM_PrvX509ElementGet(ptrCertElement,\
              &ptrElementData, CertElementDataLength,\
              ptrCert->CertFormat);
          }
          else
          #endif /* ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) ||
            (KEYM_CERT_X509_CRL_ENABLED == STD_ON)) */
          {
            #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
            retVal = KeyM_PrvCvcElementGet(ptrCertElement,\
              &ptrElementData, CertElementDataLength);
            #endif
          }

          if (E_OK == retVal)
          {
            /* @Trace: KeyM_SUD_FUNC_112 */
            (void)KeyM_PrvMemCopy(ptrElementData, CertElementData, \
              *CertElementDataLength);
          }
          else
          {
            /* @Trace: KeyM_SUD_FUNC_113 */
            #if (KEYM_DEV_ERROR_DETECT == STD_ON)
              if (KEYM_E_KEY_CERT_SIZE_MISMATCH == retVal)
              {
                /* Report error to Det in case output buffer length is zero */
                KEYM_REPORT_ERROR(KEYM_CERTELEMENTGET_SID, KEYM_E_SMALL_BUFFER);
              }
            #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
          }
        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_110 */
          retVal = KEYM_E_PARAMETER_MISMATCH;
        }
      }
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_107 */
      retVal = KEYM_E_PARAMETER_MISMATCH;
    } /* @if (E_OK == retVal) */
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_CertElementGetFirst                              **
**                                                                            **
** Service ID         : 0x10                                                  **
**                                                                            **
** Description        : This function is used to initialize the interative    **
**                      extraction of a certificate data element. It always   **
**                      retrieves the top element from the configured         **
**                      certificate element and initializes the structure     **
**                      KeyM_CertElementIterator so that consecutive data     **
**                      from this element can be read with                    **
**                      KeyM_CertElementGetNext().                            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant for one iterator                            **
**                                                                            **
** Input Parameters   : CertId, CertElementId                                 **
**                                                                            **
** InOut parameter    : CertElementIterator, CertElementDataLength            **
**                                                                            **
** Output Parameters  : CertElementData                                       **
**                                                                            **
** Return parameter   : E_OK: Element found and data provided in the buffer.  **
**                      E_NOT_OK: Element data not found. CertElementIterator **
**                                cannot be used for further calls.           **
**                      KEYM_E_PARAMETER_MISMATCH: Certificate ID or          **
**                                                 certificate element ID     **
**                                                 invalid                    **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Provided buffer for    **
**                                                     the certificate too    **
**                                                     small.                 **
**                      KEYM_E_KEY_CERT_EMPTY: No certificate data available, **
**                                             the certificate slot is empty  **
**                      KEYM_E_KEY_CERT_INVALID: The certificate is not valid **
**                                               or has not yet been verified **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoCert                     **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError, KeyM_PrvX509ElementGetFirst,         **
**                      KeyM_PrvCvcElementGetFirst, KeyM_PrvMemCopy           **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_CryptoStack_00112 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertElementGetFirst(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  VAR(KeyM_CertElementIdType, AUTOMATIC) CertElementId, \
  P2VAR(KeyM_CertElementIteratorType, AUTOMATIC, KEYM_APPL_DATA) \
  CertElementIterator, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) CertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) CertElementDataLength)
{
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  Std_ReturnType retVal;

  retVal = E_NOT_OK;
  ptrElementData = NULL_PTR;
  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_114 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
    /* Report error to Det in case KeyM has already initialized */
    KEYM_REPORT_ERROR(KEYM_CERTELEMENTGETFIRST_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if ((NULL_PTR == CertElementData) || \
    (NULL_PTR == CertElementDataLength) || (NULL_PTR == CertElementIterator))
  {
    /* @Trace: KeyM_SUD_FUNC_115 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case output buffer pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_CERTELEMENTGETFIRST_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    if (KEYM_TOTAL_CERTIFICATE > CertId)
    {
      ptrCert = &KeyM_CryptoCert[CertId];

      if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus)
      {
        /* @Trace: KeyM_SUD_FUNC_117 */
        retVal = KEYM_E_KEY_CERT_EMPTY;
      }
      else if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
      {
        /* @Trace: KeyM_SUD_FUNC_118 */
        retVal = KEYM_E_KEY_CERT_INVALID;
      }
      else
      {
        if (ptrCert->NumberOfCertElement > CertElementId)
        {
          /* @Trace: KeyM_SUD_FUNC_120 */
          ptrCertElement = &ptrCert->PtrCertElement[CertElementId];

          #if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
            (KEYM_CERT_X509_CRL_ENABLED == STD_ON))
          if ((KEYM_CERT_FORMAT_X509 == ptrCert->CertFormat) || \
            (KEYM_CERT_FORMAT_CRL == ptrCert->CertFormat))
          {
            retVal = KeyM_PrvX509ElementGetFirst(ptrCertElement,\
              CertElementIterator, &ptrElementData,\
              CertElementDataLength, ptrCert->CertFormat);
          }
          else
          #endif /* ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) ||
            (KEYM_CERT_X509_CRL_ENABLED == STD_ON)) */
          {
            #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
            retVal = KeyM_PrvCvcElementGetFirst(ptrCertElement, \
              CertElementIterator, &ptrElementData, CertElementDataLength);
            #endif
          }

          if (E_OK == retVal)
          {
            /* @Trace: KeyM_SUD_FUNC_121 */
            CertElementIterator->certId = CertId;
            CertElementIterator->elementId = CertElementId;
            CertElementIterator->resultOfGet = KEYM_TRUE;
            (void)KeyM_PrvMemCopy(ptrElementData, CertElementData, \
              *CertElementDataLength);
          }
          else
          {
            /* @Trace: KeyM_SUD_FUNC_122 */
            CertElementIterator->resultOfGet = KEYM_FALSE;
            #if (KEYM_DEV_ERROR_DETECT == STD_ON)
              if (KEYM_E_KEY_CERT_SIZE_MISMATCH == retVal)
              {
                /* Report error to Det in case output buffer length is zero */
                KEYM_REPORT_ERROR(KEYM_CERTELEMENTGETFIRST_SID, \
                KEYM_E_SMALL_BUFFER);
              }
            #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
          }

        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_119 */
          retVal = KEYM_E_PARAMETER_MISMATCH;
        }
      }
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_116 */
      retVal = KEYM_E_PARAMETER_MISMATCH;
    } /* @if (KEYM_TOTAL_CERTIFICATE > CertId) */
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name      : KeyM_PartOfCertElementGetNext                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_CertElementGetNext,            **
**                      this function is created to reduce code metric of     **
**                      KeyM_CertElementGetNext                               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCert, ptrCertElement,                              **
**                                                                            **
** InOut Parameters   : ptrCertElementIterator, ptrCertElementDataLength      **
**                                                                            **
** Output Parameters  : ptrCertElementData                                    **
**                                                                            **
** Return parameter   : E_OK                                                  **
**                      E_NOT_OK                                              **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH                         **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError, KeyM_PrvX509ElementGetNext,          **
**                      KeyM_PrvCvcElementGetNext, KeyM_PrvMemCopy            **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PartOfCertElementGetNext(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(KeyM_CertElementIteratorType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrCertElementIterator, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLength)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;

  /* @Trace: KeyM_SUD_FUNC_151 */
  ptrElementData = NULL_PTR;
  #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_OFF)
    retVal = E_NOT_OK;
  #endif
  #if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
    (KEYM_CERT_X509_CRL_ENABLED == STD_ON))
  if ((KEYM_CERT_FORMAT_X509 == ptrCert->CertFormat) || \
    (KEYM_CERT_FORMAT_CRL == ptrCert->CertFormat))
  {
    /* @Trace: KeyM_SUD_FUNC_152 */
    retVal = KeyM_PrvX509ElementGetNext(ptrCertElement,\
      ptrCertElementIterator, &ptrElementData,\
      ptrCertElementDataLength, ptrCert->CertFormat);
  }
  else
  #endif /* ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) ||
    (KEYM_CERT_X509_CRL_ENABLED == STD_ON)) */
  {
    #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
    /* @Trace: KeyM_SUD_FUNC_153 */
    retVal = KeyM_PrvCvcElementGetNext(ptrCertElement,\
      ptrCertElementIterator, &ptrElementData,\
      ptrCertElementDataLength);
    #endif
  }

  /* @Trace: KeyM_SUD_FUNC_154 */
  if (E_OK == retVal)
  {
    ptrCertElementIterator->resultOfGet = KEYM_TRUE;
    retVal = KeyM_PrvMemCopy(ptrElementData, ptrCertElementData, \
      *ptrCertElementDataLength);
  }
  else
  {
    if (KEYM_E_KEY_CERT_SIZE_MISMATCH == retVal)
    {
      #if (KEYM_DEV_ERROR_DETECT == STD_ON)
        /* Report error to Det in case output buffer length is zero */
        KEYM_REPORT_ERROR(KEYM_CERTELEMENTGETNEXT_SID, KEYM_E_SMALL_BUFFER);
      #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
    }
  }
  
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h" 
/*******************************************************************************
** Function Name      : KeyM_CertElementGetNext                               **
**                                                                            **
** Service ID         : 0x11                                                  **
**                                                                            **
** Description        : This function provides further data from a certificate**
**                      element, e.g. if a set of data are located in one     **
**                      certificate element that shall be read one after      **
**                      another. This function can only be called if the      **
**                      function KeyM_CertElementGetFirst() has been called   **
**                      once before                                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant for one iterator                            **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : CertElementIterator, CertElementDataLength            **
**                                                                            **
** Output Parameters  : CertElementData                                       **
**                                                                            **
** Return parameter   : E_OK: Element found and data provided in the buffer.  **
**                      E_NOT_OK: Element data not found. CertElementIterator **
**                                cannot be used for further calls.           **
**                      KEYM_E_PARAMETER_MISMATCH: Certificate ID or          **
**                                                 certificate element ID     **
**                                                 invalid                    **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Provided buffer for    **
**                                                     the certificate too    **
**                                                     small.                 **
**                      KEYM_E_KEY_CERT_EMPTY: No certificate data available, **
**                                             the certificate slot is empty  **
**                      KEYM_E_KEY_CERT_INVALID: The certificate is not valid **
**                                               or has not yet been verified **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoCert                     **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError, KeyM_PartOfCertElementGetNext        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_CryptoStack_00112 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertElementGetNext(\
  P2VAR(KeyM_CertElementIteratorType, AUTOMATIC, KEYM_APPL_DATA) \
  CertElementIterator, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) CertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) CertElementDataLength)
{
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement;
  uint16 elementId;
  Std_ReturnType retVal;

  retVal = E_NOT_OK;

  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_123 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_CERTELEMENTGETNEXT_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if ((NULL_PTR == CertElementData) || \
    (NULL_PTR == CertElementDataLength) || (NULL_PTR == CertElementIterator))
  {
    /* @Trace: KeyM_SUD_FUNC_124 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case output buffer pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_CERTELEMENTGETNEXT_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (KEYM_TRUE == CertElementIterator->resultOfGet)
  {
    if (KEYM_TOTAL_CERTIFICATE > CertElementIterator->certId)
    {
      ptrCert = &KeyM_CryptoCert[CertElementIterator->certId];

      if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus)
      {
        /* @Trace: KeyM_SUD_FUNC_127 */
        retVal = KEYM_E_KEY_CERT_EMPTY;
      }
      else if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
      {
        /* @Trace: KeyM_SUD_FUNC_128 */
        retVal = KEYM_E_KEY_CERT_INVALID;
      }
      else
      {
        elementId = CertElementIterator->elementId;

        if (ptrCert->NumberOfCertElement > elementId)
        {
          ptrCertElement = &ptrCert->PtrCertElement[elementId];

          if (KEYM_TRUE == ptrCertElement->ElementHasIteration)
          {
            /* @Trace: KeyM_SUD_FUNC_131 */
            retVal = KeyM_PartOfCertElementGetNext(ptrCert, ptrCertElement, \
              CertElementIterator, CertElementData,\
              CertElementDataLength);
          }
          else
          {
            /* @Trace: KeyM_SUD_FUNC_130 */
            retVal = KEYM_E_KEY_CERT_INVALID;
          } /* @if (KEYM_TRUE == ptrCertElement->ElementHasIteration) */
        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_129 */
          retVal = KEYM_E_PARAMETER_MISMATCH;
        } /* @if (E_OK == retVal) */
      } /* @if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus) */
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_126 */
      retVal = KEYM_E_PARAMETER_MISMATCH;
    } /* @if (KEYM_TOTAL_CERTIFICATE > CertId) */

    /* @Trace: KeyM_SUD_FUNC_132 */
    if (E_OK != retVal)
    {
      CertElementIterator->resultOfGet = KEYM_FALSE;
    }
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_125 */
    retVal = E_NOT_OK;
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_CertGetStatus                                    **
**                                                                            **
** Service ID         : 0x12                                                  **
**                                                                            **
** Description        : This function provides the status of a certificate.   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : CertId                                                **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : Status                                                **
**                                                                            **
** Return parameter   : E_OK                                                  **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoCert                     **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_KeyM_00003 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertGetStatus(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  P2VAR(KeyM_CertificateStatusType, AUTOMATIC, KEYM_APPL_DATA) Status)
{
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  Std_ReturnType retVal;

  retVal = E_NOT_OK;
  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_133 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_CERTGETSTATUS_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (NULL_PTR == Status)
  {
    /* @Trace: KeyM_SUD_FUNC_134 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case output buffer pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_CERTGETSTATUS_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    if (KEYM_TOTAL_CERTIFICATE > CertId)
    {
      /* @Trace: KeyM_SUD_FUNC_136 */
      retVal = E_OK;

      ptrCert = &KeyM_CryptoCert[CertId];
      *Status = ptrCert->CertStatus;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_135 */
      retVal = KEYM_E_PARAMETER_MISMATCH;
    } /* @if (E_OK == retVal) */
  }
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_CertificateElementGetByIndex                     **
**                                                                            **
** Service ID         : 0x13                                                  **
**                                                                            **
** Description        : This function provides the element data of a          **
**                      certificate. The function is used if an element type  **
**                      can have more than one parameter. The index specifies **
**                      which element shall be read. The function works       **
**                      similar to the                                        **
**                      KeyM_CertElementGetFirst/KeyM_CertElementGetNext, but **
**                      instead of the iteration, the individual elements can **
**                      be accessed by index (like the operation in the       **
**                      service interface).                                   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : CertId, CertElementId, Index                          **
**                                                                            **
** InOut parameter    : CertElementDataLengthPtr                              **
**                                                                            **
** Output Parameters  : CertElementDataPtr                                    **
**                                                                            **
** Return parameter   : E_OK: Element found and data provided in the buffer.  **
**                      E_NOT_OK:  Element data not found.                    **
**                      KEYM_E_PARAMETER_MISMATCH: Certificate ID or          **
**                                                 certificate element ID     **
**                                                 invalid                    **
**                      KEYM_E_KEY_CERT_SIZE_MISMATCH: Provided buffer for    **
**                                                     the certificate element**
**                                                     too small.             **
**                      KEYM_E_KEY_CERT_EMPTY: No certificate data available, **
**                                             the certificate slot is empty  **
**                      KEYM_E_KEY_CERT_INVALID: The certificate is not valid **
**                                               or has not yet been verified **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoCert                     **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError, KeyM_PrvElementGetByIndex,           **
**                      KeyM_PrvMemCopy                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_CryptoStack_00112 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertificateElementGetByIndex(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  VAR(KeyM_CertElementIdType, AUTOMATIC) CertElementId, \
  VAR(uint32, AUTOMATIC) Index, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) CertElementDataPtr, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) CertElementDataLengthPtr)
{
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  Std_ReturnType retVal;

  retVal = E_NOT_OK;
  ptrElementData = NULL_PTR;
  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_137 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_CERTIFICATEELEMENTGETBYINDEX_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if ((NULL_PTR == CertElementDataPtr) || \
    (NULL_PTR == CertElementDataLengthPtr))
  {
    /* @Trace: KeyM_SUD_FUNC_138 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case output buffer pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_CERTIFICATEELEMENTGETBYINDEX_SID, \
        KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    if (KEYM_TOTAL_CERTIFICATE > CertId)
    {
      ptrCert = &KeyM_CryptoCert[CertId];

      if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus)
      {
        /* @Trace: KeyM_SUD_FUNC_140 */
        retVal = KEYM_E_KEY_CERT_EMPTY;
      }
      else if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
      {
        /* @Trace: KeyM_SUD_FUNC_141 */
        retVal = KEYM_E_KEY_CERT_INVALID;
      }
      else
      {
        if (ptrCert->NumberOfCertElement > CertElementId)
        {
          ptrCertElement = &ptrCert->PtrCertElement[CertElementId];

          retVal = KeyM_PrvElementGetByIndex(ptrCert, ptrCertElement, Index,\
            &ptrElementData, CertElementDataLengthPtr);

          if (E_OK == retVal)
          {
            /* @Trace: KeyM_SUD_FUNC_143 */
            (void)KeyM_PrvMemCopy(ptrElementData, CertElementDataPtr, \
              *CertElementDataLengthPtr);
          }
          else
          {
            /* @Trace: KeyM_SUD_FUNC_144 */
            #if (KEYM_DEV_ERROR_DETECT == STD_ON)
              if (KEYM_E_KEY_CERT_SIZE_MISMATCH == retVal)
              {
                /* Report error to Det in case output buffer length is zero */
                KEYM_REPORT_ERROR(KEYM_CERTIFICATEELEMENTGETBYINDEX_SID, \
                  KEYM_E_SMALL_BUFFER);
              }
            #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
          }

        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_142 */
          retVal = KEYM_E_PARAMETER_MISMATCH;
        }
      }
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_139 */
      retVal = KEYM_E_PARAMETER_MISMATCH;
    } /* @if (E_OK == retVal) */
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_CertificateElementGetCount                       **
**                                                                            **
** Service ID         : 0x14                                                  **
**                                                                            **
** Description        : This function provides the total number of data       **
**                      elements that are available for the specified         **
**                      certificate element. Typically, only one data element **
**                      is available. But in some cases, several data elements**
**                      can be assigned to one certificate element in a row.  **
**                      This function retrieves the total number of elements. **
**                      The individual data elements can then accessed with   **
**                      KeyM_CertificateElementGetByIndex()                   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : CertId, CertElementId                                 **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : CountPtr                                              **
**                                                                            **
** Return parameter   : E_OK: Element found and data provided in the buffer.  **
**                      E_NOT_OK:  Element data not found.                    **
**                      KEYM_E_PARAMETER_MISMATCH: Certificate ID or          **
**                                                 certificate element ID     **
**                                                 invalid                    **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoCert                     **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError, KeyM_PrvX509ElementGetCount,         **
**                      KeyM_PrvCvcElementGetCount                            **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00357 SRS_CryptoStack_00112 SRS_BSW_00337 SRS_CryptoStack_00106 SRS_CryptoStack_00113 SRS_CryptoStack_00115 SRS_KeyM_00001 SRS_BSW_00385 */
FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertificateElementGetCount(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  VAR(KeyM_CertElementIdType, AUTOMATIC) CertElementId, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) CountPtr)
{
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement;
  Std_ReturnType retVal;

  retVal = E_NOT_OK;
  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    /* @Trace: KeyM_SUD_FUNC_145 */
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_CERTIFICATEELEMENTGETCOUNT_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if (NULL_PTR == CountPtr)
  {
    /* @Trace: KeyM_SUD_FUNC_146 */
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case output buffer pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_CERTIFICATEELEMENTGETCOUNT_SID, \
        KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    if (KEYM_TOTAL_CERTIFICATE > CertId)
    {
      /* @Trace: KeyM_SUD_FUNC_148 */
      ptrCert = &KeyM_CryptoCert[CertId];

      if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
      {
        retVal = E_NOT_OK;
      }
      else
      {
        if (ptrCert->NumberOfCertElement > CertElementId)
        {
          ptrCertElement = &ptrCert->PtrCertElement[CertElementId];

          #if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
            (KEYM_CERT_X509_CRL_ENABLED == STD_ON))
          if ((KEYM_CERT_FORMAT_X509 == ptrCert->CertFormat) || \
            (KEYM_CERT_FORMAT_CRL == ptrCert->CertFormat))
          {
            /* @Trace: KeyM_SUD_FUNC_149 */
            retVal = KeyM_PrvX509ElementGetCount(ptrCert, \
              ptrCertElement, CountPtr);
          }
          else
          #endif /* ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) ||
            (KEYM_CERT_X509_CRL_ENABLED == STD_ON)) */
          {
            #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
              /* @Trace: KeyM_SUD_FUNC_150 */
              retVal = KeyM_PrvCvcElementGetCount(ptrCertElement, CountPtr);
            #endif
          }
        }
        else
        {
          retVal = KEYM_E_PARAMETER_MISMATCH;
        }
      }
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_147 */
      retVal = KEYM_E_PARAMETER_MISMATCH;
    } /* @if (E_OK == retVal) */
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_CertElementGetOIDHex                                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function provides the content of a Oid           **
**                      certificate element -  Object Id.                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : CertId, CertElementId                                 **
**                                                                            **
** InOut parameter    : CertElementOidDataLength                              **
**                                                                            **
** Output Parameters  : CertElementOidData                                    **
**                                                                            **
** Return parameter   : E_OK: data found and returned       **
**in the buffer.                                                              **
**                      E_NOT_OK:  OID Element data not found.                **
**                      KEYM_E_PARAMETER_MISMATCH: Certificate ID or          **
**                                                 certificate element ID     **
**                                                 invalid                    **
**                      KEYM_E_KEY_CERT_EMPTY: No certificate data available, **
**                                             the certificate slot is empty  **
**                      KEYM_E_KEY_CERT_INVALID: The certificate is not valid **
**                                               or has not yet been verified **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoCert                     **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError,  KeyM_PrvMemCopy                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertElementGetOIDHex(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  VAR(KeyM_CertElementIdType, AUTOMATIC) CertElementId, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) CertElementOidData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) CertElementOidDataLength)
{
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement;

  Std_ReturnType retVal = E_NOT_OK;
  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_CERTELEMENTGET_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if ((NULL_PTR == CertElementOidData) || (NULL_PTR == CertElementOidDataLength))
  {
    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case output buffer pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_CERTELEMENTGET_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    if (KEYM_TOTAL_CERTIFICATE > CertId)
    {
      ptrCert = &KeyM_CryptoCert[CertId];
      if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus)
      {
        retVal = KEYM_E_KEY_CERT_EMPTY;
      }
      else if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
      {
        retVal = KEYM_E_KEY_CERT_INVALID;
      }
      else
      {
        if (ptrCert->NumberOfCertElement > CertElementId)
        {
          ptrCertElement = &ptrCert->PtrCertElement[CertElementId];
            if( NULL_PTR != ptrCertElement)
            {  
              if (NULL_PTR != ptrCertElement->PtrElementObjectId)
              {
                if ((KEYM_CERT_SUBJECT_NAME == ptrCertElement->ElementOfStruct) ||\
                    (KEYM_CERT_ISSUER_NAME == ptrCertElement->ElementOfStruct) || \
                    (KEYM_CERT_EXTENSION == ptrCertElement->ElementOfStruct))
                {
                  /* @Trace: KeyM_SUD_FUNC_992 */
                  /*These Oid has been verified*/
                  *CertElementOidDataLength = ptrCertElement->ObjectIdLength;

                  (void)KeyM_PrvMemCopy(ptrCertElement->PtrElementObjectId, CertElementOidData, \
                    *CertElementOidDataLength);

                  retVal = E_OK;
                }
                else
                {
                  retVal = E_NOT_OK;
                }
              }
              else
              {
                /* @Trace: KeyM_SUD_FUNC_998 */
                retVal = E_NOT_OK;
              }
            }
            else
            {
              retVal = E_NOT_OK;
            }
        }
        else /*if (ptrCert->NumberOfCertElement > CertElementId)*/
        {
          retVal = KEYM_E_PARAMETER_MISMATCH;
        }
      }
    }
    else
    {
      retVal = KEYM_E_PARAMETER_MISMATCH;
    }
  } /* @if (KEYM_UNINIT == KeyM_ModuleState) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name      : KeyM_CertGetDERPacketData                             **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function provides all all element data in Der
**                      format                                                **
**                   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : CertId, 
KeyM_CertificateElementTypeOfStructure                      typestruct        **
**                                                                            **
** InOut parameter    : CertElementOidDataLength                              **
**                                                                            **
** Output Parameters  : DataPtr    
                        DataLengthPtr                                         **
**                                                                            **
** Return parameter   : E_OK: data found and data provided                    **
**in the buffer.                                                              **
**                      E_NOT_OK:  OID Element data not found.                **
**                      KEYM_E_PARAMETER_MISMATCH: Certificate ID or          **
**                                                 certificate element ID     **
**                                                 invalid                    **
**                      KEYM_E_KEY_CERT_EMPTY: No certificate data available, **
**                                             the certificate slot is empty  **
**                      KEYM_E_KEY_CERT_INVALID: The certificate is not valid **
**                                               or has not yet been verified **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CryptoCert                     **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError,  KeyM_PrvMemCopy                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertGetDERPacketData(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptrData, \
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptrDataLength,
  CONST(uint8, AUTOMATIC)  Typestruct)
{
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;

  Std_ReturnType retVal = E_NOT_OK;
  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT == KeyM_ModuleState)
  {
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case KeyM has already initialized */
      KEYM_REPORT_ERROR(KEYM_CERTELEMENTGET_SID, KEYM_E_UNINIT);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else if ((NULL_PTR == ptrData) || (NULL_PTR == ptrDataLength))
  {

    retVal = KEYM_E_PARAMETER_MISMATCH;
    #if (KEYM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case output buffer pointer is NULL_PTR */
      KEYM_REPORT_ERROR(KEYM_CERTELEMENTGET_SID, KEYM_E_PARAM_POINTER);
    #endif /* KEYM_DEV_ERROR_DETECT == STD_ON */
  }
  else
  {
    if (KEYM_TOTAL_CERTIFICATE > CertId)
    {
      ptrCert = &KeyM_CryptoCert[CertId];
      if (KEYM_CERTIFICATE_NOT_AVAILABLE == ptrCert->CertStatus)
      {
        retVal = KEYM_E_KEY_CERT_EMPTY;
      }
      else if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus)
      {
        retVal = KEYM_E_KEY_CERT_INVALID;
      }
      else
      {
        if( (NULL_PTR != ptrCert->PtrCertData) && (0 != ptrCert->CertLength) )
         {
          /* @Trace: KeyM_SUD_FUNC_997 */
          retVal = KeyM_PrvX509GetDERPacketData(ptrCert->PtrCertData, \
                                              ptrCert->CertLength, \
                                              ptrData, \
                                              ptrDataLength, \
                                              Typestruct);
         if( E_OK != retVal)
          {
          retVal = E_NOT_OK;
          }
        }
      }
    }
  }
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */
/*******************************************************************************
** Function Name      : KeyM_MainFunction                                     **
**                                                                            **
** Service ID         : 0x19                                                  **
**                                                                            **
** Description        : This function Function is called periodically         **
**                      according the specified time interval.                **
**                                                                            **
** Sync/Async         : None                                                  **
**                                                                            **
** Re-entrancy        : None                                                  **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CurrentJob                     **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError, KeyM_PrvProcessUpdateOperation,      **
**                      KeyM_PrvProcessFinalizeOperation,                     **
**                      KeyM_PrvProcessVerifyOperation,                       **
**                      KeyM_PrvProcessServiceCertificateOperation,           **
**                      KeyM_PrvProcessVerifyCertOperation,                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_MainFunction(void)
{
  /* @Trace: KeyM_SUD_FUNC_155 */
  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT != KeyM_ModuleState)
  {
    switch(KeyM_CurrentJob)
    {
      #if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)
      case KEYM_UPDATE_JOB:
        /* @Trace: KeyM_SUD_FUNC_156 */
        /* Process update operation */
        KeyM_PrvProcessUpdateOperation();
        break;

      #if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
      case KEYM_FINALIZE_JOB:
        /* @Trace: KeyM_SUD_FUNC_157 */
        /* Process finalize operation */
        KeyM_PrvProcessFinalizeOperation();
        break;
      #endif /* KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */

      #if (KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON)
      case KEYM_VERIFY_JOB:
        #if (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_158 */
        /* Process verify operation */
        KeyM_PrvProcessVerifyOperation();
        #endif /* KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON */
        break;
      #endif /* KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON */
      #endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */
      #if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
      #if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
      case KEYM_SERVICE_CERTIFICATE_JOB:
        /* @Trace: KeyM_SUD_FUNC_159 */
        /* Process ServiceCertificate operation */
        KeyM_PrvProcessServiceCertificateOperation();
        break;
      #endif /* KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON */
      case KEYM_VERIFY_CERTIFICATES_JOB:
      case KEYM_VERIFY_CERTIFICATE_JOB:
      case KEYM_VERIFY_CERTIFICATECHAIN_JOB:
        /* @Trace: KeyM_SUD_FUNC_160 */
        /* Process Verify Certificates operation */
        KeyM_PrvProcessVerifyCertOperation();
        break;
      #endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */
      case KEYM_NO_JOB:
      default:
        /*Do nothing */
        break;
    }
  }
  else
  {
    /* Do nothing */
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)

#if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_BackgroundKeyUpdate                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function perform key update operation in main    **
**                      background function                                   **
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
** Return parameter   : void                                                  **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_BackGroundDone, KeyM_JobState, KeyM_PtrKeyName,  **
**                      KeyM_KeyNameLength, KeyM_OperationResult              **
**                      KeyM_PtrResultData, KeyM_PtrRequestData,              **
**                      KeyM_RequestDataLength, KeyM_DataBuffer, KeyM_KeyId,  **
**                      KeyM_DataBufferLength, KeyM_HandlerUpdateNextKey,     **
**                      KeyM_HandlerUpdateOperation                           **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_KH_Verify                                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static void KeyM_BackgroundKeyUpdate(void)
{
  Std_ReturnType retVal;
  KeyM_ResultType operationResult;
  KeyM_KH_UpdateOperationType updateOperationKH;

  /* @Trace: KeyM_SUD_FUNC_169 */
  updateOperationKH = KEYM_KH_UPDATE_KEY_UPDATE_REPEAT;
  KeyM_DataBufferLength = KEYM_INTERAL_BUFFER_LENGTH;

  /* Delegate the operation to the handler */
  retVal = KeyM_KH_Update(KeyM_PtrKeyName, \
    KeyM_KeyNameLength, \
    KeyM_PtrRequestData, \
    KeyM_RequestDataLength, \
    KeyM_DataBuffer, \
    &KeyM_DataBufferLength, \
    &KeyM_KeyId, \
    &updateOperationKH);

  if ((E_OK == retVal) && \
    (KeyM_DataBufferLength > KEYM_ZERO) && \
    (KEYM_KH_UPDATE_KEY_UPDATE_REPEAT == updateOperationKH) && \
    (KEYM_TOTAL_KEY > KeyM_KeyId))
  {
    /* Set the flag to indicate that there is next key update
      request */
    KeyM_HandlerUpdateNextKey = KEYM_TRUE;
    operationResult = KEYM_RT_OK;
  }
  else if ((E_OK == retVal) && \
    (KEYM_KH_UPDATE_FINISH == updateOperationKH))
  {
    /* In this case, set the job state to be completed and the
      update operation result is OK, the update
      operation has finished */
    operationResult = KEYM_RT_OK;
    KeyM_HandlerUpdateNextKey = KEYM_FALSE;
    KeyM_JobState = KEYM_COMPLETE;
  }
  else
  {
    /* In this case, set the job state to be completed and the
      update operation result, the update operation has finished */
    /* @Trace: KeyM_SUD_FUNC_170 */
    if (KEYM_E_KEY_CERT_WRITE_FAIL == retVal)
    {
      operationResult = KEYM_RT_KEY_CERT_WRITE_FAIL;
    }
    else if (KEYM_E_KEY_CERT_UPDATE_FAIL == retVal)
    {
      operationResult = KEYM_RT_KEY_CERT_UPDATE_FAIL;
    }
    else if (KEYM_E_PARAMETER_MISMATCH == retVal)
    {
      operationResult = KEYM_RT_PARAMETER_MISMATCH;
    }
    else
    {
      operationResult = KEYM_RT_NOT_OK;
    }

    KeyM_HandlerUpdateNextKey = KEYM_FALSE;
    KeyM_JobState = KEYM_COMPLETE;
  }

  KeyM_OperationResult = operationResult;
  KeyM_HandlerUpdateOperation = updateOperationKH;
  /* Set this flag to TRUE to indicate that the Key update handler
    has done, and then it allows processing of key update operation
    in the Main function */
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  KeyM_BackGroundDone = KEYM_TRUE;
  SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON */

#if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_BackgroundKeyFinalize                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function perform key finalize operation in main  **
**                      background function                                   **
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
** Return parameter   : void                                                  **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_BackGroundDone, KeyM_PtrRequestData,             **
**                      KeyM_RequestDataLength, KeyM_ResultDataMaxLength,     **
**                      KeyM_HandlerRetVal                                    **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_KH_Finalize                                      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static void KeyM_BackgroundKeyFinalize(void)
{
  Std_ReturnType retVal;

  /* @Trace: KeyM_SUD_FUNC_172 */
  /* Delegate the operation to the handler */
  retVal = KeyM_KH_Finalize(KeyM_PtrRequestData, KeyM_RequestDataLength, \
    KeyM_PtrResultData, &KeyM_ResultDataMaxLength);
  /* Save the returned value of handler, it will be used in
     the Main function */
  KeyM_HandlerRetVal = retVal;
  /* Set this flag to TRUE to indicate that the Key finalize handler
    has done, and then it allows processing of key finalize operation
    in the Main function */
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  KeyM_BackGroundDone = KEYM_TRUE;
  SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */
#endif /* KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */

#if (KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_BackgroundKeyVerify                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function perform key verify operation in main    **
**                      background function                                   **
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
** Return parameter   : void                                                  **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_BackGroundDone, KeyM_JobState, KeyM_PtrKeyName,  **
**                      KeyM_KeyNameLength, KeyM_OperationResult              **
**                      KeyM_PtrResultData, KeyM_PtrRequestData,              **
**                      KeyM_RequestDataLength, KeyM_PtrResultDataLength      **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_KH_Verify                                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static void KeyM_BackgroundKeyVerify(void)
{
  Std_ReturnType retVal;
  KeyM_ResultType operationResult;

  /* @Trace: KeyM_SUD_FUNC_173 */
  /* Delegate the operation to the handler */
  retVal = KeyM_KH_Verify(KeyM_PtrKeyName, KeyM_KeyNameLength, \
    KeyM_PtrRequestData, KeyM_RequestDataLength, \
    KeyM_PtrResultData, KeyM_PtrResultDataLength);

  /* Update verify operation result based on the returned value of handler, \
     this will be used by verify callback in the Main function */
  if (E_OK == retVal)
  {
    operationResult = KEYM_RT_OK;
  }
  else if (KEYM_E_KEY_CERT_SIZE_MISMATCH == retVal)
  {
    operationResult = KEYM_RT_KEY_CERT_SIZE_MISMATCH;
  }
  else if (KEYM_E_PARAMETER_MISMATCH == retVal)
  {
    operationResult = KEYM_RT_PARAMETER_MISMATCH;
  }
  else
  {
    operationResult = KEYM_RT_NOT_OK;
  }

  KeyM_OperationResult = operationResult;
  /* The verify operation is performed synchronously by verify handler, \
     thus after the handler has finished, set job state to be completed */
  KeyM_JobState = KEYM_COMPLETE;
  /* Set this flag to TRUE to indicate that the Key verify handler
     has done, and then it allows processing of key verify operation
     in the Main function */
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  KeyM_BackGroundDone = KEYM_TRUE;
  SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON */
#endif /* KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON */
#endif /* KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON */

#endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */

#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_BackgroundCertificateService                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function perform Service Certificate operation   **
**                      in main background function                           **
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
** Return parameter   : void                                                  **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_BackGroundDone, KeyM_JobState, KeyM_CertService, **
**                      KeyM_PtrCertName, KeyM_CertNameLength,                **
**                      KeyM_PtrResultData, KeyM_PtrRequestData,              **
**                      KeyM_RequestDataLength, KeyM_ResultDataMaxLength      **
**                      KeyM_OperationResult                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_KH_ServiceCertificate,                           **
**                      KeyM_PrvPerformServiceCertificateOperation            **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static void KeyM_BackgroundCertificateService(void)
{
  #if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_ON)
    Std_ReturnType retVal;
    KeyM_ResultType operationResult;
    /* @Trace: KeyM_SUD_FUNC_176 */
    retVal = KeyM_KH_ServiceCertificate(KeyM_CertService,\
      KeyM_PtrCertName,\
      KeyM_CertNameLength,\
      KeyM_PtrRequestData,\
      KeyM_RequestDataLength,\
      KeyM_PtrResultData,\
      &KeyM_ResultDataMaxLength);
    /* Update operation result based on the returned value of handler, \
      this will be used by callback function in the Main function */
    if (E_OK == retVal)
    {
      operationResult = KEYM_RT_OK;
    }
    else if (E_NOT_OK == retVal)
    {
      operationResult = KEYM_RT_NOT_OK;
    }
    else if (KEYM_E_PARAMETER_MISMATCH == retVal)
    {
      operationResult = KEYM_RT_PARAMETER_MISMATCH;
    }
    else
    {
      operationResult = KEYM_RT_KEY_CERT_SIZE_MISMATCH;
    }

    KeyM_OperationResult = operationResult;
    /* The ServiceCertificate operation is performed by the handler, \
      thus after the handler has finished, set job state to be completed */
    KeyM_JobState = KEYM_COMPLETE;
  #else
    /* @Trace: KeyM_SUD_FUNC_175 */
    /* Perform ServiceCertificate operation */
    KeyM_PrvPerformServiceCertificateOperation();
  #endif /* KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_ON */

  /* Set this flag to TRUE to indicate that the ServiceCertificate
    operation in the background main function has done, \
    and then it allows processing of this operation
    in the Main function */
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  KeyM_BackGroundDone = KEYM_TRUE;
  SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON */

/*******************************************************************************
** Function Name      : KeyM_BackgroundCertificatesVerify                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function perform Verify Certificates operation   **
**                      in main background function                           **
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
** Return parameter   : void                                                  **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_BackGroundDone, KeyM_JobState, KeyM_CryptoCert,  **
**                      KeyM_CertId, KeyM_UpperCertId                         **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvPerformVerifyCertPairOperation                **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static void KeyM_BackgroundCertificatesVerify(void)
{
  /* @Trace: KeyM_SUD_FUNC_178 */
  if ((KEYM_TOTAL_CERTIFICATE > KeyM_CertId) && \
    (KEYM_TOTAL_CERTIFICATE > KeyM_UpperCertId))
  {
    /* Perform VerifyCertificates operation */
    KeyM_PrvPerformVerifyCertPairOperation(&KeyM_CryptoCert[KeyM_CertId], \
      &KeyM_CryptoCert[KeyM_UpperCertId]);
    SchM_Enter_KeyM_GLOBALVAR_PROTECTION();      
    /* The verify certificate operation has finished, \
       set job state to be completed */
    KeyM_JobState = KEYM_COMPLETE;
    /* Set this flag to TRUE to indicate that the VerifyCertificates
      operation in the background main function has done, \
      and then it allows processing of certificate verify operation
      in the Main function */
    KeyM_BackGroundDone = KEYM_TRUE;
    SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_BackgroundCertificateVerify                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function perform Verify Certificate operation    **
**                      in main background function                           **
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
** Return parameter   : void                                                  **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_BackGroundDone, KeyM_JobState,KeyM_CryptoCert,   **
**                      KeyM_CertId                                           **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvPerformVerifyCertOperation                    **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static void KeyM_BackgroundCertificateVerify(void)
{
  /* @Trace: KeyM_SUD_FUNC_179 */
  if (KEYM_TOTAL_CERTIFICATE > KeyM_CertId)
  {
    /* Perform VerifyCertificate operation */
    KeyM_PrvPerformVerifyCertOperation(&KeyM_CryptoCert[KeyM_CertId]);
    SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
    /* The verify certificate operation has finished, \
       set job state to be completed */
    KeyM_JobState = KEYM_COMPLETE;
    /* Set this flag to TRUE to indicate that the VerifyCertificates
      operation in the background main function has done, \
      and then it allows processing of certificate verify operation
      in the Main function */
    KeyM_BackGroundDone = KEYM_TRUE;
    SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_BackgroundCertificateChainVerify                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This function perform VerifyCertificateChain operation**
**                      in main background function                           **
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
** Return parameter   : void                                                  **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_BackGroundDone, KeyM_JobState                    **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvPerformVerifyCertChainOperation               **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static void KeyM_BackgroundCertificateChainVerify(void)
{
  /* @Trace: KeyM_SUD_FUNC_180 */
  /* Perform VerifyCertificateChain operation */
  KeyM_PrvPerformVerifyCertChainOperation();

  /* The verify certificate operation has finished,
     set job state to be completed */
  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  KeyM_JobState = KEYM_COMPLETE;
  /* Set this flag to TRUE to indicate that the VerifyCertificateChain
    operation in the background main function has done,
    and then it allows processing of certificate verify operation
    in the Main function */
  KeyM_BackGroundDone = KEYM_TRUE;
  SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

/*******************************************************************************
** Function Name      : KeyM_MainBackgroundFunction                           **
**                                                                            **
** Service ID         : 0x1a                                                  **
**                                                                            **
** Description        : Function is called from a pre-emptive operating system**
**                      when no other task operation is needed. Can be used   **
**                      for calling time consuming synchronous functions such **
**                      as KeyM_KH_Update().                                  **
**                                                                            **
** Sync/Async         : None                                                  **
**                                                                            **
** Re-entrancy        : None                                                  **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : KeyM must be initialized                              **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_ModuleState, KeyM_CurrentJob, KeyM_CryptoCert,   **
**                      KeyM_BackGroundDone                                   **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError, KeyM_BackgroundKeyUpdate,            **
**                      KeyM_BackgroundKeyFinalize,                           **
**                      KeyM_BackgroundKeyVerify,                             **
**                      KeyM_BackgroundCertificateService,                    **
**                      KeyM_BackgroundCertificatesVerify,                    **
**                      KeyM_BackgroundCertificateVerify,                     **
**                      KeyM_BackgroundCertificateChainVerify,                **
**                      KeyM_PrvParseCertificate                              **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_MainBackgroundFunction(void)
{
  #if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
    uint16 indexCnt;
    P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert;
  #endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */
  KeyM_RequestJobType currentJob = KEYM_NO_JOB;
  KeyM_StateType moduleState = KEYM_IDLE;

  SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
  moduleState = KeyM_ModuleState;
  SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
  /* @Trace: KeyM_SUD_FUNC_161 */
  /* Check for initialization status of KeyM */
  if (KEYM_UNINIT != moduleState)
  {
    SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
    if (KEYM_FALSE == KeyM_BackGroundDone)
    {
      currentJob = KeyM_CurrentJob;
      SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
      switch (currentJob)
      {
        #if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)
        case KEYM_UPDATE_JOB:
          #if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
            /* @Trace: KeyM_SUD_FUNC_103 */
            KeyM_BackgroundKeyUpdate();
          #endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON */
          break;
        #if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
        case KEYM_FINALIZE_JOB:
          #if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
            /* @Trace: KeyM_SUD_FUNC_162 */
            KeyM_BackgroundKeyFinalize();
          #endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */
          break;
        #endif /* KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */

        #if (KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON)
        case KEYM_VERIFY_JOB:
          #if (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON)
            #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON)
              /* @Trace: KeyM_SUD_FUNC_163 */
              KeyM_BackgroundKeyVerify();
            #endif /* KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON */
          #endif /* KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON */
          break;
        #endif /* KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON */
        #endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */
        #if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
        #if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
        case KEYM_SERVICE_CERTIFICATE_JOB:
          /* @Trace: KeyM_SUD_FUNC_164 */
          KeyM_BackgroundCertificateService();
          break;
        #endif /* KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON */
        case KEYM_VERIFY_CERTIFICATES_JOB:
          /* @Trace: KeyM_SUD_FUNC_165 */
          KeyM_BackgroundCertificatesVerify();
          break;
        case KEYM_VERIFY_CERTIFICATE_JOB:
          /* @Trace: KeyM_SUD_FUNC_166 */
          KeyM_BackgroundCertificateVerify();
          break;
        case KEYM_VERIFY_CERTIFICATECHAIN_JOB:
          /* @Trace: KeyM_SUD_FUNC_167 */
          KeyM_BackgroundCertificateChainVerify();
          break;
        #endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */
        case KEYM_NO_JOB:
        default:
          /* @Trace: KeyM_SUD_FUNC_168 */
          #if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
          for (indexCnt = KEYM_ZERO; KEYM_TOTAL_CERTIFICATE > indexCnt; indexCnt++)
          {
            ptrCert = &KeyM_CryptoCert[indexCnt];
            if (KEYM_CERTIFICATE_NOT_PARSED == ptrCert->CertStatus)
            {
              /* The certificate parsing is started */
              SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
              ptrCert->InProgress = KEYM_ONE;
              SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
              /* At here, certificate parsing process always successful */
              KeyM_PrvParseCertificate(ptrCert, \
                ptrCert->PtrCertData, ptrCert->CertLength);
              /* The certificate parsing is finished */
              SchM_Enter_KeyM_GLOBALVAR_PROTECTION();
              ptrCert->InProgress = KEYM_ZERO;
              SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
            }
          } /* @for (indexCnt = KEYM_ZERO; KEYM_TOTAL_KEY > indexCnt; indexCnt++) */
          #endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */
          break;
      }
    }
    else
    {
      SchM_Exit_KeyM_GLOBALVAR_PROTECTION();
    }
  }
  else
  {
    /* Do nothing */
  }
  KEYM_UNUSED(currentJob);
  KEYM_UNUSED(moduleState);
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
