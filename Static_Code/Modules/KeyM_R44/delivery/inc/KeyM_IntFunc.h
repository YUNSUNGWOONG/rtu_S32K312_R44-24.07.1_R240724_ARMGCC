/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_IntFunc.h                                                **
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
** 1.0.2     08-Nov-2021   TamTV6       Implement #20971                      **
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
** 1.0.7.0   07-Apr-2023   PhuocLH9     #CP44-1636,#CP44-1664                 **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
#ifndef KEYM_INT_FUNC_H
#define KEYM_INT_FUNC_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM Types Header file */
#include "KeyM_IntType.h"
/* KeyM Header file */
#include "KeyM.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvMemCmp(\
  P2CONST(void, AUTOMATIC, KEYM_APPL_CONST) ptrSrcData, \
  P2CONST(void, AUTOMATIC, KEYM_APPL_CONST) ptrDesData, \
  CONST(uint32, KEYM_CONST) dataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvMemCopy(\
  P2CONST(void, AUTOMATIC, KEYM_APPL_CONST) ptrSrcData, \
  P2VAR(void, AUTOMATIC, KEYM_APPL_DATA) ptrDesData, \
  CONST(uint32, KEYM_CONST) dataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvMemClear(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSrcData, \
  CONST(uint32, KEYM_CONST) dataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvGetKeyIndexByName(\
  P2VAR(void, AUTOMATIC, KEYM_APPL_DATA) ptrKeyArray, \
  const uint16 keyArrayLength, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrKeyName, \
  const uint16 nameLength, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrKeyIndex);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_ADDITIONAL_HINT_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvGetKeyIndexByExtractedSHEKeyId(\
  P2CONST(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_DATA) ptrKey, \
  const uint16 keyArrayLength, \
  const uint8 extractedSHEKeyId, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrKeyIndex);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CRYPTO_KEY_ADDITIONAL_HINT_ENABLED == STD_ON) */

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvProcessUpdateOperation(void);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvProcessFinalizeOperation(void);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */

#if (KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvPerformVerifyOperation(\
  P2CONST(KeyM_CryptoKeyType, AUTOMATIC, KEYM_APPL_DATA) ptrKey, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrRequestData, \
  VAR(uint16, AUTOMATIC) reqDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrResponseData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrResponseDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_OFF) */

#if (KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvProcessVerifyOperation(void);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvCsmCallback(\
  const uint32 csmJobID, Csm_ResultType csmResult);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE == STD_ON */
#endif /* KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON */

#endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON */

#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, KEYM_CODE) KeyM_PrvGetPublicKeyAlgorithmCount(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert \
  );
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"


#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvProcessVerifyCertOperation(void);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvPerformVerifyCertPairOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrUpperCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvPerformVerifyCertOperation(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrVerifiedCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvPerformVerifyCertChainOperation(void);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvPerformServiceCertificateOperation(void);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED ==
  STD_OFF) */

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvProcessServiceCertificateOperation(void);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvCheckCertificateElement(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  const uint16 elementIndex, \
  const uint8 tag, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  const uint16 objectIdLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_USE_STBM == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvGetCurrentTime(\
  StbM_SynchronizedTimeBaseType stbMTimeBaseId, \
  P2VAR(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrCurrentTime);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvParseInt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  const uint8 length, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) resultInt);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCheckDateValid(\
  P2CONST(KeyM_DateType, AUTOMATIC, KEYM_APPL_CONST) ptrDate, \
  const uint16 yearMax, \
  const uint16 yearMin);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvConvertDateToSecond(\
  P2CONST(KeyM_DateType, AUTOMATIC, KEYM_APPL_CONST) ptrDate, \
  P2VAR(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrSeconds);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvParseCertificate(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  const uint16 dataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvConstructCertChain(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvElementRuleVerify(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON) */

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvElementCopy(\
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrSrcElement, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrDesElement);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvElementGetByIndex(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  VAR(uint32, AUTOMATIC) indexCnt, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (((KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) && \
     (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) && \
      (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON) && \
      (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)) || \
     (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON))
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvConvertRsaPublicKeyFormat(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrModulus, \
  const uint16 modulusLen, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExponent, \
  const uint16 exponentLen, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPublicKeyData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKeyLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (((KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) && \
  (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) && \
  (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON) && \
  (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)) || \
  (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)) */

#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

#endif /* KEYM_INT_FUNC_H */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
