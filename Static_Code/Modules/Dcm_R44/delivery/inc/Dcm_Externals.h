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
**  SRC-MODULE: Dcm_Externals.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the declaration for Dcm callout functions  **
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
** 0.0.1     31-Dec-2019   SonDT1         AR440 Implementation                **
** 0.0.2     16-Aug-2020   HueKM          Fix defect and coding rules         **
** 0.0.3     13-Oct-2020   HueKM          Changes made as per #15766          **
** 1.0.3     13-Jul-2022   LanhLT         Changes made as per #36622          **
** 1.0.7     16-Dec-2022   LanhLT         Refer #CP44-1179                    **
** 1.0.9     31-Mar-2023   LanhLT         Refer #CP44-1739                    **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-2768                    **
*******************************************************************************/

#ifndef DCM_EXTERNALS_H
#define DCM_EXTERNALS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "HwResource.h"
#include "Dcm_Types.h"
#include "Dcm_Cfg.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DCM_START_SEC_CALLOUT_CODE
#include "MemMap.h"

#if (HWRESOURCE_VENDOR(HWRESOURCE_INFINEON))
/* Structure for programming condition used in both DCM and FBL (For AURIX) */
typedef struct
{
  /* Tester source address configured per protocol */
  uint16 TesterSourceAddr;
  /* reserved for align */
  uint16 reserved0;
  /* Id of the connection on which the request has been received */
  uint16 ConnectionId;
  /* Service identifier of the received request */
  uint8 Sid;
  /* Identifier of the received subfunction */
  uint8 SubFncId;
  /* Set to true in order to request reprogramming of the ECU */
  uint8 ReprogramingRequest;
  /* Indicate whether the application has been updated or not */
  uint8 ApplUpdated;
  /* Set to true in case the flashloader or application shall send a response */
  uint8 ResponseRequired;
  /* Jump from FBL */
  uint8 JumpFromBootloader;
  /* Security Level 0:lock otherwise:unlock */
  uint8 SecurityLevel;
  /* Reserved bit */
  uint8 Reserved[2];
} Dcm_McuDepProgConditionsType;

#else

/* Structure for programming condition used in both DCM and FBL */
typedef struct
{
  /* Tester source address configured per protocol */
  uint16 TesterSourceAddr;
  /* Id of the connection on which the request has been received */
  uint16 ConnectionId;
  /* Service identifier of the received request */
  uint8 Sid;
  /* Identifier of the received subfunction */
  uint8 SubFncId;
  /* Set to true in order to request reprogramming of the ECU */
  uint8 ReprogramingRequest;
  /* Indicate whether the application has been updated or not */
  uint8 ApplUpdated;
  /* Set to true in case the flashloader or application shall send a response */
  uint8 ResponseRequired;
  /* Security Level 0:lock otherwise:unlock */
  uint8 SecurityLevel;
} Dcm_McuDepProgConditionsType;
#endif


/*******************************************************************************
**          Callout definitions                                               **
*******************************************************************************/
/* @Trace: SWS_Dcm_00539 */
extern FUNC(Dcm_ReturnReadMemoryType, DCM_CALLOUT_CODE) Dcm_ReadMemory(
  Dcm_OpStatusType OpStatus
  , uint8 MemoryIdentifier
  , uint32 MemoryAddress
  , uint32 MemorySize
  , Dcm_Uint8PtrType MemoryData
  , Dcm_NrcPtrType ErrorCode);

/* @Trace: SWS_Dcm_00540 */
extern FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_WriteMemory(
  Dcm_OpStatusType OpStatus
  , uint8 MemoryIdentifier
  , uint32 MemoryAddress
  , uint32 MemorySize
  , Dcm_Uint8ConstPtrType MemoryData
  , Dcm_NrcPtrType ErrorCode);

/* @Trace: SWS_Dcm_00544 */
extern FUNC(Dcm_EcuStartModeType, DCM_CALLOUT_CODE) Dcm_GetProgConditions(
  P2VAR(Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA) ProgConditions);

/* @Trace: SWS_Dcm_00543 */
extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SetProgConditions(
  Dcm_OpStatusType OpStatus
  , P2CONST(Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_CONST) ProgConditions);

/* @Trace: SWS_Dcm_91078 */
extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ProcessRequestAddFile(
  Dcm_OpStatusType OpStatus
  , uint16 FilePathAndNameLength
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) FilePathAndName
  , uint8 DataFormatIdentifier
  , uint64 FileSizeUncompressed
  , uint64 FileSizeCompressed
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) MaxNumberOfBlockLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

/* @Trace: SWS_Dcm_91079 */
extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ProcessRequestDeleteFile(
  Dcm_OpStatusType OpStatus
  , uint16 FilePathAndNameLength
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) FilePathAndName
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

/* @Trace: SWS_Dcm_91080 */
extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ProcessRequestReplaceFile(
  Dcm_OpStatusType OpStatus
  , uint16 FilePathAndNameLength
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) FilePathAndName
  , uint8 DataFormatIdentifier
  , uint64 FileSizeUncompressed
  , uint64 FileSizeCompressed
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) MaxNumberOfBlockLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

/* @Trace: SWS_Dcm_91081 */
extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ProcessRequestReadFile(
  Dcm_OpStatusType OpStatus
  , uint16 FilePathAndNameLength
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) FilePathAndName
  , uint8 DataFormatIdentifier
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) FileSizeUncompressed
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) FileSizeCompressed
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) MaxNumberOfBlockLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

/* @Trace: SWS_Dcm_91082 */
extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ProcessRequestReadDir(
  Dcm_OpStatusType OpStatus
  , uint16 FilePathAndNameLength
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) FilePathAndName
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) DirInfoLength
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) MaxNumberOfBlockLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

/* @Trace: SWS_Dcm_91083 */
extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_WriteFile(
  Dcm_OpStatusType OpStatus
  , uint64 DataLength
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) Data
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

/* @Trace: SWS_Dcm_91085 */
extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ReadFileOrDir(
  Dcm_OpStatusType OpStatus
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) DataLength
  , P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

/*******************************************************************************
**                        File transfer function definition                   **
*******************************************************************************/
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ProcessRequestAddFileFuncType)(
  Dcm_OpStatusType OpStatus
  , uint16 FilePathAndNameLength
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) FilePathAndName
  , uint8 DataFormatIdentifier
  , uint64 FileSizeUncompressed
  , uint64 FileSizeCompressed
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) MaxNumberOfBlockLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ProcessRequestDeleteFileFunType)(
  Dcm_OpStatusType OpStatus
  , uint16 FilePathAndNameLength
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) FilePathAndName
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ProcessRequestReplaceFileFunType)(
  Dcm_OpStatusType OpStatus
  , uint16 FilePathAndNameLength
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) FilePathAndName
  , uint8 DataFormatIdentifier
  , uint64 FileSizeUncompressed
  , uint64 FileSizeCompressed
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) MaxNumberOfBlockLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ProcessRequestReadFileFunType)(
  Dcm_OpStatusType OpStatus
  , uint16 FilePathAndNameLength
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) FilePathAndName
  , uint8 DataFormatIdentifier
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) FileSizeUncompressed
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) FileSizeCompressed
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) MaxNumberOfBlockLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ProcessRequestReadDirFunType)(
  Dcm_OpStatusType OpStatus
  , uint16 FilePathAndNameLength
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) FilePathAndName
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) DirInfoLength
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) MaxNumberOfBlockLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_WriteFileFunType)(
  Dcm_OpStatusType OpStatus
  , uint64 DataLength
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) Data
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ReadFileOrDirFunType)(
  Dcm_OpStatusType OpStatus
  , P2VAR(uint64, AUTOMATIC, DCM_APPL_DATA) DataLength
  , P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

/*******************************************************************************
**          Configurable Interfaces - Security Access                         **
*******************************************************************************/
// Xxx_GetSeed
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_GetSeedAsyncFunType)(
  Dcm_OpStatusType OpStatus
  , P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Seed
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_GetSeedAsyncFunAdrType)(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pSecurityAccessRecord
  , Dcm_OpStatusType LucOpStatus
  , P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pSeed
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);

// Xxx_CompareKey
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_CompareKeyAsyncFunType)(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) Key
  , VAR(uint8, AUTOMATIC) LucOpStatus
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);

// Xxx_GetSecurityAttemptCounter
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_GetSecurityAttemptCounterFunType)(
  Dcm_OpStatusType OpStatus
  , P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) AttemptCounter);

// Xxx_SetSecurityAttemptCounter
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_SetSecurityAttemptCounterFunType)(
  Dcm_OpStatusType OpStatus
  , uint8 AttemptCounter);


/*******************************************************************************
**          Configurable Interfaces - Data Services                           **
*******************************************************************************/
// Xxx_ReadData
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ReadDataSyncFunType)(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ReadDataAsyncFunType)(
  Dcm_OpStatusType OpStatus
  , P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ReadDataAsyncErrorFunType)(
  Dcm_OpStatusType OpStatus
  , P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

// Xxx_WriteData
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_WriteDataFixedSyncFunType)(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) Data
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_WriteDataDynSyncFunType)(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) Data
  , uint16 DataLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_WriteDataFixedAsyncFunType)(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) Data
  , Dcm_OpStatusType OpStatus
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_WriteDataDynAsyncFunType)(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) Data
  , uint16 DataLength
  , Dcm_OpStatusType OpStatus
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);


// Xxx_ReadDataLength
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ReadDataLengthSyncFunType)(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ReadDataLengthAsyncFunType)(
  Dcm_OpStatusType OpStatus
  , P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);

// Xxx_ConditionCheckRead
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ConditionCheckReadSyncFunType)(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ConditionCheckReadAsyncFunType)(
  Dcm_OpStatusType OpStatus
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

// Xxx_GetScalingInformation
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_GetScalingInformationSyncFunType)(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ScalingInfo
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_GetScalingInformationAsyncFunType)(
  Dcm_OpStatusType OpStatus
  , P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ScalingInfo
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

// Xxx_ReturnControlToECU
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ReturnControlToEcuFunType)(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

// Xxx_ResetToDefault
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ResetToDefaultSyncFunType)(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ResetToDefaultAsyncFunType)(
  Dcm_OpStatusType OpStatus
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

// Xxx_FreezeCurrentState
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_FreezeCurrentStateSyncFunType)(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_FreezeCurrentStateAsyncFunType)(
  Dcm_OpStatusType OpStatus
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

// Xxx_ShortTermAdjustment
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ShortTermAdjustmentFixedSyncFunType)(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ControlStateInfo
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ShortTermAdjustmentDynSyncFunType)(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ControlStateInfo
  , uint16 DataLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ShortTermAdjustmentFixedAsyncFunType)(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ControlStateInfo
  , Dcm_OpStatusType OpStatus
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ShortTermAdjustmentDynAsyncFunType)(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ControlStateInfo
  , uint16 DataLength
  , Dcm_OpStatusType OpStatus
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);


/*******************************************************************************
**          Configurable Interfaces - Data Services DID Range                 **
*******************************************************************************/
// Xxx_IsDidAvailable
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_IsDidAvailableFunType)(
  uint16 DID
  , Dcm_OpStatusType OpStatus
  , P2VAR(Dcm_DidSupportedType, AUTOMATIC, DCM_APPL_DATA) Supported);

// Xxx_ReadDidData
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ReadDidDataFunType)(
  uint16 DID
  , P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data
  , Dcm_OpStatusType OpStatus
  , P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

// Xxx_WriteDidData
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_WriteDidDataFunType)(
  uint16 DID
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) Data
  , Dcm_OpStatusType OpStatus
  , uint16 DataLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

// Xxx_ReadDidRangeDataLength
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ReadDidRangeDataLengthFunType)(
  uint16 DID
  , Dcm_OpStatusType OpStatus
  , P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) DataLength);


/*******************************************************************************
**          Configurable Interfaces - Info Type Services                      **
*******************************************************************************/
// Xxx_GetInfotypeValueData
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_GetInfoTypeValueDataFunType)(
  Dcm_OpStatusType OpStatus
  , P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataValueBuffer
  , P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DataValueBufferSize);

/*******************************************************************************
**          Configurable Interfaces - Request Control Services                **
*******************************************************************************/
// Xxx_RequestControl
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_RequestControlFunType)(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) OutBuffer
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) InBuffer);


/*******************************************************************************
**          Configurable Interfaces - Callback DCM Request Services           **
*******************************************************************************/
// Xxx_StartProtocol
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_StartProtocolFunType)(
  Dcm_ProtocolType ProtocolType
  , uint16 TesterSourceAddress
  , uint16 ConnectionId);

// Xxx_StopProtocol
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_StopProtocolFunType)(
  Dcm_ProtocolType ProtocolType
  , uint16 TesterSourceAddress
  , uint16 ConnectionId);


/*******************************************************************************
**          Configurable Interfaces - Service Request Notification            **
*******************************************************************************/
// Xxx_Indication
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_IndicationFunType)(
  uint8 SID
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) RequestData
  , uint16 DataSize
  , uint8 ReqType
  , uint16 ConnectionId
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
  , Dcm_ProtocolType ProtocolType
  , uint16 TesterSourceAddress);

// Xxx_Confirmation
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ConfirmationFunType)(
  uint8 SID
  , uint8 ReqType
  , uint16 ConnectionId
  , Dcm_ConfirmationStatusType ConfirmationStatus
  , Dcm_ProtocolType ProtocolType
  , uint16 TesterSourceAddress);


/*******************************************************************************
**          Configurable Interfaces - Clear DTC Check Function                **
*******************************************************************************/
// Xxx_ClearDTCCheckFnc
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ClearDTCCheckFunType)(
  uint32 GoDTC
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);


/*******************************************************************************
**          Configurable Interfaces - Upload Download Services                **
*******************************************************************************/
// Xxx_ProcessRequestDownload
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ProcessRequestDownloadFunType)(
  Dcm_OpStatusType OpStatus
  , uint8 DataFormatIdentifier
  , uint8 MemoryIdentifier
  , uint32 MemoryAddress
  , uint32 MemorySize
  , P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) BlockLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

// Xxx_ProcessRequestTransferExit
#if ((DCM_TRANSFER_EXIT_SERVICE == STD_ON) && (DCM_TRANSFER_REQUEST_PARAM_RECORD_USED == STD_ON))
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ProcessRequestTransferExitFunType)(
  Dcm_OpStatusType OpStatus
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) transferRequestParameterRecord
  , uint32 transferRequestParameterRecordSize
  , P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) transferResponseParameterRecord
  , P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) transferResponseParameterRecordSize
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
#else
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ProcessRequestTransferExitFunType)(
  Dcm_OpStatusType OpStatus
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);
#endif /*(DCM_TRANSFER_EXIT_SERVICE == STD_ON) && (DCM_TRANSFER_REQUEST_PARAM_RECORD_USED == STD_ON)*/

// Xxx_ProcessRequestUpload
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_ProcessRequestUploadFunType)(
  Dcm_OpStatusType OpStatus
  , uint8 DataFormatIdentifier
  , uint8 MemoryIdentifier
  , uint32 MemoryAddress
  , uint32 MemorySize
  , P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) BlockLength
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

// Xxx_ProcessTransferDataRead
typedef P2FUNC(Dcm_ReturnReadMemoryType, DCM_CALLOUT_CODE, Dcm_ProcessTransferDataReadFunType)(
  Dcm_OpStatusType OpStatus
  , uint8 MemoryIdentifier
  , uint32 MemoryAddress
  , uint32 MemorySize
  , Dcm_RequestDataArrayType MemoryData
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

// Xxx_ProcessTransferDataWrite
typedef P2FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE, Dcm_ProcessTransferDataWriteFunType)(
  Dcm_OpStatusType OpStatus
  , uint8 MemoryIdentifier
  , uint32 MemoryAddress
  , uint32 MemorySize
  , const Dcm_RequestDataArrayType MemoryData
  , P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);

/*******************************************************************************
**          Others                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00763 SWS_Dcm_00764 */
typedef P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, Dcm_DiagnosticServiceFunType)(
  Dcm_ExtendedOpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);


#if (DCM_CNR_USED_SHA1 == STD_ON)
extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SignatureVerify(
    P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) dataPtr,
    VAR(uint32, AUTOMATIC) dataLength,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) signaturePtr,
    VAR(uint32, AUTOMATIC) signatureLength,
    P2CONST(Dcm_AsymPublicKeyType, AUTOMATIC, DCM_APPL_CONST) publicKey,
    P2VAR(Std_ReturnType, AUTOMATIC, DCM_APPL_CONST) verifyPtr);
#endif

#if (DCM_CSAC_CONFIGURED == STD_ON) || (DCM_AUTHENTICATION_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_GetRandomSeed
  (P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) RandomSeed);

extern FUNC(void, DCM_CALLOUT_CODE) Dcm_GetPublicKey
  (P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) PublicKey);
#endif

#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
extern FUNC(void, DCM_CALLOUT_CODE) Dcm_Authentication_User_CallOut (
  Dcm_OpStatusType OpStatus, 
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);

  extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SettingAccessRightsFailedFnc (
  P2VAR(Dcm_CertAuthorizationInfoType, AUTOMATIC, DCM_APPL_DATA) authorization,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);

  extern FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DeauthenticationFailedFnc (
  Dcm_OpStatusType OpStatus, 
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);
#endif

#define DCM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"

#endif /* End DCM_EXTERNALS_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
