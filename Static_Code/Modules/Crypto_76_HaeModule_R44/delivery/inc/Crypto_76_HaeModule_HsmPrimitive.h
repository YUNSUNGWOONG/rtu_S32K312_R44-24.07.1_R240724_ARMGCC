#ifndef CRYPTO_76_HAEMODULE_PRIMITIVE_H
#define CRYPTO_76_HAEMODULE_PRIMITIVE_H

#include "Crypto_76_HaeModule_Crypto.h"
#include "Crypto_76_HaeModule_UserTypes.h"
#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
#include "Hsm_Cfg.h"
#endif

/*
 * Alogrithm Configuration
 * If an algorithm that is not supported by HSM is set to be undefined and an algorithm that is supported is set to be defined.
 */
/* AES 128, 256 */
#if (defined(HAEHSM_PRIMITIVE_AESENCECB_SUPPORT) || defined(HAEHSM_PRIMITIVE_AESENCCBC_SUPPORT) || defined(HAEHSM_PRIMITIVE_AESENCCTR_SUPPORT) || defined(HAEHSM_PRIMITIVE_AESENCOFB_SUPPORT) \
  || defined(HAEHSM_PRIMITIVE_AESDECECB_SUPPORT) || defined(HAEHSM_PRIMITIVE_AESDECCBC_SUPPORT) || defined(HAEHSM_PRIMITIVE_AESDECCTR_SUPPORT) || defined(HAEHSM_PRIMITIVE_AESDECOFB_SUPPORT))
#ifdef HAEHSM_CONFIG_AES_256_SUPPORT
  #define HAEHSM_PRIMITIVE_AES256_SUPPORT
#else
  #undef HAEHSM_PRIMITIVE_AES256_SUPPORT
#endif
#endif

/* ECC ECDH */
#ifdef HAEHSM_PRIMITIVE_ECCECDH_SUPPORT
#define HAEHSM_PRIMITIVE_ECCECDHP256R1_SUPPORT
#ifdef HAEHSM_CONFIG_P521R1_SUPPORT
  #define HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT
#else
  #undef HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT
#endif
#ifdef HAEHSM_CONFIG_X448_SUPPORT
  #define HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT
#else
  #undef HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT
#endif
#endif

#ifndef HSM_AES_GCM_TAG_LEN
#define HSM_AES_GCM_TAG_LEN                             (16)
#endif

#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
#define AES_128_KEY_BIT_SIZE                            (AES_BYTE_SIZE * 8)
#endif
#ifdef HAEHSM_PRIMITIVE_AES256_SUPPORT
#define AES_256_KEY_BIT_SIZE                            (AES_256_BYTE_SIZE * 8)
#endif

/*
 * Maximum length of the salt, in bytes.
 * It is a value between 0 and emLen - hLen - 2, where emLen is the size of the RSA modulus
 * and hLen is the size of the digest applied to the message to sign or verify.
 */
#define RSA_PKCS1_PSS_SALT_SIZE                         (RSA_BYTE_SIZE - SHA256_DIGEST_SIZE - 2)

#if defined(HAEHSM_PRIMITIVE_ECCECDSASIGNP521R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDSAVERIFYP521R1_SUPPORT)
#define HSM_CRYPTO_ECC_ECDSA_P521R1_SIGN_SIZE           (ECC_BYTES_SIZE_P521R1 + ECC_BYTES_SIZE_P521R1 - 4)
#endif

#ifdef HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT
#define HSM_CRYPTO_ECC_PUBLICKEY_P521R1_SIZE            (ECC_BYTES_SIZE_P521R1 + ECC_BYTES_SIZE_P521R1 - 4)
#define HSM_CRYPTO_ECC_BYTES_SIZE_P521R1                (ECC_BYTES_SIZE_P521R1 - 2)
#endif

/*
 * Alogrithm Configuration
 * If an algorithm that is not supported by HSM is set to be undefined and an algorithm that is supported is set to be defined.
 */
/* AES 128, 256 */
#if (defined(HAEHSM_PRIMITIVE_AESENCECB_SUPPORT) || defined(HAEHSM_PRIMITIVE_AESENCCBC_SUPPORT) || defined(HAEHSM_PRIMITIVE_AESENCCTR_SUPPORT) || defined(HAEHSM_PRIMITIVE_AESENCOFB_SUPPORT) \
  || defined(HAEHSM_PRIMITIVE_AESDECECB_SUPPORT) || defined(HAEHSM_PRIMITIVE_AESDECCBC_SUPPORT) || defined(HAEHSM_PRIMITIVE_AESDECCTR_SUPPORT) || defined(HAEHSM_PRIMITIVE_AESDECOFB_SUPPORT))
#ifdef HAEHSM_CONFIG_AES_256_SUPPORT
  #define HAEHSM_PRIMITIVE_AES256_SUPPORT
#else
  #undef HAEHSM_PRIMITIVE_AES256_SUPPORT
#endif
#endif

/* ECC ECDH */
#ifdef HAEHSM_PRIMITIVE_ECCECDH_SUPPORT
#define HAEHSM_PRIMITIVE_ECCECDHP256R1_SUPPORT
#ifdef HAEHSM_CONFIG_P521R1_SUPPORT
  #define HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT
#else
  #undef HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT
#endif
#ifdef HAEHSM_CONFIG_X448_SUPPORT
  #define HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT
#else
  #undef HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT
#endif
#endif



#ifndef HSM_AES_GCM_TAG_LEN
#define HSM_AES_GCM_TAG_LEN                             (16)
#endif

#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
#define AES_128_KEY_BIT_SIZE                            (AES_BYTE_SIZE * 8)
#endif
#ifdef HAEHSM_PRIMITIVE_AES256_SUPPORT
#define AES_256_KEY_BIT_SIZE                            (AES_256_BYTE_SIZE * 8)
#endif

/*
 * Maximum length of the salt, in bytes.
 * It is a value between 0 and emLen - hLen - 2, where emLen is the size of the RSA modulus
 * and hLen is the size of the digest applied to the message to sign or verify.
 */
#define RSA_PKCS1_PSS_SALT_SIZE                         (RSA_BYTE_SIZE - SHA256_DIGEST_SIZE - 2)

#if defined(HAEHSM_PRIMITIVE_ECCECDSASIGNP521R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDSAVERIFYP521R1_SUPPORT)
#define HSM_CRYPTO_ECC_ECDSA_P521R1_SIGN_SIZE           (ECC_BYTES_SIZE_P521R1 + ECC_BYTES_SIZE_P521R1 - 4)
#endif

#ifdef HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT
#define HSM_CRYPTO_ECC_PUBLICKEY_P521R1_SIZE            (ECC_BYTES_SIZE_P521R1 + ECC_BYTES_SIZE_P521R1 - 4)
#define HSM_CRYPTO_ECC_BYTES_SIZE_P521R1                (ECC_BYTES_SIZE_P521R1 - 2)
#endif


/* Sha256 must be supported for EccEcdsaSign */
#ifdef HAEHSM_PRIMITIVE_ECCECDSASIGN_SUPPORT
#ifndef HAEHSM_PRIMITIVE_SHA256_SUPPORT
#define HAEHSM_PRIMITIVE_SHA256_SUPPORT
#endif
#endif
/* Sha512 must be supported for EccEcdsaSignP521r1 */
#ifdef HAEHSM_PRIMITIVE_ECCECDSASIGNP521R1_SUPPORT
#ifndef HAEHSM_PRIMITIVE_SHA512_SUPPORT
#define HAEHSM_PRIMITIVE_SHA512_SUPPORT
#endif
#endif
/* Sha256 must be supported for RsaPkcs1v15Verify */
#ifdef HAEHSM_PRIMITIVE_RSAPKCS1V15VERIFY_SUPPORT
#ifndef HAEHSM_PRIMITIVE_SHA256_SUPPORT
#define HAEHSM_PRIMITIVE_SHA256_SUPPORT
#endif
#endif
/* Sha160 must be supported for Sha1_RsaPkcs1v15Verify */
#ifdef HAEHSM_PRIMITIVE_SHA1_RSAPKCS1V15VERIFY_SUPPORT
#ifndef HAEHSM_PRIMITIVE_SHA160_SUPPORT
#define HAEHSM_PRIMITIVE_SHA160_SUPPORT
#endif
#endif
/* Sha256 must be supported for EccEcdsaVerify */
#ifdef HAEHSM_PRIMITIVE_ECCECDSAVERIFY_SUPPORT
#ifndef HAEHSM_PRIMITIVE_SHA256_SUPPORT
#define HAEHSM_PRIMITIVE_SHA256_SUPPORT
#endif
#endif
/* Sha512 must be supported for EccEcdsaVerifyP521r1 */
#ifdef HAEHSM_PRIMITIVE_ECCECDSAVERIFYP521R1_SUPPORT
#ifndef HAEHSM_PRIMITIVE_SHA512_SUPPORT
#define HAEHSM_PRIMITIVE_SHA512_SUPPORT
#endif
#endif
/* Sha256 must be supported for RsaPkcs1v15Sign */
#ifdef HAEHSM_PRIMITIVE_RSAPKCS1V15SIGN_SUPPORT
#ifndef HAEHSM_PRIMITIVE_SHA256_SUPPORT
#define HAEHSM_PRIMITIVE_SHA256_SUPPORT
#endif
#endif
/* Sha256 must be supported for RsaPkcs1PssSign */
#ifdef HAEHSM_PRIMITIVE_RSAPKCS1PSSSIGN_SUPPORT
#ifndef HAEHSM_PRIMITIVE_SHA256_SUPPORT
#define HAEHSM_PRIMITIVE_SHA256_SUPPORT
#endif
#endif
/* Sha256 must be supported for RsaPkcs1PssVerify */
#ifdef HAEHSM_PRIMITIVE_RSAPKCS1PSSVERIFY_SUPPORT
#ifndef HAEHSM_PRIMITIVE_SHA256_SUPPORT
#define HAEHSM_PRIMITIVE_SHA256_SUPPORT
#endif
#endif

#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
/* Normal Case */
typedef struct 
{
    uint32 timeout;
} HaeHsmPrimitiveVariable_Start;
typedef struct
{
    uint32 remainDataLen;
    uint32 maxTxLen;
    uint32 txIndex;
    uint32 txLen;
    uint32 timeout;
} HaeHsmPrimitiveVariable_Update;
typedef struct 
{
    uint32 timeout;
} HaeHsmPrimitiveVariable_Finish;

/* HaeHsm_Primtive_Crypto_Pbkdf2 */
typedef struct
{
    uint16 keyNum;
    uint32 timeout;
} HaeHsmPrimitiveVariable_Pbkdf2_Start;
typedef struct
{
    uint8 *password;
    uint32 pLen;
    uint8 *salt;
    uint32 sLen;
    uint32 icount;
    uint8 *derivedKey;
    uint32 dkLen;
    uint32 timeout;
} HaeHsmPrimitiveVariable_Pbkdf2_Update;
typedef struct 
{
    uint32 timeout;
} HaeHsmPrimitiveVariable_Pbkdf2_Finish;
typedef struct
{
  HaeHsmPrimitiveVariable_Pbkdf2_Start  start;
  HaeHsmPrimitiveVariable_Pbkdf2_Update update;
  HaeHsmPrimitiveVariable_Pbkdf2_Finish finish;
} 
HaeHsmPrimitiveVariable_Pbkdf2;

/* The union of primitive variables */
typedef union 
{
    HaeHsmPrimitiveVariable_Start   start;
    HaeHsmPrimitiveVariable_Update  update;
    HaeHsmPrimitiveVariable_Finish  finish;
    /* Pbkdef2 */
    HaeHsmPrimitiveVariable_Pbkdf2  Pbkdf2;
} HaeHsmPrimitiveVariable;

 typedef struct
{
    HSMAPI_CTX_t                HsmApiCtx;
    uint32                      mode;           /* Save the current mode. */
    uint32                      state;          /* Save the current state. */
    HaeHsmPrimitiveVariable     var;            /* Stores variables to be used when re-entering the state of the current mode. */
} HaeHsmPrimitiveData;
#endif

#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
void HaeHsm_Primtive_Init( CryptoDriverObject *Object );
void HaeHsm_Primitive_GetState(uint32 *mode, uint32 *state);
void HaeHsm_Primitive_SetState(uint32 mode, uint32 state);
#endif
#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
Std_ReturnType HaeHsm_Primtive_CancelJob( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_SHA160_SUPPORT
Std_ReturnType HaeHsm_Primitive_Sha160( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_SHA256_SUPPORT
Std_ReturnType HaeHsm_Primitive_Sha256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_SHA512_SUPPORT
Std_ReturnType HaeHsm_Primitive_Sha512( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_SHA512_224_SUPPORT
Std_ReturnType HaeHsm_Primitive_Sha512_224( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_SHA512_256_SUPPORT
Std_ReturnType HaeHsm_Primitive_Sha512_256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_SHAKE256_SUPPORT
Std_ReturnType HaeHsm_Primitive_Shake256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_AESCMAC_GEN_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesCmac_Gen( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_HMACSHA256_GEN_SUPPORT
Std_ReturnType HaeHsm_Primitive_HmacSha256_Gen( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_AESCMAC_VERIFY_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesCmac_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_HMACSHA256_VERIFY_SUPPORT
Std_ReturnType HaeHsm_Primitive_HmacSha256_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_AESENCECB_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesEncECB( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_AESENCCBC_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesEncCBC( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_AESENCCTR_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesEncCTR( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_AESENCOFB_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesEncOFB( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_AESENCGCM_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesEncGCM( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_RSAPKCS1OAEPENC_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs1oaepEnc( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_RSAPKCS1V15ENC_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs1v15Enc( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_AESDECECB_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesDecECB( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_AESDECCBC_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesDecCBC( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_AESDECCTR_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesDecCTR( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_AESDECOFB_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesDecOFB( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_AESDECGCM_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesDecGCM( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_RSAPKCS1OAEPDEC_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs1oaepDec( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_RSAPKCS1V15DEC_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs1v15Dec( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_RSAPKCS1V15SIGN_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs1v15Sign( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_RSAPKCS1PSSSIGN_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs1PssSign( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_ECCECDSASIGN_SUPPORT
Std_ReturnType HaeHsm_Primitive_EccEcdsaSign( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_ECCECDSASIGNP521R1_SUPPORT
Std_ReturnType HaeHsm_Primitive_EccEcdsaSignP521r1( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_ECCEDDSASIGNED448_SUPPORT
Std_ReturnType HaeHsm_Primitive_EccEddsaSignEd448( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_RSAPKCS1V15VERIFY_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs1v15Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_SHA1_RSAPKCS1V15VERIFY_SUPPORT
Std_ReturnType HaeHsm_Primitive_Sha1_RsaPkcs1v15Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_RSAPKCS1PSSVERIFY_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs1PssVerify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_ECCECDSAVERIFY_SUPPORT
Std_ReturnType HaeHsm_Primitive_EccEcdsaVerify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_ECCECDSAVERIFYP521R1_SUPPORT
Std_ReturnType HaeHsm_Primitive_EccEcdsaVerifyP521r1( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_ECCEDDSAVERIFYED448_SUPPORT
Std_ReturnType HaeHsm_Primitive_EccEddsaVerifyEd448( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_ECCECDH_SUPPORT
Std_ReturnType HaeHsm_Primitive_EccEcdh( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_PSEUDORANDOMGENERATE_SUPPORT
Std_ReturnType HaeHsm_Primitive_PseudoRandomGenerate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_CUSTOM_PSEUDORANDOMGENERATE_SUPPORT
Std_ReturnType HaeHsm_Primitive_Custom_PseudoRandomGenerate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_TRUERANDOMGENERATE_SUPPORT
Std_ReturnType HaeHsm_Primitive_TrueRandomGenerate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_KEYDERIVE_SUPPORT
Std_ReturnType HaeHsm_Primitive_KeyDerive( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_RSAPKCS3DHKEYPAIRGEN_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs3DHKeypairGen( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_RSAPKCS3DHSHAREDVALUEGEN_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs3DHSharedValueGen( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#ifdef HAEHSM_PRIMITIVE_KEYSETVALID_SUPPORT
Std_ReturnType HaeHsm_Primitive_KeySetValid( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif
#if defined(HAEHSM_PRIMITIVE_KEYDERIVE_SUPPORT)
Std_ReturnType HaeHsm_Primitive_Crypto_KeyDerive( uint32 cryptoKeyId, uint32 targetCryptoKeyId, uint32 AlgorithmType );
#endif
#if defined(HAEHSM_PRIMITIVE_RSAPKCS3DHKEYPAIRGEN_SUPPORT)
Std_ReturnType HaeHsm_Primitive_Crypto_KeyExchangeCalcPubVal( uint32 cryptoKeyId, uint8* publicValuePtr, uint32* publicValueLengthPtr, uint32 AlgorithmType );
#endif
#if defined(HAEHSM_PRIMITIVE_RSAPKCS3DHSHAREDVALUEGEN_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDH_SUPPORT) \
    || defined(HAEHSM_PRIMITIVE_ECCECDHP256R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT)
Std_ReturnType HaeHsm_Primitive_Crypto_KeyExchangeCalcSecret( uint32 cryptoKeyId, const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength, uint32 AlgorithmType );
#endif

#endif /* CRYPTO_76_HAEMODULE_PRIMITIVE_H */
