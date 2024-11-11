#define CRYPTO_76_HAEMODULE_COMMON_C
#include "Crypto_76_HaeModule_Crypto.h"
#include "Crypto_76_HaeModule_Common.h"
#include "SchM_Crypto_76_HaeModule.h"

/* Declare local Variables */
#define CRYPTO_76_HAEMODULE_START_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"
DECLARE_CRYPTO_RESOUCE_TYPE(ResType_HaeModuleApi);
static DECLARE_CRYPTO_LOCK_TYPE(LockType_Resource);
#define CRYPTO_76_HAEMODULE_STOP_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"


#define CRYPTO_76_HAEMODULE_START_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"
static boolean HaeModule_Crypto_InterCore_Lock(uint32 *CoreLock)
{
    /*
     * [ User implementation required ]
     * If HSM Crypto Driver is executed only on one CPU, there is no problem.
     * If HSM Crypto Driver is executed on multiple CPUs,
     * it is necessary to implement code that allows all CPUs to be locked in this function.
     */
    return TRUE;
}

static void HaeModule_Crypto_InterCore_UnLock(uint32 *CoreLock)
{
    /*
     * [ User implementation required ]
     * If HSM Crypto Driver is executed only on one CPU, there is no problem.
     * If HSM Crypto Driver is executed on multiple CPUs,
     * it is necessary to implement code that allows all CPUs to be unlocked in this function.
     */
}

static void HaeModule_Crypto_Core_DisableInterrupt(void)
{
    SchM_Enter_Crypto_76_HaeModule_GLOBALVAR_PROTECTION();
}

static void HaeModule_Crypto_Core_EnableInterrupt(void)
{
    SchM_Exit_Crypto_76_HaeModule_GLOBALVAR_PROTECTION();
}

boolean HaeModule_Crypto_CriticalSection_Lock(CRYPTO_LOCK_TYPE *Lock)
{
    boolean Result = FALSE;

    HaeModule_Crypto_Core_DisableInterrupt();
    if(HaeModule_Crypto_InterCore_Lock(&Lock->CoreLock) == TRUE)
    {
        Result = TRUE;
    }
    else
    {
       HaeModule_Crypto_Core_EnableInterrupt();
    }

    return Result;
}

void HaeModule_Crypto_CriticalSection_UnLock(CRYPTO_LOCK_TYPE *Lock)
{
    HaeModule_Crypto_InterCore_UnLock(&Lock->CoreLock);
    HaeModule_Crypto_Core_EnableInterrupt();
}

boolean HaeModule_Crypto_GetResource(CRYPTO_RESOUCE_TYPE *Resource)
{
    boolean Result = FALSE;

    if(HaeModule_Crypto_CriticalSection_Lock(&LockType_Resource) == TRUE)
    {
        if((Resource != NULL) && (*Resource == 0))
        {
            *Resource = 1;
            Result = TRUE;
        }

        HaeModule_Crypto_CriticalSection_UnLock(&LockType_Resource);
    }

    return Result;
}

void HaeModule_Crypto_ReleaseResource(CRYPTO_RESOUCE_TYPE *Resource)
{
    if((Resource != NULL) && (*Resource != 0))
    {
        *Resource = 0;
    }
}

void HaeModule_Crypto_Memcpy(uint8 *dst, const uint8 *src, uint32 len)
{
	while (len > 0)
	{
		*dst = *src;
		len--;
		dst++;
		src++;
	}
}

void HaeModule_Crypto_Memset(uint8 *dst, uint8 src, uint32 len)
{
	while (len > 0)
	{
		*dst = src;
		dst++;
		len--;
	}
}

#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
Std_ReturnType HaeModule_Crypto_TranslateHsmDrvResult(Std_ReturnType HsmDrvResult)
{
    Std_ReturnType Result;

    switch( HsmDrvResult )
    {
        case E_OK:
            Result = E_OK;
            break;
        case E_NOT_OK:
            Result = E_NOT_OK;
            break;
        case HSM_E_BUSY:
            Result = CRYPTO_E_BUSY;
            break;
        case HSM_E_KEY_NOT_VALID:
            Result = CRYPTO_E_KEY_NOT_VALID;
            break;
        case HSM_E_UNINIT:
        case HSM_E_WAIT:
        case HSM_E_WRONG_SEQ:
        case HSM_E_NOT_SUPPORTED:
        case HSM_E_LENGTH_NOT_VALID:
        case HSM_E_VALUE_NOT_VALID:
        default:
            Result = E_NOT_OK;
            break;
    }

    return Result;
}
#endif

#define CRYPTO_76_HAEMODULE_STOP_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"


