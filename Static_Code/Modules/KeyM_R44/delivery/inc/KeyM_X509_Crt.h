/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_X509_Crt.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key manager internal header file for X509 CRT                 **
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
#ifndef KEYM_X509_CRT_H
#define KEYM_X509_CRT_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM X509 header file */
#include "KeyM_X509.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
#if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
/* @Trace: KeyM_SUD_DATATYPE_052 */
/* Structure for an X.509 certificate. */
typedef struct
{
  /* The raw certificate body (DER). The part that is To Be Signed */
  KeyM_AsnElementType TBSCert;
  /* The raw X.509 version */
  KeyM_ElementType * PtrRawVersion;
  /* Unique id for certificate issued by a specific CA */
  KeyM_ElementType * PtrSerialNumber;
  /* Signature algorithm */
  KeyM_ElementType * PtrRawSignature;
  /* Raw not before date of certificate validity */
  KeyM_ElementType * PtrRawNotBefore;
  /* Raw not after date of certificate validity */
  KeyM_ElementType * PtrRawNotAfter;
  /* Container for the subject public key algorithm */
  KeyM_ElementType * PtrPublicKeyAlgorithm;
  /* Container for the subject public key value */
  KeyM_ElementType * PtrSubjectPublicKey;
  /* Optional X.509 v2/v3 issuer unique identifier */
  KeyM_ElementType * PtrIssuerUniqueID;
  /* Optional X.509 v2/v3 subject unique identifier */
  KeyM_ElementType * PtrSubjectUniqueID;
  /* Signature algorithm is used to sign Tbs part */
  KeyM_ElementType * PtrSignatureAlgorithm;
  /* Signature value of the tbs part signed with the private key */
  KeyM_ElementType * PtrSignatureValue;
  /* Optional X.509 v3 extensions */
  KeyM_ElementType * PtrExtensions;
  /* Parsed issuer */
  KeyM_ElementType * PtrIssuer;
  /* Parsed subject */
  KeyM_ElementType * PtrSubject;
  /* Parsed before date of certificate validity in seconds */
  uint64 NotBefore;
  /* Parsed after date of certificate validity in seconds */
  uint64 NotAfter;
  /* Public key type */
  uint8 PublicKeyType;
  /* Signature algorithm type */
  uint8 SignAlgType;
  /* Number of name in Issuer */
  uint8 IssuerNum;
  /* Number of name in Subject */
  uint8 SubjectNum;
  /* Number of extensions */
  uint8 ExtensionNum;
} KeyM_X509CertificateType;

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvX509CertificateParseDer(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  const uint16 dataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvX509CertCheckParent(\
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrChild, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParent);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvX509CertificatePairVerify(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrUpperCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvCopyParsedX509Certificate(\
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrSrcCert, \
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrDesCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvAdjustX509Certificate(\
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCurAddress, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrNewAddress);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvRecoverX509Certificate(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509CertificateGenerate(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) */
#endif /* (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF) */
#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

#endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

#endif /* KEYM_X509_CRT_H */
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
