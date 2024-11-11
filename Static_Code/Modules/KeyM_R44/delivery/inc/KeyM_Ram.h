/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_Ram.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key Manager RAM variable declaration                          **
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
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
#ifndef KEYM_RAM_H
#define KEYM_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM Header file */
#include "KeyM.h"
/* KeyM Types Header file */
#include "KeyM_IntType.h"
/* Rte type header file */
#include "Rte_Type.h"

#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
/* KeyM X509 CRT Header file */
#include "KeyM_X509_Crt.h"
/* KeyM X509 CRT Header file */
#include "KeyM_X509_Crl.h"
/* KeyM CVC Header file */
#include "KeyM_Cvc.h"
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: KeyM_SUD_GLOBALVAR_001 */
/* Global variable to store the initialization status of Key manager */
extern VAR(KeyM_StateType, KEYM_VAR_INIT) KeyM_ModuleState;
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)

#if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)

#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: KeyM_SUD_GLOBALVAR_002 */
/* Global variable to store the current status of update session */
extern VAR(boolean, KEYM_VAR_INIT) KeyM_SessionState;
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: KeyM_SUD_GLOBALVAR_031 */
/* Global variable to store the start operation mode */
extern VAR(KeyM_StartType, KEYM_VAR_INIT) KeyM_StartOperationMode;
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: KeyM_SUD_GLOBALVAR_012 */
/* Global variable to store the start response data pointer */
extern P2CONST(uint8, KEYM_VAR_INIT, KEYM_APPL_CONST) KeyM_PtrStartRequestData;
/* @Trace: KeyM_SUD_GLOBALVAR_014 */
/* Global variable to store the start response data pointer */
extern P2VAR(uint8, KEYM_VAR_INIT, KEYM_APPL_DATA) KeyM_PtrStartResponseData;
/* @Trace: KeyM_SUD_GLOBALVAR_015 */
/* Global variable to store the start response data length pointer */
extern P2VAR(uint16, KEYM_VAR_INIT, KEYM_APPL_DATA) \
  KeyM_PtrStartResponseDataLength;
/* @Trace: KeyM_SUD_GLOBALVAR_013 */
/* Global variable to store the start request data length */
extern VAR(uint16, KEYM_VAR_INIT) KeyM_StartRequestDataLength;
/* @Trace: KeyM_SUD_GLOBALVAR_016 */
/* Global variable to store the start response data length value */
extern VAR(uint16, KEYM_VAR_INIT) KeyM_StartResponseDataLength;
/* @Trace: KeyM_SUD_GLOBALVAR_017 */
/* Internal buffer for KeyM Start operation */
extern VAR(uint8, KEYM_VAR_INIT) KeyM_StartDataBuffer[KEYM_INTERAL_BUFFER_LENGTH];
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */
#endif /* KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */

#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#if ((KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON) || \
    (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON))
/* @Trace: KeyM_SUD_GLOBALVAR_018 */
/* Global variable to hold the pointer to key name data */
extern P2CONST(uint8, KEYM_VAR_INIT, KEYM_APPL_CONST) KeyM_PtrKeyName;
/* @Trace: KeyM_SUD_GLOBALVAR_022 */
/* Global variable to hold the length of key name */
extern VAR(uint16, KEYM_VAR_INIT) KeyM_KeyNameLength;
#endif /* #if ((KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON) || \
              (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON)) */
/* @Trace: KeyM_SUD_GLOBALVAR_023 */
/* Global variable to hold the current key ID */
extern VAR(KeyM_CryptoKeyIdType, KEYM_VAR_INIT) KeyM_KeyId;
/* @Trace: KeyM_SUD_GLOBALVAR_024 */
/* Global variable is used as flag that indicates whether key handler updation requests a key updation */
extern VAR(boolean, KEYM_VAR_INIT) KeyM_HandlerUpdateNextKey;
#if (KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF)
/* @Trace: KeyM_SUD_GLOBALVAR_025 */
/* Global variable to hold the length of respond data of key verify function */
extern VAR(uint32, KEYM_VAR_INIT) KeyM_VerifyRespondDataLength;
#endif /* (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF) */
#endif /* (KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON) */
#if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
/* @Trace: KeyM_SUD_GLOBALVAR_026 */
/* Global variable to hold the handler update operation */
extern VAR(KeyM_KH_UpdateOperationType, KEYM_VAR_INIT) \
  KeyM_HandlerUpdateOperation;
#endif /* (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON) */
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#if (KEYM_TOTAL_KEY > 0U)
#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: KeyM_SUD_GLOBALVAR_021 */
/* KeyM crypto key configuration array */
extern VAR(KeyM_CryptoKeyType, KEYM_VAR_INIT) KeyM_CryptoKey[KEYM_TOTAL_KEY];
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* (KEYM_TOTAL_KEY > 0U) */

#endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */

#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: KeyM_SUD_GLOBALVAR_003 */
/* Internal buffer for KeyM operation */
extern VAR(uint8, KEYM_VAR_INIT) KeyM_DataBuffer[KEYM_INTERAL_BUFFER_LENGTH];
#if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
/* @Trace: KeyM_SUD_GLOBALVAR_027 */
/* Global variable to hold the length of actual data in the internal buffer */
extern VAR(uint16, KEYM_VAR_INIT) KeyM_DataBufferLength;
#endif /* (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON) */
/* @Trace: KeyM_SUD_GLOBALVAR_005 */
/* Global variable to hold the length of request data */
extern VAR(uint16, KEYM_VAR_INIT) KeyM_RequestDataLength;
/* @Trace: KeyM_SUD_GLOBALVAR_007 */
/* Global variable to hold the length of response data buffer */
extern VAR(uint16, KEYM_VAR_INIT) KeyM_ResultDataMaxLength;
/* @Trace: KeyM_SUD_GLOBALVAR_004 */
/* Global variable to hold the pointer to request data buffer */
extern P2CONST(uint8, KEYM_VAR_INIT, KEYM_APPL_CONST) KeyM_PtrRequestData;
/* @Trace: KeyM_SUD_GLOBALVAR_006 */
/* Global variable to hold the pointer to response data buffer */
extern P2VAR(uint8, KEYM_VAR_INIT, KEYM_APPL_DATA) KeyM_PtrResultData;
#if ((KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON) && \
    (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON))
/* @Trace: KeyM_SUD_GLOBALVAR_028 */
/* Global variable to hold the pointer to length of response data buffer */
extern P2VAR(uint16, KEYM_VAR_INIT, KEYM_APPL_DATA) KeyM_PtrResultDataLength;
/* @Trace: KeyM_SUD_GLOBALVAR_019 */
/* Global variable to hold the CSM request result */
extern VAR(Csm_ResultType, KEYM_VAR_INIT) KeyM_CsmRequestResult;
/* @Trace: KeyM_SUD_GLOBALVAR_029 */
/* Global variable is used as flag that indicates
  whether Csm request has finished */
extern VAR(boolean, KEYM_VAR_INIT) KeyM_CsmRequestDone;
#endif /* ((KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON) && \
         (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON)) */
/* @Trace: KeyM_SUD_GLOBALVAR_020 */
/* Global variable is used as flag that indicates
  whether key handler has done */
extern VAR(boolean, KEYM_VAR_INIT) KeyM_BackGroundDone;
#if ((KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON) && \
    (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON))
/* @Trace: KeyM_SUD_GLOBALVAR_008 */
/* Global variable to hold the key handler return value */
extern VAR(Std_ReturnType, KEYM_VAR_INIT) KeyM_HandlerRetVal;
#endif /* ((KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON) && \
          (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)) */
/* @Trace: KeyM_SUD_GLOBALVAR_009 */
/* Global variable to hold the current request */
extern VAR(KeyM_RequestJobType, KEYM_VAR_INIT) KeyM_CurrentJob;
/* @Trace: KeyM_SUD_GLOBALVAR_010 */
/* Global variable to hold a job state */
extern VAR(KeyM_JobStateType, KEYM_VAR_INIT) KeyM_JobState;
/* @Trace: KeyM_SUD_GLOBALVAR_011 */
/* Global variable to hold the operation result */
extern VAR(KeyM_ResultType, KEYM_VAR_INIT) KeyM_OperationResult;
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: KeyM_SUD_GLOBALVAR_038 */
/* Global variable to hold the current certificate ID */
extern VAR(KeyM_CertificateIdType, KEYM_VAR_INIT) KeyM_CertId;
/* @Trace: KeyM_SUD_GLOBALVAR_032 */
/* Global variable to hold the upper certificate ID */
extern VAR(KeyM_CertificateIdType, KEYM_VAR_INIT) KeyM_UpperCertId;
/* @Trace: KeyM_SUD_GLOBALVAR_039 */
/* Global variable to hold the intermediate certificate chain data */
extern P2CONST(KeyM_CertDataType, KEYM_VAR_INIT, KEYM_APPL_CONST) \
  KeyM_CertChainData;
/* @Trace: KeyM_SUD_GLOBALVAR_033 */
/* Global variable to hold the length of the intermediate chain */
extern VAR(uint8, KEYM_VAR_INIT) KeyM_NumberOfCertificates;

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
/* @Trace: KeyM_SUD_GLOBALVAR_040 */
/* Global variable to hold the certificate service */
extern VAR(KeyM_ServiceCertificateType, KEYM_VAR_INIT) KeyM_CertService;
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_ON)
/* @Trace: KeyM_SUD_GLOBALVAR_034 */
/* Global variable to hold the pointer to cert name data */
extern P2CONST(uint8, KEYM_VAR_INIT, KEYM_APPL_CONST) KeyM_PtrCertName;
/* @Trace: KeyM_SUD_GLOBALVAR_041 */
/* Global variable to hold the length of cert name */
extern VAR(uint16, KEYM_VAR_INIT) KeyM_CertNameLength;
#endif /* (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_ON) */
#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

#if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
/* @Trace: KeyM_SUD_GLOBALDATA_001 */
/* Global array to hold the id of certificate revocation lists */
extern CONST(uint16, KEYM_CONST) KeyM_CertRevocationListId[KEYM_CERT_REVOCATION_LIST_NUM];
#endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */

#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: KeyM_SUD_GLOBALVAR_035 */
/* Array to hold the current certificate chain */
extern VAR(uint16, KEYM_VAR_INIT) KeyM_CertChain[KEYM_CERTIFICATE_CHAIN_MAX_DEPTH];
/* @Trace: KeyM_SUD_GLOBALVAR_042 */
/* Global variable to hold the actual length of current certificate chain */
extern VAR(uint8, KEYM_VAR_INIT) KeyM_CertChainLength;
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: KeyM_SUD_GLOBALVAR_037 */
/* KeyM crypto certificate configuration array */
extern VAR(KeyM_CertType, KEYM_VAR_INIT) KeyM_CryptoCert[KEYM_TOTAL_CERTIFICATE];
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */


#endif /* KEYM_RAM_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
