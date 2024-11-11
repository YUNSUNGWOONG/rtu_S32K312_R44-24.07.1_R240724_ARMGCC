/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_X509.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key Manager internal API Functionality of X509                **
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
** 1.0.1.0   27-Mar-2021   TamTV6       Fix defect #18117, #18146, #18212,    **
**                                      #18166, Add Trace SUD                 **
** 1.0.2     08-Nov-2021   TamTV6       Implement #20971                      **
** 1.0.3.0   20-May-2022   DienTC1      #22113                                **
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
** 1.0.6.0   09-Dec-2022   DienTC1      #CP44-1308                            **
** 1.0.6.1   08-Feb-2023   DienTC1      #CP44-1655                            **
** 1.0.7.0   07-Apr-2023   PhuocLH9     #CP44-1636,#CP44-1664,#CP44-1854      **
**                                      #CP44-1541,#CP44-1665,#CP44-1684      **
** 1.0.8.0   31-Jul-2023   PhuocLH9     #CP44-2396,#CP44-2394                 **
** 1.0.9.0   21-Feb-2024   JS Kang      #CP44-3635                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:11.5 CERT-C:EXP36-C [Justified:Low] 
   "It uses casting from void* to object(struct) pointer in order to read a raw 
   memory by the specific format. If using working around like memory copy to 
   pass over this violation, the source code becomes very complex, hard to read 
   and take time to fix testing failed cases." */
/* polyspace-begin MISRA-C3:10.3 [Justified:Low] 
   "It needs to calculate the length without the tainted data." */
/* polyspace-begin MISRA-C3:10.4 [Justified:Low] 
   "It needs to calculate the length without the tainted data." */
/* polyspace-begin MISRA-C3:12.1 [Justified:Low] 
   "It needs to calculate the length without the tainted data." */
/* polyspace-begin MISRA-C3:2.2 [Justified:Low] 
   "It needs to calculate the length without the tainted data." */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM X509 header file */
#include "KeyM_X509.h"
/* KeyM X509 CRL header file */
#include "KeyM_X509_Crl.h"
/* KeyM X509 CRT header file */
#include "KeyM_X509_Crt.h"
/* KeyM internal function prototype */
#include "KeyM_IntFunc.h"
/* KeyM OID Header file */
#include "KeyM_OID.h"
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
#if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
  (KEYM_CERT_X509_CRL_ENABLED == STD_ON))
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509ParseTime(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  const uint8 length, \
  const uint8 yearLength, \
  P2VAR(KeyM_X509TimeType, AUTOMATIC, KEYM_APPL_DATA) ptrTime);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509CheckTimeDataValid(\
  P2CONST(KeyM_X509TimeType, AUTOMATIC, KEYM_APPL_CONST) ptrTime);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetAttrTypeValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCurName, \
  P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrValue);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetBasicConstraintsExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetKeyUsageExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetExtendedKeyUsageExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetSubjectAltNameExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCrlDistributionPointsExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetSubjectKeyIdentExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetAuthorityKeyIdentExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetAuthorityInfoAccessExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetUnknownExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCrlNumberExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCrlIssuingDistributionPointExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509ParsingExtension(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  const uint8 extType);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetAlgorithmCount(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAlgData, \
  const uint32 algDataLength, \
  const uint8 algorithmType, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetExtensionCount(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtensionData, \
  const uint32 extDataLength, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount,\
  const KeyM_CertFormatType certFormat);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetAlgorithmByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAlgData, \
  const uint32 algDataLength, \
  const uint8 algorithmType, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetIssuerSubjectByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrIssuerSubjectData, \
  const uint32 issuerDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetExtensionByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtensionData, \
  const uint32 extDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen, \
  const KeyM_CertFormatType certFormat);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetRsaAlgorithmByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAlgData, \
  const uint32 algDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetRsaAlgorithmCount(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAlgData, \
  const uint32 algDataLength, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetEccAlgorithmByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAlgData, \
  const uint32 algDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetEccAlgorithmCount(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAlgData, \
  const uint32 algDataLength, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint32 KeyM_PrvX509CountDuplicatesInSet(
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrSet, \
  VAR(uint32, AUTOMATIC) size, \
  VAR(uint32, AUTOMATIC) index);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetRevokedCertByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrRevokedCertData, \
  const uint32 revokDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name      : KeyM_PrvX509GetVersion                                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get version element in a certificate                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd, tag                                           **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert, ptrRawVersion                   **
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
**                      KeyM_Asn1GetTag, KeyM_PrvCheckCertificateElement      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetVersion(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrRawVersion, \
  const uint8 tag)
{
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrVerEnd;
  uint16 retVal;
  uint16 length;
  uint16 elementIndex;
  boolean hasVersion;

  length = 0U;
  hasVersion = KEYM_FALSE;
  /* @Trace: KeyM_SUD_FUNC_439 */
  /* Get tag */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);

  if (KEYM_E_ASN1_UNEXPECTED_TAG == retVal)
  {
    /* The version element is optional, so the unexpected tag error
      is accepted */
    retVal = KEYM_E_OK;
  }
  else if (KEYM_E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_440 */
    #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
    if (KEYM_ASN1_INTEGER != tag)
    #endif
    {
      /* Update end position */
      ptrVerEnd = &(*ptrPosition)[length];
      /* Get version number */
      retVal = KeyM_Asn1GetTag(ptrPosition, ptrVerEnd, &length, \
        KEYM_ASN1_INTEGER);
    }
    hasVersion = KEYM_TRUE;
  }
  else
  {
    /* Do nothing */
  }

  if (KEYM_E_OK == retVal)
  {
    if ((NULL_PTR != ptrRawVersion) && (KEYM_TRUE == hasVersion))
    {
      /* @Trace: KeyM_SUD_FUNC_441 */
      elementIndex = ptrRawVersion->ElementIndex;
      /* Check the certificate element of Version */
      retVal = KeyM_PrvCheckCertificateElement(ptrCert, elementIndex, \
        KEYM_ASN1_INTEGER, NULL_PTR, 0u);
      if (KEYM_E_OK == retVal)
      {
        /* Update raw Version tag, data and length */
        ptrRawVersion->Element.Tag = KEYM_ASN1_INTEGER;
        ptrRawVersion->Element.Length = length;
        ptrRawVersion->Element.PtrData = *ptrPosition;
        /* Update position to the next element of DER certificate */
        *ptrPosition = &(*ptrPosition)[length];
        ptrCert->PtrCertElement[elementIndex].PtrElement = ptrRawVersion;
      }
    }
    else if ((NULL_PTR == ptrRawVersion) && (KEYM_FALSE == hasVersion))
    {
      /* @Trace: KeyM_SUD_FUNC_442 */
      /* Accept the case there is no element */
      retVal = KEYM_E_OK;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_443 */
      retVal = KEYM_E_INVALID_VERSION;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509GetIssuerSubject                          **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get Issuer or Subject element in a certificate        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrEnd, numberOfName                                  **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert                                  **
**                                                                            **
** Output Parameters  : ptrNameArr                                            **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1GetTag, KeyM_PrvCheckCertificateElement      **
**                      KeyM_PrvX509GetAttrTypeValue                          **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetIssuerSubject(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrNameArr, \
  const uint8 numberOfName)
{
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCurrentName;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrDataEnd;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSetEnd;
  KeyM_ElementType curName;
  KeyM_AsnElementType objectId;
  KeyM_AsnElementType value;
  uint16 retVal;
  uint16 length;
  uint16 elementIndex;
  uint8 nameIndex;
  uint8 indexCnt;

  length = 0U;
  nameIndex = 0U;
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
    KEYM_ASN1_SEQUENCE | KEYM_ASN1_PC_CONSTRUCTED);

  ptrDataEnd = &(*ptrPosition)[length];
  /* @Trace: KeyM_SUD_FUNC_444 */
  if (KEYM_E_OK == retVal)
  {
    if ((NULL_PTR != ptrNameArr) && (0u < numberOfName))
    {
      /* @Trace: KeyM_SUD_FUNC_445 */
      while ((*ptrPosition < ptrDataEnd) && \
        (KEYM_E_OK == retVal) && (nameIndex < numberOfName))
      {
        /* Parse SET */
        retVal = KeyM_Asn1GetTag(ptrPosition, ptrDataEnd, &length, \
          KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SET);

        if (KEYM_E_OK == retVal)
        {
          ptrSetEnd  = &(*ptrPosition)[length];
          /* @Trace: KeyM_SUD_FUNC_446 */
          while ((*ptrPosition < ptrSetEnd) && \
            (KEYM_E_OK == retVal) && (nameIndex < numberOfName))
          {
            objectId.PtrData = NULL_PTR;
            objectId.Length = 0u;
            objectId.Tag = 0u;
            value.PtrData = NULL_PTR;
            value.Length = 0u;
            value.Tag = 0u;
            curName.ElementIndex = 0u;
            curName.Element.PtrData = NULL_PTR;
            curName.Element.Length = 0u;
            curName.Element.Tag = 0u;

            retVal = KeyM_PrvX509GetAttrTypeValue(ptrPosition, ptrSetEnd, \
              &curName, &objectId, &value);

            if (KEYM_E_OK == retVal)
            {
              /* @Trace: KeyM_SUD_FUNC_447 */
              for (indexCnt = 0u; indexCnt < numberOfName; indexCnt++)
              {
                ptrCurrentName = &ptrNameArr[indexCnt];
                elementIndex = ptrCurrentName->ElementIndex;
                /* Check the certificate element */
                retVal = KeyM_PrvCheckCertificateElement(ptrCert, \
                  elementIndex, value.Tag, objectId.PtrData,\
                  objectId.Length);

                if (KEYM_E_OK == retVal)
                {
                  ptrCurrentName->Element.PtrData = curName.Element.PtrData;
                  ptrCurrentName->Element.Length = curName.Element.Length;
                  ptrCurrentName->Element.Tag = curName.Element.Tag;
                  ptrCert->PtrCertElement[elementIndex].PtrElement = \
                    ptrCurrentName;
                  nameIndex++;
                  break;
                }
              }
            } /* @if (KEYM_E_OK == retVal) */
          } /* @((*ptrPosition < ptrSetEnd) && (KEYM_E_OK == retVal) &&
          (nameIndex < extensionNum)) */
        } /* @ if (KEYM_E_OK == retVal) */
      } /* @while ((*ptrPosition < ptrDataEnd) && (KEYM_E_OK == retVal) &&
      (nameIndex < extensionNum)) */
    }
    else
    {
      retVal = KEYM_E_INVALID_NAME;
    } /* @if (NULL_PTR != ptrNameArr) */
  } /* @if (KEYM_E_OK == retVal) */

  /* @Trace: KeyM_SUD_FUNC_448 */
  if ((KEYM_E_OK == retVal) && 
      /* Remove this to support universal config: ((nameIndex != numberOfName) || */
      (*ptrPosition != ptrDataEnd))
  {
    retVal = KEYM_E_INVALID_NAME;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509GetSignAlgorithm                          **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get signature algorithm identifier element in a       **
**                      certificate                                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd, elementStruct                                 **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert                                  **
**                                                                            **
** Output Parameters  : ptrSignAlgType, ptrSignAlgorithm                      **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1GetTag, KeyM_PrvCheckCertificateElement      **
**                      KeyM_Asn1GetAlgorithmIdent,                           **
**                      KeyM_PrvX509GetSignatureAlgType,                      **
**                      KeyM_PrvX509ParseRsaSsaPssParams,                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetSignAlgorithm(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSignAlgType, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrSignAlgorithm)
{
  KeyM_AsnElementType objectId;
  KeyM_AsnElementType params;
  uint16 length;
  uint8 tag;
  uint16 retVal;
  uint16 elementIndex;
  uint8 signAlgType;
  /* Initialize variables */
  length = 0U;
  tag = KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE;
  signAlgType = 0u;
  objectId.Tag = KEYM_ZERO;
  objectId.Length = KEYM_ZERO;
  objectId.PtrData = NULL_PTR;

  /* Get AlgorithmIdentifier */
  /* @Trace: KeyM_SUD_FUNC_449 */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);

  if (KEYM_E_OK == retVal)
  {
    if (NULL_PTR != ptrSignAlgorithm)
    {
      /* @Trace: KeyM_SUD_FUNC_451 */
      /* Update raw Signature tag, data and length */
      ptrSignAlgorithm->Element.Tag = tag;
      ptrSignAlgorithm->Element.Length = length;
      ptrSignAlgorithm->Element.PtrData = *ptrPosition;
      params.PtrData = NULL_PTR;
      params.Length = 0u;
      params.Tag = 0u;
      /* Parse AlgorithmIdentifier */
      retVal = KeyM_Asn1GetAlgorithmIdent(ptrPosition, \
        &(*ptrPosition)[length], &objectId, &params);
      /* @Trace: KeyM_SUD_FUNC_452 */
      if (KEYM_E_OK == retVal)
      {
        retVal = KeyM_PrvX509GetSignatureAlgType(objectId.PtrData, \
          (uint8)objectId.Length, &signAlgType);

        if (KEYM_E_OK == retVal)
        {
          if ((KEYM_PK_RSASSA_PSS != signAlgType) && \
            ((KEYM_ASN1_NULL != params.Tag) && (0u != params.Tag)))
          {
            /* @Trace: KeyM_SUD_FUNC_454 */
            /* Make sure parameters are absent or NULL */
            retVal = KEYM_E_INVALID_ALG;
          }
          else if (KEYM_PK_RSASSA_PSS == signAlgType)
          {
            /* @Trace: KeyM_SUD_FUNC_455 */
            retVal = KeyM_PrvX509ParseRsaSsaPssParams(&params);
          }
          else
          {
            /* Do nothing */
          }
          /* @Trace: KeyM_SUD_FUNC_456 */
          if (KEYM_E_OK == retVal)
          {
            *ptrSignAlgType = signAlgType;
            elementIndex = ptrSignAlgorithm->ElementIndex;
            /* Check the certificate element of signature */
            retVal = KeyM_PrvCheckCertificateElement(ptrCert, \
              elementIndex, tag, NULL_PTR, 0u);
            /* @Trace: KeyM_SUD_FUNC_457 */
            if (KEYM_E_OK == retVal)
            {
              ptrCert->PtrCertElement[elementIndex].PtrElement = \
                ptrSignAlgorithm;
            }
          }
        }
        else
        {
          /* @Trace: KeyM_SUD_FUNC_453 */
          retVal = KEYM_E_INVALID_ALG;
        } /* @(KEYM_E_OK == retVal) */
      } /* @if (KEYM_E_OK == retVal) */
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_450 */
      retVal = KEYM_E_INVALID_ALG;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509GetValidTime                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get valid time of the certificate                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert                                  **
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
**                      KeyM_PrvCheckCertificateElement, KeyM_PrvX509GetTime  **
**                      KeyM_PrvX509ConvertDateToSecond                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetValidTime(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrRawValidTime, \
  P2VAR(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrParsedValidTime)
{
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrRawTime;
  KeyM_X509TimeType validTime;
  uint16 retVal;
  uint16 length;
  uint16 elementIndex;
  uint8 tag;

  length = 0U;
  tag = 0U;
  ptrRawTime = NULL_PTR;
  validTime.Year = 0u;
  validTime.Mon = 0u;
  validTime.Day = 0u;
  validTime.Hour = 0u;
  validTime.Min = 0u;
  validTime.Sec = 0u;
  /* @Trace: KeyM_SUD_FUNC_458 */
  /* Get time */
  retVal = KeyM_PrvX509GetTime(ptrPosition, ptrEnd, &tag, &length,\
    &ptrRawTime, &validTime);

  if (KEYM_E_OK == retVal)
  {
    if (NULL_PTR != ptrRawValidTime)
    {
      /* @Trace: KeyM_SUD_FUNC_460 */
      elementIndex = ptrRawValidTime->ElementIndex;
      /* Check the certificate element of validTime */
      retVal = KeyM_PrvCheckCertificateElement(ptrCert, elementIndex, \
        tag, NULL_PTR, 0u);
      if (KEYM_E_OK == retVal)
      {
        /* @Trace: KeyM_SUD_FUNC_461 */
        /* Update raw validTime tag, data and length */
        ptrRawValidTime->Element.Tag = tag;
        ptrRawValidTime->Element.Length = length;
        ptrRawValidTime->Element.PtrData = ptrRawTime;
        ptrCert->PtrCertElement[elementIndex].PtrElement = ptrRawValidTime;

        /* Convert This Update validTime to seconds */
        KeyM_PrvX509ConvertDateToSecond(&validTime, ptrParsedValidTime);
      }
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_459 */
      retVal = KEYM_E_INVALID_DATE;
    }
  }
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509ParseEccSignatureValue                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse ECDSA signature value in a certificate          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd, ptrLength                                     **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
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
**                      KeyM_Asn1GetTag                                       **
*******************************************************************************/
static uint16 KeyM_PrvX509ParseEccSignatureValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  uint16 retVal;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSignEnd;
  uint16 rsLength;

  rsLength = 0u;
  *ptrLength  = 0u;
  /* @Trace: KeyM_SUD_FUNC_559 */
  /* Parse ECC signature value */
  /*
   * Signature  ::=  SEQUENCE  {
   *      INTEGER   r, \
   *      INTEGER   s   }
   */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, ptrLength, \
    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

  if (KEYM_E_OK == retVal)
  {
    ptrSignEnd = &((*ptrPosition)[*ptrLength]);

    /* Get r element */
    retVal = KeyM_Asn1GetTag(ptrPosition, ptrSignEnd, &rsLength, \
      KEYM_ASN1_INTEGER);
    /* @Trace: KeyM_SUD_FUNC_560 */
    if (KEYM_E_OK == retVal)
    {
      *ptrPosition = &((*ptrPosition)[rsLength]);
      *ptrLength = rsLength;
      /* Get s element */
      retVal = KeyM_Asn1GetTag(ptrPosition, ptrSignEnd, &rsLength, \
        KEYM_ASN1_INTEGER);
      /* @Trace: KeyM_SUD_FUNC_561 */
      if (KEYM_E_OK == retVal)
      {
        *ptrPosition = &((*ptrPosition)[rsLength]);
        *ptrLength += rsLength;
      }
    }
  }

  return retVal;
}

/*******************************************************************************
** Function Name      : KeyM_PrvX509GetSignatureValue                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get signature value in a certificate                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd, signAlgType                                   **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert                                  **
**                                                                            **
** Output Parameters  : ptrSignValue                                          **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1GetBitstringNoneUnusedBits,                  **
**                      KeyM_PrvX509ParseEccSignatureValue,                   **
**                      KeyM_PrvCheckCertificateElement                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetSignatureValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  const uint8 signAlgType, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrSignValue)
{
  uint16 length;
  uint8 tag;
  uint16 retVal;
  uint16 elementIndex;

  length = 0U;
  /* Get tag */
  tag = **ptrPosition;
  /* @Trace: KeyM_SUD_FUNC_468 */
  /* The signature value is BITSTRING without unused bits */
  retVal = KeyM_Asn1GetBitstringNoneUnusedBits(ptrPosition, ptrEnd, &length);

  if (KEYM_E_OK == retVal)
  {
    if (NULL_PTR != ptrSignValue)
    {
      /* @Trace: KeyM_SUD_FUNC_470 */
      /* Get the tag, length and start position of signature element */
      ptrSignValue->Element.Tag = tag;
      ptrSignValue->Element.Length = length;
      ptrSignValue->Element.PtrData = *ptrPosition;
      /* signature type in below range are Ecc type - define in KeyM_OID.h*/
      if ((KEYM_PK_ECDSA_SHA1 <= signAlgType) &&
          (KEYM_PK_ECDSA_SHA512 >= signAlgType))
      {
          retVal = KeyM_PrvX509ParseEccSignatureValue(ptrPosition,
                                                      ptrEnd, &length);
      }
      else
      {
        /*signature are continous bit string - just jump to the end of length*/
        *ptrPosition = &(*ptrPosition)[ptrSignValue->Element.Length];
      }

      if (KEYM_E_OK == retVal)
      {
        /* @Trace: KeyM_SUD_FUNC_471 */
        elementIndex = ptrSignValue->ElementIndex;
        /* Check the certificate element of signature value */
        retVal = KeyM_PrvCheckCertificateElement(ptrCert, elementIndex, tag,
                                                 NULL_PTR, 0u);
        if (KEYM_E_OK == retVal)
        {
          /* @Trace: KeyM_SUD_FUNC_472 */
          ptrCert->PtrCertElement[elementIndex].PtrElement = ptrSignValue;
        }
      }
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_469 */
      retVal = KEYM_E_INVALID_SIGNATURE;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPartOfX509GetExtensions                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvX509GetExtensions,          **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvX509GetExtensions                             **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetBoolean,                 **
**                      KeyM_PrvX509GetCertExtensionType,                     **
**                      KeyM_PrvX509GetCrlExtensionType,                      **
**                      KeyM_PrvX509ParsingExtension,                         **
**                      KeyM_PrvCheckCertificateElement                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvPartOfX509GetExtensions(\
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
  uint8 isCritical;
  uint8 extType;
  uint16 length;
  uint8 tag;
  uint16 retVal;
  uint16 elementIndex;
  uint8 extIndex;
  uint8 indexCnt;
  /* Initialize variables */
  extIndex = 0u;

  /*
  * Extensions  ::=  SEQUENCE SIZE (1..MAX) OF Extension
  *
  * Extension  ::=  SEQUENCE  {
  *      extnID      OBJECT IDENTIFIER,
  *      critical    BOOLEAN DEFAULT FALSE,
  *      extnValue   OCTET STRING  }
  */
  /* Tag of extensions element is SEQUENCE OF */
  tag = KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE;
  /* Get tag and length of extensions element */
  length = 0u;
  /* @Trace: KeyM_SUD_FUNC_562 */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);

  /* Get extension */
  while ((*ptrPosition < ptrEnd) && (KEYM_E_OK == retVal) && \
    (extIndex < extensionNum))
  {
    /*
    * Extension  ::=  SEQUENCE  {
    *      extnID      OBJECT IDENTIFIER,
    *      critical    BOOLEAN DEFAULT FALSE,
    *      extnValue   OCTET STRING  }
    */

    /* Extension is SEQUENCE type */
    tag = KEYM_ASN1_SEQUENCE | KEYM_ASN1_PC_CONSTRUCTED;
    /* Get tag and length of extension */
    retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);
    /* @Trace: KeyM_SUD_FUNC_563 */
    if (KEYM_E_OK == retVal)
    {
      /* Update the RawExtensions tag, length, data */
      curExtension.Element.PtrData = *ptrPosition;
      curExtension.Element.Length = length;
      curExtension.Element.Tag = tag;

      /* Update end position of extension */
      ptrEndExtn = &(*ptrPosition)[length];

      /* Get extension ID */
      retVal = KeyM_Asn1GetTag(ptrPosition, ptrEndExtn, \
        &length, KEYM_ASN1_OID);

      if (KEYM_E_OK == retVal)
      {
        extnObjectId.PtrData = *ptrPosition;
        extnObjectId.Length = length;
        /* Go to the position of the critical element of extension */
        *ptrPosition = &(*ptrPosition)[length];

        /* Get critical */
        isCritical = 0U;
        retVal = KeyM_Asn1GetBoolean(ptrPosition, ptrEndExtn, \
                                     &isCritical);
        /* @Trace: KeyM_SUD_FUNC_565 */
        if ((KEYM_E_OK == retVal) || (KEYM_E_ASN1_UNEXPECTED_TAG == retVal))
        {
          /* Extension value should be octet string type */
          retVal = KeyM_Asn1GetTag(ptrPosition, ptrEndExtn, \
            &length, KEYM_ASN1_OCTET_STRING);

          if (KEYM_E_OK == retVal)
          {
            /* Detect supported extensions */
            extType = 0U;
            /* @Trace: KeyM_SUD_FUNC_566 */
            #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
            if (KEYM_CERT_FORMAT_X509 == ptrCert->CertFormat)
            {
              retVal = KeyM_PrvX509GetCertExtensionType(extnObjectId.PtrData, \
                (uint8)extnObjectId.Length, &extType);
            }
            else
            #endif
            {
              #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
                retVal = KeyM_PrvX509GetCrlExtensionType(\
                  extnObjectId.PtrData, \
                  (uint8)extnObjectId.Length, &extType);
              #endif
            }
            
            /* polyspace+7 DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "The value of if condition depends on input passed by other module, component or test. In reality, it is variant instead of a constant." */
            /* @Trace: KeyM_SUD_FUNC_568 */
            if (KEYM_E_OK != retVal)
            {
              /* if this extension is not recognized, \
                 return fail and finish parsing */
              retVal = KEYM_E_INVALID_EXTENSIONS;
            }
            else
            {
              /* Parse extension */
              retVal = KeyM_PrvX509ParsingExtension(ptrPosition, ptrEndExtn,\
                extType);

              if (KEYM_E_OK == retVal)
              {
                for (indexCnt = 0u; indexCnt < extensionNum; indexCnt++)
                {
                  ptrExtension = &ptrExtensions[indexCnt];
                  elementIndex = ptrExtension->ElementIndex;
                  /* Check the certificate element of extensions */
                  retVal = KeyM_PrvCheckCertificateElement(ptrCert,\
                    elementIndex, tag, extnObjectId.PtrData,\
                    extnObjectId.Length);

                  if (KEYM_E_OK == retVal)
                  {
                    ptrExtension->Element.PtrData = \
                      curExtension.Element.PtrData;
                    ptrExtension->Element.Length = curExtension.Element.Length;
                    ptrExtension->Element.Tag = curExtension.Element.Tag;
                    ptrCert->PtrCertElement[elementIndex].PtrElement = \
                      ptrExtension;
                    extIndex++;
                    break;
                  } /* @if ((KEYM_E_OK == retVal) ||
                  (KEYM_E_NO_ELEMENT_CONFIG == retVal)) */
                }
              } /* @if (KEYM_E_OK == retVal) */
            } /* @if (KEYM_E_OK == retVal) */
          } /* @if (KEYM_E_OK == retVal) */
        } /* @if (KEYM_E_OK == retVal) */
      } /* @if (KEYM_E_OK == retVal) */
    } /* @if (KEYM_E_OK == retVal) */
  } /* @while ((*ptrPosition < ptrEnd) && (KEYM_E_OK == retVal)) */
  /* @Trace: KeyM_SUD_FUNC_569 */
  if ((KEYM_E_OK == retVal) &&
      /* Remove this to support universal config: ((extIndex != extensionNum) || */
      (*ptrPosition != ptrEnd))
  {
    retVal = KEYM_E_INVALID_EXTENSIONS;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509GetExtensions                             **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get extension element in a X509 certificate           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd, extensionNum, option                          **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert                                  **
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
**                      KeyM_Asn1GetTag, KeyM_PrvPartOfX509GetExtensions      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetExtensions(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrExtensions, \
  const uint8 extensionNum, \
  const uint8 option)
{
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEndExtensions;
  uint16 length;
  uint8 tag;
  uint16 retVal;

  if ((*ptrPosition == ptrEnd) && (0u == extensionNum))
  {
    /* @Trace: KeyM_SUD_FUNC_473 */
    /* Because extensions element is optional so the certificate
      may not has these elements. The current position is
      the end of TBS. */
    retVal = KEYM_E_OK;
  }
  else if ((*ptrPosition == ptrEnd) || (0u == extensionNum))
  {
    /* @Trace: KeyM_SUD_FUNC_474 */
    retVal = KEYM_E_INVALID_EXTENSIONS;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_475 */
    /* Extensions element is context specific and constructed type */
    tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | option;
    /* Get tag and length */
    length = 0U;
    retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);

    if (KEYM_E_OK == retVal)
    {
      /* Update the end position of extensions element */
      ptrEndExtensions = &(*ptrPosition)[length];

      retVal = KeyM_PrvPartOfX509GetExtensions(ptrPosition, ptrEndExtensions, \
        ptrCert, ptrExtensions, extensionNum);
    } /* @if (KEYM_E_OK == retVal) */
  } /* @if (*ptrPosition == ptrEnd) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetKeyUsageExt                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse Key usage extension value                       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
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
**                      KeyM_Asn1GetTag                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetKeyUsageExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd)
{
  uint16 retVal;
  uint16 length;

  length = 0u;

  /* @Trace: KeyM_SUD_FUNC_589 */
  /* Key usage extension is BITSTRING type */
  /* Certificate type is a single byte bitstring */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, KEYM_ASN1_BIT_STRING);

  if (KEYM_E_OK == retVal)
  {
    *ptrPosition = &(*ptrPosition)[length];
    /* @Trace: KeyM_SUD_FUNC_590 */
    if (*ptrPosition != ptrEnd)
    {
      retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetBasicConstraintsExt                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse basic constraints extension value               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetBoolean                  **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetBasicConstraintsExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd)
{
  uint16 retVal;
  uint16 length;
  uint8 cA;

  length = 0U;
  cA = 0u;
  /*
   * BasicConstraints ::= SEQUENCE {
   *      cA                      BOOLEAN DEFAULT FALSE,
   *      pathLenConstraint       INTEGER (0..MAX) OPTIONAL }
   */
  /* @Trace: KeyM_SUD_FUNC_585 */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

  if ((KEYM_E_OK == retVal) && (length != 0u))
  {
    /* The CA element is BOOLEAN type */
    retVal = KeyM_Asn1GetBoolean(ptrPosition, ptrEnd, &cA);
    /* @Trace: KeyM_SUD_FUNC_586 */
    if ((KEYM_E_OK == retVal) || (KEYM_E_ASN1_UNEXPECTED_TAG == retVal))
    {
      retVal = KEYM_E_OK;
      /* @Trace: KeyM_SUD_FUNC_587 */
      if (*ptrPosition == ptrEnd)
      {
        /* The current position is the end position of extension value,
           it means that the Max Path Length element of extension value is
           not present. So do nothing in this case */
      }
      else
      {
        /* The pathLenConstraint element is INTEGER type */
        retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, \
          &length, KEYM_ASN1_INTEGER);
        /* @Trace: KeyM_SUD_FUNC_588 */
        if (KEYM_E_OK == retVal)
        {
          *ptrPosition = &(*ptrPosition)[length];

          if (*ptrPosition != ptrEnd)
          {
            retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
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
** Function Name      : KeyM_PrvX509GetExtendedKeyUsageExt                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse Extended Key usage extension                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetExtendedKeyUsageExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd)
{
  uint16 retVal;
  uint16 length;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtEnd;

  length = 0U;
  /* @Trace: KeyM_SUD_FUNC_591 */
  /* Get main sequence tag */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

  if (KEYM_E_OK == retVal)
  {
    ptrExtEnd = &(*ptrPosition)[length];
    /* @Trace: KeyM_SUD_FUNC_592 */
    while ((*ptrPosition < ptrExtEnd) && (KEYM_E_OK == retVal))
    {
      *ptrPosition = &(*ptrPosition)[KEYM_ONE];
      retVal = KeyM_Asn1GetLength(ptrPosition, ptrExtEnd, &length);

      if (KEYM_E_OK == retVal)
      {
        *ptrPosition = &(*ptrPosition)[length];
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetSubjectAltNameExt                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse Subject Alternative Name extension              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetSubjectAltNameExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd)
{
  uint16 retVal;
  uint16 length;
  uint8 tag;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtEnd;

  length = 0U;
  /* @Trace: KeyM_SUD_FUNC_594 */
  /* Get main sequence tag */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

  if (KEYM_E_OK == retVal)
  {
    ptrExtEnd = &(*ptrPosition)[length];
    /* @Trace: KeyM_SUD_FUNC_595 */
    while ((*ptrPosition < ptrExtEnd) && (KEYM_E_OK == retVal))
    {
      tag = **ptrPosition;

      if (tag != (KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | 2u))
      {
        /* NOTE: we only support dNSName at this point */
        retVal = KEYM_E_ASN1_UNEXPECTED_TAG;
      }
      else
      {
        *ptrPosition = &(*ptrPosition)[KEYM_ONE];
        retVal = KeyM_Asn1GetLength(ptrPosition, ptrExtEnd, &length);

        if (KEYM_E_OK == retVal)
        {
          *ptrPosition = &(*ptrPosition)[length];
        }
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetCrlDistributionPointsExt               **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse CRL Distribution Points extension               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
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
**                      KeyM_Asn1GetTag                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCrlDistributionPointsExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd)
{
  uint16 retVal;
  uint16 length;
  uint8 tag;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtEnd;

  length = 0U;
  /* @Trace: KeyM_SUD_FUNC_597 */
  /* Get main sequence tag */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

  if (KEYM_E_OK == retVal)
  {
    ptrExtEnd = &(*ptrPosition)[length];
    /* @Trace: KeyM_SUD_FUNC_598 */
    while ((*ptrPosition < ptrExtEnd) && (KEYM_E_OK == retVal))
    {
      tag = KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE;
      retVal = KeyM_Asn1GetTag(ptrPosition, ptrExtEnd, &length, tag);

      if (KEYM_E_OK == retVal)
      {
        /* NOTE: we only support DistributionPointName at this point */
        tag = (KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | \
          KEYM_ASN1_PC_CONSTRUCTED | 0u);

        retVal = KeyM_Asn1GetTag(ptrPosition, ptrExtEnd, &length, tag);

        if (KEYM_E_OK == retVal)
        {
          /* NOTE: we only support fullName at this point */
          retVal = KeyM_Asn1GetTag(ptrPosition, ptrExtEnd, &length, tag);

          if (KEYM_E_OK == retVal)
          {
            /* NOTE: we only support uniformResourceIdentifier at this point */
            tag = (KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | 6u);
            retVal = KeyM_Asn1GetTag(ptrPosition, ptrExtEnd, &length, tag);

            if (KEYM_E_OK == retVal)
            {
              *ptrPosition = &(*ptrPosition)[length];
            }
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
** Function Name      : KeyM_PrvX509GetSubjectKeyIdentExt                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse Subject Key Identifier extension                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
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
**                      KeyM_Asn1GetTag                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetSubjectKeyIdentExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd)
{
  uint16 retVal;
  uint16 length;
  length = 0U;

  /*
   * SubjectKeyIdentifier ::= KeyIdentifier
   */
  /* @Trace: KeyM_SUD_FUNC_583 */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, \
    &length, KEYM_ASN1_OCTET_STRING);

  if (KEYM_E_OK == retVal)
  {
    *ptrPosition = &(*ptrPosition)[length];
    /* @Trace: KeyM_SUD_FUNC_584 */
    if (*ptrPosition != ptrEnd)
    {
      retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name      : KeyM_PrvX509GetAuthorityKeyIdentExt                   **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse Authority Key Identifier extension              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetAuthorityKeyIdentExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd)
{
  uint16 retVal;
  uint16 length;

  length = 0U;

  /*
   * AuthorityKeyIdentifier ::= SEQUENCE {
   *    keyIdentifier             [0] KeyIdentifier           OPTIONAL,
   *    authorityCertIssuer       [1] GeneralNames            OPTIONAL,
   *    authorityCertSerialNumber [2] CertificateSerialNumber OPTIONAL  }
   */
  /* @Trace: KeyM_SUD_FUNC_579 */
  /* Get main sequence tag */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

  if (KEYM_E_OK == retVal)
  {
    /* Retrieve all available data */
    *ptrPosition = &(*ptrPosition)[length];
    /* @Trace: KeyM_SUD_FUNC_582 */
    if (*ptrPosition != ptrEnd)
    {
      retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetAuthorityInfoAccess                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse Authority Info Access extension                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetAuthorityInfoAccessExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd)
{
  uint16 retVal;
  uint16 length;

  length = 0U;

  /*
   *  AuthorityInfoAccessSyntax  ::=
   *        SEQUENCE SIZE (1..MAX) OF AccessDescription
   *
   *  AccessDescription  ::=  SEQUENCE {
   *           accessMethod          OBJECT IDENTIFIER,
   *           accessLocation        GeneralName  }
   */
  /* @Trace: KeyM_SUD_FUNC_1579 */
  /* Get main sequence tag */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

  if ((KEYM_E_OK == retVal) && (length != 0u))
  {    
      retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
        KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
      /* @Trace: KeyM_SUD_FUNC_1581 */
      if (KEYM_E_OK == retVal)
      {
        *ptrPosition = &(*ptrPosition)[length];
        /* @Trace: KeyM_SUD_FUNC_1582 */
        if (*ptrPosition != ptrEnd)
        {
          retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
        }
      }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetUnknownExt                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse Unknown extension. Returns all ext value.       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetUnknownExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd)
{
  uint16 retVal;
  uint16 length;

  retVal = KEYM_E_NOT_OK;

  /* @Trace: KeyM_SUD_FUNC_1583 */
  /* Gathers all available data in extension OCTET STRING */
  if (ptrEnd > *ptrPosition)
  {
    length = (uint16)(sint32)(ptrEnd - *ptrPosition);
    *ptrPosition = &(*ptrPosition)[length];
    
    retVal = KEYM_E_OK;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetCrlNumberExt                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse CRL number extension value                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
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
**                      KeyM_Asn1GetTag                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCrlNumberExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd)
{
  uint16 retVal;
  uint16 length;
  length = 0U;

  /*
   * CrlNumber ::= INTEGER (0..MAX)
   */
  /* @Trace: KeyM_SUD_FUNC_600 */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, KEYM_ASN1_INTEGER);

  if (KEYM_E_OK == retVal)
  {
    *ptrPosition = &(*ptrPosition)[length];
    /* @Trace: KeyM_SUD_FUNC_601 */
    if (*ptrPosition != ptrEnd)
    {
      retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetCrlIssuingDistributionPointExt         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse CRL Issuing Distribution Point extension        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
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
**                      KeyM_Asn1GetTag                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCrlIssuingDistributionPointExt(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd)
{
  uint16 retVal;
  uint16 length;
  uint8 tag;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtEnd;

  length = 0U;
  /* @Trace: KeyM_SUD_FUNC_602 */
  /* Get main sequence tag */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

  if (KEYM_E_OK == retVal)
  {
    ptrExtEnd = &(*ptrPosition)[length];

    /* NOTE: we only support DistributionPointName at this point */
    tag = (KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 0u);

    retVal = KeyM_Asn1GetTag(ptrPosition, ptrExtEnd, &length, tag);
    /* @Trace: KeyM_SUD_FUNC_603 */
    if (KEYM_E_OK == retVal)
    {
      /* NOTE: we only support fullName at this point */
      retVal = KeyM_Asn1GetTag(ptrPosition, ptrExtEnd, &length, tag);
      /* @Trace: KeyM_SUD_FUNC_604 */
      if (KEYM_E_OK == retVal)
      {
        /* NOTE: we only support uniformResourceIdentifier at this point */
        tag = (KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | 6u);
        retVal = KeyM_Asn1GetTag(ptrPosition, ptrExtEnd, &length, tag);
        /* @Trace: KeyM_SUD_FUNC_605 */
        if (KEYM_E_OK == retVal)
        {
          *ptrPosition = &(*ptrPosition)[length];

          if (*ptrPosition != ptrExtEnd)
          {
            retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
          }
        }
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name      : KeyM_PrvX509ParsingExtension                          **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse a extension in the extensions element of X509   **
**                      certificate                                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd, extType                                       **
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
**                      KeyM_PrvX509GetAuthorityKeyIdentExt,                  **
**                      KeyM_PrvX509GetSubjectKeyIdentExt,                    **
**                      KeyM_PrvX509GetBasicConstraintsExt,                   **
**                      KeyM_PrvX509GetKeyUsageExt,                           **
**                      KeyM_PrvX509GetExtendedKeyUsageExt,                   **
**                      KeyM_PrvX509GetSubjectAltNameExt,                     **
**                      KeyM_PrvX509GetCrlDistributionPointsExt,              **
**                      KeyM_PrvX509GetCrlNumberExt,                          **
**                      KeyM_PrvX509GetCrlIssuingDistributionPointExt         **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509ParsingExtension(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  const uint8 extType)
{
  uint16 retVal;
  retVal = KEYM_E_OK;

  /* @Trace: KeyM_SUD_FUNC_570 */
  switch(extType)
  {
    case KEYM_X509_EXT_AUTHORITY_KEY_IDENTIFIER:
      /* Parse Authority Key Identifier */
      retVal = KeyM_PrvX509GetAuthorityKeyIdentExt(ptrPosition, ptrEnd);
      break;
    case KEYM_X509_EXT_SUBJECT_KEY_IDENTIFIER:
      #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_571 */
        /* Parse Subject Key Identifier */
        retVal = KeyM_PrvX509GetSubjectKeyIdentExt(ptrPosition, ptrEnd);
      #endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
      break;

    case KEYM_X509_EXT_BASIC_CONSTRAINTS:
      #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_572 */
        /* Parse basic constraints */
        retVal = KeyM_PrvX509GetBasicConstraintsExt(ptrPosition, ptrEnd);
      #endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
      break;

    case KEYM_X509_EXT_KEY_USAGE:
      #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_573 */
        /* Parse key usage */
        retVal = KeyM_PrvX509GetKeyUsageExt(ptrPosition, ptrEnd);
      #endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
      break;

    case KEYM_X509_EXT_EXTENDED_KEY_USAGE:
      #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_574 */
        /* Parse extended key usage */
        retVal = KeyM_PrvX509GetExtendedKeyUsageExt(ptrPosition, ptrEnd);
      #endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
      break;
    case KEYM_X509_EXT_SUBJECT_ALT_NAME:
      #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_575 */
        /* Parse subject alternative name */
        retVal = KeyM_PrvX509GetSubjectAltNameExt(ptrPosition, ptrEnd);
      #endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
      break;
    case KEYM_X509_EXT_CRL_DISTRIBUTION_POINTS:
      #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_576 */
        /* Parse CRL Distribution Points */
        retVal = KeyM_PrvX509GetCrlDistributionPointsExt(ptrPosition, ptrEnd);
      #endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
      break;
    case KEYM_X509_EXT_CRL_NUMBER:
      #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_577 */
        /* Parse CRL number */
        retVal = KeyM_PrvX509GetCrlNumberExt(ptrPosition, ptrEnd);
      #endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
      break;
    case KEYM_X509_EXT_ISSUING_DISTRIBUTION_POINT:
      #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
        /* @Trace: KeyM_SUD_FUNC_578 */
        /* Parse CRL Issuing Distribution Point */
        retVal = KeyM_PrvX509GetCrlIssuingDistributionPointExt(ptrPosition, \
          ptrEnd);
      #endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
      break;
    case KEYM_X509_EXT_AUTHORITY_INFO_ACCESS:
      /* Parse Authority Info Access */
      retVal = KeyM_PrvX509GetAuthorityInfoAccessExt(ptrPosition, ptrEnd);
      break;
    case KEYM_X509_EXT_UNKNOWN:
      /* Parse Un-known extension */
      retVal = KeyM_PrvX509GetUnknownExt(ptrPosition, ptrEnd);
      break;
    default:
      /* Do nothing */
      break;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509ConvertEccSignatureValue                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is convert ECC signature value to adapt          **
**                      CSM signature verify function                         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrActualSignValue, actualSignValueLength             **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrOutSign                                            **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1GetTag, KeyM_PrvMemCopy                      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvX509ConvertEccSignatureValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrActualSignValue, \
  const uint16 actualSignValueLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrOutSign, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrOutSignLen)
{
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd;
  uint16 length;
  uint16 r_len = 0u;
  uint16 s_len = 0u;
  uint16 N_len = 0u;
  uint8 tmpSignBuffer[KEYM_ECC_SIGNATURE_VALUE_MAX_LENGTH];
  uint16 idx;

  /* @Trace: KeyM_SUD_FUNC_476 */
  ptrPosition = ptrActualSignValue;
  ptrEnd = &ptrPosition[actualSignValueLength];
  length = 0u;

  /* ==================================
   * Signature  ::=  SEQUENCE  {
   *      INTEGER   r, \
   *      INTEGER   s   }
   * ==================================*/
  (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, \
    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
  
  /* ==================================
   * Algorithm explanation:
   * Find N_len = max (r_len, s_len)
   * Relocate output buffer data.
   * Pass to Csm.
   * ==================================*/
  for (idx = 0; idx < KEYM_ECC_SIGNATURE_VALUE_MAX_LENGTH; idx++)
  { 
    tmpSignBuffer[idx] = 0x00; /* Make zero bit padding */
  }
  
  for (idx = 0; idx < *ptrOutSignLen; idx++)
  { 
    ptrOutSign[idx] = 0x00; /* Make zero bit padding */
  }

  /* Get r element */
  (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_INTEGER);
  r_len = length;
  if (2 * r_len <= KEYM_ECC_SIGNATURE_VALUE_MAX_LENGTH) /* Make sure tmp buffer is enough to store actual data */
  {
    (void)KeyM_PrvMemCopy(ptrPosition, 
                          &tmpSignBuffer[0], 
                          r_len);
    
    /* Get s element */
    ptrPosition = &ptrPosition[r_len];
    (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_INTEGER);
    s_len = length;
    
    if (2 * s_len <= KEYM_ECC_SIGNATURE_VALUE_MAX_LENGTH) /* Make sure tmp buffer is enough to store actual data */
    {
      (void)KeyM_PrvMemCopy(ptrPosition, 
                            &tmpSignBuffer[KEYM_ECC_SIGNATURE_VALUE_MAX_LENGTH - s_len], 
                            s_len);

      N_len = (r_len > s_len)? r_len : s_len; /* N = max(r, s), now sign: (N | N) size */

      if ((N_len * 2U) <= *ptrOutSignLen) /* Make sure output buffer is enough to store proper data */
      {
        /* Set size and relocate output buffer. */
        *ptrOutSignLen = N_len * 2U;
        
        (void)KeyM_PrvMemCopy(&tmpSignBuffer[0], 
                              &ptrOutSign[N_len - r_len], 
                              r_len);  
        (void)KeyM_PrvMemCopy(&tmpSignBuffer[KEYM_ECC_SIGNATURE_VALUE_MAX_LENGTH - s_len], 
                              &ptrOutSign[2U * N_len - s_len], 
                              s_len);
      }
      else
      {
        /* if output buffer is not enough, leave it as zero buffer. */
      }
    }
  }  
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
/*******************************************************************************
** Function Name      : KeyM_PrvX509WriteElement                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write a element in X509 certificate                   **
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
**                      KeyM_Asn1WriteTag, KeyM_Asn1WriteLength               **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509WriteElement(\
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
  uint16 i = 0u;
  retVal = E_NOT_OK;

  /* @Trace: KeyM_SUD_FUNC_478 */
  if (NULL_PTR != ptrCertElement)
  {
    bytesToStoreLen = 0u;
    elementIndex = ptrCertElement->ElementIndex;
    length = ptrCert->PtrCertElement[elementIndex].ElementMaxLength;

    if ((*ptrPosition < ptrStart) || (*ptrPosition < (&(ptrStart[length]))))
    {
      /* @Trace: KeyM_SUD_FUNC_479 */
      retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_480 */
      for (i = 0; i < length; i++)
      {
        (*ptrPosition)--;
      }
      
      /* Write length of publicExponent data */
      retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, length,\
                                   &bytesToStoreLen);
      if (E_OK == retVal)
      {
        length += bytesToStoreLen;
        retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, tag, &bytesToStoreLen);

        if (E_OK == retVal)
        {
          /* @Trace: KeyM_SUD_FUNC_481 */
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
** Function Name      : KeyM_PrvX509WriteExtensions                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write extension element in X509 certificate           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrStart, ptrExtArr, numberOfExt, ptrCert, option     **
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
**                      KeyM_Asn1WriteTag, KeyM_Asn1WriteLength               **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509WriteExtensions(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrExtArr, \
  const uint8 numberOfExt, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength, \
  const uint8 option)
{
  Std_ReturnType retVal;
  uint16 elementIndex;
  uint8 indexCnt;
  uint16 subLength;
  uint16 length;
  uint8 bytesToStoreLen;
  uint8 tag;
  uint16 i = 0u;

  retVal = E_OK;
  bytesToStoreLen = 0u;
  length = 0u;

  /* @Trace: KeyM_SUD_FUNC_482 */
  for (indexCnt = 1u; indexCnt <= numberOfExt; indexCnt++)
  {
    elementIndex = ptrExtArr[numberOfExt - indexCnt].ElementIndex;
    subLength = ptrCert->PtrCertElement[elementIndex].ElementMaxLength;

    if (*ptrPosition < (&(ptrStart[subLength])))
    {
      retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
    }
    else
    {
      for (i = 0; i < subLength; i++)
      {
        (*ptrPosition)--;
      }
      
        
      /* Write length of data */
      retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, subLength,\
        &bytesToStoreLen);

      if (E_OK == retVal)
      {
        subLength += bytesToStoreLen;
        tag = KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE;
        retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, \
          tag, &bytesToStoreLen);

        if (E_OK == retVal)
        {
          subLength += bytesToStoreLen;
          length += subLength;
        }
      }
    }

    if (E_OK != retVal)
    {
      break;
    }
  }
  /* @Trace: KeyM_SUD_FUNC_483 */
  if (E_OK == retVal)
  {
    /* Write length of data */
    retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, length,\
      &bytesToStoreLen);
    /* @Trace: KeyM_SUD_FUNC_484 */
    if (E_OK == retVal)
    {
      length += bytesToStoreLen;
      tag = KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE;
      retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, tag, &bytesToStoreLen);
      /* @Trace: KeyM_SUD_FUNC_485 */
      if (E_OK == retVal)
      {
        length += bytesToStoreLen;
        /* Write length of data */
        retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, length,\
          &bytesToStoreLen);
        /* @Trace: KeyM_SUD_FUNC_486 */
        if (E_OK == retVal)
        {
          length += bytesToStoreLen;
          tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | \
            KEYM_ASN1_PC_CONSTRUCTED | option;
          retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, \
            tag, &bytesToStoreLen);

          if (E_OK == retVal)
          {
            length += bytesToStoreLen;
            *ptrLength += length;
          }
        }
      } /* @if (KEYM_E_OK == retVal) */
    } /* @if (KEYM_E_OK == retVal) */
  } /* @if (KEYM_E_OK == retVal) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509WriteTime                                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write a time element in certificate                   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrStart, ptrCert, ptrParsedCert                      **
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
**                      KeyM_PrvX509WriteElement                              **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509WriteTime(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrTime, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  uint8 tag;
  retVal = E_NOT_OK;

  /* @Trace: KeyM_SUD_FUNC_487 */
  if (NULL_PTR != ptrTime)
  {
    #if (KEYM_CERT_ELEMENT_OBJECT_TYPE_ENABLED == STD_ON)
    tag = ptrCert->PtrCertElement[ptrTime->ElementIndex].ObjectType;
    if ((KEYM_ASN1_UTC_TIME == tag) || (KEYM_ASN1_GENERALIZED_TIME == tag))
    {
      /* Do nothing */
    }
    else
    #endif
    {
      tag = KEYM_ASN1_UTC_TIME;
    }

    retVal = KeyM_PrvX509WriteElement(ptrPosition, ptrStart, ptrCert, ptrTime, \
      ptrLength, tag);
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509WriteIssuerSubject                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write a issuer or subject element in certificate      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrStart, ptrCert, ptrNameArr, numberOfName           **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert                                  **
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
**                      KeyM_Asn1WriteTag, KeyM_Asn1WriteLength               **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509WriteIssuerSubject(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrNameArr, \
  const uint8 numberOfName, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  uint16 elementIndex;
  uint8 indexCnt;
  uint16 subLength;
  uint16 length;
  uint8 bytesToStoreLen;
  uint8 tag;
  uint16 i = 0u;

  retVal = E_OK;
  bytesToStoreLen = 0u;
  length = 0u;
  /* @Trace: KeyM_SUD_FUNC_488 */
  if ((NULL_PTR != ptrNameArr) && (0u < numberOfName))
  {
    /* @Trace: KeyM_SUD_FUNC_489 */
    for (indexCnt = 1u; ((indexCnt <= numberOfName) && (E_OK == retVal)); indexCnt++)
    {
      elementIndex = ptrNameArr[numberOfName - indexCnt].ElementIndex;
      subLength = ptrCert->PtrCertElement[elementIndex].ElementMaxLength;

      if ((*ptrPosition < ptrStart) || \
        (*ptrPosition < (&(ptrStart[subLength]))))
      {
        retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
      }
      else
      {
        for (i = 0; i < subLength; i++)
        {
          (*ptrPosition)--;
        }
        /* Write length of data */
        retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, subLength,\
          &bytesToStoreLen);
        /* @Trace: KeyM_SUD_FUNC_490 */
        if (E_OK == retVal)
        {
          subLength += bytesToStoreLen;
          tag = KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE;
          retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, \
            tag, &bytesToStoreLen);
          /* @Trace: KeyM_SUD_FUNC_491 */
          if (E_OK == retVal)
          {
            subLength += bytesToStoreLen;
            /* Write length of data */
            retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, subLength,\
              &bytesToStoreLen);
            subLength += bytesToStoreLen;
            /* @Trace: KeyM_SUD_FUNC_492 */
            if (E_OK == retVal)
            {
              tag = KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SET;
              retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, \
                tag, &bytesToStoreLen);

              if (E_OK == retVal)
              {
                subLength += bytesToStoreLen;
                length += subLength;
              }
            }
          }
        } /* @if (KEYM_E_OK == retVal) */
      } /* @if (KEYM_E_OK == retVal) */
    } /* @if (KEYM_E_OK == retVal) */

    /* @Trace: KeyM_SUD_FUNC_493 */
    if (E_OK == retVal)
    {
      /* Write length of data */
      retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, length,\
        &bytesToStoreLen);
      /* @Trace: KeyM_SUD_FUNC_494 */
      if (E_OK == retVal)
      {
        length += bytesToStoreLen;
        tag = KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE;
        retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, \
          tag, &bytesToStoreLen);

        if (E_OK == retVal)
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
#endif /* (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF) */
#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name      : KeyM_PrvPartOfX509ParseRsaSsaPssParams                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvX509ParseRsaSsaPssParams,   **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvX509ParseRsaSsaPssParams                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd                                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
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
**                      KeyM_Asn1WriteTag                                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvPartOfX509ParseRsaSsaPssParams(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd)
{
  uint16 retVal;
  uint8 tag;
  uint16 length;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEnd2;

  length = 0u;
  /* Salt length */
  tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 2u;
  /* @Trace: KeyM_SUD_FUNC_543 */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);

  if ((KEYM_E_OK == retVal) || (KEYM_E_ASN1_UNEXPECTED_TAG == retVal))
  {
    if (KEYM_E_OK == retVal)
    {
      /* @Trace: KeyM_SUD_FUNC_545 */
      ptrEnd2 = &((*ptrPosition)[length]);

      retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd2, &length, \
        KEYM_ASN1_INTEGER);
      if (KEYM_E_OK == retVal)
      {
        *ptrPosition = &((*ptrPosition)[length]);
      }
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_544 */
      /* Accept the unexpected tag error */
      retVal = KEYM_E_OK;
    }
    /* @Trace: KeyM_SUD_FUNC_547 */
    if ((*ptrPosition != ptrEnd) && (KEYM_E_OK == retVal))
    {
      /* Trailer field */
      tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 3u;
      retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);
      /* @Trace: KeyM_SUD_FUNC_548 */
      if (KEYM_E_OK == retVal)
      {
        ptrEnd2 = &((*ptrPosition)[length]);

        retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd2, &length, \
          KEYM_ASN1_INTEGER);

        if (KEYM_E_OK == retVal)
        {
          *ptrPosition = &((*ptrPosition)[length]);
        }
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509ParseRsaSsaPssParams                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse the parameter element of RSASSA-PSS algorithm   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrParams                                             **
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
**                      KeyM_Asn1WriteTag, KeyM_Asn1GetAlgorithmIdentNull,    **
**                      KeyM_Asn1GetAlgorithmIdent,                           **
**                      KeyM_PrvPartOfX509ParseRsaSsaPssParams                **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvX509ParseRsaSsaPssParams(\
  P2CONST(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrParams)
{
  uint16 retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEnd1;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEnd2;
  uint16 length;
  uint8 tag;
  KeyM_AsnElementType algId;
  KeyM_AsnElementType algParams;

  retVal = KEYM_E_OK;
  /* @Trace: KeyM_SUD_FUNC_495 */
  /* Make sure params is a SEQUENCE and setup bounds */
  if ((KEYM_ASN1_NULL == ptrParams->Tag) || (0u == ptrParams->Tag) || \
    (0u == ptrParams->Length))
  {
    /* Do nothing */
  }
  else
  {
    length = 0u;
    algId.PtrData = NULL_PTR;
    algId.Length = 0u;
    algId.Tag = 0u;
    algParams.PtrData = NULL_PTR;
    algParams.Length = 0u;
    algParams.Tag = 0u;
    ptrPosition = ptrParams->PtrData;
    ptrEnd1 = &ptrPosition[ptrParams->Length];
    /* HashAlgorithm */
    tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 0u;
    retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd1, &length, tag);

    if ((KEYM_E_OK == retVal) || (KEYM_E_ASN1_UNEXPECTED_TAG == retVal))
    {
      /* @Trace: KeyM_SUD_FUNC_496 */
      if (KEYM_E_OK == retVal)
      {
        ptrEnd2 = &ptrPosition[length];
        retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd2, &length, \
          KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
        /* @Trace: KeyM_SUD_FUNC_497 */
        if (KEYM_E_OK == retVal)
        {
          /* HashAlgorithm ::= AlgorithmIdentifier (without parameters) */
          retVal = KeyM_Asn1GetAlgorithmIdentNull(&ptrPosition, \
            ptrEnd2, &algId);
        }
      }
      else
      {
        /* Accept the unexpected tag error */
        retVal = KEYM_E_OK;
      }
      /* @Trace: KeyM_SUD_FUNC_498 */
      if ((ptrPosition != ptrEnd1) && (KEYM_E_OK == retVal))
      {
        /* MaskGenAlgorithm */
        tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 1u;
        retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd1, &length, tag);
        /* @Trace: KeyM_SUD_FUNC_499 */
        if ((KEYM_E_OK == retVal) || (KEYM_E_ASN1_UNEXPECTED_TAG == retVal))
        {
          if (KEYM_E_OK == retVal)
          {
            ptrEnd2 = &ptrPosition[length];

            retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd2, &length, \
              KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
            /* @Trace: KeyM_SUD_FUNC_500 */
            if (KEYM_E_OK == retVal)
            {
              /* MaskGenAlgorithm ::= AlgorithmIdentifier (with parameters) */
              retVal = KeyM_Asn1GetAlgorithmIdent(&ptrPosition, ptrEnd2, \
                &algId, &algParams);
            }
          }
          else
          {
            /* Accept the unexpected tag error */
            retVal = KEYM_E_OK;
          }
          /* @Trace: KeyM_SUD_FUNC_501 */
          if ((ptrPosition != ptrEnd1) && (KEYM_E_OK == retVal))
          {
            retVal = KeyM_PrvPartOfX509ParseRsaSsaPssParams(&ptrPosition, \
              ptrEnd1);
          }
        }
      }
    }
    /* @Trace: KeyM_SUD_FUNC_502 */
    if ((ptrPosition != ptrEnd1) && (KEYM_E_OK == retVal))
    {
      retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509GetTime                                   **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get time element                                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrEndOfData                                          **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrTag, ptrLength, ptrRawTime, ptrTime                **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1GetLength, KeyM_PrvX509ParseTime             **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvX509GetTime(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrTag, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrRawTime, \
  P2VAR(KeyM_X509TimeType, AUTOMATIC, KEYM_APPL_DATA) ptrTime
)
{
  uint16 retVal;
  uint16 length;
  uint8 yearLength;
  uint8 tag;
  /* Initialize variables */
  retVal = KEYM_E_OK;
  length = 0U;

  /* Get tag value */
  tag = **ptrPosition;

  if (KEYM_ASN1_UTC_TIME == tag)
  {
    /* @Trace: KeyM_SUD_FUNC_462 */
    /* UCT-TIME format: YYMMDDHHMMSSZ, so we need 2 digits for year number */
    yearLength = KEYM_TWO;
  }
  else if (KEYM_ASN1_GENERALIZED_TIME == tag)
  {
    /* @Trace: KeyM_SUD_FUNC_463 */
    /* GENERALIZED-TIME format: YYYYMMDDHHMMSSZ, so we need 4 digits
       for year number */
    yearLength = KEYM_FOUR;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_464 */
	  yearLength = 0u;
    retVal = KEYM_E_ASN1_UNEXPECTED_TAG;
  }
  /* @Trace: KeyM_SUD_FUNC_465 */
  if (KEYM_E_OK == retVal)
  {
    /* Go to start position of the Length in the Type-length-value */
    (*ptrPosition)++;
    /* Get length */
    retVal = KeyM_Asn1GetLength(ptrPosition, ptrEndOfData, &length);
    /* @Trace: KeyM_SUD_FUNC_466 */
    if (KEYM_E_OK == retVal)
    {
      #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
      if ((NULL_PTR != ptrTag) && (NULL_PTR != ptrLength) && \
        (NULL_PTR != ptrRawTime))
      #endif
      {
        /* Get the tag, length and start position of time element */
        *ptrTag = tag;
        *ptrLength = length;
        *ptrRawTime = *ptrPosition;
      }
      /* Parse time value */
      retVal = KeyM_PrvX509ParseTime(ptrPosition, (uint8)length, \
        (uint8)yearLength, ptrTime);
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509ConvertDateToSecond                       **
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
**                      KeyM_PrvConvertDateToSecond                           **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvX509ConvertDateToSecond(\
  P2CONST(KeyM_X509TimeType, AUTOMATIC, KEYM_APPL_DATA) ptrDate, \
  P2VAR(uint64, AUTOMATIC, KEYM_APPL_DATA) ptrSeconds)
{
  KeyM_DateType dateCur;
  /* @Trace: KeyM_SUD_FUNC_467 */
  /* Initialize dateCur with the input date */
  dateCur.Year = ptrDate->Year;
  dateCur.Mon = ptrDate->Mon;
  dateCur.Day = ptrDate->Day;
  *ptrSeconds = 0u;
  /* Convert date to seconds */
  KeyM_PrvConvertDateToSecond(&dateCur, ptrSeconds);
  /* Add the hour, minute and second */
  *ptrSeconds += (uint64)((uint64)((uint64)(ptrDate->Hour) * (uint64)3600u) + \
    (uint64)((uint64)(ptrDate->Min) * (uint64)60u) + \
    (uint64)(ptrDate->Sec));
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509ParseTime                                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse a raw time value                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : length, yearLength                                    **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrTime                                               **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvParseInt, KeyM_PrvX509CheckTimeDataValid      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509ParseTime(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  const uint8 length, \
  const uint8 yearLength, \
  P2VAR(KeyM_X509TimeType, AUTOMATIC, KEYM_APPL_DATA) ptrTime)
{
  uint16 retVal;
  uint16 interNum;

  /* The min length is 13 or 15 depending on year length */
  if (length != (yearLength + KEYM_ELEVEN))
  {
    /* @Trace: KeyM_SUD_FUNC_550 */
    retVal = KEYM_E_INVALID_DATE;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_551 */
    interNum = 0u;
    /* Parse year */
    retVal = KeyM_PrvParseInt(ptrPosition, yearLength, &interNum);

    if (KEYM_E_OK == retVal)
    {
      ptrTime->Year = interNum;
      /* For UTCTime, Where YY is greater than or equal to 50, the year SHALL be
        interpreted as 19YY; and Where YY is less than 50,
        the year SHALL be interpreted as 20YY.*/
      if (2U == yearLength)
      {
         if (50U > ptrTime->Year)
         {
           ptrTime->Year += 100U;
         }

         ptrTime->Year += 1900U;
      }

      /* Parse month */
      retVal = KeyM_PrvParseInt(ptrPosition, 2U, &interNum);
      /* @Trace: KeyM_SUD_FUNC_552 */
      if (KEYM_E_OK == retVal)
      {
        ptrTime->Mon = (uint8)interNum;
        /* Parse day */
        retVal = KeyM_PrvParseInt(ptrPosition, 2U, &interNum);
        if (KEYM_E_OK == retVal)
        {
          ptrTime->Day = (uint8)interNum;
          /* Parse hour */
          retVal = KeyM_PrvParseInt(ptrPosition, 2U, &interNum);
          /* @Trace: KeyM_SUD_FUNC_553 */
          if (KEYM_E_OK == retVal)
          {
            ptrTime->Hour = (uint8)interNum;
            /* Parse minute */
            retVal = KeyM_PrvParseInt(ptrPosition, 2U, &interNum);
            if (KEYM_E_OK == retVal)
            {
              ptrTime->Min = (uint8)interNum;
              /* Parse seconds */
              retVal = KeyM_PrvParseInt(ptrPosition, 2U, &interNum);

              if (KEYM_E_OK == retVal)
              {
                ptrTime->Sec = (uint8)interNum;
                /* @Trace: KeyM_SUD_FUNC_554 */
                /* Parse trailing 'Z' */
                if (90U == **ptrPosition)
                {
                  (*ptrPosition)++;
                  /* At this point, we should have parsed all characters */
                  retVal = KeyM_PrvX509CheckTimeDataValid(ptrTime);
                }
                else
                {
                  retVal = KEYM_E_INVALID_DATE;
                }
              }
            } /* @Parse minute */
          } /* @Parse hour */
        } /* @Parse day */
      } /* @Parse month */
    } /* @Parse year */
  } /* @if (length != (yearLength + KEYM_ELEVEN)) */
  /* @Trace: KeyM_SUD_FUNC_555 */
  if (KEYM_E_OK != retVal)
  {
    retVal = KEYM_E_INVALID_DATE;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509CheckTimeDataValid                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check a time is valid                                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrTime                                               **
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
**                      KeyM_PrvCheckDateValid                                **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509CheckTimeDataValid(\
  P2CONST(KeyM_X509TimeType, AUTOMATIC, KEYM_APPL_CONST) ptrTime)
{
  KeyM_DateType date;
  uint16 retVal;

  /* Check the year, hour, minute and second value
    are not bigger than maximum */
  if ((23U < ptrTime->Hour) || (59U < ptrTime->Min) || (59U < ptrTime->Sec))
  {
    /* @Trace: KeyM_SUD_FUNC_556 */
    retVal = KEYM_E_INVALID_DATE;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_557 */
    date.Year = ptrTime->Year;
    date.Mon = ptrTime->Mon;
    date.Day = ptrTime->Day;
    /* Check date value */
    retVal = KeyM_PrvCheckDateValid(&date, 9999U, 1970U);

    if (KEYM_E_OK != retVal)
    {
      retVal = KEYM_E_INVALID_DATE;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetAttrTypeValue                          **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get attribute and value in a distinguished name(DN)   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrEndOfData                                          **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrCurName, ptrObjectId                               **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetAttrTypeValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCurName, \
  P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrValue)
{
  uint16 retVal;
  uint16 length;

  length = 0U;
  ptrValue->PtrData = NULL_PTR;
  ptrValue->Length = 0u;
  ptrValue->Tag = 0u;
  ptrObjectId->PtrData = NULL_PTR;
  ptrObjectId->Length = 0u;
  ptrObjectId->Tag = 0u;

  /*
   *  AttributeTypeAndValue ::= SEQUENCE {
   *    type     AttributeType,
   *    value    AttributeValue }
   *
   *  AttributeType ::= OBJECT IDENTIFIER
   *
   *  AttributeValue ::= ANY DEFINED BY AttributeType
   */
  /* @Trace: KeyM_SUD_FUNC_535 */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEndOfData, &length, \
                          KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
  if (KEYM_E_OK == retVal)
  {
    if (1 > (ptrEndOfData - *ptrPosition))
    {
      /* @Trace: KeyM_SUD_FUNC_536 */
      retVal = KEYM_E_ASN1_OUT_OF_DATA;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_537 */
      ptrCurName->Element.PtrData = *ptrPosition;
      ptrCurName->Element.Length = length;
      ptrCurName->Element.Tag = KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE;

      ptrObjectId->Tag = **ptrPosition;

      retVal = KeyM_Asn1GetTag(ptrPosition, ptrEndOfData, \
        &length, KEYM_ASN1_OID);

      if (KEYM_E_OK == retVal)
      {
        /* @Trace: KeyM_SUD_FUNC_538 */
        ptrObjectId->PtrData = *ptrPosition;
        ptrObjectId->Length = length;
        *ptrPosition = &(*ptrPosition)[length];

        if (1 > (ptrEndOfData - *ptrPosition))
        {
          /* @Trace: KeyM_SUD_FUNC_539 */
          retVal = KEYM_E_ASN1_OUT_OF_DATA;
        }
        else
        {
          /* Note: we only support UTF8 and PRINTABLE STRING */
          /* @Trace: KeyM_SUD_FUNC_541 */
          ptrValue->Tag = **ptrPosition;
          (*ptrPosition)++;
          retVal = KeyM_Asn1GetLength(ptrPosition, ptrEndOfData, &length);

          if (KEYM_E_OK == retVal)
          {
            /* @Trace: KeyM_SUD_FUNC_542 */
            ptrValue->Length = length;
            ptrValue->PtrData = *ptrPosition;
            *ptrPosition = &(*ptrPosition)[length];
          }
        } /* @if ((ptrEndOfData - *ptrPosition) < 1U) */
      } /* @if (KEYM_E_OK != retVal) */
    } /* @if ((ptrEndOfData - *ptrPosition) < 1U) */
  } /* @if (KEYM_E_OK != retVal) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509NameCmp                                   **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Compare two X.509 Names                               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrName1, ptrName2, name1Num, name2Num                **
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
**                      KeyM_PrvMemCmp                                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509NameCmp(\
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrName1, \
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrName2, \
  const uint8 name1Num, \
  const uint8 name2Num)
{
  /* In order to support Certificate Universal Configuration, it must compare
   * unordered sets with different size. Each set may contain null elements.
   */
  
  Std_ReturnType retVal;
  uint32 i = 0u;
  uint32 set1Counter = 0u;
  uint32 set2Counter = 0u;

  retVal = E_OK;

  /* @Trace: KeyM_SUD_FUNC_503 */
  /* 1. Validate actual size of input sets */
  uint32 realSet1Size = 0;
  uint32 realSet2Size = 0;

  for (i = 0; i < name1Num; i++)
  {
    if (ptrName1[i].Element.Length > 0)
    {
      realSet1Size++;
    }    
  }

  for (i = 0; i < name2Num; i++)
  {
    if (ptrName2[i].Element.Length > 0)
    {
      realSet2Size++;
    }    
  }

  if (realSet1Size == realSet2Size)
  {
    /* Matched checking:
     *      1. Each of item existing in 1st set must exist in 2nd set as well and
     *      2. The number of its duplication in 2 sets must be equal 
     */  
    boolean matched;
    for (set1Counter = 0; set1Counter < name1Num; set1Counter++)
    {
      if (0 != ptrName1[set1Counter].Element.Length)
      {
        matched = FALSE;
        for (set2Counter = 0; set2Counter < name2Num; set2Counter++)
        {
          if ((ptrName1[set1Counter].Element.Length == ptrName2[set2Counter].Element.Length) &&
              (E_OK == KeyM_PrvMemCmp(ptrName1[set1Counter].Element.PtrData, 
                                      ptrName2[set2Counter].Element.PtrData, 
                                      ptrName1[set1Counter].Element.Length)))
          {
            /* 2. Check item co-existence done. */
            if (KeyM_PrvX509CountDuplicatesInSet(ptrName1, name1Num, set1Counter) == 
                KeyM_PrvX509CountDuplicatesInSet(ptrName2, name2Num, set2Counter))
            {
              /* 3. Check same duplication done. */  
              matched = TRUE;
            } else
            {            
              /* dup not matched */
            }
            
            break;
          } else
          {          
            /* find: not this item */
          }
        }
        
        if (FALSE == matched)
        {
          retVal = E_NOT_OK;
          break;
        }
      }
    }
  } else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvPartOfX509ElementGetRsaAlgorithmByIndex       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of                                     **
**                      KeyM_PrvX509ElementGetRsaAlgorithmByIndex, this       **
**                      function is created to reduce code metric of          **
**                      KeyM_PrvX509ElementGetRsaAlgorithmByIndex             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrPosition, ptrEnd, dataIndex, currentIndex          **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrDataLength, ptrElementData                         **
**                                                                            **
** Return parameter   : boolean                                               **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1GetTag, KeyM_Asn1GetAlgorithmIdent           **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvPartOfX509ElementGetRsaAlgorithmByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  const uint32 dataIndex, \
  const uint32 currentIndex, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_CONST) ptrDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData)
{
  Std_ReturnType retVal;
  KeyM_AsnElementType objectId;
  KeyM_AsnElementType params;
  uint8 tag;
  uint16 length;
  boolean found;
  uint32 actualIndex;

  length = 0u;
  found = KEYM_FALSE;
  actualIndex = currentIndex;
  objectId.PtrData = NULL_PTR;
  objectId.Length = 0u;
  objectId.Tag = 0u;

  /* MaskGenAlgorithm */
  tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 1u;
  /* @Trace: KeyM_SUD_FUNC_606 */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);

  if (E_OK == retVal)
  {
    params.PtrData = NULL_PTR;
    params.Length = 0u;
    params.Tag = 0u;
    (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
      KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
    /* MaskGenAlgorithm ::= AlgorithmIdentifier (with parameters) */
    (void)KeyM_Asn1GetAlgorithmIdent(ptrPosition, ptrEnd, &objectId, &params);
    actualIndex++;
    /* @Trace: KeyM_SUD_FUNC_607 */
    if (actualIndex == dataIndex)
    {
      *ptrElementData = objectId.PtrData;
      *ptrDataLength = objectId.Length;
      found = KEYM_TRUE;
    }
    else
    {
      actualIndex++;
      /* @Trace: KeyM_SUD_FUNC_608 */
      if (actualIndex == dataIndex)
      {
        (void)KeyM_Asn1GetTag(&params.PtrData, ptrEnd, &params.Length, \
          KEYM_ASN1_OID);
        *ptrElementData = params.PtrData;
        *ptrDataLength = params.Length;
        found = KEYM_TRUE;
      }
    }
  }

  if ((*ptrPosition != ptrEnd) && (KEYM_FALSE == found))
  {
    /* @Trace: KeyM_SUD_FUNC_609 */
    /* Salt length */
    tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 2u;
    retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);
    if (E_OK == retVal)
    {
      (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, KEYM_ASN1_INTEGER);
      actualIndex++;
      if (actualIndex == dataIndex)
      {
        *ptrElementData = *ptrPosition;
        *ptrDataLength = length;
        found = KEYM_TRUE;
      }
      *ptrPosition = &((*ptrPosition)[length]);
    }
    /* @Trace: KeyM_SUD_FUNC_610 */
    if ((*ptrPosition != ptrEnd) && (KEYM_FALSE == found))
    {
      /* Trailer field */
      tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 3u;
      (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);
      (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, KEYM_ASN1_INTEGER);
      actualIndex++;
      if (actualIndex == dataIndex)
      {
        *ptrElementData = *ptrPosition;
        *ptrDataLength = length;
        found = KEYM_TRUE;
      }
    } /* @if ((ptrPosition != ptrEnd) && (KEYM_FALSE == found)) */
  }

  return found;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGetRsaAlgorithmByIndex             **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get RSA algorithm element data by index               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrAlgData, algDataLength, dataIndex                  **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength,                  **
**                      KeyM_Asn1GetAlgorithmIdentNull,                       **
**                      KeyM_PrvPartOfX509ElementGetRsaAlgorithmByIndex       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetRsaAlgorithmByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAlgData, \
  const uint32 algDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen)
{
  Std_ReturnType retVal = E_NOT_OK;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEnd;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrData;
  uint32 dataLength;
  uint16 length;
  uint8 tag;
  KeyM_AsnElementType objectId;
  boolean found;
  uint32 actualIndex;

  length = 0u;
  ptrData = NULL_PTR;
  dataLength = 0u;
  found = KEYM_FALSE;
  actualIndex = 0u;

  ptrPosition = ptrAlgData;
  ptrEnd = &ptrPosition[algDataLength];
  /* @Trace: KeyM_SUD_FUNC_612 */
  retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_OID);

  if (E_OK == retVal)
  {
    if (actualIndex == dataIndex)
    {
      ptrData = ptrPosition;
      dataLength = length;
      found = KEYM_TRUE;
    }
    else
    {
      ptrPosition = &ptrPosition[length];
      /* @Trace: KeyM_SUD_FUNC_613 */
      if (ptrPosition != ptrEnd)
      {
        if (KEYM_ASN1_NULL == *ptrPosition)
        {
          /* Do nothing */
        }
        else
        {
          ptrPosition++;
          /* @Trace: KeyM_SUD_FUNC_614 */
          if (*ptrPosition != 0u)
          {
            (void)KeyM_Asn1GetLength(&ptrPosition, ptrEnd, &length);
            ptrEnd = &(ptrPosition[length]);

            /* HashAlgorithm */
            tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC |
                  KEYM_ASN1_PC_CONSTRUCTED | 0u;
            /* @Trace: KeyM_SUD_FUNC_615 */
            retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, tag);

            if (E_OK == retVal)
            {
              objectId.PtrData = NULL_PTR;
              objectId.Length = 0u;
              objectId.Tag = 0u;
              (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length,
                                    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
              /* HashAlgorithm ::= AlgorithmIdentifier (without parameters) */
              (void)KeyM_Asn1GetAlgorithmIdentNull(&ptrPosition,
                                                   ptrEnd, &objectId);
              actualIndex++;
              if (actualIndex == dataIndex)
              {
                ptrData = objectId.PtrData;
                dataLength = objectId.Length;
                found = KEYM_TRUE;
              }
            }
            /* @Trace: KeyM_SUD_FUNC_616 */
            if ((ptrPosition != ptrEnd) && (KEYM_FALSE == found))
            {
              found = KeyM_PrvPartOfX509ElementGetRsaAlgorithmByIndex(
                  &ptrPosition, ptrEnd, dataIndex,
                  actualIndex, &dataLength, &ptrData);
            }
          }
        } /* @if (KEYM_ASN1_NULL == *ptrPosition) */
      }   /* @if (ptrPosition != ptrEnd) */
    }     /* @if (actualIndex == dataIndex) */
    /* @Trace: KeyM_SUD_FUNC_617 */
    if (KEYM_FALSE == found)
    {
      retVal = E_NOT_OK;
    }
    else if (dataLength > *ptrElementDataLen)
    {
      retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
    }
    else
    {
      retVal = E_OK;
      *ptrElementData = ptrData;
      *ptrElementDataLen = dataLength;
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGetRsaAlgorithmCount               **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get RSA algorithm element data count                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrAlgData, algDataLength                             **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength,                  **
**                      KeyM_Asn1GetAlgorithmIdentNull,                       **
**                      KeyM_Asn1GetAlgorithmIdent                            **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetRsaAlgorithmCount(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAlgData, \
  const uint32 algDataLength, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount)
{
  Std_ReturnType retVal = E_NOT_OK;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEnd;
  KeyM_AsnElementType objectId;
  KeyM_AsnElementType params;
  uint8 tag;
  uint16 length;
  uint16 count;

  length = 0u;
  count = 0u;

  ptrPosition = ptrAlgData;
  ptrEnd = &ptrPosition[algDataLength];
  /* @Trace: KeyM_SUD_FUNC_618 */
  retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_OID);

  if (E_OK == retVal)
  {
    count++;
    ptrPosition = &ptrPosition[length];

    if (ptrPosition != ptrEnd)
    {
      tag = *ptrPosition;
      /* @Trace: KeyM_SUD_FUNC_619 */
      if (KEYM_ASN1_NULL == tag)
      {
        /* Do nothing */
      }
      else
      {
        objectId.PtrData = NULL_PTR;
        objectId.Length = 0u;
        objectId.Tag = 0u;
        params.PtrData = NULL_PTR;
        params.Length = 0u;
        params.Tag = 0u;

        ptrPosition++;
        (void)KeyM_Asn1GetLength(&ptrPosition, ptrEnd, &length);
        ptrEnd = &ptrPosition[length];

        /* HashAlgorithm */
        tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 0u;
        retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, tag);
        /* @Trace: KeyM_SUD_FUNC_620 */
        if (E_OK == retVal)
        {
          (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length,
                                KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
          /* HashAlgorithm ::= AlgorithmIdentifier (without parameters) */
          (void)KeyM_Asn1GetAlgorithmIdentNull(&ptrPosition, ptrEnd, &objectId);
          count++;
        }

        if (ptrPosition != ptrEnd)
        {
          /* MaskGenAlgorithm */
          tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 1u;
          retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, tag);
          /* @Trace: KeyM_SUD_FUNC_621 */
          if (E_OK == retVal)
          {
            (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length,
                                  KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
            /* MaskGenAlgorithm ::= AlgorithmIdentifier (with parameters) */
            (void)KeyM_Asn1GetAlgorithmIdent(&ptrPosition, ptrEnd,
                                             &objectId, &params);
            count += 2u;
          }

          if (ptrPosition != ptrEnd)
          {
            /* Salt length */
            tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC |
                  KEYM_ASN1_PC_CONSTRUCTED | 2u;
            retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, tag);
            /* @Trace: KeyM_SUD_FUNC_622 */
            if (E_OK == retVal)
            {
              (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd,
                                    &length, KEYM_ASN1_INTEGER);
              count++;
              ptrPosition = &ptrPosition[length];
            }

            if (ptrPosition != ptrEnd)
            {
              retVal = E_OK;
              /* Trailer field */
              count++;
            } /* @if (ptrPosition != ptrEnd) */
          }   /* @if (ptrPosition != ptrEnd) */
        }     /* @if (ptrPosition != ptrEnd) */
      }       /* @if (KEYM_ASN1_NULL == tag) */
    }         /* @if (ptrPosition != ptrEnd) */

    *ptrCount = count;
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGetEccAlgorithmByIndex             **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get ECC signature algorithm or public key algorithm   **
**                      element data by index                                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrAlgData, algDataLength, dataIndex                  **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetEccAlgorithmByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAlgData, \
  const uint32 algDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen)
{
  Std_ReturnType retVal = E_NOT_OK;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEnd;
  uint8 tag;
  uint16 length;
  uint32 dataLength;
  boolean finished;
  uint32 actualIndex;

  length = 0u;
  finished = KEYM_FALSE;
  actualIndex = 0u;

  ptrPosition = ptrAlgData;
  ptrEnd = &ptrPosition[algDataLength];
  /* @Trace: KeyM_SUD_FUNC_624 */
  retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_OID);

  if (E_OK == retVal)
  {
    if (actualIndex == dataIndex)
    {
      finished = KEYM_TRUE;
    }
    else
    {
      ptrPosition = &ptrPosition[length];
      /* @Trace: KeyM_SUD_FUNC_625 */
      if (ptrPosition != ptrEnd)
      {
        tag = *ptrPosition;
        /* @Trace: KeyM_SUD_FUNC_626 */
        /* Make sure params is a OID  */
        if (KEYM_ASN1_OID == tag)
        {
          ptrPosition++;
          (void)KeyM_Asn1GetLength(&ptrPosition, ptrEnd, &length);
          actualIndex++;
          /* @Trace: KeyM_SUD_FUNC_627 */
          if (actualIndex == dataIndex)
          {
            finished = KEYM_TRUE;
          }
        }
      }
    }

    dataLength = length;
    /* @Trace: KeyM_SUD_FUNC_628 */
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
      *ptrElementData = &ptrAlgData[ptrPosition - ptrAlgData];
      *ptrElementDataLen = dataLength;
    }
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGetEccAlgorithmCount               **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get ECC signature algorithm or public key algorithm   **
**                      element data count                                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrAlgData, algDataLength                             **
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
**                      KeyM_Asn1GetTag                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetEccAlgorithmCount(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAlgData, \
  const uint32 algDataLength, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount)
{
  Std_ReturnType retVal = E_NOT_OK;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEnd;
  uint8 tag;
  uint16 length;
  uint16 count;

  length = 0u;
  count = 0u;
  ptrPosition = ptrAlgData;
  ptrEnd = &ptrPosition[algDataLength];
  /* @Trace: KeyM_SUD_FUNC_629 */
  retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_OID);

  if (E_OK == retVal)
  {
    count++;
    ptrPosition = &ptrPosition[length];
    if (ptrPosition != ptrEnd)
    {
      tag = *ptrPosition;
      /* @Trace: KeyM_SUD_FUNC_630 */
      /* Make sure params is a OID  */
      if (KEYM_ASN1_OID == tag)
      {
        count++;
      }
    }

    *ptrCount = count;
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGetAlgorithmByIndex                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get signature algorithm, public key algorithm element **
**                      data by index                                         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrAlgData, algDataLength, algorithmType, dataIndex   **
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
**                      KeyM_PrvX509ElementGetRsaAlgorithmByIndex,            **
**                      KeyM_PrvX509ElementGetEccAlgorithmByIndex             **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetAlgorithmByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAlgData, \
  const uint32 algDataLength, \
  const uint8 algorithmType, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen)
{
  Std_ReturnType retVal;
  retVal = E_OK;

  /* @Trace: KeyM_SUD_FUNC_631 */
  if ((KEYM_PK_RSA == algorithmType) || \
    ((KEYM_PK_RSASSA_PSS <= algorithmType) && \
    (KEYM_PK_RSA_SHA512 >= algorithmType)))
  {
    retVal = KeyM_PrvX509ElementGetRsaAlgorithmByIndex(ptrAlgData,\
      algDataLength, dataIndex, ptrElementData, ptrElementDataLen);
  }
  else if ((KEYM_PK_EC == algorithmType) || \
    ((KEYM_PK_ECDSA_SHA1 <= algorithmType) && \
    (KEYM_PK_ECDSA_SHA512 >= algorithmType)))
  {
    retVal = KeyM_PrvX509ElementGetEccAlgorithmByIndex(ptrAlgData, \
      algDataLength, dataIndex, ptrElementData, ptrElementDataLen);
  }
  else
  {
    /* Shall not enter here */
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGetAlgorithmCount                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get element data count of signature algorithm,        **
**                      public key algorithm                                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrAlgData, algDataLength, algorithmType              **
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
**                      KeyM_PrvX509ElementGetRsaAlgorithmCount,              **
**                      KeyM_PrvX509ElementGetEccAlgorithmCount               **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetAlgorithmCount(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAlgData, \
  const uint32 algDataLength, \
  const uint8 algorithmType, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount)
{
  Std_ReturnType retVal;
  retVal = E_OK;

  /* @Trace: KeyM_SUD_FUNC_633 */
  if ((KEYM_PK_RSA == algorithmType) || \
    ((KEYM_PK_RSASSA_PSS <= algorithmType) && \
    (KEYM_PK_RSA_SHA512 >= algorithmType)))
  {
    retVal = KeyM_PrvX509ElementGetRsaAlgorithmCount(ptrAlgData,\
      algDataLength, ptrCount);
  }
  else if ((KEYM_PK_EC == algorithmType) || \
    ((KEYM_PK_ECDSA_SHA1 <= algorithmType) && \
    (KEYM_PK_ECDSA_SHA512 >= algorithmType)))
  {
    retVal = KeyM_PrvX509ElementGetEccAlgorithmCount(ptrAlgData,\
      algDataLength, ptrCount);
  }
  else
  {
    /* Shall not enter here */
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGetIssuerSubjectByIndex            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get element data of Issuer, Subject name by index     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrNameArr, nameLength, dataIndex                     **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetIssuerSubjectByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrIssuerSubjectData, \
  const uint32 issuerDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrPosition;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEnd;
  uint16 length;
  uint32 dataLength;

  ptrPosition = ptrIssuerSubjectData;
  ptrEnd = &ptrPosition[issuerDataLength];
  length = 0u;
  retVal = E_OK;

  if (0u == dataIndex)
  {
    /* @Trace: KeyM_SUD_FUNC_636 */
    (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_OID);
    ptrPosition = &ptrPosition[length];
    /* Skip the one byte of tag */
    ptrPosition++;
    (void)KeyM_Asn1GetLength(&ptrPosition, ptrEnd, &length);

    dataLength = length;

    if (dataLength > *ptrElementDataLen)
    {
      retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
    }
    else
    {
      *ptrElementData = &ptrIssuerSubjectData[ptrPosition - ptrIssuerSubjectData];
      *ptrElementDataLen = dataLength;
    }
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_635 */
    retVal = E_NOT_OK;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGetRevokedCertByIndex              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get revokedCertificates element data by index         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrRevokedCertData, revokDataLength, dataIndex,       **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetRevokedCertByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrRevokedCertData, \
  const uint32 revokDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrPosition;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEnd;
  uint16 length;
  uint32 dataLength;
  boolean found;

  ptrPosition = ptrRevokedCertData;
  ptrEnd = &ptrPosition[revokDataLength];
  length = 0u;
  retVal = E_OK;
  found = KEYM_FALSE;
  /* @Trace: KeyM_SUD_FUNC_637 */
  (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_INTEGER);

  if (0u == dataIndex)
  {
    found = KEYM_TRUE;
  }
  else
  {
    ptrPosition = &ptrPosition[length];
    /* Skip the one byte of tag */
    ptrPosition++;
    (void)KeyM_Asn1GetLength(&ptrPosition, ptrEnd, &length);

    if (1u == dataIndex)
    {
      found = KEYM_TRUE;
    }
  }

  dataLength = length;
  /* @Trace: KeyM_SUD_FUNC_638 */
  if (KEYM_FALSE == found)
  {
    retVal = E_NOT_OK;
  }
  else if (dataLength > *ptrElementDataLen)
  {
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
  }
  else
  {
    *ptrElementData = ptrPosition;
    *ptrElementDataLen = dataLength;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name      : KeyM_PrvPartOfX509ElementGetExtensionByIndex          **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is part of KeyM_PrvX509ElementGetExtensionByIndex**
**                      .This function is created to reduce code metric of    **
**                      KeyM_PrvX509ElementGetExtensionByIndex                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd, extType, dataIndex, currentIndex              **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static boolean KeyM_PrvPartOfX509ElementGetExtensionByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  const uint8 extType, \
  const uint32 dataIndex, \
  const uint32 currentIndex, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  boolean found;
  uint32 actualIndex;
  uint16 length;
  sint32 temp_length = 0u;

  found = KEYM_FALSE;
  actualIndex = currentIndex;
  length = 0u;
  /* @Trace: KeyM_SUD_FUNC_640 */
  if (KEYM_X509_EXT_AUTHORITY_KEY_IDENTIFIER == extType)
  {
    (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
      KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

    while (*ptrPosition < ptrEnd)
    {
      /* Skip the 1-byte tag */
      (*ptrPosition)++;
      (void)KeyM_Asn1GetLength(ptrPosition, ptrEnd, &length);

      if (dataIndex == actualIndex)
      {
        found = KEYM_TRUE;
        break;
      }
      else
      {
        *ptrPosition = &(*ptrPosition)[length];
        actualIndex++;
      }
    }
  }
  else if (KEYM_X509_EXT_AUTHORITY_INFO_ACCESS == extType)
  {
    /* @Trace: KeyM_SUD_FUNC_641 */
    (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
      KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

    while (*ptrPosition < ptrEnd)
    {
      /* Extract a SEQUENCE */
      (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
        KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

      if (dataIndex == actualIndex)
      {
        found = KEYM_TRUE;
        break;
      }
      else
      {
        *ptrPosition = &(*ptrPosition)[length];
        actualIndex++;
      }
    }
  }
  #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
  else if (KEYM_X509_EXT_BASIC_CONSTRAINTS == extType)
  {
    /* @Trace: KeyM_SUD_FUNC_643 */
    /*
     * BasicConstraints ::= SEQUENCE {
     *      cA                      BOOLEAN DEFAULT FALSE,
     *      pathLenConstraint       INTEGER (0..MAX) OPTIONAL }
     */
    (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
      KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
    /* cA */
    if ((KEYM_ASN1_BOOLEAN == **ptrPosition) && (ptrEnd != *ptrPosition))
    {
      (*ptrPosition)++;
      length = **ptrPosition;
      (*ptrPosition)++;
      if (dataIndex == actualIndex)
      {
        found = KEYM_TRUE;
      }
      else
      {
        /* Go to the position of the next element of extension */
        *ptrPosition = &(*ptrPosition)[length];
      }
      actualIndex++;
    }
    /* @Trace: KeyM_SUD_FUNC_644 */
    if ((KEYM_FALSE == found) && (ptrEnd != *ptrPosition))
    {
      /* The pathLenConstraint is present */
      (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
        KEYM_ASN1_INTEGER);

      if (dataIndex == actualIndex)
      {
        found = KEYM_TRUE;
      }
    }
  }
  else if ((KEYM_X509_EXT_EXTENDED_KEY_USAGE == extType) || \
    (KEYM_X509_EXT_SUBJECT_ALT_NAME == extType))
  {
    /* @Trace: KeyM_SUD_FUNC_645 */
    (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
      KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

    while (*ptrPosition < ptrEnd)
    {
      /* Skip the one byte if tag */
      (*ptrPosition)++;
      (void)KeyM_Asn1GetLength(ptrPosition, ptrEnd, &length);

      if (dataIndex == actualIndex)
      {
        found = KEYM_TRUE;
        break;
      }
      else
      {
        *ptrPosition = &(*ptrPosition)[length];
        actualIndex++;
      }
    }
  }
  else if (KEYM_X509_EXT_CRL_DISTRIBUTION_POINTS == extType)
  {
    /* @Trace: KeyM_SUD_FUNC_646 */
    (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
      KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

    while (*ptrPosition < ptrEnd)
    {
      (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
        KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
      /* Skip the one byte if tag */
      (*ptrPosition)++;
      (void)KeyM_Asn1GetLength(ptrPosition, ptrEnd, &length);
      /* Skip the one byte if tag */
      (*ptrPosition)++;
      (void)KeyM_Asn1GetLength(ptrPosition, ptrEnd, &length);
      /* Skip the one byte if tag */
      (*ptrPosition)++;
      (void)KeyM_Asn1GetLength(ptrPosition, ptrEnd, &length);
      if (dataIndex == actualIndex)
      {
        found = KEYM_TRUE;
        break;
      }
      else
      {
        *ptrPosition = &(*ptrPosition)[length];
        actualIndex++;
      }
    }
  }
  else if ((KEYM_X509_EXT_KEY_USAGE == extType) || \
    (KEYM_X509_EXT_SUBJECT_KEY_IDENTIFIER == extType))
  {
    /* @Trace: KeyM_SUD_FUNC_647 */
    /* Skip the one byte if tag */
    (*ptrPosition)++;
    (void)KeyM_Asn1GetLength(ptrPosition, ptrEnd, &length);

    if (dataIndex == actualIndex)
    {
      found = KEYM_TRUE;
    }
  }
  #endif /* #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
  #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
  else if (KEYM_X509_EXT_ISSUING_DISTRIBUTION_POINT == extType)
  {
    /* @Trace: KeyM_SUD_FUNC_648 */
    (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, \
      KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
    /* Skip the one byte if tag */
    (*ptrPosition)++;
    (void)KeyM_Asn1GetLength(ptrPosition, ptrEnd, &length);
    /* Skip the one byte if tag */
    (*ptrPosition)++;
    (void)KeyM_Asn1GetLength(ptrPosition, ptrEnd, &length);
    /* Skip the one byte if tag */
    (*ptrPosition)++;
    (void)KeyM_Asn1GetLength(ptrPosition, ptrEnd, &length);
    if (dataIndex == actualIndex)
    {
      found = KEYM_TRUE;
    }
  }
  else if (KEYM_X509_EXT_CRL_NUMBER == extType)
  {
    /* @Trace: KeyM_SUD_FUNC_649 */
    (void)KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, KEYM_ASN1_INTEGER);

    if (dataIndex == actualIndex)
    {
      found = KEYM_TRUE;
    }
  }
  #endif /* #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
  else if (KEYM_X509_EXT_UNKNOWN == extType)
  {
    /* @Trace: KeyM_SUD_FUNC_1647 */
    /* Gathers this OCTET STRING */
    temp_length = ptrEnd - *ptrPosition;
    if (temp_length >= 0 && temp_length <= 65535)
    {
      length = (uint16)temp_length;
    }

    if (dataIndex == actualIndex)
    {
      found = KEYM_TRUE;
    }
  }
  else
  {
    /* Shout not enter here */
  } /* @if (KEYM_X509_EXT_BASIC_CONSTRAINTS == extType) */

  *ptrLength = length;
  return found;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGetExtensionByIndex                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get element data of extensions                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrExtensionData, extDataLength, dataIndex,certFormat **
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
**                      KeyM_Asn1GetTag, KeyM_PrvX509GetCertExtensionType,    **
**                      KeyM_PrvX509GetCrlExtensionType,                      **
**                      KeyM_PrvPartOfX509ElementGetExtensionByIndex          **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetExtensionByIndex(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtensionData, \
  const uint32 extDataLength, \
  const uint32 dataIndex, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrElementDataLen, \
  const KeyM_CertFormatType certFormat)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEnd;
  KeyM_AsnElementType extnObjectId;
  uint16 length;
  uint32 dataLength;
  uint32 actualIndex;
  boolean found;
  uint8 extType;

  length = 0u;
  extType = 0u;

  found = KEYM_FALSE;
  actualIndex = 0u;

  ptrPosition = ptrExtensionData;
  ptrEnd = &ptrPosition[extDataLength];
  /* @Trace: KeyM_SUD_FUNC_650 */
  /* Get extnID */
  (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_OID);

  extnObjectId.PtrData = ptrPosition;
  extnObjectId.Length = length;

  /* Go to the position of the critical element of extension */
  ptrPosition = &ptrPosition[length];
  /* Get option critical */
  retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_BOOLEAN);

  if (E_OK == retVal)
  {
    if (dataIndex == actualIndex)
    {
      found = KEYM_TRUE;
    }
    else
    {
      /* Go to the position of the extnValue element of extension */
      ptrPosition = &ptrPosition[length];
    }
    actualIndex++;
  }
  /* @Trace: KeyM_SUD_FUNC_651 */
  if (KEYM_FALSE == found)
  {
    /* Get extnValue */
    (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, \
      &length, KEYM_ASN1_OCTET_STRING);

    /* Detect supported extensions */
    #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
    if (KEYM_CERT_FORMAT_X509 == certFormat)
    {
      (void)KeyM_PrvX509GetCertExtensionType(extnObjectId.PtrData, \
        (uint8)extnObjectId.Length, &extType);
    }
    else
    #endif
    {
      #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
        (void)KeyM_PrvX509GetCrlExtensionType(extnObjectId.PtrData, \
          (uint8)extnObjectId.Length, &extType);
      #endif
    }

    found = KeyM_PrvPartOfX509ElementGetExtensionByIndex(&ptrPosition, \
      ptrEnd, extType, dataIndex, actualIndex, &length);
  } /* @if (dataIndex == actualIndex) */

  dataLength = length;
  /* @Trace: KeyM_SUD_FUNC_652 */
  if (KEYM_FALSE == found)
  {
    retVal = E_NOT_OK;
  }
  else if (dataLength > *ptrElementDataLen)
  {
    retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
  }
  else
  {
    retVal = E_OK;
    *ptrElementData = &ptrExtensionData[ptrPosition - ptrExtensionData];
    *ptrElementDataLen = dataLength;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGetExtensionCount                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get element data count of extensions                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrExtensionData, extDataLength, certFormat           **
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
**                      KeyM_Asn1GetTag, KeyM_PrvX509GetCertExtensionType,    **
**                      KeyM_PrvX509GetCrlExtensionType, KeyM_Asn1GetLength   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509ElementGetExtensionCount(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtensionData, \
  const uint32 extDataLength, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount, \
  const KeyM_CertFormatType certFormat)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEnd;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtnObjectId;
  uint8 extnObjectIdLength;
  uint16 length;
  uint16 count;
  uint8 extType;

  length = 0u;
  count = 0u;
  extType = 0u;

  ptrPosition = ptrExtensionData;
  ptrEnd = &ptrPosition[extDataLength];
  /* @Trace: KeyM_SUD_FUNC_653 */
  /* Get extension ID */
  (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_OID);

  ptrExtnObjectId = ptrPosition;
  extnObjectIdLength = (uint8)length;

  /* Go to the position of the critical element of extension */
  ptrPosition = &ptrPosition[length];
  /* Get optional critical */
  retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_BOOLEAN);

  if (E_OK == retVal)
  {
    count++;
    /* Go to the position of the extnValue element of extension */
    ptrPosition = &ptrPosition[length];
  }
  else
  {
    retVal = E_OK;
  }

  /* Extension value should be octet string type */
  (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_OCTET_STRING);

  /* Detect supported extensions */
  #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
  /* @Trace: KeyM_SUD_FUNC_654 */
  if (KEYM_CERT_FORMAT_X509 == certFormat)
  {
    (void)KeyM_PrvX509GetCertExtensionType(ptrExtnObjectId, \
      (uint8)extnObjectIdLength, &extType);
  }
  else
  #endif
  {
    #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
      (void)KeyM_PrvX509GetCrlExtensionType(ptrExtnObjectId, \
        (uint8)extnObjectIdLength, &extType);
    #endif
  }

  if (KEYM_X509_EXT_AUTHORITY_KEY_IDENTIFIER == extType)
  {
    /* @Trace: KeyM_SUD_FUNC_656 */
    (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, \
      KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

    while (ptrPosition < ptrEnd)
    {
      ptrPosition++;
      (void)KeyM_Asn1GetLength(&ptrPosition, ptrEnd, &length);
      count++;
      ptrPosition = &ptrPosition[length];
    }
  }
  else if (KEYM_X509_EXT_AUTHORITY_INFO_ACCESS == extType)
  {
    /* @Trace: KeyM_SUD_FUNC_655 */
    (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, \
      KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

    while (ptrPosition < ptrEnd)
    {
      (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, \
        KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

      count++;
      ptrPosition = &ptrPosition[length];
    }
  }
  #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
  else if (KEYM_X509_EXT_BASIC_CONSTRAINTS == extType)
  {
    /* @Trace: KeyM_SUD_FUNC_657 */
    /*
     * BasicConstraints ::= SEQUENCE {
     *      cA                      BOOLEAN DEFAULT FALSE,
     *      pathLenConstraint       INTEGER (0..MAX) OPTIONAL }
     */
    (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, \
      KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
    /* cA */
    retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_BOOLEAN);

    if (E_OK == retVal)
    {
      count++;
      ptrPosition = &ptrPosition[length];
    }

    if (ptrEnd != ptrPosition)
    {
      /* The pathLenConstraint is present */
      count++;
    }
  }
  else if ((KEYM_X509_EXT_EXTENDED_KEY_USAGE == extType) || \
    (KEYM_X509_EXT_SUBJECT_ALT_NAME == extType) ||\
    (KEYM_X509_EXT_CRL_DISTRIBUTION_POINTS == extType))
  {
    /* @Trace: KeyM_SUD_FUNC_658 */
    (void)KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, \
      KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

    while (ptrPosition < ptrEnd)
    {
      ptrPosition++;
      (void)KeyM_Asn1GetLength(&ptrPosition, ptrEnd, &length);
      count++;
      ptrPosition = &ptrPosition[length];
    }
  }
  else if ((KEYM_X509_EXT_KEY_USAGE == extType) || \
    (KEYM_X509_EXT_SUBJECT_KEY_IDENTIFIER == extType))
  {
    /* @Trace: KeyM_SUD_FUNC_659 */
    /* For the key usage extension always have one element data */
    count++;
  }
  #endif /* #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
  #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
  else if ((KEYM_X509_EXT_ISSUING_DISTRIBUTION_POINT == extType) || \
    (KEYM_X509_EXT_CRL_NUMBER == extType))
  {
    /* @Trace: KeyM_SUD_FUNC_660 */
    count++;
  }
  #endif /* #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
  else if (KEYM_X509_EXT_UNKNOWN == extType)
  {
    /* @Trace: KeyM_SUD_FUNC_1650 */
    /* For Unknown extension, the total number of sub-element is always considered to be 1.*/
    count = 1u;
  }
  else
  {
    /* Shall not enter here */
  } /* @if (KEYM_X509_EXT_BASIC_CONSTRAINTS == extType) */

  *ptrCount = count;

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGetCount                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get X509 certificate element data count               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCert, ptrCertElement                               **
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
**                      KeyM_PrvX509ElementGetAlgorithmCount,                 **
**                      KeyM_PrvX509ElementGetExtensionCount                  **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509ElementGetCount(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrCount)
{
  Std_ReturnType retVal;
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert;
  #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl;
  #endif /* #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  uint32 elementDataLen;
  uint8 algorithmType;
  KeyM_CertificateElementTypeOfStructure elementOfStruct;

  retVal = E_NOT_OK;
  /* @Trace: KeyM_SUD_FUNC_504 */
  if (NULL_PTR != ptrCertElement->PtrElement)
  {
    ptrElementData = ptrCertElement->PtrElement->Element.PtrData;
    elementDataLen = ptrCertElement->PtrElement->Element.Length;
    /* @Trace: KeyM_SUD_FUNC_505 */
    if (NULL_PTR != ptrElementData)
    {
      elementOfStruct = ptrCertElement->ElementOfStruct;

      if ((KEYM_CERT_VERSION_NUMBER == elementOfStruct) || \
        (KEYM_CERT_SERIAL_NUMBER == elementOfStruct) || \
        (KEYM_CERT_ISSUER_NAME == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_NAME == elementOfStruct) || \
        (KEYM_CERT_ISSUER_UNIQUE_IDENTIFIER == elementOfStruct) || \
        (KEYM_CERT_SIGNATURE == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_UNIQUE_IDENTIFIER == elementOfStruct) || \
        (KEYM_CERT_VALIDITY_PERIOD_NOT_AFTER == elementOfStruct) || \
        (KEYM_CERT_VALIDITY_PERIOD_NOT_BEFORE == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_SUBJECT_PUBLIC_KEY == \
        elementOfStruct))
      {
        /* @Trace: KeyM_SUD_FUNC_506 */
        retVal = E_OK;
        *ptrCount = 1u;
      }
      #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
      else if (KEYM_CERT_REVOKED_CERTIFICATES == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_507 */
        retVal = E_OK;
        *ptrCount = 2u;
      }
      #endif /* #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
      else if ((KEYM_CERT_SIGNATURE_ALGORITHM_ID == elementOfStruct) || \
        (KEYM_CERT_SIGNATURE_ALGORITHM == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_PUBLIC_KEY_ALGORITHM == \
        elementOfStruct))
      {
        /* @Trace: KeyM_SUD_FUNC_508 */
        if (KEYM_CERT_FORMAT_X509 == ptrCert->CertFormat)
        {
          ptrParsedCert = (KeyM_X509CertificateType*)ptrCert->PtrParsedCert;
          if (KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_PUBLIC_KEY_ALGORITHM == \
            elementOfStruct)
          {
            algorithmType = ptrParsedCert->PublicKeyType;
          }
          else
          {
            algorithmType = ptrParsedCert->SignAlgType;
          }
        }
        else
        {
          #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
            ptrParsedCrl = (KeyM_X509CrlType*)ptrCert->PtrParsedCert;
            algorithmType = ptrParsedCrl->SignAlgType;
          #else
            algorithmType = 0u;
          #endif /* #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
        }

        retVal = KeyM_PrvX509ElementGetAlgorithmCount(ptrElementData, \
          elementDataLen, algorithmType, ptrCount);
      }
      else if (KEYM_CERT_EXTENSION == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_509 */
        retVal = KeyM_PrvX509ElementGetExtensionCount(ptrElementData,\
          elementDataLen, ptrCount, ptrCert->CertFormat);
      }
      else
      {
        /* Shall not enter here */
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGetByIndex                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get X509 certificate element data by index            **
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
**                      KeyM_PrvX509ElementGetIssuerSubjectByIndex,           **
**                      KeyM_PrvX509ElementGetAlgorithmByIndex,               **
**                      KeyM_PrvX509ElementGetRevokedCertByIndex,             **
**                      KeyM_PrvX509ElementGetExtensionByIndex                **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509ElementGetByIndex(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  VAR(uint32, AUTOMATIC) indexCnt, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen)
{
  Std_ReturnType retVal;
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert;
  #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl;
  #endif /* #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  uint32 elementDataLen;
  uint8 algorithmType;
  KeyM_CertificateElementTypeOfStructure elementOfStruct;

  retVal = E_NOT_OK;
  /* @Trace: KeyM_SUD_FUNC_510 */
  if (NULL_PTR != ptrCertElement->PtrElement)
  {
    ptrElementData = ptrCertElement->PtrElement->Element.PtrData;
    elementDataLen = ptrCertElement->PtrElement->Element.Length;
    /* @Trace: KeyM_SUD_FUNC_511 */
    if (NULL_PTR != ptrElementData)
    {
      elementOfStruct = ptrCertElement->ElementOfStruct;

      if ((KEYM_CERT_VERSION_NUMBER == elementOfStruct) || \
        (KEYM_CERT_SERIAL_NUMBER == elementOfStruct) || \
        (KEYM_CERT_ISSUER_UNIQUE_IDENTIFIER == elementOfStruct) || \
        (KEYM_CERT_SIGNATURE == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_UNIQUE_IDENTIFIER == elementOfStruct) || \
        (KEYM_CERT_VALIDITY_PERIOD_NOT_AFTER == elementOfStruct) || \
        (KEYM_CERT_VALIDITY_PERIOD_NOT_BEFORE == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_SUBJECT_PUBLIC_KEY == \
        elementOfStruct))
      {
        if (0u != indexCnt)
        {
          /* @Trace: KeyM_SUD_FUNC_512 */
          retVal = E_NOT_OK;
        }
        else
        {
          if (elementDataLen > *ptrCertElementDataLen)
          {
            /* @Trace: KeyM_SUD_FUNC_513 */
            retVal = KEYM_E_KEY_CERT_SIZE_MISMATCH;
          }
          else
          {
            /* @Trace: KeyM_SUD_FUNC_514 */
            retVal = E_OK;
            *ptrCertElementData = ptrElementData;
            *ptrCertElementDataLen = elementDataLen;
          }
        }
      }
      else if ((KEYM_CERT_ISSUER_NAME == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_NAME == elementOfStruct))
      {
        /* @Trace: KeyM_SUD_FUNC_515 */
        retVal = KeyM_PrvX509ElementGetIssuerSubjectByIndex(ptrElementData, \
          elementDataLen, indexCnt, ptrCertElementData,\
          ptrCertElementDataLen);
      }
      else if ((KEYM_CERT_SIGNATURE_ALGORITHM_ID == elementOfStruct) || \
        (KEYM_CERT_SIGNATURE_ALGORITHM == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_PUBLIC_KEY_ALGORITHM == \
        elementOfStruct))
      {
        /* @Trace: KeyM_SUD_FUNC_516 */
        if (KEYM_CERT_FORMAT_X509 == ptrCert->CertFormat)
        {
          ptrParsedCert = (KeyM_X509CertificateType*)ptrCert->PtrParsedCert;
          if (KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_PUBLIC_KEY_ALGORITHM == \
            elementOfStruct)
          {
            algorithmType = ptrParsedCert->PublicKeyType;
          }
          else
          {
            algorithmType = ptrParsedCert->SignAlgType;
          }
        }
        else
        {
          #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
            ptrParsedCrl = (KeyM_X509CrlType*)ptrCert->PtrParsedCert;
            algorithmType = ptrParsedCrl->SignAlgType;
          #else
            algorithmType = 0u;
          #endif /* #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
        }

        retVal = KeyM_PrvX509ElementGetAlgorithmByIndex(ptrElementData, \
          elementDataLen, algorithmType, indexCnt, \
          ptrCertElementData, ptrCertElementDataLen);
      }
      #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
      else if (KEYM_CERT_REVOKED_CERTIFICATES == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_517 */
        retVal =  KeyM_PrvX509ElementGetRevokedCertByIndex(ptrElementData,\
          elementDataLen, indexCnt, ptrCertElementData,\
          ptrCertElementDataLen);
      }
      #endif /* #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
      else if (KEYM_CERT_EXTENSION == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_518 */
        retVal =  KeyM_PrvX509ElementGetExtensionByIndex(ptrElementData,\
          elementDataLen, indexCnt, ptrCertElementData,\
          ptrCertElementDataLen, ptrCert->CertFormat);
      }
      else
      {
        /* Shall not enter here */
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGet                                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get X509 certificate element data which has one       **
**                      element is assigned to the respective OID             **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
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
**                      KeyM_PrvX509ElementGetIssuerSubjectByIndex,           **
**                      KeyM_PrvX509ElementGetExtensionCount,                 **
**                      KeyM_PrvX509ElementGetExtensionByIndex                **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509ElementGet(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen, \
  const KeyM_CertFormatType certFormat)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  uint32 elementDataLen;
  KeyM_CertificateElementTypeOfStructure elementOfStruct;
  uint16 count;

  retVal = E_NOT_OK;
  count = 0u;
  /* @Trace: KeyM_SUD_FUNC_519 */
  if (NULL_PTR != ptrCertElement->PtrElement)
  {
    ptrElementData = ptrCertElement->PtrElement->Element.PtrData;
    elementDataLen = ptrCertElement->PtrElement->Element.Length;
    /* @Trace: KeyM_SUD_FUNC_520 */
    if (NULL_PTR != ptrElementData)
    {
      elementOfStruct = ptrCertElement->ElementOfStruct;

     if ((KEYM_CERT_ISSUER_NAME == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_NAME == elementOfStruct))
      {
        /* @Trace: KeyM_SUD_FUNC_522 */
        retVal = KeyM_PrvX509ElementGetIssuerSubjectByIndex(ptrElementData, \
          elementDataLen, 0u,\
          ptrCertElementData,\
          ptrCertElementDataLen);
      }
      else if (KEYM_CERT_EXTENSION == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_523 */
        (void)KeyM_PrvX509ElementGetExtensionCount(ptrElementData,\
          elementDataLen,\
          &count, certFormat);

        if (1u != count)
        {
          retVal = E_NOT_OK;
        }
        else
        {
          retVal = KeyM_PrvX509ElementGetExtensionByIndex(ptrElementData, \
            elementDataLen, 0u,\
            ptrCertElementData,\
            ptrCertElementDataLen,\
            certFormat);
        }
      }
      else
      {
        /* Because cert element data is ready, just returning element data 
         * pointer and its length is enough.
         */
        *ptrCertElementData=ptrElementData;
        *ptrCertElementDataLen = elementDataLen;

        retVal = E_OK;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509ElementGetFirst                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get the first element data of a X509 certificate      **
**                      element which may has multiple element data are       **
**                      assigned to one OID                                   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCertElement, certFormat                            **
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
**                      KeyM_PrvX509ElementGetIssuerSubjectByIndex,           **
**                      KeyM_PrvX509ElementGetExtensionCount,                 **
**                      KeyM_PrvX509ElementGetExtensionByIndex                **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509ElementGetFirst(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(KeyM_CertElementIteratorType, AUTOMATIC, KEYM_APPL_DATA) \
  ptrCertElementIterator, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen, \
  const KeyM_CertFormatType certFormat)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  uint32 elementDataLen;
  KeyM_CertificateElementTypeOfStructure elementOfStruct;
  uint16 count;

  retVal = E_NOT_OK;
  count = 0u;

  /* @Trace: KeyM_SUD_FUNC_525 */
  if (NULL_PTR != ptrCertElement->PtrElement)
  {
    ptrElementData = ptrCertElement->PtrElement->Element.PtrData;
    elementDataLen = ptrCertElement->PtrElement->Element.Length;
    /* @Trace: KeyM_SUD_FUNC_526 */
    if (NULL_PTR != ptrElementData)
    {
      elementOfStruct = ptrCertElement->ElementOfStruct;

      if ((KEYM_CERT_VERSION_NUMBER == elementOfStruct) || \
        (KEYM_CERT_SERIAL_NUMBER == elementOfStruct) || \
        (KEYM_CERT_ISSUER_UNIQUE_IDENTIFIER == elementOfStruct) || \
        (KEYM_CERT_SIGNATURE == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_UNIQUE_IDENTIFIER == elementOfStruct) || \
        (KEYM_CERT_VALIDITY_PERIOD_NOT_AFTER == elementOfStruct) || \
        (KEYM_CERT_VALIDITY_PERIOD_NOT_BEFORE == elementOfStruct) || \
        (KEYM_CERT_SIGNATURE_ALGORITHM_ID == elementOfStruct) || \
        (KEYM_CERT_SIGNATURE_ALGORITHM == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_PUBLIC_KEY_ALGORITHM == \
          elementOfStruct) || \
        (KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_SUBJECT_PUBLIC_KEY == \
          elementOfStruct) || \
        (KEYM_CERT_REVOKED_CERTIFICATES == elementOfStruct) || \
        (NULL_PTR == ptrCertElement->PtrElementObjectId))
      {
        /* @Trace: KeyM_SUD_FUNC_527 */
        retVal = E_NOT_OK;
      }
      else if ((KEYM_CERT_ISSUER_NAME == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_NAME == elementOfStruct))
      {
        /* @Trace: KeyM_SUD_FUNC_528 */
        count = 1u;
        retVal = KeyM_PrvX509ElementGetIssuerSubjectByIndex(ptrElementData, \
          elementDataLen, 0u,\
          ptrCertElementData,\
          ptrCertElementDataLen);


      }
      else if (KEYM_CERT_EXTENSION == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_529 */
        (void)KeyM_PrvX509ElementGetExtensionCount(ptrElementData,\
          elementDataLen,\
          &count, certFormat);

        retVal = KeyM_PrvX509ElementGetExtensionByIndex(ptrElementData, \
          elementDataLen, 0u,\
          ptrCertElementData,\
          ptrCertElementDataLen,\
          certFormat);

      }
      else
      {
        /* Shall not enter here */
      }

      if (E_OK == retVal)
      {
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
** Function Name      : KeyM_PrvX509ElementGetNext                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get the next element data of a X509 certificate       **
**                      element which may has multiple element data are       **
**                      assigned to one OID                                   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCertElement, certFormat                            **
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
**                      KeyM_PrvX509ElementGetIssuerSubjectByIndex,           **
**                      KeyM_PrvX509ElementGetExtensionByIndex                **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509ElementGetNext(\
  P2CONST(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrCertElement, \
  P2VAR(KeyM_CertElementIteratorType, AUTOMATIC, KEYM_APPL_DATA) \
    ptrCertElementIterator, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrCertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) ptrCertElementDataLen, \
  const KeyM_CertFormatType certFormat)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrElementData;
  uint32 elementDataLen;
  KeyM_CertificateElementTypeOfStructure elementOfStruct;
  uint16 indexCnt;

  retVal = E_NOT_OK;
  /* @Trace: KeyM_SUD_FUNC_530 */
  if (NULL_PTR != ptrCertElement->PtrElement)
  {
    ptrElementData = ptrCertElement->PtrElement->Element.PtrData;
    elementDataLen = ptrCertElement->PtrElement->Element.Length;
    /* @Trace: KeyM_SUD_FUNC_531 */
    if (NULL_PTR != ptrElementData)
    {
      indexCnt = ptrCertElementIterator->currentIndex + 1u;
      elementOfStruct = ptrCertElement->ElementOfStruct;

      if ((KEYM_CERT_VERSION_NUMBER == elementOfStruct) || \
        (KEYM_CERT_SERIAL_NUMBER == elementOfStruct) || \
        (KEYM_CERT_ISSUER_UNIQUE_IDENTIFIER == elementOfStruct) || \
        (KEYM_CERT_SIGNATURE == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_UNIQUE_IDENTIFIER == elementOfStruct) || \
        (KEYM_CERT_VALIDITY_PERIOD_NOT_AFTER == elementOfStruct) || \
        (KEYM_CERT_VALIDITY_PERIOD_NOT_BEFORE == elementOfStruct) || \
        (KEYM_CERT_SIGNATURE_ALGORITHM_ID == elementOfStruct) || \
        (KEYM_CERT_SIGNATURE_ALGORITHM == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_PUBLIC_KEY_ALGORITHM == \
          elementOfStruct) || \
        (KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_SUBJECT_PUBLIC_KEY == \
          elementOfStruct) || \
        (KEYM_CERT_REVOKED_CERTIFICATES == elementOfStruct) || \
        (NULL_PTR == ptrCertElement->PtrElementObjectId))
      {
        /* @Trace: KeyM_SUD_FUNC_532 */
        retVal = E_NOT_OK;
      }
      else if ((KEYM_CERT_ISSUER_NAME == elementOfStruct) || \
        (KEYM_CERT_SUBJECT_NAME == elementOfStruct))
      {
        /* @Trace: KeyM_SUD_FUNC_533 */
        retVal = KeyM_PrvX509ElementGetIssuerSubjectByIndex(ptrElementData, \
          elementDataLen, indexCnt,\
          ptrCertElementData,\
          ptrCertElementDataLen);
      }
      else if (KEYM_CERT_EXTENSION == elementOfStruct)
      {
        /* @Trace: KeyM_SUD_FUNC_534 */
        retVal = KeyM_PrvX509ElementGetExtensionByIndex(ptrElementData, \
          elementDataLen, indexCnt,\
          ptrCertElementData,\
          ptrCertElementDataLen,\
          certFormat);
      }
      else
      {
        /* Shall not enter here */
      }

      if (E_OK == retVal)
      {
        ptrCertElementIterator->currentIndex = indexCnt;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509CountDuplicatesInSet                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Compare unordered set of subject/issuer names         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrSet, size, index                                   **
**                                                                            **
** InOut Parameters   :                                                       **
**                                                                            **
** Output Parameters  :                                                       **
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
static uint32 KeyM_PrvX509CountDuplicatesInSet(
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrSet, \
  VAR(uint32, AUTOMATIC) size, \
  VAR(uint32, AUTOMATIC) index)
{ 
  uint32 count = 0;
  uint32 j = 0;

  for (j = 0; j < size; j++)
  {
    if ((ptrSet[j].Element.Length == ptrSet[index].Element.Length) &&
        (E_OK == KeyM_PrvMemCmp(ptrSet[j].Element.PtrData, 
                                ptrSet[index].Element.PtrData, 
                                ptrSet[index].Element.Length)))
    {
      count++;
    }        
  } 
  
  return count;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name      : KeyM_PrvX509GetDERPacketData                          **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get information in DER format of certificate          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCertData, Typestruct,   CertLength                 **
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
**                      Function(s) invoked :    KeyM_Asn1GetTag              **
**                                 KeyM_PrvMemCopy                            **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509GetDERPacketData(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCertData, \
  CONST(uint16, AUTOMATIC)  CertLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrDataLen, \
  CONST(uint8, AUTOMATIC) Typestruct)
{
  Std_ReturnType retVal;
  uint16 length;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd;
  uint8 *temp_position;
  uint8 stop_reading = 0; 
  ptrPosition = ptrCertData;
  length = CertLength;
  ptrEnd = &ptrPosition[length];
  
    retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, \
    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

    if (((&(ptrPosition[length])) != ptrEnd) && (E_OK != retVal))
    {
      retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_993 */
		  /*TBS position*/
      retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, \
        KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
      if( retVal == E_OK)
      {   
        /*bypass Version*/
        retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, \
        		  (KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 0U));

      }
      if( retVal == E_OK)
      {

        /* Update position to the next element of DER certificate  - serial*/
        ptrPosition = &(ptrPosition)[length];
        /* bypass Serial */
        retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, KEYM_ASN1_INTEGER);
      }
      if (retVal == E_OK )
      {
        /* Update position to the next element of DER certificate  - signature algorithm*/
        ptrPosition = &(ptrPosition)[length];
        /*bypass signature algorithm*/
        retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length,
                                 KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
      }
      if (retVal == E_OK)
      {
        /* @Trace: KeyM_SUD_FUNC_994 */
        /* Update position to the next element of DER certificate  -issuer */
        ptrPosition = &(ptrPosition)[length];
        temp_position = ptrPosition;
        /*bypass issuer - get issuer length*/
        retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length,
                                 KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
        if (KEYM_CERT_ISSUER_NAME == Typestruct)
        {
        *ptrDataLen = length + length / 128 + 2;
        /* if lenth >255, need 2 byte for L value in TLV format*/
        (void)KeyM_PrvMemCopy(&temp_position[0], ptrData,
                              *ptrDataLen);
        stop_reading = 1;
        }
      }
      if (retVal == E_OK && 0 == stop_reading)
      { 
        /* Update position to the next element of DER certificate  -time valid */
        ptrPosition = &(ptrPosition)[length];
        /*Issuer point*/
        /*bypass time*/
        retVal |= KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length,
                                  KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
      }
      if (retVal == E_OK && 0 == stop_reading)
      {
        /* @Trace: KeyM_SUD_FUNC_995 */
        /* Update position to the next element of DER certificate  -subject */
        ptrPosition = &(ptrPosition)[length];
        temp_position = ptrPosition;
        /*bypass subject- get subject length*/
        retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length,
                                 KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
        if (KEYM_CERT_SUBJECT_NAME == Typestruct)
        {
        *ptrDataLen = length + length / 128 + 2;
        /* if lenth >255, need 2 byte for L value in TLV format*/
        (void)KeyM_PrvMemCopy(&temp_position[0], ptrData,
                              *ptrDataLen);
        stop_reading = 1;
        }
      }
      if (retVal == E_OK && 0 == stop_reading)
      {
        /* Update position to the next element of DER certificate  -public key information */
        ptrPosition = &(ptrPosition)[length];
        /*bypass public key information*/
        retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length,
                                 KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
      }
      if (retVal == E_OK && 0 == stop_reading)
      {
        /* @Trace: KeyM_SUD_FUNC_996 */
        /* Update position to the next element of DER certificate  -extension */
        ptrPosition = &(ptrPosition)[length];
        temp_position = ptrPosition;
        /*bypass extension - get extension lenth*/
        retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length,
                                 KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 0x03U);
        if (KEYM_CERT_EXTENSION == Typestruct)
        {
        *ptrDataLen = length + length / 128 + 2;
        /* if lenth >255, need 2 byte for L value in TLV format*/
        (void)KeyM_PrvMemCopy(&temp_position[0], ptrData,
                              *ptrDataLen);
        stop_reading = 1;
        }
      }
      if (retVal == E_OK && 0 == stop_reading)
      {
        /* Update position to the next element of DER certificate  -extension */
        ptrPosition = &(ptrPosition)[length];
        /*bypass extension*/
        retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length,
                                 KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
      }
      if (retVal == E_OK && 0 == stop_reading)
      {
        /* Update position to the next element of DER certificate  -signature ID */
        ptrPosition = &(ptrPosition)[length];
        /*bypass signature ID */
        retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length,
                                 KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
      }
      if (retVal == E_OK && 0 == stop_reading)
      {
        /* Update position to the next element of DER certificate  -signature  */
        ptrPosition = &(ptrPosition)[length];
        /*bypass signature  */
        retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length,
                                 KEYM_ASN1_BIT_STRING);
      }
    }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || (KEYM_CERT_X509_CRL_ENABLED == STD_ON)) */
#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:2.2 */
/* polyspace-end MISRA-C3:12.1 */
/* polyspace-end MISRA-C3:10.4 */
/* polyspace-end MISRA-C3:10.3 */
/* polyspace-end MISRA-C3:11.5 CERT-C:EXP36-C */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
