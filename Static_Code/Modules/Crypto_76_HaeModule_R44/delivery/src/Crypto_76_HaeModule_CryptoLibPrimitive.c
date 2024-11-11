/*!
  @file Crypto_76_HaeModule_CryptoLibPrimitive.c
  @brief CryptoLib Primitives file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rghts reserved.
*/
#include "Crypto_76_HaeModule_CryptoLibPrimitive.h"
#include "Crypto_76_HaeModule_Common.h"
#include "Crypto_76_HaeModule_Job.h"
#include "Crypto_76_HaeModule_Key.h"
#include "Crypto_76_HaeModule_Det.h"

#define CRYPTO_76_HAEMODULE_START_RAM_VAR_CLEARED
#include "Crypto_76_HaeModule_MemMap.h"
#ifdef HAEMODULE_CRYPTOOBJECT_HAECRYPTOLIB_SUPPORT
static HaeCryptoLibPrimitiveData gHaeCryptoLib_PrimitiveData;
#endif
#define CRYPTO_76_HAEMODULE_STOP_RAM_VAR_CLEARED
#include "Crypto_76_HaeModule_MemMap.h"


#define CRYPTO_76_HAEMODULE_START_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"

#ifdef HAEMODULE_CRYPTOOBJECT_HAECRYPTOLIB_SUPPORT
#include "Hmg_Common.h"

boolean g_cryptoLib_gcmLastUpdateCall = 1;
boolean g_cryptoLib_gmacLastUpdateCall = 1;

typedef union {
    const uint8 *pConst;
    uint8 *p;
} ConstToPointer;

typedef struct {
    CryptoKeyElement *key;
    CryptoKeyElement *key2;
    uint32 curveType;
} HaeCryptoLibKeyData;

typedef Std_ReturnType(*START)(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element);
typedef Std_ReturnType(*UPDATE)(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput);
typedef Std_ReturnType(*FINISH)(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput);

typedef Std_ReturnType(*KEY_OPERATION)(uint32 cryptoKeyId, uint32 targetCryptoKey, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput);

#define CRYPTO_KE_KEY 1
#define CRYPTO_KE_IV 5
#define CRYPTO_KE_SALT 13
#define CRYPTO_KE_SEED 16
#define CRYPTO_KE_CURVETYPE 29
#define CRYPTO_KE_BASE 8
#define CRYPTO_KE_PRIVKEY 9
#define CYRPTO_KE_SHAREDVALUE 1
#define CRYPTO_KE_PASSWORD 1
#define CRYPTO_KE_ITERATIONS 14

void HaeCryptoLib_Primtive_Init( CryptoDriverObject *Object )
{
    Object->PrimitiveData = (CryptoPrimitiveData *)&gHaeCryptoLib_PrimitiveData;
    gHaeCryptoLib_PrimitiveData.hashDrbg_sha256_instance = 0;
    gHaeCryptoLib_PrimitiveData.chachaPoly.key = NULL;
    gHaeCryptoLib_PrimitiveData.chachaPoly.nonce = NULL;
}

/* [Caution] The function below is to use the feature to execute each mode (Start/Update/Finish) multiple times. 
   The current settings are set to disable this feature. */
void HaeCryptoLib_Primitive_GetState(uint32 *mode, uint32 *state)
{
    *mode  = 0;
    *state = (uint32)HAEMODULE_PRIMITIVESTATE_END;
}

/* [Caution] The function below is to use the feature to execute each mode (Start/Update/Finish) multiple times. 
   The current settings are set to disable this feature. */
void HaeCryptoLib_Primitive_SetState(uint32 mode, uint32 state)
{
    /* Nothing to do */
}

Std_ReturnType HaeCryptoLib_Primtive_CancelJob( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    /* Nothing to do */
    return E_OK;
}

static Std_ReturnType isReadAccess(const CryptoKeyElement *element) {
    Std_ReturnType result = E_OK;

    if (element == NULL) {
        result = CRYPTO_E_KEY_EMPTY;
    }
    else if ((element->CryptoKeyElementValue == NULL) || (element->CryptoKeyElementValueState == FALSE)) {
        result = CRYPTO_E_KEY_NOT_AVAILABLE;
    }
    else if (element->CryptoKeyElementReadAccess == CRYPTO_RA_DENIED) {
        result = CRYPTO_E_KEY_READ_FAIL;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType isWriteAccess(const CryptoKeyElement *element) {
    Std_ReturnType result = E_OK;

    if (element == NULL) {
        result = CRYPTO_E_KEY_EMPTY;
    }
    else if (element->CryptoKeyElementValue == NULL) {
        result = CRYPTO_E_KEY_NOT_AVAILABLE;
    }
    else if (element->CryptoKeyElementWriteAccess == CRYPTO_WA_DENIED) {
        result = CRYPTO_E_KEY_WRITE_FAIL;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_SetKey(HaeCryptoLibKeyData *element, uint32 cryptoKeyId, const Crypto_AlgorithmInfoType *algorithm, const Crypto_ServiceInfoType service) {
    Std_ReturnType result = E_OK;

    /* This function should always be checked in the last position. */
    if(HaeModule_CryptoKeyId_Lock(cryptoKeyId) != TRUE)
    {
        result = CRYPTO_E_BUSY;
    }
    else {
        element->key = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEY);
        result = isReadAccess(element->key);

        if ((result == E_OK)
        && ((algorithm->mode == CRYPTO_ALGOMODE_CBC)
            || (algorithm->mode == CRYPTO_ALGOMODE_OFB)
            || (algorithm->mode == CRYPTO_ALGOMODE_CTR)
            || (algorithm->mode == CRYPTO_ALGOMODE_GCM)
            || (algorithm->mode == CRYPTO_ALGOMODE_GMAC)
            || (algorithm->family == CRYPTO_ALGOFAM_CHACHA))) {
            element->key2 = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_IV);
            result = isReadAccess(element->key2);
            if (result != E_OK) {
                element->key2 = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_IV + 1000);
                result = isReadAccess(element->key2);
            }
        }

        if ((result == E_OK)
        && (algorithm->mode == CRYPTO_ALGOMODE_RSAES_OAEP)) {
            element->key2 = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_SEED);
            result = isReadAccess(element->key2);
            if (result != E_OK) {
                element->key2 = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_SEED + 1000);
                result = isReadAccess(element->key2);
            }
        }

        if ((result == E_OK)
        && ((algorithm->mode == CRYPTO_ALGOMODE_RSASSA_PSS)
            || ((algorithm->family == CRYPTO_ALGOFAM_ECCNIST) && (algorithm->secondaryFamily != CRYPTO_ALGOFAM_SHAKE256)))) {
            element->key2 = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_SALT);
            result = isReadAccess(element->key2);
            if (result != E_OK) {
                element->key2 = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_SALT + 1000);
                result = isReadAccess(element->key2);
            }
        }

        if ((result == E_OK)
        && ((algorithm->family == CRYPTO_ALGOFAM_ECCNIST) && (algorithm->secondaryFamily != CRYPTO_ALGOFAM_SHAKE256))) {
            CryptoKeyElement *curve = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_CURVETYPE);
            result = isReadAccess(curve);
            if (result == E_OK) {
                HMG_MEMCPY((uint8*)&element->curveType, curve->CryptoKeyElementValue, (uint32)sizeof(uint32));
            }
        }

        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
    }

    return result;
}

typedef union {
    CryptoPrimitiveData *primitiveData;
    HaeCryptoLibPrimitiveData *ctx;
} cryptoLibData_in;

static Std_ReturnType CryptoLib_Operation(CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job, START start, UPDATE update, FINISH finish) {
    cryptoLibData_in in;
    Std_ReturnType result = E_NOT_OK;
    Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput = &job->jobPrimitiveInputOutput;
    const Crypto_ServiceInfoType service = job->jobPrimitiveInfo->primitiveInfo->service;
    const Crypto_AlgorithmInfoType *algorithm = &job->jobPrimitiveInfo->primitiveInfo->algorithm;
    Std_ReturnType work = E_OK;

    in.primitiveData = PrimitiveData;

    if ((jobPrimitiveInputOutput->mode & CRYPTO_OPERATIONMODE_START) != 0) {
        HaeCryptoLibKeyData element = { NULL, NULL, 0 };

        if (service == CRYPTO_HASH) {
            in.ctx->secondaryFamily = algorithm->family;
            result = E_OK;
        }
        else if (HaeModule_Crypto_Get_Key(job->cryptoKeyId) == NULL) {
            result = CRYPTO_E_KEY_NOT_AVAILABLE;
        }
        else {
            in.ctx->secondaryFamily = algorithm->secondaryFamily;
            result = CryptoLib_SetKey(&element, job->cryptoKeyId, algorithm, service);
        }

        if (result == E_OK) {
            result = start(in.ctx, &element);
            if (result != E_OK) {
                work = E_NOT_OK;
            }
        }
    }

    if (((jobPrimitiveInputOutput->mode & CRYPTO_OPERATIONMODE_UPDATE) != 0)
    && (work == E_OK)) {
        result = update(in.ctx, jobPrimitiveInputOutput);
        if (result != E_OK) {
            work = E_NOT_OK;
        }
    }

    if (((jobPrimitiveInputOutput->mode & CRYPTO_OPERATIONMODE_FINISH) != 0)
    && (work == E_OK)) {
        result = finish(in.ctx, jobPrimitiveInputOutput);
    }

    return result;
}

static Std_ReturnType CryptoLib_Void(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    return E_OK;
}

static Std_ReturnType CryptoLib_KeyOperation(Crypto_JobType* job, KEY_OPERATION key_operation) {
    Std_ReturnType result = E_NOT_OK;

    if (HaeModule_Crypto_Get_Key(job->cryptoKeyId) == NULL) {
        result = CRYPTO_E_KEY_NOT_AVAILABLE;
    }
    else if (job->jobId == 0xffffffffU) {
        // Key Interface
        result = key_operation(job->cryptoKeyId, job->targetCryptoKeyId, &job->jobPrimitiveInputOutput);
    }
    /* This function should always be checked in the last position. */
    else if(HaeModule_CryptoKeyId_Lock(job->cryptoKeyId) != TRUE) {
        result = CRYPTO_E_BUSY;
    }
    else {
        if (job->jobPrimitiveInfo->primitiveInfo->service == CRYPTO_KEYDERIVE) {
            if (HaeModule_Crypto_Get_Key(job->cryptoKeyId) == NULL) {
                result = CRYPTO_E_KEY_NOT_AVAILABLE;
            }
            else if(HaeModule_CryptoKeyId_Lock(job->targetCryptoKeyId) != TRUE) {
                result = CRYPTO_E_BUSY;
            }
            else {
                result = key_operation(job->cryptoKeyId, job->targetCryptoKeyId, NULL);

                HaeModule_CryptoKeyId_UnLock(job->targetCryptoKeyId);
            }
        }
        else {
            result = key_operation(job->cryptoKeyId, 0, &job->jobPrimitiveInputOutput);
        }

        HaeModule_CryptoKeyId_UnLock(job->cryptoKeyId);
    }

    return result;
}

static uint32 getHLen(Crypto_AlgorithmFamilyType hashType) {
    uint32 hLen = 0;

    switch (hashType) {
    case CRYPTO_ALGOFAM_SHA1:
        hLen = 20;
        break;
    case CRYPTO_ALGOFAM_SHA2_224:
        hLen = 28;
        break;
    case CRYPTO_ALGOFAM_SHA2_256:
        hLen = 32;
        break;
    case CRYPTO_ALGOFAM_SHA2_384:
        hLen = 48;
        break;
    case CRYPTO_ALGOFAM_SHA2_512:
        hLen = 64;
        break;
    case CRYPTO_ALGOFAM_SHA2_512_224:
        hLen = 28;
        break;
    case CRYPTO_ALGOFAM_SHA2_512_256:
        hLen = 32;
        break;
    default:
        /* Nothing to do */
        break;
    }

    return hLen;
}

static Std_ReturnType getStartIndexBigInteger(uint32 *index, const uint8 *in, uint32 inLen, uint32 keyLen) {
    Std_ReturnType result = E_NOT_OK;

    if (inLen == keyLen) {
        *index = 0;
        result = E_OK;
    }
    if ((inLen == (keyLen + 1)) && (in[0] == 0u)) {
        *index = 1;
        result = E_OK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType setEccBigInteger(uint8 *out, const uint8 *in, uint32 inLen, uint32 keyLen) {
    Std_ReturnType result = E_NOT_OK;

    if (inLen <= keyLen) {
        uint32 outLen = (keyLen == 66) ? 68 : keyLen;

        HMG_MEMSET(out, 0, outLen - inLen);
        HMG_MEMCPY(&out[outLen - inLen], in, inLen);

        result = E_OK;
    }

    return result;
}


static uint8 HmgHash_start(HaeCryptoLibPrimitiveData *ctx) {
    uint8 result = HMG_FAILURE;

    switch (ctx->secondaryFamily) {
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA160_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA1:
        result = Hmg_Sha160Start(&ctx->unionCtx.hash_sha160);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA224_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_224:
        result = Hmg_Sha224Start(&ctx->unionCtx.hash_sha224);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA256_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_256:
        result = Hmg_Sha256Start(&ctx->unionCtx.hash_sha256);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA384_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_384:
        result = Hmg_Sha384Start(&ctx->unionCtx.hash_sha384);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA512_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_512:
        result = Hmg_Sha512Start(&ctx->unionCtx.hash_sha512);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA512_224_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_512_224:
        result = Hmg_Sha512_224Start(&ctx->unionCtx.hash_sha512_224);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA512_256_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_512_256:
        result = Hmg_Sha512_256Start(&ctx->unionCtx.hash_sha512_256);
        break;
#endif
    default:
        result = HMG_FAILURE;
        break;
    }

    return result;
}

static uint8 HmgHash_update(HaeCryptoLibPrimitiveData *ctx, const uint8 *in, uint32 inLen) {
    uint8 result = HMG_FAILURE;

    switch (ctx->secondaryFamily) {
    case CRYPTO_ALGOFAM_SHA1:
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA160_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_VERIFY_SUPPORT)
        result = Hmg_Sha160Update(&ctx->unionCtx.hash_sha160, in, inLen);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA224_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_224:
        result = Hmg_Sha224Update(&ctx->unionCtx.hash_sha224, in, inLen);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA256_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_256:
        result = Hmg_Sha256Update(&ctx->unionCtx.hash_sha256, in, inLen);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA384_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_384:
        result = Hmg_Sha384Update(&ctx->unionCtx.hash_sha384, in, inLen);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA512_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_512:
        result = Hmg_Sha512Update(&ctx->unionCtx.hash_sha512, in, inLen);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA512_224_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_512_224:
        result = Hmg_Sha512_224Update(&ctx->unionCtx.hash_sha512_224, in, inLen);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA512_256_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_512_256:
        result = Hmg_Sha512_256Update(&ctx->unionCtx.hash_sha512_256, in, inLen);
        break;
#endif
    default:
        result = HMG_FAILURE;
        break;
    }

    return result;
}

static uint8 HmgHash_finish(HaeCryptoLibPrimitiveData *ctx, uint8 *out) {
    uint8 result = HMG_FAILURE;

    switch (ctx->secondaryFamily) {
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA160_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA1:
        result = Hmg_Sha160Finish(&ctx->unionCtx.hash_sha160, out);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA224_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_224:
        result = Hmg_Sha224Finish(&ctx->unionCtx.hash_sha224, out);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA256_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_256:
        result = Hmg_Sha256Finish(&ctx->unionCtx.hash_sha256, out);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA384_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_384:
        result = Hmg_Sha384Finish(&ctx->unionCtx.hash_sha384, out);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA512_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_VERIFY_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_512:
        result = Hmg_Sha512Finish(&ctx->unionCtx.hash_sha512, out);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA512_224_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_512_224:
        result = Hmg_Sha512_224Finish(&ctx->unionCtx.hash_sha512_224, out);
        break;
#endif
#if defined (HAECRYPTOLIB_PRIMITIVE_SHA512_256_SUPPORT)
    case CRYPTO_ALGOFAM_SHA2_512_256:
        result = Hmg_Sha512_256Finish(&ctx->unionCtx.hash_sha512_256, out);
        break;
#endif
    default:
        result = HMG_FAILURE;
        break;
    }

    return result;
}

#if defined (HAECRYPTOLIB_PRIMITIVE_SHA160_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_SHA224_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_SHA256_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_SHA384_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_SHA512_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_SHA512_224_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_SHA512_256_SUPPORT)
static Std_ReturnType CryptoLib_Hash_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (HmgHash_start(ctx) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_Hash_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (HmgHash_update(ctx, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_Hash_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 hLen = getHLen(ctx->secondaryFamily);

    if (*jobPrimitiveInputOutput->outputLengthPtr < hLen) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (HmgHash_finish(ctx, jobPrimitiveInputOutput->outputPtr) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = hLen;
    }
    else {
        /* Nothing to do */
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA160_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha160( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_Hash_Start, CryptoLib_Hash_Update, CryptoLib_Hash_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA224_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha224( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_Hash_Start, CryptoLib_Hash_Update, CryptoLib_Hash_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA256_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_Hash_Start, CryptoLib_Hash_Update, CryptoLib_Hash_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA384_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha384( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_Hash_Start, CryptoLib_Hash_Update, CryptoLib_Hash_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA512_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha512( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_Hash_Start, CryptoLib_Hash_Update, CryptoLib_Hash_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA512_224_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha512_224( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_Hash_Start, CryptoLib_Hash_Update, CryptoLib_Hash_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHA512_256_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Sha512_256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_Hash_Start, CryptoLib_Hash_Update, CryptoLib_Hash_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_SHAKE256_SUPPORT
static Std_ReturnType CryptoLib_SHAKE256_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    Hmg_Shake256Start(&ctx->unionCtx.hash_shake256);
    result = E_OK;

    return result;
}

static Std_ReturnType CryptoLib_SHAKE256_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    Hmg_Shake256Update(&ctx->unionCtx.hash_shake256, jobPrimitiveInputOutput->inputPtr, (int)jobPrimitiveInputOutput->inputLength);
    result = E_OK;

    return result;
}

static Std_ReturnType CryptoLib_SHAKE256_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < 32) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else {
        Hmg_Shake256Finish(&ctx->unionCtx.hash_shake256, jobPrimitiveInputOutput->outputPtr, 32);
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = 32;
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_Shake256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_SHAKE256_Start, CryptoLib_SHAKE256_Update, CryptoLib_SHAKE256_Finish);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA160_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA160_VERIFY_SUPPORT)
static Std_ReturnType CryptoLib_SHA160_HMAC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_HmacSha160Start(&ctx->unionCtx.hmac_sha160, element->key->CryptoKeyElementValue, element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_SHA160_HMAC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_HmacSha160Update(&ctx->unionCtx.hmac_sha160, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA160_GENERATE_SUPPORT
static Std_ReturnType CryptoLib_SHA160_HMAC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < HMG_HMAC_SHA160_DIGEST_SIZE) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_HmacSha160Finish(&ctx->unionCtx.hmac_sha160, jobPrimitiveInputOutput->outputPtr) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = HMG_HMAC_SHA160_DIGEST_SIZE;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_HmacSha160_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_SHA160_HMAC_Start, CryptoLib_SHA160_HMAC_Update, CryptoLib_SHA160_HMAC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA160_VERIFY_SUPPORT
static Std_ReturnType CryptoLib_SHA160_HMAC_Verify(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint8 MAC[HMG_HMAC_SHA160_DIGEST_SIZE] = { 0 };
    uint32 macLength = jobPrimitiveInputOutput->secondaryInputLength / 8;

    if (macLength > CRYPTO_BUFFER_MAX_LENGTH) {
        *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
    }
    else if (Hmg_HmacSha160Finish(&ctx->unionCtx.hmac_sha160, MAC) == HMG_SUCCESS) {
        result = E_OK;
        if (HMG_MEMCMP(jobPrimitiveInputOutput->secondaryInputPtr, MAC, macLength) == 0) {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
        }
        else {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
        }
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_HmacSha160_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_SHA160_HMAC_Start, CryptoLib_SHA160_HMAC_Update, CryptoLib_SHA160_HMAC_Verify);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA224_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA224_VERIFY_SUPPORT)
static Std_ReturnType CryptoLib_SHA224_HMAC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_HmacSha224Start(&ctx->unionCtx.hmac_sha224, element->key->CryptoKeyElementValue, element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_SHA224_HMAC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_HmacSha224Update(&ctx->unionCtx.hmac_sha224, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA224_GENERATE_SUPPORT
static Std_ReturnType CryptoLib_SHA224_HMAC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < HMG_HMAC_SHA224_DIGEST_SIZE) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_HmacSha224Finish(&ctx->unionCtx.hmac_sha224, jobPrimitiveInputOutput->outputPtr) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = HMG_HMAC_SHA224_DIGEST_SIZE;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_HmacSha224_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_SHA224_HMAC_Start, CryptoLib_SHA224_HMAC_Update, CryptoLib_SHA224_HMAC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA224_VERIFY_SUPPORT
static Std_ReturnType CryptoLib_SHA224_HMAC_Verify(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint8 MAC[CRYPTO_BUFFER_MAX_LENGTH] = { 0 };
    uint32 macLength = jobPrimitiveInputOutput->secondaryInputLength / 8;

    if (macLength > CRYPTO_BUFFER_MAX_LENGTH) {
        *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
    }
    else if (Hmg_HmacSha224Finish(&ctx->unionCtx.hmac_sha224, MAC) == HMG_SUCCESS) {
        result = E_OK;
        if (HMG_MEMCMP(jobPrimitiveInputOutput->secondaryInputPtr, MAC, macLength) == 0) {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
        }
        else {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
        }
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_HmacSha224_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_SHA224_HMAC_Start, CryptoLib_SHA224_HMAC_Update, CryptoLib_SHA224_HMAC_Verify);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA256_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA256_VERIFY_SUPPORT)
static Std_ReturnType CryptoLib_SHA256_HMAC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_HmacSha256Start(&ctx->unionCtx.hmac_sha256, element->key->CryptoKeyElementValue, element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_SHA256_HMAC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_HmacSha256Update(&ctx->unionCtx.hmac_sha256, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA256_GENERATE_SUPPORT
static Std_ReturnType CryptoLib_SHA256_HMAC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < HMG_HMAC_SHA256_DIGEST_SIZE) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_HmacSha256Finish(&ctx->unionCtx.hmac_sha256, jobPrimitiveInputOutput->outputPtr) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = HMG_HMAC_SHA256_DIGEST_SIZE;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_HmacSha256_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_SHA256_HMAC_Start, CryptoLib_SHA256_HMAC_Update, CryptoLib_SHA256_HMAC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA256_VERIFY_SUPPORT
static Std_ReturnType CryptoLib_SHA256_HMAC_Verify(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint8 MAC[CRYPTO_BUFFER_MAX_LENGTH] = { 0 };
    uint32 macLength = jobPrimitiveInputOutput->secondaryInputLength / 8;

    if (macLength > CRYPTO_BUFFER_MAX_LENGTH) {
        *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
    }
    else if (Hmg_HmacSha256Finish(&ctx->unionCtx.hmac_sha256, MAC) == HMG_SUCCESS) {
        result = E_OK;
        if (HMG_MEMCMP(jobPrimitiveInputOutput->secondaryInputPtr, MAC, macLength) == 0) {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
        }
        else {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
        }
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_HmacSha256_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_SHA256_HMAC_Start, CryptoLib_SHA256_HMAC_Update, CryptoLib_SHA256_HMAC_Verify);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA384_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA384_VERIFY_SUPPORT)
static Std_ReturnType CryptoLib_SHA384_HMAC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_HmacSha384Start(&ctx->unionCtx.hmac_sha384, element->key->CryptoKeyElementValue, element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_SHA384_HMAC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_HmacSha384Update(&ctx->unionCtx.hmac_sha384, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA384_GENERATE_SUPPORT
static Std_ReturnType CryptoLib_SHA384_HMAC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < HMG_HMAC_SHA384_DIGEST_SIZE) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_HmacSha384Finish(&ctx->unionCtx.hmac_sha384, jobPrimitiveInputOutput->outputPtr) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = HMG_HMAC_SHA384_DIGEST_SIZE;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_HmacSha384_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_SHA384_HMAC_Start, CryptoLib_SHA384_HMAC_Update, CryptoLib_SHA384_HMAC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA384_VERIFY_SUPPORT
static Std_ReturnType CryptoLib_SHA384_HMAC_Verify(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint8 MAC[CRYPTO_BUFFER_MAX_LENGTH] = { 0 };
    uint32 macLength = jobPrimitiveInputOutput->secondaryInputLength / 8;

    if (macLength > CRYPTO_BUFFER_MAX_LENGTH) {
        *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
    }
    else if (Hmg_HmacSha384Finish(&ctx->unionCtx.hmac_sha384, MAC) == HMG_SUCCESS) {
        result = E_OK;
        if (HMG_MEMCMP(jobPrimitiveInputOutput->secondaryInputPtr, MAC, macLength) == 0) {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
        }
        else {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
        }
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_HmacSha384_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_SHA384_HMAC_Start, CryptoLib_SHA384_HMAC_Update, CryptoLib_SHA384_HMAC_Verify);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA512_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_HMACSHA512_VERIFY_SUPPORT)
static Std_ReturnType CryptoLib_SHA512_HMAC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_HmacSha512Start(&ctx->unionCtx.hmac_sha512, element->key->CryptoKeyElementValue, element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_SHA512_HMAC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_HmacSha512Update(&ctx->unionCtx.hmac_sha512, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA512_GENERATE_SUPPORT
static Std_ReturnType CryptoLib_SHA512_HMAC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < HMG_HMAC_SHA512_DIGEST_SIZE) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_HmacSha512Finish(&ctx->unionCtx.hmac_sha512, jobPrimitiveInputOutput->outputPtr) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = HMG_HMAC_SHA512_DIGEST_SIZE;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_HmacSha512_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_SHA512_HMAC_Start, CryptoLib_SHA512_HMAC_Update, CryptoLib_SHA512_HMAC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HMACSHA512_VERIFY_SUPPORT
static Std_ReturnType CryptoLib_SHA512_HMAC_Verify(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint8 MAC[CRYPTO_BUFFER_MAX_LENGTH] = { 0 };
    uint32 macLength = jobPrimitiveInputOutput->secondaryInputLength / 8;

    if (macLength > CRYPTO_BUFFER_MAX_LENGTH) {
        *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
    }
    else if (Hmg_HmacSha512Finish(&ctx->unionCtx.hmac_sha512, MAC) == HMG_SUCCESS) {
        result = E_OK;
        if (HMG_MEMCMP(jobPrimitiveInputOutput->secondaryInputPtr, MAC, macLength) == 0) {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
        }
        else {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
        }
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_HmacSha512_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_SHA512_HMAC_Start, CryptoLib_SHA512_HMAC_Update, CryptoLib_SHA512_HMAC_Verify);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESECB_DECRYPT_SUPPORT
static Std_ReturnType CryptoLib_TDES_ECB_DEC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key->CryptoKeyElementValueSize != (HMG_TDES_THREE_KEY * HMG_DES_KEY_BYTE_SIZE)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (Hmg_TdesEcbDecStart(&ctx->unionCtx.tdesEcb, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_TDES_ECB_DEC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_TdesEcbDecUpdate(&ctx->unionCtx.tdesEcb, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_TDES_ECB_DEC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 len = 0;

    if (Hmg_TdesEcbDecFinish(&ctx->unionCtx.tdesEcb, &len) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_TdesEcb_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_TDES_ECB_DEC_Start, CryptoLib_TDES_ECB_DEC_Update, CryptoLib_TDES_ECB_DEC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESECB_ENCRYPT_SUPPORT
static Std_ReturnType CryptoLib_TDES_ECB_ENC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key->CryptoKeyElementValueSize != (HMG_TDES_THREE_KEY * HMG_DES_KEY_BYTE_SIZE)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (Hmg_TdesEcbEncStart(&ctx->unionCtx.tdesEcb, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_TDES_ECB_ENC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_TdesEcbEncUpdate(&ctx->unionCtx.tdesEcb, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_TDES_ECB_ENC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 len = 0;

    if (Hmg_TdesEcbEncFinish(&ctx->unionCtx.tdesEcb, &len) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_TdesEcb_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_TDES_ECB_ENC_Start, CryptoLib_TDES_ECB_ENC_Update, CryptoLib_TDES_ECB_ENC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESCBC_DECRYPT_SUPPORT
static Std_ReturnType CryptoLib_TDES_CBC_DEC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if ((element->key->CryptoKeyElementValueSize != (HMG_TDES_THREE_KEY * HMG_DES_KEY_BYTE_SIZE))
    || (element->key2->CryptoKeyElementValueSize != HMG_DES_BLOCK_BYTE_SIZE)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (Hmg_TdesCbcDecStart(&ctx->unionCtx.tdesCbc, element->key2->CryptoKeyElementValue, (uint8)element->key2->CryptoKeyElementValueSize, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_TDES_CBC_DEC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_TdesCbcDecUpdate(&ctx->unionCtx.tdesCbc, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_TDES_CBC_DEC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 len = 0;

    if (Hmg_TdesCbcDecFinish(&ctx->unionCtx.tdesCbc, &len) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_TdesCbc_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_TDES_CBC_DEC_Start, CryptoLib_TDES_CBC_DEC_Update, CryptoLib_TDES_CBC_DEC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESCBC_ENCRYPT_SUPPORT
static Std_ReturnType CryptoLib_TDES_CBC_ENC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if ((element->key->CryptoKeyElementValueSize != (HMG_TDES_THREE_KEY * HMG_DES_KEY_BYTE_SIZE))
    || (element->key2->CryptoKeyElementValueSize != HMG_DES_BLOCK_BYTE_SIZE)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (Hmg_TdesCbcEncStart(&ctx->unionCtx.tdesCbc, element->key2->CryptoKeyElementValue, (uint8)element->key2->CryptoKeyElementValueSize, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_TDES_CBC_ENC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_TdesCbcEncUpdate(&ctx->unionCtx.tdesCbc, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_TDES_CBC_ENC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 len = 0;

    if (Hmg_TdesCbcEncFinish(&ctx->unionCtx.tdesCbc, &len) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_TdesCbc_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_TDES_CBC_ENC_Start, CryptoLib_TDES_CBC_ENC_Update, CryptoLib_TDES_CBC_ENC_Finish);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_TDESCTR_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_TDESCTR_DECRYPT_SUPPORT)
static Std_ReturnType CryptoLib_TDES_CTR_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if ((element->key->CryptoKeyElementValueSize != (HMG_TDES_THREE_KEY * HMG_DES_KEY_BYTE_SIZE))
    || (element->key2->CryptoKeyElementValueSize != HMG_DES_BLOCK_BYTE_SIZE)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (Hmg_TdesCtrStart(&ctx->unionCtx.tdesCtr, element->key2->CryptoKeyElementValue, (uint8)element->key2->CryptoKeyElementValueSize, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_TDES_CTR_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_TdesCtrUpdate(&ctx->unionCtx.tdesCtr, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_TDES_CTR_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 len = 0;

    if (Hmg_TdesCtrFinish(&ctx->unionCtx.tdesCtr, &len) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESCTR_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_TdesCtr_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_TDES_CTR_Start, CryptoLib_TDES_CTR_Update, CryptoLib_TDES_CTR_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESCTR_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_TdesCtr_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_TDES_CTR_Start, CryptoLib_TDES_CTR_Update, CryptoLib_TDES_CTR_Finish);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_TDESCMAC_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_TDESCMAC_VERIFY_SUPPORT)
static Std_ReturnType CryptoLib_TDES_CMAC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key->CryptoKeyElementValueSize != (HMG_TDES_THREE_KEY * HMG_DES_KEY_BYTE_SIZE)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (Hmg_TdesCmacStart(&ctx->unionCtx.tdesCmac, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_TDES_CMAC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_TdesCmacUpdate(&ctx->unionCtx.tdesCmac, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESCMAC_GENERATE_SUPPORT
static Std_ReturnType CryptoLib_TDES_CMAC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 len = 0;

    if (*jobPrimitiveInputOutput->outputLengthPtr < HMG_DES_BLOCK_BYTE_SIZE) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_TdesCmacFinish(&ctx->unionCtx.tdesCmac, jobPrimitiveInputOutput->outputPtr, &len) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = HMG_DES_BLOCK_BYTE_SIZE;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_TdesCmac_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_TDES_CMAC_Start, CryptoLib_TDES_CMAC_Update, CryptoLib_TDES_CMAC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_TDESCMAC_VERIFY_SUPPORT
static Std_ReturnType CryptoLib_TDES_CMAC_Verify(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint8 MAC[CRYPTO_BUFFER_MAX_LENGTH] = { 0 };
    uint32 macLength = jobPrimitiveInputOutput->secondaryInputLength / 8;
    uint32 len = 0;

    if (macLength > CRYPTO_BUFFER_MAX_LENGTH) {
        *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
    }
    else if (Hmg_TdesCmacFinish(&ctx->unionCtx.tdesCmac, MAC, &len) == HMG_SUCCESS) {
        result = E_OK;
        if (HMG_MEMCMP(jobPrimitiveInputOutput->secondaryInputPtr, MAC, macLength) == 0) {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
        }
        else {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
        }
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_TdesCmac_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_TDES_CMAC_Start, CryptoLib_TDES_CMAC_Update, CryptoLib_TDES_CMAC_Verify);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESECB_DECRYPT_SUPPORT
static Std_ReturnType CryptoLib_AES_ECB_DEC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_AesEcbDecStart(&ctx->unionCtx.aesEcb, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_ECB_DEC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_AesEcbDecUpdate(&ctx->unionCtx.aesEcb, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_ECB_DEC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 len = 0;

    if (Hmg_AesEcbDecFinish(&ctx->unionCtx.aesEcb, &len) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_AesEcb_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_ECB_DEC_Start, CryptoLib_AES_ECB_DEC_Update, CryptoLib_AES_ECB_DEC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESECB_ENCRYPT_SUPPORT
static Std_ReturnType CryptoLib_AES_ECB_ENC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_AesEcbEncStart(&ctx->unionCtx.aesEcb, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_ECB_ENC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_AesEcbEncUpdate(&ctx->unionCtx.aesEcb, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_ECB_ENC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 len = 0;

    if (Hmg_AesEcbEncFinish(&ctx->unionCtx.aesEcb, &len) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_AesEcb_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_ECB_ENC_Start, CryptoLib_AES_ECB_ENC_Update, CryptoLib_AES_ECB_ENC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESCBC_DECRYPT_SUPPORT
static Std_ReturnType CryptoLib_AES_CBC_DEC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key2->CryptoKeyElementValueSize != HMG_AES_N_BLOCK) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (Hmg_AesCbcDecStart(&ctx->unionCtx.aesCbc, element->key2->CryptoKeyElementValue, (uint8)element->key2->CryptoKeyElementValueSize, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_CBC_DEC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_AesCbcDecUpdate(&ctx->unionCtx.aesCbc, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_CBC_DEC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 len = 0;

    if (Hmg_AesCbcDecFinish(&ctx->unionCtx.aesCbc, &len) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_AesCbc_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_CBC_DEC_Start, CryptoLib_AES_CBC_DEC_Update, CryptoLib_AES_CBC_DEC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESCBC_ENCRYPT_SUPPORT
static Std_ReturnType CryptoLib_AES_CBC_ENC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key2->CryptoKeyElementValueSize != HMG_AES_N_BLOCK) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (Hmg_AesCbcEncStart(&ctx->unionCtx.aesCbc, element->key2->CryptoKeyElementValue, (uint8)element->key2->CryptoKeyElementValueSize, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_CBC_ENC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_AesCbcEncUpdate(&ctx->unionCtx.aesCbc, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_CBC_ENC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 len = 0;

    if (Hmg_AesCbcEncFinish(&ctx->unionCtx.aesCbc, &len) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_AesCbc_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_CBC_ENC_Start, CryptoLib_AES_CBC_ENC_Update, CryptoLib_AES_CBC_ENC_Finish);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_AESOFB_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESOFB_DECRYPT_SUPPORT)
static Std_ReturnType CryptoLib_AES_OFB_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key2->CryptoKeyElementValueSize != HMG_AES_N_BLOCK) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (Hmg_AesOfbStart(&ctx->unionCtx.aesOfb, element->key2->CryptoKeyElementValue, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_OFB_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_AesOfbUpdate(&ctx->unionCtx.aesOfb, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_OFB_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 len = 0;

    if (Hmg_AesOfbFinish(&ctx->unionCtx.aesOfb, &len) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESOFB_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesOfb_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_OFB_Start, CryptoLib_AES_OFB_Update, CryptoLib_AES_OFB_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESOFB_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesOfb_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_OFB_Start, CryptoLib_AES_OFB_Update, CryptoLib_AES_OFB_Finish);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_AESCTR_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESCTR_DECRYPT_SUPPORT)
static Std_ReturnType CryptoLib_AES_CTR_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key2->CryptoKeyElementValueSize != HMG_AES_N_BLOCK) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (Hmg_AesCtrStart(&ctx->unionCtx.aesCtr, element->key2->CryptoKeyElementValue, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_CTR_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_AesCtrUpdate(&ctx->unionCtx.aesCtr, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_CTR_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 len = 0;

    if (Hmg_AesCtrFinish(&ctx->unionCtx.aesCtr, &len) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESCTR_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesCtr_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_CTR_Start, CryptoLib_AES_CTR_Update, CryptoLib_AES_CTR_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESCTR_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesCtr_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_CTR_Start, CryptoLib_AES_CTR_Update, CryptoLib_AES_CTR_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESGCM_DECRYPT_SUPPORT
static Std_ReturnType CryptoLib_AES_GCM_DEC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_AesGcmDecStart(&ctx->unionCtx.aesGcm, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize, element->key2->CryptoKeyElementValue, element->key2->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_GCM_DEC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (g_cryptoLib_gcmLastUpdateCall != 0) {
        ctx->unionCtx.aesGcm.isFinalCall = 1;
    }
    else {
        ctx->unionCtx.aesGcm.isFinalCall = 0;
    }

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_AesGcmDecUpdate(&ctx->unionCtx.aesGcm, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength, jobPrimitiveInputOutput->secondaryInputPtr, jobPrimitiveInputOutput->secondaryInputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_GCM_DEC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_AesGcmDecFinish(&ctx->unionCtx.aesGcm, jobPrimitiveInputOutput->tertiaryInputPtr, jobPrimitiveInputOutput->tertiaryInputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
    }
    else {
        *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_AesGcm_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_GCM_DEC_Start, CryptoLib_AES_GCM_DEC_Update, CryptoLib_AES_GCM_DEC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESGCM_ENCRYPT_SUPPORT
static Std_ReturnType CryptoLib_AES_GCM_ENC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_AesGcmEncStart(&ctx->unionCtx.aesGcm, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize, element->key2->CryptoKeyElementValue, element->key2->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_GCM_ENC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (g_cryptoLib_gcmLastUpdateCall != 0) {
        ctx->unionCtx.aesGcm.isFinalCall = 1;
    }
    else {
        ctx->unionCtx.aesGcm.isFinalCall = 0;
    }

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_AesGcmEncUpdate(&ctx->unionCtx.aesGcm, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength, jobPrimitiveInputOutput->secondaryInputPtr, jobPrimitiveInputOutput->secondaryInputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_GCM_ENC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->secondaryOutputLengthPtr < HMG_AES_N_BLOCK) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_AesGcmEncFinish(&ctx->unionCtx.aesGcm, jobPrimitiveInputOutput->secondaryOutputPtr, HMG_AES_N_BLOCK) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->secondaryOutputLengthPtr = HMG_AES_N_BLOCK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_AesGcm_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_GCM_ENC_Start, CryptoLib_AES_GCM_ENC_Update, CryptoLib_AES_GCM_ENC_Finish);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_AESCMAC_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESCMAC_VERIFY_SUPPORT)
static Std_ReturnType CryptoLib_AES_CMAC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_AesCmacStart(&ctx->unionCtx.aesCmac, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_CMAC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_AesCmacUpdate(&ctx->unionCtx.aesCmac, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESCMAC_GENERATE_SUPPORT
static Std_ReturnType CryptoLib_AES_CMAC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < HMG_AES_N_BLOCK) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_AesCmacFinish(&ctx->unionCtx.aesCmac, jobPrimitiveInputOutput->outputPtr) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = HMG_AES_N_BLOCK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_AesCmac_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_CMAC_Start, CryptoLib_AES_CMAC_Update, CryptoLib_AES_CMAC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESCMAC_VERIFY_SUPPORT
static Std_ReturnType CryptoLib_AES_CMAC_Verify(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint8 MAC[CRYPTO_BUFFER_MAX_LENGTH] = { 0 };
    uint32 macLength = jobPrimitiveInputOutput->secondaryInputLength / 8;

    if (macLength > CRYPTO_BUFFER_MAX_LENGTH) {
        *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
    }
    else if (Hmg_AesCmacFinish(&ctx->unionCtx.aesCmac, MAC) == HMG_SUCCESS) {
        result = E_OK;
        if (HMG_MEMCMP(jobPrimitiveInputOutput->secondaryInputPtr, MAC, macLength) == 0) {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
        }
        else {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
        }
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_AesCmac_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_CMAC_Start, CryptoLib_AES_CMAC_Update, CryptoLib_AES_CMAC_Verify);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_AESGMAC_GENERATE_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_AESGMAC_VERIFY_SUPPORT)
static Std_ReturnType CryptoLib_AES_GMAC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_AesGmacStart(&ctx->unionCtx.aesGmac, element->key->CryptoKeyElementValue, (uint8)element->key->CryptoKeyElementValueSize, element->key2->CryptoKeyElementValue, element->key2->CryptoKeyElementValueSize) == HMG_SUCCESS) {
        result = E_OK;
    }
    else {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }

    return result;
}

static Std_ReturnType CryptoLib_AES_GMAC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (g_cryptoLib_gmacLastUpdateCall != 0) {
        ctx->unionCtx.aesGmac.isFinalCall = 1;
    }
    else {
        ctx->unionCtx.aesGmac.isFinalCall = 0;
    }
    if (Hmg_AesGmacUpdate(&ctx->unionCtx.aesGmac, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength, NULL, 0) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESGMAC_GENERATE_SUPPORT
static Std_ReturnType CryptoLib_AES_GMAC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < HMG_AES_N_BLOCK) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_AesGmacFinish(&ctx->unionCtx.aesGmac, jobPrimitiveInputOutput->outputPtr, HMG_AES_N_BLOCK) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = HMG_AES_N_BLOCK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_AesGmac_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_GMAC_Start, CryptoLib_AES_GMAC_Update, CryptoLib_AES_GMAC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESGMAC_VERIFY_SUPPORT
static Std_ReturnType CryptoLib_AES_GMAC_Verify(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint8 MAC[CRYPTO_BUFFER_MAX_LENGTH] = { 0 };
    uint32 macLength = jobPrimitiveInputOutput->secondaryInputLength / 8;

    if (Hmg_AesGmacFinish(&ctx->unionCtx.aesGmac, MAC, macLength) == HMG_SUCCESS) {
        result = E_OK;
        if (HMG_MEMCMP(jobPrimitiveInputOutput->secondaryInputPtr, MAC, macLength) == 0) {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
        }
        else {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
        }
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_AesGmac_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_AES_GMAC_Start, CryptoLib_AES_GMAC_Update, CryptoLib_AES_GMAC_Verify);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_CHACHA20_ENCRYPT_SUPPORT) || defined (HAECRYPTOLIB_PRIMITIVE_CHACHA20_DECRYPT_SUPPORT)
static Std_ReturnType CryptoLib_CHACHA20_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if ((element->key->CryptoKeyElementValueSize != 32)
    || (element->key2->CryptoKeyElementValueSize != 16)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else {
        uint32 initialCounter = 0;
        uint8 nonce[12] = { 0 };

        HMG_MEMCPY((uint8*)&initialCounter, element->key2->CryptoKeyElementValue, 4);
        HMG_MEMCPY(nonce, &element->key2->CryptoKeyElementValue[4], 12);
        if (Hmg_Chacha20Start(&ctx->unionCtx.chacha20, element->key->CryptoKeyElementValue, initialCounter, nonce) == HMG_SUCCESS) {
            result = E_OK;
        }
    }

    return result;
}

static Std_ReturnType CryptoLib_CHACHA20_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_Chacha20Update(&ctx->unionCtx.chacha20, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_CHACHA20_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (Hmg_Chacha20Finish(&ctx->unionCtx.chacha20) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_CHACHA20_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Chacha20_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_CHACHA20_Start, CryptoLib_CHACHA20_Update, CryptoLib_CHACHA20_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_CHACHA20_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_Chacha20_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_CHACHA20_Start, CryptoLib_CHACHA20_Update, CryptoLib_CHACHA20_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_CHACHA20POLY1305_DECRYPT_SUPPORT
static Std_ReturnType CryptoLib_CHACHA20_POLY1305_DEC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if ((element->key->CryptoKeyElementValueSize != 32)
    || (element->key2->CryptoKeyElementValueSize != 12)) {
        ctx->chachaPoly.key = NULL;
        ctx->chachaPoly.nonce = NULL;
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else {
        ctx->chachaPoly.key = element->key->CryptoKeyElementValue;
        ctx->chachaPoly.nonce = element->key2->CryptoKeyElementValue;
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_CHACHA20_POLY1305_DEC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    Std_ReturnType work = E_OK;

    if (ctx->chachaPoly.key != NULL) {
        if (Hmg_Chacha20Poly1305DecryptStart(&ctx->unionCtx.chachaPoly, ctx->chachaPoly.key, ctx->chachaPoly.nonce, jobPrimitiveInputOutput->secondaryInputPtr, jobPrimitiveInputOutput->secondaryInputLength) == HMG_SUCCESS) {
            ctx->chachaPoly.key = NULL;
            ctx->chachaPoly.nonce = NULL;
        }
        else {
            work = E_NOT_OK;
        }
    }

    if (work == E_OK) {
        if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else if (Hmg_Chacha20Poly1305DecryptUpdate(&ctx->unionCtx.chachaPoly, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
            result = E_OK;
            *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
        }
        else {
            /* Nothing to do */
        }
    }

    return result;
}

static Std_ReturnType CryptoLib_CHACHA20_POLY1305_DEC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (jobPrimitiveInputOutput->tertiaryInputLength == 16) {
        if (Hmg_Chacha20Poly1305DecryptFinish(&ctx->unionCtx.chachaPoly, jobPrimitiveInputOutput->tertiaryInputPtr) == HMG_SUCCESS) {
            result = E_OK;
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
        }
        else {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
        }
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_Chacha20Poly1305_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_CHACHA20_POLY1305_DEC_Start, CryptoLib_CHACHA20_POLY1305_DEC_Update, CryptoLib_CHACHA20_POLY1305_DEC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_CHACHA20POLY1305_ENCRYPT_SUPPORT
static Std_ReturnType CryptoLib_CHACHA20_POLY1305_ENC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if ((element->key->CryptoKeyElementValueSize != 32)
    || (element->key2->CryptoKeyElementValueSize != 12)) {
        ctx->chachaPoly.key = NULL;
        ctx->chachaPoly.nonce = NULL;
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else {
        ctx->chachaPoly.key = element->key->CryptoKeyElementValue;
        ctx->chachaPoly.nonce = element->key2->CryptoKeyElementValue;
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_CHACHA20_POLY1305_ENC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    Std_ReturnType work = E_OK;

    if (ctx->chachaPoly.key != NULL) {
        if (Hmg_Chacha20Poly1305EncryptStart(&ctx->unionCtx.chachaPoly, ctx->chachaPoly.key, ctx->chachaPoly.nonce, jobPrimitiveInputOutput->secondaryInputPtr, jobPrimitiveInputOutput->secondaryInputLength) == HMG_SUCCESS) {
            ctx->chachaPoly.key = NULL;
            ctx->chachaPoly.nonce = NULL;
        }
        else {
            work = E_NOT_OK;
        }
    }

    if (work == E_OK) {
        if (*jobPrimitiveInputOutput->outputLengthPtr < jobPrimitiveInputOutput->inputLength) {
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else if (Hmg_Chacha20Poly1305EncryptUpdate(&ctx->unionCtx.chachaPoly, jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
            result = E_OK;
            *jobPrimitiveInputOutput->outputLengthPtr = jobPrimitiveInputOutput->inputLength;
        }
        else {
            /* Nothing to do */
        }
    }

    return result;
}

static Std_ReturnType CryptoLib_CHACHA20_POLY1305_ENC_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->secondaryOutputLengthPtr < 16) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_Chacha20Poly1305EncryptFinish(&ctx->unionCtx.chachaPoly, jobPrimitiveInputOutput->secondaryOutputPtr) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->secondaryOutputLengthPtr = 16;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_Chacha20Poly1305_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_CHACHA20_POLY1305_ENC_Start, CryptoLib_CHACHA20_POLY1305_ENC_Update, CryptoLib_CHACHA20_POLY1305_ENC_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESXTS_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesXts_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return E_NOT_OK;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_AESXTS_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_AesXts_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return E_NOT_OK;
}
#endif

typedef union {
    const uint8 *inputPtr;
    HAEMODULE_RSAES_OAEP_INPUT_t *param;
} rsaesOaep_in;

#if defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA160_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA224_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA256_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA384_DECRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA512_DECRYPT_SUPPORT)
static Std_ReturnType CryptoLib_RSAES_OAEP_DEC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key->CryptoKeyElementValueSize != (2 * HMG_RSA_BYTES_SIZE)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else {
        ctx->rsa.mod = element->key->CryptoKeyElementValue;
        ctx->rsa.exp = &element->key->CryptoKeyElementValue[HMG_RSA_BYTES_SIZE];

        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_RSAES_OAEP_DEC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    rsaesOaep_in inCtx;

    inCtx.inputPtr = jobPrimitiveInputOutput->inputPtr;

    if (inCtx.param->textLength == HMG_RSA_BYTES_SIZE) {
        HmgRsaPrivatekey priKey = { NULL };
        HmgPkcs1OaepCtx oaepCtx = { NULL };

        priKey.modulus = ctx->rsa.mod;
        priKey.exponent = ctx->rsa.exp;

        oaepCtx.pLabel = inCtx.param->labelPtr;
        oaepCtx.labelLen = inCtx.param->labelLength;
        oaepCtx.hashAlgorithm = ctx->secondaryFamily;

        if (Hmg_RsaPkcs1OaepDecrypt(jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->outputLengthPtr, inCtx.param->textPtr, &oaepCtx, &priKey) == HMG_SUCCESS) {
            result = E_OK;
        }
    }

    return result;
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA160_ENCRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA224_ENCRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA256_ENCRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA384_ENCRYPT_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA512_ENCRYPT_SUPPORT)
static Std_ReturnType CryptoLib_RSAES_OAEP_ENC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;
    uint32 hLen = getHLen(ctx->secondaryFamily);

    if ((element->key->CryptoKeyElementValueSize != (HMG_RSA_BYTES_SIZE + 4))
    || (element->key2->CryptoKeyElementValueSize != hLen)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else {
        ctx->rsa.mod = element->key->CryptoKeyElementValue;
        ctx->rsa.exp = &element->key->CryptoKeyElementValue[HMG_RSA_BYTES_SIZE];
        ctx->rsa.seed_salt = element->key2->CryptoKeyElementValue;

        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_RSAES_OAEP_ENC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    rsaesOaep_in inCtx;

    inCtx.inputPtr = jobPrimitiveInputOutput->inputPtr;

    if (*jobPrimitiveInputOutput->outputLengthPtr < HMG_RSA_BYTES_SIZE) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else {
        HmgRsaPublickey pubKey = { NULL };
        HmgPkcs1OaepCtx oaepCtx = { NULL };

        pubKey.modulus = ctx->rsa.mod;
        pubKey.exponent = (uint32)ctx->rsa.exp[0];
        pubKey.exponent |= ((uint32)ctx->rsa.exp[1] << 8);
        pubKey.exponent |= ((uint32)ctx->rsa.exp[2] << 16);
        pubKey.exponent |= ((uint32)ctx->rsa.exp[3] << 24);

        oaepCtx.pLabel = inCtx.param->labelPtr;
        oaepCtx.labelLen = inCtx.param->labelLength;
        oaepCtx.pSeed = ctx->rsa.seed_salt;
        oaepCtx.hashAlgorithm = ctx->secondaryFamily;

        if (Hmg_RsaPkcs1OaepEncrypt(jobPrimitiveInputOutput->outputPtr, inCtx.param->textPtr, inCtx.param->textLength, &oaepCtx, &pubKey) == HMG_SUCCESS) {
            result = E_OK;
            *jobPrimitiveInputOutput->outputLengthPtr = HMG_RSA_BYTES_SIZE;
        }
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA160_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha160_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSAES_OAEP_DEC_Start, CryptoLib_RSAES_OAEP_DEC_Update, CryptoLib_Void);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA160_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha160_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSAES_OAEP_ENC_Start, CryptoLib_RSAES_OAEP_ENC_Update, CryptoLib_Void);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA224_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha224_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSAES_OAEP_DEC_Start, CryptoLib_RSAES_OAEP_DEC_Update, CryptoLib_Void);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA224_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha224_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSAES_OAEP_ENC_Start, CryptoLib_RSAES_OAEP_ENC_Update, CryptoLib_Void);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA256_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha256_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSAES_OAEP_DEC_Start, CryptoLib_RSAES_OAEP_DEC_Update, CryptoLib_Void);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA256_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha256_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSAES_OAEP_ENC_Start, CryptoLib_RSAES_OAEP_ENC_Update, CryptoLib_Void);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA384_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha384_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSAES_OAEP_DEC_Start, CryptoLib_RSAES_OAEP_DEC_Update, CryptoLib_Void);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA384_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha384_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSAES_OAEP_ENC_Start, CryptoLib_RSAES_OAEP_ENC_Update, CryptoLib_Void);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA512_DECRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha512_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSAES_OAEP_DEC_Start, CryptoLib_RSAES_OAEP_DEC_Update, CryptoLib_Void);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESOAEPSHA512_ENCRYPT_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsaesOaepSha512_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSAES_OAEP_ENC_Start, CryptoLib_RSAES_OAEP_ENC_Update, CryptoLib_Void);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESPKCS15_DECRYPT_SUPPORT
static Std_ReturnType CryptoLib_RSAES_PKCS15_DEC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key->CryptoKeyElementValueSize == (2 * HMG_RSA_BYTES_SIZE)) {
        ctx->rsa.mod = element->key->CryptoKeyElementValue;
        ctx->rsa.exp = &element->key->CryptoKeyElementValue[HMG_RSA_BYTES_SIZE];
        result = E_OK;
    }
    else {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }

    return result;
}

static Std_ReturnType CryptoLib_RSAES_PKCS15_DEC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (jobPrimitiveInputOutput->inputLength == HMG_RSA_BYTES_SIZE) {
        HmgRsaPrivatekey priKey = { NULL };

        priKey.modulus = ctx->rsa.mod;
        priKey.exponent = ctx->rsa.exp;

        if (Hmg_RsaPkcs1v15Decrypt(jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->outputLengthPtr, jobPrimitiveInputOutput->inputPtr, &priKey) == HMG_SUCCESS) {
            result = E_OK;
        }
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_RsaesPkcs15_Decrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSAES_PKCS15_DEC_Start, CryptoLib_RSAES_PKCS15_DEC_Update, CryptoLib_Void);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSAESPKCS15_ENCRYPT_SUPPORT
static Std_ReturnType CryptoLib_RSAES_PKCS15_ENC_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key->CryptoKeyElementValueSize == (HMG_RSA_BYTES_SIZE + 4)) {
        ctx->rsa.mod = element->key->CryptoKeyElementValue;
        ctx->rsa.exp = &element->key->CryptoKeyElementValue[HMG_RSA_BYTES_SIZE];

        result = E_OK;
    }
    else {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }

    return result;
}

static Std_ReturnType CryptoLib_RSAES_PKCS15_ENC_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    HmgRsaPublickey pubKey = { NULL };

    pubKey.modulus = ctx->rsa.mod;
    pubKey.exponent = (uint32)ctx->rsa.exp[0];
    pubKey.exponent |= ((uint32)ctx->rsa.exp[1] << 8);
    pubKey.exponent |= ((uint32)ctx->rsa.exp[2] << 16);
    pubKey.exponent |= ((uint32)ctx->rsa.exp[3] << 24);

    if (Hmg_RsaPkcs1v15Encrypt(jobPrimitiveInputOutput->outputPtr, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength, &pubKey) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = HMG_RSA_BYTES_SIZE;
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_RsaesPkcs15_Encrypt( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSAES_PKCS15_ENC_Start, CryptoLib_RSAES_PKCS15_ENC_Update, CryptoLib_Void);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_GENERATE_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_GENERATE_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_GENERATE_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_GENERATE_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_GENERATE_SUPPORT)
static Std_ReturnType CryptoLib_RSASSA_PKCS15_GENERATE_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key->CryptoKeyElementValueSize != (2 * HMG_RSA_BYTES_SIZE)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (HmgHash_start(ctx) == HMG_SUCCESS) {
        ctx->rsa.mod = element->key->CryptoKeyElementValue;
        ctx->rsa.exp = &element->key->CryptoKeyElementValue[HMG_RSA_BYTES_SIZE];

        result = E_OK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_RSASSA_PKCS15_GENERATE_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (HmgHash_update(ctx, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_RSASSA_PKCS15_GENERATE_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint8 md[CRYPTO_BUFFER_MAX_LENGTH] = { 0 };

    if (HmgHash_finish(ctx, md) == HMG_SUCCESS) {
        HmgRsaPrivatekey priKey = { NULL };

        priKey.modulus = ctx->rsa.mod;
        priKey.exponent = ctx->rsa.exp;

        if (*jobPrimitiveInputOutput->outputLengthPtr < HMG_RSA_BYTES_SIZE) {
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else if (Hmg_RsaPkcs1v15Sign(jobPrimitiveInputOutput->outputPtr, md, ctx->secondaryFamily, &priKey) == HMG_SUCCESS) {
            result = E_OK;
            *jobPrimitiveInputOutput->outputLengthPtr = HMG_RSA_BYTES_SIZE;
        }
        else {
            /* Nothing to do */
        }
    }

    return result;
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_VERIFY_SUPPORT)
static Std_ReturnType CryptoLib_RSASSA_PKCS15_VERIFY_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key->CryptoKeyElementValueSize != (HMG_RSA_BYTES_SIZE + 4)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (HmgHash_start(ctx) == HMG_SUCCESS) {
        ctx->rsa.mod = element->key->CryptoKeyElementValue;
        ctx->rsa.exp = &element->key->CryptoKeyElementValue[HMG_RSA_BYTES_SIZE];

        result = E_OK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_RSASSA_PKCS15_VERIFY_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (HmgHash_update(ctx, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_RSASSA_PKCS15_VERIFY_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 index = 0;

    if (getStartIndexBigInteger(&index, jobPrimitiveInputOutput->secondaryInputPtr, jobPrimitiveInputOutput->secondaryInputLength, HMG_RSA_BYTES_SIZE) == E_OK) {
        uint8 md[CRYPTO_BUFFER_MAX_LENGTH] = { 0 };

        if (HmgHash_finish(ctx, md) == HMG_SUCCESS) {
            HmgRsaPublickey pubKey = { NULL };

            pubKey.modulus = ctx->rsa.mod;
            pubKey.exponent = (uint32)ctx->rsa.exp[0];
            pubKey.exponent |= ((uint32)ctx->rsa.exp[1] << 8);
            pubKey.exponent |= ((uint32)ctx->rsa.exp[2] << 16);
            pubKey.exponent |= ((uint32)ctx->rsa.exp[3] << 24);

            result = E_OK;
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
            if (Hmg_RsaPkcs1v15Verify(&jobPrimitiveInputOutput->secondaryInputPtr[index], md, ctx->secondaryFamily, &pubKey) == HMG_SUCCESS) {
                *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
            }
        }
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha160_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PKCS15_GENERATE_Start, CryptoLib_RSASSA_PKCS15_GENERATE_Update, CryptoLib_RSASSA_PKCS15_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA160_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha160_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PKCS15_VERIFY_Start, CryptoLib_RSASSA_PKCS15_VERIFY_Update, CryptoLib_RSASSA_PKCS15_VERIFY_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha224_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PKCS15_GENERATE_Start, CryptoLib_RSASSA_PKCS15_GENERATE_Update, CryptoLib_RSASSA_PKCS15_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA224_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha224_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PKCS15_VERIFY_Start, CryptoLib_RSASSA_PKCS15_VERIFY_Update, CryptoLib_RSASSA_PKCS15_VERIFY_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha256_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PKCS15_GENERATE_Start, CryptoLib_RSASSA_PKCS15_GENERATE_Update, CryptoLib_RSASSA_PKCS15_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA256_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha256_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PKCS15_VERIFY_Start, CryptoLib_RSASSA_PKCS15_VERIFY_Update, CryptoLib_RSASSA_PKCS15_VERIFY_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha384_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PKCS15_GENERATE_Start, CryptoLib_RSASSA_PKCS15_GENERATE_Update, CryptoLib_RSASSA_PKCS15_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA384_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha384_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PKCS15_VERIFY_Start, CryptoLib_RSASSA_PKCS15_VERIFY_Update, CryptoLib_RSASSA_PKCS15_VERIFY_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha512_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PKCS15_GENERATE_Start, CryptoLib_RSASSA_PKCS15_GENERATE_Update, CryptoLib_RSASSA_PKCS15_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPKCS15SHA512_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPkcs15Sha512_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PKCS15_VERIFY_Start, CryptoLib_RSASSA_PKCS15_VERIFY_Update, CryptoLib_RSASSA_PKCS15_VERIFY_Finish);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA160_GENERATE_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA224_GENERATE_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA256_GENERATE_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA384_GENERATE_SUPPORT)
static Std_ReturnType CryptoLib_RSASSA_PSS_GENERATE_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key->CryptoKeyElementValueSize != (2 * HMG_RSA_BYTES_SIZE)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (HmgHash_start(ctx) == HMG_SUCCESS) {
        ctx->rsa.mod = element->key->CryptoKeyElementValue;
        ctx->rsa.exp = &element->key->CryptoKeyElementValue[HMG_RSA_BYTES_SIZE];
        ctx->rsa.seed_salt = element->key2->CryptoKeyElementValue;
        ctx->rsa.saltLength = element->key2->CryptoKeyElementValueSize;

        result = E_OK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_RSASSA_PSS_GENERATE_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (HmgHash_update(ctx, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_RSASSA_PSS_GENERATE_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint8 md[CRYPTO_BUFFER_MAX_LENGTH] = { 0 };

    if (HmgHash_finish(ctx, md) == HMG_SUCCESS) {
        HmgRsaPrivatekey priKey = { NULL };
        HmgPkcs1PssCtx pssCtx = { NULL };

        priKey.modulus = ctx->rsa.mod;
        priKey.exponent = ctx->rsa.exp;

        pssCtx.pDigest = md;
        pssCtx.pSalt = ctx->rsa.seed_salt;
        pssCtx.sLen = (uint8)ctx->rsa.saltLength;
        pssCtx.hashAlgorithm = ctx->secondaryFamily;

        if (*jobPrimitiveInputOutput->outputLengthPtr < HMG_RSA_BYTES_SIZE) {
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else if (Hmg_RsaPkcs1PssSign(jobPrimitiveInputOutput->outputPtr, &pssCtx, &priKey) == HMG_SUCCESS) {
            result = E_OK;
            *jobPrimitiveInputOutput->outputLengthPtr = HMG_RSA_BYTES_SIZE;
        }
        else {
            /* Nothing to do */
        }
    }

    return result;
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA160_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA256_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA384_VERIFY_SUPPORT)
static Std_ReturnType CryptoLib_RSASSA_PSS_VERIFY_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key->CryptoKeyElementValueSize != (HMG_RSA_BYTES_SIZE + 4)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (HmgHash_start(ctx) == HMG_SUCCESS) {
        ctx->rsa.mod = element->key->CryptoKeyElementValue;
        ctx->rsa.exp = &element->key->CryptoKeyElementValue[HMG_RSA_BYTES_SIZE];
        ctx->rsa.saltLength = element->key2->CryptoKeyElementValue[0];

        result = E_OK;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

static Std_ReturnType CryptoLib_RSASSA_PSS_VERIFY_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (HmgHash_update(ctx, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_RSASSA_PSS_VERIFY_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 index = 0;

    if (getStartIndexBigInteger(&index, jobPrimitiveInputOutput->secondaryInputPtr, jobPrimitiveInputOutput->secondaryInputLength, HMG_RSA_BYTES_SIZE) == E_OK) {
        uint8 md[CRYPTO_BUFFER_MAX_LENGTH] = { 0 };

        if (HmgHash_finish(ctx, md) == HMG_SUCCESS) {
            HmgRsaPublickey pubKey = { NULL };
            HmgPkcs1PssCtx pssCtx = { NULL };

            pubKey.modulus = ctx->rsa.mod;
            pubKey.exponent = (uint32)ctx->rsa.exp[0];
            pubKey.exponent |= ((uint32)ctx->rsa.exp[1] << 8);
            pubKey.exponent |= ((uint32)ctx->rsa.exp[2] << 16);
            pubKey.exponent |= ((uint32)ctx->rsa.exp[3] << 24);

            pssCtx.pDigest = md;
            pssCtx.sLen = (uint8)ctx->rsa.saltLength;
            pssCtx.hashAlgorithm = ctx->secondaryFamily;

            result = E_OK;
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
            if (Hmg_RsaPkcs1PssVerify(&jobPrimitiveInputOutput->secondaryInputPtr[index], &pssCtx, &pubKey) == HMG_SUCCESS) {
                *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
            }
        }
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA160_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha160_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PSS_GENERATE_Start, CryptoLib_RSASSA_PSS_GENERATE_Update, CryptoLib_RSASSA_PSS_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA160_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha160_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PSS_VERIFY_Start, CryptoLib_RSASSA_PSS_VERIFY_Update, CryptoLib_RSASSA_PSS_VERIFY_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA224_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha224_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PSS_GENERATE_Start, CryptoLib_RSASSA_PSS_GENERATE_Update, CryptoLib_RSASSA_PSS_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA224_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha224_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PSS_VERIFY_Start, CryptoLib_RSASSA_PSS_VERIFY_Update, CryptoLib_RSASSA_PSS_VERIFY_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA256_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha256_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PSS_GENERATE_Start, CryptoLib_RSASSA_PSS_GENERATE_Update, CryptoLib_RSASSA_PSS_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA256_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha256_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PSS_VERIFY_Start, CryptoLib_RSASSA_PSS_VERIFY_Update, CryptoLib_RSASSA_PSS_VERIFY_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA384_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha384_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PSS_GENERATE_Start, CryptoLib_RSASSA_PSS_GENERATE_Update, CryptoLib_RSASSA_PSS_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_RSASSAPSSSHA384_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_RsassaPssSha384_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_RSASSA_PSS_VERIFY_Start, CryptoLib_RSASSA_PSS_VERIFY_Update, CryptoLib_RSASSA_PSS_VERIFY_Finish);
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_GENERATE_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_GENERATE_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_GENERATE_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_GENERATE_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_GENERATE_SUPPORT)
static Std_ReturnType CryptoLib_ECDSA_GENERATE_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (HmgHash_start(ctx) == HMG_SUCCESS) {
        ctx->ecc.keyLength = 0;

        switch (element->curveType) {
        case HAEMODULE_CRYPTO_CURVETYPE_P160R1:
            ctx->ecc.keyLength = 20;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_P224R1:
            ctx->ecc.keyLength = 28;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_P256R1:
            ctx->ecc.keyLength = 32;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_P521R1:
            ctx->ecc.keyLength = 66;
            break;
        default:
            /* Nothing to do */
            break;
        }

        if ((element->key->CryptoKeyElementValueSize != ctx->ecc.keyLength)
        || (element->key2->CryptoKeyElementValueSize != ctx->ecc.keyLength)) {
            result = CRYPTO_E_KEY_SIZE_MISMATCH;
        }
        else {
            ctx->ecc.x = element->key->CryptoKeyElementValue;
            ctx->ecc.salt = element->key2->CryptoKeyElementValue;

            result = E_OK;
        }
    }

    return result;
}

static Std_ReturnType CryptoLib_ECDSA_GENERATE_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (HmgHash_update(ctx, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_ECDSA_GENERATE_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint8 md[CRYPTO_BUFFER_MAX_LENGTH] = { 0 };

    if (*jobPrimitiveInputOutput->outputLengthPtr < (2 * ctx->ecc.keyLength)) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else {
        if (HmgHash_finish(ctx, md) == HMG_SUCCESS) {
            uint8 md_ext[HMG_ECC_MAX_BYTES_SIZE] = { 0 };

            if (setEccBigInteger(md_ext, md, getHLen(ctx->secondaryFamily), ctx->ecc.keyLength) == E_OK) {
                HmgEcdsaSign sign;
                uint8 resultHmg = HMG_FAILURE;

                sign.r = jobPrimitiveInputOutput->outputPtr;
                sign.s = &jobPrimitiveInputOutput->outputPtr[ctx->ecc.keyLength];

                switch (ctx->ecc.keyLength) {
                case 20:
                    resultHmg = Hmg_EccEcdsaSign_p160r1(&sign, md_ext, ctx->ecc.salt, ctx->ecc.x);
                    break;
                case 28:
                    resultHmg = Hmg_EccEcdsaSign_p224r1(&sign, md_ext, ctx->ecc.salt, ctx->ecc.x);
                    break;
                case 32:
                    resultHmg = Hmg_EccEcdsaSign_p256r1(&sign, md_ext, ctx->ecc.salt, ctx->ecc.x);
                    break;
                case 66:
                {
                    uint8 priKey[HMG_ECC_MAX_BYTES_SIZE] = { 0 };
                    uint8 randNum[HMG_ECC_MAX_BYTES_SIZE] = { 0 };
                    uint8 r[HMG_ECC_MAX_BYTES_SIZE] = { 0 };
                    uint8 s[HMG_ECC_MAX_BYTES_SIZE] = { 0 };

                    HMG_MEMCPY(&priKey[2], ctx->ecc.x, ctx->ecc.keyLength);
                    HMG_MEMCPY(&randNum[2], ctx->ecc.salt, ctx->ecc.keyLength);
                    sign.r = r;
                    sign.s = s;

                    resultHmg = Hmg_EccEcdsaSign_p521r1(&sign, md_ext, randNum, priKey);
                    if (resultHmg == HMG_SUCCESS) {
                        HMG_MEMCPY(jobPrimitiveInputOutput->outputPtr, &r[2], ctx->ecc.keyLength);
                        HMG_MEMCPY(&jobPrimitiveInputOutput->outputPtr[ctx->ecc.keyLength], &s[2], ctx->ecc.keyLength);
                    }
                }
                    break;
                default:
                    /* Nothing to do */
                    break;
                }

                if (resultHmg == HMG_SUCCESS) {
                    result = E_OK;
                    *jobPrimitiveInputOutput->outputLengthPtr = 2 * ctx->ecc.keyLength;
                }
            }
        }
    }

    return result;
}
#endif

#if defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_VERIFY_SUPPORT) \
    || defined (HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_VERIFY_SUPPORT)
static Std_ReturnType CryptoLib_ECDSA_VERIFY_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (HmgHash_start(ctx) == HMG_SUCCESS) {
        ctx->ecc.keyLength = 0;

        switch (element->curveType) {
        case HAEMODULE_CRYPTO_CURVETYPE_P160R1:
            ctx->ecc.keyLength = 20;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_P224R1:
            ctx->ecc.keyLength = 28;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_P256R1:
            ctx->ecc.keyLength = 32;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_P521R1:
            ctx->ecc.keyLength = 66;
            break;
        default:
            /* Nothing to do */
            break;
        }

        if (element->key->CryptoKeyElementValueSize != (2 * ctx->ecc.keyLength)) {
            result = CRYPTO_E_KEY_SIZE_MISMATCH;
        }
        else {
            ctx->ecc.x = element->key->CryptoKeyElementValue;
            ctx->ecc.y = &element->key->CryptoKeyElementValue[ctx->ecc.keyLength];

            result = E_OK;
        }
    }

    return result;
}

static Std_ReturnType CryptoLib_ECDSA_VERIFY_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (HmgHash_update(ctx, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength) == HMG_SUCCESS) {
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_ECDSA_VERIFY_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint8 md[CRYPTO_BUFFER_MAX_LENGTH] = { 0 };
    uint32 index = 0;

    if ((jobPrimitiveInputOutput->secondaryInputLength & 1u) == 0u) {
        uint32 signLen = jobPrimitiveInputOutput->secondaryInputLength / 2;
        if (getStartIndexBigInteger(&index, jobPrimitiveInputOutput->secondaryInputPtr, signLen, ctx->ecc.keyLength) == E_OK) {
            if (getStartIndexBigInteger(&index, &jobPrimitiveInputOutput->secondaryInputPtr[signLen], signLen, ctx->ecc.keyLength) == E_OK) {
                result = E_OK;
            }
        }
    }

    if (result == E_OK) {
        result = E_NOT_OK;
        if (HmgHash_finish(ctx, md) == HMG_SUCCESS) {
            uint8 md_ext[HMG_ECC_MAX_BYTES_SIZE] = { 0 };

            if (setEccBigInteger(md_ext, md, getHLen(ctx->secondaryFamily), ctx->ecc.keyLength) == E_OK) {
                HmgEcPublickey pubKey;
                HmgEcdsaSign sign;
                ConstToPointer secondaryInputPtr;
                uint8 resultHmg = HMG_FAILURE;

                pubKey.x = ctx->ecc.x;
                pubKey.y = ctx->ecc.y;

                secondaryInputPtr.pConst = jobPrimitiveInputOutput->secondaryInputPtr;
                sign.r = &secondaryInputPtr.p[index];
                sign.s = &secondaryInputPtr.p[ctx->ecc.keyLength + (2 * index)];

                switch (ctx->ecc.keyLength) {
                case 20:
                    resultHmg = Hmg_EccEcdsaVerify_p160r1(&sign, md_ext, &pubKey);
                    break;
                case 28:
                    resultHmg = Hmg_EccEcdsaVerify_p224r1(&sign, md_ext, &pubKey);
                    break;
                case 32:
                    resultHmg = Hmg_EccEcdsaVerify_p256r1(&sign, md_ext, &pubKey);
                    break;
                case 66:
                {
                    uint8 x[HMG_ECC_MAX_BYTES_SIZE] = { 0 };
                    uint8 y[HMG_ECC_MAX_BYTES_SIZE] = { 0 };
                    uint8 r[HMG_ECC_MAX_BYTES_SIZE] = { 0 };
                    uint8 s[HMG_ECC_MAX_BYTES_SIZE] = { 0 };

                    HMG_MEMCPY(&x[2], ctx->ecc.x, ctx->ecc.keyLength);
                    HMG_MEMCPY(&y[2], ctx->ecc.y, ctx->ecc.keyLength);
                    pubKey.x = x;
                    pubKey.y = y;
                    HMG_MEMCPY(&r[2], sign.r, ctx->ecc.keyLength);
                    HMG_MEMCPY(&s[2], sign.s, ctx->ecc.keyLength);
                    sign.r = r;
                    sign.s = s;

                    resultHmg = Hmg_EccEcdsaVerify_p521r1(&sign, md_ext, &pubKey);
                }
                    break;
                default:
                    /* Nothing to do */
                    break;
                }

                result = E_OK;
                *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
                if (resultHmg == HMG_SUCCESS) {
                    *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
                }
            }
        }
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha160_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_ECDSA_GENERATE_Start, CryptoLib_ECDSA_GENERATE_Update, CryptoLib_ECDSA_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA160_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha160_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_ECDSA_VERIFY_Start, CryptoLib_ECDSA_VERIFY_Update, CryptoLib_ECDSA_VERIFY_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha224_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_ECDSA_GENERATE_Start, CryptoLib_ECDSA_GENERATE_Update, CryptoLib_ECDSA_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA224_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha224_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_ECDSA_VERIFY_Start, CryptoLib_ECDSA_VERIFY_Update, CryptoLib_ECDSA_VERIFY_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha256_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_ECDSA_GENERATE_Start, CryptoLib_ECDSA_GENERATE_Update, CryptoLib_ECDSA_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA256_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha256_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_ECDSA_VERIFY_Start, CryptoLib_ECDSA_VERIFY_Update, CryptoLib_ECDSA_VERIFY_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha384_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_ECDSA_GENERATE_Start, CryptoLib_ECDSA_GENERATE_Update, CryptoLib_ECDSA_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA384_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha384_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_ECDSA_VERIFY_Start, CryptoLib_ECDSA_VERIFY_Update, CryptoLib_ECDSA_VERIFY_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha512_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_ECDSA_GENERATE_Start, CryptoLib_ECDSA_GENERATE_Update, CryptoLib_ECDSA_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDSASHA512_VERIFY_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_EcdsaSha512_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_ECDSA_VERIFY_Start, CryptoLib_ECDSA_VERIFY_Update, CryptoLib_ECDSA_VERIFY_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_EDDSAED448_GENERATE_SUPPORT
static Std_ReturnType CryptoLib_EDDSA_ED448_GENERATE_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key->CryptoKeyElementValueSize != HMG_ED448_KEY_BYTES) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else {
        ctx->eddsa.key = element->key->CryptoKeyElementValue;

        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_EDDSA_ED448_GENERATE_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (jobPrimitiveInputOutput->inputLength == sizeof(HAEMODULE_EDDSA_ED448_INTPUT_t)) {
        ctx->eddsa.in.inputPtr = jobPrimitiveInputOutput->inputPtr;
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_EDDSA_ED448_GENERATE_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (*jobPrimitiveInputOutput->outputLengthPtr < HMG_ED448_SIGN_BYTES) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_EccEddsaSign_ed448(jobPrimitiveInputOutput->outputPtr, ctx->eddsa.in.param->message, ctx->eddsa.in.param->messageLength, ctx->eddsa.in.param->context, (uint8)ctx->eddsa.in.param->contextLength, (const uint8*)ctx->eddsa.key) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = HMG_ED448_SIGN_BYTES;
    }
    else {
        /* Nothing to do */
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_EddsaEd448_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_EDDSA_ED448_GENERATE_Start, CryptoLib_EDDSA_ED448_GENERATE_Update, CryptoLib_EDDSA_ED448_GENERATE_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_EDDSAED448_VERIFY_SUPPORT
static Std_ReturnType CryptoLib_EDDSA_ED448_VERIFY_Start(HaeCryptoLibPrimitiveData *ctx, HaeCryptoLibKeyData *element) {
    Std_ReturnType result = E_NOT_OK;

    if (element->key->CryptoKeyElementValueSize != HMG_ED448_KEY_BYTES) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else {
        ctx->eddsa.key = element->key->CryptoKeyElementValue;

        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_EDDSA_ED448_VERIFY_Update(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;

    if (jobPrimitiveInputOutput->inputLength == sizeof(HAEMODULE_EDDSA_ED448_INTPUT_t)) {
        ctx->eddsa.in.inputPtr = jobPrimitiveInputOutput->inputPtr;
        result = E_OK;
    }

    return result;
}

static Std_ReturnType CryptoLib_EDDSA_ED448_VERIFY_Finish(HaeCryptoLibPrimitiveData *ctx, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    uint32 index = 0;
    uint32 keyLen = HMG_ED448_SIGN_BYTES / 2;

    if ((jobPrimitiveInputOutput->secondaryInputLength & 1u) == 0u) {
        uint32 signLen = jobPrimitiveInputOutput->secondaryInputLength / 2;
        if (getStartIndexBigInteger(&index, jobPrimitiveInputOutput->secondaryInputPtr, signLen, keyLen) == E_OK) {
            if (getStartIndexBigInteger(&index, &jobPrimitiveInputOutput->secondaryInputPtr[signLen], signLen, keyLen) == E_OK) {
                result = E_OK;
            }
        }
    }

    if (result == E_OK) {
        uint8 sign[HMG_ED448_SIGN_BYTES] = { 0 };
        HMG_MEMCPY(sign, &jobPrimitiveInputOutput->secondaryInputPtr[index], keyLen);
        HMG_MEMCPY(&sign[keyLen], &jobPrimitiveInputOutput->secondaryInputPtr[keyLen + (2 * index)], keyLen);
        *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_NOT_OK;
        if (Hmg_EccEddsaVerify_ed448(sign, ctx->eddsa.in.param->message, ctx->eddsa.in.param->messageLength, ctx->eddsa.in.param->context, (uint8)ctx->eddsa.in.param->contextLength, (const uint8*)ctx->eddsa.key) == HMG_SUCCESS) {
            *jobPrimitiveInputOutput->verifyPtr = CRYPTO_E_VER_OK;
        }
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_EddsaEd448_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_Operation(PrimitiveData, job, CryptoLib_EDDSA_ED448_VERIFY_Start, CryptoLib_EDDSA_ED448_VERIFY_Update, CryptoLib_EDDSA_ED448_VERIFY_Finish);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_DH_CALCPUBVAL_SUPPORT
static Std_ReturnType CryptoLib_DH_CALCPUBVAL(uint32 cryptoKeyId, uint32 targetCryptoKey, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    CryptoKeyElement *base = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_BASE);
    CryptoKeyElement *priKey = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_PRIVKEY);
    Std_ReturnType result_base = isReadAccess(base);
    Std_ReturnType result_priKey = isReadAccess(priKey);

    if (result_base != E_OK) {
        result = result_base;
    }
    else if (result_priKey != E_OK) {
        result = result_priKey;
    }
    else if ((base->CryptoKeyElementValueSize != (2 * HMG_DH_BYTES_SIZE))
    || (priKey->CryptoKeyElementValueSize != HMG_DH_BYTES_SIZE)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (*jobPrimitiveInputOutput->outputLengthPtr < HMG_DH_BYTES_SIZE) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else {
        uint8 *p = base->CryptoKeyElementValue;
        uint8 *g = &base->CryptoKeyElementValue[HMG_DH_BYTES_SIZE];

        if (Hmg_DiffieHellmanKeypairGen(NULL, jobPrimitiveInputOutput->outputPtr, priKey->CryptoKeyElementValue, g, p) == HMG_SUCCESS) {
            *jobPrimitiveInputOutput->outputLengthPtr = HMG_DH_BYTES_SIZE;
            result = E_OK;
        }
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_Dh_CalcPubVal( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_KeyOperation(job, CryptoLib_DH_CALCPUBVAL);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_DH_CALCSECRET_SUPPORT
static Std_ReturnType CryptoLib_DH_CALCSECRET(uint32 cryptoKeyId, uint32 targetCryptoKey, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    CryptoKeyElement *base = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_BASE);
    CryptoKeyElement *priKey = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_PRIVKEY);
    CryptoKeyElement *secret = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CYRPTO_KE_SHAREDVALUE);
    Std_ReturnType result_base = isReadAccess(base);
    Std_ReturnType result_priKey = isReadAccess(priKey);
    Std_ReturnType result_secret = isWriteAccess(secret);

    if (result_base != E_OK) {
        result = result_base;
    }
    else if (result_priKey != E_OK) {
        result = result_priKey;
    }
    else if (result_secret != E_OK) {
        result = result_secret;
    }
    else if ((base->CryptoKeyElementValueSize != HMG_DH_BYTES_SIZE)
    || (priKey->CryptoKeyElementValueSize != HMG_DH_BYTES_SIZE)
    || (jobPrimitiveInputOutput->inputLength != HMG_DH_BYTES_SIZE)) {
        result = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if (secret->CryptoKeyElementSize < HMG_DH_BYTES_SIZE) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else {
        uint8 *p = base->CryptoKeyElementValue;

        if (Hmg_DiffieHellmanSharedvalueGen(secret->CryptoKeyElementValue, jobPrimitiveInputOutput->inputPtr, priKey->CryptoKeyElementValue, p) == HMG_SUCCESS) {
            result = E_OK;
            secret->CryptoKeyElementValueSize = HMG_DH_BYTES_SIZE;
            secret->CryptoKeyElementValueState = TRUE;
        }
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_Dh_CalcSecret( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_KeyOperation(job, CryptoLib_DH_CALCSECRET);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDH_CALCPUBVAL_SUPPORT
static Std_ReturnType CryptoLib_ECDH_CALCPUBVAL(uint32 cryptoKeyId, uint32 targetCryptoKey, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    CryptoKeyElement *curve = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_CURVETYPE);
    CryptoKeyElement *priKey = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_PRIVKEY);
    Std_ReturnType result_curve = isReadAccess(curve);
    Std_ReturnType result_priKey = isReadAccess(priKey);

    if (result_curve != E_OK) {
        result = result_curve;
    }
    else if (result_priKey != E_OK) {
        result = result_priKey;
    }
    else {
        uint32 keyLength = 0;

        switch (curve->CryptoKeyElementValue[0]) {
        case HAEMODULE_CRYPTO_CURVETYPE_P160R1:
            keyLength = 20;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_P224R1:
            keyLength = 28;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_P256R1:
            keyLength = 32;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_P521R1:
            keyLength = 66;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_CURVE448:
            keyLength = 56;
            break;
        default:
            /* Nothing to do */
            break;
        }

        if (priKey->CryptoKeyElementValueSize != keyLength) {
            result = CRYPTO_E_KEY_SIZE_MISMATCH;
        }
        else if (keyLength == 56) {
            // X448
            if (*jobPrimitiveInputOutput->outputLengthPtr < keyLength) {
                result = CRYPTO_E_SMALL_BUFFER;
            }
            else if (Hmg_EcckeyGenerate_p448(jobPrimitiveInputOutput->outputPtr, priKey->CryptoKeyElementValue) == HMG_SUCCESS) {
                result = E_OK;
                *jobPrimitiveInputOutput->outputLengthPtr = keyLength;
            }
            else {
                /* Nothing to do */
            }
        }
        else if (*jobPrimitiveInputOutput->outputLengthPtr < (2 * keyLength)) {
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else {
            uint8 resultHmg = HMG_FAILURE;
            HmgEcPublickey pubKey;

            pubKey.x = jobPrimitiveInputOutput->outputPtr;
            pubKey.y = &jobPrimitiveInputOutput->outputPtr[keyLength];

            switch (keyLength) {
            case 20:
                resultHmg = Hmg_EcckeyGenerate_p160r1(&pubKey, priKey->CryptoKeyElementValue);
                break;
            case 28:
                resultHmg = Hmg_EcckeyGenerate_p224r1(&pubKey, priKey->CryptoKeyElementValue);
                break;
            case 32:
                resultHmg = Hmg_EcckeyGenerate_p256r1(&pubKey, priKey->CryptoKeyElementValue);
                break;
            case 66:
            {
                uint8 prix[HMG_ECC_MAX_BYTES_SIZE] = { 0 };
                uint8 x[HMG_ECC_MAX_BYTES_SIZE] = { 0 };
                uint8 y[HMG_ECC_MAX_BYTES_SIZE] = { 0 };

                HMG_MEMCPY(&prix[2], priKey->CryptoKeyElementValue, keyLength);
                pubKey.x = x;
                pubKey.y = y;

                resultHmg = Hmg_EcckeyGenerate_p521r1(&pubKey, prix);
                if (resultHmg == HMG_SUCCESS) {
                    HMG_MEMCPY(jobPrimitiveInputOutput->outputPtr, &x[2], keyLength);
                    HMG_MEMCPY(&jobPrimitiveInputOutput->outputPtr[keyLength], &y[2], keyLength);
                }
            }
                break;
            default:
                /* Nothing to do */
                break;
            }

            if (resultHmg == HMG_SUCCESS) {
                result = E_OK;
                *jobPrimitiveInputOutput->outputLengthPtr = 2 * keyLength;
            }
        }
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_Ecdh_CalcPubVal( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_KeyOperation(job, CryptoLib_ECDH_CALCPUBVAL);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_ECDH_CALCSECRET_SUPPORT
static Std_ReturnType CryptoLib_ECDH_CALCSECRET(uint32 cryptoKeyId, uint32 targetCryptoKey, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    CryptoKeyElement *curve = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_CURVETYPE);
    CryptoKeyElement *priKey = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_PRIVKEY);
    CryptoKeyElement *secret = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CYRPTO_KE_SHAREDVALUE);
    Std_ReturnType result_curve = isReadAccess(curve);
    Std_ReturnType result_priKey = isReadAccess(priKey);
    Std_ReturnType result_secret = isWriteAccess(secret);

    if (result_curve != E_OK) {
        result = result_curve;
    }
    else if (result_priKey != E_OK) {
        result = result_priKey;
    }
    else if (result_secret != E_OK) {
        result = result_secret;
    }
    else {
        uint32 curveType = 0;
        uint32 keyLength = 0;

        HMG_MEMCPY((uint8*)&curveType, curve->CryptoKeyElementValue, (uint32)sizeof(uint32));

        switch (curveType) {
        case HAEMODULE_CRYPTO_CURVETYPE_P160R1:
            keyLength = 20;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_P224R1:
            keyLength = 28;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_P256R1:
            keyLength = 32;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_P521R1:
            keyLength = 66;
            break;
        case HAEMODULE_CRYPTO_CURVETYPE_CURVE448:
            keyLength = 56;
            break;
        default:
            /* Nothing to do */
            break;
        }

        if (priKey->CryptoKeyElementValueSize != keyLength) {
            result = CRYPTO_E_KEY_SIZE_MISMATCH;
        }
        else if (secret->CryptoKeyElementSize < keyLength) {
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else if (keyLength == 56) {
            // X448
            if (jobPrimitiveInputOutput->inputLength != keyLength) {
                result = CRYPTO_E_KEY_SIZE_MISMATCH;
            }
            else if (Hmg_EccEcdh_p448(secret->CryptoKeyElementValue, priKey->CryptoKeyElementValue, jobPrimitiveInputOutput->inputPtr) == HMG_SUCCESS) {
                result = E_OK;
                secret->CryptoKeyElementValueSize = keyLength;
                secret->CryptoKeyElementValueState = TRUE;
            }
            else {
                /* Nothing to do */
            }
        }
        else if (jobPrimitiveInputOutput->inputLength != (2 * keyLength)) {
            result = CRYPTO_E_KEY_SIZE_MISMATCH;
        }
        else {
            uint8 resultHmg = HMG_FAILURE;
            HmgEcPublickey pubKey;
            ConstToPointer inputPtr;

            inputPtr.pConst = jobPrimitiveInputOutput->inputPtr;
            pubKey.x = inputPtr.p;
            pubKey.y = &inputPtr.p[keyLength];

            switch (keyLength) {
            case 20:
                resultHmg = Hmg_EccEcdh_p160r1(secret->CryptoKeyElementValue, priKey->CryptoKeyElementValue, &pubKey);
                break;
            case 28:
                resultHmg = Hmg_EccEcdh_p224r1(secret->CryptoKeyElementValue, priKey->CryptoKeyElementValue, &pubKey);
                break;
            case 32:
                resultHmg = Hmg_EccEcdh_p256r1(secret->CryptoKeyElementValue, priKey->CryptoKeyElementValue, &pubKey);
                break;
            case 66:
            {
                uint8 pubx[HMG_ECC_MAX_BYTES_SIZE] = { 0 };
                uint8 puby[HMG_ECC_MAX_BYTES_SIZE] = { 0 };
                uint8 prix[HMG_ECC_MAX_BYTES_SIZE] = { 0 };
                uint8 x[HMG_ECC_MAX_BYTES_SIZE] = { 0 };

                HMG_MEMCPY(&pubx[2], jobPrimitiveInputOutput->inputPtr, keyLength);
                HMG_MEMCPY(&puby[2], &jobPrimitiveInputOutput->inputPtr[keyLength], keyLength);
                pubKey.x = pubx;
                pubKey.y = puby;
                HMG_MEMCPY(&prix[2], priKey->CryptoKeyElementValue, keyLength);

                resultHmg = Hmg_EccEcdh_p521r1(x, prix, &pubKey);
                if (resultHmg == HMG_SUCCESS) {
                    HMG_MEMCPY(secret->CryptoKeyElementValue, &x[2], keyLength);
                }
            }
                break;
            default:
                /* Nothing to do */
                break;
            }

            if (resultHmg == HMG_SUCCESS) {
                result = E_OK;
                secret->CryptoKeyElementValueSize = keyLength;
                secret->CryptoKeyElementValueState = TRUE;
            }
        }
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_Ecdh_CalcSecret( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return CryptoLib_KeyOperation(job, CryptoLib_ECDH_CALCSECRET);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_PBKDF2HMACSHA256_SUPPORT
static Std_ReturnType CryptoLib_PBKDF2_HMAC_SHA256(uint32 cryptoKeyId, uint32 targetCryptoKey, Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput) {
    Std_ReturnType result = E_NOT_OK;
    CryptoKeyElement *password = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_PASSWORD);
    CryptoKeyElement *salt = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_SALT);
    CryptoKeyElement *iterations = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_ITERATIONS);
    CryptoKeyElement *key = HaeModule_Crypto_Get_KeyElement(targetCryptoKey, CRYPTO_KE_KEY);
    Std_ReturnType result_password = isReadAccess(password);
    Std_ReturnType result_salt = isReadAccess(salt);
    Std_ReturnType result_iterations = isReadAccess(iterations);
    Std_ReturnType result_key = isWriteAccess(key);

    if (result_password != E_OK) {
        result = result_password;
    }
    else if (result_salt != E_OK) {
        result = result_salt;
    }
    else if (result_iterations != E_OK) {
        result = result_iterations;
    }
    else if (result_key != E_OK) {
        result = result_key;
    }
    else {
        uint32 iter = 0;

        HMG_MEMCPY((uint8*)&iter, iterations->CryptoKeyElementValue, (uint32)sizeof(uint32));

        if (Hmg_PBKDF2(key->CryptoKeyElementValue, key->CryptoKeyElementSize,
            password->CryptoKeyElementValue, password->CryptoKeyElementValueSize,
            salt->CryptoKeyElementValue, salt->CryptoKeyElementValueSize,
            iter) == HMG_SUCCESS) {
            result = E_OK;
            key->CryptoKeyElementValueSize = key->CryptoKeyElementSize;
            key->CryptoKeyElementValueState = TRUE;
        }
    }

    return result;
}

Std_ReturnType HaeCryptoLib_Primitive_Pbkdf2HmacSha256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
	return CryptoLib_KeyOperation(job, CryptoLib_PBKDF2_HMAC_SHA256);
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HASHDRBGSHA256_GENERATE_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HashDrbgSha256_Generate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_NOT_OK;
    Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput = &job->jobPrimitiveInputOutput;

    if (gHaeCryptoLib_PrimitiveData.hashDrbg_sha256_instance == 0) {
        result = CRYPTO_E_ENTROPY_EXHAUSTION;
    }
    else if (*jobPrimitiveInputOutput->outputLengthPtr < job->jobPrimitiveInfo->primitiveInfo->resultLength) {
        result = CRYPTO_E_SMALL_BUFFER;
    }
    else if (Hmg_Hashdrbg_Sha256_Gen(&gHaeCryptoLib_PrimitiveData.hashDrbg_sha256, jobPrimitiveInputOutput->outputPtr, job->jobPrimitiveInfo->primitiveInfo->resultLength, NULL, 0, NULL, 0) == HMG_SUCCESS) {
        result = E_OK;
        *jobPrimitiveInputOutput->outputLengthPtr = job->jobPrimitiveInfo->primitiveInfo->resultLength;
    }
    else {
        result = CRYPTO_E_ENTROPY_EXHAUSTION;
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_HASHDRBGSHA256_SEED_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_HashDrbgSha256_Seed( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_NOT_OK;
    Crypto_JobPrimitiveInputOutputType *jobPrimitiveInputOutput = &job->jobPrimitiveInputOutput;

    if (gHaeCryptoLib_PrimitiveData.hashDrbg_sha256_instance == 0) {
        const uint8 *entropy = jobPrimitiveInputOutput->inputPtr;
        uint32 entropyLength = (jobPrimitiveInputOutput->inputLength / 3) * 2;
        uint32 nonceLength = jobPrimitiveInputOutput->inputLength - entropyLength;
        const uint8 *nonce = &entropy[entropyLength];
        if (Hmg_Hashdrbg_Sha256_Init(&gHaeCryptoLib_PrimitiveData.hashDrbg_sha256, entropy, entropyLength, nonce, nonceLength, NULL, 0, FALSE) == HMG_SUCCESS) {
            gHaeCryptoLib_PrimitiveData.hashDrbg_sha256_instance = 1;
            result = E_OK;
        }
    }
    else {
        Hmg_Hashdrbg_Sha256_Reseed(&gHaeCryptoLib_PrimitiveData.hashDrbg_sha256, jobPrimitiveInputOutput->inputPtr, jobPrimitiveInputOutput->inputLength, NULL, 0);
        result = E_OK;
    }

    return result;
}
#endif

#ifdef HAECRYPTOLIB_PRIMITIVE_KEYSETVALID_SUPPORT
Std_ReturnType HaeCryptoLib_Primitive_KeySetValid( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_NOT_OK;

    if(CRYPTO_GET_RESOURCE(&ResType_HaeModuleApi) == TRUE) {
        result = HaeModule_Crypto_KeySetValid(job->cryptoKeyId);
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
    }
    else {
        result = CRYPTO_E_BUSY;
    }

    return result;
}
#endif

#endif //HAEMODULE_CRYPTOOBJECT_HAECRYPTOLIB_SUPPORT

#define CRYPTO_76_HAEMODULE_STOP_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"

