/*!
  @file Crypto_76_HaeModule.h
  @brief Crypto interface API header file
  @note Copyright 2020 by HYUNDAI AUTOEVER Corp. All rights reserved.
*/
#ifndef CRYPTO_HAEMODULE_H
#define CRYPTO_HAEMODULE_H

#if 0 /* mobilgene doesn't support this header file */
#include "StandardTypes.h"
#else
#include "Std_Types.h"
#endif
#include "Csm.h"
#include "CryIf.h"
#include "Det.h"

#include "Crypto_76_HaeModule_Cfg.h"

/* [SWS_Crypto_91016] */
/* Description: Configuration data structure of CryIf module */
typedef struct
{
    // The content of the configuration data structure is implementation specific.
    uint32 dummy;
} Crypto_76_HaeModule_ConfigType;


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
/* mobilgene calls this function to initialize driver */
void Crypto_76_HaeModule_Init( const Crypto_76_HaeModule_ConfigType* configPtr );

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
#if (CRYPTO_76_HAEMODULE_CRYPTOVERSIONINFOAPI_VALUE == TRUE)
void Crypto_76_HaeModule_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif

/*!
  @brief Performs the crypto primitive, that is configured in the job parameter.
  @details Service ID[hex]: 0x03 \n
        Sync/Async: Sync or Async, depends on the job configuration \n
        Reentrancy: Reentrant \n
        [SWS_Crypto_00057] If the module is not initialized and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_ProcessJob shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00058] If the parameter objectId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00059] If the parameter job is a null pointer and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_POINTER to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00064] If the parameter job->jobPrimitiveInfo->primitiveInfo->service is not supported by the Crypto Driver Object \n
            and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK \n
        [SWS_Crypto_00201] If the parameter job->jobPrimitiveInfo->primitiveInfo->service is set to \n
            CRYPTO_KEYSETVALID, CRYPTO_RANDOMSEED, CRYPTO_KEYGENERATE, CRYPTO_KEYDERIVE, CRYPTO_KEYEXCHANGECALCPUBVAL, \n
            CRYPTO_KEYEXCHANGECALCSECRET, CRYPTO_CERTIFICATEPARSE of CRYPTO_CERTIFICATEVERIFY, the parameter job->cryptoKeyId must be in range; \n
            else the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to DET and return E_NOT_OK. \n
        [SWS_Crypto_00202] If the parameter job->jobPrimitiveInfo->primitiveInfo->service is set to CRYPTO_KEYDERIVE or CRYPTO_CERTIFICATEVERIFY, \n
            the parameter job->cryptoTargetKeyId must be in range; else the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to DET and return E_NOT_OK \n
        [SWS_Crypto_00065] If job->jobPrimitiveInfo->primitiveInfo->service is set to CRYPTO_HASH or CRYPTO_MACGENERATE, \n
            the parameter job->jobPrimitiveInfo->primitiveInfo->resultLength is required. \n
            If the configured result length of the job is smaller than the result length of the chosen algorithm, \n
            the most significant bits of the result shall be truncated to the configured result length. \n
        [SWS_Crypto_00067] If the parameter job->jobPrimitiveInfo->primitiveInfo->algorithm (with its variation in family, keyLength and mode) \n
            is not supported by the Crypto Driver Object and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_ProcessJob shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
            Depending of the crypto service configured in job->jobPrimitiveInfo-> primitiveInfo->service, different parameters of job->jobPrimitiveInput are required to be set with valid values. \n
            The table in SWS_Crypto_00071 specifies which parameters are required or optional for a service in different modes. The following requirements specify the behavior if a required member is a null pointer. \n
        [SWS_Crypto_00070] If a pointer to a buffer is required as an argument, but it is a null pointer, the Crypto_ProcessJob() function shall report CRYPTO_E_PARAM_POINTER to the DET \n
            if development error detection for the Crypto Driver is enabled, and return E_NOT_OK. \n
        [SWS_Crypto_00142] If a length pointer is required as an argument, but the value, which is pointed by the length pointer is zero, and if development error detection for the Crypto Driver is enabled, \n
            the Crypto_ProcessJob() function report CRYPTO_E_PARAM_VALUE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00072] All crypto services listed in Crypto_ServiceInfoType except of CRYPTO_HASH, and CRYPTO_RANDOMGENERATE \n
            require a key represented as a key identifier. \n
        [SWS_Crypto_00134] If the crypto primitive requires input data, its memory location is referred by the pointer job->jobPrimitiveInput.inputPtr. \n
            On calling Crypto_ProcessJob, the length of this data is stored in job->jobPrimitiveInput.inputLength. \n
        [SWS_Crypto_00203] If job->jobRedirectionInfoRef is not a NULLPTR and the configuration bit for the inputRedirection, \n
            secondaryInputRedirection and/or tertiaryInputRedirection is set within job-> jobRedirectionInfoRef->redirectionConfig, \n
            then the corresponding key element buffer located by job-> jobRedirectionInfoRef->inputKeyId+ job-> jobRedirectionInfoRef->inputKeyElementId, \n
            job-> jobRedirectionInfoRef->secondaryInputKeyId+ job-> jobRedirectionInfoRef->secondaryInputKeyElementId, and/or jobRedirectionInfoRef->tertiaryInputKeyId+ job-> jobRedirectionInfoRef->tertiaryInputKeyElementId \n
            and its length shall be used. If in addition input data is provided together with valid re-direction information \n
            and the crypto operation allows a data operation on both input data and key element data (e.g. for hash or MAC operation), \n
            then both data shall be processed. The key element data is always processed first, followed by the input data. \n
        [SWS_Crypto_00135] If the crypto primitive requires a buffer for the result, its memory location is referred by the pointer job->jobPrimitiveInput.outputPtr. \n
            On calling this function, job->jobPrimitiveInput. outputLengthPtr shall contain the size of the associated buffer. \n
            When the request has finished, the actual length of the returned value shall be stored. \n
        [SWS_Crypto_00136] If the buffer job->jobPrimitiveInput.outputPtr or job->jobPrimitiveInput.secondaryOutputPtr is too small, \n
            or in case of input/output re-direction the corresponding key element buffer is too small, to store the result of the request, \n
            CRYPTO_E_SMALL_BUFFER shall be returned and the function shall additionally report the runtime error CRYPTO_E_RE_SMALL_BUFFER. \n
        [SWS_Crypto_00204] If job->jobRedirectionInfoRef is not a NULLPTR and the configuration bit for the outputRedirection and/or secondaryoutputRedirection is set within job-> jobRedirectionInfoRef->redirectionConfig, \n
            then the corresponding key element buffer located by job-> jobRedirectionInfoRef->outputKeyId + job-> jobRedirectionInfoRef->outputKeyElementId and/or job-> jobRedirectionInfoRef->secondaryOutputKeyId + job-> jobRedirectionInfoRef->secondaryOutputKeyElementId \n
            shall be used as output. The length of the respective key element shall be set according to the length of the output.
        [SWS_Crypto_00141] If the random generator service is chosen and the corresponding entropy, the function shall return CRYPTO_E_ENTROPY_EXHAUSTION. \n
            The function Crypto_ProcessJob shall additionally report the runtime error CRYPTO_E_RE_ENTROPY_EXHAUSTED.
  @param[in] objectId       Holds the identifier of the Crypto Driver Object.
  @param[in, out] job       Pointer to the configuration of the job. \n
                            Contains structures with job and primitive relevant information but also pointer to result buffers.
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed \n
        CRYPTO_E_BUSY: Request failed, Crypro Driver Object is busy \n
        CRYPTO_E_KEY_NOT_VALID: Request failed, the key is not valid \n
        CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key element has the wrong size \n
        CRYPTO_E_QUEUE_FULL: Request failed, the queue is full \n
        CRYPTO_E_KEY_READ_FAIL: The service request failed, because key element extraction is not allowed \n
        CRYPTO_E_KEY_WRITE_FAIL: The service request failed because the writing access failed \no
        CRYPTO_E_KEY_NOT_AVAILABLE: The service request failed because the key is not available \n
        CRYPTO_E_ENTROPY_EXHAUSTION: Request failed, the entropy is exhausted \n
        CRYPTO_E_SMALL_BUFFER: The provided buffer is too small to store the result \n
        CRYPTO_E_JOB_CANCELED: The service request failed because the synchronous Job has been canceled \n
        CRYPTO_E_KEY_EMPTY: Request failed because of uninitialized source key element
*/
Std_ReturnType Crypto_76_HaeModule_ProcessJob( uint32 objectId, Crypto_JobType* job );

/*!
  @brief This interface removes the provided job from the queue and cancels the processing of the job if possible.
  @details Service ID[hex]: 0x0E \n
        Sync/Async: Synchronous \n
        Reentrancy: Reentrant, but not for same Crypto Driver Object \n
        [SWS_Crypto_00123] If development error detection for the Crypto Driver is enabled, \n
            The function Crypto_CancelJob shall raise the error CRYPTO_E_UNINIT and return E_NOT_OK if the module is not yet initialized. \n
        [SWS_Crypto_00124] If development error detection for the Crypto Driver is enabled: \n
            The function Crypto_CancelJob shall raise the error CRYPTO_E_PARAM_HANDLE and return E_NOT_OK if the parameter objectId is out or range. \n
        [SWS_Crypto_00125] If development error detection for the Crypto Driver is enabled: \n
            The function Crypto_CancelJob shall raise the error CRYPTO_E_PARAM_POINTER and return E_NOT_OK if the parameter job is a null pointer. \n
        [SWS_Crypto_00214] If no errors are detected by Crypto Driver and the driver does currently not process this job, \n
            the service Crypto_CancelJob() shall return E_OK without any processing. \n
        [SWS_Crypto_00143] If no errors are detected by Crypto Driver and the driver is able to cancel the job immediately, \n
            the service Crypto_CancelJob() shall remove the job from the queue and cancel the job in the hardware. \n
            If the cancellation is successful E_OK shall be returned, otherwise it shall return E_NOT_OK. \n
        [SWS_Crypto_00183] If no errors are detected by Crypto Driver and the driver is not able to cancel the job (e.g. due to hardware limitations), \n
            the service Crypto_CancelJob() shall return CRYPTO_E_JOB_CANCELED.
  @param[in] objectId       Holds the identifier of the Crypto Driver Object.
  @param[in,out] job        Pointer to the configuration of the job. Contains structures with job and primitive relevant information.
  @return E_OK: Request successful, job has been removed. \n
        E_NOT_OK: Request failed, job couldn't be removed. \n
        CRYPTO_E_JOB_CANCELED: The job has been cancelled but is still processed. No results will be returned to the application.
*/
Std_ReturnType Crypto_76_HaeModule_CancelJob( uint32 objectId, Crypto_JobType* job );

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
Std_ReturnType Crypto_76_HaeModule_KeyElementSet( uint32 cryptoKeyId, uint32 keyElementId, const uint8* keyPtr, uint32 keyLength );

/*!
  @brief Sets the key state of the key identified by cryptoKeyId to valid.
  @details Service ID[hex]: 0x05 \n
        Sync/Async: Synchronous \n
        Reentrancy: Non Reentrant \n
        [SWS_Crypto_00196] If the module is not yet initialized and development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeySetValid shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00197] If parameter cryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeySetValid shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        If no errors are detected by Crypto Driver, the service Crypto_KeySetValid() sets the key cryptoKeyId to “valid”.
  @param[in] cryptoKeyId    Holds the identifier of the key which shall be set to valid.
  @return E_OK: Request successful \n
        E_NOT_OK: Request failed \n
        CRYPTO_E_BUSY: Request failed, Crypto Driver Object is busy
*/
Std_ReturnType Crypto_76_HaeModule_KeySetValid( uint32 cryptoKeyId );

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
Std_ReturnType Crypto_76_HaeModule_KeyElementGet( uint32 cryptoKeyId, uint32 keyElementId, uint8* resultPtr, uint32* resultLengthPtr );

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
Std_ReturnType Crypto_76_HaeModule_KeyElementCopy( uint32 cryptoKeyId, uint32 keyElementId, uint32 targetCryptoKeyId, uint32 targetKeyElementId );

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
Std_ReturnType Crypto_76_HaeModule_KeyElementPartialCopy( uint32 cryptoKeyId, uint32 keyElementId, uint32 keyElementSourceOffset, uint32 keyElementTargetOffset, uint32 keyElementCopyLength, uint32 targetCryptoKeyId, uint32 targetKeyElementId );

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
Std_ReturnType Crypto_76_HaeModule_KeyCopy( uint32 cryptoKeyId, uint32 targetCryptoKeyId );

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
Std_ReturnType Crypto_76_HaeModule_KeyElementIdsGet( uint32 cryptoKeyId, uint32* keyElementIdsPtr, uint32* keyElementIdsLengthPtr );

/*!
  @brief Not supported.
*/
Std_ReturnType Crypto_76_HaeModule_RandomSeed( uint32 cryptoKeyId, const uint8* seedPtr, uint32 seedLength );

/*!
  @brief Not supported.
*/
Std_ReturnType Crypto_76_HaeModule_KeyGenerate( uint32 cryptoKeyId );

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
Std_ReturnType Crypto_76_HaeModule_KeyDerive( uint32 cryptoKeyId, uint32 targetCryptoKeyId );

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
Std_ReturnType Crypto_76_HaeModule_KeyExchangePubValCalc( uint32 cryptoKeyId, uint8* publicValuePtr, uint32* publicValueLengthPtr );

/*!
  @brief Calculates the shared secret key for the key exchange with the key material of the key identified by the cryptoKeyId and the partner public key. \n
         The shared secret key is stored as a key element in the same key.
  @details Service ID[hex]: 0x0a \n
        Sync/Async: Synchronous \n
        Reentrancy: Reentrant, but not for the same cryptoKeyId \n
        [SWS_Crypto_00111] ⌈ If the module is not yet initialized and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyExchangeCalcSecret shall report CRYPTO_E_UNINIT to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00112] ⌈ If the parameter cryptoKeyId is out of range and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyExchangeCalcSecret shall report CRYPTO_E_PARAM_HANDLE to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00113] ⌈ If the parameter partnerPublicValuePtr is a null pointer and if development error detection for the Crypto Driver is enabled, \n
            the function Crypto_KeyExchangeCalcSecret shall report CRYPTO_E_PARAM_POINTER to the DET and return E_NOT_OK. \n
        [SWS_Crypto_00115] ⌈ If partnerPublicValueLength is zero and if development error detection for the Crypto Driver is enabled, \n
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
Std_ReturnType Crypto_76_HaeModule_KeyExchangeSecretCalc( uint32 cryptoKeyId, const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength );

#endif /* CRYPTO_HAEMODULE_H */
