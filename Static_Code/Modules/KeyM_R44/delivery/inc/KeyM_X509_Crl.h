/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_X509_Crl.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key manager internal header file for X509 CRL                 **
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
#ifndef KEYM_X509_CRL_H
#define KEYM_X509_CRL_H

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
#if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
/* @Trace: KeyM_SUD_DATATYPE_050 */
/* Certificate revocation list entry. Contains the CA-specific serial numbers
  and revocation dates. */
typedef struct
{
  /* Raw CRL entry */
  KeyM_ElementType RawCrlEntry;
  /* Revoked certificate serial number in the entry */
  KeyM_AsnElementType Serial;
  /* Revocation date of the certificate in the entry */
  uint64 RevocationDate;
} KeyM_X509CrlEntryType;
/* @Trace: KeyM_SUD_DATATYPE_051 */
/* Certificate revocation list structure. Every CRL may have multiple entries */
typedef struct
{
  /* The raw CRL body (DER). The part that is To Be Signed */
  KeyM_AsnElementType TBSCertList;
  /* The raw X.509 CRL version */
  KeyM_ElementType * PtrRawVersion;
  /* CRL signature type identifier */
  KeyM_ElementType * PtrRawSignature;
  /* Raw This Update date of CRL */
  KeyM_ElementType * PtrRawThisUpdate;
  /* Raw Next Update date of CRL */
  KeyM_ElementType * PtrRawNextUpdate;
  /* Signature algorithm is used to sign Tbs part */
  KeyM_ElementType * PtrSignatureAlgorithm;
  /* Signature value of the tbs part signed with the private key */
  KeyM_ElementType * PtrSignatureValue;
  /* Optional X.509 CRL v2 extensions */
  KeyM_ElementType * PtrExtensions;
  /* Parsed issuer */
  KeyM_ElementType * PtrIssuer;
  /* The CRL entries containing the certificate revocation times for this CA */
  KeyM_X509CrlEntryType * PtrEntryList;
  /* Parsed This Update date of CRL in seconds */
  uint64 ThisUpdate;
  /* Parsed Next Update date of CRL in seconds */
  uint64 NextUpdate;
  /* Number of name in the Issuer */
  uint8 IssuerNum;
  /* Number of entry in the EntryList */
  uint8 EntryNum;
  /* Number of extensions */
  uint8 ExtensionNum;
  /* Signature algorithm type */
  uint8 SignAlgType;

} KeyM_X509CrlType;

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvX509CrlParseDer(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  const uint16 dataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvX509CrlVerify(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCrl, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvCheckCertRevoked(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSerialNumber, \
  const uint16 serialLength, \
  const uint64 currentTime);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvAdjustX509Clr(\
  P2VAR(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCurAddress, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrNewAddress);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvRecoverX509Crl(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvCopyParsedCRL(\
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrSrcCrl, \
  P2VAR(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrDesCrl);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509CrlGenerate(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF) */
#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

#endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */
#endif /* KEYM_X509_CRL_H */
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
