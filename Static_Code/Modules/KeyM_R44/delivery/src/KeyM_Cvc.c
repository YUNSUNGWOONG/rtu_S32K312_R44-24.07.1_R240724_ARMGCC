/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_Cvc.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key Manager internal API Functionality of CVC                 **
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
** 1.0.1.0   27-Mar-2021   TamTV6       Fix #18139, #18146, #18153,           **
**                                      #18157, #18158, #18166, add Trace SUD **
** 1.0.2     08-Nov-2021   TamTV6       Implement #20971                      **
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
** 1.0.9.0   21-Feb-2024   JS Kang      #CP44-3635                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:11.5 CERT-C:EXP36-C [Justified:Low] 
   "It uses casting from void* to object(struct) pointer in order to read a raw 
   memory by the specific format. If using working around like memory copy to 
   pass over this violation, the source code becomes very complex, hard to read 
   and take time to fix testing failed cases."*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM internal function prototype */
#include "KeyM_IntFunc.h"
/* KeyM X509 CRL header file */
#include "KeyM_X509_Crl.h"
/* KeyM CVC header file */
#include "KeyM_Cvc.h"
/* KeyM OID header file */
#include "KeyM_OID.h"
/* KeyM Ram variables header file */
#include "KeyM_Ram.h"
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
#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
#if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcGetCertElement(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrElement, \
  const uint8 tag);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcGetCertPublicKey(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcGetCertExtensions(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrExtensions, \
  const uint8 extensionNum);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcGetCertDate(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrRawDate, \
  P2VAR(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrSecond, \
  const uint8 tag);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcGetCertHolderAuthorization(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrHolderAuthor);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcParseTime(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2VAR(KeyM_DateType, AUTOMATIC, KEYM_APPL_DATA) ptrDate);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcGetPublicKeyDomainParams(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcConvertRSAPublicKeyFormat(\
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPublicKeyData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKeyLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
#if (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
  static Std_ReturnType KeyM_PrvCvcWriteElement(\
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
  static Std_ReturnType KeyM_PrvCvcWriteSignatureValue(\
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
    P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
    P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSignValue, \
    const uint16 signValLength, \
    P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
  static Std_ReturnType KeyM_PrvCvcWriteExtensions(\
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
    P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
    P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
    P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrExtArr, \
    const uint8 numberOfExt, \
    P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
  static Std_ReturnType KeyM_PrvCvcWritePublicKeyValue(\
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
    P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
    P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
    P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKey, \
    P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
  static Std_ReturnType KeyM_PrvCvcWriteEccPublicKeyValue(\
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
    P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
    P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
    P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
    P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKey, \
    const uint16 publicKeyLen, \
    P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
  static Std_ReturnType KeyM_PrvCvcWriteRsaPublicKeyValue(\
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
    P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
    P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
    P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKey, \
    const uint16 publicKeyLen, \
    P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
  static Std_ReturnType KeyM_CvcWriteTag(\
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
    P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrStartOfData, \
    const uint8 tag, \
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrLengthBytes);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
  static Std_ReturnType KeyM_PrvPartOfCvcCertificateGenerate(\
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
    P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
    P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
    P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrBuffer, \
    P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
  static Std_ReturnType KeyM_PrvCvcParseRsaPublicKeyValue(\
    P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKey, \
    const uint16 publicKeyLen, \
    P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrModulus, \
    P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrExponent);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) */
#endif /* (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF) */
#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvPartOfCvcCertificateParseDer(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcElementGetExtensionCount(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtensionData, \
  const uint32 extDataLength, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcElementGetExtensionByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtensionData, \
  const uint32 extDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcElementGetHolderAuthorByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrHolderAuthorData, \
  const uint32 holderDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcCertStorePublicKey(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrt);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_CvcGetTag(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength, \
  const uint8 tag);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_CvcGetTag                                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get the tag and length of Cvc element. Updates the    **
**                      pointer to immediately behind the tag and length      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEndOfData, tag                                     **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrLength                                **
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
**                      KeyM_Asn1GetLength                                    **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_CvcGetTag(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength, \
  const uint8 tag)
{
  Std_ReturnType retVal;
  uint8 actualTag;

  retVal = E_OK;
  actualTag = 0u;
  *ptrLength = 0u;
  /* @Trace: KeyM_SUD_FUNC_878 */
  if (1 > (ptrEndOfData - *ptrPosition))
  {
    retVal = KEYM_E_ASN1_OUT_OF_DATA;
  }
  else if ((0x5Fu == **ptrPosition) || (0x7Fu == **ptrPosition))
  {
    /* Get the lower byte of tag */
    (*ptrPosition)++;
    actualTag = **ptrPosition;
  }
  else
  {
    actualTag = **ptrPosition;
  }

  if (E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_879 */
    if (actualTag != tag)
    {
      retVal = KEYM_E_ASN1_UNEXPECTED_TAG;
    }
    else
    {
      (*ptrPosition)++;
      retVal = KeyM_Asn1GetLength(ptrPosition, ptrEndOfData, ptrLength);
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvCvcCertificateParseDer                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse one CVC certificate in DER format from a buffer **
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
**                      KeyM_CvcGetTag, KeyM_PrvPartOfCvcCertificateParseDer, **
**                      KeyM_PrvCvcGetCertElement                             **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvCvcCertificateParseDer(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  const uint16 dataLength)
{
  uint16 retVal;
  uint16 length;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCertEnd;
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert;

  ptrPosition = ptrData;
  length = dataLength;
  ptrEnd = &ptrPosition[length];

  /* @Trace: KeyM_SUD_FUNC_822 */
  /*
   * Certificate  ::=  SEQUENCE  {
   *      tbsCertificate       TBSCertificate,
   *      signatureValue       OCTET STRING  }
   */
  retVal = KeyM_CvcGetTag(&ptrPosition, ptrEnd, &length, KEYM_CVC_CERTIFICATE);
  if (KEYM_E_OK == retVal)
  {
    if ((&(ptrPosition[length])) != ptrEnd)
    {
      /* @Trace: KeyM_SUD_FUNC_823 */
      retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_824 */
      ptrParsedCert = (KeyM_CvcCertificateType*)ptrCert->PtrParsedCert;
      ptrCertEnd = &ptrPosition[length];
      ptrParsedCert->TBSCert.PtrData = ptrPosition;

      /* ==================================
       * TBSCertificate  ::=  SEQUENCE  {
       * ==================================*/
      retVal = KeyM_CvcGetTag(&ptrPosition, ptrCertEnd, &length, \
        KEYM_CVC_CERTIFICATE_BODY);
      if (KEYM_E_OK == retVal)
      {
        ptrEnd = &ptrPosition[length];
        ptrParsedCert->TBSCert.Length = \
          (uint16)((sint32)(ptrEnd - ptrParsedCert->TBSCert.PtrData));
        retVal = KeyM_PrvPartOfCvcCertificateParseDer(&ptrPosition, \
          ptrEnd, ptrCert, ptrParsedCert);
        /* @Trace: KeyM_SUD_FUNC_825 */
        if (KEYM_E_OK == retVal)
        {
          /* End of TBSCertificate, the current position must be
            the end of TBS */
          if (ptrEnd != ptrPosition)
          {
            retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
          }
          else
          {
            /* Set end position is the end of certificate */
            ptrEnd = ptrCertEnd;
            /* Get Certificate Signature */
            retVal = KeyM_PrvCvcGetCertElement(&ptrPosition, ptrEnd, \
              ptrCert, ptrParsedCert->PtrSignatureValue, \
              KEYM_CVC_SIGNATURE);
            if ((KEYM_E_OK == retVal) && (ptrEnd != ptrPosition))
            {
              /* End of Certificate, the current position must be the end
                 of Certificate */
              retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
            }
          } /* @if (ptrEnd != ptrPosition) */
        } /* @if (KEYM_E_OK == retVal) */
      } /* @if (KEYM_E_OK == retVal) */
    } /* @if (KEYM_E_OK == retVal) */
  } /* @if (KEYM_E_OK == retVal) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPartOfCvcCertificateParseDer                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvCvcCertificateParseDer,     **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvCvcCertificateParseDer                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd, ptrCert                                       **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrParsedCert                            **
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
**                      KeyM_PrvCvcGetCertElement, KeyM_PrvCvcGetCertPublicKey**
**                      KeyM_PrvCvcGetCertHolderAuthorization,                **
**                      KeyM_PrvCvcGetCertDate, KeyM_PrvCvcGetCertExtensions  **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvPartOfCvcCertificateParseDer(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert)
{
  uint16 retVal;
  /* @Trace: KeyM_SUD_FUNC_880 */
  /* Get Certificate Profile Identifier */
  retVal = KeyM_PrvCvcGetCertElement(ptrPosition, ptrEnd, ptrCert,\
    ptrParsedCert->PtrRawProfileId,\
    KEYM_CVC_CERTIFICATE_PROFILE_IDENTIFIER);
  if (KEYM_E_OK == retVal)
  {
    /* Get Certification Authority Reference */
    retVal = KeyM_PrvCvcGetCertElement(ptrPosition, ptrEnd, ptrCert,\
      ptrParsedCert->PtrRawAuthorityRefer,\
      KEYM_CVC_CERTIFICATE_AUTHORITY_REFERENCE);

    if (KEYM_E_OK == retVal)
    {
      /* Get Public Key */
      retVal = KeyM_PrvCvcGetCertPublicKey(ptrPosition, ptrEnd,\
        ptrCert, ptrParsedCert);

      /* @Trace: KeyM_SUD_FUNC_882 */
      if (KEYM_E_OK == retVal)
      {
        /* Get Certificate Holder Reference */
        retVal = KeyM_PrvCvcGetCertElement(ptrPosition, ptrEnd, ptrCert,\
          ptrParsedCert->PtrRawHolderRefer,\
          KEYM_CVC_CERTIFICATE_HOLDER_REFERENCE);

        if (KEYM_E_OK == retVal)
        {
          /* Get Certificate Holder Authorization Template */
          retVal = KeyM_PrvCvcGetCertHolderAuthorization(ptrPosition, ptrEnd, \
            ptrCert, ptrParsedCert->PtrRawHolderAuthorTemplate);

          /* @Trace: KeyM_SUD_FUNC_884 */
          if (KEYM_E_OK == retVal)
          {
            /* Get Certificate Effective Date */
            retVal = KeyM_PrvCvcGetCertDate(ptrPosition, ptrEnd, ptrCert, \
              ptrParsedCert->PtrRawEffectiveDate, \
              &ptrParsedCert->EffectiveDate, \
              KEYM_CVC_CERTIFICATE_EFFECTIVE_DATE);

            if (KEYM_E_OK == retVal)
            {
              /* Get Certificate Expiration Date */
              retVal = KeyM_PrvCvcGetCertDate(ptrPosition, ptrEnd, ptrCert, \
                ptrParsedCert->PtrRawExpirationDate, \
                &ptrParsedCert->ExpirationDate, \
                KEYM_CVC_CERTIFICATE_EXPIRATION_DATE);

              if (KEYM_E_OK == retVal)
              {
                /* Get Certificate Extensions */
                retVal = KeyM_PrvCvcGetCertExtensions(ptrPosition, ptrEnd, \
                  ptrCert, ptrParsedCert->PtrExtensions, \
                  ptrParsedCert->ExtensionNum);
              }
            }
          } /* @if (KEYM_E_OK == retVal) */
        } /* @if (KEYM_E_OK == retVal) */
      } /* @if (KEYM_E_OK == retVal) */
    } /* @if (KEYM_E_OK == retVal) */
  } /* @if (KEYM_E_OK == retVal) */
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcGetCertElement                             **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get a element in a CVC certificate                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd, tag                                           **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert, ptrElement                      **
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
**                      KeyM_CvcGetTag, KeyM_PrvCheckCertificateElement       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcGetCertElement(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrElement, \
  const uint8 tag)
{
  uint16 retVal;
  uint16 length;
  uint16 elementIndex;

  /* @Trace: KeyM_SUD_FUNC_887 */
  length = 0U;
  retVal = KeyM_CvcGetTag(ptrPosition, ptrEnd, &length, tag);

  if (KEYM_E_OK == retVal)
  {
    if (NULL_PTR != ptrElement)
    {
      elementIndex = ptrElement->ElementIndex;
      /* Check the certificate element of profile ID */
      retVal = KeyM_PrvCheckCertificateElement(ptrCert, elementIndex, tag, \
        NULL_PTR, 0u);
      /* @Trace: KeyM_SUD_FUNC_888 */
      if (KEYM_E_OK == retVal)
      {
        /* Update raw Version tag, data and length */
        ptrElement->Element.Tag = tag;
        ptrElement->Element.Length = length;
        ptrElement->Element.PtrData = *ptrPosition;
        ptrCert->PtrCertElement[elementIndex].PtrElement = ptrElement;
        /* Update position to the next element of CVC certificate */
        *ptrPosition = &(*ptrPosition)[length];
      }
    }
    else
    {
      retVal = KEYM_E_INVALID_FORMAT;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcGetCertPublicKey                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get Certificate Public Key element in a CVC           **
**                      certificate                                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert, ptrParsedCert                   **
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
**                      KeyM_CvcGetTag, KeyM_PrvCvcGetSignatureAlgType,       **
**                      KeyM_PrvCheckCertificateElement,                      **
**                      KeyM_PrvCvcGetPublicKeyDomainParams                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcGetCertPublicKey(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert)
{
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrRawPublicKeyObjectId;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKeyEnd;
  uint8 keyType;
  uint16 retVal;
  uint16 length;
  uint8 tag;
  uint16 elementIndex;

  /* @Trace: KeyM_SUD_FUNC_889 */
  length = 0U;
  tag = KEYM_CVC_PUBLIC_KEY;
  ptrRawPublicKeyObjectId = ptrParsedCert->PtrRawPublicKeyObjectId;

  retVal = KeyM_CvcGetTag(ptrPosition, ptrEnd, &length, tag);

  if (KEYM_E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_890 */
    if (NULL_PTR != ptrRawPublicKeyObjectId)
    {
      ptrPublicKeyEnd = &(*ptrPosition)[length];
      tag = KEYM_CVC_OBJECT_IDENTIFIER;
      retVal = KeyM_CvcGetTag(ptrPosition, ptrPublicKeyEnd, &length, tag);

      if (KEYM_E_OK == retVal)
      {
        retVal = KeyM_PrvCvcGetSignatureAlgType(*ptrPosition, \
          (const uint8)length, &keyType);

        /* @Trace: KeyM_SUD_FUNC_891 */
        if (KEYM_E_OK == retVal)
        {
          elementIndex = ptrRawPublicKeyObjectId->ElementIndex;
          /* Check the certificate element of public key object identifer */
          retVal = KeyM_PrvCheckCertificateElement(ptrCert, elementIndex, \
            tag, NULL_PTR, 0u);

          if (KEYM_E_OK == retVal)
          {
            /* Update RawPublicKeyObjectId tag, data and length */
            ptrRawPublicKeyObjectId->Element.Tag = tag;
            ptrRawPublicKeyObjectId->Element.Length = length;
            ptrRawPublicKeyObjectId->Element.PtrData = *ptrPosition;
            ptrCert->PtrCertElement[elementIndex].PtrElement = \
            ptrRawPublicKeyObjectId;
            /* Store public key type */
            ptrParsedCert->PublicKeyType = keyType;
            /* Update position to the PtrPublicKeyDomainParams */
            *ptrPosition = &(*ptrPosition)[length];
            retVal = KeyM_PrvCvcGetPublicKeyDomainParams(ptrPosition, \
              ptrPublicKeyEnd, ptrCert, ptrParsedCert);
          }
        }
        else
        {
          retVal = KEYM_E_INVALID_PUBLIC_KEY;
        } /* @if (KEYM_E_OK == retVal) */
      } /* @if (KEYM_E_OK == retVal) */
    }
    else
    {
      retVal = KEYM_E_INVALID_PUBLIC_KEY;
    }
  } /* @if (KEYM_E_OK != retVal) */
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcGetPublicKeyDomainParams                   **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get public key domain parameters                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert, ptrParsedCert                   **
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
**                      KeyM_CvcGetTag, KeyM_PrvCheckCertificateElement       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcGetPublicKeyDomainParams(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert)
{
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrDomainParam;
  uint16 retVal;
  uint16 length;
  uint8 tag;
  uint8 paramIndex;
  uint16 elementIndex;
  uint8 domainParamNum;
  uint8 indexCnt;

  retVal = KEYM_E_OK;
  paramIndex = 0u;
  domainParamNum = ptrParsedCert->DomainParamNum;
  tag = **ptrPosition;

  if ((KEYM_CVC_PRIME_MODULUS != tag) && (KEYM_CVC_PUBLIC_POINT != tag))
  {
    /* @Trace: KeyM_SUD_FUNC_892 */
    retVal = KEYM_E_ASN1_UNEXPECTED_TAG;
  }
  else if ((NULL_PTR != ptrParsedCert->PtrPublicKeyDomainParams) && \
    (0u < domainParamNum))
  {
    /* @Trace: KeyM_SUD_FUNC_894 */
    while ((*ptrPosition < ptrEnd) && (KEYM_E_OK == retVal) && \
      (paramIndex < domainParamNum))
    {
      length = 0u;
      retVal = KeyM_CvcGetTag(ptrPosition, ptrEnd, &length, tag);

      if (KEYM_E_OK == retVal)
      {
        if ((KEYM_CVC_PUBLIC_POINT == tag) && \
          (KEYM_PK_ECDSA_SHA1 <= ptrParsedCert->PublicKeyType) && \
          (0x04u != **ptrPosition))
        {
          retVal = KEYM_E_INVALID_PUBLIC_KEY;
        }
        else
        {
          for (indexCnt = 0u; indexCnt < domainParamNum; indexCnt++)
          {
            ptrDomainParam = &ptrParsedCert->PtrPublicKeyDomainParams[indexCnt];
            elementIndex = ptrDomainParam->ElementIndex;
            /* Check the certificate element of public key object identifer */
            retVal = KeyM_PrvCheckCertificateElement(ptrCert, elementIndex, \
              tag, NULL_PTR, 0u);

            if (KEYM_E_OK == retVal)
            {
              ptrDomainParam->Element.PtrData = *ptrPosition;
              ptrDomainParam->Element.Length = length;
              ptrDomainParam->Element.Tag = tag;
              ptrCert->PtrCertElement[elementIndex].PtrElement = \
              ptrDomainParam;
              tag++;
              paramIndex++;
              *ptrPosition = &(*ptrPosition)[length];
              break;
            }
          }
        }
      }
    }
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_893 */
    retVal = KEYM_E_INVALID_PUBLIC_KEY;
  } /* @if ((KEYM_CVC_PRIME_MODULUS != tag) && (KEYM_CVC_PUBLIC_POINT != tag)) */

  /* @Trace: KeyM_SUD_FUNC_897 */
  if ((KEYM_E_OK == retVal) && ((paramIndex != domainParamNum) || \
    (*ptrPosition != ptrEnd)))
  {
    retVal = KEYM_E_INVALID_PUBLIC_KEY;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcConvertRSAPublicKeyFormat                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Convert RSA public key from CVC format to X509 format **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : ptrParsedCert                                         **
**                                                                            **
** Output Parameters  : ptrPublicKeyData, ptrPublicKeyLength                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvConvertRsaPublicKeyFormat                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcConvertRSAPublicKeyFormat(\
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPublicKeyData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKeyLength)
{
  Std_ReturnType retVal;
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrModulus;
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrExponent;

  /* Convert to RFC 5280 public key format:
     RSAPublicKey ::= SEQUENCE {
     modulus            INTEGER,    -- n
     publicExponent     INTEGER  }  -- e */

  /* @Trace: KeyM_SUD_FUNC_918 */
  /* Find the index of publicExponent element */
  if (KEYM_CVC_PUBLIC_EXPONENT == \
    ptrParsedCert->PtrPublicKeyDomainParams[0u].Element.Tag)
  {
    ptrExponent = &ptrParsedCert->PtrPublicKeyDomainParams[0u];
    ptrModulus = &ptrParsedCert->PtrPublicKeyDomainParams[1u];
  }
  else
  {
    ptrExponent = &ptrParsedCert->PtrPublicKeyDomainParams[1u];
    ptrModulus = &ptrParsedCert->PtrPublicKeyDomainParams[0u];
  }

  retVal = KeyM_PrvConvertRsaPublicKeyFormat(ptrModulus->Element.PtrData, \
    ptrModulus->Element.Length, ptrExponent->Element.PtrData, \
    ptrExponent->Element.Length, ptrPublicKeyData, ptrPublicKeyLength);

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcGetCertHolderAuthorization                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get Certificate Holder Authorization template element**
**                      in CVC certificate                                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert, ptrHolderAuthor                 **
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
**                      KeyM_CvcGetTag, KeyM_PrvCheckCertificateElement       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcGetCertHolderAuthorization(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrHolderAuthor)
{
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAuthorEnd;
  uint16 retVal;
  uint16 length;
  uint8 tag;
  uint16 elementIndex;

  /* @Trace: KeyM_SUD_FUNC_898 */
  length = 0U;
  tag = KEYM_CVC_CERTIFICATE_HOLDER_AUTHORIZATION_TEMPLATE;
  retVal = KeyM_CvcGetTag(ptrPosition, ptrEnd, &length, tag);

  if (KEYM_E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_899 */
    if (NULL_PTR != ptrHolderAuthor)
    {
      ptrHolderAuthor->Element.Tag = tag;
      ptrHolderAuthor->Element.Length = length;
      ptrHolderAuthor->Element.PtrData = *ptrPosition;
      ptrAuthorEnd = &(*ptrPosition)[length];

      retVal = KeyM_CvcGetTag(ptrPosition, ptrAuthorEnd, &length, \
        KEYM_CVC_OBJECT_IDENTIFIER);

      if (KEYM_E_OK == retVal)
      {
        *ptrPosition = &(*ptrPosition)[length];
        retVal = KeyM_CvcGetTag(ptrPosition, ptrAuthorEnd, &length, \
          KEYM_CVC_DISCRETIONARY_DATA);
        /* @Trace: KeyM_SUD_FUNC_900 */
        if (KEYM_E_OK == retVal)
        {
          elementIndex = ptrHolderAuthor->ElementIndex;
          /* Check the certificate element of Date */
          retVal = KeyM_PrvCheckCertificateElement(ptrCert, elementIndex, tag, \
            NULL_PTR, 0u);
          /* @Trace: KeyM_SUD_FUNC_901 */
          if (KEYM_E_OK == retVal)
          {
            ptrCert->PtrCertElement[elementIndex].PtrElement = ptrHolderAuthor;
            *ptrPosition = &(*ptrPosition)[length];
          }
        }
      }
    }
    else
    {
      retVal = KEYM_E_INVALID_FORMAT;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcGetCertDate                                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get Certificate Effective Date element in a CVC       **
**                      certificate                                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd, tag                                           **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert, ptrRawDate                      **
**                                                                            **
** Output Parameters  : ptrSecond                                             **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_CvcGetTag, KeyM_PrvCheckCertificateElement,      **
**                      KeyM_PrvCvcParseTime, KeyM_PrvConvertDateToSecond     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcGetCertDate(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrRawDate, \
  P2VAR(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrSecond, \
  const uint8 tag)
{
  KeyM_DateType date;
  uint16 retVal;
  uint16 length;
  uint16 elementIndex;

  /* @Trace: KeyM_SUD_FUNC_902 */
  length = 0U;
  date.Year = 0u;
  date.Mon = 0u;
  date.Day = 0u;

  retVal = KeyM_CvcGetTag(ptrPosition, ptrEnd, &length, tag);

  if (KEYM_E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_903 */
    if (NULL_PTR != ptrRawDate)
    {
      elementIndex = ptrRawDate->ElementIndex;
      /* Check the certificate element of Date */
      retVal = KeyM_PrvCheckCertificateElement(ptrCert, elementIndex, tag, \
        NULL_PTR, 0u);

      if (KEYM_E_OK == retVal)
      {
        /* Update Date tag, data and length */
        ptrRawDate->Element.Tag = tag;
        ptrRawDate->Element.Length = length;
        ptrRawDate->Element.PtrData = *ptrPosition;
        ptrCert->PtrCertElement[elementIndex].PtrElement = ptrRawDate;
        /* Parse the raw time */
        retVal = KeyM_PrvCvcParseTime(ptrPosition, &date);
        /* @Trace: KeyM_SUD_FUNC_904 */
        if (KEYM_E_OK == retVal)
        {
          /* Convert Date to seconds */
          KeyM_PrvConvertDateToSecond(&date, ptrSecond);
        }
      }
    }
    else
    {
      retVal = KEYM_E_INVALID_DATE;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvPartOfCvcGetCertExtensions                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvCvcGetCertExtensions,       **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvCvcGetCertExtensions                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd, ptrCert, extensionNum                         **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrExtensions                                         **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_CvcGetTag, KeyM_Asn1GetLength,                   **
**                      KeyM_PrvCheckCertificateElement                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvPartOfCvcGetCertExtensions(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrExtensions, \
  const uint8 extensionNum)
{
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEndExtn;
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrExtension;
  KeyM_AsnElementType extnObjectId;
  KeyM_ElementType curExtension;
  uint16 retVal;
  uint16 length;
  uint8 tag;
  uint16 elementIndex;
  uint8 extIndex;
  uint8 indexCnt;

  retVal = KEYM_E_OK;
  extIndex = 0;

  /* @Trace: KeyM_SUD_FUNC_912 */
  /* Get extension */
  while ((*ptrPosition < ptrEnd) && (KEYM_E_OK == retVal) && \
    (extIndex < extensionNum))
  {
    /*
    * Discretionary Data Template
    *  Object Identifier
    *  Context Specific Data Object 1
    *  ...
    *  Context Specific Data Object n
    */

    /* Extension is Discretionary Data Template type */
    tag = KEYM_CVC_DISCRETIONARY_DATA_TEMPLATE;
    length = 0u;
    /* Get tag and length of extension */
    retVal = KeyM_CvcGetTag(ptrPosition, ptrEnd, &length, tag);

    if (KEYM_E_OK == retVal)
    {
      curExtension.Element.Tag = tag;
      curExtension.Element.Length = length;
      curExtension.Element.PtrData = *ptrPosition;

      /* Update end position of extension */
      ptrEndExtn = &(*ptrPosition)[length];

      /* Get extension ID */
      retVal = KeyM_CvcGetTag(ptrPosition, ptrEndExtn, &length, \
        KEYM_CVC_OBJECT_IDENTIFIER);
      /* @Trace: KeyM_SUD_FUNC_913 */
      if (KEYM_E_OK == retVal)
      {
        /* Go to the position of the first context specific data
          element of extension */
        extnObjectId.PtrData = *ptrPosition;
        extnObjectId.Length = length;
        *ptrPosition = &(*ptrPosition)[length];
        /* @Trace: KeyM_SUD_FUNC_914 */
        /* Parse extension value */
        while ((*ptrPosition < ptrEndExtn) && (KEYM_E_OK == retVal))
        {
          /* Skip one byte tag */
          *ptrPosition = &(*ptrPosition)[1u];
          retVal = KeyM_Asn1GetLength(ptrPosition, ptrEndExtn, &length);

          if (KEYM_E_OK == retVal)
          {
            /* Go to the position of the next context specific data
              element of extension */
            *ptrPosition = &(*ptrPosition)[length];
          } /* @if (KEYM_E_OK != retVal) */
        }

        if (KEYM_E_OK == retVal)
        {
          /* @Trace: KeyM_SUD_FUNC_916 */
          for (indexCnt = 0u; indexCnt < extensionNum; indexCnt++)
          {
            ptrExtension = &ptrExtensions[indexCnt];
            elementIndex = ptrExtension->ElementIndex;
            /* Check the certificate element of extensions */
            retVal = KeyM_PrvCheckCertificateElement(ptrCert,elementIndex, \
              tag, extnObjectId.PtrData, \
              extnObjectId.Length);

            if (KEYM_E_OK == retVal)
            {
              ptrExtension->Element.PtrData = curExtension.Element.PtrData;
              ptrExtension->Element.Length = curExtension.Element.Length;
              ptrExtension->Element.Tag = curExtension.Element.Tag;
              ptrCert->PtrCertElement[elementIndex].PtrElement = ptrExtension;
              extIndex++;
              break;
            } /* @if ((KEYM_E_OK == retVal) || (KEYM_E_NO_ELEMENT_CONFIG == retVal)) */
          }
        } /* @if (KEYM_E_OK == retVal) */
      } /* @if (KEYM_E_OK != retVal) */
    } /* @if (KEYM_E_OK != retVal) */
  } /* @while ((*ptrPosition < ptrEnd) && (KEYM_E_OK == retVal)) */

  if ((KEYM_E_OK == retVal) && ((extIndex != extensionNum) || \
    (*ptrPosition != ptrEnd)))
  {
    /* @Trace: KeyM_SUD_FUNC_917 */
    retVal = KEYM_E_INVALID_EXTENSIONS;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcGetCertExtensions                          **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get Certificate Extensions element in CVC certificate **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd, extensionNum                                  **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert, ptrExtensions                   **
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
**                      KeyM_CvcGetTag,                                       **
**                      KeyM_PrvPartOfCvcGetCertExtensions                    **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcGetCertExtensions(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrExtensions, \
  const uint8 extensionNum)
{
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEndExtensions;
  uint16 retVal;
  uint16 length;
  uint8 tag;

  if ((*ptrPosition == ptrEnd) && (0u == extensionNum))
  {
    /* @Trace: KeyM_SUD_FUNC_909 */
    /* Because extensions element is optional so the cerificate
      may not has these elements. The current position is
      the end of TBS. Do nothing in this case. */
    retVal = KEYM_E_OK;
  }
  else if ((*ptrPosition == ptrEnd) || (0u == extensionNum))
  {
    /* @Trace: KeyM_SUD_FUNC_910 */
    retVal = KEYM_E_INVALID_EXTENSIONS;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_911 */
    tag = KEYM_CVC_CERTIFICATE_EXTENSIONS;
    length = 0U;
    retVal = KeyM_CvcGetTag(ptrPosition, ptrEnd, &length, tag);

    if (KEYM_E_OK == retVal)
    {
      ptrEndExtensions = &(*ptrPosition)[length];
      retVal = KeyM_PrvPartOfCvcGetCertExtensions(ptrPosition, \
        ptrEndExtensions, ptrCert, ptrExtensions, extensionNum);
    } /* @if (KEYM_E_OK != retVal) */
  } /* @if (*ptrPosition == ptrEnd) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcParseTime                                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse a raw time value                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrDate                                  **
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
**                      KeyM_PrvParseInt, KeyM_PrvCheckDateValid              **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCvcParseTime(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2VAR(KeyM_DateType, AUTOMATIC, KEYM_APPL_DATA) ptrDate)
{
  uint16 retVal;
  uint16 interNum;

  /* @Trace: KeyM_SUD_FUNC_905 */
  interNum = 0u;

  /* A date is encoded in the format YYMMDD using timezone GMT */
  retVal = KeyM_PrvParseInt(ptrPosition, 2U, &interNum);
  if (KEYM_E_OK == retVal)
  {
    ptrDate->Year = interNum;
    /* The year is in the range of 2000 to 2099 */
    ptrDate->Year += 2000U;
    /* Parse month */
    retVal = KeyM_PrvParseInt(ptrPosition, 2U, &interNum);
    /* @Trace: KeyM_SUD_FUNC_906 */
    if (KEYM_E_OK == retVal)
    {
      ptrDate->Mon = (uint8)interNum;
      /* Parse day */
      retVal = KeyM_PrvParseInt(ptrPosition, 2U, &interNum);
      /* @Trace: KeyM_SUD_FUNC_907 */
      if (KEYM_E_OK == retVal)
      {
        ptrDate->Day = (uint8)interNum;
        /* Check date */
        retVal =  KeyM_PrvCheckDateValid(ptrDate, 2099U, 2000U);
      }
    }
  } /* @if (KEYM_E_OK == retVal) */

  if (KEYM_E_OK != retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_908 */
    retVal = KEYM_E_INVALID_DATE;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcCheckParent                                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check certificate is parent(upper certiticate)        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrChild, ptrParent                                   **
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
**                      KeyM_PrvMemCmp                                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvCvcCheckParent(\
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrChild, \
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParent)
{
  uint16 retVal;

  if (ptrChild->PtrRawAuthorityRefer->Element.Length == \
    ptrParent->PtrRawHolderRefer->Element.Length)
  {
    /* @Trace: KeyM_SUD_FUNC_826 */
    retVal = KeyM_PrvMemCmp(ptrChild->PtrRawAuthorityRefer->Element.PtrData, \
      ptrParent->PtrRawHolderRefer->Element.PtrData, \
      ptrChild->PtrRawAuthorityRefer->Element.Length);
    if (KEYM_E_OK != retVal)
    {
      retVal = KEYM_E_BADCERT_NAME_MISMATCH;
    }
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_827 */
    retVal = KEYM_E_BADCERT_NAME_MISMATCH;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvCvcCertStorePublicKey                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Store extracted public key to CSM                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCert, ptrParsedCrt                                 **
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
**                      KeyM_PrvCvcConvertRSAPublicKeyFormat, Csm_KeySetValid,**
**                      Csm_KeyElementSet                                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcCertStorePublicKey(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrt)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKey;
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrDomainParam;
  uint16 publicKeyLength;
  uint8 indexCnt;
  uint8 publicKeyData[KEYM_PUBLIC_KEY_VALUE_MAX_LENGTH];

  publicKeyData[0u] = 0u;
  ptrPublicKey = &publicKeyData[0u];
  publicKeyLength = KEYM_PUBLIC_KEY_VALUE_MAX_LENGTH;

  /* @Trace: KeyM_SUD_FUNC_919 */
  if (KEYM_PK_ECDSA_SHA1 <= ptrParsedCrt->PublicKeyType)
  {
    retVal = E_NOT_OK;
    /* @Trace: KeyM_SUD_FUNC_920 */
    for (indexCnt = 0u; indexCnt < ptrParsedCrt->DomainParamNum; indexCnt++)
    {
      ptrDomainParam = &ptrParsedCrt->PtrPublicKeyDomainParams[indexCnt];

      if (KEYM_CVC_PUBLIC_POINT == ptrDomainParam->Element.Tag)
      {
        retVal = E_OK;
        break;
      }
    }

    if (E_OK == retVal)
    {
      /* @Trace: KeyM_SUD_FUNC_921 */
      /* For Ecc public key, the first byte is prefix byte, so the
      actual public key data starts from the second byte */
      ptrPublicKey = \
        &ptrParsedCrt->PtrPublicKeyDomainParams[indexCnt].Element.PtrData[1u];
      publicKeyLength = \
        ptrParsedCrt->PtrPublicKeyDomainParams[indexCnt].Element.Length - 1u;
    }
  }
  else
  {
    /* For key type RSA, we need to convert to RSA public key
      format in RFC 5280, because the Crypto driver only support
      this format */
    retVal = KeyM_PrvCvcConvertRSAPublicKeyFormat(ptrParsedCrt, &ptrPublicKey, \
      &publicKeyLength);
  }

  if (E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_922 */
    /* Store public key to CSM */
    retVal = Csm_KeyElementSet(ptrCert->CsmSignVerifyKeyId, \
      KEYM_KEY_ELEMENT1_ID, \
      ptrPublicKey, \
      publicKeyLength);

    if (KEYM_E_OK == retVal)
    {
      /* Validate the public key */
      retVal = Csm_KeySetValid(ptrCert->CsmSignVerifyKeyId);
    }
  }

  return retVal;

}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcCertificatePairVerify                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Verify CVC certificate pair                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrUpperCert                                          **
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
**                      KeyM_PrvCvcCheckParent, Csm_SignatureVerify,          **
**                      KeyM_PrvCvcCertStorePublicKey, KeyM_PrvGetCurrentTime **
**                      or UserGetCurrentTimeFunc,                            **
**                      KeyM_PrvCheckCertRevoked, KeyM_PrvElementRuleVerify   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvCvcCertificatePairVerify(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrUpperCert)
{
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrt;
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedUpperCert;
  Crypto_VerifyResultType verifyResult;
  uint64 currentTime;
  uint16 retVal;
  KeyM_CertificateStatusType certStatus;
  #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrHolderRefer;
  uint16 holderReferLength;
  #endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */

  /* Initialize variables */
  verifyResult = CRYPTO_E_VER_NOT_OK;
  ptrParsedCrt = (KeyM_CvcCertificateType*)(ptrCert->PtrParsedCert);
  ptrParsedUpperCert = (KeyM_CvcCertificateType*)(ptrUpperCert->PtrParsedCert);
  /* Check the upper certificate has holder reference is the same Authority reference
     of the current certificate */
  retVal = KeyM_PrvCvcCheckParent(ptrParsedCrt, ptrParsedUpperCert);

  if (KEYM_E_OK != retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_829 */
    certStatus = KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST;
  }
  else
  {
    if (ptrCert->IsRoot == KEYM_TRUE)
    {
      /* @Trace: KeyM_SUD_FUNC_830 */
      retVal = KeyM_PrvCvcCertStorePublicKey(ptrCert, ptrParsedCrt);
    }

    if (KEYM_E_OK != retVal)
    {
      /* @Trace: KeyM_SUD_FUNC_831 */
      certStatus = KEYM_CERTIFICATE_INVALID;
    }
    else
    {
      /* Check if current cert is correctly signed by the upper cert */
      retVal = Csm_SignatureVerify(ptrUpperCert->CsmSignVerifyJob.CsmJobId, \
        CRYPTO_OPERATIONMODE_SINGLECALL, ptrParsedCrt->TBSCert.PtrData, \
        ptrParsedCrt->TBSCert.Length, \
        ptrParsedCrt->PtrSignatureValue->Element.PtrData, \
        ptrParsedCrt->PtrSignatureValue->Element.Length, \
        &verifyResult);

      if (KEYM_E_OK != retVal)
      {
        /* @Trace: KeyM_SUD_FUNC_832 */
        certStatus = KEYM_CERTIFICATE_INVALID;
      }
      else if (CRYPTO_E_VER_OK != verifyResult)
      {
        /* @Trace: KeyM_SUD_FUNC_833 */
        certStatus = KEYM_E_CERTIFICATE_SIGNATURE_FAIL;
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_834 */
        currentTime = 0U;
        /* Get the current time */
        #if (KEYM_USE_STBM == STD_ON)
        retVal = KeyM_PrvGetCurrentTime(ptrCert->CertTimebaseId, &currentTime);
        #else
        retVal = KEYM_USER_GET_CURRENT_TIME(&currentTime);
        #endif

        if (KEYM_E_OK == retVal)
        {
          #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
          /* @Trace: KeyM_SUD_FUNC_846 */
          ptrHolderRefer = ptrParsedCrt->PtrRawHolderRefer->Element.PtrData;
          holderReferLength = ptrParsedCrt->PtrRawHolderRefer->Element.Length;
          /* Check whether the certificate is revoked */
          retVal = KeyM_PrvCheckCertRevoked(ptrHolderRefer, holderReferLength,\
            currentTime);

          if (KEYM_E_BADCERT_REVOKED == retVal)
          {
            certStatus = KEYM_E_CERTIFICATE_REVOKED;
          }
          else
          #endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
          {
            /* Check for validity of the certificate */
            if ((ptrParsedCrt->EffectiveDate > currentTime) || \
              (ptrParsedCrt->ExpirationDate < currentTime))
            {
              /* @Trace: KeyM_SUD_FUNC_847 */
              certStatus = KEYM_E_CERTIFICATE_VALIDITY_PERIOD_FAIL;
            }
            else
            {
              /* @Trace: KeyM_SUD_FUNC_848 */
              #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON)
              /* Verify element according to element verification rule */
              retVal = KeyM_PrvElementRuleVerify(ptrCert);

              if (KEYM_E_OK != retVal)
              {
                certStatus = KEYM_E_CERTIFICATE_INVALID_CONTENT;
              }
              else
              #endif /* #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON) */
              {
                certStatus = KEYM_CERTIFICATE_VALID;
                if ((KEYM_CERTIFICATE_VALID != ptrCert->CertStatus) && \
                  (KEYM_TRUE != ptrCert->IsRoot))
                {
                  /* @Trace: KeyM_SUD_FUNC_849 */
                  /* Store the public key of the certificate to CSM,
                    except the root. The public key of the root
                    needs to be set and validated in
                    KeyMCertCsmSignatureVerifyKeyRef beforehand */
                  retVal = KeyM_PrvCvcCertStorePublicKey(ptrCert, ptrParsedCrt);

                  if (KEYM_E_OK != retVal)
                  {
                    certStatus = KEYM_CERTIFICATE_INVALID;
                  }
                  else
                  {
                    certStatus = KEYM_CERTIFICATE_VALID;
                  }
                } /* @if ((KEYM_CERTIFICATE_VALID != ptrCert->CertStatus) &&
                  (ptrCert->IsRoot != KEYM_TRUE)) */
              } /* @if (KEYM_E_OK != retVal) */
            } /* @if ((ptrParsedCrt->EffectiveDate > currentTime) || \
                (ptrParsedCrt->ExpirationDate < currentTime)) */
          }
        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_835 */
          certStatus = KEYM_CERTIFICATE_INVALID;
        } /* @if (E_OK == retVal) */
      } /* @if (KEYM_E_OK != retVal) */
    } /* @if (KEYM_E_OK != retVal) */
  } /* @if (KEYM_E_OK != retVal) */

  ptrCert->CertStatus = certStatus;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcElementGetExtensionByIndex                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get element data of extensions by index               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrExtensionData, extDataLength, dataIndex            **
**                                                                            **
** InOut Parameters   : ptrElementDataLen                                     **
**                                                                            **
** Output Parameters  : ptrElementData                                        **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_CvcGetTag, KeyM_Asn1GetLength                    **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcElementGetExtensionByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtensionData, \
  const uint32 extDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrExtEnd;
  uint16 length;
  uint32 dataLength;
  uint32 actualIndex;
  boolean finished;

  /* @Trace: KeyM_SUD_FUNC_923 */
  length = 0u;
  retVal = E_OK;
  finished = KEYM_FALSE;
  actualIndex = 0u;

  ptrPosition = ptrExtensionData;
  ptrExtEnd = &ptrPosition[extDataLength];

  /*
  * Discretionary Data Template
  *  Object Identifier
  *  Context Specific Data Object 1
  *  ...
  *  Context Specific Data Object n
  */

  /* Get extension ID */
  (void)KeyM_CvcGetTag(&ptrPosition, ptrExtEnd, &length, \
    KEYM_CVC_OBJECT_IDENTIFIER);

  /* Go to the position of the first context specific data
   element of extension */
  ptrPosition = &ptrPosition[length];

  while (ptrPosition < ptrExtEnd)
  {
    /* Skip one byte tag */
    ptrPosition = &ptrPosition[1u];
    (void)KeyM_Asn1GetLength(&ptrPosition, ptrExtEnd, &length);

    if (dataIndex == actualIndex)
    {
      finished = KEYM_TRUE;
      break;
    }
    else
    {
      actualIndex++;
      /* Go to the position of the next context specific data
       element of extension */
      ptrPosition = &ptrPosition[length];
    }
  }

  dataLength = length;
  /* @Trace: KeyM_SUD_FUNC_924 */
  if (KEYM_FALSE == finished)
  {
    retVal = E_NOT_OK;
  }
  else if (dataLength > *ptrElementDataLen)
  {
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
  }
  else
  {
    *ptrElementData = &ptrExtensionData[ptrPosition - ptrExtensionData];
    *ptrElementDataLen = dataLength;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcElementGetExtensionCount                   **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get element data count of extensions                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrExtensionData, extDataLength                       **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrCount                                              **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_CvcGetTag, KeyM_Asn1GetLength                    **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcElementGetExtensionCount(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtensionData, \
  const uint32 extDataLength, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrExtEnd;
  uint16 length;
  uint16 count;

  /* @Trace: KeyM_SUD_FUNC_926 */
  length = 0u;
  count = 0u;
  retVal = E_OK;

  ptrPosition = ptrExtensionData;
  ptrExtEnd = &ptrPosition[extDataLength];

  /* Get extension ID */
  (void)KeyM_CvcGetTag(&ptrPosition, ptrExtEnd, &length, \
    KEYM_CVC_OBJECT_IDENTIFIER);

  /* Go to the position of the first context specific data
     element of extension */
  ptrPosition = &ptrPosition[length];

  while (ptrPosition < ptrExtEnd)
  {
    /* Skip one byte tag */
    ptrPosition = &ptrPosition[1u];
    (void)KeyM_Asn1GetLength(&ptrPosition, ptrExtEnd, &length);
    count++;
    /* Go to the position of the next context specific data
      element of extension */
    ptrPosition = &ptrPosition[length];
  }

  *ptrCount = count;

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcElementGetHolderAuthorByIndex              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get element data of holder auhtorization by index     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrHolderAuthorData, holderDataLength, dataIndex      **
**                                                                            **
** InOut Parameters   : ptrElementDataLen                                     **
**                                                                            **
** Output Parameters  : ptrElementData                                        **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_CvcGetTag, KeyM_Asn1GetLength                    **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcElementGetHolderAuthorByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrHolderAuthorData, \
  const uint32 holderDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrHolderAuthorEnd;
  uint16 length;
  uint32 dataLength;
  boolean finished;

  /* @Trace: KeyM_SUD_FUNC_927 */
  length = 0u;
  retVal = E_OK;
  finished = KEYM_FALSE;

  ptrPosition = ptrHolderAuthorData;
  ptrHolderAuthorEnd = &ptrPosition[holderDataLength];

  /* Get extension ID */
  (void)KeyM_CvcGetTag(&ptrPosition, ptrHolderAuthorEnd, &length, \
    KEYM_CVC_OBJECT_IDENTIFIER);

  if (0u == dataIndex)
  {
    finished = KEYM_TRUE;
  }
  else
  {
    ptrPosition = &ptrPosition[length];
    /* Skip the one byte of tag */
    ptrPosition++;
    (void)KeyM_Asn1GetLength(&ptrPosition, ptrHolderAuthorEnd, &length);

    if (1u == dataIndex)
    {
      finished = KEYM_TRUE;
    }
  }

  dataLength = length;

  if (KEYM_FALSE == finished)
  {
    /* @Trace: KeyM_SUD_FUNC_928 */
    retVal = E_NOT_OK;
  }
  else if (dataLength > *ptrElementDataLen)
  {
    /* @Trace: KeyM_SUD_FUNC_929 */
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_930 */
    *ptrElementData = &ptrHolderAuthorData[ptrPosition - ptrHolderAuthorData];
    *ptrElementDataLen = dataLength;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcElementGetCount                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get CVC certificate element data count                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCertElement                                        **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrCount                                              **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvCvcElementGetExtensionCount                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcElementGetCount(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  uint32 elementDataLen;
  KeyM_CertificateElementTypeOfStructure elementOfStruct;

  retVal = E_NOT_OK;
  /* @Trace: KeyM_SUD_FUNC_836 */
  if (NULL_PTR != ptrCertElement->PtrElement)
  {
    elementDataLen = ptrCertElement->PtrElement->Element.Length;
    ptrElementData = ptrCertElement->PtrElement->Element.PtrData;

    if (NULL_PTR != ptrElementData)
    {
      /* @Trace: KeyM_SUD_FUNC_837 */
      retVal = E_OK;
      elementOfStruct = ptrCertElement->ElementOfStruct;
      if (KEYM_CERT_EXTENSION == elementOfStruct)
      {
        retVal = KeyM_PrvCvcElementGetExtensionCount(ptrElementData, \
          elementDataLen, ptrCount);
      }
      else if (KEYM_CERT_SUBJECT_AUTHORIZATION == elementOfStruct)
      {
        *ptrCount = 2u;
      }
      else
      {
        *ptrCount = 1u;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvCvcElementGetByIndex                          **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get CVC certificate element data by index             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCertElement, indexCnt                              **
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
**                      KeyM_PrvCvcElementGetExtensionByIndex                 **
**                      KeyM_PrvCvcElementGetHolderAuthorByIndex              **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcElementGetByIndex(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  VAR(uint32, AUTOMATIC) indexCnt, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  uint32 elementDataLen;
  KeyM_CertificateElementTypeOfStructure elementOfStruct;

  retVal = E_NOT_OK;
  /* @Trace: KeyM_SUD_FUNC_840 */
  if (NULL_PTR != ptrCertElement->PtrElement)
  {
    elementDataLen = ptrCertElement->PtrElement->Element.Length;
    ptrElementData = ptrCertElement->PtrElement->Element.PtrData;
    if (NULL_PTR != ptrElementData)
    {
      elementOfStruct = ptrCertElement->ElementOfStruct;
      if (KEYM_CERT_EXTENSION == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_842 */
        retVal = KeyM_PrvCvcElementGetExtensionByIndex(ptrElementData, \
          elementDataLen, indexCnt, ptrCertElementData, \
          ptrCertElementDataLen);
      }
      else if (KEYM_CERT_SUBJECT_AUTHORIZATION == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_843 */
        retVal = KeyM_PrvCvcElementGetHolderAuthorByIndex(ptrElementData, \
          elementDataLen, indexCnt, ptrCertElementData, \
          ptrCertElementDataLen);
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_844 */
        if (0u != indexCnt)
        {
          retVal = E_NOT_OK;
        }
        else
        {
          if (elementDataLen > *ptrCertElementDataLen)
          {
            retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
          }
          else
          {
            retVal = E_OK;
            *ptrCertElementData = ptrElementData;
            *ptrCertElementDataLen = elementDataLen;
          }
        }
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name      : KeyM_PrvCvcElementGet                                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get CVC certificate element data which has one        **
**                      element is assigned to the respective OID             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCertElement                                        **
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
**                      KeyM_PrvCvcElementGetExtensionCount                   **
**                      KeyM_PrvCvcElementGetExtensionByIndex                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcElementGet(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  uint32 elementDataLen;
  KeyM_CertificateElementTypeOfStructure elementOfStruct;
  uint16 count;

  retVal = E_NOT_OK;
  count = 0u;
  /* @Trace: KeyM_SUD_FUNC_850 */
  if (NULL_PTR != ptrCertElement->PtrElement)
  {
    elementDataLen = ptrCertElement->PtrElement->Element.Length;
    ptrElementData = ptrCertElement->PtrElement->Element.PtrData;

    if (NULL_PTR != ptrElementData)
    {
      elementOfStruct = ptrCertElement->ElementOfStruct;
      if (KEYM_CERT_EXTENSION == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_851 */
        (void)KeyM_PrvCvcElementGetExtensionCount(ptrElementData, \
          elementDataLen, &count);

        if (1u != count)
        {
          retVal = E_NOT_OK;
        }
        else
        {
          retVal = KeyM_PrvCvcElementGetExtensionByIndex(ptrElementData, \
            elementDataLen, 0u, ptrCertElementData, ptrCertElementDataLen);
        }
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_852 */
        retVal = E_NOT_OK;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvCvcElementGetFirst                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get CVC certificate element data which has one        **
**                      element is assigned to the respective OID             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCertElement                                        **
**                                                                            **
** InOut Parameters   : ptrCertElementDataLen                                 **
**                                                                            **
** Output Parameters  : ptrCertElementData, ptrCertElementIterator            **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvCvcElementGetExtensionCount                   **
**                      KeyM_PrvCvcElementGetExtensionByIndex                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcElementGetFirst(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(KeyM_CertElementIteratorType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrCertElementIterator, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  uint32 elementDataLen;
  KeyM_CertificateElementTypeOfStructure elementOfStruct;
  uint16 count;

  retVal = E_NOT_OK;
  count = 0u;
  /* @Trace: KeyM_SUD_FUNC_854 */
  if (NULL_PTR != ptrCertElement->PtrElement)
  {
    elementDataLen = ptrCertElement->PtrElement->Element.Length;
    ptrElementData = ptrCertElement->PtrElement->Element.PtrData;

    if (NULL_PTR != ptrElementData)
    {
      elementOfStruct = ptrCertElement->ElementOfStruct;
      if (KEYM_CERT_EXTENSION == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_855 */
        (void)KeyM_PrvCvcElementGetExtensionCount(ptrElementData, \
          elementDataLen, &count);

        retVal = KeyM_PrvCvcElementGetExtensionByIndex(ptrElementData, \
          elementDataLen, 0u, ptrCertElementData, ptrCertElementDataLen);
      }
      else if (KEYM_CERT_SUBJECT_AUTHORIZATION == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_856 */
        /* This element has 2 sub-element data */
        count = 2u;

        retVal = KeyM_PrvCvcElementGetHolderAuthorByIndex(ptrElementData, \
          elementDataLen, 0u, ptrCertElementData, ptrCertElementDataLen);
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_857 */
        retVal = E_NOT_OK;
      }

      if (E_OK == retVal)
      {
        /* @Trace: KeyM_SUD_FUNC_858 */
        ptrCertElementIterator->elementCount = count;
        ptrCertElementIterator->currentIndex = 0u;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvCvcElementGetNext                             **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get the next element data of a CVC Certificate        **
**                      element which may has multiple element data are       **
**                      assigned to one OID                                   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCertElement                                        **
**                                                                            **
** InOut Parameters   : ptrCertElementDataLen                                 **
**                                                                            **
** Output Parameters  : ptrCertElementData, ptrCertElementIterator            **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvCvcElementGetExtensionByIndex                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcElementGetNext(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(KeyM_CertElementIteratorType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrCertElementIterator, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  uint32 elementDataLen;
  KeyM_CertificateElementTypeOfStructure elementOfStruct;
  uint16 indexCnt;

  retVal = E_NOT_OK;

  /* @Trace: KeyM_SUD_FUNC_859 */
  if (NULL_PTR != ptrCertElement->PtrElement)
  {
    elementDataLen = ptrCertElement->PtrElement->Element.Length;
    ptrElementData = ptrCertElement->PtrElement->Element.PtrData;

    if (NULL_PTR != ptrElementData)
    {
      elementOfStruct = ptrCertElement->ElementOfStruct;
      indexCnt = ptrCertElementIterator->currentIndex + 1u;
      if (KEYM_CERT_EXTENSION == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_860 */
        retVal = KeyM_PrvCvcElementGetExtensionByIndex(ptrElementData,\
          elementDataLen, indexCnt, ptrCertElementData, ptrCertElementDataLen);
      }
      else if (KEYM_CERT_SUBJECT_AUTHORIZATION == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_861 */
        retVal = KeyM_PrvCvcElementGetHolderAuthorByIndex(ptrElementData,\
          elementDataLen, indexCnt, ptrCertElementData, ptrCertElementDataLen);
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_862 */
        retVal = E_NOT_OK;
      }

      if (E_OK == retVal)
      {
        /* @Trace: KeyM_SUD_FUNC_863 */
        ptrCertElementIterator->currentIndex = indexCnt;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvCopyParsedCVCCertificate                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Copy parsed CVC certificate                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrSrcCert                                            **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrDesCert                                            **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvElementCopy                                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvCopyParsedCVCCertificate(\
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrSrcCert,
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrDesCert)
{
  uint8 indexCnt;
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrSrcElement;
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrDesElement;
  /* @Trace: KeyM_SUD_FUNC_864 */
  /* Copy certificate body */
  ptrDesCert->TBSCert.PtrData = ptrSrcCert->TBSCert.PtrData;
  ptrDesCert->TBSCert.Length = ptrSrcCert->TBSCert.Length;
  /* Copy RawProfileId */
  ptrDesElement = ptrDesCert->PtrRawProfileId;
  ptrSrcElement = ptrSrcCert->PtrRawProfileId;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy RawAuthorityRefer */
  ptrDesElement = ptrDesCert->PtrRawAuthorityRefer;
  ptrSrcElement = ptrSrcCert->PtrRawAuthorityRefer;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy RawPublicKeyObjectId */
  ptrDesElement = ptrDesCert->PtrRawPublicKeyObjectId;
  ptrSrcElement = ptrSrcCert->PtrRawPublicKeyObjectId;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy RawHolderRefer */
  ptrDesElement = ptrDesCert->PtrRawHolderRefer;
  ptrSrcElement = ptrSrcCert->PtrRawHolderRefer;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy RawHolderAuthorTemplate */
  ptrDesElement = ptrDesCert->PtrRawHolderAuthorTemplate;
  ptrSrcElement = ptrSrcCert->PtrRawHolderAuthorTemplate;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy RawEffectiveDate */
  ptrDesElement = ptrDesCert->PtrRawEffectiveDate;
  ptrSrcElement = ptrSrcCert->PtrRawEffectiveDate;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy RawExpirationDate */
  ptrDesElement = ptrDesCert->PtrRawExpirationDate;
  ptrSrcElement = ptrSrcCert->PtrRawExpirationDate;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy SignatureValue */
  ptrDesElement = ptrDesCert->PtrSignatureValue;
  ptrSrcElement = ptrSrcCert->PtrSignatureValue;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);

  ptrDesCert->EffectiveDate = ptrSrcCert->EffectiveDate;
  ptrDesCert->ExpirationDate = ptrSrcCert->ExpirationDate;
  ptrDesCert->PublicKeyType = ptrSrcCert->PublicKeyType;
  ptrDesCert->ExtensionNum = ptrSrcCert->ExtensionNum;
  ptrDesCert->DomainParamNum = ptrSrcCert->DomainParamNum;
  /* @Trace: KeyM_SUD_FUNC_865 */
  /* Copy parsed PublicKeyDomainParams */
  for (indexCnt = 0u; indexCnt < ptrDesCert->DomainParamNum; indexCnt++)
  {
    ptrDesElement = &ptrDesCert->PtrPublicKeyDomainParams[indexCnt];
    ptrSrcElement = &ptrSrcCert->PtrPublicKeyDomainParams[indexCnt];
    KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  }
  /* Copy RawExtensions */
  for (indexCnt = 0u; indexCnt < ptrDesCert->ExtensionNum; indexCnt++)
  {
    ptrDesElement = &ptrDesCert->PtrExtensions[indexCnt];
    ptrSrcElement = &ptrSrcCert->PtrExtensions[indexCnt];
    KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)

/*******************************************************************************
** Function Name      : KeyM_PrvAdjustCvcCertificate                          **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Adjust parsed CVC certificate based on new address    **
**                      of certificate data buffer                            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCurAddress, ptrNewAddress                          **
**                                                                            **
** InOut Parameters   : ptrParsedCert                                         **
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
FUNC(void, KEYM_CODE) KeyM_PrvAdjustCvcCertificate(\
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCurAddress, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrNewAddress)
{
  sint32 deltaAddress;
  uint8 indexCnt;

  deltaAddress = (sint32)(ptrNewAddress - ptrCurAddress);
  /* @Trace: KeyM_SUD_FUNC_866 */
  /* Adjust certificate body */
  ptrParsedCert->TBSCert.PtrData = \
    &(ptrParsedCert->TBSCert.PtrData)[deltaAddress];
  /* Adjust RawProfileId */
  ptrParsedCert->PtrRawProfileId->Element.PtrData = \
    &(ptrParsedCert->PtrRawProfileId->Element.PtrData)[deltaAddress];
  /* Adjust RawAuthorityRefer */
  ptrParsedCert->PtrRawAuthorityRefer->Element.PtrData = \
    &(ptrParsedCert->PtrRawAuthorityRefer->Element.PtrData)[deltaAddress];
  /* Adjust RawPublicKeyObjectId */
  ptrParsedCert->PtrRawPublicKeyObjectId->Element.PtrData = \
    &(ptrParsedCert->PtrRawPublicKeyObjectId->Element.PtrData)[deltaAddress];
  /* Adjust RawHolderRefer */
  ptrParsedCert->PtrRawHolderRefer->Element.PtrData = \
    &(ptrParsedCert->PtrRawHolderRefer->Element.PtrData)[deltaAddress];
  /* Adjust RawHolderAuthorTemplate */
  ptrParsedCert->PtrRawHolderAuthorTemplate->Element.PtrData = \
    &(ptrParsedCert->PtrRawHolderAuthorTemplate->Element.PtrData)[deltaAddress];
  /* Adjust RawEffectiveDate */
  ptrParsedCert->PtrRawEffectiveDate->Element.PtrData = \
    &(ptrParsedCert->PtrRawEffectiveDate->Element.PtrData)[deltaAddress];
  /* Adjust RawExpirationDate */
  ptrParsedCert->PtrRawExpirationDate->Element.PtrData = \
    &(ptrParsedCert->PtrRawExpirationDate->Element.PtrData)[deltaAddress];
  /* Adjust SignatureValue */
  ptrParsedCert->PtrSignatureValue->Element.PtrData = \
    &(ptrParsedCert->PtrSignatureValue->Element.PtrData)[deltaAddress];
  /* @Trace: KeyM_SUD_FUNC_867 */
  /* Adjust PtrPublicKeyDomainParams */
  for (indexCnt = 0u; indexCnt < ptrParsedCert->DomainParamNum; indexCnt++)
  {
    ptrParsedCert->PtrPublicKeyDomainParams[indexCnt].Element.PtrData = \
      &(ptrParsedCert->PtrPublicKeyDomainParams[indexCnt].Element.PtrData)\
      [deltaAddress];
  }
  /* Adjust extensions */
  for (indexCnt = 0u; indexCnt < ptrParsedCert->ExtensionNum; indexCnt++)
  {
    ptrParsedCert->PtrExtensions[indexCnt].Element.PtrData = \
      &(ptrParsedCert->PtrExtensions[indexCnt].Element.PtrData)[deltaAddress];
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvRecoverCvcCertificate                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Recover parsed CVC certificate                        **
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
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvRecoverCvcCertificate(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert;
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedElement;
  uint16 elementIndex;
  uint8 indexCnt;

  ptrParsedCert = (KeyM_CvcCertificateType*)ptrCert->PtrParsedCert;
  /* @Trace: KeyM_SUD_FUNC_868 */
  /* Recover RawProfileId */
  elementIndex = ptrParsedCert->PtrRawProfileId->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrRawProfileId;
  /* Recover RawAuthorityRefer */
  elementIndex = ptrParsedCert->PtrRawAuthorityRefer->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrRawAuthorityRefer;
  /* Recover RawPublicKeyObjectId */
  elementIndex = ptrParsedCert->PtrRawPublicKeyObjectId->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrRawPublicKeyObjectId;
  /* Recover RawHolderRefer */
  elementIndex = ptrParsedCert->PtrRawHolderRefer->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrRawHolderRefer;
  /* Recover RawHolderAuthorTemplate */
  elementIndex = ptrParsedCert->PtrRawHolderAuthorTemplate->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrRawHolderAuthorTemplate;
  /* Recover RawEffectiveDate */
  elementIndex = ptrParsedCert->PtrRawEffectiveDate->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrRawEffectiveDate;
  /* Recover RawExpirationDate */
  elementIndex = ptrParsedCert->PtrRawExpirationDate->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrRawExpirationDate;
  /* Recover SignatureValue */
  elementIndex = ptrParsedCert->PtrSignatureValue->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrSignatureValue;
  /* @Trace: KeyM_SUD_FUNC_869 */
  /* Recover PtrPublicKeyDomainParams */
  for (indexCnt = 0u; indexCnt < ptrParsedCert->DomainParamNum; indexCnt++)
  {
    ptrParsedElement = &ptrParsedCert->PtrPublicKeyDomainParams[indexCnt];
    elementIndex = ptrParsedElement->ElementIndex;
    ptrCert->PtrCertElement[elementIndex].PtrElement = ptrParsedElement;
  }
  /* Recover RawExtensions */
  for (indexCnt = 0u; indexCnt < ptrParsedCert->ExtensionNum; indexCnt++)
  {
    ptrParsedElement = &ptrParsedCert->PtrExtensions[indexCnt];
    elementIndex = ptrParsedElement->ElementIndex;
    ptrCert->PtrCertElement[elementIndex].PtrElement = ptrParsedElement;
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_CvcWriteTag                                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write a CVC tag in ASN.1 format. This function works  **
**                      backwards in data buffer                              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrStartOfData, tag                                   **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrLengthBytes                                        **
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
static Std_ReturnType KeyM_CvcWriteTag(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrStartOfData, \
  const uint8 tag, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrLengthBytes)
{
  Std_ReturnType retVal;
  uint8 upperTag;

  upperTag = 0u;
  retVal = E_OK;

  /* @Trace: KeyM_SUD_FUNC_931 */
  if ((KEYM_CVC_CERTIFICATE_HOLDER_REFERENCE == tag) || \
    ((KEYM_CVC_CERTIFICATE_EXPIRATION_DATE <= tag) && \
    (KEYM_CVC_SIGNATURE >= tag)))
  {
    upperTag = 0x5Fu;
  }
  else if ((KEYM_CVC_CERTIFICATE == tag) || \
    ((KEYM_CVC_PUBLIC_KEY <= tag) && (KEYM_CVC_CERTIFICATE_BODY >= tag)))
  {
    upperTag = 0x7Fu;
  }
  else
  {
    /* Do nothing */
  }

  if (0u == upperTag)
  {
    /* @Trace: KeyM_SUD_FUNC_933 */
    if (1 > (*ptrPosition - ptrStartOfData))
    {
      retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
    }
    else
    {
      (*ptrPosition)--;
      **ptrPosition = tag;
      *ptrLengthBytes = 0x1u;
    }
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_934 */
    if (2 > (*ptrPosition - ptrStartOfData))
    {
      retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
    }
    else
    {
      (*ptrPosition)--;
      **ptrPosition = tag;
      (*ptrPosition)--;
      **ptrPosition = upperTag;
      *ptrLengthBytes = 0x2u;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvCvcWriteElement                               **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write a element in CVC certificate                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrStart, tag, ptrCert, ptrCertElement                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrLength                                             **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1WriteLength, KeyM_CvcWriteTag                **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcWriteElement(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength, \
  const uint8 tag)
{
  Std_ReturnType retVal;
  uint16 elementIndex;
  uint16 length;
  uint8 bytesToStoreLen;

  retVal = E_NOT_OK;
  /* @Trace: KeyM_SUD_FUNC_935 */
  if (NULL_PTR != ptrCertElement)
  {
    bytesToStoreLen = 0u;
    elementIndex = ptrCertElement->ElementIndex;
    length = ptrCert->PtrCertElement[elementIndex].ElementMaxLength;
    /* @Trace: KeyM_SUD_FUNC_936 */
    if (*ptrPosition < (&(ptrStart[length])))
    {
      retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
    }
    else
    {
      *ptrPosition -= length;
      /* Write length of publicExponent data */
      retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, length,\
        &bytesToStoreLen);

      if (KEYM_E_OK == retVal)
      {
        length += bytesToStoreLen;

        retVal = KeyM_CvcWriteTag(ptrPosition, ptrStart, tag, &bytesToStoreLen);
        /* @Trace: KeyM_SUD_FUNC_937 */
        if (KEYM_E_OK == retVal)
        {
          length += bytesToStoreLen;
          *ptrLength += length;
        }
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcWriteSignatureValue                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write signature value element in CVC certificate      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrStart, ptrSignValue, signValLength, ptrCert        **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrLength                                             **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1WriteLength, KeyM_CvcWriteTag,KeyM_PrvMemCopy**
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcWriteSignatureValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSignValue, \
  const uint16 signValLength, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  uint16 length;
  uint8 bytesToStoreLen;
  uint8 tag;

  bytesToStoreLen = 0u;
  length = signValLength;

  if (*ptrPosition < (&(ptrStart[length])))
  {
    /* @Trace: KeyM_SUD_FUNC_938 */
    retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_939 */
    (*ptrPosition) -= length;
    (void)KeyM_PrvMemCopy(ptrSignValue, *ptrPosition, length);
    /* Write length of data */
    retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, length,\
      &bytesToStoreLen);

    if (E_OK == retVal)
    {
      length += bytesToStoreLen;
      tag = KEYM_CVC_SIGNATURE;
      retVal = KeyM_CvcWriteTag(ptrPosition, ptrStart, tag, &bytesToStoreLen);

      if (E_OK == retVal)
      {
        length += bytesToStoreLen;
        *ptrLength += length;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcWriteExtensions                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write extension element in CVC certificate            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrStart, ptrExtArr, numberOfExt, ptrCert             **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrLength                                             **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1WriteLength, KeyM_CvcWriteTag                **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcWriteExtensions(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrExtArr, \
  const uint8 numberOfExt, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  uint16 elementIndex;
  uint8 index;
  uint16 subLength;
  uint16 length;
  uint8 bytesToStoreLen;
  uint8 tag;

  retVal = E_OK;
  bytesToStoreLen = 0u;
  length = 0u;

  /* @Trace: KeyM_SUD_FUNC_941 */
  for (index = 1u; ((index <= numberOfExt) && (E_OK == retVal)); index++)
  {
    elementIndex = ptrExtArr[numberOfExt - index].ElementIndex;
    subLength = ptrCert->PtrCertElement[elementIndex].ElementMaxLength;

    if (*ptrPosition < (&(ptrStart[subLength])))
    {
      retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
    }
    else
    {
      (*ptrPosition) -= subLength;
      /* Write length of data */
      retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, subLength,\
        &bytesToStoreLen);

      if (E_OK == retVal)
      {
        subLength += bytesToStoreLen;
        tag = KEYM_CVC_DISCRETIONARY_DATA_TEMPLATE;
        retVal = KeyM_CvcWriteTag(ptrPosition, ptrStart, tag, &bytesToStoreLen);

        if (E_OK == retVal)
        {
          subLength += bytesToStoreLen;
          length += subLength;
        }
      }
    }
  }

  if (E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_942 */
    /* Write length of data */
    retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, length, \
      &bytesToStoreLen);

    if (E_OK == retVal)
    {
      length += bytesToStoreLen;
      tag = KEYM_CVC_CERTIFICATE_EXTENSIONS;
      retVal = KeyM_CvcWriteTag(ptrPosition, ptrStart, tag, &bytesToStoreLen);

      if (E_OK == retVal)
      {
        length += bytesToStoreLen;
        *ptrLength += length;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcWriteEccPublicKeyValue                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write ECC public key value element in CVC certificate **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrStart, ptrParsedCert, ptrCert                      **
**                      ptrPublicKey, publicKeyLen                            **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrLength                                             **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1WriteLength, KeyM_CvcWriteTag,               **
**                      KeyM_PrvMemCopy                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcWriteEccPublicKeyValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKey, \
  const uint16 publicKeyLen, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement;
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrDomainParam;
  uint8 numberOfParam;
  uint16 elementIndex;
  uint8 index;
  uint16 subLength;
  uint8 bytesToStoreLen;
  uint8 tag;

  retVal = E_NOT_OK;
  bytesToStoreLen = 0u;
  ptrDomainParam = ptrParsedCert->PtrPublicKeyDomainParams;
  numberOfParam = ptrParsedCert->DomainParamNum;
  /* @Trace: KeyM_SUD_FUNC_945 */
  if ((1u == numberOfParam) || (6u == numberOfParam) || (7u == numberOfParam))
  {
    if (7u == numberOfParam)
    {
      tag = KEYM_CVC_COFACTOR;
    }
    else
    {
      tag = KEYM_CVC_PUBLIC_POINT;
    }
    /* @Trace: KeyM_SUD_FUNC_946 */
    for (index = 1u; index <= numberOfParam; index++)
    {
      elementIndex = ptrDomainParam[numberOfParam - index].ElementIndex;
      ptrCertElement = &ptrCert->PtrCertElement[elementIndex];

      if (KEYM_CVC_PUBLIC_POINT != tag)
      {
        subLength = ptrCertElement->ElementMaxLength;
      }
      else
      {
        subLength = publicKeyLen;
      }

      if (*ptrPosition < (&(ptrStart[subLength])))
      {
        /* @Trace: KeyM_SUD_FUNC_947 */
        retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_948 */
        (*ptrPosition) -= subLength;

        if (KEYM_CVC_PUBLIC_POINT == tag)
        {
          (void)KeyM_PrvMemCopy(ptrPublicKey, *ptrPosition, subLength);
            /* Add one byte of 0x04 to indicate the public key format
            is uncompressed */
          (*ptrPosition)--;
          **ptrPosition = 0x04u;
          subLength++;
        }
        retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, subLength, \
          &bytesToStoreLen);

        if (E_OK == retVal)
        {
          subLength += bytesToStoreLen;
          retVal = KeyM_CvcWriteTag(ptrPosition, ptrStart, tag, \
            &bytesToStoreLen);

          if (E_OK == retVal)
          {
            subLength += bytesToStoreLen;
            *ptrLength += subLength;
            tag--;
          }
        }
      }

      if (E_OK != retVal)
      {
        break;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcParseRsaPublicKeyValue                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse RSA public key value element in CVC certificate **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrPublicKey, publicKeyLen                            **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrModulus, ptrExponent                               **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_CvcGetTag                                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcParseRsaPublicKeyValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKey, \
  const uint16 publicKeyLen, \
  P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrModulus, \
  P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrExponent)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  uint16 length;

  /* @Trace: KeyM_SUD_FUNC_949 */
  ptrPosition = ptrPublicKey;
  ptrEnd = &ptrPosition[publicKeyLen];
  length = 0u;
  ptrModulus->Length = 0u;
  ptrExponent->Length = 0u;

  /* Parse the RSA public key:
    RSAPublicKey ::= SEQUENCE {
    modulus INTEGER, -- n
    publicExponent INTEGER, -- e } */
  retVal = KeyM_CvcGetTag(&ptrPosition, ptrEnd, &length, \
    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
  if (E_OK == retVal)
  {
    /* Get modulus */
    retVal = KeyM_CvcGetTag(&ptrPosition, ptrEnd, &length, \
      KEYM_ASN1_INTEGER);
    if (E_OK == retVal)
    {
       ptrModulus->PtrData = ptrPosition;
       ptrModulus->Length = length;
       ptrPosition = &ptrPosition[length];
       /* Get exponent */
       retVal = KeyM_CvcGetTag(&ptrPosition, ptrEnd, &length, \
          KEYM_ASN1_INTEGER);
      if (E_OK == retVal)
      {
        ptrExponent->Length = length;
        ptrExponent->PtrData = ptrPosition;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcWriteRsaPublicKeyValue                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write RSA public key value element in CVC certificate **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrStart, ptrParsedCert, ptrCert                      **
**                      ptrPublicKey, publicKeyLen                            **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrLength                                             **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvCvcParseRsaPublicKeyValue, KeyM_CvcWriteTag,  **
**                      KeyM_Asn1WriteLength, KeyM_PrvMemCopy                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcWriteRsaPublicKeyValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKey, \
  const uint16 publicKeyLen, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  (void)ptrCert;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData;
  KeyM_AsnElementType modulus;
  KeyM_AsnElementType exponent;
  uint8 numberOfParam;
  uint8 index;
  uint16 subLength;
  uint16 length;
  uint8 bytesToStoreLen;
  uint8 tag;

  /* @Trace: KeyM_SUD_FUNC_952 */
  modulus.Length = 0u;
  modulus.PtrData = NULL_PTR;
  exponent.Length = 0u;
  exponent.PtrData = NULL_PTR;
  /* Get modulus and exponent */
  retVal = KeyM_PrvCvcParseRsaPublicKeyValue(ptrPublicKey, publicKeyLen, \
    &modulus, &exponent);

  if (E_OK == retVal)
  {
    bytesToStoreLen = 0u;
    length = 0u;
    tag = KEYM_CVC_PUBLIC_EXPONENT;
    subLength = exponent.Length;
    ptrData = exponent.PtrData;
    numberOfParam = ptrParsedCert->DomainParamNum;

    /* RSA public key has 2 parameters only */
    if (2u == numberOfParam)
    {
      /* @Trace: KeyM_SUD_FUNC_953 */
      for (index = 1u; ((index <= numberOfParam) && (E_OK == retVal)); index++)
      {
        if (*ptrPosition < (&(ptrStart[subLength])))
        {
          retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
        }
        else
        {
          (*ptrPosition) -= subLength;

          (void)KeyM_PrvMemCopy(ptrData, *ptrPosition, subLength);

          retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, subLength,\
            &bytesToStoreLen);

          if (E_OK == retVal)
          {
            subLength += bytesToStoreLen;
            retVal = KeyM_CvcWriteTag(ptrPosition, ptrStart, tag, \
              &bytesToStoreLen);

            if (E_OK == retVal)
            {
              subLength += bytesToStoreLen;
              length += subLength;
              tag--;
              subLength = modulus.Length;
              ptrData = modulus.PtrData;
            }
          }
        }
      }

      if (E_OK == retVal)
      {
        *ptrLength += length;
      }
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcWritePublicKeyValue                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write public key value element in CVC certificate     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrStart, ptrParsedCert, ptrCert                      **
**                      ptrPublicKey                                          **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrLength                                             **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Csm_KeyElementGet, KeyM_PrvCvcWriteRsaPublicKeyValue, **
**                      KeyM_PrvCvcWriteEccPublicKeyValue                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvCvcWritePublicKeyValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKey, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  uint32 length;

  /* @Trace: KeyM_SUD_FUNC_954 */
  length = KEYM_PUBLIC_KEY_VALUE_MAX_LENGTH;
  retVal = Csm_KeyElementGet(ptrCert->CsmSignVerifyKeyId, \
    KEYM_KEY_ELEMENT1_ID, ptrPublicKey, &length);

  if (E_OK == retVal)
  {
    if (KEYM_CERT_ALGORITHM_ECC == ptrCert->CertAlgorithm)
    {
      retVal = KeyM_PrvCvcWriteEccPublicKeyValue(ptrPosition, ptrStart, \
        ptrCert, ptrParsedCert, ptrPublicKey, (uint16)length, ptrLength);
    }
    else
    {
      retVal = KeyM_PrvCvcWriteRsaPublicKeyValue(ptrPosition, ptrStart, \
        ptrCert, ptrParsedCert, ptrPublicKey, (uint16)length, ptrLength);
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCvcCertificateGenerate                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Generate one CVC certificate skeleton in DER format   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCert, dataLength                                   **
**                                                                            **
** InOut Parameters   : ptrData                                               **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      KeyM_DataBuffer                                       **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvCvcWriteElement, KeyM_Asn1WriteLength,        **
**                      KeyM_PrvPartOfCvcCertificateGenerate,                 **
**                      Csm_SignatureGenerate, KeyM_PrvCvcWriteSignatureValue,**
**                      KeyM_PrvMemCopy, KeyM_CvcWriteTag                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcCertificateGenerate(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrDataLength)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrInputPosition;
  P2VAR(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert;
  uint16 length;
  uint16 subLength;
  uint8 buffer[KEYM_SIGNATURE_VALUE_MAX_LENGTH];
  uint32 bufferLength;
  uint8 bytesToStoreLen;

  length = 0u;
  ptrStart = &KeyM_DataBuffer[0u];
  ptrPosition = &ptrStart[KEYM_INTERAL_BUFFER_LENGTH];
  ptrParsedCert = (KeyM_CvcCertificateType*)ptrCert->PtrParsedCert;
  /* @Trace: KeyM_SUD_FUNC_870 */
  retVal = KeyM_PrvPartOfCvcCertificateGenerate(&ptrPosition, ptrStart, \
    ptrCert, ptrParsedCert, &buffer[0u], &length);

  if (E_OK == retVal)
  {
    /* Write Profile Identifier */
    retVal = KeyM_PrvCvcWriteElement(&ptrPosition, ptrStart, ptrCert, \
      ptrParsedCert->PtrRawProfileId, &length, \
      KEYM_CVC_CERTIFICATE_PROFILE_IDENTIFIER);
    /* @Trace: KeyM_SUD_FUNC_871 */
    if (E_OK == retVal)
    {
      bytesToStoreLen = 0u;
      /* Write length of TBS */
      retVal = KeyM_Asn1WriteLength(&ptrPosition, ptrStart, length, \
        &bytesToStoreLen);
      /* @Trace: KeyM_SUD_FUNC_872 */
      if (E_OK == retVal)
      {
        length += bytesToStoreLen;
        /* Write tag of TBS */
        retVal = KeyM_CvcWriteTag(&ptrPosition, ptrStart, \
          KEYM_CVC_CERTIFICATE_BODY, \
          &bytesToStoreLen);
        if (E_OK == retVal)
        {
          bufferLength = 0u;
          length += bytesToStoreLen;
          /* Make signature */
          retVal = Csm_SignatureGenerate(ptrCert->CsmSignGenerateJob.CsmJobId, \
            CRYPTO_OPERATIONMODE_SINGLECALL, ptrPosition, length, \
            &buffer[0u], &bufferLength);
          /* @Trace: KeyM_SUD_FUNC_873 */
          if (E_OK == retVal)
          {
            subLength = 0u;
            ptrInputPosition = &ptrData[*ptrDataLength];
            /* Write signature value */
            retVal = KeyM_PrvCvcWriteSignatureValue(&ptrInputPosition, \
              ptrData, &buffer[0u], (const uint16)bufferLength, &subLength);
            if (E_OK == retVal)
            {
              /* @Trace: KeyM_SUD_FUNC_874 */
              if ((&(ptrData[length])) > ptrInputPosition)
              {
                retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
              }
              else
              {
                ptrInputPosition -= length;
                (void)KeyM_PrvMemCopy(ptrPosition, ptrInputPosition, length);
                length += subLength;

                /* Write length of certificate */
                retVal = KeyM_Asn1WriteLength(&ptrInputPosition, ptrData, \
                  length, &bytesToStoreLen);
                /* @Trace: KeyM_SUD_FUNC_875 */
                if (E_OK == retVal)
                {
                  length += bytesToStoreLen;
                  /* Write tag of certificate */
                  retVal = KeyM_CvcWriteTag(&ptrInputPosition, ptrData,\
                    KEYM_CVC_CERTIFICATE, &bytesToStoreLen);
                  if (E_OK == retVal)
                  {
                    length += bytesToStoreLen;
                    *ptrDataLength = length;
                    KeyM_PtrResultData = ptrInputPosition;
                  }
                } /* @if (E_OK == retVal) */
              } /* @if (E_OK == retVal) */
            } /* @if (E_OK == retVal) */
          } /* @if (E_OK == retVal) */
        } /* @if (E_OK == retVal) */
      } /* @if (E_OK == retVal) */
    } /* @if (E_OK == retVal) */
  } /* @if (E_OK == retVal) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPartOfCvcCertificateGenerate                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvCvcCertificateGenerate,     **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvCvcCertificateGenerate                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrStart, ptrCert, ptrParsedCert, ptrBuffer           **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrLength                                             **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvCvcWriteExtensions, KeyM_PrvCvcWriteElement,  **
**                      KeyM_PrvCvcWritePublicKeyValue, KeyM_Asn1WriteLength, **
**                      KeyM_CvcWriteTag                                      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvPartOfCvcCertificateGenerate(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrBuffer, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  uint16 subLength;
  uint8 bytesToStoreLen;

  /* @Trace: KeyM_SUD_FUNC_955 */
  retVal = E_OK;

  /* Write Extensions */
  if ((NULL_PTR != ptrParsedCert->PtrExtensions) && \
    (0u < ptrParsedCert->ExtensionNum))
  {
    retVal = KeyM_PrvCvcWriteExtensions(ptrPosition, ptrStart, ptrCert, \
      ptrParsedCert->PtrExtensions, \
      ptrParsedCert->ExtensionNum, ptrLength);
  }

  if (E_OK == retVal)
  {
    /* Write Expiration Date */
    retVal = KeyM_PrvCvcWriteElement(ptrPosition, ptrStart, ptrCert,\
      ptrParsedCert->PtrRawExpirationDate, ptrLength,\
      KEYM_CVC_CERTIFICATE_EXPIRATION_DATE);

    if (E_OK == retVal)
    {
      /* Write Effective Date */
      retVal = KeyM_PrvCvcWriteElement(ptrPosition, ptrStart, ptrCert,\
        ptrParsedCert->PtrRawEffectiveDate, ptrLength,\
        KEYM_CVC_CERTIFICATE_EFFECTIVE_DATE);

      if (E_OK == retVal)
      {
        /* @Trace: KeyM_SUD_FUNC_958 */
        /* Write Holder Authorization Template */
        retVal = KeyM_PrvCvcWriteElement(ptrPosition, ptrStart, ptrCert,\
          ptrParsedCert->PtrRawHolderAuthorTemplate, ptrLength, \
          KEYM_CVC_CERTIFICATE_HOLDER_AUTHORIZATION_TEMPLATE);

        if (E_OK == retVal)
        {
          /* Write Holder Reference */
          retVal = KeyM_PrvCvcWriteElement(ptrPosition, ptrStart, ptrCert,\
            ptrParsedCert->PtrRawHolderRefer, ptrLength, \
            KEYM_CVC_CERTIFICATE_HOLDER_REFERENCE);
          /* @Trace: KeyM_SUD_FUNC_959 */
          if (E_OK == retVal)
          {
            subLength = 0u;
            /* Write Public Key value */
            retVal = KeyM_PrvCvcWritePublicKeyValue(ptrPosition, \
              ptrStart, ptrCert, ptrParsedCert, ptrBuffer, &subLength);

            if (E_OK == retVal)
            {
              /* @Trace: KeyM_SUD_FUNC_961 */
              /* Write Public Key algorithm */
              retVal = KeyM_PrvCvcWriteElement(ptrPosition, ptrStart, ptrCert,\
                ptrParsedCert->PtrRawPublicKeyObjectId,\
                &subLength, KEYM_CVC_OBJECT_IDENTIFIER);

              if (E_OK == retVal)
              {
                bytesToStoreLen = 0u;
                /* Write length of public key information */
                retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, \
                  subLength, &bytesToStoreLen);
                /* @Trace: KeyM_SUD_FUNC_962 */
                if (E_OK == retVal)
                {
                  /* Write tag of public key */
                  subLength += bytesToStoreLen;
                  retVal = KeyM_CvcWriteTag(ptrPosition, ptrStart,\
                    KEYM_CVC_PUBLIC_KEY, &bytesToStoreLen);
                  if (E_OK == retVal)
                  {
                    /* @Trace: KeyM_SUD_FUNC_963 */
                    subLength += bytesToStoreLen;
                    *ptrLength += subLength;
                    /* Write Authority Reference */
                    retVal = KeyM_PrvCvcWriteElement(ptrPosition, ptrStart, \
                      ptrCert, ptrParsedCert->PtrRawAuthorityRefer, \
                      ptrLength, KEYM_CVC_CERTIFICATE_AUTHORITY_REFERENCE);
                  }
                }
              } /* @if (E_OK == retVal) */
            } /* @if (E_OK == retVal) */
          } /* @if (E_OK == retVal) */
        } /* @if (E_OK == retVal) */
      } /* @if (E_OK == retVal) */
    } /* @if (E_OK == retVal) */
  } /* @if (E_OK == retVal) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) */
#endif /* (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF) */
#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

#endif /* (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */
#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:11.5 CERT-C:EXP36-C */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
