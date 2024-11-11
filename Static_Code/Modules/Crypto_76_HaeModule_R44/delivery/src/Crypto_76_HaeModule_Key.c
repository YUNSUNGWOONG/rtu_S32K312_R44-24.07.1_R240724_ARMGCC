/*!
  @file Crypto_76_HaeModule_Key.c
  @brief Key Management Interface source file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#include "Crypto_76_HaeModule_Crypto.h"
#include "Crypto_76_HaeModule_UserTypes.h"
#include "Crypto_76_HaeModule_Key.h"
#include "Crypto_76_HaeModule_General.h"
#include "Crypto_76_HaeModule_Common.h"
#include "Crypto_76_HaeModule_Det.h"
#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
#include "SecurityApp_KeyManagement.h"
#include "Crypto_76_HaeModule_HsmPrimitive.h"
#endif
#ifdef HAEMODULE_CRYPTOOBJECT_HAECRYPTOLIB_SUPPORT
#include "Crypto_76_HaeModule_CryptoLibPrimitive.h"
#endif

#define WAIT_RESP_TIMEOUT 300000000 // 15sec

extern CryptoKey gHaeModule_CryptoKeys[HAEMODULE_CRYPTOKEYS_NUM];

/* Declare local Variables */
#define CRYPTO_76_HAEMODULE_START_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"
static DECLARE_CRYPTO_LOCK_TYPE(LockType_HaeModuleKey);
#define CRYPTO_76_HAEMODULE_STOP_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"

#define CRYPTO_76_HAEMODULE_START_RAM_VAR_CLEARED
#include "Crypto_76_HaeModule_MemMap.h"
static HaeModule_ResKeyType gHaeModule_ResKeyType;
#define CRYPTO_76_HAEMODULE_STOP_RAM_VAR_CLEARED
#include "Crypto_76_HaeModule_MemMap.h"


#define CRYPTO_76_HAEMODULE_START_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"
static void CRYPTO_KEYELEMENT_VALUESTATE(CryptoKeyElement *Element, boolean State, uint32 Size, boolean Force)
{
    if(Element != NULL)
    {
        if((State == FALSE) || (Size == 0))
        {
            Element->CryptoKeyElementValueSize  = 0;
            Element->CryptoKeyElementValueState = FALSE;
        }
        else
        {
            if((Element->CryptoKeyElementValueSize < Size) || (Force == TRUE))
            {
                Element->CryptoKeyElementValueSize = Size;
            }
            Element->CryptoKeyElementValueState = State;
        }
    }
}

static void HaeModule_CryptoKeyId_LockInit(void)
{
    HaeModule_Crypto_Memset((uint8 *)&gHaeModule_ResKeyType, 0, (uint32)sizeof(HaeModule_ResKeyType));
}

/*
 * While cryptoKeyId is in use, it is locked to prevent other functions from using it.
 */
boolean HaeModule_CryptoKeyId_Lock( uint32 cryptoKeyId )
{
    boolean Result = FALSE;
    uint32 i;

    if(CRYPTO_CRITICAL_SECTION_LOCK(&LockType_HaeModuleKey) == TRUE)
    {
        for(i = 0; i < gHaeModule_ResKeyType.count; i++)
        {
            if(cryptoKeyId == gHaeModule_ResKeyType.cryptoKeyId[i])
            {
                break;
            }
        }

        if(i >= gHaeModule_ResKeyType.count)
        {
            if(gHaeModule_ResKeyType.count < (uint32)HAEMODULE_RESKEYTYPE_CRYPTOKEYID_MAX_NUM)
            {
                gHaeModule_ResKeyType.cryptoKeyId[gHaeModule_ResKeyType.count] = cryptoKeyId;
                gHaeModule_ResKeyType.count++;
                Result = TRUE;
            }
        }

        CRYPTO_CRITICAL_SECTION_UNLOCK(&LockType_HaeModuleKey);
    }

    return Result;
}

/*
 * Unlocks cryptoKeyId.
 */
void HaeModule_CryptoKeyId_UnLock( uint32 cryptoKeyId )
{
    uint32 i;
    uint32 count;

    if(CRYPTO_CRITICAL_SECTION_LOCK(&LockType_HaeModuleKey) == TRUE)
    {
        for(i = 0; i < gHaeModule_ResKeyType.count; i++)
        {
            if(cryptoKeyId == gHaeModule_ResKeyType.cryptoKeyId[i])
            {
                break;
            }
        }

        count = i;
        i++;

        while(i < gHaeModule_ResKeyType.count)
        {
            gHaeModule_ResKeyType.cryptoKeyId[count] = gHaeModule_ResKeyType.cryptoKeyId[i];
            count++;
            i++;
        }

        gHaeModule_ResKeyType.count = count;
        CRYPTO_CRITICAL_SECTION_UNLOCK(&LockType_HaeModuleKey);
    }
}

CryptoKey* HaeModule_Crypto_Get_Key(uint32 cryptoKeyId)
{
    CryptoKey *Key;
    CryptoKey *FindKey = NULL;
    uint32 k;

    for(k = 0; k < (uint32)HAEMODULE_CRYPTOKEYS_NUM; k++)
    {
        Key = &gHaeModule_CryptoKeys[k];
        if(Key->CryptoKeyId == cryptoKeyId)
        {
            FindKey = Key;
            break;
        }
    }

    return FindKey;
}

CryptoKeyElement* HaeModule_Crypto_Get_KeyElement(uint32 cryptoKeyId, uint32 keyElementId)
{
    CryptoKey *Key;
    CryptoKeyType *Type;
    CryptoKeyElement *Element;
    CryptoKeyElement *FindElement = NULL;
    uint32 e;

    Key = HaeModule_Crypto_Get_Key(cryptoKeyId);
    if(Key != NULL)
    {
        Type = Key->CryptoKeyTypeRef;
        for(e = 0; (Type != NULL) && (e < Type->CryptoKeyElementNum); e++)
        {
            Element = Type->CryptoKeyElementRef[e];
            if((Element != NULL) && (Element->CryptoKeyElementId == keyElementId))
            {
                FindElement = Element;
                break;
            }
        }
    }

    return FindElement;
}

static void HaeModule_Crypto_KeyElementInitValue(void)
{
    CryptoKey *Key;
    CryptoKeyType *Type;
    CryptoKeyElement *Element;
    #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
    Std_ReturnType HsmDrvResult;
    #endif
    #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
    Rsa_Keypair_t RsaKeypair;
    #endif
    #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
    Ecc_Keypair_t EccKeypair;
    #endif
    #if defined(HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT) \
        || defined(HAEHSM_PRIMITIVE_ECCECDSASIGNP521R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDSAVERIFYP521R1_SUPPORT)
    Ecc_P521r1_Keypair_t EccP521r1Keypair;
    #endif
    #if defined(HAEHSM_PRIMITIVE_ECCEDDSASIGNED448_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCEDDSAVERIFYED448_SUPPORT)
    Ecc_ED448_Keypair_t EccEd448Keypair;
    #endif
    #if defined(HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT)
    Ecc_X448_Keypair_t EccX448Keypair;
    #endif
    #if defined(HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT)
    uint32 index;
    #endif
    Crypto_HaeHsmKeyType keyType;
    uint16 keyIndex;
    uint32 k, e, i;

    /*
     * CryptoKeyElementInitValue which will be used to fill the key element during startup
     * (i) for all non-persistent key elements, and (ii) for those persistent key elements that have never been written.
    */
    for(k = 0; k < (uint32)HAEMODULE_CRYPTOKEYS_NUM; k++)
    {
        Key = &gHaeModule_CryptoKeys[k];
        Type = Key->CryptoKeyTypeRef;
        if(Type != NULL)
        {
            for(e = 0; e < Type->CryptoKeyElementNum; e++)
            {
                Element = Type->CryptoKeyElementRef[e];
                if((Element != NULL) && (Element->CryptoKeyElementInitValue != NULL))
                {
                    if(Element->CryptoKeyElementWriteAccess == CRYPTO_WA_ALLOWED)
                    {
                        keyType  = Element->CryptoKeyElementHsmKeyType;
                        keyIndex = Element->CryptoKeyElementHsmKeyIndex;

                        switch( keyType )
                        {
                            #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
                            case HAEHSM_KEY_TYPE_AES:
                                HsmDrvResult = HSM_KeyManagementValidateKey(AES_KEY, keyIndex);
                                if(HsmDrvResult != E_OK)
                                {
                                    (void)HSM_KeyManagementSetAesKey(keyIndex, (const UINT8*)Element->CryptoKeyElementInitValue, 0);
                                }
                                break;
                            #endif

                            #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
                            case HAEHSM_KEY_TYPE_RSA:
                                HsmDrvResult = HSM_KeyManagementValidateKey(RSA_KEY, keyIndex);
                                if(HsmDrvResult != E_OK)
                                {
                                    index = 0;
                                    for(i = 0; i < (uint32)RSA_BYTE_SIZE; i++)
                                    {
                                        RsaKeypair.mod[i] = Element->CryptoKeyElementInitValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)RSA_BYTE_SIZE; i++)
                                    {
                                        RsaKeypair.priExp[i] = Element->CryptoKeyElementInitValue[index];
                                        index++;
                                    }

                                    (void)HSM_KeyManagementSetRsaKey(keyIndex, (Rsa_Keypair_t*)&RsaKeypair, 0);
                                }
                                break;
                            #endif

                            #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
                            case HAEHSM_KEY_TYPE_ECC:
                                HsmDrvResult = HSM_KeyManagementValidateKey(ECC_KEY, keyIndex);
                                if(HsmDrvResult != E_OK)
                                {
                                    index = 0;
                                    for(i = 0; i < (uint32)ECC_BYTE_SIZE; i++)
                                    {
                                        EccKeypair.prikey[i] = Element->CryptoKeyElementInitValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)ECC_BYTE_SIZE; i++)
                                    {
                                        EccKeypair.pubkeyX[i] = Element->CryptoKeyElementInitValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)ECC_BYTE_SIZE; i++)
                                    {
                                        EccKeypair.pubkeyY[i] = Element->CryptoKeyElementInitValue[index];
                                        index++;
                                    }

                                    (void)HSM_KeyManagementSetEccKey(keyIndex, (Ecc_Keypair_t*)&EccKeypair, 0);
                                }
                                break;
                            #endif

                            #if defined(HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT) \
                                || defined(HAEHSM_PRIMITIVE_ECCECDSASIGNP521R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDSAVERIFYP521R1_SUPPORT)
                            case HAEHSM_KEY_TYPE_ECC_P521R1:
                                HsmDrvResult = HSM_KeyManagementValidateKey(ECC_P521R1_KEY, keyIndex);
                                if(HsmDrvResult != E_OK)
                                {
                                    index = 0;
                                    for(i = 0; i < (uint32)ECC_P521r1_BYTE_SIZE; i++)
                                    {
                                        EccP521r1Keypair.prikey[i] = Element->CryptoKeyElementInitValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)ECC_P521r1_BYTE_SIZE; i++)
                                    {
                                        EccP521r1Keypair.pubkeyX[i] = Element->CryptoKeyElementInitValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)ECC_P521r1_BYTE_SIZE; i++)
                                    {
                                        EccP521r1Keypair.pubkeyY[i] = Element->CryptoKeyElementInitValue[index];
                                        index++;
                                    }

                                    (void)HSM_KeyManagementSetEccP521r1Key(keyIndex, (Ecc_P521r1_Keypair_t*)&EccP521r1Keypair, 0);
                                }
                                break;
                            #endif

                            #if defined(HAEHSM_PRIMITIVE_ECCEDDSASIGNED448_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCEDDSAVERIFYED448_SUPPORT)
                            case HAEHSM_KEY_TYPE_ECC_ED448:
                                HsmDrvResult = HSM_KeyManagementValidateKey(ECC_ED448_KEY, keyIndex);
                                if(HsmDrvResult != E_OK)
                                {
                                    index = 0;
                                    for(i = 0; i < (uint32)ECC_ED448_BYTE_SIZE; i++)
                                    {
                                        EccEd448Keypair.prikey[i] = Element->CryptoKeyElementInitValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)ECC_ED448_BYTE_SIZE; i++)
                                    {
                                        EccEd448Keypair.pubkey[i] = Element->CryptoKeyElementInitValue[index];
                                        index++;
                                    }

                                    (void)HSM_KeyManagementSetEccED448Key(keyIndex, (Ecc_ED448_Keypair_t*)&EccEd448Keypair, 0);
                                }
                                break;
                            #endif

                            #if defined(HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT)
                            case HAEHSM_KEY_TYPE_ECC_X448:
                                HsmDrvResult = HSM_KeyManagementValidateKey(ECC_X448_KEY, keyIndex);
                                if(HsmDrvResult != E_OK)
                                {
                                    index = 0;
                                    for(i = 0; i < (uint32)ECC_X448_BYTE_SIZE; i++)
                                    {
                                        EccX448Keypair.prikey[i] = Element->CryptoKeyElementInitValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)ECC_X448_BYTE_SIZE; i++)
                                    {
                                        EccX448Keypair.pubkey[i] = Element->CryptoKeyElementInitValue[index];
                                        index++;
                                    }

                                    (void)HSM_KeyManagementSetEccX448Key(keyIndex, (Ecc_X448_Keypair_t*)&EccX448Keypair, 0);
                                }
                                break;
                            #endif

                            default:
                                /* HAEHSM_KEY_TYPE_NONE */
                                if(Element->CryptoKeyElementValue != NULL)
                                {
                                    for(i = 0; i < Element->CryptoKeyElementSize; i++)
                                    {
                                        Element->CryptoKeyElementValue[i] = Element->CryptoKeyElementInitValue[i];
                                    }

                                    CRYPTO_KEYELEMENT_VALUESTATE(Element, TRUE, Element->CryptoKeyElementSize, TRUE);
                                }
                                break;
                        }
                    }
                }
            }
        }
    }
}

static Std_ReturnType HaeModule_Crypto_SetKeyState(CryptoKey *Key)
{
    CryptoKeyType *Type;
    CryptoKeyElement *Element;
    Std_ReturnType Result = E_OK;
    Std_ReturnType HsmDrvResult;
    Crypto_HaeHsmKeyType keyType;
    uint16 keyIndex;
    uint32 e;

    if(Key != NULL)
    {
        Key->CryptoKeyState = TRUE;

        Type = Key->CryptoKeyTypeRef;
        if((Type != NULL) && (Type->CryptoKeyElementNum != 0))
        {
            for(e = 0; (e < Type->CryptoKeyElementNum) && (Result == E_OK); e++)
            {
                Element = Type->CryptoKeyElementRef[e];
                if(Element != NULL)
                {
                    keyType  = Element->CryptoKeyElementHsmKeyType;
                    keyIndex = Element->CryptoKeyElementHsmKeyIndex;

                    HsmDrvResult = E_OK;

                    switch (keyType) {
                    #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
                    case HAEHSM_KEY_TYPE_AES:
                        HsmDrvResult = HSM_KeyManagementValidateKey(AES_KEY, keyIndex);
                        break;
                    #endif

                    #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
                    case HAEHSM_KEY_TYPE_RSA:
                        HsmDrvResult = HSM_KeyManagementValidateKey(RSA_KEY, keyIndex);
                        break;
                    #endif

                    #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
                    case HAEHSM_KEY_TYPE_ECC:
                        HsmDrvResult = HSM_KeyManagementValidateKey(ECC_KEY, keyIndex);
                        break;
                    #endif

                    #if defined(HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT) \
                        || defined(HAEHSM_PRIMITIVE_ECCECDSASIGNP521R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDSAVERIFYP521R1_SUPPORT)
                    case HAEHSM_KEY_TYPE_ECC_P521R1:
                        HsmDrvResult = HSM_KeyManagementValidateKey(ECC_P521R1_KEY, keyIndex);
                        break;
                    #endif

                    #if defined (HAEHSM_PRIMITIVE_ECCEDDSASIGNED448_SUPPORT) || defined (HAEHSM_PRIMITIVE_ECCEDDSAVERIFYED448_SUPPORT)
                    case HAEHSM_KEY_TYPE_ECC_ED448:
                        HsmDrvResult = HSM_KeyManagementValidateKey(ECC_ED448_KEY, keyIndex);
                        break;
                    #endif

                    #if defined(HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT)
                    case HAEHSM_KEY_TYPE_ECC_X448:
                        HsmDrvResult = HSM_KeyManagementValidateKey(ECC_X448_KEY, keyIndex);
                        break;
                    #endif

                    default:
                        if(Element->CryptoKeyElementPersist == TRUE)
                        {
                            /* In case of HSM Key */
                            HsmDrvResult = E_NOT_OK;
                        }
                        break;
                    }

                    if(HsmDrvResult != E_OK)
                    {
                        Key->CryptoKeyState = FALSE;
                    }

                    if((Element->CryptoKeyElementValue != NULL)
                        && (Element->CryptoKeyElementValueState != TRUE)
                    )
                    {
                         Key->CryptoKeyState = FALSE;
                    }
                }
                else
                {
                    Key->CryptoKeyState = FALSE;
                    Result = E_NOT_OK;
                }
            }
        }
        else
        {
            Key->CryptoKeyState = FALSE;
        }
    }
    else
    {
        Result = E_NOT_OK;
    }

    return Result;
}

static Std_ReturnType HaeModule_Crypto_KeyStateInit(void)
{
    CryptoKey *Key;
    Std_ReturnType Result = E_OK;
    uint32 k;

    /*
     * [SWS_Crypto_00198] If during initialization of the Crypto Driver the value of a persistent key could not be loaded,
     * the Crypto Driver shall set the state of the corresponding key to invalid.
     */
    for(k = 0; k < (uint32)HAEMODULE_CRYPTOKEYS_NUM; k++)
    {
        Key = &gHaeModule_CryptoKeys[k];

        Result = HaeModule_Crypto_SetKeyState(Key);
        if(Result != E_OK)
        {
            break;
        }
    }

    return Result;
}

/*!
  @brief Initialize key management interface
  @details Set the initialization value and state of key elements
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed
*/
Std_ReturnType HaeModule_Crypto_KeyInit(void)
{
    Std_ReturnType Result;

    HaeModule_CryptoKeyId_LockInit();
    HaeModule_Crypto_KeyElementInitValue();

    Result = HaeModule_Crypto_KeyStateInit();

    return Result;
}

/*!
  @brief Get key state
  @details Get the state, valid or invalid, of the given key id
  @param[in] cryptoKeyId    Holds the identifier of the key
  @return E_OK: Valid state \n
        E_NOT_OK: Invalid state
*/
Std_ReturnType HaeModule_Crypto_IsKeyValid( uint32 cryptoKeyId )
{
    Std_ReturnType Result = E_NOT_OK;
    CryptoKey *Key;

    Key = HaeModule_Crypto_Get_Key(cryptoKeyId);
    if(Key != NULL)
    {
        if(Key->CryptoKeyState == TRUE)
        {
            Result = E_OK;
        }
    }

    return Result;
}

/*!
  @brief Sets the given key element bytes to the key identified by cryptoKeyId
  @details Service ID[hex]: 0x04 \n
        Sync/Async: Synchronous \n
        Reentrancy: Non Reentrant \n
        [SWS_Crypto_00075] If the Crypto Driver is not yet initialized and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementSet shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00076] If cryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementSet shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00077] If parameter keyElementId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementSet shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00078] If the parameter keyPtr is a null pointer and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementSet shall report CRYPTO_E_PARAM_POINTER to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00079] If keyLength is zero and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementSet shall report CRYPTO_E_PARAM_VALUE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00146] If keyLength is smaller than the size of the key element, and the key element is not configured to allow partial access, \n
            the function Crypto_KeyElementSet shall return CRYPTO_E_KEY_SIZE_MISMATCH.
  @param[in] cryptoKeyId    Holds the identifier of the key whose key element shall be set.
  @param[in] keyElementId   Holds the identifier of the key element which shall be set.
  @param[in] keyPtr         Holds the pointer to the key data which shall be set as key element.
  @param[in] keyLength      Contains the length of the key element in bytes.
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed \n
        CRYPTO_E_BUSY: Request failed, Crypto Driver Object is busy \n
        CRYPTO_E_KEY_WRITE_FAIL:Request failed because write access was denied \n
        CRYPTO_E_KEY_NOT_AVAILABLE: Request failed because the key is not available \n
        CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, key element size does not match size of provided data
*/
Std_ReturnType HaeModule_Crypto_KeyElementSet( uint32 cryptoKeyId, uint32 keyElementId, const uint8* keyPtr, uint32 keyLength )
{
    Std_ReturnType Result = E_OK;
    CryptoKey *Key = NULL;
    CryptoKeyElement *Element = NULL;
    uint32 i;

    if(HaeModule_Is_Crypto_Init() != TRUE)
    {
        HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTSET, CRYPTO_DET_E_UNINIT);
        Result = E_NOT_OK;
    }
    /* This function should always be checked in the last position. */
    else if(HaeModule_CryptoKeyId_Lock(cryptoKeyId) != TRUE)
    {
        Result = CRYPTO_E_BUSY;
    }
    else
    {
        Key = HaeModule_Crypto_Get_Key(cryptoKeyId);
        if(Key == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTSET, CRYPTO_DET_E_PARAM_HANDLE);
            Result = E_NOT_OK;
        }
        else
        {
            Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, keyElementId);
            if(Element == NULL)
            {
                HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTSET, CRYPTO_DET_E_PARAM_HANDLE);
                Result = CRYPTO_E_KEY_NOT_AVAILABLE;
            }
            else if(keyPtr == NULL)
            {
                HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTSET, CRYPTO_DET_E_PARAM_POINTER);
                Result = E_NOT_OK;
            }
            else if(keyLength == 0)
            {
                HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTSET, CRYPTO_DET_E_PARAM_VALUE);
                Result = E_NOT_OK;
            }
            else if(Element->CryptoKeyElementWriteAccess == CRYPTO_WA_DENIED)
            {
                Result = CRYPTO_E_KEY_WRITE_FAIL;
            }
            else if(Element->CryptoKeyElementValue == NULL)
            {
                Result = E_NOT_OK;
            }
            else if(Element->CryptoKeyElementSize < keyLength)
            {
                Result = CRYPTO_E_KEY_SIZE_MISMATCH;
            }
            else if((Element->CryptoKeyElementSize > keyLength) && (Element->CryptoKeyElementAllowPartialAccess != TRUE))
            {
                Result = CRYPTO_E_KEY_SIZE_MISMATCH;
            }
            else
            {
                for(i = 0; i < keyLength; i++)
                {
                    Element->CryptoKeyElementValue[i] = keyPtr[i];
                }

                CRYPTO_KEYELEMENT_VALUESTATE(Element, TRUE, keyLength, TRUE);
                Key->CryptoKeyState = FALSE;
            }
        }

        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
    }

    return Result;
}

/*!
  @brief Sets the key state of the key identified by cryptoKeyId to valid.
  @details Service ID[hex]: 0x05 \n
        Sync/Async: Synchronous \n
        Reentrancy: Non Reentrant \n
        [SWS_Crypto_00196] If the module is not yet initialized and development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeySetValid shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00197] If parameter cryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeySetValid shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        If no errors are detected by Crypto Driver, the service Crypto_KeySetValid() sets the key cryptoKeyId to �쐖alid��.
  @param[in] cryptoKeyId    Holds the identifier of the key which shall be set to valid.
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed \n
        CRYPTO_E_BUSY: Request failed, Crypto Driver Object is busy
*/
Std_ReturnType HaeModule_Crypto_KeySetValid( uint32 cryptoKeyId )
{
    CryptoKey *Key;
    CryptoKeyType *Type;
    CryptoKeyElement *Element;
    Std_ReturnType Result = E_OK;
    #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
    Rsa_Keypair_t RsaKeypair;
    #endif
    #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
    Ecc_Keypair_t EccKeypair;
    #endif
    #if defined(HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT) \
        || defined(HAEHSM_PRIMITIVE_ECCECDSASIGNP521R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDSAVERIFYP521R1_SUPPORT)
    Ecc_P521r1_Keypair_t EccP521r1Keypair;
    #endif
    #if defined(HAEHSM_PRIMITIVE_ECCEDDSASIGNED448_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCEDDSAVERIFYED448_SUPPORT)
    Ecc_ED448_Keypair_t EccEd448Keypair;
    #endif
    #if defined(HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT)
    Ecc_X448_Keypair_t EccX448Keypair;
    #endif
    #if defined(HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT)
    uint32 index;
    #endif
    Crypto_HaeHsmKeyType keyType;
    uint16 keyIndex;
    uint32 e, i;

    if(HaeModule_Is_Crypto_Init() != TRUE)
    {
        HaeModule_Det_ReportError(CRYPTO_API_KEYSETVALID, CRYPTO_DET_E_UNINIT);
        Result = E_NOT_OK;
    }
    /* This function should always be checked in the last position. */
    else if(HaeModule_CryptoKeyId_Lock(cryptoKeyId) != TRUE)
    {
        Result = CRYPTO_E_BUSY;
    }
    else
    {
        Key = HaeModule_Crypto_Get_Key(cryptoKeyId);
        if(Key == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYSETVALID, CRYPTO_DET_E_PARAM_HANDLE);
            Result = E_NOT_OK;
        }
        else
        {
            if(Key->CryptoKeyState != TRUE)
            {
                Type = Key->CryptoKeyTypeRef;
                for(e = 0; (Type != NULL) && (e < Type->CryptoKeyElementNum) && (Result == E_OK); e++)
                {
                    Element = Type->CryptoKeyElementRef[e];
                    if((Element != NULL) && (Element->CryptoKeyElementValue != NULL) && (Element->CryptoKeyElementValueState == TRUE))
                    {
                        if(Element->CryptoKeyElementWriteAccess == CRYPTO_WA_ALLOWED)
                        {
                            keyType  = Element->CryptoKeyElementHsmKeyType;
                            keyIndex = Element->CryptoKeyElementHsmKeyIndex;

                            switch( keyType )
                            {
                                #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
                                case HAEHSM_KEY_TYPE_AES:
                                    Result = HSM_DRIVER_RETURN(HSM_KeyManagementSetAesKey(keyIndex, (UINT8*)Element->CryptoKeyElementValue, 0));
                                    break;
                                #endif

                                #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
                                case HAEHSM_KEY_TYPE_RSA:
                                    index = 0;
                                    for(i = 0; i < (uint32)RSA_BYTE_SIZE; i++)
                                    {
                                        RsaKeypair.mod[i] = Element->CryptoKeyElementValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)RSA_BYTE_SIZE; i++)
                                    {
                                        RsaKeypair.priExp[i] = Element->CryptoKeyElementValue[index];
                                        index++;
                                    }

                                    Result = HSM_DRIVER_RETURN(HSM_KeyManagementSetRsaKey(keyIndex, (Rsa_Keypair_t*)&RsaKeypair, 0));
                                    break;
                                #endif

                                #ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
                                case HAEHSM_KEY_TYPE_ECC:
                                    index = 0;
                                    for(i = 0; i < (uint32)ECC_BYTE_SIZE; i++)
                                    {
                                        EccKeypair.prikey[i] = Element->CryptoKeyElementValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)ECC_BYTE_SIZE; i++)
                                    {
                                        EccKeypair.pubkeyX[i] = Element->CryptoKeyElementValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)ECC_BYTE_SIZE; i++)
                                    {
                                        EccKeypair.pubkeyY[i] = Element->CryptoKeyElementValue[index];
                                        index++;
                                    }

                                    Result = HSM_DRIVER_RETURN(HSM_KeyManagementSetEccKey(keyIndex, (Ecc_Keypair_t*)&EccKeypair, 0));
                                    break;
                                #endif

                                #if defined(HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT) \
                                    || defined(HAEHSM_PRIMITIVE_ECCECDSASIGNP521R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDSAVERIFYP521R1_SUPPORT)
                                case HAEHSM_KEY_TYPE_ECC_P521R1:
                                    index = 0;
                                    for(i = 0; i < (uint32)ECC_P521r1_BYTE_SIZE; i++)
                                    {
                                        EccP521r1Keypair.prikey[i] = Element->CryptoKeyElementValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)ECC_P521r1_BYTE_SIZE; i++)
                                    {
                                        EccP521r1Keypair.pubkeyX[i] = Element->CryptoKeyElementValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)ECC_P521r1_BYTE_SIZE; i++)
                                    {
                                        EccP521r1Keypair.pubkeyY[i] = Element->CryptoKeyElementValue[index];
                                        index++;
                                    }

                                    Result = HSM_DRIVER_RETURN(HSM_KeyManagementSetEccP521r1Key(keyIndex, (Ecc_P521r1_Keypair_t*)&EccP521r1Keypair, 0));
                                    break;
                                #endif

                                #if defined(HAEHSM_PRIMITIVE_ECCEDDSASIGNED448_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCEDDSAVERIFYED448_SUPPORT)
                                case HAEHSM_KEY_TYPE_ECC_ED448:
                                    index = 0;
                                    for(i = 0; i < (uint32)ECC_ED448_BYTE_SIZE; i++)
                                    {
                                        EccEd448Keypair.prikey[i] = Element->CryptoKeyElementValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)ECC_ED448_BYTE_SIZE; i++)
                                    {
                                        EccEd448Keypair.pubkey[i] = Element->CryptoKeyElementValue[index];
                                        index++;
                                    }

                                    Result = HSM_DRIVER_RETURN(HSM_KeyManagementSetEccED448Key(keyIndex, (Ecc_ED448_Keypair_t*)&EccEd448Keypair, 0));
                                    break;
                                #endif

                                #if defined(HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT)
                                case HAEHSM_KEY_TYPE_ECC_X448:
                                    index = 0;
                                    for(i = 0; i < (uint32)ECC_X448_BYTE_SIZE; i++)
                                    {
                                        EccX448Keypair.prikey[i] = Element->CryptoKeyElementValue[index];
                                        index++;
                                    }
                                    for(i = 0; i < (uint32)ECC_X448_BYTE_SIZE; i++)
                                    {
                                        EccX448Keypair.pubkey[i] = Element->CryptoKeyElementValue[index];
                                        index++;
                                    }

                                    Result = HSM_DRIVER_RETURN(HSM_KeyManagementSetEccX448Key(keyIndex, (Ecc_X448_Keypair_t*)&EccX448Keypair, 0));
                                    break;
                                #endif

                                default:
                                    /* HAEHSM_KEY_TYPE_NONE */
                                    Result = E_NOT_OK;
                                    break;
                            }

                            if(Result == E_OK)
                            {
                                /* In case of HSM Key */
                                for(i = 0; i < Element->CryptoKeyElementSize; i++)
                                {
                                    Element->CryptoKeyElementValue[i] = 0;
                                }

                                CRYPTO_KEYELEMENT_VALUESTATE(Element, FALSE, 0, TRUE);
                            }
                            else {
                                /* In case of non-HSM Key */
                                if (keyIndex == 0) {
                                    Result = E_OK;
                                }
                            }
                        }
                    }
                }

                if(Result == E_OK)
                {
                    Key->CryptoKeyState = TRUE;
                }
            }
        }

        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
    }

    return Result;
}

/*!
  @brief This interface shall be used to get a key element of the key identified by the cryptoKeyId and store the key element \n
         in the memory location pointed by the result pointer.
  @details Service ID[hex]: 0x06 \n
        Sync/Async: Synchronous \n
        Reentrancy: Reentrant \n
        [SWS_Crypto_00140] If the function Crypto_KeyElementGet returns CRYPTO_E_KEY_NOT_AVAILABLE, \n
            the function shall additionally report the runtime error CRYPTO_E_RE_KEY_NOT_AVAILABLE. \n
        [SWS_Crypto_00139] If the function Crypto_KeyElementGet returns CRYPTO_E_KEY_READ_FAIL, \n
            the function shall additionally report the runtime error CRYPTO_E_RE_KEY_READ_FAIL. \n
        [SWS_Crypto_00085] If the module is not yet initialized and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementGet shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00086] If the parameter cryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementGet shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00087] If the parameter keyElementId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementGet shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00088] If the parameter resultPtr is a null pointer and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementGet shall report CRYPTO_E_PARAM_POINTER the DET and return E_NOT_OK. \n
        [SWS_Crypto_00089] If the parameter resultLengthPtr is a null pointer and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementGet shall report CRYPTO_E_PARAM_POINTER to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00090] If the value, which is pointed by resultLengthPtr is zero and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementGet shall report CRYPTO_E_PARAM_VALUE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00092] The pointer resultPtr holds the memory location, where the data of the key element shall be stored. On calling this function, \n
            resultLengthPtr shall contain the size of the buffer provided by resultPtr. When the request has finished, \n
            the actual length of the returned value shall be stored.
  @param[in] cryptoKeyId            Holds the identifier of the key which shall be set to valid.
  @param[in] keyElementId           Holds the identifier of the key element which shall be returned.
  @param[in,out] resultLengthPtr    Holds a pointer to a memory location in which the length information is stored.
  @param[out] resultPtr             Holds the pointer of the buffer for the returned key element
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed \n
        CRYPTO_E_BUSY: Request failed, Crypto Driver Object is busy \n
        CRYPTO_E_KEY_NOT_AVAILABLE: Request failed, the requested key element is not available \n
        CRYPTO_E_KEY_READ_FAIL: Request failed because read access was denied \n
        CRYPTO_E_SMALL_BUFFER: The provided buffer is too small to store the result \n
        CRYPTO_E_KEY_EMPTY: Request failed because of uninitialized source key element
*/
Std_ReturnType HaeModule_Crypto_KeyElementGet( uint32 cryptoKeyId, uint32 keyElementId, uint8* resultPtr, uint32* resultLengthPtr )
{
    Std_ReturnType Result = E_OK;
    CryptoKey *Key;
    CryptoKeyElement *Element;
    uint32 i, Length;

    if(HaeModule_Is_Crypto_Init() != TRUE)
    {
        HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTGET, CRYPTO_DET_E_UNINIT);
        Result = E_NOT_OK;
    }
    /* This function should always be checked in the last position. */
    else if(HaeModule_CryptoKeyId_Lock(cryptoKeyId) != TRUE)
    {
        Result = CRYPTO_E_BUSY;
    }
    else
    {
        Key = HaeModule_Crypto_Get_Key(cryptoKeyId);
        if(Key == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTGET, CRYPTO_DET_E_PARAM_HANDLE);
            Result = E_NOT_OK;
        }
        else
        {
            Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, keyElementId);
            if(Element == NULL)
            {
                HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTGET, CRYPTO_DET_E_PARAM_HANDLE);
                Result = CRYPTO_E_KEY_NOT_AVAILABLE;
            }
            else if((resultPtr == NULL) || (resultLengthPtr == NULL))
            {
                HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTGET, CRYPTO_DET_E_PARAM_POINTER);
                Result = E_NOT_OK;
            }
            else if(*resultLengthPtr == 0)
            {
                HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTGET, CRYPTO_DET_E_PARAM_VALUE);
                Result = E_NOT_OK;
            }
            else if((Element->CryptoKeyElementAllowPartialAccess != TRUE) && (Element->CryptoKeyElementSize > *resultLengthPtr))
            {
                Result = CRYPTO_E_SMALL_BUFFER;
            }
            else if(Element->CryptoKeyElementReadAccess != CRYPTO_RA_ALLOWED)
            {
                HaeModule_Det_ReportRuntimeError(CRYPTO_API_KEYELEMENTGET, CRYPTO_DET_E_RE_KEY_READ_FAIL);
                Result = CRYPTO_E_KEY_READ_FAIL;
            }
            else if((Element->CryptoKeyElementValue == NULL) || (Element->CryptoKeyElementValueState != TRUE))
            {
                HaeModule_Det_ReportRuntimeError(CRYPTO_API_KEYELEMENTGET, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                Result = CRYPTO_E_KEY_EMPTY;
            }
            else
            {
                if(Element->CryptoKeyElementAllowPartialAccess == TRUE)
                {
                    Length = Element->CryptoKeyElementValueSize;
                }
                else
                {
                    Length = Element->CryptoKeyElementSize;
                }

                for(i = 0; i < Length; i++)
                {
                    resultPtr[i] = Element->CryptoKeyElementValue[i];
                }

                *resultLengthPtr = Length;
            }
        }

        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
    }

    return Result;
}

static Std_ReturnType HaeModule_Crypto_Internal_KeyElementCopyPartial( const CryptoKey *cryptoKey, const CryptoKeyElement *keyElement,
                                                        uint32 keyElementSourceOffset,
                                                        uint32 keyElementTargetOffset,
                                                        uint32 keyElementCopyLength,
                                                        const CryptoKey *targetCryptoKey, CryptoKeyElement *targetKeyElement )
{
    Std_ReturnType Result = E_OK;
    uint32 i;

    if(((keyElementSourceOffset + keyElementCopyLength) > keyElement->CryptoKeyElementSize)
    || ((keyElementTargetOffset + keyElementCopyLength) > targetKeyElement->CryptoKeyElementSize)
    )
    {
        Result  = CRYPTO_E_KEY_SIZE_MISMATCH;
    }
    else if(keyElement->CryptoKeyElementReadAccess == CRYPTO_RA_DENIED)
    {
        Result = CRYPTO_E_KEY_READ_FAIL;
    }
    else if(targetKeyElement->CryptoKeyElementWriteAccess == CRYPTO_WA_DENIED)
    {
        Result = CRYPTO_E_KEY_WRITE_FAIL;
    }
    else if((keyElement->CryptoKeyElementValue == NULL) || (keyElement->CryptoKeyElementValueState == FALSE))
    {
        Result = CRYPTO_E_KEY_EMPTY;
    }
    else if(targetKeyElement->CryptoKeyElementValue == NULL)
    {
        Result = CRYPTO_E_KEY_NOT_AVAILABLE;
    }
    else
    {
        for(i = 0; i < keyElementCopyLength; i++)
        {
            targetKeyElement->CryptoKeyElementValue[keyElementTargetOffset + i] = keyElement->CryptoKeyElementValue[keyElementSourceOffset + i];
        }
    }

    return Result;
}

/*!
  @brief Copies a key element to another key element in the same crypto driver.
  @details Service ID[hex]: 0x0f \n
        Sync/Async: Synchronous \n
        Reentrancy: Reentrant, but not for the same cryptoKeyId \n
        [SWS_Crypto_00149] If the Crypto Driver is not yet initialized and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementCopy shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00150] If cryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementCopy shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00151] If targetCryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementCopy shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00152] If parameter keyElementId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementCopy shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00153] If parameter targetKeyElementId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementCopy shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00154] If no errors are detected by the Crypto Driver, the function shall copy the key element referenced by keyElementId in the key referenced by cryptoKeyId \n
            to the key element referenced by targetKeyElementId in the key referenced by targetCryptoKeyId.
  @param[in] cryptoKeyId            Holds the identifier of the key whose key element shall be the source element.
  @param[in] keyElementId           Holds the identifier of the key element which shall be the source for the copy operation.
  @param[in] targetCryptoKeyId      Holds the identifier of the key whose key element shall be the destination element.
  @param[in] targetKeyElementId     Holds the identifier of the key element which shall be the destination for the copy operation.
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed \n
        CRYPTO_E_BUSY: Request failed, Crypto Driver Object is busy \n
        CRYPTO_E_KEY_NOT_AVAILABLE: Request failed, the requested key element is not available \n
        CRYPTO_E_KEY_READ_FAIL: Request failed, not allowed to extract key element \n
        CRYPTO_E_KEY_WRITE_FAIL: Request failed, not allowed to write key element \n
        CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, key element sizes are not compatible \n
        CRYPTO_E_KEY_EMPTY: Request failed because of uninitialized source key element
*/
Std_ReturnType HaeModule_Crypto_KeyElementCopy( uint32 cryptoKeyId, uint32 keyElementId, uint32 targetCryptoKeyId, uint32 targetKeyElementId )
{
    CryptoKey *Key, *targetKey;
    CryptoKeyElement *Element, *targetElement;
    Std_ReturnType Result = E_OK;

    if(HaeModule_Is_Crypto_Init() != TRUE)
    {
        HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTCOPY, CRYPTO_DET_E_UNINIT);
        Result = E_NOT_OK;
    }
    else
    {
        Key = HaeModule_Crypto_Get_Key(cryptoKeyId);
        if(Key == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTCOPY, CRYPTO_DET_E_PARAM_HANDLE);
            Result = E_NOT_OK;
        }
        else
        {
            Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, keyElementId);
            if(Element == NULL)
            {
                HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTCOPY, CRYPTO_DET_E_PARAM_HANDLE);
                Result = E_NOT_OK;
            }
            else
            {
                targetKey = HaeModule_Crypto_Get_Key(targetCryptoKeyId);
                if(targetKey == NULL)
                {
                    HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTCOPY, CRYPTO_DET_E_PARAM_HANDLE);
                    Result = E_NOT_OK;
                }
                else
                {
                    targetElement = HaeModule_Crypto_Get_KeyElement(targetCryptoKeyId, targetKeyElementId);
                    if(targetElement == NULL)
                    {
                        HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTCOPY, CRYPTO_DET_E_PARAM_HANDLE);
                        Result = E_NOT_OK;
                    }
                    else if(Element->CryptoKeyElementSize != targetElement->CryptoKeyElementSize)
                    {
                        Result = CRYPTO_E_KEY_SIZE_MISMATCH;
                    }
                    else
                    {
                        Result = HaeModule_Crypto_Internal_KeyElementCopyPartial(Key, Element, 0, 0, Element->CryptoKeyElementSize, targetKey, targetElement);
                        if(Result == E_OK)
                        {
                            CRYPTO_KEYELEMENT_VALUESTATE(targetElement, TRUE, Element->CryptoKeyElementSize, TRUE);
                            targetKey->CryptoKeyState = FALSE;
                        }
                    }
                }
            }
        }
    }

    return Result;
}

/*!
  @brief Copies a key element to another key element in the same crypto driver. \n
        The keyElementSourceOffset and keyElementCopyLength allows to copy just a part of the source key element into the destination. \n
        The offset of the target key is also specified with this function.
  @details Service ID[hex]: 0x13 \n
        Sync/Async: Synchronous \n
        Reentrancy: Reentrant, but not for the same cryptoKeyId \n
        [SWS_Crypto_00205] If the Crypto Driver is not yet initialized and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementCopyPartial shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00206] If cryptoKeyId, keyElementId , targetKeyElementId or targetCryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementCopyPartial shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00207] If the total length of the key element specified with keyElementId of the key referenced by cryptoKeyId is smaller than keyElementSourceOffset + keyElementCopyLength \n
            Crypto_KeyElementCopyPartial shall return CRYPTO_E_KEY_SIZE_MISMATCH. \n
        [SWS_Crypto_00208] If the maximum available buffer of the key element specified with targetKeyElementId of the key referenced by targetCryptoKeyId is smaller than keyElementTargetOffset + keyElementCopyLength, \n
            the function Crypto_KeyElementCopyPartial shall return CRYPTO_E_KEY_SIZE_MISMATCH. \n
        [SWS_Crypto_00209] If no errors are detected by the Crypto Driver, the function Crypto_KeyElementCopyPartial shall copy a part of the key element referenced by keyElementId of the key \n
            referenced by cryptoKeyId with the offset of keyElementSourceOffset and with the length specified by keyElementCopyLength to the key element referenced by targetKeyElementId of the key referenced by targetCryptoKeyId. \n
        [SWS_Crypto_00210] If the current length of the target key element is greater or equal than (keyElementTargetOffset + keyElementCopyLength), the key element length remains unchanged. \n
        [SWS_Crypto_00211] If the current length of the target key element is lower than (keyElementTargetOffset + keyElementCopyLength) and the maximum length of the key element is greater or equal \n
            than (keyElementTargetOffset + keyElementCopyLength), then the source data shall be copied into the target key element and the length shall be set to (keyElementTargetOffset + keyElementCopyLength).
  @param[in] cryptoKeyId            Holds the identifier of the key whose key element shall be the source element.
  @param[in] keyElementId           Holds the identifier of the key element which shall be the source for the copy operation.
  @param[in] keyElementSourceOffset This is the offset of the of the source key element indicating the start index of the copy operation.
  @param[in] keyElementTargetOffset This is the offset of the of the target key element indicating the start index of the copy operation.
  @param[in] keyElementCopyLength   Specifies the number of bytes that shall be copied.
  @param[in] targetCryptoKeyId      Holds the identifier of the key whose key element shall be the destination element.
  @param[in] targetKeyElementId     Holds the identifier of the key element which shall be the destination for the copy operation.
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed \n
        CRYPTO_E_BUSY: Request failed, Crypto Driver Object is busy \n
        CRYPTO_E_KEY_NOT_AVAILABLE: Request failed, the requested key element is not available \n
        CRYPTO_E_KEY_READ_FAIL: Request failed, not allowed to extract key element \n
        CRYPTO_E_KEY_WRITE_FAIL: Request failed, not allowed to write key element \n
        CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, key element sizes are not compatible \n
        CRYPTO_E_KEY_EMPTY: Request failed because of uninitialized source key element
*/
Std_ReturnType HaeModule_Crypto_KeyElementCopyPartial( uint32 cryptoKeyId, uint32 keyElementId, uint32 keyElementSourceOffset, uint32 keyElementTargetOffset, uint32 keyElementCopyLength, uint32 targetCryptoKeyId, uint32 targetKeyElementId )
{
    CryptoKey *Key, *targetKey;
    CryptoKeyElement *Element, *targetElement;
    Std_ReturnType Result = E_OK;

    if(HaeModule_Is_Crypto_Init() != TRUE)
    {
        HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTCOPY, CRYPTO_DET_E_UNINIT);
        Result = E_NOT_OK;
    }
    else
    {
        Key = HaeModule_Crypto_Get_Key(cryptoKeyId);
        if(Key == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTCOPY, CRYPTO_DET_E_PARAM_HANDLE);
            Result = E_NOT_OK;
        }
        else
        {
            Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, keyElementId);
            if(Element == NULL)
            {
                HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTCOPY, CRYPTO_DET_E_PARAM_HANDLE);
                Result = E_NOT_OK;
            }
            else
            {
                targetKey = HaeModule_Crypto_Get_Key(targetCryptoKeyId);
                if(targetKey == NULL)
                {
                    HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTCOPY, CRYPTO_DET_E_PARAM_HANDLE);
                    Result = E_NOT_OK;
                }
                else
                {
                    targetElement = HaeModule_Crypto_Get_KeyElement(targetCryptoKeyId, targetKeyElementId);
                    if(targetElement == NULL)
                    {
                        HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTCOPY, CRYPTO_DET_E_PARAM_HANDLE);
                        Result = E_NOT_OK;
                    }
                    else if((Element->CryptoKeyElementAllowPartialAccess != TRUE) || (targetElement->CryptoKeyElementAllowPartialAccess != TRUE))
                    {
                        Result = E_NOT_OK;
                    }
                    else
                    {
                        Result = HaeModule_Crypto_Internal_KeyElementCopyPartial(Key, Element, keyElementSourceOffset, keyElementTargetOffset, keyElementCopyLength, targetKey, targetElement);
                        if(Result == E_OK)
                        {
                            CRYPTO_KEYELEMENT_VALUESTATE(targetElement, TRUE, (keyElementTargetOffset + keyElementCopyLength), FALSE);
                            targetKey->CryptoKeyState = FALSE;
                        }
                    }
                }
            }
        }
    }

    return Result;
}

/*!
  @brief Copies a key with all its elements to another key in the same crypto driver.
  @details Service ID[hex]: 0x10 \n
        Sync/Async: Synchronous \n
        Reentrancy: Reentrant, but not for the same cryptoKeyId \n
        [SWS_Crypto_00156] If the Crypto Driver is not yet initialized and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyCopy shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00157] If cryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyCopy shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00158] If targetCryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyCopy shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00159] If no errors are detected by the Crypto Driver, \n
            the function shall copy all key elements in the key referenced by cryptoKeyId to the key the key referenced by targetCryptoKeyId.
  @param[in] cryptoKeyId            Holds the identifier of the key whose key element shall be the source element.
  @param[in] targetCryptoKeyId      Holds the identifier of the key whose key element shall be the destination element.
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed \n
        CRYPTO_E_BUSY: Request failed, Crypto Driver Object is busy \n
        CRYPTO_E_KEY_NOT_AVAILABLE: Request failed, the requested key element is not available \n
        CRYPTO_E_KEY_READ_FAIL: Request failed, not allowed to extract key element \n
        CRYPTO_E_KEY_WRITE_FAIL: Request failed, not allowed to write key element \n
        CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, key element sizes are not compatible \n
        CRYPTO_E_KEY_EMPTY: Request failed because of uninitialized source key element
*/
Std_ReturnType HaeModule_Crypto_KeyCopy( uint32 cryptoKeyId, uint32 targetCryptoKeyId )
{
    CryptoKey *Key, *targetKey;
    CryptoKeyType *Type;
    CryptoKeyElement *Element;
    Std_ReturnType Result = E_OK;
    uint32 e;

    if(HaeModule_Is_Crypto_Init() != TRUE)
    {
        HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTCOPY, CRYPTO_DET_E_UNINIT);
        Result = E_NOT_OK;
    }
    else
    {
        Key = HaeModule_Crypto_Get_Key(cryptoKeyId);
        if(Key == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTCOPY, CRYPTO_DET_E_PARAM_HANDLE);
            Result = E_NOT_OK;
        }
        else
        {
            targetKey = HaeModule_Crypto_Get_Key(targetCryptoKeyId);
            if(targetKey == NULL)
            {
                HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTCOPY, CRYPTO_DET_E_PARAM_HANDLE);
                Result = E_NOT_OK;
            }
            else
            {
                Type = Key->CryptoKeyTypeRef;
                for(e = 0; (Type != NULL) && (e < Type->CryptoKeyElementNum) && (Result == E_OK); e++)
                {
                    Element = Type->CryptoKeyElementRef[e];
                    if(Element != NULL)
                    {
                        Result = HaeModule_Crypto_KeyElementCopy(cryptoKeyId, Element->CryptoKeyElementId, targetCryptoKeyId, Element->CryptoKeyElementId);
                    }
                }
            }
        }
    }

    return Result;
}

/*!
  @brief Used to retrieve information which key elements are available in a given key.
  @details Service ID[hex]: 0x11 \n
        Sync/Async: Synchronous \n
        Reentrancy: Reentrant, but not for the same cryptoKeyId \n
        [SWS_Crypto_00161] If the Crypto Driver is not yet initialized and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementIdsGet shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00162] If cryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyElementIdsGet shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        If no errors are detected by the Crypto Driver, the function stores all ids of the key elements available in the key identified \n
        by cryptoKeyId to an array provided by keyElementIdsPtr. \n
        It also stores the number of elements to the value, which is pointed by keyElementIdsLengthPtr.
  @param[in] cryptoKeyId            Holds the identifier of the key whose available element ids shall be exported.
  @param[out] keyElementIdsPtr      Contains the pointer to the array where the ids of the key elements shall be stored.
  @param[in] keyElementIdsLengthPtr Holds a pointer to the memory location in which the number of key elements in the given key is stored. \n
                                    On calling this function, this parameter shall contain the size of the buffer provided by keyElementIdsPtr. \n
                                    When the request has finished, the actual number of key elements shall be stored.
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed \n
        E_BUSY: Request failed, Crypto Driver Object is busy \n
        CRYPTO_E_SMALL_BUFFER: The provided buffer is too small to store the result
*/
Std_ReturnType HaeModule_Crypto_KeyElementIdsGet( uint32 cryptoKeyId, uint32* keyElementIdsPtr, uint32* keyElementIdsLengthPtr )
{
    Std_ReturnType Result = E_OK;
    CryptoKey *Key;
    CryptoKeyType *Type;
    CryptoKeyElement *Element;
    uint32 id = 0;
    uint32 e;

    if(HaeModule_Is_Crypto_Init() != TRUE)
    {
        HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTIDSGET, CRYPTO_DET_E_UNINIT);
        Result = E_NOT_OK;
    }
    else if((keyElementIdsPtr == NULL) || (keyElementIdsLengthPtr == NULL))
    {
        HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTIDSGET, CRYPTO_DET_E_PARAM_POINTER);
        Result = E_NOT_OK;
    }
    /* This function should always be checked in the last position. */
    else if(HaeModule_CryptoKeyId_Lock(cryptoKeyId) != TRUE)
    {
        Result = CRYPTO_E_BUSY;
    }
    else
    {
        Key = HaeModule_Crypto_Get_Key(cryptoKeyId);
        if(Key == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYELEMENTIDSGET, CRYPTO_DET_E_PARAM_HANDLE);
            Result = E_NOT_OK;
        }
        else
        {
            Type = Key->CryptoKeyTypeRef;
            for(e = 0; (Type != NULL) && (e < Type->CryptoKeyElementNum) && (Result == E_OK); e++)
            {
                Element = Type->CryptoKeyElementRef[e];
                if(Element != NULL)
                {
                    if(id < *keyElementIdsLengthPtr)
                    {
                        keyElementIdsPtr[id] = Element->CryptoKeyElementId;
                        id++;
                    }
                    else
                    {
                        Result = CRYPTO_E_SMALL_BUFFER;
                    }
                }
            }

            *keyElementIdsLengthPtr = id;
        }

        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
    }

    return Result;
}

Std_ReturnType HaeModule_Crypto_RandomSeed( uint32 cryptoKeyId, const uint8* seedPtr, uint32 seedLength )
{
    Std_ReturnType result = E_NOT_OK;
    CryptoKeyElement *element;

    if(HaeModule_Is_Crypto_Init() != TRUE) {
        HaeModule_Det_ReportError(CRYPTO_API_RANDOMSEED, CRYPTO_DET_E_UNINIT);
    }
    else {
        element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_RANDOM_ALGORITHM);
        if(element == NULL) {
            HaeModule_Det_ReportError(CRYPTO_API_RANDOMSEED, CRYPTO_DET_E_PARAM_HANDLE);
        }
        else if(element->CryptoKeyElementReadAccess == CRYPTO_RA_DENIED) {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_RANDOMSEED, CRYPTO_DET_E_RE_KEY_READ_FAIL);
        }
        else if((element->CryptoKeyElementValue == NULL) || (element->CryptoKeyElementValueState != TRUE)) {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_RANDOMSEED, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
        }
        else if(seedPtr == NULL) {
            HaeModule_Det_ReportError(CRYPTO_API_RANDOMSEED, CRYPTO_DET_E_PARAM_POINTER);
        }
        else if(seedLength == 0){
            HaeModule_Det_ReportError(CRYPTO_API_RANDOMSEED, CRYPTO_DET_E_PARAM_VALUE);
        }
        else {
            uint32 algorithmType = 0;
            // CryptoLib - start
            Crypto_JobType job;
            job.cryptoKeyId = 0; //dummy
            job.jobPrimitiveInputOutput.inputPtr = seedPtr;
            job.jobPrimitiveInputOutput.inputLength = seedLength;
            job.jobId = 0xffffffffU;
            // CryptoLib - end

            HaeModule_Crypto_Memcpy((uint8 *)&algorithmType, (const uint8 *)element->CryptoKeyElementValue, 4);

            switch (algorithmType) {
            case HAEMODULE_CRYPTO_DRBG_SHA256:
                result = HaeCryptoLib_Primitive_HashDrbgSha256_Seed(NULL, &job);
                break;
            default:
                /* Nothing to do */
                break;
            }
        }
    }

    return result;
}

Std_ReturnType HaeModule_Crypto_KeyGenerate( uint32 cryptoKeyId )
{
    /* Not supported function */
    return E_NOT_OK;
}

/*!
  @brief Derives a new key by using the key elements in the given key identified by the cryptoKeyId. \n
         The given key contains the key elements for the password, salt. \n
         The derived key is stored in the key element with the id 1 of the key identified by targetCryptoKeyId. \n
         The number of iterations is given in the key element CRYPTO_KE_KEYDERIVATION_ITERATIONS.
  @details Service ID[hex]: 0x08 \n
        Sync/Async: Synchronous \n
        Reentrancy: Reentrant, but not for the same cryptoKeyId \n
        [SWS_Crypto_00097] If the module is not yet initialized and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyDerive shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00098] If the parameter cryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyDerive shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00180] If the parameter targetCryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyDerive shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00166] If no errors are detected by Crypto Driver, the service Crypto_KeyDerive() derives a key element with the aid of a salt and a password.
  @param[in] cryptoKeyId            Holds the identifier of the key which is used for key derivation.
  @param[in] targetCryptoKeyId      Holds the identifier of the key which is used to store the derived key.
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed \n
        E_BUSY: Request failed, Crypto Driver Object is busy \n
        CRYPTO_E_KEY_EMPTY: Request failed because of uninitialized source key element
*/
Std_ReturnType HaeModule_Crypto_KeyDerive( uint32 cryptoKeyId, uint32 targetCryptoKeyId )
{
    Std_ReturnType Result = E_OK;
    CryptoKey *Key, *targetKey;
    CryptoKeyElement *Element;
    CryptoKeyElement *AlgorithmElement  = NULL;

    if(HaeModule_Is_Crypto_Init() != TRUE)
    {
        HaeModule_Det_ReportError(CRYPTO_API_KEYDERIVE, CRYPTO_DET_E_UNINIT);
        Result = E_NOT_OK;
    }
    /* This function should always be checked in the last position. */
    else if (HaeModule_CryptoKeyId_Lock(cryptoKeyId) != TRUE) {
        Result = CRYPTO_E_BUSY;
    }
    /* This function should always be checked in the last position. */
    else if (HaeModule_CryptoKeyId_Lock(targetCryptoKeyId) != TRUE) {
        Result = CRYPTO_E_BUSY;
        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
    }
    else
    {
        Key = HaeModule_Crypto_Get_Key(cryptoKeyId);
        targetKey = HaeModule_Crypto_Get_Key(targetCryptoKeyId);

        if((Key == NULL) || (targetKey == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYDERIVE, CRYPTO_DET_E_PARAM_HANDLE);
            Result = E_NOT_OK;
        }
        else if(Key->CryptoKeyState != TRUE)
        {
            /* [SWS_Crypto_00039] If a key is in the state �쐇nvalid��,
            crypto services which make use of that key, shall return with CRYPTO_E_KEY_NOT_VALID. */
            Result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYDERIVATION_ALGORITHM);
            if((Element != NULL)
            && (Element->CryptoKeyElementValue != NULL)
            && (Element->CryptoKeyElementValueState == TRUE)
            && (Element->CryptoKeyElementReadAccess == CRYPTO_RA_ALLOWED)
            && (Element->CryptoKeyElementValueSize == (uint32)sizeof(uint32)))
            {
                AlgorithmElement = Element;
            }

            if(AlgorithmElement == NULL)
            {
                Result = CRYPTO_E_KEY_EMPTY;
            }
            else
            {
                uint32 algorithmType = 0;
                // CryptoLib - start
                Crypto_JobType job;
                job.cryptoKeyId = cryptoKeyId;
                job.targetCryptoKeyId = targetCryptoKeyId;
                job.jobId = 0xffffffffU;
                // CryptoLib - end

                HaeModule_Crypto_Memcpy((uint8 *)&algorithmType, (const uint8 *)AlgorithmElement->CryptoKeyElementValue, (uint32)sizeof(uint32));

                switch (algorithmType) {
                case HAEMODULE_CRYPTO_PBKDF2_HMAC_SHA256:
                    #ifdef HAECRYPTOLIB_PRIMITIVE_PBKDF2HMACSHA256_SUPPORT
                    Result = HaeCryptoLib_Primitive_Pbkdf2HmacSha256(NULL, &job);
                    #else
                    Result = E_NOT_OK;
                    #endif
                    break;
                case HAEMODULE_CRYPTO_PBKDF2_HMAC_SHA256_HSM:
                    #if defined(HAEHSM_PRIMITIVE_KEYDERIVE_SUPPORT)
                    Result = HaeHsm_Primitive_Crypto_KeyDerive(cryptoKeyId, targetCryptoKeyId, algorithmType);
                    #else
                    Result = E_NOT_OK;
                    #endif
                    break;
                default:
                    Result = E_NOT_OK;
                    break;
                }

                if (Result == E_OK) {
                    targetKey->CryptoKeyState = FALSE;
                }
            }
        }

        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
        HaeModule_CryptoKeyId_UnLock(targetCryptoKeyId);
    }

    return Result;
}

/*!
  @brief Calculates the public value for the key exchange and stores the public key in the memory location pointed by the public value pointer.
  @details Service ID[hex]: 0x09 \n
        Sync/Async: Synchronous \n
        Reentrancy: Reentrant, but not for the same cryptoKeyId \n
        [SWS_Crypto_00103] If the module is not yet initialized and if development error detection for the Crypto Driver is enabled, \n
            The function Crypto_KeyExchangeCalcPubVal shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00104] If the parameter cryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyExchangeCalcPubVal shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00105] If the parameter publicValuePtr is a null pointer and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyExchangeCalcPubVal shall report CRYPTO_E_PARAM_POINTER to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00106] If the parameter pubValueLengthPtr is a null pointer and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyExchangeCalcPubVal shall report CRYPTO_E_PARAM_POINTER to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00107] If the value, which is pointed by pubValueLengthPtr is zero and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyExchangeCalcPubVal shall report CRYPTO_E_PARAM_VALUE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00167] If no errors are detected by Crypto Driver, the service Crypto_KeyExchangeCalcPubVal() calculates the public value of the current job for the key exchange. \n
        [SWS_Crypto_00109] The pointer publicValuePtr holds the memory location, where the data of the public value shall be stored. On calling this function, \n
            publicValueLengthPtr shall contain the size of the buffer provided by publicValuePtr. \n
            When the request has finished, the actual length of the returned value shall be stored. \n
        [SWS_Crypto_00110] If the buffer publicValuePtr is too small to store the result of the request, \n
            CRYPTO_E_SMALL_BUFFER shall be returned and the function shall additionally report the runtime error CRYPTO_E_RE_SMALL_BUFFER.
  @param[in] cryptoKeyId            Holds the identifier of the key which shall be used for the key exchange protocol.
  @param[out] publicValuePtr        Contains the pointer to the data where the public value shall be stored.
  @param[in] publicValueLengthPtr   Holds a pointer to the memory location in which the public value length information is stored.
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed \n
        E_BUSY: Request failed, Crypto Driver Object is busy \n
        CRYPTO_E_SMALL_BUFFER: The provided buffer is too small to store the result \n
        CRYPTO_E_KEY_EMPTY: Request failed because of uninitialized source key element
*/
Std_ReturnType HaeModule_Crypto_KeyExchangeCalcPubVal( uint32 cryptoKeyId, uint8* publicValuePtr, uint32* publicValueLengthPtr )
{
    Std_ReturnType Result = E_OK;
    CryptoKey *Key;
    CryptoKeyElement *Element;
    CryptoKeyElement *AlgorithmElement  = NULL;

    if(HaeModule_Is_Crypto_Init() != TRUE)
    {
        HaeModule_Det_ReportError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_UNINIT);
        Result = E_NOT_OK;
    }
    /* This function should always be checked in the last position. */
    else if (HaeModule_CryptoKeyId_Lock(cryptoKeyId) != TRUE) {
        Result = CRYPTO_E_BUSY;
    }
    else
    {
        Key = HaeModule_Crypto_Get_Key(cryptoKeyId);
        if(Key == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_PARAM_HANDLE);
            Result = E_NOT_OK;
        }
        else if(Key->CryptoKeyState != TRUE)
        {
            /* [SWS_Crypto_00039] If a key is in the state �쐇nvalid��,
            crypto services which make use of that key, shall return with CRYPTO_E_KEY_NOT_VALID. */
            Result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if((publicValuePtr == NULL) || (publicValueLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_PARAM_POINTER);
            Result = E_NOT_OK;
        }
        else if(*publicValueLengthPtr == 0)
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_PARAM_VALUE);
            Result = E_NOT_OK;
        }
        else
        {
            Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_ALGORITHM);
            if((Element != NULL)
            && (Element->CryptoKeyElementValue != NULL)
            && (Element->CryptoKeyElementValueState == TRUE)
            && (Element->CryptoKeyElementReadAccess == CRYPTO_RA_ALLOWED)
            && (Element->CryptoKeyElementValueSize == (uint32)sizeof(uint32)))
            {
                AlgorithmElement = Element;
            }

            if(AlgorithmElement == NULL)
            {
                Result = CRYPTO_E_KEY_EMPTY;
            }
            else
            {
                uint32 algorithmType = 0;
                // CryptoLib - start
                Crypto_JobType job;
                job.cryptoKeyId = cryptoKeyId;
                job.targetCryptoKeyId = 0;
                job.jobPrimitiveInputOutput.outputPtr = publicValuePtr;
                job.jobPrimitiveInputOutput.outputLengthPtr = publicValueLengthPtr;
                job.jobId = 0xffffffffU;
                // CryptoLib - end

                HaeModule_Crypto_Memcpy((uint8 *)&algorithmType, (const uint8 *)AlgorithmElement->CryptoKeyElementValue, (uint32)sizeof(uint32));

                switch (algorithmType) {
                case HAEMODULE_CRYPTO_DH:
                    #ifdef HAECRYPTOLIB_PRIMITIVE_DH_CALCPUBVAL_SUPPORT
                    Result = HaeCryptoLib_Primitive_Dh_CalcPubVal(NULL, &job);
                    #else
                    Result = E_NOT_OK;
                    #endif
                    break;
                case HAEMODULE_CRYPTO_ECDH:
                    #ifdef HAECRYPTOLIB_PRIMITIVE_ECDH_CALCPUBVAL_SUPPORT
                    Result = HaeCryptoLib_Primitive_Ecdh_CalcPubVal(NULL, &job);
                    #else
                    Result = E_NOT_OK;
                    #endif
                    break;
                case HAEMODULE_CRYPTO_DH_HSM:
                    #if defined(HAEHSM_PRIMITIVE_RSAPKCS3DHKEYPAIRGEN_SUPPORT)
                    Result = HaeHsm_Primitive_Crypto_KeyExchangeCalcPubVal(cryptoKeyId, publicValuePtr, publicValueLengthPtr, HAEMODULE_CRYPTO_DH_HSM);
                    #else
                    Result = E_NOT_OK;
                    #endif
                    break;
                default:
                    Result = E_NOT_OK;
                    break;
                }
            }
        }

        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
    }

    return Result;
}

/*!
  @brief Calculates the shared secret key for the key exchange with the key material of the key identified by the cryptoKeyId and the partner public key. \n
         The shared secret key is stored as a key element in the same key.
  @details Service ID[hex]: 0x0a \n
        Sync/Async: Synchronous \n
        Reentrancy: Reentrant, but not for the same cryptoKeyId \n
        [SWS_Crypto_00111] If the module is not yet initialized and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyExchangeCalcSecret shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00112] If the parameter cryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyExchangeCalcSecret shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00113] If the parameter partnerPublicValuePtr is a null pointer and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyExchangeCalcSecret shall report CRYPTO_E_PARAM_POINTER to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00115] If partnerPublicValueLength is zero and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyExchangeCalcSecret shall report CRYPTO_E_PARAM_VALUE to the DET and return E_NOT_OK.
  @param[in] cryptoKeyId                Holds the identifier of the key which shall be used for the key exchange protocol.
  @param[in] partnerPublicValuePtr      Holds the pointer to the memory location which contains the partner's public value.
  @param[in] partnerPublicValueLength   Contains the length of the partner's public value in bytes.
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed \n
        E_BUSY: Request failed, Crypto Driver Object is busy \n
        CRYPTO_E_SMALL_BUFFER: The provided buffer is too small to store the result \n
        CRYPTO_E_KEY_EMPTY: Request failed because of uninitialized source key element
*/
Std_ReturnType HaeModule_Crypto_KeyExchangeCalcSecret( uint32 cryptoKeyId, const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength )
{
    Std_ReturnType Result = E_OK;
    CryptoKey *Key;
    CryptoKeyElement *Element;
    CryptoKeyElement *AlgorithmElement  = NULL;

    if(HaeModule_Is_Crypto_Init() != TRUE)
    {
        HaeModule_Det_ReportError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_UNINIT);
        Result = E_NOT_OK;
    }
    /* This function should always be checked in the last position. */
    else if(HaeModule_CryptoKeyId_Lock(cryptoKeyId) != TRUE)
    {
        Result = CRYPTO_E_BUSY;
    }
    else
    {
        Key = HaeModule_Crypto_Get_Key(cryptoKeyId);
        if(Key == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_PARAM_HANDLE);
            Result = E_NOT_OK;
        }
        else if(Key->CryptoKeyState != TRUE)
        {
            /* [SWS_Crypto_00039] If a key is in the state �쐇nvalid��,
            crypto services which make use of that key, shall return with CRYPTO_E_KEY_NOT_VALID. */
            Result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(partnerPublicValuePtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_PARAM_POINTER);
            Result = E_NOT_OK;
        }
        else if(partnerPublicValueLength == 0)
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_PARAM_VALUE);
            Result = E_NOT_OK;
        }
        else
        {
            Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_ALGORITHM);
            if((Element != NULL)
            && (Element->CryptoKeyElementValue != NULL)
            && (Element->CryptoKeyElementValueState == TRUE)
            && (Element->CryptoKeyElementReadAccess == CRYPTO_RA_ALLOWED)
            && (Element->CryptoKeyElementValueSize == (uint32)sizeof(uint32)))
            {
                AlgorithmElement = Element;
            }

            if(AlgorithmElement == NULL)
            {
                Result = CRYPTO_E_KEY_EMPTY;
            }
            else
            {
                uint32 algorithmType = 0;
                // CryptoLib - start
                Crypto_JobType job;
                job.cryptoKeyId = cryptoKeyId;
                job.targetCryptoKeyId = 0;
                job.jobPrimitiveInputOutput.inputPtr = partnerPublicValuePtr;
                job.jobPrimitiveInputOutput.inputLength = partnerPublicValueLength;
                job.jobId = 0xffffffffU;
                // CryptoLib - end

                HaeModule_Crypto_Memcpy((uint8 *)&algorithmType, (const uint8 *)AlgorithmElement->CryptoKeyElementValue, (uint32)sizeof(uint32));

                switch (algorithmType) {
                case HAEMODULE_CRYPTO_DH:
                    #ifdef HAECRYPTOLIB_PRIMITIVE_DH_CALCSECRET_SUPPORT
                    Result = HaeCryptoLib_Primitive_Dh_CalcSecret(NULL, &job);
                    #else
                    Result = E_NOT_OK;
                    #endif
                    break;
                case HAEMODULE_CRYPTO_ECDH:
                    #ifdef HAECRYPTOLIB_PRIMITIVE_ECDH_CALCSECRET_SUPPORT
                    Result = HaeCryptoLib_Primitive_Ecdh_CalcSecret(NULL, &job);
                    #else
                    Result = E_NOT_OK;
                    #endif
                    break;
                case HAEMODULE_CRYPTO_DH_HSM:
                    #if defined(HAEHSM_PRIMITIVE_RSAPKCS3DHSHAREDVALUEGEN_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDH_SUPPORT) \
                        || defined(HAEHSM_PRIMITIVE_ECCECDHP256R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT)
                    Result = HaeHsm_Primitive_Crypto_KeyExchangeCalcSecret(cryptoKeyId, partnerPublicValuePtr, partnerPublicValueLength, HAEMODULE_CRYPTO_DH_HSM);
                    #else
                    Result = E_NOT_OK;
                    #endif
                    break;
                case HAEMODULE_CRYPTO_ECDH_HSM:
                    #if defined(HAEHSM_PRIMITIVE_RSAPKCS3DHSHAREDVALUEGEN_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDH_SUPPORT) \
                        || defined(HAEHSM_PRIMITIVE_ECCECDHP256R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT)
                    Result = HaeHsm_Primitive_Crypto_KeyExchangeCalcSecret(cryptoKeyId, partnerPublicValuePtr, partnerPublicValueLength, HAEMODULE_CRYPTO_ECDH_HSM);
                    #else
                    Result = E_NOT_OK;
                    #endif
                    break;
                default:
                    Result = E_NOT_OK;
                    break;
                }

                if(Result == E_OK)
                {
                    /* Key is updated, However, it is set to valid for user convenience. */
                    Key->CryptoKeyState = TRUE;
                }
            }
        }

        HaeModule_CryptoKeyId_UnLock(cryptoKeyId);
    }

    return Result;
}

#define CRYPTO_76_HAEMODULE_STOP_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"




