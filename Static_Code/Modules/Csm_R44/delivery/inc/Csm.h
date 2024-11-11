/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Header file to publish CSM function prototypes                **
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
** 1.0.1.0   20-Mar-2021   TamTV6       Fix #17725, #17942, Add trace SUD     **
** 1.0.3.0   12-Aug-2022   DienTC1      #594                                  **
** 1.0.6.0   17-Mar-2023   DienTC1      #CP44-1436                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
#ifndef CSM_H
#define CSM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_Csm_Type.h"
#include "Csm_Cfg.h"
/* @Trace: Csm_SUD_FILE_001 */
/* @Trace: Csm_SUD_DATATYPE_001 */
/* @Trace: Csm_SUD_DATATYPE_002 */
/* @Trace: Csm_SUD_MACRO_002 */
/* @Trace: Csm_SUD_MACRO_003 */
/* @Trace: SRS_CryptoStack_00013 SRS_CryptoStack_00081 SRS_CryptoStack_00089 */
/* @Trace: SRS_CryptoStack_00090 SRS_CryptoStack_00091 SRS_CryptoStack_00092 */
/* @Trace: SRS_CryptoStack_00094 SRS_CryptoStack_00105 */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Service IDs                                           **
*******************************************************************************/
/* @Trace: Csm_SUD_MACRO_004 SRS_CryptoStack_00080 */
#define CSM_INIT_SID                                    (0x00U)
#define CSM_GET_VERSION_INFO_SID                        (0x3BU)
#define CSM_HASH_SID                                    (0x5DU)
#define CSM_MAC_GENERATE_SID                            (0x60U)
#define CSM_MAC_VERIFY_SID                              (0x61U)
#define CSM_ENCRYPT_SID                                 (0x5EU)
#define CSM_DECRYPT_SID                                 (0x5FU)
#define CSM_AEAD_ENCRYPT_SID                            (0x62U)
#define CSM_AEAD_DECRYPT_SID                            (0x63U)
#define CSM_SIGNATURE_GENERATE_SID                      (0x76U)
#define CSM_SIGNATURE_VERIFY_SID                        (0x64U)
#define CSM_RANDOM_GENERATE_SID                         (0x72U)
#define CSM_KEY_ELEMENT_SET_SID                         (0x78U)
#define CSM_KEY_SET_VALID_SID                           (0x67U)
#define CSM_KEY_ELEMENT_GET_SID                         (0x68U)
#define CSM_KEY_ELEMENT_COPY_SID                        (0x71U)
#define CSM_KEY_COPY_SID                                (0x73U)
#define CSM_KEY_ELEMENT_COPY_PARTIAL_SID                (0x79U)
#define CSM_RANDOM_SEED_SID                             (0x69U)
#define CSM_KEY_GENERATE_SID                            (0x6AU)
#define CSM_KEY_DERIVE_SID                              (0x6BU)
#define CSM_KEY_EXCHANGE_CALC_PUB_VAL_SID               (0x6CU)
#define CSM_KEY_EXCHANGE_CALC_SECRET_SID                (0x6DU)
#define CSM_JOB_KEY_SET_VALID_SID                       (0x7AU)
#define CSM_JOB_RANDOM_SEED_SID                         (0x7BU)
#define CSM_JOB_KEY_GENERATE_SID                        (0x7CU)
#define CSM_JOB_KEY_DERIVE_SID                          (0x7DU)
#define CSM_JOB_KEY_EXCHANGE_CALC_PUB_VAL_SID           (0x7EU)
#define CSM_JOB_KEY_EXCHANGE_CALC_SECRET_SID            (0x7FU)
#define CSM_CANCEL_JOB_SID                              (0x6FU)
#define CSM_CALLBACK_NOTIFICATION_SID                   (0x70U)
#define CSM_MAIN_FUNCTION_SID                           (0x01U)

/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
/* macro to avoid unused variable */
#define CSM_UNUSED(x)                                   ((void)(x))

#define CSM_INSTANCE_ID                                 (0x00U)

/* @Trace: Csm_SUD_MACRO_011 SRS_CryptoStack_00086 */
/* Development error code */
#define CSM_E_PARAM_POINTER                             (0x01U)
#define CSM_E_PARAM_HANDLE                              (0x04U)
#define CSM_E_UNINIT                                    (0x05U)
#define CSM_E_INIT_FAILED                               (0x07U)
#define CSM_E_PROCESSING_MODE                           (0x08U)

/* Runtime error code */
#define CSM_E_QUEUE_FULL                                (0x01U)

/* @Trace: Csm_SUD_MACRO_010 SRS_CryptoStack_00086 */
/* Crypto stack return code */
#define CRYPTO_E_BUSY                                   (0x02U)
#define CRYPTO_E_SMALL_BUFFER                           (0x03U)
#define CRYPTO_E_ENTROPY_EXHAUSTION                     (0x04U)
#define CRYPTO_E_QUEUE_FULL                             (0x05U)
#define CRYPTO_E_KEY_READ_FAIL                          (0x06U)
#define CRYPTO_E_KEY_WRITE_FAIL                         (0x07U)
#define CRYPTO_E_KEY_NOT_AVAILABLE                      (0x08U)
#define CRYPTO_E_KEY_NOT_VALID                          (0x09U)
#define CRYPTO_E_KEY_SIZE_MISMATCH                      (0x0AU)
#define CRYPTO_E_COUNTER_OVERFLOW                       (0x0BU)
#define CRYPTO_E_JOB_CANCELED                           (0x0CU)
#define CRYPTO_E_KEY_EMPTY                              (0x0DU)

/* @Trace: Csm_SUD_MACRO_005 */
/* Macros for Crypto_InputOutputRedirectionConfigType */
#define CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT            (0x01U)
#define CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT          (0x02U)
#define CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT           (0x04U)
#define CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT           (0x10U)
#define CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT         (0x20U)

/* @Trace: Csm_SUD_MACRO_007 */
/* Macros for Crypto_AlgorithmFamilyType */
#define CRYPTO_ALGOFAM_NOT_SET                          (0x00U)
#define CRYPTO_ALGOFAM_SHA1                             (0x01U)
#define CRYPTO_ALGOFAM_SHA2_224                         (0x02U)
#define CRYPTO_ALGOFAM_SHA2_256                         (0x03U)
#define CRYPTO_ALGOFAM_SHA2_384                         (0x04U)
#define CRYPTO_ALGOFAM_SHA2_512                         (0x05U)
#define CRYPTO_ALGOFAM_SHA2_512_224                     (0x06U)
#define CRYPTO_ALGOFAM_SHA2_512_256                     (0x07U)
#define CRYPTO_ALGOFAM_SHA3_224                         (0x08U)
#define CRYPTO_ALGOFAM_SHA3_256                         (0x09U)
#define CRYPTO_ALGOFAM_SHA3_384                         (0x0AU)
#define CRYPTO_ALGOFAM_SHA3_512                         (0x0BU)
#define CRYPTO_ALGOFAM_SHAKE128                         (0x0CU)
#define CRYPTO_ALGOFAM_SHAKE256                         (0x0DU)
#define CRYPTO_ALGOFAM_RIPEMD160                        (0x0EU)
#define CRYPTO_ALGOFAM_BLAKE_1_256                      (0x0FU)
#define CRYPTO_ALGOFAM_BLAKE_1_512                      (0x10U)
#define CRYPTO_ALGOFAM_BLAKE_2s_256                     (0x11U)
#define CRYPTO_ALGOFAM_BLAKE_2s_512                     (0x12U)
#define CRYPTO_ALGOFAM_3DES                             (0x13U)
#define CRYPTO_ALGOFAM_AES                              (0x14U)
#define CRYPTO_ALGOFAM_CHACHA                           (0x15U)
#define CRYPTO_ALGOFAM_RSA                              (0x16U)
#define CRYPTO_ALGOFAM_ED25519                          (0x17U)
#define CRYPTO_ALGOFAM_BRAINPOOL                        (0x18U)
#define CRYPTO_ALGOFAM_ECCNIST                          (0x19U)
#define CRYPTO_ALGOFAM_RNG                              (0x1BU)
#define CRYPTO_ALGOFAM_SIPHASH                          (0x1CU)
#define CRYPTO_ALGOFAM_ECIES                            (0x1DU)
#define CRYPTO_ALGOFAM_ECCANSI                          (0x1EU)
#define CRYPTO_ALGOFAM_ECCSEC                           (0x1FU)
#define CRYPTO_ALGOFAM_DRBG                             (0x20U)
#define CRYPTO_ALGOFAM_FIPS186                          (0x21U)
#define CRYPTO_ALGOFAM_PADDING_PKCS7                    (0x22U)
#define CRYPTO_ALGOFAM_PADDING_ONEWITHZEROS             (0x23U)
#define CRYPTO_ALGOFAM_PBKDF2                           (0x24U)
#define CRYPTO_ALGOFAM_KDFX963                          (0x25U)
#define CRYPTO_ALGOFAM_DH                               (0x26U)
#define CRYPTO_ALGOFAM_X25519                           (0x2EU)
#define CRYPTO_ALGOFAM_POLY1305                         (0x2DU)
#define CRYPTO_ALGOFAM_ED448                            (0xEEU)
#define CRYPTO_ALGOFAM_X448                             (0xEFU)
#define CRYPTO_ALGOFAM_CUSTOM                           (0xFFU)

/* @Trace: Csm_SUD_MACRO_008 */
/* Macros for Crypto_AlgorithmModeType */
#define CRYPTO_ALGOMODE_NOT_SET                         (0x00U)
#define CRYPTO_ALGOMODE_ECB                             (0x01U)
#define CRYPTO_ALGOMODE_CBC                             (0x02U)
#define CRYPTO_ALGOMODE_CFB                             (0x03U)
#define CRYPTO_ALGOMODE_OFB                             (0x04U)
#define CRYPTO_ALGOMODE_CTR                             (0x05U)
#define CRYPTO_ALGOMODE_GCM                             (0x06U)
#define CRYPTO_ALGOMODE_XTS                             (0x07U)
#define CRYPTO_ALGOMODE_RSAES_OAEP                      (0x08U)
#define CRYPTO_ALGOMODE_RSAES_PKCS1_v1_5                (0x09U)
#define CRYPTO_ALGOMODE_RSASSA_PSS                      (0x0AU)
#define CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5               (0x0BU)
#define CRYPTO_ALGOMODE_8ROUNDS                         (0x0CU)
#define CRYPTO_ALGOMODE_12ROUNDS                        (0x0DU)
#define CRYPTO_ALGOMODE_20ROUNDS                        (0x0EU)
#define CRYPTO_ALGOMODE_HMAC                            (0x0FU)
#define CRYPTO_ALGOMODE_CMAC                            (0x10U)
#define CRYPTO_ALGOMODE_GMAC                            (0x11U)
#define CRYPTO_ALGOMODE_CTRDRBG                         (0x12U)
#define CRYPTO_ALGOMODE_SIPHASH_2_4                     (0x13U)
#define CRYPTO_ALGOMODE_SIPHASH_4_8                     (0x14U)
#define CRYPTO_ALGOMODE_PXXXR1                          (0x15U)
#define CRYPTO_ALGOMODE_CUSTOM                          (0xFFU)

/* @Trace: Csm_SUD_MACRO_006 */
/* Macros for Crypto_ServiceInfoType */
#define CRYPTO_HASH                                     (0x00U)
#define CRYPTO_MACGENERATE                              (0x01U)
#define CRYPTO_MACVERIFY                                (0x02U)
#define CRYPTO_ENCRYPT                                  (0x03U)
#define CRYPTO_DECRYPT                                  (0x04U)
#define CRYPTO_AEADENCRYPT                              (0x05U)
#define CRYPTO_AEADDECRYPT                              (0x06U)
#define CRYPTO_SIGNATUREGENERATE                        (0x07U)
#define CRYPTO_SIGNATUREVERIFY                          (0x08U)
#define CRYPTO_RANDOMGENERATE                           (0x0BU)
#define CRYPTO_RANDOMSEED                               (0x0CU)
#define CRYPTO_KEYGENERATE                              (0x0DU)
#define CRYPTO_KEYDERIVE                                (0x0EU)
#define CRYPTO_KEYEXCHANGECALCPUBVAL                    (0x0FU)
#define CRYPTO_KEYEXCHANGECALCSECRET                    (0x10U)
#define CRYPTO_CERTIFICATEPARSE                         (0x11U)
#define CRYPTO_CERTIFICATEVERIFY                        (0x12U)
#define CRYPTO_KEYSETVALID                              (0x13U)

/* @Trace: Csm_SUD_MACRO_009 */
/* Macros for Key Management processing flags*/
#define CSM_KEYELEMENTSET_ISPROCESSING                  (0x0001U)
#define CSM_KEYSETVALID_ISPROCESSING                    (0x0002U)
#define CSM_KEYELEMENTGET_ISPROCESSING                  (0x0004U)
#define CSM_KEYELEMENTCOPY_ISPROCESSING                 (0x0008U)
#define CSM_KEYCOPY_ISPROCESSING                        (0x0010U)
#define CSM_KEYELEMENTCOPYPARTIAL_ISPROCESSING          (0x0020U)
#define CSM_RANDOMSEED_ISPROCESSING                     (0x0040U)
#define CSM_KEYGENERATE_ISPROCESSING                    (0x0080U)
#define CSM_KEYDERIVE_ISPROCESSING                      (0x0100U)
#define CSM_KEYEXCHANGEPUBVAL_ISPROCESSING              (0x0200U)
#define CSM_KEYEXCHANGECALCSECRET_ISPROCESSING          (0x0400U)
#define CSM_KEYMANFNC_ISNOTPROCESSING                   (0x0000U)

/*******************************************************************************
**                         Global Data Types                                  **
*******************************************************************************/
/* @Trace: Csm_SUD_DATATYPE_004 */
typedef uint8 Crypto_AlgorithmFamilyType;
/* @Trace: Csm_SUD_DATATYPE_005 */
typedef uint8 Crypto_AlgorithmModeType;
/* @Trace: Csm_SUD_DATATYPE_007 */
typedef uint8 Crypto_ServiceInfoType;
/* @Trace: Csm_SUD_DATATYPE_006 */
typedef uint8 Crypto_InputOutputRedirectionConfigType;

/* @Trace: Csm_SUD_DATATYPE_009 SRS_CryptoStack_00079 */
typedef enum
{
  CRYPTO_PROCESSING_ASYNC = 0x00U,
  CRYPTO_PROCESSING_SYNC
} Crypto_ProcessingType;

/* @Trace: Csm_SUD_DATATYPE_008 */
typedef enum
{
  CRYPTO_JOBSTATE_IDLE = 0x00U,
  CRYPTO_JOBSTATE_ACTIVE,
} Crypto_JobStateType;

typedef CONSTP2FUNC(void, CSM_APPL_DATA, Csm_ApplicationCallbackType)
(
  const uint32 jobID, Csm_ResultType result
);

typedef CONSTP2FUNC(Std_ReturnType, CSM_APPL_DATA, Csm_RteCallbackType)
(
  Csm_ResultType result
);

/* @Trace: Csm_SUD_DATATYPE_017 */
typedef struct
{
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) inputPtr;
  uint32 inputLength;
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) secondaryInputPtr;
  uint32 secondaryInputLength;
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) tertiaryInputPtr;
  uint32 tertiaryInputLength;
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) outputPtr;
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) outputLengthPtr;
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) secondaryOutputPtr;
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) secondaryOutputLengthPtr;
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr;
  Crypto_OperationModeType mode;
  uint32 cryIfKeyId;
  uint32 targetCryIfKeyId;
} Crypto_JobPrimitiveInputOutputType;

/* @Trace: Csm_SUD_DATATYPE_016 */
typedef struct
{
  uint8 redirectionConfig;
  uint32 inputKeyId;
  uint32 inputKeyElementId;
  uint32 secondaryInputKeyId;
  uint32 secondaryInputKeyElementId;
  uint32 tertiaryInputKeyId;
  uint32 tertiaryInputKeyElementId;
  uint32 outputKeyId;
  uint32 outputKeyElementId;
  uint32 secondaryOutputKeyId;
  uint32 secondaryOutputKeyElementId;
} Crypto_JobRedirectionInfoType;

/* @Trace: Csm_SUD_DATATYPE_012 */
typedef struct
{
  Crypto_AlgorithmFamilyType family;
  Crypto_AlgorithmFamilyType secondaryFamily;
  uint32 keyLength;
  Crypto_AlgorithmModeType mode;
} Crypto_AlgorithmInfoType;

/* @Trace: Csm_SUD_DATATYPE_013 */
typedef struct
{
  const uint32 resultLength;
  const Crypto_ServiceInfoType service;
  const Crypto_AlgorithmInfoType algorithm;
} Crypto_PrimitiveInfoType;

/* @Trace: Csm_SUD_DATATYPE_011 */
typedef struct
{
  uint32 callbackId;
  P2CONST(Crypto_PrimitiveInfoType, AUTOMATIC, CSM_APPL_CONST) primitiveInfo;
  uint32 cryIfKeyId;
  Crypto_ProcessingType processingType;
  boolean callbackUpdateNotification;
} Crypto_JobPrimitiveInfoType;

/* @Trace: Csm_SUD_DATATYPE_015 SRS_CryptoStack_00102 */
typedef struct
{
  const uint32 jobId;
  const uint32 jobPriority;
} Crypto_JobInfoType;

/* @Trace: Csm_SUD_DATATYPE_010 */
typedef struct
{
  uint32 jobId;
  Crypto_JobStateType jobState;
  Crypto_JobPrimitiveInputOutputType jobPrimitiveInputOutput;
  P2CONST(Crypto_JobPrimitiveInfoType, AUTOMATIC, CSM_APPL_CONST) \
                                                          jobPrimitiveInfo;
  P2CONST(Crypto_JobInfoType, AUTOMATIC, CSM_APPL_CONST) jobInfo;
  uint32 cryptoKeyId;
  P2VAR(Crypto_JobRedirectionInfoType, AUTOMATIC, CSM_APPL_DATA) \
                                                          jobRedirectionInfoRef;
  uint32 targetCryptoKeyId;
} Crypto_JobType;

/* @Trace: Csm_SUD_DATATYPE_014 */
/* CSM config type data structure */
typedef struct
{
  uint8 dummy;
} Csm_ConfigType;

/* @Trace: Csm_SUD_DATATYPE_003 */
/* Identification of a CSM service configuration via a numeric identifier */
typedef uint16 Csm_ConfigIdType;

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CSM_CODE) Csm_Init
(
  P2CONST(Csm_ConfigType, AUTOMATIC, CSM_APPL_CONST) configPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#if (CSM_VERSION_INFO_API == STD_ON)
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CSM_CODE) Csm_GetVersionInfo
(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CSM_APPL_DATA) versioninfo
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* polyspace-begin MISRA-C3:8.5 [Justified:Low] "According to AUTOSAR specification, these Csm service APIs can be invoked by AWS layer. So, Rte code also declares them." */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_Hash
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) dataPtr,
  VAR(uint32, AUTOMATIC) dataLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_MacGenerate
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) dataPtr,
  VAR(uint32, AUTOMATIC) dataLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) macPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) macLengthPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_MacVerify
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) dataPtr,
  VAR(uint32, AUTOMATIC) dataLength,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) macPtr,
  VAR(uint32, CSM_CONST) macLength,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_Encrypt
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) dataPtr,
  VAR(uint32, AUTOMATIC) dataLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_Decrypt
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) dataPtr,
  VAR(uint32, AUTOMATIC) dataLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_AEADEncrypt
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) plaintextPtr,
  VAR(uint32, AUTOMATIC) plaintextLength,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) associatedDataPtr,
  VAR(uint32, AUTOMATIC) associatedDataLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) ciphertextPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) ciphertextLengthPtr,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) tagPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) tagLengthPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_AEADDecrypt
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ciphertextPtr,
  VAR(uint32, AUTOMATIC) ciphertextLength,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) associatedDataPtr,
  VAR(uint32, AUTOMATIC) associatedDataLength,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) tagPtr,
  VAR(uint32, AUTOMATIC) tagLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) plaintextPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) plaintextLengthPtr,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureGenerate
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) dataPtr,
  VAR(uint32, AUTOMATIC) dataLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureVerify
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) dataPtr,
  VAR(uint32, AUTOMATIC) dataLength,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) signaturePtr,
  VAR(uint32, AUTOMATIC) signatureLength,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_RandomGenerate
(
  VAR(uint32, AUTOMATIC) jobId,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementSet
(
  VAR(uint32, AUTOMATIC) keyId,
  VAR(uint32, AUTOMATIC) keyElementId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) keyPtr,
  VAR(uint32, AUTOMATIC) keyLength
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeySetValid
(
  VAR(uint32, AUTOMATIC) keyId
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementGet
(
  VAR(uint32, AUTOMATIC) keyId,
  VAR(uint32, AUTOMATIC) keyElementId,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) keyPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) keyLengthPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopy
(
  VAR(uint32, CSM_CONST) keyId,
  VAR(uint32, CSM_CONST) keyElementId,
  VAR(uint32, CSM_CONST) targetKeyId,
  VAR(uint32, CSM_CONST) targetKeyElementId
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyCopy
(
  VAR(uint32, CSM_CONST) keyId,
  VAR(uint32, CSM_CONST) targetKeyId
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopyPartial
(
  VAR(uint32, AUTOMATIC) keyId,
  VAR(uint32, AUTOMATIC) keyElementId,
  VAR(uint32, AUTOMATIC) keyElementSourceOffset,
  VAR(uint32, AUTOMATIC) keyElementTargetOffset,
  VAR(uint32, AUTOMATIC) keyElementCopyLength,
  VAR(uint32, AUTOMATIC) targetKeyId,
  VAR(uint32, AUTOMATIC) targetKeyElementId
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_RandomSeed
(
  VAR(uint32, AUTOMATIC) keyId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) seedPtr,
  VAR(uint32, AUTOMATIC) seedLength
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyGenerate
(
  VAR(uint32, AUTOMATIC) keyId
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyDerive
(
  VAR(uint32, AUTOMATIC) keyId,
  VAR(uint32, AUTOMATIC) targetKeyId
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcPubVal
(
  VAR(uint32, AUTOMATIC) keyId,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) publicValuePtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcSecret
(
  VAR(uint32, AUTOMATIC) keyId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) partnerPublicValuePtr,
  VAR(uint32, AUTOMATIC) partnerPublicValueLength
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeySetValid
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(uint32, AUTOMATIC) keyId
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobRandomSeed
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(uint32, AUTOMATIC) keyId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) seedPtr,
  VAR(uint32, AUTOMATIC) seedLength
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyGenerate
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(uint32, AUTOMATIC) keyId
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyDerive
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(uint32, AUTOMATIC) keyId,
  VAR(uint32, AUTOMATIC) targetKeyId
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcPubVal
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(uint32, AUTOMATIC) keyId,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) publicValuePtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcSecret
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(uint32, AUTOMATIC) keyId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) partnerPublicValuePtr,
  VAR(uint32, AUTOMATIC) partnerPublicValueLength
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_CancelJob
(
  VAR(uint32, AUTOMATIC) job,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CSM_CODE) Csm_CallbackNotification
(
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
  VAR(Csm_ResultType, AUTOMATIC) result
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:8.5 */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
