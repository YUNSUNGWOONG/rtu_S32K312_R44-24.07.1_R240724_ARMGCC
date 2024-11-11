/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_IntTypes.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : KeyM type definition                                          **
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
** 1.0.3.0   13-May-2022   DienTC1      #21524                                **
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
** 1.0.6.1   08-Feb-2023   DienTC1      #CP44-1655                            **
** 1.0.7.0   07-Apr-2023   PhuocLH9     #CP44-1636,#CP44-1664                 **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
#ifndef KEYM_INT_TYPE_H
#define KEYM_INT_TYPE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: KeyM_SUD_MACRO_002 */
/* @Trace: KeyM_SUD_MACRO_003 */
/* @Trace: KeyM_SUD_GLOBALVAR_030 */
/* @Trace: KeyM_SUD_GLOBALVAR_036 */
/* KeyM Configuration Header file */
#include "KeyM_Cfg.h"
/* @Trace: KeyM_SUD_DATATYPE_041 */
/* @Trace: KeyM_SUD_DATATYPE_042 */
/* @Trace: KeyM_SUD_DATATYPE_043 */
/* @Trace: KeyM_SUD_DATATYPE_044 */
/* @Trace: KeyM_SUD_DATATYPE_045 */
/* @Trace: KeyM_SUD_DATATYPE_046 */
/* @Trace: KeyM_SUD_DATATYPE_047 */

/* @Trace: KeyM_SUD_DATATYPE_055 */

/* @Trace: KeyM_SUD_DATATYPE_057 */
/* @Trace: KeyM_SUD_DATATYPE_058 */
/* RTE KeyM Header file */
#include "Rte_KeyM_Type.h"
/* @Trace: KeyM_SUD_DATATYPE_001 */
/* @Trace: KeyM_SUD_DATATYPE_002 */
/* @Trace: KeyM_SUD_DATATYPE_054 */
/* CSM header file */
#include "Csm.h"
/* @Trace: KeyM_SUD_DATATYPE_003 */
/* @Trace: KeyM_SUD_DATATYPE_004 */
/* @Trace: KeyM_SUD_DATATYPE_005 */
#include "SchM_KeyM.h"
/* StbM Type header file */
#if (KEYM_USE_STBM == STD_ON)
#include "StbM.h"
#endif
/* NvM Header file */
#if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
#include "NvM.h"
#endif
/* DET Header file */
#if (KEYM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/* KeyM ASN1 header file */
#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
#include "KeyM_Asn1.h"
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/

/*******************************************************************************
**                      Return Error Codes                                    **
*******************************************************************************/
/* @Trace: KeyM_SUD_MACRO_010 */
/* Certificate parsing error codes */
/* No error */
#define KEYM_E_OK                      (uint16)(0x0000U)
/* Common error */
#define KEYM_E_NOT_OK                  (uint16)(0x0001U)
/* Not support feature */
#define KEYM_E_FEATURE_NOT_SUPPORTED   (uint16)(0x3100U)
/* The CRT/CRL/CSR format is invalid, e.g. different type expected. */
#define KEYM_E_INVALID_FORMAT          (uint16)(0x3200U)
/* The CRT/CRL/CSR version element is invalid. */
#define KEYM_E_INVALID_VERSION         (uint16)(0x3300U)
/* The serial tag or value is invalid. */
#define KEYM_E_INVALID_SERIAL          (uint16)(0x3400U)
/* The algorithm tag or value is invalid. */
#define KEYM_E_INVALID_ALG             (uint16)(0x3500U)
/* The name tag or value is invalid. */
#define KEYM_E_INVALID_NAME            (uint16)(0x3600U)
/* The date tag or value is invalid. */
#define KEYM_E_INVALID_DATE            (uint16)(0x3700U)
/* The signature tag or value invalid. */
#define KEYM_E_INVALID_SIGNATURE       (uint16)(0x3800U)
/* The extension tag or value is invalid. */
#define KEYM_E_INVALID_EXTENSIONS      (uint16)(0x3900U)
/* Signature algorithms do not match. */
#define KEYM_E_SIG_MISMATCH            (uint16)(0x3A00U)
/* The public key is invalid */
#define KEYM_E_INVALID_PUBLIC_KEY      (uint16)(0x3B00U)
/* The certificate revocation list is invalid. */
#define KEYM_E_INVALID_REVOKED_LIST    (uint16)(0x3C00U)
/* The certificate issuer unique id is invalid. */
#define KEYM_E_INVALID_UNIQUE_ID       (uint16)(0x3D00U)
/* The certificate has been revoked (is on a CRL). */
#define KEYM_E_BADCERT_REVOKED         (uint16)(0x42U)
/* The children certificate issuer name does not match
  with the parent certificate subject name. */
#define KEYM_E_BADCERT_NAME_MISMATCH   (uint16)(0x43U)

/** Size of WORD and BYTE of Ecc curve */
#define KEYM_ECC_CURVEp521r1_BYTES_SIZE                     (66U)
#define KEYM_ECC_CURVEp256r1_BYTES_SIZE                     (32U)
#define KEYM_ECC_CURVEp224r1_BYTES_SIZE                     (28U)
#define KEYM_ECC_CURVEp160r1_BYTES_SIZE                     (20U)

/*  KeyM certificate Element Curve Types */

#ifndef KEYM_CERT_ELEMENT_CURVE_NOT_SET
#define KEYM_CERT_ELEMENT_CURVE_NOT_SET                   (0x00U)
#endif

#ifndef KEYM_CERT_ELEMENT_CURVE_P160R1
#define KEYM_CERT_ELEMENT_CURVE_P160R1                    (0x01U)
#endif

#ifndef KEYM_CERT_ELEMENT_CURVE_P224R1
#define KEYM_CERT_ELEMENT_CURVE_P224R1                    (0x02U)
#endif

#ifndef KEYM_CERT_ELEMENT_CURVE_P256R1
#define KEYM_CERT_ELEMENT_CURVE_P256R1                    (0x03U)
#endif

#ifndef KEYM_CERT_ELEMENT_CURVE_P521R1
#define KEYM_CERT_ELEMENT_CURVE_P521R1                    (0x04U)
#endif
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: KeyM_SUD_MACRO_005 */
/* Instance identification */
#define KEYM_INSTANCE_ID                          (0x00U)

#define KEYM_ZERO                                 (0x00U)
#define KEYM_ONE                                  (0x01U)
#define KEYM_TWO                                  (0x02U)
#define KEYM_THREE                                (0x03U)
#define KEYM_FOUR                                 (0x04U)
#define KEYM_FIVE                                 (0x05U)
#define KEYM_SIX                                  (0x06U)
#define KEYM_SEVEN                                (0x07U)
#define KEYM_EIGHT                                (0x08U)
#define KEYM_ELEVEN                               (0x0BU)

#define KEYM_TRUE                                 ((boolean)0x01U)
#define KEYM_FALSE                                ((boolean)0x00U)

#define KEYM_SESSION_ACTIVATED                    ((boolean)0x01U)
#define KEYM_SESSION_DEACTIVATED                  ((boolean)0x00U)

#define KEYM_M1M2M3_LENGTH_IN_BYTE                (0x40U)
#define KEYM_M1M2M3_BYTE_POSITION_OF_KEYID        (0x0FU)
#define KEYM_M1M2M3_KEYID_BIT_MASK                (0xF0U)
#define KEYM_M1M2M3_KEYID_BIT_SHIFT               (0x04U)

#define KEYM_THE_8TH_BIT_MASK                     (0x80U)
#define KEYM_THE_LAST_7_BITS_MASK                 (0x7FU)

#define KEYM_KEY_ELEMENT1_ID                      (1U)
#define KEYM_KEY_ELEMENT13_ID                     (13U)
#define KEYM_KEY_ELEMENT16_ID                     (16U)
#define KEYM_KEY_ELEMENT17_ID                     (17U)
#define KEYM_INVALID_KEYID                        (0xFFFFU)
#define KEYM_KEY_DATA_LENGTH_STORED_SIZE          (2U)
#define KEYM_UPPER_BYTE_MASK                      (0xFF00U)
#define KEYM_LOWER_BYTE_MASK                      (0x00FFU)
#define KEYM_UPPER_BYTE_SHIFT                     (8U)

#define KEYM_PUBLIC_KEY_VALUE_MAX_LENGTH          (276U)
#define KEYM_PRIVATE_KEY_VALUE_MAX_LENGTH         (1200U)
#define KEYM_SIGNATURE_VALUE_MAX_LENGTH           (520U)
#define KEYM_CERT_RSA_KEY_GENERATE_ENABLED        (STD_ON)
/* Allow 68byte as a ECC Size in KeyM */
#define KEYM_ECC_SIGNATURE_VALUE_MAX_LENGTH       (136U)
#define KEYM_NUM_MONTH                            (12U)

#if (KEYM_DEV_ERROR_DETECT == STD_ON)
#define KEYM_REPORT_ERROR(sid, type)       do{ \
  (void)Det_ReportError(KEYM_MODULE_ID, KEYM_INSTANCE_ID,(sid),(type));\
  }\
  while (0)
#else
#define KEYM_REPORT_ERROR(sid, type)       {\
  (void)(sid);\
  (void)(type);\
  }
#endif /* KEYM_DEV_ERROR_DETECT == STD_ON */

/*******************************************************************************
**                       Global Data Types                                    **
*******************************************************************************/
/* @Trace: KeyM_SUD_DATATYPE_023 SRS_BSW_00335 */
/* Type definition for KEYM state types */
typedef enum
{
  KEYM_UNINIT = 0x00U,
  KEYM_IDLE = 0x01U,
  KEYM_BUSY = 0x02U
} KeyM_StateType;

/* @Trace: KeyM_SUD_DATATYPE_019 */
/* The following macros are used to specify job type */
typedef enum {
  KEYM_NO_JOB = 0x01U,
  KEYM_UPDATE_JOB = 0x02U,
  KEYM_FINALIZE_JOB = 0x03U,
  KEYM_VERIFY_JOB = 0x04U,
  KEYM_SERVICE_CERTIFICATE_JOB = 0x05U,
  KEYM_VERIFY_CERTIFICATES_JOB = 0x06U,
  KEYM_VERIFY_CERTIFICATE_JOB = 0x07U,
  KEYM_VERIFY_CERTIFICATECHAIN_JOB = 0x08U
} KeyM_RequestJobType;

/* @Trace: KeyM_SUD_DATATYPE_020 */
/* The following macros are used to indicate if a job is complete/in progress */
typedef enum {
  KEYM_COMPLETE = 0x00U,
  KEYM_REQUEST_JOB = 0x01U,
  KEYM_IN_PROGRESS = 0x02U,
  KEYM_KH_IN_PROGRESS = 0x03U
} KeyM_JobStateType;

/* @Trace: KeyM_SUD_DATATYPE_021 */
typedef enum
{
  KEYM_STORAGE_IN_CSM = 0x00U,
  KEYM_STORAGE_IN_NVM = 0x01U,
  KEYM_STORAGE_IN_RAM = 0x02U
} KeyM_KeyCertStorageType;

/* @Trace: KeyM_SUD_DATATYPE_018 */
typedef enum
{
  KEYM_STORED_KEY  = 0x00U,
  KEYM_DERIVED_KEY = 0x01U
} KeyM_CryptoKeyGenerationType;

/* @Trace: KeyM_SUD_DATATYPE_017 */
typedef enum
{
  KEYM_VERIFY_MACGENERATE = 0x00U,
  KEYM_VERIFY_MACVERIFY   = 0x01U,
  KEYM_VERIFY_ENCRYPT     = 0x02U,
  KEYM_VERIFY_DECRYPT     = 0x03U,
  KEYM_VERIFY_AEADENCRYPT = 0x04U,
  KEYM_VERIFY_AEADDECRYPT = 0x05U,
  KEYM_VERIFY_NO_TYPE     = 0xFFU
} KeyM_CryptoCsmVerifyJobType;

/* @Trace: KeyM_SUD_DATATYPE_013 */
typedef enum
{
  KEYM_CERT_ALGORITHM_ECC = 0x00U,
  KEYM_CERT_ALGORITHM_RSA = 0x01U,
} KeyM_CertAlgorithmType;

/* @Trace: KeyM_SUD_DATATYPE_015 */
typedef enum
{
  KEYM_CERT_FORMAT_CRL = 0x00U,
  KEYM_CERT_FORMAT_CVC = 0x01U,
  KEYM_CERT_FORMAT_X509 = 0x02U
} KeyM_CertFormatType;

/* @Trace: KeyM_SUD_DATATYPE_016 */
typedef enum
{
  KEYM_CERT_VERSION_NUMBER = 0x00U,
  KEYM_CERT_SERIAL_NUMBER = 0x01U,
  KEYM_CERT_SUBJECT_NAME = 0x02U,
  KEYM_CERT_ISSUER_NAME = 0x03U,
  KEYM_CERT_ISSUER_UNIQUE_IDENTIFIER = 0x04U,
  KEYM_CERT_SIGNATURE = 0x05U,
  KEYM_CERT_SIGNATURE_ALGORITHM = 0x06U,
  KEYM_CERT_SIGNATURE_ALGORITHM_ID = 0x07U,
  KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_PUBLIC_KEY_ALGORITHM = 0x08U,
  KEYM_CERT_SUBJECT_PUBLIC_KEY_INFO_SUBJECT_PUBLIC_KEY = 0x09U,
  KEYM_CERT_SUBJECT_UNIQUE_IDENTIFIER = 0x0AU,
  KEYM_CERT_VALIDITY_PERIOD_NOT_AFTER = 0x0BU,
  KEYM_CERT_VALIDITY_PERIOD_NOT_BEFORE = 0x0CU,
  KEYM_CERT_EXTENSION = 0x0DU,
  KEYM_CERT_SUBJECT_AUTHORIZATION = 0x0FU,
  KEYM_CERT_REVOKED_CERTIFICATES  = 0x10U
} KeyM_CertificateElementTypeOfStructure;

/* @Trace: KeyM_SUD_DATATYPE_014 */
typedef enum
{
  KEYM_EQUALS = 0x00U,
  KEYM_EQUALS_NOT = 0x01U,
  KEYM_GREATER_OR_EQUAL = 0x02U,
  KEYM_LESS_OR_EQUAL = 0x03U,
  KEYM_LESS_THAN = 0x04U
} KeyM_CertElementConditionType;

/* @Trace: KeyM_SUD_DATATYPE_022 */
typedef enum
{
  KEYM_AND = 0x00U,
  KEYM_OR = 0x01U
} KeyM_LogicalOperator;

/* @Trace: KeyM_SUD_DATATYPE_033 */
typedef struct
{
  /* The CSM job ID  */
  const uint32 CsmJobId;
  /* If true the CSM job is Asynchronous job, otherwise it is
    synchronous job */
  const boolean AsyncJob;
} KeyM_CsmJobType;

/* @Trace: KeyM_SUD_DATATYPE_030 */
typedef struct
{
  /* Provides a unique name of the key for identification */
  const uint8 * const PtrKeyName;
  /* The length of key name */
  const uint16 KeyNameLength;
  /* Identifier of the crypto key */
  const uint16 KeyId;
  /* The maximum size in bytes of a CryptoKey */
  const uint32 KeyMaxLength;
  /* The pointer to key data */
  uint8 * PtrKeyData;
  /* The size in bytes of a CryptoKey */
  uint32 KeyLength;
  /* Specifies how the CryptoKey will be generated. If it is derived from
    another key or simply stored */
  const KeyM_CryptoKeyGenerationType KeyGenerationType;
  /* Specify the storage location of the crypto key */
  const KeyM_KeyCertStorageType KeyStorageType;
  /* The ID of associated CSM key that is used as source for
    the key derivation of this key */
  const uint32 CsmSourceKeyId;
  /* The ID of associated CSM key that key shall be derived or stored to */
  const uint32 CsmTargetKeyId;
  /* The CSM job that the key verify function can use for verification of
    a certain key */
  const KeyM_CsmJobType CsmVerifyJob;
  /* Specifies what type of function for key verification operation is used */
  const KeyM_CryptoCsmVerifyJobType CsmVerifyJobType;
  /* If a key is configured to be derived from another key, this data
    will be added as salt */
  const uint8 * PtrKeyGenerationInfo;
  /* The length of PtrKeyGenerationInfo */
  const uint16 KeyGenerationInfoLength;
  #if (KEYM_CRYPTO_KEY_ADDITIONAL_HINT_ENABLED == STD_ON)
  /* Provide additional hints to the crypto key that is used by KeyM
    to identify the key */
  const uint8 KeyCryptoProps;
  #endif
  #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
  /* The NvM block Id which used to store key */
  const NvM_BlockIdType NvmBlockId;
  #endif
  #if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
  /* Alternated state of crypto key, if true the crypto key has
    updated and need to be finalized */
  boolean HasAlternated;
  #endif
  /* The key state, 1 is valid and 0 is invalid */
  uint8 KeyState;
} KeyM_CryptoKeyType;

#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)

/* @Trace: KeyM_SUD_DATATYPE_012 */
#if (KEYM_CERT_SERVICE_APPLICATION_CALLBACK_ENABLE == STD_ON)
typedef P2FUNC(void,\
  KEYM_APPL_CODE, KeyM_ServiceCertificateCallbackNotificationFnType)(\
  KeyM_CertificateIdType intCertId, KeyM_ResultType intResult,\
  uint16 intResultDataLength, uint8* intResultDataPtr);
#endif

/* @Trace: KeyM_SUD_DATATYPE_011 */
typedef P2FUNC(Std_ReturnType,\
  KEYM_APPL_CODE, KeyM_RteServiceCertificateCallbackNotificationFnType)(\
  KeyM_ResultType intResult, uint16 intResultDataLength, \
  uint8* intResultDataPtr);

/* @Trace: KeyM_SUD_DATATYPE_009 */
#if (KEYM_CERT_VERIFY_APPLICATION_CALLBACK_ENABLE == STD_ON)
typedef P2FUNC(Std_ReturnType,\
  KEYM_APPL_CODE, KeyM_CertificateVerifyCallbackNotificationFnType)(\
  KeyM_CertificateIdType intCertId, KeyM_CertificateStatusType intResult);
#endif

/* @Trace: KeyM_SUD_DATATYPE_010 */
typedef P2FUNC(Std_ReturnType,\
  KEYM_APPL_CODE, KeyM_RteCertificateVerifyCallbackNotificationFnType)(\
  KeyM_CertificateStatusType intResult);

/* @Trace: KeyM_SUD_DATATYPE_008 */
#if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON)
typedef P2FUNC(Std_ReturnType,\
  KEYM_APPL_CODE, KeyMCertificateElementConditionSenderReceiverFnType)(\
  uint32 * PtrSenderReceiverData);
#endif

/* @Trace: KeyM_SUD_DATATYPE_032 */
/* Structure for a element of certificate */
typedef struct
{
  /* Tag-Length-value structure  */
  KeyM_AsnElementType Element;
  /* Index of element configuration(KeyM_CertElementType)
    in the configuration array */
  uint16 ElementIndex;
} KeyM_ElementType;

/* @Trace: KeyM_SUD_DATATYPE_031 */
typedef struct
{
  /* Year   */
  uint16 Year;
  /* Month  */
  uint8 Mon;
  /* Day    */
  uint8 Day;
} KeyM_DateType;

/* @Trace: KeyM_SUD_DATATYPE_025 */
typedef struct
{
  /* The certificate element ID */
  const KeyM_CertElementIdType ElementId;
  /* The certificate element object ID */
  const uint8 * PtrElementObjectId;
  /* The length of certificate element object ID */
  const uint8 ObjectIdLength;
  /* This defines in which structure the certificate element is located */
  const KeyM_CertificateElementTypeOfStructure ElementOfStruct;
  #if (KEYM_CERT_ELEMENT_OBJECT_TYPE_ENABLED == STD_ON)
  /* The type of object */
  const uint8 ObjectType;
  #endif
  /* The maximum length of certificate element data */
  const uint16 ElementMaxLength;
  /* Defines if the certificate element can occur more than one time */
  boolean ElementHasIteration;
  /* Pointer to element value */
  KeyM_ElementType *PtrElement;
} KeyM_CertElementType;

#if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON)
/* @Trace: KeyM_SUD_DATATYPE_024 */
typedef struct
{
  /* The element data index */
  const uint16 ConditionArrayElementIndex;
  /* The element data is integer value */
  const uint64 ConditionArrayElementValue;
} KeyM_CertElementConditionArrayElementType;

/* @Trace: KeyM_SUD_DATATYPE_028 */
typedef struct
{
  #if (KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED == STD_ON)
  /* The pointer to a primitive value of integer that is used to
    compare with element value */
  const uint64 * const PtrConditionPrimitive;
  #endif

  #if (KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED == STD_ON)
  /* The pointer to a certificate element that is used to
    compare */
  const KeyM_CertElementType * const PtrCondCertElement;
  #endif

  #if (KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED == STD_ON)
  /* The array of integer values is used to
    compare with certificate element which has many element data */
  const KeyM_CertElementConditionArrayElementType * const PtrCondPrimitiveArray;
  /* The length of the above array */
  const uint16 CondPrimitiveArrayLength;
  #endif

  #if (KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED == STD_ON)
  /* The function pointer used to get SenderReceiver value */
  const KeyMCertificateElementConditionSenderReceiverFnType \
    CondSenderReceiverFunc;
  #endif
} KeyM_CertificateElementConditionValueType;

/* @Trace: KeyM_SUD_DATATYPE_027 */
typedef struct
{
  /* Condition type used to compare certificate element
    value with condition value */
  const KeyM_CertElementConditionType ConditionType;
  /* The pointer to certificate element */
  KeyM_CertElementType * const PtrCertElement;
  /* The condition values that is used to compare
    with certificate element value */
  const KeyM_CertificateElementConditionValueType ElementConditionValue;
} KeyM_CertificateElementConditionType;

/* @Trace: KeyM_SUD_DATATYPE_029 */
typedef struct
{
  /* Logical operator */
  const KeyM_LogicalOperator LogicalOperator;
  /* Element conditions are used as arguments for
    logical expression of the element rule */
  const KeyM_CertificateElementConditionType** PtrElementCondArgument;
  /* The number of element condition */
  const uint16 NumberOfCondition;
} KeyM_CertificateElementRuleType;

#endif /* #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON) */

/* @Trace: KeyM_SUD_DATATYPE_026 */
typedef struct
{
  /* Provides a unique name of the key for certificate */
  const uint8 * const PtrCertName;
  /* The length of certificate name */
  const uint16 CertNameLength;
  /* Identifier of the certificate. The set of configured identifiers shall be
    consecutive and gap-less. */
  const KeyM_CertificateIdType CertId;
  /* The maximum size in bytes of the certificate */
  const uint16 CertMaxLength;
  /* The pointer to certificate data */
  uint8 * PtrCertData;
  /* The size in bytes of a cert */
  uint16 CertLength;
  /* Specify the storage location of the certificate */
  const KeyM_KeyCertStorageType CertStorageType;
  /* The function name for the Rte certificate verify callback */
  const KeyM_RteCertificateVerifyCallbackNotificationFnType \
    RteCertVerifyCallback;
  #if (KEYM_CERT_VERIFY_APPLICATION_CALLBACK_ENABLE == STD_ON)
  /* The function name for the application certificate verify callback */
  const KeyM_CertificateVerifyCallbackNotificationFnType CertVerifyCallback;
  #endif
  #if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
  /* The function name for the Rte service certificate callback */
  const KeyM_RteServiceCertificateCallbackNotificationFnType \
    RteCertServiceCallback;
  #if (KEYM_CERT_SERVICE_APPLICATION_CALLBACK_ENABLE == STD_ON)
  /* The function name for the application service certificate callback */
  const KeyM_ServiceCertificateCallbackNotificationFnType CertServiceCallback;
  #endif
  #endif
  /* The Identifier of the certificate that is the next higher in
    the PKI hierarchical structure */
  const KeyM_CertificateIdType UpperHierarchicalCert;
  /* Specify in which format the certificate will be provided. */
  const KeyM_CertFormatType CertFormat;
  /* Specify in which format the certificate will be provided */
  const KeyM_CertAlgorithmType CertAlgorithm;
  /* The CSM job that is used for signature verification of
    a certain certificate */
  const KeyM_CsmJobType CsmSignVerifyJob;
  /* The CSM key ID associated to the CSM signature verify job */
  const uint32 CsmSignVerifyKeyId;
  #if (KEYM_CERT_SIGNATURE_GENERATE_ENABLED == STD_ON)
  /* The CSM job that is used for signature generation of
    a certain certificate */
  const KeyM_CsmJobType CsmSignGenerateJob;
  #endif
  #if (KEYM_USE_STBM == STD_ON)
  /* The reference to an StbM time base to validate the validity period */
  const StbM_SynchronizedTimeBaseType CertTimebaseId;
  #endif
  #if (KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED == STD_ON)
  /* The private key of a certificate */
  KeyM_CryptoKeyType * const PtrCertPrvKeyStorageKey;
  #endif
  /* The ID of associated CSM key where the certificate shall be stored to */
  const uint32 CsmTargetKeyId;
  #if (KEYM_CERT_ELEMENT_VERIFICATION_ENABLED == STD_ON)
  /* The certificate element rules which should be verified within the
    certification validation step */
  const KeyM_CertificateElementRuleType** PtrCertElementRule;
  /* The number of certificate element rule */
  const uint16 NumberOfElementRule;
  #endif
  /* The certificate elements */
  KeyM_CertElementType * const PtrCertElement;
  /* The number of certificate element */
  const uint16 NumberOfCertElement;
  /* Indicate the certificate is a root CA */
  const boolean IsRoot;
  /* Indicate the certificate is in progress (parsing, verifying) */
  uint8 InProgress;
  /* The status of the certificate */
  KeyM_CertificateStatusType CertStatus;
  #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
  /* The NvM block Id which used to store certificate */
  const NvM_BlockIdType NvmBlockId;
  #endif
  /* The pointer to parsed certificate or CRL */
  void * PtrParsedCert;
} KeyM_CertType;

#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

#endif /* KEYM_INT_TYPE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
