/*!
  @file Crypto_76_HaeModule_Cfg.c
  @brief Crypto configuration source file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#if 0 /* mobilgene doesn't support this header file */
#include "StandardTypes.h"
#else
#include "Std_Types.h"
#endif
#include "Csm.h"
#include "Crypto_76_HaeModule_Cfg.h"
#include "Crypto_76_HaeModule_Crypto.h"
#include "Crypto_76_HaeModule_Job.h"
#include "Crypto_76_HaeModule_HsmPrimitive.h"
#include "Crypto_76_HaeModule_CryptoLibPrimitive.h"

CryptoKey gHaeModule_CryptoKeys[HAEMODULE_CRYPTOKEYS_NUM];
const CryptoPrimitiveList gHaeModule_CryptoPrimitiveList[HAEMODULE_CRYPTOOBJECTS_NUM];
CryptoDriverObject gHaeModule_CryptoDriverObjects[HAEMODULE_CRYPTOOBJECTS_NUM];

#define CRYPTO_76_HAEMODULE_START_ROM_CONST
#include "Crypto_76_HaeModule_MemMap.h"
static const uint8 CryptoKeyElement_RandomSeed_L9_InitValue[4] = {0x01, 0x00, 0x00, 0x00};
static const uint8 CryptoKeyElement_Hash_Dummy_Fota_InitValue[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#define CRYPTO_76_HAEMODULE_STOP_ROM_CONST
#include "Crypto_76_HaeModule_MemMap.h"

#define CRYPTO_76_HAEMODULE_START_RAM_VAR_CLEARED
#include "Crypto_76_HaeModule_MemMap.h"
static uint8 CryptoKeyElement_RandomSeed_L9_Value[4];
static uint8 CryptoKeyElement_Hash_Dummy_Fota_Value[32];
static uint8 CryptoKeyElement_RSASSA_PKCS1_v1_5_Asims_Public_Key_Value[260];
static uint8 CryptoKeyElement_Decr_AES_CTR_Key0_cipherkey_Value[16];
static uint8 CryptoKeyElement_Decr_AES_CTR_Key0_iv_Value[16];
static uint8 CryptoKeyElement_Decr_AES_CTR_Key1_cipherkey_Value[16];
static uint8 CryptoKeyElement_Decr_AES_CTR_Key1_iv_Value[16];
static uint8 CryptoKeyElement_MacVer_AES_CMAC_key_Value[16];
#define CRYPTO_76_HAEMODULE_STOP_RAM_VAR_CLEARED
#include "Crypto_76_HaeModule_MemMap.h"

#define CRYPTO_76_HAEMODULE_START_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"
static CryptoKeyElement CryptoKeyElement_RandomSeed_L9 = {4, 4, CryptoKeyElement_RandomSeed_L9_InitValue, CRYPTO_RA_ALLOWED, FALSE, FALSE, CRYPTO_WA_ALLOWED, CRYPTO_KE_FORMAT_BIN_OCTET, FALSE, 0, CryptoKeyElement_RandomSeed_L9_Value, HAEHSM_KEY_TYPE_NONE, 0};
static CryptoKeyElement CryptoKeyElement_Hash_Dummy_Fota = {1, 32, CryptoKeyElement_Hash_Dummy_Fota_InitValue, CRYPTO_RA_ALLOWED, FALSE, FALSE, CRYPTO_WA_ALLOWED, CRYPTO_KE_FORMAT_BIN_OCTET, FALSE, 0, CryptoKeyElement_Hash_Dummy_Fota_Value, HAEHSM_KEY_TYPE_NONE, 0};
static CryptoKeyElement CryptoKeyElement_RSASSA_PKCS1_v1_5_Asims_Public_Key = {1, 260, NULL, CRYPTO_RA_ALLOWED, FALSE, FALSE, CRYPTO_WA_ALLOWED, CRYPTO_KE_FORMAT_BIN_OCTET, FALSE, 0, CryptoKeyElement_RSASSA_PKCS1_v1_5_Asims_Public_Key_Value, HAEHSM_KEY_TYPE_NONE, 0};
static CryptoKeyElement CryptoKeyElement_Decr_AES_CTR_Key0_cipherkey = {1, 16, NULL, CRYPTO_RA_ALLOWED, FALSE, FALSE, CRYPTO_WA_ALLOWED, CRYPTO_KE_FORMAT_BIN_OCTET, FALSE, 0, CryptoKeyElement_Decr_AES_CTR_Key0_cipherkey_Value, HAEHSM_KEY_TYPE_NONE, 0};
static CryptoKeyElement CryptoKeyElement_Decr_AES_CTR_Key0_iv = {5, 16, NULL, CRYPTO_RA_ALLOWED, FALSE, FALSE, CRYPTO_WA_ALLOWED, CRYPTO_KE_FORMAT_BIN_OCTET, FALSE, 0, CryptoKeyElement_Decr_AES_CTR_Key0_iv_Value, HAEHSM_KEY_TYPE_NONE, 0};
static CryptoKeyElement CryptoKeyElement_Decr_AES_CTR_Key1_cipherkey = {1, 16, NULL, CRYPTO_RA_ALLOWED, FALSE, FALSE, CRYPTO_WA_ALLOWED, CRYPTO_KE_FORMAT_BIN_OCTET, FALSE, 0, CryptoKeyElement_Decr_AES_CTR_Key1_cipherkey_Value, HAEHSM_KEY_TYPE_NONE, 0};
static CryptoKeyElement CryptoKeyElement_Decr_AES_CTR_Key1_iv = {5, 16, NULL, CRYPTO_RA_ALLOWED, FALSE, FALSE, CRYPTO_WA_ALLOWED, CRYPTO_KE_FORMAT_BIN_OCTET, FALSE, 0, CryptoKeyElement_Decr_AES_CTR_Key1_iv_Value, HAEHSM_KEY_TYPE_NONE, 0};
static CryptoKeyElement CryptoKeyElement_MacVer_AES_CMAC_key = {1, 16, NULL, CRYPTO_RA_ALLOWED, FALSE, FALSE, CRYPTO_WA_ALLOWED, CRYPTO_KE_FORMAT_BIN_OCTET, FALSE, 0, CryptoKeyElement_MacVer_AES_CMAC_key_Value, HAEHSM_KEY_TYPE_NONE, 0};
#define CRYPTO_76_HAEMODULE_STOP_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"

#define CRYPTO_76_HAEMODULE_START_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"
static CryptoKeyElement* CryptoKeyType_RandomSeed_L9_Elements[] = {&CryptoKeyElement_RandomSeed_L9};
static CryptoKeyElement* CryptoKeyType_Hash_Dummy_Fota_Elements[] = {&CryptoKeyElement_Hash_Dummy_Fota};
static CryptoKeyElement* CryptoKeyType_RSASSA_PKCS1_v1_5_Asims_Public_Key_Elements[] = {&CryptoKeyElement_RSASSA_PKCS1_v1_5_Asims_Public_Key};
static CryptoKeyElement* CryptoKeyType_Decr_AES_CTR_Key0_Type_Elements[] = {&CryptoKeyElement_Decr_AES_CTR_Key0_cipherkey, &CryptoKeyElement_Decr_AES_CTR_Key0_iv};
static CryptoKeyElement* CryptoKeyType_Decr_AES_CTR_Key1_Type_Elements[] = {&CryptoKeyElement_Decr_AES_CTR_Key1_cipherkey, &CryptoKeyElement_Decr_AES_CTR_Key1_iv};
static CryptoKeyElement* CryptoKeyType_MacVer_AES_CMAC_key_Type_Elements[] = {&CryptoKeyElement_MacVer_AES_CMAC_key};
#define CRYPTO_76_HAEMODULE_STOP_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"

#define CRYPTO_76_HAEMODULE_START_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"
static CryptoKeyType CryptoKeyType_RandomSeed_L9 = {CryptoKeyType_RandomSeed_L9_Elements, 1};
static CryptoKeyType CryptoKeyType_Hash_Dummy_Fota = {CryptoKeyType_Hash_Dummy_Fota_Elements, 1};
static CryptoKeyType CryptoKeyType_RSASSA_PKCS1_v1_5_Asims_Public_Key = {CryptoKeyType_RSASSA_PKCS1_v1_5_Asims_Public_Key_Elements, 1};
static CryptoKeyType CryptoKeyType_Decr_AES_CTR_Key0_Type = {CryptoKeyType_Decr_AES_CTR_Key0_Type_Elements, 2};
static CryptoKeyType CryptoKeyType_Decr_AES_CTR_Key1_Type = {CryptoKeyType_Decr_AES_CTR_Key1_Type_Elements, 2};
static CryptoKeyType CryptoKeyType_MacVer_AES_CMAC_key_Type = {CryptoKeyType_MacVer_AES_CMAC_key_Type_Elements, 1};
#define CRYPTO_76_HAEMODULE_STOP_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"

#define CRYPTO_76_HAEMODULE_START_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"
CryptoKey gHaeModule_CryptoKeys[HAEMODULE_CRYPTOKEYS_NUM] = {
	{CRYPTOKEY_RANDOMSEED_L9, &CryptoKeyType_RandomSeed_L9, FALSE},
	{CRYPTOKEY_HASH_DUMMY_FOTA, &CryptoKeyType_Hash_Dummy_Fota, FALSE},
	{CRYPTOKEY_RSASSA_PKCS1_V1_5_ASIMS_PUBLIC_KEY, &CryptoKeyType_RSASSA_PKCS1_v1_5_Asims_Public_Key, FALSE},
	{CRYPTOKEY_DECR_AES_CTR_KEY0, &CryptoKeyType_Decr_AES_CTR_Key0_Type, FALSE},
	{CRYPTOKEY_DECR_AES_CTR_KEY1, &CryptoKeyType_Decr_AES_CTR_Key1_Type, FALSE},
	{CRYPTOKEY_MACVER_AES_CMAC_KEY, &CryptoKeyType_MacVer_AES_CMAC_key_Type, FALSE},
};
#define CRYPTO_76_HAEMODULE_STOP_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"

#define CRYPTO_76_HAEMODULE_START_ROM_CONST
#include "Crypto_76_HaeModule_MemMap.h"
static const CryptoPrimitive HaeCryptoLib_CryptoPrimtives[] = {
	{CRYPTO_MACGENERATE, CRYPTO_ALGOFAM_AES, CRYPTO_ALGOFAM_NOT_SET, CRYPTO_ALGOMODE_CMAC, (Crypto_PrimitiveProcess)HaeCryptoLib_Primitive_AesCmac_Generate},
	{CRYPTO_MACVERIFY, CRYPTO_ALGOFAM_AES, CRYPTO_ALGOFAM_NOT_SET, CRYPTO_ALGOMODE_CMAC, (Crypto_PrimitiveProcess)HaeCryptoLib_Primitive_AesCmac_Verify},
	{CRYPTO_DECRYPT, CRYPTO_ALGOFAM_AES, CRYPTO_ALGOFAM_NOT_SET, CRYPTO_ALGOMODE_CTR, (Crypto_PrimitiveProcess)HaeCryptoLib_Primitive_AesCtr_Decrypt},
	{CRYPTO_ENCRYPT, CRYPTO_ALGOFAM_AES, CRYPTO_ALGOFAM_NOT_SET, CRYPTO_ALGOMODE_CTR, (Crypto_PrimitiveProcess)HaeCryptoLib_Primitive_AesCtr_Encrypt},
	{CRYPTO_KEYDERIVE, CRYPTO_ALGOFAM_PBKDF2, CRYPTO_ALGOFAM_SHA2_256, CRYPTO_ALGOMODE_HMAC, (Crypto_PrimitiveProcess)HaeCryptoLib_Primitive_Pbkdf2HmacSha256},
	{CRYPTO_SIGNATUREGENERATE, CRYPTO_ALGOFAM_RSA, CRYPTO_ALGOFAM_SHA1, CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5, (Crypto_PrimitiveProcess)HaeCryptoLib_Primitive_RsassaPkcs15Sha160_Generate},
	{CRYPTO_SIGNATUREVERIFY, CRYPTO_ALGOFAM_RSA, CRYPTO_ALGOFAM_SHA1, CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5, (Crypto_PrimitiveProcess)HaeCryptoLib_Primitive_RsassaPkcs15Sha160_Verify},
	{CRYPTO_SIGNATUREGENERATE, CRYPTO_ALGOFAM_RSA, CRYPTO_ALGOFAM_SHA2_256, CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5, (Crypto_PrimitiveProcess)HaeCryptoLib_Primitive_RsassaPkcs15Sha256_Generate},
	{CRYPTO_SIGNATUREVERIFY, CRYPTO_ALGOFAM_RSA, CRYPTO_ALGOFAM_SHA2_256, CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5, (Crypto_PrimitiveProcess)HaeCryptoLib_Primitive_RsassaPkcs15Sha256_Verify},
	{CRYPTO_HASH, CRYPTO_ALGOFAM_SHA1, CRYPTO_ALGOFAM_NOT_SET, CRYPTO_ALGOMODE_NOT_SET, (Crypto_PrimitiveProcess)HaeCryptoLib_Primitive_Sha160},
	{CRYPTO_HASH, CRYPTO_ALGOFAM_SHA2_256, CRYPTO_ALGOFAM_NOT_SET, CRYPTO_ALGOMODE_NOT_SET, (Crypto_PrimitiveProcess)HaeCryptoLib_Primitive_Sha256},
	{CRYPTO_RANDOMGENERATE, CRYPTO_ALGOFAM_RNG, CRYPTO_ALGOFAM_NOT_SET, CRYPTO_ALGOMODE_NOT_SET, (Crypto_PrimitiveProcess)HaeCryptoLib_Primitive_HashDrbgSha256_Generate},
	{CRYPTO_RANDOMSEED, CRYPTO_ALGOFAM_DRBG, CRYPTO_ALGOFAM_SHA2_256, CRYPTO_ALGOMODE_NOT_SET, (Crypto_PrimitiveProcess)HaeCryptoLib_Primitive_HashDrbgSha256_Seed},
};
#define CRYPTO_76_HAEMODULE_STOP_ROM_CONST
#include "Crypto_76_HaeModule_MemMap.h"

#define CRYPTO_76_HAEMODULE_START_ROM_CONST
#include "Crypto_76_HaeModule_MemMap.h"
const CryptoPrimitiveList gHaeModule_CryptoPrimitiveList[HAEMODULE_CRYPTOOBJECTS_NUM] = {
    {
        0,
        (Crypto_PrimitiveInit)HaeCryptoLib_Primtive_Init,
        (Crypto_PrimitiveProcess)HaeCryptoLib_Primtive_CancelJob,
        (Crypto_PrimitiveGetState)HaeCryptoLib_Primitive_GetState,
        (Crypto_PrimitiveSetState)HaeCryptoLib_Primitive_SetState,
    },
};
#define CRYPTO_76_HAEMODULE_STOP_ROM_CONST
#include "Crypto_76_HaeModule_MemMap.h"

#define CRYPTO_76_HAEMODULE_START_RAM_VAR_CLEARED
#include "Crypto_76_HaeModule_MemMap.h"
static CryptoObjectQueue HaeCryptoLib_Queue[10];
#define CRYPTO_76_HAEMODULE_STOP_RAM_VAR_CLEARED
#include "Crypto_76_HaeModule_MemMap.h"

#define CRYPTO_76_HAEMODULE_START_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"
CryptoDriverObject gHaeModule_CryptoDriverObjects[HAEMODULE_CRYPTOOBJECTS_NUM] = {
	{0, 10, HaeCryptoLib_CryptoPrimtives, 13, NULL, HaeCryptoLib_Queue, NULL, {(uint32)HAEMODULE_JOBSTATE_IDLE,0,NULL,0,NULL,0,0,0}, NULL, 0},
};
#define CRYPTO_76_HAEMODULE_STOP_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"

#define CRYPTO_76_HAEMODULE_START_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"
/*!
  @brief If asynchronous job processing is configured and there are job queues, the function is called cyclically to process queued jobs.
  @details Service ID[hex]: 0x0C \n
        It is necessary for asynchronous job processing. For synchronous job processing providing the main function is optional.
  @param[in] None
  @return None
*/
void Crypto_76_HaeModule_HaeCryptoLib_MainFunction( void )
{
    HaeModule_Crypto_MainFunction(0);
}
#define CRYPTO_76_HAEMODULE_STOP_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"

