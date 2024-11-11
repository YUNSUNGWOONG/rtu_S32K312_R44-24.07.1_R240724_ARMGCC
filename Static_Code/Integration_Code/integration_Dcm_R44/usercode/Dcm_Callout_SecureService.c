/*******************************************************************************
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Dcm_Callout_SecureService.c                                   **
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
** 1.2.0     06-Nov-2023   SY Kim         Refer #CP44-3194, #CP44-3137        **
** 1.3.0     04-Dec-2023   SY Kim         Refer #CP44-3445                    **
*******************************************************************************/

/*******************************************************************************
**                       Include Section                                      **
*******************************************************************************/

#include "Std_Types.h"
#include "Dcm_Cfg.h"
#include "Dcm_Types.h"
#include "Dcm_Callout_SecureService.h"
#include "SchM_Dcm.h"
#include "Dcm_Version.h"

#if (DCM_CSAC_CONFIGURED == STD_ON) || (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
#include "Rte_Dcm.h"
#include "Csm.h"
#include "Dcm_Ram.h"

#if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
#include "Dcm_Authentication.h"
#endif

#if (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4)
#include "Dcm_Externals.h"
#else /*For DCM_VERSION_AR_RELEASE_MINOR_VERSION == 0*/
#include "Dcm_CallOuts.h"
#endif


/*******************************************************************************
**                       Global Variables                                     **
*******************************************************************************/
/* Hac Random Generate */
#define DCM_HAE_HAC_RANDOM_SEED_LENGTH                  (16U)
#define DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH             (8U)

#if (defined(CSM_RANDOM_AUTHSMTRUERANDOMGENERATE) \
  && (CSM_RANDOM_AUTHSMTRUERANDOMGENERATE == STD_ON))

/*AutHsm TrueRandomGenerate*/
#if HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM       (STD_ON)
// TEST //#pragma ghs section bss=".gbbss.DEFAULT_GLOBALB_RAM_VAR_CLEARED"
uint8 Dcm_GaaRandom[DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH];
// TEST //#pragma ghs section
#else
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM            (STD_ON)
#endif

#if(defined(CSM_AUTHSMTRUERANDOMGENERATE_L21_INDEX))
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_AUTHSMTRUERANDOMGENERATE_L21_INDEX)
#elif(defined(CSM_AUTHSMTRUERANDOMGENERATE_SID29_INDEX))
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_AUTHSMTRUERANDOMGENERATE_SID29_INDEX)
#endif
/*End of AutHsm TrueRandomGenerate*/

/*
 * AutHsm PseudoRandomGenerate
 * #24991: When HSM applied, run TRNG at the 1st time only then run PRNG for all
 *         CSM will process appropriate logic according to DCM_RANDOM_GENERATE_CSM_ID value
 * */
#elif (defined(CSM_RANDOM_AUTHSMPSEUDORANDOMGENERATE) && (CSM_RANDOM_AUTHSMPSEUDORANDOMGENERATE == STD_ON))
#if HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM       (STD_ON)
// TEST //#pragma ghs section bss=".gbbss.DEFAULT_GLOBALB_RAM_VAR_CLEARED"
uint8 Dcm_GaaRandom[DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH];
// TEST //#pragma ghs section
#else
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM            (STD_ON)
#endif

#if(defined(CSM_AUTHSMPSEUDORANDOMGENERATE_L21_INDEX))
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_AUTHSMPSEUDORANDOMGENERATE_L21_INDEX)
#elif(defined(CSM_AUTHSMPSEUDORANDOMGENERATE_SID29_INDEX))
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_AUTHSMPSEUDORANDOMGENERATE_SID29_INDEX)
#endif

/*End of AutHsm PseudoRandomGenerate*/

#elif (defined(CSM_RANDOM_AUTICUSRANDOMGENERATE) && (CSM_RANDOM_AUTICUSRANDOMGENERATE == STD_ON))

#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_ICUS           (STD_ON)

#if(defined(CSM_AUTICUSRANDOMGENERATE_L21_INDEX))
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_AUTICUSRANDOMGENERATE_L21_INDEX)
#elif(defined(CSM_AUTICUSRANDOMGENERATE_SID29_INDEX))
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_AUTICUSRANDOMGENERATE_SID29_INDEX)
#endif

/*HaeHsm TrueRandomGenerate*/
#elif (defined(CSM_RANDOM_HAEHSMTRUERANDOMGENERATE) && (CSM_RANDOM_HAEHSMTRUERANDOMGENERATE == STD_ON))

#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM            (STD_ON)

#if(defined(CSM_HAEHSMTRUERANDOMGENERATE_L21_INDEX))
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_HAEHSMTRUERANDOMGENERATE_L21_INDEX)
#elif(defined(CSM_HAEHSMTRUERANDOMGENERATE_SID29_INDEX))
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_HAEHSMTRUERANDOMGENERATE_SID29_INDEX)
#endif
/*End of HaeHsm TrueRandomGenerate*/

/*
 * HaeHsm PseudoRandomGenerate
 * #24991: When HSM applied, run TRNG at the 1st time only then run PRNG for all
 *         CSM will process appropriate logic according to DCM_RANDOM_GENERATE_CSM_ID value *
 * */
#elif (defined(CSM_RANDOM_HAEHSMPSEUDORANDOMGENERATE) && (CSM_RANDOM_HAEHSMPSEUDORANDOMGENERATE == STD_ON))

#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM            (STD_ON)

#if(defined(CSM_HAEHSMPSEUDORANDOMGENERATE_L21_INDEX))
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_HAEHSMPSEUDORANDOMGENERATE_L21_INDEX)
#elif(defined(CSM_HAEHSMPSEUDORANDOMGENERATE_SID29_INDEX))
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_HAEHSMPSEUDORANDOMGENERATE_SID29_INDEX)
#endif
/*End of HaeHsm PseudoRandomGenerate*/

#elif ((defined(CSM_RANDOM_HAEPSEUDORANDOMSEED) && (CSM_RANDOM_HAEPSEUDORANDOMSEED == STD_ON)) \
  && (defined(CSM_RANDOM_HAEPSEUDORANDOMGENERATE) && (CSM_RANDOM_HAEPSEUDORANDOMGENERATE == STD_ON)))

#define DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE          (STD_ON)

#if((defined(CSM_HAEPSEUDORANDOMSEED_L21_INDEX)) && (defined(CSM_HAEPSEUDORANDOMGENERATE_L21_INDEX)))
#define DCM_RANDOM_SEED_CSM_ID                          (CSM_HAEPSEUDORANDOMSEED_L21_INDEX)
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_HAEPSEUDORANDOMGENERATE_L21_INDEX)
#elif((defined(CSM_HAEPSEUDORANDOMSEED_SID29_INDEX)) && (defined(CSM_HAEPSEUDORANDOMGENERATE_SID29_INDEX)))
#define DCM_RANDOM_SEED_CSM_ID                          (CSM_HAEPSEUDORANDOMSEED_SID29_INDEX)
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_HAEPSEUDORANDOMGENERATE_SID29_INDEX)
#endif

/* For Pseudo Random Generate */
static boolean Dcm_GblSetHaePseudoSeed = DCM_FALSE;

#elif ((defined(CSM_RANDOM_HAEHACRANDOMSEED) && (CSM_RANDOM_HAEHACRANDOMSEED == STD_ON)) \
  && (defined(CSM_RANDOM_HAEHACRANDOMGENERATE) && (CSM_RANDOM_HAEHACRANDOMGENERATE == STD_ON)))

#define DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE          (STD_ON)

#if((defined(CSM_HAEHACRANDOMSEED_L21_INDEX)) && (defined(CSM_HAEHACRANDOMGENERATE_L21_INDEX)))
#define DCM_RANDOM_SEED_CSM_ID                          (CSM_HAEHACRANDOMSEED_L21_INDEX)
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_HAEHACRANDOMGENERATE_L21_INDEX)
#elif((defined(CSM_HAEHACRANDOMSEED_SID29_INDEX)) && (defined(CSM_HAEHACRANDOMGENERATE_SID29_INDEX)))
#define DCM_RANDOM_SEED_CSM_ID                          (CSM_HAEHACRANDOMSEED_SID29_INDEX)
#define DCM_RANDOM_GENERATE_CSM_ID                      (CSM_HAEHACRANDOMGENERATE_SID29_INDEX)
#endif

/* For HAC Random Generate */
static boolean Dcm_GblSetHaePseudoSeed = DCM_FALSE;
#elif (DCM_CRYPTO_R44_USED == STD_ON)
static boolean Dcm_GblSetHaePseudoSeed = DCM_FALSE;
#else
#error "Dcm_Callout_SecureService.c Random generate configuration error!"
#endif


#if ((defined(CSM_SIGNATURE_AUTHSMPKCS1V15SHA1VERIFY) \
    && (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1VERIFY == STD_ON)) \
  && (defined(CSM_SIGNATURE_AUTHSMPKCS1V15SHA1SEEDVERIFY) \
    && (CSM_SIGNATURE_AUTHSMPKCS1V15SHA1SEEDVERIFY == STD_ON)))

#if HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)
#define DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM               (STD_ON)
#endif

#define DCM_SIGNATURE_VERIFY_CSM_ID                     (CSM_AUTHSMPKCS1V15SHA1VERIFY_L21_INDEX)
#define DCM_SIGNATURE_VERIFY_SEED_CSM_ID                (CSM_AUTHSMPKCS1V15SHA1SEEDVERIFY_L21_INDEX)

#elif ((defined(CSM_SIGNATURE_AUTHSMPKCS1V15SHA256VERIFY) \
    && (CSM_SIGNATURE_AUTHSMPKCS1V15SHA256VERIFY == STD_ON)) \
  && (defined(CSM_SIGNATURE_AUTHSMPKCS1V15SHA256SEEDVERIFY) \
    && (CSM_SIGNATURE_AUTHSMPKCS1V15SHA256SEEDVERIFY == STD_ON)))

#if HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)
#define DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM               (STD_ON)
#endif

#define DCM_SIGNATURE_VERIFY_CSM_ID                     (CSM_AUTHSMPKCS1V15SHA256VERIFY_L21_INDEX)
#define DCM_SIGNATURE_VERIFY_SEED_CSM_ID                (CSM_AUTHSMPKCS1V15SHA256SEEDVERIFY_L21_INDEX)

#elif ((defined(CSM_SIGNATURE_HAEPKCS1V15SHA1VERIFY) \
    && (CSM_SIGNATURE_HAEPKCS1V15SHA1VERIFY == STD_ON)) \
  && (defined(CSM_SIGNATURE_HAEPKCS1V15SHA1SEEDVERIFY) \
    && (CSM_SIGNATURE_HAEPKCS1V15SHA1SEEDVERIFY == STD_ON)))

#define DCM_SIGNATURE_VERIFY_CSM_ID                     (CSM_HAEPKCS1V15SHA1VERIFY_L21_INDEX)
#define DCM_SIGNATURE_VERIFY_SEED_CSM_ID                (CSM_HAEPKCS1V15SHA1SEEDVERIFY_L21_INDEX)

#elif ((defined(CSM_SIGNATURE_HAEPKCS1V15SHA256VERIFY) \
    && (CSM_SIGNATURE_HAEPKCS1V15SHA256VERIFY == STD_ON)) \
    && (defined(CSM_HAEPKCS1V15SHA256VERIFY_L21_INDEX)))

#define DCM_SIGNATURE_VERIFY_CSM_ID                     (CSM_HAEPKCS1V15SHA256VERIFY_L21_INDEX)
#define DCM_SIGNATURE_VERIFY_SEED_CSM_ID                (CSM_HAEPKCS1V15SHA256SEEDVERIFY_L21_INDEX)
#elif ((defined(CSM_SIGNATURE_HAEPKCS1V15SHA256VERIFY) \
    && (CSM_SIGNATURE_HAEPKCS1V15SHA256VERIFY == STD_ON)) \
    && (defined(CSM_HAEPKCS1V15SHA256VERIFY_SID29_INDEX)))
#define DCM_SIGNATURE_VERIFY_CSM_ID                     (CSM_HAEPKCS1V15SHA256VERIFY_SID29_INDEX)
#define DCM_SIGNATURE_VERIFY_SEED_CSM_ID                (CSM_HAEPKCS1V15SHA256SEEDVERIFY_SID29_INDEX)

#elif ((defined(CSM_SIGNATURE_ESCPKCS1V15SHA1VERIFY) \
    && (CSM_SIGNATURE_ESCPKCS1V15SHA1VERIFY == STD_ON)) \
  && (defined(CSM_SIGNATURE_ESCPKCS1V15SHA1SEEDVERIFY) \
    && (CSM_SIGNATURE_ESCPKCS1V15SHA1SEEDVERIFY == STD_ON)))

#define DCM_SIGNATURE_VERIFY_CSM_ID                     (CSM_ESCPKCS1V15SHA1VERIFY_L21_INDEX)
#define DCM_SIGNATURE_VERIFY_SEED_CSM_ID                (CSM_ESCPKCS1V15SHA1SEEDVERIFY_L21_INDEX)

#elif ((defined(CSM_SIGNATURE_ESCPKCS1V15SHA256VERIFY) \
    && (CSM_SIGNATURE_ESCPKCS1V15SHA256VERIFY == STD_ON)) \
  && (defined(CSM_SIGNATURE_ESCPKCS1V15SHA256SEEDVERIFY) \
    && (CSM_SIGNATURE_ESCPKCS1V15SHA256SEEDVERIFY == STD_ON)))

#define DCM_SIGNATURE_VERIFY_CSM_ID                     (CSM_ESCPKCS1V15SHA256VERIFY_L21_INDEX)
#define DCM_SIGNATURE_VERIFY_SEED_CSM_ID                (CSM_ESCPKCS1V15SHA256SEEDVERIFY_L21_INDEX)

#elif (DCM_CRYPTO_R44_USED == STD_ON)
#else
#error "Dcm_Callout_SecureService.c PKCS#1 V1.5 configuration error!"
#endif

#if (defined (CSM_PKCS1V15SHA256VERIFY_CRL_SID29_INDEX))
#define DCM_SIGNATURE_VERIFY_CRL_CSM_ID                 (CSM_PKCS1V15SHA256VERIFY_CRL_SID29_INDEX)
#elif (defined (CSM_PKCS1V15SHA256VERIFY_CRL_L21_INDEX))
#define DCM_SIGNATURE_VERIFY_CRL_CSM_ID                 (CSM_PKCS1V15SHA256VERIFY_CRL_L21_INDEX)
#elif (defined (CSM_PKCS1V15SHA256VERIFY_CRL_L21_INDEX) || (defined (CSM_PKCS1V15SHA256VERIFY_CRL_SID29_INDEX)))
#define DCM_SIGNATURE_VERIFY_CRL_CSM_ID                 (CSM_PKCS1V15SHA256VERIFY_CRL_L21_INDEX)
#endif

#if (defined (CSM_SHA256_CRL_INDEX))
#define DCM_SHA256_CRL_CSM_ID                 (CSM_SHA256_CRL_INDEX)
#endif

#if !defined(DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM)
#define DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM       (STD_OFF)
#endif

#if (DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM == STD_ON)
// TEST //#pragma ghs section bss=".gbbss.DEFAULT_GLOBALB_RAM_VAR_CLEARED"
#endif
static VAR(Csm_AsymPublicKeyType, DCM_VAR) Dcm_GddSignPublicKey;

static VAR(Csm_AsymPublicKeyType, DCM_VAR) Dcm_GddTesterSignPublicKey;
#if (DCM_SECURITY_CRL_ENABLE == STD_ON)

/* for Dcm UnitTest*/
#ifndef DCM_MODULE_ACTIVE
static
#endif

VAR(Csm_AsymPublicKeyType, DCM_VAR) Dcm_GddHashPublicKeyVal;
#endif
#if (DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM == STD_ON)
// TEST //#pragma ghs section
#endif

#if !defined(DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM)
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM       (STD_OFF)
#endif

#if !defined(DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM)
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM            (STD_OFF)
#endif

#if !defined(DCM_USE_CSM_TRUE_RANDOM_GENERATE_ICUS)
#define DCM_USE_CSM_TRUE_RANDOM_GENERATE_ICUS           (STD_OFF)
#endif

#if !defined(DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE)
#define DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE          (STD_OFF)
#endif

typedef enum
{
  DCM_CS_READY,
  DCM_CS_SERVER_CERT,
  DCM_CS_CRL_CERT,
  DCM_CS_CRL_KEYID,
  DCM_CS_MAKE_RANDOM,
  DCM_CS_TESTER_CERT,
} Dcm_CertStageType;

typedef enum
{
  DCM_CP_READY,
  DCM_CP_CRL_READY,
  DCM_CP_CRL_KEYID_READY,
  DCM_CP_DOING,
  DCM_CP_CERT_VERIFY,
  DCM_CP_SUCCESS,
  DCM_CP_FAIL,
  DCM_CP_CRL_FAIL
} Dcm_CertProgressStatusType;

typedef enum
{
  DCM_CAS_READY,
  DCM_CAS_REQ_START,
  DCM_CAS_REQ_CERT_SIGNATUREVERIFY,
  DCM_CAS_REQ_CRL_SIGNATUREVERIFY,
  DCM_CAS_REQ_TESTER_SIGNATUREVERIFY,
  DCM_CAS_REQ_UPDATE,
  DCM_CAS_REQ_FINISH
} Dcm_CertAlgorithmStepType;

static FUNC(void, DCM_CODE) Dcm_DspSecure_MemCopy(  
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) aDest,
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) aSrc,
  CONST(uint32, DCM_CONST) aSize);

static VAR(Dcm_CertStageType, DCM_VAR) Dcm_GddCertStage;
static VAR(Dcm_CertProgressStatusType, DCM_VAR) Dcm_GddCertProgress;
static VAR(Dcm_CertAlgorithmStepType, DCM_VAR) Dcm_GddCertAlgorithmStep;

static VAR(Dcm_CertInfoType, DCM_APPL_DATA) Dcm_GstCertificationInfo;

#if (DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM == STD_ON)
// TEST //#pragma ghs section bss=".gbbss.DEFAULT_GLOBALB_RAM_VAR_CLEARED"
#endif
static VAR(uint8, DCM_VAR) Dcm_GaaSecureData[PLAINDATA + DCM_CERTIFICATE_SIGNATURE];
#if (DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM == STD_ON)
// TEST //#pragma ghs section
#endif

/*Certification Authority Reference Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCertAuthorityReference[DCM_AUTHORITY_REFERENCE];
/*Authorization Role Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaAuthorizationRole[DCM_HOLDER_ROLE];
/*Expiration Date Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaEffectiveDate[DCM_EFFECTIVE_DATE];
/*Expiration Date Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaExpirationDate[DCM_EXPERATION_DATE];
/*Certificate Holder Reference */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCertHolderReference[DCM_HOLDER_REFERENCE];

#if (DCM_SECURITY_CRL_ENABLE == STD_ON)
/*CRL Issuer Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLIssuer[DCM_CRL_ISSUER];
/*CRL Certification Group Count Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLCertGroupCount[DCM_CRL_CERT_GROUP_COUNT];
/*CRL Certification Authority Key ID Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLCertAuthorityKeyID[DCM_CRL_CERT_AUTHORITY_KEYID];
/*CRL Effective Date Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLEffectiveDate[DCM_CRL_EFFECTIVE_DATE];
/*CRL Expiration Date Info */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLExpirationDate[DCM_CRL_EXPIRATION_DATE];
/*CRL Distribution Point Name */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLDistributionPointName[DCM_CRL_DISTRIBUTION_NAME];
/*CRL Revoked Cert Start Seq Num */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLRevokedCertStartSeqNum[DCM_CRL_REVOKED_CERT_START_SEQNUM];
/*CRL Distribution Point Name */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLCertStatusSize[DCM_CRL_CERT_STATUS_SIZE];
/*CRL Distribution Point Name */
static VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCRLCertStatusBits[DCM_CRL_CERT_STATUSBITS_MAX_SIZE];

static VAR(uint32, DCM_NOINIT_DATA) Dcm_GaaConvPresendDate;

/*CRL Distribution Point Name */

/* for Dcm UnitTest*/
#ifndef DCM_MODULE_ACTIVE
static
#endif
VAR(uint8, DCM_NOINIT_DATA) Dcm_GaaCertDigest[DCM_CRL_CERT_AUTHORITY_KEYID];

/* for Dcm UnitTest*/
#ifndef DCM_MODULE_ACTIVE
static
#endif
VAR(uint32, DCM_NOINIT_DATA) Dcm_GaaCRLDigestLength;
#endif /* #if (DCM_SECURITY_CRL_ENABLE == STD_ON) */

#if (DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM == STD_ON)
// TEST //#pragma ghs section bss=".gbbss.DEFAULT_GLOBALB_RAM_VAR_CLEARED"
#endif
static VAR(Crypto_VerifyResultType, DCM_VAR) Dcm_GddVerifyResult;
static VAR(uint8, DCM_VAR) Dcm_GaaSecureSeed[DCM_SECURE_SEED_SIZE];
#if (DCM_USE_CSM_AUT_HSM_PKCS1V15_ICUM == STD_ON)
// TEST //#pragma ghs section
#endif

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dcm_Secure_Init                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function initializes the secure service Module.**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dcm_GddVerifyResult,                                **
**                                                                            **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, DCM_CODE) Dcm_Secure_Init(void)
{
  #if (DCM_CRYPTO_R44_USED == STD_ON)
  Dcm_GddVerifyResult = CRYPTO_E_VER_NOT_OK;
  #else
  Dcm_GddVerifyResult = CSM_E_VER_NOT_OK;
  #endif
  
  Dcm_GddCertStage = DCM_CS_READY;
  Dcm_GddCertProgress = DCM_CP_READY;
  Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_MemCopy                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : It is used to copy the data from  src to dest.      **
**                        module                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : src                                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dest                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DspSecure_MemCopy(  
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) aDest,
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) aSrc,
  CONST(uint32, DCM_CONST) aSize)

{
  uint32 i = 0U;

  if ((NULL_PTR != aDest) && (NULL_PTR != aSrc))
  {
    for (i = 0; i < aSize; i++)
    {
      aDest[i] = aSrc[i];
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspConvertNum                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : It is used to convert number from hex to dec.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : src                                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dest                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if (DCM_SECURITY_CRL_ENABLE == STD_ON)
static FUNC(uint32, DCM_CODE) Dcm_DspConvertNum(  
  CONST(uint32, DCM_CONST) aNum)

{
  uint32 temp, temp2, expo, retVal = 0U;
  uint8 count, i = 0U;

  
  temp = aNum;
  count = 0U;
  while(temp>0)
  { 

    temp2 = temp%16U;
    temp = temp/16U;

    expo = 1U;
    i = count;

    while(i>0)
    {
      expo = expo*10U;
      i--;
    }
    
    retVal += temp2*expo;
    count++;
   
  }

  return retVal;
  
}
#endif


/*******************************************************************************
** Function Name        : Dcm_DspParsePlaintext                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function parses the certification come from    **
**                        tester.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DspParsePlaintext(
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) pSecureData)
{
  uint8 *LpExponent;
  
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) LpSecureData;
  LpSecureData = pSecureData;

  /* set pointer to read the Expiration data */
  LpSecureData = &LpSecureData[DCM_PROFILE_ID];

  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCertAuthorityReference, LpSecureData, DCM_AUTHORITY_REFERENCE);
  
  /* set pointer to read the Expiration data */
  LpSecureData = &LpSecureData[DCM_AUTHORITY_REFERENCE];

  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaEffectiveDate, LpSecureData, DCM_EFFECTIVE_DATE);

  /* set pointer to read the Expiration data */
  LpSecureData = &LpSecureData[DCM_EFFECTIVE_DATE];

  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaExpirationDate, LpSecureData, DCM_EXPERATION_DATE);

  /* set pointer to read the AuthorizationRole data */
  LpSecureData = &LpSecureData[DCM_EXPERATION_DATE + DCM_AUTHORIZATION_OBJECT_ID];

  /* copy Certificate Holder Authorization */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCertHolderReference, LpSecureData, DCM_HOLDER_REFERENCE);

  /* set pointer to read the AuthorizationRole data */
  LpSecureData = &LpSecureData[DCM_HOLDER_REFERENCE];

  /* copy Certificate Holder Authorization */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaAuthorizationRole, LpSecureData, DCM_HOLDER_ROLE);

  /* set pointer to read the exponent data */
  LpSecureData = &LpSecureData[DCM_HOLDER_ROLE + DCM_PUBKEY_OBJECT_ID];


  /* copy the exponent data */
/*  (void)Dcm_DspSecure_MemCopy(&(Dcm_GddSignPublicKey.data[(DCM_PUBLICKEY_MODULUS) / sizeof(Csm_AlignType)]),
    LpSecureData, 4);*/

  LpExponent = &(Dcm_GddTesterSignPublicKey.data[(DCM_PUBLICKEY_MODULUS) / sizeof(Csm_AlignType)]);
  #if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)  
  LpExponent[0] = LpSecureData[3];
  LpExponent[1] = LpSecureData[2];
  LpExponent[2] = LpSecureData[1];
  LpExponent[3] = LpSecureData[0];
  #else
  LpExponent[0] = LpSecureData[0];
  LpExponent[1] = LpSecureData[1];
  LpExponent[2] = LpSecureData[2];
  LpExponent[3] = LpSecureData[3];
  #endif

  /* set pointer to read the Modulus data */
  LpSecureData = &LpSecureData[DCM_PUBLICKEY_EXPONENT];

  #if(DCM_CRYPTO_R44_USED != STD_ON)
  {
  	Dcm_GddTesterSignPublicKey.length = DCM_PUBLICKEY_MODULUS + 4U;
  (void)Dcm_DspSecure_MemCopy((uint8*)(Dcm_GddTesterSignPublicKey.data),
    LpSecureData, DCM_PUBLICKEY_MODULUS);
}
  #elif(DCM_CRYPTO_R44_USED == STD_ON)
  {
  	Dcm_GddTesterSignPublicKey.length = DCM_PUBLICKEY_MODULUS + 38U;
    uint8 LaaStartTempExponent[33] = { 0x30U, 0x82U, 0x01U, 0x22U, 0x30U, 0x0DU, 0x06U, 0x09U, 0x2AU, 0x86U, 0x48U, 0x86U, 0xF7U, 0x0DU, 0x01U, 0x01U,
                                       0x01U, 0x05U, 0x00U, 0x03U, 0x82U, 0x01U, 0x0FU, 0x00U, 0x30U, 0x82U, 0x01U, 0x0AU, 0x02U, 0x82U, 0x01U, 0x01U,
                                       0x00U };
    (void)Dcm_DspSecure_MemCopy((uint8*)(Dcm_GddTesterSignPublicKey.data), LaaStartTempExponent, 33);

    (void)Dcm_DspSecure_MemCopy((uint8*)&(Dcm_GddTesterSignPublicKey.data[33U]), LpSecureData, DCM_PUBLICKEY_MODULUS);
    uint8 LaaEndTempExponent[5] = { 0x02U, 0x03U, 0x01U, 0x00U, 0x01U };
    (void)Dcm_DspSecure_MemCopy((uint8*)&(Dcm_GddTesterSignPublicKey.data[33U+DCM_PUBLICKEY_MODULUS]), LaaEndTempExponent, 5);
  }
  #endif
}
/*******************************************************************************
** Function Name        : Dcm_DspParseCRLPlaintext                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function parses the CRL come from              **
**                        tester.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_SECURITY_CRL_ENABLE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_DspParseCRLPlaintext(
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) pSecureData)
{

  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) LpSecureData;
  LpSecureData = pSecureData;

  /* set pointer to read the Expiration data */
  LpSecureData = &LpSecureData[DCM_CRL_VERSION + DCM_CRL_SIGNATURE_ALGORITHM];

  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLIssuer, LpSecureData, DCM_CRL_ISSUER);

  /* set pointer to read the Expiration data */
  LpSecureData = &LpSecureData[DCM_CRL_ISSUER];

  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLDistributionPointName, LpSecureData, DCM_CRL_DISTRIBUTION_NAME);

  /* set pointer to read the Effective data */
  LpSecureData = &LpSecureData[DCM_CRL_DISTRIBUTION_NAME];
  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLCertGroupCount, LpSecureData, DCM_CRL_CERT_GROUP_COUNT);  

  /* set pointer to read the Effective data */
  LpSecureData = &LpSecureData[DCM_CRL_CERT_GROUP_COUNT];
  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLCertAuthorityKeyID, LpSecureData, DCM_CRL_CERT_AUTHORITY_KEYID);  
  
  /* set pointer to read the Effective data */
  LpSecureData = &LpSecureData[DCM_CRL_CERT_AUTHORITY_KEYID];
  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLEffectiveDate, LpSecureData, DCM_CRL_EFFECTIVE_DATE);  

  /* set pointer to read the Expiration data */
  LpSecureData = &LpSecureData[DCM_CRL_EFFECTIVE_DATE];
  /* copy Certificate Expiration Date */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLExpirationDate, LpSecureData, DCM_CRL_EXPIRATION_DATE);

  /* set pointer to read the AuthorizationRole data */
  LpSecureData = &LpSecureData[DCM_EXPERATION_DATE];

  /* copy Certificate Holder Authorization */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLRevokedCertStartSeqNum, LpSecureData, DCM_CRL_REVOKED_CERT_START_SEQNUM);

  /* set pointer to read the AuthorizationRole data */
  LpSecureData = &LpSecureData[DCM_CRL_REVOKED_CERT_START_SEQNUM];

  /* copy Certificate Holder Authorization */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLCertStatusSize, LpSecureData, DCM_CRL_CERT_STATUS_SIZE);

  /* set pointer to read the AuthorizationRole data */
  LpSecureData = &LpSecureData[DCM_CRL_CERT_STATUS_SIZE];

  /* copy Certificate Holder Authorization */
  (void)Dcm_DspSecure_MemCopy(Dcm_GaaCRLCertStatusBits, LpSecureData, (Dcm_GaaCRLLength - CRL_FIXED_PLAINDATA - DCM_CRL_SIGNATURE));


}
#endif


/*******************************************************************************
** Function Name        : Dcm_DspDoRandomSeed                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function provide the input data to the Random  **
**                        Seed service                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE == STD_ON) || (DCM_CRYPTO_R44_USED == STD_ON))
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspDoRandomSeed(void)
{
  static VAR(uint8, DCM_VAR) Dcm_GaaHaeHacSalt[DCM_HAE_HAC_RANDOM_SEED_LENGTH];
  Std_ReturnType LddRetVal = E_OK;

  uint8 count;
  
  for(count=0; count<DCM_HAE_HAC_RANDOM_SEED_LENGTH; count++)
    {
       Dcm_GaaHaeHacSalt[count]=0U;
    }
  

  
  if (Dcm_GblSetHaePseudoSeed == DCM_FALSE)
  {
    /* Get RandomSeed */
    /* polyspace-begin DEFECT:DEAD_CODE MISRA-C3:14.3,2.1 [Justified:Low] "LddRetVal depend on retured value and it will must be E_OK and other function shall be called " */
    LddRetVal = Dcm_GetRandomSeed(Dcm_GaaHaeHacSalt);
    #if (DCM_CRYPTO_R44_USED == STD_ON)
    if (LddRetVal == E_OK)
    {
      LddRetVal = Csm_RandomSeed(Dcm_GaaSecureAccessCryptoConnectionConfig[DCM_SECURITY_CONFIG_L21_R44_INDEX].ulRandomSeedKeyId,
      Dcm_GaaHaeHacSalt, DCM_HAE_HAC_RANDOM_SEED_LENGTH);
    }

    #elif (DCM_CRYPTO_R44_USED != STD_ON)
    /* Update RandomSeed */
    if (LddRetVal == E_OK)
    {
      LddRetVal = Csm_RandomSeedStart(DCM_RANDOM_SEED_CSM_ID);
    }

    if (LddRetVal == E_OK)
    {
      LddRetVal = Csm_RandomSeedUpdate(DCM_RANDOM_SEED_CSM_ID,
        Dcm_GaaHaeHacSalt, DCM_HAE_HAC_RANDOM_SEED_LENGTH);
    }

    if (LddRetVal == E_OK)
    {
      LddRetVal = Csm_RandomSeedFinish(DCM_RANDOM_SEED_CSM_ID);
    }
    #endif /*(DCM_CRYPTO_R44_USED != STD_ON)*/
    if (LddRetVal == E_OK)
    {
      Dcm_GblSetHaePseudoSeed = DCM_TRUE;
    }
    /* polyspace-end DEFECT:DEAD_CODE MISRA-C3:14.3,2.1 [Justified:Low] "LddRetVal depend on retured value and it will must be E_OK and other function shall be called " */
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspGetRandomNum                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function generate random number                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : randomLength                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : random                                              **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_USE_CSM_TRUE_RANDOM_GENERATE_ICUS == STD_OFF) \
 && (DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM == STD_OFF))
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetRandomNum(uint8* RandomNum,
  uint32 randomLength)
{
  Std_ReturnType LddRetVal;

  if ((RandomNum == NULL_PTR) || (randomLength != DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH))
  {
    LddRetVal = E_NOT_OK;
  }
  else
  {
    #if ((DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM == STD_ON) \
      || (DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE == STD_ON))
      LddRetVal = Csm_RandomGenerate(DCM_RANDOM_GENERATE_CSM_ID,RandomNum, randomLength);
    #elif (DCM_CRYPTO_R44_USED == STD_ON)
    uint32* resultLengthPtr = &randomLength;
      LddRetVal = Csm_RandomGenerate(Dcm_GaaSecureAccessCryptoConnectionConfig[DCM_SECURITY_CONFIG_L21_R44_INDEX].ulRandomJobId, \
      RandomNum, resultLengthPtr);
    #endif

    #if (DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE == STD_ON)
    if (LddRetVal == CSM_E_ENTROPY_EXHAUSTION)
    {
      Dcm_GblSetHaePseudoSeed = DCM_FALSE;
      LddRetVal = Dcm_DspDoRandomSeed();

      if (LddRetVal == E_OK)
      {
        LddRetVal = Csm_RandomGenerate(DCM_RANDOM_GENERATE_CSM_ID,
          RandomNum, randomLength);
      }
    }
    #elif (DCM_CRYPTO_R44_USED == STD_ON)
    if (LddRetVal == CRYPTO_E_ENTROPY_EXHAUSTION)
    {
      Dcm_GblSetHaePseudoSeed = DCM_FALSE;
      LddRetVal = Dcm_DspDoRandomSeed();
      if (LddRetVal == E_OK)
      {
        uint32* resultLengthPtr = &randomLength;
        LddRetVal = Csm_RandomGenerate(Dcm_GaaSecureAccessCryptoConnectionConfig[DCM_SECURITY_CONFIG_L21_R44_INDEX].ulRandomJobId, \
          RandomNum, resultLengthPtr);
      }
    }
    #endif
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspGetSeedForSA                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Dcm_DspGetSeedForSA provides a means not only  **
**                        to process secure access for signature but also to  **
**                        get seed data.                                      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Seed, Error                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : DCM_ES95489_SUPPORT                                 **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspGetSeed(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pSecurityAccessRecord,
  Dcm_OpStatusType LucOpStatus, 
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pSeed,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;
  uint8 LucIndex;

  if (DCM_INITIAL == LucOpStatus)
  {
    Dcm_Secure_Init();
  }

  switch (Dcm_GddCertProgress)
  {
  case DCM_CP_READY:
    if (Dcm_GddCertStage == DCM_CS_READY)
    {
      if (Dcm_GddCertAlgorithmStep == DCM_CAS_READY)
      {
        uint8 LaaPublicKey[DCM_PUBLICKEY_MODULUS] = {0U};
		    

		/* Get the server's public key from FBL */
        Dcm_GetPublicKey(LaaPublicKey);
        #if (DCM_CRYPTO_R44_USED != STD_ON)
        uint8 LaaTempExponent[4];
        #if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
        LaaTempExponent[0] = 0x01U;
        LaaTempExponent[1] = 0x00U;
        LaaTempExponent[2] = 0x01U;
        LaaTempExponent[3] = 0x00U;  
        #else
        LaaTempExponent[0] = 0x00U;
        LaaTempExponent[1] = 0x01U;
        LaaTempExponent[2] = 0x00U;
        LaaTempExponent[3] = 0x01U; 
        #endif

        Dcm_GddSignPublicKey.length = DCM_PUBLICKEY_MODULUS + 4U;

        (void)Dcm_DspSecure_MemCopy((uint8*)(Dcm_GddSignPublicKey.data),
          LaaPublicKey, DCM_PUBLICKEY_MODULUS);

        (void)Dcm_DspSecure_MemCopy(
          (uint8*)&(Dcm_GddSignPublicKey.data[(DCM_PUBLICKEY_MODULUS) / sizeof(Csm_AlignType)]),
          LaaTempExponent, 4);
          #elif (DCM_CRYPTO_R44_USED == STD_ON)
            Dcm_GddSignPublicKey.length = DCM_PUBLICKEY_MODULUS + 38U;

            uint8 LaaStartTempExponent[33] = { 0x30U, 0x82U, 0x01U, 0x22U, 0x30U, 0x0DU, 0x06U, 0x09U, 0x2AU, 0x86U, 0x48U, 0x86U, 0xF7U, 0x0DU, 0x01U, 0x01U,
                                              0x01U, 0x05U, 0x00U, 0x03U, 0x82U, 0x01U, 0x0FU, 0x00U, 0x30U, 0x82U, 0x01U, 0x0AU, 0x02U, 0x82U, 0x01U, 0x01U,
                                              0x00U };
            (void)Dcm_DspSecure_MemCopy((uint8*)(Dcm_GddSignPublicKey.data), LaaStartTempExponent, 33);
            (void)Dcm_DspSecure_MemCopy((uint8*)&(Dcm_GddSignPublicKey.data[33U]), LaaPublicKey, DCM_PUBLICKEY_MODULUS);
            uint8 LaaEndTempExponent[5] = { 0x02U, 0x03U, 0x01U, 0x00U, 0x01U };
            (void)Dcm_DspSecure_MemCopy((uint8*)&(Dcm_GddSignPublicKey.data[33U+DCM_PUBLICKEY_MODULUS]), LaaEndTempExponent, 5);
          #endif /*(DCM_CRYPTO_R44_USED != STD_ON)*/
        #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
        {
          uint8 LaaTempHashExponent[4] = { 0x00U, 0x01U, 0x00U, 0x01U };
	        /* public key for hash  */
	         Dcm_GddHashPublicKeyVal.length = DCM_PUBLICKEY_MODULUS + 4U;

	        (void)Dcm_DspSecure_MemCopy(
	            (uint8*)&(Dcm_GddHashPublicKeyVal.data), LaaTempHashExponent, 4);

	        (void)Dcm_DspSecure_MemCopy((uint8*)&(Dcm_GddHashPublicKeyVal.data[4U]),
	          LaaPublicKey, DCM_PUBLICKEY_MODULUS);
        }
        #endif
          
          (void)Dcm_DspSecure_MemCopy(Dcm_GaaSecureData, pSecurityAccessRecord,
            (PLAINDATA + DCM_CERTIFICATE_SIGNATURE));
          #if (DCM_CRYPTO_R44_USED != STD_ON)
        if (Csm_SignatureVerifyStart(DCM_SIGNATURE_VERIFY_CSM_ID, &Dcm_GddSignPublicKey) == E_OK)
        {

          LddRetVal = DCM_SECURE_PENDING;

          Dcm_GddCertStage = DCM_CS_SERVER_CERT; /* Server signature verification */
          Dcm_GddCertProgress = DCM_CP_DOING;
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_START;
        }
          #elif (DCM_CRYPTO_R44_USED == STD_ON)
          LddRetVal = Csm_KeyElementSet(
            Dcm_GaaSecureAccessCryptoConnectionConfig[DCM_SECURITY_CONFIG_L21_R44_INDEX].ulPublicKeyId,
            0x01, /*This Value must be set 0x01*/
            Dcm_GddSignPublicKey.data,
            Dcm_GddSignPublicKey.length
          );
          if (LddRetVal == E_OK)
          {
            LddRetVal = Csm_KeySetValid(Dcm_GaaSecureAccessCryptoConnectionConfig[DCM_SECURITY_CONFIG_L21_R44_INDEX].ulPublicKeyId);
          }
          if (LddRetVal == E_OK)
          {
            LddRetVal = Csm_SignatureVerify(
              Dcm_GaaSecureAccessCryptoConnectionConfig[DCM_SECURITY_CONFIG_L21_R44_INDEX].ulCertVerifyJobId,
              CRYPTO_OPERATIONMODE_SINGLECALL,
              Dcm_GaaSecureData,
              PLAINDATA,
              &Dcm_GaaSecureData[PLAINDATA],
              DCM_CERTIFICATE_SIGNATURE,
              &Dcm_GddVerifyResult); 
          }
          if (LddRetVal == E_OK)
          {
            LddRetVal = DCM_SECURE_PENDING;
            Dcm_GddCertStage = DCM_CS_SERVER_CERT; 
            Dcm_GddCertProgress = DCM_CP_DOING;
            Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_CERT_SIGNATUREVERIFY;
          }
          #endif
        else
        {
          #if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
          if (Dcm_GstMsgContext.reqData[0] == 0x01U)
          {
            /*
              NRC 0x51
              Signature of the Certificate could not be verified.
            */
            *pErrorCode =  DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSIGNATURE;
          }
          else
          #endif
          {
            *pErrorCode = DCM_E_SECURITYACCESSDENIED;
          }
          LddRetVal = E_NOT_OK;
        }
      }
      else
      {
      }
    }
    else
    {
    }    
    break;
	
  #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
  case DCM_CP_CRL_READY:
  {
    uint32 ExpirationDate;
    Dcm_DspParsePlaintext(Dcm_GaaSecureData);

    /*  1. date check  */
    if(NULL_PTR != Dcm_GaaCbkPresentDate.pGetPresentDateFun)
    {
      (void)Dcm_GaaCbkPresentDate.pGetPresentDateFun(Dcm_GaaPresentDate);
    }
    Dcm_GaaConvPresendDate = 
	(uint32)((uint32)((Dcm_GaaPresentDate[0]) 	<< 16U) +
    (uint32)((Dcm_GaaPresentDate[1]) 			<< 8U) +  
	(uint32)(Dcm_GaaPresentDate[2]));

    Dcm_GaaConvPresendDate = Dcm_DspConvertNum(Dcm_GaaConvPresendDate);

    ExpirationDate = (uint32)((uint32)((Dcm_GaaExpirationDate[0]) << 16U) +
                  (uint32)((Dcm_GaaExpirationDate[1]) << 8U) +  (uint32)(Dcm_GaaExpirationDate[2]));

    ExpirationDate = Dcm_DspConvertNum(ExpirationDate);


    if((Dcm_GaaConvPresendDate != 0) && (Dcm_GaaConvPresendDate <= ExpirationDate))    
    {
      /* 7. CRL Integrity check  */
        P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRecord;
        if (Dcm_GstMsgContext.reqData[0] == 0x01U) /*subfunction verifyCertificateUnidirectional*/
        {
          pRecord = &Dcm_GstMsgContext.reqData[4];
        }
        else /*subfunction others*/
        {
          pRecord = &Dcm_GstMsgContext.reqData[1];
        }
        (void)Dcm_DspSecure_MemCopy(Dcm_GaaSecureData, &pRecord[PLAINDATA + DCM_CERTIFICATE_SIGNATURE], Dcm_GaaCRLLength);

        #ifdef DCM_SIGNATURE_VERIFY_CRL_CSM_ID
        if (Csm_SignatureVerifyStart(DCM_SIGNATURE_VERIFY_CRL_CSM_ID, &Dcm_GddSignPublicKey) == E_OK)
        {
        LddRetVal = DCM_SECURE_PENDING;

        Dcm_GddCertStage = DCM_CS_CRL_CERT; /* Server signature verification => need to change */ 
        Dcm_GddCertProgress = DCM_CP_DOING;
        Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_START;
      }
      else
      #endif
        #if (DCM_CRYPTO_R44_USED == STD_ON)
        LddRetVal = Csm_KeyElementSet(
          Dcm_GaaSecureAccessCryptoConnectionConfig[DCM_SECURITY_CONFIG_L21_R44_INDEX].ulPublicKeyId,
          0x01, /*This Value must be set 0x01*/
          Dcm_GddSignPublicKey.data,
          Dcm_GddSignPublicKey.length
        );
        if (E_OK == LddRetVal)
      {
          LddRetVal = Csm_KeySetValid(Dcm_GaaSecureAccessCryptoConnectionConfig[DCM_SECURITY_CONFIG_L21_R44_INDEX].ulPublicKeyId);
        }
        if (E_OK == LddRetVal)
        {
          LddRetVal = Csm_SignatureVerify(
          Dcm_GaaSecureAccessCryptoConnectionConfig[DCM_SECURITY_CONFIG_L21_R44_INDEX].ulCRLVerifyJobId,
          CRYPTO_OPERATIONMODE_SINGLECALL,
          Dcm_GaaSecureData,
          CRL_PLAINDATA,
          &Dcm_GaaSecureData[Dcm_GaaCRLLength - DCM_CRL_SIGNATURE],
          DCM_CRL_SIGNATURE,
          &Dcm_GddVerifyResult); 
        }
        if (E_OK == LddRetVal)
        {
          LddRetVal = DCM_SECURE_PENDING;
          Dcm_GddCertStage = DCM_CS_CRL_CERT; 
          Dcm_GddCertProgress = DCM_CP_DOING;
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_CRL_SIGNATUREVERIFY;
        }
        else
        #endif /*(DCM_CRYPTO_R44_USED == STD_ON)*/
        {
          *pErrorCode = DCM_E_CRLINTEGRITYCHECKFAILED;
        LddRetVal = E_NOT_OK;
      }       

    }
    else
    {
      #if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
      if (Dcm_GstMsgContext.reqData[0] == 0x01U)
      {
      /* NRC 0x50
      * Date and time of the server does not match 
      * the validity period of the Certificate
      */
      *pErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTIMEPERIOD;
      }
      else
      #endif
      {
      *pErrorCode = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
      }
      LddRetVal = E_NOT_OK;       
    }


    break;
    }

  case DCM_CP_CRL_KEYID_READY:
    {

    /* 6. CRL Key Identifier Check - public key hash */
    #ifdef DCM_SHA256_CRL_CSM_ID
    if (Csm_HashStart(DCM_SHA256_CRL_CSM_ID) == E_OK)
    {
      LddRetVal = DCM_SECURE_PENDING;

      Dcm_GddCertStage = DCM_CS_CRL_KEYID;
      Dcm_GddCertProgress = DCM_CP_DOING;
      Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_START;
    }
    else
    #endif
      #if (DCM_CRYPTO_R44_USED == STD_ON)
      Dcm_GaaCRLDigestLength = 32;
      LddRetVal = Csm_Hash(
        Dcm_GaaSecureAccessCryptoConnectionConfig[DCM_SECURITY_CONFIG_L21_R44_INDEX].ulCRLHashJobId,
        CRYPTO_OPERATIONMODE_SINGLECALL,
        Dcm_GddHashPublicKeyVal.data,
        Dcm_GddHashPublicKeyVal.length,
        Dcm_GaaCertDigest,
        &Dcm_GaaCRLDigestLength
      );
      if (E_OK == LddRetVal)
    {
        LddRetVal = DCM_SECURE_PENDING;
        Dcm_GddCertStage = DCM_CS_CRL_KEYID;
        Dcm_GddCertProgress = DCM_CP_SUCCESS;
        Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_FINISH;
      }
      else
      #endif /*(DCM_CRYPTO_R44_USED == STD_ON)*/
      {
        *pErrorCode = DCM_E_CRLINTEGRITYCHECKFAILED;
      LddRetVal = E_NOT_OK;
    }

      }
    break;
  #endif
  case DCM_CP_DOING:
    LddRetVal = DCM_SECURE_PENDING;
    break;

  case DCM_CP_SUCCESS:
  {
    #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
    boolean checkFail = DCM_FALSE;
    uint8 count;

    Dcm_DspParseCRLPlaintext(Dcm_GaaSecureData);

    /* 6. Public key Identifier check */
    checkFail = DCM_FALSE;
    for(count = 0; count < DCM_CRL_CERT_AUTHORITY_KEYID ; count++)
    {
      if(Dcm_GaaCertDigest[count] != Dcm_GaaCRLCertAuthorityKeyID[count])
      {
        checkFail = DCM_TRUE;
        break;
      }
    }

    if(checkFail == DCM_FALSE)
    {
      /*  1. CRL ExpirationDate Check */
      uint32 ExpirationDate;

      ExpirationDate = (uint32)((uint32)((Dcm_GaaCRLExpirationDate[0]) << 16U) +
                    (uint32)((Dcm_GaaCRLExpirationDate[1]) << 8U) +  (uint32)(Dcm_GaaCRLExpirationDate[2]));

      ExpirationDate = Dcm_DspConvertNum(ExpirationDate);

      if((Dcm_GaaConvPresendDate != 0) && (Dcm_GaaConvPresendDate <= ExpirationDate))
      {
        /*  2. Authority Reference Check  */
        for(count = 0; count < DCM_AUTHORITY_REFERENCE ; count++)
        {
          if(Dcm_GaaCertAuthorityReference[count] != Dcm_GaaCRLIssuer[count])
          {
            checkFail = DCM_TRUE;
            break;
          }
        }

        if(checkFail == DCM_FALSE)
        {

          uint32 holderReference, crlDistributionPoint, crlCertGroupCount;
          holderReference = (uint32)(((Dcm_GaaCertHolderReference[12]) << 24U) +  (uint32)((Dcm_GaaCertHolderReference[13]) << 16U) +
                            (uint32)((Dcm_GaaCertHolderReference[14]) << 8U) +  (uint32)(Dcm_GaaCertHolderReference[15]));

          holderReference = Dcm_DspConvertNum(holderReference);
          crlDistributionPoint = (uint32)(((Dcm_GaaCRLDistributionPointName[12]) << 24U) +  (uint32)((Dcm_GaaCRLDistributionPointName[13]) << 16U) +
                            (uint32)((Dcm_GaaCRLDistributionPointName[14]) << 8U) +  (uint32)(Dcm_GaaCRLDistributionPointName[15]));

          crlDistributionPoint = Dcm_DspConvertNum(crlDistributionPoint);

          crlCertGroupCount = (uint32)(((Dcm_GaaCRLCertGroupCount[0]) << 24U) +  (uint32)((Dcm_GaaCRLCertGroupCount[1]) << 16U) +
                            (uint32)((Dcm_GaaCRLCertGroupCount[2]) << 8U) +  (uint32)(Dcm_GaaCRLCertGroupCount[3]));

          crlCertGroupCount = Dcm_DspConvertNum(crlCertGroupCount);

          /*  3. Company, Group Information Check */

          if((crlCertGroupCount != 0) && ((((holderReference -1U)/crlCertGroupCount)+1U ) == crlDistributionPoint))
          {

            /*  4. CRL Distribution Point Check */
            checkFail = DCM_FALSE;
            for(count = 0; count < (DCM_HOLDER_REFERENCE-4U) ; count++)
            {
              if(Dcm_GaaCertHolderReference[count] != Dcm_GaaCRLDistributionPointName[count])
              {
                checkFail = DCM_TRUE;
                break;
              }
            }

            if(checkFail == DCM_FALSE)
            {
              uint32 startSeqNum;
              startSeqNum = (uint32)(((Dcm_GaaCRLRevokedCertStartSeqNum[0]) << 24U) +  (uint32)((Dcm_GaaCRLRevokedCertStartSeqNum[1]) << 16U) +
                            (uint32)((Dcm_GaaCRLRevokedCertStartSeqNum[2]) << 8U) +  (uint32)(Dcm_GaaCRLRevokedCertStartSeqNum[3]));

              startSeqNum = Dcm_DspConvertNum(startSeqNum);

              /*   5. CRL Start num check */
              if( (((holderReference / crlCertGroupCount) * crlCertGroupCount) +1U ) == startSeqNum)
              {

                
                /* 8. CRL check */
                boolean isCrlList = DCM_FALSE;
                uint32 crlCount;
                uint32 certStatusSize;
                uint8 mBit;

                certStatusSize = (uint32)(((Dcm_GaaCRLCertStatusSize[0]) << 24U) +  (uint32)((Dcm_GaaCRLCertStatusSize[1]) << 16U) +
                                 (uint32)((Dcm_GaaCRLCertStatusSize[2]) << 8U) +  (uint32)(Dcm_GaaCRLCertStatusSize[3]));


                certStatusSize = Dcm_DspConvertNum(certStatusSize);

                if(certStatusSize > DCM_CRL_CERT_STATUSBITS_MAX_SIZE )
                {
                  certStatusSize = DCM_CRL_CERT_STATUSBITS_MAX_SIZE;
                }

                /* Validity Check */
                for(crlCount = 0 ; crlCount < certStatusSize; crlCount++)
                {
                  for(mBit = 0 ; mBit < 8U; mBit++)
                  {
                    if( ((Dcm_GaaCRLCertStatusBits[crlCount] << mBit) & 0x80) == 0x80)
                    {
                         if((startSeqNum+(crlCount*8U)+mBit) == holderReference)
                           {
                              isCrlList = DCM_TRUE;
                              break;
                           }
                     }
                   }

                  if(isCrlList == DCM_TRUE)
                  {
                    #if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
                    if (Dcm_GstMsgContext.reqData[0] == 0x01U)
                    {
                    *pErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCERTIFICATE;
                    }
                    else
                    #endif
                    {
                    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
                    }
                    LddRetVal = E_NOT_OK;
                    break;
                  }
                }

              }
              else
              {
                #if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
                if (Dcm_GstMsgContext.reqData[0] == 0x01U)
                {
                *pErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSCOPE;
                }
                else
                #endif
                {
                *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
                }
                LddRetVal = E_NOT_OK;       
              } 
            }
            else
            {
              #if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
              if (Dcm_GstMsgContext.reqData[0] == 0x01U)
              {
              
              *pErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSCOPE;
              }
              else
              #endif
              {
              *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
              }
              LddRetVal = E_NOT_OK;       
            }
          }
          else
          {     
            #if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
            if (Dcm_GstMsgContext.reqData[0] == 0x01U)
            {
            *pErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSCOPE;
            }
            else
            #endif
            {
            *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
            }
            LddRetVal = E_NOT_OK;       
          }
        }
        else
        {
          #if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
          if (Dcm_GstMsgContext.reqData[0] == 0x01U)
          {
          *pErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSCOPE;
          }
          else
          #endif
          {
          *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
          }
          LddRetVal = E_NOT_OK;       
        }

      }
      else
      {
        *pErrorCode = DCM_E_CRLEXPIRED;
        LddRetVal = E_NOT_OK;       
      }
    }
    else
    {
      *pErrorCode = DCM_E_CRLINTEGRITYCHECKFAILED;
      LddRetVal = E_NOT_OK;
    }

    #else
      Dcm_DspParsePlaintext(Dcm_GaaSecureData);
    #endif

    /* polyspace +2 DEFECT:DEAD_CODE DEFECT:USELESS_IF MISRA-C3:14.3 [Justified:low] "LddRetVal can be E_NOT_OK accrording to the result of Csm_SignatureVerifyStart." */
    if (LddRetVal != E_NOT_OK)
    {
      #if ((DCM_USE_CSM_TRUE_RANDOM_GENERATE_ICUS == STD_ON) \
        || (DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM == STD_ON))

      if ( (Dcm_GddCertStage == DCM_CS_SERVER_CERT) || (Dcm_GddCertStage == DCM_CP_CRL_KEYID_READY))
      {
        Dcm_GddCertStage = DCM_CS_MAKE_RANDOM;
        Dcm_GddCertProgress = DCM_CP_DOING;
        Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_START;
        /* Async function */
        #if (DCM_USE_CSM_TRUE_RANDOM_GENERATE_ICUS == STD_ON)
        /* RH850 F1K */
        LddRetVal = Csm_RandomGenerate(DCM_RANDOM_GENERATE_CSM_ID,
          pSeed, DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH);
        #elif (DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM == STD_ON)
        /* RH850 F1KM */
        LddRetVal = Csm_RandomGenerate(DCM_RANDOM_GENERATE_CSM_ID,
          Dcm_GaaRandom, DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH);
        #endif

        if (LddRetVal == E_OK)
        {
          LddRetVal = DCM_SECURE_PENDING;
        }
        else
        {
          #if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
          if (Dcm_GstMsgContext.reqData[0] == 0x01U)
          {
            /*
              NRC 0x51
              Signature of the Certificate could not be verified.
            */
            *pErrorCode =  DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSIGNATURE;
          }
          else
          #endif
          {
            *pErrorCode = DCM_E_SECURITYACCESSDENIED;
          }
          LddRetVal = E_NOT_OK;
        }
      }
      else if (Dcm_GddCertStage == DCM_CS_MAKE_RANDOM)
      {
        #if (DCM_USE_CSM_TRUE_RANDOM_GENERATE_HSM_ICUM == STD_ON)
    	  (void)Dcm_DspSecure_MemCopy(pSeed, Dcm_GaaRandom,
          DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH);
        #endif
        for (LucIndex = 0; LucIndex < DCM_SECURE_SEED_SIZE; LucIndex++)
        {
          Dcm_GaaSecureSeed[LucIndex] = pSeed[LucIndex];
        }

        Dcm_Secure_Init();
      }
      else
      {
      
      }

      #else
    
      #if (DCM_USE_CSM_PSEUDO_RANDOM_GENERATE_HAE == STD_ON) || (DCM_CRYPTO_R44_USED == STD_ON)
      LddRetVal = Dcm_DspDoRandomSeed();

      if (LddRetVal == E_OK)
      {
        LddRetVal = Dcm_DspGetRandomNum(pSeed, DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH);
      }
      #else 
      LddRetVal = Dcm_DspGetRandomNum(pSeed, DCM_SECURE_ACCESS_RANDOM_GEN_LENGTH);
      #endif

      if (LddRetVal == E_OK)
      {
        for (LucIndex = 0; LucIndex < DCM_SECURE_SEED_SIZE; LucIndex++)
        {
          Dcm_GaaSecureSeed[LucIndex] = pSeed[LucIndex];
        }
      }
      else
      {
        #if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
        if (Dcm_GstMsgContext.reqData[0] == 0x01U)
        {
          /*
            NRC 0x51
            Signature of the Certificate could not be verified.
          */
          *pErrorCode =  DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSIGNATURE;
          }
          else
          #endif
          {
            *pErrorCode = DCM_E_SECURITYACCESSDENIED;
          }
          LddRetVal = E_NOT_OK;
        }

      Dcm_Secure_Init();

      #endif
    }
  }
  break;

  case DCM_CP_CRL_FAIL:
    *pErrorCode = DCM_E_CRLINTEGRITYCHECKFAILED;
    LddRetVal = E_NOT_OK;

    Dcm_Secure_Init();
    break;

  case DCM_CP_FAIL:
  default:
    {
    #if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
      if (Dcm_GstMsgContext.reqData[0] == 0x01U)
      {
        /*
        * NRC 0x51
        * Signature of the Certificate could not be verified
        */
      *pErrorCode = DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSIGNATURE;
      }
      else 
    #endif
      {
        *pErrorCode = DCM_E_SECURITYACCESSDENIED;
      }
    }

    LddRetVal = E_NOT_OK;

    Dcm_Secure_Init();
    break;
  }
  
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspCompareKey                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Dcm_DspGetSeedForSA provides a means not only  **
**                        to process secure access for signature but also to  **
**                        compare key data.                                   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Key, OpStatus                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : DCM_ES95489_SUPPORT                                 **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/

FUNC(Std_ReturnType, DCM_CODE) Dcm_DspCompareKey(
  P2CONST(uint8, AUTOMATIC, DCM_PRIVATE_DATA) LpReqResData, 
  VAR(uint8, AUTOMATIC) LucOpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;

  switch (Dcm_GddCertProgress)
  {
  case DCM_CP_READY:
    if (Dcm_GddCertAlgorithmStep == DCM_CAS_READY)
    {
      (void)Dcm_DspSecure_MemCopy(Dcm_GaaSecureData, LpReqResData, DCM_CERTIFICATE_SIGNATURE);
      #if (DCM_CRYPTO_R44_USED != STD_ON)
      if (Csm_SignatureVerifyStart(DCM_SIGNATURE_VERIFY_SEED_CSM_ID, &Dcm_GddTesterSignPublicKey) == E_OK)
      {

        LddRetVal = DCM_SECURE_PENDING;

        Dcm_GddCertStage = DCM_CS_TESTER_CERT; /* Tester signature*/
        Dcm_GddCertProgress = DCM_CP_DOING;
        Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_START;
      }
      else
      #elif (DCM_CRYPTO_R44_USED == STD_ON)
      #if (DCM_CNR_USED_SHA1 == STD_ON)
      LddRetVal = Dcm_SignatureVerify(
        Dcm_GaaSecureSeed,
        DCM_SECURE_SEED_SIZE,
        Dcm_GaaSecureData,
        DCM_CERTIFICATE_SIGNATURE,
        &Dcm_GddTesterSignPublicKey,
        &Dcm_GddVerifyResult); 
      #else
      LddRetVal = Csm_KeyElementSet(
        Dcm_GaaSecureAccessCryptoConnectionConfig[DCM_SECURITY_CONFIG_L21_R44_INDEX].ulCnRPublicKeyId,
        0x01,
        (uint8*)Dcm_GddTesterSignPublicKey.data,
        Dcm_GddTesterSignPublicKey.length
        );
      if (LddRetVal == E_OK)
      {
        LddRetVal = Csm_KeySetValid(Dcm_GaaSecureAccessCryptoConnectionConfig[DCM_SECURITY_CONFIG_L21_R44_INDEX].ulCnRPublicKeyId);
      }
      if (LddRetVal == E_OK)
      {
        LddRetVal = Csm_SignatureVerify(
        Dcm_GaaSecureAccessCryptoConnectionConfig[DCM_SECURITY_CONFIG_L21_R44_INDEX].ulCnRVerifyJobId,
        CRYPTO_OPERATIONMODE_SINGLECALL,
        Dcm_GaaSecureSeed,
        DCM_SECURE_SEED_SIZE,
        Dcm_GaaSecureData,
        DCM_CERTIFICATE_SIGNATURE,
        &Dcm_GddVerifyResult);   
      }
      #endif
      if (LddRetVal == E_OK)
      {
        LddRetVal = DCM_SECURE_PENDING;
        Dcm_GddCertStage = DCM_CS_TESTER_CERT; /* Tester signature*/
        #if (DCM_CNR_USED_SHA1 == STD_ON)
        Dcm_GddCertProgress = DCM_CP_SUCCESS;
        #else
        Dcm_GddCertProgress = DCM_CP_DOING;
        #endif
        Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_TESTER_SIGNATUREVERIFY;
      }
      else
      #endif
      {
        LddRetVal = E_NOT_OK;
      }
    }
    break;

  case DCM_CP_DOING:
    LddRetVal = DCM_SECURE_PENDING;
    break;

  case DCM_CP_SUCCESS:
    /* copy Certificate Expiration Date */
    (void)Dcm_DspSecure_MemCopy(Dcm_GstCertificationInfo.expirationDate, 
      Dcm_GaaExpirationDate, DCM_EXPERATION_DATE);

    /* copy Certificate Holder Authorization */
    (void)Dcm_DspSecure_MemCopy(Dcm_GstCertificationInfo.authorization, 
      Dcm_GaaAuthorizationRole, DCM_HOLDER_ROLE);

    #if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
	/* 03: Authentication subfunction proofOfOwnership */
    if (Dcm_GstMsgContext.reqData[0] == 0x03U)
    {
      P2VAR(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_DATA) pPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddRxPduId];
      uint8 AuthenticationIdIndex = Dcm_GetAuthConnectionIndex(pPduIdTable->usMainConnectionId);
	  if (AuthenticationIdIndex != AUTHENTICATION_CONNECTION_ID_NOT_CONFIGURED)
	  {
	      if((Dcm_GaaAuthenticationConnectionESConfig[AuthenticationIdIndex].ucAuthenticationUsePort == USE_ASYNCH_CLIENT_SERVER) ||
	          (Dcm_GaaAuthenticationConnectionESConfig[AuthenticationIdIndex].ucAuthenticationUsePort == USE_ASYNCH_FNC))
	      {
	        if (NULL_PTR != Dcm_GaaAuthenticationConnectionESConfig[AuthenticationIdIndex].pAsyncSettingAccessRightsFailedFun)
	        {
	          LddRetVal = Dcm_GaaAuthenticationConnectionESConfig[AuthenticationIdIndex].pAsyncSettingAccessRightsFailedFun
	          (&Dcm_GstCertificationInfo.authorization, pErrorCode);
	        }
	      }
	      else
	      {
	        /* Nothing */
	      }
	  }
	  else
	  {
	    /*Nothing*/
	  }
    }
    #endif
    
    Dcm_Secure_Init();
    break;

  case DCM_CP_FAIL:
  default:
    LddRetVal = E_NOT_OK;

    Dcm_Secure_Init();
    break;
  }
  DCM_UNUSED(LucOpStatus);

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspVerifySignatureSeedCbk                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Dcm_DspVerifySignatureSeedCbk provides a means **
**                        not only to process secure access for signature but **
**                        also to compare key data.                           **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Key, OpStatus                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : DCM_ES95489_SUPPORT                                 **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_CRYPTO_R44_USED != STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspVerifySignatureSeedCbk(Std_ReturnType RetVal)
#elif (DCM_CRYPTO_R44_USED == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspVerifySignatureSeedCbk(const uint32 jobID, Csm_ResultType RetVal)
#endif
{
  if(E_OK == RetVal)
  {
    switch (Dcm_GddCertStage)
    {
    case DCM_CS_SERVER_CERT:
      switch (Dcm_GddCertAlgorithmStep)
      {
      #if (DCM_CRYPTO_R44_USED != STD_ON)
      case DCM_CAS_REQ_START:
        if (Csm_SignatureVerifyUpdate(DCM_SIGNATURE_VERIFY_CSM_ID, Dcm_GaaSecureData, PLAINDATA) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_UPDATE;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        break;

      case DCM_CAS_REQ_UPDATE:
        if (Csm_SignatureVerifyFinish(DCM_SIGNATURE_VERIFY_CSM_ID, &Dcm_GaaSecureData[PLAINDATA],
          DCM_CERTIFICATE_SIGNATURE, &Dcm_GddVerifyResult) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_FINISH;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        break;

      case DCM_CAS_REQ_FINISH:
        if (Dcm_GddVerifyResult == CSM_E_VER_OK)
        {
          #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
            Dcm_GddCertProgress = DCM_CP_CRL_READY;
          #else
            Dcm_GddCertProgress = DCM_CP_SUCCESS;
          #endif
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
        break;

      #elif (DCM_CRYPTO_R44_USED == STD_ON)
      case DCM_CAS_REQ_CERT_SIGNATUREVERIFY:
        if (Dcm_GddVerifyResult == CRYPTO_E_VER_OK)
        {
          #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
            Dcm_GddCertProgress = DCM_CP_CRL_READY;
          #else
            Dcm_GddCertProgress = DCM_CP_SUCCESS;
          #endif
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
        break;
      #endif /*(DCM_CRYPTO_R44_USED != STD_ON)*/
      default:
	/* Do Nothing */
        break;
      }
      break;
      
    #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
    case DCM_CS_CRL_CERT:
      switch (Dcm_GddCertAlgorithmStep)
      {
      #if (DCM_CRYPTO_R44_USED == STD_OFF)
      case DCM_CAS_REQ_START:
        #ifdef DCM_SIGNATURE_VERIFY_CRL_CSM_ID
        if (Csm_SignatureVerifyUpdate(DCM_SIGNATURE_VERIFY_CRL_CSM_ID, Dcm_GaaSecureData, (Dcm_GaaCRLLength-DCM_CRL_SIGNATURE)) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_UPDATE;
        }
        else
        #endif
        {
          Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
        }
        break;

      case DCM_CAS_REQ_UPDATE:
        #ifdef DCM_SIGNATURE_VERIFY_CRL_CSM_ID
        if (Csm_SignatureVerifyFinish(DCM_SIGNATURE_VERIFY_CRL_CSM_ID, &Dcm_GaaSecureData[Dcm_GaaCRLLength-DCM_CRL_SIGNATURE],
          DCM_CRL_SIGNATURE, &Dcm_GddVerifyResult) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_FINISH;
        }
        else
        #endif
        {
          Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
        }
        break;

      case DCM_CAS_REQ_FINISH:
        if (Dcm_GddVerifyResult == CSM_E_VER_OK)
        {
          Dcm_GddCertProgress = DCM_CP_CRL_KEYID_READY;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
        }
        Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
        break;
      #elif (DCM_CRYPTO_R44_USED == STD_ON)
      case DCM_CAS_REQ_CRL_SIGNATUREVERIFY:
        if (Dcm_GddVerifyResult == CRYPTO_E_VER_OK)
        {
          Dcm_GddCertProgress = DCM_CP_CRL_KEYID_READY;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
        }
        Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_FINISH;
        break;
      #endif /*(DCM_CRYPTO_R44_USED != STD_ON)*/

      default:
	      /* Do Nothing */
        break;
      }
      break;

     case DCM_CS_CRL_KEYID:
      switch (Dcm_GddCertAlgorithmStep)
      {
      #if (DCM_CRYPTO_R44_USED == STD_OFF)
      case DCM_CAS_REQ_START:
        #ifdef DCM_SHA256_CRL_CSM_ID
        if (Csm_HashUpdate(DCM_SHA256_CRL_CSM_ID, Dcm_GddHashPublicKeyVal.data , Dcm_GddHashPublicKeyVal.length) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_UPDATE;
        }
        else
        #endif
        {
          Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
        }
        break;

      case DCM_CAS_REQ_UPDATE:
      {
    	  Dcm_GaaCRLDigestLength = 32;
        #ifdef DCM_SHA256_CRL_CSM_ID
        if (Csm_HashFinish(DCM_SHA256_CRL_CSM_ID, Dcm_GaaCertDigest,
          &Dcm_GaaCRLDigestLength, DCM_FALSE) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_FINISH;
        }
        else
        #endif
        {
          Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
        }
        break;
      }
      #endif /*(DCM_CRYPTO_R44_USED != STD_ON)*/

      case DCM_CAS_REQ_FINISH:
        #if (DCM_CRYPTO_R44_USED == STD_ON)
        if (Dcm_GddVerifyResult == CRYPTO_E_VER_OK)
        #elif (DCM_CRYPTO_R44_USED != STD_ON)
        if (Dcm_GddVerifyResult == CSM_E_VER_OK)
        #endif
        {
          Dcm_GddCertProgress = DCM_CP_SUCCESS;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
        }
        Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
        break;

      default:
	      /* Do Nothing */
        break;
      }
      break;
   #endif
      

    case DCM_CS_MAKE_RANDOM:
      if (Dcm_GddCertAlgorithmStep == DCM_CAS_REQ_START)
      {
        Dcm_GddCertProgress = DCM_CP_SUCCESS;
      }
      Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
      break;

    case DCM_CS_TESTER_CERT:
      switch (Dcm_GddCertAlgorithmStep)
      {
      #if (DCM_CRYPTO_R44_USED == STD_OFF)
      case DCM_CAS_REQ_START:
        if (Csm_SignatureVerifyUpdate(DCM_SIGNATURE_VERIFY_SEED_CSM_ID, Dcm_GaaSecureSeed,
          DCM_SECURE_SEED_SIZE) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_UPDATE;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        break;

      case DCM_CAS_REQ_UPDATE:
        if (Csm_SignatureVerifyFinish(DCM_SIGNATURE_VERIFY_SEED_CSM_ID, Dcm_GaaSecureData,
          DCM_CERTIFICATE_SIGNATURE, &Dcm_GddVerifyResult) == E_OK)
        {
          Dcm_GddCertAlgorithmStep = DCM_CAS_REQ_FINISH;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        break;

      case DCM_CAS_REQ_FINISH:
        if (Dcm_GddVerifyResult == CSM_E_VER_OK)
        {
          Dcm_GddCertProgress = DCM_CP_SUCCESS;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
        break;
	  #elif (DCM_CRYPTO_R44_USED == STD_ON)
      case DCM_CAS_REQ_TESTER_SIGNATUREVERIFY:
        if (Dcm_GddVerifyResult == CRYPTO_E_VER_OK)
        {
          Dcm_GddCertProgress = DCM_CP_SUCCESS;
        }
        else
        {
          Dcm_GddCertProgress = DCM_CP_FAIL;
        }
        Dcm_GddCertAlgorithmStep = DCM_CAS_READY;
        break;
      #endif /*(DCM_CRYPTO_R44_USED != STD_ON)*/
      default:
	/* Do Nothing */
        break;
      }
      break;

    default:
      /* Do Nothing */
      break;
    }
  }
  else
  {
    if((Dcm_GddCertStage == DCM_CS_CRL_CERT) || (Dcm_GddCertStage == DCM_CS_CRL_KEYID))
    {
      Dcm_GddCertProgress = DCM_CP_CRL_FAIL;
    }
    else
    {
      Dcm_GddCertProgress = DCM_CP_FAIL;
    }

     
  }

  #if (DCM_CRYPTO_R44_USED == STD_ON)
  DCM_UNUSED(jobID);
  #elif (DCM_CRYPTO_R44_USED == STD_OFF)
  return E_OK;
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_GetCertificationInfo                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Dcm_GetCertificationInfo provides information  **
**                        of the certification to application.                **
**                                                                            **
** Sync/Async           : synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpCertifInfo                                        **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : DCM_ES95489_SUPPORT                                 **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_CSAC_CONFIGURED == STD_ON) || (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetCertificationInfo(
  P2VAR(Dcm_CertInfoType, AUTOMATIC, DCM_APPL_DATA) CertInfo)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 currentLevel;
  
  if(CertInfo!=NULL_PTR){
   SchM_Enter_Dcm_DATA_UPDATE();
    if (E_OK == Dcm_GetSecurityLevel(&currentLevel))
    {
      if ((Dcm_SecLevelType)33 == currentLevel)
      {
         /* copy Certificate Expiration Date */
        (void)Dcm_DspSecure_MemCopy(CertInfo->expirationDate, 
                    Dcm_GstCertificationInfo.expirationDate, DCM_EXPERATION_DATE);

        /* copy Certificate Holder Authorization */
        (void)Dcm_DspSecure_MemCopy(CertInfo->authorization, 
                         Dcm_GstCertificationInfo.authorization, DCM_HOLDER_ROLE);

        LddRetVal = E_OK;
      }
    }
    SchM_Exit_Dcm_DATA_UPDATE();
  }    

  return LddRetVal;
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#else
/* polyspace +7 MISRA-C3:8.13 [Justified:Low] "Dcm_GetCertificationInfo is the API that SWP should offer to user. 
   this API is always generated so the parameter CertInfo should be P2VAR and there's no defect on the code" */
#define DCM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetCertificationInfo(
  P2VAR(Dcm_CertInfoType, AUTOMATIC, DCM_APPL_DATA) CertInfo)
{
  DCM_UNUSED_PTR(CertInfo);
  return E_NOT_OK;
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* CSAC Algorithm */

/*******************************************************************************
 **                      End of File                                           **
 *******************************************************************************/
