/*!
  @file Crypto_76_HaeModule_CryptoLibPrimitive.c
  @brief CryptoLib Primitives file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef CRYPTO_76_HAEMODULE_CRYPTOLIBPRIMITIVE_H
#define CRYPTO_76_HAEMODULE_CRYPTOLIBPRIMITIVE_H

#include "Crypto_76_HaeModule_Crypto.h"
#include "Crypto_76_HaeModule_UserTypes.h"

#define CRYPTO_BUFFER_MAX_LENGTH 64

#ifdef HAEMODULE_CRYPTOOBJECT_HAECRYPTOLIB_SUPPORT

#if defined (HAECRYPTOLIB_PRIMITIVE_SHA160_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA160_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_VERIFY_SUPPORT)
#include "Hmg_Sha160.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_SHA224_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_SHA256_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA256_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_VERIFY_SUPPORT)
#include "Hmg_Sha256.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_SHA384_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA384_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_SHA512_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_SHA512_224_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_SHA512_256_SUPPORT)
#include "Hmg_Sha512.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA160_VERIFY_SUPPORT)
#include "Hmg_HmacSha160.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA256_VERIFY_SUPPORT)
#include "Hmg_HmacSha256.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA384_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA512_VERIFY_SUPPORT)
#include "Hmg_HmacSha512.h"
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHAKE256_SUPPORT
#include "Hmg_Keccak.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_TDESECB_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_TDESECB_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_TDESECB_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_TDESECB_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_TDESCBC_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_TDESCBC_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_TDESCTR_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_TDESCTR_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_TDESCMAC_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_TDESCMAC_VERIFY_SUPPORT)
#include "Hmg_Tdes.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_AESECB_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESECB_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_AESCBC_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESCBC_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_AESOFB_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESOFB_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_AESCTR_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESCTR_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_AESGCM_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESGCM_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_AESCMAC_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESCMAC_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_AESGMAC_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESGMAC_VERIFY_SUPPORT)
#include "Hmg_Aes.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_CHACHA20_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_CHACHA20_DECRYPT_SUPPORT)
#include "Hmg_Chacha.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_CHACHA20POLY1305_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_CHACHA20POLY1305_DECRYPT_SUPPORT)
#include "Hmg_Chacha20Poly1305.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA160_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA160_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA224_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA224_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA256_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA256_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA384_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA384_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA512_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA512_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSAESPKCS15_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSAESPKCS15_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA160_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA256_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA384_VERIFY_SUPPORT)
#include "Hmg_Pkcs1.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDH_CALCPUBVAL_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDH_CALCSECRET_SUPPORT)
#include "Hmg_Ecc.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_EDDSAED448_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_EDDSAED448_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDH_CALCPUBVAL_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDH_CALCSECRET_SUPPORT)
#include "Hmg_Curve448.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_DH_CALCPUBVAL_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_DH_CALCSECRET_SUPPORT)
#include "Hmg_DiffieHellman.h"
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_HASHDRBGSHA256_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HASHDRBGSHA256_GENERATE_SUPPORT)
#include "Hmg_HDrbg.h"
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_PBKDF2HMACSHA256_SUPPORT
#include "Hmg_Pbkdf2.h"
#endif

typedef union {
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA160_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA160_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_VERIFY_SUPPORT)
    HmgSha160Ctx hash_sha160;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA224_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_VERIFY_SUPPORT)
    HmgSha224Ctx hash_sha224;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA256_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA256_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_VERIFY_SUPPORT)
    HmgSha256Ctx hash_sha256;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA384_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA384_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_VERIFY_SUPPORT)
    HmgSha384Ctx hash_sha384;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA512_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_VERIFY_SUPPORT)
    HmgSha512Ctx hash_sha512;
#endif
#ifdef HAECRYPTOLIB_PRIMITIVE_SHA512_224_SUPPORT
    HmgSha512Ctx hash_sha512_224;
#endif
#ifdef HAECRYPTOLIB_PRIMITIVE_SHA512_256_SUPPORT
    HmgSha512Ctx hash_sha512_256;
#endif
#ifdef HAECRYPTOLIB_PRIMITIVE_SHAKE256_SUPPORT
    HmgKeccakCtx hash_shake256;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA160_VERIFY_SUPPORT)
    HmgHmacSha160Ctx hmac_sha160;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA224_VERIFY_SUPPORT)
    HmgHmacSha224Ctx hmac_sha224;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA256_VERIFY_SUPPORT)
    HmgHmacSha256Ctx hmac_sha256;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA384_VERIFY_SUPPORT)
    HmgHmacSha384Ctx hmac_sha384;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA512_VERIFY_SUPPORT)
    HmgHmacSha512Ctx hmac_sha512;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_TDESECB_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_TDESECB_DECRYPT_SUPPORT)
    HmgTdesEcbCtx tdesEcb;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_TDESCBC_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_TDESCBC_DECRYPT_SUPPORT)
    HmgTdesCbcCtx tdesCbc;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_TDESCTR_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_TDESCTR_DECRYPT_SUPPORT)
    HmgTdesCtrCtx tdesCtr;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_TDESCMAC_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_TDESCMAC_VERIFY_SUPPORT)
    HmgTdesCmacCtx tdesCmac;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_AESECB_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESECB_DECRYPT_SUPPORT)
    HmgAesEcbCtx aesEcb;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_AESCBC_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESCBC_DECRYPT_SUPPORT)
    HmgAesCbcCtx aesCbc;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_AESOFB_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESOFB_DECRYPT_SUPPORT)
    HmgAesOfbCtx aesOfb;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_AESCTR_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESCTR_DECRYPT_SUPPORT)
    HmgAesCtrCtx aesCtr;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_AESGCM_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESGCM_DECRYPT_SUPPORT)
    HmgAesGcmSliceCtx aesGcm;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_AESCMAC_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESCMAC_VERIFY_SUPPORT)
    HmgAesCmacCtx aesCmac;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_AESGMAC_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESGMAC_VERIFY_SUPPORT)
    HmgAesGmacCtx aesGmac;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_CHACHA20_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_CHACHA20_DECRYPT_SUPPORT)
    HmgChachaCtx chacha20;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_CHACHA20POLY1305_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_CHACHA20POLY1305_DECRYPT_SUPPORT)
    HmgChachaPolyCtx chachaPoly;
#endif
} cryptoLib_union;

typedef struct {
    uint8 *key;
    uint8 *nonce;
} cryptoLib_chacha_poly;

typedef struct {
    uint8 *mod;
    uint8 *exp;
    uint8 *seed_salt;
    uint32 saltLength;
} cryptoLib_rsa;

typedef struct {
    uint8 *x;
    uint8 *y;
    uint32 keyLength;
    uint8 *salt;
} cryptoLib_ecc;

typedef union {
    const uint8 *inputPtr;
    HAEMODULE_EDDSA_ED448_INTPUT_t *param;
} cryptoLib_eddsa_in;

typedef struct {
    uint8 *key;
    cryptoLib_eddsa_in in;
} cryptoLib_eddsa;

/*
 * You can declare global variables used in HaeCryptoLibPrimitive.
 * This global variable is passed as a parameter every time Primitive is called.
 */
typedef struct {
    cryptoLib_union unionCtx;
    uint32 hashDrbg_sha256_instance;
#if defined (HAECRYPTOLIB_PRIMITIVE_HASHDRBGSHA256_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HASHDRBGSHA256_GENERATE_SUPPORT)
    HmgHdrbgSha256Ctx hashDrbg_sha256;
#endif
    cryptoLib_chacha_poly chachaPoly;
    cryptoLib_rsa rsa;
    cryptoLib_ecc ecc;
    cryptoLib_eddsa eddsa;
    Crypto_AlgorithmFamilyType secondaryFamily;
} HaeCryptoLibPrimitiveData;

#endif /* HAEMODULE_CRYPTOOBJECT_HAECRYPTOLIB_SUPPORT */

#ifdef HAEMODULE_CRYPTOOBJECT_HAECRYPTOLIB_SUPPORT
void HaeCryptoLib_Primtive_Init( CryptoDriverObject *Object );
void HaeCryptoLib_Primitive_GetState(uint32 *mode, uint32 *state);
void HaeCryptoLib_Primitive_SetState(uint32 mode, uint32 state);
#endif
#ifdef HAEMODULE_CRYPTOOBJECT_HAECRYPTOLIB_SUPPORT
Std_ReturnType HaeCryptoLib_Primtive_CancelJob( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA160_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha160( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA224_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha224( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA256_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA384_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha384( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA512_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha512( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA512_224_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha512_224( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA512_256_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha512_256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHAKE256_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Shake256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA160_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HmacSha160_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA160_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HmacSha160_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA224_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HmacSha224_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA224_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HmacSha224_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA256_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HmacSha256_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA256_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HmacSha256_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA384_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HmacSha384_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA384_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HmacSha384_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA512_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HmacSha512_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA512_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HmacSha512_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESECB_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_TdesEcb_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESECB_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_TdesEcb_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESCBC_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_TdesCbc_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESCBC_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_TdesCbc_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESCTR_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_TdesCtr_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESCTR_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_TdesCtr_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESCMAC_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_TdesCmac_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESCMAC_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_TdesCmac_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESECB_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesEcb_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESECB_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesEcb_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESCBC_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesCbc_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESCBC_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesCbc_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESOFB_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesOfb_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESOFB_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesOfb_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESCTR_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesCtr_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESCTR_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesCtr_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESGCM_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesGcm_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESGCM_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesGcm_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESCMAC_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesCmac_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESCMAC_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesCmac_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESGMAC_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesGmac_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESGMAC_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesGmac_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_CHACHA20_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Chacha20_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_CHACHA20_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Chacha20_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_CHACHA20POLY1305_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Chacha20Poly1305_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_CHACHA20POLY1305_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Chacha20Poly1305_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESXTS_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesXts_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESXTS_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesXts_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA160_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha160_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA160_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha160_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA224_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha224_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA224_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha224_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA256_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha256_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA256_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha256_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA384_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha384_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA384_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha384_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA512_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha512_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA512_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha512_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESPKCS15_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesPkcs15_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESPKCS15_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesPkcs15_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha160_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha160_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha224_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha224_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha256_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha256_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha384_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha384_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha512_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha512_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA160_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha160_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA160_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha160_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA224_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha224_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA224_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha224_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA256_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha256_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA256_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha256_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA384_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha384_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA384_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha384_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha160_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha160_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha224_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha224_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha256_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha256_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha384_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha384_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha512_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha512_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_EDDSAED448_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EddsaEd448_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_EDDSAED448_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EddsaEd448_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_DH_CALCPUBVAL_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Dh_CalcPubVal( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_DH_CALCSECRET_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Dh_CalcSecret( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDH_CALCPUBVAL_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Ecdh_CalcPubVal( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDH_CALCSECRET_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Ecdh_CalcSecret( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_PBKDF2HMACSHA256_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Pbkdf2HmacSha256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HASHDRBGSHA256_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HashDrbgSha256_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HASHDRBGSHA256_SEED_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HashDrbgSha256_Seed( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_KEYSETVALID_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_KeySetValid( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job );
#endif

#endif /* CRYPTO_76_HAEMODULE_CRYPTOLIBPRIMITIVE_H */
