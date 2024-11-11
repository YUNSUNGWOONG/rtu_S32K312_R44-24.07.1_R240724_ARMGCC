/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_OID.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key manager internal header file for OID                      **
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
*******************************************************************************/
#ifndef KEYM_OID_H
#define KEYM_OID_H

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
/* @Trace: KeyM_SUD_MACRO_006 */
/* Top level OID tuples */
/* iso(1) member-body(2) */
#define KEYM_OID_ISO_MEMBER_BODIES     0x2Au
/* iso(1) identified-organization(3) */
#define KEYM_OID_ISO_IDENTIFIED_ORG    0x2Bu
/* joint-iso-ccitt(2) ds(5) */
#define KEYM_OID_ISO_CCITT_DS          0x55u
/* joint-iso-itu-t(2) country(16) */
#define KEYM_OID_ISO_ITU_COUNTRY       0x60u

/* ISO Member bodies OID parts */
/* us(840) */
#define KEYM_OID_COUNTRY_US                  0x86u, 0x48u
/* rsadsi(113549) */
#define KEYM_OID_ORG_RSA_DATA_SECURITY       0x86u, 0xF7u, 0x0Du
/* iso(1) member-body(2) us(840) rsadsi(113549) */
#define KEYM_OID_RSA_COMPANY                 KEYM_OID_ISO_MEMBER_BODIES,\
                                             KEYM_OID_COUNTRY_US,\
                                             KEYM_OID_ORG_RSA_DATA_SECURITY
/* ansi-X9-42(10046) */
#define KEYM_OID_ORG_ANSI_X9_42              0xCEu, 0x3Eu
#define KEYM_OID_ANSI_X9_42                  KEYM_OID_ISO_MEMBER_BODIES,\
                                             KEYM_OID_COUNTRY_US,\
                                             KEYM_OID_ORG_ANSI_X9_42
/* ansi-X9-62(10045) */
#define KEYM_OID_ORG_ANSI_X9_62              0xCEu, 0x3Du
#define KEYM_OID_ANSI_X9_62                  KEYM_OID_ISO_MEMBER_BODIES,\
                                             KEYM_OID_COUNTRY_US,\
                                             KEYM_OID_ORG_ANSI_X9_62

#define KEYM_OID_ORG_CERTICOM                0x81u, 0x04u
#define KEYM_OID_CERTICOM                    KEYM_OID_ISO_IDENTIFIED_ORG,\
                                             KEYM_OID_ORG_CERTICOM

#define KEYM_OID_ORG_PRIVATE_INTERNET        0x06u, 0x01u, 0x05u, 0x05u, 0x07u, 0x01u
#define KEYM_OID_PRIVATE_INTERNET            KEYM_OID_ISO_IDENTIFIED_ORG,\
                                             KEYM_OID_ORG_PRIVATE_INTERNET
/* ISO arc for standard certificate and CRL extensions */
/* id-ce OID */
#define KEYM_OID_ID_CE                       KEYM_OID_ISO_CCITT_DS, 0x1Du

/* OIDs for standard certificate extensions */
/* id-ce-authorityKeyIdentifier OID */
#define KEYM_OID_AUTHORITY_KEY_IDENTIFIER    KEYM_OID_ID_CE, 0x23u
/* id-ce-subjectKeyIdentifier OID */
#define KEYM_OID_SUBJECT_KEY_IDENTIFIER      KEYM_OID_ID_CE, 0x0Eu
/* id-ce-keyUsage OID */
#define KEYM_OID_KEY_USAGE                   KEYM_OID_ID_CE, 0x0Fu
/* id-ce-certificatePolicies OID */
#define KEYM_OID_CERTIFICATE_POLICIES        KEYM_OID_ID_CE, 0x20u
/* id-ce-policyMappings OID */
#define KEYM_OID_POLICY_MAPPINGS             KEYM_OID_ID_CE, 0x21u
/* id-ce-subjectAltName OID */
#define KEYM_OID_SUBJECT_ALT_NAME            KEYM_OID_ID_CE, 0x11u
/* id-ce-issuerAltName OID */
#define KEYM_OID_ISSUER_ALT_NAME             KEYM_OID_ID_CE, 0x12u
/* id-ce-subjectDirectoryAttributes OID */
#define KEYM_OID_SUBJECT_DIRECTORY_ATTRS     KEYM_OID_ID_CE, 0x09u
/* id-ce-basicConstraints OID */
#define KEYM_OID_BASIC_CONSTRAINTS           KEYM_OID_ID_CE, 0x13u
/* id-ce-nameConstraints OID */
#define KEYM_OID_NAME_CONSTRAINTS            KEYM_OID_ID_CE, 0x1Eu
/* id-ce-policyConstraints OID */
#define KEYM_OID_POLICY_CONSTRAINTS          KEYM_OID_ID_CE, 0x24u
/* id-ce-extKeyUsage OID */
#define KEYM_OID_EXTENDED_KEY_USAGE          KEYM_OID_ID_CE, 0x25u
/* id-ce-cRLDistributionPoints OID */
#define KEYM_OID_CRL_DISTRIBUTION_POINTS     KEYM_OID_ID_CE, 0x1Fu
/* id-ce-inhibitAnyPolicy OID */
#define KEYM_OID_INIHIBIT_ANYPOLICY          KEYM_OID_ID_CE, 0x36u
/* id-ce-freshestCRL OID */
#define KEYM_OID_FRESHEST_CRL                KEYM_OID_ID_CE, 0x2Eu
/* id-ce-cRLNumber OID */
#define KEYM_OID_CRL_NUMBER                  KEYM_OID_ID_CE, 0x14u
/* id-ce-cRLDistributionPoints OID */
#define KEYM_OID_ISSUING_DISTRIBUTION_POINT  KEYM_OID_ID_CE, 0x1Cu
/* id-ce-authorityInfoAccess OID */
#define KEYM_OID_AUTHORITY_INFO_ACCESS       KEYM_OID_PRIVATE_INTERNET, 0x01u

/* PKCS definition OIDs */
#define KEYM_OID_PKCS                KEYM_OID_RSA_COMPANY, 0x01u
#define KEYM_OID_PKCS1               KEYM_OID_PKCS, 0x01u

/* PKCS#1 OIDs */
/* rsaEncryption OID */
#define KEYM_OID_PKCS1_RSA           KEYM_OID_PKCS1, 0x01u
/* sha1WithRSAEncryption OID */
#define KEYM_OID_PKCS1_SHA1          KEYM_OID_PKCS1, 0x05u
/* sha224WithRSAEncryption OID */
#define KEYM_OID_PKCS1_SHA224        KEYM_OID_PKCS1, 0x0Eu
/* sha256WithRSAEncryption OID */
#define KEYM_OID_PKCS1_SHA256        KEYM_OID_PKCS1, 0x0Bu
/* sha384WithRSAEncryption OID */
#define KEYM_OID_PKCS1_SHA384        KEYM_OID_PKCS1, 0x0Cu
/* sha512WithRSAEncryption OID */
#define KEYM_OID_PKCS1_SHA512        KEYM_OID_PKCS1, 0x0Du

/* id-RSASSA-PSS OID from RFC 4055*/
#define KEYM_OID_RSASSA_PSS          KEYM_OID_PKCS1, 0x0Au
/* id-mgf1 OID from RFC 4055*/
#define KEYM_OID_MGF1                KEYM_OID_PKCS1, 0x08u

/* ECDSA signature identifiers, from RFC 5480 */
#define KEYM_OID_ANSI_X9_62_SIG          KEYM_OID_ANSI_X9_62, 0x04u
#define KEYM_OID_ANSI_X9_62_SIG_SHA2     KEYM_OID_ANSI_X9_62_SIG, 0x03u
/* ecdsa-with-SHA1 OID */
#define KEYM_OID_ECDSA_SHA1              KEYM_OID_ANSI_X9_62_SIG, 0x01u
/* ecdsa-with-SHA224 OID */
#define KEYM_OID_ECDSA_SHA224            KEYM_OID_ANSI_X9_62_SIG_SHA2, 0x01u
/* ecdsa-with-SHA256 OID */
#define KEYM_OID_ECDSA_SHA256            KEYM_OID_ANSI_X9_62_SIG_SHA2, 0x02u
/* ecdsa-with-SHA384 OID */
#define KEYM_OID_ECDSA_SHA384            KEYM_OID_ANSI_X9_62_SIG_SHA2, 0x03u
/* ecdsa-with-SHA512 OID */
#define KEYM_OID_ECDSA_SHA512            KEYM_OID_ANSI_X9_62_SIG_SHA2, 0x04u
/* id-ecPublicKey OID from RFC 5480 */
#define KEYM_OID_EC_ALG_UNRESTRICTED     KEYM_OID_ANSI_X9_62, 0x02u, 0x01u
/* id-ecDH OID from RFC 5480 */
#define KEYM_OID_EC_ALG_ECDH             KEYM_OID_CERTICOM, 0x01u, 0x0Cu

/*define for ed448, ed25519, x448, x25519 from RFC 8410*/
/* id-X25519    OBJECT IDENTIFIER ::= { 1 3 101 110 } */
#define KEYM_OID_EC_ALG_X25519           0x2B, 0x65, 0x6E
/*id-X448      OBJECT IDENTIFIER ::= { 1 3 101 111 } */
#define KEYM_OID_EC_ALG_X448             0x2B, 0x65, 0x6F
/*id-Ed25519   OBJECT IDENTIFIER ::= { 1 3 101 112 } */
#define KEYM_OID_EC_ALG_ED25519          0x2B, 0x65, 0x70
/*id-Ed448     OBJECT IDENTIFIER ::= { 1 3 101 113 } */
#define KEYM_OID_EC_ALG_ED448            0x2B, 0x65, 0x71

/* ECC name curve OID defined following rfc-5480 */
/* https://www.rfc-editor.org/rfc/rfc5480#section-2.2 */
#define CURVE_0  			    0x00
#define CURVE_3  			    0x03
#define PRIME_1					  0x01
/*ec secp521 OID*/
#define KEYM_OID_CURVEp521r1	              KEYM_OID_ISO_IDENTIFIED_ORG,\
                                              KEYM_OID_ORG_CERTICOM,CURVE_0,0x23
/*ec secp256 OID*/
#define KEYM_OID_CURVEp256r1	              KEYM_OID_ISO_MEMBER_BODIES,\
                                              KEYM_OID_COUNTRY_US,\
                                              KEYM_OID_ORG_ANSI_X9_62,\
                                              CURVE_3,PRIME_1,0x07
/*ec secp224 OID*/
#define KEYM_OID_CURVEp224r1	              KEYM_OID_ISO_IDENTIFIED_ORG,\
                                              KEYM_OID_ORG_CERTICOM,CURVE_0,0x21
/*ec secp160 OID*/
#define KEYM_OID_CURVEp160r1	              KEYM_OID_ISO_IDENTIFIED_ORG,\
                                              KEYM_OID_ORG_CERTICOM,CURVE_0,0x8

/* Number of supported curves of EC certificate */
#define KEYM_OID_CURVE_TYPE_NUMBER            (0x08u)

/* Number of recognized extensions of certificate */
#define KEYM_OID_CERT_RECOGNIZED_EXT_NUMBER       (0x08u)
/* Number of recognized extensions of CRL */
#define KEYM_OID_CRL_RECOGNIZED_EXT_NUMBER        (0x03u)
/* Number of signature algorithm type */
#define KEYM_OID_SIGNATURE_ALG_NUMBER             (0x0Du)
/* Number of public key type */
#define KEYM_OID_PUBLIC_KEY_ALG_NUMBER            (0x08u)

#define KEYM_OID_THREE                            (3u)
#define KEYM_OID_FOUR                             (4u)
#define KEYM_OID_FIVE                             (5u)
#define KEYM_OID_SEVEN                            (7u)
#define KEYM_OID_EIGHT                            (8u)
#define KEYM_OID_NINE                             (9u)
#define KEYM_OID_TEN                              (10u)

/* Public key types */
#define KEYM_PK_RSA                (0x01u)
#define KEYM_PK_EC                 (0x02u)
#define KEYM_PK_ECDH               (0x03u)
/* Signature algorithm types */
#define KEYM_PK_RSASSA_PSS         (0x04u)
#define KEYM_PK_RSA_SHA1           (0x05u)
#define KEYM_PK_RSA_SHA224         (0x06u)
#define KEYM_PK_RSA_SHA256         (0x07u)
#define KEYM_PK_RSA_SHA384         (0x08u)
#define KEYM_PK_RSA_SHA512         (0x09u)
#define KEYM_PK_ECDSA_SHA1         (0x0Au)
#define KEYM_PK_ECDSA_SHA224       (0x0Bu)
#define KEYM_PK_ECDSA_SHA256       (0x0Cu)
#define KEYM_PK_ECDSA_SHA384       (0x0Du)
#define KEYM_PK_ECDSA_SHA512       (0x0Eu)

#define KEYM_PK_EDDSA_25519        (0x0F)
#define KEYM_PK_EDDSA_448          (0x10)



/* CVC Signature algorithm types */
/* bsi-de OID */
#define KEYM_OID_BSI_DE                    0x04u, 0x00u, 0x7fu, 0x00u, 0x07
/* id-TA OID */
#define KEYM_OID_ID_TA                     KEYM_OID_BSI_DE, 0x02u, 0x02u, 0x02u
/* id-TA-RSA OID */
#define KEYM_OID_ID_TA_RSA                 KEYM_OID_ID_TA, 0x01u
/* id-TA-RSA-v1-5-SHA-1 OID */
#define KEYM_OID_ID_TA_RSA_V1_5_SHA1       KEYM_OID_ID_TA_RSA, 0x01u
/* id-TA-RSA-v1-5-SHA-256 OID */
#define KEYM_OID_ID_TA_RSA_V1_5_SHA256     KEYM_OID_ID_TA_RSA, 0x02u
/* id-TA-RSA-PSS-SHA-1 OID */
#define KEYM_OID_ID_TA_RSA_PSS_SHA1        KEYM_OID_ID_TA_RSA, 0x03u
/* id-TA-RSA-PSS-SHA-256 OID */
#define KEYM_OID_ID_TA_RSA_PSS_SHA256      KEYM_OID_ID_TA_RSA, 0x04u
/* id-TA-RSA-v1-5-SHA-512 OID */
#define KEYM_OID_ID_TA_RSA_V1_5_SHA512     KEYM_OID_ID_TA_RSA, 0x05u
/* id-TA-RSA-PSS-SHA-512 OID */
#define KEYM_OID_ID_TA_RSA_PSS_SHA512      KEYM_OID_ID_TA_RSA, 0x06u

/* id-TA-ECDSA OID */
#define KEYM_OID_ID_TA_ECDSA               KEYM_OID_ID_TA, 0x02u
/* id-TA-ECDSA-SHA-1 OID */
#define KEYM_OID_ID_TA_ECDSA_SHA1          KEYM_OID_ID_TA_ECDSA, 0x01u
/* id-TA-ECDSA-SHA-224 OID */
#define KEYM_OID_ID_TA_ECDSA_SHA224        KEYM_OID_ID_TA_ECDSA, 0x02u
/* id-TA-ECDSA-SHA-256 OID */
#define KEYM_OID_ID_TA_ECDSA_SHA256        KEYM_OID_ID_TA_ECDSA, 0x03u
/* id-TA-ECDSA-SHA-384 OID */
#define KEYM_OID_ID_TA_ECDSA_SHA384        KEYM_OID_ID_TA_ECDSA, 0x04u
/* id-TA-ECDSA-SHA-512 OID */
#define KEYM_OID_ID_TA_ECDSA_SHA512        KEYM_OID_ID_TA_ECDSA, 0x05u

/* @Trace: KeyM_SUD_DATATYPE_034 */
/* For X509 extensions */
typedef struct
{
  /* OID ASN.1 representation */
  const uint8 * PtrObjectID;
  /* Length of OID ASN.1 */
  uint8 ObjectLen;
} KeyM_ObjectIdDescriptorType;

#if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
  (KEYM_CERT_X509_CRL_ENABLED == STD_ON))
/* @Trace: KeyM_SUD_DATATYPE_035 */
/* For X509 extensions */
typedef struct
{
  /* OID */
  KeyM_ObjectIdDescriptorType ObjectDes;
  /* Extension type */
  uint8 ExtensionType;
} KeyM_ObjectIdExtType;
#endif
/* @Trace: KeyM_SUD_DATATYPE_036 */
/* Public Key or Signature algorithm type */
typedef struct
{
  /* OID */
  KeyM_ObjectIdDescriptorType ObjectDes;
  /* Public Key or Signature algorithm type */
  uint8 KeySignType;
} KeyM_ObjectIdKeyAlgorithmType;

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
#if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509GetCertExtensionType(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  const uint8 objectIdLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtType);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509GetPublicKeyType(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  const uint8 objectIdLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrKeyType);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"


#endif /* #if (KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) */

#if (KEYM_CERT_X509_CRL_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509GetCrlExtensionType(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  const uint8 objectIdLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrExtType);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* #if (KEYM_CERT_X509_CRL_ENABLED == STD_ON) */

#if ((KEYM_CERT_X509_CERTIFICATE_ENABLED == STD_ON) || \
  (KEYM_CERT_X509_CRL_ENABLED == STD_ON))
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvX509GetSignatureAlgType(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  const uint8 objectIdLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSigAlgType);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (KEYM_CERT_CVC_CERTIFICATE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_PrvCvcGetSignatureAlgType(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrObjectId, \
  const uint8 objectIdLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrSigAlgType);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */
#endif /* KEYM_OID_H */
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
