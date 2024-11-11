/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : HSE
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_RTD_3_0_0_P01_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef CRYPTO_CFG_H
#define CRYPTO_CFG_H

/**
*   @file
*
*   @addtogroup CRYPTO
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Crypto_Types.h"
#include "hse_interface.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CRYPTO_VENDOR_ID_CFG                       43
#define CRYPTO_MODULE_ID_CFG                       114
#define CRYPTO_AR_RELEASE_MAJOR_VERSION_CFG        4
#define CRYPTO_AR_RELEASE_MINOR_VERSION_CFG        7
#define CRYPTO_AR_RELEASE_REVISION_VERSION_CFG     0
#define CRYPTO_SW_MAJOR_VERSION_CFG                3
#define CRYPTO_SW_MINOR_VERSION_CFG                0
#define CRYPTO_SW_PATCH_VERSION_CFG                0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if Crypto Cfg header file and Crypto Types header file are of the same vendor */
#if (CRYPTO_VENDOR_ID_CFG != CRYPTO_VENDOR_ID_TYPES)
    #error "Crypto_Cfg.h and Crypto_Types.h have different vendor ids"
#endif

/* Check if Crypto Cfg header file and Crypto Types header file are of the same Autosar version */
#if ((CRYPTO_AR_RELEASE_MAJOR_VERSION_CFG    != CRYPTO_AR_RELEASE_MAJOR_VERSION_TYPES) || \
     (CRYPTO_AR_RELEASE_MINOR_VERSION_CFG    != CRYPTO_AR_RELEASE_MINOR_VERSION_TYPES) || \
     (CRYPTO_AR_RELEASE_REVISION_VERSION_CFG != CRYPTO_AR_RELEASE_REVISION_VERSION_TYPES) \
    )
    #error "AutoSar Version Numbers of Crypto_Cfg.h and Crypto_Types.h are different"
#endif

/* Check if Crypto Cfg header file and Crypto Types header file are of the same Software version */
#if ((CRYPTO_SW_MAJOR_VERSION_CFG != CRYPTO_SW_MAJOR_VERSION_TYPES) || \
     (CRYPTO_SW_MINOR_VERSION_CFG != CRYPTO_SW_MINOR_VERSION_TYPES) || \
     (CRYPTO_SW_PATCH_VERSION_CFG != CRYPTO_SW_PATCH_VERSION_TYPES)    \
    )
    #error "Software Version Numbers of Crypto_Cfg.h and Crypto_Types.h are different"
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Pre-processor switch to enable/disable development error detection for Crypto API */
#define CRYPTO_DEV_ERROR_DETECT                         (STD_ON)

/* Pre-processor switch to enable/disable the API to read out the modules version information */
#define CRYPTO_VERSION_INFO_API                         (STD_OFF)

/* Crypto instance ID value */
#define CRYPTO_INSTANCE_ID                              ((uint8)0)

/* Set asynchronous job process method */
#define CRYPTO_USE_INTERRUPTS_FOR_ASYNC_JOBS            (STD_ON)

/* Crypto Timeout value */
#define CRYPTO_TIMEOUT_DURATION_U32                     ((uint32)1000000000U)

/* Pre-processor switch to enable/disable the support in Crypto_ProcessJob() for handling key management services */
#define CRYPTO_JOB_KEY_MANAGEMENT_SUPPORT               (STD_OFF)

/* Defines for the available MU instances */
#define CRYPTO_MU_0_U8                                  ((uint8)0U)
#define CRYPTO_MU_1_U8                                  ((uint8)1U)

/* Pre-processor switch to disable multicore support in Crypto driver */
#define CRYPTO_ENABLE_MULTICORE_SUPPORT                 (STD_OFF)

/* Max number of partitions configured from the application */
#define CRYPTO_MAX_NUMBER_PARTITIONS_U8                 ((uint8)1U)

/* Number of configured partitions the driver can run in */
#define CRYPTO_NUMBER_PARTITIONS_ALLOWED_TO_RUN_IN_U8   ((uint8)1U)

/* Number of configured Crypto driver objects */
#define CRYPTO_NUMBER_OF_DRIVER_OBJECTS_U32             ((uint32)1U)

/* Compile time switch stating that there is at least one configured key */
#define CRYPTO_KEYS_EXIST                               (STD_ON)

/* Number of Crypto keys */
#define CRYPTO_NUMBER_OF_KEYS_U32                       ((uint32)25U)

/* Number of Crypto key elements */
#define CRYPTO_NUMBER_OF_KEY_ELEMENTS_U32               ((uint32)24U)

/* Support for enabling alternate mapping of crypto job keys.
*       STD_ON:  the Crypto driver will read the key related information of Csm jobs from an alternate location which is the cryptoKeyId member of the Crypto_JobType structure.
*       STD_OFF: the Crypto driver will read the key related information of Csm jobs from the cryIfKeyId member of Crypto_JobPrimitiveInfoType substructure of the Crypto_JobType structure. */
#define CRYPTO_ENABLE_ALTERNATE_MAPPING_FOR_JOB_KEY     (STD_ON)

/* Switch for configuring the measure unit the Crypto driver will use for processing the secondaryInputLength parameter of a received MacVerify job.
*       STD_ON:  the Crypto driver will consider that the secondaryInputLength parameter of a received MacVerify job is measured in bits.
*       STD_OFF: the Crypto driver will consider that the secondaryInputLength parameter of a received MacVerify job is measured in bytes. */
#define CRYPTO_SECINPUTLEN_FOR_MACVERIFY_JOBS_USES_BITS (STD_OFF)

/* Switch for configuring the measure unit the Crypto driver will use for processing the inputLength and resultLength parameters of a received FastCmac job.
*       STD_ON:  the Crypto driver will consider that the inputLength and resultLength parameters of a received FastCmac job are measured in bytes.
*       STD_OFF: the Crypto driver will consider that the inputLength and resultLength parameters of a received FastCmac job are measured in bits. */
#define CRYPTO_LENGTHS_FOR_FASTCMAC_JOBS_USE_BYTES      (STD_OFF)

/* Identifiers for the blobs of information that need to be stored in NVRAM used by the Crypto driver */
#define CRYPTO_NVRAM_BLOB_0_ID                          (0U)
#define CRYPTO_NVRAM_BLOB_1_ID                          (1U)

/* Sizes for the blobs of information used by the Crypto driver */
#define CRYPTO_SIZEOF_NVRAM_BLOB_0                      (4U)
#define CRYPTO_SIZEOF_NVRAM_BLOB_1                      (56U)


/* Compile time switch stating that support for Nvram read/write operations is enabled or disabled */
#define CRYPTO_ENABLE_NVRAM_READ_WRITE_SUPPORT          (STD_OFF)

/* Pre-processor switch to enable/disable support in Crypto driver for job redirection feature */
#define CRYPTO_ENABLE_REDIRECTION_SUPPORT               (STD_OFF)

/* Pre-processor switch to enable/disable support in Crypto driver for feeding Hse Firmware with descriptors using Crypto_KeyElementGet() API */
#define CRYPTO_ENABLE_FEED_HSE_DESC_SUPPORT             (STD_OFF)

/* Support for User mode.
*       STD_ON:  the Crypto driver can be executed from both supervisor and user mode
*       STD_OFF: the Crypto driver can be executed only from supervisor mode */
#define CRYPTO_ENABLE_USER_MODE_SUPPORT                 (STD_OFF)

/* Support for TLS1.2 key derivation in Crypto_KeyDerive() API */
#define CRYPTO_ENABLE_TLS12_DERIVE_SUPPORT              (STD_OFF)

#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
    #ifdef CRYPTO_ENABLE_USER_MODE_SUPPORT
        #if (STD_ON == CRYPTO_ENABLE_USER_MODE_SUPPORT)
            #error MCAL_ENABLE_USER_MODE_SUPPORT is not enabled. For running Crypto driver in user mode the MCAL_ENABLE_USER_MODE_SUPPORT needs to be defined.
        #endif /* (STD_ON == CRYPTO_ENABLE_USER_MODE_SUPPORT) */
    #endif /* ifndef CRYPTO_ENABLE_USER_MODE_SUPPORT */
#endif /* ifndef MCAL_ENABLE_USER_MODE_SUPPORT*/

/* Support for SHE */
#define CRYPTO_SPT_SHE                                  (STD_ON)

/* Support for Miyaguchi-Preneel compression function (SHE spec support) */
#define CRYPTO_SPT_MP                                   (STD_ON)

/* Support for AES */
#define CRYPTO_SPT_AES                                  (STD_ON)
    #define CRYPTO_SPT_AES_CBC                          (STD_ON)
    #define CRYPTO_SPT_AES_CFB                          (STD_ON)
    #define CRYPTO_SPT_AES_CTR                          (STD_ON)
    #define CRYPTO_SPT_AES_ECB                          (STD_ON)
    #define CRYPTO_SPT_AES_OFB                          (STD_ON)

/* Support for AEAD */
#define CRYPTO_SPT_AEAD                                 (STD_ON)

/* Support for MAC */
#define CRYPTO_SPT_MAC                                  (STD_ON)
    #define CRYPTO_SPT_CMAC                             (STD_ON)
    #define CRYPTO_SPT_FAST_CMAC                        (STD_ON)
    #define CRYPTO_SPT_GMAC                             (STD_ON)
    #define CRYPTO_SPT_HMAC                             (STD_ON)
    #define CRYPTO_SPT_XCBCMAC                          (STD_OFF)

/* Support for TDES_(128, 192)_(ECB, CBC, CFB, OFB) as defined  in NIST SP 800-67 rev1. */
#define CRYPTO_SPT_TDES                                 (STD_OFF)

/* Support for HASH primitives */
#define CRYPTO_SPT_HASH                                 (STD_ON)
    #define CRYPTO_SPT_MD5                              (STD_OFF)
    #define CRYPTO_SPT_SHA1                             (STD_ON)
    #define CRYPTO_SPT_SHA2_224                         (STD_ON)
    #define CRYPTO_SPT_SHA2_256                         (STD_ON)
    #define CRYPTO_SPT_SHA2_384                         (STD_ON)
    #define CRYPTO_SPT_SHA2_512                         (STD_ON)
    #define CRYPTO_SPT_SHA2_512_224                     (STD_ON)
    #define CRYPTO_SPT_SHA2_512_256                     (STD_ON)
    #define CRYPTO_SPT_SHA3                             (STD_OFF)

/* Support for SIPHASH primitive */
#define CRYPTO_SPT_SIPHASH                              (STD_OFF)

/* Support for RSA primitives */
#define CRYPTO_SPT_RSA                                  (STD_ON)
    #define CRYPTO_SPT_RSAES_NO_PADDING                 (STD_ON)
    #define CRYPTO_SPT_RSAES_OAEP                       (STD_ON)
    #define CRYPTO_SPT_RSAES_PCKS1_V15                  (STD_ON)
    #define CRYPTO_SPT_RSAASSA_PSS                      (STD_ON)
    #define CRYPTO_SPT_RSASSA_PCKS1_V15                 (STD_ON)

/* Support for ECC primitives */
#define CRYPTO_SPT_ECC                                  (STD_ON)
    #define CRYPTO_SPT_EDDSA                            (STD_ON)
    #define CRYPTO_SPT_ECDSA                            (STD_ON)
    #define CRYPTO_SPT_SECP256R1                        (STD_ON)
    #define CRYPTO_SPT_SECP384R1                        (STD_ON)
    #define CRYPTO_SPT_SECP521R1                        (STD_ON)
    #define CRYPTO_SPT_BRAINPOOLP256R1                  (STD_ON)
    #define CRYPTO_SPT_BRAINPOOLP320R1                  (STD_ON)
    #define CRYPTO_SPT_BRAINPOOLP384R1                  (STD_ON)
    #define CRYPTO_SPT_BRAINPOOLP512R1                  (STD_ON)
    #define CRYPTO_SPT_EC25519_ED25519                  (STD_ON)
    #define CRYPTO_SPT_EC25519_CURVE25519               (STD_ON)
    #define CRYPTO_SPT_EC448_ED448                      (STD_OFF)
    #define CRYPTO_SPT_EC448_CURVE448                   (STD_OFF)

/* Support for various key operations */
#define CRYPTO_SPT_KEY_IMPORT                           (STD_ON)
    #define CRYPTO_SPT_SHE_KEY_IMPORT                   (STD_ON)
    #define CRYPTO_SPT_SYM_KEY_IMPORT                   (STD_ON)
    #define CRYPTO_SPT_RSA_KEY_IMPORT                   (STD_ON)
    #define CRYPTO_SPT_ECC_KEY_IMPORT                   (STD_ON)
    #define CRYPTO_SPT_ENC_AUTH_KEY_IMPORT              (STD_ON)
#define CRYPTO_SPT_KEY_EXPORT                           (STD_ON)
    #define CRYPTO_SPT_SHE_KEY_EXPORT                   (STD_ON)
    #define CRYPTO_SPT_SYM_KEY_EXPORT                   (STD_ON)
    #define CRYPTO_SPT_RSA_KEY_EXPORT                   (STD_ON)
    #define CRYPTO_SPT_ECC_KEY_EXPORT                   (STD_ON)
#define CRYPTO_SPT_FORMATKEYCATALOGS                    (STD_ON)
#define CRYPTO_SPT_GETKEYINFO                           (STD_ON)

/* Support for key derivation */
#define CRYPTO_SPT_KEY_DERIVE                           (STD_ON)
    #define CRYPTO_SPT_KDF_ANS_X963                     (STD_ON)
    #define CRYPTO_SPT_PBKDF2                           (STD_ON)
    #define CRYPTO_SPT_KDFTLS_12PRF                     (STD_ON)

/* Support for Diffie-Hellman Compute Key */
#define CRYPTO_SPT_COMPUTE_DH                           (STD_ON)

/* Support for key generation */
#define CRYPTO_SPT_KEY_GENERATE                         (STD_ON)
    #define CRYPTO_SPT_SYM_RND_KEY_GEN                  (STD_ON)
    #define CRYPTO_SPT_RSA_KEY_PAIR_GEN                 (STD_ON)
    #define CRYPTO_SPT_ECC_KEY_PAIR_GEN                 (STD_ON)
    #define CRYPTO_SPT_CLASSIC_DH_KEY_PAIR_GEN          (STD_OFF)

/* Support for Cipher modes flags for AES keys */
#define CRYPTO_AES_BLOCK_MODE_MASK                      (STD_ON)

/* Support for HSE ECC key format */
#define CRYPTO_ECC_KEY_FORMAT                           (STD_ON)

/* Support for Compressed ECC key format */
#define CRYPTO_ECC_COMPRESSED_FORMAT                    (STD_ON)

/* Support for Crypto operations using TCM addresses */
#define CRYPTO_ENABLE_TCM_SUPPORT                       (STD_OFF)

/* Define stating if at least one key in the configuration has support for encrypted and/or authenticated import */
#define CRYPTO_ENABLE_ENC_AUTH_KEY_IMPORT               (STD_OFF)

/* Define stating if at least one key in the configuration has support for encrypted and/or authenticated export */
#define CRYPTO_ENABLE_ENC_AUTH_KEY_EXPORT               (STD_ON)

/* Symbolic names for the CryptoDriverObjectId attribute of all the Crypto Driver Objects */
#define CryptoConf_CryptoDriverObject_HaeHSE                               ((uint32)0U)

/* Symbolic names for the CryptoKeyId attribute of all the Crypto keys */
#define CryptoConf_CryptoKey_Dummy                                         ((uint32)0U)
#define CryptoConf_CryptoKey_Dummy2                                        ((uint32)1U)
#define CryptoConf_CryptoKey_PBKDF2_Source_Key                             ((uint32)2U)
#define CryptoConf_CryptoKey_PBKDF2_Target_Key                             ((uint32)3U)
#define CryptoConf_CryptoKey_PBKDF2_Extracted_Key                          ((uint32)4U)
#define CryptoConf_CryptoKey_PBKDF2_ExtractedKey                           ((uint32)5U)
#define CryptoConf_CryptoKey_PBKDF2_Encrypt_Key                            ((uint32)6U)
#define CryptoConf_CryptoKey_PBKDF2_Decrypt_Key                            ((uint32)7U)
#define CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK0                        ((uint32)8U)
#define CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK1                        ((uint32)9U)
#define CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK2                        ((uint32)10U)
#define CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK3                        ((uint32)11U)
#define CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK4                        ((uint32)12U)
#define CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK5                        ((uint32)13U)
#define CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK6                        ((uint32)14U)
#define CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK7                        ((uint32)15U)
#define CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK8                        ((uint32)16U)
#define CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK9                        ((uint32)17U)
#define CryptoConf_CryptoKey_Dummy3                                        ((uint32)18U)
#define CryptoConf_CryptoKey_Dummy4                                        ((uint32)19U)
#define CryptoConf_CryptoKey_Dummy5                                        ((uint32)20U)
#define CryptoConf_CryptoKey_Dummy6                                        ((uint32)21U)
#define CryptoConf_CryptoKey_Dummy7                                        ((uint32)22U)
#define CryptoConf_CryptoKey_MacGen_Sha256_HMAC_key                        ((uint32)23U)
#define CryptoConf_CryptoKey_MacVer_Sha256_HMAC_key                        ((uint32)24U)

/* Symbolic names for the CryptoKeyElementId attribute of all the Crypto key elements */
#define CryptoConf_CryptoKeyElement_Dummy                                  ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_Password             ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_Salt                 ((uint32)13U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_Iteration            ((uint32)14U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Target_Key                      ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_Algorithm            ((uint32)15U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_Algorithm_Secondary  ((uint32)100U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Extracted_Key                   ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_ExtractedKey                    ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_ExtractedKey_forExport          ((uint32)99U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Encrypt_Key                     ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Decrypt_Key                     ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK0                 ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK1                 ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK2                 ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK3                 ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK4                 ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK5                 ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK6                 ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK7                 ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK8                 ((uint32)1U)
#define CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK9                 ((uint32)1U)
#define CryptoConf_CryptoKeyElement_MacGen_Sha256_HMAC_key                 ((uint32)1U)
#define CryptoConf_CryptoKeyElement_MacVer_Sha256_HMAC_key                 ((uint32)1U)

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef struct
{
    const uint8  u8CryptoAuthMacAlgo;          /* Defines the MAC scheme: CMAC, HMAC, GMAC or XCBC_MAC */
    const uint8  u8CryptoAuthCipherAlgo;       /* Used only when MAC scheme is CMAC */
    const uint8  u8CryptoAuthHashAlgo;         /* Used only when MAC scheme is HMAC */
    const uint32 u32CryptoAuthIvLength;        /* Used only when MAC scheme is GMAC */
    const uint8* pCryptoAuthIv;                /* Used only when MAC scheme is GMAC */
}Crypto_AuthMacSchemeType;

typedef struct
{
    const uint8   u8CryptoAuthSignScheme;       /* Defines the signScheme:  ECDSA, EDDSA, RSASSA_PSS or RSASSA_PKCS1_V15 */
    const uint8   u8CryptoAuthContextLength;    /* Used only when signScheme is EDDSA */
    const uint8*  pCryptoAuthContext;           /* Used only when signScheme is EDDSA */
    const boolean bCryptoHashEddsa;             /* Used only when signScheme is EDDSA */
    const uint8   u8CryptoAuthSaltLength;       /* Used only when signScheme is RSASSA_PSS */
    const uint8   u8CryptoAuthSignHashAlgo;     /* Always used when signScheme is any of ECDSA, RSASSA_PSS, RSASSA_PKCS1_V15 */
}Crypto_AuthSignSchemeType;

typedef struct
{
    const uint16    u16CryptoAuthKeyContLength;
    const HOST_ADDR u32CryptoAuthKeyCont;
    const uint16    u16CryptoAuthTagLength0;
    const uint8*    pCryptoAuthTag0;
    const uint16    u16CryptoAuthTagLength1;
    const uint8*    pCryptoAuthTag1;
}Crypto_AuthContainerType;

typedef struct
{
    const uint8  u8CryptoCipherAlgo;
    const uint8  u8CryptoCipherBlockMode;
    const uint32 u32CryptoCipherIVLen;
    const uint8* pCryptoCipherIV;
    const uint8  u8CryptoAuthCipherMode;
    const uint32 u32CryptoAuthCipherTagLen;
    const uint8* pCryptoAuthCipherTag;
    const uint32 u32CryptoAuthCipherIVLen;
    const uint8* pCryptoAuthCipherIV;
    const uint32 u32CryptoAuthCipherAADLen;
    const uint8* pCryptoAuthCipherAAD;
    const uint8  u8CryptoCipherRsaHashAlgo;
    const uint32 u32CryptoCipherRsaLabelLen;
    const uint8* pCryptoCipherRsaLabel;
    const uint32 u32EncryptedHseKeyBitLen;
}Crypto_CipherSchemeType;

typedef struct
{
    const uint8  u8CryptoCipherAlgo;
    const uint8  u8CryptoCipherBlockMode;
    const uint32 u32CryptoCipherIVLen;
    const uint8* pCryptoCipherIV;
    const uint8  u8CryptoAuthCipherMode;
    const uint32 u32CryptoAuthCipherIVLen;
    const uint8* pCryptoAuthCipherIV;
    const uint32 u32CryptoAuthCipherAADLen;
    const uint8* pCryptoAuthCipherAAD;
    const uint8  u8CryptoCipherRsaHashAlgo;
    const uint32 u32CryptoCipherRsaLabelLen;
    const uint8* pCryptoCipherRsaLabel;
}Crypto_ExportCipherSchemeType;

/* Structure storing information about a Crypto Key Element */
typedef struct
{
    /* Members storing Autosar required information */
    const   uint32                           u32CryptoKeyElementId;
    const   boolean                          bCryptoKeyElementAllowPartialAccess;
    const   Crypto_KeyFormatType             eCryptoKeyFormat;
    const   boolean                          bCryptoKeyElementPersist;
    const   Crypto_KeyElementReadAccessType  eCryptoKeyElementReadAccess;
    const   uint32                           u32CryptoKeyElementMaxSize;
    const   Crypto_KeyElementWriteAccessType eCryptoKeyElementWriteAccess;
    uint32* const                            pu32CryptoElementActualSize;
    uint8*  const                            pCryptoElementArray;
    /* Members storing HW specific required information (HSE related) */
    const   uint32                           u32HseCipherKeyHandle;
    const   Crypto_CipherSchemeType*         pHseCipherScheme;
    const   uint32                           u32HseAuthKeyHandle;
    const   Crypto_AuthMacSchemeType*        pHseAuthMacScheme;
    const   Crypto_AuthSignSchemeType*       pHseAuthSignScheme;
    const   Crypto_AuthContainerType*        pHseAuthContainer;
    const   uint32                           u32HseKeyCounter;
    const   uint32                           u32HseExportCipherKeyHandle;
    const   Crypto_ExportCipherSchemeType*   pHseExportCipherScheme;
    const   uint32                           u32HseExportAuthKeyHandle;
    const   Crypto_AuthMacSchemeType*        pHseExportAuthMacScheme;
    const   Crypto_AuthSignSchemeType*       pHseExportAuthSignScheme;
    const   uint8                            u8HseEccCurveId;
    const   uint16                           u16HseKeyFlags;
    const   uint32                           u32HseKeySmrFlags;
    const   uint8                            u8HseKeyType;
    const   uint32                           u32HseKeyHandle;
} Crypto_KeyElementType;



/* Structure containing the number and list of Crypto Driver Objects allocated to a partition */
typedef struct
{
    const uint8  u8NumCDOs;
    const uint8* au8CDOsList;
}Crypto_PartitionToCdoMappingType;

/* Structure storing information about a Crypto Driver Object */
typedef struct
{
    Crypto_QueueElementType* const    pQueuedJobs;
    const uint32                      u32CryptoQueueSize;
    const Crypto_PrimitiveType* const pCryptoKeyPrimitives;
    const uint32                      u32NoCryptoPrimitives;
} Crypto_ObjectType;

/* Structure storing information about which Mu instance is allocated to a partition */
typedef struct
{
    const uint8 u8MuInstance;
    const uint8 u8IdxMuInstance;
} Crypto_PartitionToMuMappingType;

/*==================================================================================================
*                                  GLOBAL CONSTANTS DECLARATIONS
==================================================================================================*/

#define CRYPTO_START_SEC_CONST_8
#include "Crypto_MemMap.h"

/* Array storing the mapping of the MU instance per partition */
extern const Crypto_PartitionToMuMappingType Crypto_aPartitionToMuMapping[CRYPTO_MAX_NUMBER_PARTITIONS_U8];

#define CRYPTO_STOP_SEC_CONST_8
#include "Crypto_MemMap.h"

#define CRYPTO_START_SEC_CONST_UNSPECIFIED
#include "Crypto_MemMap.h"

/* Variables related to Hse KeyCatalog feature */
extern const hseKeyGroupCfgEntry_t aHseNvmKeyCatalog[6U];
extern const hseKeyGroupCfgEntry_t aHseRamKeyCatalog[6U];

#define CRYPTO_STOP_SEC_CONST_UNSPECIFIED
#include "Crypto_MemMap.h"


/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define CRYPTO_START_SEC_VAR_CLEARED_8
#include "Crypto_MemMap.h"

/* Array storing blob 0 containing information that should be persistent between resets */
extern uint8 Crypto_au8NvramBlob0[CRYPTO_SIZEOF_NVRAM_BLOB_0];

#define CRYPTO_STOP_SEC_VAR_CLEARED_8
#include "Crypto_MemMap.h"


#define CRYPTO_START_SEC_VAR_CLEARED_8_NO_CACHEABLE
#include "Crypto_MemMap.h"

/* Array storing blob 1 containing information that should be persistent between resets */
extern uint8 Crypto_au8NvramBlob1[CRYPTO_SIZEOF_NVRAM_BLOB_1];

#define CRYPTO_STOP_SEC_VAR_CLEARED_8_NO_CACHEABLE
#include "Crypto_MemMap.h"



/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* CRYPTO_CFG_H */

