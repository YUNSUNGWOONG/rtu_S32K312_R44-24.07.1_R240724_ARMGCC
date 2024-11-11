/*!
  @file Crypto_76_HaeModule.c
  @brief Crypto interface API source file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#include "Crypto_76_HaeModule.h"
#include "Crypto_76_HaeModule_Crypto.h"
#include "Crypto_76_HaeModule_Common.h"
#include "Crypto_76_HaeModule_General.h"
#include "Crypto_76_HaeModule_Job.h"
#include "Crypto_76_HaeModule_Key.h"


#define CRYPTO_76_HAEMODULE_START_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"
/*
 * [SWS_Crypto_00012] In case several Crypto Driver instances (of same or different vendor) are implemented in one ECU
 * the file names, API names, and published parameters must be distinguished such that no two definitions with the same name are generated.
 */
/* mobilgene calls this function to initialize driver */
void Crypto_76_HaeModule_Init( const Crypto_76_HaeModule_ConfigType* configPtr )
{
    HaeModule_Crypto_Init(configPtr);
}

#if (CRYPTO_76_HAEMODULE_CRYPTOVERSIONINFOAPI_VALUE == TRUE)
void Crypto_76_HaeModule_GetVersionInfo(Std_VersionInfoType * versioninfo)
{
    HaeModule_Crypto_GetVersionInfo(versioninfo);
}
#endif

Std_ReturnType Crypto_76_HaeModule_ProcessJob( uint32 objectId, Crypto_JobType* job )
{
    return HaeModule_Crypto_ProcessJob(objectId, job);
}

Std_ReturnType Crypto_76_HaeModule_CancelJob( uint32 objectId, Crypto_JobType* job )
{
    return HaeModule_Crypto_CancelJob(objectId, job);
}

Std_ReturnType Crypto_76_HaeModule_KeyElementSet( uint32 cryptoKeyId, uint32 keyElementId, const uint8* keyPtr, uint32 keyLength )
{
    return HaeModule_Crypto_KeyElementSet(cryptoKeyId, keyElementId, keyPtr, keyLength);
}

Std_ReturnType Crypto_76_HaeModule_KeySetValid( uint32 cryptoKeyId )
{
    Std_ReturnType Result;

    if(CRYPTO_GET_RESOURCE(&ResType_HaeModuleApi) == TRUE)
    {
        Result = HaeModule_Crypto_KeySetValid(cryptoKeyId);
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
    }
    else
    {
        Result = CRYPTO_E_BUSY;
    }

    return Result;
}

Std_ReturnType Crypto_76_HaeModule_KeyElementGet( uint32 cryptoKeyId, uint32 keyElementId, uint8* resultPtr, uint32* resultLengthPtr )
{
    return HaeModule_Crypto_KeyElementGet(cryptoKeyId, keyElementId, resultPtr, resultLengthPtr);
}

Std_ReturnType Crypto_76_HaeModule_KeyElementCopy( uint32 cryptoKeyId, uint32 keyElementId, uint32 targetCryptoKeyId, uint32 targetKeyElementId )
{
    Std_ReturnType Result = E_OK;

    /* This function should always be checked in the last position. */
    if(HaeModule_CryptoKeyId_Lock(cryptoKeyId) != TRUE)
    {
        Result = CRYPTO_E_BUSY;
    }
    /* This function should always be checked in the last position. */
    else if(HaeModule_CryptoKeyId_Lock(targetCryptoKeyId) != TRUE)
    {
        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
        Result = CRYPTO_E_BUSY;
    }
    else
    {
        Result = HaeModule_Crypto_KeyElementCopy(cryptoKeyId, keyElementId, targetCryptoKeyId, targetKeyElementId);
        HaeModule_CryptoKeyId_UnLock(targetCryptoKeyId);
        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
    }

    return Result;
}

Std_ReturnType Crypto_76_HaeModule_KeyElementPartialCopy( uint32 cryptoKeyId, uint32 keyElementId, uint32 keyElementSourceOffset, uint32 keyElementTargetOffset, uint32 keyElementCopyLength, uint32 targetCryptoKeyId, uint32 targetKeyElementId )
{
    Std_ReturnType Result = E_OK;

    /* This function should always be checked in the last position. */
    if(HaeModule_CryptoKeyId_Lock(cryptoKeyId) != TRUE)
    {
        Result = CRYPTO_E_BUSY;
    }
    else
    {
        Result = HaeModule_Crypto_KeyElementCopyPartial(cryptoKeyId, keyElementId, keyElementSourceOffset, keyElementTargetOffset, keyElementCopyLength, targetCryptoKeyId, targetKeyElementId);
        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
    }

    return Result;
}

Std_ReturnType Crypto_76_HaeModule_KeyCopy( uint32 cryptoKeyId, uint32 targetCryptoKeyId )
{
    Std_ReturnType Result = E_OK;

    /* This function should always be checked in the last position. */
    if(HaeModule_CryptoKeyId_Lock(cryptoKeyId) != TRUE)
    {
        Result = CRYPTO_E_BUSY;
    }
    /* This function should always be checked in the last position. */
    else if(HaeModule_CryptoKeyId_Lock(targetCryptoKeyId) != TRUE)
    {
        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
        Result = CRYPTO_E_BUSY;
    }
    else
    {
        Result = HaeModule_Crypto_KeyCopy(cryptoKeyId, targetCryptoKeyId);
        HaeModule_CryptoKeyId_UnLock(targetCryptoKeyId);
        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
    }

    return Result;
}

Std_ReturnType Crypto_76_HaeModule_KeyElementIdsGet( uint32 cryptoKeyId, uint32* keyElementIdsPtr, uint32* keyElementIdsLengthPtr )
{
    return HaeModule_Crypto_KeyElementIdsGet(cryptoKeyId, keyElementIdsPtr, keyElementIdsLengthPtr);
}

Std_ReturnType Crypto_76_HaeModule_RandomSeed( uint32 cryptoKeyId, const uint8* seedPtr, uint32 seedLength )
{
    Std_ReturnType Result;

    if(CRYPTO_GET_RESOURCE(&ResType_HaeModuleApi) == TRUE)
    {
        Result = HaeModule_Crypto_RandomSeed(cryptoKeyId, seedPtr, seedLength);
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
    }
    else
    {
        Result = CRYPTO_E_BUSY;
    }

    return Result;
}

Std_ReturnType Crypto_76_HaeModule_KeyGenerate( uint32 cryptoKeyId )
{
    Std_ReturnType Result;

    if(CRYPTO_GET_RESOURCE(&ResType_HaeModuleApi) == TRUE)
    {
        Result = HaeModule_Crypto_KeyGenerate(cryptoKeyId);
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
    }
    else
    {
        Result = CRYPTO_E_BUSY;
    }

    return Result;
}

Std_ReturnType Crypto_76_HaeModule_KeyDerive( uint32 cryptoKeyId, uint32 targetCryptoKeyId )
{
    Std_ReturnType Result;

    if(CRYPTO_GET_RESOURCE(&ResType_HaeModuleApi) == TRUE)
    {
        Result = HaeModule_Crypto_KeyDerive(cryptoKeyId, targetCryptoKeyId);
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
    }
    else
    {
        Result = CRYPTO_E_BUSY;
    }

    return Result;
}

Std_ReturnType Crypto_76_HaeModule_KeyExchangePubValCalc( uint32 cryptoKeyId, uint8* publicValuePtr, uint32* publicValueLengthPtr )
{
    Std_ReturnType Result;

    if(CRYPTO_GET_RESOURCE(&ResType_HaeModuleApi) == TRUE)
    {
        Result = HaeModule_Crypto_KeyExchangeCalcPubVal(cryptoKeyId, publicValuePtr, publicValueLengthPtr);
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
    }
    else
    {
        Result = CRYPTO_E_BUSY;
    }

    return Result;
}

Std_ReturnType Crypto_76_HaeModule_KeyExchangeSecretCalc( uint32 cryptoKeyId, const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength )
{
    Std_ReturnType Result;

    if(CRYPTO_GET_RESOURCE(&ResType_HaeModuleApi) == TRUE)
    {
        Result = HaeModule_Crypto_KeyExchangeCalcSecret(cryptoKeyId, partnerPublicValuePtr, partnerPublicValueLength);
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
    }
    else
    {
        Result = CRYPTO_E_BUSY;
    }

    return Result;
}

#define CRYPTO_76_HAEMODULE_STOP_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"
