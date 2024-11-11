/*!
  @file Crypto_76_HaeModule_UserTypes.h
  @brief User type definition header file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef CRYPTO_76_HAEMODULE_USERTYPES_H
#define CRYPTO_76_HAEMODULE_USERTYPES_H

/* Alogrithm Curve Type */
#define HAEMODULE_CRYPTO_CURVETYPE_P160R1         (0x01)
#define HAEMODULE_CRYPTO_CURVETYPE_P224R1         (0x02)
#define HAEMODULE_CRYPTO_CURVETYPE_P256R1         (0x03)
#define HAEMODULE_CRYPTO_CURVETYPE_P521R1         (0x05)
#define HAEMODULE_CRYPTO_CURVETYPE_CURVE448       (0x06)

/* CRYPTO_KE_RANDOM_ALGORITHM */
#define HAEMODULE_CRYPTO_DRBG_SHA256              (0x01)

/* CRYPTO_KE_KEYEXCHANGE_ALGORITHM */
#define HAEMODULE_CRYPTO_DH                       (0x01)
#define HAEMODULE_CRYPTO_ECDH                     (0x02)
#define HAEMODULE_CRYPTO_DH_HSM                   (0x81)
#define HAEMODULE_CRYPTO_ECDH_HSM                 (0x82)

/* CRYPTO_KE_KEYDERIVATION_ALGORITHM */
#define HAEMODULE_CRYPTO_PBKDF2_HMAC_SHA256       (0x01)
#define HAEMODULE_CRYPTO_PBKDF2_HMAC_SHA256_HSM   (0x81)


extern boolean g_cryptoLib_gcmLastUpdateCall;
extern boolean g_cryptoLib_gmacLastUpdateCall;

typedef struct
{
    uint8* textPtr;             /* plaintext/ciphertext data */
    uint32 textLength;          /* plaintext/ciphertext byte size */
    uint8* labelPtr;            /* Label data */
    uint32 labelLength;         /* Label byte size */
} HAEMODULE_RSAES_OAEP_INPUT_t;

typedef struct
{
    uint8* message;             /* message data */
    uint32 messageLength;       /* message byte size */
    uint8* context;             /* context data */
    uint32 contextLength;       /* context byte size */
} HAEMODULE_EDDSA_ED448_INTPUT_t;

#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
typedef struct
{
    uint8* digestPtr;
    uint8* saltPtr;
    uint32 saltLength;
} HSM_RSA_PKCS1_PSS_SIGNGENERATE_INTPUT_t;
#endif

#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
typedef struct
{
    uint8* digestPtr;
    uint32 saltLength;
} HSM_RSA_PKCS1_PSS_SIGNVERIFY_INTPUT_t;
#endif

#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
typedef struct
{
    uint8* digestPtr;
    uint8* secretNumberPtr;
} HSM_ECC_ECDSA_SIGNGENERATE_INTPUT_t;
#endif

#endif /* CRYPTO_76_HAEMODULE_USERTYPES_H */
