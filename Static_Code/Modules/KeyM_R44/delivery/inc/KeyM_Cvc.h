/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_Cvc.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key manager internal header file for CVC                      **
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
#ifndef KEYM_CVC_H
#define KEYM_CVC_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM Types Header file */
#include "KeyM_IntType.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
#if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
/* @Trace: KeyM_SUD_MACRO_008 */
/* The tag number for DER encoded CVC types */
#define KEYM_CVC_OBJECT_IDENTIFIER                            (0x06U)
#define KEYM_CVC_CERTIFICATE_AUTHORITY_REFERENCE              (0x42U)
#define KEYM_CVC_DISCRETIONARY_DATA                           (0x53U)
#define KEYM_CVC_CERTIFICATE_HOLDER_REFERENCE                 (0x20U)
#define KEYM_CVC_CERTIFICATE_EXPIRATION_DATE                  (0x24U)
#define KEYM_CVC_CERTIFICATE_EFFECTIVE_DATE                   (0x25U)
#define KEYM_CVC_CERTIFICATE_PROFILE_IDENTIFIER               (0x29U)
#define KEYM_CVC_SIGNATURE                                    (0x37U)
#define KEYM_CVC_CERTIFICATE_EXTENSIONS                       (0x65U)
#define KEYM_CVC_AUTHENTICATION                               (0x67U)
#define KEYM_CVC_DISCRETIONARY_DATA_TEMPLATE                  (0x73U)
#define KEYM_CVC_CERTIFICATE                                  (0x21U)
#define KEYM_CVC_PUBLIC_KEY                                   (0x49U)
#define KEYM_CVC_CERTIFICATE_HOLDER_AUTHORIZATION_TEMPLATE    (0x4CU)
#define KEYM_CVC_CERTIFICATE_BODY                             (0x4EU)
#define KEYM_CVC_COMPOSITE_MODULUS                            (0x81U)
#define KEYM_CVC_PUBLIC_EXPONENT                              (0x82U)
#define KEYM_CVC_PRIME_MODULUS                                (0x81U)
#define KEYM_CVC_ORDER_OF_THE_SUBGROUP                        (0x82U)
#define KEYM_CVC_GENERATOR                                    (0x83U)
#define KEYM_CVC_PUBLIC_VALUE                                 (0x84U)
#define KEYM_CVC_FIRST_COEFFCIENT                             (0x82U)
#define KEYM_CVC_SECOND_COEFFCIENT                            (0x83U)
#define KEYM_CVC_BAS_POINT                                    (0x84U)
#define KEYM_CVC_ORDER_OF_THE_BASE_POINT                      (0x85U)
#define KEYM_CVC_PUBLIC_POINT                                 (0x86U)
#define KEYM_CVC_COFACTOR                                     (0x87U)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* @Trace: KeyM_SUD_DATATYPE_049 */
/* Structure for an CVC certificate. */
typedef struct
{
  /* The raw certificate body (DER). The part that is To Be Signed */
  KeyM_AsnElementType TBSCert;
  /* The raw CVC Certificate Profile Identifier */
  KeyM_ElementType * PtrRawProfileId;
  /* The raw Certificate Authority Reference  */
  KeyM_ElementType * PtrRawAuthorityRefer;
  /* The raw Public Key Object Identifier  */
  KeyM_ElementType * PtrRawPublicKeyObjectId;
  /* The raw Holder Reference */
  KeyM_ElementType * PtrRawHolderRefer;
  /* The raw Holder Authorization Template */
  KeyM_ElementType * PtrRawHolderAuthorTemplate;
  /* The raw Effective Date */
  KeyM_ElementType * PtrRawEffectiveDate;
  /* The raw Expiration Date */
  KeyM_ElementType * PtrRawExpirationDate;
  /* Signature value of the tbs part signed with the private key */
  KeyM_ElementType * PtrSignatureValue;
  /* Optional extensions */
  KeyM_ElementType * PtrExtensions;
  /* The raw Public Key Domain Parameters */
  KeyM_ElementType * PtrPublicKeyDomainParams;
  /* Parsed Effective Date of validity period in seconds */
  uint64 EffectiveDate;
  /* Parsed Expiration Date of validity period in seconds */
  uint64 ExpirationDate;
  /* Public key type */
  uint8 PublicKeyType;
  /* Number of extensions */
  uint8 ExtensionNum;
  /* Number of domain paramters */
  uint8 DomainParamNum;
} KeyM_CvcCertificateType;

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvCvcCertificateParseDer(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  const uint16 dataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvCvcCertificatePairVerify(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrUpperCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvCopyParsedCVCCertificate(\
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrSrcCert, \
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrDesCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvCvcCheckParent(\
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrChild, \
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParent);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcElementGetCount(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcElementGetByIndex(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  VAR(uint32, AUTOMATIC) indexCnt, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcElementGet(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcElementGetFirst(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(KeyM_CertElementIteratorType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrCertElementIterator, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcElementGetNext(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(KeyM_CertElementIteratorType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrCertElementIterator, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvAdjustCvcCertificate(\
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCurAddress, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrNewAddress);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvRecoverCvcCertificate(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcCertificateGenerate(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) */
#endif /* (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF) */
#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

#endif /* (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */
#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */
#endif /* KEYM_CVC_H */
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
