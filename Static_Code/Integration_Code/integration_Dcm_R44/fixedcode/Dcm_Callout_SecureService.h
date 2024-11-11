/*******************************************************************************
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Dcm_Callout_SecureService.h                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions for UDS services           **
**              implemented by DSP layer of Dcm module                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                Description                      **
********************************************************************************
** 1.1.0     15-Oct-2023   SY Kim         Refer #CP44-2595                    **
** 1.2.0     06-Nov-2023   SY Kim         Refer #CP44-3194                    **
*******************************************************************************/
#ifndef DCM_CALLOUT_SECURESERVICE_H
#define DCM_CALLOUT_SECURESERVICE_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm.h"
#include "Platform_Types.h"
#include "Dcm_Cfg.h"
#if (DCM_CRYPTO_R44_USED == STD_ON)
#include "Csm.h"
#endif
 
/*******************************************************************************
**                      Macros for DCM_ES95489_SUPPORT                        **
*******************************************************************************/
#define DCM_CHKCERTIFICATION                ((uint8)0x01)
#define DCM_CHKKEY                          ((uint8)0x02)

#define DCM_SECURE_INITIAL                  ((uint8)0x00)
#define DCM_SECURE_COMPLETE                 ((uint8)0x01)
#define DCM_SECURE_FAILURE                  ((uint8)0x02)

/* For algorithm processing step */ 
#define DCM_ALGM_INITIAL                    ((uint8)0x00)
#define DCM_ALGM_UPDATE                     ((uint8)0x01)
#define DCM_ALGM_FINISH                     ((uint8)0x02)
#define DCM_ALGM_VERIFY                     ((uint8)0x03)

#define DCM_SECURE_SEED_SIZE                (8U)

#define DCM_CERT                            (0U)  
#define DCM_CERTCRL                         (1U)          

/* Certificate field information */
#define DCM_PROFILE_ID                      (1U)
#define DCM_AUTHORITY_REFERENCE             (14U)
#define DCM_EFFECTIVE_DATE                  (3U)
#define DCM_EXPERATION_DATE                 (3U)
#define DCM_AUTHORIZATION_OBJECT_ID         (23U)
#define DCM_HOLDER_REFERENCE                (16U)
#define DCM_HOLDER_ROLE                     (4U)
#define DCM_PUBKEY_OBJECT_ID                (20U)
#define DCM_PUBLICKEY_EXPONENT              (4U)
#define DCM_PUBLICKEY_MODULUS               (256U)
#define DCM_CERTIFICATE_SIGNATURE           (256U)

#define PLAINDATA                           (DCM_PROFILE_ID +\
                                             DCM_AUTHORITY_REFERENCE +\
                                             DCM_EFFECTIVE_DATE +\
                                             DCM_EXPERATION_DATE +\
                                             DCM_AUTHORIZATION_OBJECT_ID +\
                                             DCM_HOLDER_REFERENCE +\
                                             DCM_HOLDER_ROLE +\
                                             DCM_PUBKEY_OBJECT_ID +\
                                             DCM_PUBLICKEY_EXPONENT +\
                                             DCM_PUBLICKEY_MODULUS)

/* CRL field information */
#define DCM_CRL_VERSION                     (1U) 
#define DCM_CRL_SIGNATURE_ALGORITHM         (22U)
#define DCM_CRL_ISSUER                      (14U)
#define DCM_CRL_DISTRIBUTION_NAME           (16U)
#define DCM_CRL_CERT_GROUP_COUNT            (4U)
#define DCM_CRL_CERT_AUTHORITY_KEYID        (32U)
#define DCM_CRL_EFFECTIVE_DATE              (3U)
#define DCM_CRL_EXPIRATION_DATE             (3U)
#define DCM_CRL_REVOKED_CERT_START_SEQNUM   (4U)
#define DCM_CRL_CERT_STATUS_SIZE            (4U)
#define DCM_CRL_CERT_STATUS_BITS            (126U)
#define DCM_CRL_RESERVED_FIELD              (16U)
#define DCM_CRL_SIGNATURE                   (256U)

#define CRL_PLAINDATA                       (DCM_CRL_VERSION +\
                                             DCM_CRL_SIGNATURE_ALGORITHM +\
                                             DCM_CRL_ISSUER +\
                                             DCM_CRL_DISTRIBUTION_NAME +\
                                             DCM_CRL_CERT_GROUP_COUNT +\
                                             DCM_CRL_CERT_AUTHORITY_KEYID +\
                                             DCM_CRL_EFFECTIVE_DATE +\
                                             DCM_CRL_EXPIRATION_DATE +\
                                             DCM_CRL_REVOKED_CERT_START_SEQNUM +\
                                             DCM_CRL_CERT_STATUS_SIZE +\
                                             DCM_CRL_CERT_STATUS_BITS +\
                                             DCM_CRL_RESERVED_FIELD)

#define CRL_FIXED_PLAINDATA                 (DCM_CRL_VERSION +\
                                             DCM_CRL_SIGNATURE_ALGORITHM +\
                                             DCM_CRL_ISSUER +\
                                             DCM_CRL_DISTRIBUTION_NAME +\
                                             DCM_CRL_CERT_GROUP_COUNT +\
                                             DCM_CRL_CERT_AUTHORITY_KEYID +\
                                             DCM_CRL_EFFECTIVE_DATE +\
                                             DCM_CRL_EXPIRATION_DATE +\
                                             DCM_CRL_REVOKED_CERT_START_SEQNUM +\
                                             DCM_CRL_CERT_STATUS_SIZE +\
                                             DCM_CRL_RESERVED_FIELD)


#define DCM_CRL_CERT_STATUSBITS_MAX_SIZE     (1251U)

#define DCM_SECURE_PENDING                  (10U)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/ 
#define DCM_START_SEC_CODE
#include "MemMap.h"

#if (DCM_CSAC_CONFIGURED == STD_ON) || (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetSeed(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pSecurityAccessRecord,
  Dcm_OpStatusType LucOpStatus, 
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pSeed,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspCompareKey(
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) LpReqResData, 
  VAR(uint8, AUTOMATIC) LucOpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);

#if (DCM_CRYPTO_R44_USED == STD_OFF)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspVerifySignatureSeedCbk(Std_ReturnType RetVal);
#elif (DCM_CRYPTO_R44_USED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_DspVerifySignatureSeedCbk(
const uint32 jobID, Csm_ResultType RetVal);
#endif

#endif  
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetCertificationInfo(
  P2VAR(Dcm_CertInfoType, AUTOMATIC, DCM_APPL_DATA) CertInfo);

 
#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif
 
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
