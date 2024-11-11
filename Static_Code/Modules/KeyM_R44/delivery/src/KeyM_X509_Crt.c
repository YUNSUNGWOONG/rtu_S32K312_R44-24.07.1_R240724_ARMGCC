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
** 1.0.1.0   27-Mar-2021   TamTV6       Fix defect #18154, Add Trace SUD      **
** 1.0.2     08-Nov-2021   TamTV6       Implement #20971                      **
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
** 1.0.7.0   07-Apr-2023   PhuocLH9     #CP44-1636,#CP44-1664,#CP44-1854      **
**                                      #CP44-1541,#CP44-1665,#CP44-1684      **
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
/* KeyM X509 CRT header file */
#include "KeyM_X509_Crt.h"
/* KeyM X509 CRL header file */
#include "KeyM_X509_Crl.h"
/* KeyM internal function prototype */
#include "KeyM_IntFunc.h"
/* KeyM Ram header file  */
#include "KeyM_Ram.h"
/* KeyM OID header file */
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
#if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCertSerial(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCertValidity(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCertPublicKeyInfo(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509ParsePublickeyInfor(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId,\
  P2CONST(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrParams,
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKeyAlgorithm
  );
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCertPublicKeyValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCertUniqueID(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrUniqueID, \
  const uint8 tag);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509CertStorePublicKey(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrt);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvPartOfX509CertificateParseDer(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF)
#if (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON)

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509WriteSignatureValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSignValue, \
  const uint16 signValLength, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509WritePublicKeyValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKey, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvPartOneOfX509CertificateGenerate(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrBuffer, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvPartTwoOfX509CertificateGenerate(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvPartThreeOfX509CertificateGenerate(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
  #define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) */
#endif /* (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF) */
#endif /* (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_CertificateStatusType KeyM_PrvPartOfX509CertificatePairVerify(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrt);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509CertificateParseDer                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Parse one X.509 certificate in DER format from        **
**                      a buffer                                              **
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
**                      KeyM_Asn1GetTag, KeyM_PrvX509GetSignAlgorithm,        **
**                      KeyM_PrvPartOfX509CertificateParseDer, KeyM_PrvMemCmp,**
**                      KeyM_PrvX509GetSignatureValue                         **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvX509CertificateParseDer(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  const uint16 dataLength)
{
  uint16 retVal;
  uint16 length;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCertEnd;
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert;

  ptrPosition = ptrData;
  length = dataLength;
  ptrEnd = &ptrPosition[length];
  /*
   * Certificate  ::=  SEQUENCE  {
   *      tbsCertificate       TBSCertificate,
   *      signatureAlgorithm   AlgorithmIdentifier,
   *      signatureValue       BIT STRING  }
   */
  /* @Trace: KeyM_SUD_FUNC_661 */
  retVal = KeyM_Asn1GetTag(&ptrPosition, ptrEnd, &length, \
    KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);

  if (KEYM_E_OK == retVal)
  {
    if ((&(ptrPosition[length])) != ptrEnd)
    {
      retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
    }
    else
    {
      ptrParsedCert = (KeyM_X509CertificateType*)ptrCert->PtrParsedCert;
      ptrCertEnd = &ptrPosition[length];
      ptrParsedCert->TBSCert.PtrData = ptrPosition;

      /* ==================================
       * TBSCertificate  ::=  SEQUENCE  {
       * ==================================*/
      retVal = KeyM_Asn1GetTag(&ptrPosition, ptrCertEnd, &length, \
        KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE);
      /* @Trace: KeyM_SUD_FUNC_662 */
      if (KEYM_E_OK == retVal)
      {
        ptrEnd = &ptrPosition[length];
        ptrParsedCert->TBSCert.Length = \
        (uint16)((sint32)(ptrEnd - ptrParsedCert->TBSCert.PtrData));

        retVal = KeyM_PrvPartOfX509CertificateParseDer(&ptrPosition, ptrEnd, \
          ptrCert, ptrParsedCert);
        /* @Trace: KeyM_SUD_FUNC_663 */
        if (KEYM_E_OK == retVal)
        {
          /* Set end position is the end of certificate */
          ptrEnd = ptrCertEnd;
          /* Get signature algorithm */
          retVal = KeyM_PrvX509GetSignAlgorithm(\
            &ptrPosition, ptrEnd, ptrCert, \
            &ptrParsedCert->SignAlgType, \
            ptrParsedCert->PtrSignatureAlgorithm);

          if (KEYM_E_OK == retVal)
          {
            /* @Trace: KeyM_SUD_FUNC_664 */
            /* Check Signature Algorithm ID in the TBS is the same
               Signature Algorithm ID at the end of certificate */
            if (ptrParsedCert->PtrRawSignature->Element.Length != \
              ptrParsedCert->PtrSignatureAlgorithm->Element.Length)
            {
               retVal = KEYM_E_SIG_MISMATCH;
            }
            else
            {
              retVal = KeyM_PrvMemCmp(\
                ptrParsedCert->PtrRawSignature->Element.PtrData, \
                ptrParsedCert->PtrSignatureAlgorithm->Element.PtrData, \
                ptrParsedCert->PtrRawSignature->Element.Length);
              /* @Trace: KeyM_SUD_FUNC_665 */
              if (KEYM_E_OK != retVal)
              {
                retVal = KEYM_E_SIG_MISMATCH;
              }
              else
              {
                retVal = KeyM_PrvX509GetSignatureValue(&ptrPosition, \
                  ptrEnd, ptrCert, ptrParsedCert->SignAlgType,\
                  ptrParsedCert->PtrSignatureValue);

                if (KEYM_E_OK == retVal)
                {
                  /* @Trace: KeyM_SUD_FUNC_666 */
                  /* End of Certificate, the current position must be the end
                     of Certificate */
                  if (ptrEnd != ptrPosition)
                  {
                    retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
                  }
                } /* @if (KEYM_E_OK == retVal) */
              } /* @if (KEYM_E_OK == retVal) */
            } /* @if (ptrParsedCert->PtrRawSignature->Element.Length != \
                ptrParsedCert->PtrSignatureAlgorithm->Element.Length) */
          } /* @if (KEYM_E_OK == retVal) */
        } /* @if (KEYM_E_OK == retVal) */
      } /* @if (KEYM_E_OK == retVal) */
    } /* @if (KEYM_E_OK == retVal) */
  } /* @if (KEYM_E_OK == retVal) */
  return retVal;
} /* @End of KeyM_PrvX509CertificateParseDer */
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPartOfX509CertificateParseDer                 **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvX509CertificateParseDer,    **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvX509CertificateParseDer                       **
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
**                      KeyM_PrvX509GetVersion, KeyM_PrvX509GetCertSerial,    **
**                      KeyM_PrvX509GetSignAlgorithm,                         **
**                      KeyM_PrvX509GetIssuerSubject,                         **
**                      KeyM_PrvX509GetCertValidity,                          **
**                      KeyM_PrvX509GetCertPublicKeyInfo,                     **
**                      KeyM_PrvX509GetCertUniqueID, KeyM_PrvX509GetExtensions**
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvPartOfX509CertificateParseDer(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert)
{
  uint16 retVal;
  uint8 tag;

  /*
   * Version  ::=  INTEGER  {  v1(0), v2(1), v3(2)  }
   *
   * CertificateSerialNumber  ::=  INTEGER
   *
   * signature  AlgorithmIdentifier
   */
  /* @Trace: KeyM_SUD_FUNC_697 */
  tag = (KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 0U);
  retVal = KeyM_PrvX509GetVersion(ptrPosition, ptrEnd, ptrCert,\
    ptrParsedCert->PtrRawVersion, tag);
  if (KEYM_E_OK == retVal)
  {
    /* Get Serial */
    retVal = KeyM_PrvX509GetCertSerial(ptrPosition, ptrEnd, ptrCert,\
      ptrParsedCert);
    /* @Trace: KeyM_SUD_FUNC_698 */
    if (KEYM_E_OK == retVal)
    {
      /* Get signature algorithm identifier in TBS */
      retVal = KeyM_PrvX509GetSignAlgorithm(\
        ptrPosition, ptrEnd, ptrCert, \
        &ptrParsedCert->SignAlgType, \
        ptrParsedCert->PtrRawSignature);

      /*
       * issuer Name
       *
       * Validity ::= SEQUENCE {
       *      notBefore      Time, \
       *      notAfter       Time }
       *
       * subject  Name
       *
       */
      /* @Trace: KeyM_SUD_FUNC_699 */
      if (KEYM_E_OK == retVal)
      {
        /* Get issuer name */
        retVal = KeyM_PrvX509GetIssuerSubject(ptrPosition, ptrEnd,\
          ptrCert, ptrParsedCert->PtrIssuer,\
          ptrParsedCert->IssuerNum);
        /* @Trace: KeyM_SUD_FUNC_700 */
        if (KEYM_E_OK == retVal)
        {
          /* Get validity time */
          retVal = KeyM_PrvX509GetCertValidity(ptrPosition, \
            ptrEnd, ptrCert, ptrParsedCert);
          /* @Trace: KeyM_SUD_FUNC_701 */
          if (KEYM_E_OK == retVal)
          {
            /* Get subject name */
            retVal = KeyM_PrvX509GetIssuerSubject(ptrPosition, \
              ptrEnd, ptrCert, ptrParsedCert->PtrSubject,\
              ptrParsedCert->SubjectNum);
            /* @Trace: KeyM_SUD_FUNC_702 */
            /*
             * SubjectPublicKeyInfo
             */
            if (KEYM_E_OK == retVal)
            {
              retVal = KeyM_PrvX509GetCertPublicKeyInfo(ptrPosition,\
                ptrEnd, ptrCert, ptrParsedCert);
              /* @Trace: KeyM_SUD_FUNC_703 */
              /*
               *  issuerUniqueID  [1]  IMPLICIT UniqueIdentifier OPTIONAL, \
               *                       -- If present, version shall be v2 or v3
               *  subjectUniqueID [2]  IMPLICIT UniqueIdentifier OPTIONAL, \
               *                       -- If present, version shall be v2 or v3
               */
              if (KEYM_E_OK == retVal)
              {
                /* Get issuerUniqueID */
                tag = (KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | 1U);
                retVal = KeyM_PrvX509GetCertUniqueID(ptrPosition, \
                  ptrEnd, ptrCert, ptrParsedCert->PtrIssuerUniqueID, tag);

                if (KEYM_E_OK == retVal)
                {
                  /* Get subjectUniqueID */
                  tag = (KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | 2U);
                  retVal = KeyM_PrvX509GetCertUniqueID(ptrPosition, \
                    ptrEnd, ptrCert,\
                    ptrParsedCert->PtrSubjectUniqueID, tag);
                  /* @Trace: KeyM_SUD_FUNC_704 */
                  /*
                   *  extensions      [3]  EXPLICIT Extensions OPTIONAL
                   *                       -- If present, version shall be v3
                   */
                  if (KEYM_E_OK == retVal)
                  {
                    retVal = KeyM_PrvX509GetExtensions(ptrPosition, ptrEnd, \
                      ptrCert, ptrParsedCert->PtrExtensions,\
                      ptrParsedCert->ExtensionNum, 3u);
                    /* @Trace: KeyM_SUD_FUNC_705 */
                    /* End of TBSCertificate, the current position
                      must be the end of TBS */
                    if (ptrEnd != *ptrPosition)
                    {
                      retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
                    }
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
** Function Name      : KeyM_PrvX509GetCertIssuerUniqueID                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get unique ID element in a certificate                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrEnd, tag                                           **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrCert, ptrUniqueID                     **
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
static uint16 KeyM_PrvX509GetCertUniqueID(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrUniqueID, \
  const uint8 tag)
{
  uint16 length;
  uint16 retVal;
  uint16 elementIndex;
  boolean hasUniqueId;

  /* @Trace: KeyM_SUD_FUNC_728 */
  retVal = KEYM_E_OK;
  length = 0U;
  hasUniqueId = KEYM_FALSE;
  if (*ptrPosition == ptrEnd)
  {
    /* Because issuerUniqueID, subjectUniqueID and extensions elements are
      optional so the certificate may not has these elements.
      The current position is the end of TBS */
  }
  else
  {
    retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);

    if ((KEYM_E_ASN1_UNEXPECTED_TAG == retVal) || (KEYM_E_OK == retVal))
    {
      if (KEYM_E_ASN1_UNEXPECTED_TAG == retVal)
      {
        /* The issuerUniqueID are optional, so if the get tag
         function return unexpected tag error, it means that
         the certificate has not this element. This is not actual error, \
         we should return OK and continue getting next element */
        retVal = KEYM_E_OK;
      }
      else
      {
        hasUniqueId = KEYM_TRUE;
      }
    } /* @if ((KEYM_E_ASN1_UNEXPECTED_TAG != retVal) && (KEYM_E_OK != retVal)) */
  } /* @if (*ptrPosition == ptrEnd) */

  if (KEYM_E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_729 */
    if ((NULL_PTR != ptrUniqueID) && (KEYM_TRUE == hasUniqueId))
    {
      elementIndex = ptrUniqueID->ElementIndex;
      /* Check the certificate element of issuerUniqueID */
      retVal = KeyM_PrvCheckCertificateElement(ptrCert, elementIndex, tag,\
        NULL_PTR, 0u);

      if (KEYM_E_OK == retVal)
      {
        /* Update the IssuerUniqueID tag, length, data */
        ptrUniqueID->Element.Tag = tag;
        ptrUniqueID->Element.Length = length;
        ptrUniqueID->Element.PtrData = *ptrPosition;
        /* Move position to the next element */
        *ptrPosition = &(*ptrPosition)[length];
        ptrCert->PtrCertElement[elementIndex].PtrElement = ptrUniqueID;
      }
    }
    else if ((NULL_PTR == ptrUniqueID) && (KEYM_FALSE == hasUniqueId))
    {
      /* Accept the case there is no element */
      retVal = KEYM_E_OK;
    }
    else
    {
      retVal = KEYM_E_INVALID_UNIQUE_ID;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetCertPublicKeyInfo                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get PublicKeyInfo element in a certificate            **
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
**                      KeyM_Asn1GetTag, KeyM_Asn1GetAlgorithmIdent,          **
**                      KeyM_PrvX509GetPublicKeyType,                         **
**                      KeyM_PrvX509ParseRsaSsaPssParams,                     **
**                      KeyM_PrvCheckCertificateElement,                      **
**                      KeyM_PrvX509GetCertPublicKeyValue                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCertPublicKeyInfo(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert)
{
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKeyAlgorithm;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKeyEnd;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrAlgorithmEnd;
  KeyM_AsnElementType objectId;
  KeyM_AsnElementType params;  
  uint16 retVal;
  uint16 length;
  uint8 keyType;
  uint8 tag;
  uint16 elementIndex;
  uint8 numOfAlgorithmCfg = 0;

  /* Initialize variables */
  length = 0U;
  keyType = 0U;
  tag = KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE;

  objectId.Tag = KEYM_ZERO;
  objectId.Length = KEYM_ZERO;
  objectId.PtrData = NULL_PTR;

  /* @Trace: KeyM_SUD_FUNC_713 */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);
  if (KEYM_E_OK == retVal)
  {
    /* Update the end position of the Public Key Info */
    ptrPublicKeyEnd = &(*ptrPosition)[length];

    /* Get AlgorithmIdentifier */
    retVal = KeyM_Asn1GetTag(ptrPosition, ptrPublicKeyEnd, &length, tag);
    /* @Trace: KeyM_SUD_FUNC_714 */
    if (KEYM_E_OK == retVal)
    {
      ptrPublicKeyAlgorithm = ptrParsedCert->PtrPublicKeyAlgorithm;
      ptrAlgorithmEnd = &(*ptrPosition)[length];

      if (NULL_PTR != ptrPublicKeyAlgorithm)
      {
        /* @Trace: KeyM_SUD_FUNC_716 */
        ptrPublicKeyAlgorithm->Element.Tag = tag;
        ptrPublicKeyAlgorithm->Element.Length = length;
        ptrPublicKeyAlgorithm->Element.PtrData = *ptrPosition;

        params.Tag = KEYM_ZERO;
        params.Length = KEYM_ZERO;
        params.PtrData = NULL_PTR;
        /* Parse AlgorithmIdentifier */
        retVal = KeyM_Asn1GetAlgorithmIdent(ptrPosition, ptrAlgorithmEnd,
                                            &objectId, &params);

        if (KEYM_E_OK == retVal)
        {
          retVal = KeyM_PrvX509GetPublicKeyType(objectId.PtrData,
                                                (uint8)objectId.Length, &keyType);

          if (KEYM_E_OK == retVal)
          {
            /* @Trace: KeyM_SUD_FUNC_718 */
            if ((KEYM_PK_RSA == keyType) && (KEYM_ASN1_NULL != params.Tag) &&
                (0u != params.Tag))
            {
              /* parameters are absent or NULL */
              retVal = KEYM_E_INVALID_PUBLIC_KEY;
            }
            else if (((KEYM_PK_EC == keyType) || (KEYM_PK_ECDH == keyType)) &&
                     (KEYM_ASN1_OID != params.Tag) && (0u != params.Tag))
            {
              /* parameters are absent or OID */
              retVal = KEYM_E_INVALID_PUBLIC_KEY;
            }
            else if (KEYM_PK_RSASSA_PSS == keyType)
            {
              retVal = KeyM_PrvX509ParseRsaSsaPssParams(&params);
            }
            else
            {
              /* Shall not enter here */
            }

            if (KEYM_E_OK == retVal)
            {
              ptrParsedCert->PublicKeyType = keyType;

              numOfAlgorithmCfg = KeyM_PrvGetPublicKeyAlgorithmCount(ptrCert);
              /*Get number of public key algorithm - maximum is 2 for ECC certificate */
              /* @Trace: KeyM_SUD_FUNC_967 */
              if (2 == numOfAlgorithmCfg)
              {
                /* more than 1 public key algorithms -> check OID and parse*/
                retVal = KeyM_PrvX509ParsePublickeyInfor(ptrCert,
                                                         &objectId, &params, ptrPublicKeyAlgorithm);
              }
              else if (1 == numOfAlgorithmCfg)
              {
               /* 1 public key algorithm in configuration*/
                elementIndex = ptrPublicKeyAlgorithm->ElementIndex;
                /* Check the certificate element of subject public key algorithm*/
                retVal = KeyM_PrvCheckCertificateElement(ptrCert, elementIndex,
                                                         tag, NULL_PTR, 0u);
                if (KEYM_E_OK == retVal)
                {
                  ptrCert->PtrCertElement[elementIndex].PtrElement =
                      ptrPublicKeyAlgorithm;
                } 
              }
              else
              {
                /* this code is not exist because generator validation number 34*/
              }
              /* @Trace: KeyM_SUD_FUNC_719 */
              if (KEYM_E_OK == retVal)
              {
                /* Get public key value */
                retVal = KeyM_PrvX509GetCertPublicKeyValue(ptrPosition,
                                                           ptrPublicKeyEnd, ptrCert, ptrParsedCert);
              }
              else
              {
                /* @Trace: KeyM_SUD_FUNC_968 */
                retVal = KEYM_E_INVALID_PUBLIC_KEY;
              }
            } /* @if (KEYM_E_OK != retVal) */
          }
          else
          {
            /* @Trace: KeyM_SUD_FUNC_717 */
            retVal = KEYM_E_INVALID_PUBLIC_KEY;
          } /* @if (KEYM_E_OK == retVal) */
        }
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_715 */
        retVal = KEYM_E_INVALID_FORMAT;
      } /* @if (NULL_PTR != ptrPublicKeyAlgorithm) */
    } /* @if (KEYM_E_OK == retVal) */
  } /* @if (KEYM_E_OK != retVal) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509ParsePublickeyInfor                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : parse element algorithm of public key, both algorithm **
**                     and curve name                                         **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrObjectId,ptrParams                                 **
**                                                                            **
** InOut Parameters   : ptrPublicKeyAlgorithm, ptrCert                        **
**                                                                            **
** Output Parameters  : retVal                                                **
**                                                                            **
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509ParsePublickeyInfor(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId,\
  P2CONST(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrParams,
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKeyAlgorithm
  )
{
	P2VAR(KeyM_CertElementType, AUTOMATIC, KEYM_APPL_DATA) ptrElement;
	P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrPubKeyAlgo;
	uint16 retVal = KEYM_E_NOT_OK;
	uint8 cnt = 0;
	uint16 elementIndex = 0;
	uint16 index = 0;

  /*Get pointer publickey Altgorithm in Parsecert pointer*/
  ptrPubKeyAlgo = ptrPublicKeyAlgorithm;

  for (index = 0; index < ptrCert->NumberOfCertElement; index++)
  {
    ptrElement = &(ptrCert->PtrCertElement[index]);
    /* Get current element*/
    if (KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_PUBLIC_KEY_ALGORITHM ==
        ptrElement->ElementOfStruct)
    {
      /*If element is publickey algorithm, check OID if match*/
      for (cnt = 0; cnt < 2; cnt++)
      {
        ptrPubKeyAlgo = &ptrPubKeyAlgo[cnt];
        /*compare the element ID of PtrElement and PtrParsecert(get from input)*/
        if (ptrElement->ElementId == ptrPubKeyAlgo->ElementIndex)
        {
          /*Compare OID of element in configuration and actual data*/
          retVal = KeyM_PrvCheckCertificateElement(ptrCert, ptrElement->ElementId,\
                  ptrObjectId->Tag, ptrObjectId->PtrData, ptrObjectId->Length);

          if (KEYM_E_OK == retVal)
          {
            /*OID match -> parse algorithm*/
            ptrPubKeyAlgo->Element.Tag = ptrObjectId->Tag;
            ptrPubKeyAlgo->Element.Length = ptrObjectId->Length;
            ptrPubKeyAlgo->Element.PtrData = ptrObjectId->PtrData;
            /* Parse public key Algorithm information - algorithm in EC certificate */

            elementIndex = ptrPubKeyAlgo->ElementIndex;

            ptrCert->PtrCertElement[elementIndex].PtrElement =
                ptrPubKeyAlgo;
          }
          else
          {
            /*Compare OID of element in configuration and actual data*/
            retVal = KeyM_PrvCheckCertificateElement(ptrCert, ptrElement->ElementId,\
                        ptrParams->Tag, ptrParams->PtrData, ptrParams->Length);

            if (KEYM_E_OK == retVal)
            {
              /*OID match -> parse curve name*/
              ptrPubKeyAlgo->Element.Tag = ptrParams->Tag;
              ptrPubKeyAlgo->Element.Length = ptrParams->Length;
              ptrPubKeyAlgo->Element.PtrData = ptrParams->PtrData;
              /* Parse  public key Algorithm information - curve name in EC certificate */

              elementIndex = ptrPubKeyAlgo->ElementIndex;

              ptrCert->PtrCertElement[elementIndex].PtrElement =
                  ptrPubKeyAlgo;
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
** Function Name      : KeyM_PrvX509GetCertPublicKeyValue                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get Public Key value element in a certificate         **
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
**                      KeyM_Asn1GetBitstringNoneUnusedBits,                  **
**                      KeyM_PrvCheckCertificateElement                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCertPublicKeyValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert)
{
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrSubjectPublicKey;
  uint16 retVal;
  uint16 length;
  uint16 elementIndex;

  /* @Trace: KeyM_SUD_FUNC_723 */
  /* Initialize variables */
  length = 0U;
  ptrSubjectPublicKey = ptrParsedCert->PtrSubjectPublicKey;
  /* Get public key value */
  retVal = KeyM_Asn1GetBitstringNoneUnusedBits(ptrPosition, \
    ptrEnd, &length);

  if (KEYM_E_OK == retVal)
  {
    if (((KEYM_PK_EC == ptrParsedCert->PublicKeyType) || \
      (KEYM_PK_ECDH == ptrParsedCert->PublicKeyType)) && \
      (0x04u != **ptrPosition))
    {
      /* @Trace: KeyM_SUD_FUNC_724 */
      /* For ECC public key, the library only support uncompressed form, so
         the first byte(prefix) of public key must be 0x04 */
      retVal = KEYM_E_INVALID_PUBLIC_KEY;
    }
    else
    {
      if (NULL_PTR != ptrSubjectPublicKey)
      {
        /* @Trace: KeyM_SUD_FUNC_726 */
        elementIndex = ptrSubjectPublicKey->ElementIndex;
        /* Check the certificate element of subject public key */
        retVal = KeyM_PrvCheckCertificateElement(ptrCert, elementIndex, \
          KEYM_ASN1_BIT_STRING, NULL_PTR, 0u);

        if (KEYM_E_OK == retVal)
        {
          /* @Trace: KeyM_SUD_FUNC_727 */
          /* Update the SubjectPublicKey tag, length, data */
          ptrSubjectPublicKey->Element.Tag = KEYM_ASN1_BIT_STRING;
          ptrSubjectPublicKey->Element.Length = length;
          ptrSubjectPublicKey->Element.PtrData = *ptrPosition;
          ptrCert->PtrCertElement[elementIndex].PtrElement = \
            ptrSubjectPublicKey;
          /* Move position to the next element */
          *ptrPosition = &(*ptrPosition)[length];
        }
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_725 */
        retVal = KEYM_E_INVALID_PUBLIC_KEY;
      }
    }
  } /* @if (KEYM_E_OK == retVal) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetCertSerial                             **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get serial element in a certificate                   **
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
**                      KeyM_Asn1GetTag, KeyM_PrvCheckCertificateElement      **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCertSerial(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert)
{
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrSerialNumber;
  uint16 length;
  uint8 tag;
  uint16 retVal;
  uint16 elementIndex;

  length = 0U;
  tag = KEYM_ASN1_INTEGER;
  ptrSerialNumber = ptrParsedCert->PtrSerialNumber;
  /* @Trace: KeyM_SUD_FUNC_706 */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);

  if (KEYM_E_OK == retVal)
  {
    if (NULL_PTR != ptrSerialNumber)
    {
      /* @Trace: KeyM_SUD_FUNC_708 */
      elementIndex = ptrSerialNumber->ElementIndex;
      /* Check the certificate element of serial number */
      retVal = KeyM_PrvCheckCertificateElement(ptrCert, elementIndex, tag,\
        NULL_PTR, 0u);

      if (KEYM_E_OK == retVal)
      {
        /* Update the SerialNumber tag, length, data */
        ptrSerialNumber->Element.Tag = tag;
        ptrSerialNumber->Element.Length = length;
        ptrSerialNumber->Element.PtrData = *ptrPosition;
        ptrCert->PtrCertElement[elementIndex].PtrElement = ptrSerialNumber;
        *ptrPosition = &((*ptrPosition)[length]);
      }
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_707 */
      retVal = KEYM_E_INVALID_SERIAL;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetCertValidity                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get validity time element in a certificate            **
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
**                      KeyM_Asn1GetTag, KeyM_PrvX509GetValidTime             **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static uint16 KeyM_PrvX509GetCertValidity(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrEnd, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert)
{

  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrDateEnd;
  uint16 retVal;
  uint16 length;
  uint8 tag;
  uint64 validTime;

  /* Initialize variables */
  length = 0U;
  tag = KEYM_ASN1_PC_CONSTRUCTED | KEYM_ASN1_SEQUENCE;
  /* @Trace: KeyM_SUD_FUNC_709 */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEnd, &length, tag);
  if (KEYM_E_OK == retVal)
  {
    validTime = 0u;
    /* Update the end position of validity */
    ptrDateEnd = &(*ptrPosition)[length];
    /* Get not before time */
    retVal = KeyM_PrvX509GetValidTime(ptrPosition, ptrDateEnd, ptrCert, \
      ptrParsedCert->PtrRawNotBefore, &validTime);
    /* @Trace: KeyM_SUD_FUNC_710 */
    if (KEYM_E_OK == retVal)
    {
      ptrParsedCert->NotBefore = validTime;
      validTime = 0u;
      /* Get not after time */
      retVal = KeyM_PrvX509GetValidTime(ptrPosition, ptrDateEnd, ptrCert, \
        ptrParsedCert->PtrRawNotAfter, &validTime);
      /* @Trace: KeyM_SUD_FUNC_711 */
      if (KEYM_E_OK == retVal)
      {
        ptrParsedCert->NotAfter = validTime;
        if (*ptrPosition != ptrDateEnd)
        {
          retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
        }
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509CertCheckParent                           **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Check certificate is parent(upper certificate)        **
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
**                      KeyM_PrvX509NameCmp                                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint16, KEYM_CODE) KeyM_PrvX509CertCheckParent(\
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrChild, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParent)
{
  uint16 retVal;

  /* @Trace: KeyM_SUD_FUNC_667 */
  /* Support universal cert configuration */
  retVal = KeyM_PrvX509NameCmp(ptrChild->PtrIssuer,
                               ptrParent->PtrSubject, 
                               ptrChild->IssuerNum, 
                               ptrParent->SubjectNum);

  if (KEYM_E_OK != retVal)
  {
    retVal = KEYM_E_BADCERT_NAME_MISMATCH;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509CertStorePublicKey                        **
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
**                      Csm_KeyElementSet, Csm_KeySetValid                    **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509CertStorePublicKey(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrt)
{
  Std_ReturnType retVal;
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKey;
  uint16 publicKeyLength;

  /* @Trace: KeyM_SUD_FUNC_731 */
  if ((KEYM_PK_EC == ptrParsedCrt->PublicKeyType) || \
      (KEYM_PK_ECDH == ptrParsedCrt->PublicKeyType))
  {
    /* For Ecc public key, the first byte is prefix byte, so the
      actual public key data starts from the second byte */
    ptrPublicKey = &(ptrParsedCrt->PtrSubjectPublicKey->Element.PtrData[1u]);
    publicKeyLength = ptrParsedCrt->PtrSubjectPublicKey->Element.Length - 1u;
  }
  else
  {
    /* For other key types as RSA */
    ptrPublicKey = ptrParsedCrt->PtrSubjectPublicKey->Element.PtrData;
    publicKeyLength = ptrParsedCrt->PtrSubjectPublicKey->Element.Length;
  }

  retVal = Csm_KeyElementSet(ptrCert->CsmSignVerifyKeyId, \
    KEYM_KEY_ELEMENT1_ID, \
    ptrPublicKey, \
    publicKeyLength);

  if (KEYM_E_OK == retVal)
  {
    /* Validate the public key */
    retVal = Csm_KeySetValid(ptrCert->CsmSignVerifyKeyId);
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509CertificatePairVerify                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Verify a X509 certificate pair                        **
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
**                      KeyM_PrvX509CertCheckParent, Csm_SignatureVerify,     **
**                      KeyM_PrvX509CertStorePublicKey,                       **
**                      KeyM_PrvX509ConvertEccSignatureValue,                 **
**                      KeyM_PrvPartOfX509CertificatePairVerify               **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, KEYM_CODE) KeyM_PrvX509CertificatePairVerify(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrUpperCert)
{
  const KeyM_X509CertificateType *ptrParsedCrt;
  const KeyM_X509CertificateType *ptrParsedUpperCert;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSignValue;
  Crypto_VerifyResultType verifyResult;
  uint16 retVal;
  KeyM_CertificateStatusType certStatus;
  uint8 signValue[KEYM_ECC_SIGNATURE_VALUE_MAX_LENGTH];
  uint16 signLength;

  /* Initialize variables */
  verifyResult = CRYPTO_E_VER_NOT_OK;
  certStatus = ptrCert->CertStatus;
  ptrParsedCrt = (KeyM_X509CertificateType*)(ptrCert->PtrParsedCert);
  ptrParsedUpperCert = (KeyM_X509CertificateType*)(ptrUpperCert->PtrParsedCert);
  /* @Trace: KeyM_SUD_FUNC_669 */
  /* Check the upper certificate has subject name is the same issuer name of the
    current certificate */
  retVal = KeyM_PrvX509CertCheckParent(ptrParsedCrt, ptrParsedUpperCert);

  if (KEYM_E_OK != retVal)
  {
    certStatus = KEYM_E_CERTIFICATE_INVALID_CHAIN_OF_TRUST;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_670 */
    if ((KEYM_TRUE == ptrCert->IsRoot) && \
      (KEYM_CERTIFICATE_VALID != certStatus))
    {
      retVal = KeyM_PrvX509CertStorePublicKey(ptrCert, ptrParsedCrt);
    }

    if (KEYM_E_OK != retVal)
    {
      certStatus = KEYM_CERTIFICATE_INVALID;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_672 */
      if ((KEYM_PK_ECDSA_SHA1 <= ptrParsedCrt->SignAlgType) && \
        (KEYM_PK_ECDSA_SHA512 >= ptrParsedCrt->SignAlgType))
      {
        /* Convert ECC signature value */
        signLength = KEYM_ECC_SIGNATURE_VALUE_MAX_LENGTH;
        
        KeyM_PrvX509ConvertEccSignatureValue(\
        ptrParsedCrt->PtrSignatureValue->Element.PtrData, \
        ptrParsedCrt->PtrSignatureValue->Element.Length,\
        &signValue[0u], &signLength);

        ptrSignValue = &signValue[0u];
      }
      else
      {
        ptrSignValue = ptrParsedCrt->PtrSignatureValue->Element.PtrData;
        signLength = ptrParsedCrt->PtrSignatureValue->Element.Length;
      }

      /* Check if current cert is correctly signed by the upper cert */
      retVal = Csm_SignatureVerify(ptrUpperCert->CsmSignVerifyJob.CsmJobId, \
        CRYPTO_OPERATIONMODE_SINGLECALL, \
        ptrParsedCrt->TBSCert.PtrData, \
        ptrParsedCrt->TBSCert.Length, \
        ptrSignValue, signLength,\
        &verifyResult);
      /* @Trace: KeyM_SUD_FUNC_673 */
      if (KEYM_E_OK != retVal)
      {
        certStatus = KEYM_CERTIFICATE_INVALID;
      }
      else if (CRYPTO_E_VER_OK != verifyResult)
      {
        certStatus = KEYM_E_CERTIFICATE_SIGNATURE_FAIL;
      }
      else
      {
        certStatus = KeyM_PrvPartOfX509CertificatePairVerify(ptrCert, \
          ptrParsedCrt);
      } /* @if (KEYM_E_OK != retVal) */
    } /* @if (KEYM_E_OK != retVal) */
  } /* @if (KEYM_E_OK != retVal) */
  ptrCert->CertStatus = certStatus;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvPartOfX509CertificatePairVerify               **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvX509CertificatePairVerify,  **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvX509CertificatePairVerify                     **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCert                                               **
**                                                                            **
** InOut Parameters   : ptrParsedCrt                                          **
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
**                      KeyM_PrvElementRuleVerify, KeyM_PrvCheckCertRevoked   **
**                      KeyM_PrvX509CertStorePublicKey                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static KeyM_CertificateStatusType KeyM_PrvPartOfX509CertificatePairVerify(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCrt)
{
  uint64 currentTime;
  uint16 retVal;
  KeyM_CertificateStatusType crtStatus;
  #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSerialNumber;
  uint16 serialLength;
  #endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
  currentTime = 0U;
  crtStatus = ptrCert->CertStatus;
  /* @Trace: KeyM_SUD_FUNC_990 */
  /* Get the current time */
  #if (KEYM_USE_STBM == STD_ON)
  retVal = KeyM_PrvGetCurrentTime(ptrCert->CertTimebaseId, &currentTime);
  #else
  retVal = KEYM_USER_GET_CURRENT_TIME(&currentTime);
  #endif

  if (KEYM_E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_734 */
    #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
    ptrSerialNumber = ptrParsedCrt->PtrSerialNumber->Element.PtrData;
    serialLength = ptrParsedCrt->PtrSerialNumber->Element.Length;
    /* Check whether the certificate is revoked */
    retVal = KeyM_PrvCheckCertRevoked(ptrSerialNumber, \
      serialLength, currentTime);

    if (KEYM_E_BADCERT_REVOKED == retVal)
    {
      /* @Trace: KeyM_SUD_FUNC_735 */
      crtStatus = KEYM_E_CERTIFICATE_REVOKED;
    }
    else
    #endif /* (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */
    {
      /* Check for validity of the certificate */
      if ((ptrParsedCrt->NotBefore > currentTime) || \
        (ptrParsedCrt->NotAfter < currentTime))
      {
        /* @Trace: KeyM_SUD_FUNC_736 */
        crtStatus = KEYM_E_CERTIFICATE_VALIDITY_PERIOD_FAIL;
      }
      else
      {
        /* @Trace: KeyM_SUD_FUNC_737 */
        #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON)
        /* Verify element according to element verification rule */
        retVal = KeyM_PrvElementRuleVerify(ptrCert);

        if (KEYM_E_OK != retVal)
        {
          crtStatus = KEYM_E_CERTIFICATE_INVALID_CONTENT;
        }
        else
        #endif /* #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON) */
        {
          if (KEYM_CERTIFICATE_VALID != crtStatus)
          {
            crtStatus = KEYM_CERTIFICATE_VALID;
            /* Store the public key of the certificate to CSM, except the root.
             The public key of the root needs to be set and validated
             in KeyMCertCsmSignatureVerifyKeyRef beforehand */
            if (KEYM_TRUE != ptrCert->IsRoot)
            {
              /* @Trace: KeyM_SUD_FUNC_738 */
              retVal = KeyM_PrvX509CertStorePublicKey(ptrCert, ptrParsedCrt);

              if (KEYM_E_OK != retVal)
              {
                crtStatus = KEYM_CERTIFICATE_INVALID;
              }
              else
              {
                crtStatus = KEYM_CERTIFICATE_VALID;
              }
            } /* @if (KEYM_TRUE != ptrCert->IsRoot) */
          } /* @if (KEYM_CERTIFICATE_VALID != ptrCert->CertStatus) */
        } /* @if (KEYM_E_OK != retVal) */
      } /* @if ((ptrParsedCrt->NotBefore > currentTime) || \
          (ptrParsedCrt->NotAfter < currentTime)) */
    } /* @if (KEYM_E_BADCERT_REVOKED == retVal) */
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_733 */
    crtStatus = KEYM_CERTIFICATE_INVALID;
  } /* @if (E_OK == retVal) */

  return crtStatus;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvCopyParsedX509Certificate                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Copy parsed X509 certificate                          **
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
FUNC(void, KEYM_CODE) KeyM_PrvCopyParsedX509Certificate(\
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrSrcCert, \
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrDesCert)
{
  uint8 indexCnt;
  P2CONST(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrSrcElement;
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrDesElement;
  /* @Trace: KeyM_SUD_FUNC_675 */
  /* Copy certificate body */
  ptrDesCert->TBSCert.PtrData = ptrSrcCert->TBSCert.PtrData;
  ptrDesCert->TBSCert.Length = ptrSrcCert->TBSCert.Length;
  /* Copy RawVersion */
  ptrDesElement = ptrDesCert->PtrRawVersion;
  ptrSrcElement = ptrSrcCert->PtrRawVersion;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy SerialNumber */
  ptrDesElement = ptrDesCert->PtrSerialNumber;
  ptrSrcElement = ptrSrcCert->PtrSerialNumber;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy RawSignature */
  ptrDesElement = ptrDesCert->PtrRawSignature;
  ptrSrcElement = ptrSrcCert->PtrRawSignature;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy RawNotBefore */
  ptrDesElement = ptrDesCert->PtrRawNotBefore;
  ptrSrcElement = ptrSrcCert->PtrRawNotBefore;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy RawNotAfter */
  ptrDesElement = ptrDesCert->PtrRawNotAfter;
  ptrSrcElement = ptrSrcCert->PtrRawNotAfter;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy PublicKeyAlgorithm */
  ptrDesElement = ptrDesCert->PtrPublicKeyAlgorithm;
  ptrSrcElement = ptrSrcCert->PtrPublicKeyAlgorithm;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy SubjectPublicKey */
  ptrDesElement = ptrDesCert->PtrSubjectPublicKey;
  ptrSrcElement = ptrSrcCert->PtrSubjectPublicKey;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy IssuerUniqueID */
  ptrDesElement = ptrDesCert->PtrIssuerUniqueID;
  ptrSrcElement = ptrSrcCert->PtrIssuerUniqueID;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy SubjectUniqueID */
  ptrDesElement = ptrDesCert->PtrSubjectUniqueID;
  ptrSrcElement = ptrSrcCert->PtrSubjectUniqueID;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy SignatureAlgorithm */
  ptrDesElement = ptrDesCert->PtrSignatureAlgorithm;
  ptrSrcElement = ptrSrcCert->PtrSignatureAlgorithm;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  /* Copy SignatureValue */
  ptrDesElement = ptrDesCert->PtrSignatureValue;
  ptrSrcElement = ptrSrcCert->PtrSignatureValue;
  KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);

  ptrDesCert->NotBefore = ptrSrcCert->NotBefore;
  ptrDesCert->NotAfter = ptrSrcCert->NotAfter;
  ptrDesCert->PublicKeyType = ptrSrcCert->PublicKeyType;
  ptrDesCert->SignAlgType = ptrSrcCert->SignAlgType;
  ptrDesCert->IssuerNum = ptrSrcCert->IssuerNum;
  ptrDesCert->SubjectNum = ptrSrcCert->SubjectNum;
  ptrDesCert->ExtensionNum = ptrSrcCert->ExtensionNum;

  /* Copy parsed Issuer */
  for (indexCnt = 0u; indexCnt < ptrDesCert->IssuerNum; indexCnt++)
  {
    ptrDesElement = &ptrDesCert->PtrIssuer[indexCnt];
    ptrSrcElement = &ptrSrcCert->PtrIssuer[indexCnt];
    KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  }
  /* @Trace: KeyM_SUD_FUNC_676 */
  /* Copy parsed Subject */
  for (indexCnt = 0u; indexCnt < ptrDesCert->SubjectNum; indexCnt++)
  {
    ptrDesElement = &ptrDesCert->PtrSubject[indexCnt];
    ptrSrcElement = &ptrSrcCert->PtrSubject[indexCnt];
    KeyM_PrvElementCopy(ptrSrcElement, ptrDesElement);
  }
  /* @Trace: KeyM_SUD_FUNC_677 */
  /* Copy Extensions */
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
** Function Name      : KeyM_PrvAdjustX509Certificate                         **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Adjust parsed X509 certificate based on new address   **
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
FUNC(void, KEYM_CODE) KeyM_PrvAdjustX509Certificate(\
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrCurAddress, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrNewAddress)
{
  sint32 deltaAddress;
  uint8 indexCnt;

  deltaAddress = (sint32)(ptrNewAddress - ptrCurAddress);

  /* @Trace: KeyM_SUD_FUNC_678 */
  /* Adjust certificate body */
  ptrParsedCert->TBSCert.PtrData = \
    &(ptrParsedCert->TBSCert.PtrData)[deltaAddress];
  /* Adjust RawVersion */
  if (NULL_PTR != ptrParsedCert->PtrRawVersion)
  {
    ptrParsedCert->PtrRawVersion->Element.PtrData = \
      &(ptrParsedCert->PtrRawVersion->Element.PtrData)[deltaAddress];
  }

  /* Adjust SerialNumber */
  ptrParsedCert->PtrSerialNumber->Element.PtrData = \
    &(ptrParsedCert->PtrSerialNumber->Element.PtrData)[deltaAddress];
  /* Adjust RawSignature */
  ptrParsedCert->PtrRawSignature->Element.PtrData = \
    &(ptrParsedCert->PtrRawSignature->Element.PtrData)[deltaAddress];
  /* Adjust RawNotBefore */
  ptrParsedCert->PtrRawNotBefore->Element.PtrData = \
    &(ptrParsedCert->PtrRawNotBefore->Element.PtrData)[deltaAddress];
  /* Adjust RawNotAfter */
  ptrParsedCert->PtrRawNotAfter->Element.PtrData = \
    &(ptrParsedCert->PtrRawNotAfter->Element.PtrData)[deltaAddress];
  /* Adjust PublicKeyAlgorithm */
  ptrParsedCert->PtrPublicKeyAlgorithm->Element.PtrData = \
    &(ptrParsedCert->PtrPublicKeyAlgorithm->Element.PtrData)[deltaAddress];
  /* Adjust SubjectPublicKey */
  ptrParsedCert->PtrSubjectPublicKey->Element.PtrData = \
    &(ptrParsedCert->PtrSubjectPublicKey->Element.PtrData)[deltaAddress];

  if (NULL_PTR != ptrParsedCert->PtrIssuerUniqueID)
  {
    /* Adjust IssuerUniqueID */
    ptrParsedCert->PtrIssuerUniqueID->Element.PtrData = \
      &(ptrParsedCert->PtrIssuerUniqueID->Element.PtrData)[deltaAddress];
  }

  if (NULL_PTR != ptrParsedCert->PtrSubjectUniqueID)
  {
    /* Adjust SubjectUniqueID */
    ptrParsedCert->PtrSubjectUniqueID->Element.PtrData = \
      &(ptrParsedCert->PtrSubjectUniqueID->Element.PtrData)[deltaAddress];
  }

  /* Adjust SignatureAlgorithm */
  ptrParsedCert->PtrSignatureAlgorithm->Element.PtrData = \
    &(ptrParsedCert->PtrSignatureAlgorithm->Element.PtrData)[deltaAddress];
  /* Adjust SignatureValue */
  ptrParsedCert->PtrSignatureValue->Element.PtrData = \
    &(ptrParsedCert->PtrSignatureValue->Element.PtrData)[deltaAddress];

  /* @Trace: KeyM_SUD_FUNC_679 */
  /* Adjust parsed Issuer */
  for (indexCnt = 0u; indexCnt < ptrParsedCert->IssuerNum; indexCnt++)
  {
    ptrParsedCert->PtrIssuer[indexCnt].Element.PtrData = \
      &(ptrParsedCert->PtrIssuer[indexCnt].Element.PtrData)[deltaAddress];
  }
  /* Adjust parsed Subject */
  for (indexCnt = 0u; indexCnt < ptrParsedCert->SubjectNum; indexCnt++)
  {
    ptrParsedCert->PtrSubject[indexCnt].Element.PtrData = \
      &(ptrParsedCert->PtrSubject[indexCnt].Element.PtrData)[deltaAddress];
  }

  /* Adjust Extensions */
  for (indexCnt = 0u; indexCnt < ptrParsedCert->ExtensionNum; indexCnt++)
  {
    ptrParsedCert->PtrExtensions[indexCnt].Element.PtrData = \
      &(ptrParsedCert->PtrExtensions[indexCnt].Element.PtrData)[deltaAddress];
  }
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvRecoverX509Certificate                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Recover parsed X509 certificate                       **
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
FUNC(void, KEYM_CODE) KeyM_PrvRecoverX509Certificate(\
  P2VAR(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert)
{
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert;
  P2VAR(KeyM_ElementType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedElement;
  uint8 indexCnt;
  uint16 elementIndex;
  ptrParsedCert = (KeyM_X509CertificateType*)ptrCert->PtrParsedCert;

  /* @Trace: KeyM_SUD_FUNC_683 */
  /* Recover RawVersion */
  if (NULL_PTR != ptrParsedCert->PtrRawVersion)
  {
    elementIndex = ptrParsedCert->PtrRawVersion->ElementIndex;
    ptrCert->PtrCertElement[elementIndex].PtrElement = \
    ptrParsedCert->PtrRawVersion;
  }
  /* Recover SerialNumber */
  elementIndex = ptrParsedCert->PtrSerialNumber->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrSerialNumber;
  /* Recover RawSignature */
  elementIndex = ptrParsedCert->PtrRawSignature->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrRawSignature;
  /* Recover RawNotBefore */
  elementIndex = ptrParsedCert->PtrRawNotBefore->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrRawNotBefore;
  /* Recover RawNotAfter */
  elementIndex = ptrParsedCert->PtrRawNotAfter->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrRawNotAfter;
  /* Recover PublicKeyAlgorithm */
  elementIndex = ptrParsedCert->PtrPublicKeyAlgorithm->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrPublicKeyAlgorithm;
  /* Recover SubjectPublicKey */
  elementIndex = ptrParsedCert->PtrSubjectPublicKey->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrSubjectPublicKey;
  /* Recover IssuerUniqueID */
  if (NULL_PTR != ptrParsedCert->PtrIssuerUniqueID)
  {
    elementIndex = ptrParsedCert->PtrIssuerUniqueID->ElementIndex;
    ptrCert->PtrCertElement[elementIndex].PtrElement = \
    ptrParsedCert->PtrIssuerUniqueID;
  }
  if (NULL_PTR != ptrParsedCert->PtrSubjectUniqueID)
  {
    /* Recover SubjectUniqueID */
    elementIndex = ptrParsedCert->PtrSubjectUniqueID->ElementIndex;
    ptrCert->PtrCertElement[elementIndex].PtrElement = \
    ptrParsedCert->PtrSubjectUniqueID;
  }
  /* Recover SignatureAlgorithm */
  elementIndex = ptrParsedCert->PtrSignatureAlgorithm->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrSignatureAlgorithm;
  /* Recover SignatureValue */
  elementIndex = ptrParsedCert->PtrSignatureValue->ElementIndex;
  ptrCert->PtrCertElement[elementIndex].PtrElement = \
  ptrParsedCert->PtrSignatureValue;
  /* @Trace: KeyM_SUD_FUNC_684 */
  /* Recover Issuer  */
  for (indexCnt = 0u; indexCnt < ptrParsedCert->IssuerNum; indexCnt++)
  {
    ptrParsedElement = &ptrParsedCert->PtrIssuer[indexCnt];
    elementIndex = ptrParsedElement->ElementIndex;
    ptrCert->PtrCertElement[elementIndex].PtrElement = ptrParsedElement;
  }
  /* Recover Subject  */
  for (indexCnt = 0u; indexCnt < ptrParsedCert->SubjectNum; indexCnt++)
  {
    ptrParsedElement = &ptrParsedCert->PtrSubject[indexCnt];
    elementIndex = ptrParsedElement->ElementIndex;
    ptrCert->PtrCertElement[elementIndex].PtrElement = ptrParsedElement;
  }
  /* Recover Extensions */
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
** Function Name      : KeyM_PrvX509WriteSignatureValue                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write signature value element in certificate          **
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
**                      KeyM_PrvMemCopy, KeyM_Asn1WriteLength,                **
**                      KeyM_Asn1WriteTag                                     **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509WriteSignatureValue(\
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
  /* Add one byte which is used to contain
    the number of unused bits of BIT string*/
  length = signValLength + 1u;

  /* @Trace: KeyM_SUD_FUNC_742 */
  if (*ptrPosition < (&(ptrStart[length])))
  {
    retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
  }
  else
  {
    (*ptrPosition) -= signValLength;
    (void)KeyM_PrvMemCopy(ptrSignValue, *ptrPosition, signValLength);
    /* One byte is used to contain the number of unused bits of BIT string */
    (*ptrPosition)--;
    **ptrPosition = 0u;
    /* Write length of data */
    retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, length,\
      &bytesToStoreLen);
    /* @Trace: KeyM_SUD_FUNC_743 */
    if (E_OK == retVal)
    {
      length += bytesToStoreLen;
      tag = KEYM_ASN1_BIT_STRING;
      retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, tag, &bytesToStoreLen);

      if (E_OK == retVal)
      {
        /* @Trace: KeyM_SUD_FUNC_744 */
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
** Function Name      : KeyM_PrvX509WritePublicKeyValue                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write public key value element in certificate         **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrStart, ptrPublicKey, ptrCert                       **
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
**                      KeyM_PrvMemCopy, Csm_KeyElementGet,                   **
**                      KeyM_Asn1WriteLength, KeyM_Asn1WriteTag               **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvX509WritePublicKeyValue(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPublicKey, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  uint32 length;
  uint8 bytesToStoreLen;
  uint8 tag;

  /* @Trace: KeyM_SUD_FUNC_745 */
  bytesToStoreLen = 0u;
  length = KEYM_PUBLIC_KEY_VALUE_MAX_LENGTH;

  /* Get the public from CSM */
  retVal = Csm_KeyElementGet(ptrCert->CsmSignVerifyKeyId, \
    KEYM_KEY_ELEMENT1_ID, ptrPublicKey, &length);

  if (E_OK == retVal)
  {
    if (*ptrPosition < (&(ptrStart[length])))
    {
      /* @Trace: KeyM_SUD_FUNC_746 */
      retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_747 */
      (*ptrPosition) -= length;
      (void)KeyM_PrvMemCopy(ptrPublicKey, *ptrPosition, length);

      if (KEYM_CERT_ALGORITHM_ECC == ptrCert->CertAlgorithm)
      {
        /* Add one byte of 0x04 to indicate the public key format
           is uncompressed */
        (*ptrPosition)--;
        **ptrPosition = 0x04u;
        length++;
      }

      /* One byte of 0 is used to contain
        the number of unused bits of BIT string */
      (*ptrPosition)--;
      **ptrPosition = 0u;
      length++;

      /* Write length of data */
      retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, \
        (const uint16)length, &bytesToStoreLen);

      if (E_OK == retVal)
      {
        /* @Trace: KeyM_SUD_FUNC_748 */
        length += bytesToStoreLen;
        tag = KEYM_ASN1_BIT_STRING;
        retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, \
          tag, &bytesToStoreLen);

        if (E_OK == retVal)
        {
          /* @Trace: KeyM_SUD_FUNC_749 */
          length += bytesToStoreLen;
          *ptrLength += (uint16)length;
        }
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvX509CertificateGenerate                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Generate one X.509 certificate skeleton in DER format **
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
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvPartOneOfX509CertificateGenerate,             **
**                      KeyM_PrvPartTwoOfX509CertificateGenerate,             **
**                      KeyM_PrvPartThreeOfX509CertificateGenerate,           **
**                      Csm_SignatureGenerate, KeyM_Asn1WriteLength,          **
**                      KeyM_PrvX509WriteSignatureValue, KeyM_PrvMemCopy,     **
**                      KeyM_PrvX509WriteElement, KeyM_Asn1WriteTag           **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509CertificateGenerate(\
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrDataLength)
{
  Std_ReturnType retVal;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrPosition;
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrInputPosition;
  P2VAR(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert;
  uint16 length;
  uint16 subLength;
  uint8 buffer[KEYM_SIGNATURE_VALUE_MAX_LENGTH];
  uint32 bufferLength;
  uint8 bytesToStoreLen;
  uint8 tag;

  length = 0u;
  ptrStart = &KeyM_DataBuffer[0u];
  ptrPosition = &ptrStart[KEYM_INTERAL_BUFFER_LENGTH];
  ptrParsedCert = (KeyM_X509CertificateType*)ptrCert->PtrParsedCert;
  /* @Trace: KeyM_SUD_FUNC_689 */
  retVal = KeyM_PrvPartOneOfX509CertificateGenerate(&ptrPosition, ptrStart,\
    ptrCert, ptrParsedCert, &buffer[0u], &length);

  if (E_OK == retVal)
  {
    retVal = KeyM_PrvPartTwoOfX509CertificateGenerate(&ptrPosition, ptrStart,\
      ptrCert, ptrParsedCert, &length);
    /* @Trace: KeyM_SUD_FUNC_690 */
    if (E_OK == retVal)
    {
      retVal = KeyM_PrvPartThreeOfX509CertificateGenerate(&ptrPosition, \
        ptrStart, ptrCert, ptrParsedCert, &length);
      /* @Trace: KeyM_SUD_FUNC_691 */
      if (E_OK == retVal)
      {
        /* Make signature */
        bufferLength = KEYM_SIGNATURE_VALUE_MAX_LENGTH;
        retVal = Csm_SignatureGenerate(ptrCert->CsmSignGenerateJob.CsmJobId, \
          CRYPTO_OPERATIONMODE_SINGLECALL, ptrPosition, length, \
          &buffer[0u], &bufferLength);
        /* @Trace: KeyM_SUD_FUNC_692 */
        if (E_OK == retVal)
        {
          subLength = 0u;
          ptrInputPosition = &ptrData[*ptrDataLength];
          /* Write signature value */
          retVal = KeyM_PrvX509WriteSignatureValue(&ptrInputPosition, ptrData, \
            &buffer[0u], (const uint16)bufferLength, &subLength);
          /* @Trace: KeyM_SUD_FUNC_693 */
          if (E_OK == retVal)
          {
            /* Write signature algorithm */
            tag = KEYM_ASN1_SEQUENCE | KEYM_ASN1_PC_CONSTRUCTED;
            retVal = KeyM_PrvX509WriteElement(&ptrInputPosition, ptrData, \
              ptrCert, ptrParsedCert->PtrSignatureAlgorithm,\
              &subLength, tag);
            /* @Trace: KeyM_SUD_FUNC_694 */
            if (E_OK == retVal)
            {
              if ((&(ptrData[length])) > ptrInputPosition)
              {
                retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
              }
              else
              {
                ptrInputPosition -= length;
                (void)KeyM_PrvMemCopy(ptrPosition, ptrInputPosition, length);
                length += subLength;
                bytesToStoreLen = 0u;

                /* Write length of certificate */
                retVal = KeyM_Asn1WriteLength(&ptrInputPosition, \
                  ptrData, length, &bytesToStoreLen);
                /* @Trace: KeyM_SUD_FUNC_695 */
                if (E_OK == retVal)
                {
                  length += bytesToStoreLen;
                  /* Write tag of certificate */
                  retVal = KeyM_Asn1WriteTag(&ptrInputPosition, ptrData, \
                    tag, &bytesToStoreLen);
                  /* @Trace: KeyM_SUD_FUNC_696 */
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
** Function Name      : KeyM_PrvPartOneOfX509CertificateGenerate              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvX509CertificateGenerate,    **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvX509CertificateGenerate                       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrStart, ptrCert, ptrBuffer, ptrParsedCert           **
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
**                      KeyM_PrvX509WriteExtensions, KeyM_PrvX509WriteElement,**
**                      KeyM_PrvX509WritePublicKeyValue, KeyM_Asn1WriteTag,   **
**                      KeyM_PrvX509WriteSignatureValue,                      **
**                      KeyM_Asn1WriteLength,                                 **
**                      KeyM_PrvX509WriteIssuerSubject                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvPartOneOfX509CertificateGenerate(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrBuffer, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  uint16 subLength;
  uint8 bytesToStoreLen;
  uint8 tag;

  retVal = E_OK;
  /* @Trace: KeyM_SUD_FUNC_751 */
  if ((NULL_PTR != ptrParsedCert->PtrExtensions) && \
    (0u < ptrParsedCert->ExtensionNum))
  {
    retVal = KeyM_PrvX509WriteExtensions(ptrPosition, ptrStart, ptrCert,\
      ptrParsedCert->PtrExtensions, ptrParsedCert->ExtensionNum, \
      ptrLength, 3u);
  }

  if (E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_752 */
    /* Write SubjectUniqueID */
    if (NULL_PTR != ptrParsedCert->PtrSubjectUniqueID)
    {
      tag = (KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 2U);
      retVal = KeyM_PrvX509WriteElement(ptrPosition, ptrStart, ptrCert,\
        ptrParsedCert->PtrSubjectUniqueID, ptrLength, tag);
    }

    if (E_OK == retVal)
    {
      /* @Trace: KeyM_SUD_FUNC_753 */
      /* Write IssuerUniqueID */
      if (NULL_PTR != ptrParsedCert->PtrIssuerUniqueID)
      {
        tag = (KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | \
          KEYM_ASN1_PC_CONSTRUCTED | 1U);
        retVal = KeyM_PrvX509WriteElement(ptrPosition, ptrStart, ptrCert,\
          ptrParsedCert->PtrIssuerUniqueID, ptrLength, tag);
      }

      if (E_OK == retVal)
      {
        subLength = 0u;
        /* Write Subject public key value */
        retVal = KeyM_PrvX509WritePublicKeyValue(ptrPosition, ptrStart, \
          ptrCert, ptrBuffer, &subLength);
        /* @Trace: KeyM_SUD_FUNC_754 */
        if (E_OK == retVal)
        {
          /* Write Subject public key algorithm */
          tag = KEYM_ASN1_SEQUENCE | KEYM_ASN1_PC_CONSTRUCTED;
          retVal = KeyM_PrvX509WriteElement(ptrPosition, ptrStart, ptrCert,\
            ptrParsedCert->PtrPublicKeyAlgorithm, &subLength, tag);

          if (E_OK == retVal)
          {
            bytesToStoreLen = 0u;
            /* Write length of public key information */
            retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, subLength, \
              &bytesToStoreLen);
            /* @Trace: KeyM_SUD_FUNC_755 */
            if (E_OK == retVal)
            {
              /* Write tag of public key information */
              subLength += bytesToStoreLen;
              tag = KEYM_ASN1_SEQUENCE | KEYM_ASN1_PC_CONSTRUCTED;
              retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, tag, \
                &bytesToStoreLen);
              if (E_OK == retVal)
              {
                subLength += bytesToStoreLen;
                *ptrLength += subLength;
                /* Write Subject */
                retVal = KeyM_PrvX509WriteIssuerSubject(ptrPosition, ptrStart,\
                  ptrCert, ptrParsedCert->PtrSubject, \
                  ptrParsedCert->SubjectNum, ptrLength);
              }
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
** Function Name      : KeyM_PrvPartTwoOfX509CertificateGenerate              **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvX509CertificateGenerate,    **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvX509CertificateGenerate                       **
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
**                      KeyM_PrvX509WriteTime, KeyM_Asn1WriteLength,          **
**                      KeyM_Asn1WriteTag, KeyM_PrvX509WriteElement,          **
**                      KeyM_PrvX509WriteIssuerSubject                        **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvPartTwoOfX509CertificateGenerate(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  uint16 subLength;
  uint8 bytesToStoreLen;
  uint8 tag;

  /* @Trace: KeyM_SUD_FUNC_756 */
  subLength = 0u;
  /* Write Not after */
  retVal = KeyM_PrvX509WriteTime(ptrPosition, ptrStart, ptrCert,\
    ptrParsedCert->PtrRawNotAfter, &subLength);

  if (E_OK == retVal)
  {
    /* Write Not Before */
    retVal = KeyM_PrvX509WriteTime(ptrPosition, ptrStart, ptrCert,\
      ptrParsedCert->PtrRawNotBefore, &subLength);
    /* @Trace: KeyM_SUD_FUNC_757 */
    if (E_OK == retVal)
    {
      bytesToStoreLen = 0u;
      /* Write length of validity */
      retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, subLength, \
        &bytesToStoreLen);

      if (E_OK == retVal)
      {
        /* Write tag of validity */
        subLength += bytesToStoreLen;
        tag = KEYM_ASN1_SEQUENCE | KEYM_ASN1_PC_CONSTRUCTED;
        retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, \
          tag, &bytesToStoreLen);
        /* @Trace: KeyM_SUD_FUNC_758 */
        if (E_OK == retVal)
        {
          subLength += bytesToStoreLen;
          *ptrLength += subLength;
          /* Write Issuer */
          retVal = KeyM_PrvX509WriteIssuerSubject(ptrPosition, ptrStart, \
            ptrCert, ptrParsedCert->PtrIssuer, \
            ptrParsedCert->IssuerNum, ptrLength);

          if (E_OK == retVal)
          {
            /* Write signature algorithm */
            tag = KEYM_ASN1_SEQUENCE | KEYM_ASN1_PC_CONSTRUCTED;
            retVal = KeyM_PrvX509WriteElement(ptrPosition, ptrStart, ptrCert,\
              ptrParsedCert->PtrRawSignature,\
              ptrLength, tag);
            /* @Trace: KeyM_SUD_FUNC_759 */
            if (E_OK == retVal)
            {
              /* Write Serial */
              retVal = KeyM_PrvX509WriteElement(ptrPosition, ptrStart, \
                ptrCert, ptrParsedCert->PtrSerialNumber, ptrLength,\
                KEYM_ASN1_INTEGER);
            }
          }
        } /* @if (KEYM_E_OK == retVal) */
      } /* @if (KEYM_E_OK == retVal) */
    } /* @if (KEYM_E_OK == retVal) */
  } /* @if (KEYM_E_OK == retVal) */
  
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : KeyM_PrvPartThreeOfX509CertificateGenerate            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : This is a part of KeyM_PrvX509CertificateGenerate,    **
**                      this function is created to reduce code metric of     **
**                      KeyM_PrvX509CertificateGenerate                       **
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
** Return parameter   : uint16                                                **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1WriteLength,                                 **
**                      KeyM_Asn1WriteTag, KeyM_PrvX509WriteElement           **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
static Std_ReturnType KeyM_PrvPartThreeOfX509CertificateGenerate(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrStart, \
  P2CONST(KeyM_CertType, AUTOMATIC, KEYM_APPL_DATA) ptrCert, \
  P2CONST(KeyM_X509CertificateType, AUTOMATIC, KEYM_APPL_DATA) ptrParsedCert, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  uint16 subLength;
  uint8 bytesToStoreLen;
  uint16 length;
  uint8 tag;

  retVal = E_OK;
  /* @Trace: KeyM_SUD_FUNC_760 */
  /* Write Version */
  if (NULL_PTR != ptrParsedCert->PtrRawVersion)
  {
    subLength = 0u;
    retVal = KeyM_PrvX509WriteElement(ptrPosition, ptrStart, ptrCert,\
      ptrParsedCert->PtrRawVersion, &subLength,\
      KEYM_ASN1_INTEGER);
    if (E_OK == retVal)
    {
      bytesToStoreLen = 0u;
      retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, \
        subLength, &bytesToStoreLen);
      /* @Trace: KeyM_SUD_FUNC_761 */
      if (E_OK == retVal)
      {
        subLength += bytesToStoreLen;
        tag = KEYM_ASN1_CLASS_CONTEXT_SPECIFIC | KEYM_ASN1_PC_CONSTRUCTED | 0u;
        retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, \
          tag, &bytesToStoreLen);
        if (E_OK == retVal)
        {
          subLength += bytesToStoreLen;
        }
      }
    }
  }
  else
  {
    subLength = 0u;
  }

  if (E_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_762 */
    bytesToStoreLen = 0u;
    length = *ptrLength + subLength;
    /* Write length of TBS */
    retVal = KeyM_Asn1WriteLength(ptrPosition, ptrStart, \
      length, &bytesToStoreLen);

    if (E_OK == retVal)
    {
      /* @Trace: KeyM_SUD_FUNC_763 */
      length += bytesToStoreLen;
      /* Write tag of TBS */
      tag = KEYM_ASN1_SEQUENCE | KEYM_ASN1_PC_CONSTRUCTED;
      retVal = KeyM_Asn1WriteTag(ptrPosition, ptrStart, tag, &bytesToStoreLen);
      if (E_OK == retVal)
      {
        length += bytesToStoreLen;
        *ptrLength = length;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON) */
#endif /* #if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_OFF) */
#endif /* #if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */
#endif /* (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */
#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:11.5 CERT-C:EXP36-C */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
