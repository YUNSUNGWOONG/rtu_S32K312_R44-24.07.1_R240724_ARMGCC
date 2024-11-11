/*!
  @file Crypto_76_HaeModule_Det.c
  @brief DET(Default Error Tracer) source file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#include "Crypto_76_HaeModule_Crypto.h"
#include "Crypto_76_HaeModule_Det.h"

#define CRYPTO_76_HAEMODULE_START_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"
/*!
  @brief Service to report development errors.
  @details Sync/Async: Not Applicable: The function never returns \n
        Reentrancy: Reentrant \n
        It may be callable in interrupt context. \n
        Since the DET can be called in normal mode or in interrupt context (from stack or integration) \n
        this has to be considered during implementation of the hook functions: \n
        It can be called in interrupt context; this should be considered when halting the system.
  @param[in] ApiId      ID of API service in which error is detected (defined in SWS of calling module)
  @param[in] ErrorId    ID of detected development error (defined in SWS of calling module).
  @return never returns a value, but has a return type for compatibility with services and hooks
*/
Std_ReturnType HaeModule_Det_ReportError( CRYPTO_DET_APIID ApiId, CRYPTO_DET_ERRORID ErrorId )
{
#if (CRYPTO_76_HAEMODULE_CRYPTODEVERRORDETECT_VALUE == TRUE)
    return Det_ReportError((uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)ApiId, (uint8)ErrorId);
#else
    return E_OK;
#endif
}

/*!
  @brief Service to report runtime errors. If a callout has been configured then this callout shall be called.
  @details Sync/Async: Synchronous \n
        Reentrancy: Reentrant \n
        It may be callable in interrupt context. \n
        Since the DET can be called in normal mode or in interrupt context (from stack or integration) \n
        this has to be considered during implementation of the hook functions: \n
        It can be called in interrupt context; this should be considered when halting the system.
  @param[in] ApiId      ID of API service in which error is detected (defined in SWS of calling module)
  @param[in] ErrorId    ID of detected development error (defined in SWS of calling module).
  @return returns always E_OK (is required for services)
*/
Std_ReturnType HaeModule_Det_ReportRuntimeError( CRYPTO_DET_APIID ApiId, CRYPTO_DET_RUNTIME_ERRORID ErrorId )
{
#if (CRYPTO_76_HAEMODULE_CRYPTODEVERRORDETECT_VALUE == TRUE)
    return Det_ReportRuntimeError((uint16)CRYPTO_MODULE_ID, (uint8)CRYPTO_INSTANCE_ID, (uint8)ApiId, (uint8)ErrorId);
#else
    return E_OK;
#endif
}
#define CRYPTO_76_HAEMODULE_STOP_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"




