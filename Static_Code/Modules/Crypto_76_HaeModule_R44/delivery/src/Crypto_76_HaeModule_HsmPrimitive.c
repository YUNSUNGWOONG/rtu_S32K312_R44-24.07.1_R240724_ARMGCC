#include "Crypto_76_HaeModule_HsmPrimitive.h"
#include "Crypto_76_HaeModule_Common.h"
#include "Crypto_76_HaeModule_Job.h"
#include "Crypto_76_HaeModule_Key.h"
#include "Crypto_76_HaeModule_Det.h"
#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
#include "CryptoService_Def.h"
#include "CryptoService_Hash.h"
#include "CryptoService_Aes.h"
#include "CryptoService_RsaPkcs1.h"
#include "CryptoService_Ecc.h"
#include "SecurityApp_Rng.h"
#include "SecurityApp_KeyManagement.h"
#include "CryptoService_Pbkdf2.h"
#include "CryptoService_RsaPkcs3.h"
#include "CryptoService_Ecc.h"
#endif

#define WAIT_BUSY_TIMEOUT 300000000 // 15sec
#define WAIT_RESP_TIMEOUT 300000000 // 15sec

#define CRYPTO_76_HAEMODULE_START_RAM_VAR_CLEARED
#include "Crypto_76_HaeModule_MemMap.h"
#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
static HaeHsmPrimitiveData gHaeHsm_PrimitiveData;
#endif
#define CRYPTO_76_HAEMODULE_STOP_RAM_VAR_CLEARED
#include "Crypto_76_HaeModule_MemMap.h"


#define CRYPTO_76_HAEMODULE_START_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"
#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
void HaeHsm_Primtive_Init( CryptoDriverObject *Object )
{
    Object->PrimitiveData = (CryptoPrimitiveData *)&gHaeHsm_PrimitiveData;
}

static HaeHsmPrimitiveData* getPrimitiveData(CryptoPrimitiveData *PrimitiveData) {
    return &gHaeHsm_PrimitiveData;
}
#endif

/* The function below is to use the feature to execute each mode (Start/Update/Finish) multiple times. */
#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
/* [Caution] This function should only be called externally. */
/* This is a function to inform the outside of the current mode and state. */
void HaeHsm_Primitive_GetState(uint32 *mode, uint32 *state)
{
    *mode  = gHaeHsm_PrimitiveData.mode;
    *state = gHaeHsm_PrimitiveData.state;
}

/* [Caution] This function should only be called externally. */
/* This is a function that sets the mode and state value to be executed externally. */
void HaeHsm_Primitive_SetState(uint32 mode, uint32 state)
{
    gHaeHsm_PrimitiveData.mode  = mode;
    gHaeHsm_PrimitiveData.state = state;
}

/* This is a function to get the current mode and state. */
static void HaeHsm_PrimitiveState_Get(uint32 *mode, uint32 *state)
{
    *mode  = gHaeHsm_PrimitiveData.mode;
    *state = gHaeHsm_PrimitiveData.state;
}
/* This is a function to change the state of the current mode. */
static void HaeHsm_PrimitiveState_Set(uint32 state)
{
    gHaeHsm_PrimitiveData.state = state;
}
/* This is a function to end the current mode. 
   Clears the current mode bit and sets the state to HAEMODULE_PRIMITIVESTATE_END to indicate that the current mode has ended.*/
static void HaeHsm_PrimitiveState_End(uint32 mode)
{
    gHaeHsm_PrimitiveData.mode  &= ~mode;
    gHaeHsm_PrimitiveData.state = (uint32)HAEMODULE_PRIMITIVESTATE_END;
}
#endif

#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
Std_ReturnType HaeHsm_Primtive_CancelJob( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
    return E_OK;
}
#endif

#ifdef HAEMODULE_CRYPTOOBJECT_HAEHSM_SUPPORT
static Std_ReturnType HaeHsm_Primitive_GetjobRedirectionInfo(const Crypto_JobRedirectionInfoType *jobRedirectionInfoRef, uint8  redirectionConfig, uint32 *KeyId, uint32 *KeyElementId)
{
    Std_ReturnType Result = E_OK;

    if(((redirectionConfig & (uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT) != 0)
        && ((jobRedirectionInfoRef->redirectionConfig & (uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT) != 0))
    {
        *KeyId          = jobRedirectionInfoRef->inputKeyId;
        *KeyElementId   = jobRedirectionInfoRef->inputKeyElementId;
    }
    else if(((redirectionConfig & (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT) != 0)
        && ((jobRedirectionInfoRef->redirectionConfig & (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT) != 0))
    {
        *KeyId          = jobRedirectionInfoRef->secondaryInputKeyId;
        *KeyElementId   = jobRedirectionInfoRef->secondaryInputKeyElementId;
    }
    else if(((redirectionConfig & (uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT) != 0)
        && ((jobRedirectionInfoRef->redirectionConfig & (uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT) != 0))
    {
        *KeyId          = jobRedirectionInfoRef->tertiaryInputKeyId;
        *KeyElementId   = jobRedirectionInfoRef->tertiaryInputKeyElementId;
    }
    else if(((redirectionConfig & (uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT) != 0)
        && ((jobRedirectionInfoRef->redirectionConfig & (uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT) != 0))
    {
        *KeyId          = jobRedirectionInfoRef->outputKeyId;
        *KeyElementId   = jobRedirectionInfoRef->outputKeyElementId;
    }
    else if(((redirectionConfig & (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT) != 0)
        && ((jobRedirectionInfoRef->redirectionConfig & (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT) != 0))
    {
        *KeyId          = jobRedirectionInfoRef->secondaryOutputKeyId;
        *KeyElementId   = jobRedirectionInfoRef->secondaryOutputKeyElementId;
    }
    else
    {
        Result = E_NOT_OK;
    }

    return Result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_SHA160_SUPPORT
Std_ReturnType HaeHsm_Primitive_Sha160( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint32 remainDataLength = job->jobPrimitiveInputOutput.inputLength;
    uint32 maxTxLen = 1020;
    uint32 txLen = 0;
    uint32 i = 0;
    uint8 digest[SHA160_DIGEST_SIZE];
    uint32 digestLength = SHA160_DIGEST_SIZE;
    uint8* outputPtr;
    uint32* outputLengthPtr;
    uint32 KeyId;
    uint32 KeyElementId;
    volatile uint32 timeout = 0;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HSM_DRIVER_RETURN(HSM_Sha160Start(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
    }
    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength == 0)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainDataLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainDataLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainDataLength;
                }

                HsmDrvResult = HSM_Sha160Update(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                remainDataLength -= txLen;
                i+= txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if(job->jobRedirectionInfoRef != NULL)
        {
            outputPtr = digest;
            outputLengthPtr = &digestLength;
        }
        else
        {
            outputPtr = job->jobPrimitiveInputOutput.outputPtr;
            outputLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
        }

        if ((outputPtr == NULL) || (outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*outputLengthPtr < (uint32)SHA160_DIGEST_SIZE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_Sha160Finish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, outputPtr));
            if(result == E_OK)
            {
                *outputLengthPtr = (uint32)SHA160_DIGEST_SIZE;

                if(job->jobRedirectionInfoRef != NULL)
                {
                    result = HaeHsm_Primitive_GetjobRedirectionInfo(job->jobRedirectionInfoRef,
                                ((uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT),
                                &KeyId, &KeyElementId);
                    if(result == E_OK)
                    {
                        result = HaeModule_Crypto_KeyElementSet(KeyId, KeyElementId, outputPtr, *outputLengthPtr);
                    }
                }
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_SHA256_SUPPORT
Std_ReturnType HaeHsm_Primitive_Sha256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint32 remainDataLength = job->jobPrimitiveInputOutput.inputLength;
    uint32 maxTxLen = 1020;
    uint32 txLen = 0;
    uint32 i = 0;
    uint8 digest[SHA256_DIGEST_SIZE];
    uint32 digestLength = SHA256_DIGEST_SIZE;
    uint8* outputPtr;
    uint32* outputLengthPtr;
    uint32 KeyId;
    uint32 KeyElementId;
    volatile uint32 timeout = 0;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HSM_DRIVER_RETURN(HSM_Sha256Start(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength == 0)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainDataLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainDataLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainDataLength;
                }

                HsmDrvResult = HSM_Sha256Update(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                remainDataLength -= txLen;
                i += txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if(job->jobRedirectionInfoRef != NULL)
        {
            outputPtr = digest;
            outputLengthPtr = &digestLength;
        }
        else
        {
            outputPtr = job->jobPrimitiveInputOutput.outputPtr;
            outputLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
        }

        if ((outputPtr == NULL) || (outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*outputLengthPtr < (uint32)SHA256_DIGEST_SIZE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_Sha256Finish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, outputPtr));
            if(result == E_OK)
            {
                *outputLengthPtr = (uint32)SHA256_DIGEST_SIZE;

                if(job->jobRedirectionInfoRef != NULL)
                {
                    result = HaeHsm_Primitive_GetjobRedirectionInfo(job->jobRedirectionInfoRef,
                                ((uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT),
                                &KeyId, &KeyElementId);
                    if(result == E_OK)
                    {
                        result = HaeModule_Crypto_KeyElementSet(KeyId, KeyElementId, outputPtr, *outputLengthPtr);
                    }
                }
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif


#ifdef HAEHSM_PRIMITIVE_SHA512_SUPPORT
Std_ReturnType HaeHsm_Primitive_Sha512( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint32 remainDataLength = job->jobPrimitiveInputOutput.inputLength;
    uint32 maxTxLen = 1024;
    uint32 txLen = 0;
    uint32 i = 0;
    uint8 digest[SHA512_DIGEST_SIZE];
    uint32 digestLength = SHA512_DIGEST_SIZE;
    uint8* outputPtr;
    uint32* outputLengthPtr;
    uint32 KeyId;
    uint32 KeyElementId;
    volatile uint32 timeout = 0;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HSM_DRIVER_RETURN(HSM_Sha512Start(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength == 0)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainDataLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainDataLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainDataLength;
                }

                HsmDrvResult = HSM_Sha512Update(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                remainDataLength -= txLen;
                i += txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if(job->jobRedirectionInfoRef != NULL)
        {
            outputPtr = digest;
            outputLengthPtr = &digestLength;
        }
        else
        {
            outputPtr = job->jobPrimitiveInputOutput.outputPtr;
            outputLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
        }

        if ((outputPtr == NULL) || (outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*outputLengthPtr < (uint32)SHA512_DIGEST_SIZE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_Sha512Finish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, outputPtr));
            if(result == E_OK)
            {
                *outputLengthPtr = (uint32)SHA512_DIGEST_SIZE;

                if(job->jobRedirectionInfoRef != NULL)
                {
                    result = HaeHsm_Primitive_GetjobRedirectionInfo(job->jobRedirectionInfoRef,
                                ((uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT),
                                &KeyId, &KeyElementId);
                    if(result == E_OK)
                    {
                        result = HaeModule_Crypto_KeyElementSet(KeyId, KeyElementId, outputPtr, *outputLengthPtr);
                    }
                }
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_SHA512_224_SUPPORT
Std_ReturnType HaeHsm_Primitive_Sha512_224( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint32 remainDataLength = job->jobPrimitiveInputOutput.inputLength;
    uint32 maxTxLen = 1024;
    uint32 txLen = 0;
    uint32 i = 0;
    uint8 digest[SHA512_224_DIGEST_SIZE];
    uint32 digestLength = SHA512_224_DIGEST_SIZE;
    uint8* outputPtr;
    uint32* outputLengthPtr;
    uint32 KeyId;
    uint32 KeyElementId;
    volatile uint32 timeout = 0;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HSM_DRIVER_RETURN(HSM_Sha512_224Start(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength == 0)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainDataLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainDataLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainDataLength;
                }

                HsmDrvResult = HSM_Sha512_224Update(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                remainDataLength -= txLen;
                i += txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if(job->jobRedirectionInfoRef != NULL)
        {
            outputPtr = digest;
            outputLengthPtr = &digestLength;
        }
        else
        {
            outputPtr = job->jobPrimitiveInputOutput.outputPtr;
            outputLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
        }

        if ((outputPtr == NULL) || (outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*outputLengthPtr < (uint32)SHA512_224_DIGEST_SIZE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_Sha512_224Finish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, outputPtr));
            if(result == E_OK)
            {
                *outputLengthPtr = (uint32)SHA512_224_DIGEST_SIZE;

                if(job->jobRedirectionInfoRef != NULL)
                {
                    result = HaeHsm_Primitive_GetjobRedirectionInfo(job->jobRedirectionInfoRef,
                                ((uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT),
                                &KeyId, &KeyElementId);
                    if(result == E_OK)
                    {
                        result = HaeModule_Crypto_KeyElementSet(KeyId, KeyElementId, outputPtr, *outputLengthPtr);
                    }
                }
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_SHA512_256_SUPPORT
Std_ReturnType HaeHsm_Primitive_Sha512_256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint32 remainDataLength = job->jobPrimitiveInputOutput.inputLength;
    uint32 maxTxLen = 1024;
    uint32 txLen = 0;
    uint32 i = 0;
    uint8 digest[SHA512_256_DIGEST_SIZE];
    uint32 digestLength = SHA512_256_DIGEST_SIZE;
    uint8* outputPtr;
    uint32* outputLengthPtr;
    uint32 KeyId;
    uint32 KeyElementId;
    volatile uint32 timeout = 0;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HSM_DRIVER_RETURN(HSM_Sha512_256Start(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength == 0)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainDataLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainDataLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainDataLength;
                }

                HsmDrvResult = HSM_Sha512_256Update(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                remainDataLength -= txLen;
                i += txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if(job->jobRedirectionInfoRef != NULL)
        {
            outputPtr = digest;
            outputLengthPtr = &digestLength;
        }
        else
        {
            outputPtr = job->jobPrimitiveInputOutput.outputPtr;
            outputLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
        }

        if ((outputPtr == NULL) || (outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*outputLengthPtr < (uint32)SHA512_256_DIGEST_SIZE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_Sha512_256Finish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, outputPtr));
            if(result == E_OK)
            {
                *outputLengthPtr = (uint32)SHA512_256_DIGEST_SIZE;

                if(job->jobRedirectionInfoRef != NULL)
                {
                    result = HaeHsm_Primitive_GetjobRedirectionInfo(job->jobRedirectionInfoRef,
                                ((uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT),
                                &KeyId, &KeyElementId);
                    if(result == E_OK)
                    {
                        result = HaeModule_Crypto_KeyElementSet(KeyId, KeyElementId, outputPtr, *outputLengthPtr);
                    }
                }
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_SHAKE256_SUPPORT
Std_ReturnType HaeHsm_Primitive_Shake256( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint32 remainDataLength = job->jobPrimitiveInputOutput.inputLength;
    uint32 maxTxLen = 1024;
    uint32 txLen = 0;
    uint32 i = 0;
    uint8 digest[SHA256_DIGEST_SIZE];
    uint32 digestLength = SHA256_DIGEST_SIZE;
    uint8* outputPtr;
    uint32* outputLengthPtr;
    uint32 KeyId;
    uint32 KeyElementId;
    volatile uint32 timeout = 0;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HSM_DRIVER_RETURN(HSM_Shake256Start(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength == 0)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainDataLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainDataLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainDataLength;
                }

                HsmDrvResult = HSM_Shake256Update(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                remainDataLength -= txLen;
                i += txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if(job->jobRedirectionInfoRef != NULL)
        {
            outputPtr = digest;
            outputLengthPtr = &digestLength;
        }
        else
        {
            outputPtr = job->jobPrimitiveInputOutput.outputPtr;
            outputLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
        }

        if ((outputPtr == NULL) || (outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*outputLengthPtr < (uint32)SHA256_DIGEST_SIZE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_Shake256Finish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, outputPtr));
            if(result == E_OK)
            {
                *outputLengthPtr = (uint32)SHA256_DIGEST_SIZE;

                if(job->jobRedirectionInfoRef != NULL)
                {
                    result = HaeHsm_Primitive_GetjobRedirectionInfo(job->jobRedirectionInfoRef,
                                ((uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT),
                                &KeyId, &KeyElementId);
                    if(result == E_OK)
                    {
                        result = HaeModule_Crypto_KeyElementSet(KeyId, KeyElementId, outputPtr, *outputLengthPtr);
                    }
                }
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_AESCMAC_GEN_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesCmac_Gen( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint32 remainDataLength = job->jobPrimitiveInputOutput.inputLength;
    uint32 maxTxLen = HSM_GetMaxTranSizeByte();
    uint32 txLen = 0;
    uint32 i = 0;
    uint8 cmac[HSM_AES128_CMAC_LEN];
    uint32 cmacLength = HSM_AES128_CMAC_LEN;
    uint8* outputPtr;
    uint32* outputLengthPtr;
    uint16 keyNum;
    uint32 KeyId;
    uint32 KeyElementId;
    volatile uint32 timeout = 0;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_MAC_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_AesCmacStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum, remainDataLength));
        }
    }
    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength == 0)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainDataLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainDataLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainDataLength;
                }

                HsmDrvResult = HSM_AesCmacUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                remainDataLength -= txLen;
                i += txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if(job->jobRedirectionInfoRef != NULL)
        {
            outputPtr = cmac;
            outputLengthPtr = &cmacLength;
        }
        else
        {
            outputPtr = job->jobPrimitiveInputOutput.outputPtr;
            outputLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
        }

        if ((outputPtr == NULL) || (outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*outputLengthPtr < (uint32)HSM_AES128_CMAC_LEN)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_AesCmacFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, outputPtr));
            if(result == E_OK)
            {
                *outputLengthPtr = (uint32)HSM_AES128_CMAC_LEN;

                if(job->jobRedirectionInfoRef != NULL)
                {
                    result = HaeHsm_Primitive_GetjobRedirectionInfo(job->jobRedirectionInfoRef,
                                ((uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT),
                                &KeyId, &KeyElementId);
                    if(result == E_OK)
                    {
                        result = HaeModule_Crypto_KeyElementSet(KeyId, KeyElementId, outputPtr, *outputLengthPtr);
                    }
                }
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_HMACSHA256_GEN_SUPPORT
Std_ReturnType HaeHsm_Primitive_HmacSha256_Gen( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint32 remainDataLength = job->jobPrimitiveInputOutput.inputLength;
    uint32 maxTxLen = 1020;
    uint32 txLen = 0;
    uint32 i = 0;
    uint8 digest[SHA256_DIGEST_SIZE];
    uint32 digestLength = SHA256_DIGEST_SIZE;
    uint8* outputPtr;
    uint32* outputLengthPtr;
    uint16 keyNum;
    uint32 KeyId;
    uint32 KeyElementId;
    volatile uint32 timeout = 0;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_MAC_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_HmacSha256Start(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }
    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength == 0)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainDataLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainDataLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainDataLength;
                }

                HsmDrvResult = HSM_HmacSha256Update(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                remainDataLength -= txLen;
                i += txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if(job->jobRedirectionInfoRef != NULL)
        {
            outputPtr = digest;
            outputLengthPtr = &digestLength;
        }
        else
        {
            outputPtr = job->jobPrimitiveInputOutput.outputPtr;
            outputLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
        }

        if ((outputPtr == NULL) || (outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*outputLengthPtr < (uint32)SHA256_DIGEST_SIZE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_HmacSha256Finish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, outputPtr));
            if(result == E_OK)
            {
                *outputLengthPtr = (uint32)SHA256_DIGEST_SIZE;

                if(job->jobRedirectionInfoRef != NULL)
                {
                    result = HaeHsm_Primitive_GetjobRedirectionInfo(job->jobRedirectionInfoRef,
                                ((uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT | (uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT),
                                &KeyId, &KeyElementId);
                    if(result == E_OK)
                    {
                        result = HaeModule_Crypto_KeyElementSet(KeyId, KeyElementId, outputPtr, *outputLengthPtr);
                    }
                }
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_AESCMAC_VERIFY_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesCmac_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint32 remainDataLength = job->jobPrimitiveInputOutput.inputLength;
    uint32 maxTxLen = HSM_GetMaxTranSizeByte();
    uint32 txLen = 0;
    uint32 i = 0;
    uint8 cmac[HSM_AES128_CMAC_LEN];
    uint16 keyNum;
    volatile uint32 timeout = 0;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_MAC_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_AesCmacStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum, remainDataLength));
        }
    }
    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength == 0)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainDataLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainDataLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainDataLength;
                }

                HsmDrvResult = HSM_AesCmacUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                remainDataLength -= txLen;
                i += txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.verifyPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.secondaryInputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.secondaryInputLength != HSM_AES128_CMAC_LEN)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_AesCmacFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, cmac));
            if(result == E_OK)
            {
                for (i = 0; i < HSM_AES128_CMAC_LEN; i++)
                {
                    if (cmac[i] != job->jobPrimitiveInputOutput.secondaryInputPtr[i])
                    {
                        result = E_NOT_OK;
                        break;
                    }
                }

                if (result == E_OK)
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_OK;
                    result = E_OK;
                }
                else
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
                    result = E_OK;
                }
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_HMACSHA256_VERIFY_SUPPORT
Std_ReturnType HaeHsm_Primitive_HmacSha256_Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint32 remainDataLength = job->jobPrimitiveInputOutput.inputLength;
    uint32 maxTxLen = 1020;
    uint32 txLen = 0;
    uint32 i = 0;
    uint8 hmac[SHA256_DIGEST_SIZE];
    uint16 keyNum;
    volatile uint32 timeout = 0;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_MAC_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_HmacSha256Start(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }
    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength == 0)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainDataLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainDataLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainDataLength;
                }

                HsmDrvResult = HSM_HmacSha256Update(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                remainDataLength -= txLen;
                i += txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.verifyPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.secondaryInputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.secondaryInputLength != SHA256_DIGEST_SIZE)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_HmacSha256Finish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, hmac));
            if(result == E_OK)
            {
                for (i = 0; i < SHA256_DIGEST_SIZE; i++)
                {
                    if (hmac[i] != job->jobPrimitiveInputOutput.secondaryInputPtr[i])
                    {
                        result = E_NOT_OK;
                        break;
                    }
                }

                if (result == E_OK)
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_OK;
                    result = E_OK;
                }
                else
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
                    result = E_OK;
                }
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_AESENCECB_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesEncECB( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode;
    uint32 state;
    HaeHsmPrimitiveData *HsmPrimitiveData = getPrimitiveData(PrimitiveData);
    uint16 keyNum;
    uint8* cipherTextPtr = job->jobPrimitiveInputOutput.outputPtr;
    uint32* cipherLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
    AES_MODE aesMode = HSM_AES_ECB_MODE;
    CryptoKeyElement* Element;
    
    HaeHsm_PrimitiveState_Get(&mode, &state);

    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        if (state == (uint32)HAEMODULE_PRIMITIVESTATE_INIT)
        {
            HaeModule_Crypto_Memset((uint8 *)& HsmPrimitiveData->var.start, 0, (uint32)sizeof(HaeHsmPrimitiveVariable_Start));
            HsmPrimitiveData->var.start.timeout = 0;

            result = E_OK;
            HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_START);
        }
        else if (state == (uint32)HAEMODULE_PRIMITIVESTATE_START)
        {
            if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_128_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES_ECB_MODE;
            }
            #ifdef HAEHSM_PRIMITIVE_AES256_SUPPORT
            else if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES256_ECB_MODE;
            }
            #endif
            else
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }

            if(result == E_OK)
            {
                Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
                if(Element == NULL)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else
                {
                    keyNum = Element->CryptoKeyElementHsmKeyIndex;
                    HsmDrvResult = HSM_AesEncStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, aesMode, keyNum, NULL);
                    if (HsmDrvResult == E_OK)
                    {
                        /* When all states in the mode are finished, we call HaeHsm_PrimitiveState_End function to end directly. */
                        result = E_OK;
                        HaeHsm_PrimitiveState_End((uint32)CRYPTO_OPERATIONMODE_START);
                    }
                    else if (HsmDrvResult == HSM_E_BUSY)
                    {
                        HsmPrimitiveData->var.start.timeout++;
                        if (HsmPrimitiveData->var.start.timeout < WAIT_BUSY_TIMEOUT)
                        {
                            /* Set to retry the current mode state. */
                            result = E_OK;
                            HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_START);
                        }
                        else
                        {
                            result = HSM_DRIVER_RETURN(HsmDrvResult);
                        }
                    }
                    else
                    {
                        result = HSM_DRIVER_RETURN(HsmDrvResult);
                    }
                }
            }
            else
            {
                result = E_NOT_OK;
            }
        }
        else
        {
            result = E_NOT_OK;
        }

        /* If the return value is an error, the mode ends. */
        if(result != E_OK)
        {
            HaeHsm_PrimitiveState_End((uint32)CRYPTO_OPERATIONMODE_START);
        }
    }
    else if((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0)
    {
        if(state == (uint32)HAEMODULE_PRIMITIVESTATE_INIT)
        {
            if (job->jobPrimitiveInputOutput.inputPtr == NULL)
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
                result = E_NOT_OK;
            }
            else if ((cipherTextPtr == NULL) || (cipherLengthPtr == NULL))
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
                result = E_NOT_OK;
            }
            else if ((job->jobPrimitiveInputOutput.inputLength == 0) || (*cipherLengthPtr == 0))
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }
            else if (job->jobPrimitiveInputOutput.inputLength > *cipherLengthPtr)
            {
                HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
                result = CRYPTO_E_SMALL_BUFFER;
            }
            else
            {
                HsmPrimitiveData->var.update.remainDataLen  = job->jobPrimitiveInputOutput.inputLength;
                HsmPrimitiveData->var.update.maxTxLen       = HSM_GetMaxTranSizeByte();
                HsmPrimitiveData->var.update.txIndex        = 0;
                HsmPrimitiveData->var.update.txLen          = 0;
                HsmPrimitiveData->var.update.timeout        = 0;

                result = E_OK;
                HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_UPDATE);
            }
        }
        else if(state == (uint32)HAEMODULE_PRIMITIVESTATE_UPDATE)
        {
            if (HsmPrimitiveData->var.update.remainDataLen > 0)
            {
                if (HsmPrimitiveData->var.update.remainDataLen > HsmPrimitiveData->var.update.maxTxLen)
                {
                    HsmPrimitiveData->var.update.txLen = HsmPrimitiveData->var.update.maxTxLen;
                }
                else
                {
                    HsmPrimitiveData->var.update.txLen = HsmPrimitiveData->var.update.remainDataLen;
                }

                HsmDrvResult = HSM_AesEncUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx,
                                            &job->jobPrimitiveInputOutput.inputPtr[HsmPrimitiveData->var.update.txIndex], 
                                            HsmPrimitiveData->var.update.txLen);
                if(HsmDrvResult == E_OK)
                {
                    HsmPrimitiveData->var.update.timeout = 0;
                    result = E_OK;
                    HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_UPDATE_WAITRESP);
                }
                else if(HsmDrvResult == HSM_E_BUSY)
                {
                    HsmPrimitiveData->var.update.timeout++;
                    if (HsmPrimitiveData->var.update.timeout < WAIT_BUSY_TIMEOUT)
                    {
                        /* Set to retry the current mode state. */
                        result = E_OK;
                        HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_UPDATE);
                    }
                    else
                    {
                        HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        result = HSM_DRIVER_RETURN(HsmDrvResult);
                    }
                }
                else
                {
                    HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                    result = HSM_DRIVER_RETURN(HsmDrvResult);
                }
            }
            else
            {
                 /* When all states in the mode are finished, we call HaeHsm_PrimitiveState_End function to end directly. */
                result = E_OK;
                HaeHsm_PrimitiveState_End((uint32)CRYPTO_OPERATIONMODE_UPDATE);
            }
        }
        else if(state == (uint32)HAEMODULE_PRIMITIVESTATE_UPDATE_WAITRESP)
        {
            HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
            if (HsmDrvResult == E_OK)
            {
                result = HSM_DRIVER_RETURN(HsmDrvResult);
                HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_UPDATE_READRXBUFF);
            }
            else if (HsmDrvResult == HSM_E_WAIT)
            {
                HsmPrimitiveData->var.update.timeout++;
                if (HsmPrimitiveData->var.update.timeout < WAIT_RESP_TIMEOUT)
                {
                    /* Set to retry the current mode state. */
                    result = E_OK;
                    HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_UPDATE_WAITRESP);
                }
                else
                {
                    HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                    result = HSM_DRIVER_RETURN(HsmDrvResult);
                }
            }
            else
            {
                HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }
        }
        else if(state == (uint32)HAEMODULE_PRIMITIVESTATE_UPDATE_READRXBUFF)
        {
            HsmDrvResult = HSM_ReadRxBuff((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId, 
                                    HsmPrimitiveData->var.update.txLen, 
                                    &cipherTextPtr[HsmPrimitiveData->var.update.txIndex]);
            if(HsmDrvResult == E_OK)
            {
                HsmPrimitiveData->var.update.remainDataLen -= HsmPrimitiveData->var.update.txLen;
                HsmPrimitiveData->var.update.txIndex += HsmPrimitiveData->var.update.txLen;
                *cipherLengthPtr = HsmPrimitiveData->var.update.txIndex;

                HsmPrimitiveData->var.update.timeout = 0;
                result = E_OK;
                HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_UPDATE);
            }
            else
            {
                HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }            
        }
        else
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
            result = E_NOT_OK;
        }

        /* If the return value is an error, the mode ends. */
        if(result != E_OK)
        {
            HaeHsm_PrimitiveState_End((uint32)CRYPTO_OPERATIONMODE_UPDATE);
        }
    }
    else if((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0)
    {
        if(state == (uint32)HAEMODULE_PRIMITIVESTATE_INIT)
        {
            HsmPrimitiveData->var.finish.timeout = 0;
            result = E_OK;
            HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_FINISH);
        } 
        else if(state == (uint32)HAEMODULE_PRIMITIVESTATE_FINISH)
        {
            HsmDrvResult = HSM_AesEncFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx);
            if (HsmDrvResult == E_OK)
            {
                /* When all states in the mode are finished, we call HaeHsm_PrimitiveState_End function to end directly. */
                result = E_OK;
                HaeHsm_PrimitiveState_End((uint32)CRYPTO_OPERATIONMODE_FINISH);
            }
            else if (HsmDrvResult == HSM_E_BUSY)
            {
                HsmPrimitiveData->var.finish.timeout++;
                if (HsmPrimitiveData->var.finish.timeout < WAIT_BUSY_TIMEOUT)
                {
                    /* Set to retry the current mode state. */
                    result = E_OK;
                    HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_FINISH);
                }
                else
                {
                    result = HSM_DRIVER_RETURN(HsmDrvResult);
                }
            }
            else
            {
                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }
        }
        else
        {
            result = E_NOT_OK;
        }

        /* If the return value is an error, the mode ends. */
        if(result != E_OK)
        {
            HaeHsm_PrimitiveState_End((uint32)CRYPTO_OPERATIONMODE_FINISH);
        }
    }
    else
    {
        result = E_NOT_OK;
        HaeHsm_PrimitiveState_End(mode);
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_AESENCCBC_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesEncCBC( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    uint32 remainPlainTextLength = job->jobPrimitiveInputOutput.inputLength;
    uint8* cipherTextPtr = job->jobPrimitiveInputOutput.outputPtr;
    uint32* cipherLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
    uint8 ivPtr[16];
    uint32 ivPtrLength = 16;
    uint32 txLen = 0;
    uint32 i = 0;
    volatile uint32 timeout = 0;
    uint32 maxTxLen = HSM_GetMaxTranSizeByte();
    AES_MODE aesMode = HSM_AES_CBC_MODE;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HaeModule_Crypto_KeyElementGet(job->cryptoKeyId, CRYPTO_KE_CIPHER_IV, ivPtr, &ivPtrLength);
        if (result == E_OK)
        {
            if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_128_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES_CBC_MODE;
            }
            #ifdef HAEHSM_PRIMITIVE_AES256_SUPPORT
            else if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES256_CBC_MODE;
            }
            #endif
            else
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }

            if(result == E_OK)
            {
                Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
                if(Element == NULL)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else
                {
                    keyNum = Element->CryptoKeyElementHsmKeyIndex;
                    result = HSM_DRIVER_RETURN(HSM_AesEncStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, aesMode, keyNum, ivPtr));
                }
            }
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((cipherTextPtr == NULL) || (cipherLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((remainPlainTextLength == 0) || (*cipherLengthPtr == 0))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (remainPlainTextLength > *cipherLengthPtr)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainPlainTextLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainPlainTextLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainPlainTextLength;
                }

                HsmDrvResult = HSM_AesEncUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);

                    if (HsmDrvResult == E_OK)
                    {
                        HsmDrvResult = HSM_ReadRxBuff((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId, txLen, &cipherTextPtr[i]);
                    }
                }

                remainPlainTextLength -= txLen;
                i += txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
            *cipherLengthPtr = i;
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        result = HSM_DRIVER_RETURN(HSM_AesEncFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_AESENCCTR_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesEncCTR( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    uint32 remainPlainTextLength = job->jobPrimitiveInputOutput.inputLength;
    uint8* cipherTextPtr = job->jobPrimitiveInputOutput.outputPtr;
    uint32* cipherLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
    uint8 ivPtr[16];
    uint32 ivPtrLength = 16;
    uint32 txLen = 0;
    uint32 i = 0;
    volatile uint32 timeout = 0;
    uint32 maxTxLen = HSM_GetMaxTranSizeByte();
    AES_MODE aesMode = HSM_AES_CTR_MODE;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HaeModule_Crypto_KeyElementGet(job->cryptoKeyId, CRYPTO_KE_CIPHER_IV, ivPtr, &ivPtrLength);
        if (result == E_OK)
        {
            if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_128_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES_CTR_MODE;
            }
            #ifdef HAEHSM_PRIMITIVE_AES256_SUPPORT
            else if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES256_CTR_MODE;
            }
            #endif
            else
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }

            if(result == E_OK)
            {
                Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
                if(Element == NULL)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else
                {
                    keyNum = Element->CryptoKeyElementHsmKeyIndex;
                    result = HSM_DRIVER_RETURN(HSM_AesEncStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, aesMode, keyNum, ivPtr));
                }
            }
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((cipherTextPtr == NULL) || (cipherLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((remainPlainTextLength == 0) || (*cipherLengthPtr == 0))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (remainPlainTextLength > *cipherLengthPtr)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainPlainTextLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainPlainTextLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainPlainTextLength;
                }

                HsmDrvResult = HSM_AesEncUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);

                    if (HsmDrvResult == E_OK)
                    {
                        HsmDrvResult = HSM_ReadRxBuff((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId, txLen, &cipherTextPtr[i]);
                    }
                }

                remainPlainTextLength -= txLen;
                i+= txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
            *cipherLengthPtr = i;
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        result = HSM_DRIVER_RETURN(HSM_AesEncFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_AESENCOFB_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesEncOFB( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    uint32 remainPlainTextLength = job->jobPrimitiveInputOutput.inputLength;
    uint8* cipherTextPtr = job->jobPrimitiveInputOutput.outputPtr;
    uint32* cipherLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
    uint8 ivPtr[16];
    uint32 ivPtrLength = 16;
    uint32 txLen = 0;
    uint32 i = 0;
    volatile uint32 timeout = 0;
    uint32 maxTxLen = HSM_GetMaxTranSizeByte();
    AES_MODE aesMode = HSM_AES_OFB_MODE;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HaeModule_Crypto_KeyElementGet(job->cryptoKeyId, CRYPTO_KE_CIPHER_IV, ivPtr, &ivPtrLength);
        if (result == E_OK)
        {
            if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_128_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES_OFB_MODE;
            }
            #ifdef HAEHSM_PRIMITIVE_AES256_SUPPORT
            else if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES256_OFB_MODE;
            }
            #endif
            else
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }

            if(result == E_OK)
            {
                Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
                if(Element == NULL)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else
                {
                    keyNum = Element->CryptoKeyElementHsmKeyIndex;
                    result = HSM_DRIVER_RETURN(HSM_AesEncStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, aesMode, keyNum, ivPtr));
                }
            }
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((cipherTextPtr == NULL) || (cipherLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((remainPlainTextLength == 0) || (*cipherLengthPtr == 0))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (remainPlainTextLength > *cipherLengthPtr)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainPlainTextLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainPlainTextLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainPlainTextLength;
                }

                HsmDrvResult = HSM_AesEncUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);

                    if (HsmDrvResult == E_OK)
                    {
                        HsmDrvResult = HSM_ReadRxBuff((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId, txLen, &cipherTextPtr[i]);
                    }
                }

                remainPlainTextLength -= txLen;
                i+= txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
            *cipherLengthPtr = i;
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        result = HSM_DRIVER_RETURN(HSM_AesEncFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_AESENCGCM_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesEncGCM( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    const uint8* plainTextPtr;
    uint32 plainTextLength;
    const uint8* aadPtr;
    uint32 aadLen;
    uint8* cipherTextPtr;
    uint32* cipherLengthPtr;
    uint8* tagPtr;
    uint32* tagLenPtr;
    uint8 ivPtr[16];
    uint32 ivPtrLength = 16;
    volatile uint32 timeout = 0;
    AES_MODE aesMode;
    CryptoKeyElement* Element;
    /*
     * GCM output format : cipher data + tag
     * When the HSM finishes the Update service, it executes the HSM_ReadRxBuff function to obtain the cipher data and tags together.
     * 1. The maximum size of plaintext data is 128 bytes.
     * 2. Tag size is 16 bytes.
     */
    uint8 aesOutput[256];

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HaeModule_Crypto_KeyElementGet(job->cryptoKeyId, CRYPTO_KE_CIPHER_IV, ivPtr, &ivPtrLength);
        if (result == E_OK)
        {
            if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES256_GCM_MODE;
            }
            else
            {
                aesMode = HSM_AES_GCM_MODE;
            }

            Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
            if(Element == NULL)
            {
                HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                result = CRYPTO_E_KEY_NOT_VALID;
            }
            else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
            {
                HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                result = CRYPTO_E_KEY_NOT_VALID;
            }
            else
            {
                keyNum = Element->CryptoKeyElementHsmKeyIndex;
                if(aesMode == HSM_AES256_GCM_MODE)
                {
                    result = HSM_DRIVER_RETURN(HSM_Aes256GcmEncStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, aesMode, keyNum, ivPtr, ivPtrLength));
                }
                else
                {
                    result = HSM_DRIVER_RETURN(HSM_AesGcmEncStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, aesMode, keyNum, ivPtr, ivPtrLength));
                }
            }
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
        {
            aesMode = HSM_AES256_GCM_MODE;
        }
        else
        {
            aesMode = HSM_AES_GCM_MODE;
        }

        /* Input parameters */
        plainTextPtr    = job->jobPrimitiveInputOutput.inputPtr;
        plainTextLength = job->jobPrimitiveInputOutput.inputLength;
        aadPtr          = job->jobPrimitiveInputOutput.secondaryInputPtr;
        aadLen          = job->jobPrimitiveInputOutput.secondaryInputLength;

        /* Output parameters */
        cipherTextPtr   = job->jobPrimitiveInputOutput.outputPtr;
        cipherLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
        tagPtr          = job->jobPrimitiveInputOutput.secondaryOutputPtr;
        tagLenPtr       = job->jobPrimitiveInputOutput.secondaryOutputLengthPtr;

        if (plainTextPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (cipherTextPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((plainTextLength == 0) || (*cipherLengthPtr == 0))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (plainTextLength > *cipherLengthPtr)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else if ((uint32)sizeof(aesOutput) < (plainTextLength + HSM_AES_GCM_TAG_LEN))
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = E_NOT_OK;
        }
        else if ((aadLen > 0) && (aadPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (tagPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*tagLenPtr < (uint32)HSM_AES_GCM_TAG_LEN)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = E_NOT_OK;
        }
        else
        {
            if(aesMode == HSM_AES256_GCM_MODE)
            {
                HsmDrvResult = HSM_Aes256GcmEncUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, plainTextPtr, plainTextLength, aadPtr, aadLen);
            }
            else
            {
                HsmDrvResult = HSM_AesGcmEncUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, plainTextPtr, plainTextLength, aadPtr, aadLen);
            }

            if(HsmDrvResult == E_OK)
            {
                timeout = 0;
                do
                {
                    HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                    if (HsmDrvResult != HSM_E_WAIT)
                    {
                        break;
                    }
                    timeout++;
                } while (timeout < WAIT_RESP_TIMEOUT);

                if (HsmDrvResult == E_OK)
                {
                    HsmDrvResult = HSM_ReadRxBuff((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId, (plainTextLength + HSM_AES_GCM_TAG_LEN), aesOutput);
                }
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
            if(result == E_OK)
            {
                HaeModule_Crypto_Memcpy(cipherTextPtr, &aesOutput[0], plainTextLength);
                HaeModule_Crypto_Memcpy(tagPtr, &aesOutput[plainTextLength], HSM_AES_GCM_TAG_LEN);
                *cipherLengthPtr = plainTextLength;
                *tagLenPtr = HSM_AES_GCM_TAG_LEN;
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
        {
            aesMode = HSM_AES256_GCM_MODE;
        }
        else
        {
            aesMode = HSM_AES_GCM_MODE;
        }

        if(aesMode == HSM_AES256_GCM_MODE)
        {
            result = HSM_DRIVER_RETURN(HSM_Aes256GcmEncFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_AesGcmEncFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_RSAPKCS1OAEPENC_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs1oaepEnc( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    volatile uint32 timeout = 0;
    HAEMODULE_RSAES_OAEP_INPUT_t HsmRsaPkcs1OaepEncryptInput;
    CryptoKeyElement* Element;
    uint8 *seed = NULL;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1oaepEncStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != sizeof(HAEMODULE_RSAES_OAEP_INPUT_t))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_SEED);
            if((Element != NULL)
                && (Element->CryptoKeyElementValue != NULL)
                && (Element->CryptoKeyElementValueState == TRUE)
                && (Element->CryptoKeyElementValueSize == SHA256_DIGEST_SIZE)
            )
            {
                seed = Element->CryptoKeyElementValue;
            }

            if(seed == NULL)
            {
                HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                result = CRYPTO_E_KEY_NOT_VALID;
            }
            else
            {
                HaeModule_Crypto_Memcpy((uint8 *)&HsmRsaPkcs1OaepEncryptInput, (const uint8 *)job->jobPrimitiveInputOutput.inputPtr, (uint32)sizeof(HAEMODULE_RSAES_OAEP_INPUT_t));
                HsmDrvResult = HSM_RsaPkcs1oaepEncUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, HsmRsaPkcs1OaepEncryptInput.textPtr, HsmRsaPkcs1OaepEncryptInput.textLength,
                                                        HsmRsaPkcs1OaepEncryptInput.labelPtr, HsmRsaPkcs1OaepEncryptInput.labelLength,
                                                        seed);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if ((job->jobPrimitiveInputOutput.outputPtr == NULL) || (job->jobPrimitiveInputOutput.outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*job->jobPrimitiveInputOutput.outputLengthPtr < (uint32)HAC_RSA_BYTES_SIZE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1oaepEncFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, job->jobPrimitiveInputOutput.outputPtr));
            if(result == E_OK)
            {
                *job->jobPrimitiveInputOutput.outputLengthPtr = (uint32)HAC_RSA_BYTES_SIZE;
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_RSAPKCS1V15ENC_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs1v15Enc( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    volatile uint32 timeout = 0;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1v15EncStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength == 0)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HsmDrvResult = HSM_RsaPkcs1v15EncUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, job->jobPrimitiveInputOutput.inputPtr, job->jobPrimitiveInputOutput.inputLength);
            if(HsmDrvResult == E_OK)
            {
                timeout = 0;
                do
                {
                    HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                    if (HsmDrvResult != HSM_E_WAIT)
                    {
                        break;
                    }
                    timeout++;
                } while (timeout < WAIT_RESP_TIMEOUT);
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if ((job->jobPrimitiveInputOutput.outputPtr == NULL) || (job->jobPrimitiveInputOutput.outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*job->jobPrimitiveInputOutput.outputLengthPtr < (uint32)HAC_RSA_BYTES_SIZE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1v15EncFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, job->jobPrimitiveInputOutput.outputPtr));
            if(result == E_OK)
            {
                *job->jobPrimitiveInputOutput.outputLengthPtr = (uint32)HAC_RSA_BYTES_SIZE;
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_AESDECECB_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesDecECB( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    uint32 remainPlainTextLength = job->jobPrimitiveInputOutput.inputLength;
    uint8* cipherTextPtr = job->jobPrimitiveInputOutput.outputPtr;
    uint32* cipherLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
    uint32 txLen = 0;
    uint32 i = 0;
    volatile uint32 timeout = 0;
    uint32 maxTxLen = HSM_GetMaxTranSizeByte();
    AES_MODE aesMode = HSM_AES_ECB_MODE;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_128_KEY_BIT_SIZE)
        {
            aesMode = HSM_AES_ECB_MODE;
        }
        #ifdef HAEHSM_PRIMITIVE_AES256_SUPPORT
        else if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
        {
            aesMode = HSM_AES256_ECB_MODE;
        }
        #endif
        else
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }

        if(result == E_OK)
        {
            Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
            if(Element == NULL)
            {
                HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                result = CRYPTO_E_KEY_NOT_VALID;
            }
            else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
            {
                HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                result = CRYPTO_E_KEY_NOT_VALID;
            }
            else
            {
                keyNum = Element->CryptoKeyElementHsmKeyIndex;
                result = HSM_DRIVER_RETURN(HSM_AesDecStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, aesMode, keyNum, NULL));
            }
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((cipherTextPtr == NULL) || (cipherLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((remainPlainTextLength == 0) || (*cipherLengthPtr == 0))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (remainPlainTextLength > *cipherLengthPtr)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainPlainTextLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainPlainTextLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainPlainTextLength;
                }

                HsmDrvResult = HSM_AesDecUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);

                    if (HsmDrvResult == E_OK)
                    {
                        HsmDrvResult = HSM_ReadRxBuff((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId, txLen, &cipherTextPtr[i]);
                    }
                }

                remainPlainTextLength -= txLen;
                i += txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
            *cipherLengthPtr = i;
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        result = HSM_DRIVER_RETURN(HSM_AesDecFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_AESDECCBC_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesDecCBC( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    uint32 remainPlainTextLength = job->jobPrimitiveInputOutput.inputLength;
    uint8* cipherTextPtr = job->jobPrimitiveInputOutput.outputPtr;
    uint32* cipherLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
    uint8 ivPtr[16];
    uint32 ivPtrLength = 16;
    uint32 txLen = 0;
    uint32 i = 0;
    volatile uint32 timeout = 0;
    uint32 maxTxLen = HSM_GetMaxTranSizeByte();
    AES_MODE aesMode = HSM_AES_CBC_MODE;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HaeModule_Crypto_KeyElementGet(job->cryptoKeyId, CRYPTO_KE_CIPHER_IV, ivPtr, &ivPtrLength);
        if (result == E_OK)
        {
            if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_128_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES_CBC_MODE;
            }
            #ifdef HAEHSM_PRIMITIVE_AES256_SUPPORT
            else if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES256_CBC_MODE;
            }
            #endif
            else
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }

            if(result == E_OK)
            {
                Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
                if(Element == NULL)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else
                {
                    keyNum = Element->CryptoKeyElementHsmKeyIndex;
                    result = HSM_DRIVER_RETURN(HSM_AesDecStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, aesMode, keyNum, ivPtr));
                }
            }
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((cipherTextPtr == NULL) || (cipherLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((remainPlainTextLength == 0) || (*cipherLengthPtr == 0))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (remainPlainTextLength > *cipherLengthPtr)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainPlainTextLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainPlainTextLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainPlainTextLength;
                }

                HsmDrvResult = HSM_AesDecUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);

                    if (HsmDrvResult == E_OK)
                    {
                        HsmDrvResult = HSM_ReadRxBuff((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId, txLen, &cipherTextPtr[i]);
                    }
                }

                remainPlainTextLength -= txLen;
                i+= txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
            *cipherLengthPtr = i;
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        result = HSM_DRIVER_RETURN(HSM_AesDecFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_AESDECCTR_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesDecCTR( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    uint32 remainPlainTextLength = job->jobPrimitiveInputOutput.inputLength;
    uint8* cipherTextPtr = job->jobPrimitiveInputOutput.outputPtr;
    uint32* cipherLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
    uint8 ivPtr[16];
    uint32 ivPtrLength = 16;
    uint32 txLen = 0;
    uint32 i = 0;
    volatile uint32 timeout = 0;
    uint32 maxTxLen = HSM_GetMaxTranSizeByte();
    AES_MODE aesMode = HSM_AES_CTR_MODE;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HaeModule_Crypto_KeyElementGet(job->cryptoKeyId, CRYPTO_KE_CIPHER_IV, ivPtr, &ivPtrLength);
        if (result == E_OK)
        {
            if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_128_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES_CTR_MODE;
            }
            #ifdef HAEHSM_PRIMITIVE_AES256_SUPPORT
            else if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES256_CTR_MODE;
            }
            #endif
            else
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }

            if(result == E_OK)
            {
                Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
                if(Element == NULL)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else
                {
                    keyNum = Element->CryptoKeyElementHsmKeyIndex;
                    result = HSM_DRIVER_RETURN(HSM_AesDecStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, aesMode, keyNum, ivPtr));
                }
            }
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((cipherTextPtr == NULL) || (cipherLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((remainPlainTextLength == 0) || (*cipherLengthPtr == 0))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (remainPlainTextLength > *cipherLengthPtr)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainPlainTextLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainPlainTextLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainPlainTextLength;
                }

                HsmDrvResult = HSM_AesDecUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);

                    if (HsmDrvResult == E_OK)
                    {
                        HsmDrvResult = HSM_ReadRxBuff((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId, txLen, &cipherTextPtr[i]);
                    }
                }

                remainPlainTextLength -= txLen;
                i += txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
            *cipherLengthPtr = i;
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        result = HSM_DRIVER_RETURN(HSM_AesDecFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_AESDECOFB_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesDecOFB( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    uint32 remainPlainTextLength = job->jobPrimitiveInputOutput.inputLength;
    uint8* cipherTextPtr = job->jobPrimitiveInputOutput.outputPtr;
    uint32* cipherLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
    uint8 ivPtr[16];
    uint32 ivPtrLength = 16;
    uint32 txLen = 0;
    uint32 i = 0;
    volatile uint32 timeout = 0;
    uint32 maxTxLen = HSM_GetMaxTranSizeByte();
    AES_MODE aesMode = HSM_AES_OFB_MODE;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HaeModule_Crypto_KeyElementGet(job->cryptoKeyId, CRYPTO_KE_CIPHER_IV, ivPtr, &ivPtrLength);
        if (result == E_OK)
        {
            if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_128_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES_OFB_MODE;
            }
            #ifdef HAEHSM_PRIMITIVE_AES256_SUPPORT
            else if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES256_OFB_MODE;
            }
            #endif
            else
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }

            if(result == E_OK)
            {
                Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
                if(Element == NULL)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                    result = CRYPTO_E_KEY_NOT_VALID;
                }
                else
                {
                    keyNum = Element->CryptoKeyElementHsmKeyIndex;
                    result = HSM_DRIVER_RETURN(HSM_AesDecStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, aesMode, keyNum, ivPtr));
                }
            }
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((cipherTextPtr == NULL) || (cipherLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((remainPlainTextLength == 0) || (*cipherLengthPtr == 0))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (remainPlainTextLength > *cipherLengthPtr)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            HsmDrvResult = E_OK;

            while ((remainPlainTextLength > 0) && (HsmDrvResult == E_OK))
            {
                if (remainPlainTextLength > maxTxLen)
                {
                    txLen = maxTxLen;
                }
                else
                {
                    txLen = remainPlainTextLength;
                }

                HsmDrvResult = HSM_AesDecUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, &job->jobPrimitiveInputOutput.inputPtr[i], txLen);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);

                    if (HsmDrvResult == E_OK)
                    {
                        HsmDrvResult = HSM_ReadRxBuff((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId, txLen, &cipherTextPtr[i]);
                    }
                }

                remainPlainTextLength -= txLen;
                i += txLen;
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
            *cipherLengthPtr = i;
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        result = HSM_DRIVER_RETURN(HSM_AesDecFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_AESDECGCM_SUPPORT
Std_ReturnType HaeHsm_Primitive_AesDecGCM( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    const uint8* cipherTextPtr;
    uint32 cipherLength;
    const uint8* aadPtr;
    uint32 aadLen;
    const uint8* tagPtr;
    uint32 tagLen;
    uint8* plainTextPtr = job->jobPrimitiveInputOutput.outputPtr;
    uint32* plainLengthPtr = job->jobPrimitiveInputOutput.outputLengthPtr;
    uint8 ivPtr[16];
    uint32 ivPtrLength = 16;
    volatile uint32 timeout = 0;
    AES_MODE aesMode;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HaeModule_Crypto_KeyElementGet(job->cryptoKeyId, CRYPTO_KE_CIPHER_IV, ivPtr, &ivPtrLength);
        if (result == E_OK)
        {
            if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES256_GCM_MODE;
            }
            else
            {
                aesMode = HSM_AES_GCM_MODE;
            }

            Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
            if(Element == NULL)
            {
                HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                result = CRYPTO_E_KEY_NOT_VALID;
            }
            else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
            {
                HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
                result = CRYPTO_E_KEY_NOT_VALID;
            }
            else
            {
                keyNum = Element->CryptoKeyElementHsmKeyIndex;
                if(aesMode == HSM_AES256_GCM_MODE)
                {
                    result = HSM_DRIVER_RETURN(HSM_Aes256GcmDecStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, aesMode, keyNum, ivPtr, ivPtrLength));
                }
                else
                {
                    result = HSM_DRIVER_RETURN(HSM_AesGcmDecStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, aesMode, keyNum, ivPtr, ivPtrLength));
                }
            }
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
        {
            aesMode = HSM_AES256_GCM_MODE;
        }
        else
        {
            aesMode = HSM_AES_GCM_MODE;
        }

        cipherTextPtr   = job->jobPrimitiveInputOutput.inputPtr;
        cipherLength    = job->jobPrimitiveInputOutput.inputLength;
        aadPtr          = job->jobPrimitiveInputOutput.secondaryInputPtr;
        aadLen          = job->jobPrimitiveInputOutput.secondaryInputLength;
        tagPtr          = job->jobPrimitiveInputOutput.tertiaryInputPtr;
        tagLen          = job->jobPrimitiveInputOutput.tertiaryInputLength;

        if (cipherTextPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((plainTextPtr == NULL) || (plainLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((cipherLength == 0) || (*plainLengthPtr == 0))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (cipherLength > *plainLengthPtr)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else if ((aadLen > 0) && (aadPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (tagPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (tagLen < (uint32)HSM_AES_GCM_TAG_LEN)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            if(aesMode == HSM_AES256_GCM_MODE)
            {
                HsmDrvResult = HSM_Aes256GcmDecUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, tagPtr, cipherTextPtr, cipherLength, aadPtr, aadLen);
            }
            else
            {
                HsmDrvResult = HSM_AesGcmDecUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, tagPtr, cipherTextPtr, cipherLength, aadPtr, aadLen);
            }

            if(HsmDrvResult == E_OK)
            {
                timeout = 0;
                do
                {
                    HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                    if (HsmDrvResult != HSM_E_WAIT)
                    {
                        break;
                    }
                    timeout++;
                } while (timeout < WAIT_RESP_TIMEOUT);

                if (HsmDrvResult == E_OK)
                {
                    HsmDrvResult = HSM_ReadRxBuff((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId, cipherLength, plainTextPtr);
                }
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
            if(result == E_OK)
            {
                *plainLengthPtr = cipherLength;
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.verifyPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else
        {
            if(job->jobPrimitiveInfo->primitiveInfo->algorithm.keyLength == (uint32)AES_256_KEY_BIT_SIZE)
            {
                aesMode = HSM_AES256_GCM_MODE;
            }
            else
            {
                aesMode = HSM_AES_GCM_MODE;
            }

            if(aesMode == HSM_AES256_GCM_MODE)
            {
                result = HSM_DRIVER_RETURN(HSM_Aes256GcmDecFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
            }
            else
            {
                result = HSM_DRIVER_RETURN(HSM_AesGcmDecFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx));
            }

            if(result == E_OK)
            {
                *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_OK;
            }
            else
            {
                *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
            }
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_RSAPKCS1OAEPDEC_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs1oaepDec( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    volatile uint32 timeout = 0;
    HAEMODULE_RSAES_OAEP_INPUT_t HsmRsaPkcs1OaepDecryptInput;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1oaepDecStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != sizeof(HAEMODULE_RSAES_OAEP_INPUT_t))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HaeModule_Crypto_Memcpy((uint8 *)&HsmRsaPkcs1OaepDecryptInput, (const uint8 *)job->jobPrimitiveInputOutput.inputPtr, (uint32)sizeof(HAEMODULE_RSAES_OAEP_INPUT_t));
            HsmDrvResult = HSM_RsaPkcs1oaepDecUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, HsmRsaPkcs1OaepDecryptInput.textPtr, HsmRsaPkcs1OaepDecryptInput.labelPtr, HsmRsaPkcs1OaepDecryptInput.labelLength);
            if(HsmDrvResult == E_OK)
            {
                timeout = 0;
                do
                {
                    HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                    if (HsmDrvResult != HSM_E_WAIT)
                    {
                        break;
                    }
                    timeout++;
                } while (timeout < WAIT_RESP_TIMEOUT);
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if ((job->jobPrimitiveInputOutput.outputPtr == NULL) || (job->jobPrimitiveInputOutput.outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*job->jobPrimitiveInputOutput.outputLengthPtr == 0)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1oaepDecFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, job->jobPrimitiveInputOutput.outputPtr, job->jobPrimitiveInputOutput.outputLengthPtr));
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_RSAPKCS1V15DEC_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs1v15Dec( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    volatile uint32 timeout = 0;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_CIPHER_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1v15DecStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != HAC_RSA_BYTES_SIZE)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HsmDrvResult = HSM_RsaPkcs1v15DecUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, job->jobPrimitiveInputOutput.inputPtr);
            if(HsmDrvResult == E_OK)
            {
                timeout = 0;
                do
                {
                    HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                    if (HsmDrvResult != HSM_E_WAIT)
                    {
                        break;
                    }
                    timeout++;
                } while (timeout < WAIT_RESP_TIMEOUT);
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        if ((job->jobPrimitiveInputOutput.outputPtr == NULL) || (job->jobPrimitiveInputOutput.outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*job->jobPrimitiveInputOutput.outputLengthPtr == 0)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1v15DecFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, job->jobPrimitiveInputOutput.outputPtr, job->jobPrimitiveInputOutput.outputLengthPtr));
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_RSAPKCS1V15SIGN_SUPPORT
static Std_ReturnType HaeHsm_Primitive_Internal_RsaPkcs1v15Sign( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    volatile uint32 timeout = 0;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_SIGNATURE_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1v15SignStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        // job->jobPrimitiveInputOutput.inputPtr: Digest
        // job->jobPrimitiveInputOutput.secondaryInputPtr: Salt
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != SHA256_DIGEST_SIZE)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HsmDrvResult = HSM_RsaPkcs1v15SignUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, job->jobPrimitiveInputOutput.inputPtr);
            if(HsmDrvResult == E_OK)
            {
                timeout = 0;
                do
                {
                    HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                    if (HsmDrvResult != HSM_E_WAIT)
                    {
                        break;
                    }
                    timeout++;
                } while (timeout < WAIT_RESP_TIMEOUT);
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        // job->jobPrimiritveInputOut.outputPtr: Generated Signature
        if ((job->jobPrimitiveInputOutput.outputPtr == NULL) || (job->jobPrimitiveInputOutput.outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*job->jobPrimitiveInputOutput.outputLengthPtr < (uint32)HAC_RSA_BYTES_SIZE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1v15SignFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, job->jobPrimitiveInputOutput.outputPtr));
            if(result == E_OK)
            {
                *job->jobPrimitiveInputOutput.outputLengthPtr = (uint32)HAC_RSA_BYTES_SIZE;
            }
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}

Std_ReturnType HaeHsm_Primitive_RsaPkcs1v15Sign( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    Crypto_JobType primitiveJob;
    uint8 digest[SHA256_DIGEST_SIZE];
    uint32 digestLength = SHA256_DIGEST_SIZE;


    HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
    primitiveJob.jobPrimitiveInputOutput.mode           = job->jobPrimitiveInputOutput.mode;
    primitiveJob.jobPrimitiveInputOutput.inputPtr       = job->jobPrimitiveInputOutput.inputPtr;
    primitiveJob.jobPrimitiveInputOutput.inputLength    = job->jobPrimitiveInputOutput.inputLength;
    primitiveJob.jobRedirectionInfoRef                  = NULL;

    if((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0)
    {
        primitiveJob.jobPrimitiveInputOutput.outputPtr          = (uint8*)&digest;
        primitiveJob.jobPrimitiveInputOutput.outputLengthPtr    = (uint32*)&digestLength;
    }

    result = HaeHsm_Primitive_Sha256(PrimitiveData, &primitiveJob);
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
        primitiveJob.jobPrimitiveInputOutput.mode               = CRYPTO_OPERATIONMODE_SINGLECALL;
        primitiveJob.jobPrimitiveInputOutput.inputPtr           = (uint8*)digest;
        primitiveJob.jobPrimitiveInputOutput.inputLength        = (uint32)sizeof(digest);
        primitiveJob.jobPrimitiveInputOutput.outputPtr          = job->jobPrimitiveInputOutput.outputPtr;
        primitiveJob.jobPrimitiveInputOutput.outputLengthPtr    = job->jobPrimitiveInputOutput.outputLengthPtr;
        primitiveJob.cryptoKeyId                                = job->cryptoKeyId;

        result = HaeHsm_Primitive_Internal_RsaPkcs1v15Sign(PrimitiveData, &primitiveJob);
        if(result != E_OK)
        {
            /* In this design, if it's CRYPTO_E_BUSY, we can't wait and try again. */
            result = E_NOT_OK;
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_RSAPKCS1PSSSIGN_SUPPORT
static Std_ReturnType HaeHsm_Primitive_Internal_RsaPkcs1PssSign( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    volatile uint32 timeout = 0;
    HSM_RSA_PKCS1_PSS_SIGNGENERATE_INTPUT_t HsmRsaPkcs1PssSignInput;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_SIGNATURE_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1PssSignStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        // job->jobPrimitiveInputOutput.inputPtr: Plaintext
        // job->jobPrimitiveInputOutput.secondaryInputPtr: Salt
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != sizeof(HSM_RSA_PKCS1_PSS_SIGNGENERATE_INTPUT_t))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HaeModule_Crypto_Memcpy((uint8 *)&HsmRsaPkcs1PssSignInput, (const uint8 *)job->jobPrimitiveInputOutput.inputPtr, (uint32)sizeof(HSM_RSA_PKCS1_PSS_SIGNGENERATE_INTPUT_t));
            HsmDrvResult = HSM_RsaPkcs1PssSignUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, HsmRsaPkcs1PssSignInput.digestPtr, HsmRsaPkcs1PssSignInput.saltPtr, HsmRsaPkcs1PssSignInput.saltLength);
            if(HsmDrvResult == E_OK)
            {
                timeout = 0;
                do
                {
                    HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                    if (HsmDrvResult != HSM_E_WAIT)
                    {
                        break;
                    }
                    timeout++;
                } while (timeout < WAIT_RESP_TIMEOUT);
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        // job->jobPrimiritveInputOut.outputPtr: Generated Signature
        if ((job->jobPrimitiveInputOutput.outputPtr == NULL) || (job->jobPrimitiveInputOutput.outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*job->jobPrimitiveInputOutput.outputLengthPtr < (uint32)HAC_RSA_BYTES_SIZE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1PssSignFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, job->jobPrimitiveInputOutput.outputPtr));
            if(result == E_OK)
            {
                *job->jobPrimitiveInputOutput.outputLengthPtr = (uint32)HAC_RSA_BYTES_SIZE;
            }
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}

Std_ReturnType HaeHsm_Primitive_RsaPkcs1PssSign( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    HSM_RSA_PKCS1_PSS_SIGNGENERATE_INTPUT_t HsmRsaPkcs1PssSignInput;
    Crypto_JobType primitiveJob;
    uint8 digest[SHA256_DIGEST_SIZE];
	uint8 salt[RSA_PKCS1_PSS_SALT_SIZE];
    uint32 digestLength = SHA256_DIGEST_SIZE;


    HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
    primitiveJob.jobPrimitiveInputOutput.mode           = job->jobPrimitiveInputOutput.mode;
    primitiveJob.jobPrimitiveInputOutput.inputPtr       = job->jobPrimitiveInputOutput.inputPtr;
    primitiveJob.jobPrimitiveInputOutput.inputLength    = job->jobPrimitiveInputOutput.inputLength;
    primitiveJob.jobRedirectionInfoRef                  = NULL;

    if((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0)
    {
        primitiveJob.jobPrimitiveInputOutput.outputPtr          = (uint8*)&digest;
        primitiveJob.jobPrimitiveInputOutput.outputLengthPtr    = (uint32*)&digestLength;
    }

    result = HaeHsm_Primitive_Sha256(PrimitiveData, &primitiveJob);
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        result = HSM_DRIVER_RETURN(HSM_TrueRandomGenerate((UINT8 *)salt, (UINT32)RSA_PKCS1_PSS_SALT_SIZE));
        if(result == E_OK)
        {
            HaeModule_Crypto_Memset((uint8 *)&HsmRsaPkcs1PssSignInput, 0, (uint32)sizeof(HsmRsaPkcs1PssSignInput));
            HsmRsaPkcs1PssSignInput.digestPtr   = digest;
            HsmRsaPkcs1PssSignInput.saltPtr     = salt;
            HsmRsaPkcs1PssSignInput.saltLength  = (uint32)RSA_PKCS1_PSS_SALT_SIZE;

            HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
            primitiveJob.jobPrimitiveInputOutput.mode               = CRYPTO_OPERATIONMODE_SINGLECALL;
            primitiveJob.jobPrimitiveInputOutput.inputPtr           = (uint8*)&HsmRsaPkcs1PssSignInput;
            primitiveJob.jobPrimitiveInputOutput.inputLength        = (uint32)sizeof(HsmRsaPkcs1PssSignInput);
            primitiveJob.jobPrimitiveInputOutput.outputPtr          = job->jobPrimitiveInputOutput.outputPtr;
            primitiveJob.jobPrimitiveInputOutput.outputLengthPtr    = job->jobPrimitiveInputOutput.outputLengthPtr;
            primitiveJob.cryptoKeyId                                = job->cryptoKeyId;

            result = HaeHsm_Primitive_Internal_RsaPkcs1PssSign(PrimitiveData, &primitiveJob);
            if(result != E_OK)
            {
                /* In this design, if it's CRYPTO_E_BUSY, we can't wait and try again. */
                result = E_NOT_OK;
            }
        }
        else
        {
            result = E_NOT_OK;
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_ECCECDSASIGN_SUPPORT
static Std_ReturnType HaeHsm_Primitive_Internal_EccEcdsaSign( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    ECC_ECDSA_SIGN_t sign;
    uint32 i, index;
    volatile uint32 timeout = 0;
    HSM_ECC_ECDSA_SIGNGENERATE_INTPUT_t HsmEccEcdsaSignInput;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_SIGNATURE_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_EccEcdsaSignStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        // job->jobPrimitiveInputOutput.inputPtr: digest (32)
        // job->jobPrimitiveInputOutput.secondaryInputPtr: secretValue (32)
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != sizeof(HSM_ECC_ECDSA_SIGNGENERATE_INTPUT_t))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HaeModule_Crypto_Memcpy((uint8 *)&HsmEccEcdsaSignInput, (const uint8 *)job->jobPrimitiveInputOutput.inputPtr, (uint32)sizeof(HSM_ECC_ECDSA_SIGNGENERATE_INTPUT_t));
            HsmDrvResult = HSM_EccEcdsaSignUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, HsmEccEcdsaSignInput.digestPtr, HsmEccEcdsaSignInput.secretNumberPtr);
            if(HsmDrvResult == E_OK)
            {
                timeout = 0;
                do
                {
                    HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                    if (HsmDrvResult != HSM_E_WAIT)
                    {
                        break;
                    }
                    timeout++;
                } while (timeout < WAIT_RESP_TIMEOUT);
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        // job->jobPrimiritveInputOut.outputPtr: Generated Signature
        if ((job->jobPrimitiveInputOutput.outputPtr == NULL) || (job->jobPrimitiveInputOutput.outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*job->jobPrimitiveInputOutput.outputLengthPtr < (uint32)sizeof(ECC_ECDSA_SIGN_t))
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_EccEcdsaSignFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, (ECC_ECDSA_SIGN_t*)&sign));
            if(result == E_OK)
            {
                index = 0;
                for(i = 0; i < (uint32)ECC_BYTES_SIZE; i++)
                {
                    job->jobPrimitiveInputOutput.outputPtr[index] = sign.r[i];
                    index++;
                }
                for(i = 0; i < (uint32)ECC_BYTES_SIZE; i++)
                {
                    job->jobPrimitiveInputOutput.outputPtr[index] = sign.s[i];
                    index++;
                }

                *job->jobPrimitiveInputOutput.outputLengthPtr = index;
            }
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}

Std_ReturnType HaeHsm_Primitive_EccEcdsaSign( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    HSM_ECC_ECDSA_SIGNGENERATE_INTPUT_t HsmEccEcdsaSignInput;
    Crypto_JobType primitiveJob;
    uint8 digest[SHA256_DIGEST_SIZE];
	uint8 secret[ECC_BYTES_SIZE];
    uint32 digestLength = SHA256_DIGEST_SIZE;


    HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
    primitiveJob.jobPrimitiveInputOutput.mode           = job->jobPrimitiveInputOutput.mode;
    primitiveJob.jobPrimitiveInputOutput.inputPtr       = job->jobPrimitiveInputOutput.inputPtr;
    primitiveJob.jobPrimitiveInputOutput.inputLength    = job->jobPrimitiveInputOutput.inputLength;
    primitiveJob.jobRedirectionInfoRef                  = NULL;

    if((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0)
    {
        primitiveJob.jobPrimitiveInputOutput.outputPtr          = (uint8*)&digest;
        primitiveJob.jobPrimitiveInputOutput.outputLengthPtr    = (uint32*)&digestLength;
    }

    result = HaeHsm_Primitive_Sha256(PrimitiveData, &primitiveJob);
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        result = HSM_DRIVER_RETURN(HSM_TrueRandomGenerate((UINT8 *)secret, (UINT32)sizeof(secret)));
        if(result == E_OK)
        {
            HaeModule_Crypto_Memset((uint8 *)&HsmEccEcdsaSignInput, 0, (uint32)sizeof(HsmEccEcdsaSignInput));
            HsmEccEcdsaSignInput.digestPtr       = digest;
            HsmEccEcdsaSignInput.secretNumberPtr = secret;

            HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
            primitiveJob.jobPrimitiveInputOutput.mode               = CRYPTO_OPERATIONMODE_SINGLECALL;
            primitiveJob.jobPrimitiveInputOutput.inputPtr           = (uint8*)&HsmEccEcdsaSignInput;
            primitiveJob.jobPrimitiveInputOutput.inputLength        = (uint32)sizeof(HsmEccEcdsaSignInput);
            primitiveJob.jobPrimitiveInputOutput.outputPtr          = job->jobPrimitiveInputOutput.outputPtr;
            primitiveJob.jobPrimitiveInputOutput.outputLengthPtr    = job->jobPrimitiveInputOutput.outputLengthPtr;
            primitiveJob.cryptoKeyId                                = job->cryptoKeyId;

            result = HaeHsm_Primitive_Internal_EccEcdsaSign(PrimitiveData, &primitiveJob);
            if(result != E_OK)
            {
                /* In this design, if it's CRYPTO_E_BUSY, we can't wait and try again. */
                result = E_NOT_OK;
            }
        }
        else
        {
            result = E_NOT_OK;
        }
    }

    return result;
}
#endif

#if defined(HAEHSM_PRIMITIVE_ECCECDSASIGNP521R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDSAVERIFYP521R1_SUPPORT)
/*
 * In the specification, the signature size of ECC ECDSA P521R1 is 132(66 + 66) bytes.
 * Internally, 136(68+68) byte size is used because 4(2+2) byte padding is placed before the array.
 * Therefore, we convert it to 132(66 + 66) bytes according to the specification and return it.
*/
static void EccEcdsaP521r1Sign_Convert_Crypto_to_Hsm(const uint8 *cryptoSign, uint32 secInLenStartIdx, ECC_ECDSA_P521R1_SIGN_t *hsmSign)
{
    uint32 i, index;

    HaeModule_Crypto_Memset((uint8 *)hsmSign, 0, (uint32)sizeof(ECC_ECDSA_P521R1_SIGN_t));
    index = secInLenStartIdx;
    for(i = 2; i < (uint32)ECC_BYTES_SIZE_P521R1; i++)
    {
        hsmSign->r[i] = cryptoSign[index];
        index++;
    }
    index += secInLenStartIdx;
    for(i = 2; i < (uint32)ECC_BYTES_SIZE_P521R1; i++)
    {
        hsmSign->s[i] = cryptoSign[index];
        index++;
    }
}
static void EccEcdsaP521r1Sign_Convert_Hsm_to_Crypto(const ECC_ECDSA_P521R1_SIGN_t *hsmSign, uint8 *cryptoSign)
{
    uint32 i, index;

    index = 0;
    for(i = 2; i < (uint32)ECC_BYTES_SIZE_P521R1; i++)
    {
        cryptoSign[index] = hsmSign->r[i];
        index++;
    }
    for(i = 2; i < (uint32)ECC_BYTES_SIZE_P521R1; i++)
    {
        cryptoSign[index] = hsmSign->s[i];
        index++;
    }
}
#endif

#ifdef HAEHSM_PRIMITIVE_ECCECDSASIGNP521R1_SUPPORT
#if (ECC_BYTES_SIZE_P521R1 < SHA512_DIGEST_SIZE)
#error The defined value of ECC_BYTES_SIZE_P521R1 or SHA512_DIGEST_SIZE is incorrect
#endif
static Std_ReturnType HaeHsm_Primitive_Internal_EccEcdsaSignP521r1( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    ECC_ECDSA_P521R1_SIGN_t sign;
    volatile uint32 timeout = 0;
    HSM_ECC_ECDSA_SIGNGENERATE_INTPUT_t HsmEccEcdsaSignInput;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_SIGNATURE_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_EccEcdsaSignP521r1Start(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != sizeof(HSM_ECC_ECDSA_SIGNGENERATE_INTPUT_t))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HaeModule_Crypto_Memcpy((uint8 *)&HsmEccEcdsaSignInput, (const uint8 *)job->jobPrimitiveInputOutput.inputPtr, (uint32)sizeof(HSM_ECC_ECDSA_SIGNGENERATE_INTPUT_t));
            HsmDrvResult = HSM_EccEcdsaSignP521r1Update(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, HsmEccEcdsaSignInput.digestPtr, HsmEccEcdsaSignInput.secretNumberPtr);
            if(HsmDrvResult == E_OK)
            {
                timeout = 0;
                do
                {
                    HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                    if (HsmDrvResult != HSM_E_WAIT)
                    {
                        break;
                    }
                    timeout++;
                } while (timeout < WAIT_RESP_TIMEOUT);
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        // job->jobPrimiritveInputOut.outputPtr: Generated Signature
        if ((job->jobPrimitiveInputOutput.outputPtr == NULL) || (job->jobPrimitiveInputOutput.outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*job->jobPrimitiveInputOutput.outputLengthPtr < (uint32)HSM_CRYPTO_ECC_ECDSA_P521R1_SIGN_SIZE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_EccEcdsaSignP521r1Finish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, (ECC_ECDSA_P521R1_SIGN_t*)&sign));
            if(result == E_OK)
            {
                EccEcdsaP521r1Sign_Convert_Hsm_to_Crypto(&sign, job->jobPrimitiveInputOutput.outputPtr);
                *job->jobPrimitiveInputOutput.outputLengthPtr = HSM_CRYPTO_ECC_ECDSA_P521R1_SIGN_SIZE;
            }
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}

Std_ReturnType HaeHsm_Primitive_EccEcdsaSignP521r1( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    HSM_ECC_ECDSA_SIGNGENERATE_INTPUT_t HsmEccEcdsaSignInput;
    Crypto_JobType primitiveJob;
    /*
     * The array used for Digest and Secret Number is 68 bytes in size and requires zero padding at the front.
     * The actual size of the Digest is 64 bytes.
     * The actual size of the Secret Number is 65 bytes.
     */
    uint8 digest[ECC_BYTES_SIZE_P521R1];
	uint8 secret[ECC_BYTES_SIZE_P521R1];
    uint32 digestLength = SHA512_DIGEST_SIZE;

    HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
    primitiveJob.jobPrimitiveInputOutput.mode           = job->jobPrimitiveInputOutput.mode;
    primitiveJob.jobPrimitiveInputOutput.inputPtr       = job->jobPrimitiveInputOutput.inputPtr;
    primitiveJob.jobPrimitiveInputOutput.inputLength    = job->jobPrimitiveInputOutput.inputLength;
    primitiveJob.jobRedirectionInfoRef                  = NULL;

    if((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0)
    {
        HaeModule_Crypto_Memset((uint8 *)digest, 0, (uint32)sizeof(digest));
        primitiveJob.jobPrimitiveInputOutput.outputPtr          = (uint8*)&digest[(ECC_BYTES_SIZE_P521R1 - SHA512_DIGEST_SIZE)];
        primitiveJob.jobPrimitiveInputOutput.outputLengthPtr    = (uint32*)&digestLength;
    }

    result = HaeHsm_Primitive_Sha512(PrimitiveData, &primitiveJob);
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        /*
         * According to the specification, the size of the secret number is defined in bits.
         * In terms of bytes, it is between 65 and 66 bytes. We allow only 65 bytes to be generated as a random variable.
         */
        HaeModule_Crypto_Memset((uint8 *)secret, 0, (uint32)sizeof(secret));
        result = HSM_DRIVER_RETURN(HSM_TrueRandomGenerate((UINT8 *)&secret[3], ((UINT32)ECC_BYTES_SIZE_P521R1-3)));
        if(result == E_OK)
        {
            HaeModule_Crypto_Memset((uint8 *)&HsmEccEcdsaSignInput, 0, (uint32)sizeof(HsmEccEcdsaSignInput));
            HsmEccEcdsaSignInput.digestPtr       = digest;
            HsmEccEcdsaSignInput.secretNumberPtr = secret;
            HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
            primitiveJob.jobPrimitiveInputOutput.mode               = CRYPTO_OPERATIONMODE_SINGLECALL;
            primitiveJob.jobPrimitiveInputOutput.inputPtr           = (uint8*)&HsmEccEcdsaSignInput;
            primitiveJob.jobPrimitiveInputOutput.inputLength        = (uint32)sizeof(HsmEccEcdsaSignInput);
            primitiveJob.jobPrimitiveInputOutput.outputPtr          = job->jobPrimitiveInputOutput.outputPtr;
            primitiveJob.jobPrimitiveInputOutput.outputLengthPtr    = job->jobPrimitiveInputOutput.outputLengthPtr;
            primitiveJob.cryptoKeyId                                = job->cryptoKeyId;

            result = HaeHsm_Primitive_Internal_EccEcdsaSignP521r1(PrimitiveData, &primitiveJob);
            if(result != E_OK)
            {
                /* In this design, if it's CRYPTO_E_BUSY, we can't wait and try again. */
                result = E_NOT_OK;
            }
        }
        else
        {
            result = E_NOT_OK;
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_ECCEDDSASIGNED448_SUPPORT
Std_ReturnType HaeHsm_Primitive_EccEddsaSignEd448( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    ECC_EDDSA_ED448_SIGN_t sign;
    uint32 i, index;
    volatile uint32 timeout = 0;
    HAEMODULE_EDDSA_ED448_INTPUT_t HsmEccEddsaSignEd448Input;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_SIGNATURE_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_EccEddsaSignEd448Start(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != sizeof(HAEMODULE_EDDSA_ED448_INTPUT_t))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            HaeModule_Crypto_Memcpy((uint8 *)&HsmEccEddsaSignEd448Input, (const uint8 *)job->jobPrimitiveInputOutput.inputPtr, (uint32)sizeof(HAEMODULE_EDDSA_ED448_INTPUT_t));
            HsmDrvResult = HSM_EccEddsaSignEd448Update(&(getPrimitiveData(PrimitiveData))->HsmApiCtx,
                                                    HsmEccEddsaSignEd448Input.message, HsmEccEddsaSignEd448Input.messageLength,
                                                    HsmEccEddsaSignEd448Input.context, HsmEccEddsaSignEd448Input.contextLength);
            if(HsmDrvResult == E_OK)
            {
                timeout = 0;
                do
                {
                    HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                    if (HsmDrvResult != HSM_E_WAIT)
                    {
                        break;
                    }
                    timeout++;
                } while (timeout < WAIT_RESP_TIMEOUT);
            }

            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        // job->jobPrimiritveInputOut.outputPtr: Generated Signature
        if ((job->jobPrimitiveInputOutput.outputPtr == NULL) || (job->jobPrimitiveInputOutput.outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (*job->jobPrimitiveInputOutput.outputLengthPtr < (uint32)sizeof(ECC_EDDSA_ED448_SIGN_t))
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_SMALL_BUFFER);
            result = CRYPTO_E_SMALL_BUFFER;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_EccEddsaSignEd448Finish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, (ECC_EDDSA_ED448_SIGN_t*)&sign));
            if(result == E_OK)
            {
                index = 0;
                for(i = 0; i < (uint32)ED448_SIGN_BYTES; i++)
                {
                    job->jobPrimitiveInputOutput.outputPtr[index] = sign.s[i];
                    index++;
                }

                *job->jobPrimitiveInputOutput.outputLengthPtr = index;
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_RSAPKCS1V15VERIFY_SUPPORT
static Std_ReturnType HaeHsm_Primitive_Internal_RsaPkcs1v15Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    uint32 secInLenStartIdx = 0;
    volatile uint32 timeout = 0;
    UINT8 verifyResult = (UINT8)HSM_VERIFY_FAILURE;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_SIGNATURE_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1v15VerifyStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        // job->jobPrimitiveInputOutput.inputPtr: Digest (32)
        // job->jobPrimitiveInputOutput.secondaryInputPtr: Sign (256)
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != SHA256_DIGEST_SIZE)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.secondaryInputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else
        {
            if(job->jobPrimitiveInputOutput.secondaryInputLength == HAC_RSA_BYTES_SIZE)
            {
                secInLenStartIdx = 0;
            }
            else if((job->jobPrimitiveInputOutput.secondaryInputLength == (HAC_RSA_BYTES_SIZE + 1)) && (job->jobPrimitiveInputOutput.secondaryInputPtr[0] == 0u))
            {
                secInLenStartIdx = 1;
            }
            else
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }

            if(result == E_OK)
            {
                HsmDrvResult = HSM_RsaPkcs1v15VerifyUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, job->jobPrimitiveInputOutput.inputPtr, &(job->jobPrimitiveInputOutput.secondaryInputPtr[secInLenStartIdx]));  // for Java signature - anti-negative exception
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }
        }
        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        // job->jobPrimiritveInputOut.outputPtr: Generated Signature
        if (job->jobPrimitiveInputOutput.verifyPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1v15VerifyFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, (UINT8 *)&verifyResult));
            if (result == E_OK)
            {
                if (verifyResult == (UINT8)HSM_VERIFY_SUCCESS)
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_OK;
                }
                else
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
                }
            }
            else
            {
                *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
            }
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}

Std_ReturnType HaeHsm_Primitive_RsaPkcs1v15Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    Crypto_JobType primitiveJob;
    uint8 digest[SHA256_DIGEST_SIZE];
    uint32 digestLength = SHA256_DIGEST_SIZE;

    HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
    primitiveJob.jobPrimitiveInputOutput.mode           = job->jobPrimitiveInputOutput.mode;
    primitiveJob.jobPrimitiveInputOutput.inputPtr       = job->jobPrimitiveInputOutput.inputPtr;
    primitiveJob.jobPrimitiveInputOutput.inputLength    = job->jobPrimitiveInputOutput.inputLength;
    primitiveJob.jobRedirectionInfoRef                  = NULL;

    if((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0)
    {
        primitiveJob.jobPrimitiveInputOutput.outputPtr          = (uint8*)&digest;
        primitiveJob.jobPrimitiveInputOutput.outputLengthPtr    = (uint32*)&digestLength;
    }

    result = HaeHsm_Primitive_Sha256(PrimitiveData, &primitiveJob);
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
        primitiveJob.jobPrimitiveInputOutput.mode               = CRYPTO_OPERATIONMODE_SINGLECALL;
        primitiveJob.jobPrimitiveInputOutput.inputPtr           = (uint8*)digest;
        primitiveJob.jobPrimitiveInputOutput.inputLength        = (uint32)SHA256_DIGEST_SIZE;
        primitiveJob.jobPrimitiveInputOutput.secondaryInputPtr  = job->jobPrimitiveInputOutput.secondaryInputPtr;
        primitiveJob.jobPrimitiveInputOutput.secondaryInputLength   = job->jobPrimitiveInputOutput.secondaryInputLength;
        primitiveJob.jobPrimitiveInputOutput.verifyPtr          = job->jobPrimitiveInputOutput.verifyPtr;
        primitiveJob.cryptoKeyId                                = job->cryptoKeyId;

        result = HaeHsm_Primitive_Internal_RsaPkcs1v15Verify(PrimitiveData, &primitiveJob);
        if(result != E_OK)
        {
            /* In this design, if it's CRYPTO_E_BUSY, we can't wait and try again. */
            result = E_NOT_OK;
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_SHA1_RSAPKCS1V15VERIFY_SUPPORT
static Std_ReturnType HaeHsm_Primitive_Internal_Sha1_RsaPkcs1v15Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    uint32 secInLenStartIdx = 0;
    volatile uint32 timeout = 0;
    UINT8 verifyResult = (UINT8)HSM_VERIFY_FAILURE;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_SIGNATURE_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1v15VerifyStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        // job->jobPrimitiveInputOutput.inputPtr: Digest (20)
        // job->jobPrimitiveInputOutput.secondaryInputPtr: Sign (256)
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != SHA160_DIGEST_SIZE)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.secondaryInputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else
        {
            if(job->jobPrimitiveInputOutput.secondaryInputLength == HAC_RSA_BYTES_SIZE)
            {
                secInLenStartIdx = 0;
            }
            else if((job->jobPrimitiveInputOutput.secondaryInputLength == (HAC_RSA_BYTES_SIZE + 1)) && (job->jobPrimitiveInputOutput.secondaryInputPtr[0] == 0u))
            {
                secInLenStartIdx = 1;
            }
            else
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }

            if(result == E_OK)
            {
                HsmDrvResult = HSM_RsaPkcs1v15Sha160VerifyUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, job->jobPrimitiveInputOutput.inputPtr, &job->jobPrimitiveInputOutput.secondaryInputPtr[secInLenStartIdx]);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        // job->jobPrimiritveInputOut.outputPtr: Generated Signature
        if (job->jobPrimitiveInputOutput.verifyPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1v15VerifyFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, (UINT8 *)&verifyResult));
            if (result == E_OK)
            {
                if (verifyResult == (UINT8)HSM_VERIFY_SUCCESS)
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_OK;
                }
                else
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
                }
            }
            else
            {
                *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
            }
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}

Std_ReturnType HaeHsm_Primitive_Sha1_RsaPkcs1v15Verify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    Crypto_JobType primitiveJob;
    uint8 digest[SHA160_DIGEST_SIZE];
    uint32 digestLength = SHA160_DIGEST_SIZE;

    HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
    primitiveJob.jobPrimitiveInputOutput.mode           = job->jobPrimitiveInputOutput.mode;
    primitiveJob.jobPrimitiveInputOutput.inputPtr       = job->jobPrimitiveInputOutput.inputPtr;
    primitiveJob.jobPrimitiveInputOutput.inputLength    = job->jobPrimitiveInputOutput.inputLength;
    primitiveJob.jobRedirectionInfoRef                  = NULL;

    if((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0)
    {
        primitiveJob.jobPrimitiveInputOutput.outputPtr          = (uint8*)&digest;
        primitiveJob.jobPrimitiveInputOutput.outputLengthPtr    = (uint32*)&digestLength;
    }

    result = HaeHsm_Primitive_Sha160(PrimitiveData, &primitiveJob);
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
        primitiveJob.jobPrimitiveInputOutput.mode               = CRYPTO_OPERATIONMODE_SINGLECALL;
        primitiveJob.jobPrimitiveInputOutput.inputPtr           = (uint8*)digest;
        primitiveJob.jobPrimitiveInputOutput.inputLength        = (uint32)SHA160_DIGEST_SIZE;
        primitiveJob.jobPrimitiveInputOutput.secondaryInputPtr  = job->jobPrimitiveInputOutput.secondaryInputPtr;
        primitiveJob.jobPrimitiveInputOutput.secondaryInputLength   = job->jobPrimitiveInputOutput.secondaryInputLength;
        primitiveJob.jobPrimitiveInputOutput.verifyPtr          = job->jobPrimitiveInputOutput.verifyPtr;
        primitiveJob.cryptoKeyId                                = job->cryptoKeyId;

        result = HaeHsm_Primitive_Internal_Sha1_RsaPkcs1v15Verify(PrimitiveData, &primitiveJob);
        if(result != E_OK)
        {
            /* In this design, if it's CRYPTO_E_BUSY, we can't wait and try again. */
            result = E_NOT_OK;
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_RSAPKCS1PSSVERIFY_SUPPORT
Std_ReturnType HaeHsm_Primitive_Internal_RsaPkcs1PssVerify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    uint32 secInLenStartIdx = 0;
    volatile uint32 timeout = 0;
    UINT8 verifyResult = (UINT8)HSM_VERIFY_FAILURE;
    HSM_RSA_PKCS1_PSS_SIGNVERIFY_INTPUT_t HsmRsaPkcs1PssVerifyInput;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_SIGNATURE_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1PssVerifyStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        // job->jobPrimitiveInputOutput.inputPtr: Digest (32)
        // job->jobPrimitiveInputOutput.secondaryInputPtr: Sign (256)
        // job->jobPrimitiveInputOutput.tertiaryInputLength: Salt Length
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != sizeof(HSM_RSA_PKCS1_PSS_SIGNVERIFY_INTPUT_t))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.secondaryInputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else
        {
            if(job->jobPrimitiveInputOutput.secondaryInputLength == HAC_RSA_BYTES_SIZE)
            {
                secInLenStartIdx = 0;
            }
            else if((job->jobPrimitiveInputOutput.secondaryInputLength == (HAC_RSA_BYTES_SIZE + 1)) && (job->jobPrimitiveInputOutput.secondaryInputPtr[0] == 0u)) // for Java signature - anti-negative exception
            {
                secInLenStartIdx = 1;
            }
            else
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }

            if(result == E_OK)
            {
                HaeModule_Crypto_Memcpy((uint8 *)&HsmRsaPkcs1PssVerifyInput, (const uint8 *)job->jobPrimitiveInputOutput.inputPtr, (uint32)sizeof(HSM_RSA_PKCS1_PSS_SIGNVERIFY_INTPUT_t));
                HsmDrvResult = HSM_RsaPkcs1PssVerifyUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, HsmRsaPkcs1PssVerifyInput.digestPtr, &(job->jobPrimitiveInputOutput.secondaryInputPtr[secInLenStartIdx]), HsmRsaPkcs1PssVerifyInput.saltLength);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        // job->jobPrimiritveInputOut.outputPtr: Generated Signature
        if (job->jobPrimitiveInputOutput.verifyPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_RsaPkcs1PssVerifyFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, (UINT8 *)&verifyResult));
            if (result == E_OK)
            {
                if (verifyResult == (UINT8)HSM_VERIFY_SUCCESS)
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_OK;
                }
                else
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
                }
            }
            else
            {
                *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
            }
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}

Std_ReturnType HaeHsm_Primitive_RsaPkcs1PssVerify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    HSM_RSA_PKCS1_PSS_SIGNVERIFY_INTPUT_t HsmRsaPkcs1PssVerifyInput;
    Crypto_JobType primitiveJob;
    uint8 digest[SHA256_DIGEST_SIZE];
    uint32 digestLength = SHA256_DIGEST_SIZE;

    HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
    primitiveJob.jobPrimitiveInputOutput.mode           = job->jobPrimitiveInputOutput.mode;
    primitiveJob.jobPrimitiveInputOutput.inputPtr       = job->jobPrimitiveInputOutput.inputPtr;
    primitiveJob.jobPrimitiveInputOutput.inputLength    = job->jobPrimitiveInputOutput.inputLength;
    primitiveJob.jobRedirectionInfoRef                  = NULL;

    if((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0)
    {
        primitiveJob.jobPrimitiveInputOutput.outputPtr          = (uint8*)&digest;
        primitiveJob.jobPrimitiveInputOutput.outputLengthPtr    = (uint32*)&digestLength;
    }

    result = HaeHsm_Primitive_Sha256(PrimitiveData, &primitiveJob);
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        HaeModule_Crypto_Memset((uint8 *)&HsmRsaPkcs1PssVerifyInput, 0, (uint32)sizeof(HSM_RSA_PKCS1_PSS_SIGNVERIFY_INTPUT_t));
        HsmRsaPkcs1PssVerifyInput.digestPtr     = digest;
        HsmRsaPkcs1PssVerifyInput.saltLength    = (uint32)RSA_PKCS1_PSS_SALT_SIZE;

        HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
        primitiveJob.jobPrimitiveInputOutput.mode               = CRYPTO_OPERATIONMODE_SINGLECALL;
        primitiveJob.jobPrimitiveInputOutput.inputPtr           = (uint8*)&HsmRsaPkcs1PssVerifyInput;
        primitiveJob.jobPrimitiveInputOutput.inputLength        = (uint32)sizeof(HSM_RSA_PKCS1_PSS_SIGNVERIFY_INTPUT_t);
        primitiveJob.jobPrimitiveInputOutput.secondaryInputPtr  = job->jobPrimitiveInputOutput.secondaryInputPtr;
        primitiveJob.jobPrimitiveInputOutput.secondaryInputLength   = job->jobPrimitiveInputOutput.secondaryInputLength;
        primitiveJob.jobPrimitiveInputOutput.verifyPtr          = job->jobPrimitiveInputOutput.verifyPtr;
        primitiveJob.cryptoKeyId                                = job->cryptoKeyId;

        result = HaeHsm_Primitive_Internal_RsaPkcs1PssVerify(PrimitiveData, &primitiveJob);
        if(result != E_OK)
        {
            /* In this design, if it's CRYPTO_E_BUSY, we can't wait and try again. */
            result = E_NOT_OK;
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_ECCECDSAVERIFY_SUPPORT
static Std_ReturnType HaeHsm_Primitive_Internal_EccEcdsaVerify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    uint32 secInLenStartIdx = 0;
    ECC_ECDSA_SIGN_t sign;
    uint32 i, index;
    volatile uint32 timeout = 0;
    UINT8 verifyResult = (UINT8)HSM_VERIFY_FAILURE;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_SIGNATURE_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_EccEcdsaVerifyStart(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != ECC_BYTES_SIZE)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.secondaryInputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else
        {
            if(job->jobPrimitiveInputOutput.secondaryInputLength == sizeof(ECC_ECDSA_SIGN_t))
            {
                secInLenStartIdx = 0;
            }
            else if((job->jobPrimitiveInputOutput.secondaryInputLength == (ECC_BYTES_SIZE + 1) * 2)  // for Java signature - anti-negative exception
                    && (job->jobPrimitiveInputOutput.secondaryInputPtr[0] == 0u) && (job->jobPrimitiveInputOutput.secondaryInputPtr[ECC_BYTES_SIZE + 1] == 0u))
            {
                secInLenStartIdx = 1;
            }
            else
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }

            if(result == E_OK)
            {
                index = secInLenStartIdx;
                for(i = 0; i < ECC_BYTES_SIZE; i++)
                {
                    sign.r[i] = job->jobPrimitiveInputOutput.secondaryInputPtr[index];
                    index++;
                }
                index += secInLenStartIdx;
                for(i = 0; i < ECC_BYTES_SIZE; i++)
                {
                    sign.s[i] = job->jobPrimitiveInputOutput.secondaryInputPtr[index];
                    index++;
                }

                HsmDrvResult = HSM_EccEcdsaVerifyUpdate(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, job->jobPrimitiveInputOutput.inputPtr, (const ECC_ECDSA_SIGN_t *)&sign);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        // job->jobPrimiritveInputOut.outputPtr: Generated Signature
        if (job->jobPrimitiveInputOutput.verifyPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_EccEcdsaVerifyFinish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, (UINT8 *)&verifyResult));
            if (result == E_OK)
            {
                if (verifyResult == (UINT8)HSM_VERIFY_SUCCESS)
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_OK;
                }
                else
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
                }
            }
            else
            {
                *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
            }
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}

Std_ReturnType HaeHsm_Primitive_EccEcdsaVerify( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    Crypto_JobType primitiveJob;
    uint8 digest[SHA256_DIGEST_SIZE];
    uint32 digestLength = SHA256_DIGEST_SIZE;

    HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
    primitiveJob.jobPrimitiveInputOutput.mode           = job->jobPrimitiveInputOutput.mode;
    primitiveJob.jobPrimitiveInputOutput.inputPtr       = job->jobPrimitiveInputOutput.inputPtr;
    primitiveJob.jobPrimitiveInputOutput.inputLength    = job->jobPrimitiveInputOutput.inputLength;
    primitiveJob.jobRedirectionInfoRef                  = NULL;

    if((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0)
    {
        primitiveJob.jobPrimitiveInputOutput.outputPtr          = (uint8*)&digest;
        primitiveJob.jobPrimitiveInputOutput.outputLengthPtr    = (uint32*)&digestLength;
    }

    result = HaeHsm_Primitive_Sha256(PrimitiveData, &primitiveJob);
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
        primitiveJob.jobPrimitiveInputOutput.mode               = CRYPTO_OPERATIONMODE_SINGLECALL;
        primitiveJob.jobPrimitiveInputOutput.inputPtr           = (uint8*)digest;
        primitiveJob.jobPrimitiveInputOutput.inputLength        = (uint32)SHA256_DIGEST_SIZE;
        primitiveJob.jobPrimitiveInputOutput.secondaryInputPtr  = job->jobPrimitiveInputOutput.secondaryInputPtr;
        primitiveJob.jobPrimitiveInputOutput.secondaryInputLength   = job->jobPrimitiveInputOutput.secondaryInputLength;
        primitiveJob.jobPrimitiveInputOutput.verifyPtr          = job->jobPrimitiveInputOutput.verifyPtr;
        primitiveJob.cryptoKeyId                                = job->cryptoKeyId;

        result = HaeHsm_Primitive_Internal_EccEcdsaVerify(PrimitiveData, &primitiveJob);
        if(result != E_OK)
        {
            /* In this design, if it's CRYPTO_E_BUSY, we can't wait and try again. */
            result = E_NOT_OK;
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_ECCECDSAVERIFYP521R1_SUPPORT
#if (ECC_BYTES_SIZE_P521R1 < SHA512_DIGEST_SIZE)
#error The defined value of ECC_BYTES_SIZE_P521R1 or SHA512_DIGEST_SIZE is incorrect
#endif
static Std_ReturnType HaeHsm_Primitive_Internal_EccEcdsaVerifyP521r1( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    uint32 secInLenStartIdx = 0;
    ECC_ECDSA_P521R1_SIGN_t sign;
    volatile uint32 timeout = 0;
    UINT8 verifyResult = (UINT8)HSM_VERIFY_FAILURE;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_SIGNATURE_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_EccEcdsaVerifyP521r1Start(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != ECC_BYTES_SIZE_P521R1)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.secondaryInputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else
        {
            if(job->jobPrimitiveInputOutput.secondaryInputLength == sizeof(ECC_ECDSA_P521R1_SIGN_t))
            {
                secInLenStartIdx = 0;
            }
            else if((job->jobPrimitiveInputOutput.secondaryInputLength == (ECC_BYTES_SIZE_P521R1 + 1) * 2)  // for Java signature - anti-negative exception
                    && (job->jobPrimitiveInputOutput.secondaryInputPtr[0] == 0u) && (job->jobPrimitiveInputOutput.secondaryInputPtr[ECC_BYTES_SIZE_P521R1 + 1] == 0u))
            {
                secInLenStartIdx = 1;
            }
            else
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }

            if(result == E_OK)
            {
                EccEcdsaP521r1Sign_Convert_Crypto_to_Hsm(job->jobPrimitiveInputOutput.secondaryInputPtr, secInLenStartIdx, &sign);
                HsmDrvResult = HSM_EccEcdsaVerifyP521r1Update(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, job->jobPrimitiveInputOutput.inputPtr, (const ECC_ECDSA_P521R1_SIGN_t *)&sign);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        // job->jobPrimiritveInputOut.outputPtr: Generated Signature
        if (job->jobPrimitiveInputOutput.verifyPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_EccEcdsaVerifyP521r1Finish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, (UINT8 *)&verifyResult));
            if (result == E_OK)
            {
                if (verifyResult == (UINT8)HSM_VERIFY_SUCCESS)
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_OK;
                }
                else
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
                }
            }
            else
            {
                *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
            }
        }

        if (result != E_OK)
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}

Std_ReturnType HaeHsm_Primitive_EccEcdsaVerifyP521r1( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    Crypto_JobType primitiveJob;
    /*
     * The array used for Digest and Secret Number is 68 bytes in size and requires zero padding at the front.
     * The actual size of the Digest is 64 bytes.
     */
    uint8 digest[ECC_BYTES_SIZE_P521R1];
    uint32 digestLength = SHA512_DIGEST_SIZE;

    HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
    primitiveJob.jobPrimitiveInputOutput.mode           = job->jobPrimitiveInputOutput.mode;
    primitiveJob.jobPrimitiveInputOutput.inputPtr       = job->jobPrimitiveInputOutput.inputPtr;
    primitiveJob.jobPrimitiveInputOutput.inputLength    = job->jobPrimitiveInputOutput.inputLength;
    primitiveJob.jobRedirectionInfoRef                  = NULL;

    if((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0)
    {
        HaeModule_Crypto_Memset((uint8 *)digest, 0, (uint32)sizeof(digest));
        primitiveJob.jobPrimitiveInputOutput.outputPtr          = (uint8*)&digest[(ECC_BYTES_SIZE_P521R1 - SHA512_DIGEST_SIZE)];
        primitiveJob.jobPrimitiveInputOutput.outputLengthPtr    = (uint32*)&digestLength;
    }

    result = HaeHsm_Primitive_Sha512(PrimitiveData, &primitiveJob);
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        HaeModule_Crypto_Memset((uint8 *)&primitiveJob, 0, (uint32)sizeof(primitiveJob));
        primitiveJob.jobPrimitiveInputOutput.mode               = CRYPTO_OPERATIONMODE_SINGLECALL;
        primitiveJob.jobPrimitiveInputOutput.inputPtr           = (uint8*)digest;
        primitiveJob.jobPrimitiveInputOutput.inputLength        = (uint32)ECC_BYTES_SIZE_P521R1;
        primitiveJob.jobPrimitiveInputOutput.secondaryInputPtr  = job->jobPrimitiveInputOutput.secondaryInputPtr;
        primitiveJob.jobPrimitiveInputOutput.secondaryInputLength   = job->jobPrimitiveInputOutput.secondaryInputLength;
        primitiveJob.jobPrimitiveInputOutput.verifyPtr          = job->jobPrimitiveInputOutput.verifyPtr;
        primitiveJob.cryptoKeyId                                = job->cryptoKeyId;

        result = HaeHsm_Primitive_Internal_EccEcdsaVerifyP521r1(PrimitiveData, &primitiveJob);
        if(result != E_OK)
        {
            /* In this design, if it's CRYPTO_E_BUSY, we can't wait and try again. */
            result = E_NOT_OK;
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_ECCEDDSAVERIFYED448_SUPPORT
Std_ReturnType HaeHsm_Primitive_EccEddsaVerifyEd448( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    Std_ReturnType HsmDrvResult;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;
    uint16 keyNum;
    uint32 secInLenStartIdx = 0;
    ECC_EDDSA_ED448_SIGN_t sign;
    uint32 i, index;
    volatile uint32 timeout = 0;
    UINT8 verifyResult = (UINT8)HSM_VERIFY_FAILURE;
    HAEMODULE_EDDSA_ED448_INTPUT_t HsmEccEddsaEd448Input;
    CryptoKeyElement* Element;

    // Start
    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        Element = HaeModule_Crypto_Get_KeyElement(job->cryptoKeyId, CRYPTO_KE_SIGNATURE_KEY);
        if(Element == NULL)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else if(Element->CryptoKeyElementHsmKeyType == HAEHSM_KEY_TYPE_NONE)
        {
            HaeModule_Det_ReportRuntimeError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_RE_KEY_NOT_AVAILABLE);
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            keyNum = Element->CryptoKeyElementHsmKeyIndex;
            result = HSM_DRIVER_RETURN(HSM_EccEddsaVerifyEd448Start(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, keyNum));
        }
    }

    // Update
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0) && (result == E_OK))
    {
        if (job->jobPrimitiveInputOutput.inputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.inputLength != sizeof(HAEMODULE_EDDSA_ED448_INTPUT_t))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else if (job->jobPrimitiveInputOutput.secondaryInputPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else
        {
            if(job->jobPrimitiveInputOutput.secondaryInputLength == sizeof(ECC_EDDSA_ED448_SIGN_t)))
            {
                secInLenStartIdx = 0;
            }
            else if((job->jobPrimitiveInputOutput.secondaryInputLength == (((ED448_SIGN_BYTES / 2) + 1) * 2))
                    && (job->jobPrimitiveInputOutput.secondaryInputPtr[0] == 0u) && (job->jobPrimitiveInputOutput.secondaryInputPtr[(ED448_SIGN_BYTES / 2) + 1] == 0u)) // for Java signature - anti-negative exception
            {
                secInLenStartIdx = 1;
            }
            else
            {
                HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
                result = E_NOT_OK;
            }

            if(result == E_OK)
            {
                index = secInLenStartIdx;
                for(i = 0; i < ED448_SIGN_BYTES / 2; i++)
                {
                    sign.s[i] = job->jobPrimitiveInputOutput.secondaryInputPtr[index];
                    index++;
                }
                index += secInLenStartIdx;
                for(; i < ED448_SIGN_BYTES; i++)
                {
                    sign.s[i] = job->jobPrimitiveInputOutput.secondaryInputPtr[index];
                    index++;
                }

                HaeModule_Crypto_Memcpy((uint8 *)&HsmEccEddsaEd448Input, (const uint8 *)job->jobPrimitiveInputOutput.inputPtr, (uint32)sizeof(HAEMODULE_EDDSA_ED448_INTPUT_t));
                HsmDrvResult = HSM_EccEddsaVerifyEd448Update(&(getPrimitiveData(PrimitiveData))->HsmApiCtx,
                                                                HsmEccEddsaEd448Input.message, HsmEccEddsaEd448Input.messageLength,
                                                                HsmEccEddsaEd448Input.context, HsmEccEddsaEd448Input.contextLength,
                                                                (const ECC_EDDSA_ED448_SIGN_t *)&sign);
                if(HsmDrvResult == E_OK)
                {
                    timeout = 0;
                    do
                    {
                        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                        if (HsmDrvResult != HSM_E_WAIT)
                        {
                            break;
                        }
                        timeout++;
                    } while (timeout < WAIT_RESP_TIMEOUT);
                }

                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    // Finish
    if(((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0) && (result == E_OK))
    {
        // job->jobPrimiritveInputOut.outputPtr: Generated Signature
        if (job->jobPrimitiveInputOutput.verifyPtr == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_EccEddsaVerifyEd448Finish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, (UINT8 *)&verifyResult));
            if (result == E_OK)
            {
                if (verifyResult == (UINT8)HSM_VERIFY_SUCCESS)
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_OK;
                }
                else
                {
                    *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
                }
            }
            else
            {
                *job->jobPrimitiveInputOutput.verifyPtr = CRYPTO_E_VER_NOT_OK;
            }
        }

        if ((result != E_OK) && (result != CRYPTO_E_BUSY))
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        }
    }

    return result;
}
#endif

/*
* Random Number Generate
*/
#ifdef HAEHSM_PRIMITIVE_PSEUDORANDOMGENERATE_SUPPORT
Std_ReturnType HaeHsm_Primitive_PseudoRandomGenerate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;

    if (mode == (uint32)CRYPTO_OPERATIONMODE_SINGLECALL)
    {
        if ((job->jobPrimitiveInputOutput.outputPtr == NULL) || (job->jobPrimitiveInputOutput.outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((*job->jobPrimitiveInputOutput.outputLengthPtr == 0) || (*job->jobPrimitiveInputOutput.outputLengthPtr > 1024))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_PseudoRandomGenerate(job->jobPrimitiveInputOutput.outputPtr, *job->jobPrimitiveInputOutput.outputLengthPtr));
        }

    }
    else
    {
        result = E_NOT_OK;
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_CUSTOM_PSEUDORANDOMGENERATE_SUPPORT
Std_ReturnType HaeHsm_Primitive_Custom_PseudoRandomGenerate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    return HaeHsm_Primitive_PseudoRandomGenerate(PrimitiveData, job);
}
#endif

#ifdef HAEHSM_PRIMITIVE_TRUERANDOMGENERATE_SUPPORT
Std_ReturnType HaeHsm_Primitive_TrueRandomGenerate( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    uint32 mode = (uint32)job->jobPrimitiveInputOutput.mode;

    if (mode == (uint32)CRYPTO_OPERATIONMODE_SINGLECALL)
    {
        if ((job->jobPrimitiveInputOutput.outputPtr == NULL) || (job->jobPrimitiveInputOutput.outputLengthPtr == NULL))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_POINTER);
            result = E_NOT_OK;
        }
        else if ((*job->jobPrimitiveInputOutput.outputLengthPtr == 0) || (*job->jobPrimitiveInputOutput.outputLengthPtr > 1024))
        {
            HaeModule_Det_ReportError(CRYPTO_API_PROCESSJOB, CRYPTO_DET_E_PARAM_VALUE);
            result = E_NOT_OK;
        }
        else
        {
            result = HSM_DRIVER_RETURN(HSM_TrueRandomGenerate(job->jobPrimitiveInputOutput.outputPtr, *job->jobPrimitiveInputOutput.outputLengthPtr));
        }

    }
    else
    {
        result = E_NOT_OK;
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_KEYDERIVE_SUPPORT
Std_ReturnType HaeHsm_Primtive_Crypto_Pbkdf2_Start( uint32 state, CryptoPrimitiveData *PrimitiveData, uint32 cryptoKeyId)
{
    Std_ReturnType result;
    Std_ReturnType HsmDrvResult;
    HaeHsmPrimitiveData *HsmPrimitiveData = getPrimitiveData(PrimitiveData);
    CryptoKey *Key;
    CryptoKeyElement *Element;
    uint16 keyNum;
    union {
        uint8   uaValue[4];
        uint8   ubValue;
        uint16  uwValue;
        uint32  ulValue;
    } iteration;
    uint32 i;

    if(state == (uint32)HAEMODULE_PRIMITIVESTATE_INIT)
    {
        HaeModule_Crypto_Memset((uint8 *)&HsmPrimitiveData->var.Pbkdf2.start, 0, (uint32)sizeof(HaeHsmPrimitiveVariable_Pbkdf2_Start));

        Key = HaeModule_Crypto_Get_Key(cryptoKeyId);
        if(Key == NULL)
        {
            HaeModule_Det_ReportError(CRYPTO_API_KEYDERIVE, CRYPTO_DET_E_PARAM_HANDLE);
            result = E_NOT_OK;
        }
        else if(Key->CryptoKeyState != TRUE)
        {
            /* [SWS_Crypto_00039] If a key is in the state invalid,
            crypto services which make use of that key, shall return with CRYPTO_E_KEY_NOT_VALID. */
            result = CRYPTO_E_KEY_NOT_VALID;
        }
        else
        {
            Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYDERIVATION_HSMKEYINDEX);
            if((Element != NULL)
            && (Element->CryptoKeyElementSize != 0)
            && (Element->CryptoKeyElementValue != NULL)
            && (Element->CryptoKeyElementValueState == TRUE)
            )
            {
                for(i = 0; i < (uint32)sizeof(iteration.uaValue); i++)
                {
                    iteration.uaValue[i] = 0;
                }

                for(i = 0; (i < (uint32)sizeof(iteration.uaValue)) && (i < Element->CryptoKeyElementSize); i++)
                {
                    iteration.uaValue[i] = Element->CryptoKeyElementValue[i];
                }

                switch( Element->CryptoKeyElementSize )
                {
                    case 1:
                        keyNum = (uint16)iteration.ubValue;
                        break;
                    case 2:
                        keyNum = (uint16)iteration.uwValue;
                        break;
                    case 4:
                    default:
                        keyNum = (uint16)iteration.ulValue;
                        break;
                }

                HsmPrimitiveData->var.Pbkdf2.start.keyNum = keyNum;
            }
            else
            {
                HsmPrimitiveData->var.Pbkdf2.start.keyNum = 0;
            }

            result = E_OK;
            HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_START);
        }
    }
    else if(state == (uint32)HAEMODULE_PRIMITIVESTATE_START)
    {
        HsmDrvResult = HSM_Pbkdf2Start(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, HsmPrimitiveData->var.Pbkdf2.start.keyNum);
        if(HsmDrvResult == E_OK)
        {
            /* When all states in the mode are finished, we call HaeHsm_PrimitiveState_End function to end directly. */
            result = E_OK;
            HaeHsm_PrimitiveState_End((uint32)CRYPTO_OPERATIONMODE_START);
        }
        else if(HsmDrvResult == HSM_E_BUSY)
        {
            HsmPrimitiveData->var.Pbkdf2.start.timeout++;
            if(HsmPrimitiveData->var.Pbkdf2.start.timeout < WAIT_BUSY_TIMEOUT)
            {
                /* Set to retry the current mode state. */
                result = E_OK;
                HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_START);
            }
            else
            {
                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }
        }
        else
        {
            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }
    }
    else
    {
        result = E_NOT_OK;
    }

    /* If the return value is an error, the mode ends. */
    if(result != E_OK)
    {
        HaeHsm_PrimitiveState_End(CRYPTO_OPERATIONMODE_START);
    }

    return result;
}

Std_ReturnType HaeHsm_Primtive_Crypto_Pbkdf2_Update( uint32 state, CryptoPrimitiveData *PrimitiveData, uint32 cryptoKeyId, uint32 targetCryptoKeyId )
{
    Std_ReturnType result;
    Std_ReturnType HsmDrvResult;
    HaeHsmPrimitiveData *HsmPrimitiveData = getPrimitiveData(PrimitiveData);
    CryptoKey *targetKey;
    CryptoKeyElement *Element, *targetElement;
    union {
        uint8   uaValue[4];
        uint8   ubValue;
        uint16  uwValue;
        uint32  ulValue;
    } iteration;
    uint32 i;

    if(state == (uint32)HAEMODULE_PRIMITIVESTATE_INIT)
    {
        HaeModule_Crypto_Memset((uint8 *)&HsmPrimitiveData->var.Pbkdf2.update, 0, (uint32)sizeof(HaeHsmPrimitiveVariable_Pbkdf2_Update));
        HsmPrimitiveData->var.Pbkdf2.update.password    = NULL;
        HsmPrimitiveData->var.Pbkdf2.update.pLen        = ((uint32)0xFFFFFFFFU);
        HsmPrimitiveData->var.Pbkdf2.update.salt        = NULL;
        HsmPrimitiveData->var.Pbkdf2.update.sLen        = ((uint32)0xFFFFFFFFU);
        HsmPrimitiveData->var.Pbkdf2.update.icount      = ((uint32)0xFFFFFFFFU);
        HsmPrimitiveData->var.Pbkdf2.update.derivedKey  = NULL;
        HsmPrimitiveData->var.Pbkdf2.update.dkLen       = ((uint32)0xFFFFFFFFU);

        if(HsmPrimitiveData->var.Pbkdf2.start.keyNum == 0)
        {
            Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYDERIVATION_PASSWORD);
            if((Element != NULL)
            && (Element->CryptoKeyElementValue != NULL)
            && (Element->CryptoKeyElementValueState == TRUE)
            )
            {
                HsmPrimitiveData->var.Pbkdf2.update.password = Element->CryptoKeyElementValue;
                if(Element->CryptoKeyElementAllowPartialAccess == TRUE)
                {
                    HsmPrimitiveData->var.Pbkdf2.update.pLen = Element->CryptoKeyElementValueSize;
                }
                else
                {
                    HsmPrimitiveData->var.Pbkdf2.update.pLen = Element->CryptoKeyElementSize;
                }
            }
        }
        else
        {
            HsmPrimitiveData->var.Pbkdf2.update.password = NULL;
            HsmPrimitiveData->var.Pbkdf2.update.pLen     = 0;
        }

        Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYDERIVATION_SALT);
        if((Element != NULL)
            && (Element->CryptoKeyElementValue != NULL)
            && (Element->CryptoKeyElementValueState == TRUE)
        )
        {
            HsmPrimitiveData->var.Pbkdf2.update.salt = Element->CryptoKeyElementValue;
            if(Element->CryptoKeyElementAllowPartialAccess == TRUE)
            {
                HsmPrimitiveData->var.Pbkdf2.update.sLen = Element->CryptoKeyElementValueSize;
            }
            else
            {
                HsmPrimitiveData->var.Pbkdf2.update.sLen = Element->CryptoKeyElementSize;
            }
        }

        Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYDERIVATION_ITERATIONS);
        if((Element != NULL)
            && (Element->CryptoKeyElementSize != 0)
            && (Element->CryptoKeyElementValue != NULL)
            && (Element->CryptoKeyElementValueState == TRUE)
        )
        {
            for(i = 0; i < (uint32)sizeof(iteration.uaValue); i++)
            {
                iteration.uaValue[i] = 0;
            }

            for(i = 0; (i < (uint32)sizeof(iteration.uaValue)) && (i < Element->CryptoKeyElementSize); i++)
            {
                iteration.uaValue[i] = Element->CryptoKeyElementValue[i];
            }

            switch( Element->CryptoKeyElementSize )
            {
                case 1:
                    HsmPrimitiveData->var.Pbkdf2.update.icount = (uint32)iteration.ubValue;
                    break;
                case 2:
                    HsmPrimitiveData->var.Pbkdf2.update.icount = (uint32)iteration.uwValue;
                    break;
                case 4:
                default:
                    HsmPrimitiveData->var.Pbkdf2.update.icount = (uint32)iteration.ulValue;
                    break;
            }
        }

        if(((HsmPrimitiveData->var.Pbkdf2.start.keyNum == 0) && ((HsmPrimitiveData->var.Pbkdf2.update.password == NULL) || (HsmPrimitiveData->var.Pbkdf2.update.pLen == ((uint32)0xFFFFFFFFU))))
        || (HsmPrimitiveData->var.Pbkdf2.update.salt == NULL) 
        || (HsmPrimitiveData->var.Pbkdf2.update.sLen == ((uint32)0xFFFFFFFFU)) 
        || (HsmPrimitiveData->var.Pbkdf2.update.icount == ((uint32)0xFFFFFFFFU)))
        {
            result = CRYPTO_E_KEY_EMPTY;
        }
        else
        {
            targetKey = HaeModule_Crypto_Get_Key(targetCryptoKeyId);
            if(targetKey == NULL)
            {
                HaeModule_Det_ReportError(CRYPTO_API_KEYDERIVE, CRYPTO_DET_E_PARAM_HANDLE);
                result = E_NOT_OK;
            }
            else
            {
                targetElement = HaeModule_Crypto_Get_KeyElement(targetCryptoKeyId, 1);
                if((targetElement != NULL)
                && (targetElement->CryptoKeyElementWriteAccess == CRYPTO_WA_ALLOWED)
                && (targetElement->CryptoKeyElementValue != NULL)
                )
                {
                    HsmPrimitiveData->var.Pbkdf2.update.derivedKey = targetElement->CryptoKeyElementValue;
                    HsmPrimitiveData->var.Pbkdf2.update.dkLen      = targetElement->CryptoKeyElementSize;
                }

                if((HsmPrimitiveData->var.Pbkdf2.update.derivedKey == NULL) || (HsmPrimitiveData->var.Pbkdf2.update.dkLen == ((uint32)0xFFFFFFFFU)))
                {
                    result = E_NOT_OK;
                }
                else
                {
                    result = E_OK;
                    HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_UPDATE);
                }
            }
        }
    }
    else if(state == (uint32)HAEMODULE_PRIMITIVESTATE_UPDATE)
    {
        HsmDrvResult = HSM_Pbkdf2Update(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, HsmPrimitiveData->var.Pbkdf2.start.keyNum, 
                                                        HsmPrimitiveData->var.Pbkdf2.update.dkLen, 
                                                        HsmPrimitiveData->var.Pbkdf2.update.password, HsmPrimitiveData->var.Pbkdf2.update.pLen, 
                                                        HsmPrimitiveData->var.Pbkdf2.update.salt, HsmPrimitiveData->var.Pbkdf2.update.sLen, 
                                                        HsmPrimitiveData->var.Pbkdf2.update.icount);
        if(HsmDrvResult == E_OK)
        {
            HsmPrimitiveData->var.Pbkdf2.update.timeout = 0;
            result = E_OK;
            HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_UPDATE_WAITRESP);
        }
        else if(HsmDrvResult == HSM_E_BUSY)
        {
            HsmPrimitiveData->var.Pbkdf2.update.timeout++;
            if (HsmPrimitiveData->var.Pbkdf2.update.timeout < WAIT_BUSY_TIMEOUT)
            {
                /* Set to retry the current mode state. */
                result = E_OK;
                HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_UPDATE);
            }
            else
            {
                HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }
        }
        else
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }
    }
    else if(state == (uint32)HAEMODULE_PRIMITIVESTATE_UPDATE_WAITRESP)
    {
        HsmDrvResult = HSM_WaitResp((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
        if (HsmDrvResult == E_OK)
        {
            result = E_OK;
            HaeHsm_PrimitiveState_End(CRYPTO_OPERATIONMODE_UPDATE);
        }
        else if (HsmDrvResult == HSM_E_WAIT)
        {
            HsmPrimitiveData->var.Pbkdf2.update.timeout++;
            if (HsmPrimitiveData->var.Pbkdf2.update.timeout < WAIT_RESP_TIMEOUT)
            {
                /* Set to retry the current mode state. */
                result = E_OK;
                HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_UPDATE_WAITRESP);
            }
            else
            {
                HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }
        }
        else
        {
            HSM_CancelJob((getPrimitiveData(PrimitiveData))->HsmApiCtx.jobId);
            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }
    }
    else
    {
        result = E_NOT_OK;
    }

    /* If the return value is an error, the mode ends. */
    if(result != E_OK)
    {
        HaeHsm_PrimitiveState_End(CRYPTO_OPERATIONMODE_UPDATE);
    }

    return result;
}

Std_ReturnType HaeHsm_Primtive_Crypto_Pbkdf2_Finish( uint32 state, CryptoPrimitiveData *PrimitiveData, uint32 targetCryptoKeyId )
{
    Std_ReturnType result;
    Std_ReturnType HsmDrvResult;
    HaeHsmPrimitiveData *HsmPrimitiveData = getPrimitiveData(PrimitiveData);
    CryptoKey *targetKey;
    CryptoKeyElement *targetElement;

    if(state == (uint32)HAEMODULE_PRIMITIVESTATE_INIT)
    {
        HaeModule_Crypto_Memset((uint8 *)&HsmPrimitiveData->var.Pbkdf2.finish, 0, (uint32)sizeof(HaeHsmPrimitiveVariable_Pbkdf2_Finish));

        result = E_OK;
        HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_FINISH);
    }
    else if(state == (uint32)HAEMODULE_PRIMITIVESTATE_FINISH)
    {
        HsmDrvResult = HSM_Pbkdf2Finish(&(getPrimitiveData(PrimitiveData))->HsmApiCtx, 
                                    HsmPrimitiveData->var.Pbkdf2.update.dkLen, 
                                    HsmPrimitiveData->var.Pbkdf2.update.derivedKey);
        if(HsmDrvResult == E_OK)
        {
            targetKey = HaeModule_Crypto_Get_Key(targetCryptoKeyId);
            if(targetKey == NULL)
            {
                HaeModule_Det_ReportError(CRYPTO_API_KEYDERIVE, CRYPTO_DET_E_PARAM_HANDLE);
                result = E_NOT_OK;
            }
            else
            {
                targetElement = HaeModule_Crypto_Get_KeyElement(targetCryptoKeyId, 1);
                if(targetElement != NULL)
                {
                    targetElement->CryptoKeyElementValueSize = HsmPrimitiveData->var.Pbkdf2.update.dkLen;
                    targetElement->CryptoKeyElementValueState = TRUE;
                    targetKey->CryptoKeyState = FALSE;

                     /* When all states in the mode are finished, we call HaeHsm_PrimitiveState_End function to end directly. */
                    result = E_OK;
                    HaeHsm_PrimitiveState_End((uint32)CRYPTO_OPERATIONMODE_FINISH);
                }
                else
                {
                    result = E_NOT_OK;
                }
            }
        }
        else if(HsmDrvResult == HSM_E_BUSY)
        {
            HsmPrimitiveData->var.Pbkdf2.finish.timeout++;
            if (HsmPrimitiveData->var.Pbkdf2.finish.timeout < WAIT_BUSY_TIMEOUT)
            {
                /* Set to retry the current mode state. */
                result = E_OK;
                HaeHsm_PrimitiveState_Set((uint32)HAEMODULE_PRIMITIVESTATE_FINISH);
            }
            else
            {
                result = HSM_DRIVER_RETURN(HsmDrvResult);
            }
        }
        else
        {
            result = HSM_DRIVER_RETURN(HsmDrvResult);
        }
    }
    else
    {
        result = E_NOT_OK;
    }

    /* If the return value is an error, the mode ends. */
    if(result != E_OK)
    {
        HaeHsm_PrimitiveState_End(CRYPTO_OPERATIONMODE_FINISH);
    }

    return result;
}

Std_ReturnType HaeHsm_Primtive_Crypto_Pbkdf2( uint32 mode, uint32 state, CryptoPrimitiveData *PrimitiveData, 
                                            uint32 cryptoKeyId, uint32 targetCryptoKeyId )
{
    Std_ReturnType result;

    if((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0)
    {
        result = HaeHsm_Primtive_Crypto_Pbkdf2_Start(state, PrimitiveData, cryptoKeyId);
    }
    else if((mode & (uint32)CRYPTO_OPERATIONMODE_UPDATE) != 0)
    {
        result = HaeHsm_Primtive_Crypto_Pbkdf2_Update(state, PrimitiveData, cryptoKeyId, targetCryptoKeyId);
    }
    else if((mode & (uint32)CRYPTO_OPERATIONMODE_FINISH) != 0)
    {
        result = HaeHsm_Primtive_Crypto_Pbkdf2_Finish(state, PrimitiveData, targetCryptoKeyId);
    }
    else
    {
        result = E_NOT_OK;
        HaeHsm_PrimitiveState_End(mode);
    }

    return result;
}
#endif

#if defined(HAEHSM_PRIMITIVE_KEYDERIVE_SUPPORT)
Std_ReturnType HaeHsm_Primitive_Crypto_KeyDerive( uint32 cryptoKeyId, uint32 targetCryptoKeyId, uint32 AlgorithmType )
{
    Std_ReturnType result = E_NOT_OK;
    uint32 mode  = CRYPTO_OPERATIONMODE_SINGLECALL;
    uint32 state = 0;
    boolean JobProcessing = TRUE;

    if (AlgorithmType == HAEMODULE_CRYPTO_PBKDF2_HMAC_SHA256_HSM)
    {
        HaeHsm_Primitive_SetState(mode, state);

        do
        {
            result = HaeHsm_Primtive_Crypto_Pbkdf2(mode, state, (CryptoPrimitiveData *)getPrimitiveData(NULL), cryptoKeyId, targetCryptoKeyId);

            HaeHsm_PrimitiveState_Get(&mode, &state);
            if(state == (uint32)HAEMODULE_PRIMITIVESTATE_END)
            {
                if(result == E_OK)
                {
                    if(mode == 0)
                    {
                        /* End Job */
                        JobProcessing = FALSE;
                    }
                    else
                    {
                        /* Continue until primitive mode ends */
                        state = HAEMODULE_PRIMITIVESTATE_INIT;
                    }
                }
                else
                {
                    /* This is a case where an error occurred and the job was terminated */
                    JobProcessing = FALSE;
                }
            }
        } while ( JobProcessing == TRUE );
    }

    return result;
}
#endif

/*
 * Key related service
 */
#ifdef HAEHSM_PRIMITIVE_KEYDERIVE_SUPPORT
Std_ReturnType HaeHsm_Primitive_KeyDerive( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType result = E_OK;
    uint32 mode;
    uint32 state;

    HaeHsm_PrimitiveState_Get(&mode, &state);

    if(((mode & (uint32)CRYPTO_OPERATIONMODE_START) != 0) && (state == (uint32)HAEMODULE_PRIMITIVESTATE_INIT))
    {
        if(CRYPTO_GET_RESOURCE(&ResType_HaeModuleApi) != TRUE)
        {
            result = CRYPTO_E_BUSY;
        }
        /* This function should always be checked in the last position. */
        else if(HaeModule_CryptoKeyId_Lock(job->cryptoKeyId) != TRUE)
        {
            CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
            result = CRYPTO_E_BUSY;
        }
        /* This function should always be checked in the last position. */
        else if(HaeModule_CryptoKeyId_Lock(job->targetCryptoKeyId) != TRUE)
        {
            HaeModule_CryptoKeyId_UnLock(job->cryptoKeyId);
            CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
            result = CRYPTO_E_BUSY;
        }
        else
        {
            result = E_OK;
        }
    }

    if(result == E_OK)
    {
        result = HaeHsm_Primtive_Crypto_Pbkdf2(mode, state, PrimitiveData, job->cryptoKeyId, job->targetCryptoKeyId);

        HaeHsm_PrimitiveState_Get(&mode, &state);
        if(state == (uint32)HAEMODULE_PRIMITIVESTATE_END)
        {
        	if((result != E_OK) || (mode == 0))
            {
                HaeModule_CryptoKeyId_UnLock(job->targetCryptoKeyId);
                HaeModule_CryptoKeyId_UnLock(job->cryptoKeyId);
                CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
            }
        }
    }

    return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_RSAPKCS3DHKEYPAIRGEN_SUPPORT
static Std_ReturnType HaeHsm_Primitive_Crypto_RsaPkcs3DHKeypairGenerate(const UINT8 *xa, const UINT8 *dh_base, const UINT8 *dh_prime, UINT8* public, UINT8 *private)
{
	Std_ReturnType result = E_OK;
	HSMAPI_CTX_t pkcs3Ctx;
    UINT8 privateDummy[HAC_RSA_BYTES_SIZE];
	volatile UINT32 timeout = 0;

    if(private == NULL)
    {
        private = privateDummy;
    }

	result = HSM_RsaPkcs3DHKeypairGenStart(&pkcs3Ctx);

    if(result == E_OK)
    {
        result = HSM_RsaPkcs3DHKeypairGenUpdate(&pkcs3Ctx, xa, dh_base, dh_prime);
        if (result == E_OK)
        {
            timeout = 0;
            do
            {
                result = HSM_WaitResp(pkcs3Ctx.jobId);
                if (result != HSM_E_WAIT)
                {
                    break;
                }
                timeout++;
            } while (timeout < WAIT_RESP_TIMEOUT);
        }

        if (result != E_OK)
        {
            HSM_CancelJob(pkcs3Ctx.jobId);
        }
    }

    if(result == E_OK)
    {
	    result = HSM_RsaPkcs3DHKeypairGenFinish(&pkcs3Ctx, public, private);
    }

	return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_RSAPKCS3DHSHAREDVALUEGEN_SUPPORT
Std_ReturnType HaeHsm_Primitive_Crypto_RsaPkcs3DHSharedValueGenerate(const UINT8* y, const UINT8* x, const UINT8* dh_prime, UINT8* secretValue)
{
	Std_ReturnType result = E_OK;
	HSMAPI_CTX_t pkcs3Ctx;
	volatile UINT32 timeout = 0;

	result = HSM_RsaPkcs3DHSharedValueGenStart(&pkcs3Ctx);
    if (result == E_OK)
    {
        result = HSM_RsaPkcs3DHSharedValueGenUpdate(&pkcs3Ctx, y, x, dh_prime);
        if (result == E_OK)
        {
            timeout = 0;
            do
            {
                result = HSM_WaitResp(pkcs3Ctx.jobId);
                if (result != HSM_E_WAIT)
                {
                    break;
                }
                timeout++;
            } while (timeout < WAIT_RESP_TIMEOUT);
        }

        if (result != E_OK)
        {
            HSM_CancelJob(pkcs3Ctx.jobId);
        }
    }

    if (result == E_OK)
    {
        result = HSM_RsaPkcs3DHSharedValueGenFinish(&pkcs3Ctx, secretValue);
    }

	return result;
}
#endif

#if defined(HAEHSM_PRIMITIVE_RSAPKCS3DHKEYPAIRGEN_SUPPORT)
Std_ReturnType HaeHsm_Primitive_Crypto_KeyExchangeCalcPubVal( uint32 cryptoKeyId, uint8* publicValuePtr, uint32* publicValueLengthPtr, uint32 AlgorithmType )
{
    Std_ReturnType Result = E_OK;
    CryptoKey *Key;
    CryptoKeyElement *Element;
    #ifdef HAEHSM_PRIMITIVE_RSAPKCS3DHKEYPAIRGEN_SUPPORT
    CryptoKeyElement *BaseElement       = NULL;
    #endif
    CryptoKeyElement *PrivKeyElement    = NULL;
    CryptoKeyElement *OwnPubKeyElement  = NULL;

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
        Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_PRIVKEY);
        if((Element != NULL)
        && (Element->CryptoKeyElementValue != NULL)
        && (Element->CryptoKeyElementValueState == TRUE)
        && (Element->CryptoKeyElementReadAccess == CRYPTO_RA_ALLOWED))
        {
            PrivKeyElement = Element;
        }

        Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_OWNPUBKEY);
        if((Element != NULL)
        && (Element->CryptoKeyElementValue != NULL)
        && (Element->CryptoKeyElementValueState == TRUE)
        && (Element->CryptoKeyElementReadAccess == CRYPTO_RA_ALLOWED))
        {
            OwnPubKeyElement = Element;
        }

        if((PrivKeyElement == NULL) || (OwnPubKeyElement == NULL))
        {
            Result = CRYPTO_E_KEY_EMPTY;
        }
        else
        {
            Result = E_NOT_OK;
            if (AlgorithmType == HAEMODULE_CRYPTO_DH_HSM) {
                #ifdef HAEHSM_PRIMITIVE_RSAPKCS3DHKEYPAIRGEN_SUPPORT
                Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_BASE);
                if((Element != NULL)
                && (Element->CryptoKeyElementValue != NULL)
                && (Element->CryptoKeyElementValueState == TRUE)
                && (Element->CryptoKeyElementReadAccess == CRYPTO_RA_ALLOWED))
                {
                    BaseElement = Element;
                }

                if(BaseElement == NULL)
                {
                    Result = CRYPTO_E_KEY_EMPTY;
                }
                else if (BaseElement->CryptoKeyElementValueSize != (uint32)HAC_RSA_BYTES_SIZE)
                {
                    Result = CRYPTO_E_KEY_NOT_VALID;
                }
                else if(*publicValueLengthPtr < (uint32)HAC_RSA_BYTES_SIZE)
                {
                    HaeModule_Det_ReportError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_PARAM_VALUE);
                    Result = E_NOT_OK;
                }
                else if (OwnPubKeyElement->CryptoKeyElementValueSize != (uint32)HAC_RSA_BYTES_SIZE)
                {
                    Result = CRYPTO_E_KEY_NOT_VALID;
                }
                else
                {
                    Result = HSM_DRIVER_RETURN(HaeHsm_Primitive_Crypto_RsaPkcs3DHKeypairGenerate((uint8 *)PrivKeyElement->CryptoKeyElementValue,
                                                (uint8 *)OwnPubKeyElement->CryptoKeyElementValue,
                                                (uint8 *)BaseElement->CryptoKeyElementValue,
                                                publicValuePtr,
                                                NULL));
                    *publicValueLengthPtr = (uint32)HAC_RSA_BYTES_SIZE;
                }
                #else
                Result = E_NOT_OK;
                #endif
            }
        }
    }

    return Result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_RSAPKCS3DHKEYPAIRGEN_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs3DHKeypairGen( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType Result;

    if(CRYPTO_GET_RESOURCE(&ResType_HaeModuleApi) != TRUE)
    {
        Result = CRYPTO_E_BUSY;
    }
    /* This function should always be checked in the last position. */
    else if(HaeModule_CryptoKeyId_Lock(job->cryptoKeyId) != TRUE)
    {
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
        Result = CRYPTO_E_BUSY;
    }
    else
    {
        Result = HaeHsm_Primitive_Crypto_KeyExchangeCalcPubVal(job->cryptoKeyId,
                                            job->jobPrimitiveInputOutput.outputPtr,
                                            job->jobPrimitiveInputOutput.outputLengthPtr,
                                            HAEMODULE_CRYPTO_DH_HSM);

        HaeModule_CryptoKeyId_UnLock(job->cryptoKeyId);
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
    }

    return Result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_ECCECDHP256R1_SUPPORT
static Std_ReturnType HaeHsm_Primitive_Crypto_Ecdh_P256r1(const uint16 keyNum, const ECC_PUBLICKEY_t *pubkey, uint8 *secretValue)
{
	Std_ReturnType result = E_OK;
	HSMAPI_CTX_t eccCtx;
	volatile UINT32 timeout = 0;

    result = HSM_EccEcdhStart(&eccCtx, keyNum);
    if(result == E_OK)
    {
        result = HSM_EccEcdhUpdate(&eccCtx, pubkey);
        if(result == E_OK)
        {
            timeout = 0;
            do
            {
                result = HSM_WaitResp(eccCtx.jobId);
                if (result != HSM_E_WAIT)
                {
                    break;
                }
                timeout++;
            } while (timeout < WAIT_RESP_TIMEOUT);
        }

        if (result != E_OK)
        {
            HSM_CancelJob(eccCtx.jobId);
        }
    }

	if(result == E_OK)
    {
		result = HSM_EccEcdhFinish(&eccCtx, secretValue);
	}

	return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT
static void EccEcdhP521r1_PublicKey_Convert_Crypto_to_Hsm(const uint8 *cryptoPubkey, ECC_PUBLICKEY_P521R1_t *hsmPubkey)
{
    uint32 i, index;

    HaeModule_Crypto_Memset((uint8 *)hsmPubkey, 0, (uint32)sizeof(ECC_PUBLICKEY_P521R1_t));
    index = 0;
    for(i = 2; i < (uint32)ECC_BYTES_SIZE_P521R1; i++)
    {
        hsmPubkey->x[i] = cryptoPubkey[index];
        index++;
    }
    for(i = 2; i < (uint32)ECC_BYTES_SIZE_P521R1; i++)
    {
        hsmPubkey->y[i] = cryptoPubkey[index];
        index++;
    }
}

static void EccEcdhP521r1_SecretValue_Convert_Hsm_to_Crypto(const uint8 *hsmSecretValue, uint8 *cryptoSecretValue)
{
    uint32 i, index;

    index = 0;
    for(i = 2; i < (uint32)ECC_BYTES_SIZE_P521R1; i++)
    {
        cryptoSecretValue[index] = hsmSecretValue[i];
        index++;
    }
}

static Std_ReturnType HaeHsm_Primitive_Crypto_Ecdh_P521r1(const uint16 keyNum, const ECC_PUBLICKEY_P521R1_t *pubkey, uint8 *secretValue)
{
	Std_ReturnType result = E_OK;
	HSMAPI_CTX_t eccCtx;
	volatile UINT32 timeout = 0;

    result = HSM_EccEcdhP521r1Start(&eccCtx, keyNum);
    if(result == E_OK)
    {
        result = HSM_EccEcdhP521r1Update(&eccCtx, pubkey);
        if(result == E_OK)
        {
            timeout = 0;
            do
            {
                result = HSM_WaitResp(eccCtx.jobId);
                if (result != HSM_E_WAIT)
                {
                    break;
                }
                timeout++;
            } while (timeout < WAIT_RESP_TIMEOUT);
        }

        if (result != E_OK)
        {
            HSM_CancelJob(eccCtx.jobId);
        }
    }

	if(result == E_OK)
    {
		result = HSM_EccEcdhP521r1Finish(&eccCtx, secretValue);
	}

	return result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT
static Std_ReturnType HaeHsm_Primitive_Crypto_Ecdh_X448(const uint16 keyNum, const ECC_PUBLICKEY_X448_t *pubkey, uint8 *secretValue)
{
	Std_ReturnType result = E_OK;
	HSMAPI_CTX_t eccCtx;
	volatile UINT32 timeout = 0;

    result = HSM_EccEcdhX448Start(&eccCtx, keyNum);
    if(result == E_OK)
    {
        result = HSM_EccEcdhX448Update(&eccCtx, pubkey);
        if(result == E_OK)
        {
            timeout = 0;
            do
            {
                result = HSM_WaitResp(eccCtx.jobId);
                if (result != HSM_E_WAIT)
                {
                    break;
                }
                timeout++;
            } while (timeout < WAIT_RESP_TIMEOUT);
        }

        if (result != E_OK)
        {
            HSM_CancelJob(eccCtx.jobId);
        }
    }

	if(result == E_OK)
    {
		result = HSM_EccEcdhX448Finish(&eccCtx, secretValue);
	}

	return result;
}
#endif

#if defined(HAEHSM_PRIMITIVE_RSAPKCS3DHSHAREDVALUEGEN_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDH_SUPPORT) \
    || defined(HAEHSM_PRIMITIVE_ECCECDHP256R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT) || defined(HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT)
Std_ReturnType HaeHsm_Primitive_Crypto_KeyExchangeCalcSecret( uint32 cryptoKeyId, const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength, uint32 AlgorithmType )
{
    Std_ReturnType Result = E_OK;
    CryptoKey *Key;
    CryptoKeyElement *Element;
    #ifdef HAEHSM_PRIMITIVE_RSAPKCS3DHSHAREDVALUEGEN_SUPPORT
    CryptoKeyElement *BaseElement       = NULL;
    CryptoKeyElement *PrivKeyElement    = NULL;
    #endif
    CryptoKeyElement *SharedValueElement= NULL;
    CryptoKeyElement *CurveTypeElement  = NULL;
    uint32 SharedValueSize = 0;
    uint32 CurveType;
    #ifdef HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT
    ECC_PUBLICKEY_P521R1_t EccPubkeyP521r1;
    uint8 EccEcdhP521r1_SecretValue[ECC_BYTES_SIZE_P521R1];
    #endif

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
        Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CYRPTO_KE_KEYEXCHANGE_SHAREDVALUE);
        if((Element != NULL)
        && (Element->CryptoKeyElementValue != NULL)
        && (Element->CryptoKeyElementWriteAccess == CRYPTO_WA_ALLOWED))
        {
            SharedValueElement = Element;
        }

        if(SharedValueElement == NULL)
        {
            Result = CRYPTO_E_KEY_EMPTY;
        }
        else
        {
            if(AlgorithmType == (uint32)HAEMODULE_CRYPTO_DH_HSM)
            {
                #ifdef HAEHSM_PRIMITIVE_RSAPKCS3DHSHAREDVALUEGEN_SUPPORT
                Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_PRIVKEY);
                if((Element != NULL)
                && (Element->CryptoKeyElementValue != NULL)
                && (Element->CryptoKeyElementValueState == TRUE)
                && (Element->CryptoKeyElementReadAccess == CRYPTO_RA_ALLOWED))
                {
                    PrivKeyElement = Element;
                }

                Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_BASE);
                if((Element != NULL)
                && (Element->CryptoKeyElementValue != NULL)
                && (Element->CryptoKeyElementValueState == TRUE)
                && (Element->CryptoKeyElementReadAccess == CRYPTO_RA_ALLOWED))
                {
                    BaseElement = Element;
                }

                if((PrivKeyElement == NULL) || (BaseElement == NULL))
                {
                    Result = CRYPTO_E_KEY_EMPTY;
                }
                else if (PrivKeyElement->CryptoKeyElementValueSize != HAC_RSA_BYTES_SIZE)
                {
                    Result = CRYPTO_E_KEY_NOT_VALID;
                }
                else if (BaseElement->CryptoKeyElementValueSize != (uint32)HAC_RSA_BYTES_SIZE)
                {
                    Result = CRYPTO_E_KEY_NOT_VALID;
                }
                else if(partnerPublicValueLength != (uint32)HAC_RSA_BYTES_SIZE)
                {
                    HaeModule_Det_ReportError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_PARAM_VALUE);
                    Result = E_NOT_OK;
                }
                else if (SharedValueElement->CryptoKeyElementSize < (uint32)HAC_RSA_BYTES_SIZE)
                {
                    HaeModule_Det_ReportRuntimeError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_RE_SMALL_BUFFER);
                    Result = CRYPTO_E_SMALL_BUFFER;
                }
                else
                {
                    Result = HSM_DRIVER_RETURN(HaeHsm_Primitive_Crypto_RsaPkcs3DHSharedValueGenerate(partnerPublicValuePtr,
                                                (uint8 *)PrivKeyElement->CryptoKeyElementValue,
                                                (uint8 *)BaseElement->CryptoKeyElementValue,
                                                (uint8 *)SharedValueElement->CryptoKeyElementValue));
                    SharedValueSize = (uint32)HAC_RSA_BYTES_SIZE;
                }
                #else
                Result = E_NOT_OK;
                #endif
            }
            else if(AlgorithmType == (uint32)HAEMODULE_CRYPTO_ECDH_HSM)
            {
                Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_CURVETYPE);
                if((Element != NULL)
                && (Element->CryptoKeyElementValue != NULL)
                && (Element->CryptoKeyElementValueState == TRUE)
                && (Element->CryptoKeyElementReadAccess == CRYPTO_RA_ALLOWED)
                && (Element->CryptoKeyElementValueSize == (uint32)sizeof(uint32)))
                {
                    CurveTypeElement = Element;
                }

                Element = HaeModule_Crypto_Get_KeyElement(cryptoKeyId, CRYPTO_KE_KEYEXCHANGE_PRIVKEY);
                if(Element != NULL)
                {
                    PrivKeyElement = Element;
                }

                if((CurveTypeElement == NULL) || (PrivKeyElement == NULL))
                {
                    Result = CRYPTO_E_KEY_EMPTY;
                }
                else
                {
                    HaeModule_Crypto_Memcpy((uint8 *)&CurveType, (const uint8 *)CurveTypeElement->CryptoKeyElementValue, (uint32)sizeof(uint32));
                    if(CurveType == (uint32)HAEMODULE_CRYPTO_CURVETYPE_P256R1)
                    {
                        if(PrivKeyElement->CryptoKeyElementHsmKeyType != HAEHSM_KEY_TYPE_NONE)
                        {
                            #ifdef HAEHSM_PRIMITIVE_ECCECDHP256R1_SUPPORT
                            if(partnerPublicValueLength != (uint32)sizeof(ECC_PUBLICKEY_t))
                            {
                                HaeModule_Det_ReportError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_PARAM_VALUE);
                                Result = E_NOT_OK;
                            }
                            else if (SharedValueElement->CryptoKeyElementSize < (uint32)ECC_BYTES_SIZE)
                            {
                                HaeModule_Det_ReportRuntimeError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_RE_SMALL_BUFFER);
                                Result = CRYPTO_E_SMALL_BUFFER;
                            }
                            else
                            {
                                Result = HSM_DRIVER_RETURN(HaeHsm_Primitive_Crypto_Ecdh_P256r1(PrivKeyElement->CryptoKeyElementHsmKeyIndex,
                                                            (ECC_PUBLICKEY_t *)partnerPublicValuePtr,
                                                            (uint8 *)SharedValueElement->CryptoKeyElementValue));
                                SharedValueSize = (uint32)ECC_BYTES_SIZE;
                            }
                            #else
                            Result = E_NOT_OK;
                            #endif
                        }
                        else
                        {
                            Result = E_NOT_OK;
                        }
                    }
                    else if(CurveType == (uint32)HAEMODULE_CRYPTO_CURVETYPE_P521R1)
                    {
                        if(PrivKeyElement->CryptoKeyElementHsmKeyType != HAEHSM_KEY_TYPE_NONE)
                        {
                            #ifdef HAEHSM_PRIMITIVE_ECCECDHP521R1_SUPPORT
                            if(partnerPublicValueLength != (uint32)HSM_CRYPTO_ECC_PUBLICKEY_P521R1_SIZE)
                            {
                                HaeModule_Det_ReportError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_PARAM_VALUE);
                                Result = E_NOT_OK;
                            }
                            else if (SharedValueElement->CryptoKeyElementSize < (uint32)HSM_CRYPTO_ECC_BYTES_SIZE_P521R1)
                            {
                                HaeModule_Det_ReportRuntimeError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_RE_SMALL_BUFFER);
                                Result = CRYPTO_E_SMALL_BUFFER;
                            }
                            else
                            {
                                EccEcdhP521r1_PublicKey_Convert_Crypto_to_Hsm(partnerPublicValuePtr, &EccPubkeyP521r1);
                                Result = HSM_DRIVER_RETURN(HaeHsm_Primitive_Crypto_Ecdh_P521r1(PrivKeyElement->CryptoKeyElementHsmKeyIndex,
                                                            (ECC_PUBLICKEY_P521R1_t *)&EccPubkeyP521r1,
                                                            (uint8 *)EccEcdhP521r1_SecretValue));

                                EccEcdhP521r1_SecretValue_Convert_Hsm_to_Crypto(EccEcdhP521r1_SecretValue, SharedValueElement->CryptoKeyElementValue);
                                SharedValueSize = (uint32)HSM_CRYPTO_ECC_BYTES_SIZE_P521R1;
                            }
                            #else
                            Result = E_NOT_OK;
                            #endif
                        }
                        else
                        {
                            Result = E_NOT_OK;
                        }
                    }
                    else if(CurveType == (uint32)HAEMODULE_CRYPTO_CURVETYPE_CURVE448)
                    {
                        if(PrivKeyElement->CryptoKeyElementHsmKeyType != HAEHSM_KEY_TYPE_NONE)
                        {
                            #ifdef HAEHSM_PRIMITIVE_ECCECDHX448_SUPPORT
                            if(partnerPublicValueLength != (uint32)sizeof(ECC_PUBLICKEY_X448_t))
                            {
                                HaeModule_Det_ReportError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_PARAM_VALUE);
                                Result = E_NOT_OK;
                            }
                            else if (SharedValueElement->CryptoKeyElementSize < (uint32)X448_BYTES)
                            {
                                HaeModule_Det_ReportRuntimeError(CRYPTO_API_KEYEXCHANGECALCSECRET, CRYPTO_DET_E_RE_SMALL_BUFFER);
                                Result = CRYPTO_E_SMALL_BUFFER;
                            }
                            else
                            {
                                Result = HSM_DRIVER_RETURN(HaeHsm_Primitive_Crypto_Ecdh_X448(PrivKeyElement->CryptoKeyElementHsmKeyIndex,
                                                            (ECC_PUBLICKEY_X448_t *)partnerPublicValuePtr,
                                                            (uint8 *)SharedValueElement->CryptoKeyElementValue));
                                SharedValueSize = (uint32)X448_BYTES;
                            }
                            #else
                            Result = E_NOT_OK;
                            #endif
                        }
                        else
                        {
                            Result = E_NOT_OK;
                        }
                    }
                    else
                    {
                        Result = E_NOT_OK;
                    }
                }
            }
            else
            {
                Result = E_NOT_OK;
            }

            if((Result == E_OK) && (SharedValueSize > 0))
            {
                SharedValueElement->CryptoKeyElementValueSize = SharedValueSize;
                SharedValueElement->CryptoKeyElementValueState = TRUE;
            }
        }

        if(Result == E_OK)
        {
            /* Key is updated, However, it is set to valid for user convenience. */
            Key->CryptoKeyState = TRUE;
        }
    }

    return Result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_RSAPKCS3DHSHAREDVALUEGEN_SUPPORT
Std_ReturnType HaeHsm_Primitive_RsaPkcs3DHSharedValueGen( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType Result;

    if(CRYPTO_GET_RESOURCE(&ResType_HaeModuleApi) != TRUE)
    {
        Result = CRYPTO_E_BUSY;
    }
    /* This function should always be checked in the last position. */
    else if(HaeModule_CryptoKeyId_Lock(job->cryptoKeyId) != TRUE)
    {
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
        Result = CRYPTO_E_BUSY;
    }
    else
    {
        Result = HaeHsm_Primitive_Crypto_KeyExchangeCalcSecret(job->cryptoKeyId,
                                            job->jobPrimitiveInputOutput.inputPtr,
                                            job->jobPrimitiveInputOutput.inputLength,
                                            HAEMODULE_CRYPTO_DH_HSM);

        HaeModule_CryptoKeyId_UnLock(job->cryptoKeyId);
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
    }

    return Result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_ECCECDH_SUPPORT
Std_ReturnType HaeHsm_Primitive_EccEcdh( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType Result;

    if(CRYPTO_GET_RESOURCE(&ResType_HaeModuleApi) != TRUE)
    {
        Result = CRYPTO_E_BUSY;
    }
    /* This function should always be checked in the last position. */
    else if(HaeModule_CryptoKeyId_Lock(job->cryptoKeyId) != TRUE)
    {
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
        Result = CRYPTO_E_BUSY;
    }
    else
    {
        Result = HaeHsm_Primitive_Crypto_KeyExchangeCalcSecret(job->cryptoKeyId,
                                            job->jobPrimitiveInputOutput.inputPtr,
                                            job->jobPrimitiveInputOutput.inputLength,
                                            HAEMODULE_CRYPTO_ECDH_HSM);

         HaeModule_CryptoKeyId_UnLock(job->cryptoKeyId);
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
    }

    return Result;
}
#endif

#ifdef HAEHSM_PRIMITIVE_KEYSETVALID_SUPPORT
Std_ReturnType HaeHsm_Primitive_KeySetValid( CryptoPrimitiveData *PrimitiveData, Crypto_JobType* job )
{
    Std_ReturnType Result;

    if(CRYPTO_GET_RESOURCE(&ResType_HaeModuleApi) == TRUE)
    {
        Result = HaeModule_Crypto_KeySetValid(job->cryptoKeyId);
        CRYPTO_RELEASE_RESOURCE(&ResType_HaeModuleApi);
    }
    else
    {
        Result = CRYPTO_E_BUSY;
    }

    return Result;
}
#endif
#define CRYPTO_76_HAEMODULE_STOP_SEC_CODE
#include "Crypto_76_HaeModule_MemMap.h"

