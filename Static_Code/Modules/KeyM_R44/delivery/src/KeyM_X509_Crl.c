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
** 1.0.1.0   27-Mar-2021   TamTV6       Fix defect #18231, Add Trace SUD      **
** 1.0.2     08-Nov-2021   TamTV6       Implement #20971                      **
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
** 1.0.9.0   21-Feb-2024   JS Kang      #CP44-3635                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM X509 CRL header file */
#include "KeyM_X509_Crl.h"
/* KeyM X509 CRT header file */
#include "KeyM_X509_Crt.h"
/* KeyM CVC header file */
#include "KeyM_Cvc.h"
/* KeyM internal function prototype */
#include "KeyM_IntFunc.h"
/* KeyM OID header file */
#include "KeyM_OID.h"
/* KeyM Ram header file  */
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
#if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCrlRevokedCertificates(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvPartOfX509CrlParseDer(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrTbsEnd, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCrlEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCheckX509ParantName(\
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrParentCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCheckCvcParantName(\
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrParentCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509WriteRevokedCertificates(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CrlEntryType, AUTOMATIC, KEYM_APPL_DATA) ptrEntryArr, \
  const uint8 numberOfEntry, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvPartOfX509CrlGenerate(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF) */
#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name      : KeyM_PrvX509CrlParseDer                               **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse one X.509 CRL in DER format from a buffer       **
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
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1GetTag, KeyM_PrvX509GetVersion,              **
**                      KeyM_PrvX509GetSignAlgorithm,                         **
**                      KeyM_PrvX509GetIssuerSubject, KeyM_PrvX509GetValidTime**
**                      KeyM_PrvPartOfX509CrlParseDer                         **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvX509CrlParseDer(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  const uint16 dataLength)
{
  uint16 retVal;
  uint16 length;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCrlEnd;
  P2VAR(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl;

  /* @Trace: KeyM_SUD_FUNC_764 */
  ptrPosition = ptrData;
  length = dataLength;
  ptrEnd = &ptrPosition[length];

  /*
   * CertificateList  ::=  SEQUENCE  {
   *      tbsCertList          TBSCertList,
   *      signatureAlgorithm   AlgorithmIdentifier,
   *      signatureValue       BIT STRING  }
   */
  /* Get tag */
  retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, \
    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

  if (KEYM_E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_765 */
    if ((&(ptrPosition[length])) != ptrEnd)
    {
      retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
    }
    else
    {
      ptrParsedCrl = (KeyM_X509CrlType*)ptrCert->PtrParsedCert;
      ptrCrlEnd = &ptrPosition[length];
      ptrParsedCrl->TBSCertList.PtrData = ptrPosition;

      /*
       * TBSCertList  ::=  SEQUENCE  {
       */
      /* Get tag */
      retVal = KeyM_Asn1GetTag(&ptrPosition, ptrCrlEnd, &length, \
        KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

      if (KEYM_E_OK == retVal)
      {
        ptrEnd = &ptrPosition[length];
        ptrParsedCrl->TBSCertList.Length = \
          (uint16)((sint32)(ptrEnd - ptrParsedCrl->TBSCertList.PtrData));
        /*
         * Version  ::=  INTEGER  OPTIONAL {  v1(0), v2(1)  }
         *               -- if present, MUST be v2
         *
         * signature AlgorithmIdentifier
         */
        retVal = KeyM_PrvX509GetVersion(&ptrPosition, ptrEnd, ptrCert,\
          ptrParsedCrl->PtrRawVersion, KEYM_ASN1_INTEGER);
        /* @Trace: KeyM_SUD_FUNC_766 */
        if (KEYM_E_OK == retVal)
        {
          /* Get signature Algorithm */
          retVal = KeyM_PrvX509GetSignAlgorithm(\
            &ptrPosition, ptrEnd, ptrCert, \
            &ptrParsedCrl->SignAlgType, \
            ptrParsedCrl->PtrRawSignature);
          /* @Trace: KeyM_SUD_FUNC_767 */
          /*
           * issuer Name
           * thisUpdate Time
           * nextUpdate Time OPTIONAL
           */
          if (KEYM_E_OK == retVal)
          {
            /* Get Issuer name */
            retVal = KeyM_PrvX509GetIssuerSubject(&ptrPosition, ptrEnd,\
              ptrCert, ptrParsedCrl->PtrIssuer, ptrParsedCrl->IssuerNum);
            /* @Trace: KeyM_SUD_FUNC_768 */
            if (KEYM_E_OK == retVal)
            {
              /* Get thisUpdate time */
              retVal = KeyM_PrvX509GetValidTime(&ptrPosition, ptrEnd, ptrCert,\
                ptrParsedCrl->PtrRawThisUpdate, &ptrParsedCrl->ThisUpdate);
              /* @Trace: KeyM_SUD_FUNC_769 */
              if (KEYM_E_OK == retVal)
              {
                /* Get nextUpdate time */
                retVal = KeyM_PrvX509GetValidTime(&ptrPosition, ptrEnd, \
                  ptrCert, ptrParsedCrl->PtrRawNextUpdate, \
                  &ptrParsedCrl->NextUpdate);
                /* @Trace: KeyM_SUD_FUNC_770 */
                if (KEYM_E_OK == retVal)
                {
                  retVal = KeyM_PrvPartOfX509CrlParseDer(&ptrPosition, ptrEnd, \
                    ptrCrlEnd, ptrCert, ptrParsedCrl);
                }
              } /* @if (KEYM_E_OK == retVal) */
            } /* @if (KEYM_E_OK == retVal) */
          } /* @if (KEYM_E_OK == retVal) */
        } /* @if (KEYM_E_OK == retVal) */
      } /* @if (KEYM_E_OK != retVal) */
    } /* @if (length != (ptrEnd - ptrPosition)) */
  } /* @if (KEYM_E_OK != retVal) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPartOfX509CrlParseDer                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvX509CrlParseDer, this       **
**                      function is created to reduce code metric of          **
**                      KeyM_PrvX509CrlParseDer                               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrTbsEnd, ptrCrlEnd                                  **
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
**                      KeyM_PrvX509GetCrlRevokedCertificates,                **
**                      KeyM_PrvX509GetExtensions, KeyM_PrvMemCmp,            **
**                      KeyM_PrvX509GetSignAlgorithm,                         **
**                      KeyM_PrvX509GetSignatureValue                         **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvPartOfX509CrlParseDer(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrTbsEnd, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCrlEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl)
{
  uint16 retVal;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEndOfPart;

  /* @Trace: KeyM_SUD_FUNC_796 */
  ptrEndOfPart = ptrTbsEnd;
  /*
   * revokedCertificates    SEQUENCE OF SEQUENCE   {
   *      userCertificate        CertificateSerialNumber,
   *      revocationDate         Time,
   *      crlEntryExtensions     Extensions OPTIONAL
   *                                   -- if present, MUST be v2
   *                        } OPTIONAL
   */
  retVal = KeyM_PrvX509GetCrlRevokedCertificates(ptrPosition, \
    ptrEndOfPart, ptrCert, ptrParsedCrl);
  /*
   * crlExtensions          EXPLICIT Extensions OPTIONAL
   *                              -- if present, MUST be v2
   */
  if (KEYM_E_OK == retVal)
  {
    retVal = KeyM_PrvX509GetExtensions(ptrPosition, ptrEndOfPart, \
      ptrCert, ptrParsedCrl->PtrExtensions,\
      ptrParsedCrl->ExtensionNum, 0u);
    /* @Trace: KeyM_SUD_FUNC_797 */
    if (KEYM_E_OK == retVal)
    {
      /* Set end position is the end of certificate */
      ptrEndOfPart = ptrCrlEnd;
      /*
       *  signatureAlgorithm   AlgorithmIdentifier,
       *  signatureValue       BIT STRING
       */
      /* Get signature algorithm */
      retVal = KeyM_PrvX509GetSignAlgorithm(\
        ptrPosition, ptrEndOfPart, ptrCert, \
        &ptrParsedCrl->SignAlgType,
        ptrParsedCrl->PtrSignatureAlgorithm);
      /* @Trace: KeyM_SUD_FUNC_798 */
      if (KEYM_E_OK == retVal)
      {
        /* Check Signature Algorithm ID in the TBS is the same
          Signature Algorithm ID at the end of certificate */
        if (ptrParsedCrl->PtrRawSignature->Element.Length != \
          ptrParsedCrl->PtrSignatureAlgorithm->Element.Length)
        {
           retVal = KEYM_E_SIG_MISMATCH;
        }
        else
        {
          retVal = KeyM_PrvMemCmp(\
            ptrParsedCrl->PtrRawSignature->Element.PtrData, \
            ptrParsedCrl->PtrSignatureAlgorithm->Element.PtrData, \
            ptrParsedCrl->PtrRawSignature->Element.Length);

          if (KEYM_E_OK != retVal)
          {
            /* @Trace: KeyM_SUD_FUNC_799 */
            retVal = KEYM_E_SIG_MISMATCH;
          }
          /* @Trace: KeyM_SUD_FUNC_800 */
          if (KEYM_E_OK == retVal)
          {
            retVal = KeyM_PrvX509GetSignatureValue(ptrPosition, \
              ptrEndOfPart, ptrCert, ptrParsedCrl->SignAlgType,\
              ptrParsedCrl->PtrSignatureValue);
            if (KEYM_E_OK == retVal)
            {
              /* End of Certificate, the current position must be the end
                of Certificate */
              if (ptrEndOfPart != *ptrPosition)
              {
                retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
              }
            }
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
** Function Name      : KeyM_PrvX509GetCrlRevokedCertificates                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get RevokedCertificates element in a CRL              **
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
**                      KeyM_Asn1GetTag, KeyM_PrvX509GetTime,                 **
**                      KeyM_PrvX509ConvertDateToSecond,                      **
**                      KeyM_PrvCheckCertificateElement                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCrlRevokedCertificates(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl)
{
  P2VAR(KeyM_X509CrlEntryType, AUTOMATIC, KEYM_APPL_DATA) ptrCurrentEntry;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEntryEnd;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEntryListEnd;
  KeyM_X509TimeType revocationDate;
  uint16 retVal;
  uint16 length;
  uint16 elementIndex;
  uint8 tag;
  uint8 entryIndex;
  boolean finished;

  length = 0U;
  finished = KEYM_FALSE;
  entryIndex = 0U;
  ptrEntryEnd = NULL_PTR;
  revocationDate.Year = 0u;
  revocationDate.Mon = 0u;
  revocationDate.Day = 0u;
  revocationDate.Hour = 0u;
  revocationDate.Min = 0u;
  revocationDate.Sec = 0u;

  tag = KEYM_ASN1_SEQUENCE | KEYM_ASN1_PC_CONSTRUCTED;
  /* @Trace: KeyM_SUD_FUNC_801 */
  /* Get tag */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);

  if (KEYM_E_OK == retVal)
  {
    if (NULL_PTR != ptrParsedCrl->PtrEntryList)
    {
      /* @Trace: KeyM_SUD_FUNC_803 */
      /* Update end position of RawRevokedCertificates element */
      ptrEntryListEnd = &(*ptrPosition)[length];

      while ((finished == KEYM_FALSE) && (KEYM_E_OK == retVal))
      {
        ptrCurrentEntry = &(ptrParsedCrl->PtrEntryList[entryIndex]);

        /* Get tag */
        retVal = KeyM_Asn1GetTag(ptrPosition, ptrEntryListEnd, &length, tag);

        if (KEYM_E_OK == retVal)
        {
          ptrCurrentEntry->RawCrlEntry.Element.Tag = tag;
          ptrCurrentEntry->RawCrlEntry.Element.PtrData = *ptrPosition;
          ptrCurrentEntry->RawCrlEntry.Element.Length = length;
          ptrEntryEnd = &(*ptrPosition)[length];
          /* Get certificate serial in the entry */
          retVal = KeyM_Asn1GetTag(ptrPosition, ptrEntryEnd, \
            &length, KEYM_ASN1_INTEGER);

          if (KEYM_E_OK == retVal)
          {
            ptrCurrentEntry->Serial.Length = length;
            ptrCurrentEntry->Serial.PtrData = *ptrPosition;
            *ptrPosition = &(*ptrPosition)[length];
            /* Get revocation date of the certificate in the entry */
            retVal = KeyM_PrvX509GetTime(ptrPosition, ptrEntryEnd, \
              NULL_PTR, NULL_PTR, NULL_PTR,\
              &revocationDate);
            /* @Trace: KeyM_SUD_FUNC_804 */
            if (KEYM_E_OK == retVal)
            {
              if (*ptrPosition != ptrEntryEnd)
              {
                /* The current implement does not support crl entry extension,
                  so in this case, we skip to the entry end position */
                *ptrPosition = ptrEntryEnd;
              }

              /* Convert revocation time to seconds */
              KeyM_PrvX509ConvertDateToSecond(&revocationDate, \
                &(ptrCurrentEntry->RevocationDate));

              elementIndex = ptrCurrentEntry->RawCrlEntry.ElementIndex;
              /* Check the certificate element of CRL revokedCertificates */
              retVal = KeyM_PrvCheckCertificateElement(ptrCert, elementIndex,\
                tag, NULL_PTR, 0u);
              /* @Trace: KeyM_SUD_FUNC_805 */
              if (KEYM_E_OK == retVal)
              {
                ptrCert->PtrCertElement[elementIndex].PtrElement = \
                  &ptrCurrentEntry->RawCrlEntry;
                entryIndex++;
                if (entryIndex == ptrParsedCrl->EntryNum)
                {
                  finished = KEYM_TRUE;
                  if (*ptrPosition != ptrEntryListEnd)
                  {
                    retVal = KEYM_E_INVALID_REVOKED_LIST;
                  }
                }
              }
            } /* @if (KEYM_E_OK == retVal) */
          } /* @if (KEYM_E_OK == retVal) */
        } /* @if (KEYM_E_OK == retVal) */
      } /* @while ((finished == KEYM_FALSE) && (KEYM_E_OK == retVal)) */
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_802 */
      retVal = KEYM_E_INVALID_REVOKED_LIST;
    } /* @if (NULL_PTR != ptrParsedCrl->PtrEntryList) */
  } /* @if (KEYM_E_OK != retVal) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvCheckX509ParantName                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check the Subject of X509 certificate is the same     **
**                      issuer name of CRL                                    **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrParsedCrl, ptrParentCert                           **
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
**                      KeyM_PrvX509NameCmp                                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCheckX509ParantName(\
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrParentCert)
{
  uint16 retVal;
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert;

  /* @Trace: KeyM_SUD_FUNC_806 */
  retVal = E_NOT_OK;
  ptrParsedCert = (KeyM_X509CertificateType*)(ptrParentCert->PtrParsedCert);

  if (ptrParsedCrl->IssuerNum == ptrParsedCert->SubjectNum)
  {
    /* Support universal cert configuration */
    retVal = KeyM_PrvX509NameCmp(ptrParsedCrl->PtrIssuer, \
                                 ptrParsedCert->PtrSubject, 
                                 ptrParsedCrl->IssuerNum, 
                                 ptrParsedCert->IssuerNum);
  }

  return retVal;

}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */

#if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvCheckCvcParantName                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check the holder reference of CVC is the same issuer  **
**                      name of CRL                                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrParsedCrl, ptrParentCert                           **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength, KeyM_PrvMemCmp   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvCheckCvcParantName(\
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrParentCert)
{
  uint16 retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData;
  P2CONST(KeyM_CvcCertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert;
  uint16 length;

  /* @Trace: KeyM_SUD_FUNC_807 */
  retVal = E_NOT_OK;
  length = 0u;
  ptrParsedCert = (KeyM_CvcCertificateType*)(ptrParentCert->PtrParsedCert);

  /* The CRL issuer must have only one DN name(common name)
    corresponding to concatenated elements: Country Code, Holder Mnemonic,
    Sequence Number of CVC Certificate Holder Reference */
  ptrPosition = ptrParsedCrl->PtrIssuer[0u].Element.PtrData;
  ptrEndOfData = &ptrPosition[ptrParsedCrl->PtrIssuer[0u].Element.Length];
  /* Skip OID of DN name */
  (void)KeyM_Asn1GetTag(&ptrPosition, ptrEndOfData, &length, KEYM_ASN1_OID);
  /* Go to value of DN name */
  ptrPosition = &ptrPosition[length];
  ptrPosition++;
  (void)KeyM_Asn1GetLength(&ptrPosition, ptrEndOfData, &length);

  if (length == ptrParsedCert->PtrRawHolderRefer->Element.Length)
  {
    /* Compare value of CRL DN name and CVC Holder Reference */
    retVal = KeyM_PrvMemCmp(ptrPosition, \
      ptrParsedCert->PtrRawHolderRefer->Element.PtrData, length);
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */

/*******************************************************************************
** Function Name      : KeyM_PrvPartOfX509CrlVerify                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvX509CrlVerify,              **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvX509CrlVerify                                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCrl                                                **
**                                                                            **
** InOut Parameters   : ptrParsedCrl                                          **
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
**                      KeyM_PrvGetCurrentTime or UserGetCurrentTimeFunc,     **
**                      KeyM_PrvElementRuleVerify                             **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_CertificateStatusType KeyM_PrvPartOfX509CrlVerify(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCrl, \
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl)
{
  uint64 currentTime;
  uint16 retVal;
  KeyM_CertificateStatusType crlStatus;
  /* @Trace: KeyM_SUD_FUNC_991 */
  currentTime = 0U;
  /* Get the current time */
  #if (KEYM_USE_STBM == STD_ON)
  retVal = KeyM_PrvGetCurrentTime(ptrCrl->CertTimebaseId, &currentTime);
  #else
  retVal = KEYM_USER_GET_CURRENT_TIME(&currentTime);
  #endif

  if (KEYM_E_OK == retVal)
  {
    /* Check for validity of CRL */
    if (((ptrParsedCrl->NextUpdate < currentTime) && \
      (ptrParsedCrl->NextUpdate != 0u)) || \
      (ptrParsedCrl->ThisUpdate > currentTime))
    {
      /* @Trace: KeyM_SUD_FUNC_809 */
      crlStatus = KEYM_E_CERTIFICATE_VALIDITY_PERIOD_FAIL;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_810 */
      #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON)
      /* Verify element according to element verification rule */
      retVal = KeyM_PrvElementRuleVerify(ptrCrl);

      if (KEYM_E_OK != retVal)
      {
        crlStatus = KEYM_E_CERTIFICATE_INVALID_CONTENT;
      }
      else
      #endif /* #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON) */
      {
        crlStatus = KEYM_CERTIFICATE_VALID;
      }
    }
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_808 */
    crlStatus = KEYM_CERTIFICATE_INVALID;
  }

  return crlStatus;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509CrlVerify                                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Verify CRL                                            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCert                                               **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrCrl                                                **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvCheckX509ParantName, Csm_SignatureVerify,     **
**                      KeyM_PrvCheckCvcParantName,                           **
**                      KeyM_PrvX509ConvertEccSignatureValue,                 **
**                      KeyM_PrvPartOfX509CrlVerify                           **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvX509CrlVerify(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCrl, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSignValue;
  Crypto_VerifyResultType verifyResult;
  KeyM_CertificateStatusType crlStatus;
  uint16 retVal;
  uint8 signValue[KEYM_ECC_SIGNATURE_VALUE_MAX_LENGTH];
  uint16 signLength;
  /* Initialize vairables */
  retVal = E_NOT_OK;
  verifyResult = CRYPTO_E_VER_NOT_OK;

  ptrParsedCrl = (KeyM_X509CrlType*)(ptrCrl->PtrParsedCert);

  /* Check parent name */
  #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
  /* @Trace: KeyM_SUD_FUNC_771 */
  if (KEYM_CERT_FORMAT_X509 == ptrCert->CertFormat)
  {
    retVal = KeyM_PrvCheckX509ParantName(ptrParsedCrl, ptrCert);
  }
  else
  #endif
  {
    /* @Trace: KeyM_SUD_FUNC_772 */
    #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
    if (KEYM_CERT_FORMAT_CVC == ptrCert->CertFormat)
    {
      retVal = KeyM_PrvCheckCvcParantName(ptrParsedCrl, ptrCert);
    }
    else
    #endif
    {
      /* Shall not enter here */
    }
  }

  if (KEYM_E_OK != retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_773 */
    crlStatus = KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_774 */
    if ((KEYM_PK_ECDSA_SHA1 <= ptrParsedCrl->SignAlgType) && \
      (KEYM_PK_ECDSA_SHA512 >= ptrParsedCrl->SignAlgType))
    {
      signLength = KEYM_ECC_SIGNATURE_VALUE_MAX_LENGTH;

      /* Convert ECC signature value */
      KeyM_PrvX509ConvertEccSignatureValue(\
      ptrParsedCrl->PtrSignatureValue->Element.PtrData, \
      ptrParsedCrl->PtrSignatureValue->Element.Length,\
      &signValue[0u], &signLength);

      ptrSignValue = &signValue[0u];
    }
    else
    {
      ptrSignValue = ptrParsedCrl->PtrSignatureValue->Element.PtrData;
      signLength = ptrParsedCrl->PtrSignatureValue->Element.Length;
    }

    /* Check if CRL is correctly signed by the certificate */
    retVal = Csm_SignatureVerify(ptrCert->CsmSignVerifyJob.CsmJobId, \
      CRYPTO_OPERATIONMODE_SINGLECALL, \
      ptrParsedCrl->TBSCertList.PtrData, \
      ptrParsedCrl->TBSCertList.Length, \
      ptrSignValue, signLength, &verifyResult);
    /* @Trace: KeyM_SUD_FUNC_775 */
    if (KEYM_E_OK != retVal)
    {
      crlStatus = KEYM_CERTIFICATE_INVALID;
    }
    else if (CRYPTO_E_VER_OK != verifyResult)
    {
      crlStatus = KEYM_E_CERTIFICATE_SIGNATURE_FAIL;
    }
    else
    {
      crlStatus = KeyM_PrvPartOfX509CrlVerify(ptrCrl, ptrParsedCrl);
    } /* @if (KEYM_E_OK != retVal) */
  } /* @if (ptrParsedCrl->IssuerNum != ptrParsedCert->SubjectNum) */
  ptrCrl->CertStatus = crlStatus;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvCertIsRevoked                                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check the certificate is in CRL                       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrSerialNumber, serialLength, currentTime, ptrCrl    **
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
static uint16 KeyM_PrvCertIsRevoked(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSerialNumber, \
  const uint16 serialLength, \
  const uint64 currentTime, \
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrCrl)
{
  P2CONST(KeyM_X509CrlEntryType, AUTOMATIC, KEYM_APPL_DATA) ptrCrlEntry;
  uint16 retVal;
  uint8 index;

  retVal = KEYM_E_OK;
  /* @Trace: KeyM_SUD_FUNC_795 */
  for (index = 0u; index < ptrCrl->EntryNum; index++)
  {
    ptrCrlEntry = &ptrCrl->PtrEntryList[index];
    /* Check the serial number of certificate */
    if (serialLength == ptrCrlEntry->Serial.Length)
    {
      retVal = KeyM_PrvMemCmp(ptrSerialNumber, \
        ptrCrlEntry->Serial.PtrData, serialLength);
      if (KEYM_E_OK == retVal)
      {
        if (currentTime > ptrCrlEntry->RevocationDate)
        {
          retVal = KEYM_E_BADCERT_REVOKED;
        }
        break;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCheckCertRevoked                              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check that the given certificate is not revoked       **
**                      according to the CRL.                                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrSerialNumber, serialLength, currentTime            **
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
**                      KeyM_PrvCertIsRevoked                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvCheckCertRevoked(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSerialNumber, \
  const uint16 serialLength, \
  const uint64 currentTime)
{
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrCrl;
  uint8 index;
  uint16 retVal;
  uint16 crlId;

  /* Initialize variables */
  retVal = KEYM_E_OK;
  /* @Trace: KeyM_SUD_FUNC_741 */
  for (index = 0u; ((KEYM_CERT_REVOCATION_LIST_NUM > index) && \
    (KEYM_E_OK == retVal)); index++)
  {
    crlId = KeyM_CertRevocationListId[index];

    if ((KEYM_TOTAL_CERTIFICATE > crlId) && \
      (KEYM_CERTIFICATE_VALID == KeyM_CryptoCert[crlId].CertStatus))
    {
      ptrCrl = (KeyM_X509CrlType*)(KeyM_CryptoCert[crlId].PtrParsedCert);

      /* Check if certificate is revoked */
      retVal = KeyM_PrvCertIsRevoked(ptrSerialNumber, serialLength, \
        currentTime, ptrCrl);

      if (KEYM_E_BADCERT_REVOKED == retVal)
      {
        /* Break the loop */
      }
      else
      {
        /* Continue the loop in this case */
        retVal = KEYM_E_OK;
      }
    } /* @if (KeyM_CryptoCert[crlId].CertStatus == KEYM_CERTIFICATE_INVALID) */
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
/*******************************************************************************
** Function Name      : KeyM_PrvAdjustX509Clr                                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Adjust parsed X509 CRL based on new address           **
**                      of certificate data buffer                            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCurAddress, ptrNewAddress                          **
**                                                                            **
** InOut Parameters   : ptrParsedCrl                                          **
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
FUNC(void, KEYM_CODE) KeyM_PrvAdjustX509Clr(\
  P2VAR(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCurAddress, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrNewAddress)
{
  sint32 deltaAddress;
  uint8 index;

  deltaAddress = (sint32)(ptrNewAddress - ptrCurAddress);
  /* @Trace: KeyM_SUD_FUNC_777 */
  /* Adjust the parsed Crl */
  ptrParsedCrl->TBSCertList.PtrData = \
    &(ptrParsedCrl->TBSCertList.PtrData)[deltaAddress];
  if (NULL_PTR != ptrParsedCrl->PtrRawVersion)
  {
    ptrParsedCrl->PtrRawVersion->Element.PtrData = \
    &(ptrParsedCrl->PtrRawVersion->Element.PtrData)[deltaAddress];
  }
  ptrParsedCrl->PtrRawSignature->Element.PtrData = \
    &(ptrParsedCrl->PtrRawSignature->Element.PtrData)[deltaAddress];
  ptrParsedCrl->PtrRawThisUpdate->Element.PtrData = \
    &(ptrParsedCrl->PtrRawThisUpdate->Element.PtrData)[deltaAddress];
  ptrParsedCrl->PtrRawNextUpdate->Element.PtrData = \
    &(ptrParsedCrl->PtrRawNextUpdate->Element.PtrData)[deltaAddress];
  ptrParsedCrl->PtrSignatureAlgorithm->Element.PtrData = \
    &(ptrParsedCrl->PtrSignatureAlgorithm->Element.PtrData)[deltaAddress];
  ptrParsedCrl->PtrSignatureValue->Element.PtrData = \
    &(ptrParsedCrl->PtrSignatureValue->Element.PtrData)[deltaAddress];
  /* @Trace: KeyM_SUD_FUNC_778 */
  /* Adjust parsed Issuer */
  for (index = 0u; index < ptrParsedCrl->IssuerNum; index++)
  {
    ptrParsedCrl->PtrIssuer[index].Element.PtrData = \
      &(ptrParsedCrl->PtrIssuer[index].Element.PtrData)[deltaAddress];
  }

  /* Adjust CRL entries */
  for (index = 0u; index < ptrParsedCrl->EntryNum ; index++)
  {
    ptrParsedCrl->PtrEntryList[index].RawCrlEntry.Element.PtrData = \
      &(ptrParsedCrl->PtrEntryList[index].\
      RawCrlEntry.Element.PtrData)[deltaAddress];
    ptrParsedCrl->PtrEntryList[index].Serial.PtrData = \
      &(ptrParsedCrl->PtrEntryList[index].Serial.PtrData)[deltaAddress];
  }

   /* Adjust Extensions */
  for (index = 0u; index < ptrParsedCrl->ExtensionNum; index++)
  {
    ptrParsedCrl->PtrExtensions[index].Element.PtrData = \
      &(ptrParsedCrl->PtrExtensions[index].Element.PtrData)[deltaAddress];
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvCopyParsedCRL                                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Copy parsed X509 CRL                                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrSrcCrl                                             **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrDesCrl                                             **
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
FUNC(void, KEYM_CODE) KeyM_PrvCopyParsedCRL(\
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrSrcCrl, \
  P2VAR(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrDesCrl)
{
  uint8 index;
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrSrcElement;
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrDesElement;
  P2CONST(KeyM_X509CrlEntryType, AUTOMATIC, KEYM_APPL_DATA) ptrSrcEntry;
  P2VAR(KeyM_X509CrlEntryType, AUTOMATIC, KEYM_APPL_DATA) ptrDesEntry;

  /* @Trace: KeyM_SUD_FUNC_781 */
  /* Copy certificate body */
  ptrDesCrl->TBSCertList.PtrData = ptrSrcCrl->TBSCertList.PtrData;
  ptrDesCrl->TBSCertList.Length = ptrSrcCrl->TBSCertList.Length;
  /* Copy RawVersion */
  ptrDesElement = ptrDesCrl->PtrRawVersion;
  ptrSrcElement = ptrSrcCrl->PtrRawVersion;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy RawSignature */
  ptrDesElement = ptrDesCrl->PtrRawSignature;
  ptrSrcElement = ptrSrcCrl->PtrRawSignature;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy RawThisUpdate */
  ptrDesElement = ptrDesCrl->PtrRawThisUpdate;
  ptrSrcElement = ptrSrcCrl->PtrRawThisUpdate;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy RawNextUpdate */
  ptrDesElement = ptrDesCrl->PtrRawNextUpdate;
  ptrSrcElement = ptrSrcCrl->PtrRawNextUpdate;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy SignatureAlgorithm */
  ptrDesElement = ptrDesCrl->PtrSignatureAlgorithm;
  ptrSrcElement = ptrSrcCrl->PtrSignatureAlgorithm;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy SignatureValue */
  ptrDesElement = ptrDesCrl->PtrSignatureValue;
  ptrSrcElement = ptrSrcCrl->PtrSignatureValue;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);

  ptrDesCrl->ThisUpdate = ptrSrcCrl->ThisUpdate;
  ptrDesCrl->NextUpdate = ptrSrcCrl->NextUpdate;
  ptrDesCrl->IssuerNum = ptrSrcCrl->IssuerNum;
  ptrDesCrl->EntryNum = ptrSrcCrl->EntryNum;
  ptrDesCrl->SignAlgType = ptrSrcCrl->SignAlgType;
  ptrDesCrl->ExtensionNum = ptrSrcCrl->ExtensionNum;
  /* @Trace: KeyM_SUD_FUNC_782 */
  /* Copy parsed Issuer */
  for (index = 0u; index < ptrDesCrl->IssuerNum; index++)
  {
    ptrDesElement = &ptrDesCrl->PtrIssuer[index];
    ptrSrcElement = &ptrSrcCrl->PtrIssuer[index];
    KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  }
  /* Copy parsed EntryList */
  for (index = 0u; index < ptrDesCrl->EntryNum; index++)
  {
    ptrDesEntry = &ptrDesCrl->PtrEntryList[index];
    ptrSrcEntry = &ptrSrcCrl->PtrEntryList[index];

    ptrDesElement = &ptrDesEntry->RawCrlEntry;
    ptrSrcElement = &ptrSrcEntry->RawCrlEntry;
    KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);

    ptrDesEntry->Serial.PtrData = ptrSrcEntry->Serial.PtrData;
    ptrDesEntry->Serial.Length = ptrSrcEntry->Serial.Length;

    ptrDesEntry->RevocationDate = ptrSrcEntry->RevocationDate;
  }

  /* Copy Extensions */
  for (index = 0u; index < ptrDesCrl->ExtensionNum; index++)
  {
    ptrDesElement = &ptrDesCrl->PtrExtensions[index];
    ptrSrcElement = &ptrSrcCrl->PtrExtensions[index];
    KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name      : KeyM_PrvRecoverX509Crl                                **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Recover parsed X509 CRL                               **
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
FUNC(void, KEYM_CODE) KeyM_PrvRecoverX509Crl(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  P2VAR(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrl;
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedElement;
  uint8 index;
  uint16 elementIndex;

  ptrParsedCrl = (KeyM_X509CrlType*)ptrCert->PtrParsedCert;
  /* @Trace: KeyM_SUD_FUNC_784 */
  /* Recover RawVersion */
  if (NULL_PTR != ptrParsedCrl->PtrRawVersion)
  {
    elementIndex = ptrParsedCrl->PtrRawVersion->ElementIndex;
    ptrCert->PtrCertElement[elementIndex].PtrElement = \
    ptrParsedCrl->PtrRawVersion;
  }
  /* Recover RawSignature */
  elementIndex = ptrParsedCrl->PtrRawSignature->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCrl->PtrRawSignature;
  /* Recover RawThisUpdate */
  elementIndex = ptrParsedCrl->PtrRawThisUpdate->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCrl->PtrRawThisUpdate;
  /* Recover RawNextUpdate */
  elementIndex = ptrParsedCrl->PtrRawNextUpdate->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCrl->PtrRawNextUpdate;
  /* Recover SignAlgorithm */
  elementIndex = ptrParsedCrl->PtrSignatureAlgorithm->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCrl->PtrSignatureAlgorithm;
  /* Recover SignValue */
  elementIndex = ptrParsedCrl->PtrSignatureValue->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCrl->PtrSignatureValue;
  /* @Trace: KeyM_SUD_FUNC_785 */
  /* Recover Issuer  */
  for (index = 0u; index < ptrParsedCrl->IssuerNum; index++)
  {
    ptrParsedElement = &ptrParsedCrl->PtrIssuer[index];
    elementIndex = ptrParsedElement->ElementIndex;
    ptrCert->PtrCertElement[elementIndex].PtrElement = ptrParsedElement;
  }
  /* Recover CRL entry list  */
  for (index = 0u; index < ptrParsedCrl->EntryNum; index++)
  {
    ptrParsedElement = &ptrParsedCrl->PtrEntryList[index].RawCrlEntry;
    elementIndex = ptrParsedElement->ElementIndex;
    ptrCert->PtrCertElement[elementIndex].PtrElement = ptrParsedElement;
  }

  /* Recover Extensions */
  for (index = 0u; index < ptrParsedCrl->ExtensionNum; index++)
  {
    ptrParsedElement = &ptrParsedCrl->PtrExtensions[index];
    elementIndex = ptrParsedElement->ElementIndex;
    ptrCert->PtrCertElement[elementIndex].PtrElement = ptrParsedElement;
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509WriteRevokedCertificates                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write revokedCertificates element in X509 CRL         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrStart, ptrEntryArr, numberOfEntry, ptrCert         **
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
**                      KeyM_Asn1WriteLength, KeyM_Asn1WriteTag               **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509WriteRevokedCertificates(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition,
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart,
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert,
  P2CONST(KeyM_X509CrlEntryType, AUTOMATIC, KEYM_APPL_DATA) ptrEntryArr,
  const uint8 numberOfEntry,
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  uint16 elementIndex;
  uint8 index;
  uint16 subLength;
  uint16 length;
  uint8 bytesToStoreLen;
  uint8 tag;

  bytesToStoreLen = 0u;
  length = 0u;
  retVal = E_NOT_OK;
  tag = KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE;
  /* @Trace: KeyM_SUD_FUNC_812 */
  for (index = 1u; index <= numberOfEntry; index++)
  {
    elementIndex = ptrEntryArr[numberOfEntry - index].RawCrlEntry.ElementIndex;
    subLength = ptrCert->PtrCertElement[elementIndex].ElementMaxLength;

    if (*ptrPosition < (&(ptrStart[subLength])))
    {
      /* @Trace: KeyM_SUD_FUNC_813 */
      retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_814 */
      *ptrPosition -= subLength;
      /* Write length of data */
      retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, subLength,\
        &bytesToStoreLen);

      if (E_OK == retVal)
      {
        subLength += bytesToStoreLen;
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

  if (E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_816 */
    /* Write length of data */
    retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, length, \
      &bytesToStoreLen);

    if (E_OK == retVal)
    {
      length += bytesToStoreLen;
      retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, tag, &bytesToStoreLen);
      /* @Trace: KeyM_SUD_FUNC_817 */
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
** Function Name      : KeyM_PrvX509CrlGenerate                               **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Generate one X.509 CRL skeleton in DER format         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCert, ptrData                                      **
**                                                                            **
** InOut Parameters   : ptrDataLength                                         **
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
**                      KeyM_PrvX509WriteElement, KeyM_PrvX509WriteExtensions,**
**                      KeyM_PrvX509WriteRevokedCertificates,                 **
**                      KeyM_PrvPartOfX509CrlGenerate, KeyM_Asn1WriteLength,  **
**                      KeyM_Asn1WriteTag                                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509CrlGenerate(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrDataLength)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2VAR(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert;
  uint16 length;
  uint16 subLength;
  uint8 bytesToStoreLen;
  uint8 tag;

  /* @Trace: KeyM_SUD_FUNC_787 */
  length = 0u;
  subLength = 0u;
  ptrStart = ptrData;
  ptrPosition = &ptrStart[*ptrDataLength];
  ptrParsedCert = (KeyM_X509CrlType*)ptrCert->PtrParsedCert;

  /* Write signature value */
  retVal = KeyM_PrvX509WriteElement(&ptrPosition, ptrStart, ptrCert,\
    ptrParsedCert->PtrSignatureValue, &length, KEYM_ASN1_BIT_STRING);

  if (E_OK == retVal)
  {
    /* Write signature algorithm */
    tag = KEYM_ASN1_SEQUENCE | KEYM_ASN1_PC_CONSTRUCTED;
    retVal = KeyM_PrvX509WriteElement(&ptrPosition, ptrStart, ptrCert,\
      ptrParsedCert->PtrSignatureAlgorithm, &length, tag);
    /* @Trace: KeyM_SUD_FUNC_788 */
    if (E_OK == retVal)
    {
      /* Write Extensions */
      if ((NULL_PTR != ptrParsedCert->PtrExtensions) && \
        (0u < ptrParsedCert->ExtensionNum))
      {
        retVal = KeyM_PrvX509WriteExtensions(&ptrPosition, ptrStart, ptrCert,\
          ptrParsedCert->PtrExtensions, \
          ptrParsedCert->ExtensionNum, &subLength, 0u);
      }

      if (E_OK == retVal)
      {
        /* @Trace: KeyM_SUD_FUNC_789 */
        /* Write revokedCertificates */
        if ((NULL_PTR != ptrParsedCert->PtrEntryList) && \
          (0u < ptrParsedCert->EntryNum))
        {
          retVal = KeyM_PrvX509WriteRevokedCertificates(&ptrPosition,\
            ptrStart, ptrCert, ptrParsedCert->PtrEntryList, \
            ptrParsedCert->EntryNum, &subLength);
        }
        if (E_OK == retVal)
        {
          retVal = KeyM_PrvPartOfX509CrlGenerate(&ptrPosition, \
            ptrStart, ptrCert, ptrParsedCert, &subLength);
          /* @Trace: KeyM_SUD_FUNC_790 */
          if (E_OK == retVal)
          {
            bytesToStoreLen = 0u;
            /* Write length of TBS */
            retVal = KeyM_Asn1WriteLength(&ptrPosition, ptrStart, \
              subLength, &bytesToStoreLen);
            /* @Trace: KeyM_SUD_FUNC_791 */
            if (E_OK == retVal)
            {
              subLength += bytesToStoreLen;
              /* Write tag of TBS */
              tag = KEYM_ASN1_SEQUENCE | KEYM_ASN1_PC_CONSTRUCTED;
              retVal = KeyM_Asn1WriteTag(&ptrPosition, ptrStart, \
                tag, &bytesToStoreLen);
              /* @Trace: KeyM_SUD_FUNC_792 */
              if (E_OK == retVal)
              {
                subLength += bytesToStoreLen;
                /* Length of CRL */
                length += subLength;
                /* Write length of certificate */
                retVal = KeyM_Asn1WriteLength(&ptrPosition, ptrStart, length, \
                  &bytesToStoreLen);
                /* @Trace: KeyM_SUD_FUNC_793 */
                if (E_OK == retVal)
                {
                  length += bytesToStoreLen;
                  /* Write tag of certificate */
                  retVal = KeyM_Asn1WriteTag(&ptrPosition, ptrStart, \
                    tag, &bytesToStoreLen);
                  if (E_OK == retVal)
                  {
                    length += bytesToStoreLen;
                    *ptrDataLength = length;
                    KeyM_PtrResultData = ptrPosition;
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
** Function Name      : KeyM_PrvPartOfX509CrlGenerate                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvX509CrlGenerate, this       **
**                      function is created to reduce code metric of          **
**                      KeyM_PrvX509CrlGenerate                               **
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
**                      KeyM_PrvX509WriteTime, KeyM_PrvX509WriteElement,      **
**                      KeyM_PrvX509WriteIssuerSubject                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvPartOfX509CrlGenerate(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CrlType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  /* @Trace: KeyM_SUD_FUNC_818 */
  /* Write Next Update */
  retVal = KeyM_PrvX509WriteTime(ptrPosition, ptrStart, ptrCert,\
    ptrParsedCert->PtrRawNextUpdate, ptrLength);

  if (E_OK == retVal)
  {
    /* Write This Update */
    retVal = KeyM_PrvX509WriteTime(ptrPosition, ptrStart, ptrCert,\
      ptrParsedCert->PtrRawThisUpdate, ptrLength);
    /* @Trace: KeyM_SUD_FUNC_819 */
    if (E_OK == retVal)
    {
      /* Write Issuer */
      retVal = KeyM_PrvX509WriteIssuerSubject(ptrPosition, ptrStart, ptrCert,\
        ptrParsedCert->PtrIssuer, ptrParsedCert->IssuerNum, ptrLength);
      /* @Trace: KeyM_SUD_FUNC_820 */
      if (E_OK == retVal)
      {
        /* Write signature algorithm */
        retVal = KeyM_PrvX509WriteElement(ptrPosition, ptrStart, ptrCert,\
          ptrParsedCert->PtrRawSignature, ptrLength, \
          (KEYM_ASN1_SEQUENCE | KEYM_ASN1_PC_CONSTRUCTED));
        /* @Trace: KeyM_SUD_FUNC_821 */
        if (E_OK == retVal)
        {
          /* Write Version */
          if (NULL_PTR != ptrParsedCert->PtrRawVersion)
          {
            retVal = KeyM_PrvX509WriteElement(ptrPosition, ptrStart, ptrCert,\
              ptrParsedCert->PtrRawVersion, ptrLength, KEYM_ASN1_INTEGER);
          }
        }
      }
    } /* @if (KEYM_E_OK == retVal) */
  } /* @if (KEYM_E_OK == retVal) */
  
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF) */
#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

#endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
