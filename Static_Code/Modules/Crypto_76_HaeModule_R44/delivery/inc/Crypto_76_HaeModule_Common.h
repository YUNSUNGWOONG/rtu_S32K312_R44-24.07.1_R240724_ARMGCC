#ifndef CRYPTO_76_HAEMODULE_COMMON_H
#define CRYPTO_76_HAEMODULE_COMMON_H

#include "Crypto_76_HaeModule_Crypto.h"

typedef uint32  CRYPTO_RESOUCE_TYPE;

typedef struct {
    uint32 CoreLock;
} CRYPTO_LOCK_TYPE;


#define DECLARE_CRYPTO_LOCK_TYPE(name)              CRYPTO_LOCK_TYPE name = {0}
#define CRYPTO_CRITICAL_SECTION_LOCK(pLock)         HaeModule_Crypto_CriticalSection_Lock(pLock)
#define CRYPTO_CRITICAL_SECTION_UNLOCK(pLock)       HaeModule_Crypto_CriticalSection_UnLock(pLock)

#define DECLARE_CRYPTO_RESOUCE_TYPE(name)           CRYPTO_RESOUCE_TYPE name = 0
#define CRYPTO_GET_RESOURCE(pResource)              HaeModule_Crypto_GetResource(pResource)
#define CRYPTO_RELEASE_RESOURCE(pResource)          HaeModule_Crypto_ReleaseResource(pResource)

#ifndef EXTERN_DECLARE_CRYPTO_RESOUCE_TYPE
#ifdef CRYPTO_76_HAEMODULE_COMMON_C
#define EXTERN_DECLARE_CRYPTO_RESOUCE_TYPE(name)
#else
#define EXTERN_DECLARE_CRYPTO_RESOUCE_TYPE(name)    extern CRYPTO_RESOUCE_TYPE name
#endif
#endif

#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
#define HSM_DRIVER_RETURN                           HaeModule_Crypto_TranslateHsmDrvResult
#endif

EXTERN_DECLARE_CRYPTO_RESOUCE_TYPE(ResType_HaeModuleApi);


boolean HaeModule_Crypto_CriticalSection_Lock(CRYPTO_LOCK_TYPE *Lock);
void HaeModule_Crypto_CriticalSection_UnLock(CRYPTO_LOCK_TYPE *Lock);
boolean HaeModule_Crypto_GetResource(CRYPTO_RESOUCE_TYPE *Resource);
void HaeModule_Crypto_ReleaseResource(CRYPTO_RESOUCE_TYPE *Resource);
void HaeModule_Crypto_Memcpy(uint8 *dst, const uint8 *src, uint32 len);
void HaeModule_Crypto_Memset(uint8 *dst, uint8 src, uint32 len);
#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
Std_ReturnType HaeModule_Crypto_TranslateHsmDrvResult(Std_ReturnType HsmDrvResult);
#endif

#endif /* CRYPTO_76_HAEMODULE_COMMON_H */
