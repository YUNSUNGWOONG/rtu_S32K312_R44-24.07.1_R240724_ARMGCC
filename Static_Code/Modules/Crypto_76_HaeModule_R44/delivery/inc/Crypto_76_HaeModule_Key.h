/*!
  @file Crypto_76_HaeModule_Key.h
  @brief Key Management Interface header file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef CRYPTO_76_HAEMODULE_KEY_H
#define CRYPTO_76_HAEMODULE_KEY_H

/*
 * CryptoKeyId must be prevented from being used by other functions while it is being updated.
 * To achieve this, variables that can tell whether cryptoKeyId is used must be added and managed as many as the number of cryptoKeyIds.
 * However, it takes a lot of resources.
 * Therefore, we set the number of variables assuming that the number of cryptoKeyIds used simultaneously is limited.
 */
#define HAEMODULE_RESKEYTYPE_CRYPTOKEYID_MAX_NUM      (10)
typedef struct
{
    uint32 count;
    uint32 cryptoKeyId[HAEMODULE_RESKEYTYPE_CRYPTOKEYID_MAX_NUM];
} HaeModule_ResKeyType;


Std_ReturnType HaeModule_Crypto_KeyInit(void);
Std_ReturnType HaeModule_Crypto_IsKeyValid( uint32 cryptoKeyId );
boolean HaeModule_CryptoKeyId_Lock( uint32 cryptoKeyId );
void HaeModule_CryptoKeyId_UnLock( uint32 cryptoKeyId );
CryptoKey* HaeModule_Crypto_Get_Key(uint32 cryptoKeyId);
CryptoKeyElement* HaeModule_Crypto_Get_KeyElement(uint32 cryptoKeyId, uint32 keyElementId);
Std_ReturnType HaeModule_Crypto_KeyElementSet( uint32 cryptoKeyId, uint32 keyElementId, const uint8* keyPtr, uint32 keyLength );
Std_ReturnType HaeModule_Crypto_KeySetValid( uint32 cryptoKeyId );
Std_ReturnType HaeModule_Crypto_KeyElementGet( uint32 cryptoKeyId, uint32 keyElementId, uint8* resultPtr, uint32* resultLengthPtr );
Std_ReturnType HaeModule_Crypto_KeyElementCopy( uint32 cryptoKeyId, uint32 keyElementId, uint32 targetCryptoKeyId, uint32 targetKeyElementId );
Std_ReturnType HaeModule_Crypto_KeyElementCopyPartial( uint32 cryptoKeyId, uint32 keyElementId, uint32 keyElementSourceOffset, uint32 keyElementTargetOffset, uint32 keyElementCopyLength, uint32 targetCryptoKeyId, uint32 targetKeyElementId );
Std_ReturnType HaeModule_Crypto_KeyCopy( uint32 cryptoKeyId, uint32 targetCryptoKeyId );
Std_ReturnType HaeModule_Crypto_KeyElementIdsGet( uint32 cryptoKeyId, uint32* keyElementIdsPtr, uint32* keyElementIdsLengthPtr );
Std_ReturnType HaeModule_Crypto_RandomSeed( uint32 cryptoKeyId, const uint8* seedPtr, uint32 seedLength );
Std_ReturnType HaeModule_Crypto_KeyGenerate( uint32 cryptoKeyId );
Std_ReturnType HaeModule_Crypto_KeyDerive( uint32 cryptoKeyId, uint32 targetCryptoKeyId );
Std_ReturnType HaeModule_Crypto_KeyExchangeCalcPubVal( uint32 cryptoKeyId, uint8* publicValuePtr, uint32* publicValueLengthPtr );
Std_ReturnType HaeModule_Crypto_KeyExchangeCalcSecret( uint32 cryptoKeyId, const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength );

#endif /* CRYPTO_76_HAEMODULE_KEY_H */
