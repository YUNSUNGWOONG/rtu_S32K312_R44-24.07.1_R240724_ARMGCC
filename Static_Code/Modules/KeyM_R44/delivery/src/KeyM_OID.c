/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_OID.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key manager internal source file for OID                      **
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
** 1.0.2     08-Nov-2021   TamTV6       Implement #20971                      **
** 1.0.3.0   20-May-2022   DienTC1      #22113                                **
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
** 1.0.7.0   07-Apr-2023   PhuocLH9     #CP44-1636,#CP44-1664                 **
** 1.0.8.0   31-Jul-2023   PhuocLH9     #CP44-2396,#CP44-2394                 **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM OID header file */
#include "KeyM_OID.h"
/* KeyM internal function prototype */
#include "KeyM_IntFunc.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/

#if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetCertExtensionType                      **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get the recognized extension type of certificate      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrObjectId, objectIdLength                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrExtType                                            **
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
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509GetCertExtensionType(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  const uint8 objectIdLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtType)
{
  Std_ReturnType retVal;
  uint8 indexCnt;
  /* KeyUsage extension OID */
  const uint8 keyUsageExtOid[KEYM_OID_THREE] = {KEYM_OID_KEY_USAGE};
  /* BasicConstraints extension OID */
  const uint8 basicConstraintsExtOid[KEYM_OID_THREE] = \
    {KEYM_OID_BASIC_CONSTRAINTS};
  /* Extended Key Usage extension OID */
  const uint8 extendedKeyUsageExtOid[KEYM_OID_THREE] = \
    {KEYM_OID_EXTENDED_KEY_USAGE};
  /* Subject Alternative extension OID */
  const uint8 subjectAltNameExtOid[KEYM_OID_THREE] = \
    {KEYM_OID_SUBJECT_ALT_NAME};
  /* Subject Key Identifier extension OID */
  const uint8 subjectKeyIdentExtOid[KEYM_OID_THREE] = \
    {KEYM_OID_SUBJECT_KEY_IDENTIFIER};
  /* Authority Key Identifier extension OID */
  const uint8 authorityKeyIdentExtOid[KEYM_OID_THREE] = \
    {KEYM_OID_AUTHORITY_KEY_IDENTIFIER};
  /* CRL Distribution Points extension OID */
  const uint8 crlDistributionPointsExtOid[KEYM_OID_THREE] = \
    {KEYM_OID_CRL_DISTRIBUTION_POINTS};
  /* Authority Info Access extension OID */
  const uint8 authorityInfoAccessExtOid[KEYM_OID_EIGHT] = \
    {KEYM_OID_AUTHORITY_INFO_ACCESS};
  /* The recognized extension OID array */
  KeyM_ObjectIdExtType objectIdExt[KEYM_OID_CERT_RECOGNIZED_EXT_NUMBER];
  KeyM_ObjectIdExtType * ptrObjectIdExt;

  ptrObjectIdExt = &objectIdExt[0u];
  ptrObjectIdExt->ObjectDes.PtrObjectID = &authorityKeyIdentExtOid[0u];
  ptrObjectIdExt->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdExt->ExtensionType = KEYM_X509_EXT_AUTHORITY_KEY_IDENTIFIER;

  ptrObjectIdExt = &objectIdExt[1u];
  ptrObjectIdExt->ObjectDes.PtrObjectID = &subjectKeyIdentExtOid[0u];
  ptrObjectIdExt->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdExt->ExtensionType = KEYM_X509_EXT_SUBJECT_KEY_IDENTIFIER;

  ptrObjectIdExt = &objectIdExt[2u];
  ptrObjectIdExt->ObjectDes.PtrObjectID = &keyUsageExtOid[0u];
  ptrObjectIdExt->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdExt->ExtensionType = KEYM_X509_EXT_KEY_USAGE;

  ptrObjectIdExt = &objectIdExt[3u];
  ptrObjectIdExt->ObjectDes.PtrObjectID = &basicConstraintsExtOid[0u];
  ptrObjectIdExt->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdExt->ExtensionType = KEYM_X509_EXT_BASIC_CONSTRAINTS;

  ptrObjectIdExt = &objectIdExt[4u];
  ptrObjectIdExt->ObjectDes.PtrObjectID = &extendedKeyUsageExtOid[0u];
  ptrObjectIdExt->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdExt->ExtensionType = KEYM_X509_EXT_EXTENDED_KEY_USAGE;

  ptrObjectIdExt = &objectIdExt[5u];
  ptrObjectIdExt->ObjectDes.PtrObjectID = &subjectAltNameExtOid[0u];
  ptrObjectIdExt->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdExt->ExtensionType = KEYM_X509_EXT_SUBJECT_ALT_NAME;

  ptrObjectIdExt = &objectIdExt[6u];
  ptrObjectIdExt->ObjectDes.PtrObjectID = &crlDistributionPointsExtOid[0u];
  ptrObjectIdExt->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdExt->ExtensionType = KEYM_X509_EXT_CRL_DISTRIBUTION_POINTS;

  ptrObjectIdExt = &objectIdExt[7u];
  ptrObjectIdExt->ObjectDes.PtrObjectID = &authorityInfoAccessExtOid[0u];
  ptrObjectIdExt->ObjectDes.ObjectLen = KEYM_OID_EIGHT;
  ptrObjectIdExt->ExtensionType = KEYM_X509_EXT_AUTHORITY_INFO_ACCESS;

  retVal = E_NOT_OK;

  /* @Trace: KeyM_SUD_FUNC_434 */
  for (indexCnt = 0U; KEYM_OID_CERT_RECOGNIZED_EXT_NUMBER > indexCnt; indexCnt++)
  {
    ptrObjectIdExt = &objectIdExt[indexCnt];
    if (objectIdLength == ptrObjectIdExt->ObjectDes.ObjectLen)
    {
      retVal = KeyM_PrvMemCmp(\
        (const void*)(&(ptrObjectIdExt->ObjectDes.PtrObjectID[0u])), \
        (const void*)ptrObjectId, objectIdLength);
      if (E_OK == retVal)
      {
        *ptrExtType = ptrObjectIdExt->ExtensionType;
        break;
      }
    }
  }

  /* If Extension OID is unmatched, set to UNKOWN type */
  if (E_NOT_OK == retVal)
  {
    /* @Trace: KeyM_SUD_FUNC_1434 */
    *ptrExtType = KEYM_X509_EXT_UNKNOWN;
    retVal = E_OK;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_PrvX509GetPublicKeyType                          **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get the public key algorithm type of X509 certiticate **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrObjectId, objectIdLength                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrKeyType                                            **
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
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509GetPublicKeyType(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  const uint8 objectIdLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrKeyType)
{
  Std_ReturnType retVal;
  uint8 indexCnt;
  uint8 indexData;
  /* Public key OID */
  const uint8 ecGenericOid[KEYM_OID_SEVEN] = {KEYM_OID_EC_ALG_UNRESTRICTED};
  const uint8 ecdhOid[KEYM_OID_FIVE] = {KEYM_OID_EC_ALG_ECDH};
  const uint8 rsaEncryptionOid[KEYM_OID_NINE] = {KEYM_OID_PKCS1_RSA};
  const uint8 rsassaPssOid[KEYM_OID_NINE] = {KEYM_OID_RSASSA_PSS};

  const uint8 x25519Oid[KEYM_OID_THREE] = {KEYM_OID_EC_ALG_X25519};
  const uint8 x448Oid[KEYM_OID_THREE] = {KEYM_OID_EC_ALG_X448};
  const uint8 ed25519Oid[KEYM_OID_THREE] = {KEYM_OID_EC_ALG_ED25519};
  const uint8 ed448Oid[KEYM_OID_THREE] = {KEYM_OID_EC_ALG_ED448};

  /* The public key OID array */
  KeyM_ObjectIdKeyAlgorithmType objectIdPublicKey[KEYM_OID_PUBLIC_KEY_ALG_NUMBER];
  KeyM_ObjectIdKeyAlgorithmType * ptrObjectIdPublicKey;

  ptrObjectIdPublicKey = &objectIdPublicKey[0u];
  ptrObjectIdPublicKey->ObjectDes.PtrObjectID = &rsaEncryptionOid[0u];
  ptrObjectIdPublicKey->ObjectDes.ObjectLen = KEYM_OID_NINE;
  ptrObjectIdPublicKey->KeySignType = KEYM_PK_RSA;

  ptrObjectIdPublicKey = &objectIdPublicKey[1u];
  ptrObjectIdPublicKey->ObjectDes.PtrObjectID = &ecGenericOid[0u];
  ptrObjectIdPublicKey->ObjectDes.ObjectLen = KEYM_OID_SEVEN;
  ptrObjectIdPublicKey->KeySignType = KEYM_PK_EC;

  ptrObjectIdPublicKey = &objectIdPublicKey[2u];
  ptrObjectIdPublicKey->ObjectDes.PtrObjectID = &ecdhOid[0u];
  ptrObjectIdPublicKey->ObjectDes.ObjectLen = KEYM_OID_FIVE;
  ptrObjectIdPublicKey->KeySignType = KEYM_PK_ECDH;

  ptrObjectIdPublicKey = &objectIdPublicKey[3u];
  ptrObjectIdPublicKey->ObjectDes.PtrObjectID = &rsassaPssOid[0u];
  ptrObjectIdPublicKey->ObjectDes.ObjectLen = KEYM_OID_NINE;
  ptrObjectIdPublicKey->KeySignType = KEYM_PK_RSASSA_PSS;

  ptrObjectIdPublicKey = &objectIdPublicKey[4u];
  ptrObjectIdPublicKey->ObjectDes.PtrObjectID = &x25519Oid[0u];
  ptrObjectIdPublicKey->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdPublicKey->KeySignType = KEYM_PK_ECDH;

  ptrObjectIdPublicKey = &objectIdPublicKey[5u];
  ptrObjectIdPublicKey->ObjectDes.PtrObjectID = &x448Oid[0u];
  ptrObjectIdPublicKey->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdPublicKey->KeySignType = KEYM_PK_ECDH;  
 
  ptrObjectIdPublicKey = &objectIdPublicKey[6u];
  ptrObjectIdPublicKey->ObjectDes.PtrObjectID = &ed25519Oid[0u];
  ptrObjectIdPublicKey->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdPublicKey->KeySignType = KEYM_PK_EDDSA_25519; 

  ptrObjectIdPublicKey = &objectIdPublicKey[7u];
  ptrObjectIdPublicKey->ObjectDes.PtrObjectID = &ed448Oid[0u];
  ptrObjectIdPublicKey->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdPublicKey->KeySignType = KEYM_PK_EDDSA_448;   

  retVal = E_NOT_OK;
  /* @Trace: KeyM_SUD_FUNC_435 */
  for (indexCnt = 0U; KEYM_OID_PUBLIC_KEY_ALG_NUMBER > indexCnt; indexCnt++)
  {
    ptrObjectIdPublicKey = &objectIdPublicKey[indexCnt];
    if (objectIdLength == ptrObjectIdPublicKey->ObjectDes.ObjectLen)
    {
      for (indexData = 0U; indexData < objectIdLength; indexData++)
      {

        if (ptrObjectIdPublicKey->ObjectDes.PtrObjectID[indexData] != \
          ptrObjectId[indexData])

        {
          retVal = E_NOT_OK;
          break;
        }
        else
        {
          retVal = E_OK;
        }
      }

      if (E_OK == retVal)
      {
        *ptrKeyType = ptrObjectIdPublicKey->KeySignType;
        break;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */

#if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetCrlExtensionType                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get the recognized extension type of CRL              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrObjectId, objectIdLength                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrExtType                                            **
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
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509GetCrlExtensionType(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  const uint8 objectIdLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtType)
{
  Std_ReturnType retVal;
  uint8 index;

  /* Authority Key Identifier extension OID */
  const uint8 authorityKeyIdentExtOid[KEYM_OID_THREE] = \
    {KEYM_OID_AUTHORITY_KEY_IDENTIFIER};
  /* CRL number extension OID */
  const uint8 cRLNumberExtOid[KEYM_OID_THREE] = {KEYM_OID_CRL_NUMBER};
  /* CRL Issuing Distribution Point extension OID */
  const uint8 crlIssuingDisPointsExtOid[KEYM_OID_THREE] = \
    {KEYM_OID_ISSUING_DISTRIBUTION_POINT};
  /* The recognized extension OID array */
  KeyM_ObjectIdExtType objectIdExt[KEYM_OID_CRL_RECOGNIZED_EXT_NUMBER];
  KeyM_ObjectIdExtType * ptrObjectIdExt;

  ptrObjectIdExt = &objectIdExt[0u];
  ptrObjectIdExt->ObjectDes.PtrObjectID = &authorityKeyIdentExtOid[0u];
  ptrObjectIdExt->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdExt->ExtensionType = KEYM_X509_EXT_AUTHORITY_KEY_IDENTIFIER;

  ptrObjectIdExt = &objectIdExt[1u];
  ptrObjectIdExt->ObjectDes.PtrObjectID = &cRLNumberExtOid[0u];
  ptrObjectIdExt->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdExt->ExtensionType = KEYM_X509_EXT_CRL_NUMBER;

  ptrObjectIdExt = &objectIdExt[2u];
  ptrObjectIdExt->ObjectDes.PtrObjectID = &crlIssuingDisPointsExtOid[0u];
  ptrObjectIdExt->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdExt->ExtensionType = KEYM_X509_EXT_ISSUING_DISTRIBUTION_POINT;

  retVal = E_NOT_OK;
  /* @Trace: KeyM_SUD_FUNC_436 */
  for (index = 0U; KEYM_OID_CRL_RECOGNIZED_EXT_NUMBER > index; index++)
  {
    ptrObjectIdExt = &objectIdExt[index];
    if (objectIdLength == ptrObjectIdExt->ObjectDes.ObjectLen)
    {
      retVal = KeyM_PrvMemCmp(\
        (const void*)(&(ptrObjectIdExt->ObjectDes.PtrObjectID[0u])), \
        (const void*)ptrObjectId, objectIdLength);
      if (E_OK == retVal)
      {
        *ptrExtType = ptrObjectIdExt->ExtensionType;
        break;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */

#if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
  (KEYM_CERT_X509_CRL_ENABLED == STD_ON))
/*******************************************************************************
** Function Name      : KeyM_PrvX509GetSignatureAlgType                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get the signature algorithm type of X509 certificate  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrObjectId, objectIdLength                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrSigAlgType                                         **
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
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509GetSignatureAlgType(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  const uint8 objectIdLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSigAlgType)
{
  Std_ReturnType retVal;
  uint8 indexCnt;
  uint8 indexData;
  /* ECC signature algorithm OID */
  const uint8 ecdsaWithSha1Oid[KEYM_OID_SEVEN] = {KEYM_OID_ECDSA_SHA1};
  const uint8 ecdsaWithSha224Oid[KEYM_OID_EIGHT] = {KEYM_OID_ECDSA_SHA224};
  const uint8 ecdsaWithSha256Oid[KEYM_OID_EIGHT] = {KEYM_OID_ECDSA_SHA256};
  const uint8 ecdsaWithSha384Oid[KEYM_OID_EIGHT] = {KEYM_OID_ECDSA_SHA384};
  const uint8 ecdsaWithSha512Oid[KEYM_OID_EIGHT] = {KEYM_OID_ECDSA_SHA512};
  /* RSA signature algorithm OID */
  const uint8 rsassaPssOid[KEYM_OID_NINE] = {KEYM_OID_RSASSA_PSS};
  const uint8 sha1WithRSAEncrypOid[KEYM_OID_NINE] = {KEYM_OID_PKCS1_SHA1};
  const uint8 sha224WithRSAEncrypOid[KEYM_OID_NINE] = {KEYM_OID_PKCS1_SHA224};
  const uint8 sha256WithRSAEncrypOid[KEYM_OID_NINE] = {KEYM_OID_PKCS1_SHA256};
  const uint8 sha384WithRSAEncrypOid[KEYM_OID_NINE] = {KEYM_OID_PKCS1_SHA384};
  const uint8 sha512WithRSAEncrypOid[KEYM_OID_NINE] = {KEYM_OID_PKCS1_SHA512};

  /*448 and 25519 algorithm OID*/
  const uint8 ed25519Oid[KEYM_OID_THREE] = {KEYM_OID_EC_ALG_ED25519};
  const uint8 ed448Oid[KEYM_OID_THREE] = {KEYM_OID_EC_ALG_ED448};



  /* The signature algorithm OID array */
  KeyM_ObjectIdKeyAlgorithmType objectIdSignatureAlg[KEYM_OID_SIGNATURE_ALG_NUMBER];
  KeyM_ObjectIdKeyAlgorithmType * ptrObjectIdSignatureAlg;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[0u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ecdsaWithSha1Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_SEVEN;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_ECDSA_SHA1;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[1u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ecdsaWithSha224Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_EIGHT;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_ECDSA_SHA224;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[2u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ecdsaWithSha256Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_EIGHT;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_ECDSA_SHA256;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[3u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ecdsaWithSha384Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_EIGHT;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_ECDSA_SHA384;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[4u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ecdsaWithSha512Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_EIGHT;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_ECDSA_SHA512;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[5u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &rsassaPssOid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_NINE;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_RSASSA_PSS;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[6u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &sha1WithRSAEncrypOid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_NINE;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_RSA_SHA1;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[7u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &sha224WithRSAEncrypOid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_NINE;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_RSA_SHA224;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[8u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &sha256WithRSAEncrypOid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_NINE;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_RSA_SHA256;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[9u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &sha384WithRSAEncrypOid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_NINE;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_RSA_SHA384;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[10u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &sha512WithRSAEncrypOid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_NINE;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_RSA_SHA512;

 /*448 and 25519 array OID*/
  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[11u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ed25519Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_EDDSA_25519; 

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[12u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ed448Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_EDDSA_448;   

  retVal = E_NOT_OK;
  /* @Trace: KeyM_SUD_FUNC_437 */
  for (indexCnt = 0U; KEYM_OID_SIGNATURE_ALG_NUMBER > indexCnt; indexCnt++)
  {
    ptrObjectIdSignatureAlg = &objectIdSignatureAlg[indexCnt];
    if (objectIdLength == ptrObjectIdSignatureAlg->ObjectDes.ObjectLen)
    {
      for (indexData = 0U; indexData < objectIdLength; indexData++)
      {
        if (ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID[indexData] != \
          ptrObjectId[indexData])

        {
          retVal = E_NOT_OK;
          break;
        }
        else
        {
          retVal = E_OK;
        }
      }

      if (E_OK == retVal)
      {
        *ptrSigAlgType = ptrObjectIdSignatureAlg->KeySignType;
        break;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
  (KEYM_CERT_X509_CRL_ENABLED == STD_ON)) */

#if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
/*******************************************************************************
** Function Name      : KeyM_PrvCvcGetSignatureAlgType                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get the CVC signature algorithm type                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrObjectId, objectIdLength                           **
**                                                                            **
** InOut Parameters   : None                                                  **
**                                                                            **
** Output Parameters  : ptrSigAlgType                                         **
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
FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcGetSignatureAlgType(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  const uint8 objectIdLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSigAlgType)
{
  Std_ReturnType retVal;
  uint8 indexCnt;
  uint8 indexData;
  /* ECC signature algorithm OID */
  const uint8 ecdsaSha1Oid[KEYM_OID_TEN] = {KEYM_OID_ID_TA_ECDSA_SHA1};
  const uint8 ecdsaSha224Oid[KEYM_OID_TEN] = {KEYM_OID_ID_TA_ECDSA_SHA224};
  const uint8 ecdsaSha256Oid[KEYM_OID_TEN] = {KEYM_OID_ID_TA_ECDSA_SHA256};
  const uint8 ecdsaSha384Oid[KEYM_OID_TEN] = {KEYM_OID_ID_TA_ECDSA_SHA384};
  const uint8 ecdsaSha512Oid[KEYM_OID_TEN] = {KEYM_OID_ID_TA_ECDSA_SHA512};
  /* RSA signature algorithm OID */
  const uint8 rsaSha1Oid[KEYM_OID_TEN] = {KEYM_OID_ID_TA_RSA_V1_5_SHA1};
  const uint8 rsaSha256Oid[KEYM_OID_TEN] = {KEYM_OID_ID_TA_RSA_V1_5_SHA256};
  const uint8 rsaPssSha1Oid[KEYM_OID_TEN] = {KEYM_OID_ID_TA_RSA_PSS_SHA1};
  const uint8 rsaPssSha256Oid[KEYM_OID_TEN] = {KEYM_OID_ID_TA_RSA_PSS_SHA256};
  const uint8 rsaSha512Oid[KEYM_OID_TEN] = {KEYM_OID_ID_TA_RSA_V1_5_SHA512};
  const uint8 rsaPssSha512Oid[KEYM_OID_TEN] = {KEYM_OID_ID_TA_RSA_PSS_SHA512};
  
  /*448 and 25519 algorithm OID*/
  const uint8 ed25519Oid[KEYM_OID_THREE] = {KEYM_OID_EC_ALG_ED25519};
  const uint8 ed448Oid[KEYM_OID_THREE] = {KEYM_OID_EC_ALG_ED448};

  /* The signature algorithm OID array */
  KeyM_ObjectIdKeyAlgorithmType objectIdSignatureAlg[KEYM_OID_SIGNATURE_ALG_NUMBER];
  KeyM_ObjectIdKeyAlgorithmType * ptrObjectIdSignatureAlg;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[0u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ecdsaSha1Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_TEN;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_ECDSA_SHA1;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[1u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ecdsaSha224Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_TEN;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_ECDSA_SHA224;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[2u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ecdsaSha256Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_TEN;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_ECDSA_SHA256;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[3u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ecdsaSha384Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_TEN;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_ECDSA_SHA384;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[4u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ecdsaSha512Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_TEN;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_ECDSA_SHA512;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[5u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &rsaSha1Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_TEN;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_RSA_SHA1;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[6u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &rsaSha256Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_TEN;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_RSA_SHA256;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[7u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &rsaPssSha1Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_TEN;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_RSASSA_PSS;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[8u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &rsaPssSha256Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_TEN;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_RSASSA_PSS;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[9u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &rsaSha512Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_TEN;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_RSA_SHA512;

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[10u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &rsaPssSha512Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_TEN;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_RSASSA_PSS;

 /*448 and 25519 array OID*/
  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[11u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ed25519Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_EDDSA_25519; 

  ptrObjectIdSignatureAlg = &objectIdSignatureAlg[12u];
  ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID = &ed448Oid[0u];
  ptrObjectIdSignatureAlg->ObjectDes.ObjectLen = KEYM_OID_THREE;
  ptrObjectIdSignatureAlg->KeySignType = KEYM_PK_EDDSA_448;   

  retVal = E_NOT_OK;
  /* @Trace: KeyM_SUD_FUNC_438 */
  for (indexCnt = 0U; KEYM_OID_SIGNATURE_ALG_NUMBER > indexCnt; indexCnt++)
  {
    ptrObjectIdSignatureAlg = &objectIdSignatureAlg[indexCnt];
    if (objectIdLength == ptrObjectIdSignatureAlg->ObjectDes.ObjectLen)
    {
      for (indexData = 0U; indexData < objectIdLength; indexData++)
      {
        if (ptrObjectIdSignatureAlg->ObjectDes.PtrObjectID[indexData] != \
          ptrObjectId[indexData])
        {
          retVal = E_NOT_OK;
          break;
        }
        else
        {
          retVal = E_OK;
        }
      }

      if (E_OK == retVal)
      {
        *ptrSigAlgType = ptrObjectIdSignatureAlg->KeySignType;
        break;
      }
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON) */
#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
