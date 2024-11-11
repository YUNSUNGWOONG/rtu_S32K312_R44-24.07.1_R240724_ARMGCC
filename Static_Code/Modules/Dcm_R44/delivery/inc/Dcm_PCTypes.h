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
**  SRC-MODULE: Dcm_PCTypes.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Contain the definition of Dcm data types                      **
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
** 0.0.2     19-Mar-2020   LanhLT         Add SourceTesterAddress             **
**                                        in struct Dcm_PduIdTable            **
** 0.0.3     16-Aug-2020   HueKM          Correct all periodic structs        **
** 0.0.4     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.5     02-Nov-2020   LanhLT         Changes made as per #16832          **
** 0.0.6     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 1.0.1     05-Oct-2021   LanhLT         Changes made as per #20533          **
** 1.0.9     31-Mar-2023   LanhLT         Refer #CP44-1558, #CP44-1763        **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
** 1.1.0     15-Sep-2023   SY Kim         Refer #CP44-2768, #CP44-2676        **
** 1.1.1     30-Oct-2023   DanhTQ1        Refer #CP44-3035                    **
** 1.1.2     31-Oct-2023   DH Kwak        Refer #CP44-2873 #CP44-3194         **
** 1.4.1     01-Apr-2024   DanhTQ1        Refer #CP44-3362                    **
*******************************************************************************/
#ifndef DCM_PCTYPES_H
#define DCM_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm.h"
#include "Dcm_Externals.h"

#if (DCM_NVM_CONFIGURED == STD_ON)
#include "NvM.h"
#endif

#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
#include "KeyM.h"
#endif

/*******************************************************************************
** Structure declarations of Mode Condition                                   **
*******************************************************************************/
#if (DCM_MODE_CONDITION == STD_ON)
typedef P2FUNC(uint8, DCM_APPL_CODE, Dcm_GetCurrentModeFunType)(void);

typedef struct STagDcm_ModeConditionConfigType
{
  Dcm_GetCurrentModeFunType pGetCurrentMode;

  Dcm_ConditionType ConditionType;

  Dcm_CompareModeType CompareMode;

  P2CONST(uint32, AUTOMATIC, DCM_APPL_CONST) pPrimitiveCompareValue;

  uint32 PrimitiveCompareValue; 

  /* DcmSwcSRDataElementRef configure DcmDspExternalSRDataElementClass 
    if it is not configuration, udDID = 0
  */
  uint16 usDID;

  uint8 ucBsworSwcMode;

  uint8 NumberOfDataElementArray;

  /* DcmSwcSRDataElementRef configure DcmDspPidService01ExternalSRDataElementClass 
    if it is not configuration, ucDsPPIDDataIndex = FF
  */
  uint8 ucDspPIDDataIndex;

  Dcm_DataType ucSRDataType;

} Dcm_ModeConditionConfigType;

typedef P2CONST(Dcm_ModeConditionConfigType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_ModeConditionConfigConstPtrType;
#endif

#if (DCM_MODE_RULE == STD_ON)
typedef struct STagDcm_ModeRuleConfigType
{
  Dcm_LogicalOperatorType LogicalOperator;

  #if (DCM_DSP_MODE_RULE_NRC == STD_ON)
  Dcm_NegativeResponseCodeType NrcValue;
  #endif

  uint8 ucDcmNoOfModeCondnArg;

  uint8 ucIndexOfModeConditionIndexArray;

  uint8 ucDcmNoOfModeRuleArg;

  uint8 ucIndexOfModeRuleIndexArray;

} Dcm_ModeRuleConfigType;

typedef P2CONST(Dcm_ModeRuleConfigType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_ModeRuleConfigConstPtrType;
#endif

/*******************************************************************************
** Structure declarations of Pack UnPack Signal                               **
*******************************************************************************/
typedef struct STagDcm_PackUnPackType
{
  uint16 usSignalSize;

  boolean blByteConversion;

} Dcm_PackUnPackType;

typedef struct STagDcm_UnPackFuncType
{
  P2FUNC(void, DCM_APPL_CODE, pUnPackFunc)(
    P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutData,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRxData,
    P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pUnPackData);
} Dcm_UnPackFuncType;

typedef struct STagDcm_PackFuncType
{
  P2FUNC(void, DCM_APPL_CODE, pPackFunc)(
    P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pInData,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData,
    P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pPackData);
} Dcm_PackFuncType;

/*******************************************************************************
** Structure declarations of Diagnostic Session Service                       **
*******************************************************************************/
typedef struct STagDcm_DiagSessionConfigType
{
  Dcm_SesCtrlType ddSesCtrlLevel;

  Dcm_SesForBootType ucSesForBootLevel;

  uint16 usSesP2ServerMax;

  uint16 usSesP2StrServerMax;

} Dcm_DiagSessionConfigType;

typedef P2CONST(Dcm_DiagSessionConfigType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_SessionConfigConstPtrType;

/*******************************************************************************
** Structure declarations of Ecu Reset Service                                **
*******************************************************************************/
#if (DCM_ECURESET_SERVICE == STD_ON)
typedef struct STagDcm_EcuResetConfigType
{
  Dcm_EcuResetResponseType ucResToEcuReset;

  uint8 ucResetType;

} Dcm_EcuResetConfigType;

typedef P2CONST(Dcm_EcuResetConfigType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_EcuResetCfgPtrType;
#endif

/*******************************************************************************
** Structure declarations of Clear DTC Service                                **
*******************************************************************************/
#if (DCM_DSP_CLR_DIAG_SERVICE == STD_ON)
typedef struct STagDcm_DspClearDTCConfig
{
  Dcm_ClearDTCCheckFunType pClearDTCCheckFun;

  #if (DCM_MODE_RULE == STD_ON)
  boolean blModeRuleConfigured;

  Dcm_ModeType ucModeRuleIndex;
  #endif

} Dcm_DspClearDTCConfig;
#endif

/*******************************************************************************
** Structure declarations of Read DTC Service                                 **
*******************************************************************************/
#if ((DCM_READDTC_SUPPORT == STD_ON) && \
  (DCM_AUTHENTICATION_SERVICE == STD_ON) && \
  (DCM_NUM_OF_USER_DEFINED_FAULT_MEMORY > 0))
typedef struct STagDcm_DspReadDTCInfoConfigType
{
  Dcm_AuthenticationRoleType Role;

  uint8 MemoryId;
} Dcm_DspReadDTCInfoConfigType;

typedef P2CONST(Dcm_DspReadDTCInfoConfigType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_DspReadDTCInfoConfigConstPtrType;
#endif

/*******************************************************************************
** Structure declarations of Security Access Service                          **
*******************************************************************************/
typedef struct STagDcm_SecurityLevConfigType
{
  #if (DCM_DSP_SECURITY_SERVICE == STD_ON)
  /* Get seed function when Access Data Record is not present */
  Dcm_GetSeedAsyncFunType pGetSeedAsyncFun;

  /* Get seed function when Access Data Record is present */
  Dcm_GetSeedAsyncFunAdrType pGetSeedAsyncFunAdr;

  /* Compare key function */
  Dcm_CompareKeyAsyncFunType pCompareKeyAsyncFun;

  #if (DCM_NUM_OF_ATTEMPT_COUNTER_ENABLE != DCM_ZERO)
  /* Function to get the AttemptCounter value from the application */
  Dcm_GetSecurityAttemptCounterFunType pGetSecurityAttemptCounterFun;

  /* Function to set the AttemptCounter value to the application */
  Dcm_SetSecurityAttemptCounterFunType pSetSecurityAttemptCounterFun;
  #endif
  #endif

  /* Security level value */
  Dcm_SecLevelType ddSecLevel;

  /* Size of the AccessDataRecord used in GetSeed */
  uint32 ulSecurityADRSize;

  /* Size of security key */
  uint32 ulSizeOfKey;

  /* Size of security seed */
  uint32 ulSizeOfSeed;

  /* Delay time after the maximum number of failed security accesses is reach */
  uint32 usSecDelayTime;

  /* Start delay timer on power on (in ms) */
  uint32 usSecurityDelayTimeOnBoot;

  /* Number of failed security accesses after the delay time is activated */
  uint8 ucSecNumMaxAttDelay;

  /* Define the kind of interface that use for security access */
  Dcm_SecurityUsePortType ucSecurityUsePort;

  /* Control the existence of GetAttemptCounter and SetAttempCounter APIs */
  boolean blSecAttCounterEnable;

} Dcm_SecurityLevConfigType;

typedef P2CONST(Dcm_SecurityLevConfigType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_SecurityLevConfigConstPtrType;

/*******************************************************************************
** Structure declarations of security access service with Csm R44             **
*******************************************************************************/

#if (DCM_CRYPTO_R44_USED == STD_ON)
typedef struct STagDcm_SecureAccessCryptoConfigType
{
  uint32 ulPublicKeyId;

  uint32 ulCertVerifyJobId;

  uint32 ulCRLVerifyJobId;

  uint32 ulCRLHashJobId;

  uint32 ulRandomSeedKeyId;

  uint32 ulRandomJobId;

  uint32 ulCnRPublicKeyId;

  uint32 ulCnRVerifyJobId;

}Dcm_SecureAccessCryptoConfigType;
#endif

/*******************************************************************************
** Structure declarations of Communication Control Service                    **
*******************************************************************************/
#if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) \
     || (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))

typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_SchMSwitchCommModeFunType)(
  Dcm_CommunicationModeType CommunicationType);

typedef struct STagDcm_AllCommControlConfig
{
  Dcm_SchMSwitchCommModeFunType pSchMSwitchCommModeFunc;

  uint8 ComMChannelId;

  boolean ChannelUsed;

} Dcm_AllCommControlConfig;

typedef P2CONST(Dcm_AllCommControlConfig, AUTOMATIC, DCM_APPL_CONST)
  Dcm_AllCommControlConfigConstPtrType;

typedef struct STagDcm_CommControlConfigType
{
  Dcm_SchMSwitchCommModeFunType pSchMSwitchCommModeFunc;

  uint8 SubNetNumber;

  uint8 ComMChannelId;

  boolean ChannelUsed;

} Dcm_CommControlConfigType;

typedef P2CONST(Dcm_CommControlConfigType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_CommControlConfigConstPtrType;

typedef struct STagDcm_CommControlSubNodeConfigType
{
  Dcm_SchMSwitchCommModeFunType pSchMSwitchCommModeFunc;

  uint16 SubNodeId;

  uint8 ComMChannelId;

  boolean SubNodeUsed;
  
} Dcm_CommControlSubNodeConfigType;

typedef P2CONST(Dcm_CommControlSubNodeConfigType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_CommControlSubNodeConfigConstPtrType;
#endif

/*******************************************************************************
** Structure declarations of Read Memory By Address Service                   **
*******************************************************************************/
#if ((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) || \
  (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
typedef struct STagDcm_ReadMemRngInfoConfigType
{
  Dcm_Uint8ConstPtrType pReadMemRngSes;

  Dcm_Uint8ConstPtrType pReadMemRngSec;

  uint32 ulReadMemRngHigh;

  uint32 ulReadMemRngLow;

  #if (DCM_MODE_RULE == STD_ON)
  Dcm_ModeType ucDIDmoderuleArrayindex;
  #endif

  uint8 ReadMemSesCount;
  
  uint8 ucReadMemSecCount;

  uint8 ucReadMemoryIdentifier;

  boolean blUseMemoryValue;

  #if (DCM_MODE_RULE == STD_ON)
  boolean blModeRuleConfigured;
  #endif

} Dcm_ReadMemRngInfoConfigType;

typedef P2CONST(Dcm_ReadMemRngInfoConfigType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_ReadMemRngInfoConfigConstPtrType;
#endif

/*******************************************************************************
** Structure declarations of Write Memory By Address Service                  **
*******************************************************************************/
#if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
typedef struct STagDcm_WriteMemRngInfoConfigType
{
  Dcm_Uint8ConstPtrType pWriteMemRngSes;

  Dcm_Uint8ConstPtrType pWriteMemRngSec;

  uint32 ulWriteMemRngHigh;

  uint32 ulWriteMemRngLow;

  #if (DCM_MODE_RULE == STD_ON)
  Dcm_ModeType ucDIDmoderuleArrayindex;
  #endif

  uint8 WriteMemSesCount;

  uint8 ucWriteMemSecCount;

  uint8 ucWriteMemoryIdentifier;

  boolean blUseMemoryValue;

  #if (DCM_MODE_RULE == STD_ON)
  boolean blModeRuleConfigured;
  #endif

} Dcm_WriteMemRngInfoConfigType;

typedef P2CONST(Dcm_WriteMemRngInfoConfigType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_WriteMemRngInfoConfigConstPtrType;
#endif

/*******************************************************************************
** Structure declarations of Did Services                                     **
*******************************************************************************/
#if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
#if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
typedef struct STagDcm_DIDInfoTypeDidWrite
{
  /* Pointer to array of sessions supporting the did for write */
  Dcm_Uint8ConstPtrType pDidWriteSession;

  /* Pointer to array of security levels supporting the did for write */
  Dcm_Uint8ConstPtrType pDidWriteSecurity;

  #if (DCM_MODE_RULE == STD_ON)
  /* Variable to hold the index of mode rule configuration */
  Dcm_ModeType ucModeRuleIndex;
  #endif

  #if(DCM_AUTHENTICATION_SERVICE == STD_ON)
  /* Variable to hold the role of did for write */
  Dcm_AuthenticationRoleType ddDidWriteRole;
  #endif

  /* Number of sessions */
  uint8 ucDidWriteSesCount;

  /* Number of security levels */
  uint8 ucDidWriteSecCount;

  #if (DCM_MODE_RULE == STD_ON)
  /* Determine if the mode rule is configured or not */
  boolean blModeRuleConfigured;
  #endif

} Dcm_DIDInfoTypeDidWrite;

typedef P2CONST(Dcm_DIDInfoTypeDidWrite, AUTOMATIC, DCM_APPL_CONST)
  Dcm_DidWriteConfigConstPtrType;
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) \
     || (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON) \
     || (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON) \
     || (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
typedef struct STagDcm_DIDInfoTypeDidRead
{
  /* Pointer to array of sessions supporting the DID for Read */
  Dcm_Uint8ConstPtrType pDidReadSession;

  /* Pointer to array of security levels supporting the DID for Read */
  Dcm_Uint8ConstPtrType pDidReadSecurity;

  #if (DCM_MODE_RULE == STD_ON)
  /* Variable to hold the index of moderuleArrayindex */
  Dcm_ModeType ucDIDmoderuleArrayindex;
  #endif

  #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
  Dcm_AuthenticationRoleType DidReadRole;
  #endif

  /* Number of sessions */
  uint8 ucDidReadSesCount;

  /* Number of security levels */
  uint8 ucDidReadSecCount;

  #if (DCM_MODE_RULE == STD_ON)
  boolean blModeRuleConfigured;
  #endif

} Dcm_DIDInfoTypeDidRead;

typedef P2CONST(Dcm_DIDInfoTypeDidRead, AUTOMATIC, DCM_APPL_CONST) 
  Dcm_DidReadConfigConstPtrType;
#endif

#if (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
typedef struct STagDcm_DIDInfoTypeDidCtrl
{
  /* Pointer to array of sessions supporting the requested DID */
  Dcm_Uint8ConstPtrType pDidCtrlSession;

  /* Pointer to array of security levels supporting the requested DID*/
  Dcm_Uint8ConstPtrType pDidCtrlSecurity;

  /* The value defines the size of the controlEnableMaskRecord in bytes */
  uint32 ulDidControlMaskSize;

  /* Indicate the presence of controlEnableMask */
  Dcm_DidControlMaskType ucDidControlMask;

  #if (DCM_MODE_RULE == STD_ON)
  /*variable to hold the index of moderuleArrayindex */
  Dcm_ModeType ucModeRuleIndex;
  #endif

  #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
  Dcm_AuthenticationRoleType ddDidCtrlRole;
  #endif

  /* Number of sessions */
  uint8 ucDidCtrlSesCount;

  /* Number of security levels */
  uint8 ucDidCtrlSecCount;

  /* This indicates the presence of Freeze current state */
  boolean blFreezeCrntState;

  /* This indicates the presence of Reset to default */
  boolean blResetToDefault;

  /* This indicates the presence of Short term adjustment */
  boolean blShrtTermAdj;

  #if (DCM_MODE_RULE == STD_ON)
  /* Variable to hold the index of moderuleArrayindex */
  boolean blModeRuleConfigured;
  #endif

} Dcm_DIDInfoTypeDidCtrl;

typedef P2CONST(Dcm_DIDInfoTypeDidCtrl, AUTOMATIC, DCM_APPL_CONST)
  Dcm_DidCtrlConstPtrType;
#endif

typedef struct STagDcm_DIDInfoType
{
  #if (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_DidCtrlConstPtrType pDidControl;
  #endif

  #if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) \
      || (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON) \
      || (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON) \
      || (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
  Dcm_DidReadConfigConstPtrType pDidRead;
  #endif

  #if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_DidWriteConfigConstPtrType pDidWrite;
  #endif

  /* Indicates if this DID can be dynamically defined or not */
  boolean blDynamicallyDefined;

} Dcm_DIDInfoType;

typedef P2CONST(Dcm_DIDInfoType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_DidInfoConfigConstPtrType;

typedef struct STagDcm_DataInfoType
{
  /* Provides the  size of the scaling information */
  uint32 ulDataScalingInfoSize;

} Dcm_DataInfoType;

typedef P2CONST(Dcm_DataInfoType, AUTOMATIC, DCM_APPL_CONST) 
  Dcm_DataInfoConfigConstPtrType;

#if (DCM_OBD_DID_SUPPORT_INFO == STD_ON)
typedef struct STagDcm_DcmDspDidSupportInfo
{
  uint8 ucDidSupportInfoLen;

  uint8 ucDidSupportInfoPos;

} Dcm_DcmDspDidSupportInfo;

typedef P2CONST(Dcm_DcmDspDidSupportInfo, AUTOMATIC, DCM_APPL_CONST) 
  Dcm_DcmDspDidSupportInfoConstPtrType;
#endif

typedef struct STagDcm_DcmDspDataConfig
{
  #if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) \
       || (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
  Dcm_ReadDataSyncFunType pReadDataSyncFun;
  Dcm_ReadDataAsyncFunType pReadDataAsyncFun;
  Dcm_ReadDataAsyncErrorFunType pReadDataAsyncErrorFun;

  Dcm_ReadDataLengthSyncFunType pReadDataLengthSyncFun;
  Dcm_ReadDataLengthAsyncFunType pReadDataLengthAsyncFun;

  Dcm_ConditionCheckReadSyncFunType pConditionCheckReadSyncFun;
  Dcm_ConditionCheckReadAsyncFunType pConditionCheckReadAsyncFun;
  #endif

  #if (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_ShortTermAdjustmentFixedSyncFunType pShortTermAdjustmentFixedSyncFun;
  Dcm_ShortTermAdjustmentDynSyncFunType pShortTermAdjustmentDynSyncFun;
  Dcm_ShortTermAdjustmentFixedAsyncFunType pShortTermAdjustmentFixedAsyncFun;
  Dcm_ShortTermAdjustmentDynAsyncFunType pShortTermAdjustmentDynAsyncFun;

  Dcm_ReturnControlToEcuFunType pReturnControlToEcuFun;

  Dcm_ResetToDefaultSyncFunType pResetToDefaultSyncFun;
  Dcm_ResetToDefaultAsyncFunType pResetToDefaultAsyncFun;

  Dcm_FreezeCurrentStateSyncFunType pFreezeCurrentStateSyncFun;
  Dcm_FreezeCurrentStateAsyncFunType pFreezeCurrentStateAsyncFun;
  #endif

  #if (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_GetScalingInformationSyncFunType pGetScalingInformationSyncFun;
  Dcm_GetScalingInformationAsyncFunType pGetScalingInformationAsyncFun;
  #endif

  #if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_WriteDataFixedAsyncFunType pWriteDataFixedAsyncFun;
  Dcm_WriteDataDynAsyncFunType pWriteDataDynAsyncFun;
  Dcm_WriteDataFixedSyncFunType pWriteDataFixedSyncFun;
  Dcm_WriteDataDynSyncFunType pWriteDataDynSyncFun;
  #endif

  /* Pointer to Dcm_DataInfoType type */
  Dcm_DataInfoConfigConstPtrType pDataInfo;

  /* @Trace: ECUC_Dcm_01106 */
  uint16 usDcmDspDataByteSize;

  /* NRAM blockId to access the data */
  NvM_BlockIdType usDcmDspDataBlockIdRef;

  #if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
   /* Sender-Reciever Interface */
  uint8 ucWriteFunctionIndex;
  #endif

  #if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) \
       || (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) \
       || (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
  /* Sender-Reciever Interface */
  uint8 ucReadFunctionIndex;
  #endif

  #if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) \
       || (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
  /* ECU Signal */
  uint8 ucEcuSignalFunctionIndex;
  #endif

  /* UsePort */
  Dcm_DataUsePortType ucDcmDspDataUsePort;

  /* DataType*/
  Dcm_DataType ucDcmDspDataType;

  #if (DCM_OBD_DID_SUPPORT_INFO == STD_ON)
  uint8 ucDidDataSupportInfoBit;

  Dcm_DcmDspDidSupportInfoConstPtrType pDIDDataSupportInfoRef;
  #endif

} Dcm_DcmDspDataconfig;

typedef P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) 
  Dcm_DataConfigConstPtrType;

typedef struct STagDcm_DidSignalConfigType
{
  /* Pointer to data configuration */
  Dcm_DataConfigConstPtrType pDataConfig;

  /* Store signal byte offset */
  uint16 usByteOffset;

  /* Store pack function index */
  uint8 ucPackFuncIndex;

  /* Store unpack function index */
  uint8 ucUnPackFuncIndex;

  /* Store the current status of signal */
  uint8 ucSignalOpStatus;

  /* Determine whether perform byte conversion or not */
  boolean blByteConversion;

} Dcm_DidSignalConfigType;

typedef P2VAR(Dcm_DidSignalConfigType, AUTOMATIC, DCM_APPL_DATA) 
  Dcm_DidSignalConfigPtrType;

typedef struct STagDcm_DIDParaConfig
{
  /* Reference to DcmDspData container and position relevant for this DID */
  Dcm_DidSignalConfigPtrType pDcmDspSignal;

  /* Reference to DcmDspDidInfo containing information on this DID */
  Dcm_DidInfoConfigConstPtrType pDidInfo;

  /* Pointer to array of DID reference */
  Dcm_Uint16ConstPtrType pDidRef;

  /*  2 byte Identifier of the DID */
  uint16 usDcmDspDidIdentifier;

  /* Number of DidReferrence count */
  uint16 usDidRefCount;

  /* Length of a DID in byte */
  uint16 usDidSize;

  /* Number of DcmDspSignal */
  uint8 ucDcmDspSignalCount;

  /*  Allow to activate or deactivate the usage of a DID, for multi purpose
  ECUs true = DID available false = DID not available */
  boolean blDspDidUsed;

  /* Determine whether the Did Size is configured */
  boolean blDidSizeConfigured;

  Dcm_DidUsePortType ucDcmDspDidUsePort;

  #if (DCM_OBD_DID_SUPPORT_INFO)
  Dcm_DcmDspDidSupportInfoConstPtrType pDcmDspDidSupportInfo;
  #endif

  #if (DCM_MODE_CONDITION_SR_DID_USED == STD_ON)
  uint8 ucSRSignalIndex;
  #endif

} Dcm_DIDParaConfig;

typedef P2CONST(Dcm_DIDParaConfig, AUTOMATIC, DCM_APPL_CONST) 
  Dcm_DidParaConfigConstPtrType;

typedef struct STagDcm_DIDRangeConfig
{
  Dcm_IsDidAvailableFunType pIsDidAvailableFun;

  Dcm_ReadDidDataFunType pReadDidDataFun;

  Dcm_WriteDidDataFunType pWriteDidDataFun;

  /* Reference to DcmDspDidInfo containing information on this DID */
  Dcm_DidInfoConfigConstPtrType pDidInfo;

  /*  DID Range Lower limit */
  uint16 usDidRangeIdLowerLimit;

  /*  DID Range Upper limit */
  uint16 usDidRangeIdUpperLimit;

  /*  Maximum data length in bytes */
  uint16 usDidRangeMaxDataLength;

  /* Status of DID signal value read / write operation */
  uint8 ucDidRangeOpStatus;

  /*  Parameter specifying if there are gaps in the DID range */
  boolean blDidRangeHasGaps;

  boolean blDcmDspDidRangeUsePort;

} Dcm_DIDRangeConfig;

typedef P2VAR(Dcm_DIDRangeConfig, AUTOMATIC, DCM_APPL_DATA) 
  Dcm_DidRangeConfigPtrType;
#endif

#if(((DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)) && \
   (DCM_DATA_SENDER_RECEIVER == STD_ON) || \
   (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
#if (DCM_READ_WRITE_SEND_RECV_UINT8 == STD_ON)
typedef struct STagDcm_DIDSigReadWriteUint8Function
{
  #if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pWriteDataUint8Func)
    (P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) Data);
  #endif

  #if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
       (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pReadDataUint8Func)
    (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);
  #endif

} Dcm_DIDSigReadWriteUint8Function;
#endif

#if (DCM_READ_WRITE_SEND_RECV_UINT16 == STD_ON)
typedef struct STagDcm_DIDSigReadWriteUint16Function
{
  #if(DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pWriteDataUint16Func)
    (P2CONST(uint16, AUTOMATIC, DCM_APPL_CONST) Data);
  #endif

  #if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
       (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pReadDataUint16Func)
    (P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) Data);
  #endif

} Dcm_DIDSigReadWriteUint16Function;
#endif

#if (DCM_READ_WRITE_SEND_RECV_UINT32 == STD_ON)
typedef struct STagDcm_DIDSigReadWriteUint32Function
{
  #if(DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pWriteDataUint32Func)
    (P2CONST(uint32, AUTOMATIC, DCM_APPL_CONST) Data);
  #endif

  #if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
       (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pReadDataUint32Func)
    (P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) Data);
  #endif

} Dcm_DIDSigReadWriteUint32Function;
#endif

#if (DCM_READ_WRITE_SEND_RECV_SINT8 == STD_ON)
typedef struct STagDcm_DIDSigReadWriteSint8Function
{
  #if(DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pWriteDataSint8Func)
    (P2CONST(sint8, AUTOMATIC, DCM_APPL_CONST) Data);
  #endif

  #if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
       (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pReadDataSint8Func)
    (P2VAR(sint8, AUTOMATIC, DCM_APPL_DATA) Data);
  #endif

} Dcm_DIDSigReadWriteSint8Function;
#endif

#if (DCM_READ_WRITE_SEND_RECV_SINT16 == STD_ON)
typedef struct STagDcm_DIDSigReadWriteSint16Function
{
  #if(DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pWriteDataSint16Func)
    (P2CONST(sint16, AUTOMATIC, DCM_APPL_CONST) Data);
  #endif

  #if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
       (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pReadDataSint16Func)
    (P2VAR(sint16, AUTOMATIC, DCM_APPL_DATA) Data);
  #endif

} Dcm_DIDSigReadWriteSint16Function;
#endif

#if(DCM_READ_WRITE_SEND_RECV_SINT32 == STD_ON)
typedef struct STagDcm_DIDSigReadWriteSint32Function
{
  #if(DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pWriteDataSint32Func)
    (P2CONST(sint32, AUTOMATIC, DCM_APPL_CONST) Data);
  #endif

  #if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
       (DCM_MODE_CONDITION_SR_DID_USED== STD_ON))
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pReadDataSint32Func)
    (P2VAR(sint32, AUTOMATIC, DCM_APPL_DATA) Data);
  #endif

} Dcm_DIDSigReadWriteSint32Function;
#endif
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
#if (DCM_USE_ECU_SIGNAL_ENABLED == STD_ON)
#if (DCM_DSP_USE_ECU_SIGNAL_UINT8 == STD_ON)
typedef struct STagDcm_DIDEcuSignalUint8Function
{
  P2FUNC(void, DCM_APPL_CODE, pDataReadEcuSignalUint8)
    (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) signal);

  P2FUNC(void, DCM_APPL_CODE, pDataControlEcuSignalUint8Fnc)
    (uint8 action, uint8 signal);

} Dcm_DIDEcuSignalUint8Function;
#endif

#if (DCM_DSP_USE_ECU_SIGNAL_UINT16 == STD_ON)
typedef struct STagDcm_DIDEcuSignalUint16Function
{
  P2FUNC(void, DCM_APPL_CODE, pDataReadEcuSignalUint16)
    (P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) signal);

  P2FUNC(void, DCM_APPL_CODE, pDataControlEcuSignalUint16Fnc)
    (uint8 action, uint16 signal);

} Dcm_DIDEcuSignalUint16Function;
#endif

#if (DCM_DSP_USE_ECU_SIGNAL_UINT32 == STD_ON)
typedef struct STagDcm_DIDEcuSignalUint32Function
{
  P2FUNC(void, DCM_APPL_CODE, pDataReadEcuSignalUint32)
    (P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) signal);

  P2FUNC(void, DCM_APPL_CODE, pDataControlEcuSignalUint32Fnc)
    (uint8 action, uint32 signal);

} Dcm_DIDEcuSignalUint32Function;
#endif

#if (DCM_DSP_USE_ECU_SIGNAL_SINT8 == STD_ON)
typedef struct STagDcm_DIDSignalSint8Function
{
  P2FUNC(void, DCM_APPL_CODE, pDataReadEcuSignalSint8)
    (P2VAR(sint8, AUTOMATIC, DCM_APPL_DATA) signal);

  P2FUNC(void, DCM_APPL_CODE, pDataControlEcuSignalSint8Fnc)
    (uint8 action, sint8 signal);

} Dcm_DIDEcuSignalSint8Function;
#endif

#if (DCM_DSP_USE_ECU_SIGNAL_SINT16 == STD_ON)
typedef struct STagDcm_DIDEcuSignalSint16Function
{
  P2FUNC(void, DCM_APPL_CODE, pDataReadEcuSignalSint16)
    (P2VAR(sint16, AUTOMATIC, DCM_APPL_DATA) signalSint16);

  P2FUNC(void, DCM_APPL_CODE, pDataControlEcuSignalSint16Fnc)
    (uint8 action, sint16 signal);

} Dcm_DIDEcuSignalSint16Function;
#endif

#if(DCM_DSP_USE_ECU_SIGNAL_SINT32 == STD_ON)
typedef struct STagDcm_DIDEcuSignalSint32Function
{
  P2FUNC(void, DCM_APPL_CODE, pDataReadEcuSignalSint32)
    (P2VAR(sint32, AUTOMATIC, DCM_APPL_DATA) signalSint32);

  P2FUNC(void, DCM_APPL_CODE, pDataControlEcuSignalSint32Fnc)
    (uint8 action, sint32 signal);

} Dcm_DIDEcuSignalSint32Function;
#endif
#endif
#endif

/*******************************************************************************
** Structure declarations of Dynamically Defined by Identifier Service        **
*******************************************************************************/
#if (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
typedef struct STagDcm_MemAddrInfoType
{
  /* Specify the memory source address information */
  uint32 ulMemAdd;

  /* Specify the total number of bytes from the memory address */
  uint32 ulMemSize;

  /* Store the priority in response message of read data services */
  uint8 ucPriority;

  /* Store memory identifier in case multiple flash devices are used */
  uint8 ucMemoryId;

} Dcm_MemAddInfoType;

typedef P2VAR(Dcm_MemAddInfoType, AUTOMATIC, DCM_APPL_DATA)
  Dcm_MemAddInfoPtrType;

typedef struct STagDcm_SourceDidInfoType
{
  /* Store source data identifier */
  uint16 usSourceDid;

  /* Specify the total number of bytes from the source data record */
  uint8 ucMemSize;

  /* Store the priority in response message of read data services */
  uint8 ucPriority;

  /* Specify the starting byte position in the source data record */
  uint8 ucPosInSource;

} Dcm_SourceDidInfoType;

typedef P2VAR(Dcm_SourceDidInfoType, AUTOMATIC, DCM_APPL_DATA)
  Dcm_SourceDidInfoPtrType;

typedef struct STagDcm_DynDidInfoType
{
  /* Pointer to array that contains memory address source */
  Dcm_MemAddInfoPtrType pMemAddInfo;

  /* Pointer to array that contains data identifier source */
  Dcm_SourceDidInfoPtrType pSourceDidInfo;

  /* Store data identifier */
  uint16 usDynDid;

  /* Store maximum number of source elements */
  uint8 ucMaxElement;

  /* Store number of current elements of memory address source */
  uint8 ucMemAddCount;

  /* Store number of current elements of data identifier source */
  uint8 ucSourceDidCount;

  /* Determine if the data identifier is already dynamically defined */
  boolean blActive;

} Dcm_DynDidInfoType;

typedef P2VAR(Dcm_DynDidInfoType, AUTOMATIC, DCM_APPL_DATA)
  Dcm_DynDidInfoPtrType;
#endif

/*******************************************************************************
** Structure declarations of Read Data By Periodic Identifier Service         **
*******************************************************************************/
#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
typedef struct STagDcm_PeriodicStatusType
{
  uint8 ucTxPduIdx;

  uint8 ucDataInfoIdx;

  boolean blOnResTrans;

  boolean blOnInitRequest;

  PduIdType ddRxPduId;

} Dcm_PeriodicStatusType;

typedef struct STagDcm_PeriodicSchedulerInfoType
{
  uint16 pQueueData[DCM_MAX_PDID_SCHEDULER];

  uint8 pTimerCount[DCM_PDID_NUM_OF_TIMER];

  uint8 ucQueueRear;

  uint8 ucQueueFront;

  uint8 ucQueueSize;

  uint8 ucNewNumPdid;

  uint8 ucActiveNumPdid;

} Dcm_PeriodicSchedulerInfoType;

typedef struct STagDcm_PeriodicDidInfoType
{
  uint16 usDid;

  uint16 usDidLen;

  uint8 ucState;

  uint8 ucTmMode;

  boolean blActive;

  /*
    DCM_PDID_INACTIVE
    DCM_PDID_FIRST_RESPONSE
    DCM_PDID_SCHEDULER_RESPONSE
  */
  uint8 ucStatus;

} Dcm_PeriodicDidInfoType;

typedef P2VAR(Dcm_PeriodicDidInfoType, AUTOMATIC, DCM_APPL_DATA)
  Dcm_PeriodicDidInfoPtrType;

typedef struct STagDcm_PeriodicDataInfoType
{
  Dcm_Uint8PtrType pDataBuffer;

  uint32 ulMaxDataLen;

  uint32 ulDataLen;

  uint8 ucDataStatus;

} Dcm_PeriodicDataInfoType;

typedef P2VAR(Dcm_PeriodicDataInfoType, AUTOMATIC, DCM_APPL_DATA)
  Dcm_PeriodicDataInfoPtrType;

typedef struct STagDcm_PeriodicTxPduType
{
  /* Status of the ongoing RxPduId */
  Dcm_Uint8PtrType pPerPduIdStatus;

  /* TxPduId for periodic transmission */
  PduIdType ddPerTxPduId;

  /* Handle Id to be used by the Lower Layer */
  uint16 usPerTxConfirmPduId;

  /* Index to the data buffer info */
  uint8 ucDataBufferId;

  /* Mask required for updating the status of TxPduId */
  uint16 usPerPduIdStatusMask;

  /* Busy status of this Tx connection */
  boolean blBusyStatus;

} Dcm_PeriodicTxPduType;

typedef P2VAR(Dcm_PeriodicTxPduType, AUTOMATIC, DCM_APPL_DATA)
  Dcm_PeriodicTxPduPtrType;
#endif

/*******************************************************************************
** Structure declaration of Routine Control Service                           **
*******************************************************************************/
#if (DCM_ROUTINECONTROL_SERVICE == STD_ON)
typedef struct STagDcm_CommonAuthorizationType
{
  /* Pointer to the list of session levels */
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pSessionLevel;

  /* Pointer to the list of security levels */
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pSecurityLevel;

  #if (DCM_MODE_RULE == STD_ON)
  /* The index of mode rule in configuration sets */
  Dcm_ModeType ucModeRuleIndex;
  #endif

  /* Number of session levels in supported list */
  uint8 ucSessionCount;

  /* Number of security levels in supported list */
  uint8 ucSecurityCount;

  #if (DCM_MODE_RULE == STD_ON)
  /* Determine whether the check of mode rule is configured */
  boolean blModeRuleConfigured;
  #endif

} Dcm_CommonAuthorizationType;

typedef P2CONST(Dcm_CommonAuthorizationType, AUTOMATIC, DCM_APPL_DATA) 
  Dcm_CommonAuthorizationPtrType;

typedef struct STagDcm_RoutineSignalType
{
  uint16 usSignalPos;

  uint16 usSignalSize;

  Dcm_DataType ucSignalType;

  uint8 ucSignalByteType;

  uint8 ucPackFuncIndex;

  uint8 ucUnPackFuncIndex;

  boolean blByteConversion;

} Dcm_RoutineSignalType;

typedef P2CONST(Dcm_RoutineSignalType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_RoutineSignalPtrType;

typedef struct STagDcm_RoutineInfoConfigType
{
  /* Pointer to routine input signals */
  Dcm_RoutineSignalPtrType pRoutineInSignal;

  /* Pointer to routine output signals */
  Dcm_RoutineSignalPtrType pRoutineOutSignal;

  /* Pointer to common authorizarion configuration */
  Dcm_CommonAuthorizationPtrType pCommonAuthorization;

  /* Number of input signals */
  uint16 usNumOfInSignal;

  /* Number of output signals */
  uint16 usNumOfOutSignal;

  #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
  /* Store authentication role */
  Dcm_AuthenticationRoleType ddRoutineRole;
  #endif

  /* Determine whether routine confirmation is enable */
  boolean blConfirmEnable;

} Dcm_RoutineInfoConfigType;

typedef P2CONST(Dcm_RoutineInfoConfigType, AUTOMATIC, DCM_APPL_CONST) 
  Dcm_RoutineInfoConfigPtrType;

typedef struct STagDcm_RoutineConfigType
{
  /* Pointer to routine stop information */
  Dcm_RoutineInfoConfigPtrType pRoutineStop;

  /* Pointer to routine start information */
  Dcm_RoutineInfoConfigPtrType pRoutineStart;

  /* Pointer to routine request result information */
  Dcm_RoutineInfoConfigPtrType pRoutineRequestResult;

  /* 2 bytes identifier of the RID */
  uint16 usRoutineId;

  /* Manufacturer specific value for OBD RID */
  uint8 ucRoutineInfoByte;

  /* Allow to activate or deactivate the usage of a routine */
  boolean blRoutineUsed;

  /* If this parameter is set to true, the DCM uses a port interface */
  boolean blRoutineUsePort;

} Dcm_RoutineConfigType;

typedef P2CONST(Dcm_RoutineConfigType, AUTOMATIC, DCM_APPL_CONST) 
  Dcm_RoutineConfigPtrType;
#endif

/*******************************************************************************
** Structure declaration of Upload Download Services                          **
*******************************************************************************/
#if ((DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON) || \
     (DCM_REQUEST_UPLOAD_SERVICE == STD_ON)   || \
     (DCM_TRANSFER_DATA_SERVICE == STD_ON)    || \
     (DCM_TRANSFER_EXIT_SERVICE == STD_ON))
typedef struct STagDcm_MemoryTransferFncConfigType
{
  #if (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)
  /* Function to process Request Download Service */
  Dcm_ProcessRequestDownloadFunType pProcessRequestDownloadFnc;
  #endif

  #if (DCM_REQUEST_UPLOAD_SERVICE == STD_ON)
  /* Function to process Request Upload Service */
  Dcm_ProcessRequestUploadFunType pProcessRequestUploadFnc;
  #endif

  #if (DCM_TRANSFER_DATA_SERVICE == STD_ON)
  /* Function to process Transfer Data for Request Upload Service */
  Dcm_ProcessTransferDataReadFunType pProcessTransferDataReadFnc;

  /* Function to process Transfer Data for Request Download Service */
  Dcm_ProcessTransferDataWriteFunType pProcessTransferDataWriteFnc;
  #endif
  
  #if (DCM_TRANSFER_EXIT_SERVICE == STD_ON)
  /* Function to process Request Transfer Exit Service */
  Dcm_ProcessRequestTransferExitFunType pProcessRequestTransferExitFnc;
  #endif

} Dcm_MemoryTransferFncConfigType;
#endif

#if (DCM_TRANSFER_DATA_SERVICE == STD_ON) || \
    (DCM_FILE_TRANSFER_SERVICE == STD_ON)
typedef struct StagDcm_FileTransferFncConfigType
{
  #if (DCM_FILE_TRANSFER_SERVICE == STD_ON)
  /* Function to process Request Add File */
  Dcm_ProcessRequestAddFileFuncType pProcessRequestAddFileFnc;

  /* Function to process Request Delete File */
  Dcm_ProcessRequestDeleteFileFunType pProcessRequestDeleteFileFnc;

  /* Function to process Request Replace File */
  Dcm_ProcessRequestReplaceFileFunType pProcessRequestReplaceFileFnc;

  /* Function to process Request Read File */
  Dcm_ProcessRequestReadFileFunType pProcessRequestReadFileFnc;

  /* Function to process Request Read Dir */
  Dcm_ProcessRequestReadDirFunType pProcessRequestReadDirFnc;
  #endif

  #if (DCM_TRANSFER_DATA_SERVICE == STD_ON)
  /* Function to process write file in Transfer Data Service */
  Dcm_WriteFileFunType pWriteFileFnc;

  /* Function to process read file or dir in Transfer Data Service */
  Dcm_ReadFileOrDirFunType pReadFileOrDirFnc;
  #endif

} Dcm_FileTransferFncConfigType;
#endif

#if (DCM_FILE_TRANSFER_SERVICE == STD_ON)
typedef struct STagDcm_RequestFileTransferConfigType
{
  /* The value of fileSizeOrDirInfoParameterLength parameter */
  uint8 ucFileSizeOrDirInfoLength;

  /* The value of lengthFormatIdentifier parameter */
  uint8 uclengthFormatIdentifier;

  #if (DCM_FILE_TRANSFER_USE_PORT == STD_ON)
  /* Maximum size for the fileAndDirName parameter with RTE interfaces */
  uint16 usMaxFileAndDirNameSize;
  #endif

} Dcm_FileTransferConfigType;
#endif

/*******************************************************************************
** Structure declarations of Response On Event Service                        **
*******************************************************************************/
#if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
typedef struct STagDcm_DspRoeConfiguration
{
  /* Reference to a Did which is watched. 
   * Only evaluated if supported eventType is onChangeOfDataIdentifier */
  P2CONST(uint16, AUTOMATIC, DCM_APPL_CONST) pRoeDidRef;

  /* Initial Roe status of this RoeEvent */
  Dcm_RoeStatusType ucRoeInitialEventStatus;

  /* EventId for a global identification of this ROE event */
  uint8 ucRoeEventId;

  /* Value of the relevant DTCStatusMask. 
   * Only evaluated if supported eventType is onDTCStatusChange */
  uint8 ucRoeDTCStatusMask;

  /* Property for supported eventType */
  /* True: onChangeOfDataIdentifier, False: onDTCStatusChange */
  boolean blIsOnChngOfDIDRxed;

} Dcm_DspRoeConfiguration;

typedef struct STagDcm_RoeRequestInfo
{
  /* Configuration for each RoeEvent */
  Dcm_DspRoeConfiguration RoeConfig;

  /* Request data length (excluding service identifier) */
  Dcm_MsgLenType ddRoeReqDataLen;

  uint16 usDIDValueSize;

  /* eventTypeRecord from requested msg */
  uint16 ucEventTypeRecord;

  /* Request data, including service identifier */
  Dcm_MsgItemType RoeReqData[DCM_ROE_MAX_REQ_DATA_LEN];

  /* Temporary buffer to store the DID value managed internally */
  uint8 ucInternalBuffer[DCM_ROE_DID_MAX_DATA_LENGTH];

  PduIdType ddRoeRxPduId;

  PduIdType ddRoeTxPduId;

  /* Rx address type */
  uint8 ucRxAddrType;

  /* Current state */
  Dcm_RoeStatusType ucCurrentState;

  Dcm_RoeEventWindowTimeType EventWindowTime;

  /* Session which roe is started */
  Dcm_SesCtrlType ucSessionActive;

} Dcm_RoeRequestInfo;

typedef struct STagDcm_RoeNonVolatileInfo
{
  uint16 NVEventTypeRecord;

  Dcm_RoeEventWindowTimeType NVEventWindowTime;

  Dcm_RoeStatusType NVState;

  uint8 IsOnChangeOfDID;

  uint8 NVRoeEventId;

  //index of Dcm_GddRoeRequestInfo
  uint8 NVIndex;

  uint8 NVActiveSession;

} Dcm_RoeNonVolatileInfo;

typedef union STagDcm_RoeEventStoreType
{
  Dcm_RoeNonVolatileInfo Data;

  uint8 NVDataBuffer[sizeof(Dcm_RoeNonVolatileInfo)];

} Dcm_RoeEventStoreType;

#if (DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
typedef struct STagDcm_DslRoeTrans
{
  /* TxPduId for Roe transmission if ROE Transmission Type is TYPE1 */
  PduIdType ddRoeTxPduId;

  /* Handle Id to be used by the Lower Layer to confirm the transmission */
  uint16 usRoeTxConfirmPduId;

  /* Buffer used for the transmission of ROE event messages */
  uint8 ucRoeRxBufferId;

  /* Buffer used for the transmission of ROE event messages */
  uint8 ucRoeTxBufferId;

} Dcm_DslRoeTrans;

typedef P2CONST(Dcm_DslRoeTrans, AUTOMATIC, DCM_APPL_CONST) 
  Dcm_DslRoeTransConstPtrType;
#endif
#endif

/*******************************************************************************
** Structure declarations of Authentication Service                           **
*******************************************************************************/
#if (DCM_AUTHENTICATION_SERVICE == STD_ON)

typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_SchMSwitchAuthenticationStateFunType)(
  uint8 AuthenticationState);

typedef struct STagDcm_AuthenticationConfigType
{
  Dcm_AuthenticationRoleType DeauthenticatedRole;

  #if (DCM_AUTHENTICATION_GENERAL_NRC_MODE_RULE == STD_ON)
  Dcm_NegativeResponseCodeType GeneralNrc;
  uint8 GeneralNrcModeRuleIndex;
  #endif

  #if (DCM_AUTHENTICATION_PERSIST_STATE_MODE_RULE == STD_ON)
  uint8 PersistStateModeRuleIndex;
  NvM_BlockIdType PersistStateNvMBlockId;
  #endif
} Dcm_AuthenticationConfigType;

#if (DCM_STANDARD_SUPPORT == DCM_ES95486_02_SUPPORT)

typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_AuthenticationUniDirectionalFunType)(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) CertificateData,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ChallengeServerData,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrCode);

typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_AuthenticationProofOfOwnerShipClientFunType)(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) ProofOfOwnerShipClientData,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);

typedef uint8 Dcm_AuthenticationWLSidType[DCM_AUTHENTICATION_WHITE_LIST_SERVICES_MAX_SIZE];

#if (DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON)
typedef uint8 Dcm_AuthenticationWLDidType[DCM_AUTHENTICATION_WHITE_LIST_DID_MAX_SIZE];
#endif

#if (DCM_DSP_AUTHENTICATION_WHITE_LIST_RID_CONFIGURED == STD_ON)
typedef uint8 Dcm_AuthenticationWLRidType[DCM_AUTHENTICATION_WHITE_LIST_RID_MAX_SIZE];
#endif

#if (DCM_DSP_AUTHENTICATION_WHITE_LIST_MEMORY_SELECTION_CONFIGURED == STD_ON)
typedef uint8 Dcm_AuthenticationWLMemorySelectionType[DCM_AUTHENTICATION_WHITE_LIST_MEMORY_SELECTION_MAX_SIZE];
#endif

typedef struct STagDcm_AuthenticationConnectionESConfigType
{
  /* Callout function to infom Dcm change authentication state */
  Dcm_SchMSwitchAuthenticationStateFunType pSchMSwitchAuthenticationStateFun;

  /* Callout function to processing subfunction UniDirectional */
  Dcm_AuthenticationUniDirectionalFunType pUniDirectionalFun;

  /* Callout function to processing subfunction ProofOfOwnerShipClient */
  Dcm_AuthenticationProofOfOwnerShipClientFunType pProofOfOwnerShipClientFun;

  /*Dcm role in Authenticated state */
  Dcm_AuthenticationRoleType AuthenticatedRole;

  /* white list services data (SID has subfunction) */
  Dcm_AuthenticationWLSidType pWLSidWithSubfunction;

  /* white list services data (SID has no subfunction) */
  Dcm_AuthenticationWLSidType pWLSidsWithoutSubfunction;

  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON)
  Dcm_AuthenticationWLDidType pWLDid;
  #endif

  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_MEMORY_SELECTION_CONFIGURED == STD_ON)
  Dcm_AuthenticationWLMemorySelectionType pWLMemorySelection;
  #endif

  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_RID_CONFIGURED == STD_ON)
  Dcm_AuthenticationWLRidType pWLRid;
  #endif

  /* Size of Certificate Client data */
  uint32 ulCertificateClientSize;

  /* Size of Challenge Server data */
  uint32 ulChallengeServerSize;

  /* Size of ProofOfOwnerShip Client data */
  uint32 ulProofOfOwnerShipClientSize;

  /*Connection Id*/
  uint16 usConnectionId;

  /* Size of white list services data (SID has subfunction) */
  uint8 ucWLSidWithSubfuncSize;

  /* Size of white list services data (SID has no subfunction) */
  uint8 ucWLSidWithoutSubfuncSize;

  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON)
  uint8 ucWLDidSize;
  #endif

  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_MEMORY_SELECTION_CONFIGURED == STD_ON)
  uint8 ucWLMemorySelectionSize;
  #endif

  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_RID_CONFIGURED == STD_ON)
  uint8 ucWLRidSize;
  #endif

  P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, pAsyncSettingAccessRightsFailedFun)(
  P2VAR(Dcm_CertAuthorizationInfoType, AUTOMATIC, DCM_APPL_DATA) authorization,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) Error);

  P2FUNC(Std_ReturnType, DCM_CALLOUT_CODE, pAsyncDeauthenticationFailedFun)(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) Error);

  uint8 ucAuthenticationUsePort;

} Dcm_AuthenticationConnectionESConfigType;

#elif (DCM_STANDARD_SUPPORT  == DCM_ISO14229_SUPPORT)
typedef struct STagDcm_AuthenticationElementType
{
  KeyM_CertElementIdType Id;

  Dcm_Uint8PtrType pData;

  Dcm_Uint32PtrType pDataLen;

  Dcm_Uint32PtrType pDataEleLen;

  uint32 DataMaxLen;
} Dcm_AuthenticationElementType;

typedef P2VAR(Dcm_AuthenticationElementType, AUTOMATIC, DCM_APPL_DATA)
  Dcm_AuthenticationElementPtrType;

typedef struct STagDcm_AuthenticationConnectionConfigType
{
  Dcm_SchMSwitchAuthenticationStateFunType pSchMSwitchAuthenticationStateFun;

  KeyM_CertificateIdType CertId;

  Dcm_AuthenticationElementPtrType pRole;
  Dcm_AuthenticationElementPtrType pWLServices;

  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON)
  Dcm_AuthenticationElementPtrType pWLDid;
  #endif

  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_MEMORY_SELECTION_CONFIGURED == STD_ON)
  Dcm_AuthenticationElementPtrType pWLMemorySelection;
  #endif

  #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_RID_CONFIGURED == STD_ON)
  Dcm_AuthenticationElementPtrType pWLRid;
  #endif

  uint32 RandomJobId;
  uint32 ProofofOwnerShipClientJobId;
  uint32 ClientChallengeSignJobId;
  uint32 ECUCertificateId;

  #if (DCM_AUTHENTICATION_TARGET_ID_MODE_RULE == STD_ON)
  uint8 TargetIdModeRuleIndex;
  KeyM_CertElementIdType CompareCertId;
  Dcm_Uint8ConstPtrType pCompareData;
  uint8 CompareDataLen;
  #endif

} Dcm_AuthenticationConnectionConfigType;

typedef P2CONST(Dcm_AuthenticationConnectionConfigType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_AuthenticationConnectionConfigConstPtrType;
#endif /* DCM_STANDARD_SUPPORT */
#endif /*(DCM_AUTHENTICATION_SERVICE == STD_ON)*/

/*******************************************************************************
** Structure declaration of OBD Service 01 and OBD Service 02                 **
*******************************************************************************/
#if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
typedef struct STagDcm_PIDPackSignal
{
  Dcm_DataType ucSignalType;

  uint8 ucSignalByteType;

  uint8 ucPackFuncIndex;

  boolean blByteConversion;

} Dcm_PIDPackSignal;
#endif

#if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON) || \
     (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON))
typedef struct STagDcmDspPidSupportInfo
{
  /* Length of the supported information in bytes */
  uint8 ucDcmDspPidSupportInfoLen;

  /* Position of the supported information in bytes */
  uint8 ucDcmDspPidSupportInfoPos;

} DcmDspPidSupportInfo;

typedef struct STagDcmDspPidDataConfigType
{
  #if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
  Dcm_ReadDataSyncFunType pReadPidDataFun;

  P2CONST(Dcm_PIDPackSignal, AUTOMATIC, DCM_APPL_CONST) pDcmDspPidPackSigRef;
  #endif

  P2CONST(DcmDspPidSupportInfo,AUTOMATIC, DCM_APPL_CONST) pDcmDspPidDataSupportInfoRef;

  #if ((DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON) || \
       (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON))
  /* Data Element Index of PID */
  uint8 ucPIDDataElementIndex;
  #endif

  /* Length of data associated to the PID in byte */
  uint8 ucDcmDspPidDataByteSize;

  /* This is the position in byte of the PID structure and will not start at
   * position 0 in case a support information is available */
  uint8 ucDcmDspPidByteOffset;

  /* Referenced Bit of the SupportInfo */
  uint8 ucDcmDspPidDataSupportInfoBit;

  #if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
  Dcm_DataUsePortType ucDcmDspPidDataUsePort;
  Dcm_DataType ucDcmPIDDataType;

  #if ((DCM_PID_DATA_SENDER_RECEIVER == STD_ON) || \
    (DCM_PID_DATA_SENDER_RECEIVER_AS_SERVICE == STD_ON))
  uint8 ucReadFunctionIndex;
  Dcm_EndianType PidDataEndian;
  #endif
  #endif

} Dcm_DspPidData;
#endif

#if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
     (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON) || \
     (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON))
typedef struct STagDcm_PIDConfigType
{
  /* Pointer to the DcmDspPid  for a Signal in the PID */
  P2CONST(Dcm_DspPidData, AUTOMATIC, DCM_APPL_CONST) pDcmDspPidData;

  /* 1 bytes Identifier of the PID */
  uint8 ucDcmDspPidIdentifier;

  /* Length of the PID in byte. */
  uint8 ucPidBufferSize;

  /* ucPidService */
  Dcm_PidServiceType ucPidService;

  /* No of PID Data */
  uint8 ucNumofPIDData;

  /*  No of PID SupportInfo */
  uint8 ucNumofPIDSupportInfo;

  /* Allow to activate or deactivate the usage of a PID */
  boolean blPIDUse;

} Dcm_PIDConfigType;
#endif

#if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
#if (DCM_DSP_PID_BOOLEAN == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_PIDDataBoolReadFunType)(
  P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA) Data);

typedef struct STagDcm_PIDDataReadBooleanFun
{
  Dcm_PIDDataBoolReadFunType pReadPidDataBoolFun;

} Dcm_PIDBooleanFunc;
#endif

#if (DCM_DSP_PID_UINT8 == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_PIDDataUint8ReadFunType)(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);

typedef struct STagDcm_PIDDataReadUint8Fun
{
  Dcm_PIDDataUint8ReadFunType pReadPidDataUint8Fun;

} Dcm_PIDUint8Func;
#endif

#if (DCM_DSP_PID_UINT8_N == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_PIDDataUint8NReadFunType)(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Data);

typedef struct STagDcm_PIDDataReadUint8NFun
{
  Dcm_PIDDataUint8NReadFunType pReadPidDataUint8NFun;

} Dcm_PIDUint8NFunc;
#endif

#if (DCM_DSP_PID_SINT8 == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_PIDDataSint8ReadFunType)(
  P2VAR(sint8, AUTOMATIC, DCM_APPL_DATA) Data);

typedef struct STagDcm_PIDDataReadSint8Fun
{
  Dcm_PIDDataSint8ReadFunType pReadPidDataSint8Fun;

} Dcm_PIDSint8Func;
#endif

#if (DCM_DSP_PID_SINT8_N == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_PIDDataSint8NReadFunType)(
  P2VAR(sint8, AUTOMATIC, DCM_APPL_DATA) Data);

typedef struct STagDcm_PIDDataReadSint8NFun
{
  Dcm_PIDDataSint8NReadFunType pReadPidDataSint8NFun;

} Dcm_PIDSint8NFunc;
#endif

#if (DCM_DSP_PID_UINT16 == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_PIDDataUint16ReadFunType)(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) Data);

typedef struct STagDcm_PIDDataReadUint16Fun
{
  Dcm_PIDDataUint16ReadFunType pReadPidDataUint16Fun;

} Dcm_PIDUint16Func;
#endif

#if (DCM_DSP_PID_UINT16_N == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_PIDDataUint16NReadFunType)(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) Data);

typedef struct STagDcm_PIDDataReadUint16NFun
{
  Dcm_PIDDataUint16NReadFunType pReadPidDataUint16NFun;

} Dcm_PIDUint16NFunc;
#endif

#if (DCM_DSP_PID_SINT16 == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_PIDDataSint16ReadFunType)(
  P2VAR(sint16, AUTOMATIC, DCM_APPL_DATA) Data);

typedef struct STagDcm_PIDDataReadSint16Fun
{
  Dcm_PIDDataSint16ReadFunType pReadPidDataSint16Fun;

} Dcm_PIDSint16Func;
#endif

#if (DCM_DSP_PID_SINT16_N == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_PIDDataSint16NReadFunType)(
  P2VAR(sint16, AUTOMATIC, DCM_APPL_DATA) Data);

typedef struct STagDcm_PIDDataReadSint16NFun
{
  Dcm_PIDDataSint16NReadFunType pReadPidDataSint16NFun;

} Dcm_PIDSint16NFunc;
#endif

#if (DCM_DSP_PID_UINT32 == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_PIDDataUint32ReadFunType)(
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) Data);

typedef struct STagDcm_PIDDataReadUint32Fun
{
  Dcm_PIDDataUint32ReadFunType pReadPidDataUint32Fun;

} Dcm_PIDUint32Func;
#endif

#if (DCM_DSP_PID_UINT32_N == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_PIDDataUint32NReadFunType)(
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) Data);

typedef struct STagDcm_PIDDataReadUint32NFun
{
  Dcm_PIDDataUint32NReadFunType pReadPidDataUint32NFun;

} Dcm_PIDUint32NFunc;
#endif

#if (DCM_DSP_PID_SINT32 == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_PIDDataSint32ReadFunType)(
  P2VAR(sint32, AUTOMATIC, DCM_APPL_DATA) Data);

typedef struct STagDcm_PIDDataReadSint32Fun
{
  Dcm_PIDDataSint32ReadFunType pReadPidDataSint32Fun;

} Dcm_PIDSint32Func;
#endif

#if (DCM_DSP_PID_SINT32_N == STD_ON)
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_PIDDataSint32NReadFunType)(
  P2VAR(sint32, AUTOMATIC, DCM_APPL_DATA) Data);

typedef struct STagDcm_PIDDataReadSint32NFun
{
  Dcm_PIDDataSint32NReadFunType pReadPidDataSint32NFun;

} Dcm_PIDSint32NFunc;
#endif
#endif

/*******************************************************************************
** Structure declaration of OBD MID Service                                   **
*******************************************************************************/
#if (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON)
typedef struct STagDcm_OBDMidTids
{
  /* Function name for request to application to get DTR value */
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pGetDTRValueFnc)(
    Dcm_OpStatusType OpStatus,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) TestValue,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) MinLimit,
    P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) MaxLimit,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) Status);

  /* Test Id for Service 06 */
  uint8 ucTestResultTestId;

  /* Contains the OBDMID and the assigned TIDs for Service 06 */
  uint8 ucTestResultUaSid;

} Dcm_OBDMidTids;

typedef struct STagDcm_OBDMidConfigType
{
  /* To hold Tid, Uasid */
  P2CONST(Dcm_OBDMidTids, AUTOMATIC, DCM_APPL_CONST) pDcmObdMidTids;

  /* Contains the OBDMID and the assigned TIDs for Service 06 */
  uint8 ucTestResultObdmid;

  uint8 ucNoOfTids;

} Dcm_OBDMidConfigType;
#endif

/*******************************************************************************
** Structure declaration of Request Control service                           **
*******************************************************************************/
#if (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON)
typedef struct STagDcm_RequestControlConfigType
{
  Dcm_RequestControlFunType pReqControlFnc;

  uint8 ucRequestControlInBufferSize;

  uint8 ucRequestControlOutBufferSize;

  uint8 ucRequestControlTestId;

} Dcm_RequestControlConfigType;
#endif

/*******************************************************************************
** Structure declaration of Vehicle Info Service                              **
*******************************************************************************/
#if (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
typedef struct STagDcm_VehInfoDataConfigType
{
  Dcm_GetInfoTypeValueDataFunType pGetVehInfoDataReadFun;

  uint8 ucVehInfoDataOrder;

  uint8 ucVehInfoBufSize;

  boolean blVehInfoUsePort;

} Dcm_VehInfoData;

typedef struct STagDcm_VehInfoConfigType
{
  P2CONST(Dcm_VehInfoData, AUTOMATIC, DCM_APPL_CONST) pDcmVehInfoData;

  uint8 ucVehInfoTypeId;

  uint8 ucNoOfVehInfoData;

  boolean blVehInfoNODIProvResp;

} Dcm_VehInfoConfigType;
#endif

/*******************************************************************************
** Structure declarations of Availability OBD ID                              **
*******************************************************************************/
typedef struct STagDcm_IDEncodeByteConfig
{
  /*EncodedByteA Information */
  uint8 ucEncodeByteA;

  /*EncodedByteB Information */
  uint8 ucEncodeByteB;

  /*EncodedByteC Information */
  uint8 ucEncodeByteC;

  /*EncodedByteD Information */
  uint8 ucEncodeByteD;

} Dcm_IDEncodeByteConfig;

/*******************************************************************************
** Structure declarations of Dsd layer                                        **
*******************************************************************************/
typedef struct STagDcm_SubServiceIdConfigType
{
  /* Pointer to array of sessions supporting the Sub service Id */
  Dcm_Uint8ConstPtrType pSubSerSession;

  /* Pointer to array of security levels supporting the Sub service Id */
  Dcm_Uint8ConstPtrType pSubSerSecurity;

  Dcm_DiagnosticServiceFunType pSubServiceFnc;

  #if (DCM_MODE_RULE == STD_ON)
   /*variable to hold the index of moderuleArrayindex */
  Dcm_ModeType ucsubmoderuleArrayindex;
  #endif

  #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
  Dcm_AuthenticationRoleType SubServiceRole;
  #endif

  /* Number of sessions */
  uint8 ucSubSerSessionCount;

  /* Number of security levels */
  uint8 ucSubSerSecurityCount;

  /* Id of the SubService identifier in hex. The possible Service identifier
     are predefined in the ISO 14229-1 and ISO 15031-5 */
  uint8 ucSubServiceId;
  
  #if (DCM_READDTC_SUPPORT == STD_ON)
  /* Subfunction Length */
  uint8 ucSubFuncLength;
  #endif

  boolean SubServiceUsed;

  #if (DCM_MODE_RULE == STD_ON)
  /* variable to hold the index of moderuleArrayindex */
  boolean blModeRuleConfigured;
  #endif

} Dcm_SubServiceIdConfigType;

typedef P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_SubServiceIdConfigConstPtrType;

typedef struct STagDcm_ServiceIdConfigType
{
  /* Pointer to array of sessions supporting the requested service Id */
  Dcm_Uint8ConstPtrType pSession;

  /* Pointer to array of security levels supporting the requested service Id */
  Dcm_Uint8ConstPtrType pSecurity;

  Dcm_DiagnosticServiceFunType pDiagnosticService;

  /* Reference to the Sub Service table configured for this Service ID */
  Dcm_SubServiceIdConfigConstPtrType pSubServiceId;

  #if (DCM_MODE_RULE == STD_ON)
  /* index for seviceModeruleindexarray at service level */
  Dcm_ModeType ucseviceModeruleindexarray;
  #endif

  #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
  Dcm_AuthenticationRoleType ServiceRole;
  #endif

  /* Number of sessions */
  uint8 ucSessionCount;

  /* Number of security levels */
  uint8 ucSecurityCount;

  /* Number of Sub Service configured for this ServiceID */
  uint8 ucSubServiceCount;

  /* Service Id */
  uint8 ucServiceId;
  
  /* Minimum Length of request to validate */
  uint8 ucMinReqLength;

  boolean ServiceUsed;

  /* Sub function availability */
  boolean blSubFunctionAvailable;

  #if (DCM_MODE_RULE == STD_ON)
  /* index for seviceModeruleindexarray at service level */
  boolean blModeRuleConfigured;
  #endif

} Dcm_ServiceIdConfigType;

typedef P2CONST(Dcm_ServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST)
  Dcm_ServiceIdConfigConstPtrType;

/*******************************************************************************
** Structure declarations of Dsl layer                                        **
*******************************************************************************/
typedef struct STagDcm_PduIdTable
{
  /* Status of the ongoing RxPduId */
  Dcm_Uint8PtrType pPduIdStatus;

  #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  /* Pointer to periodic Tx pdu reference */
  Dcm_PeriodicTxPduPtrType pPerTxPdu;
  #endif

  #if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) \
       && (DCM_PROTOCOL_TRANSTYPE2 == STD_ON))
  Dcm_DslRoeTransConstPtrType pRoeTxId;
  #endif

  #if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) \
       || (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))
  /* Function to perform mode switch for the corresponding network */
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pSchMSwitchCommModeFunc)
    (Dcm_CommunicationModeType CommunicationType);
  #endif

  /* Referred TxPduId configured for a particular RxPduId */
  PduIdType ddTxPduId;

  Dcm_ProtocolType ProtocolType;

  uint32 ulRxCopiedLength;

  /* Handle Id to be used by the Lower Layer to confirm the transmission
     of the DcmDsProtocolTxPdu to the LowerLayer */
  uint16 usTxConfirmationPduId;

  /* Tester source address configured per protocol and provided
     for the jump to Bootloader */
  uint16 ConfigTesterAddress;

  #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
  uint16 usMainConnectionId;
  #endif

  #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  /* Index in Rx buffer using to simulate UDS 0x22 request */
  uint8 ucPerRxBufferId;
  #endif

  /* Rx address type */
  Dcm_ProtocolRxAddrType ucRxAddrType;

  /* Mask required for updating the status of RxPduId */
  uint16 usPduIdStatusMask;

  /* Buffer Id for message transmission */
  uint8 ucTxBufferId;

  /* Buffer Id for message reception */
  uint8 ucRxBufferId;

  #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
  /* Number of periodic Tx connection reference */
  uint8 ucNumPerTxPdu;
  #endif

  uint8 ComMChannelId;

  uint8 ucReceiveStatus;

  uint16 RxConnectionId;

  Dcm_PduRefType PduRef;

  uint16 SourceTesterAddress;

} Dcm_PduIdTable;

typedef P2VAR(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_DATA) 
  Dcm_PduIdTablePtrType;

typedef struct STagDcm_ProtocolConfig
{
  /* Status of the ongoing Protocol */
  Dcm_Uint8PtrType pProtocolStatus;

  boolean ProtocolUsed;

  /* Pointer to table of service identifiers */
  /* @Trace: SWS_Dcm_00035 */
  Dcm_ServiceIdConfigConstPtrType pServiceIdTable;

  #if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* Defines the maximum length of the response in case that use paged-buffer */
  uint16 usProtocolMaxResSize;
  #endif

  /* This parameter is used to guarantee that the DCM response is available on
  * the bus before reaching P2
  */
  uint16 usTimStrP2ServerAdjust;

  /* This parameter is used to guarantee that the DCM response is available on
  * the bus before reaching P2*
  */
  uint16 usTimStrP2StarServerAdjust;

  /* Protocol priority */
  uint8 ucProtocolPrio;

  /* Mask required for updating the status of Protocol */
  uint8 ucPrtclStatusMask;

  uint8 ucServiceCount;

  Dcm_ProtocolTransType ProtocolTransType;

  boolean IsSendRespPendOnRestart;

  uint8 DemClientId;

  uint16 EcuAddress;

} Dcm_ProtocolConfig;

typedef P2CONST(Dcm_ProtocolConfig, AUTOMATIC, DCM_APPL_CONST) 
  Dcm_ProtocolConfigConstPtrType;

typedef struct STagDcm_BufferConfig
{
  /* Pointer to RAM buffer area for the configured buffer Id */
  Dcm_MsgType pBufferArea;

  /* Size of the Buffer */
  Dcm_MsgLenType ulBufferSize;

} Dcm_BufferConfig;

typedef P2CONST(Dcm_BufferConfig, AUTOMATIC, DCM_APPL_CONST)
  Dcm_BufferConfigConstPtrType;

typedef struct STagDcm_CbkReqServicesConfigType
{
  Dcm_StartProtocolFunType pStartProtocolFun;

  Dcm_StopProtocolFunType pStopProtocolFun;

} Dcm_CbkReqServicesConfigType;

typedef struct STagDcm_SerReqManuIndConfigType
{
  Dcm_IndicationFunType pManuIndicationFun;

  Dcm_ConfirmationFunType pManuConfirmationFun;

} Dcm_SerReqManuIndConfigType;

typedef struct STagDcm_SerReqSuppIndConfigType
{
  Dcm_IndicationFunType pSuppIndicationFun;

  Dcm_ConfirmationFunType pSuppConfirmationFun;

} Dcm_SerReqSuppIndConfigType;

/*******************************************************************************
** Structure declaration for CallBackDCMRequestServices                       **
*******************************************************************************/

typedef struct STagDcm_CbkPresentDateConfigType
{
  /* Function name to get present date from application */
  P2FUNC(Std_ReturnType, DCM_APPL_CODE, pGetPresentDateFun)
    (P2VAR(uint8, AUTOMATIC, DCM_APPL_CODE) Data);

}Dcm_CbkPresentDateConfigType;

/*******************************************************************************
** Structure related to Endianness Conversion                                 **
*******************************************************************************/
#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /*  WORD Type Index */
  #define DCM_WORD_MS_BYTE_IDX        0U
  #define DCM_WORD_LS_BYTE_IDX        1U

  /*  DWORD Type Index */
  #define DCM_DWORD_MS_BYTE_IDX       0U
  #define DCM_DWORD_MS_MID_BYTE_IDX   1U
  #define DCM_DWORD_LS_MID_BYTE_IDX   2U
  #define DCM_DWORD_LS_BYTE_IDX       3U
#else
  /*  WORD Type Index */
  #define DCM_WORD_MS_BYTE_IDX        1U
  #define DCM_WORD_LS_BYTE_IDX        0U

  /*  DWORD Type Index */
  #define DCM_DWORD_LS_BYTE_IDX       0U
  #define DCM_DWORD_LS_MID_BYTE_IDX   1U
  #define DCM_DWORD_MS_MID_BYTE_IDX   2U
  #define DCM_DWORD_MS_BYTE_IDX       3U
#endif

#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
typedef union
{
  struct                                     /* Defining byte fields */
  {
    uint8 ucLsByte;                          /* Least significant byte */
    uint8 ucMsByte;                          /* Most significant byte */
  } ddByte;

  uint16 usWordReg16;                        /* 16 bit CRC field */

} Tun_DcmWord16;

#else

typedef union
{
  struct
  {
    uint8 ucMsByte;                          /* Most significant byte */
    uint8 ucLsByte;                          /* Least significant byte */
  } ddByte;

  uint16 usWordReg16;                        /* 16 bit field */

} Tun_DcmWord16;

#endif

#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
typedef union                                /* Little Endian Ordering */
{
  struct
  {
    uint8 ucLsByte;                           /* Least Significant byte (0) */
    uint8 ucMidLowByte;                       /* Byte (1) */
    uint8 ucMidHiByte;                        /* Byte (2) */
    uint8 ucMsByte;                           /* Most Significant byte (3) */
  } ddByte;

  uint32 ulLongReg32;

} Tun_DcmDword32;

#else

typedef union                                /* Big Endian Ordering */
{
  struct
  {
    uint8 ucMsByte;                          /* Most Significant byte (3) */
    uint8 ucMidHiByte;                       /* Byte (2) */
    uint8 ucMidLowByte;                      /* Byte (1) */
    uint8 ucLsByte;                          /* Least Significant byte (0) */
  } ddByte;

  uint32 ulLongReg32;

} Tun_DcmDword32;

#endif

/* Union for 16 bit CPU byte order */
typedef union
{
  struct
  {
    uint8 BO_Byte[DCM_TWO];
  } byte_val;

  uint16 whole_word;

} Dcm_MIWord_Access;

/* Union for 32 bit CPU byte order */
typedef union
{
  struct
  {
    uint8 BO_Byte[DCM_FOUR];
  } byte_val;

  uint32 whole_dword;

} Dcm_MIdWord_Access;

/*******************************************************************************
** Internal Structure declarations of module                                  **
*******************************************************************************/
typedef struct STagDcm_RequestContextType
{
  Dcm_MsgContextPtrType rct_MsgContext;

  Dcm_ServiceIdConfigConstPtrType rct_ServiceCfg;

  PduIdType rct_RxPduId;

  Std_ReturnType rct_RequestResult;

  uint8 rct_SubFunctionId;

} Dcm_RequestContextType;

typedef P2VAR(Dcm_RequestContextType, AUTOMATIC, DCM_APPL_DATA) 
  Dcm_RequestContextPtrType;

typedef struct STagDcm_DspServiceProcessingStsType
{
  uint8 ucRoeStoreRequest;

  uint8 ucReadScalingDataPending;

  uint8 ucSecSeedReqPending;

  uint8 ucSecCompareKeyReqPending;

  uint8 ucSecSeedReq;

} Dcm_DspServiceProcessingStsType;

typedef struct STagDcm_TxRespStatusType
{
  uint8 ucNormResponse;

  uint8 ucNegResp;

  uint8 ucRespFailed;

  uint8 ucRespPending;

  uint8 ucFirstPageTrans;

  uint8 ucPagedTrans;

  uint8 ucFailedInd;

  uint8 ucDslPagedTrans;

  uint8 ucNeedFailedConfiramtion;

} Dcm_TxRespStatusType;

typedef struct STagDcm_PrtclTxBufStatusType
{
  uint8 ucCopyTxRejected;

  uint8 ucReportOBDDtc;

  uint8 ucPeriodicIdStatus;

  uint8 ReportNumOfDtc;

  uint8 ucBufferProvided;

  uint8 ucProtclStatus;

  uint8 ucClearDTCStatus;

  uint8 ucOBDClearDTCStatus;

  uint8 ucNumFilterDTCStatus;

} Dcm_PrtclTxBufStatusType;

typedef struct STagDcm_DspSerPgStatusType
{
  uint8 ucMultipleRecd;

  uint8 ucPagingInMid;

  uint8 ucFirstPage;

  uint8 ucPagingStarted;

  uint8 ucUpdatePageStarted;

  uint8 ucLastPage;

  uint8 ucDemDisableInvoked;

} Dcm_DspSerPgStatusType;

typedef struct STagDcm_ServicePendingStatusType
{
  uint8 ucIoCtrlReadCdtChkPendingStatus;

  uint8 ucReadPerDidPendingStatus;

  uint8 ucWriteDataByIdPendingStatus;

  uint8 ucReadDataPendingStatus;

  uint8 ucCheckReadPendingStatus;

  uint8 ucIocontrolPendingStatus;

} Dcm_ServicePendingStatusType;

typedef struct STagDcm_ServiceForcePendingStatusType
{
  uint8 ucForcePendingStatus;

  uint8 ucWriteMemForcePendingStatus;

  uint8 ucReadMemForcePendingStatus;

} Dcm_ServiceForcePendingStatusType;

typedef struct STagDcm_MemServicePendingStatusType
{
  uint8 ucStartProtocolFailed;

  uint8 ucIoCtrlReadDataPendingStatus;

  uint8 ucWriteMemPendingStatus;

  uint8 ucReadMemPendingStatus;

} Dcm_MemServicePendingStatusType;

/*******************************************************************************
** Data of Dsl layer                                                          **
*******************************************************************************/
#if (DCM_NUM_OF_PDUIDTABLECONFIG != DCM_ZERO)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Dcm_PduIdTable, DCM_VAR) Dcm_GaaPduIdTableConfig[
  DCM_NUM_OF_PDUIDTABLECONFIG];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_PROTOCOLCONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaProtocolIds[
  DCM_NUM_OF_PROTOCOLCONFIG];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_ProtocolConfig, DCM_CONST) Dcm_GaaProtocolConfig[
  DCM_NUM_OF_PROTOCOLCONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, DCM_VAR) Dcm_GaaRxStatus[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, DCM_VAR) Dcm_GaaProtclStatus[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, DCM_VAR) Dcm_GaaBufferArea[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#if (DCM_NUM_OF_BUFFER_CONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_BufferConfig, DCM_CONST) Dcm_GaaBufferConfig[
  DCM_NUM_OF_BUFFER_CONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_TOTAL_NUM_OF_CALLBACK_REQUEST != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_CbkReqServicesConfigType, DCM_CONST) Dcm_GaaCbkReqServices[
  DCM_TOTAL_NUM_OF_CALLBACK_REQUEST];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUMBER_OF_REQUEST_MANUFACTURER_INDICATION != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_SerReqManuIndConfigType, DCM_CONST) Dcm_GaaManuIndConfigType[
  DCM_NUMBER_OF_REQUEST_MANUFACTURER_INDICATION];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUMBER_OF_REQUEST_SUPPLIER_INDICATION != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_SerReqSuppIndConfigType, DCM_CONST) Dcm_GaaSuppIndConfigType[
  DCM_NUMBER_OF_REQUEST_SUPPLIER_INDICATION];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
** Data of Dsd layer                                                          **
*******************************************************************************/
#if (DCM_NUM_OF_SUBSERVICEIDCONFIG != DCM_ZERO )
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_SubServiceIdConfigType, DCM_CONST) Dcm_GaaSubServiceIdConfig[
  DCM_NUM_OF_SUBSERVICEIDCONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_SIDCONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_ServiceIdConfigType, DCM_CONST) Dcm_GaaSIdConfig[
  DCM_NUM_OF_SIDCONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_GAASESSIONSTOSID != DCM_ZERO)
#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaSessionsToSId[
  DCM_NUM_OF_GAASESSIONSTOSID];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_SECURITYLEVELSTOSID != DCM_ZERO)
#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaSecuritylevelsToSId[
  DCM_NUM_OF_SECURITYLEVELSTOSID];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

/*******************************************************************************
** Data of Mode Condition                                                     **
*******************************************************************************/
#if (DCM_MODE_CONDITION == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_ModeConditionConfigType, DCM_CONST) Dcm_GaaModeConditionConfig[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaModeConditionIndexArray[];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"

#define DCM_START_SEC_CONST_32
#include "MemMap.h"
extern CONST(uint32, DCM_CONST) Dcm_GaaSwcDataElementArrayElement[];
#define DCM_STOP_SEC_CONST_32
#include "MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
// minimum size is 4, maximum is number of DcmSwcDataElementArrayElement * 4
extern VAR(uint8, DCM_VAR) Dcm_GaaModeConditionSwcData[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#endif

#if (DCM_MODE_RULE == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_ModeRuleConfigType, DCM_CONST) Dcm_GaaModeRuleConfig[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaModeRuleIndexArray[];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

/*******************************************************************************
** Data of Pack UnPack Signal                                                 **
*******************************************************************************/
#if (DCM_NUM_OF_PACK_FUNC_CONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PackFuncType, DCM_CONST) Dcm_GaaPackFunc[
  DCM_NUM_OF_PACK_FUNC_CONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_UNPACK_FUNC_CONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_UnPackFuncType, DCM_CONST) Dcm_GaaUnPackFunc[
  DCM_NUM_OF_UNPACK_FUNC_CONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
** Data of diagnostic session service                                         **
*******************************************************************************/
#if (DCM_NUM_OF_DIAGSESSIONCONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DiagSessionConfigType, DCM_CONST) Dcm_GaaDiagSessionConfig[
  DCM_NUM_OF_DIAGSESSIONCONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
** Data of Ecu Reset Service                                                  **
*******************************************************************************/
#if(DCM_ECURESET_SERVICE == STD_ON)
#if (DCM_NUM_OF_ECURESETCONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_EcuResetConfigType, DCM_CONST) Dcm_GaaEcuResetConfig[
  DCM_NUM_OF_ECURESETCONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Data of Clear DTC Service                                                  **
*******************************************************************************/
#if ((DCM_DSP_CLR_DIAG_SERVICE == STD_ON) \
      && (DCM_DSP_CLEARDTC_CONFIGURED == STD_ON))
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DspClearDTCConfig, DCM_CONST) Dcm_GaaClearDTCConfig[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
** Data of Read DTC Service                                                   **
*******************************************************************************/
#if ((DCM_READDTC_SUPPORT == STD_ON) && \
  (DCM_AUTHENTICATION_SERVICE == STD_ON) && \
  (DCM_NUM_OF_USER_DEFINED_FAULT_MEMORY != DCM_ZERO))
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DspReadDTCInfoConfigType, DCM_CONST)Dcm_GaaDspReadDTCInfo[
  DCM_NUM_OF_USER_DEFINED_FAULT_MEMORY];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
** Data of Security Access Service                                            **
*******************************************************************************/
#if (DCM_NUM_OF_SECURITYLEVELCONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_SecurityLevConfigType, DCM_CONST) Dcm_GaaSecurityLevConfig[
  DCM_NUM_OF_SECURITYLEVELCONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_CRYPTO_R44_USED == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_SecureAccessCryptoConfigType, DCM_CONST) Dcm_GaaSecureAccessCryptoConnectionConfig[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array of CallBackPresentDate*/
extern CONST(Dcm_CbkPresentDateConfigType, DCM_CONST)
  Dcm_GaaCbkPresentDate;
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
** Data of Communication Control Service                                      **
*******************************************************************************/
#if ((DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON) \
     || (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON))
#if (DCM_TOTAL_NUM_OF_SPECIFIC_CHANNEL != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_CommControlConfigType, DCM_CONST) Dcm_GaaCommControlConfig[
  DCM_TOTAL_NUM_OF_SPECIFIC_CHANNEL];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_TOTAL_NUM_OF_ALL_CHANNEL != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_AllCommControlConfig, DCM_CONST) Dcm_GaaAllCommControlConfig[
  DCM_TOTAL_NUM_OF_ALL_CHANNEL];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_TOTAL_NUM_OF_SUBNODE != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_CommControlSubNodeConfigType, DCM_CONST) 
  Dcm_GaaCommControlSubNodeConfig[DCM_TOTAL_NUM_OF_SUBNODE];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Data of Read Memory By Address Service                                     **
*******************************************************************************/
#if ((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON) \
     || (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
#if (DCM_TOTAL_NUM_READ_MEMORY_CONFIGURED != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_ReadMemRngInfoConfigType, DCM_CONST) Dcm_GaaReadMemRngConfig[
  DCM_TOTAL_NUM_READ_MEMORY_CONFIGURED];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if ((DCM_READ_MEMORY_BY_ADDRESS_SERVICE == STD_ON)  || \
     (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON) || \
     (DCM_REQUEST_UPLOAD_SERVICE == STD_ON)          || \
     (DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON)        || \
     (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
#if (DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaAddressAndLengthFormatIds[
  DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Data of Write Memory By Address Service                                    **
*******************************************************************************/
#if (DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE == STD_ON)
#if (DCM_TOTAL_NUM_WRITE_MEMORY_CONFIGURED != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_WriteMemRngInfoConfigType, DCM_CONST) Dcm_GaaWriteMemRngConfig[
  DCM_TOTAL_NUM_WRITE_MEMORY_CONFIGURED];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Data of Did Services                                                       **
*******************************************************************************/
#if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)

#if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
#if (DCM_NUM_OF_GAADIDINFOTYPEDIDWRITECONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDInfoTypeDidWrite, DCM_CONST)
  Dcm_GaaDIDInfoTypeDidWriteConfig[DCM_NUM_OF_GAADIDINFOTYPEDIDWRITECONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) \
     || (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON) \
     || (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON) \
     || (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
#if (DCM_NUM_OF_GAADIDINFOTYPEDIDREADCONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDInfoTypeDidRead, DCM_CONST) Dcm_GaaDIDInfoTypeDidReadConfig[
  DCM_NUM_OF_GAADIDINFOTYPEDIDREADCONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if(DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
#if (DCM_NUM_OF_GAADIDINFOTYPEDIDCTRLCONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDInfoTypeDidCtrl, DCM_CONST) Dcm_GaaDIDInfoTypeDidCtrlConfig[
  DCM_NUM_OF_GAADIDINFOTYPEDIDCTRLCONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if (DCM_NUM_OF_DCMDSPDIDRANGECONFIG != DCM_ZERO)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Dcm_DIDRangeConfig, DCM_VAR) Dcm_GaaDcmDspDIDRangeConfig[
  DCM_NUM_OF_DCMDSPDIDRANGECONFIG];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_GAADATAINFOTYPECONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DataInfoType, DCM_CONST) Dcm_GaaDataInfoTypeConfig[
  DCM_NUM_OF_GAADATAINFOTYPECONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_GAADCMDSPDATACONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DcmDspDataconfig, DCM_CONST) Dcm_GaaDcmDspDataConfig[
  DCM_NUM_OF_GAADCMDSPDATACONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_GAADCMDSPSIGNALCONFIG != DCM_ZERO)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Dcm_DidSignalConfigType, DCM_VAR) Dcm_GaaDcmDspSignalConfig[
  DCM_NUM_OF_GAADCMDSPSIGNALCONFIG];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_DIDPARACONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(uint16, DCM_CONST) Dcm_GaaDidId[
  DCM_NUM_OF_DIDPARACONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDParaConfig, DCM_CONST) Dcm_GaaDIDParaConfig[
  DCM_NUM_OF_DIDPARACONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_GAADIDINFOTYPECONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDInfoType, DCM_CONST) Dcm_GaaDIDInfoTypeConfig[
  DCM_NUM_OF_GAADIDINFOTYPECONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if ((DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, DCM_APPL_DATA) Dcm_GaaDIDSignalData[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#if (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, DCM_VAR) Dcm_GaaDIDSignalOutData[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif
#endif

#define DCM_START_SEC_CONST_16
#include "MemMap.h"
extern CONST(uint16, DCM_CONST) Dcm_GaaDidRefToDid[];
#define DCM_STOP_SEC_CONST_16
#include "MemMap.h"


#if(((DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)) && \
   (DCM_DATA_SENDER_RECEIVER == STD_ON) || \
   (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
#if(DCM_READ_WRITE_SEND_RECV_UINT8 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDSigReadWriteUint8Function, DCM_CONST) 
  Dcm_GaaSigReadWriteUint8Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(DCM_READ_WRITE_SEND_RECV_UINT16 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDSigReadWriteUint16Function, DCM_CONST)
  Dcm_GaaSigReadWriteUint16Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(DCM_READ_WRITE_SEND_RECV_UINT32 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDSigReadWriteUint32Function, DCM_CONST)
  Dcm_GaaSigReadWriteUint32Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(DCM_READ_WRITE_SEND_RECV_SINT8 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDSigReadWriteSint8Function, DCM_CONST)
  Dcm_GaaSigReadWriteSint8Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(DCM_READ_WRITE_SEND_RECV_SINT16 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDSigReadWriteSint16Function, DCM_CONST)
  Dcm_GaaSigReadWriteSint16Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(DCM_READ_WRITE_SEND_RECV_SINT32 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDSigReadWriteSint32Function, DCM_CONST)
  Dcm_GaaSigReadWriteSint32Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
    ((DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) && \
    (DCM_USE_ECU_SIGNAL_ENABLED == STD_ON)))

#if(DCM_DSP_USE_ECU_SIGNAL_UINT8 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDEcuSignalUint8Function, DCM_CONST)
  Dcm_GaaEcuSignalUint8Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(DCM_DSP_USE_ECU_SIGNAL_UINT16 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDEcuSignalUint16Function, DCM_CONST)
  Dcm_GaaEcuSignalUint16Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(DCM_DSP_USE_ECU_SIGNAL_UINT32 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDEcuSignalUint32Function, DCM_CONST)
  Dcm_GaaEcuSignalUint32Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(DCM_DSP_USE_ECU_SIGNAL_SINT8 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDEcuSignalSint8Function, DCM_CONST)
  Dcm_GaaEcuSignalSint8Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(DCM_DSP_USE_ECU_SIGNAL_SINT16 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDEcuSignalSint16Function, DCM_CONST)
  Dcm_GaaEcuSignalSint16Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(DCM_DSP_USE_ECU_SIGNAL_SINT32 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DIDEcuSignalSint32Function, DCM_CONST)
  Dcm_GaaEcuSignalSint32Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if (DCM_OBD_DID_SUPPORT_INFO == STD_ON)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DcmDspDidSupportInfo, DCM_CONST) Dcm_GaaDIDSupportInfoConf[];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
** Data of Dynamically Defined by Identifier service                          **
*******************************************************************************/
#if (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
#if (DCM_TOTAL_NUM_OF_DYN_DID != DCM_ZERO)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Dcm_DynDidInfoType, DCM_VAR) Dcm_GaaDynDidInfoConfig[
  DCM_TOTAL_NUM_OF_DYN_DID];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_TOTAL_NUM_OF_SOURCE_DYN_DID != DCM_ZERO)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Dcm_MemAddInfoType, DCM_VAR) Dcm_GaaDynMemAddInfo[
  DCM_TOTAL_NUM_OF_SOURCE_DYN_DID];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Dcm_SourceDidInfoType, DCM_VAR) Dcm_GaaDynSourceDidInfo[
  DCM_TOTAL_NUM_OF_SOURCE_DYN_DID];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Data of Read Data By Periodic Identifier Service                           **
*******************************************************************************/
#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
#if (DCM_TOTAL_NUM_OF_PDID != DCM_ZERO)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Dcm_PeriodicDidInfoType, DCM_VAR) Dcm_GaaPerDidInfo[
  DCM_TOTAL_NUM_OF_PDID];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_PDID_NUM_OF_CONNECTION != DCM_ZERO)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Dcm_PeriodicDataInfoType, DCM_VAR) Dcm_GaaPerDataInfo[
  DCM_PDID_NUM_OF_CONNECTION];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Dcm_PeriodicTxPduType, DCM_VAR) Dcm_GaaPerTxPduInfo[
  DCM_PDID_NUM_OF_CONNECTION];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, DCM_VAR) Dcm_GaaPerTxStatus[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

/*******************************************************************************
** Data of Routine Control Service                                            **
*******************************************************************************/
#if (DCM_ROUTINECONTROL_SERVICE == STD_ON)
#if (DCM_NUM_OF_ROUTINE_CONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_RoutineConfigType, DCM_CONST) Dcm_GaaRoutineConfig[
  DCM_NUM_OF_ROUTINE_CONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_ROUTINE_INFO_CONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_RoutineInfoConfigType, DCM_CONST) Dcm_GaaRoutineInfoConfig[
  DCM_NUM_OF_ROUTINE_INFO_CONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_ROUTINE_SIGNAL_CONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_RoutineSignalType, DCM_CONST) Dcm_GaaRoutineSignal[
  DCM_NUM_OF_ROUTINE_SIGNAL_CONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_COMMON_AUTHORIZATION != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_CommonAuthorizationType, DCM_CONST) Dcm_GaaCommonAuthorization[
  DCM_NUM_OF_COMMON_AUTHORIZATION];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_ROUTINE_IN_SIGNAL_ONE_BYTE == STD_ON)
#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, DCM_VAR) Dcm_GaaRoutineInData8[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

#if (DCM_ROUTINE_OUT_SIGNAL_ONE_BYTE == STD_ON)
#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, DCM_VAR) Dcm_GaaRoutineOutData8[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

#if (DCM_ROUTINE_IN_SIGNAL_TWO_BYTE == STD_ON)
#define DCM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
extern VAR(uint16, DCM_VAR) Dcm_GaaRoutineInData16[];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#endif

#if (DCM_ROUTINE_OUT_SIGNAL_TWO_BYTE == STD_ON)
#define DCM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
extern VAR(uint16, DCM_VAR) Dcm_GaaRoutineOutData16[];
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#endif

#if (DCM_ROUTINE_IN_SIGNAL_FOUR_BYTE == STD_ON)
#define DCM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
extern VAR(uint32, DCM_VAR) Dcm_GaaRoutineInData32[];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"
#endif

#if (DCM_ROUTINE_OUT_SIGNAL_FOUR_BYTE == STD_ON)
#define DCM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
extern VAR(uint32, DCM_VAR) Dcm_GaaRoutineOutData32[];
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Data of Upload Download Services                                           **
*******************************************************************************/
#if ((DCM_REQUEST_DOWNLOAD_SERVICE == STD_ON) || \
     (DCM_REQUEST_UPLOAD_SERVICE == STD_ON)   || \
     (DCM_TRANSFER_DATA_SERVICE == STD_ON)    || \
     (DCM_TRANSFER_EXIT_SERVICE == STD_ON))
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_MemoryTransferFncConfigType, DCM_CONST) 
  Dcm_GaaMemTransferFncConfig;
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (DCM_NUM_OF_MEM_TRANSFER_ID_CONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaMemTransferId[
  DCM_NUM_OF_MEM_TRANSFER_ID_CONFIG];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_MEM_TRANSFER_ADDR_LEN_FORMAT_ID != DCM_ZERO)
#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaMemTransferAddrLenFormatId[
  DCM_NUM_OF_MEM_TRANSFER_ADDR_LEN_FORMAT_ID];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif
#endif

#if (DCM_TRANSFER_DATA_SERVICE == STD_ON) || \
    (DCM_FILE_TRANSFER_SERVICE == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_FileTransferFncConfigType, DCM_CONST) 
  Dcm_GaaFileTransferFncConfig;
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_FILE_TRANSFER_SERVICE == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_FileTransferConfigType, DCM_CONST) Dcm_GaaFileTransferConfig;
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
** Data of Response On Event Service                                          **
*******************************************************************************/
#if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
#if (DCM_NUM_OF_ROE_EVENT_CONFIG != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DspRoeConfiguration, DCM_CONST) Dcm_GaaDcmDspRoeCfg[
  DCM_NUM_OF_ROE_EVENT_CONFIG];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_NUM_OF_EVENTWINDOWTIME_SUPPORTED != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_RoeEventWindowTimeType, DCM_CONST) 
  Dcm_GaaEventWindowTimeSupport[DCM_NUM_OF_EVENTWINDOWTIME_SUPPORTED];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_PROTOCOL_TRANSTYPE2 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DslRoeTrans, DCM_CONST) Dcm_DslRoeConnections[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Data of Authentication Service                                             **
*******************************************************************************/
#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_AuthenticationConfigType, DCM_CONST) Dcm_AuthenticationConfig;
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (DCM_AUTHENTICATION_CONNECTION_ES_NUM != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_AuthenticationConnectionESConfigType, DCM_CONST) 
  Dcm_GaaAuthenticationConnectionESConfig[DCM_AUTHENTICATION_CONNECTION_ES_NUM];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_AUTHENTICATION_CONNECTION_NUM != DCM_ZERO)
#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaAuthConnectionIds[
  DCM_AUTHENTICATION_CONNECTION_NUM];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaCertCompareEleDataValues[];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"

#if (DCM_AUTHENTICATION_CONNECTION_NUM != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_AuthenticationConnectionConfigType, DCM_CONST) 
  Dcm_GaaAuthenticationConnectionConfig[DCM_AUTHENTICATION_CONNECTION_NUM];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
extern VAR(Dcm_AuthenticationElementType, DCM_VAR) Dcm_GaaAuthenticationElement[];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, DCM_VAR) Dcm_GaaAuthenticationElementData[];
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /*(DCM_AUTHENTICATION_CONNECTION_NUM != DCM_ZERO)*/
#endif

/*******************************************************************************
** Data of OBD Service 01 and OBD Service 02                                  **
*******************************************************************************/
#if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
  (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON))
#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaPIDs[DCM_TOTAL_NUM_OF_PIDS];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

#if((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
    (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON) || \
    (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON))
#if (DCM_TOTAL_NUM_OF_PIDS != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDConfigType, DCM_CONST) Dcm_GaaPIDConfig[
  DCM_TOTAL_NUM_OF_PIDS];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_DspPidData, DCM_CONST) Dcm_GaaDcmDspPidData[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (DCM_OBD_PID_SUPPORT_INFO == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(DcmDspPidSupportInfo, DCM_CONST) Dcm_GaaDcmDspPidSupportInfo[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDPackSignal, DCM_CONST) Dcm_GaaPIDPackSignal[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (DCM_DSP_PID_BOOLEAN == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDBooleanFunc, DCM_CONST) Dcm_GaaPIDBooleanFunc[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_DSP_PID_UINT8 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDUint8Func, DCM_CONST) Dcm_GaaPIDUint8Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_DSP_PID_UINT8_N == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDUint8NFunc, DCM_CONST) Dcm_GaaPIDUint8NFunc[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_DSP_PID_UINT16 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDUint16Func, DCM_CONST) Dcm_GaaPIDUint16Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_DSP_PID_UINT16_N == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDUint16NFunc, DCM_CONST) Dcm_GaaPIDUint16NFunc[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_DSP_PID_UINT32 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDUint32Func, DCM_CONST) Dcm_GaaPIDUint32Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_DSP_PID_UINT32_N == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDUint32NFunc, DCM_CONST) Dcm_GaaPIDUint32NFunc[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_DSP_PID_SINT8 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDSint8Func, DCM_CONST) Dcm_GaaPIDSint8Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_DSP_PID_SINT8_N == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDSint8NFunc, DCM_CONST) Dcm_GaaPIDSint8NFunc[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_DSP_PID_SINT16 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDSint16Func, DCM_CONST) Dcm_GaaPIDSint16Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_DSP_PID_SINT16_N == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDSint16NFunc, DCM_CONST) Dcm_GaaPIDSint16NFunc[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_DSP_PID_SINT32 == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDSint32Func, DCM_CONST) Dcm_GaaPIDSint32Func[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_DSP_PID_SINT32_N == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_PIDSint32NFunc, DCM_CONST) Dcm_GaaPIDSint32NFunc[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Data of OBD MID Service                                                    **
*******************************************************************************/
#if (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_OBDMidConfigType, DCM_CONST) Dcm_GaaOBDMidConfig[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_OBDMidTids, DCM_CONST) Dcm_GaaObdMidTids[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaOBDMIDs[];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif

/*******************************************************************************
** Data of Request Control service                                            **
*******************************************************************************/
#if (DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE == STD_ON)
#if (DCM_NUM_OF_REQ_CONTROL != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_RequestControlConfigType, DCM_CONST) Dcm_GaaRequestControlConfig[
  DCM_NUM_OF_REQ_CONTROL];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (DCM_TOTAL_NUM_OF_TIDS != DCM_ZERO)
#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaTIDs[DCM_TOTAL_NUM_OF_TIDS];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Data of Vehicle Info Service                                               **
*******************************************************************************/
#if (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
#if (DCM_TOTAL_NUM_OF_VEHINFOTYPE != DCM_ZERO)
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_VehInfoConfigType, DCM_CONST) Dcm_GaaVehInfoConfig[
  DCM_TOTAL_NUM_OF_VEHINFOTYPE];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_VehInfoData, DCM_CONST) Dcm_GaaVehInfoData[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (DCM_TOTAL_NUM_OF_VIDS != DCM_ZERO)
#define DCM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, DCM_CONST) Dcm_GaaVIDs[];
#define DCM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
** Data of Availability OBD ID                                                **
*******************************************************************************/
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_IDEncodeByteConfig, DCM_CONST) Dcm_GaaPIDEncodeByte1[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_IDEncodeByteConfig, DCM_CONST) Dcm_GaaPIDEncodeByte[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_IDEncodeByteConfig, DCM_CONST) Dcm_GaaOBDMIDEncodeByte[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_IDEncodeByteConfig, DCM_CONST) Dcm_GaaTIDEncodeByte[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dcm_IDEncodeByteConfig, DCM_CONST) Dcm_GaaVIDEncodeByte[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONSTP2CONST(uint8, AUTOMATIC, DCM_CONST) Dcm_GpOBDBaseAddress[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONSTP2CONST(Dcm_IDEncodeByteConfig, AUTOMATIC, DCM_CONST) Dcm_GpEncodeByte[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
