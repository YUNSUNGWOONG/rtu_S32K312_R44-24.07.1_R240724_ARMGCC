/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_X509.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key manager internal header file for X509                     **
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
** 1.0.3.0   20-May-2022   DienTC1      #22113                                **
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
** 1.0.8.0   31-Jul-2023   PhuocLH9     #CP44-2396,#CP44-2394                 **
*******************************************************************************/
#ifndef KEYM_X509_H
#define KEYM_X509_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM ASN1 header file */
#include "KeyM_Asn1.h"
/* KeyM Types Header file */
#include "KeyM_IntType.h"
/* KeyM header file */
#include "KeyM.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
#if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
  (KEYM_CERT_X509_CRL_ENABLED == STD_ON))
/* @Trace: KeyM_SUD_MACRO_009 */
/* X.509 extension types */
/* Supported */
#define KEYM_X509_EXT_AUTHORITY_KEY_IDENTIFIER   (0x01U)
/* Supported */
#define KEYM_X509_EXT_SUBJECT_KEY_IDENTIFIER     (0x02U)
/* Supported */
#define KEYM_X509_EXT_KEY_USAGE                  (0x03U)
/* Not Supported */
#define KEYM_X509_EXT_CERTIFICATE_POLICIES       (0x04U)
/* Not Supported */
#define KEYM_X509_EXT_POLICY_MAPPINGS            (0x05U)
/* Supported */
#define KEYM_X509_EXT_SUBJECT_ALT_NAME           (0x06U)
/* Not Supported */
#define KEYM_X509_EXT_ISSUER_ALT_NAME            (0x07U)
/* Not Supported */
#define KEYM_X509_EXT_SUBJECT_DIRECTORY_ATTRS    (0x08U)
/* Supported */
#define KEYM_X509_EXT_BASIC_CONSTRAINTS          (0x09U)
/* Not Supported */
#define KEYM_X509_EXT_NAME_CONSTRAINTS           (0x0AU)
/* Not Supported */
#define KEYM_X509_EXT_POLICY_CONSTRAINTS         (0x0BU)
/* Supported */
#define KEYM_X509_EXT_EXTENDED_KEY_USAGE         (0x0CU)
/* Supported */
#define KEYM_X509_EXT_CRL_DISTRIBUTION_POINTS    (0x0DU)
/* Not Supported */
#define KEYM_X509_EXT_INIHIBIT_ANYPOLICY         (0x0EU)
/* Not Supported */
#define KEYM_X509_EXT_FRESHEST_CRL               (0x0FU)
/* Supported */
#define KEYM_X509_EXT_CRL_NUMBER                 (0x10U)
/* Supported */
#define KEYM_X509_EXT_ISSUING_DISTRIBUTION_POINT (0x11U)
/* Supported */
#define KEYM_X509_EXT_AUTHORITY_INFO_ACCESS      (0x12U)
/* Unknown */
#define KEYM_X509_EXT_UNKNOWN                    (0xFFU)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* @Trace: KeyM_SUD_DATATYPE_053 */
/** Container for date and time (precision in seconds). */
typedef struct
{
  uint16 Year;    /* Year   */
  uint8 Mon;      /* Month  */
  uint8 Day;      /* Day    */
  uint8 Hour;     /* Hour   */
  uint8 Min;      /* Minute */
  uint8 Sec;      /* Second */
} KeyM_X509TimeType;

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetTime(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrTag, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrRawTime, \
  P2VAR(KeyM_X509TimeType, AUTOMATIC, KEYM_APPL_DATA) ptrTime);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetVersion(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrRawVersion, \
  const uint8 tag);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetIssuerSubject(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrNameArr, \
  const uint8 numberOfName);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetSignAlgorithm(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSignAlgType, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrSignAlgorithm);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetSignatureValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  const uint8 signAlgType, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrSignValue);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvX509ConvertEccSignatureValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrActualSignValue, \
  const uint16 actualSignValueLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrOutSign, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrOutSignLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_PrvX509ConvertDateToSecond(\
  P2CONST(KeyM_X509TimeType, AUTOMATIC, KEYM_APPL_DATA) ptrDate, \
  P2VAR(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrSeconds);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetExtensions(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrExtensions, \
  const uint8 extensionNum, \
  const uint8 option);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetValidTime(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrRawValidTime, \
  P2VAR(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrParsedValidTime);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint16, KEYM_CODE) KeyM_PrvX509ParseRsaSsaPssParams(\
  P2CONST(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrParams);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509NameCmp(\
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrName1, \
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrName2, \
  const uint8 name1Num, \
  const uint8 name2Num);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509ElementGet(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen, \
  const KeyM_CertFormatType certFormat);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509ElementGetByIndex(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  VAR(uint32, AUTOMATIC) indexCnt, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509ElementGetCount(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509ElementGetFirst(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(KeyM_CertElementIteratorType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrCertElementIterator, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen, \
  const KeyM_CertFormatType certFormat);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509ElementGetNext(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(KeyM_CertElementIteratorType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrCertElementIterator, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen, \
  const KeyM_CertFormatType certFormat);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509GetDERPacketData(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCertData, \
  CONST(uint16, AUTOMATIC)  CertLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrDataLen, \
  CONST(uint8, AUTOMATIC) Typestruct);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509WriteElement(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength, \
  const uint8 tag);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509WriteIssuerSubject(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrNameArr, \
  const uint8 numberOfName, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509WriteExtensions(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrExtArr, \
  const uint8 numberOfExt, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength, \
  const uint8 option);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509WriteTime(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrTime, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF) */
#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

#endif /* ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) ||
  (KEYM_CERT_X509_CRL_ENABLED == STD_ON)) */
#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */
#endif /* KEYM_X509_H */
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
