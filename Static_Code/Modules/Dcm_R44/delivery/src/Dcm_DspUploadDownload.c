/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Dcm_DspUploadDownload.c                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Main processing for upload download data functional unit      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     24-Apr-2020   HueKM          Initial version                     **
** 0.0.2     16-Aug-2020   HueKM          Change get buffer size function     **
** 0.0.3     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.4     02-Nov-2020   HueKM          Changes made as per #16832          **
** 0.0.5     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.6     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.7.0   29-Dec-2022   LanhLT         Update code as per #CP44-1179       **
** 1.0.9     31-Mar-2023   LanhLT         Refer #CP44-1780                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_Ram.h"
#include "Dcm_DsdInternal.h"
#include "Dcm_Externals.h"
#include "Dcm_ReqRespHandling.h"
#include "Dcm_Utils.h"

#include "Dcm_DspUploadDownload.h"

/*******************************************************************************
**                            Macro Definition                                **
*******************************************************************************/
#if ((DCM_TRANSFER_DATA_SERVICE == STD_ON)  || \
     (DCM_TRANSFER_EXIT_SERVICE == STD_ON)  || \
     (DCM_FILE_TRANSFER_SERVICE == STD_ON)  || \
     (DCM_REQUEST_UPLOAD_SERVICE == STD_ON) || \
     (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON))
#define DCM_UPLOAD_DOWNLOAD_SERVICES_ENABLE
#endif

/*******************************************************************************
**                  Common macro to get operation status                      **
*******************************************************************************/
#ifdef DCM_UPLOAD_DOWNLOAD_SERVICES_ENABLE

/* polyspace-begin MISRA2012:D4.9 [Justified:Low] Justify with annotations */

#define DCM_UD_CLR_FLAG(i)        (Dcm_UdOpStatus[i] = DCM_UD_INITIAL)
#define DCM_UD_SET_PENDING(i)     (Dcm_UdOpStatus[i] = DCM_UD_PENDING)
#define DCM_UD_SET_FORCE_RCRRP(i) (Dcm_UdOpStatus[i] = DCM_UD_FORCE_RCRRP)

#define DCM_UD_IS_PENDING(i)      (Dcm_UdOpStatus[i] == DCM_UD_PENDING)
#define DCM_UD_IS_FORCE_RCRRP(i)  (Dcm_UdOpStatus[i] == DCM_UD_FORCE_RCRRP)

#define DCM_UD_IS_FLAG_SET(i)     (Dcm_UdOpStatus[i] != DCM_UD_INITIAL)
#define DCM_UD_IS_FLAG_CLEARED(i) (Dcm_UdOpStatus[i] == DCM_UD_INITIAL)

/* polyspace-end MISRA2012:D4.9 [Justified:Low] Justify with annotations */

typedef enum 
{
  #if (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
  DCM_DOWNLOAD_FLAG,
  #endif

  #if (DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
  DCM_UPLOAD_FLAG,
  #endif

  #if (DCM_TRANSFER_DATA_SERVICE == STD_ON)
  DCM_TRANSFER_DATA_FLAG,
  #endif

  #if (DCM_TRANSFER_EXIT_SERVICE == STD_ON)
  DCM_TRANSFER_EXIT_FLAG,
  #endif
  
  #if (DCM_FILE_TRANSFER_SERVICE == STD_ON)
  DCM_FILE_TRANSFER_FLAG,
  #endif

  /* If upload download services are enable, this value is greater than ZERO */
  DCM_UD_MAX_SERVICE_FLAG
} Dcm_UdServiceFlagType;

typedef enum 
{
  DCM_UD_INITIAL,
  DCM_UD_PENDING,
  DCM_UD_FORCE_RCRRP
} Dcm_UdOpStatusType;

typedef P2FUNC(void, DCM_CODE, Dcm_InternalProcessFuncType) (
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CODE, Dcm_CallProcessFuncType) (
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
static VAR(Dcm_UdOpStatusType, DCM_VAR) Dcm_UdOpStatus[DCM_UD_MAX_SERVICE_FLAG];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

/*******************************************************************************
**           Common data for request upload and download services             **
*******************************************************************************/
#if ((DCM_REQUEST_UPLOAD_SERVICE == STD_ON) || \
     (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON))

#define DCM_UD_BLOCK_LENGTH_SIZE ((uint8) 0x04)

/* TODO: Add new parameter to PDF file */
#define DCM_USE_MEMORY_IDENTIFIER (STD_OFF)

typedef struct
{
  uint32 memoryAddr;
  uint32 memorySize;
  uint32 blockLength;

  uint8 memoryId;
  uint8 dataFormatId;
} Dcm_MemoryInfoType;

typedef P2VAR(Dcm_MemoryInfoType, AUTOMATIC, DCM_APPL_DATA) Dcm_MemoryInfoPtrType;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
static VAR(Dcm_MemoryInfoType, DCM_VAR) Dcm_MemoryInfo;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif

/*******************************************************************************
**              Common data for request file transfer services                **
*******************************************************************************/
#if (DCM_FILE_TRANSFER_SERVICE == STD_ON)

typedef enum
{
  DCM_UNDEFINED_FILE_OPERATION,
  DCM_ADD_FILE,
  DCM_DELETE_FILE,
  DCM_REPLACE_FILE,
  DCM_READ_FILE,
  DCM_READ_DIR,
} Dcm_FileOperationType;

/* polyspace +1 MISRA2012:2.4 [Justified:Low] Justify with annotations */
typedef struct STagDcm_FileInfoType
{
  uint64 blockLength;
  uint64 fileSizeCompressed;
  uint64 fileSizeUnCompressedOrDirInfoLength;

  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pFilePathAndName;

  uint16 filePathAndNameLen;

  Dcm_FileOperationType operationType;

  uint8 dataFormatId;
} Dcm_FileInfoType;

typedef P2VAR(Dcm_FileInfoType, AUTOMATIC, DCM_APPL_DATA) Dcm_FileInfoPtrType;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
static VAR(Dcm_FileInfoType, DCM_VAR) Dcm_FileInfo;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif

/*******************************************************************************
**                   Common data for transfer data services                   **
*******************************************************************************/
#if (DCM_TRANSFER_DATA_SERVICE == STD_ON)

typedef enum
{
  DCM_UPLOAD_TRANSFER,
  DCM_DOWNLOAD_TRANSFER,
  DCM_READ_FILE_TRANSFER,
  DCM_WRITE_FILE_TRANSFER,
  DCM_NO_TRANSFER,
} Dcm_TransferType;

/* polyspace +1 MISRA2012:2.4 [Justified:Low] Justify with annotations */
typedef struct STagDcm_TransferDataType
{
  uint64 fileBlockLength;
  uint64 fileDataLen;
  uint64 remainFileSize;

  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataRead;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataWrite;
  
  uint32 dataBlockLength;
  uint32 remainMemSize;
  uint32 currentMemAddr;
  uint8 memoryId;

  Dcm_TransferType transferType;

  uint8 blockSeqCounter;
} Dcm_TransferDataType;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
static VAR(Dcm_TransferDataType, DCM_VAR) Dcm_TransferData;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif

/*******************************************************************************
**          Common data for request transfer exit services                    **
*******************************************************************************/
#if ((DCM_TRANSFER_EXIT_SERVICE == STD_ON) && (DCM_TRANSFER_REQUEST_PARAM_RECORD_USED == STD_ON))

typedef struct STagDcm_RequestTransferExitParamRecordType
{
  /* transferRequestParameterRecord in the request message after SID*/
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) transferRequestParameterRecord;

  /*output data for transferRequestParameterRecord*/
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) transferResponseParameterRecord;

  /* size of transferRequestParameterRecord */
  uint32 transferRequestParameterRecordSize;

  /* size of output data for transferRequestParameterRecord */
  uint32 transferResponseParameterRecordSize;

} Dcm_RequestTransferExitParamRecordType;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
static VAR(Dcm_RequestTransferExitParamRecordType, DCM_VAR) Dcm_RequestTransferExitParamRecordData;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif /*(DCM_TRANSFER_EXIT_SERVICE == STD_ON) && (DCM_TRANSFER_REQUEST_PARAM_RECORD_USED == STD_ON)*/


/*******************************************************************************
**                      Static Function Definition                            **
*******************************************************************************/
#ifdef DCM_UPLOAD_DOWNLOAD_SERVICES_ENABLE
static FUNC(void, DCM_CODE) Dcm_CheckProcessingDone(
  boolean syncType,
  Dcm_UdServiceFlagType flagType,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode);

static FUNC(void, DCM_CODE) Dcm_SendNrcRccrp(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);
#endif /* END OF DCM_UPLOAD_DOWNLOAD_SERVICES_ENABLE */

#if ((DCM_REQUEST_UPLOAD_SERVICE == STD_ON) || \
     (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_InitMemoryInfo(void);

static FUNC(void, DCM_CODE) Dcm_SetMemoryInfo(
  Dcm_MemoryInfoPtrType pMemInfo);

static FUNC(uint32, DCM_CODE) Dcm_GetMaxBufferSize(
  Dcm_UdServiceFlagType flagType,
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(boolean, DCM_CODE) Dcm_CheckAddrAndLenFormatId(
  uint8 addrAndLenFormatId);

#if (DCM_USE_MEMORY_IDENTIFIER == STD_ON)
static FUNC(boolean, DCM_CODE) Dcm_CheckMemoryIdentifier(
  Dcm_Uint8PtrType pReqData,
  Dcm_MemoryInfoPtrType pMemInfo);
#endif

#if (DCM_DEV_ERROR_DETECT == STD_ON)
static FUNC(boolean, DCM_CODE) Dcm_CheckBlockLength(
  Dcm_UdServiceFlagType flagType,
  Dcm_MsgContextPtrType pMsgContext);
#endif

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckUpDownRequest(
  Dcm_UdServiceFlagType flagType,
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_UpdateUpDownResponse(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_TriggerUploadDownloadProcess(
  Dcm_UdServiceFlagType flagType);
#endif /* END OF REQUEST DOWNLOAD AND REQUEST UPLOAD */

#if (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessDownloadFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_InternalProcessDownload(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);
#endif /* END OF REQUEST DOWNLOAD */

#if (DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessUploadFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_InternalProcessUpload(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);
#endif /* END OF REQUEST UPLOAD */

#if (DCM_FILE_TRANSFER_SERVICE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_InitFileInfo(void);

static FUNC(void, DCM_CODE) Dcm_SetFileInfo(
  Dcm_FileInfoPtrType pFileInfo);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckFileSizeParameterLength(
  uint8 fileSizeParameterLen);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckFileTransferRequest(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckAddOrRepFileRequest(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckDelFileOrReadDirRequest(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckReadFileRequest(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallFileTransferFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessAddFileFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessDeleteFileFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessReplaceFileFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessReadFileFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessReadDirFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_InternalProcessFileTransfer(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

static FUNC(boolean, DCM_CODE) Dcm_CheckFileTransferInfo(void);

static FUNC(boolean, DCM_CODE) Dcm_CheckAddOrRepFileInfo(void);

static FUNC(boolean, DCM_CODE) Dcm_CheckReadFileInfo(void);

static FUNC(boolean, DCM_CODE) Dcm_CheckReadDirInfo(void);

static FUNC(void, DCM_CODE) Dcm_UpdateFileTransferResponse(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_UpdateAddOrRepFileResponse(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_UpdateDeleteFileResponse(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_UpdateReadFileResponse(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_UpdateReadDirResponse(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_TriggerFileTransferProcess(void);
#endif /* END OF REQUEST FILE TRANSFER */

#if (DCM_TRANSFER_DATA_SERVICE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_InitTransferData(void);

static FUNC(void, DCM_CODE) Dcm_IncreaseBlockSequenceCounter(void);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) 
Dcm_CheckTransferDataRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_BooleanPtrType pRepeatBlock);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) 
Dcm_CheckTransferDataUploadRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_BooleanPtrType pRepeatBlock);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) 
Dcm_CheckTransferDataDownloadRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_BooleanPtrType pRepeatBlock);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE)
Dcm_CheckTransferDataReadFileRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_BooleanPtrType pRepeatBlock);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE)
Dcm_CheckTransferDataWriteFileRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_BooleanPtrType pRepeatBlock);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) 
Dcm_CheckBlockSequenceCounter(
  uint8 blockCounter,
  Dcm_BooleanPtrType pRepeatBlock);

static FUNC(void, DCM_CODE) Dcm_UpdateTransferDataUploadResponse(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_UpdateTransferDataDownloadResponse(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_UpdateTransferDataReadFileResponse(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_UpdateTransferDataWriteFileResponse(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_TransferDataRepeatBlock(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(Dcm_ReturnReadMemoryType, DCM_CODE)
Dcm_CallProcessTransferDataReadFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Dcm_ReturnWriteMemoryType, DCM_CODE)
Dcm_CallProcessTransferDataWriteFunc(
  Dcm_OpStatusType OpStatus,
  uint32 memSize,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallWriteFileFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallReadFileOrDirFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallTransferDataFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_InternalProcessTransferData(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_InternalProcessTransferRead(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_InternalProcessTransferWrite(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_InternalProcessReadFileOrDir(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_InternalProcessWriteFile(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_TRANSFER_EXIT_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckTransferExitRequest(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessTransferExitFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_InternalProcessTransferExit(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);
#endif /* END OF REQUEST TRANSFER EXIT */

#if ((DCM_TRANSFER_EXIT_SERVICE == STD_ON) && (DCM_TRANSFER_REQUEST_PARAM_RECORD_USED == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_RequestTransferExitWithParamRecord( 
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);
#endif /*((DCM_TRANSFER_EXIT_SERVICE == STD_ON) && (DCM_TRANSFER_REQUEST_PARAM_RECORD_USED == STD_ON))*/

#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_CheckProcessingDone                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check whether finish the service processing         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : flagType, syncType, pMsgContext, errorCode          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#ifdef DCM_UPLOAD_DOWNLOAD_SERVICES_ENABLE
static FUNC(void, DCM_CODE) Dcm_CheckProcessingDone(
  boolean syncType,
  Dcm_UdServiceFlagType flagType,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode)
{
  /* @Trace: Dcm_SUD_API_31706 */
  if (DCM_UD_IS_FLAG_CLEARED(flagType))
  {
    if (DCM_POS_RESP != errorCode)
    {
      /* @Trace: Dcm_SUD_API_31512 */
      Dcm_InternalSetNegResponse(pMsgContext, errorCode);
    }

    /* @Trace: Dcm_SUD_API_31513 */
    Dcm_InternalProcessingDone(pMsgContext, syncType);
  }
}

/*******************************************************************************
** Function Name        : Dcm_SendNrcRccrp                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Send the NRC 0x78 in case E_FORCE_RCRRP returned    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pErrorCode                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(void, DCM_CODE) Dcm_SendNrcRccrp(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Dcm_GusMaxNoOfForceRespPend++;

  if (Dcm_GusMaxNoOfForceRespPend >= (uint16) DCM_DIAG_RESP_MAX_NUM_RESPEND)
  {
    /* @Trace: Dcm_SUD_API_31660 */
    Dcm_GusMaxNoOfForceRespPend = (uint16) DCM_ZERO;

    *pErrorCode = DCM_E_GENERALREJECT;

    Dcm_CancelUploadDownloadServices();
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31661 */
    /* Get service id for response message */
    uint8 serviceId = (pMsgContext->idContext) & DCM_SID_MASK;

    Dcm_SetNegResp(serviceId, DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING);

    Dcm_TxRespStatus.ucNegResp = DCM_TRUE;
    Dcm_TxRespStatus.ucNeedFailedConfiramtion = DCM_TRUE;
    
    /* Send 0x78 from main function */    
    Dcm_GblPduRTransmitResponse = DCM_TRUE;
  }
}
#endif /* END OF DCM_UPLOAD_DOWNLOAD_SERVICES_ENABLE */

/*******************************************************************************
** Function Name        : Dcm_InitMemoryInfo                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize data for UDS 0x34 and 0x35 service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if ((DCM_REQUEST_UPLOAD_SERVICE == STD_ON) || \
     (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_InitMemoryInfo(void)
{
  /* @Trace: Dcm_SUD_API_31592 */
  Dcm_MemoryInfo.memoryAddr = 0U;
  Dcm_MemoryInfo.memorySize = 0U;
  Dcm_MemoryInfo.blockLength = 0U;
  Dcm_MemoryInfo.memoryId = 0U;
  Dcm_MemoryInfo.dataFormatId = 0U;
}

/*******************************************************************************
** Function Name        : Dcm_SetMemoryInfo                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set the data for UDS 0x34 and 0x35 service          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMemInfo                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(void, DCM_CODE) Dcm_SetMemoryInfo(
  Dcm_MemoryInfoPtrType pMemInfo)
{
  /* @Trace: Dcm_SUD_API_31707 */
  if (NULL_PTR != pMemInfo) 
  {
    /* @Trace: Dcm_SUD_API_31663 */
    Dcm_MemoryInfo = *pMemInfo;   
  }
}

/*******************************************************************************
** Function Name        : Dcm_GetMaxBufferSize                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the buffer size is configured in protocol       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : flagType, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(uint32, DCM_CODE) Dcm_GetMaxBufferSize(
  Dcm_UdServiceFlagType flagType,
  Dcm_MsgContextPtrType pMsgContext)
{
  uint32 bufferSize = 0U;

  #if (DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
  /* @Trace: Dcm_SUD_API_31585 */
  if (DCM_UPLOAD_FLAG == flagType)
  {
    /* @Trace: Dcm_SUD_API_31586 */
    bufferSize = Dcm_DsdInternal_GetBufferSize(
      pMsgContext->dcmRxPduId, DCM_BUFFER_KIND_TX);
  }
  #endif

  #if (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
  /* @Trace: Dcm_SUD_API_31588 */
  if (DCM_DOWNLOAD_FLAG == flagType)
  {
    /* @Trace: Dcm_SUD_API_31587 */
    bufferSize = Dcm_DsdInternal_GetBufferSize(
      pMsgContext->dcmRxPduId, DCM_BUFFER_KIND_RX);
  }
  #endif

  return bufferSize;
}

/*******************************************************************************
** Function Name        : Dcm_CheckAddrAndLenFormatId                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the address and length format identifier   **
**                        in request message is valid or not                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : addrAndLenFormatId                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_CheckAddrAndLenFormatId(
  uint8 addrAndLenFormatId)
{
  boolean retVal;
  
  #if (DCM_NUM_OF_MEM_TRANSFER_ADDR_LEN_FORMAT_ID != DCM_ZERO)
  uint8 idx;
  retVal = DCM_FALSE;
  for (idx = 0U; idx < (uint8) DCM_NUM_OF_MEM_TRANSFER_ADDR_LEN_FORMAT_ID; idx++)
  {
    if (addrAndLenFormatId == Dcm_GaaMemTransferAddrLenFormatId[idx])
    {
      /* @Trace: Dcm_SUD_API_31479 */
      retVal = DCM_TRUE;
      break;
    }
  }
  #else
  /* @Trace: Dcm_SUD_API_31477 */
  retVal = DCM_TRUE;
  DCM_UNUSED(addrAndLenFormatId);
  #endif

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_CheckMemoryIdentifier                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if memory identifier in the request message   **
**                        is valid or not                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : pReqData, pMemInfo                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DCM_USE_MEMORY_IDENTIFIER == STD_ON)
static FUNC(boolean, DCM_CODE) Dcm_CheckMemoryIdentifier(
  Dcm_Uint8PtrType pReqData,
  Dcm_MemoryInfoPtrType pMemInfo)
{
  /* @Trace: Dcm_SUD_API_31508 */
  boolean retVal = DCM_FALSE;

  /*
   * We assume that the memory identifier 
   * in the request message that is the part of memory address.
   * So, we will not increase the index of pReqData in main process function.
   */
  pReqData++;
  uint8 memoryId = *(pReqData);
  
  uint8 idx;
  for (idx = 0U; idx < (uint8) DCM_NUM_OF_MEM_TRANSFER_ID_CONFIG; idx++)
  {
    if (memoryId == Dcm_GaaMemTransferId[idx])
    {
      /* @Trace: Dcm_SUD_API_31510 */
      retVal = DCM_TRUE;
      pMemInfo->memoryId = memoryId;
      break;
    }
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CheckBlockLength                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the returned block length is exceed        **
**                        the maximum buffer size or not                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : serviceFlag, pMsgContext                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DCM_DEV_ERROR_DETECT == STD_ON)
static FUNC(boolean, DCM_CODE) Dcm_CheckBlockLength(
  Dcm_UdServiceFlagType flagType,
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_31482 */
  boolean retVal = DCM_TRUE;

  /*
   * The block length describe complete length in transferData service.
   * So, we will include SID and blockSequenceCounter parameter.
   */
  uint32 bufferSize = Dcm_GetMaxBufferSize(flagType, pMsgContext);

  if (Dcm_MemoryInfo.blockLength > bufferSize)
  {
    /* @Trace: Dcm_SUD_API_31481 */
    retVal = DCM_FALSE;

    /* @Trace: SWS_Dcm_01418 SWS_Dcm_01421 */
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_INTERFACE_BUFFER_OVERFLOW);
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CheckUpDownRequest                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check the request message of UDS 0x34 and 0x35      **
**                        is valid or not                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : serviceFlag, pMsgContext                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckUpDownRequest(
  Dcm_UdServiceFlagType flagType,
  Dcm_MsgContextPtrType pMsgContext)
{
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  uint8 addrAndLenFormatId;
  Dcm_MemoryInfoType memInfo;
  Dcm_Uint8PtrType pReqData = pMsgContext->reqData;

  /* Initialize value for memory identifier */
  memInfo.memoryId = 0U;

  /* Get dataFormatIdentifier */
  memInfo.dataFormatId = *(pReqData);

  /* Get addressAndLengthFormatIdentifier */
  pReqData++;
  addrAndLenFormatId = *(pReqData);
  
  /* @Trace: SWS_Dcm_00856 SWS_Dcm_00857 */
  if (DCM_FALSE == Dcm_CheckAddrAndLenFormatId(addrAndLenFormatId))
  {
    /* @Trace: Dcm_SUD_API_31561 */
    errorCode = DCM_E_REQUESTOUTOFRANGE;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31562 */
    uint8 memAddrBytes = DCM_GET_MEMORY_ADDR_BYTES(addrAndLenFormatId);
    uint8 memSizeBytes = DCM_GET_MEMORY_SIZE_BYTES(addrAndLenFormatId);

    if (pMsgContext->reqDataLen != ((uint32) memAddrBytes + memSizeBytes + DCM_TWO))
    {
      /* @Trace: Dcm_SUD_API_31563 */
      errorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    else
    {
      /* @Trace: SWS_Dcm_01057 SWS_Dcm_01055 */
      #if (DCM_USE_MEMORY_IDENTIFIER == STD_ON)
      if (DCM_FALSE == Dcm_CheckMemoryIdentifier(pReqData, &memInfo))
      {
        /* @Trace: Dcm_SUD_API_31564 */
        errorCode = DCM_E_REQUESTOUTOFRANGE;
      }
      else
      #endif
      {
        /* @Trace: Dcm_SUD_API_31565 */
        /* Get memory address, include the memory identifier if it is configured  */
        pReqData++;
        memInfo.memoryAddr = Dcm_RequestParameterToUint32(memAddrBytes, pReqData);
        
        /* Skip memAddrBytes to get memory size */
        pReqData = &pReqData[memAddrBytes];
        memInfo.memorySize = Dcm_RequestParameterToUint32(memSizeBytes, pReqData);

        /* @Trace: SWS_Dcm_01417 SWS_Dcm_01420 */
        memInfo.blockLength = Dcm_GetMaxBufferSize(flagType, pMsgContext);

        /* Update memory info to static variable for further process */
        Dcm_SetMemoryInfo(&memInfo);
      }
    }
  }

  return errorCode;
}

/*******************************************************************************
** Function Name        : Dcm_UpdateUpDownResponse                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fill the data of response message to pMsgContext    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_UpdateUpDownResponse(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_31693 */
  Dcm_Uint8PtrType pResData = pMsgContext->resData;

  /* The length of response message is 5 (exclude SID) */
  pMsgContext->resDataLen = 5U;

  /* The size of block length is 4 byte, we fill it to high nibble */
  pResData[0U] = DCM_UD_BLOCK_LENGTH_SIZE << 4U;
  Dcm_Uint32ToResponseParameter(
    DCM_UD_BLOCK_LENGTH_SIZE, Dcm_MemoryInfo.blockLength, &pResData[1U]);
}

/*******************************************************************************
** Function Name        : Dcm_TriggerUploadDownloadProcess                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Update the data for transfer data process           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : flagType                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_TriggerUploadDownloadProcess(
  Dcm_UdServiceFlagType flagType)
{
  #if (DCM_TRANSFER_DATA_SERVICE == STD_ON)
  #if (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
  if (DCM_DOWNLOAD_FLAG == flagType)
  {
    /* @Trace: Dcm_SUD_API_31675 */
    Dcm_TransferData.transferType = DCM_DOWNLOAD_TRANSFER;
  }
  #endif

  #if (DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
  if (DCM_UPLOAD_FLAG == flagType)
  {
    /* @Trace: Dcm_SUD_API_31676 */
    Dcm_TransferData.transferType = DCM_UPLOAD_TRANSFER;
  }
  #endif

  /* @Trace: Dcm_SUD_API_31677 */
  /* Copy data for transfer process */
  Dcm_IsBlockSeqCounterRollOver = DCM_FALSE;
  Dcm_TransferData.blockSeqCounter = 1U;
  Dcm_TransferData.remainMemSize = Dcm_MemoryInfo.memorySize;
  Dcm_TransferData.currentMemAddr = Dcm_MemoryInfo.memoryAddr;
  Dcm_TransferData.dataBlockLength = Dcm_MemoryInfo.blockLength;
  Dcm_TransferData.memoryId = Dcm_MemoryInfo.memoryId;
  #else
  DCM_UNUSED(flagType);
  #endif
}
#endif /* END OF REQUEST DOWNLOAD AND REQUEST UPLOAD */

/*******************************************************************************
** Function Name        : Dcm_CallProcessDownloadFunc                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call and get the return value of                    **
**                        xxx_ProcessRequestDownload() function               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessDownloadFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType retVal = E_NOT_OK;
  
  if (NULL_PTR != Dcm_GaaMemTransferFncConfig.pProcessRequestDownloadFnc)
  {
    /* @Trace: Dcm_SUD_API_31416 */
    retVal = Dcm_GaaMemTransferFncConfig.pProcessRequestDownloadFnc(
              OpStatus, 
              Dcm_MemoryInfo.dataFormatId,
              Dcm_MemoryInfo.memoryId, 
              Dcm_MemoryInfo.memoryAddr, 
              Dcm_MemoryInfo.memorySize,
              &(Dcm_MemoryInfo.blockLength), 
              pErrorCode);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31415 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_InternalProcessDownload                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal processing function for UDS 0x34 service   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_InternalProcessDownload(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_31599 */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00754. Dcm must be implement to cover all return values of Xxx_ProcessRequestDownload." */
  Std_ReturnType retVal = Dcm_CallProcessDownloadFunc(OpStatus, pErrorCode);

  switch (retVal)
  {
    case E_OK:
      /* @Trace: Dcm_SUD_API_31600 */
      DCM_UD_CLR_FLAG(DCM_DOWNLOAD_FLAG);

      #if (DCM_DEV_ERROR_DETECT == STD_ON)
      if (DCM_TRUE == Dcm_CheckBlockLength(DCM_DOWNLOAD_FLAG, pMsgContext))
      #endif
      {
        /* @Trace: Dcm_SUD_API_31601 */
        /* Clear the error code variable */
        *pErrorCode = DCM_POS_RESP;
        
        /* @Trace: SWS_Dcm_01419 */
        Dcm_UpdateUpDownResponse(pMsgContext);

        Dcm_TriggerUploadDownloadProcess(DCM_DOWNLOAD_FLAG);
      }
      break;

    case DCM_E_PENDING:
      /* @Trace: Dcm_SUD_API_31604 */
      DCM_UD_SET_PENDING(DCM_DOWNLOAD_FLAG);
      break;

    case DCM_E_FORCE_RCRRP:
      /* @Trace: SWS_Dcm_00528 */
      /* @Trace: Dcm_SUD_API_31605 */
      DCM_UD_SET_FORCE_RCRRP(DCM_DOWNLOAD_FLAG);
      Dcm_SendNrcRccrp(pMsgContext, pErrorCode);
      break;

    default: /* E_NOT_OK */
      /* @Trace: SWS_Dcm_00757 SWS_Dcm_01132 */
      /* @Trace: Dcm_SUD_API_31603 */
      /* The negative response code is updated in pErrorCode */
      DCM_UD_CLR_FLAG(DCM_DOWNLOAD_FLAG);
      break;
  }
 /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00754. Dcm must be implement to cover all return values of Xxx_ProcessRequestDownload." */
}

/*******************************************************************************
** Function Name        : Dcm_DcmRequestDownload                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main processing function for UDS 0x34 service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
/* @Trace: SRS_Diag_04033 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmRequestDownload(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_00496 */
  /* @Trace: Dcm_SUD_API_31568 */
  Std_ReturnType retVal = E_OK;
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  /* Clear the pending state before go to main process */
  DCM_UD_CLR_FLAG(DCM_DOWNLOAD_FLAG);

  errorCode = Dcm_CheckUpDownRequest(DCM_DOWNLOAD_FLAG, pMsgContext);
  if (DCM_POS_RESP == errorCode)
  {
    /* @Trace: Dcm_SUD_API_31569 */
    Dcm_InternalProcessDownload(DCM_INITIAL, pMsgContext, &errorCode);
  }

  Dcm_CheckProcessingDone(DCM_ASYNC_DONE, DCM_DOWNLOAD_FLAG, pMsgContext, errorCode);
  
  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return retVal;
}
#endif /* END OF REQUEST DOWNLOAD */

/*******************************************************************************
** Function Name        : Dcm_CallProcessUploadFunc                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call and get the return value of                    **
**                        xxx_ProcessRequestUpload() function                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessUploadFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType retVal = E_NOT_OK;
  if (NULL_PTR != Dcm_GaaMemTransferFncConfig.pProcessRequestUploadFnc)
  {
    /* @Trace: Dcm_SUD_API_31444 */
    retVal = Dcm_GaaMemTransferFncConfig.pProcessRequestUploadFnc(
              OpStatus, 
              Dcm_MemoryInfo.dataFormatId,
              Dcm_MemoryInfo.memoryId, 
              Dcm_MemoryInfo.memoryAddr, 
              Dcm_MemoryInfo.memorySize,
              &(Dcm_MemoryInfo.blockLength), 
              pErrorCode);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31443 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_InternalProcessUpload                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal processing function for UDS 0x35 service   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_InternalProcessUpload(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_31645 */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00756. Dcm must be implement to cover all return values of Xxx_ProcessRequestUpload." */
  Std_ReturnType retVal = Dcm_CallProcessUploadFunc(OpStatus, pErrorCode);

  switch (retVal)
  {
    case E_OK:
      /* @Trace: Dcm_SUD_API_31646 */
      DCM_UD_CLR_FLAG(DCM_UPLOAD_FLAG);

      #if (DCM_DEV_ERROR_DETECT == STD_ON)
      if (DCM_TRUE == Dcm_CheckBlockLength(DCM_UPLOAD_FLAG, pMsgContext))
      #endif
      {
        /* @Trace: Dcm_SUD_API_31647 */
        /* Clear the error code variable */
        *pErrorCode = DCM_POS_RESP;
        
        /* @Trace: SWS_Dcm_01422 */
        Dcm_UpdateUpDownResponse(pMsgContext);

        Dcm_TriggerUploadDownloadProcess(DCM_UPLOAD_FLAG);
      }
      break;

    case DCM_E_PENDING:
      /* @Trace: Dcm_SUD_API_31650 */
      DCM_UD_SET_PENDING(DCM_UPLOAD_FLAG);
      break;

    case DCM_E_FORCE_RCRRP:
      /* @Trace: SWS_Dcm_00528 */
      /* @Trace: Dcm_SUD_API_31651 */
      DCM_UD_SET_FORCE_RCRRP(DCM_UPLOAD_FLAG);
      Dcm_SendNrcRccrp(pMsgContext, pErrorCode);
      break;

    default: /*E_NOT_OK*/
      /* @Trace: SWS_Dcm_00758 SWS_Dcm_01133 */
      /* @Trace: Dcm_SUD_API_31649 */
      /* The negative response code is updated in pErrorCode */
      DCM_UD_CLR_FLAG(DCM_UPLOAD_FLAG);
      break;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00756. Dcm must be implement to cover all return values of Xxx_ProcessRequestUpload." */
}

/*******************************************************************************
** Function Name        : Dcm_DcmRequestUpload                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main processing function for UDS 0x35 service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
/* @Trace: SRS_Diag_04033 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmRequestUpload(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_00499 */
  /* @Trace: Dcm_SUD_API_31577 */
  Std_ReturnType retVal = E_OK;
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  /* Clear the pending state before go to main process */
  DCM_UD_CLR_FLAG(DCM_UPLOAD_FLAG);
  
  errorCode = Dcm_CheckUpDownRequest(DCM_UPLOAD_FLAG, pMsgContext);
  if (DCM_POS_RESP == errorCode)
  {
    /* @Trace: Dcm_SUD_API_31578 */
    Dcm_InternalProcessUpload(DCM_INITIAL, pMsgContext, &errorCode);
  }
  
  Dcm_CheckProcessingDone(DCM_ASYNC_DONE, DCM_UPLOAD_FLAG, pMsgContext, errorCode);
  
  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return retVal;
}
#endif /* END OF REQUEST UPLOAD */

/*******************************************************************************
** Function Name        : Dcm_InitFileInfo                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize data for UDS 0x38 service                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DCM_FILE_TRANSFER_SERVICE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_InitFileInfo(void)
{
  /* @Trace: Dcm_SUD_API_31591 */
  Dcm_FileInfo.blockLength = 0U;
  Dcm_FileInfo.fileSizeCompressed = 0U;
  Dcm_FileInfo.fileSizeUnCompressedOrDirInfoLength = 0U; 
  Dcm_FileInfo.pFilePathAndName = NULL_PTR;
  Dcm_FileInfo.filePathAndNameLen = 0U;
  Dcm_FileInfo.operationType = DCM_UNDEFINED_FILE_OPERATION;
  Dcm_FileInfo.dataFormatId = 0U;
}

/*******************************************************************************
** Function Name        : Dcm_SetFileInfo                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Set the data for UDS 0x38 service                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pFileInfo                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(void, DCM_CODE) Dcm_SetFileInfo(
  Dcm_FileInfoPtrType pFileInfo)
{
  /* @Trace: Dcm_SUD_API_31708 */
  if (NULL_PTR != pFileInfo) 
  {
    /* @Trace: Dcm_SUD_API_31662 */
    Dcm_FileInfo = *pFileInfo;
  }
}

/*******************************************************************************
** Function Name        : Dcm_CheckFileSizeParameterLength                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check whether the fileSizeParameterLength is valid  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : fileSizeParameterLen                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckFileSizeParameterLength(
  uint8 fileSizeParameterLen)
{
  /* @Trace: Dcm_SUD_API_31492 */
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;
  
  /* @Trace: SWS_Dcm_01448 */
  if ((fileSizeParameterLen < 0x01) || (fileSizeParameterLen > 0x08))
  {
    /* @Trace: Dcm_SUD_API_31493 */
    errorCode = DCM_E_REQUESTOUTOFRANGE;
  }  

  return errorCode;
}  

/*******************************************************************************
** Function Name        : Dcm_CheckFileTransferRequest                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the request message of UDS 0x38            **
**                        is valid or not                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckFileTransferRequest(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* polyspace +2 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;
  Dcm_FileOperationType operationType = (Dcm_FileOperationType) pMsgContext->reqData[0];

  switch (operationType) 
  {
    case DCM_ADD_FILE:
    case DCM_REPLACE_FILE:
      /* @Trace: Dcm_SUD_API_31503 */
      errorCode = Dcm_CheckAddOrRepFileRequest(pMsgContext);
      break;

    case DCM_READ_DIR:
    case DCM_DELETE_FILE:
      /* @Trace: Dcm_SUD_API_31504 */
      errorCode = Dcm_CheckDelFileOrReadDirRequest(pMsgContext);
      break;

    case DCM_READ_FILE:
      /* @Trace: Dcm_SUD_API_31505 */
      errorCode = Dcm_CheckReadFileRequest(pMsgContext);
      break;

    default:
      /* @Trace: SWS_Dcm_01449 */
      /* @Trace: Dcm_SUD_API_31506 */
      errorCode = DCM_E_REQUESTOUTOFRANGE;
      break;
  }

  return errorCode;
}

/*******************************************************************************
** Function Name        : Dcm_CheckAddOrRepFileRequest                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check request message in case the operation mode    **
**                        is add file or replace file                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckAddOrRepFileRequest(
  Dcm_MsgContextPtrType pMsgContext)
{
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;
  Dcm_Uint8PtrType pReqData = pMsgContext->reqData;

  uint8 fileSizeParameterLen;
  Dcm_FileInfoType fileInfo = {0U};

  /* Get modeOfOperation */
  /* polyspace +1 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
  fileInfo.operationType = (Dcm_FileOperationType) *(pReqData);

  /* Get filePathAndNameLength parameter from request message */
  pReqData++;
  fileInfo.filePathAndNameLen = Dcm_RequestParameterToUint16(2U, pReqData);
  
  /* Get a pointer to filePathAndName */
  pReqData = &pReqData[2U];
  fileInfo.pFilePathAndName = pReqData;

  /* Get dataFormatIdentifier */
  pReqData = &pReqData[fileInfo.filePathAndNameLen];
  fileInfo.dataFormatId = *(pReqData);

  /* Get fileSizeParameterLength */
  pReqData++;
  fileSizeParameterLen = *(pReqData);
  
  errorCode = Dcm_CheckFileSizeParameterLength(fileSizeParameterLen);
  if (DCM_POS_RESP == errorCode)
  {
    /* @Trace: Dcm_SUD_API_31472 */
    uint32 expectedLength = 
       (fileInfo.filePathAndNameLen + ((uint32) fileSizeParameterLen << DCM_ONE) + DCM_FIVE);
    
    /* Full length check */
    if (pMsgContext->reqDataLen != expectedLength)
    {
      /* @Trace: Dcm_SUD_API_31473 */
      errorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_31474 */
      /* Get fileSizeUnCompressed from the request message */
      pReqData++;
      fileInfo.fileSizeUnCompressedOrDirInfoLength = 
        Dcm_RequestParameterToUint64(fileSizeParameterLen, pReqData);

      /* Get fileSizeCompressed from the request message */
      pReqData = &pReqData[fileSizeParameterLen];
      fileInfo.fileSizeCompressed = 
        Dcm_RequestParameterToUint64(fileSizeParameterLen, pReqData);

      /* Update to static variable for further process */
      Dcm_SetFileInfo(&fileInfo);
    }
  }

  return errorCode;
}

/*******************************************************************************
** Function Name        : Dcm_CheckDelFileOrReadDirRequest                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check request message in case the operation mode    **
**                        is delete file or read directory                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckDelFileOrReadDirRequest(
  Dcm_MsgContextPtrType pMsgContext)
{
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;
  Dcm_Uint8PtrType pReqData = pMsgContext->reqData;

  Dcm_FileInfoType fileInfo = {0U};

  /* Get modeOfOperation */
  /* polyspace +1 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
  fileInfo.operationType = (Dcm_FileOperationType) *(pReqData);

  /* Get filePathAndNameLength parameter from request message */
  pReqData++;
  fileInfo.filePathAndNameLen = Dcm_RequestParameterToUint16(2U, pReqData);

  /* Get a pointer to filePathAndName */
  pReqData = &pReqData[2U];
  fileInfo.pFilePathAndName = pReqData;

  /* Full length check */
  if (pMsgContext->reqDataLen != ((uint32) fileInfo.filePathAndNameLen + DCM_THREE))
  {
    /* @Trace: Dcm_SUD_API_31490 */
    errorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31489 */
    /* Update to static variable for further process */
    Dcm_SetFileInfo(&fileInfo);
  }

  return errorCode;
}

/*******************************************************************************
** Function Name        : Dcm_CheckReadFileRequest                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check request message in case the operation mode    **
**                        is read file                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckReadFileRequest(
  Dcm_MsgContextPtrType pMsgContext)
{
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;
  Dcm_Uint8PtrType pReqData = pMsgContext->reqData;

  Dcm_FileInfoType fileInfo = {0U};

  /* Get modeOfOperation */
  /* polyspace +1 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
  fileInfo.operationType = (Dcm_FileOperationType) *(pReqData);

  /* Get filePathAndNameLength parameter from request message */
  pReqData++;
  fileInfo.filePathAndNameLen = Dcm_RequestParameterToUint16(2U, pReqData);

  /* Get a pointer to filePathAndName */
  pReqData = &pReqData[2U];
  fileInfo.pFilePathAndName = pReqData;

  /* Get dataFormatIdentifier */
  pReqData = &pReqData[fileInfo.filePathAndNameLen];
  fileInfo.dataFormatId = *(pReqData);

  if (pMsgContext->reqDataLen != ((uint32) fileInfo.filePathAndNameLen + DCM_FOUR))
  {
    /* @Trace: Dcm_SUD_API_31523 */
    errorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31522 */
    /* Update to static variable for further process */
    Dcm_SetFileInfo(&fileInfo);
  }

  return errorCode;
}

/*******************************************************************************
** Function Name        : Dcm_CallFileTransferFunc                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call processing function for UDS 0x38 service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallFileTransferFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_31400 */
  Std_ReturnType retVal = E_NOT_OK;

  switch (Dcm_FileInfo.operationType)
  {
    case DCM_ADD_FILE:
      /* @Trace: Dcm_SUD_API_31401 */
      retVal = Dcm_CallProcessAddFileFunc(OpStatus, pErrorCode);
      break;

    case DCM_DELETE_FILE:
      /* @Trace: Dcm_SUD_API_31402 */
      retVal = Dcm_CallProcessDeleteFileFunc(OpStatus, pErrorCode);
      break;

    case DCM_REPLACE_FILE:
      /* @Trace: Dcm_SUD_API_31403 */
      retVal = Dcm_CallProcessReplaceFileFunc(OpStatus, pErrorCode);
      break;
    
    case DCM_READ_FILE:
      /* @Trace: Dcm_SUD_API_31405 */
      retVal = Dcm_CallProcessReadFileFunc(OpStatus, pErrorCode);
      break;

    case DCM_READ_DIR:
      /* @Trace: Dcm_SUD_API_31404 */
      retVal = Dcm_CallProcessReadDirFunc(OpStatus, pErrorCode);
      break;

    default:
      /* No action in this case */
      break;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_CallProcessAddFileFunc                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call processing function in case the operation mode **
**                        is add file                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessAddFileFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType retVal = E_NOT_OK;

  if (NULL_PTR != Dcm_GaaFileTransferFncConfig.pProcessRequestAddFileFnc)
  {
    /* @Trace: SWS_Dcm_01446 SWS_Dcm_01447 */
    /* @Trace: Dcm_SUD_API_31408 */
    retVal = Dcm_GaaFileTransferFncConfig.pProcessRequestAddFileFnc(
          OpStatus,
          Dcm_FileInfo.filePathAndNameLen,
          Dcm_FileInfo.pFilePathAndName,
          Dcm_FileInfo.dataFormatId,
          Dcm_FileInfo.fileSizeUnCompressedOrDirInfoLength,
          Dcm_FileInfo.fileSizeCompressed,
          &(Dcm_FileInfo.blockLength),
          pErrorCode);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31407 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_CallProcessDeleteFileFunc                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call processing function in case the operation mode **
**                        is delete file                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessDeleteFileFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType retVal = E_NOT_OK;

  if (NULL_PTR != Dcm_GaaFileTransferFncConfig.pProcessRequestDeleteFileFnc)
  {
    /* @Trace: SWS_Dcm_01446 SWS_Dcm_01447 */
    /* @Trace: Dcm_SUD_API_31411 */
    retVal = Dcm_GaaFileTransferFncConfig.pProcessRequestDeleteFileFnc(
          OpStatus,
          Dcm_FileInfo.filePathAndNameLen,
          Dcm_FileInfo.pFilePathAndName,
          pErrorCode);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31412 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return retVal;
} 

/*******************************************************************************
** Function Name        : Dcm_CallProcessReplaceFileFunc                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call processing function in case the operation mode **
**                        is replace file                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessReplaceFileFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType retVal = E_NOT_OK;

  if (NULL_PTR != Dcm_GaaFileTransferFncConfig.pProcessRequestReplaceFileFnc)
  {
    /* @Trace: SWS_Dcm_01446 SWS_Dcm_01447 */
    /* @Trace: Dcm_SUD_API_31428 */
    retVal = Dcm_GaaFileTransferFncConfig.pProcessRequestReplaceFileFnc(
          OpStatus,
          Dcm_FileInfo.filePathAndNameLen,
          Dcm_FileInfo.pFilePathAndName,
          Dcm_FileInfo.dataFormatId,
          Dcm_FileInfo.fileSizeUnCompressedOrDirInfoLength,
          Dcm_FileInfo.fileSizeCompressed,
          &(Dcm_FileInfo.blockLength),
          pErrorCode);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31427 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return retVal;
} 

/*******************************************************************************
** Function Name        : Dcm_CallProcessReadFileFunc                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call processing function in case the operation mode **
**                        is read file                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessReadFileFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType retVal = E_NOT_OK;

  if (NULL_PTR != Dcm_GaaFileTransferFncConfig.pProcessRequestReadFileFnc)
  {
    /* @Trace: SWS_Dcm_01446 SWS_Dcm_01447 */
    /* @Trace: Dcm_SUD_API_31424 */
    retVal = Dcm_GaaFileTransferFncConfig.pProcessRequestReadFileFnc(
          OpStatus,
          Dcm_FileInfo.filePathAndNameLen,
          Dcm_FileInfo.pFilePathAndName,
          Dcm_FileInfo.dataFormatId,
          &(Dcm_FileInfo.fileSizeUnCompressedOrDirInfoLength),
          &(Dcm_FileInfo.fileSizeCompressed),
          &(Dcm_FileInfo.blockLength),
          pErrorCode);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31423 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return retVal;  
} 

/*******************************************************************************
** Function Name        : Dcm_CallProcessReadDirFunc                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call processing function in case the operation mode **
**                        is read directory                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessReadDirFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType retVal = E_NOT_OK;

  if (NULL_PTR != Dcm_GaaFileTransferFncConfig.pProcessRequestReadDirFnc)
  {
    /* @Trace: SWS_Dcm_01446 SWS_Dcm_01447 */
    /* @Trace: Dcm_SUD_API_31420 */
    retVal = Dcm_GaaFileTransferFncConfig.pProcessRequestReadDirFnc(
          OpStatus,
          Dcm_FileInfo.filePathAndNameLen,
          Dcm_FileInfo.pFilePathAndName,
          &(Dcm_FileInfo.fileSizeUnCompressedOrDirInfoLength),
          &(Dcm_FileInfo.blockLength),
          pErrorCode);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31419 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return retVal;
} 

/*******************************************************************************
** Function Name        : Dcm_InternalProcessFileTransfer                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal processing for UDS 0x38 service            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_InternalProcessFileTransfer(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* TODO:
  The conflict between DCM AR4.4 and ISO 14229-1 about the mean of block length
  + In AR4.4: 
  maxNumberOfBlockLength: max number of bytes to be included in the $36 request
  EXCLUDING the SID and the blockSequenceCounter
  + In ISO 14229-1:
  maxNumberOfBlockLength: the length reflects the complete message length,
  INCLUDING the SID and the data parameters present in the $36 request

  => So, I implemented according to ISO 14229-1,
  because the $34 and $35 is used blockLength parameter like the ISO.
  It can be a mistake of DCM AR4.4.
  */
  
  /* @Trace: SWS_Dcm_01450 SWS_Dcm_01451 SWS_Dcm_01452 SWS_Dcm_01453 SWS_Dcm_01454 */
  /* @Trace: Dcm_SUD_API_31607 */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_91078, SWS_Dcm_91079, SWS_Dcm_91080, SWS_Dcm_91081,
    Dcm must be implement to cover all return values of those functions." */
  Std_ReturnType retVal = Dcm_CallFileTransferFunc(OpStatus, pErrorCode);
  switch (retVal)
  {
    case E_OK:
      DCM_UD_CLR_FLAG(DCM_FILE_TRANSFER_FLAG);
      
      /* @Trace: SWS_Dcm_01457 SWS_Dcm_01458 */
      if (DCM_FALSE == Dcm_CheckFileTransferInfo())
      {
        /* @Trace: Dcm_SUD_API_31609 */
        *pErrorCode = DCM_E_GENERALREJECT;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_31610 */
        /* Clear the error code variable value */
        *pErrorCode = DCM_POS_RESP;
        
        /* @Trace: SWS_Dcm_01455 SWS_Dcm_01090 SWS_Dcm_01456 SWS_Dcm_01091 */
        Dcm_UpdateFileTransferResponse(pMsgContext);

        Dcm_TriggerFileTransferProcess();
      }
      break;

    case DCM_E_PENDING:
      /* @Trace: Dcm_SUD_API_31613 */
      DCM_UD_SET_PENDING(DCM_FILE_TRANSFER_FLAG);
      break;

    case DCM_E_FORCE_RCRRP:
      /* @Trace: SWS_Dcm_00528 */
      /* @Trace: Dcm_SUD_API_31614 */
      DCM_UD_SET_FORCE_RCRRP(DCM_FILE_TRANSFER_FLAG);
      Dcm_SendNrcRccrp(pMsgContext, pErrorCode);
      break;

    default: /* E_NOT_OK */
      /* @Trace: SWS_Dcm_01088 */
      /* @Trace: Dcm_SUD_API_31612 */
      /* The error code is updated in pErrorCode */
      DCM_UD_CLR_FLAG(DCM_FILE_TRANSFER_FLAG);
      break;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_91078, SWS_Dcm_91079, SWS_Dcm_91080, SWS_Dcm_91081,
    Dcm must be implement to cover all return values of those functions." */
}

/*******************************************************************************
** Function Name        : Dcm_CheckFileTransferInfo                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check the file information that returned form API   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_CheckFileTransferInfo(void)
{
  /* @Trace: Dcm_SUD_API_31495 */
  boolean retVal = DCM_FALSE;

  switch (Dcm_FileInfo.operationType)
  {
    case DCM_ADD_FILE:
    case DCM_REPLACE_FILE:
      /* @Trace: Dcm_SUD_API_31496 */
      retVal = Dcm_CheckAddOrRepFileInfo();
      break;

    case DCM_DELETE_FILE:
      /* @Trace: Dcm_SUD_API_31497 */
      /* No check file information for this case */
      retVal = DCM_TRUE;
      break;

    case DCM_READ_FILE:
      /* @Trace: Dcm_SUD_API_31498 */
      retVal = Dcm_CheckReadFileInfo();
      break;

    case DCM_READ_DIR:
      /* @Trace: Dcm_SUD_API_31499 */
      retVal = Dcm_CheckReadDirInfo();
      break;

    default:
      /* No action in this case */
      break;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_CheckAddOrRepFileInfo                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check the file information that returned form API   **
**                        in case the operation mode is add or replace file   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_CheckAddOrRepFileInfo(void)
{
  /* @Trace: Dcm_SUD_API_31470 */
  boolean retVal = DCM_FALSE;

  uint8 lenFormatId = Dcm_GaaFileTransferConfig.uclengthFormatIdentifier;

  retVal = Dcm_CheckParameterByteLen(lenFormatId, Dcm_FileInfo.blockLength);

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_CheckReadFileInfo                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check the file information that returned form API   **
**                        in case the operation mode is read file             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_CheckReadFileInfo(void)
{
  /* @Trace: Dcm_SUD_API_31517 */
  boolean retVal = DCM_FALSE;

  uint8 lenFormatId = Dcm_GaaFileTransferConfig.uclengthFormatIdentifier;
  uint8 fileSizeLen = Dcm_GaaFileTransferConfig.ucFileSizeOrDirInfoLength;

  retVal = Dcm_CheckParameterByteLen(lenFormatId, Dcm_FileInfo.blockLength);
  if (DCM_TRUE == retVal)
  {
    /* @Trace: Dcm_SUD_API_31518 */
    retVal = Dcm_CheckParameterByteLen(
      fileSizeLen, Dcm_FileInfo.fileSizeCompressed);

    if (DCM_TRUE == retVal)
    {
      /* @Trace: Dcm_SUD_API_31519 */
      retVal = Dcm_CheckParameterByteLen(
        fileSizeLen, Dcm_FileInfo.fileSizeUnCompressedOrDirInfoLength);
    }
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_CheckReadDirInfo                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check the file information that returned form API   **
**                        in case the operation mode is read directory        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_CheckReadDirInfo(void)
{
  /* @Trace: Dcm_SUD_API_31514 */
  boolean retVal = DCM_FALSE;

  uint8 lenFormatId = Dcm_GaaFileTransferConfig.uclengthFormatIdentifier;
  uint8 dirInfoParameterLen = Dcm_GaaFileTransferConfig.ucFileSizeOrDirInfoLength;
  
  retVal = Dcm_CheckParameterByteLen(lenFormatId, Dcm_FileInfo.blockLength);
  if (DCM_TRUE == retVal)
  {
    /* @Trace: Dcm_SUD_API_31515 */
    retVal = Dcm_CheckParameterByteLen(
      dirInfoParameterLen, Dcm_FileInfo.fileSizeUnCompressedOrDirInfoLength);
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_UpdateFileTransferResponse                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fill the data to response message for 0x38 service  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_UpdateFileTransferResponse(
  Dcm_MsgContextPtrType pMsgContext)
{
  switch (Dcm_FileInfo.operationType)
  {
    case DCM_ADD_FILE:
    case DCM_REPLACE_FILE:
      /* @Trace: Dcm_SUD_API_31680 */
      Dcm_UpdateAddOrRepFileResponse(pMsgContext);
      break;

    case DCM_DELETE_FILE:
      /* @Trace: Dcm_SUD_API_31681 */
      Dcm_UpdateDeleteFileResponse(pMsgContext);
      break;

    case DCM_READ_FILE:
      /* @Trace: Dcm_SUD_API_31682 */
      Dcm_UpdateReadFileResponse(pMsgContext);
      break;

    case DCM_READ_DIR:
      /* @Trace: Dcm_SUD_API_31683 */
      Dcm_UpdateReadDirResponse(pMsgContext);
      break;

    default:
      /* @Trace: Dcm_SUD_API_31684 */
      /* No action in this case */
      break;
  }  
}  

/*******************************************************************************
** Function Name        : Dcm_UpdateAddOrRepFileResponse                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fill the data to response message for 0x38 service  **
**                        is case the operation mode is add or replace file   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_UpdateAddOrRepFileResponse(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_31678 */
  Dcm_Uint8PtrType pResData = pMsgContext->resData;

  uint64 blockLength = Dcm_FileInfo.blockLength;
  uint8 lenFormatId = Dcm_GaaFileTransferConfig.uclengthFormatIdentifier;
  
  pMsgContext->resDataLen = DCM_THREE + (Dcm_MsgLenType) lenFormatId;

  pResData[0U] = (uint8) Dcm_FileInfo.operationType;
  pResData[1U] = lenFormatId;

  pResData = &pResData[2U];
  Dcm_Uint64ToResponseParameter(lenFormatId, blockLength, pResData);

  pResData[lenFormatId] = Dcm_FileInfo.dataFormatId;
}

/*******************************************************************************
** Function Name        : Dcm_UpdateDeleteFileResponse                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fill the data to response message for 0x38 service  **
**                        is case the operation mode is delete file           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_UpdateDeleteFileResponse(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_31679 */
  pMsgContext->resDataLen = 1U;

  pMsgContext->resData[0U] = (uint8) Dcm_FileInfo.operationType;
}

/*******************************************************************************
** Function Name        : Dcm_UpdateReadFileResponse                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fill the data to response message for 0x38 service  **
**                        is case the operation mode is read file             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_UpdateReadFileResponse(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_31686 */
  Dcm_Uint8PtrType pResData = pMsgContext->resData;

  uint64 blockLength = Dcm_FileInfo.blockLength;
  uint64 fileSizeCompressed = Dcm_FileInfo.fileSizeCompressed;
  uint64 fileSizeUnCompressed = Dcm_FileInfo.fileSizeUnCompressedOrDirInfoLength;

  uint8 lenFormatId = Dcm_GaaFileTransferConfig.uclengthFormatIdentifier;
  uint8 fileSizeLen = Dcm_GaaFileTransferConfig.ucFileSizeOrDirInfoLength;

  pMsgContext->resDataLen = ((uint32) fileSizeLen << DCM_ONE) + DCM_FIVE + lenFormatId;

  pResData[0U] = (uint8) Dcm_FileInfo.operationType;
  pResData[1U] = lenFormatId;

  pResData = &pResData[2U];
  Dcm_Uint64ToResponseParameter(lenFormatId, blockLength, pResData);

  pResData = &pResData[lenFormatId];
  pResData[0U] = Dcm_FileInfo.dataFormatId;

  /* 
  The file size parameter length in AR4.4 have range from 1 to 4.
  So, we will assign the MSB byte of fileSizeOrDirInfoParameterLength parameter
  in response message is 0x00.
  And the LSB byte is the value of fileSizeLen variable.
  */
  pResData[1U] = 0U;
  pResData[2U] = fileSizeLen;

  pResData = &pResData[3U];
  Dcm_Uint64ToResponseParameter(fileSizeLen, fileSizeUnCompressed, pResData);

  pResData = &pResData[fileSizeLen];
  Dcm_Uint64ToResponseParameter(fileSizeLen, fileSizeCompressed, pResData);
}

/*******************************************************************************
** Function Name        : Dcm_UpdateReadDirResponse                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fill the data to response message for 0x38 service  **
**                        is case the operation mode is read directory        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_UpdateReadDirResponse(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_31685 */
  Dcm_Uint8PtrType pResData = pMsgContext->resData;

  uint64 blockLength = Dcm_FileInfo.blockLength;
  uint64 dirInfoLength = Dcm_FileInfo.fileSizeUnCompressedOrDirInfoLength;

  uint8 lenFormatId = Dcm_GaaFileTransferConfig.uclengthFormatIdentifier;
  uint8 dirInfoParameterLen = Dcm_GaaFileTransferConfig.ucFileSizeOrDirInfoLength;

  pMsgContext->resDataLen = (Dcm_MsgLenType) lenFormatId + dirInfoParameterLen + DCM_FIVE;

  pResData[0U] = (uint8) Dcm_FileInfo.operationType;
  pResData[1U] = lenFormatId;

  pResData = &pResData[2U];
  Dcm_Uint64ToResponseParameter(lenFormatId, blockLength, pResData);

  /* Ref: ISO 14229-1, 
  If the modeOfOperation parameter equals to 0x05 (ReadDir) 
  the value of this parameter (dataFormatIdentifier) shall be equal to 0x00.
  */
  pResData = &pResData[lenFormatId];
  pResData[0U] = 0U;

  /* 
  The dir info parameter length in AR4.4 have range from 1 to 4.
  So, we will assign the MSB byte of fileSizeOrDirInfoParameterLength parameter
  in response message is 0x00.
  And the LSB byte is the value of dirInfoParameterLen variable.
  */
  pResData[1U] = 0U;
  pResData[2U] = dirInfoParameterLen;

  pResData = &pResData[3U];
  Dcm_Uint64ToResponseParameter(dirInfoParameterLen, dirInfoLength, pResData);
}

/*******************************************************************************
** Function Name        : Dcm_TriggerFileTransferProcess                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Update data for transfer file process               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_TriggerFileTransferProcess(void)
{
  #if (DCM_TRANSFER_DATA_SERVICE == STD_ON)
  switch (Dcm_FileInfo.operationType)
  {
    case DCM_ADD_FILE:
    case DCM_REPLACE_FILE:
      /* @Trace: Dcm_SUD_API_31670 */
      Dcm_TransferData.transferType = DCM_WRITE_FILE_TRANSFER;
      break;

    case DCM_READ_FILE:
    case DCM_READ_DIR:
      /* @Trace: Dcm_SUD_API_31671 */
      Dcm_TransferData.transferType = DCM_READ_FILE_TRANSFER;
      break;

    default:
      /* No action in this case */
      break;
  }

  /* @Trace: Dcm_SUD_API_31673 */
  /* The value of block sequence counter is begin with ONE */
  Dcm_TransferData.blockSeqCounter = 1U;
  Dcm_IsBlockSeqCounterRollOver = DCM_FALSE;
  /* Copy data for transfer process */
  Dcm_TransferData.fileBlockLength = Dcm_FileInfo.blockLength;
  Dcm_TransferData.remainFileSize = Dcm_FileInfo.fileSizeUnCompressedOrDirInfoLength;
  #else
  return;
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_DcmRequestFileTransfer                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main processing function for UDS 0x38 service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
/* @Trace: SRS_Diag_04135 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmRequestFileTransfer(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_01083 */
  /* @Trace: Dcm_SUD_API_31571 */
  Std_ReturnType retVal = E_OK;
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  /* Clear the pending state before go to main process */
  DCM_UD_CLR_FLAG(DCM_FILE_TRANSFER_FLAG);

  errorCode = Dcm_CheckFileTransferRequest(pMsgContext);
  if (DCM_POS_RESP == errorCode)
  {
    /* @Trace: Dcm_SUD_API_31572 */
    Dcm_InternalProcessFileTransfer(DCM_INITIAL, pMsgContext, &errorCode);
  }

  Dcm_CheckProcessingDone(DCM_ASYNC_DONE, DCM_FILE_TRANSFER_FLAG, pMsgContext, errorCode);

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return retVal;
}
#endif /* END OF REQUEST FILE TRANSFER */

/*******************************************************************************
** Function Name        : Dcm_InitTransferData                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize for UDS 0x36 service                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DCM_TRANSFER_DATA_SERVICE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_InitTransferData(void)
{
  /* @Trace: Dcm_SUD_API_31593 */
  Dcm_TransferData.fileBlockLength = 0U;
  Dcm_TransferData.fileDataLen = 0U;
  Dcm_TransferData.remainFileSize = 0U;
  Dcm_TransferData.dataBlockLength = 0U;
  Dcm_TransferData.remainMemSize = 0U;
  Dcm_TransferData.currentMemAddr = 0U;
  Dcm_TransferData.memoryId = 0U;
  Dcm_TransferData.transferType = DCM_NO_TRANSFER;
  Dcm_TransferData.blockSeqCounter = 0U;
  Dcm_IsBlockSeqCounterRollOver = DCM_FALSE;
}

/*******************************************************************************
** Function Name        : Dcm_IncreaseBlockSequenceCounter                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Increase block sequence counter in Dcm module       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_IncreaseBlockSequenceCounter(void)
{
  if (Dcm_TransferData.blockSeqCounter < 255U)
  {
    /* @Trace: Dcm_SUD_API_31590 */
    Dcm_TransferData.blockSeqCounter++;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31589 */
    Dcm_TransferData.blockSeqCounter = 0U;
    Dcm_IsBlockSeqCounterRollOver = DCM_TRUE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_CheckTransferDataRequest                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check whether request message of UDS 0x36 service   **
**                        is valid or not                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pRepeatBlock                                        **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) 
Dcm_CheckTransferDataRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_BooleanPtrType pRepeatBlock)
{
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  switch (Dcm_TransferData.transferType) 
  {
    case DCM_UPLOAD_TRANSFER:
      /* @Trace: Dcm_SUD_API_31538 */
      errorCode = Dcm_CheckTransferDataUploadRequest(
        pMsgContext, pRepeatBlock);
      break;

    case DCM_DOWNLOAD_TRANSFER:
      /* @Trace: Dcm_SUD_API_31539 */
      errorCode = Dcm_CheckTransferDataDownloadRequest(
        pMsgContext, pRepeatBlock);
      break;

    case DCM_READ_FILE_TRANSFER:
      /* @Trace: Dcm_SUD_API_31540 */
      errorCode = Dcm_CheckTransferDataReadFileRequest(
        pMsgContext, pRepeatBlock);
      break;

    case DCM_WRITE_FILE_TRANSFER:
      /* @Trace: Dcm_SUD_API_31541 */
      errorCode = Dcm_CheckTransferDataWriteFileRequest(
        pMsgContext, pRepeatBlock);
      break;

    default:
      /* @Trace: Dcm_SUD_API_31542 */
      errorCode = DCM_E_REQUESTSEQUENCEERROR;
      break;
  }

  return errorCode;
}

/*******************************************************************************
** Function Name        : Dcm_CheckTransferDataUploadRequest                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check whether request message of UDS 0x36 service   **
**                        is valid or not in case upload process enable       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pRepeatBlock                                        **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) 
Dcm_CheckTransferDataUploadRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_BooleanPtrType pRepeatBlock)
{
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  if (1U != pMsgContext->reqDataLen)
  {
    /* @Trace: Dcm_SUD_API_31545 */
    errorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31546 */
    uint8 blockCounter = pMsgContext->reqData[0];
    errorCode = Dcm_CheckBlockSequenceCounter(blockCounter, pRepeatBlock);

    if ((DCM_POS_RESP == errorCode) && 
        (DCM_FALSE == *pRepeatBlock))
    {
      if (0U == Dcm_TransferData.remainMemSize)
      {
        /* @Trace: Dcm_SUD_API_31548 */
        errorCode = DCM_E_REQUESTSEQUENCEERROR;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_31547 */
        Dcm_TransferData.pDataRead = &(pMsgContext->resData[1U]);
      }
    }
  }

  return errorCode;
}

/*******************************************************************************
** Function Name        : Dcm_CheckTransferDataDownloadRequest                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check whether request message of UDS 0x36 service   **
**                        is valid or not in case download process enable     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pRepeatBlock                                        **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) 
Dcm_CheckTransferDataDownloadRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_BooleanPtrType pRepeatBlock)
{
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;
  
  if ((pMsgContext->reqDataLen > (Dcm_TransferData.dataBlockLength - 1U)) ||
     ((pMsgContext->reqDataLen != (Dcm_TransferData.remainMemSize + 1U)) &&
      (Dcm_TransferData.remainMemSize < (Dcm_TransferData.dataBlockLength - 2U)) &&
      (Dcm_TransferData.remainMemSize != 0U)))
  {
    /* @Trace: Dcm_SUD_API_31526 */
    errorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31527 */
    uint8 blockCounter = pMsgContext->reqData[0];
    errorCode = Dcm_CheckBlockSequenceCounter(blockCounter, pRepeatBlock);

    if ((DCM_POS_RESP == errorCode) && 
        (DCM_FALSE == *pRepeatBlock))
    {
      if (0U == Dcm_TransferData.remainMemSize)
      {
        /* @Trace: Dcm_SUD_API_31529 */
        errorCode = DCM_E_REQUESTSEQUENCEERROR;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_31528 */
        Dcm_TransferData.pDataWrite = &(pMsgContext->reqData[1U]);
      }
    }
  }

  return errorCode;
}

/*******************************************************************************
** Function Name        : Dcm_CheckTransferDataReadFileRequest                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check whether request message of UDS 0x36 service   **
**                        is valid or not in case read file process enable    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pRepeatBlock                                        **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE)
Dcm_CheckTransferDataReadFileRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_BooleanPtrType pRepeatBlock)
{
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  if (1U != pMsgContext->reqDataLen)
  {
    /* @Trace: Dcm_SUD_API_31532 */
    errorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31533 */
    uint8 blockCounter = pMsgContext->reqData[0];
    errorCode = Dcm_CheckBlockSequenceCounter(blockCounter, pRepeatBlock);

    if ((DCM_POS_RESP == errorCode) && 
        (DCM_FALSE == *pRepeatBlock))
    {
      if (0U == Dcm_TransferData.remainFileSize)
      {
        /* @Trace: Dcm_SUD_API_31535 */
        errorCode = DCM_E_REQUESTSEQUENCEERROR;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_31534 */
        Dcm_TransferData.pDataRead = &(pMsgContext->resData[1U]);
      }
    }
  }

  return errorCode;
}

/*******************************************************************************
** Function Name        : Dcm_CheckTransferDataWriteFileRequest               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check whether request message of UDS 0x36 service   **
**                        is valid or not in case write file process enable   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pRepeatBlock                                        **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE)
Dcm_CheckTransferDataWriteFileRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_BooleanPtrType pRepeatBlock)
{
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  if ((pMsgContext->reqDataLen != (Dcm_TransferData.fileBlockLength - 1U)) ||
     ((pMsgContext->reqDataLen != (Dcm_TransferData.remainFileSize + 1U)) &&
      (Dcm_TransferData.remainFileSize < (Dcm_TransferData.fileBlockLength - 2U)) &&
      (Dcm_TransferData.remainFileSize != 0U)))
  {
    /* @Trace: Dcm_SUD_API_31551 */
    errorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31552 */
    uint8 blockCounter = pMsgContext->reqData[0];
    errorCode = Dcm_CheckBlockSequenceCounter(blockCounter, pRepeatBlock);

    if ((DCM_POS_RESP == errorCode) && 
        (DCM_FALSE == *pRepeatBlock))
    {
      if (0U == Dcm_TransferData.remainFileSize)
      {
        /* @Trace: Dcm_SUD_API_31554 */
        errorCode = DCM_E_REQUESTSEQUENCEERROR;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_31553 */
        Dcm_TransferData.pDataWrite = &(pMsgContext->reqData[1U]);
      }
    } 
  }

  return errorCode;
}

/*******************************************************************************
** Function Name        : Dcm_CheckBlockSequenceCounter                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check whether the block sequence counter            **
**                        from the request message is valid                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : blockCounter                                        **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pRepeatBlock                                        **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) 
Dcm_CheckBlockSequenceCounter(
  uint8 blockCounter,
  Dcm_BooleanPtrType pRepeatBlock)
{
  /* @Trace: Dcm_SUD_API_31484 */
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  uint8 blockCounterOnServer = Dcm_TransferData.blockSeqCounter;

  if (blockCounter != blockCounterOnServer)
  {
    /* Check if BlockSeqCounter of first TransferData is 0x00 */
    if ((blockCounter == 0U) && \
         (Dcm_IsBlockSeqCounterRollOver == DCM_FALSE))
    {
      errorCode = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
    }
    else if (blockCounter == (blockCounterOnServer - 1U))
    {
      /* @Trace: Dcm_SUD_API_31486 */
      *pRepeatBlock = DCM_TRUE;
    }
    else
    {
      /* @Trace: SWS_Dcm_00645 */
      /* @Trace: Dcm_SUD_API_31485 */
      errorCode = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
    }
  }

  return errorCode;
}

/*******************************************************************************
** Function Name        : Dcm_UpdateTransferDataUploadResponse                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fill the response message for UDS 0x38 service      **
**                        in case upload process enable                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_UpdateTransferDataUploadResponse(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* Set the block sequence counter to response message */
  pMsgContext->resData[0U] = pMsgContext->reqData[0];

  if (Dcm_TransferData.remainMemSize < (Dcm_TransferData.dataBlockLength - 2U))
  {
    /* @Trace: Dcm_SUD_API_31691 */
    pMsgContext->resDataLen = Dcm_TransferData.remainMemSize + 1U;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31690 */
    pMsgContext->resDataLen = Dcm_TransferData.dataBlockLength - 1U;
  }
}

/*******************************************************************************
** Function Name        : Dcm_UpdateTransferDataDownloadResponse              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fill the response message for UDS 0x38 service      **
**                        in case download process enable                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_UpdateTransferDataDownloadResponse(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_31687 */
  pMsgContext->resData[0U] =  pMsgContext->reqData[0];
  pMsgContext->resDataLen = 1U;
}

/*******************************************************************************
** Function Name        : Dcm_UpdateTransferDataReadFileResponse              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fill the response message for UDS 0x38 service      **
**                        in case read file process enable                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_UpdateTransferDataReadFileResponse(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_31688 */
  pMsgContext->resData[0U] = pMsgContext->reqData[0];
  pMsgContext->resDataLen = (Dcm_MsgLenType) (Dcm_TransferData.fileDataLen + 1U);
}

/*******************************************************************************
** Function Name        : Dcm_UpdateTransferDataWriteFileResponse             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fill the response message for UDS 0x38 service      **
**                        in case write file process enable                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_UpdateTransferDataWriteFileResponse(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_31692 */
  pMsgContext->resData[0U] = pMsgContext->reqData[0];
  pMsgContext->resDataLen = 1U;
}

/*******************************************************************************
** Function Name        : Dcm_TransferDataRepeatBlock                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process UDS 0x36 service in case the block sequence **
**                        counter is repeated                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_TransferDataRepeatBlock(
  Dcm_MsgContextPtrType pMsgContext)
{
  switch (Dcm_TransferData.transferType)
  {
    case DCM_UPLOAD_TRANSFER:
      /* @Trace: Dcm_SUD_API_31664 */
      pMsgContext->resDataLen = Dcm_TransferData.dataBlockLength - 1U;
      break;

    case DCM_DOWNLOAD_TRANSFER:
      /* @Trace: Dcm_SUD_API_31665 */
      pMsgContext->resDataLen = 1U;
      break;

    case DCM_READ_FILE_TRANSFER:
      /* @Trace: Dcm_SUD_API_31666 */
      pMsgContext->resDataLen = (Dcm_MsgLenType) (Dcm_TransferData.fileDataLen + 1U);
      break;

    case DCM_WRITE_FILE_TRANSFER:
      /* @Trace: Dcm_SUD_API_31667 */
      pMsgContext->resDataLen = 1U;
      break;

    default:
      /* @Trace: Dcm_SUD_API_31668 */
      /* No action in this case */
      break;        
  }
}

/*******************************************************************************
** Function Name        : Dcm_CallProcessTransferDataReadFunc                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call the processing function of UDS 0x36 service    **
**                        in case upload process enable                       ** 
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Dcm_ReturnReadMemoryType                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Dcm_ReturnReadMemoryType, DCM_CODE)
Dcm_CallProcessTransferDataReadFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode)
{
  Dcm_ReturnReadMemoryType retVal = E_NOT_OK;

  uint32 memSize = Dcm_TransferData.dataBlockLength - 2U;
  
  if (NULL_PTR != Dcm_GaaMemTransferFncConfig.pProcessTransferDataReadFnc)
  {
    /* @Trace: Dcm_SUD_API_31432 */
    retVal = Dcm_GaaMemTransferFncConfig.pProcessTransferDataReadFnc(
              OpStatus, 
              Dcm_TransferData.memoryId, 
              Dcm_TransferData.currentMemAddr, 
              memSize,
              Dcm_TransferData.pDataRead, 
              pErrorCode);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31431 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_CallProcessTransferDataWriteFunc                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call the processing function of UDS 0x36 service    **
**                        in case download process enable                     ** 
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Dcm_ReturnWriteMemoryType                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Dcm_ReturnWriteMemoryType, DCM_CODE)
Dcm_CallProcessTransferDataWriteFunc(
  Dcm_OpStatusType OpStatus,
  uint32 memSize,
  Dcm_NrcPtrType pErrorCode)
{
  Dcm_ReturnWriteMemoryType retVal= E_NOT_OK;

  if (NULL_PTR != Dcm_GaaMemTransferFncConfig.pProcessTransferDataWriteFnc)
  {
      /* @Trace: Dcm_SUD_API_31436 */      
      retVal = Dcm_GaaMemTransferFncConfig.pProcessTransferDataWriteFnc(
              OpStatus, 
              Dcm_TransferData.memoryId, 
              Dcm_TransferData.currentMemAddr, 
              memSize,
              Dcm_TransferData.pDataWrite, 
              pErrorCode);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31435 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_CallWriteFileFunc                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call the processing function of UDS 0x36 service    **
**                        in case write file process enable                   ** 
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallWriteFileFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType retVal= E_NOT_OK;

  Dcm_TransferData.fileDataLen = Dcm_TransferData.fileBlockLength - 2U;

  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
  if (NULL_PTR != Dcm_GaaFileTransferFncConfig.pWriteFileFnc)
  {
    /* @Trace: Dcm_SUD_API_31458 */
    retVal = Dcm_GaaFileTransferFncConfig.pWriteFileFnc(
              OpStatus, 
              Dcm_TransferData.fileDataLen, 
              Dcm_TransferData.pDataWrite, 
              pErrorCode);
  }
  /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
  else
  {
    /* @Trace: Dcm_SUD_API_31457 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_CallReadFileOrDirFunc                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call the processing function of UDS 0x36 service    **
**                        in case read file process enable                    ** 
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallReadFileOrDirFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType retVal= E_NOT_OK;

  Dcm_TransferData.fileDataLen = Dcm_TransferData.fileBlockLength - 2U;

  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
  if (NULL_PTR != Dcm_GaaFileTransferFncConfig.pReadFileOrDirFnc)
  {
    /* @Trace: Dcm_SUD_API_31448 */
    retVal = Dcm_GaaFileTransferFncConfig.pReadFileOrDirFnc(
              OpStatus, 
              &(Dcm_TransferData.fileDataLen), 
              Dcm_TransferData.pDataRead, 
              pErrorCode);
  }
  /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
  else
  {
    /* @Trace: Dcm_SUD_API_31447 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_CallTransferDataFunc                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call the processing function of UDS 0x36 service    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallTransferDataFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode)
{
  /* This function just use for cancel transfer data process */
  Std_ReturnType retVal = E_OK;

  switch (Dcm_TransferData.transferType)
  {
    case DCM_UPLOAD_TRANSFER:
      /* @Trace: Dcm_SUD_API_31451 */
      (void) Dcm_CallProcessTransferDataReadFunc(OpStatus, pErrorCode);
      break;

    case DCM_DOWNLOAD_TRANSFER:
      /* @Trace: Dcm_SUD_API_31452 */
      (void) Dcm_CallProcessTransferDataWriteFunc(OpStatus, Dcm_GstMsgContext.reqDataLen -1, pErrorCode);
      break;

    case DCM_READ_FILE_TRANSFER:
      /* @Trace: Dcm_SUD_API_31453 */
      (void) Dcm_CallReadFileOrDirFunc(OpStatus, pErrorCode);
      break;

    case DCM_WRITE_FILE_TRANSFER:
      /* @Trace: Dcm_SUD_API_31454 */
      (void) Dcm_CallWriteFileFunc(OpStatus, pErrorCode);
      break;

    default:
      /* @Trace: Dcm_SUD_API_31455 */
      /* No action in this case */
      break;        
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_InternalProcessTransferData                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal processing function for UDs 0x36 service   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_InternalProcessTransferData(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  switch (Dcm_TransferData.transferType)
  {
    case DCM_UPLOAD_TRANSFER:
      /* @Trace: Dcm_SUD_API_31622 */
      Dcm_InternalProcessTransferRead(OpStatus, pMsgContext, pErrorCode);
      break;

    case DCM_DOWNLOAD_TRANSFER:
      /* @Trace: Dcm_SUD_API_31623 */
      Dcm_InternalProcessTransferWrite(OpStatus, pMsgContext, pErrorCode);
      break;

    case DCM_READ_FILE_TRANSFER:
      /* @Trace: Dcm_SUD_API_31624 */
      Dcm_InternalProcessReadFileOrDir(OpStatus, pMsgContext, pErrorCode);
      break;

    case DCM_WRITE_FILE_TRANSFER:
      /* @Trace: Dcm_SUD_API_31625 */
      Dcm_InternalProcessWriteFile(OpStatus, pMsgContext, pErrorCode);
      break;

    default:
      /* @Trace: Dcm_SUD_API_31626 */
      /* No action in this case */
      break;        
  }
}

/*******************************************************************************
** Function Name        : Dcm_InternalProcessTransferRead                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal processing function for UDs 0x36 service   **
**                        in case upload process enable                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_InternalProcessTransferRead(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Dcm_ReturnReadMemoryType retVal;
  
  /* @Trace: SWS_Dcm_00504 */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_91070. Dcm must be implement to cover all return values of Xxx_ProcessTransferDataRead." */
  retVal = Dcm_CallProcessTransferDataReadFunc(OpStatus, pErrorCode);
  switch (retVal)
  {
    case DCM_READ_OK:
      /* @Trace: Dcm_SUD_API_31634 */
      *pErrorCode = DCM_POS_RESP;

      DCM_UD_CLR_FLAG(DCM_TRANSFER_DATA_FLAG);

      Dcm_UpdateTransferDataUploadResponse(pMsgContext);

      Dcm_IncreaseBlockSequenceCounter();

      Dcm_TransferData.remainMemSize -= pMsgContext->resDataLen - 1U;
      Dcm_TransferData.currentMemAddr += pMsgContext->resDataLen - 1U;
      break;

    case DCM_READ_PENDING:
      /* @Trace: Dcm_SUD_API_31636 */
      DCM_UD_SET_PENDING(DCM_TRANSFER_DATA_FLAG);
      break;

    case DCM_READ_FORCE_RCRRP:
      /* @Trace: SWS_Dcm_00528 */
      /* @Trace: Dcm_SUD_API_31637 */
      DCM_UD_SET_FORCE_RCRRP(DCM_TRANSFER_DATA_FLAG);
      Dcm_SendNrcRccrp(pMsgContext, pErrorCode);
      break;

    default: /* DCM_READ_FAILED */
      /* @Trace: SWS_Dcm_01173 */
      /* @Trace: Dcm_SUD_API_31635 */
      DCM_UD_CLR_FLAG(DCM_TRANSFER_DATA_FLAG);
      break;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_91070. Dcm must be implement to cover all return values of Xxx_ProcessTransferDataRead." */
}

/*******************************************************************************
** Function Name        : Dcm_InternalProcessTransferWrite                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal processing function for UDs 0x36 service   **
**                        in case download process enable                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_InternalProcessTransferWrite(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Dcm_ReturnWriteMemoryType retVal;
  
  /* @Trace: SWS_Dcm_00503 */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_91071, the function Xxx_ProcessTransferDataWrite has return 4 values.
    So, Dcm must be implement to cover all return value of function Xxx_ProcessTransferDataWrite." */
  retVal = Dcm_CallProcessTransferDataWriteFunc(OpStatus, (pMsgContext->reqDataLen) - 1U, pErrorCode);
  switch (retVal)
  {
    case DCM_WRITE_OK:
      /* @Trace: Dcm_SUD_API_31640 */
      *pErrorCode = DCM_POS_RESP;

      DCM_UD_CLR_FLAG(DCM_TRANSFER_DATA_FLAG);

      Dcm_UpdateTransferDataDownloadResponse(pMsgContext);

      Dcm_IncreaseBlockSequenceCounter();

      Dcm_TransferData.remainMemSize -= pMsgContext->reqDataLen - 1U;
      Dcm_TransferData.currentMemAddr += pMsgContext->reqDataLen - 1U;
      break;

    case DCM_WRITE_PENDING:
      /* @Trace: Dcm_SUD_API_31642 */
      DCM_UD_SET_PENDING(DCM_TRANSFER_DATA_FLAG);
      break;

    case DCM_WRITE_FORCE_RCRRP:
      /* @Trace: SWS_Dcm_00528 */
      /* @Trace: Dcm_SUD_API_31643 */
      DCM_UD_SET_FORCE_RCRRP(DCM_TRANSFER_DATA_FLAG);
      Dcm_SendNrcRccrp(pMsgContext, pErrorCode);
      if (*pErrorCode == DCM_E_GENERALREJECT)
      {
        /* polyspace +1 MISRA-C3:17.7 [Justified:Low] Justify with annotations */
        Dcm_CallProcessTransferDataWriteFunc(DCM_CANCEL, Dcm_TransferData.dataBlockLength - 2U, pErrorCode);
      }
      break;

    default: /* DCM_WRITE_FAILED */
      /* @Trace: SWS_Dcm_01173 */
      /* @Trace: Dcm_SUD_API_31641 */
      DCM_UD_CLR_FLAG(DCM_TRANSFER_DATA_FLAG);
      break;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_91071, the function Xxx_ProcessTransferDataWrite has return 4 values.
    So, Dcm must be implement to cover all return value of function Xxx_ProcessTransferDataWrite." */
}

/*******************************************************************************
** Function Name        : Dcm_InternalProcessReadFileOrDir                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal processing function for UDs 0x36 service   **
**                        in case read file process enable                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_InternalProcessReadFileOrDir(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType retVal;
  
  /* @Trace: SWS_Dcm_01445 */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_91081, SWS_Dcm_91082. 
   Dcm must be implement to cover all return values of those functions." */
  retVal = Dcm_CallReadFileOrDirFunc(OpStatus, pErrorCode);
  switch (retVal)
  {
    case E_OK:
      /* @Trace: Dcm_SUD_API_31617 */
      *pErrorCode = DCM_POS_RESP;

      DCM_UD_CLR_FLAG(DCM_TRANSFER_DATA_FLAG);

      Dcm_UpdateTransferDataReadFileResponse(pMsgContext);

      Dcm_IncreaseBlockSequenceCounter();

      Dcm_TransferData.remainFileSize++;
      Dcm_TransferData.remainFileSize -= pMsgContext->resDataLen;
      break;

    case DCM_E_PENDING:
      /* @Trace: Dcm_SUD_API_31619 */
      DCM_UD_SET_PENDING(DCM_TRANSFER_DATA_FLAG);
      break;

    case DCM_E_FORCE_RCRRP:
      /* @Trace: SWS_Dcm_00528 */
      /* @Trace: Dcm_SUD_API_31620 */
      DCM_UD_SET_FORCE_RCRRP(DCM_TRANSFER_DATA_FLAG);
      Dcm_SendNrcRccrp(pMsgContext, pErrorCode);
      break;

    default: /* E_NOT_OK */
      /* @Trace: SWS_Dcm_01173 */
      /* @Trace: Dcm_SUD_API_31618 */
      DCM_UD_CLR_FLAG(DCM_TRANSFER_DATA_FLAG);
      break;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_91081, SWS_Dcm_91082. 
   Dcm must be implement to cover all return values of those functions." */
}

/*******************************************************************************
** Function Name        : Dcm_InternalProcessWriteFile                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal processing function for UDs 0x36 service   **
**                        in case write file process enable                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_InternalProcessWriteFile(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType retVal;

  /* @Trace: SWS_Dcm_01444 */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_91083,  Dcm must be implement to cover all return value of function Dcm_WriteFile." */
  retVal = Dcm_CallWriteFileFunc(OpStatus, pErrorCode);
  switch (retVal)
  {
    case E_OK:
      /* @Trace: Dcm_SUD_API_31654 */
      *pErrorCode = DCM_POS_RESP;

      DCM_UD_CLR_FLAG(DCM_TRANSFER_DATA_FLAG);

      Dcm_UpdateTransferDataWriteFileResponse(pMsgContext);

      Dcm_IncreaseBlockSequenceCounter();

      Dcm_TransferData.remainFileSize++;
      Dcm_TransferData.remainFileSize -= pMsgContext->reqDataLen;
      break;

    case DCM_E_PENDING:
      /* @Trace: Dcm_SUD_API_31656 */
      DCM_UD_SET_PENDING(DCM_TRANSFER_DATA_FLAG);
      break;

    case DCM_E_FORCE_RCRRP:
      /* @Trace: SWS_Dcm_00528 */
      /* @Trace: Dcm_SUD_API_31657 */
      DCM_UD_SET_FORCE_RCRRP(DCM_TRANSFER_DATA_FLAG);
      Dcm_SendNrcRccrp(pMsgContext, pErrorCode);
      break;

    default: /* E_NOT_OK */
      /* @Trace: SWS_Dcm_01173 */
      /* @Trace: Dcm_SUD_API_31655 */
      DCM_UD_CLR_FLAG(DCM_TRANSFER_DATA_FLAG);
      break;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_91083,  Dcm must be implement to cover all return value of function Dcm_WriteFile." */
}

/*******************************************************************************
** Function Name        : Dcm_DcmTransferData                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main processing function for UDs 0x36 service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +4 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmTransferData(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_00502 */
  /* @Trace: Dcm_SUD_API_31580 */
  Std_ReturnType retVal = E_OK;
  boolean repeatBlock = DCM_FALSE;
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  /* Clear the pending state before go to main process */
  DCM_UD_CLR_FLAG(DCM_TRANSFER_DATA_FLAG);

  errorCode = Dcm_CheckTransferDataRequest(pMsgContext, &repeatBlock);
  if (DCM_POS_RESP == errorCode)
  {
    if (DCM_FALSE == repeatBlock)
    {
      /* @Trace: Dcm_SUD_API_31582 */
      Dcm_InternalProcessTransferData(DCM_INITIAL, pMsgContext, &errorCode);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_31581 */
      Dcm_TransferDataRepeatBlock(pMsgContext);
    }
  }

  Dcm_CheckProcessingDone(DCM_ASYNC_DONE, DCM_TRANSFER_DATA_FLAG, pMsgContext, errorCode);

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CheckTransferExitRequest                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check whether request message of UDS 0x37 service   **
**                        is valid or not                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_TRANSFER_EXIT_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckTransferExitRequest(
  Dcm_MsgContextPtrType pMsgContext)
{
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;
  
  /* Ref: ES95486
  After exclude SID, the request length is zero */
  #if(DCM_TRANSFER_REQUEST_PARAM_RECORD_USED != STD_ON)
  if (0U != pMsgContext->reqDataLen)
  {
    /* @Trace: Dcm_SUD_API_31557 */
    errorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  #endif
  {
    /* @Trace: Dcm_SUD_API_31559 */
    #if (DCM_TRANSFER_DATA_SERVICE == STD_ON)
    if (Dcm_TransferData.transferType >= DCM_NO_TRANSFER)
    #endif
    {
      /* @Trace: Dcm_SUD_API_31558 */
      errorCode = DCM_E_REQUESTSEQUENCEERROR;
    }
  }

  return errorCode;
}

/*******************************************************************************
** Function Name        : Dcm_CallProcessTransferExitFunc                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call processing function for UDS 0x37 service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_CallProcessTransferExitFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_NrcPtrType pErrorCode)
{
  /* if user using transferdatarecord data for service 0x37, this function will not used */
  Std_ReturnType retVal = E_NOT_OK;
  #if (DCM_TRANSFER_REQUEST_PARAM_RECORD_USED != STD_ON)
  if (NULL_PTR != Dcm_GaaMemTransferFncConfig.pProcessRequestTransferExitFnc)
  {
    /* @Trace: Dcm_SUD_API_31440 */
    retVal = Dcm_GaaMemTransferFncConfig.pProcessRequestTransferExitFnc(
              OpStatus, 
              pErrorCode);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_31439 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  #else
  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  #endif /*DCM_TRANSFER_REQUEST_PARAM_RECORD_USED != STD_ON*/

  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_InternalProcessTransferExit                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal processing function for UDS 0x37 service   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_InternalProcessTransferExit(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode) 
{
  Std_ReturnType retVal;

  #if ((DCM_TRANSFER_EXIT_SERVICE == STD_ON) && (DCM_TRANSFER_REQUEST_PARAM_RECORD_USED == STD_ON))
  retVal = Dcm_RequestTransferExitWithParamRecord( OpStatus, pMsgContext, pErrorCode);
  #else
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00755, Dcm must be verify all retunr value of function Xxx_ProcessRequestTransferExit." */
  retVal = Dcm_CallProcessTransferExitFunc(OpStatus, pErrorCode);
  #endif

  switch (retVal)
  {
    case E_OK:
      /* @Trace: Dcm_SUD_API_31628 */
      *pErrorCode = DCM_POS_RESP;

      DCM_UD_CLR_FLAG(DCM_TRANSFER_EXIT_FLAG);

      /* Update response length */
      pMsgContext->resDataLen = 0U;
      
      Dcm_ClearTransferDataProcess();
      break;

    case E_NOT_OK:
      /* @Trace: SWS_Dcm_00759 SWS_Dcm_01134 */
      /* @Trace: Dcm_SUD_API_31629 */
      /* The error code is updated in pErrorCode */
      DCM_UD_CLR_FLAG(DCM_TRANSFER_EXIT_FLAG);
      break;

    case DCM_E_PENDING:
      /* @Trace: Dcm_SUD_API_31630 */
      DCM_UD_SET_PENDING(DCM_TRANSFER_EXIT_FLAG);
      break;

    case DCM_E_FORCE_RCRRP:
      /* @Trace: SWS_Dcm_00528 */
      /* @Trace: Dcm_SUD_API_31631 */
      DCM_UD_SET_FORCE_RCRRP(DCM_TRANSFER_EXIT_FLAG);
      Dcm_SendNrcRccrp(pMsgContext, pErrorCode);
      break;

    default:
      /* @Trace: Dcm_SUD_API_31632 */
      /* No action in this case */
      break;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "As per SWS_Dcm_00755, Dcm must be verify all retunr value of function Xxx_ProcessRequestTransferExit." */
}

/*******************************************************************************
** Function Name        : Dcm_DcmRequestTransferExit                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main processing function for UDS 0x37 service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +4 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmRequestTransferExit(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_00505 */
  /* @Trace: Dcm_SUD_API_31574 */
  Std_ReturnType retVal = E_OK;
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  /* Clear the pending state before go to main process */
  DCM_UD_CLR_FLAG(DCM_TRANSFER_EXIT_FLAG);
  
  errorCode = Dcm_CheckTransferExitRequest(pMsgContext);
  if (DCM_POS_RESP == errorCode)
  {
    /* @Trace: Dcm_SUD_API_31575 */
    Dcm_InternalProcessTransferExit(DCM_INITIAL, pMsgContext, &errorCode);
  }
  
  Dcm_CheckProcessingDone(DCM_ASYNC_DONE, DCM_TRANSFER_EXIT_FLAG, pMsgContext, errorCode);
  
  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return retVal;
} 
#endif /* END OF REQUEST TRANSFER EXIT */

#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* END OF UPLOAD DOWNLOAD SERVICES */

/*******************************************************************************
** Function Name        : Dcm_InitUploadDownloadServices                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize data for upload download services        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, DCM_CODE) Dcm_InitUploadDownloadServices(void)
{
  /* @Trace: Dcm_SUD_API_31594 */
  #ifdef DCM_UPLOAD_DOWNLOAD_SERVICES_ENABLE
  uint16 flagType;

  for (flagType = 0U; flagType < (uint16) DCM_UD_MAX_SERVICE_FLAG; flagType++)
  {
    /* @Trace: Dcm_SUD_API_31595 */
    DCM_UD_CLR_FLAG(flagType);
  }

  #if ((DCM_REQUEST_UPLOAD_SERVICE == STD_ON) || \
       (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON))
  /* @Trace: Dcm_SUD_API_31596 */
  Dcm_InitMemoryInfo();
  #endif

  #if (DCM_FILE_TRANSFER_SERVICE == STD_ON)
  /* @Trace: Dcm_SUD_API_31597 */
  Dcm_InitFileInfo();
  #endif

  #if (DCM_TRANSFER_DATA_SERVICE == STD_ON)
  /* @Trace: Dcm_SUD_API_31598 */
  Dcm_InitTransferData();
  #endif
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_ClearTransferDataProcess                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Clear the transfer data process                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_ClearTransferDataProcess(void)
{
  /* @Trace: Dcm_SUD_API_31567 */
  #if (DCM_TRANSFER_DATA_SERVICE == STD_ON)
  Dcm_TransferData.transferType = DCM_NO_TRANSFER;
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_UploadDownloadServicesPending                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main processing function in case upload download    **
**                        return DCM_E_PENDING or DCM_E_FORCE_RCRRP           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : resPendConfirm, pMsgContext                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_UploadDownloadServicesPending(
  boolean resPendConfirm,
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_31695 */
  #ifdef DCM_UPLOAD_DOWNLOAD_SERVICES_ENABLE
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  Dcm_InternalProcessFuncType intProcessFunc[] = 
  {
    #if (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
    Dcm_InternalProcessDownload,
    #endif

    #if (DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
    Dcm_InternalProcessUpload,
    #endif

    #if (DCM_TRANSFER_DATA_SERVICE == STD_ON)
    Dcm_InternalProcessTransferData,
    #endif

    #if (DCM_TRANSFER_EXIT_SERVICE == STD_ON)
    Dcm_InternalProcessTransferExit,
    #endif

    #if (DCM_FILE_TRANSFER_SERVICE == STD_ON)
    Dcm_InternalProcessFileTransfer
    #endif
  };

  uint16 flagType;

  for (flagType = 0U; flagType < (uint16) DCM_UD_MAX_SERVICE_FLAG; flagType++)
  {
    if (DCM_UD_IS_FLAG_SET(flagType))
    {
      if (DCM_UD_IS_FORCE_RCRRP(flagType))
      {
        if (DCM_TRUE == resPendConfirm)
        {
          /* @Trace: Dcm_SUD_API_31704 */
          intProcessFunc[flagType](DCM_FORCE_RCRRP_OK, pMsgContext, &errorCode);
        }
      }
      else
      {
        /* @Trace: Dcm_SUD_API_31703 */
        intProcessFunc[flagType](DCM_PENDING, pMsgContext, &errorCode);
      }
      
      /* @Trace: Dcm_SUD_API_31705 */
      /* Pending operation is processed in Main Function 
       * So, we should check with DCM_SYNC_DONE to transfer response directly */
      /* polyspace +2 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
      Dcm_CheckProcessingDone(
        DCM_SYNC_DONE, (Dcm_UdServiceFlagType) flagType, pMsgContext, errorCode);
    } 
  }
  #else
  DCM_UNUSED(resPendConfirm);
  DCM_UNUSED(pMsgContext);
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_CancelUploadDownloadServices                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Cancel the operation of upload download services    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_CancelUploadDownloadServices(void)
{
  /* @Trace: Dcm_SUD_API_31460 */
  #ifdef DCM_UPLOAD_DOWNLOAD_SERVICES_ENABLE
  Dcm_NegativeResponseCodeType errorCode = DCM_POS_RESP;

  Dcm_CallProcessFuncType callProcessFunc[] =
  {
    #if (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
    Dcm_CallProcessDownloadFunc,
    #endif

    #if (DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
    Dcm_CallProcessUploadFunc,
    #endif

    #if (DCM_TRANSFER_DATA_SERVICE == STD_ON)
    Dcm_CallTransferDataFunc,
    #endif

    #if (DCM_TRANSFER_EXIT_SERVICE == STD_ON)
    Dcm_CallProcessTransferExitFunc,
    #endif

    #if (DCM_FILE_TRANSFER_SERVICE == STD_ON)
    Dcm_CallFileTransferFunc
    #endif
  };

  uint16 flagType;

  for (flagType = 0U; flagType < (uint16) DCM_UD_MAX_SERVICE_FLAG; flagType++)
  {
    /* @Trace: Dcm_SUD_API_31469 */
    if (DCM_UD_IS_FLAG_SET(flagType))
    {
      /* @Trace: Dcm_SUD_API_31468 */
      DCM_UD_CLR_FLAG(flagType);

      #if ((DCM_TRANSFER_EXIT_SERVICE == STD_ON) && (DCM_TRANSFER_REQUEST_PARAM_RECORD_USED == STD_ON))
      if (flagType == DCM_TRANSFER_EXIT_FLAG)
      {
        (void) Dcm_RequestTransferExitWithParamRecord(DCM_CANCEL, &Dcm_GstMsgContext, &errorCode);
      }
      else
      #endif
      {
      /* @Trace: SWS_Dcm_01413 */
      (void) callProcessFunc[flagType](DCM_CANCEL, &errorCode);
      }
    }
  }
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_RequestTransferExitWithParamRecord              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal processing function for UDS 0x37 service   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if ((DCM_TRANSFER_EXIT_SERVICE == STD_ON) && (DCM_TRANSFER_REQUEST_PARAM_RECORD_USED == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_RequestTransferExitWithParamRecord( 
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode) 
{
  Std_ReturnType retVal;
  if (NULL_PTR != Dcm_GaaMemTransferFncConfig.pProcessRequestTransferExitFnc)
  {
    if (DCM_INITIAL == OpStatus)
    {
      Dcm_RequestTransferExitParamRecordData.transferRequestParameterRecord = pMsgContext->reqData;
      Dcm_RequestTransferExitParamRecordData.transferRequestParameterRecordSize = DCM_TRANSFER_REQUEST_PARAM_RECORD_SIZE;

      Dcm_RequestTransferExitParamRecordData.transferResponseParameterRecord = pMsgContext->resData;
      Dcm_RequestTransferExitParamRecordData.transferResponseParameterRecordSize = pMsgContext->resMaxDataLen;
    }

    retVal = Dcm_GaaMemTransferFncConfig.pProcessRequestTransferExitFnc(
              OpStatus 
              , Dcm_RequestTransferExitParamRecordData.transferRequestParameterRecord
              , Dcm_RequestTransferExitParamRecordData.transferRequestParameterRecordSize
              , Dcm_RequestTransferExitParamRecordData.transferResponseParameterRecord
              , &Dcm_RequestTransferExitParamRecordData.transferResponseParameterRecordSize
              , pErrorCode);
  }
  else
  {
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return retVal;
}

#endif /* ((DCM_TRANSFER_EXIT_SERVICE == STD_ON) && (DCM_TRANSFER_REQUEST_PARAM_RECORD_USED == STD_ON)) */

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                              End of File                                   **
*******************************************************************************/
