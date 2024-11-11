/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_Ram.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key Manager RAM variable definitions                          **
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
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM Ram variables header file */
#include "KeyM_Ram.h"

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
/* Global variable to store the initialization status of Key manager */
VAR(KeyM_StateType, KEYM_VAR_INIT) KeyM_ModuleState = KEYM_UNINIT;
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)

#if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store the current status of update session */
VAR(boolean, KEYM_VAR_INIT) KeyM_SessionState \
= KEYM_SESSION_DEACTIVATED;
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store the start operation mode */
VAR(KeyM_StartType, KEYM_VAR_INIT) KeyM_StartOperationMode;
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global variable to store the start response data pointer */
P2CONST(uint8, KEYM_VAR_INIT, KEYM_APPL_CONST) KeyM_PtrStartRequestData;
/* Global variable to store the start request data length */
VAR(uint16, KEYM_VAR_INIT) KeyM_StartRequestDataLength;
/* Global variable to store the start response data pointer */
P2VAR(uint8, KEYM_VAR_INIT, KEYM_APPL_DATA) KeyM_PtrStartResponseData;
/* Global variable to store the start response data length pointer */
P2VAR(uint16, KEYM_VAR_INIT, KEYM_APPL_DATA) KeyM_PtrStartResponseDataLength;
/* Global variable to store the start response data length value */
VAR(uint16, KEYM_VAR_INIT) KeyM_StartResponseDataLength;
/* Internal buffer for KeyM Start operation */
VAR(uint8, KEYM_VAR_INIT) KeyM_StartDataBuffer[KEYM_INTERAL_BUFFER_LENGTH];
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */
#endif /* KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */

#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#if ((KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON) || \
    (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON))
/* Global variable to hold the pointer to key name data */
P2CONST(uint8, KEYM_VAR_INIT, KEYM_APPL_CONST) KeyM_PtrKeyName;
/* Global variable to hold the length of key name */
VAR(uint16, KEYM_VAR_INIT) KeyM_KeyNameLength;
#endif /* #if ((KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON) || \
              (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON)) */
/* Global variable to hold the current key ID */
VAR(KeyM_CryptoKeyIdType, KEYM_VAR_INIT) KeyM_KeyId;
/* Global variable is used as flag that indicates
  whether key handler updation requests a key updation */
VAR(boolean, KEYM_VAR_INIT) KeyM_HandlerUpdateNextKey;
#if (KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF)
/* Global variable to hold the length of respond data of key verify function */
VAR(uint32, KEYM_VAR_INIT) KeyM_VerifyRespondDataLength;
#endif /* (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF) */
#endif /* (KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON) */
#if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
/* Global variable to hold the handler update operation */
VAR(KeyM_KH_UpdateOperationType, KEYM_VAR_INIT) KeyM_HandlerUpdateOperation;
#endif /* (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON) */
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */

#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* Internal buffer for KeyM operation */
VAR(uint8, KEYM_VAR_INIT) KeyM_DataBuffer[KEYM_INTERAL_BUFFER_LENGTH];
#if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
/* Global variable to hold the length of actual data in the internal buffer */
VAR(uint16, KEYM_VAR_INIT) KeyM_DataBufferLength;
#endif /* (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON) */
/* Global variable to hold the pointer to request data buffer */
P2CONST(uint8, KEYM_VAR_INIT, KEYM_APPL_CONST) KeyM_PtrRequestData;
/* Global variable to hold the length of request data */
VAR(uint16, KEYM_VAR_INIT) KeyM_RequestDataLength;
/* Global variable to hold the pointer to response data buffer */
P2VAR(uint8, KEYM_VAR_INIT, KEYM_APPL_DATA) KeyM_PtrResultData;
#if ((KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON) && \
    (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON))
/* Global variable to hold the pointer to length of response data buffer */
P2VAR(uint16, KEYM_VAR_INIT, KEYM_APPL_DATA) KeyM_PtrResultDataLength;
/* Global variable to hold the CSM request result */
VAR(Csm_ResultType, KEYM_VAR_INIT) KeyM_CsmRequestResult;
/* Global variable is used as flag that indicates
  whether Csm request has finished */
VAR(boolean, KEYM_VAR_INIT) KeyM_CsmRequestDone;
#endif /* ((KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON) && \
          (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON)) */
/* Global variable to hold the length of response data buffer */
VAR(uint16, KEYM_VAR_INIT) KeyM_ResultDataMaxLength;
/* Global variable is used as flag that indicates
  whether background task has done */
VAR(boolean, KEYM_VAR_INIT) KeyM_BackGroundDone;
#if ((KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON) && \
    (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON))
/* Global variable to hold the key handler return value */
VAR(Std_ReturnType, KEYM_VAR_INIT) KeyM_HandlerRetVal;
#endif /* ((KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON) && \
          (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)) */
/* Global variable to hold the current request */
VAR(KeyM_RequestJobType, KEYM_VAR_INIT) KeyM_CurrentJob;
/* Global variable to hold a job state */
VAR(KeyM_JobStateType, KEYM_VAR_INIT) KeyM_JobState;
/* Global variable to hold the operation result */
VAR(KeyM_ResultType, KEYM_VAR_INIT) KeyM_OperationResult;
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global variable to hold the current certificate ID */
VAR(KeyM_CertificateIdType, KEYM_VAR_INIT) KeyM_CertId;
/* Global variable to hold the upper certificate ID */
VAR(KeyM_CertificateIdType, KEYM_VAR_INIT) KeyM_UpperCertId;
/* Global variable to hold the certificate chain data */
P2CONST(KeyM_CertDataType, KEYM_VAR_INIT, KEYM_APPL_CONST) KeyM_CertChainData;
/* Global variable to hold the length of the intermediate chain */
VAR(uint8, KEYM_VAR_INIT) KeyM_NumberOfCertificates;

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
/* Global variable to hold the certificate service */
VAR(KeyM_ServiceCertificateType, KEYM_VAR_INIT) KeyM_CertService;
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_ON)
/* Global variable to hold the pointer to cert name data */
P2CONST(uint8, KEYM_VAR_INIT, KEYM_CONST) KeyM_PtrCertName;
/* Global variable to hold the length of cert name */
VAR(uint16, KEYM_VAR_INIT) KeyM_CertNameLength;
#endif /* (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_ON) */
#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

#if (KEYM_CERTIFICATE_CHAIN_MAX_DEPTH > 0U)
/* Current certificate chain */
VAR(uint16, KEYM_VAR_INIT) KeyM_CertChain[KEYM_CERTIFICATE_CHAIN_MAX_DEPTH];
/* Global variable to hold the actual length of current certificate chain */
VAR(uint8, KEYM_VAR_INIT) KeyM_CertChainLength;
#endif /* (KEYM_CERTIFICATE_CHAIN_MAX_DEPTH > 0U) */
#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
