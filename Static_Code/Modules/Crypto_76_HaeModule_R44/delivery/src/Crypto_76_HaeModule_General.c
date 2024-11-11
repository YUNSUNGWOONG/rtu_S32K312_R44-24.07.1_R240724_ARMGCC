/*!
  @file Crypto_76_HaeModule_General.c
  @brief General API source file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#include "Crypto_76_HaeModule_Crypto.h"
#include "Crypto_76_HaeModule_General.h"
#include "Crypto_76_HaeModule_Common.h"
#include "Crypto_76_HaeModule_Key.h"
#include "Crypto_76_HaeModule_Det.h"
#include "Crypto_76_HaeModule_Job.h"


#define CRYPTO_76_HAEMODULE_START_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"
static boolean gCrypto_Init_Done = FALSE;
static DECLARE_CRYPTO_RESOUCE_TYPE(ResType_CryptoInit);
#define CRYPTO_76_HAEMODULE_STOP_RAM_VAR_INIT
#include "Crypto_76_HaeModule_MemMap.h"


#define CRYPTO_76_HAEMODULE_START_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"
/*!
  @brief Check if crypto driver is initialized.
  @return TRUE: Initialized successful \n
        FALSE: Not initialized yet or has failed in procedure of initialization.
*/
boolean HaeModule_Is_Crypto_Init(void)
{
    return gCrypto_Init_Done;
}

/*!
  @brief Initializes the Crypto Driver.
  @details Service ID[hex]: 0x00 \n
        Sync/Async: Synchronous \n
        Reentrancy: Reentrant \n
        [SWS_Crypto_00215] The Configuration pointer configPtr shall always have a null pointer value. (SWS_BSW_00050) \n
        [SWS_Crypto_00198] If during initialization of the Crypto Driver the value of a persistent key could not be loaded, \n
            the Crypto Driver shall set the state of the corresponding key to invalid. \n
        [SWS_Crypto_00045] If the initialization of the Crypto Driver fails, the Crypto shall report CRYPTO_E_INIT_FAILED to the DET.
  @param[in] configPtr      Pointer to a selected configuration structure
  @return None
*/
void HaeModule_Crypto_Init( const Crypto_76_HaeModule_ConfigType* configPtr )
{
    Std_ReturnType Result;

    /* We accept only one thread to execute a crypto driver initialization at a time */
    if(CRYPTO_GET_RESOURCE(&ResType_CryptoInit) == TRUE)
    {
        /* If crypto initialization is already done, we don't need to reinitialize any more */
        /* The HSM Driver must have already been initialized. */
        if(gCrypto_Init_Done != TRUE)
        {
            Result = HaeModule_Crypto_KeyInit();
            if(Result == E_OK)
            {
                HaeModule_Crypto_JobInit();

                gCrypto_Init_Done = TRUE;
            }

            if(Result != E_OK)
            {
                HaeModule_Det_ReportError(CRYPTO_API_INIT, CRYPTO_DET_E_INIT_FAILED);
            }
        }

        CRYPTO_RELEASE_RESOURCE(&ResType_CryptoInit);
    }
}

/*!
  @brief Returns the version information of this module.
  @details Service ID[hex]: 0x01 \n
        Sync/Async: Synchronous \n
        Reentrancy: Reentrant \n
        [SWS_Crypto_00047] If the parameter versioninfo is a null pointer and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_GetVersionInfo shall report CRYPTO_E_PARAM_POINTER to the DET.
  @param[out] versioninfo   Pointer to where to store the version information of this module.
  @return None
*/
void HaeModule_Crypto_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
    if(versioninfo != NULL)
    {
        versioninfo->vendorID           = CRYPTO_76_HAEMODULE_VENDOR_ID;
        versioninfo->moduleID           = CRYPTO_76_HAEMODULE_MODULE_ID;
        versioninfo->sw_major_version   = CRYPTO_76_HAEMODULE_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version   = CRYPTO_76_HAEMODULE_SW_MINOR_VERSION;
        versioninfo->sw_patch_version   = CRYPTO_76_HAEMODULE_SW_PATCH_VERSION;
    }
    else
    {
        HaeModule_Det_ReportError(CRYPTO_API_GETVERSIONINFO, CRYPTO_DET_E_PARAM_POINTER);
    }
}
#define CRYPTO_76_HAEMODULE_STOP_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"

