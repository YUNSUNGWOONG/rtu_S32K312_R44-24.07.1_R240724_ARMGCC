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
**  SRC-MODULE: Dcm_DspServices.c                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the definitions for UDS services           **
**              implemented by DSP layer of Dcm module                        **
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
** 0.0.1     31-Dec-2019   HueKM          AR440 Implementation                **
** 0.0.2     25-Apr-2020   LamNV10        Change pre-compile for SID19 sub 05 **
** 0.0.3     11-Jun-2020   HueKM          Update code for SID2F               **
** 0.0.4     03-Aug-2020   HueKM          Update code for SID2C as per #14836 **
** 0.0.5     16-Aug-2020   HueKM          Update code for SID2A as per #14836 **
** 0.0.6     20-Aug-2020   HueKM          Change read did size to uint32      **
** 0.0.7     22-Sep-2020   LanhLT         Add DID, DTC white list entry.      **
** 0.0.8     10-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.9     02-Nov-2020   HueKM          Changes made as per #16832          **
** 0.0.10    04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.11    23-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.2     12-May-2022   LanhLT         Update code as per #27145, #26479   **
** 1.0.7     16-Dec-2022   LanhLT         Fix UNECE, #CP44-1166, #CP44-1001   **
**                                        #CP44-1002, #CP44-1178              **
** 1.0.9     31-Mar-2023   LanhLT         Refer #CP44-1558, #CP44-1551        **
**                                        #CP44-1744                          **
** 1.0.12    30-Jun-2023    SY Kim        Refer #CP44-2255                    **
** 1.0.13    04-Jul-2023   DanhTQ1        Refer #CP44-2334                    **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-2768, #CP44-3106        **
** 1.1.1     30-Oct-2023   DanhTQ1        Refer #CP44-3035                    **
** 1.3.0     31-Dec-2023   EK Kim         Refer #CP44-1515                    **
** 1.3.0_HF1 13-Jan-2024   SY Kim         Refer #45119                        **
** 1.3.1     24-Jan-2024   DanhTQ1        Refer #CP44-3126                    **
** 1.4.0     29-Mar-2024   EK Kim         Refer #CP44-3850                    **
** 1.4.1     01-Apr-2024   DanhTQ1,       Refer #CP44-3362, CP44-5272         **
**                         QuanTDM                                            **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_Types.h"
#include "Dcm_DspMain.h"
#include "Dcm_DspServices.h"
#include "Rte_Dcm.h"
#include "SchM_Dcm.h"
#include "Dcm_Externals.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dem.h"
#endif
#include "Dcm_DsdInternal.h"
#include "Dcm_DslInternal.h"
#include "BswM_Dcm.h"
#if (DCM_NVM_CONFIGURED == STD_ON)
#include "NvM.h"
#endif
#include "SchM_Dcm.h"
#include "Dcm_DspNonPagedDTCSubFct.h"
#include "Dcm_DspReadDTCInfo.h"
#include "Dcm_DspReadSSDTCInfo.h"
#include "Dcm_PackUnPack.h"
#include "Dcm_DspOBDServices.h"
#include "Dcm_DspOBDInternals.h"
#include "Dcm_DslManageSecurity.h"
#include "Dcm_DspMemoryServices.h"

#include "Dcm_Config.h"
#include "Dcm_Utils.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dcm_DemInterfaces.h"
#endif
#include "Dcm_Lib.h"
#include "Dcm_Validate.h"
#include "Dcm_Authentication.h"
#include "Dcm_ReqRespHandling.h"
#include "Dcm_Callout_SecureService.h"

#if (DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON)
#include "Dcm_APIs.h"
#endif

/* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */

/*******************************************************************************
**                      STATIC MACRO                                          **
*******************************************************************************/

#define DCM_SIG_STATE_UNDEFINE               0x00u
#define DCM_SIG_STATE_CONDITION_CHECK_READ   0x01u
#define DCM_SIG_STATE_READ_SIGNAL            0x02u
#define DCM_SIG_STATE_READ_LEN               0x03u


#define DCM_DID_STATE_UNDEFINE               0x00u
#define DCM_DID_STATE_CONDITION_CHECK_READ   0x01u
#define DCM_DID_STATE_READ_DID               0x02u

#define DCM_READDID_STATE_READ_DID           0x01u
#define DCM_READDID_STATE_READ_DIDREF        0x02u

#define DCM_DID_READ_ACCESS_MASK             0x01u
#define DCM_DID_WRITE_ACCESS_MASK            0x02u
#define DCM_DID_CONTROL_ACCESS_MASK          0x04u

/*******************************************************************************
** Static functions declarations                                              **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

#if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteSigTypeNvMBlock(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) anInputBuffer,
  Dcm_NegativeResponseCodeType *anOutNegRespCode);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadSigTypeNvMBlock(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) anOutBuffer);
#endif

#if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_GetDidInfo(
  uint16 aDidindex,
  CONST(boolean, DCM_CONST) aCfgDidRangePresent,
  P2CONST(Dcm_DIDInfoType, AUTOMATIC, DCM_APPL_CONST) *aCfgDidInfo);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidByDataSpecificIf(
  Dcm_OpStatusType OpStatus,
  Dcm_DidParaConfigConstPtrType pDidConfig,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode);
#endif

#if (((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)) && \
  (DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidByAtomicIf(
  Dcm_OpStatusType OpStatus,
  Dcm_DidParaConfigConstPtrType pDidConfig,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeNonOBDDID(
  Dcm_OpStatusType OpStatus,
  uint16 DataIdentifier,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
static FUNC(void, DCM_CODE) Dcm_DspReadDid_PackSignal(
  uint16 bufferSize,
  Dcm_DidSignalConfigPtrType pSignalCfg,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pInBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pOutBuffer);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) && \
  (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeDDDID(
  Dcm_OpStatusType OpStatus,
  uint16 DataIdentifier,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode);
#endif

#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Dcm_DidType, DCM_CODE) Dcm_DspGetDidType(
  uint16 usDidIndex);
#endif

#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_ReadDid_AuthValidate(
  uint16 didIndex,
  boolean isDidRange);
#endif
#endif

#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidType(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 DID,
  Dcm_NegativeResponseCodeType *pErrorCode);
#endif

#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeDidRange(
  Dcm_OpStatusType OpStatus,
  uint16 DataIdentifier,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_GetSizeOfDidSignal(
  Dcm_OpStatusType OpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) pDataCfg,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) pSignalSize);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) && \
  (DCM_OBD_DID_SUPPORT_INFO == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_GetDidSupportInfo(
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pSupportInfo);
#endif

#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeF186(
  Dcm_OpStatusType OpStatus,
  uint16 DataIdentifier,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode);
#endif

#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeF810(
  Dcm_OpStatusType OpStatus,
  uint16 DataIdentifier,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode);
#endif

#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeOBDDID(
  Dcm_OpStatusType OpStatus,
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NrcPtrType pErrorCode);

#if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspInternal_ReadDidTypeObdPid(
  Dcm_OpStatusType OpStatus,
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize);

#if (DCM_ENABLE_OBD_MIRROR == STD_OFF)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadPidByUdsIf(
  Dcm_OpStatusType OpStatus,
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize);
#endif
#endif

#if (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspInternal_ReadDidTypeObdVid(
  Dcm_OpStatusType OpStatus,
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize);

#if (DCM_ENABLE_OBD_MIRROR == STD_OFF)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadVidByUdsIf(
  Dcm_OpStatusType OpStatus,
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize);
#endif
#endif

#if (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspInternal_ReadDidTypeObdMid(
  Dcm_OpStatusType OpStatus,
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize);

#endif
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ConditionCheckRead(
  Dcm_OpStatusType OpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) pDataCfg,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadSigType(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) anOutputBuffer);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) && \
     (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadSigTypeMemory(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  Dcm_NegativeResponseCodeType *pErrorCode);
#endif


#if (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
static FUNC(boolean, DCM_CODE) Dcm_DynDid_GetConfigIndex(
  uint16 dataId,
  Dcm_Uint16PtrType pCfgIndex);

static FUNC(void, DCM_CODE) Dcm_DynDid_UpdatePosResp(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_DynDid_ClearOneDefinedDid(
  uint16 usDynDidIndex);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_ClearDefinedDid(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckRequestedDid(
  uint16 usDid);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckExceedDidElement(
  uint16 usDynDidIndex,
  Dcm_MsgLenType ddReqDataLen,
  Dcm_Uint8PtrType pSourceCount);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckDidSource(
  uint8 ucSourceCount,
  Dcm_Uint8PtrType pReqData);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckDefineByDid(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint8PtrType pSourceCount,
  Dcm_Uint16PtrType pDynDidIndex);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_DefineByDid(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckExceedMemoryElement(
  uint16 usSourceLen,
  uint16 usDynDidIndex,
  Dcm_MsgLenType ddReqDataLen,
  Dcm_Uint8PtrType pSourceCount);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckMemorySource(
  uint8 ucSourceCount,
  uint8 ucMemAddrBytes,
  uint8 ucMemSizeBytes,
  Dcm_Uint8PtrType pReqData);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckDefineByMemory(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint8PtrType pSourceCount,
  Dcm_Uint16PtrType pDynDidIndex);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_DefineByMemory(
  Dcm_MsgContextPtrType pMsgContext);
#endif

#if (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspIOCtrl_ValidateRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint16PtrType pDidIndex);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspIOCtrl_CheckDataId(
  uint16 dataId,
  Dcm_Uint16PtrType pDidIndex);

#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspIOCtrl_AuthValidate(
  uint16 dataId,
  Dcm_DidCtrlConstPtrType pDidCtrl);
#endif

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspIOCtrl_CheckAuthorization(
  Dcm_DidCtrlConstPtrType pDidCtrl);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspIOCtrl_CheckFullLength(
  uint8 ctrlType,
  Dcm_MsgLenType reqDataLen,
  Dcm_DidParaConfigConstPtrType pDidCfg);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspIOCtrl_CheckCtrlParameter(
  uint8 ctrlType,
  Dcm_DidParaConfigConstPtrType pDidCfg);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_InternalProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_ReadData(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DidParaConfigConstPtrType pDidCfg,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_ReturnControlToECU(
  Dcm_OpStatusType OpStatus,
  Dcm_DataConfigConstPtrType pDataCfg,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_ResetToDefault(
  Dcm_OpStatusType OpStatus,
  Dcm_DataConfigConstPtrType pDataCfg,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_FreezeCurrentState(
  Dcm_OpStatusType OpStatus,
  Dcm_DataConfigConstPtrType pDataCfg,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_ShortTermAdjustment(
  Dcm_OpStatusType OpStatus,
  uint16 dataLength,
  Dcm_DataConfigConstPtrType pDataCfg,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pCtrlStateInfo,
  Dcm_NrcPtrType pErrorCode);

static FUNC(uint32, DCM_CODE) Dcm_DspIOCtrl_GetCtrlMaskSize(
  Dcm_DidParaConfigConstPtrType pDidCfg);

static FUNC(uint16, DCM_CODE) Dcm_DspIOCtrl_UnPackSignal(
  uint32 inBufferSize,
  Dcm_DidSignalConfigPtrType pSignalCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pInBuffer,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutBuffer);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_DataSignalProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  uint32 ctrlStateSize,
  Dcm_DidSignalConfigPtrType pSignalCfg,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_DataInterfaceProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DidParaConfigConstPtrType pDidCfg,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_DspIOCtrl_UpdateResponse(
  uint16 didIndex,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode);

#if ((DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON) && \
     (DCM_MAX_CONTROL_MASK_SIZE != DCM_ZERO))
static FUNC(void, DCM_CODE) Dcm_DspIOCtrl_CalculateUnderCtrl(
  uint8 ctrlType,
  uint8 numOfSignal,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pCtrlMaskRecord);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_ProcessCallAtomicRequest(
  uint16 dataId,
  Dcm_InputOutputControlParameterType parameterType,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pControlMask,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pControlState,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_ProcessCallAtomicResponse(
  uint16 dataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pControlMask,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_SrInterfaceProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DidParaConfigConstPtrType pDidCfg,
  Dcm_NrcPtrType pErrorCode);
#endif
#endif

#if ((DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_ResetSignalOpStatus(
  uint16 didIndex);
#endif

#if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_WriteDid_ValidateRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint16PtrType pDidIndex,
  Dcm_BooleanPtrType pIsDidRange);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_WriteDid_CheckDataId(
  uint16 dataId,
  Dcm_Uint16PtrType pDidIndex,
  Dcm_BooleanPtrType pIsDidRange);

#if(DCM_AUTHENTICATION_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_WriteDid_AuthValidate(
  uint16 dataId,
  Dcm_DidWriteConfigConstPtrType pDidWrite);
#endif

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_WriteDid_CheckAuthorization(
  Dcm_DidWriteConfigConstPtrType pDidWrite);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_WriteDid_CheckFullLength(
  uint16 didIndex,
  boolean isDidRange,
  Dcm_MsgLenType reqDataLen);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_WriteDid_InternalProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

#if (DCM_NUM_OF_DCMDSPDIDRANGECONFIG != DCM_ZERO)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_WriteDid_DidRangeProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_DidRangeConfigPtrType pDidRangeConfig,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);
#endif

static FUNC(Std_ReturnType, DCM_CODE) Dcm_WriteDid_CallWriteDataFunc(
  Dcm_OpStatusType OpStatus,
  uint16 writeDataLen,
  Dcm_DataConfigConstPtrType pDataCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pInBuffer,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_WriteDid_DataIfProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_DidParaConfigConstPtrType pDidConfig,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

#if (DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_WriteDid_AtomicIfProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_DidParaConfigConstPtrType pDidConfig,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);
#endif

static FUNC(uint16, DCM_CODE) Dcm_WriteDid_UnPackSignal(
  uint16 totalWriteDataLen,
  Dcm_DidSignalConfigPtrType pSignalCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pInBuffer,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutBuffer);

static FUNC(void, DCM_CODE) Dcm_ResetWriteDidOpStatus(
  uint16 didIndex,
  boolean isDidRange);

static FUNC(void, DCM_CODE) Dcm_WriteDid_UpdateResponse(
  uint16 didIndex,
  boolean isDidRange,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode);
#endif

#if (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_ReadScalingInfo_ValidateRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint16PtrType pDidIndex);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_ReadScalingInfo_CallDataFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_Uint8PtrType pScalingInfo,
  Dcm_DataConfigConstPtrType pDataCfg,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_ReadScalingInfo_DataIfProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DidParaConfigConstPtrType pDidConfig,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_ReadScalingInfo_InternalProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_ReadScalingInfo_UpdateResponse(
  uint16 didIndex,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode);
#endif

#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)

static FUNC(Dcm_PeriodicDidInfoPtrType, DCM_CODE) Dcm_Pdid_GetConfigByRequestedPdid(
uint16 usPdid);

#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_AuthValidate(
  uint16 dataId,
  Dcm_DidReadConfigConstPtrType pDidRead);
#endif

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_CheckRequestedPid(
  uint8 periodicId,
  Dcm_Uint16PtrType pCfgIndex);

#if (DCM_DYNAMIC_DID_PER_SOURCE == STD_ON)
static FUNC(Dcm_DynDidInfoPtrType, DCM_CODE) Dcm_Pdid_GetDynDidConfig(
  uint16 usDidIndex);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_CheckSourceDid(
  uint16 usDidIndex);
#endif

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_CheckStartRequest(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_Pdid_StartOneDid(
  uint8 ucTmMode,
  uint16 usPerDidIndex);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Pdid_ConditionCheckRead(
  Dcm_OpStatusType OpStatus,
  uint16 usDidIndex,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Pdid_ReadDataLength(
  Dcm_OpStatusType OpStatus,
  uint16 usDidIndex,
  Dcm_Uint16PtrType pDataLen,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_StartTransmission(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_CheckStopRequest(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_Pdid_StopOneDid(
  uint16 usPerDidIndex);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_StopAllPids(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_StopSpecificPids(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_StopTransmission(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_Pdid_UpdateTimer(void);

static FUNC(void, DCM_CODE) Dcm_Pdid_HandleResponse(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType ddErrorCode);

static FUNC(void, DCM_CODE) Dcm_Pdid_HandleStopEvent(void);

static FUNC(void, DCM_CODE) Dcm_Pdid_ClearBusyStatus(void);
#endif

#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(boolean, DCM_CODE) Dcm_DspDidSearch(
  uint16 dataId,
  Dcm_Uint16PtrType pDidIndex,
  Dcm_BooleanPtrType pIsDidRange);

static FUNC(boolean, DCM_CODE) Dcm_GetDidRangeConfigIndex(
  uint16 dataId,
  Dcm_Uint16PtrType pCfgIndex);
#endif

#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspValidateReadDid(
  uint16 didIndex, 
  boolean isDidRange);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_ReadDid_CheckAuthorization(
  Dcm_DidReadConfigConstPtrType pDidRead);
#endif

#if ((DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON) \
     || (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) \
     || (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_DspInternal_GetSizeOfDid(
  Dcm_DidParaConfigConstPtrType pDidConfig,
  Dcm_Uint16PtrType pMinLength,
  Dcm_Uint16PtrType pMaxLength);
#endif

#if (DCM_DSP_SECURITY_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_CallGetSeedFnc(
  Dcm_OpStatusType OpStatus,
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  Dcm_Uint8PtrType pReqData,
  Dcm_NrcPtrType pErrorCode);

#if((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || \
    (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_CheckContinuousReqSeed(
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  Dcm_NrcPtrType pErrorCode);
#endif

static FUNC(void, DCM_CODE) Dcm_DspInternal_RequestSeedOk(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  boolean isNewSecLevel);

static FUNC(void, DCM_CODE) Dcm_DspInternal_ProcessGetSeedFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspInternal_ProcessRequestSeed(
  Dcm_MsgContextPtrType pMsgContext,
  uint8 SecAccessType);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_CallCompareKeyFnc(
  Dcm_OpStatusType OpStatus,
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  Dcm_Uint8PtrType pReqData,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_DspInternal_CompareKeyOk(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg);

static FUNC(void, DCM_CODE) Dcm_DspInternal_CompareKeyFail(
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  Dcm_NrcPtrType pErrorCode);

static FUNC(void, DCM_CODE) Dcm_DspInternal_ProcessCompareKeyFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspInternal_ProcessCompareKey(
  Dcm_MsgContextPtrType pMsgContext,
  uint8 SecAccessType);
#endif

#if (DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_APPL_CODE) Dcm_ValidateControlDTCSetting(
  Dcm_MsgContextPtrType pMsgContext);

static FUNC(void, DCM_CODE) Dcm_ProcessControlDTCSetting(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_SubServiceIdConfigConstPtrType pSubSerCfg);
#endif

#if ((DCM_READDTC_SUPPORT == STD_ON) && \
     (DCM_AUTHENTICATION_SERVICE == STD_ON) && \
     (DCM_NUM_OF_USER_DEFINED_FAULT_MEMORY > DCM_ZERO))
static FUNC(uint8, DCM_CODE) Dcm_AuthValidateReadDTCInfo(
  uint8 SubFunction
  , Dcm_MsgContextPtrType pMsgContext);
#endif

/*******************************************************************************
** Static data types                                                          **
*******************************************************************************/
#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static Std_ReturnType (*Dcm_FuncPtrList_ReadDidType[DCM_DID_TYPE_NUM])(
  Dcm_OpStatusType OpStatus,
  uint16 DataIdentifier,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode) = 
{
  /* DID_TYPE_DYN */
  #if (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
  Dcm_DspInternal_ReadDidTypeDDDID,
  #else
  NULL_PTR,
  #endif

  /* DID_TYPE_OBD */
  #if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_DspInternal_ReadDidTypeOBDDID,
  #else
  NULL_PTR,
  #endif

  #if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
       (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
  /* DID_TYPE_NONOBD */
  Dcm_DspInternal_ReadDidTypeNonOBDDID,

  /* DID_TYPE_RANGE */
  #if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
  Dcm_DspInternal_ReadDidTypeDidRange,
  #else
  NULL_PTR,
  #endif

  /* DID_TYPE_SESSION */
  Dcm_DspInternal_ReadDidTypeF186,

  /* DID_TYPE_PROTOCOLID */
  Dcm_DspInternal_ReadDidTypeF810,
  
  #else
  NULL_PTR, /* DID_TYPE_NONOBD */
  NULL_PTR, /* DID_TYPE_RANGE */
  NULL_PTR  /* DID_TYPE_SESSION */
  #endif
};
#endif

#if (DCM_LINK_CONTROL_SERVICE == STD_ON)
static uint8 Dcm_FlagSetBaudrateBeforeTransition = E_NOT_OK;
#endif

/*******************************************************************************
** Function definitions                                                       **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Dcm_DcmClearDiagnosticInformation                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The ClearDiagnosticInformation service is used to   **
**                        clear the UDS Data from the error memory. This      **
**                        service executes DEM function Dem_ClearDTC with     **
**                        parameter DTCGroup equal to the value received in   **
**                        the request to remove either one DTC or a group of  **
**                        DTCs and all related information from the           **
**                        fault memory                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GulDTCValue,               **
**                        Dcm_GddNegRespError                                 **
**                        Function(s) invoked : Dcm_ExternalSetNegResponse,   **
**                        Dcm_ExternalProcessingDone,                         **
**                        Dcm_DspClearDiagInfo                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04058 SRS_Diag_04222 */
/* @Trace: SWS_Dcm_00247 */
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_DSP_CLR_DIAG_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmClearDiagnosticInformation(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpReqResData;
  Tun_DcmDword32 LunDcmDword32;

  Dcm_GddNegRespError = DCM_POS_RESP;

  /* Get the pointer to the request data buffer */
  LpReqResData = pMsgContext->reqData;

  /* Update 4 bytes DTC */
  LunDcmDword32.ddByte.ucLsByte      = LpReqResData[DCM_TWO];
  LunDcmDword32.ddByte.ucMidLowByte  = LpReqResData[DCM_ONE];
  LunDcmDword32.ddByte.ucMidHiByte   = LpReqResData[DCM_ZERO];
  LunDcmDword32.ddByte.ucMsByte      = DCM_ZERO;

  /* Check for the validity of length */
  /* @Trace: SWS_Dcm_00272 */
  if (pMsgContext->reqDataLen != DCM_THREE)
  {
    /* @Trace: Dcm_SUD_API_60000 */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    #if (DCM_CLEAR_ITC_SERVICE_SUPPRT == STD_ON)
    /* @Trace: Dcm_SUD_API_60001 */
    Dcm_InternalTroubleCodeService = DCM_FALSE;

    if (DCM_CLEAR_ITC_SERVICE == (pMsgContext->idContext & DCM_SID_MASK))
    {
      if ((DCM_DTCGROUP_CHASSIS_GROUP != LunDcmDword32.ulLongReg32) &&
          (DCM_DTCGROUP_ALL_GROUPS != LunDcmDword32.ulLongReg32))
      {
        /* @Trace: Dcm_SUD_API_60003 */
        Dcm_GddNegRespError = DCM_E_CONDITIONSNOTCORRECT;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_60002 */
        Dcm_InternalTroubleCodeService = DCM_TRUE;
      }
    }
    #endif
  }

  if (DCM_POS_RESP == Dcm_GddNegRespError)
  {
    /* @Trace: Dcm_SUD_API_60005 */
    Dcm_GulDTCValue = LunDcmDword32.ulLongReg32;
    LddRetVal = Dcm_DspClearDiagInfo(LunDcmDword32.ulLongReg32, pMsgContext);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60004 */
    Dcm_GblSendResponse = DCM_TRUE;
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspClearDiagInfo                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is an internal function for service 0x14 and   **
**                        shall be invoked from the main for DEM_DTC_PENDING  **
**                        conditions                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : GroupOfDTC                                          **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_PrtclTxBufStatus                                **
**                                                                            **
**                        Function(s) invoked : Dem_SelectDTC,                **
**                        Dem_GetDTCSelectionResultForClearDTC,               **
**                        Dem_ClearDTC,                                       **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspClearDiagInfo(
  uint32 GroupOfDTC
  , Dcm_MsgContextPtrType pMsgContext)
{
  Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_FALSE;
  Std_ReturnType RetVal;
  Dcm_NrcPtrType pErrorCode = &Dcm_GddNegRespError;

  #if (DCM_RESPONSE_ON_EVENT_SERVICE  == STD_ON)
  /* Set the Flag when the request is 'Clear All DTCs' */
  if (DCM_DTCGROUP_ALL_GROUPS == GroupOfDTC)
  {
    /* @Trace: Dcm_SUD_API_60006 */
    Dcm_GblRoeClearAll = DCM_TRUE;
  }
  #endif

  /* Trace: DCM_19792_14_01 */
  if (DEM_DTC_GROUP_EMISSION_REL_DTCS_WWH_OBD == GroupOfDTC)
  { 

    #if((DCM_J1979_2_SUPPORT == STD_ON) \
       && (DCM_OBD_UDS_DTC_SEPARATION_SUPPORT == STD_ON))
      /* @Trace: Dcm_SUD_API_60007 */
      (void) IDem_SelectDTC(DEM_DTC_GROUP_EMISSION_REL_DTCS_WWH_OBD, DEM_DTC_FORMAT_OBD_3BYTE, DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY);
    #else
      /* @Trace: Dcm_SUD_API_60007 */
      (void) IDem_SelectDTC(DEM_DTC_GROUP_EMISSION_REL_DTCS_WWH_OBD, DEM_DTC_FORMAT_OBD, DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY);
    #endif
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60007 */
    (void) IDem_SelectDTC(GroupOfDTC, DEM_DTC_FORMAT_UDS, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
  }
  RetVal = IDem_GetDTCSelectionResultForClearDTC();

  pErrorCode = &Dcm_GddNegRespError;

  /* @Trace: SWS_Dcm_01265 */
  CHK_RET_VAL(DEM_WRONG_DTC == RetVal, *pErrorCode, DCM_E_REQUESTOUTOFRANGE);

  #if (DCM_DSP_CLEARDTC_CONFIGURED == STD_ON)
  #if (DCM_DSP_CLEARDTC_CHECK_FUNC_CONFIGURED == STD_ON)
  if (E_OK == RetVal)
  {
    /* @Trace: Dcm_SUD_API_60008 */
    Dcm_ClearDTCCheckFunType pClearDTCCheckFun;
    pClearDTCCheckFun = Dcm_GaaClearDTCConfig->pClearDTCCheckFun;

    /* polyspace +1 DEFECT:DEAD_CODE [Not a defect:Low] "pClearDTCCheckFun can be configured or not by user . No impact" */
    if (pClearDTCCheckFun != NULL_PTR)
    {
      /* @Trace: SRS_Diag_04194 */
      /* @Trace: Dcm_SUD_API_60009 */
      RetVal = pClearDTCCheckFun(GroupOfDTC, pErrorCode);
    }
  }
  #endif /* DCM_DSP_CLEARDTC_CHECK_FUNC_CONFIGURED */

  /* @Trace: SWS_Dcm_01269 */
  #if (DCM_MODE_RULE == STD_ON)
  if (E_OK == RetVal)
  {
    /* @Trace: Dcm_SUD_API_60010 */
    boolean ModeRuleConfigured = Dcm_GaaClearDTCConfig->blModeRuleConfigured;
    Dcm_ModeType ModeIndex = Dcm_GaaClearDTCConfig->ucModeRuleIndex;
    *pErrorCode = Dcm_CheckModeRule(ModeRuleConfigured, ModeIndex);
    CHK_RET_VAL(*pErrorCode != DCM_POS_RESP, RetVal, E_NOT_OK);
  }
  #endif /* DCM_MODE_RULE */
  #endif /* DCM_DSP_CLEARDTC_CONFIGURED */

  if (E_OK == RetVal)
  {
    /* @Trace: Dcm_SUD_API_60011 */
    RetVal = IDem_ClearDTC();

    /* @Trace: SWS_Dcm_00707 SWS_Dcm_00708 SWS_Dcm_00966 SWS_Dcm_01060 SWS_Dcm_01408 */
    CHK_RET_VAL(DEM_WRONG_DTC == RetVal, *pErrorCode, DCM_E_REQUESTOUTOFRANGE);
    CHK_RET_VAL(DEM_WRONG_DTCORIGIN == RetVal, *pErrorCode, DCM_E_REQUESTOUTOFRANGE);
    CHK_RET_VAL(DEM_CLEAR_FAILED == RetVal, *pErrorCode, DCM_E_CONDITIONSNOTCORRECT);
    CHK_RET_VAL(DEM_CLEAR_BUSY == RetVal, *pErrorCode, DCM_E_CONDITIONSNOTCORRECT);
    CHK_RET_VAL(DEM_CLEAR_MEMORY_ERROR == RetVal, *pErrorCode, DCM_E_GENERALPROGRAMMINGFAILURE);

    if (DEM_PENDING == RetVal)
    {
      /* @Trace: Dcm_SUD_API_70000 */
      *pErrorCode = DCM_POS_RESP;
      Dcm_PrtclTxBufStatus.ucClearDTCStatus = DCM_TRUE;
    }
  }

  /* @Trace: SWS_Dcm_00705 */
  if (E_OK == RetVal)
  {
    /* @Trace: Dcm_SUD_API_60012 */
    pMsgContext->resDataLen = 0U;

    #if (DCM_RESPONSE_ON_EVENT_SERVICE  == STD_ON)
    /* Reset the Flag */
    if (Dcm_GblRoeClearAll == DCM_TRUE)
    {
      /* @Trace: Dcm_SUD_API_60013 */
      Dcm_GblRoeClearAll = DCM_FALSE;
    }
    #endif
  }

  if (Dcm_PrtclTxBufStatus.ucClearDTCStatus == DCM_FALSE)
  {
    #if (DCM_CLEAR_ITC_SERVICE_SUPPRT == STD_ON)
    if (DCM_TRUE == Dcm_InternalTroubleCodeService)
    {
      /* @Trace: Dcm_SUD_API_60014 */
      CHK_RET_VAL(*pErrorCode != DCM_POS_RESP, *pErrorCode, DCM_E_CONDITIONSNOTCORRECT);
      Dcm_InternalTroubleCodeService = DCM_FALSE;
    }
    #endif

    /* @Trace: Dcm_SUD_API_60015 */
    Dcm_GblSendResponse = DCM_TRUE;
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmReadDTCInformation                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used for service(0x19) to read all **
**                        the status of server resident DTC information       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Dcm_GucSubFunction,Dcm_GucReadGlobal,               **
**                        Dcm_GpReqResData,                                   **
**                        Dcm_GaaSubServiceIdConfig, Dcm_GpMsgContext         **
**                        Function(s) invoked : Dcm_DspRptNoOfDTC,            **
**                        Dcm_DspRptDTC, Dcm_DspRptDTCSnapshotRecIdentfn,     **
**                        Dcm_DspRptDTCSnapshotRecByDTCNum,                   **
**                        Dcm_DspRptDTCBySeverityInfo,                        **
**                        Dcm_DspRptFailedConfirmedDTCInfo,                   **
**                        Dcm_DspRptDTCFltDetCtr,                             **
**                        Dcm_ExternalProcessingDone and                      **
**                        Dcm_ExternalSetNegResponse                          **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04058 SRS_Diag_04195 */
#if (DCM_READDTC_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadDTCInformation(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;
  Dcm_SubServiceIdConfigConstPtrType LpSubServiceCfg;

  Dcm_GucReadGlobal = DCM_FALSE;
  LpSubServiceCfg = Dcm_GetSubServiceConfigPtr(pMsgContext);

  if(NULL_PTR == LpSubServiceCfg)
  {
    /* @Trace: Dcm_SUD_API_60771 */
    /* Never be reached, but this code is added for MISRA-rules */
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
  /* External diagnostic subservice processing */
  else if (NULL_PTR != LpSubServiceCfg->pSubServiceFnc)
  {
    /* @Trace: Dcm_SUD_API_60772 */
    LddRetVal = LpSubServiceCfg->pSubServiceFnc(OpStatus, pMsgContext, pErrorCode);
  }
  /* Dcm-Internal diagnostic subservice processing */
  else
  {
    /* Check for the validity of length */
    if(pMsgContext->reqDataLen == LpSubServiceCfg->ucSubFuncLength)
    {
      /* @Trace: Dcm_SUD_API_60773 */
      /* Set the global variable with the sub function value, to do the
       * corresponding sub function's functionality in the function called */
      Dcm_GucSubFunction = LpSubServiceCfg->ucSubServiceId;

      /* Set the global variable with the response data buffer address,
       * which is to be used in the corresponding sub function invoked */
      Dcm_GpReqResData = pMsgContext->resData;

      #if ((DCM_AUTHENTICATION_SERVICE == STD_ON) && \
           (DCM_NUM_OF_USER_DEFINED_FAULT_MEMORY > DCM_ZERO))
      /* @Trace: SWS_Dcm_01545 SWS_Dcm_01546 SWS_Dcm_01547 SWS_Dcm_01534*/
      if (DCM_FALSE == Dcm_AuthValidateReadDTCInfo(Dcm_GucSubFunction, pMsgContext))
      {
        /* @Trace: Dcm_SUD_API_60774 */
        Dcm_GddNegRespError = DCM_E_AUTHENTICATIONREQUIRED;
      }
      else
      #endif
      {
        /* Invoke the sub function that is requested */
        switch(Dcm_GucSubFunction)
        {
        #if(DCM_RPT_NOOFDTC == STD_ON)
        case DCM_UDS_READ_DTC_INFO_01:
        case DCM_UDS_READ_DTC_INFO_07:
        case DCM_UDS_READ_DTC_INFO_11:
        case DCM_UDS_READ_DTC_INFO_12:
          /* @Trace: Dcm_SUD_API_60775 */
          /* Dsp function to be invoked for subfunction values 0x01, 0x07,
           * 0x11 and 0x12 */
          Dcm_DspRptNoOfDTC(pMsgContext);
          break;
        #endif

        #if(DCM_RPT_DTC == STD_ON)
        case DCM_UDS_READ_DTC_INFO_02:
          #if (DCM_READ_ITC_SERVICE_SUPPRT == STD_ON)
          /* @Trace: Dcm_SUD_API_60776 */
          Dcm_InternalTroubleCodeService = DCM_FALSE;

          if (DCM_READ_ITC_SERVICE == (pMsgContext->idContext & DCM_SID_MASK))
          {
            /* ReadITCInformation's reportITCByStatusMask
             * supports only ITCStatusMask(0x08) */
            if (DCM_ITC_STATUS_MASK != pMsgContext->reqData[1u])
            {
              /* @Trace: Dcm_SUD_API_60777 */
              Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
              break;
            }
            else
            {
              /* @Trace: Dcm_SUD_API_60778 */
              Dcm_InternalTroubleCodeService = DCM_TRUE;
             /* No break */
            }
          }
          #endif
          /* No break */
        case DCM_UDS_READ_DTC_INFO_0A:
        case DCM_UDS_READ_DTC_INFO_0F:
        case DCM_UDS_READ_DTC_INFO_13:
        case DCM_UDS_READ_DTC_INFO_15:
        case DCM_UDS_READ_DTC_INFO_17:
        case DCM_UDS_READ_DTC_INFO_55:
        #if (DCM_J1979_2_SUPPORT == STD_ON)
          /* @Trace: R21-11, SWS_Dcm_01607 */
          /* The Dcm shall support UDS Service 0X19 with subfunction 0x1A according to
           * ISO 14229-1:2020 */
          /* Trace: DCM_19792_1A_06 */
        case DCM_UDS_READ_DTC_INFO_1A:
          /* @Trace: R21-11, SWS_Dcm_01610 */
          /* The Dcm shall support UDS Service 0X19 with subfunction 0x56 according to
           * ISO 14229-1:2020 */
          /* Trace: DCM_19792_56_10 */
        case DCM_UDS_READ_DTC_INFO_56:
        #endif /* (DCM_J1979_2_SUPPORT == STD_ON) */
          /* @Trace: Dcm_SUD_API_60780 */
          /* Dsp function to be invoked for subfunction values 0x02, 0x0A,
           * 0x0F, 0x13, 0x15, 0x17, 0x55 */
          Dcm_DspRptDTC(pMsgContext);
          break;
        #endif

        #if(DCM_RPT_DTCSNAPSHOTREC_IDENTFN == STD_ON)
        case DCM_UDS_READ_DTC_INFO_03:
          /* @Trace: Dcm_SUD_API_60781 */
          /* Dsp function to be invoked for subfunction value 0x03 */
          Dcm_DspRptDTCSnapshotRecIdentfn(pMsgContext);
          break;
        #endif

        #if((DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON) || \
        (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON))
        case DCM_UDS_READ_DTC_INFO_04:
        case DCM_UDS_READ_DTC_INFO_06:
        case DCM_UDS_READ_DTC_INFO_10:
        case DCM_UDS_READ_DTC_INFO_18:
        case DCM_UDS_READ_DTC_INFO_19:
          /* @Trace: Dcm_SUD_API_60782 */
          /* Dsp function to be invoked for subfunction value 0x04, 0x06, 0x10, 0x18, 0x19 */
          Dcm_DspRptDTCSnapshotRecByDTCNum(pMsgContext);
          break;
        #endif

        #if (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON)
        case DCM_UDS_READ_DTC_INFO_05:
          /* @Trace: Dcm_SUD_API_60783 */
          /* Dsp function to be invoked for subfunction 0x05 */
          Dcm_DspRptDTCSnapshotRecByRecordNum(pMsgContext);
          break;
        #endif

        #if(DCM_RPT_DTCBYSEVERITYMASKRECORD == STD_ON)
        case DCM_UDS_READ_DTC_INFO_08:
          /* @Trace: Dcm_SUD_API_60784 */
          /* Dsp function to be invoked for subfunction values 0x08 */
          Dcm_DspRptDTCBySeverityInfo(pMsgContext);
          break;
        #endif

        #if(DCM_RPT_DTCBYSEVERITYINFOFDTC == STD_ON)
        case DCM_UDS_READ_DTC_INFO_09:
          /* @Trace: Dcm_SUD_API_60785 */
          /* Dsp function to be invoked for subfunction values 0x09 */
          Dcm_DspRptDTCBySeverityInfoOfDTC(pMsgContext);
          break;
        #endif

        #if(DCM_RPT_FAILEDCONFIRMEDDTCINFO == STD_ON)
        case DCM_UDS_READ_DTC_INFO_0B:
        case DCM_UDS_READ_DTC_INFO_0C:
        case DCM_UDS_READ_DTC_INFO_0D:
        case DCM_UDS_READ_DTC_INFO_0E:
          /* @Trace: Dcm_SUD_API_60786 */
          /* Dsp function to be invoked for subfunction values
           * 0x0B, 0x0C, 0x0D, 0x0E */
          Dcm_DspRptFailedConfirmedDTCInfo(pMsgContext);
          break;
        #endif

        #if(DCM_RPT_DTC_FLT_DET_CTR == STD_ON)
        case DCM_UDS_READ_DTC_INFO_14:
        case DCM_UDS_READ_DTC_INFO_42:
          /* @Trace: Dcm_SUD_API_60787 */
          /* Dsp function to be invoked for subfunction values 0x14 0x42 */
          Dcm_DspRptDTCFltDetCtr(pMsgContext);
          break;
        #endif

        default:
          Dcm_GddNegRespError = DCM_E_SUBFUNCTIONNOTSUPPORTED;
          /* @Trace: Dcm_SUD_API_60788 */
          /* Do Nothing */
          break;
        }
      }
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60789 */
      Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    /* Dcm_GucReadGlobal set to true after Dcm_DspRptDTC is called,
     * It  means that response is NRC or fault */
    if(Dcm_GucReadGlobal == DCM_FALSE)
    {
      if (Dcm_GddNegRespError != DCM_POS_RESP)
      {
        /* @Trace: Dcm_SUD_API_60790 */
        Dcm_InternalSetNegResponse(pMsgContext, Dcm_GddNegRespError);
      }

      /* @Trace: Dcm_SUD_API_60791 */
      Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
    }
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_AuthValidateReadDTCInfo                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check access right and white list for UDS SID 0x19  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : SubFunction, pMsgContext                            **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if ((DCM_READDTC_SUPPORT == STD_ON) && \
     (DCM_AUTHENTICATION_SERVICE == STD_ON) && \
     (DCM_NUM_OF_USER_DEFINED_FAULT_MEMORY > DCM_ZERO))
static FUNC(uint8, DCM_CODE) Dcm_AuthValidateReadDTCInfo(
  uint8 SubFunction
  , Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60050 */
  uint8 RetVal = DCM_TRUE;

  if ((DCM_UDS_READ_DTC_INFO_17 == SubFunction)
      || (DCM_UDS_READ_DTC_INFO_18 == SubFunction)
      || (DCM_UDS_READ_DTC_INFO_19 == SubFunction))
  {
    uint8 MemoryId;

    if (DCM_UDS_READ_DTC_INFO_17 == SubFunction)
    {
      /* @Trace: Dcm_SUD_API_60051 */
      MemoryId = pMsgContext->reqData[2U];
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60052 */
      MemoryId = pMsgContext->reqData[5U];
    }

    uint8 ChkVal = DCM_FALSE;
    Dcm_AuthenticationRoleType Role;

    for (uint8 idx = 0U; idx < DCM_NUM_OF_USER_DEFINED_FAULT_MEMORY; idx++)
    {
      /* @Trace: Dcm_SUD_API_60053 */
      Dcm_DspReadDTCInfoConfigConstPtrType pReadDTCInfoCfg;
      pReadDTCInfoCfg = &Dcm_GaaDspReadDTCInfo[idx];

      if (MemoryId == pReadDTCInfoCfg->MemoryId)
      {
        /* @Trace: Dcm_SUD_API_60054 */
        Dcm_MemCopy(Role, pReadDTCInfoCfg->Role, DCM_AUTHENTICATION_ROLE_SIZE);
        ChkVal = DCM_TRUE;
        break;
      }
    }

    if (DCM_TRUE == ChkVal)
    {
      /* @Trace: Dcm_SUD_API_60055 */
      ChkVal = Dcm_ValidateAccessRights(Role);

      CHK_RET_VAL(DCM_FALSE == ChkVal, ChkVal, \
        Dcm_ValidateAccessRightsWithWLMemorySelection(&MemoryId));

      RetVal = ChkVal;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60056 */
      RetVal = DCM_TRUE;
    }
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmControlDTCSetting                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The DcmControlDTCSetting service is used to stop or **
**                        resume the setting of diagnostic trouble codes      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GddNegRespError,           **
**                        Function(s) invoked : Dcm_ExternalSetNegResponse,   **
**                        Dcm_ExternalProcessingDone, Dem_EnableDTCStorage,   **
**                        Dem_DisableDTCStorage                               **
**                                                                            **
*******************************************************************************/
#if (DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)
/* @Trace: SRS_Diag_04159 SRS_Diag_04180 */
/* @Trace: SWS_Dcm_00249 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmControlDTCSetting(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType ReqResult = E_OK;

  Dcm_GddNegRespError = DCM_POS_RESP;

  Dcm_SubServiceIdConfigConstPtrType pSubSerCfg = Dcm_GetSubServiceConfigPtr(pMsgContext);

  if (NULL_PTR == pSubSerCfg)
  {
    /* @Trace: Dcm_SUD_API_60057 */
    /* Never be reached, but this code is added for MISRA-rules */
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }
  /* External diagnostic subservice processing  */
  else if (NULL_PTR != pSubSerCfg->pSubServiceFnc)
  {
    if ((pMsgContext != NULL_PTR) && (DCM_INITIAL == OpStatus) && (pMsgContext->reqDataLen > 0U))
    {
      /* @Trace: Dcm_SUD_API_60058 */
      /* The pointer in pMsgContext shall point behind the SubFunction */
      pMsgContext->reqData = &pMsgContext->reqData[1U];
      pMsgContext->reqDataLen--;
    }

    /* @Trace: Dcm_SUD_API_60059 */
    ReqResult = pSubSerCfg->pSubServiceFnc(OpStatus, pMsgContext, pErrorCode);
  }
  /* Internal diagnostic subservice processing  */
  else
  {
    Dcm_NegativeResponseCodeType ChkVal = Dcm_ValidateControlDTCSetting(pMsgContext);

    if (ChkVal != DCM_POS_RESP)
    {
      /* @Trace: Dcm_SUD_API_60060 */
      Dcm_InternalSetNegResponse(pMsgContext, ChkVal);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60061 */
      Dcm_ProcessControlDTCSetting(OpStatus, pMsgContext, pSubSerCfg);
    }

    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }

  return ReqResult;
}

/*******************************************************************************
** Function Name        : Dcm_ValidateControlDTCSetting                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate request message for UDS 0x85 service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_APPL_CODE) Dcm_ValidateControlDTCSetting(
  Dcm_MsgContextPtrType pMsgContext)
{
  Dcm_NegativeResponseCodeType ChkVal = DCM_POS_RESP;

  CHK_RET_VAL(pMsgContext == NULL_PTR, ChkVal, DCM_E_CONDITIONSNOTCORRECT);
  VALIDATE_NEXT(ChkVal, (pMsgContext->reqData == NULL_PTR), DCM_E_CONDITIONSNOTCORRECT);
  VALIDATE_NEXT(ChkVal, (pMsgContext->resData == NULL_PTR), DCM_E_CONDITIONSNOTCORRECT);

  /* @Trace: SWS_Dcm_01564 SWS_Dcm_00829 */
  uint8 ExpReqLen = 1U;

  /* @Trace: Dcm_SUD_API_60062 */
  #if (DCM_DSP_CONTROL_DTC_SUPPORT_OPTION_RECORD == STD_ON)
  ExpReqLen = 4U;
  #endif

  /* @Trace: Dcm_SUD_API_60063 */
  VALIDATE_NEXT(ChkVal
    , (pMsgContext->reqDataLen != ExpReqLen)
    , DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);

  /* @Trace: SWS_Dcm_01399 */
  /* @Trace: SRS_Diag_04159 */
  /* @Trace: Dcm_SUD_API_60064 */
  #if (DCM_DSP_CONTROL_DTC_SUPPORT_OPTION_RECORD == STD_ON)
  VALIDATE_NEXT(ChkVal
    , (pMsgContext->reqData[1U] != 0xFF
       || pMsgContext->reqData[2U] != 0xFF
       || pMsgContext->reqData[3U] != 0xFF)
    , DCM_E_REQUESTOUTOFRANGE);
  #endif

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessControlDTCSetting                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal process function for UDS 0x85 service      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext, pSubSerCfg                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_ProcessControlDTCSetting(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_SubServiceIdConfigConstPtrType pSubSerCfg)
{
  uint8 DTCSettingType = pSubSerCfg->ucSubServiceId;

  /* @Trace: SRS_Diag_04115 */
  /* @Trace: SWS_Dcm_01063 SWS_Dcm_00406 */
  Std_ReturnType RetVal;
  #if (DCM_DEM_CONFIGURED == STD_ON)
  RetVal = (DTCSettingType == DCM_DTC_SETTING_TYPE_ON) ?
    IDem_EnableDTCSetting() : IDem_DisableDTCSetting();
  #else
  RetVal = E_OK;
  #endif
  
  if (RetVal == E_OK)
  {
    /* @Trace: Dcm_SUD_API_60066 */
    Dcm_GblDTCSettingDisabled = (DTCSettingType == DCM_DTC_SETTING_TYPE_ON) ?
      DCM_FALSE : DCM_TRUE;

    /* @Trace: SWS_Dcm_00783 SWS_Dcm_00784 */
    Dcm_ControlDTCSettingType DTCSetting = (DTCSettingType == DCM_DTC_SETTING_TYPE_ON) ?
      DCM_ENABLEDTCSETTING : DCM_DISABLEDTCSETTING;

    #if (DCM_DEM_CONFIGURED == STD_ON)
    (void) SchM_Switch_Dcm_DcmControlDTCSetting(DTCSetting);
    #endif

    pMsgContext->resDataLen = 1U;
    pMsgContext->resData[0U] = DTCSettingType;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60065 */
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
  }

  DCM_UNUSED(OpStatus);
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmSecurityAccess                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service provides a means to access data and/or **
**                        diagnostic services, which have restricted access   **
**                        for security, emissions or safety reasons           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04005 SRS_Diag_04198 SRS_ES95489_01E_00001 */
/* @Trace: SRS_ES95489_01E_00002 SRS_ES96590_00E_00001 SRS_ES96590_00E_00002 */
#if (DCM_DSP_SECURITY_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmSecurityAccess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_00252 */
  Std_ReturnType LddRetVal = E_OK;

  Dcm_SubServiceIdConfigConstPtrType LpSubServiceCfg;
  LpSubServiceCfg = Dcm_GetSubServiceConfigPtr(pMsgContext);

  if (NULL_PTR == LpSubServiceCfg)
  {
    /* @Trace: Dcm_SUD_API_60067 */
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
  else if (NULL_PTR != LpSubServiceCfg->pSubServiceFnc)
  {
    /* @Trace: Dcm_SUD_API_60068 */
    LddRetVal = LpSubServiceCfg->pSubServiceFnc(OpStatus, pMsgContext, pErrorCode);
  }
  else
  {
    Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;
    uint8 LucSecAccessType = pMsgContext->reqData[DCM_ZERO] & DCM_SUBFUNCTION_MASK;

    /* @Trace: SWS_Dcm_01350 */
    if (DCM_TRUE == Dcm_IsTimerRunning(DCM_SECURITY_TIMER))
    {
      /* @Trace: Dcm_SUD_API_60069 */
      LddErrorCode = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
    }
    else if (DCM_ZERO != (LucSecAccessType & DCM_BIT0_AND_MASK))
    {
      /* @Trace: Dcm_SUD_API_60070 */
      LddErrorCode = Dcm_DspInternal_ProcessRequestSeed(
        pMsgContext, LucSecAccessType);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60071 */
      LddErrorCode = Dcm_DspInternal_ProcessCompareKey(
        pMsgContext, LucSecAccessType);
    }

    if ((DCM_FALSE == Dcm_DspServiceProcessingSts.ucSecSeedReqPending) &&
        (DCM_FALSE == Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending))
    {
      if (DCM_POS_RESP != LddErrorCode)
      {
        /* @Trace: Dcm_SUD_API_60072 */
        Dcm_InternalSetNegResponse(pMsgContext, LddErrorCode);
      }

      /* @Trace: Dcm_SUD_API_70001 */
      Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
    }
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_CallGetSeedFnc                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get getSeed() function from security configuration  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pSecLvlCfg, pReqData                      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_CallGetSeedFnc(
  Dcm_OpStatusType OpStatus,
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  Dcm_Uint8PtrType pReqData,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60079 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ((NULL_PTR != pSecLvlCfg) && (NULL_PTR != pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_60073 */
    *pErrorCode = DCM_POS_RESP;

    if ((USE_ASYNCH_FNC == pSecLvlCfg->ucSecurityUsePort) ||
        (USE_ASYNCH_CLIENT_SERVER == pSecLvlCfg->ucSecurityUsePort))
    {
      if (pSecLvlCfg->ulSecurityADRSize > DCM_ZERO)
      {
        if (NULL_PTR != pSecLvlCfg->pGetSeedAsyncFunAdr)
        {
          /* @Trace: Dcm_SUD_API_60075 */
          LddRetVal = pSecLvlCfg->pGetSeedAsyncFunAdr(
            &pReqData[DCM_ONE], OpStatus, &Dcm_GaaSeed[DCM_ZERO], pErrorCode);
        }
      }
      else
      {
        if (NULL_PTR != pSecLvlCfg->pGetSeedAsyncFun)
        {
          /* @Trace: Dcm_SUD_API_60077 */
          LddRetVal = pSecLvlCfg->pGetSeedAsyncFun(
            OpStatus, &Dcm_GaaSeed[DCM_ZERO], pErrorCode);
        }
      }
    }

    if ((E_NOT_OK == LddRetVal) && (DCM_POS_RESP == *pErrorCode))
    {
      /* @Trace: Dcm_SUD_API_60078 */
      *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    }
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_CheckContinuousReqSeed              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check continuous request seed is sent               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pSecLvlCfg                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || \
    (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_CheckContinuousReqSeed(
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;

  Dcm_IncSecurityAttemptCounter();

  if (DCM_TRUE == Dcm_IsSecurityAttemptCounterExceeded())
  {
    /* @Trace: Dcm_SUD_API_60080 */
    LddRetVal = E_NOT_OK;
    *pErrorCode = DCM_E_EXCEEDNUMBEROFATTEMPTS;

    Dcm_DecSecurityAttemptCounter();
    Dcm_DspServiceProcessingSts.ucSecSeedReq = DCM_FALSE;

    Dcm_StartTimer(DCM_SECURITY_TIMER, pSecLvlCfg->usSecDelayTime);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60081 */
    /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "Not a defect. This function is used to check requests" */
    Dcm_StartInformSecurityAttemptCounters();
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_RequestSeedOk                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process in case request seed function          **
**                        return E_OK                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pSecLvlCfg, isNewSecLevel                           **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DspInternal_RequestSeedOk(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  boolean isNewSecLevel)
{
  uint8 LucSeedVal;
  /* polyspace +1 CERT-C:EXP34-C [Justified:Low] "The NULL_PTR was checked in the function Dcm_DspInternal_CallGetSeedFnc " */
  uint32 LulSeedSize = pSecLvlCfg->ulSizeOfSeed;

  if (DCM_TRUE == isNewSecLevel)
  {
    /* @Trace: Dcm_SUD_API_60082 */
    /* Indicate the request seed was accepted */
    Dcm_DspServiceProcessingSts.ucSecSeedReq = DCM_TRUE;
  }

  /* @Trace: Dcm_SUD_API_60083 */
  /* Response length = sizeOfSeed + 1 (sub-function byte) */
  pMsgContext->resDataLen = LulSeedSize + DCM_ONE;
  pMsgContext->resData[DCM_ZERO] = pMsgContext->reqData[DCM_ZERO];

  for (uint32 LulIndex = DCM_ZERO; LulIndex < LulSeedSize; LulIndex++)
  {
    /* @Trace: Dcm_SUD_API_60084 Dcm_SUD_API_60085 */
    LucSeedVal = (DCM_TRUE == isNewSecLevel) ? Dcm_GaaSeed[LulIndex] : DCM_ZERO;
    pMsgContext->resData[DCM_ONE + LulIndex] = LucSeedVal;
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ProcessGetSeedFunc                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process for the return value of GetSeed()      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pSecLvlCfg, pMsgContext                   **
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
static FUNC(void, DCM_CODE) Dcm_DspInternal_ProcessGetSeedFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60088 */
  Std_ReturnType LddRetVal = E_OK;
  Dcm_DspServiceProcessingSts.ucSecSeedReqPending = DCM_FALSE;

  #if ((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || \
       (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
  /* If the tester sends a consecutive Request Seed,
   * the request is accepted and the same seed is returned. */
  if (DCM_FALSE == Dcm_DspServiceProcessingSts.ucSecSeedReq)
  #endif
  {
    #if (DCM_SECURITY_CRL_ENABLE == STD_ON)
    Dcm_GaaCRLLength = pMsgContext->reqDataLen - PLAINDATA - DCM_CERTIFICATE_SIGNATURE - 1U;
    #endif

    /* @Trace: Dcm_SUD_API_60086 */
    /* @Trace: SWS_Dcm_00324 SWS_Dcm_00862 */
    LddRetVal = Dcm_DspInternal_CallGetSeedFnc(
      OpStatus, pSecLvlCfg, pMsgContext->reqData, pErrorCode);
  }

  switch (LddRetVal)
  {
    case E_OK:
      /* @Trace: Dcm_SUD_API_60087 */
      Dcm_DspInternal_RequestSeedOk(pMsgContext, pSecLvlCfg, DCM_TRUE);
      break;

    case E_NOT_OK:
      /* @Trace: SWS_Dcm_00659 */
      /* @Trace: Dcm_SUD_API_60089 */
      /* Error Code is updated in function argument */
      break;

    case DCM_E_PENDING:
      /* @Trace: Dcm_SUD_API_60090 */
      Dcm_DspServiceProcessingSts.ucSecSeedReqPending = DCM_TRUE;
      break;

    default:
      /* @Trace: Dcm_SUD_API_60091 */
      *pErrorCode = DCM_E_GENERALREJECT;
      break;
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ProcessRequestSeed                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process for request seed sub-function          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, SecAccessType                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspInternal_ProcessRequestSeed(
  Dcm_MsgContextPtrType pMsgContext,
  uint8 SecAccessType)
{
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  /* SecurityLevel = (SecurityAccessType + 1) / 2 */
  Dcm_SecLevelType LddSecLevel = (SecAccessType + DCM_ONE) >> DCM_ONE;
  
  Dcm_SecurityLevConfigConstPtrType LpSecLvlCfg;
  LpSecLvlCfg = Dcm_GetSecurityLevelConfigByLevel(LddSecLevel);

  if (NULL_PTR == LpSecLvlCfg)
  {
    /* @Trace: SWS_Dcm_00321 */
    /* @Trace: Dcm_SUD_API_60092 */
    LddErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
  }
  /* Message length = Security Access Data Record + 1 (sub-function byte) */
  else
  if (pMsgContext->reqDataLen != (LpSecLvlCfg->ulSecurityADRSize + DCM_ONE))
  {
    /* @Trace: Dcm_SUD_API_60093 */
    LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60094 */
    /* Prepare for next sequence check */
    Dcm_GucSecurSequChk = SecAccessType + DCM_ONE;

    /* Get current security level */
    Dcm_SecLevelType LddCurrentSecLevel = DCM_SEC_LEV_LOCKED;
    (void) Dcm_GetSecurityLevel(&LddCurrentSecLevel);

    /* @Trace: SWS_Dcm_00323 */
    if (LddSecLevel == LddCurrentSecLevel)
    {
      /* @Trace: Dcm_SUD_API_60095 */
      /* Set the seed content to ZERO if the requested level is already active */
      Dcm_DspInternal_RequestSeedOk(pMsgContext, LpSecLvlCfg, DCM_FALSE);
    }
    else
    {
      #if ((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || \
           (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
      /* @Trace: Dcm_SUD_API_60096 */
      Std_ReturnType LddRetVal = E_OK;

      /* In case consecutive request seed was sent */
      if (DCM_TRUE == Dcm_DspServiceProcessingSts.ucSecSeedReq)
      {
        /* @Trace: Dcm_SUD_API_60097 */
        LddRetVal = Dcm_DspInternal_CheckContinuousReqSeed(
          LpSecLvlCfg, &LddErrorCode);
      }

      if (E_OK == LddRetVal)
      #endif
      {
        /* @Trace: Dcm_SUD_API_60098 */
        Dcm_DspInternal_ProcessGetSeedFunc(
          DCM_INITIAL, LpSecLvlCfg, pMsgContext, &LddErrorCode);
      }
    }
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_CallCompareKeyFnc                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get compareKey() function from security config      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pSecLvlCfg, pReqData                      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_CallCompareKeyFnc(
  Dcm_OpStatusType OpStatus,
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  Dcm_Uint8PtrType pReqData,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60099 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ((NULL_PTR != pSecLvlCfg) && (NULL_PTR != pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_60100 */
    *pErrorCode = DCM_POS_RESP;

    if ((USE_ASYNCH_FNC == pSecLvlCfg->ucSecurityUsePort) ||
        (USE_ASYNCH_CLIENT_SERVER == pSecLvlCfg->ucSecurityUsePort))
    {
      /* @Trace: Dcm_SUD_API_60102 */
      if (NULL_PTR != pSecLvlCfg->pCompareKeyAsyncFun)
      {
        /* @Trace: Dcm_SUD_API_60101 */
        LddRetVal = pSecLvlCfg->pCompareKeyAsyncFun(
          &pReqData[DCM_ONE], OpStatus, pErrorCode);
      }
    }

    if ((E_NOT_OK == LddRetVal) && (DCM_POS_RESP == *pErrorCode))
    {
      /* @Trace: Dcm_SUD_API_70002 */
      *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    }
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_CompareKeyOk                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process in case compareKey() return E_OK       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, pSecLvlCfg                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DspInternal_CompareKeyOk(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg)
{
  /* @Trace: SWS_Dcm_00325 */
  /* @Trace: Dcm_SUD_API_60103 */
  DslInternal_SetSecurityLevel(pSecLvlCfg->ddSecLevel);

  /* @Trace: SRS_Diag_04208 */
  /* @Trace: SWS_Dcm_01329 */
  (void) SchM_Switch_Dcm_DcmSecurityAccess(pSecLvlCfg->ddSecLevel);

  /* Update positive response */
  pMsgContext->resDataLen = DCM_ONE;
  pMsgContext->resData[DCM_ZERO] = pMsgContext->reqData[DCM_ZERO];
  
  /* @Trace: Dcm_SUD_API_60104 */
  /* With ES96590 and QZN04 standard, keep the attempt counter value */
  /* polyspace +4 MISRA2012:2.2 [Justified:Low] Justify with annotations */
  #if ((DCM_STANDARD_SUPPORT != DCM_ES96590_SUPPORT) && \
       (DCM_STANDARD_SUPPORT != DCM_QZN04_SUPPORT))
  Dcm_ResetSecurityAttemptCounter();
  Dcm_StartInformSecurityAttemptCounters();
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_CompareKeyFail                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process in case compareKey() return FAILED     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pSecLvlCfg                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DspInternal_CompareKeyFail(
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_01397 */
  Dcm_IncSecurityAttemptCounter();

  /* @Trace: SWS_Dcm_00660 */
  if (DCM_FALSE == Dcm_IsSecurityAttemptCounterExceeded())
  {
    /* @Trace: Dcm_SUD_API_60105 */
    *pErrorCode = DCM_E_INVALIDKEY;
  }
  else
  {
    /* @Trace: SWS_Dcm_01349 */
    /* @Trace: Dcm_SUD_API_60106 */
    *pErrorCode = DCM_E_EXCEEDNUMBEROFATTEMPTS;

    /* Start security timer */
    Dcm_StartTimer(DCM_SECURITY_TIMER, pSecLvlCfg->usSecDelayTime);

    /* @Trace: Dcm_SUD_API_60107 */
    /* With ES96590 and QZN04 standard, decrease the attempt counter value */
    #if ((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || \
         (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
    Dcm_DecSecurityAttemptCounter();
    #else
    Dcm_ResetSecurityAttemptCounter();
    #endif
  }
  /* polyspace +1 MISRA2012:2.2 [Justified:Low] Justify with annotations */
  Dcm_StartInformSecurityAttemptCounters();
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ProcessCompareKeyFunc               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process for the return value of CompareKey()   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pSecLvlCfg, pMsgContext                   **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DspInternal_ProcessCompareKeyFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_SecurityLevConfigConstPtrType pSecLvlCfg,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal;

  Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending = DCM_FALSE;

  /* @Trace: SWS_Dcm_00324 SWS_Dcm_00863 */
  LddRetVal = Dcm_DspInternal_CallCompareKeyFnc(
    OpStatus, pSecLvlCfg, pMsgContext->reqData, pErrorCode);

  switch (LddRetVal)
  {
    case E_OK:
      /* @Trace: Dcm_SUD_API_60108 */
      Dcm_DspServiceProcessingSts.ucSecSeedReq = DCM_FALSE;
      Dcm_DspInternal_CompareKeyOk(pMsgContext, pSecLvlCfg);
      break;

    case E_NOT_OK:
      /* @Trace: SWS_Dcm_01150 */
      /* @Trace: Dcm_SUD_API_60109 */
      /* Error Code is updated in function argument */
      Dcm_DspServiceProcessingSts.ucSecSeedReq = DCM_FALSE;
      break;

    case DCM_E_PENDING:
      /* @Trace: Dcm_SUD_API_60112 */
      Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending = DCM_TRUE;
      break;

    case DCM_E_COMPARE_KEY_FAILED:
      /* @Trace: Dcm_SUD_API_60111 */
      Dcm_DspServiceProcessingSts.ucSecSeedReq = DCM_FALSE;
      Dcm_DspInternal_CompareKeyFail(pSecLvlCfg, pErrorCode);
      break;

    default:
      /* @Trace: Dcm_SUD_API_60110 */
      *pErrorCode = DCM_E_GENERALREJECT;
      Dcm_DspServiceProcessingSts.ucSecSeedReq = DCM_FALSE;
      break;
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ProcessCompareKey                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process for compare key sub-function           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, SecAccessType                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspInternal_ProcessCompareKey(
  Dcm_MsgContextPtrType pMsgContext,
  uint8 SecAccessType)
{
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;
  Dcm_SecurityLevConfigConstPtrType LpSecLvlCfg;

  /* Get security configuration */
  LpSecLvlCfg = Dcm_GetSecurityLevelConfig();

  if (NULL_PTR == LpSecLvlCfg)
  {
    /* @Trace: Dcm_SUD_API_60115 */
    LddErrorCode = DCM_E_GENERALREJECT;
  }
  /* According to ISO 14229, check the message length if only request seed 
     is received first. Therefore if request seed is not received, sequence error 
     should be return and no need to check the validity of length
  */
  /* After RequestSeed is successful ,ucSecSeedReq  will be true */
  else if ((DCM_FALSE == Dcm_DspServiceProcessingSts.ucSecSeedReq) ||
    ((Dcm_GucSecurSequChk != DCM_ZERO) && (Dcm_GucSecurSequChk != SecAccessType)))
  {
    /* @Trace: SWS_Dcm_00863 */
    /* @Trace: Dcm_SUD_API_60113 */
    /* The tester must send request seed before compare key subfunction */
    /* The server do not allow one request seed - more compare key sequence */
    LddErrorCode = DCM_E_REQUESTSEQUENCEERROR;
  }
  else if (pMsgContext->reqDataLen != (LpSecLvlCfg->ulSizeOfKey + DCM_ONE))
  {
    /* @Trace: Dcm_SUD_API_60114 */
    LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60116 */
    Dcm_DspInternal_ProcessCompareKeyFunc(
      DCM_INITIAL, LpSecLvlCfg, pMsgContext, &LddErrorCode);
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_SecurityAccess_PendingOperation                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to process pending operation for      **
**                        security access service                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SecurityAccess_PendingOperation(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60117 */
  uint8 LucSecAccessType;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;
  Dcm_SecurityLevConfigConstPtrType LpSecLvlCfg = NULL_PTR;

  if ((DCM_TRUE == Dcm_DspServiceProcessingSts.ucSecSeedReqPending) ||
      (DCM_TRUE == Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending))
  {
    /* @Trace: Dcm_SUD_API_60118 */
    LpSecLvlCfg = Dcm_GetSecurityLevelConfig();
    LucSecAccessType = pMsgContext->reqData[DCM_ZERO] & DCM_SUBFUNCTION_MASK;

    if (DCM_ZERO != (LucSecAccessType & DCM_BIT0_AND_MASK))
    {
      /* @Trace: Dcm_SUD_API_60120 */
      Dcm_DspInternal_ProcessGetSeedFunc(
          DCM_PENDING, LpSecLvlCfg, pMsgContext, &LddErrorCode);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60119 */
      Dcm_DspInternal_ProcessCompareKeyFunc(
        DCM_PENDING, LpSecLvlCfg, pMsgContext, &LddErrorCode);
    }

    if ((DCM_FALSE == Dcm_DspServiceProcessingSts.ucSecSeedReqPending) &&
        (DCM_FALSE == Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending))
    {
      if (DCM_POS_RESP != LddErrorCode)
      {
        /* @Trace: Dcm_SUD_API_60121 */
        Dcm_InternalSetNegResponse(pMsgContext, LddErrorCode);
      }

      /* @Trace: Dcm_SUD_API_60122 */
      /* Send response immediately */
      Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_SecurityAccess_CancelOperation                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to process pending operation for      **
**                        security access service                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_SecurityAccess_CancelOperation(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60123 */
  uint8 LucSecAccessType;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;
  Dcm_SecurityLevConfigConstPtrType LpSecLvlCfg = NULL_PTR;

  if ((DCM_TRUE == Dcm_DspServiceProcessingSts.ucSecSeedReqPending) ||
      (DCM_TRUE == Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending))
  {
    LpSecLvlCfg = Dcm_GetSecurityLevelConfig();
    LucSecAccessType = pMsgContext->reqData[DCM_ZERO] & DCM_SUBFUNCTION_MASK;

    if (DCM_ZERO != (LucSecAccessType & DCM_BIT0_AND_MASK))
    {
      /* @Trace: Dcm_SUD_API_60125 */
      (void) Dcm_DspInternal_CallGetSeedFnc(
        DCM_CANCEL, LpSecLvlCfg, pMsgContext->reqData, &LddErrorCode);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60124 */
      (void) Dcm_DspInternal_CallCompareKeyFnc(
        DCM_CANCEL, LpSecLvlCfg, pMsgContext->reqData, &LddErrorCode);
    }

    Dcm_DspServiceProcessingSts.ucSecSeedReqPending = DCM_FALSE;
    Dcm_DspServiceProcessingSts.ucSecCompareKeyReqPending = DCM_FALSE;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmCommunicationControl                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function used to control the Communication     **
**                        mode.                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None.                                               **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Dcm_GucSubNetValue, Dcm_GucCommunicationModeType,   **
**                        Dcm_GaaCommControlConfig,                           **
**                        Dcm_GddNegRespError.                                **
**                        Function(s) invoked : Dcm_ExternalSetNegResponse,   **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04198 */
#if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmCommunicationControl(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST) subServiceCfg;
  Std_ReturnType requestResult = E_OK;

  /*****************************************************************************
   *                            ES95486 Specification                          *
   ****************************************************************************/
  #if(DCM_STANDARD_SUPPORT == DCM_ES95486_SUPPORT)
  /* @Trace: Dcm_SUD_API_60126 */
  /* 00 enableRxAndTx, 01 diableNormalMessageTransmission (resp), 
   * 02 diableNormalMessageTransmission (noResp), 03 disableRxAndTx */
  uint8 subRequestLength[DCM_LOCAL_NUM_OF_SUBREQ] = {2,1,1,2};

  /* 00: undefined, 01: normal, 02: nm, 03: nm and normal */
  uint8 supportedCommunicationType[DCM_LOCAL_NUM_OF_COMTYPE] = 
  {
    DCM_FALSE, DCM_TRUE, DCM_TRUE, DCM_TRUE
  };

  /* subnet number's range */
  struct
  {
    uint8 minSubNet;
    uint8 maxSubNet;
  } subNetRange = { 0, 0 };

  /*****************************************************************************
   *                            ES96590 Specification                          *
   ****************************************************************************/
  #elif ((DCM_STANDARD_SUPPORT == DCM_ES96590_SUPPORT) || \
    (DCM_STANDARD_SUPPORT == DCM_QZN04_SUPPORT))
  /* @Trace: Dcm_SUD_API_60137 */
  /* 00 enableRxAndTx , 01 enableRxAndDisable , 
   * 02 disableRxAndEnable, 03 disableRxAndTx */
  uint8 subRequestLength[DCM_LOCAL_NUM_OF_SUBREQ] = {2,2,2,2};

  /* 00: undefined, 01: normal, 02: nm, 03: nm and normal */
  uint8 supportedCommunicationType[DCM_LOCAL_NUM_OF_COMTYPE] = 
  {
    DCM_FALSE, DCM_TRUE, DCM_TRUE, DCM_TRUE
  };

  /* subnet number's range */
  struct {
    uint8 minSubNet;
    uint8 maxSubNet;
  } subNetRange = { 0, 0 };

  /*****************************************************************************
   *                            AUTOSAR Specification                          *
   ****************************************************************************/
  #elif (DCM_STANDARD_SUPPORT == DCM_ISO14229_SUPPORT)
  /* @Trace: Dcm_SUD_API_60141 */
  /* 00 enableRxAndTx , 01 enableRxAndDisable , 
   * 02 disableRxAndEnable, 03 disableRxAndTx */
  uint8 subRequestLength[DCM_LOCAL_NUM_OF_SUBREQ] = {2,2,2,2,4,4};

  /* 00: undefined, 01: normal, 02: nm, 03: nm and normal */
  uint8 supportedCommunicationType[DCM_LOCAL_NUM_OF_COMTYPE] = 
  {
    DCM_FALSE, DCM_TRUE, DCM_TRUE, DCM_TRUE
  };

  /* subnet number's range */
  struct {
    uint8 minSubNet;
    uint8 maxSubNet;
  } subNetRange = { 0x0, 0x0F };
  #else /*DCM_ES95486_02_SUPPORT, DCM_ES95486_50_SUPPORT*/
  /* @Trace: Dcm_SUD_API_60141 */
  /* 00 enableRxAndTx , 01 enableRxAndDisable , 
   * 02 disableRxAndEnable, 03 disableRxAndTx */
  uint8 subRequestLength[DCM_LOCAL_NUM_OF_SUBREQ] = {2,2,2,2};

  /* 00: undefined, 01: normal, 02: nm, 03: nm and normal */
  uint8 supportedCommunicationType[DCM_LOCAL_NUM_OF_COMTYPE] = 
  {
    DCM_FALSE, DCM_TRUE, DCM_TRUE, DCM_TRUE
  };

  /* subnet number's range */
  struct {
    uint8 minSubNet;
    uint8 maxSubNet;
  } subNetRange = { 0x0, 0x0F };
  #endif

  subServiceCfg = Dcm_GetSubServiceConfigPtr(pMsgContext);
  if (NULL_PTR == subServiceCfg)
  {
    /* @Trace: Dcm_SUD_API_60142 */
    /* Never be reached, but this code is added for MISRA-rules */
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
  /* External diagnostic subservice processing  */
  else if (NULL_PTR != subServiceCfg->pSubServiceFnc)
  {
    if ( (DCM_INITIAL == OpStatus) && (pMsgContext->reqDataLen > 0U))
    {
      /* @Trace: SWS_Dcm_00764 */
      /* @Trace: Dcm_SUD_API_60143 */
      /* The pointer in pMsgContext shall point behind the SubFunction */
      pMsgContext->reqData = &pMsgContext->reqData[1U];
      pMsgContext->reqDataLen--;
    }

    /* @Trace: Dcm_SUD_API_60144 */
    requestResult = subServiceCfg->pSubServiceFnc(
      OpStatus, pMsgContext, pErrorCode);
  }
  else
  {
    /* Dcm-internal timeout handling */
    if (subServiceCfg->ucSubServiceId >= DCM_LOCAL_NUM_OF_SUBREQ)
    {
      /* @Trace: Dcm_SUD_API_60145 */
      /* Never be reached, but this code is added for MISRA-rules */
      Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
    }
    else if (subRequestLength[subServiceCfg->ucSubServiceId] != pMsgContext->reqDataLen)
    {
      /* @Trace: Dcm_SUD_API_60146 */
      Dcm_InternalSetNegResponse(pMsgContext, 
        DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60147 */
      Dcm_GucSubFunction = subServiceCfg->ucSubServiceId;
      /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "It depends on configuration."*/
      if (2U == subRequestLength[subServiceCfg->ucSubServiceId])
      {
        /* @Trace: Dcm_SUD_API_60127 */
        Dcm_GucSubNetValue = (uint8) \
          (((pMsgContext->reqData[1U]) & DCM_SIG_SIZE_MASK_VALUE) >> 0x04u);

        Dcm_GucCommunicationModeType = \
          ((pMsgContext->reqData[1U]) & DCM_SIG_BYTE_MASK_VALUE);
      }
      /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "It depends on configuration."*/
      #if (DCM_STANDARD_SUPPORT == DCM_ISO14229_SUPPORT)
      else
      {
        /* @Trace: Dcm_SUD_API_60128 */
        Dcm_GucCommunicationModeType = \
          ((pMsgContext->reqData[1U]) & DCM_SIG_BYTE_MASK_VALUE);

        Dcm_GucSubNodeId = \
          (((uint16)pMsgContext->reqData[2U] << 0x08u) | pMsgContext->reqData[3U]);
      }
      #else
      else
      {
        /* @Trace: Dcm_SUD_API_60129 */
        /* Length may be 1, and therefore pMsgContext->reqData[1U] 
         * is not defined(ES95486) */
        /* @Trace: SWS_ES95486_00001 SWS_ES95486_00002 */
        Dcm_GucSubNetValue = 0U;
        Dcm_GucCommunicationModeType = DCM_COMM_TYPE_NORMAL;
      }
      #endif

      if ( /* range and supported sub function check */
        (Dcm_GucCommunicationModeType >= DCM_LOCAL_NUM_OF_COMTYPE) ||
        (DCM_FALSE == supportedCommunicationType[Dcm_GucCommunicationModeType]))
      {
        /* @Trace: Dcm_SUD_API_60130 */
        Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      }
      /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] It depends on Configuration.*/
      else if (
        (Dcm_GucSubNetValue < subNetRange.minSubNet) ||
        (Dcm_GucSubNetValue > subNetRange.maxSubNet))
      {
        /* @Trace: Dcm_SUD_API_60131 */
        Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      }
      /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] It depends on Configuration.*/
      else
      {
        /* @Trace: Dcm_SUD_API_60132 */
        boolean searchResult = DCM_FALSE;

        #if (DCM_STANDARD_SUPPORT == DCM_ISO14229_SUPPORT)
        /* @Trace: SWS_Dcm_01077 SWS_Dcm_01079 */
        if ((Dcm_GucSubFunction == 0x04u) || (Dcm_GucSubFunction == 0x05u))
        {
          /* @Trace: Dcm_SUD_API_60133 */
          /* @Trace: SWS_Dcm_01078 SWS_Dcm_01080 */
          searchResult = Dcm_IsSubNodeIdSupported(Dcm_GucSubNodeId);
        }
        else
        #endif
        /* @Trace: SWS_Dcm_00512 SWS_Dcm_00785 */
        /* [ES95486 Annex. B] */
        /* polyspace +1 DEFECT:DEAD_CODE [Justified:Low] "According to the AUTOSAR SPEC SWS_Dcm_00785,SWS_Dcm_00786, this checking is needed. " */
        if ((0x0F == Dcm_GucSubNetValue) || (0U == Dcm_GucSubNetValue))
        {
          /* @Trace: Dcm_SUD_API_60134 */
          searchResult = DCM_TRUE;
        }
        else
        {
          /* @Trace: SWS_Dcm_00786 */
          /* @Trace: Dcm_SUD_API_60135 */
          uint8 channelIdx;
          
          /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "DCM_TOTAL_NUM_OF_SPECIFIC_CHANNEL is determined by configuration" */
          for(channelIdx = 0U; 
              channelIdx < DCM_TOTAL_NUM_OF_SPECIFIC_CHANNEL; 
              channelIdx++)
          /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "DCM_TOTAL_NUM_OF_SPECIFIC_CHANNEL is determined by configuration" */
          {
            /* @Trace: Dcm_SUD_API_60136 */
            Dcm_CommControlConfigConstPtrType pCommControlCfg = \
              &Dcm_GaaCommControlConfig[channelIdx];

            /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of ChannelUsed is determined by configuration" */
            if ((DCM_FALSE == pCommControlCfg->ChannelUsed)
                || (pCommControlCfg->SubNetNumber != Dcm_GucSubNetValue))
            {
              continue;
            }
            /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of ChannelUsed is determined by configuration" */

            /* @Trace: Dcm_SUD_API_60138 */
            searchResult = DCM_TRUE;
            break;
          }
        }

        /* polyspace +1 DEFECT:DEAD_CODE [Justified:Low] "According to the AUTOSAR SPEC SWS_Dcm_00785,SWS_Dcm_00786, this checking is needed. " */
        if (DCM_TRUE == searchResult)
        {
          /* @Trace: Dcm_SUD_API_60139 */
          pMsgContext->resDataLen = 1U;

           /* sub function number */
          pMsgContext->resData[0U] = pMsgContext->reqData[0U];
        }
        else
        {
          /* @Trace: Dcm_SUD_API_60140 */
          Dcm_InternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
        }
      }
    }

    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }

  /* TODO: return value shall be processed */
  return requestResult;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmEnableNormalMsgTransmission                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function used to enable normal message         **
**                        transmission.                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None.                                               **
**                                                                            **
** Remarks              : Global Variable(s) :Dcm_GddNegRespError,            **
**                        Dcm_GucSubNetValue,                                 **
**                        Dcm_GucCommunicationModeType                        **
**                        Function(s) invoked : Dcm_ExternalProcessingDone,   **
**                                              Dcm_ExternalSetNegResponse    **
**                                                                            **
*******************************************************************************/
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmEnableNormalMsgTransmission(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_ES95486_00003 */
  /* @Trace: Dcm_SUD_API_60148 */
  /* @Trace: SRS_ES95486_00E_00001 SRS_ES95486_00E_00002 SRS_ES95486_00E_00003 */
  Dcm_DspInternal_DcmEnableNormalMsgTransmission(pMsgContext);

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return E_OK;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmTesterPresent                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The DcmTesterPresent service is used to keep one or **
**                        multiple servers in a diagnostic session different  **
**                        than the defaultSession                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GddNegRespError,          **
**                        Dcm_GddNegRespError, Dcm_GaaSIdConfig,              **
**                                           Dcm_GaaSubServiceIdConfig        **
**                        Function(s) invoked :  None                         **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00251 SRS_Diag_04198 */
#if (DCM_DSP_TESTER_PRESENT_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmTesterPresent(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  P2CONST(Dcm_SubServiceIdConfigType, AUTOMATIC, DCM_APPL_CONST) subServiceCfg;
  Std_ReturnType requestResult = E_OK;

  subServiceCfg = Dcm_GetSubServiceConfigPtr(pMsgContext);
  if(NULL_PTR == subServiceCfg)
  {
    /* @Trace: Dcm_SUD_API_60149 */
    /* Never be reached, but this code is added for MISRA-rules */
    Dcm_InternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }
  /* External diagnostic subservice processing  */
  else if (NULL_PTR != subServiceCfg->pSubServiceFnc)
  {
    /* @Trace: Dcm_SUD_API_60150 */
    requestResult = subServiceCfg->pSubServiceFnc(OpStatus, 
      pMsgContext, pErrorCode);
  }
  /* Dcm-Internal diagnostic subservice processing  */
  else
  {
    /* Check for the validity of length */
    if(pMsgContext->reqDataLen != DCM_ONE)
    {
      /* @Trace: Dcm_SUD_API_60151 */
      Dcm_InternalSetNegResponse(pMsgContext, 
        DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60152 */
      pMsgContext->resDataLen = 1U;
      pMsgContext->resData[0U] = pMsgContext->reqData[0U];
    }

    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }

  return requestResult;
}
#endif /* (DCM_DSP_TESTER_PRESENT_SERVICE == STD_ON) */

/*******************************************************************************
** Function Name        : Dcm_DcmLinkControlService                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Link service is used to gain bus bandwidth     **
**                        for diagnostic purposes                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#if (DCM_LINK_CONTROL_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmLinkControlService(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  Dcm_SubServiceIdConfigConstPtrType LpSubServiceCfg;
  Dcm_NegativeResponseCodeType ErrorCode;

  LpSubServiceCfg = Dcm_GetSubServiceConfigPtr(pMsgContext);
  pErrorCode = &ErrorCode;
  *pErrorCode = DCM_POS_RESP;

  if(NULL_PTR == LpSubServiceCfg)
  {
    /* @Trace: Dcm_SUD_API_60153 */
    /* Never be reached, but this code is added for MISRA-rules */
    *pErrorCode = DCM_E_GENERALREJECT;
  }
  /* External diagnostic subservice processing  */
  else if (NULL_PTR != LpSubServiceCfg->pSubServiceFnc)
  {
    /* @Trace: Dcm_SUD_API_60155 */
    uint8 LucSubFunction = LpSubServiceCfg->ucSubServiceId;
    Dcm_MsgLenType LddReqDataLen = pMsgContext->reqDataLen;
    
    /* Message Format Check; if format is not correct, NRC13 is occurred */
    /* Request Data Length of Sub-Function 0x01 must be 2 */
    if ((LucSubFunction == DCM_LINK_CTRL_MODE_TRANSITION_WITH_FIXED_PARAMETER) && (LddReqDataLen != DCM_TWO))
    {
      /* @Trace: Dcm_SUD_API_60156 */
      *pErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    /* Message Format Check; if format is not correct, NRC13 is occurred */
    /* Request Data Length of Sub-Function 0x02 must be 4 */
    else if ((LucSubFunction == DCM_LINK_CTRL_MODE_TRANSITION_WITH_SPECIFIC_PARAMETER) && (LddReqDataLen != DCM_FOUR))
    {
      /* @Trace: Dcm_SUD_API_60157 */
      *pErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    /* Message Format Check; if format is not correct, NRC13 is occurred */
    /* Request Data Length of Sub-Function 0x03 must be 1 */
    else if ((LucSubFunction == DCM_LINK_CTRL_TRANSITION_BAUDRATE) && (LddReqDataLen != DCM_ONE))
    {
      /* @Trace: Dcm_SUD_API_60158 */
      *pErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    /* If request message have proper data format, Proceed External subservice */
    else
    {
      /* case : For sub-function 0x01, 0x02 */
      if ((LucSubFunction == DCM_LINK_CTRL_MODE_TRANSITION_WITH_FIXED_PARAMETER)
          || (LucSubFunction == DCM_LINK_CTRL_MODE_TRANSITION_WITH_SPECIFIC_PARAMETER))
      {
        /* @Trace: Dcm_SUD_API_60154 */
        LddRetVal = LpSubServiceCfg->pSubServiceFnc(
          OpStatus, pMsgContext, pErrorCode);

        Dcm_FlagSetBaudrateBeforeTransition = LddRetVal;
      }
      /* case : For sub-function 0x03 */
      else if (LucSubFunction == DCM_LINK_CTRL_TRANSITION_BAUDRATE)
      {
        if (Dcm_FlagSetBaudrateBeforeTransition == E_OK)
        {
          /* @Trace: Dcm_SUD_API_60792 */
          LddRetVal = LpSubServiceCfg->pSubServiceFnc(
            OpStatus, pMsgContext, pErrorCode);
        }
        /* NRC24 : Baudrate to transition is not set;                         */
        /*         sub-function 0x01, 0x02 is called before sub-function 0x03 */
        else
        {
          *pErrorCode = DCM_E_REQUESTSEQUENCEERROR;
        }
      }
      /* case : For other reserved subfunction; */
      /*        But never be reached            */
      else 
      {
        /* @Trace: Dcm_SUD_API_60793 */
        LddRetVal = LpSubServiceCfg->pSubServiceFnc(
          OpStatus, pMsgContext, pErrorCode);
      }
      
      if ((*pErrorCode == DCM_POS_RESP) && (LddRetVal == E_OK))
      {
        /* @Trace: Dcm_SUD_API_60159 */
        pMsgContext->resData[DCM_ZERO] = LucSubFunction;
        pMsgContext->resDataLen = DCM_ONE;
      }
      else if ((*pErrorCode == DCM_POS_RESP) && (LddRetVal != E_OK))
      {
        *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      }
      else {
        /* No Action */
      }
    }
  }
  /* Internal Linkcontrol subservice is not supported  */
  /* DcmDsdSubServiceFnc should be implemented by user */
  else
  {
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  if (*pErrorCode != DCM_POS_RESP)
  {
    Dcm_InternalSetNegResponse(pMsgContext, (*pErrorCode));
  }
  Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeF186                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the requested Dynamic DID value from the    **
**                        Application.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : dataIdentifier                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize, pErrorCode                     **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDymDefinedDIDInfoType, **
**                        Dcm_GaaDymMemDIDInfoType,                           **
**                        Dcm_GblResOnPeriodicIdStatus,                       **
**                        Dcm_GddOpStatus, Dcm_GucRMBAMemoryIdentifier,       **
**                        Dcm_GddNegRespError, Dcm_ServicePendingStatus,      **
**                        Dcm_GaaDidReadSignalData.                           **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
/* @Trace: SWS_Dcm_00085 */
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeF186(
  Dcm_OpStatusType OpStatus,
  uint16 DataIdentifier,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;
  Dcm_SesCtrlType LddSesLevel = DCM_DEFAULT_SESSION;

  if ((NULL_PTR != pDataOut) && (NULL_PTR != pDataSize))
  {
    /* @Trace: Dcm_SUD_API_60161 */
    /* Get the current session level */
    (void) Dcm_GetSesCtrlType(&LddSesLevel);

    /* Response only one byte */
    *pDataOut = LddSesLevel;
    *pDataSize = DCM_ONE;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60160 */
    LddRetVal = E_NOT_OK;
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(DataIdentifier);
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeF810                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the requested Dynamic DID value from the    **
**                        Application.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : dataIdentifier                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize, pErrorCode                     **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDymDefinedDIDInfoType, **
**                        Dcm_GaaDymMemDIDInfoType,                           **
**                        Dcm_GblResOnPeriodicIdStatus,                       **
**                        Dcm_GddOpStatus, Dcm_GucRMBAMemoryIdentifier,       **
**                        Dcm_GddNegRespError, Dcm_ServicePendingStatus,      **
**                        Dcm_GaaDidReadSignalData.                           **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
/* @Trace: SWS_Dcm_00085 */
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeF810(
  Dcm_OpStatusType OpStatus,
  uint16 DataIdentifier,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;
  uint8 LddObdProtocolId = DCM_PROTOCOLID_OBD_NONE;

  if ((NULL_PTR != pDataOut) && (NULL_PTR != pDataSize))
  {
    /* @Trace: Dcm_SUD_API_60161 */
    /* Get the current OBD Protocol ID */
    LddRetVal = Dcm_GetObdProtocolId(&LddObdProtocolId);

    /* Response only one byte */
    *pDataOut = LddObdProtocolId;
    *pDataSize = DCM_ONE;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60160 */
    LddRetVal = E_NOT_OK;
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(DataIdentifier);
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadSigTypeNvMBlock                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to read NvRam block           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucBockId                                           **
**                                                                            **
** InOut parameter      : pData                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GaaDidReadSignalData      **
**                                                                            **
**                        Function(s) invoked : NvM_ReadBlock                 **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadSigTypeNvMBlock(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) anOutBuffer)
{
  Std_ReturnType retVal = E_OK;
  NvM_RequestResultType RequestResult = NVM_REQ_PENDING;
  NvM_BlockIdType NvMBlockId = aCfgData->usDcmDspDataBlockIdRef;

  switch(anOpStatus)
  {
    case DCM_CANCEL:
      /* @Trace: SWS_Dcm_01048 */
      /* @Trace: Dcm_SUD_API_60162 */
      (void) NvM_CancelJobs(NvMBlockId);
      retVal = E_NOT_OK;
      break;

    case DCM_PENDING:
      /* @Trace: Dcm_SUD_API_60163 */
      retVal = NvM_GetErrorStatus(NvMBlockId, &RequestResult);

      if (E_OK == retVal)
      {
        switch(RequestResult)
        {
          case NVM_REQ_PENDING:
            /* @Trace: Dcm_SUD_API_60164 */
            retVal = DCM_E_PENDING;
            break;

          case NVM_REQ_OK:
            /* @Trace: Dcm_SUD_API_60165 */
            retVal = E_OK;
            break;

          default:
            /* @Trace: Dcm_SUD_API_60166 */
            retVal = E_NOT_OK;
            break;
        }
      }
      break;

    case DCM_INITIAL:
      /* @Trace: Dcm_SUD_API_60167 */
      /*Invoke NvM Api to get the data and check for return value */
      retVal = NvM_ReadBlock(NvMBlockId, (void*)anOutBuffer);

      if(retVal == E_OK)
      {
        /* @Trace: Dcm_SUD_API_60168 */
        retVal = DCM_E_PENDING;
      }
      break;

    default:
      /* @Trace: Dcm_SUD_API_60169 */
      retVal = E_NOT_OK;
      break;
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_WriteSigTypeNvMBlock                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to write NvRam block          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucBockId                                           **
**                                                                            **
** InOut parameter      : pData                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :  Dcm_GaaDidReadSignalData      **
**                                                                            **
**                        Function(s) invoked : NvM_ReadBlock                 **
**                                                                            **
*******************************************************************************/
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteSigTypeNvMBlock(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) anInputBuffer,
  Dcm_NegativeResponseCodeType *anOutNegRespCode)
{
  /* @Trace: Dcm_SUD_API_60170 */
  Std_ReturnType retVal = E_OK;
  NvM_RequestResultType RequestResult = NVM_REQ_OK;

  if ((NULL_PTR != aCfgData) && (NULL_PTR != anInputBuffer))
  {
    switch(anOpStatus)
    {
      case DCM_CANCEL:
        /* @Trace: SWS_Dcm_01048 */
        /* @Trace: Dcm_SUD_API_60173 */
        (void) NvM_CancelJobs(aCfgData->usDcmDspDataBlockIdRef);
        retVal = E_NOT_OK;
        break;

      case DCM_PENDING:
        /* @Trace: Dcm_SUD_API_60174 */
        retVal = NvM_GetErrorStatus(aCfgData->usDcmDspDataBlockIdRef, &RequestResult);

        if (E_OK == retVal)
        {
          switch(RequestResult)
          {
            case NVM_REQ_PENDING:
              /* @Trace: Dcm_SUD_API_60175 */
              retVal = DCM_E_PENDING;
              break;

            case NVM_REQ_OK:
              /* @Trace: Dcm_SUD_API_60176 */
              retVal = E_OK;
              break;

            default:
              /* @Trace: Dcm_SUD_API_60177 */
              retVal = E_NOT_OK;
              break;
          }
        }
        break;

      case DCM_INITIAL:
        /* @Trace: Dcm_SUD_API_60178 */
        /* Locking NvBlock from application */
        NvM_SetBlockLockStatus(aCfgData->usDcmDspDataBlockIdRef, DCM_FALSE);
        /* polyspace +2 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
        /* polyspace +1 CERT-C:EXP36-C [Justified:Low] "anInputBuffer depend on input type of NvM_WriteBlock. No Impact" */
        retVal = NvM_WriteBlock(aCfgData->usDcmDspDataBlockIdRef,(uint8*)anInputBuffer);

        if(retVal == E_OK)
        {
          /* @Trace: Dcm_SUD_API_60179 */
          retVal = DCM_E_PENDING;
        }
        break;

      default:
        /* @Trace: Dcm_SUD_API_60180 */
        retVal = E_NOT_OK;
        break;
    }

    /* Writing operation is successful or not */
    if (DCM_E_PENDING !=  retVal)
    {
      /* @Trace: Dcm_SUD_API_60171 */
      NvM_SetBlockLockStatus(aCfgData->usDcmDspDataBlockIdRef, DCM_TRUE);

      if (E_NOT_OK ==  retVal)
      {
        /* @Trace: SWS_Dcm_00541 */
        /* @Trace: Dcm_SUD_API_60172 */
        *anOutNegRespCode = DCM_E_GENERALPROGRAMMINGFAILURE;
      }
    }
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ConditionCheckRead                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to check the condition of data**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ConditionCheckRead(
  Dcm_OpStatusType OpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) pDataCfg,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode)
{
  Std_ReturnType RetVal = E_OK;

  if ((NULL_PTR != pDataCfg) && (NULL_PTR != pErrorCode))
  {
    switch (pDataCfg->ucDcmDspDataUsePort)
    {
      case USE_DATA_ASYNCH_FNC:
      case USE_DATA_ASYNCH_FNC_ERROR:
      case USE_DATA_ASYNCH_CLIENT_SERVER:
      case USE_DATA_ASYNCH_CLIENT_SERVER_ERROR:
        if (NULL_PTR != pDataCfg->pConditionCheckReadAsyncFun)
        {
          /* @Trace: Dcm_SUD_API_60182 */
          RetVal = pDataCfg->pConditionCheckReadAsyncFun(OpStatus, pErrorCode);
        }
        break;

      case USE_DATA_SYNCH_FNC:
      case USE_DATA_SYNCH_CLIENT_SERVER:
        if (NULL_PTR != pDataCfg->pConditionCheckReadSyncFun)
        {
          /* @Trace: Dcm_SUD_API_60183 */
          RetVal = pDataCfg->pConditionCheckReadSyncFun(pErrorCode);
        }
        break;

      default:
        /* @Trace: Dcm_SUD_API_60184 */
        /* No action in this case */
        break;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60181 */
    RetVal = E_NOT_OK;
  }

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadSigType                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to read data element          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadSigType(
  Dcm_OpStatusType anOpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) aCfgData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) anOutputBuffer)
{
  /* @Trace: Dcm_SUD_API_60185 */
  Std_ReturnType retVal = E_NOT_OK;
  Dcm_NegativeResponseCodeType LddNRC = DCM_POS_RESP;

  if(NULL_PTR != aCfgData)
  {
    /* if (OpStatus == DCM_CANCEL), This function shall return E_NOT_OK */
    if (
      (anOpStatus == DCM_INITIAL) ||
      (
        (
          (anOpStatus == DCM_CANCEL) ||
          (anOpStatus == DCM_PENDING)
        ) &&
        (
          (aCfgData->ucDcmDspDataUsePort == USE_BLOCK_ID) ||
          (aCfgData->ucDcmDspDataUsePort == USE_DATA_ASYNCH_FNC) ||
          (aCfgData->ucDcmDspDataUsePort == USE_DATA_ASYNCH_CLIENT_SERVER) ||
          (aCfgData->ucDcmDspDataUsePort == USE_DATA_ASYNCH_CLIENT_SERVER_ERROR)
        )
      )
    )
    {
      switch(aCfgData->ucDcmDspDataUsePort)
      {
        case USE_BLOCK_ID:
          /* @Trace: Dcm_SUD_API_60189 */
          /* Possibe opstatus : initial, pending, cancel */
          retVal = Dcm_DspInternal_ReadSigTypeNvMBlock(anOpStatus, 
            aCfgData, anOutputBuffer);
          break;

        /* Call the Api IoHwAb_Dcm_Read<EcuSignalName >() */
        case USE_ECU_SIGNAL:
          /* @Trace: Dcm_SUD_API_60190 */
          retVal = Dcm_CfgInternal_ReadSigTypeEcuSignal(aCfgData,
            (void*)anOutputBuffer);
          break;

        case USE_DATA_ASYNCH_CLIENT_SERVER_ERROR:
        case USE_DATA_ASYNCH_FNC_ERROR:
          if (NULL_PTR != aCfgData->pReadDataAsyncErrorFun)
          {
            /* @Trace: Dcm_SUD_API_60191 */
            /* polyspace +2 CERT-C:EXP36-C [Justified:Low] "anOutputBuffer depend on configuration of pReadDataAsyncErrorFun. No Impact" */
            retVal = aCfgData->pReadDataAsyncErrorFun(anOpStatus, 
              anOutputBuffer, &LddNRC);
          }
          break;

        case USE_DATA_ASYNCH_CLIENT_SERVER:
        case USE_DATA_ASYNCH_FNC:
         /* possibe opstatus : initial, pending, cancel */
          if (NULL_PTR != aCfgData->pReadDataAsyncFun)
          {
            /* @Trace: Dcm_SUD_API_60192 */
            /* polyspace +1 CERT-C:EXP36-C [Justified:Low] "anOutputBuffer depend on configuration of pReadDataAsyncFun. No Impact" */
            retVal = aCfgData->pReadDataAsyncFun(anOpStatus, anOutputBuffer);
          }
          break;

        case USE_DATA_SYNCH_CLIENT_SERVER:
        case USE_DATA_SYNCH_FNC:
          if (NULL_PTR != aCfgData->pReadDataSyncFun)
          {
            /* @Trace: Dcm_SUD_API_60193 */
            /* polyspace +1 CERT-C:EXP36-C [Justified:Low] "anOutputBuffer depend on configuration of pReadDataSyncFun. No Impact" */
            retVal = aCfgData->pReadDataSyncFun(anOutputBuffer);
          }
          break;

        case USE_DATA_SENDER_RECEIVER_AS_SERVICE:
        case USE_DATA_SENDER_RECEIVER:
          /* @Trace: Dcm_SUD_API_60194 */
          retVal = Dcm_CfgInternal_ReadSigTypeSenderReceiver(aCfgData, 
            (void*)anOutputBuffer);
          break;

        default:
          /* @Trace: Dcm_SUD_API_60186 */
          /* No action in this case */
          break;
      }
    }
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeDidRange                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to read did range             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : dataIdentifier, OpStatus                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize, pErrorCode                     **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
*******************************************************************************/
#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeDidRange(
  Dcm_OpStatusType OpStatus,
  uint16 DataIdentifier,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode)
{
  Std_ReturnType retVal = E_NOT_OK;
  P2VAR(Dcm_DIDRangeConfig, AUTOMATIC, DCM_APPL_DATA) pDIDRangeConfig = NULL_PTR;
  uint16 LusDIDIndex = DCM_ZERO;
  uint16 LusDataSize = DCM_ZERO;
  boolean LblDIDRange = DCM_FALSE;

  /* Get index of DID, no need to check returned value */
  (void) Dcm_DspDidSearch(DataIdentifier, &LusDIDIndex, &LblDIDRange);

  pDIDRangeConfig = Dcm_CfgInternal_GetDidRangeConfig(LusDIDIndex);

  if ((NULL_PTR == pDIDRangeConfig) || (NULL_PTR == pDataOut))
  {
    /* @Trace: Dcm_SUD_API_60195 */
    retVal = E_NOT_OK;
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60196 */
    *pErrorCode = DCM_POS_RESP;

    if (NULL_PTR != pDIDRangeConfig->pReadDidDataFun)
    {
      /* @Trace: Dcm_SUD_API_60198 */
      retVal = pDIDRangeConfig->pReadDidDataFun(
        DataIdentifier, pDataOut, OpStatus, &LusDataSize, pErrorCode);
      
      if (E_OK == retVal)
      {
        /* @Trace: Dcm_SUD_API_60199 */
        *pDataSize = LusDataSize;
      }
      else if (DCM_E_PENDING == retVal)
      {
        /* @Trace: Dcm_SUD_API_60200 */
        /* Set response pending flag to True */
        DCM_SET_RDATA_PENDING_STATUS(DCM_TRUE);
      }
      else
      {
        /* @Trace: Dcm_SUD_API_60201 */
        retVal = E_NOT_OK;
        *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      }
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60197 */
      *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    }
  }

  /* if OpStatus is DCM_CANCEL, return value shall be ignored */
  if (DCM_CANCEL == OpStatus)
  {
    /* @Trace: Dcm_SUD_API_60202 */
    retVal = E_NOT_OK;
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadSigTypeMemory                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to read did (memory)          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucDataType                                         **
**                                                                            **
** InOut parameter      : pData                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) && \
    (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadSigTypeMemory(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  Dcm_NegativeResponseCodeType *pErrorCode)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  Dcm_ReturnReadMemoryType LddReadMemRetVal;

  *pErrorCode = DCM_POS_RESP;

  /* Invoke callout Dcm_ReadMemory */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "the function Dcm_ReadMemory has return 4 values.
   So, Dcm_DspInternal_ReadSigTypeMemory depend on returned value of function Dcm_ReadMemory." */
  LddReadMemRetVal = Dcm_ReadMemory(
    OpStatus, MemoryIdentifier, 
    MemoryAddress, MemorySize, pDataOut, pErrorCode);

  if (LddReadMemRetVal == DCM_READ_OK)
  {
    /* @Trace: Dcm_SUD_API_60203 */
    LddRetVal = E_OK;
  }
  else if (LddReadMemRetVal == DCM_READ_PENDING)
  {
    /* @Trace: Dcm_SUD_API_60204 */
    LddRetVal = DCM_E_PENDING;
  }
  else if (LddReadMemRetVal == DCM_READ_FORCE_RCRRP)
  {
    /* @Trace: Dcm_SUD_API_60206 */
    /* Update Dcm_GusMaxNoOfForceRespPend */
    Dcm_GusMaxNoOfForceRespPend++;

    /* Check if Dcm_GusMaxNoOfForceRespPend reaches configured limit */
    if (DCM_FALSE == Dcm_ChkNumRespPend(DCM_READ_MEMORY_SID, 
      Dcm_GusMaxNoOfForceRespPend))
    {
      /* @Trace: Dcm_SUD_API_60208 */
      Dcm_GusMaxNoOfForceRespPend = DCM_ZERO;

      /* Invoke callout Dcm_ReadMemory with OpStatus DCM_CANCEL */
      (void) Dcm_ReadMemory(
        DCM_CANCEL, MemoryIdentifier, 
        MemoryAddress, MemorySize, pDataOut, pErrorCode);

      *pErrorCode = DCM_E_GENERALREJECT;
      LddRetVal = E_NOT_OK;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60207 */
      *pErrorCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
      LddRetVal = DCM_E_FORCE_RCRRP;
    }
  }
  else /* DCM_READ_FAILED */
  {
    /* @Trace: Dcm_SUD_API_60205 */
    *pErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
    LddRetVal = E_NOT_OK;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "the function Dcm_ReadMemory has return 4 values.
   So, Dcm_DspInternal_ReadSigTypeMemory depend on returned value of function Dcm_ReadMemory." */

  if (OpStatus == DCM_CANCEL)
  {
    /* @Trace: Dcm_SUD_API_60209 */
    LddRetVal = E_NOT_OK;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_GetSizeOfDidSignal                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to get size of data element   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_GetSizeOfDidSignal(
  Dcm_OpStatusType OpStatus,
  P2CONST(Dcm_DcmDspDataconfig, AUTOMATIC, DCM_APPL_CONST) pDataCfg,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) pSignalSize)
{
  /* @Trace: Dcm_SUD_API_60210 */
  Std_ReturnType retVal = E_NOT_OK;

  /* polyspace +1 MISRA-C3:10.1 [Justified:Low] Justify with annotations */
  if (pDataCfg && pSignalSize)
  {
    /* @Trace: Dcm_SUD_API_60211 */
    *pSignalSize = 0U;

    switch (pDataCfg->ucDcmDspDataUsePort)
    {
      case USE_DATA_ASYNCH_FNC:
      case USE_DATA_ASYNCH_FNC_ERROR:
      case USE_DATA_ASYNCH_CLIENT_SERVER:
      case USE_DATA_ASYNCH_CLIENT_SERVER_ERROR:
        if ((pDataCfg->ucDcmDspDataType == DCM_DATA_TYPE_UINT8_DYN) &&
            (pDataCfg->pReadDataLengthAsyncFun != NULL_PTR))
        {
          /* @Trace: Dcm_SUD_API_60213 */
          retVal = pDataCfg->pReadDataLengthAsyncFun(OpStatus, pSignalSize);
        }
        else
        {
          /* @Trace: Dcm_SUD_API_60212 */
          *pSignalSize = pDataCfg->usDcmDspDataByteSize;
          retVal = E_OK;
        }
        break;

      case USE_DATA_SYNCH_FNC:
      case USE_DATA_SYNCH_CLIENT_SERVER:
        if ((pDataCfg->ucDcmDspDataType == DCM_DATA_TYPE_UINT8_DYN) &&
            (pDataCfg->pReadDataLengthSyncFun != NULL_PTR))
        {
          /* @Trace: Dcm_SUD_API_60215 */
          retVal = pDataCfg->pReadDataLengthSyncFun(pSignalSize);
        }
        else
        {
          /* @Trace: Dcm_SUD_API_60214 */
          *pSignalSize = pDataCfg->usDcmDspDataByteSize;
          retVal = E_OK;
        }
        break;

       default:
         /* @Trace: Dcm_SUD_API_60216 */
        *pSignalSize = pDataCfg->usDcmDspDataByteSize;
        retVal = E_OK;
        break;
    }
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_GetDidInfo                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to get size of data element   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LpDataInfo                                          **
**                                                                            **
** InOut parameter      : LpSize                                              **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
*******************************************************************************/
#if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_GetDidInfo(
  uint16 aDidindex,
  CONST(boolean, DCM_CONST) aCfgDidRangePresent,
  P2CONST(Dcm_DIDInfoType, AUTOMATIC, DCM_APPL_CONST) *aCfgDidInfo)
{
  /* @Trace: Dcm_SUD_API_60218 */
  Std_ReturnType retVal = E_NOT_OK;

  *aCfgDidInfo = NULL_PTR;

  if (DCM_FALSE == aCfgDidRangePresent)
  {
    if (aDidindex < DCM_NUM_OF_DIDPARACONFIG)
    {
      if(Dcm_GaaDIDParaConfig[aDidindex].blDspDidUsed == DCM_TRUE)
      {
        /* @Trace: Dcm_SUD_API_60219 */
        *aCfgDidInfo = Dcm_GaaDIDParaConfig[aDidindex].pDidInfo;
        retVal = E_OK;
      }
    }
  }
  else
  {
    #if (DCM_NUM_OF_DCMDSPDIDRANGECONFIG != DCM_ZERO)
    /* @Trace: Dcm_SUD_API_60217 */
    P2VAR(Dcm_DIDRangeConfig, AUTOMATIC, DCM_APPL_DATA) pDIDRangeConfig;

    pDIDRangeConfig = Dcm_CfgInternal_GetDidRangeConfig(aDidindex);

    /* DidRange is configured correctly */
    if (NULL_PTR != pDIDRangeConfig)
    {
      /* @Trace: Dcm_SUD_API_60220 */
      *aCfgDidInfo = pDIDRangeConfig->pDidInfo;
      retVal = E_OK;
    }
    #endif
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_GetDidConfigIndex                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function is used to get the Index of  **
**                        DID whenever invoked by other functions             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : dataId                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pCfgIndex                                           **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON) || \
   (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON) || \
   (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
FUNC(boolean, DCM_CODE) Dcm_GetDidConfigIndex(
  uint16 dataId,
  Dcm_Uint16PtrType pCfgIndex)
{
  /* @Trace: Dcm_SUD_API_60225 */
  uint16 LusIdx;
  boolean LblRetVal = DCM_FALSE;

  for (LusIdx = DCM_ZERO; LusIdx < DCM_NUM_OF_DIDPARACONFIG; LusIdx++)
  {
    if (dataId == Dcm_GaaDIDParaConfig[LusIdx].usDcmDspDidIdentifier)
    {
      /* @Trace: Dcm_SUD_API_60223 */
      *pCfgIndex = LusIdx;
      LblRetVal = DCM_TRUE;
      break;
    }
  }

  return LblRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_ResetSignalOpStatus                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Reset the operation status of did signal            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : didIndex                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if ((DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_ResetSignalOpStatus(
  uint16 didIndex)
{
  Dcm_DidParaConfigConstPtrType LpDidCfg;
  LpDidCfg = Dcm_CfgInternal_GetDidConfig(didIndex);

  if (NULL_PTR != LpDidCfg)
  {
    /* @Trace: Dcm_SUD_API_60226 */
    uint8 LucIndex;
    uint8 LucNumOfSignal = LpDidCfg->ucDcmDspSignalCount;

    for (LucIndex = DCM_ZERO; LucIndex < LucNumOfSignal; LucIndex++)
    {
      /* @Trace: Dcm_SUD_API_60228 */
      /* Reset signal status to initial */
      LpDidCfg->pDcmDspSignal[LucIndex].ucSignalOpStatus = DCM_OPSTATUS_INITIAL;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60227 */
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM);
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmReadScalingDataByIdentifier                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for UDS 0x24 service          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LblRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadScalingDataByIdentifier(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60230 */
  uint16 LusDidIndex = DCM_ZERO;
  Std_ReturnType LddRetVal = E_OK;
  
  Dcm_NegativeResponseCodeType LddErrorCode;
  LddErrorCode = Dcm_ReadScalingInfo_ValidateRequest(pMsgContext, &LusDidIndex);

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60229 */
    /* Update global variables */
    Dcm_GusDIDIndexVal = LusDidIndex;

    /* Clear response message length */
    pMsgContext->resDataLen = DCM_ZERO;

    /* @Trace: SWS_Dcm_00394 */
    (void) Dcm_ReadScalingInfo_InternalProcess(
      DCM_INITIAL, pMsgContext, &LddErrorCode);
  }

  /* Determine if finish processing and update response */
  Dcm_ReadScalingInfo_UpdateResponse(LusDidIndex, pMsgContext, LddErrorCode);

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ReadScalingInfo_ValidateRequest                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate parameter in request message of UDS 0x24   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDidIndex                                           **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_ReadScalingInfo_ValidateRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint16PtrType pDidIndex)
{
  uint16 LusDataId = DCM_ZERO;
  uint16 LusDidIndex = DCM_ZERO;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  /* Check request length */
  if (DCM_TWO == pMsgContext->reqDataLen)
  {
    /* Get did from the request buffer */
    LusDataId = Dcm_RequestParameterToUint16(DCM_TWO, pMsgContext->reqData);

    /* Get index in did configuration */
    if (DCM_TRUE == Dcm_GetDidConfigIndex(LusDataId, &LusDidIndex))
    {
      /* @Trace: Dcm_SUD_API_60233 */
      /* Did Range feature cannot be applied for UDS 0x24 service */
      LddErrorCode = Dcm_DspValidateReadDid(LusDidIndex, DCM_FALSE);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60232 */
      LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }

    if (DCM_POS_RESP == LddErrorCode)
    {
      /* @Trace: Dcm_SUD_API_60234 */
      *pDidIndex = LusDidIndex;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60231 */
    LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_ReadScalingInfo_CallDataFunc                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call configured function to get scaling info size   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pScalingInfo, pDataCfg                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LblRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_ReadScalingInfo_CallDataFunc(
  Dcm_OpStatusType OpStatus,
  Dcm_Uint8PtrType pScalingInfo,
  Dcm_DataConfigConstPtrType pDataCfg,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60235 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ((NULL_PTR != pDataCfg) && (NULL_PTR != pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_60236 */
    *pErrorCode = DCM_POS_RESP;

    switch (pDataCfg->ucDcmDspDataUsePort)
    {
      case USE_DATA_SYNCH_FNC:
      case USE_DATA_SYNCH_CLIENT_SERVER:
        if (NULL_PTR != pDataCfg->pGetScalingInformationSyncFun)
        {
          /* @Trace: Dcm_SUD_API_60238 */
          LddRetVal = pDataCfg->pGetScalingInformationSyncFun(
            pScalingInfo, pErrorCode);
        }
        break;

      case USE_DATA_ASYNCH_FNC:
      case USE_DATA_ASYNCH_FNC_ERROR:
      case USE_DATA_ASYNCH_CLIENT_SERVER:
      case USE_DATA_ASYNCH_CLIENT_SERVER_ERROR:
        if (NULL_PTR != pDataCfg->pGetScalingInformationAsyncFun)
        {
          /* @Trace: Dcm_SUD_API_60240 */
          LddRetVal = pDataCfg->pGetScalingInformationAsyncFun(
            OpStatus, pScalingInfo, pErrorCode);
        }
        break;

      default:
        /* @Trace: Dcm_SUD_API_60242 */
        /* No action in this case */
        break;
    }

    /* @Trace: SWS_Dcm_00271 */
    if ((E_NOT_OK == LddRetVal) && (DCM_POS_RESP == *pErrorCode))
    {
      /* @Trace: Dcm_SUD_API_60241 */
      *pErrorCode = DCM_E_GENERALREJECT;
    }
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ReadScalingInfo_DataIfProcess                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Process to get scaling info from all signal of did  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pDidConfig                                **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LblRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_ReadScalingInfo_DataIfProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DidParaConfigConstPtrType pDidConfig,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;
  uint8 LusSignalIndex = DCM_ZERO;
  uint8 LusNumOfSignal = pDidConfig->ucDcmDspSignalCount;

  uint32 LulTotalScalingSize = DCM_ZERO;
  uint32 LulMaxScalingSize = pMsgContext->resMaxDataLen - DCM_TWO;
  Dcm_Uint8PtrType LpScalingBuffer = &pMsgContext->resData[DCM_TWO];

  /* Check if the did have configured signal or not */
  if ((NULL_PTR != pDidConfig->pDcmDspSignal) && (DCM_ZERO != LusNumOfSignal))
  {
    while ((LusSignalIndex < LusNumOfSignal) && (E_OK == LddRetVal))
    {
      /* @Trace: Dcm_SUD_API_60248 */
      /* Get the signal configuration */
      Dcm_DidSignalConfigPtrType LpSignalCfg;
      LpSignalCfg = &pDidConfig->pDcmDspSignal[LusSignalIndex];

      /* Get the data element configuration */
      uint32 LulCurrentScalingSize = DCM_ZERO;
      Dcm_DataConfigConstPtrType LpDataCfg = LpSignalCfg->pDataConfig;

      /* Check whether data info is configured */
      if (NULL_PTR != LpDataCfg->pDataInfo)
      {
        /* @Trace: Dcm_SUD_API_60249 */
        /* Pointer to response message buffer */
        LpScalingBuffer = &LpScalingBuffer[LulTotalScalingSize];

        /* Get scaling size of this signal */
        LulCurrentScalingSize = LpDataCfg->pDataInfo->ulDataScalingInfoSize;
      }

      /* Check whether the signal is processed */
      if ((DCM_ZERO != LulCurrentScalingSize) &&
          (DCM_OPSTATUS_COMPLETE != LpSignalCfg->ucSignalOpStatus))
      {
        /* @Trace: Dcm_SUD_API_60251 */
        /* Add scaling size to total size */
        LulTotalScalingSize += LulCurrentScalingSize;

        /* Check whether the buffer is overflow */
        if (LulTotalScalingSize < LulMaxScalingSize)
        {
          /* @Trace: Dcm_SUD_API_60247 */
          LddRetVal = Dcm_ReadScalingInfo_CallDataFunc(
            OpStatus, LpScalingBuffer, LpDataCfg, pErrorCode);
        }
        else
        {
          /* @Trace: Dcm_SUD_API_60250 */
          LddRetVal = E_NOT_OK;
          *pErrorCode = DCM_E_GENERALREJECT;
        }

        if (DCM_CANCEL != OpStatus)
        {
          switch (LddRetVal)
          {
            case E_OK:
              /* @Trace: Dcm_SUD_API_60252 */
              pMsgContext->resDataLen += LulCurrentScalingSize;
              LpSignalCfg->ucSignalOpStatus = DCM_OPSTATUS_COMPLETE;
              break;

            case E_NOT_OK:
              /* @Trace: Dcm_SUD_API_60253 */
              /* Error code is updated in pErrorCode argument */
              break;

            case DCM_E_PENDING:
              /* @Trace: Dcm_SUD_API_60244 */
              LpSignalCfg->ucSignalOpStatus = DCM_OPSTATUS_PENDING;
              Dcm_DspServiceProcessingSts.ucReadScalingDataPending = DCM_TRUE;
              break;

            default:
              /* @Trace: Dcm_SUD_API_60245 */
              LddRetVal = E_NOT_OK;
              *pErrorCode = DCM_E_GENERALREJECT;
              break;
          }
        }
      }      

      /* Next signal */
      LusSignalIndex++;
    }

    /* After traverse all signal, if no any scaling size is configured,
     * A request of out range error code will be sent. */
    if (DCM_ZERO == LulTotalScalingSize)
    {
      /* @Trace: Dcm_SUD_API_60246 */
      LddRetVal = E_NOT_OK;
      *pErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60243 */
    LddRetVal = E_NOT_OK;
    *pErrorCode = DCM_E_GENERALREJECT;
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ReadScalingInfo_InternalProcess                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal process function for UDS 0x24 service      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LblRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_ReadScalingInfo_InternalProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  Dcm_DidParaConfigConstPtrType LpDidConfig;

  /* Reset the pending operation flag */
  Dcm_DspServiceProcessingSts.ucReadScalingDataPending = DCM_FALSE;

  /* Get the did configuration */
  LpDidConfig = Dcm_CfgInternal_GetDidConfig(Dcm_GusDIDIndexVal);
  
  if (NULL_PTR != LpDidConfig)
  {
    /* Only did that using data element interface may have scaling information */
    if (USE_DATA_ELEMENT_SPECIFIC_INTERFACES == LpDidConfig->ucDcmDspDidUsePort)
    {
      /* @Trace: Dcm_SUD_API_60255 */
      LddRetVal = Dcm_ReadScalingInfo_DataIfProcess(
        OpStatus, pMsgContext, LpDidConfig, pErrorCode);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60256 */
      *pErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60254 */
    *pErrorCode = DCM_E_GENERALREJECT;
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ReadScalingInfo_UpdateResponse                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Determine if request is finished and update response**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : didIndex, errorCode                                 **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_ReadScalingInfo_UpdateResponse(
  uint16 didIndex,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode)
{
  /* @Trace: Dcm_SUD_API_60257 */
  if (DCM_FALSE == Dcm_DspServiceProcessingSts.ucReadScalingDataPending)
  {
    if (DCM_POS_RESP != errorCode)
    {
      /* @Trace: Dcm_SUD_API_60258 */
      Dcm_InternalSetNegResponse(pMsgContext, errorCode);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60259 */
      pMsgContext->resDataLen += DCM_TWO;
      Dcm_MemCopy(pMsgContext->resData, pMsgContext->reqData, DCM_TWO);
    }

    Dcm_ResetSignalOpStatus(didIndex);
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
}

/*******************************************************************************
** Function Name        : Dcm_ReadScalingInfo_CancelOperation                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Execute cancel operation for UDS 0x24 service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_ReadScalingInfo_CancelOperation(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60261 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if (DCM_TRUE == Dcm_DspServiceProcessingSts.ucReadScalingDataPending)
  {
    /* @Trace: Dcm_SUD_API_60260 */
    (void) Dcm_ReadScalingInfo_InternalProcess(
      DCM_CANCEL, pMsgContext, &LddErrorCode);

    Dcm_ResetSignalOpStatus(Dcm_GusDIDIndexVal);
    Dcm_DspServiceProcessingSts.ucReadScalingDataPending = DCM_FALSE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_ReadScalingInfo_PendingOperation                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Execute pending operation for UDS 0x24 service      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_ReadScalingInfo_PendingOperation(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60262 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if (DCM_TRUE == Dcm_DspServiceProcessingSts.ucReadScalingDataPending)
  {
    /* @Trace: Dcm_SUD_API_60263 */
    (void) Dcm_ReadScalingInfo_InternalProcess(
      DCM_PENDING, pMsgContext, &LddErrorCode);

    Dcm_ReadScalingInfo_UpdateResponse(
      Dcm_GusDIDIndexVal, pMsgContext, LddErrorCode);
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmDynamicallyDefineDataIdentifier              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main processing function for UDS 0x2C service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04121 */
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmDynamicallyDefineDataIdentifier(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_00259 */
  /* The UDS 0x2A service is implemented internally in Dcm module */
  Std_ReturnType LddRetVal = E_OK;

  uint8 LucDefType = pMsgContext->reqData[DCM_ZERO];
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  switch (LucDefType)
  {
    case DCM_DEFINE_DDDID_BY_DATAID:
      /* @Trace: SWS_Dcm_00646 */
      /* @Trace: Dcm_SUD_API_60264 */
      LddErrorCode = Dcm_DynDid_DefineByDid(pMsgContext);
      break;

    case DCM_DEFINE_DDDID_BY_MEMORY:
      /* @Trace: SWS_Dcm_00646 */
      /* @Trace: Dcm_SUD_API_60265 */
      LddErrorCode = Dcm_DynDid_DefineByMemory(pMsgContext);
      break;

    case DCM_CLEAR_DEFINED_DDDID:
      /* @Trace: SWS_Dcm_00647 */
      /* @Trace: Dcm_SUD_API_60266 */
      LddErrorCode = Dcm_DynDid_ClearDefinedDid(pMsgContext);
      break;

    default:
      /* @Trace: Dcm_SUD_API_60267 */
      LddErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
      break;
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60268 */
    Dcm_DynDid_UpdatePosResp(pMsgContext);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60269 */
    Dcm_InternalSetNegResponse(pMsgContext, LddErrorCode);
  }

  Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_InitData                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Init the data of UDS 0x2C service                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pConfig                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DynDid_InitData(
  Dcm_ConfigConstPtrType pConfig)
{
  /* @Trace: Dcm_SUD_API_60270 */
  /* In case the DCM_DDDID_STORAGE is configured as STD_ON,
   * The data of DDDID will be restored at the power up with NvM_ReadAll() */
  #if (DCM_DDDID_STORAGE == STD_OFF)
  uint16 LusIndex;

  /* @Trace: SWS_Dcm_00866 SWS_Dcm_00867 */
  for (LusIndex = DCM_ZERO; LusIndex < DCM_TOTAL_NUM_OF_DYN_DID; LusIndex++)
  {
    /* @Trace: Dcm_SUD_API_60271 */
    Dcm_DynDid_ClearOneDefinedDid(LusIndex);
  }
  #endif

  DCM_UNUSED(pConfig);
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_GetConfigIndex                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the dynamically define did configuration index  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : dataId                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pCfgIndex                                           **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_DynDid_GetConfigIndex(
  uint16 dataId,
  Dcm_Uint16PtrType pCfgIndex)
{
  /* @Trace: Dcm_SUD_API_60274 */
  uint16 LusIdx;
  boolean LblRetVal = DCM_FALSE;

  for (LusIdx = DCM_ZERO; LusIdx < DCM_TOTAL_NUM_OF_DYN_DID; LusIdx++)
  {
    if (dataId == Dcm_GaaDynDidInfoConfig[LusIdx].usDynDid)
    {
      /* @Trace: Dcm_SUD_API_60273 */
      *pCfgIndex = LusIdx;
      LblRetVal = DCM_TRUE;
      break;
    }
  }

  return LblRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_UpdatePosResp                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Update positive response for UDS 0x2C service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DynDid_UpdatePosResp(
  Dcm_MsgContextPtrType pMsgContext)
{
  uint8 LucDefType = pMsgContext->reqData[DCM_ZERO];
  Dcm_MsgLenType LddReqDataLen = pMsgContext->reqDataLen;

  if ((DCM_CLEAR_DEFINED_DDDID == LucDefType) && (DCM_ONE == LddReqDataLen))
  {
    /* @Trace: Dcm_SUD_API_60276 */
    pMsgContext->resDataLen = DCM_ONE;
    Dcm_MemCopy(pMsgContext->resData, pMsgContext->reqData, DCM_ONE);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60277 */
    pMsgContext->resDataLen = DCM_THREE;
    Dcm_MemCopy(pMsgContext->resData, pMsgContext->reqData, DCM_THREE);
  }

  #if (DCM_DDDID_STORAGE == STD_ON)
  /* @Trace: SWS_Dcm_00868 */
  /* @Trace: Dcm_SUD_API_60275 */
  (void) NvM_SetRamBlockStatus(DCM_DDDID_STORAGE_BLOCK_ID, DCM_TRUE);
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_ClearOneDefinedDid                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Clear only one defined dynamic did                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : usDynDidIndex                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DynDid_ClearOneDefinedDid(
  uint16 usDynDidIndex)
{
  /* @Trace: Dcm_SUD_API_60278 */
  uint8 LucIndex = DCM_ZERO;
  uint8 LucElementCount = DCM_ZERO;

  Dcm_DynDidInfoPtrType LpDynDidInfo;
  LpDynDidInfo = Dcm_CfgInternal_GetDynDidInfo(usDynDidIndex);

  if ((NULL_PTR != LpDynDidInfo) && (DCM_TRUE == LpDynDidInfo->blActive))
  {
    LucElementCount = LpDynDidInfo->ucMemAddCount + LpDynDidInfo->ucSourceDidCount;

    /* Traverse all current elements in memory address sources and did sources */
    for (LucIndex = DCM_ZERO; LucIndex < LucElementCount; LucIndex++)
    {
      /* @Trace: Dcm_SUD_API_60280 */
      /* Only the source that have priority is different than zero is valid */
      /* polyspace +2 RTE:UNR [Justify:Low] "The index value is always in configuration range " */
      LpDynDidInfo->pMemAddInfo[LucIndex].ucPriority = DCM_ZERO;
      LpDynDidInfo->pSourceDidInfo[LucIndex].ucPriority = DCM_ZERO;
    }

    /* @Trace: Dcm_SUD_API_60281 */
    /* Clear operation informations */
    LpDynDidInfo->blActive = DCM_FALSE;
    LpDynDidInfo->ucMemAddCount = DCM_ZERO;
    LpDynDidInfo->ucSourceDidCount = DCM_ZERO;
  }
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_ClearDefinedDid                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process for clear defined dynamic did          **
**                        sub-function                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_ClearDefinedDid(
  Dcm_MsgContextPtrType pMsgContext)
{
  uint16 LusIndex = DCM_ZERO;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  /* Clear all dynamically defined data identifiers */
  if (DCM_ONE == pMsgContext->reqDataLen)
  {
    for (LusIndex = DCM_ZERO; LusIndex < DCM_TOTAL_NUM_OF_DYN_DID; LusIndex++)
    {
      /* @Trace: Dcm_SUD_API_60282 */
      Dcm_DynDid_ClearOneDefinedDid(LusIndex);
    }
  }
  /* Clear specific data identifier from request message */
  else if (DCM_THREE == pMsgContext->reqDataLen)
  {
    /* @Trace: Dcm_SUD_API_60284 */
    /* Get did from request message */
    uint16 LusDid = Dcm_GetDataIdFromRequest(DCM_ONE, pMsgContext->reqData);

    /* @Trace: SWS_Dcm_00723 SWS_Dcm_00724 */
    LddErrorCode = Dcm_DynDid_CheckRequestedDid(LusDid);

    if (DCM_POS_RESP == LddErrorCode)
    {
      /* Get dynamically define did configuration index */
      if (DCM_TRUE == Dcm_DynDid_GetConfigIndex(LusDid, &LusIndex))
      {
        /* @Trace: Dcm_SUD_API_60286 */
        Dcm_DynDid_ClearOneDefinedDid(LusIndex);
      }
      else
      {
        /* @Trace: Dcm_SUD_API_60287 */
        LddErrorCode = DCM_E_GENERALREJECT;
      }
    }
  }
  /* Wrong request message length */
  else
  {
    /* @Trace: Dcm_SUD_API_60285 */
    LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_CheckRequestedDid                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate the requested did in request message       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : usDid                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckRequestedDid(
  uint16 usDid)
{
  /* @Trace: Dcm_SUD_API_60288 */
  Std_ReturnType LddResult = E_NOT_OK;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_E_REQUESTOUTOFRANGE;

  uint16 LusDidIndex = DCM_ZERO;
  Dcm_DidInfoConfigConstPtrType LpDidInfo = NULL_PTR;

  if ((usDid >= DCM_DDDID_LOWER_RANGE) && (usDid <= DCM_DDDID_UPPER_RANGE))
  {
    if (DCM_TRUE == Dcm_GetDidConfigIndex(usDid, &LusDidIndex))
    {
      /* @Trace: Dcm_SUD_API_60290 */
      /* Did Range feature cannot be applied for UDS 0x2C service */
      LddResult = Dcm_DspInternal_GetDidInfo(LusDidIndex, DCM_FALSE, &LpDidInfo);

      if ((E_OK == LddResult) && 
          (NULL_PTR != LpDidInfo) && 
          (NULL_PTR != LpDidInfo->pDidRead) &&
          (DCM_TRUE == LpDidInfo->blDynamicallyDefined))
      {
        /* @Trace: Dcm_SUD_API_60291 */
        /* Validate session, security level and mode condition */
        LddErrorCode = Dcm_ReadDid_CheckAuthorization(LpDidInfo->pDidRead);
      }
    }
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_CheckExceedDidElement                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : In case sub-function is defined by did,             **
**                        check if the source elements are exceed             **
**                        the maximum configured elements in a request message**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : usDynDidIndex, ddReqDataLen                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pSourceCount                                        **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckExceedDidElement(
  uint16 usDynDidIndex,
  Dcm_MsgLenType ddReqDataLen,
  Dcm_Uint8PtrType pSourceCount)
{
  uint8 LucSourceCount = DCM_ZERO;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;
  Dcm_DynDidInfoPtrType LpDynDidInfo = Dcm_CfgInternal_GetDynDidInfo(usDynDidIndex);

  /* The total size of one source did is 4 byte */
  if (((ddReqDataLen - DCM_THREE) % DCM_FOUR) != DCM_ZERO)
  {
    /* @Trace: Dcm_SUD_API_60292 */
    LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60293 */
    LucSourceCount = (uint8) ((ddReqDataLen - DCM_THREE) / DCM_FOUR);
    uint8 LucElementCount = LpDynDidInfo->ucMemAddCount + LpDynDidInfo->ucSourceDidCount;

    /* @Trace: SWS_Dcm_00861 */
    if ((LucSourceCount + LucElementCount) > LpDynDidInfo->ucMaxElement)
    {
      /* @Trace: Dcm_SUD_API_60294 */
      LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60295 */
    *pSourceCount = LucSourceCount;
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_CheckDidSource                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : In case sub-function is defined by did,             **
**                        validate all informations of source elements        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ucSourceCount, pReqData                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckDidSource(
  uint8 ucSourceCount,
  Dcm_Uint8PtrType pReqData)
{
  /* @Trace: Dcm_SUD_API_60297 */
  uint8 LucSourceIdx = DCM_ZERO;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;
  Dcm_DidParaConfigConstPtrType LpDidConfig = NULL_PTR;

  while ((LucSourceIdx < ucSourceCount) && (DCM_POS_RESP == LddErrorCode))
  {
    /* Get did from request message */
    uint16 LusDidIndex = DCM_ZERO;
    uint16 LusSourceDid = Dcm_GetDataIdFromRequest(DCM_ZERO, pReqData);

    /* Get did configuration index */
    if (DCM_TRUE == Dcm_GetDidConfigIndex(LusSourceDid, &LusDidIndex))
    {
      /* @Trace: Dcm_SUD_API_60299 */
      /* @Trace: SWS_Dcm_00725 SWS_Dcm_00726 SWS_Dcm_00821 */
      LddErrorCode = Dcm_DspValidateReadDid(LusDidIndex, DCM_FALSE);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60298 */
      LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }

    if (DCM_POS_RESP == LddErrorCode)
    {
      /* @Trace: Dcm_SUD_API_60300 */
      uint16 LusMinDidLen = DCM_ZERO;
      uint16 LusMaxDidLen = DCM_ZERO;

      uint16 LusPosData = (uint16) pReqData[DCM_TWO];
      uint16 LusMemSize = (uint16) pReqData[DCM_THREE];
      uint16 LusSourceDidLen = LusPosData + LusMemSize - DCM_ONE;
  
      LpDidConfig = Dcm_CfgInternal_GetDidConfig(LusDidIndex);
      Dcm_DspInternal_GetSizeOfDid(LpDidConfig, &LusMinDidLen, &LusMaxDidLen);

      /* Check if the position and source did lengh is valid */
      if ((LusPosData < DCM_ONE) || (LusSourceDidLen > LusMaxDidLen))
      {
        /* @Trace: Dcm_SUD_API_60301 */
        LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
      }
    }
    /* polyspace +2 MISRA-C3:17.8 [Justified:Low] Justify with annotations */
    LucSourceIdx++;
    pReqData = &pReqData[DCM_FOUR];
  }

  return LddErrorCode; 
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_CheckDefineByDid                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate request message                            **
**                        in case of sub-function is defined by did           **                           
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pSourceCount, pDynDidIndex                          **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckDefineByDid(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint8PtrType pSourceCount,
  Dcm_Uint16PtrType pDynDidIndex)
{
  uint8 LucSourceCount = DCM_ZERO;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  uint16 LusDid = DCM_ZERO;
  uint16 LusDynDidIndex = DCM_ZERO;

  if (pMsgContext->reqDataLen < DCM_SEVEN)
  {
    /* @Trace: Dcm_SUD_API_60304 */
    /* Minimun length check */
    LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60302 */
    /* Get did from request message */
    LusDid = Dcm_GetDataIdFromRequest(DCM_ONE, pMsgContext->reqData);

    /* @Trace: SWS_Dcm_00723 SWS_Dcm_00724 */
    LddErrorCode = Dcm_DynDid_CheckRequestedDid(LusDid);
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* Get dynamically define did configuration index */
    if (DCM_TRUE == Dcm_DynDid_GetConfigIndex(LusDid, &LusDynDidIndex))
    {
      /* @Trace: Dcm_SUD_API_60308 */
      LddErrorCode = Dcm_DynDid_CheckExceedDidElement(
        LusDynDidIndex, pMsgContext->reqDataLen, &LucSourceCount);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60303 */
      LddErrorCode = DCM_E_GENERALREJECT;
    }
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60305 */
    LddErrorCode = Dcm_DynDid_CheckDidSource(
      LucSourceCount, &pMsgContext->reqData[DCM_THREE]);
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60306 */
    *pDynDidIndex = LusDynDidIndex;
    *pSourceCount = LucSourceCount;
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_DefineByDid                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to process defined by did sub-function**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_DefineByDid(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60311 */
  uint8 LucSourceCount = DCM_ZERO;
  uint8 LucElementCount = DCM_ZERO;
  Dcm_NegativeResponseCodeType LddErrorCode;

  uint16 LusDynDidIndex = DCM_ZERO;
  Dcm_Uint8PtrType LpReqData = &pMsgContext->reqData[DCM_THREE];

  Dcm_DynDidInfoPtrType LpDynDidInfo = NULL_PTR;
  Dcm_SourceDidInfoPtrType LpSourceDidInfo = NULL_PTR;

  /* Validate all conditions that related to requested did */
  LddErrorCode = Dcm_DynDid_CheckDefineByDid(
    pMsgContext, &LucSourceCount, &LusDynDidIndex);
  
  if (DCM_POS_RESP == LddErrorCode) 
  {
    /* @Trace: Dcm_SUD_API_60310 */
    uint8 LucSourceIndex = DCM_ZERO;
    uint16 LusSourceDid = DCM_ZERO;

    LpDynDidInfo = Dcm_CfgInternal_GetDynDidInfo(LusDynDidIndex);

    LpDynDidInfo->blActive = DCM_TRUE;
    LucElementCount = LpDynDidInfo->ucMemAddCount + LpDynDidInfo->ucSourceDidCount;

    /* Pointer to the empty slot in source did array */
    LpSourceDidInfo = &LpDynDidInfo->pSourceDidInfo[LucElementCount];
    LpDynDidInfo->ucSourceDidCount = LpDynDidInfo->ucSourceDidCount + LucSourceCount;

    /* All all requested source did to array */
    for (LucSourceIndex = LucElementCount; 
         LucSourceIndex < (LucElementCount + LucSourceCount);
         LucSourceIndex++)
    {
      /* @Trace: Dcm_SUD_API_60309 */
      LusSourceDid = Dcm_GetDataIdFromRequest(DCM_ZERO, LpReqData);

      LpSourceDidInfo->usSourceDid = LusSourceDid;
      LpSourceDidInfo->ucPriority = LucSourceIndex + DCM_ONE;

      LpSourceDidInfo->ucPosInSource = LpReqData[DCM_TWO];
      LpSourceDidInfo->ucMemSize = LpReqData[DCM_THREE];

      /* Go to next source element */
      LpReqData = &LpReqData[DCM_FOUR];
      LpSourceDidInfo = &LpSourceDidInfo[DCM_ONE];
    }
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_CheckExceedMemoryElement                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : In case sub-function is defined by memory,          **
**                        check if the source elements are exceed             **
**                        the maximum configured elements in a request message**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : usSourceLen, usDynDidIndex, ddReqDataLen            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pSourceCount                                        **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckExceedMemoryElement(
  uint16 usSourceLen,
  uint16 usDynDidIndex,
  Dcm_MsgLenType ddReqDataLen,
  Dcm_Uint8PtrType pSourceCount)
{
  uint8 LucSourceCount = DCM_ZERO;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  Dcm_DynDidInfoPtrType LpDynDidInfo;
  LpDynDidInfo = Dcm_CfgInternal_GetDynDidInfo(usDynDidIndex);

  if (((ddReqDataLen - DCM_FOUR) % usSourceLen) != DCM_ZERO)
  {
    /* @Trace: Dcm_SUD_API_60313 */
    LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60314 */
    LucSourceCount = (uint8) ((ddReqDataLen - DCM_FOUR) / usSourceLen);
    uint8 LucElementCount = LpDynDidInfo->ucMemAddCount + LpDynDidInfo->ucSourceDidCount;
    
    /* @Trace: SWS_Dcm_00861 */
    if ((LucSourceCount + LucElementCount) > LpDynDidInfo->ucMaxElement)
    {
      /* @Trace: Dcm_SUD_API_60315 */
      LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60316 */
    *pSourceCount = LucSourceCount;
  }  

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_CheckMemorySource                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : In case sub-function is defined by memory,          **
**                        validate all informations of source elements        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ucSourceCount, ucMemAddrBytes,                      **
**                        ucMemSizeBytes, pReqData                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckMemorySource(
  uint8 ucSourceCount,
  uint8 ucMemAddrBytes,
  uint8 ucMemSizeBytes,
  Dcm_Uint8PtrType pReqData)
{
  /* @Trace: Dcm_SUD_API_60317 */
  boolean LblResult = DCM_FALSE;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  uint8 LucMemoryId = DCM_ZERO;
  uint8 LucRangeIndex = DCM_ZERO;
  uint8 LucSourceIndex = DCM_ZERO;

  uint32 LulMemoryAddr = DCM_ZERO;
  uint32 LulMemorySize = DCM_ZERO;

  Dcm_ReadMemRngInfoConfigConstPtrType LpReadMemRange = NULL_PTR;

  while ((LucSourceIndex < ucSourceCount) && (DCM_POS_RESP == LddErrorCode))
  {
    /* @Trace: Dcm_SUD_API_60318 */
    /* polyspace +1 MISRA-C3:17.8 [Justified:Low] Justify with annotations */
    LucMemoryId = pReqData[DCM_ZERO];
    LulMemoryAddr = Dcm_ReadMemoryAddressFromReqData(pReqData, ucMemAddrBytes);
    
    /* polyspace +1 MISRA-C3:17.8 [Justified:Low] Justify with annotations */
    pReqData = &pReqData[ucMemAddrBytes];
    LulMemorySize = Dcm_ReadMemorySizeFromReqData(pReqData, ucMemSizeBytes);
    
    LblResult = Dcm_IsReadMemoryRangeValid(
      LulMemoryAddr, LulMemorySize, &LucRangeIndex);

    if (DCM_TRUE == LblResult)
    {
      LpReadMemRange = &Dcm_GaaReadMemRngConfig[LucRangeIndex];

      /* @Trace: SWS_Dcm_01051 */
      /* polyspace +1 DEFECT:DEAD_CODE [Not a defect:Low] "blUseMemoryValue can be configured or not by user . No impact" */
      if ((DCM_FALSE == LpReadMemRange->blUseMemoryValue) ||
          (LucMemoryId == LpReadMemRange->ucReadMemoryIdentifier))
      {
        /* @Trace: SWS_Dcm_00726 */
        LblResult = Dcm_DsdValidateSecurity(
          LpReadMemRange->pReadMemRngSec, 
          LpReadMemRange->ucReadMemSecCount);

        if (DCM_TRUE == LblResult)
        {
          #if (DCM_MODE_RULE == STD_ON)
          /* @Trace: SWS_Dcm_00821 */
          /* @Trace: Dcm_SUD_API_60322 */
          LddErrorCode = Dcm_CheckModeRule(
            LpReadMemRange->blModeRuleConfigured, 
            LpReadMemRange->ucDIDmoderuleArrayindex);
          #endif
        }
        else
        {
          /* @Trace: Dcm_SUD_API_60321 */
          LddErrorCode = DCM_E_SECURITYACCESSDENIED;
        }
      }
      else
      {
        /* @Trace: Dcm_SUD_API_60320 */
        LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
      }
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60319 */
      LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }

    /* polyspace +3 MISRA-C3:17.8 [Justified:Low] Justify with annotations */
    /* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
    LucSourceIndex++;
    pReqData = &pReqData[ucMemSizeBytes];
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_CheckDefineByMemory                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate request message                            **
**                        in case of sub-function is defined by memory        **                           
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pSourceCount, pDynDidIndex                          **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_CheckDefineByMemory(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint8PtrType pSourceCount,
  Dcm_Uint16PtrType pDynDidIndex)
{
  uint8 LucSourceCount = DCM_ZERO;
  uint8 LucMemAddrBytes = DCM_ZERO;
  uint8 LucMemSizeBytes = DCM_ZERO;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  uint16 LusDid = DCM_ZERO;
  uint16 LusSourceLen = DCM_ZERO;
  uint16 LusDynDidIndex = DCM_ZERO;

  Dcm_Uint8PtrType LpReqData = pMsgContext->reqData;
  Dcm_MsgLenType LddReqDataLen = pMsgContext->reqDataLen;

  if (LddReqDataLen < DCM_SIX)
  {
    /* @Trace: Dcm_SUD_API_60324 */
    /* Minimum length check */
    LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60323 */
    /* Get did from request message */
    LusDid = Dcm_GetDataIdFromRequest(DCM_ONE, LpReqData);

    /* @Trace: SWS_Dcm_00723 SWS_Dcm_00724 */
    LddErrorCode = Dcm_DynDid_CheckRequestedDid(LusDid);
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: SWS_Dcm_00854 */
    if (DCM_FALSE == Dcm_IsAddrLenFormatIdSupported(LpReqData[DCM_THREE]))
    {
      /* @Trace: Dcm_SUD_API_60329 */
      LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
      if (DCM_TRUE == Dcm_DynDid_GetConfigIndex(LusDid, &LusDynDidIndex))
      {
        /* @Trace: Dcm_SUD_API_60325 */
        LucMemAddrBytes = DCM_GET_MEMORY_ADDR_BYTES(LpReqData[DCM_THREE]);
        LucMemSizeBytes = DCM_GET_MEMORY_SIZE_BYTES(LpReqData[DCM_THREE]);

        LusSourceLen = (uint16) LucMemAddrBytes + (uint16) LucMemSizeBytes;

        LddErrorCode = Dcm_DynDid_CheckExceedMemoryElement(
          LusSourceLen, LusDynDidIndex, LddReqDataLen, &LucSourceCount);
      }
      else
      {
        /* @Trace: Dcm_SUD_API_60326 */
        LddErrorCode = DCM_E_GENERALREJECT;
      }
    }
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60327 */
    LddErrorCode = Dcm_DynDid_CheckMemorySource(
      LucSourceCount, LucMemAddrBytes, LucMemSizeBytes, &LpReqData[DCM_FOUR]);
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60328 */
    *pDynDidIndex = LusDynDidIndex;
    *pSourceCount = LucSourceCount;
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DynDid_DefineByMemory                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to process defined by memory          **
**                        sub-function                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DynDid_DefineByMemory(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60330 */
  uint8 LucSourceCount = DCM_ZERO;
  uint8 LucElementCount = DCM_ZERO;
  Dcm_NegativeResponseCodeType LddErrorCode;

  uint16 LusDynDidIndex = DCM_ZERO;
  Dcm_Uint8PtrType LpReqData = pMsgContext->reqData;

  uint32 LulMemoryAddr = DCM_ZERO;
  uint32 LulMemorySize = DCM_ZERO;

  Dcm_DynDidInfoPtrType LpDynDidInfo = NULL_PTR;
  Dcm_MemAddInfoPtrType LpMemAddInfo = NULL_PTR;

  /* Validate all conditions for requested memory source */
  LddErrorCode = Dcm_DynDid_CheckDefineByMemory(
    pMsgContext, &LucSourceCount, &LusDynDidIndex);

  if (DCM_POS_RESP == LddErrorCode) 
  {
    /* @Trace: Dcm_SUD_API_60332 */
    uint8 LucSourceIndex = DCM_ZERO;
    uint8 LucMemAddrBytes = DCM_GET_MEMORY_ADDR_BYTES(LpReqData[DCM_THREE]);
    uint8 LucMemSizeBytes = DCM_GET_MEMORY_SIZE_BYTES(LpReqData[DCM_THREE]);

    LpDynDidInfo = Dcm_CfgInternal_GetDynDidInfo(LusDynDidIndex);

    LpDynDidInfo->blActive = DCM_TRUE;
    LucElementCount = LpDynDidInfo->ucMemAddCount + LpDynDidInfo->ucSourceDidCount;

    LpReqData = &LpReqData[DCM_FOUR];
    LpMemAddInfo = &LpDynDidInfo->pMemAddInfo[LucElementCount];
    LpDynDidInfo->ucMemAddCount = LpDynDidInfo->ucMemAddCount + LucSourceCount;

    for (LucSourceIndex = LucElementCount; 
         LucSourceIndex < (LucElementCount + LucSourceCount);
         LucSourceIndex++)
    {
      /* @Trace: Dcm_SUD_API_60331 */
      LulMemoryAddr = Dcm_ReadMemoryAddressFromReqData(LpReqData, LucMemAddrBytes);
      LpReqData = &LpReqData[LucMemAddrBytes];

      LulMemorySize = Dcm_ReadMemorySizeFromReqData(LpReqData, LucMemSizeBytes);
      LpReqData = &LpReqData[LucMemSizeBytes];

      LpMemAddInfo->ulMemAdd = LulMemoryAddr;
      LpMemAddInfo->ulMemSize = LulMemorySize;
      LpMemAddInfo->ucPriority = LucSourceIndex + DCM_ONE;
      LpMemAddInfo->ucMemoryId = Dcm_GetMemoryIdByRange(LulMemoryAddr, LulMemorySize);

      /* Go to next element */
      LpMemAddInfo = &LpMemAddInfo[DCM_ONE];
    }
  }

  return LddErrorCode;
}
#endif /* DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE */

/*******************************************************************************
** Function Name        : Dcm_DcmWriteDataByIdentifier                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for UDS 0x2E service          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmWriteDataByIdentifier(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_00255 */
  /* @Trace: Dcm_SUD_API_60334 */
  uint16 LusDidIndex = DCM_ZERO;
  boolean LblDidRange = DCM_FALSE;
  Std_ReturnType LddRetVal = E_OK;

  Dcm_NegativeResponseCodeType LddErrorCode;
  LddErrorCode = Dcm_WriteDid_ValidateRequest(
    pMsgContext, &LusDidIndex, &LblDidRange);

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60333 */
    /* Update global variables */
    Dcm_GusDIDIndexVal = LusDidIndex;
    Dcm_GblDIDRangePresent = LblDidRange;

    /* Invoke internal process function */
    (void) Dcm_WriteDid_InternalProcess(
      DCM_INITIAL, pMsgContext, &LddErrorCode);
  }

  /* Determine if finish processing and update response */
  Dcm_WriteDid_UpdateResponse(
    LusDidIndex, LblDidRange, pMsgContext, LddErrorCode);

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_WriteDid_ValidateRequest                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to process validation for request     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pDidIndex, pIsDidRange                              **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_WriteDid_ValidateRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint16PtrType pDidIndex,
  Dcm_BooleanPtrType pIsDidRange)
{
  uint16 LusDataId;
  uint16 LusDidIndex = DCM_ZERO;
  boolean LblDidRange = DCM_FALSE;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  /* @Trace: Dcm_SUD_API_60337 */
  /* Get did from the request buffer */
  LusDataId = Dcm_RequestParameterToUint16(DCM_TWO, pMsgContext->reqData);

  /* Validate requested did */
  LddErrorCode = Dcm_WriteDid_CheckDataId(
    LusDataId, &LusDidIndex, &LblDidRange);

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60335 */
    Dcm_MsgLenType LddReqLen = pMsgContext->reqDataLen;

    LddErrorCode = Dcm_WriteDid_CheckFullLength(
      LusDidIndex, LblDidRange, LddReqLen);
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60336 */
    *pDidIndex = LusDidIndex;
    *pIsDidRange = LblDidRange;
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_WriteDid_CheckDataId                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if the request did is valid or not            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : dataId                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pDidIndex, pIsDidRange                              **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_WriteDid_CheckDataId(
  uint16 dataId,
  Dcm_Uint16PtrType pDidIndex,
  Dcm_BooleanPtrType pIsDidRange)
{
  /* @Trace: Dcm_SUD_API_60339 */
  boolean LblDidRange = DCM_FALSE;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_E_REQUESTOUTOFRANGE;

  uint16 LusDidIndex = DCM_ZERO;
  Dcm_DidInfoConfigConstPtrType LpDidInfo = NULL_PTR;

  /* @Trace: SWS_Dcm_00467 */
  if (DCM_TRUE == Dcm_DspDidSearch(dataId, &LusDidIndex, &LblDidRange))
  {
    /* @Trace: SWS_Dcm_00562 */
    /* @Trace: Dcm_SUD_API_60338 */
    (void) Dcm_DspInternal_GetDidInfo(LusDidIndex, LblDidRange, &LpDidInfo);

    /* @Trace: SWS_Dcm_00468 */
    if ((NULL_PTR != LpDidInfo) && (NULL_PTR != LpDidInfo->pDidWrite))
    {
      #if(DCM_AUTHENTICATION_SERVICE == STD_ON)
      /* @Trace: SWS_Dcm_01496 */
      /* @Trace: Dcm_SUD_API_60340 */
      LddErrorCode = Dcm_WriteDid_AuthValidate(dataId, LpDidInfo->pDidWrite);

      if (DCM_POS_RESP == LddErrorCode)
      #endif
      {
        /* @Trace: Dcm_SUD_API_60341 */
        /* @Trace: SWS_Dcm_00469, SWS_Dcm_00470, SWS_Dcm_00822 */
        LddErrorCode = Dcm_WriteDid_CheckAuthorization(LpDidInfo->pDidWrite);
      }

      if (DCM_POS_RESP == LddErrorCode)
      {
        /* @Trace: Dcm_SUD_API_60343 */
        *pDidIndex = LusDidIndex;
        *pIsDidRange = LblDidRange;
      }
    }
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_WriteDid_AuthValidate                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check the access right for requested did            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : dataId, pDidWrite                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if(DCM_AUTHENTICATION_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_WriteDid_AuthValidate(
  uint16 dataId,
  Dcm_DidWriteConfigConstPtrType pDidWrite)
{
  /* @Trace: Dcm_SUD_API_60347 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  Dcm_AuthenticationRoleType LddRole;
  Dcm_MemCopy(LddRole, pDidWrite->ddDidWriteRole, DCM_AUTHENTICATION_ROLE_SIZE);

  if (DCM_FALSE == Dcm_ValidateAccessRights(LddRole))
  {
    /* @Trace: Dcm_SUD_API_60344 */
    #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON)
    uint8 LaaRecord[DCM_THREE];
    LaaRecord[DCM_ZERO] = DCM_U16_HI_BYTE(dataId);
    LaaRecord[DCM_ONE] = DCM_U16_LO_BYTE(dataId);
    LaaRecord[DCM_TWO] = DCM_DID_WRITE_ACCESS_MASK;

    if (DCM_FALSE == Dcm_ValidateAccessRightsWithWLDid(LaaRecord, DCM_THREE))
    #endif
    {
      /* @Trace: Dcm_SUD_API_60345 */
      LddErrorCode = DCM_E_AUTHENTICATIONREQUIRED;
    }
  }

  DCM_UNUSED(dataId);
  return LddErrorCode;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_WriteDid_CheckAuthorization                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate session, security and mode condition       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pDidWrite                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_WriteDid_CheckAuthorization(
  Dcm_DidWriteConfigConstPtrType pDidWrite)
{
  /* @Trace: Dcm_SUD_API_60351 */
  boolean LblResult = DCM_TRUE;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  LblResult = Dcm_DsdValidateSession(
    pDidWrite->pDidWriteSession, pDidWrite->ucDidWriteSesCount);

  if (DCM_TRUE == LblResult)
  {
    LblResult = Dcm_DsdValidateSecurity(
      pDidWrite->pDidWriteSecurity, pDidWrite->ucDidWriteSecCount);

    if (DCM_TRUE == LblResult)
    {
      /* @Trace: Dcm_SUD_API_60350 */
      #if (DCM_MODE_RULE == STD_ON)
      LddErrorCode = Dcm_CheckModeRule(
        pDidWrite->blModeRuleConfigured, pDidWrite->ucModeRuleIndex);
      #endif
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60349 */
      LddErrorCode = DCM_E_SECURITYACCESSDENIED;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60348 */
    LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_WriteDid_CheckFullLength                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check full length of request message                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : didIndex, isDidRange, reqDataLen                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_WriteDid_CheckFullLength(
  uint16 didIndex,
  boolean isDidRange,
  Dcm_MsgLenType reqDataLen)
{
  /* @Trace: Dcm_SUD_API_60356 */
  uint16 LusMinDidLen = DCM_ZERO;
  uint16 LusMaxDidLen = DCM_ZERO;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if (DCM_TRUE == isDidRange)
  {
    Dcm_DidRangeConfigPtrType LpDidRangeConfig;
    LpDidRangeConfig = Dcm_CfgInternal_GetDidRangeConfig(didIndex);

    if (NULL_PTR == LpDidRangeConfig)
    {
      /* @Trace: Dcm_SUD_API_60355 */
      LddErrorCode = DCM_E_GENERALREJECT;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60354 */
      LusMaxDidLen = LpDidRangeConfig->usDidRangeMaxDataLength;
    }
  }
  else
  {
    Dcm_DidParaConfigConstPtrType LpDidConfig;
    LpDidConfig = Dcm_CfgInternal_GetDidConfig(didIndex);

    if (NULL_PTR == LpDidConfig)
    {
      /* @Trace: Dcm_SUD_API_60353 */
      LddErrorCode = DCM_E_GENERALREJECT;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60352 */
      Dcm_DspInternal_GetSizeOfDid(LpDidConfig, &LusMinDidLen, &LusMaxDidLen);
    }
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: SWS_Dcm_00473 */
    if ((reqDataLen < (Dcm_MsgLenType) ((uint32) DCM_TWO + (uint32) LusMinDidLen)) ||
        (reqDataLen > (Dcm_MsgLenType) ((uint32) DCM_TWO + (uint32) LusMaxDidLen)))
    {
      /* @Trace: Dcm_SUD_API_60357 */
      LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_WriteDid_InternalProcess                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal process function for UDS 0x2E service      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_WriteDid_InternalProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  /* Reset the pending operation flag */
  Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus = DCM_FALSE;

  if (DCM_FALSE == Dcm_GblDIDRangePresent)
  {
    /* @Trace: Dcm_SUD_API_60358 */
    Dcm_DidParaConfigConstPtrType LpDidConfig;
    LpDidConfig = Dcm_CfgInternal_GetDidConfig(Dcm_GusDIDIndexVal);

    if (NULL_PTR != LpDidConfig)
    {
      switch (LpDidConfig->ucDcmDspDidUsePort)
      {
        case USE_ATOMIC_NV_DATA_INTERFACE:
        case USE_ATOMIC_SENDER_RECEIVER_INTERFACE:
        case USE_ATOMIC_SENDER_RECEIVER_INTERFACE_AS_SERVICE:
          #if (DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON)
          /* @Trace: SWS_Dcm_01433 */
          /* @Trace: Dcm_SUD_API_60359 */
          LddRetVal = Dcm_WriteDid_AtomicIfProcess(
            OpStatus, LpDidConfig, pMsgContext, pErrorCode);
          #endif
          break;
        
        default:
          /* @Trace: Dcm_SUD_API_60360 */
          LddRetVal = Dcm_WriteDid_DataIfProcess(
            OpStatus, LpDidConfig, pMsgContext, pErrorCode);
          break;
      }
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60361 */
    #if (DCM_ZERO != DCM_NUM_OF_DCMDSPDIDRANGECONFIG)
    Dcm_DidRangeConfigPtrType LpDidRangeCfg;
    LpDidRangeCfg = Dcm_CfgInternal_GetDidRangeConfig(Dcm_GusDIDIndexVal);

    if (NULL_PTR != LpDidRangeCfg)
    {
      /* @Trace: Dcm_SUD_API_60362 */
      LddRetVal = Dcm_WriteDid_DidRangeProcess(
        OpStatus, LpDidRangeCfg, pMsgContext, pErrorCode);
    }
    #endif
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_WriteDid_DidRangeProcess                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for write did range           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pDidRangeConfig                           **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_NUM_OF_DCMDSPDIDRANGECONFIG != DCM_ZERO)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_WriteDid_DidRangeProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_DidRangeConfigPtrType pDidRangeConfig,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60364 */
  Std_ReturnType LddRetVal = E_OK;

  uint16 LusWriteDataLen = (uint16) (pMsgContext->reqDataLen - DCM_TWO);
  uint16 LusDataId = Dcm_RequestParameterToUint16(DCM_TWO, pMsgContext->reqData);

  /* Clear error code */
  *pErrorCode = DCM_POS_RESP;

  /* Check if requested signal data is already read or not */
  if (DCM_OPSTATUS_COMPLETE != pDidRangeConfig->ucDidRangeOpStatus)
  {
    if (NULL_PTR == pDidRangeConfig->pWriteDidDataFun)
    {
      /* @Trace: Dcm_SUD_API_70003 */
      LddRetVal = E_NOT_OK;
      *pErrorCode = DCM_E_GENERALREJECT;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60365 */
      LddRetVal = pDidRangeConfig->pWriteDidDataFun(
        LusDataId, &pMsgContext->reqData[DCM_TWO], 
        OpStatus, LusWriteDataLen, pErrorCode);
    }

    if (DCM_CANCEL != OpStatus)
    {
      switch (LddRetVal)
      {
        case E_OK:
          /* @Trace: Dcm_SUD_API_60366 */
          pDidRangeConfig->ucDidRangeOpStatus = DCM_OPSTATUS_COMPLETE;
          break;

        case E_NOT_OK:
          /* @Trace: Dcm_SUD_API_60367 */
          /* Error code is update in the pointer */
          break;

        case DCM_E_PENDING:
          /* @Trace: Dcm_SUD_API_60368 */
          pDidRangeConfig->ucDidRangeOpStatus = DCM_OPSTATUS_PENDING;
          Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus = DCM_TRUE;
          break;

        default:
          /* @Trace: Dcm_SUD_API_60369 */
          LddRetVal = E_NOT_OK;
          *pErrorCode = DCM_E_GENERALREJECT;
          break;
      }
    }
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_WriteDid_CallWriteDataFunc                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Invoke write data function for did signal           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, writeDataLen, pDataCfg, pInBuffer         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_WriteDid_CallWriteDataFunc(
  Dcm_OpStatusType OpStatus,
  uint16 writeDataLen,
  Dcm_DataConfigConstPtrType pDataCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pInBuffer,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60370 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if (NULL_PTR != pDataCfg)
  {
    switch (pDataCfg->ucDcmDspDataUsePort)
    {
      case USE_BLOCK_ID:
        /* @Trace: SWS_Dcm_00541 */
        /* @Trace: Dcm_SUD_API_60372 */
        LddRetVal = Dcm_DspInternal_WriteSigTypeNvMBlock(
          OpStatus, pDataCfg, pInBuffer, pErrorCode);
        break;

      /* @Trace: SWS_Dcm_00395 */
      case USE_DATA_ASYNCH_FNC:
      case USE_DATA_ASYNCH_FNC_ERROR:
      case USE_DATA_ASYNCH_CLIENT_SERVER:
      case USE_DATA_ASYNCH_CLIENT_SERVER_ERROR:
        if ((DCM_DATA_TYPE_UINT8_DYN != pDataCfg->ucDcmDspDataType) && 
            (NULL_PTR != pDataCfg->pWriteDataFixedAsyncFun))
        {
          /* @Trace: SWS_Dcm_00541 */
          /* @Trace: Dcm_SUD_API_60373 */
          LddRetVal = pDataCfg->pWriteDataFixedAsyncFun(
            pInBuffer, OpStatus, pErrorCode);
        }
        else if ((DCM_DATA_TYPE_UINT8_DYN == pDataCfg->ucDcmDspDataType) &&
                 (NULL_PTR != pDataCfg->pWriteDataDynAsyncFun))
        {
          /* @Trace: SWS_Dcm_00541 */
          /* @Trace: Dcm_SUD_API_60374 */
          LddRetVal = pDataCfg->pWriteDataDynAsyncFun(
            pInBuffer, writeDataLen, OpStatus, pErrorCode);
        }
        else
        {
          /* @Trace: Dcm_SUD_API_60375 */
          /* No action in this case */
        }
        break;

      case USE_DATA_SYNCH_FNC:
      case USE_DATA_SYNCH_CLIENT_SERVER:
        if ((DCM_DATA_TYPE_UINT8_DYN != pDataCfg->ucDcmDspDataType) && 
            (NULL_PTR != pDataCfg->pWriteDataFixedSyncFun))
        {
          /* @Trace: SWS_Dcm_00395 */
          /* @Trace: Dcm_SUD_API_60376 */
          LddRetVal = pDataCfg->pWriteDataFixedSyncFun(
            pInBuffer, pErrorCode);
        }
        else if ((DCM_DATA_TYPE_UINT8_DYN == pDataCfg->ucDcmDspDataType) &&
                 (NULL_PTR != pDataCfg->pWriteDataDynSyncFun))
        {
          /* @Trace: SWS_Dcm_00395 */
          /* @Trace: Dcm_SUD_API_60377 */
          LddRetVal = pDataCfg->pWriteDataDynSyncFun(
            pInBuffer, writeDataLen, pErrorCode);
        }
        else
        {
          /* @Trace: Dcm_SUD_API_60378 */
          /* No action in this case */
        }
        break;

      case USE_DATA_SENDER_RECEIVER:
        /* @Trace: Dcm_SUD_API_60379 */
        LddRetVal = Dcm_CfgInternal_WriteSigTypeSenderReceiver(
          pDataCfg, pInBuffer, pErrorCode);
        break;

      default:
        /* @Trace: Dcm_SUD_API_60371 */
        /* No action in this case */
        break;
    }
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_WriteDid_DataIfProcess                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to process write did by               **
**                        data elemenet specific interface                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pDidConfig                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_WriteDid_DataIfProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_DidParaConfigConstPtrType pDidConfig,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;

  uint8 LusSignalIndex = DCM_ZERO;
  uint8 LusNumOfSignal = pDidConfig->ucDcmDspSignalCount;

  uint16 LusWriteDataLen = DCM_ZERO;
  uint16 LusTotalWriteDataLen = (uint16) (pMsgContext->reqDataLen - DCM_TWO);

  Dcm_DataConfigConstPtrType LpDataCfg = NULL_PTR;
  Dcm_DidSignalConfigPtrType LpSignalCfg = NULL_PTR;

  /* Clear error code */
  *pErrorCode = DCM_POS_RESP;  

  if ((NULL_PTR != pDidConfig->pDcmDspSignal) && (DCM_ZERO != LusNumOfSignal))
  {
    /* @Trace: Dcm_SUD_API_60381 */
    while ((LusSignalIndex < LusNumOfSignal) && (E_OK == LddRetVal))
    {
      /* @Trace: Dcm_SUD_API_60382 */
      /* Get the signal configuration */
      LpSignalCfg = &pDidConfig->pDcmDspSignal[LusSignalIndex];

      if (DCM_OPSTATUS_COMPLETE != LpSignalCfg->ucSignalOpStatus)
      {
        /* @Trace: Dcm_SUD_API_60384 */
        P2VAR(void, AUTOMATIC, DCM_APPL_DATA) LpOutBuffer;
        LpOutBuffer = (void *) &Dcm_GaaDIDSignalData[DCM_ZERO];

        /* @Trace: SWS_Dcm_00639 */
        LusWriteDataLen = Dcm_WriteDid_UnPackSignal(
          LusTotalWriteDataLen, LpSignalCfg, 
          &pMsgContext->reqData[DCM_TWO], LpOutBuffer);

        /* Get the data configuration */
        LpDataCfg = LpSignalCfg->pDataConfig;

        /* Invoke write data function */
        /* polyspace +3 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
        /* polyspace +2 CERT-C:EXP36-C [Justified:Low] "LpOutBuffer depend on configured write data function. No Impact" */
        LddRetVal = Dcm_WriteDid_CallWriteDataFunc(
          OpStatus, LusWriteDataLen, LpDataCfg, LpOutBuffer, pErrorCode);

        if (DCM_CANCEL != OpStatus)
        {
          switch (LddRetVal)
          {
            case E_OK:
              /* @Trace: Dcm_SUD_API_60383 */
              LpSignalCfg->ucSignalOpStatus = DCM_OPSTATUS_COMPLETE;
              break;

            case E_NOT_OK:
              /* @Trace: Dcm_SUD_API_60385 */
              /* Error code is updated in pErrorCode argument */
              break;

            case DCM_E_PENDING:
              /* @Trace: Dcm_SUD_API_60386 */
              LpSignalCfg->ucSignalOpStatus = DCM_OPSTATUS_PENDING;
              Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus = DCM_TRUE;
              break;

            default:
              /* @Trace: Dcm_SUD_API_60387 */
              LddRetVal = E_NOT_OK;
              *pErrorCode = DCM_E_GENERALREJECT;
              break;
          }
        }
      }

      /* Next signal */
      LusSignalIndex++;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60380 */
    LddRetVal = E_NOT_OK;
    *pErrorCode = DCM_E_GENERALREJECT;
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_WriteDid_AtomicIfProcess                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to process write did by               **
**                        atomic sender receiver interface                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pDidConfig                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_WriteDid_AtomicIfProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_DidParaConfigConstPtrType pDidConfig,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal;
  uint16 LusDidSize = DCM_ZERO;

  /* @Trace: SWS_Dcm_01432 */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Return value depend on Application code."*/
  LddRetVal = Dcm_APIs_DidData(
    pDidConfig->usDcmDspDidIdentifier, 
    &pMsgContext->reqData[DCM_TWO], &LusDidSize);

  if (E_OK == LddRetVal)
  {
    /* @Trace: Dcm_SUD_API_60389 */
    *pErrorCode = DCM_POS_RESP;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60388 */
    LddRetVal = E_NOT_OK;
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Return value depend on Application code."*/

  DCM_UNUSED(OpStatus);
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_WriteDid_UnPackSignal                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Unpack data from request message to signal buffer   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : totalWriteDataLen, pSignalCfg, pInBuffer            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pOutBuffer                                          **
**                                                                            **
** Return parameter     : LusDataLength                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(uint16, DCM_CODE) Dcm_WriteDid_UnPackSignal(
  uint16 totalWriteDataLen,
  Dcm_DidSignalConfigPtrType pSignalCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pInBuffer,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutBuffer)
{
  uint16 LusDataLength = DCM_ZERO;
  Dcm_PackUnPackType LddUnPackSignal;

  /* Only the last signal may have variable length */
  if (DCM_DATA_TYPE_UINT8_DYN == pSignalCfg->pDataConfig->ucDcmDspDataType)
  {
    /* @Trace: Dcm_SUD_API_60390 */
    LusDataLength = totalWriteDataLen - pSignalCfg->usByteOffset;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_70004 */
    LusDataLength = pSignalCfg->pDataConfig->usDcmDspDataByteSize;
  }

  if (DCM_ZERO != LusDataLength)
  {
    /* @Trace: Dcm_SUD_API_60392 */
    LddUnPackSignal.usSignalSize = LusDataLength;
    LddUnPackSignal.blByteConversion = pSignalCfg->blByteConversion;

    uint8 LucUnPackFuncIdx = pSignalCfg->ucUnPackFuncIndex;
    if (LucUnPackFuncIdx < DCM_NUM_OF_UNPACK_FUNC_CONFIG)
    {
      /* @Trace: Dcm_SUD_API_60391 */
      Dcm_GaaUnPackFunc[LucUnPackFuncIdx].pUnPackFunc(
        pOutBuffer,
        &pInBuffer[pSignalCfg->usByteOffset],
        &LddUnPackSignal);
    }
  }

  return LusDataLength;
}

/*******************************************************************************
** Function Name        : Dcm_ResetWriteDidOpStatus                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Reset the operation status of requested did         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : didIndex, isDidRange                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_ResetWriteDidOpStatus(
  uint16 didIndex,
  boolean isDidRange)
{
  if (DCM_FALSE == isDidRange)
  {
    /* @Trace: Dcm_SUD_API_60393 */
    Dcm_ResetSignalOpStatus(didIndex);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60394 */
    #if (DCM_ZERO != DCM_NUM_OF_DCMDSPDIDRANGECONFIG)
    Dcm_DidRangeConfigPtrType LpDidRangeConfig;
    LpDidRangeConfig = Dcm_CfgInternal_GetDidRangeConfig(didIndex);

    if (NULL_PTR != LpDidRangeConfig)
    {
      /* @Trace: Dcm_SUD_API_60395 */
      LpDidRangeConfig->ucDidRangeOpStatus = DCM_OPSTATUS_INITIAL;
    }
    #endif
  }
}

/*******************************************************************************
** Function Name        : Dcm_WriteDid_UpdateResponse                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Update the response for when finish processing      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : didIndex, errorCode                                 **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_WriteDid_UpdateResponse(
  uint16 didIndex,
  boolean isDidRange,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode)
{
  /* @Trace: Dcm_SUD_API_60397 */
  if (DCM_FALSE == Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus)
  {
    if (DCM_POS_RESP != errorCode)
    {
      /* @Trace: Dcm_SUD_API_60396 */
      Dcm_InternalSetNegResponse(pMsgContext, errorCode);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60398 */
      pMsgContext->resDataLen = DCM_TWO;
      Dcm_MemCopy(pMsgContext->resData, pMsgContext->reqData, DCM_TWO);
    }

    Dcm_ResetWriteDidOpStatus(didIndex, isDidRange);
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
}

/*******************************************************************************
** Function Name        : Dcm_WriteDid_PendingOperation                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Pending operation process for UDS 0x2E service      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_WriteDid_PendingOperation(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60400 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if (DCM_TRUE == Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus)
  {
    /* @Trace: Dcm_SUD_API_60399 */
    (void) Dcm_WriteDid_InternalProcess(
      DCM_PENDING, pMsgContext, &LddErrorCode);

    Dcm_WriteDid_UpdateResponse(
      Dcm_GusDIDIndexVal, Dcm_GblDIDRangePresent, pMsgContext, LddErrorCode);
  }
}

/*******************************************************************************
** Function Name        : Dcm_WriteDid_CancelOperation                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Cancel operation process for UDS 0x2E service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_WriteDid_CancelOperation(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60401 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if (DCM_TRUE == Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus)
  {
    /* @Trace: Dcm_SUD_API_60402 */
    (void) Dcm_WriteDid_InternalProcess(DCM_CANCEL, pMsgContext, &LddErrorCode);

    Dcm_ResetWriteDidOpStatus(Dcm_GusDIDIndexVal, Dcm_GblDIDRangePresent);
    Dcm_ServicePendingStatus.ucWriteDataByIdPendingStatus = DCM_FALSE;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmReadDataByIdentifier                         **
**                                                                            **
** Service ID           : 0x22                                                **
**                                                                            **
** Description          : This ReadDataByIdentifier service is used to get    **
**                        the value of one or more requested DID value.       **
**                        If the requested DID references several other DID   **
**                        the DCM module shall process the verification and   **
**                        the reading of every referenced DID                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : NA                                                  **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GusMaxNoOfRespPend,       **
**                        Dcm_GddNegRespError, Dcm_GblDIDNotSupportedSession, **
**                        Dcm_ServicePendingStatus,                           **
**                        Dcm_GblResOnPeriodicIdStatus, Dcm_GucPeriodicSID,   **
**                        Dcm_GaaDslPeriodicData,Dcm_IndexOfDslPeriodicData,  **
**                        Function(s) invoked :                               **
**                        Dcm_DsdValidateSession, Dcm_DsdValidateSecurity,    **
**              Dcm_DspInternal_ReadSigTypeNvMBlock, IoHwAb_Dcm_Read_<>,      **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadDataByIdentifier(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_00253 */
  Std_ReturnType LddRetVal = E_OK;

  Dcm_GusMaxNoOfRespPend = DCM_ZERO;
  Dcm_GddNegRespError = DCM_POS_RESP;

  if ((pMsgContext->reqDataLen < DCM_TWO) ||
     ((pMsgContext->reqDataLen % DCM_TWO) != DCM_ZERO))
  {
    /* @Trace: Dcm_SUD_API_60403 */
    Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60404 */
    #if (DCM_MAX_DID_TO_READ != DCM_ZERO)
    uint32 LulMaxLen;
    LulMaxLen = (uint32) ((uint32) DCM_MAX_DID_TO_READ << (uint32) DCM_ONE);

    /* @Trace: SWS_Dcm_01335 */
    if (pMsgContext->reqDataLen > LulMaxLen)
    {
      /* @Trace: Dcm_SUD_API_60405 */
      Dcm_GddNegRespError = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    else
    #endif
    {
      /* @Trace: Dcm_SUD_API_60406 */
      pMsgContext->resDataLen = DCM_ZERO;
      Dcm_DspInternal_DcmReadDataByIdentifier(DCM_INITIAL, pMsgContext);
    }
  }

  /* @Trace: Dcm_SUD_API_60407 */
  if (Dcm_ServicePendingStatus.ucReadDataPendingStatus == DCM_FALSE)
  {
    /* @Trace: Dcm_SUD_API_60409 */
    #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
    if (Dcm_GddPerStatus.blOnResTrans == DCM_TRUE)
    {
      /* @Trace: Dcm_SUD_API_60408 */
      uint8 LucDataIdx = Dcm_GddPerStatus.ucDataInfoIdx;

      SchM_Enter_Dcm_ProtclProtection();
      Dcm_GaaPerDataInfo[LucDataIdx].ucDataStatus = DCM_PDID_DATA_READY;
      Dcm_GaaPerDataInfo[LucDataIdx].ulDataLen = pMsgContext->resDataLen;
      SchM_Exit_Dcm_ProtclProtection();
    }
    #endif

    /* Send response from main function */
    Dcm_GblSendResponse = DCM_TRUE;
  }

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ReadDid_AuthValidate                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate access right and while list for did        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : didIndex, isDidRange                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_ReadDid_AuthValidate(
  uint16 didIndex,
  boolean isDidRange)
{
  /* @Trace: Dcm_SUD_API_60410 */
  Std_ReturnType LddResult;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  Dcm_DidInfoConfigConstPtrType LpDidInfo = NULL_PTR;
  Dcm_DidParaConfigConstPtrType LpDidConfig = NULL_PTR;

  /* Get did configuration by the index */
  LpDidConfig = Dcm_CfgInternal_GetDidConfig(didIndex);

  if (NULL_PTR != LpDidConfig)
  {
    /* @Trace: Dcm_SUD_API_60412 */
    uint16 LusDid = LpDidConfig->usDcmDspDidIdentifier;

    /* Only check access rigth for did in valid range */
    if ((LusDid < DCM_DDDID_UPPER_RANGE) || (LusDid > DCM_OBDDID_UPPER_RANGE))
    {
      /* @Trace: Dcm_SUD_API_60411 */
      /* Get did information configuration */
      LddResult = Dcm_DspInternal_GetDidInfo(didIndex, isDidRange, &LpDidInfo);

      if ((E_OK == LddResult) && 
          (NULL_PTR != LpDidInfo) && 
          (NULL_PTR != LpDidInfo->pDidRead))
      {
        /* @Trace: Dcm_SUD_API_60413 */
        Dcm_AuthenticationRoleType LddRole;

        Dcm_MemCopy(LddRole, LpDidInfo->pDidRead->DidReadRole, 
          DCM_AUTHENTICATION_ROLE_SIZE);

        if (DCM_FALSE == Dcm_ValidateAccessRights(LddRole))
        {
          /* @Trace: Dcm_SUD_API_60414 */
          #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON)
          uint8 LaaRecord[DCM_THREE];
          LaaRecord[DCM_ZERO] = DCM_U16_HI_BYTE(LusDid);
          LaaRecord[DCM_ONE] = DCM_U16_LO_BYTE(LusDid);
          LaaRecord[DCM_TWO] = DCM_DID_READ_ACCESS_MASK;

          if (DCM_FALSE == Dcm_ValidateAccessRightsWithWLDid(LaaRecord, DCM_THREE))
          #endif
          {
            /* @Trace: Dcm_SUD_API_60415 */
            LddErrorCode = DCM_E_AUTHENTICATIONREQUIRED;
          }
        }
      }
    }
  }

  return LddErrorCode;
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_DcmReadDataByIdentifier             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This ReadDataByIdentifier service is used to get    **
**                        the value of one or more requested DID value.       **
**                        If the requested DID references several other DID   **
**                        the DCM module shall process the verification and   **
**                        the reading of every referenced DID                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GusMaxNoOfRespPend,       **
**                        Dcm_GddNegRespError, Dcm_GblDIDNotSupportedSession, **
**                        Dcm_ServicePendingStatus,                           **
**                        Dcm_GblResOnPeriodicIdStatus, Dcm_GucPeriodicSID,   **
**                        Dcm_GaaDslPeriodicData,Dcm_IndexOfDslPeriodicData,  **
**                        Function(s) invoked :                               **
**                        Dcm_DsdValidateSession, Dcm_DsdValidateSecurity,    **
**              Dcm_DspInternal_ReadSigTypeNvMBlock, IoHwAb_Dcm_Read_<>,      **
**                        Dcm_ExternalSetNegResponse,                         **
**                        Dcm_ExternalProcessingDone                          **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA-C:8.3 [Justified:Low] Justify with annotations */
#if(DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspInternal_DcmReadDataByIdentifier(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType LddRetVal = E_OK;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  boolean LblDidRange = DCM_FALSE;
  uint8 LucReadDidState = DCM_READDID_STATE_READ_DID;

  uint16 LusDid = DCM_ZERO;
  uint16 LusDidIndex = DCM_ZERO;

  uint16 LusDidRefIndex = DCM_ZERO;
  uint16 LusNumRefDid = DCM_ZERO;

  uint16 LusIndex = DCM_ZERO;
  uint16 LusDidPos = DCM_ZERO;
  uint16 LusNumDid = (uint16) (pMsgContext->reqDataLen / DCM_SIZEOF_DATAID);
  
  DCM_SET_RDATA_PENDING_STATUS(DCM_FALSE);

  while ((LusIndex < LusNumDid) && (DCM_POS_RESP == LddErrorCode) && 
        ((E_OK == LddRetVal) || (DCM_E_NO_DID == LddRetVal)))
  {
    if (DCM_READDID_STATE_READ_DID == LucReadDidState)
    {
      /* @Trace: Dcm_SUD_API_60421 */
      LusDidPos = DCM_SIZEOF_DATAID * LusIndex;
      DCM_GET_DATAID_FROM_REQUEST(LusDid, pMsgContext->reqData, LusDidPos);

      /* Read 'DID' through a speficic function base on the type of DID */
      LddRetVal = Dcm_DspInternal_ReadDidType(
        OpStatus, pMsgContext, LusDid, &LddErrorCode);

      if (E_OK == LddRetVal)
      {
        /* @Trace: Dcm_SUD_API_60422 */
        /* Get index of DID, no need to check returned value */
        (void) Dcm_DspDidSearch(LusDid, &LusDidIndex, &LblDidRange);

        /* DidRef only support for Non OBD DID */
        if ((DCM_DID_TYPE_NONOBD == Dcm_DspGetDidType(Dcm_GusDIDIndexVal)) &&
            (NULL_PTR != Dcm_GaaDIDParaConfig[LusDidIndex].pDidRef))
        {
          /* @Trace: Dcm_SUD_API_60423 */
          LucReadDidState = DCM_READDID_STATE_READ_DIDREF;
        }
        else
        {
          LusIndex++;
        }
      }
      else if (DCM_E_NO_DID == LddRetVal)
      {
        LusIndex++;
      }
      else if (DCM_E_PENDING == LddRetVal)
      {
        /* Do nothing
         *  (1) pending status is already true
         *  (2) The current values remains
         *  (3) Retries the pended operation on each Dcm_Mainfunction
         */
      }
      else
      {
        /* @Trace: Dcm_SUD_API_60424 */
        LddRetVal = E_NOT_OK;
      }
    }

    if (DCM_READDID_STATE_READ_DIDREF == LucReadDidState)
    {
      /* @Trace: Dcm_SUD_API_60426 */
      LusNumRefDid = Dcm_GaaDIDParaConfig[LusDidIndex].usDidRefCount;

      while ((LusDidRefIndex < LusNumRefDid) && (DCM_POS_RESP == LddErrorCode)
             && ((E_OK == LddRetVal) || (DCM_E_NO_DID == LddRetVal)))
      {
        /* Get did reference */
        LusDid = Dcm_GaaDIDParaConfig[LusDidIndex].pDidRef[LusDidRefIndex];

        /* @Trace: SWS_Dcm_00440 */
        /* @Trace: Dcm_SUD_API_60427 */
        LddRetVal = Dcm_DspInternal_ReadDidType(
          OpStatus, pMsgContext, LusDid, &LddErrorCode);

        if ((E_OK == LddRetVal) || (DCM_E_NO_DID == LddRetVal))
        {
          /* @Trace: Dcm_SUD_API_60418 */
          LusDidRefIndex++;
        }
        else if (DCM_E_PENDING == LddRetVal)
        {
          /* Do nothing
           *  (1) pending status is already true
           *  (2) The current values remains
           *  (3) Retries the pended operation on each Dcm_Mainfunction */
        }
        else
        {
          /* @Trace: Dcm_SUD_API_60419 */
          LddRetVal = E_NOT_OK;
        }
      }

      /* Finished the DIDRef related operations */
      if ((LusDidRefIndex == LusNumRefDid) &&
         ((E_OK == LddRetVal) || (DCM_E_NO_DID == LddRetVal)))
      {
        /* @Trace: Dcm_SUD_API_60425 */
        LusIndex++;
        LucReadDidState = DCM_READDID_STATE_READ_DID;
      }
    }

    /* when number of DIDs larger than one, continute read the the next DID if the previous DID read failed */
    if ((DCM_ONE < LusNumDid ) 
        && (LusIndex < LusNumDid)
        && (DCM_POS_RESP != LddErrorCode)
        && (DCM_E_RESPONSETOOLONG != LddErrorCode)
        && (DCM_E_SECURITYACCESSDENIED != LddErrorCode)
        && (DCM_E_AUTHENTICATIONREQUIRED != LddErrorCode)
        && (DCM_E_CONDITIONSNOTCORRECT != LddErrorCode))
    {
      /* @Trace: Dcm_SUD_API_70471 */
	  /* Change NRC to positive to read the next DID except NRC 0x14 (DCM_E_RESPONSETOOLONG), 
       * NRC 0x33 (DCM_E_SECURITYACCESSDENIED), NRC 0x34 (DCM_E_AUTHENTICATIONREQUIRED) 
         NRC 0x22 (DCM_E_CONDITIONSNOTCORRECT) */
      LddErrorCode = DCM_POS_RESP;
    }

  }

  /* At least one DID is supported in the active session? */
  if ((LusIndex == LusNumDid) && (DCM_ZERO == pMsgContext->resDataLen))
  {
    /* @Trace: Dcm_SUD_API_60417 */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }
  /* Error occur */
  else if((LddErrorCode == DCM_E_RESPONSETOOLONG)
           ||(LddErrorCode == DCM_E_SECURITYACCESSDENIED)
           ||(LddErrorCode == DCM_E_AUTHENTICATIONREQUIRED)
           ||(LddErrorCode == DCM_E_CONDITIONSNOTCORRECT))
  {
    /* @Trace: Dcm_SUD_API_70469 */
    Dcm_GddNegRespError = LddErrorCode;
  }
  /* at leat 1 DID read successfully */
  else if (2U < pMsgContext->resDataLen)
  {
    /* @Trace: Dcm_SUD_API_70470 */
    Dcm_GddNegRespError = DCM_POS_RESP;
  }
  /* Other NRC, not NRC 0x14, 0x33, 0x34, 0x22 */
  else
  {
    /* @Trace: Dcm_SUD_API_60420 */
    Dcm_GddNegRespError = LddErrorCode;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspGetDidType                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to get the type of Did        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : usDidIndex                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_DidType                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Dcm_DidType, DCM_CODE) Dcm_DspGetDidType(
  uint16 usDidIndex)
{
  /* @Trace: Dcm_SUD_API_60428 */
  uint16 LusDid = DCM_ZERO;
  Dcm_DidType LddDidType = DCM_DID_TYPE_UNDEFINED;

  Dcm_DidParaConfigConstPtrType LpDidConfig;
  LpDidConfig = Dcm_CfgInternal_GetDidConfig(usDidIndex);

  if ((LpDidConfig != NULL_PTR) &&
      (LpDidConfig->pDidInfo != NULL_PTR))
  {
    /* @Trace: Dcm_SUD_API_60429 */
    LusDid = LpDidConfig->usDcmDspDidIdentifier;

    if ((LusDid >= DCM_DDDID_LOWER_RANGE) && 
        (LusDid <= DCM_DDDID_UPPER_RANGE) && 
        (LpDidConfig->pDidInfo->blDynamicallyDefined == DCM_TRUE))
    {
      /* @Trace: Dcm_SUD_API_60430 */
      LddDidType = DCM_DID_TYPE_DYN;
    }    
    else if (LusDid == DCM_READDATABYID_F810)
    {
      /* @Trace: Dcm_SUD_API_60432 */
      LddDidType = DCM_DID_TYPE_OBD_PROTOCOLID;
    }
    else if ((LusDid >= DCM_OBDDID_LOWER_RANGE) && 
            (LusDid <= DCM_OBDDID_UPPER_RANGE))
    {
      /* @Trace: Dcm_SUD_API_60431 */
      LddDidType = DCM_DID_TYPE_OBD;
    }
    else if (LusDid == DCM_READDATABYID_F186)
    {
      /* @Trace: Dcm_SUD_API_60432 */
      LddDidType = DCM_DID_TYPE_SESSION;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60433 */
      LddDidType = DCM_DID_TYPE_NONOBD;
    }
  }

  return LddDidType;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspValidateReadDid                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to validate session and security for the DID        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDIDIndex, LblDIDRangePresent                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_NegativeResponseCodeType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GblDIDNotSupportedSession **
**                        Dcm_GddNegRespError, Dcm_GaaDIDParaConfig,          **
**                        Dcm_GaaModeRuleConfig.                              **
**                        Function(s) invoked :                               **
**                        Dcm_GetSesCtrlType, Dcm_GetSecurityLevel            **
**                                                                            **
*******************************************************************************/
#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) || \
    (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspValidateReadDid(
  uint16 didIndex, 
  boolean isDidRange)
{
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  Std_ReturnType LddResult;
  Dcm_DidInfoConfigConstPtrType LpDidInfo = NULL_PTR;

  /* Get did information configuration */
  LddResult = Dcm_DspInternal_GetDidInfo(didIndex, isDidRange, &LpDidInfo);

  if ((E_OK == LddResult) && 
      (NULL_PTR != LpDidInfo) && (NULL_PTR != LpDidInfo->pDidRead))
  {
    /* @Trace: Dcm_SUD_API_60435 */
    LddErrorCode = Dcm_ReadDid_CheckAuthorization(LpDidInfo->pDidRead);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60434 */
    LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_ReadDid_CheckAuthorization                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate session, security and mode condition       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pDidRead                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_ReadDid_CheckAuthorization(
  Dcm_DidReadConfigConstPtrType pDidRead)
{
  /* @Trace: Dcm_SUD_API_60437 */
  boolean LblResult = DCM_TRUE;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  LblResult = Dcm_DsdValidateSession(
    pDidRead->pDidReadSession, pDidRead->ucDidReadSesCount);;

  if (DCM_TRUE == LblResult)
  {
    LblResult = Dcm_DsdValidateSecurity(
      pDidRead->pDidReadSecurity, pDidRead->ucDidReadSecCount);

    if (DCM_TRUE == LblResult)
    {
      /* @Trace: Dcm_SUD_API_60439 */
      #if (DCM_MODE_RULE == STD_ON)
      LddErrorCode = Dcm_CheckModeRule(
        pDidRead->blModeRuleConfigured, pDidRead->ucDIDmoderuleArrayindex);
      #endif
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60438 */
      LddErrorCode = DCM_E_SECURITYACCESSDENIED;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60436 */
    LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }

  return LddErrorCode;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidType                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the DID                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, DID                                       **
**                                                                            **
** InOut parameter      : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDymDefinedDIDInfoType, **
**                        Dcm_GaaDymMemDIDInfoType,                           **
**                        Dcm_GblResOnPeriodicIdStatus,                       **
**                        Dcm_GucRMBAMemoryIdentifier, Dcm_GddOpStatus,       **
**                        Dcm_GddNegRespError, Dcm_ServicePendingStatus,      **
**                        Dcm_GaaDidReadSignalData.                           **
**                        Function(s) : None                                  **
**                                                                            **
*******************************************************************************/
#if(DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidType(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 DID, Dcm_NegativeResponseCodeType *pErrorCode)
{
  Std_ReturnType retVal = DCM_E_NO_DID;

  uint8 LucDataBuffer[DCM_DSP_MAX_DID_SIZE];
  boolean LblIsRange = DCM_FALSE;
  boolean LblDIDSupported = DCM_FALSE;

  uint16 LusDIDIndex = DCM_ZERO;
  uint32 LulDataSize = DCM_ZERO;
  Dcm_DidParaConfigConstPtrType LpDidConfig = NULL_PTR;

  *pErrorCode = DCM_E_REQUESTOUTOFRANGE;

  if (DCM_TRUE == Dcm_DspDidSearch(DID, &LusDIDIndex, &LblIsRange))
  {
    if (DCM_TRUE == LblIsRange)
    {
      /* @Trace: SWS_Dcm_00433 */
      /* @Trace: Dcm_SUD_API_60451 */
      #if (DCM_NUM_OF_DCMDSPDIDRANGECONFIG > DCM_ZERO)
      Dcm_DidRangeConfigPtrType LpDidRangeConfig;
      LpDidRangeConfig = Dcm_CfgInternal_GetDidRangeConfig(LusDIDIndex);

      if ((NULL_PTR != LpDidRangeConfig) &&
          (NULL_PTR != LpDidRangeConfig->pDidInfo) &&
          (NULL_PTR != LpDidRangeConfig->pDidInfo->pDidRead))
      {
        /* @Trace: Dcm_SUD_API_60456 */
        LblDIDSupported = DCM_TRUE;
      }
      #endif
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60440 */
      /* @Trace: SWS_Dcm_00438 SWS_Dcm_00561 SWS_Dcm_00433 */
      LpDidConfig = Dcm_CfgInternal_GetDidConfig(LusDIDIndex);

      if ((NULL_PTR != LpDidConfig) &&
          (NULL_PTR != LpDidConfig->pDidInfo) &&
          (NULL_PTR != LpDidConfig->pDidInfo->pDidRead) &&
          (DCM_TRUE == LpDidConfig->blDspDidUsed))
      {
        /* @Trace: Dcm_SUD_API_60455 */
        LblDIDSupported = DCM_TRUE;
      }
    }
  }

  if (DCM_TRUE == LblDIDSupported)
  {
    #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
    /* @Trace: Dcm_SUD_API_60457 */
    /* @Trace: SWS_Dcm_01548 SWS_Dcm_01549 SWS_Dcm_01534 */
    *pErrorCode = Dcm_ReadDid_AuthValidate(LusDIDIndex, LblIsRange);

    if (DCM_POS_RESP == *pErrorCode)
    #endif
    {
      /* @Trace: Dcm_SUD_API_60458 */
      /* @Trace: SWS_Dcm_00434 SWS_Dcm_00435 SWS_Dcm_00819 */
      *pErrorCode = Dcm_DspValidateReadDid(LusDIDIndex, LblIsRange);
    }
  }

  if (DCM_POS_RESP == *pErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60459 */
    uint8 sizeOfDataId = DCM_ZERO;
    Dcm_DidType didKind = DCM_DID_TYPE_UNDEFINED;

    if (DCM_TRUE == LblIsRange)
    {
      /* @Trace: Dcm_SUD_API_60461 */
      #if (DCM_NUM_OF_DCMDSPDIDRANGECONFIG > DCM_ZERO)
      didKind = DCM_DID_TYPE_RANGE;
      #endif
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60460 */
      didKind = Dcm_DspGetDidType(Dcm_GusDIDIndexVal);
    }

    /* periodic DID size = 1, static did size = 2*/
    #if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
    if (Dcm_GddPerStatus.blOnResTrans == DCM_TRUE)
    {
      /* @Trace: Dcm_SUD_API_60442 */
      sizeOfDataId = DCM_ONE;
    }
    else
    #endif
    {
      /* @Trace: Dcm_SUD_API_60441 */
      sizeOfDataId = DCM_SIZEOF_DATAID;
    }

    if ((pMsgContext->resDataLen + sizeOfDataId) > pMsgContext->resMaxDataLen)
    {
      /* @Trace: Dcm_SUD_API_60443 */
      *pErrorCode = DCM_E_RESPONSETOOLONG;
      retVal = E_NOT_OK;
    }
    else if (didKind >= DCM_DID_TYPE_NUM)
    {
      /* @Trace: Dcm_SUD_API_60446 */
      retVal = DCM_E_NO_DID;
    }
    else if (NULL_PTR == Dcm_FuncPtrList_ReadDidType[didKind])
    {
      /* @Trace: Dcm_SUD_API_60444 */
      retVal = DCM_E_NO_DID;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60445 */
      DCM_SET_DATAID_IN_RESPONSE(pMsgContext->resData, pMsgContext->resDataLen, DID);

      /* Clear buffer to avoid unexpected data */
      Dcm_MemClear(&LucDataBuffer[DCM_ZERO], DCM_DSP_MAX_DID_SIZE);

      /* Main process for each type of DID */
      retVal = Dcm_FuncPtrList_ReadDidType[didKind](
        OpStatus, DID, LucDataBuffer, &LulDataSize, pErrorCode);

      if (E_OK == retVal)
      {
        /* Did range and Dynamically Defined Did will not support did size parameter */
        if ((NULL_PTR != LpDidConfig) && (DCM_TRUE == LpDidConfig->blDidSizeConfigured))
        {
          if (LulDataSize < LpDidConfig->usDidSize)
          {
            /* @Trace: SWS_Dcm_01385 */
            /* @Trace: Dcm_SUD_API_60447 */
            Dcm_MemClear(&LucDataBuffer[LulDataSize], LpDidConfig->usDidSize - LulDataSize);
          }

          /* @Trace: Dcm_SUD_API_60448 */
          /* @Trace: SWS_Dcm_01431 SWS_Dcm_01384 */
          LulDataSize = LpDidConfig->usDidSize;
        }

        if ((pMsgContext->resDataLen + LulDataSize) > pMsgContext->resMaxDataLen)
        {
          /* @Trace: Dcm_SUD_API_60449 */
          *pErrorCode = DCM_E_RESPONSETOOLONG;
          retVal = E_NOT_OK;
        }
        else
        {
          /* @Trace: Dcm_SUD_API_60450 */
          Dcm_MemCopy(&pMsgContext->resData[pMsgContext->resDataLen], LucDataBuffer, LulDataSize);
          pMsgContext->resDataLen += LulDataSize;
        }
      }
      else if (DCM_E_PENDING == retVal)
      {
        /* @Trace: Dcm_SUD_API_60452 */
        /* Reset response length and will update in next main function call */
        pMsgContext->resDataLen = DCM_ZERO;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_60453 Dcm_SUD_API_60454 */
        *pErrorCode = (DCM_POS_RESP == *pErrorCode) ? DCM_E_CONDITIONSNOTCORRECT : *pErrorCode;
        retVal = E_NOT_OK;
      }
    }
  }
  else if ((DCM_E_CONDITIONSNOTCORRECT == *pErrorCode) ||
           (DCM_E_SECURITYACCESSDENIED == *pErrorCode) ||
           (DCM_E_AUTHENTICATIONREQUIRED == *pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_70005 */
    retVal = E_NOT_OK;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_70006 */
    retVal = DCM_E_NO_DID;
  }

  return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeDDDID                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the requested Dynamic DID value from the    **
**                        Application.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : dataIdentifier, OpStatus                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize, pErrorCode                     **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Dcm_GaaDymDefinedDIDInfoType, **
**                        Dcm_GaaDymMemDIDInfoType,                           **
**                        Dcm_GblResOnPeriodicIdStatus,                       **
**                        Dcm_GucRMBAMemoryIdentifier, Dcm_GddOpStatus,       **
**                        Dcm_GddNegRespError, Dcm_ServicePendingStatus,      **
**                        Dcm_GaaDidReadSignalData.                           **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) && \
  (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeDDDID(
  Dcm_OpStatusType OpStatus,
  uint16 DataIdentifier,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode)
{
  uint8 LucNumOfSource = DCM_ZERO;
  Std_ReturnType LddRetVal = E_NOT_OK;

  uint16 LusDynDidIndex;
  Dcm_DynDidInfoPtrType LpDynDidInfo = NULL_PTR;

  *pDataSize = DCM_ZERO;

  if (DCM_TRUE == Dcm_DynDid_GetConfigIndex(DataIdentifier, &LusDynDidIndex))
  {
    /* @Trace: Dcm_SUD_API_60462 */
    /* Did Range feature cannot be applied for UDS 0x2C service */
    LpDynDidInfo = Dcm_CfgInternal_GetDynDidInfo(LusDynDidIndex);
  }

  if (NULL_PTR == LpDynDidInfo)
  {
    /* @Trace: Dcm_SUD_API_60473 */
    LddRetVal = E_NOT_OK;
    *pErrorCode = DCM_E_GENERALREJECT;
  }
  else
  {
    LucNumOfSource = LpDynDidInfo->ucMemAddCount + LpDynDidInfo->ucSourceDidCount;

    /* @Trace: SWS_Dcm_00651 */
    if ((DCM_FALSE == LpDynDidInfo->blActive) || (DCM_ZERO == LucNumOfSource))
    {
      /* @Trace: Dcm_SUD_API_60476 */
      LddRetVal = E_NOT_OK;
      *pErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60475 */
      LddRetVal = E_OK;
      *pErrorCode = DCM_POS_RESP;
    }
  }

  if (E_OK == LddRetVal)
  {
    /* @Trace: Dcm_SUD_API_60477 */
    uint8 LucPriority = DCM_ZERO;
    uint16 LusSrcDidIdx = DCM_ZERO;

    Dcm_MemAddInfoPtrType LpMemAddInfo = LpDynDidInfo->pMemAddInfo; 
    Dcm_SourceDidInfoPtrType LpSourceDidInfo = LpDynDidInfo->pSourceDidInfo;

    /* @Trace: SWS_Dcm_00652 */
    for (uint8 LucSrcIdx = DCM_ZERO; LucSrcIdx < LucNumOfSource; LucSrcIdx++)
    {
      /* @Trace: Dcm_SUD_API_60478 */
      LucPriority = LucSrcIdx + DCM_ONE;

      /**********************************
      *      defineByIdentifier         *
      **********************************/
      if (LucPriority == LpSourceDidInfo[LucSrcIdx].ucPriority)
      {
        boolean LblDidRange = DCM_FALSE;
        uint16 LusSrcDid = LpSourceDidInfo[LucSrcIdx].usSourceDid;

        if (DCM_TRUE != Dcm_DspDidSearch(LusSrcDid, &LusSrcDidIdx, &LblDidRange))
        {
          /* @Trace: Dcm_SUD_API_60464 */
          *pErrorCode  = DCM_E_REQUESTOUTOFRANGE;
        }
        else
        {
          /* @Trace: Dcm_SUD_API_60465 */
          /* @Trace: SWS_Dcm_00864, SWS_Dcm_00865 */
          #if(DCM_DYNAMIC_DID_PER_SOURCE == STD_ON)
          *pErrorCode = Dcm_DspValidateReadDid(LusSrcDidIdx, LblDidRange);
          #endif
        }

        if (DCM_POS_RESP != *pErrorCode)
        {
          /* @Trace: Dcm_SUD_API_60466 */
          LddRetVal = E_NOT_OK;
        }
        else
        {
          /* @Trace: Dcm_SUD_API_60468 */
          Dcm_DidType LddDidKind = DCM_DID_TYPE_UNDEFINED;

          if (LblDidRange == DCM_TRUE)
          {
            /* @Trace: Dcm_SUD_API_60469 */
            LddDidKind = DCM_DID_TYPE_RANGE;
          }
          else
          {
            /* @Trace: Dcm_SUD_API_60470 */
            LddDidKind = DCM_DID_TYPE_NONOBD;
          }

          if (NULL_PTR != Dcm_FuncPtrList_ReadDidType[LddDidKind])
          {
            /* @Trace: Dcm_SUD_API_60472 */
            uint32 LulResDataLen = *pDataSize;
            uint32 LulDataLen = LpSourceDidInfo[LucSrcIdx].ucMemSize;

            LddRetVal = Dcm_FuncPtrList_ReadDidType[LddDidKind](
              OpStatus, LusSrcDid, pDataOut, pDataSize, pErrorCode);

            if (E_OK == LddRetVal)
            {
              /* @Trace: Dcm_SUD_API_60474 */
              uint32 LulPosInSource = (uint32) LpSourceDidInfo[LucSrcIdx].ucPosInSource;
              uint32 LulOffsetResData = LulPosInSource - (uint32) DCM_ONE;

              Dcm_Uint8PtrType LpData = &pDataOut[LulResDataLen];
              Dcm_MemCopy(&LpData[DCM_ZERO], &LpData[LulOffsetResData], LulDataLen);

              /* Update the response length for the data updated */
              *pDataSize = LulResDataLen + LulDataLen;
            }
          }
          else
          {
            /* @Trace: Dcm_SUD_API_60471 */
            LddRetVal = E_NOT_OK;
            *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
          }
        }
      }
      /**********************************
      *    defineByMemoryAddress        *
      **********************************/
      else if (LucPriority == LpMemAddInfo[LucSrcIdx].ucPriority)
      {
        /* @Trace: SWS_Dcm_00653 */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "the function Dcm_ReadMemory has return 4 values.
        So, Dcm_DspInternal_ReadSigTypeMemory depend on returned value of function Dcm_ReadMemory." */
        LddRetVal = Dcm_DspInternal_ReadSigTypeMemory(
          OpStatus, 
          LpMemAddInfo[LucSrcIdx].ucMemoryId, 
          LpMemAddInfo[LucSrcIdx].ulMemAdd, 
          LpMemAddInfo[LucSrcIdx].ulMemSize,
          &pDataOut[*pDataSize], 
          pErrorCode);

        if (E_OK == LddRetVal)
        {
          /* @Trace: Dcm_SUD_API_60480 */
          *pErrorCode = DCM_POS_RESP;
          *pDataSize += LpMemAddInfo[LucSrcIdx].ulMemSize;     
        }
        else if (DCM_E_PENDING == LddRetVal)
        {
          /* @Trace: Dcm_SUD_API_60481 */
          DCM_SET_RDATA_PENDING_STATUS(DCM_TRUE);
        }
        else if(DCM_E_FORCE_RCRRP == LddRetVal)
        {
          /* @Trace: Dcm_SUD_API_60463 */
          LddRetVal = DCM_E_PENDING;
          DCM_SET_RDATA_PENDING_STATUS(DCM_TRUE);
        }
        else
        {
          /* @Trace: Dcm_SUD_API_70007 */
          /* pErrorCode is negative response code or DCM_CANCEL */
        }
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "the function Dcm_ReadMemory has return 4 values.
        So, Dcm_DspInternal_ReadSigTypeMemory depend on returned value of function Dcm_ReadMemory." */
      }
      /**********************************
      *          Error occur            *
      **********************************/
      else
      {
        /* @Trace: Dcm_SUD_API_60479 */
        LddRetVal = E_NOT_OK;
        *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      }

      /* Break the loop */
      if ((DCM_POS_RESP != *pErrorCode) || (E_NOT_OK == LddRetVal))
      {
        /* @Trace: Dcm_SUD_API_60467 */
        break;
      }
    }
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidByDataSpecificIf             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read Non OBD DID using data specific interface      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pDidConfig                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize, pErrorCode                     **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidByDataSpecificIf(
  Dcm_OpStatusType OpStatus,
  Dcm_DidParaConfigConstPtrType pDidConfig,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;

  uint8 LusSignalIndex = DCM_ZERO;
  uint8 LusNumOfSignal = pDidConfig->ucDcmDspSignalCount;
  uint8 LusSignalState = DCM_SIG_STATE_CONDITION_CHECK_READ;

  uint16 LusSizeOfSignal = DCM_ZERO;
  Dcm_DataConfigConstPtrType LpDataCfg = NULL_PTR;
  Dcm_DidSignalConfigPtrType LpSignalCfg = NULL_PTR;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpOutBuffer = NULL_PTR;

  /* Clear error code */
  *pErrorCode = DCM_POS_RESP;

  /* Checkes whether DID has at least one signal */
  if ((NULL_PTR != pDidConfig->pDcmDspSignal) && (DCM_ZERO != LusNumOfSignal))
  {
    /* @Trace: Dcm_SUD_API_60490 */
    while ((LusSignalIndex < LusNumOfSignal) && (E_OK == LddRetVal))
    {
      /* @Trace: Dcm_SUD_API_60491 */
      LpSignalCfg = &pDidConfig->pDcmDspSignal[LusSignalIndex];

      if (NULL_PTR == LpSignalCfg->pDataConfig)
      {
        /* @Trace: Dcm_SUD_API_60492 */
        DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM);
        *pErrorCode = DCM_E_GENERALREJECT;
        LddRetVal = E_NOT_OK;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_60493 */
        LpDataCfg = LpSignalCfg->pDataConfig;

        /* I. DCM_SIG_STATE_CONDITION_CHECK_READ phase
         *
         * Possibe errors
         *  (1) E_OK: keep going - 
         *      next step: DCM_SIG_STATE_READ_LEN for the current signal
         *  (2) E_NOT_OK : sends NRC
         *  (3) DCM_E_PENDING : 
         *      retries the current operation on each Dcm_MainFunction */
        if (DCM_SIG_STATE_CONDITION_CHECK_READ == LusSignalState)
        {
          /* @Trace: SWS_Dcm_00439 */
          /* @Trace: Dcm_SUD_API_70008 */
          LddRetVal = Dcm_DspInternal_ConditionCheckRead(OpStatus, 
            LpDataCfg, pErrorCode);

          if (E_OK == LddRetVal)
          {
            /* @Trace: Dcm_SUD_API_60495 */
            LusSignalState = DCM_SIG_STATE_READ_LEN;
          }
          else if (DCM_E_PENDING == LddRetVal)
          {
            /* @Trace: Dcm_SUD_API_60496 */
            /* Set response pending flag to True */
            DCM_SET_RDATA_PENDING_STATUS(DCM_TRUE);
          }
          else
          {
            /* @Trace: Dcm_SUD_API_60494 */
            /* pErrorCode is negative response code or DCM_CANCEL */
            LddRetVal = E_NOT_OK;
          }
        }

        /* II. DCM_SIG_STATE_READ_LEN
         *
         * Possibe errors
         *  (1) E_OK     : keep going - 
         *      next step: DCM_SIG_STATE_READ_SIGNAL for current signal
         *  (2) E_NOT_OK : sends NRC
         */
        if (DCM_SIG_STATE_READ_LEN == LusSignalState)
        {
          /* @Trace: SWS_Dcm_00436 */
          /* @Trace: Dcm_SUD_API_60497 */
          LddRetVal = Dcm_DspInternal_GetSizeOfDidSignal(OpStatus, 
            LpDataCfg, &LusSizeOfSignal);

          if (E_OK == LddRetVal)
          {
            if (DCM_ZERO != LusSizeOfSignal)
            {
              /* @Trace: Dcm_SUD_API_60484 */
              LusSignalState = DCM_SIG_STATE_READ_SIGNAL;
            }
            else
            {
              /* @Trace: Dcm_SUD_API_60485 */
              LusSignalIndex++;
              LusSignalState = DCM_SIG_STATE_CONDITION_CHECK_READ;
            }
          }
          else
          {
            /* @Trace: Dcm_SUD_API_60483 */
            LddRetVal = E_NOT_OK;
            *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
          }
        }

        /* III. DCM_SIG_STATE_READ_SIGNAL
         *
         * Possibe errors
         *  (1) E_OK          : keep going - 
         *      next step: DCM_SIG_STATE_CONDITION_CHECK_READ for a next signal
         *  (2_ E_NOT_OK      : sends NRC
         *  (3) DCM_E_PENDING : retries operation on each Dcm_MainFunction
         */
        if (DCM_SIG_STATE_READ_SIGNAL == LusSignalState)
        {
          /* @Trace: Dcm_SUD_API_60486 */
          LpOutBuffer = &Dcm_GaaDidReadSignalData[DCM_ZERO];

          /* @Trace: SWS_Dcm_00578 SWS_Dcm_00437 SWS_Dcm_00560 */
          LddRetVal = Dcm_DspInternal_ReadSigType(
            OpStatus, LpDataCfg, LpOutBuffer);

          if (E_OK == LddRetVal)
          {
            /* @Trace: SWS_Dcm_00638 */
            /* @Trace: Dcm_SUD_API_60487 */
            Dcm_DspReadDid_PackSignal(LusSizeOfSignal, 
              LpSignalCfg, LpOutBuffer, &pDataOut[*pDataSize]);

            *pDataSize += LusSizeOfSignal;

            LusSignalIndex++;
            LusSignalState = DCM_SIG_STATE_CONDITION_CHECK_READ;
          }
          else if (DCM_E_PENDING == LddRetVal)
          {
            /* @Trace: Dcm_SUD_API_60488 */
            /* Set response pending flag to True */
            DCM_SET_RDATA_PENDING_STATUS(DCM_TRUE);
          }
          else
          {
            /* @Trace: Dcm_SUD_API_60489 */
            /* pErrorCode is negative response code or DCM_CANCEL */
            LddRetVal = E_NOT_OK;
          }
        }
      }
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60482 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    LddRetVal = E_NOT_OK;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidByAtomicIf                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read Non OBD DID using atomic nv data interface or  **
**                        atomic sender receiver interface                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pDidConfig                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize, pErrorCode                     **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)) && \
  (DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidByAtomicIf(
  Dcm_OpStatusType OpStatus,
  Dcm_DidParaConfigConstPtrType pDidConfig,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  uint16 LusDidSize = DCM_ZERO;
  uint16 LusDataIdentifier = pDidConfig->usDcmDspDidIdentifier;
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) LpOutBuffer = &pDataOut[*pDataSize];

  /* @Trace: SWS_Dcm_01432 */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Return value depend on Application code."*/
  /* polyspace +1 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
  LddRetVal = Dcm_APIs_DidData(LusDataIdentifier, LpOutBuffer, &LusDidSize);

  if (E_OK == LddRetVal)
  {
    /* @Trace: Dcm_SUD_API_60499 */
    *pErrorCode = DCM_POS_RESP;
    *pDataSize += LusDidSize;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60498 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    LddRetVal = E_NOT_OK;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Return value depend on Application code."*/

  DCM_UNUSED(OpStatus);
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeNonOBDDID                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the requested Non OBD DID value from the    **
**                        Application.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : dataIdentifier, OpStatus                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize, pErrorCode                     **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeNonOBDDID(
  Dcm_OpStatusType OpStatus,
  uint16 DataIdentifier,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NegativeResponseCodeType *pErrorCode)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  Dcm_DidParaConfigConstPtrType LpDidConfig;
  LpDidConfig = Dcm_DspInternal_GetConfigByDid(DataIdentifier);

  if (NULL_PTR == LpDidConfig)
  {
    /* @Trace: Dcm_SUD_API_60500 */
    LddRetVal = E_NOT_OK;
    *pErrorCode = DCM_E_GENERALREJECT;
    DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM);
  }
  else
  {
    switch (LpDidConfig->ucDcmDspDidUsePort)
    {
      case USE_ATOMIC_NV_DATA_INTERFACE:
      case USE_ATOMIC_SENDER_RECEIVER_INTERFACE:
      case USE_ATOMIC_SENDER_RECEIVER_INTERFACE_AS_SERVICE:
        #if (DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON)
        /* @Trace: Dcm_SUD_API_60502 */
        LddRetVal = Dcm_DspInternal_ReadDidByAtomicIf(
          OpStatus, LpDidConfig, pDataOut, pDataSize, pErrorCode);
        #endif
        break;
      
      default:
        /* @Trace: Dcm_SUD_API_60501 */
        LddRetVal = Dcm_DspInternal_ReadDidByDataSpecificIf(
          OpStatus, LpDidConfig, pDataOut, pDataSize, pErrorCode);
        break;
    }
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspReadDid_PackSignal                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to pack the data for all signals of an DID.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LusDidIndex                                         **
**                                                                            **
** Output Parameters    : pMsgContext                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +6 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
static FUNC(void, DCM_CODE) Dcm_DspReadDid_PackSignal(
  uint16 bufferSize,
  Dcm_DidSignalConfigPtrType pSignalCfg,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pInBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pOutBuffer)
{
  /* @Trace: Dcm_SUD_API_60504 */
  Dcm_PackUnPackType LddPackSignal;
  LddPackSignal.usSignalSize = bufferSize;
  LddPackSignal.blByteConversion = pSignalCfg->blByteConversion;

  uint8 LucPackFuncIdx = pSignalCfg->ucPackFuncIndex;
  if (LucPackFuncIdx < DCM_NUM_OF_PACK_FUNC_CONFIG)
  {
    /* @Trace: Dcm_SUD_API_60505 */
    Dcm_GaaPackFunc[LucPackFuncIdx].pPackFunc(
      pInBuffer, pOutBuffer, &LddPackSignal);
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeOBDDID                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The Internal function is invoked for service 0x22   **
**                        to Read the requested OBD DID value from the        **
**                        Application.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : dataIdentifier, OpStatus                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize, pErrorCode                     **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* polyspace-begin MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidTypeOBDDID(
  Dcm_OpStatusType OpStatus,
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize,
  Dcm_NrcPtrType pErrorCode)
/* polyspace-end MISRA2012:8.13 [Justified:Low] Justify with annotations */
{
  Std_ReturnType LucResturnValue = E_NOT_OK;

  if ((DataId >= DCM_OBDDID_LOWER_RANGE) && (DataId <= DCM_OBDDID_RANGE_F4FF))
  {
    #if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
    /* @Trace: Dcm_SUD_API_60506 */
    Dcm_DspInternal_ReadDidTypeObdPid(OpStatus, DataId, pDataOut, pDataSize);
    #else
    /* @Trace: Dcm_SUD_API_60507 */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    #endif
  }
  else
  if ((DataId >= DCM_OBDDID_RANGE_F800) && (DataId <= DCM_OBDDID_UPPER_RANGE))
  {
    #if (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
    /* @Trace: Dcm_SUD_API_60508 */
    Dcm_DspInternal_ReadDidTypeObdVid(OpStatus, DataId, pDataOut, pDataSize);
    #else
    /* @Trace: Dcm_SUD_API_60509 */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    #endif
  }
  else
  if ((DataId >= DCM_OBDDID_RANGE_F600) && (DataId <= DCM_OBDDID_RANGE_F6FF))
  {
    #if (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON)
    /* @Trace: Dcm_SUD_API_60510 */
    Dcm_DspInternal_ReadDidTypeObdMid(OpStatus, DataId, pDataOut, pDataSize);
    #else
    /* @Trace: Dcm_SUD_API_60511 */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
    #endif
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60512 */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }

  #if ((DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON) || \
       (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON) || \
       (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON))
  if (DCM_POS_RESP == Dcm_GddNegRespError)
  {
    /* @Trace: Dcm_SUD_API_60513 */
    /* Remove OBD ID byte */
    *pDataSize = *pDataSize - DCM_ONE;

    /* Copy data from output buffer */
    Dcm_MemCopy(&pDataOut[DCM_ZERO], &pDataOut[DCM_ONE], *pDataSize);
    LucResturnValue = E_OK;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60514 */
    *pErrorCode = Dcm_GddNegRespError;
  }
  #else
  /* if no OBD services available, this function only return NRC */
  *pErrorCode = Dcm_GddNegRespError;
  DCM_UNUSED(pDataSize);
  DCM_UNUSED(pDataOut);
  #endif

  DCM_UNUSED(OpStatus);
  return LucResturnValue;
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeObdPid                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read Did inside the OBD PID range                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, DataId                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize                                 **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspInternal_ReadDidTypeObdPid(
  Dcm_OpStatusType OpStatus,
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize)
{
  #if (DCM_ENABLE_OBD_MIRROR == STD_ON)
  /* @Trace: Dcm_SUD_API_60515 */
  uint16 LusPidSize = DCM_ZERO;
  uint8 LucIdByte = DCM_U16_LO_BYTE(DataId);

  /* @Trace: SWS_Dcm_00481 SWS_Dcm_01195 */
  (void) Dcm_DspReadOBD_1_DemInfo(&LucIdByte, pDataOut, &LusPidSize, DCM_ONE);

  /* Set data size */
  *pDataSize = LusPidSize;

  DCM_UNUSED(OpStatus);
  #else
  /* @Trace: SWS_Dcm_01197 */
  /* @Trace: Dcm_SUD_API_60516 */
  (void) Dcm_DspInternal_ReadPidByUdsIf(OpStatus, DataId, pDataOut, pDataSize);
  #endif
}

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadPidByUdsIf                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read the Pid data by UDS interface                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, DataId                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize                                 **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_ENABLE_OBD_MIRROR == STD_OFF)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadPidByUdsIf(
  Dcm_OpStatusType OpStatus,
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  uint8 LucIdStatus;
  uint8 LucIdByte = DCM_U16_LO_BYTE(DataId);

  /* Get the type of OBD TID */
  LucIdStatus = Dcm_DspGetAvailibiltyIDStatus(
    DCM_GET_PID, &LucIdByte, DCM_ONE, DCM_ONE);

  if (DCM_AVAIL_ID == LucIdStatus)
  {
    /* @Trace: Dcm_SUD_API_60517 */
    LddRetVal = E_OK;

    /* Length = Number of IDs * five */
    *pDataSize = DCM_FIVE;

    /* @Trace: SWS_Dcm_01379 */
    (void) Dcm_DspReadOBD_AvlInfo(
      &LucIdByte, pDataOut, DCM_FIVE, DCM_ONE, DCM_OTHER_DID_OBD_RANGE);
  }
  else
  if ((DCM_R_PORT_PID == LucIdStatus) || (DCM_DEM_PID == LucIdStatus))
  {
    /* @Trace: Dcm_SUD_API_60519 */
    #if (DCM_OBD_DID_SUPPORT_INFO == STD_ON)
    uint8 LucSupportInfo = DCM_ZERO;

    /* @Trace: SWS_Dcm_01382 SWS_Dcm_01383 SWS_Dcm_00622 */
    if (E_OK == Dcm_DspInternal_GetDidSupportInfo(DataId, &LucSupportInfo))
    {
      /* @Trace: Dcm_SUD_API_60520 */
      LddRetVal = Dcm_FuncPtrList_ReadDidType[DCM_DID_TYPE_NONOBD](
        OpStatus, DataId, &pDataOut[DCM_TWO], pDataSize, &Dcm_GddNegRespError);

      /* Add support info byte */
      *pDataSize += DCM_ONE;
      pDataOut[DCM_ONE] = LucSupportInfo;
    }
    else
    #endif
    {
      /* @Trace: Dcm_SUD_API_60521 */
      /* @Trace: SWS_Dcm_01380 SWS_Dcm_01386 */
      LddRetVal = Dcm_FuncPtrList_ReadDidType[DCM_DID_TYPE_NONOBD](
        OpStatus, DataId, &pDataOut[DCM_ONE], pDataSize, &Dcm_GddNegRespError);
    }

    /* Add PID byte */
    *pDataSize += DCM_ONE;
    pDataOut[DCM_ZERO] = LucIdByte;
  }
  else
  {
    /* @Trace: SWS_Dcm_01381 */
    /* @Trace: Dcm_SUD_API_60518 */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }

  return LddRetVal;
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeObdVid                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read Did inside the OBD VID range                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, DataId                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize                                 **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_OBD_REQVEHICLE_INFO_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspInternal_ReadDidTypeObdVid(
  Dcm_OpStatusType OpStatus,
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize)
{
  #if (DCM_ENABLE_OBD_MIRROR == STD_ON)
  /* @Trace: Dcm_SUD_API_60522 */
  uint16 LusVidSize = DCM_ZERO;
  uint8 LucIdByte = DCM_U16_LO_BYTE(DataId);

  /* @Trace: SWS_Dcm_00483 SWS_Dcm_01195 */
  Dcm_DcmOBDRegVehicleInfoCall(&LucIdByte, pDataOut, 
    DCM_MAXVALUE, DCM_ONE, &LusVidSize);

  /* Set data size */
  *pDataSize = LusVidSize;

  DCM_UNUSED(OpStatus);
  #else
  /* @Trace: SWS_Dcm_01197 */
  /* @Trace: Dcm_SUD_API_60523 */
  (void) Dcm_DspInternal_ReadVidByUdsIf(OpStatus, DataId, pDataOut, pDataSize);
  #endif
}


/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadVidByUdsIf                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read the Vid data by UDS interface                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, DataId                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize                                 **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_ENABLE_OBD_MIRROR == STD_OFF)
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadVidByUdsIf(
  Dcm_OpStatusType OpStatus,
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  uint8 LucIdStatus;
  uint8 LucIdByte = DCM_U16_LO_BYTE(DataId);

  /* Get the type of OBD TID */
  LucIdStatus = Dcm_DspGetAvailibiltyIDStatus(
    DCM_GET_VID, &LucIdByte, DCM_ONE, DCM_NINE);

  if (DCM_AVAIL_ID == LucIdStatus)
  {
    /* @Trace: Dcm_SUD_API_60524 */
    LddRetVal = E_OK;

    /* Length = Number of IDs * five */
    *pDataSize += DCM_FIVE;

    /* @Trace: SWS_Dcm_01387 */
    (void) Dcm_DspReadOBD_AvlInfo(&LucIdByte,
      pDataOut, DCM_FIVE, DCM_ONE, DCM_OTHER_DID_INFOTYPE_RANGE);
  }
  else 
  if (DCM_OTHER_PID == LucIdStatus)
  {
    /* @Trace: SWS_Dcm_01389  */
    /* @Trace: Dcm_SUD_API_60525 */
    LddRetVal = Dcm_FuncPtrList_ReadDidType[DCM_DID_TYPE_NONOBD](
      OpStatus, DataId, &pDataOut[DCM_ONE], pDataSize, &Dcm_GddNegRespError);

    /* Add VID byte */
    *pDataSize += DCM_ONE;
    pDataOut[DCM_ZERO] = LucIdByte;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60526 */
    /* @Trace: SWS_Dcm_01388 SWS_Dcm_00275 */
    Dcm_GddNegRespError = DCM_E_REQUESTOUTOFRANGE;
  }

  return LddRetVal;
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidTypeObdMid                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read Did data inside the OBD Monitor range          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, DataId                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize                                 **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspInternal_ReadDidTypeObdMid(
  Dcm_OpStatusType OpStatus,
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize)
{
  /* @Trace: Dcm_SUD_API_60527 */
  uint8 LucIdByte = DCM_U16_LO_BYTE(DataId);
  uint16 LucMidSize = DCM_ZERO;

  /* @Trace: SWS_Dcm_00482 */
  Dcm_InternalOBDReqOnboadMonitorResultCall(
    &LucIdByte, pDataOut, DCM_ONE, &LucMidSize);

  /* Set data size */
  *pDataSize = LucMidSize;

  DCM_UNUSED(OpStatus);
}
#endif
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmInputOutputControlByIdentifier               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for UDS 0x2F service          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04218 */
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmInputOutputControlByIdentifier(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60528 */
  uint16 LusDidIndex = DCM_ZERO;
  Std_ReturnType LddRetVal = E_OK;

  Dcm_NegativeResponseCodeType LddErrorCode;
  LddErrorCode = Dcm_DspIOCtrl_ValidateRequest(pMsgContext, &LusDidIndex);

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60529 */
    /* Update global variables */
    Dcm_GusDIDIndexVal = LusDidIndex;
    Dcm_GucInOutParameter = pMsgContext->reqData[DCM_TWO];

    /* Invoke internal process function */
    (void) Dcm_DspIOCtrl_InternalProcess(
      DCM_INITIAL, pMsgContext, &LddErrorCode);
  }

  /* Determine if finish processing and update response */
  Dcm_DspIOCtrl_UpdateResponse(LusDidIndex, pMsgContext, LddErrorCode);

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_ValidateRequest                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main validation function for UDS 0x2F service       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : pMsgContext                                         **
**                                                                            **
** Output Parameters    : pDidIndex                                           **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspIOCtrl_ValidateRequest(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_Uint16PtrType pDidIndex)
{
  uint8 LucCtrlType = pMsgContext->reqData[DCM_TWO];
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  uint16 LusDataId;
  Dcm_DidParaConfigConstPtrType LpDidCfg = NULL_PTR;
  Dcm_MsgLenType LddReqLen = pMsgContext->reqDataLen;

  if (LddReqLen < DCM_IOCTRL_MINIMUM_LENGTH)
  {
    /* @Trace: Dcm_SUD_API_60530 */
    LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else if (LucCtrlType > DCM_SHORT_TERM_ADJUSTMENT)
  {
    /* @Trace: SWS_Dcm_00579 */
    /* @Trace: Dcm_SUD_API_60531 */
    LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60532 */
    /* Get data identifier from request message */
    LusDataId = Dcm_RequestParameterToUint16(DCM_TWO, pMsgContext->reqData);

    /* @Trace: SWS_Dcm_00563 SWS_Dcm_00564 SWS_Dcm_00565 */
    LddErrorCode = Dcm_DspIOCtrl_CheckDataId(LusDataId, pDidIndex);

    if (DCM_POS_RESP == LddErrorCode)
    {
      /* @Trace: Dcm_SUD_API_60533 */
      /* Get did configuration */
      LpDidCfg = Dcm_CfgInternal_GetDidConfig(*pDidIndex);

      /* @Trace: SWS_Dcm_01273 SWS_Dcm_01274 */
      LddErrorCode = Dcm_DspIOCtrl_CheckFullLength(
        LucCtrlType, LddReqLen, LpDidCfg);
    }

    if (DCM_POS_RESP == LddErrorCode)
    {
      /* @Trace: Dcm_SUD_API_60534 */
      LddErrorCode = Dcm_DspIOCtrl_CheckCtrlParameter(LucCtrlType, LpDidCfg);
    }
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_CheckDataId                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate all condition related to requested did     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : dataId                                              **
**                                                                            **
** Output Parameters    : pDidIndex                                           **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspIOCtrl_CheckDataId(
  uint16 dataId,
  Dcm_Uint16PtrType pDidIndex)
{
  /* @Trace: Dcm_SUD_API_60535 */
  uint16 LusDidIndex = DCM_ZERO;
  Dcm_DidInfoConfigConstPtrType LpDidInfo = NULL_PTR;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_E_REQUESTOUTOFRANGE;

  if (DCM_TRUE == Dcm_GetDidConfigIndex(dataId, &LusDidIndex))
  {
    /* @Trace: Dcm_SUD_API_60536 */
    /* Did Range feature can not be applied for UDS 0x2F service */
    (void) Dcm_DspInternal_GetDidInfo(LusDidIndex, DCM_FALSE, &LpDidInfo);

    if ((NULL_PTR != LpDidInfo) && (NULL_PTR != LpDidInfo->pDidControl))
    {
      #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
      /* @Trace: SWS_Dcm_01554 */
      /* @Trace: Dcm_SUD_API_60537 */
      LddErrorCode = Dcm_DspIOCtrl_AuthValidate(dataId, LpDidInfo->pDidControl);

      if (DCM_POS_RESP == LddErrorCode)
      #endif
      {
        /* @Trace: Dcm_SUD_API_60538 */
        /* @Trace: SWS_Dcm_00566 SWS_Dcm_00567 SWS_Dcm_00823 */
        LddErrorCode = Dcm_DspIOCtrl_CheckAuthorization(LpDidInfo->pDidControl);
      }

      if (DCM_POS_RESP == LddErrorCode)
      {
        /* @Trace: Dcm_SUD_API_60539 */
        *pDidIndex = LusDidIndex;
      }
    }
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_AuthValidate                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate access right for requested did             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : dataId, pDidCtrl                                    **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspIOCtrl_AuthValidate(
  uint16 dataId,
  Dcm_DidCtrlConstPtrType pDidCtrl)
{
  /* @Trace: Dcm_SUD_API_60541 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  Dcm_AuthenticationRoleType LddRole;
  Dcm_MemCopy(LddRole, pDidCtrl->ddDidCtrlRole, DCM_AUTHENTICATION_ROLE_SIZE);

  if (DCM_FALSE == Dcm_ValidateAccessRights(LddRole))
  {
    /* @Trace: Dcm_SUD_API_60542 */
    #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON)
    uint8 LaaRecord[DCM_THREE];
    LaaRecord[DCM_ZERO] = DCM_U16_HI_BYTE(dataId);
    LaaRecord[DCM_ONE] = DCM_U16_LO_BYTE(dataId);
    LaaRecord[DCM_TWO] = DCM_DID_CONTROL_ACCESS_MASK;

    if (DCM_FALSE == Dcm_ValidateAccessRightsWithWLDid(LaaRecord, DCM_THREE))
    #endif
    {
      /* @Trace: Dcm_SUD_API_60543 */
      LddErrorCode = DCM_E_AUTHENTICATIONREQUIRED;
    }
  }

  DCM_UNUSED(dataId);
  return LddErrorCode;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_CheckAuthorization                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate session, security and mode condition       **
**                        for requested did                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : pDidCtrl                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspIOCtrl_CheckAuthorization(
  Dcm_DidCtrlConstPtrType pDidCtrl)
{
  /* @Trace: Dcm_SUD_API_60545 */
  boolean LblResult = DCM_TRUE;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  LblResult = Dcm_DsdValidateSession(
    pDidCtrl->pDidCtrlSession, pDidCtrl->ucDidCtrlSesCount);

  if (DCM_TRUE == LblResult)
  {
    LblResult = Dcm_DsdValidateSecurity(
      pDidCtrl->pDidCtrlSecurity, pDidCtrl->ucDidCtrlSecCount);

    if (DCM_TRUE == LblResult)
    {
      /* @Trace: Dcm_SUD_API_60546 */
      #if (DCM_MODE_RULE == STD_ON)
      LddErrorCode = Dcm_CheckModeRule(
        pDidCtrl->blModeRuleConfigured, pDidCtrl->ucModeRuleIndex);
      #endif
    }
    else
    {
      /* @Trace: Dcm_SUD_API_70009 */
      LddErrorCode = DCM_E_SECURITYACCESSDENIED;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60544 */
    LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_CheckFullLength                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate full request message length                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : ctrlType, reqDataLen, pDidCfg                       **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspIOCtrl_CheckFullLength(
  uint8 ctrlType,
  Dcm_MsgLenType reqDataLen,
  Dcm_DidParaConfigConstPtrType pDidCfg)
{
  uint16 LusMinDidLen = DCM_ZERO;
  uint16 LusMaxDidLen = DCM_ZERO;

  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;
  uint32 LulMaskSize = Dcm_DspIOCtrl_GetCtrlMaskSize(pDidCfg);

  if (DCM_SHORT_TERM_ADJUSTMENT == ctrlType)
  {
    /* @Trace: Dcm_SUD_API_60549 */
    /* The size of min length and max length is calculated in byte */
    Dcm_DspInternal_GetSizeOfDid(pDidCfg, &LusMinDidLen, &LusMaxDidLen);

    if ((reqDataLen < (DCM_IOCTRL_MINIMUM_LENGTH + LulMaskSize + LusMinDidLen)) ||
        (reqDataLen > (DCM_IOCTRL_MINIMUM_LENGTH + LulMaskSize + LusMaxDidLen)))
    {
      /* @Trace: Dcm_SUD_API_60550 */
      LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60547 */
    if (reqDataLen != (DCM_IOCTRL_MINIMUM_LENGTH + LulMaskSize))
    {
      /* @Trace: Dcm_SUD_API_60548 */
      LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_CheckCtrlParameter                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check if input output control parameter is valid    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : ctrlType, pDidCfg                                   **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DspIOCtrl_CheckCtrlParameter(
  uint8 ctrlType,
  Dcm_DidParaConfigConstPtrType pDidCfg)
{
  /* @Trace: Dcm_SUD_API_60551 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if (NULL_PTR != pDidCfg)
  {
    Dcm_DidCtrlConstPtrType LpDidCtrl = pDidCfg->pDidInfo->pDidControl;

    /* @Trace: SWS_Dcm_CONSTR_6030 */
    if (((DCM_RETURN_CONTROL_TO_ECU == ctrlType) &&
        (DCM_FALSE == LpDidCtrl->blShrtTermAdj) &&
        (DCM_FALSE == LpDidCtrl->blResetToDefault) &&
        (DCM_FALSE == LpDidCtrl->blFreezeCrntState)) ||

        /* Check in case IOCP is Reset to Default  */
        ((DCM_RESET_TO_DEFAULT == ctrlType) &&
        (DCM_FALSE == LpDidCtrl->blResetToDefault)) ||

        /* Check in case IOCP is Freeze Current State */
        ((DCM_FREEZE_CURRENT_STATE == ctrlType) &&
        (DCM_FALSE == LpDidCtrl->blFreezeCrntState)) ||

        /* Check in case IOCP is Short Term Adjustment */
        ((DCM_SHORT_TERM_ADJUSTMENT == ctrlType) &&
        (DCM_FALSE == LpDidCtrl->blShrtTermAdj)))
    {
      /* @Trace: Dcm_SUD_API_60552 */
      LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }
  }
  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_InternalProcess                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Internal process function for UDS 0x2F service      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_InternalProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60555 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  Dcm_DidParaConfigConstPtrType LpDidCfg;
  
  Dcm_ServicePendingStatus.ucIocontrolPendingStatus = DCM_FALSE;
  Dcm_MemServicePendingStatus.ucIoCtrlReadDataPendingStatus = DCM_FALSE;

  LpDidCfg = Dcm_CfgInternal_GetDidConfig(Dcm_GusDIDIndexVal);

  if (NULL_PTR != LpDidCfg)
  {
    if (USE_DATA_ELEMENT_SPECIFIC_INTERFACES == LpDidCfg->ucDcmDspDidUsePort)
    {
      /* @Trace: SWS_Dcm_01434 */
      /* @Trace: Dcm_SUD_API_60553 */
      LddRetVal = Dcm_DspIOCtrl_DataInterfaceProcess(
        OpStatus, pMsgContext, LpDidCfg, pErrorCode);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60554 */
      #if ((DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON) && \
           (DCM_MAX_CONTROL_MASK_SIZE != DCM_ZERO))
      LddRetVal = Dcm_DspIOCtrl_SrInterfaceProcess(
        OpStatus, pMsgContext, LpDidCfg, pErrorCode);
      #endif
    }

    if ((DCM_POS_RESP == *pErrorCode) &&
        (DCM_FALSE == Dcm_ServicePendingStatus.ucIocontrolPendingStatus))
    {
      /* @Trace: Dcm_SUD_API_60556 */
      /* @Trace: SWS_Dcm_00640 SWS_Dcm_00682 */
      LddRetVal = Dcm_DspIOCtrl_ReadData(
        OpStatus, pMsgContext, LpDidCfg, pErrorCode);
    }
  }
  
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_ReadData                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read the data of did and copy to response buffer    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : OpStatus, pMsgContext, pDidCfg                      **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_ReadData(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DidParaConfigConstPtrType pDidCfg,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60561 */
  Std_ReturnType LddRetVal;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  uint32 LulDataSize = DCM_ZERO;
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) LpOutBuffer;
  LpOutBuffer = (void *) &Dcm_GaaDIDSignalOutData[DCM_ZERO];

  /* Do not support Did Range, Dynamically Did and Obd Did */
  /* polyspace +4 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
  /* polyspace +3 CERT-C:EXP36-C [Justified:Low] "LpOutBuffer depend on configured Read DID function. No Impact" */
  LddRetVal = Dcm_DspInternal_ReadDidTypeNonOBDDID(
    OpStatus, pDidCfg->usDcmDspDidIdentifier, 
    LpOutBuffer, &LulDataSize, &LddErrorCode);

  if (DCM_CANCEL != OpStatus)
  {
    switch (LddRetVal)
    {
      case E_OK:
        /* @Trace: Dcm_SUD_API_60558 */
        pMsgContext->resDataLen = LulDataSize;
        /* polyspace +2 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
        /* polyspace +1 CERT-C:EXP36-C [Justified:Low] "LpOutBuffer depend on configured Read DID function. No Impact" */
        Dcm_MemCopy(&pMsgContext->resData[DCM_THREE], LpOutBuffer, LulDataSize);
        break;

      case DCM_E_PENDING:
        /* @Trace: Dcm_SUD_API_60559 */
        Dcm_ServicePendingStatus.ucReadDataPendingStatus = DCM_FALSE;
        Dcm_MemServicePendingStatus.ucIoCtrlReadDataPendingStatus = DCM_TRUE;
        break;

      default:
        /* @Trace: Dcm_SUD_API_60560 */
        LddRetVal = E_NOT_OK;
        *pErrorCode = LddErrorCode;
        break;
    }
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_ReturnControlToECU                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call return control to ecu function                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : OpStatus, pDataCfg                                  **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_ReturnControlToECU(
  Dcm_OpStatusType OpStatus,
  Dcm_DataConfigConstPtrType pDataCfg,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60562 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ((NULL_PTR != pDataCfg) && (NULL_PTR != pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_60564 */
    *pErrorCode = DCM_POS_RESP;

    switch (pDataCfg->ucDcmDspDataUsePort)
    {
      case USE_ECU_SIGNAL:
        /* @Trace: SWS_Dcm_00580 */
        /* @Trace: Dcm_SUD_API_60563 */
        LddRetVal = Dcm_CfgInternal_IOControlSigTypeEcuSignal(
          pDataCfg, DCM_RETURN_CONTROL_TO_ECU, NULL_PTR, pErrorCode);
        break;

      default:
        /* Limited to non S/R interfaces */
        if (NULL_PTR != pDataCfg->pReturnControlToEcuFun)
        {
          /* @Trace: Dcm_SUD_API_60565 */
          LddRetVal = pDataCfg->pReturnControlToEcuFun(pErrorCode);
        }
        break;
    }

    /* @Trace: SWS_Dcm_00271 */
    if ((E_NOT_OK == LddRetVal) && (DCM_POS_RESP == *pErrorCode))
    {
      /* @Trace: Dcm_SUD_API_60566 */
      *pErrorCode = DCM_E_GENERALREJECT;
    }
  }

  DCM_UNUSED(OpStatus);
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_ResetToDefault                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call reset to default function                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : OpStatus, pDataCfg                                  **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_ResetToDefault(
  Dcm_OpStatusType OpStatus,
  Dcm_DataConfigConstPtrType pDataCfg,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60568 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ((NULL_PTR != pDataCfg) && (NULL_PTR != pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_60569 */
    *pErrorCode = DCM_POS_RESP;

    switch (pDataCfg->ucDcmDspDataUsePort)
    {
      case USE_ECU_SIGNAL:
        /* @Trace: SWS_Dcm_00580 */
        /* @Trace: Dcm_SUD_API_60570 */
        LddRetVal = Dcm_CfgInternal_IOControlSigTypeEcuSignal(
          pDataCfg, DCM_RESET_TO_DEFAULT, NULL_PTR, pErrorCode);
        break;

      case USE_DATA_SYNCH_FNC:
      case USE_DATA_SYNCH_CLIENT_SERVER:
        if (NULL_PTR != pDataCfg->pResetToDefaultSyncFun)
        {
          /* @Trace: Dcm_SUD_API_60571 */
          LddRetVal = pDataCfg->pResetToDefaultSyncFun(pErrorCode);
        }
        break;

      default:
        if (NULL_PTR != pDataCfg->pResetToDefaultAsyncFun)
        {
          /* @Trace: Dcm_SUD_API_60572 */
          LddRetVal = pDataCfg->pResetToDefaultAsyncFun(OpStatus, pErrorCode);
        }
        break;
    }

    /* @Trace: SWS_Dcm_00271 */
    if ((E_NOT_OK == LddRetVal) && (DCM_POS_RESP == *pErrorCode))
    {
      /* @Trace: Dcm_SUD_API_60575 */
      *pErrorCode = DCM_E_GENERALREJECT;
    }
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_FreezeCurrentState                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call freeze current state function                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : OpStatus, pDataCfg                                  **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_FreezeCurrentState(
  Dcm_OpStatusType OpStatus,
  Dcm_DataConfigConstPtrType pDataCfg,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60576 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ((NULL_PTR != pDataCfg) && (NULL_PTR != pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_60577 */
    *pErrorCode = DCM_POS_RESP;

    switch (pDataCfg->ucDcmDspDataUsePort)
    {
      case USE_ECU_SIGNAL:
        /* @Trace: SWS_Dcm_00580 */
        /* @Trace: Dcm_SUD_API_60578 */
        LddRetVal = Dcm_CfgInternal_IOControlSigTypeEcuSignal(
        pDataCfg, DCM_FREEZE_CURRENT_STATE, NULL_PTR, pErrorCode);
        break;

      case USE_DATA_SYNCH_FNC:
      case USE_DATA_SYNCH_CLIENT_SERVER:
        if (NULL_PTR != pDataCfg->pFreezeCurrentStateSyncFun)
        {
          /* @Trace: Dcm_SUD_API_60579 */
          LddRetVal = pDataCfg->pFreezeCurrentStateSyncFun(pErrorCode);
        }
        break;

      default:
        if (NULL_PTR != pDataCfg->pFreezeCurrentStateAsyncFun)
        {
          /* @Trace: Dcm_SUD_API_60580 */
          LddRetVal = pDataCfg->pFreezeCurrentStateAsyncFun(
            OpStatus, pErrorCode);
        }
        break;
    }

    /* @Trace: SWS_Dcm_00271 */
    if ((E_NOT_OK == LddRetVal) && (DCM_POS_RESP == *pErrorCode))
    {
      /* @Trace: Dcm_SUD_API_60582 */
      *pErrorCode = DCM_E_GENERALREJECT;
    }
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_ShortTermAdjustment                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call short term adjustment function                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : OpStatus, dataLength, pDataCfg, pCtrlStateInfo      **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* polyspace +6 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_ShortTermAdjustment(
  Dcm_OpStatusType OpStatus,
  uint16 dataLength,
  Dcm_DataConfigConstPtrType pDataCfg,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pCtrlStateInfo,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60584 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ((NULL_PTR != pDataCfg) && (NULL_PTR != pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_60587 */
    *pErrorCode = DCM_POS_RESP;

    switch (pDataCfg->ucDcmDspDataUsePort)
    {
      case USE_ECU_SIGNAL:
        /* @Trace: SWS_Dcm_00580 */
        /* @Trace: Dcm_SUD_API_60588 */
        LddRetVal = Dcm_CfgInternal_IOControlSigTypeEcuSignal(
          pDataCfg, DCM_SHORT_TERM_ADJUSTMENT, pCtrlStateInfo, pErrorCode);
        break;

      case USE_DATA_SYNCH_FNC:
      case USE_DATA_SYNCH_CLIENT_SERVER:
        if (NULL_PTR != pDataCfg->pShortTermAdjustmentFixedSyncFun)
        {
          /* @Trace: Dcm_SUD_API_60589 */
          /* polyspace +3 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
          /* polyspace +2 CERT-C:EXP36-C [Justified:Low] "pCtrlStateInfo depend on configuration of pShortTermAdjustmentFixedSyncFun. No Impact" */
          LddRetVal = pDataCfg->pShortTermAdjustmentFixedSyncFun(
            pCtrlStateInfo, pErrorCode);
        }

        if (NULL_PTR != pDataCfg->pShortTermAdjustmentDynSyncFun)
        {
          /* @Trace: Dcm_SUD_API_60590 */
          /* polyspace +3 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
          /* polyspace +2 CERT-C:EXP36-C [Justified:Low] "pCtrlStateInfo depend on configuration of pShortTermAdjustmentDynSyncFun. No Impact" */
          LddRetVal = pDataCfg->pShortTermAdjustmentDynSyncFun(
            pCtrlStateInfo, dataLength, pErrorCode);
        }
        break;

      default:
        if (NULL_PTR != pDataCfg->pShortTermAdjustmentFixedAsyncFun)
        {
          /* @Trace: Dcm_SUD_API_60592 */
          /* polyspace +3 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
          /* polyspace +2 CERT-C:EXP36-C [Justified:Low] "pCtrlStateInfo depend on configuration of pShortTermAdjustmentFixedAsyncFun. No Impact" */
          LddRetVal = pDataCfg->pShortTermAdjustmentFixedAsyncFun(
            pCtrlStateInfo, OpStatus, pErrorCode);
        }

        if (NULL_PTR != pDataCfg->pShortTermAdjustmentDynAsyncFun)
        {
          /* @Trace: Dcm_SUD_API_60593 */
          /* polyspace +3 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
          /* polyspace +2 CERT-C:EXP36-C [Justified:Low] "pCtrlStateInfo depend on configuration of pShortTermAdjustmentDynAsyncFun. No Impact" */
          LddRetVal = pDataCfg->pShortTermAdjustmentDynAsyncFun(
            pCtrlStateInfo, dataLength, OpStatus, pErrorCode);
        }
        break;
    }

    if ((E_NOT_OK == LddRetVal) && (DCM_POS_RESP == *pErrorCode))
    {
      /* @Trace: Dcm_SUD_API_60585 */
      *pErrorCode = DCM_E_GENERALREJECT;
    }
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_GetCtrlMaskSize                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the control mask size from configuration        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : pDidCfg                                             **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LulCtrlMaskSize                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(uint32, DCM_CODE) Dcm_DspIOCtrl_GetCtrlMaskSize(
  Dcm_DidParaConfigConstPtrType pDidCfg)
{
  /* @Trace: Dcm_SUD_API_60595 */
  uint32 LulCtrlMaskSize = DCM_ZERO;
  if (NULL_PTR != pDidCfg)
  {
    Dcm_DidCtrlConstPtrType LpDidCtrl = pDidCfg->pDidInfo->pDidControl;

    if (NULL_PTR != LpDidCtrl)
    {
      /* @Trace: Dcm_SUD_API_60596 */
      LulCtrlMaskSize = LpDidCtrl->ulDidControlMaskSize;
    }
  }
  return LulCtrlMaskSize;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_UnPackSignal                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Unpact the signal in case short term adjustment     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : inBufferSize, pSignalCfg, pInBuffer                 **
**                                                                            **
** Output Parameters    : pOutBuffer                                          **
**                                                                            **
** Return parameter     : LusDataLength                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(uint16, DCM_CODE) Dcm_DspIOCtrl_UnPackSignal(
  uint32 inBufferSize,
  Dcm_DidSignalConfigPtrType pSignalCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pInBuffer,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutBuffer)
{
  uint16 LusDataLength = DCM_ZERO;
  Dcm_PackUnPackType LddUnPackSignal;

  /* Only the last signal may have variable length */
  if (DCM_DATA_TYPE_UINT8_DYN == pSignalCfg->pDataConfig->ucDcmDspDataType)
  {
    /* @Trace: Dcm_SUD_API_60597 */
    LusDataLength = (uint16) inBufferSize - pSignalCfg->usByteOffset;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60598 */
    LusDataLength = pSignalCfg->pDataConfig->usDcmDspDataByteSize;
  }

  if (DCM_ZERO != LusDataLength)
  {
    /* @Trace: Dcm_SUD_API_60599 */
    LddUnPackSignal.usSignalSize = LusDataLength;
    LddUnPackSignal.blByteConversion = pSignalCfg->blByteConversion;

    uint8 LucUnPackFuncIdx = pSignalCfg->ucUnPackFuncIndex;
    if (LucUnPackFuncIdx < DCM_NUM_OF_UNPACK_FUNC_CONFIG)
    {
      /* @Trace: Dcm_SUD_API_60600 */
      Dcm_GaaUnPackFunc[LucUnPackFuncIdx].pUnPackFunc(
        pOutBuffer,
        &pInBuffer[pSignalCfg->usByteOffset],
        &LddUnPackSignal);
    }
  }

  return LusDataLength;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_DataSignalProcess                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Dispatch signal function based on control parameter **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : OpStatus, pMsgContext, ctrlStateSize, pSignalCfg    **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_DataSignalProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  uint32 ctrlStateSize,
  Dcm_DidSignalConfigPtrType pSignalCfg,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60601 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucCtrlType = pMsgContext->reqData[DCM_TWO];
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  uint16 LusDataLen = DCM_ZERO;
  Dcm_DataConfigConstPtrType LpDataCfg = pSignalCfg->pDataConfig;

  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) LpOutBuffer;
  LpOutBuffer = (void *) &Dcm_GaaDIDSignalData[DCM_ZERO];
  
  /* Check if requested signal data is already traverse or not */
  if (DCM_OPSTATUS_COMPLETE != pSignalCfg->ucSignalOpStatus)
  {
    switch (LucCtrlType)
    {
      /* @Trace: SWS_Dcm_00399 */
      case DCM_SHORT_TERM_ADJUSTMENT:
        /* @Trace: Dcm_SUD_API_60602 */
        LusDataLen = Dcm_DspIOCtrl_UnPackSignal(ctrlStateSize, pSignalCfg, 
          &pMsgContext->reqData[DCM_THREE], LpOutBuffer);

        LddRetVal = Dcm_DspIOCtrl_ShortTermAdjustment(
          OpStatus, LusDataLen, LpDataCfg, LpOutBuffer, &LddErrorCode);
        break;

      /* @Trace: SWS_Dcm_00396 */
      case DCM_RETURN_CONTROL_TO_ECU:
        /* @Trace: Dcm_SUD_API_60603 */
        LddRetVal = Dcm_DspIOCtrl_ReturnControlToECU(OpStatus, 
          LpDataCfg, &LddErrorCode);
        break;

      /* @Trace: SWS_Dcm_00397 */
      case DCM_RESET_TO_DEFAULT:
        /* @Trace: Dcm_SUD_API_60604 */
        LddRetVal = Dcm_DspIOCtrl_ResetToDefault(OpStatus, 
          LpDataCfg, &LddErrorCode);
        break;

      /* @Trace: SWS_Dcm_00398 */
      case DCM_FREEZE_CURRENT_STATE:
        /* @Trace: Dcm_SUD_API_60605 */
        LddRetVal = Dcm_DspIOCtrl_FreezeCurrentState(OpStatus, 
          LpDataCfg, &LddErrorCode);
        break;

      default:
        /* @Trace: Dcm_SUD_API_60606 */
        /* No action in this case */
        break;
    }

    if (OpStatus != DCM_CANCEL)
    {
      switch (LddRetVal)
      {
        case E_OK:
          /* @Trace: Dcm_SUD_API_60607 */
          pSignalCfg->ucSignalOpStatus = DCM_OPSTATUS_COMPLETE;
          break;

        case DCM_E_PENDING:
          /* @Trace: Dcm_SUD_API_60608 */
          pSignalCfg->ucSignalOpStatus = DCM_OPSTATUS_PENDING;
          Dcm_ServicePendingStatus.ucIocontrolPendingStatus = DCM_TRUE;
          break;

        default:
          /* @Trace: Dcm_SUD_API_60609 */
          LddRetVal = E_NOT_OK;
          *pErrorCode = LddErrorCode;
          break;
      }
    }
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_DataInterfaceProcess                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function for process Did in case use port      **
**                        is configured as data element specific interface    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : OpStatus, pMsgContext, pDidCfg                      **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_DataInterfaceProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DidParaConfigConstPtrType pDidCfg,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_60612 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  uint8 LucSignalIdx = DCM_ZERO;
  uint8 LucNumOfSignal = pDidCfg->ucDcmDspSignalCount;

  uint32 LulMaskSize = Dcm_DspIOCtrl_GetCtrlMaskSize(pDidCfg);
  uint32 LulCtrlStateSize = pMsgContext->reqDataLen - (DCM_THREE + LulMaskSize);

  Dcm_Uint8PtrType LpCtrlMaskRecord;
  LpCtrlMaskRecord = &pMsgContext->reqData[DCM_THREE + LulCtrlStateSize];

  /* @Trace: SWS_Dcm_00581 SWS_Dcm_00680 */
  while ((LucSignalIdx < LucNumOfSignal) && (DCM_POS_RESP == *pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_60610 */
    uint8 LucRecordIdx = LucSignalIdx / DCM_EIGHT;
    uint8 LucSignalMaskValue = DCM_ONE_TWO_EIGHT >> (LucSignalIdx % DCM_EIGHT);

    if ((DCM_ONE == LucNumOfSignal) ||
        (DCM_ZERO != (LpCtrlMaskRecord[LucRecordIdx] & LucSignalMaskValue)))
    {
      /* @Trace: Dcm_SUD_API_60611 */
      Dcm_DidSignalConfigPtrType LpSignalCfg;
      LpSignalCfg = &pDidCfg->pDcmDspSignal[LucSignalIdx];

      LddRetVal = Dcm_DspIOCtrl_DataSignalProcess(
        OpStatus, pMsgContext, LulCtrlStateSize, LpSignalCfg, pErrorCode);
    }

    LucSignalIdx++;
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_CalculateUnderCtrl                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Calculate under control element in atomic interface **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : ctrlType, numOfSignal, pCtrlMaskRecord              **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if ((DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON) && \
     (DCM_MAX_CONTROL_MASK_SIZE != DCM_ZERO))
/* polyspace-begin MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(void, DCM_CODE) Dcm_DspIOCtrl_CalculateUnderCtrl(
  uint8 ctrlType,
  uint8 numOfSignal,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pCtrlMaskRecord)
/* polyspace-end MISRA2012:8.13 [Justified:Low] Justify with annotations */
{
  uint8 LucSignalIdx;
  uint8 LucRecordIdx;
  uint8 LucSignalMaskValue;

  /* @Trace: Dcm_SUD_API_60616 */
  for (LucSignalIdx = DCM_ZERO; LucSignalIdx < numOfSignal; LucSignalIdx++)
  {
    /* @Trace: Dcm_SUD_API_60613 */
    LucRecordIdx = LucSignalIdx / DCM_EIGHT;
    LucSignalMaskValue = DCM_ONE_TWO_EIGHT >> (LucSignalIdx % DCM_EIGHT);

    /* Check if the signal is affected by request message */
    if (DCM_ZERO != (pCtrlMaskRecord[LucRecordIdx] & LucSignalMaskValue))
    {
      if (DCM_RETURN_CONTROL_TO_ECU != ctrlType)
      {
        /* @Trace: Dcm_SUD_API_60615 */
        /* Set the coressponding bit in under control buffer */
        Dcm_GaaUnderControl[LucRecordIdx] |= LucSignalMaskValue;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_60614 */
        /* Clear the coressponding bit in under control buffer */
        Dcm_GaaUnderControl[LucRecordIdx] &= (~ LucSignalMaskValue);
      }
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_ProcessCallAtomicRequest              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call atomic input output control request interface  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : dataId, parameterType, pControlMask, pControlState  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if ((DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON) && \
     (DCM_MAX_CONTROL_MASK_SIZE != DCM_ZERO))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_ProcessCallAtomicRequest(
  uint16 dataId,
  Dcm_InputOutputControlParameterType parameterType,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pControlMask,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pControlState,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal;

  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Return value depend on Application code."*/
  LddRetVal = Dcm_APIs_IOOperationRequest(dataId, parameterType, pControlMask);

  if (E_OK == LddRetVal)
  {
    /* @Trace: Dcm_SUD_API_60617 */
    LddRetVal = Dcm_APIs_UnderControl(dataId, &Dcm_GaaUnderControl[DCM_ZERO]);
  }

  if ((E_OK == LddRetVal) && (DCM_SHORT_TERM_ADJUSTMENT == parameterType))
  {
    /* @Trace: Dcm_SUD_API_60618 */
    LddRetVal = Dcm_APIs_ControlState(dataId, pControlState);
  }

  if (E_OK == LddRetVal)
  {
    /* @Trace: Dcm_SUD_API_60620 */
    /* The response element will be call at next main function */
    Dcm_ServicePendingStatus.ucIocontrolPendingStatus = DCM_TRUE;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60619 */
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Return value depend on Application code."*/

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_ProcessCallAtomicResponse             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call atomic input output control response interface **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : dataId, pControlMask, pMsgContext                   **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if ((DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON) && \
     (DCM_MAX_CONTROL_MASK_SIZE != DCM_ZERO))
/* polyspace-begin MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_ProcessCallAtomicResponse(
  uint16 dataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pControlMask,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode)
/* polyspace-end MISRA2012:8.13 [Justified:Low] Justify with annotations */
{
  Std_ReturnType LddRetVal;
  Dcm_IOOperationResponseType LddOperationResponse;

  /* Call atomic sender receiver io control response interface */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Return value depends on application code."*/
  LddRetVal = Dcm_APIs_IOOperationResponse(dataId, &LddOperationResponse);

  if (E_OK == LddRetVal)
  {
    switch (LddOperationResponse)
    {
      case DCM_POSITIVE_RESPONSE:
        /* @Trace: Dcm_SUD_API_60622 */
        /* @Trace: SWS_Dcm_01437 SWS_Dcm_01438 */
        (void) Dcm_APIs_IOOperationRequest(dataId, DCM_IDLE, pControlMask);
        break;

      case DCM_RESPONSE_PENDING:
        /* @Trace: Dcm_SUD_API_60623 */
        /* Action similar to E_PENDING */
        LddRetVal = DCM_E_PENDING;

        /* @Trace: SWS_Dcm_01441 */
        Dcm_ServicePendingStatus.ucIocontrolPendingStatus = DCM_TRUE;
        break;

      default:
        /* @Trace: Dcm_SUD_API_60624 */
        LddRetVal = E_NOT_OK;

        /* @Trace: SWS_Dcm_01440 */
        *pErrorCode = LddOperationResponse;
        break;
    }
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60621 */
    LddRetVal = E_NOT_OK;
    *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Return value depends on application code."*/

  DCM_UNUSED(pMsgContext);
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_SrInterfaceProcess                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function for process Did in case use port      **
**                        is configured as atomic sender receiver interface   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : OpStatus, pMsgContext, pDidCfg                      **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if ((DCM_ATOMIC_SENDER_RECEIVER_ENABLE == STD_ON) && \
     (DCM_MAX_CONTROL_MASK_SIZE != DCM_ZERO))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspIOCtrl_SrInterfaceProcess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_DidParaConfigConstPtrType pDidCfg,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  uint8 LucCtrlType = pMsgContext->reqData[DCM_TWO];
  uint16 LusDataId = pDidCfg->usDcmDspDidIdentifier;

  uint32 LulMaskSize = Dcm_DspIOCtrl_GetCtrlMaskSize(pDidCfg);
  uint32 LulCtrlStateSize = pMsgContext->reqDataLen - (DCM_THREE + LulMaskSize);

  Dcm_Uint8PtrType LpCtrlStateInfo = &pMsgContext->reqData[DCM_THREE];
  Dcm_Uint8PtrType LpCtrlMaskRecord = &LpCtrlStateInfo[LulCtrlStateSize];

  switch (OpStatus)
  {
    case DCM_INITIAL:
      /* @Trace: SWS_Dcm_01436 */
      /* @Trace: Dcm_SUD_API_60625 */
      Dcm_DspIOCtrl_CalculateUnderCtrl(
        LucCtrlType, pDidCfg->ucDcmDspSignalCount, LpCtrlMaskRecord);

      /* @Trace: SWS_Dcm_01275 SWS_Dcm_01277 */
      LddRetVal = Dcm_DspIOCtrl_ProcessCallAtomicRequest(
        LusDataId, LucCtrlType, LpCtrlMaskRecord, LpCtrlStateInfo, pErrorCode);
      break;

    case DCM_PENDING:
      /* @Trace: SWS_Dcm_01439 */
      /* @Trace: Dcm_SUD_API_60626 */
      LddRetVal = Dcm_DspIOCtrl_ProcessCallAtomicResponse(
        LusDataId, LpCtrlMaskRecord, pMsgContext, pErrorCode);
      break;

    default:
      /* @Trace: Dcm_SUD_API_60627 */
      Dcm_MemClear(Dcm_GaaUnderControl, DCM_MAX_CONTROL_MASK_SIZE);

      (void) Dcm_DspIOCtrl_ProcessCallAtomicRequest(
        LusDataId, DCM_RETURN_CONTROL_TO_ECU, 
        LpCtrlMaskRecord, LpCtrlStateInfo, pErrorCode);
      break;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_UpdateResponse                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Update response for UDS 0x2F service                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : didIndex, pMsgContext                               **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_DspIOCtrl_UpdateResponse(
  uint16 didIndex,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType errorCode)
{
  /* @Trace: Dcm_SUD_API_60628 */
  if ((Dcm_ServicePendingStatus.ucIocontrolPendingStatus == DCM_FALSE) &&
      (Dcm_ServicePendingStatus.ucReadDataPendingStatus == DCM_FALSE))
  {
    if (DCM_POS_RESP != errorCode)
    {
      /* @Trace: Dcm_SUD_API_60630 */
      Dcm_InternalSetNegResponse(pMsgContext, errorCode);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60629 */
      pMsgContext->resDataLen += DCM_THREE;
      Dcm_MemCopy(pMsgContext->resData, pMsgContext->reqData, DCM_THREE);
    }

    Dcm_ResetSignalOpStatus(didIndex);
    Dcm_InternalProcessingDone(pMsgContext, DCM_ASYNC_DONE);
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspReturnControlToEcu                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Return control of signal to ecu                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DspReturnControlToEcu(void)
{
  uint16 LucIdx;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  Dcm_DidSignalConfigPtrType LpSignalCfg = NULL_PTR;
  Dcm_DidParaConfigConstPtrType LpDidCfg = NULL_PTR;
  Dcm_DidInfoConfigConstPtrType LpDidInfo = NULL_PTR;

  /* @Trace: Dcm_SUD_API_60634 */
  for (LucIdx = DCM_ZERO; LucIdx < DCM_TOTAL_NUM_OF_STATIC_DID; LucIdx++)
  {
    /* @Trace: Dcm_SUD_API_60631 */
    /* Get the did configuration */
    LpDidCfg = Dcm_CfgInternal_GetDidConfig(LucIdx);

    /* Did Range feature can not be applied for UDS 0x2F service */
    (void) Dcm_DspInternal_GetDidInfo(LucIdx, DCM_FALSE, &LpDidInfo);

    if ((NULL_PTR != LpDidInfo) && (NULL_PTR != LpDidInfo->pDidControl))
    {
      /* @Trace: Dcm_SUD_API_60632 */
      uint8 LucSignalIdx;
      uint8 LucNumOfSignal = LpDidCfg->ucDcmDspSignalCount;

      for (LucSignalIdx = DCM_ZERO; LucSignalIdx < LucNumOfSignal; LucSignalIdx++)
      {
        /* @Trace: Dcm_SUD_API_60633 */
        LpSignalCfg = &LpDidCfg->pDcmDspSignal[LucSignalIdx];

        (void) Dcm_DspIOCtrl_ReturnControlToECU(
          DCM_CANCEL, LpSignalCfg->pDataConfig, &LddErrorCode);
      }
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_PendingOperation                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for pending operation         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DspIOCtrl_PendingOperation(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60635 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if ((Dcm_ServicePendingStatus.ucIocontrolPendingStatus == DCM_TRUE) ||
    (Dcm_MemServicePendingStatus.ucIoCtrlReadDataPendingStatus == DCM_TRUE))
  {
    /* @Trace: Dcm_SUD_API_60636 */
    (void) Dcm_DspIOCtrl_InternalProcess(DCM_PENDING, pMsgContext, &LddErrorCode);

    Dcm_DspIOCtrl_UpdateResponse(Dcm_GusDIDIndexVal, pMsgContext, LddErrorCode);
  }
}

/*******************************************************************************
** Function Name        : Dcm_DspIOCtrl_CancelOperation                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for cancel operation          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_DspIOCtrl_CancelOperation(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60637 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if ((Dcm_ServicePendingStatus.ucIocontrolPendingStatus == DCM_TRUE) ||
    (Dcm_MemServicePendingStatus.ucIoCtrlReadDataPendingStatus == DCM_TRUE))
  {
    /* @Trace: Dcm_SUD_API_60638 */
    (void) Dcm_DspIOCtrl_InternalProcess(DCM_CANCEL, pMsgContext, &LddErrorCode);

    Dcm_ResetSignalOpStatus(Dcm_GusDIDIndexVal);
    Dcm_ServicePendingStatus.ucIocontrolPendingStatus = DCM_FALSE;
    Dcm_MemServicePendingStatus.ucIoCtrlReadDataPendingStatus = DCM_FALSE;
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DcmReadDataByPeriodicIdentifier                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for UDS 0x2A service          **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04215 */
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadDataByPeriodicIdentifier(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: SWS_Dcm_00254 */
  Std_ReturnType LddRetVal = E_OK;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  uint8 LucTmMode = pMsgContext->reqData[DCM_ZERO];
  Dcm_MsgLenType LddReqDataLen = pMsgContext->reqDataLen;

  /* @Trace: SWS_Dcm_01093 */
  if ((LddReqDataLen < DCM_ONE) ||
     ((LddReqDataLen < DCM_TWO) && (DCM_PDID_MODE_STOP_SENDING != LucTmMode)))
  {
    /* @Trace: Dcm_SUD_API_60639 */
    LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  #if (DCM_MAX_PDID_TO_READ != DCM_ZERO)
  /* @Trace: SWS_Dcm_00843 */
  else if (LddReqDataLen > ((Dcm_MsgLenType) DCM_MAX_PDID_TO_READ + DCM_ONE))
  {
    /* @Trace: Dcm_SUD_API_60640 */
    LddErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  #endif
  /* @Trace: SWS_Dcm_01094 */
  else if ((LucTmMode < DCM_PDID_MODE_SLOW_RATE) ||
           (LucTmMode > DCM_PDID_MODE_STOP_SENDING))
  {
    /* @Trace: Dcm_SUD_API_60641 */
    LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }
  else if (DCM_PDID_MODE_STOP_SENDING == LucTmMode)
  {
    /* @Trace: Dcm_SUD_API_60642 */
    LddErrorCode = Dcm_Pdid_StopTransmission(pMsgContext);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60643 */
    /* Clear new num PDID in case receive new request */
    Dcm_GddPerSchInfo.ucNewNumPdid = DCM_ZERO;

    LddErrorCode = Dcm_Pdid_StartTransmission(DCM_INITIAL, pMsgContext);
  }

  /* Processing the response for initial periodic request */
  Dcm_Pdid_HandleResponse(pMsgContext, LddErrorCode);

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(pErrorCode);
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_GetConfigByRequestedPdid                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get the periodic configuration by requested did     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : periodicId                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LpPerDidInfo                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_PeriodicDidInfoPtrType, DCM_CODE) Dcm_Pdid_GetConfigByRequestedPdid(
uint16 periodicId)
{
  Dcm_PeriodicDidInfoPtrType LpPerDidInfo;
  uint16 LusIndexPDid;
  uint16 LusDid = DCM_PDID_ASSEMBLE_DID(periodicId);

  LpPerDidInfo = NULL_PTR;
  for (LusIndexPDid = (uint16)DCM_ZERO; LusIndexPDid < (uint16)DCM_TOTAL_NUM_OF_PDID; LusIndexPDid++)
  {
    if (LusDid == Dcm_GaaPerDidInfo[LusIndexPDid].usDid)
    {
      LpPerDidInfo = &Dcm_GaaPerDidInfo[LusIndexPDid];
      break;
    }
  }

  return LpPerDidInfo;
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_AuthValidate                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate access right and white list for data id    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : dataId, pDidRead                                    **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_AuthValidate(
  uint16 dataId,
  Dcm_DidReadConfigConstPtrType pDidRead)
{
  /* @Trace: Dcm_SUD_API_60647 */
  Dcm_AuthenticationRoleType LddRole;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  Dcm_MemCopy(LddRole, pDidRead->DidReadRole, DCM_AUTHENTICATION_ROLE_SIZE);

  if (DCM_FALSE == Dcm_ValidateAccessRights(LddRole))
  {
    /* @Trace: Dcm_SUD_API_60646 */
    #if (DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED == STD_ON)
    uint8 LaaRecord[DCM_THREE];
    LaaRecord[DCM_ZERO] = DCM_U16_HI_BYTE(dataId);
    LaaRecord[DCM_ONE] = DCM_U16_LO_BYTE(dataId);
    LaaRecord[DCM_TWO] = DCM_DID_READ_ACCESS_MASK;

    if (DCM_FALSE == Dcm_ValidateAccessRightsWithWLDid(LaaRecord, DCM_THREE))
    #endif
    {
      /* @Trace: Dcm_SUD_API_60648 */
      LddErrorCode = DCM_E_AUTHENTICATIONREQUIRED;
    }
  }

  DCM_UNUSED(dataId);
  return LddErrorCode;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_Pdid_CheckRequestedPid                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Validate all condition for request periodic id,     **
**                        include authentication access rigth, session,       **
**                        security and mode condition                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : periodicId                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pCfgIndex                                           **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_CheckRequestedPid(
  uint8 periodicId,
  Dcm_Uint16PtrType pCfgIndex)
{
  /* @Trace: Dcm_SUD_API_60649 */
  Std_ReturnType LddResult;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_E_REQUESTOUTOFRANGE;

  uint16 LusDidIndex = DCM_ZERO;
  uint16 LusDid = DCM_PDID_ASSEMBLE_DID(periodicId);
  Dcm_DidInfoConfigConstPtrType LpDidInfo = NULL_PTR;

  if (DCM_TRUE == Dcm_GetDidConfigIndex(LusDid, &LusDidIndex))
  {
    /* @Trace: Dcm_SUD_API_60650 */
    /* Did Range feature cannot be applied for UDS 0x2A service */
    LddResult = Dcm_DspInternal_GetDidInfo(LusDidIndex, DCM_FALSE, &LpDidInfo);

    if ((E_OK == LddResult) &&  
        (NULL_PTR != LpDidInfo) && 
        (NULL_PTR != LpDidInfo->pDidRead))
    {
      #if (DCM_AUTHENTICATION_SERVICE == STD_ON)
      /* @Trace: Dcm_SUD_API_60651 */
      /* @Trace: SWS_Dcm_01553 SWS_Dcm_01552 */
      LddErrorCode = Dcm_Pdid_AuthValidate(LusDid, LpDidInfo->pDidRead);

      if (DCM_POS_RESP == LddErrorCode)
      #endif
      {
        /* @Trace: Dcm_SUD_API_60652 */
        LddErrorCode = Dcm_ReadDid_CheckAuthorization(LpDidInfo->pDidRead);
      }
    }
  }

  if (DCM_POS_RESP == LddErrorCode)
  {
    /* @Trace: Dcm_SUD_API_60653 */
    *pCfgIndex = LusDidIndex;
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_GetDynDidConfig                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get dynamically define did by did index             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : usDidIndex                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LpDynDidInfo                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_DYNAMIC_DID_PER_SOURCE == STD_ON)
static FUNC(Dcm_DynDidInfoPtrType, DCM_CODE) Dcm_Pdid_GetDynDidConfig(
  uint16 usDidIndex)
{
  /* @Trace: Dcm_SUD_API_60655 */
  Dcm_DynDidInfoPtrType LpDynDidInfo = NULL_PTR;

  #if (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
  uint16 LusDid = DCM_ZERO;
  uint16 LusDynDidIndex = DCM_ZERO;
  
  /* Get did configuration to get data id */
  Dcm_DidParaConfigConstPtrType LpDidConfig;
  LpDidConfig = Dcm_CfgInternal_GetDidConfig(usDidIndex);

  if (NULL_PTR != LpDidConfig)
  {
    /* @Trace: Dcm_SUD_API_60656 */
    LusDid = LpDidConfig->usDcmDspDidIdentifier;

    if (DCM_TRUE == Dcm_DynDid_GetConfigIndex(LusDid, &LusDynDidIndex))
    {
      /* @Trace: Dcm_SUD_API_60657 */
      LpDynDidInfo = Dcm_CfgInternal_GetDynDidInfo(LusDynDidIndex);
    }
  }
  #endif

  return LpDynDidInfo;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_Pdid_CheckSourceDid                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check the condition for source DID of DDDID         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : usDidIndex                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_DYNAMIC_DID_PER_SOURCE == STD_ON)
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_CheckSourceDid(
  uint16 usDidIndex)
{
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  #if (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
  if (DCM_DID_TYPE_DYN == Dcm_DspGetDidType(usDidIndex))
  {
    /* @Trace: Dcm_SUD_API_60658 */
    uint8 LucNumOfSource = DCM_ZERO;
    boolean LblDidRange = DCM_FALSE;
    
    Dcm_SourceDidInfoPtrType LpSourceDidInfo = NULL_PTR;
    Dcm_DynDidInfoPtrType LpDynDidInfo = Dcm_Pdid_GetDynDidConfig(usDidIndex);

    if (NULL_PTR != LpDynDidInfo)
    {
      /* @Trace: Dcm_SUD_API_60659 */
      LpSourceDidInfo = LpDynDidInfo->pSourceDidInfo;
      LucNumOfSource = LpDynDidInfo->ucMemAddCount + LpDynDidInfo->ucSourceDidCount;
    }

    /* In case LpDynDidInfo is null, this loop will be terminated */
    for (uint8 LucIndex = DCM_ZERO; LucIndex < LucNumOfSource; LucIndex++)
    {
      /* @Trace: Dcm_SUD_API_60661 */
      uint16 LusSrcDidIdx = DCM_ZERO;
      uint16 LusSrcDid = LpSourceDidInfo[LucIndex].usSourceDid;

      /* Only source did that have priority different than ZERO is valid */
      if (DCM_ZERO != LpSourceDidInfo[LucIndex].ucPriority)
      {
        if (DCM_TRUE != Dcm_DspDidSearch(LusSrcDid, &LusSrcDidIdx, &LblDidRange))
        {
          /* @Trace: Dcm_SUD_API_60662 */
          LddErrorCode  = DCM_E_REQUESTOUTOFRANGE;
        }
        else
        {
          /* @Trace: Dcm_SUD_API_60663 */
          LddErrorCode = Dcm_DspValidateReadDid(LusSrcDidIdx, LblDidRange);
        }
      }
    }
  }
  #endif

  return LddErrorCode;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_Pdid_CheckStartRequest                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check all condition for start periodic request      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +3 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_CheckStartRequest(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60668 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  uint16 LusDidIndex = DCM_ZERO;
  uint16 LusPerDataLength = DCM_ZERO;
  Dcm_PeriodicDidInfoPtrType LpPerDidInfo = NULL_PTR;

  Dcm_MsgLenType LddIndex = DCM_ZERO;
  Dcm_MsgLenType LddNumOfDid = pMsgContext->reqDataLen - DCM_ONE;
  uint8 LucNumPdidReaded;

  /* Clear flag before go to main process */
  Dcm_ServicePendingStatus.ucReadPerDidPendingStatus = DCM_FALSE;
  LucNumPdidReaded = (uint8)DCM_ZERO;

  while ((LddIndex < LddNumOfDid) && (DCM_POS_RESP == LddErrorCode))
  {
    /* @Trace: Dcm_SUD_API_60664 */
    /* @Trace: SWS_Dcm_01095 SWS_Dcm_01100 SWS_Dcm_01096 */
    /* @Trace: SWS_Dcm_00721 SWS_Dcm_00722 SWS_Dcm_00820 */
    LddErrorCode = Dcm_Pdid_CheckRequestedPid(
      pMsgContext->reqData[DCM_ONE + LddIndex], &LusDidIndex);

    #if (DCM_DYNAMIC_DID_PER_SOURCE == STD_ON)
    if (DCM_POS_RESP == LddErrorCode)
    {
      /* @Trace: SWS_Dcm_01097 */
      /* @Trace: Dcm_SUD_API_60669 */
      LddErrorCode = Dcm_Pdid_CheckSourceDid(LusDidIndex);
    }
    #endif

    /* Check if the periodic configuration is valid */
    if (DCM_POS_RESP == LddErrorCode)
    {
      /* @Trace: Dcm_SUD_API_60670 */
      /* Get configuration to change the state machine */
      //LpPerDidInfo = Dcm_Pdid_GetConfigByDidIndex(LusDidIndex);
      LpPerDidInfo = Dcm_Pdid_GetConfigByRequestedPdid(pMsgContext->reqData[DCM_ONE + LddIndex]);

      if (NULL_PTR == LpPerDidInfo)
      {
        /* @Trace: Dcm_SUD_API_60672 */
        LddErrorCode = DCM_E_GENERALREJECT;
      }
    }

    /* Check if the slot of scheduler is free or not */
    if (DCM_POS_RESP == LddErrorCode)
    {
      /* Increase new num pdid in case this pdid is not actived */
      if (DCM_FALSE == LpPerDidInfo->blActive) 
      {
        /* @Trace: Dcm_SUD_API_60673 */
        Dcm_GddPerSchInfo.ucNewNumPdid++;
      }

      /* @Trace: SWS_Dcm_00851 */
      if ((Dcm_GddPerSchInfo.ucNewNumPdid + 
           Dcm_GddPerSchInfo.ucActiveNumPdid) <= DCM_MAX_PDID_SCHEDULER)
      {
        if (DCM_INITIAL == OpStatus)
        {
          /* @Trace: Dcm_SUD_API_60675 */
          LpPerDidInfo->ucState = DCM_PDID_STATE_CHECK_READ;
        }
      }
      else
      {
        /* @Trace: Dcm_SUD_API_60674 */
        LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
        break;
      }
    }

    /* Check if signal can be read in current condition */
    if ((DCM_POS_RESP == LddErrorCode) &&
        (DCM_PDID_STATE_CHECK_READ == LpPerDidInfo->ucState))
    {
      /* @Trace: SWS_Dcm_01098 */
      if (E_OK == Dcm_Pdid_ConditionCheckRead(OpStatus, LusDidIndex, 
        &LddErrorCode))
      {
        /* @Trace: Dcm_SUD_API_60665 */
        LpPerDidInfo->ucState = DCM_PDID_STATE_READ_LENGTH;
      }
    }

    /* Read the data length of signals */
    if ((DCM_POS_RESP == LddErrorCode) &&
        (DCM_PDID_STATE_READ_LENGTH == LpPerDidInfo->ucState))
    {
      /* @Trace: SWS_Dcm_01099 */
      if (E_OK == Dcm_Pdid_ReadDataLength(OpStatus, LusDidIndex, 
        &LusPerDataLength, &LddErrorCode))
      {
        /* @Trace: Dcm_SUD_API_60666 */
        LpPerDidInfo->usDidLen = LusPerDataLength;
        LpPerDidInfo->ucState = DCM_PDID_STATE_READY_START;
        LucNumPdidReaded++;
      }
    }

    /* Next PDID in request */
    LddIndex = LddIndex + DCM_ONE;

    if ((DCM_POS_RESP != LddErrorCode)
        && (LddIndex < LddNumOfDid))
    {
      /* if multi Pdid requested, Dcm will check all PDid supported  */
      LddErrorCode = DCM_POS_RESP;
    }
  }
  
  if (LucNumPdidReaded > DCM_ZERO)
  {
    /*at least one Pdid supported*/
    LddErrorCode = DCM_POS_RESP;
  } 
  else if (LddNumOfDid > DCM_ONE)
  {
    /*if multi Pdid requested, and no Pdid supported, NRC 0x31 return*/
    LddErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }
  else 
  {
    // do nothing
  }

  return LddErrorCode;  
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_StartOneDid                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Start one PDID to prepare periodic transmission     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ucTmMode, usPerDidIndex                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Pdid_StartOneDid(
  uint8 ucTmMode,
  uint16 usPerDidIndex)
{
  uint8 LucTimerIndex;

  /* @Trace: Dcm_SUD_API_60676 */
  Dcm_PeriodicDidInfoPtrType LpPerDidInfo;
  LpPerDidInfo = Dcm_CfgInternal_GetPdidInfo(usPerDidIndex);

  if (NULL_PTR != LpPerDidInfo)
  {
    if (DCM_TRUE == LpPerDidInfo->blActive)
    {
      /* @Trace: Dcm_SUD_API_60677 */
      /* Decrease the timer count */
      LucTimerIndex = LpPerDidInfo->ucTmMode - DCM_ONE;
      Dcm_GddPerSchInfo.pTimerCount[LucTimerIndex]--;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60678 */
      LpPerDidInfo->blActive = DCM_TRUE;
      Dcm_GddPerSchInfo.ucActiveNumPdid++;
    }
    
    LpPerDidInfo->ucStatus = DCM_PDID_FIRST_RESPONSE;
    /* Update new transmission mode */
    LpPerDidInfo->ucTmMode = ucTmMode;
    LpPerDidInfo->ucState = DCM_PDID_STATE_UNDEFINE;

    /* Increase the timer count */
    LucTimerIndex = LpPerDidInfo->ucTmMode - DCM_ONE;
    Dcm_GddPerSchInfo.pTimerCount[LucTimerIndex]++;
  }
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_ConditionCheckRead                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call and process condition check read return value  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, usDidIndex                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Pdid_ConditionCheckRead(
  Dcm_OpStatusType OpStatus,
  uint16 usDidIndex,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;

  uint8 LucIndex = DCM_ZERO;
  uint8 LucNumOfSignal = DCM_ZERO;

  Dcm_DidParaConfigConstPtrType LpDidConfig;
  Dcm_DidSignalConfigPtrType LpSignalConfig = NULL_PTR;

  /* @Trace: Dcm_SUD_API_60680 */
  /* Get did config to access the signals */
  LpDidConfig = Dcm_CfgInternal_GetDidConfig(usDidIndex);

  if (NULL_PTR != LpDidConfig)
  {
    /* @Trace: Dcm_SUD_API_60679 */
    LpSignalConfig = LpDidConfig->pDcmDspSignal;
    LucNumOfSignal = LpDidConfig->ucDcmDspSignalCount;
  }

  /* @Trace: Dcm_SUD_API_60681 */
  while ((LucIndex < LucNumOfSignal) && (DCM_POS_RESP == *pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_60682 */
    /* Reset return value */
    LddRetVal = E_OK;

    /* Determine whether the process function is call */
    switch (OpStatus)
    {
      case DCM_INITIAL:
        /* @Trace: Dcm_SUD_API_60683 */
        LddRetVal = Dcm_DspInternal_ConditionCheckRead(
          OpStatus, LpSignalConfig->pDataConfig, pErrorCode);
        break;

      case DCM_PENDING:
        if (DCM_OPSTATUS_PENDING == LpSignalConfig->ucSignalOpStatus)
        {
          /* @Trace: Dcm_SUD_API_60684 */
          LddRetVal = Dcm_DspInternal_ConditionCheckRead(
            OpStatus, LpSignalConfig->pDataConfig, pErrorCode);
        }
        break;

      default:
        if (DCM_OPSTATUS_PENDING == LpSignalConfig->ucSignalOpStatus)
        {
          /* @Trace: Dcm_SUD_API_60685 */
          (void) Dcm_DspInternal_ConditionCheckRead(
            OpStatus, LpSignalConfig->pDataConfig, pErrorCode);
        }
        break;
    }

    switch (LddRetVal)
    {
      case DCM_E_PENDING:
        /* @Trace: Dcm_SUD_API_60686 */
        Dcm_ServicePendingStatus.ucReadPerDidPendingStatus = DCM_TRUE;
        LpSignalConfig->ucSignalOpStatus = DCM_OPSTATUS_PENDING;
        break;

      default:
        /* @Trace: Dcm_SUD_API_60687 */
        LpSignalConfig->ucSignalOpStatus = DCM_OPSTATUS_INITIAL;
        break;
    }

    /* Process next signal */
    LucIndex++;
    LpSignalConfig = &LpSignalConfig[DCM_ONE];
  }

  return LddRetVal;  
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_ReadDataLength                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Call and process read data length return value      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, usDidIndex                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDataLen, pErrorCode                                **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Pdid_ReadDataLength(
  Dcm_OpStatusType OpStatus,
  uint16 usDidIndex,
  Dcm_Uint16PtrType pDataLen,
  Dcm_NrcPtrType pErrorCode)
{
  Std_ReturnType LddRetVal = E_OK;

  uint8 LucIndex = DCM_ZERO;
  uint8 LucNumOfSignal = DCM_ZERO;

  uint16 LusDataLength = DCM_ZERO;
  Dcm_DidParaConfigConstPtrType LpDidConfig;
  Dcm_DidSignalConfigPtrType LpSignalConfig = NULL_PTR;

  /* @Trace: Dcm_SUD_API_60690 */
  /* Get did config to access the signals */
  LpDidConfig = Dcm_CfgInternal_GetDidConfig(usDidIndex);

  if (NULL_PTR != LpDidConfig)
  {
    /* @Trace: Dcm_SUD_API_60688 */
    LpSignalConfig = LpDidConfig->pDcmDspSignal;
    LucNumOfSignal = LpDidConfig->ucDcmDspSignalCount;
  }

  /* @Trace: Dcm_SUD_API_60691 */
  while ((LucIndex < LucNumOfSignal) && (DCM_POS_RESP == *pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_60692 */
    /* Reset return value */
    LddRetVal = E_OK;

    /* Determine whether the process function is call */
    switch (OpStatus)
    {
      case DCM_INITIAL:
        /* @Trace: Dcm_SUD_API_60693 */
        LddRetVal = Dcm_DspInternal_GetSizeOfDidSignal(
          OpStatus, LpSignalConfig->pDataConfig, &LusDataLength);
        break;

      case DCM_PENDING:
        if (DCM_OPSTATUS_PENDING == LpSignalConfig->ucSignalOpStatus)
        {
          /* @Trace: Dcm_SUD_API_60694 */
          LddRetVal = Dcm_DspInternal_GetSizeOfDidSignal(
            OpStatus, LpSignalConfig->pDataConfig, &LusDataLength);
        }
        break;

      default:
        if (DCM_OPSTATUS_PENDING == LpSignalConfig->ucSignalOpStatus)
        {
          /* @Trace: Dcm_SUD_API_60695 */
          (void) Dcm_DspInternal_GetSizeOfDidSignal(
          OpStatus, LpSignalConfig->pDataConfig, &LusDataLength);
        }
        break;
    }

    switch (LddRetVal)
    {
      case E_OK:
        /* @Trace: Dcm_SUD_API_60696 */
        *pDataLen += LusDataLength;
        LpSignalConfig->ucSignalOpStatus = DCM_OPSTATUS_INITIAL;
        break;

      case DCM_E_PENDING:
        /* @Trace: Dcm_SUD_API_60697 */
        Dcm_ServicePendingStatus.ucReadPerDidPendingStatus = DCM_TRUE;
        LpSignalConfig->ucSignalOpStatus = DCM_OPSTATUS_PENDING;
        break;

      default:
        /* @Trace: Dcm_SUD_API_60689 */
        *pErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        LpSignalConfig->ucSignalOpStatus = DCM_OPSTATUS_INITIAL;
        break;
    }

    /* Process next signal */
    LucIndex++;
    LpSignalConfig = &LpSignalConfig[DCM_ONE];
  }

  return LddRetVal;  
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_StartTransmission                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for start periodic request    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, pMsgContext                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_StartTransmission(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext)
{
  uint8 LucTmMode = pMsgContext->reqData[DCM_ZERO];
  Dcm_PeriodicDidInfoPtrType LpPerDidInfo = NULL_PTR;

  /* @Trace: Dcm_SUD_API_60698 */
  Dcm_NegativeResponseCodeType LddErrorCode;
  LddErrorCode = Dcm_Pdid_CheckStartRequest(OpStatus, pMsgContext);

  if ((DCM_POS_RESP == LddErrorCode) && 
      (DCM_FALSE == Dcm_ServicePendingStatus.ucReadPerDidPendingStatus))
  {
    for (uint16 LusIdx = DCM_ZERO; LusIdx < DCM_TOTAL_NUM_OF_PDID; LusIdx++)
    {
      /* @Trace: Dcm_SUD_API_60700 */
      LpPerDidInfo = Dcm_CfgInternal_GetPdidInfo(LusIdx);

      /* Only start requested did that satisfy validation */
      if (DCM_PDID_STATE_READY_START == LpPerDidInfo->ucState)
      {
        /* @Trace: Dcm_SUD_API_70010 */
        Dcm_Pdid_StartOneDid(LucTmMode, LusIdx);
      }
    }

    /* @Trace: Dcm_SUD_API_60699 */
    /* Update timer after start PDID */
    //Dcm_Pdid_UpdateTimer();
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_CheckStopRequest                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check all condition for stop periodic request       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_CheckStopRequest(
  Dcm_MsgContextPtrType pMsgContext)
{
  uint16 LusDidIndex = DCM_ZERO;
  Dcm_PeriodicDidInfoPtrType LpPerDidInfo = NULL_PTR;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  Dcm_MsgLenType LddIndex = DCM_ZERO;
  Dcm_MsgLenType LddNumOfDid = pMsgContext->reqDataLen - DCM_ONE;

  /* @Trace: Dcm_SUD_API_60701 */
  while ((LddIndex < LddNumOfDid) && (DCM_POS_RESP == LddErrorCode))
  {
    /* @Trace: Dcm_SUD_API_60702 */
    /* @Trace: SWS_Dcm_01426 SWS_Dcm_01428 */
    LddErrorCode = Dcm_Pdid_CheckRequestedPid(
      pMsgContext->reqData[LddIndex + DCM_ONE], &LusDidIndex);

    if (DCM_POS_RESP == LddErrorCode)
    {
      /* @Trace: Dcm_SUD_API_60703 */
      /* Get configuration to change the state machine */
      //LpPerDidInfo = Dcm_Pdid_GetConfigByDidIndex(LusDidIndex);
      LpPerDidInfo = Dcm_Pdid_GetConfigByRequestedPdid(pMsgContext->reqData[LddIndex + DCM_ONE]);

      if (NULL_PTR != LpPerDidInfo)
      {
        /* @Trace: Dcm_SUD_API_60705 */
        LpPerDidInfo->ucState = DCM_PDID_STATE_READY_STOP;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_60704 */
        LddErrorCode = DCM_E_GENERALREJECT;
      }
    }

    /* Next PDID in request */
    LddIndex = LddIndex + DCM_ONE;
  }

  return LddErrorCode;  
}


/*******************************************************************************
** Function Name        : Dcm_Pdid_StopOneDid                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Stop one PDID that on periodic transmission         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : usPerDidIndex                                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Pdid_StopOneDid(
  uint16 usPerDidIndex)
{
  uint8 LucTimerIndex;

  /* @Trace: Dcm_SUD_API_60707 */
  Dcm_PeriodicDidInfoPtrType LpPerDidInfo;
  LpPerDidInfo = Dcm_CfgInternal_GetPdidInfo(usPerDidIndex);

  if ((NULL_PTR != LpPerDidInfo) && (DCM_TRUE == LpPerDidInfo->blActive))
  {
    /* @Trace: Dcm_SUD_API_60706 */
    /* Deactivate PDID */
    LpPerDidInfo->blActive = DCM_FALSE;
    Dcm_GddPerSchInfo.ucActiveNumPdid--;

    /* Decrease the timer count */
    LucTimerIndex = LpPerDidInfo->ucTmMode - DCM_ONE;
    Dcm_GddPerSchInfo.pTimerCount[LucTimerIndex]--;

    /* Clear all periodic state and transmission mode */
    LpPerDidInfo->usDidLen = DCM_ZERO;
    LpPerDidInfo->ucState = DCM_PDID_STATE_UNDEFINE;
    LpPerDidInfo->ucTmMode = DCM_PDID_MODE_UNDEFINE;
    LpPerDidInfo->ucStatus = DCM_PDID_INACTIVE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_StopAllPids                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Stop all Pdids without check condition              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
/* polyspace +2 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_StopAllPids(
  Dcm_MsgContextPtrType pMsgContext)
{
  uint16 LusIndex;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  /* @Trace: SWS_Dcm_01427 */
  for (LusIndex = DCM_ZERO; LusIndex < DCM_TOTAL_NUM_OF_PDID; LusIndex++)
  {
    /* @Trace: Dcm_SUD_API_60708 */
    Dcm_Pdid_StopOneDid(LusIndex);
  }

  /* @Trace: Dcm_SUD_API_60709 */
  /* Action for stop transmission */
  Dcm_Pdid_HandleStopEvent();

  DCM_UNUSED(pMsgContext);
  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_StopSpecificPids                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Stop specific Pdids from request message            **
**                        Only stop Pdids that satisfy the validation         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_StopSpecificPids(
  Dcm_MsgContextPtrType pMsgContext)
{
  uint16 LusIndex;
  Dcm_PeriodicDidInfoPtrType LpPerDidInfo = NULL_PTR;

  /* @Trace: Dcm_SUD_API_70011 */
  Dcm_NegativeResponseCodeType LddErrorCode;
  LddErrorCode = Dcm_Pdid_CheckStopRequest(pMsgContext);

  if (DCM_POS_RESP == LddErrorCode)
  {
    for (LusIndex = DCM_ZERO; LusIndex < DCM_TOTAL_NUM_OF_PDID; LusIndex++)
    {
      /* @Trace: Dcm_SUD_API_60711 */
      LpPerDidInfo = Dcm_CfgInternal_GetPdidInfo(LusIndex);

      /* Only stop requested did that satisfy validation */
      if (DCM_PDID_STATE_READY_STOP == LpPerDidInfo->ucState)
      {
        /* @Trace: Dcm_SUD_API_60712 */
        Dcm_Pdid_StopOneDid(LusIndex);
      }
    }

    /* @Trace: Dcm_SUD_API_60710 */
    /* Action for stop transmission */
    Dcm_Pdid_HandleStopEvent();
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_StopTransmission                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main process function for stop periodic request     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext                                         **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddErrorCode                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_Pdid_StopTransmission(
  Dcm_MsgContextPtrType pMsgContext)
{
  Dcm_NegativeResponseCodeType LddErrorCode;

  if (DCM_ONE == pMsgContext->reqDataLen)
  {
    /* @Trace: Dcm_SUD_API_60714 */
    LddErrorCode = Dcm_Pdid_StopAllPids(pMsgContext);
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60713 */
    LddErrorCode = Dcm_Pdid_StopSpecificPids(pMsgContext);
  }

  return LddErrorCode;
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_UpdateTimer                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Update the start or stop state of periodic timer    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Pdid_UpdateTimer(void)
{
  uint16 LusIdx;
  uint16 LusTimerIdx;

  uint32 LaaTimerRate[DCM_PDID_NUM_OF_TIMER] = 
  {
    DCM_PDID_SLOW_RATE, DCM_PDID_MEDIUM_RATE, DCM_PDID_FAST_RATE
  };

  /* @Trace: Dcm_SUD_API_60718 */
  /* Traverse all timer count to determine whether start or stop timer */
  for (LusIdx = DCM_ZERO; LusIdx < (uint16) DCM_PDID_NUM_OF_TIMER; LusIdx++)
  {
    LusTimerIdx = LusIdx + (uint16) DCM_PDID_SLOW_TIMER;

    if (DCM_ZERO == Dcm_GddPerSchInfo.pTimerCount[LusIdx])
    {
      /* @Trace: Dcm_SUD_API_60716 */
      /* polyspace +1 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
      Dcm_StopTimer((Dcm_TimerType) LusTimerIdx);
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60717 */
      /* polyspace +1 MISRA-C3:10.5 [Justified:Low] Justify with annotations */
      Dcm_StartTimer((Dcm_TimerType) LusTimerIdx, LaaTimerRate[LusIdx]);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_HandleResponse                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Handle the initial response for UDS 0x2A service    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pMsgContext, ddErrorCode                            **
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
static FUNC(void, DCM_CODE) Dcm_Pdid_HandleResponse(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType ddErrorCode)
{
  /* @Trace: Dcm_SUD_API_60719 */
  if (DCM_FALSE == Dcm_ServicePendingStatus.ucReadPerDidPendingStatus)
  {
    if (DCM_POS_RESP != ddErrorCode)
    {
      /* @Trace: Dcm_SUD_API_60720 */
      Dcm_InternalSetNegResponse(pMsgContext, ddErrorCode);
      pMsgContext->resDataLen = DCM_THREE;
    }
    else
    {
      /* @Trace: Dcm_SUD_API_60721 */
      /* Positive response only containt service id */
      pMsgContext->resDataLen = DCM_ZERO;

      /* Start again from first channel */
      Dcm_GddPerStatus.ucTxPduIdx = DCM_ZERO;

      /* Update RxPduId for further processing */
      Dcm_GddPerStatus.ddRxPduId = pMsgContext->dcmRxPduId;

      /* Update status for initial request */
      if (DCM_ZERO != Dcm_GddPerSchInfo.ucActiveNumPdid)
      {
        /* @Trace: Dcm_SUD_API_60722 */
        /* Start periodic response if remaining active PDID */
        Dcm_PrtclTxBufStatus.ucPeriodicIdStatus = DCM_TRUE;
      }
      else
      {
        /* @Trace: Dcm_SUD_API_60723 */
        /* Stop periodic response if no remaining active PDID */
        Dcm_PrtclTxBufStatus.ucPeriodicIdStatus = DCM_FALSE;
      }
    }

    /* Send initial request immediately */
    Dcm_InternalProcessingDone(pMsgContext, DCM_SYNC_DONE);
  }
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_HandleStopEvent                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Handle periodic transmission when stop event occur  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
static FUNC(void, DCM_CODE) Dcm_Pdid_HandleStopEvent(void)
{
  if (DCM_TRUE == Dcm_ServicePendingStatus.ucReadDataPendingStatus)
  {
    /* @Trace: Dcm_SUD_API_60724 */
    /* @Trace: SWS_Dcm_01115 SWS_Dcm_01116  */
    Dcm_DspInternal_DcmReadDataByIdentifier(DCM_CANCEL, &Dcm_GstPerMsgContext);

    Dcm_ServicePendingStatus.ucReadDataPendingStatus = DCM_FALSE;
  }

  /* @Trace: Dcm_SUD_API_60725 */
  /* @Trace: SWS_Dcm_01113 SWS_Dcm_01114 SWS_Dcm_01117 SWS_Dcm_01118 */
  Dcm_Pdid_ClearQueueData();

  Dcm_Pdid_ClearBusyStatus();

  /* Update timer after stop PDID */
  Dcm_Pdid_UpdateTimer();
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_HandleSessionOrSecurityChange              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Handle periodic transmission when session level     **
**                        or security level change to new state               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pdid_HandleSessionOrSecurityChange(void)
{
  Dcm_SesCtrlType LddSesLevel = DCM_DEFAULT_SESSION;
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  uint16 LusIdx = DCM_ZERO;
  uint16 LusDidIdx = DCM_ZERO;
  Dcm_PeriodicDidInfoPtrType LpPerDidInfo = NULL_PTR;  

  /* In session or security change, only action if on periodic transmission */
  /* @Trace: Dcm_SUD_API_60727 */
  /* Get the current session level */
  (void) Dcm_GetSesCtrlType(&LddSesLevel);

  /* @Trace: SWS_Dcm_01107 */
  if (DCM_DEFAULT_SESSION == LddSesLevel)
  {
    for (LusIdx = DCM_ZERO; LusIdx < DCM_TOTAL_NUM_OF_PDID; LusIdx++)
    {
      /* @Trace: Dcm_SUD_API_60728 */
      Dcm_Pdid_StopOneDid(LusIdx);
    }
  }
  else
  {
    for (LusIdx = DCM_ZERO; LusIdx < DCM_TOTAL_NUM_OF_PDID; LusIdx++)
    {
      /* @Trace: Dcm_SUD_API_60731 */
      LpPerDidInfo = Dcm_CfgInternal_GetPdidInfo(LusIdx);
      if  ((NULL_PTR != LpPerDidInfo) &&(DCM_TRUE == LpPerDidInfo->blActive) )
      {
        /* @Trace: Dcm_SUD_API_60732 */
        /* Get index based on the generated macro */
        //LusDidIdx = LusIdx + DCM_PDID_START_INDEX;
        (void)Dcm_GetDidConfigIndex(LpPerDidInfo->usDid, &LusDidIdx);

        /* @Trace: SWS_Dcm_01108 SWS_Dcm_01109 SWS_Dcm_01110 */
        LddErrorCode = Dcm_DspValidateReadDid(LusDidIdx, DCM_FALSE);

        #if (DCM_DYNAMIC_DID_PER_SOURCE == STD_ON)
        if (DCM_POS_RESP == LddErrorCode)
        {
          /* @Trace: Dcm_SUD_API_60733 */
          /* @Trace: SWS_Dcm_01111 SWS_Dcm_01112 */
          LddErrorCode = Dcm_Pdid_CheckSourceDid(LusDidIdx);
        }
        #endif

        /* Stop PDID not support in current state */
        if (DCM_POS_RESP != LddErrorCode)
        {
          /* @Trace: Dcm_SUD_API_60734 */
          Dcm_Pdid_StopOneDid(LusIdx);
        }
      }
    }
  }

  /* @Trace: Dcm_SUD_API_60729 */
  /* Clear queue and operation status */
  Dcm_Pdid_HandleStopEvent();

  /* Stop transmission if no remaining active PDID */
  if (DCM_ZERO == Dcm_GddPerSchInfo.ucActiveNumPdid)
  {
    /* @Trace: Dcm_SUD_API_60730 */
    Dcm_GddPerStatus.blOnResTrans = DCM_FALSE;
  }
  else 
  {
    Dcm_GddPerStatus.blOnResTrans = DCM_TRUE;
  }
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_ClearQueueData                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Clear all data in periodic scheduler queue          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pdid_ClearQueueData(void)
{
  uint8 LucIdx;

  for (LucIdx = DCM_ZERO; LucIdx < DCM_MAX_PDID_SCHEDULER; LucIdx++)
  {
    /* @Trace: Dcm_SUD_API_60735 */
    Dcm_GddPerSchInfo.pQueueData[LucIdx] = DCM_ZERO;
  }

  /* @Trace: Dcm_SUD_API_60736 */
  Dcm_GddPerSchInfo.ucQueueSize = DCM_ZERO;
  Dcm_GddPerSchInfo.ucQueueRear = DCM_ZERO;
  Dcm_GddPerSchInfo.ucQueueFront = DCM_ZERO;
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_EnqueueData                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Push data to periodic scheduler queue               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : usDid                                               **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Pdid_EnqueueData(
  uint16 usDid)
{
  Std_ReturnType LddRetVal = E_OK;

  if (DCM_MAX_PDID_SCHEDULER == Dcm_GddPerSchInfo.ucQueueSize)
  {
    /* @Trace: Dcm_SUD_API_60738 */
    LddRetVal = E_NOT_OK;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60737 */
    Dcm_GddPerSchInfo.ucQueueSize++;
    Dcm_GddPerSchInfo.pQueueData[Dcm_GddPerSchInfo.ucQueueRear] = usDid;

    Dcm_GddPerSchInfo.ucQueueRear++;
    Dcm_GddPerSchInfo.ucQueueRear %= DCM_MAX_PDID_SCHEDULER;
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_DequeueData                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Pull data from periodic scheduler queue             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDid                                                **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Pdid_DequeueData(
  Dcm_Uint16PtrType pDid)
{
  Std_ReturnType LddRetVal = E_OK;

  if (DCM_ZERO == Dcm_GddPerSchInfo.ucQueueSize)
  {
    /* @Trace: Dcm_SUD_API_60740 */
    LddRetVal = E_NOT_OK;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_60739 */
    Dcm_GddPerSchInfo.ucQueueSize--;
    *pDid = Dcm_GddPerSchInfo.pQueueData[Dcm_GddPerSchInfo.ucQueueFront];

    Dcm_GddPerSchInfo.ucQueueFront++;
    Dcm_GddPerSchInfo.ucQueueFront %= DCM_MAX_PDID_SCHEDULER;
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_EnqueueDataByMode                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Enqueue data when timer expired with TM mode        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ucTmMode                                            **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Pdid_EnqueueDataByMode(
  uint8 ucTmMode)
{
  uint16 LusIndex = DCM_ZERO;
  Std_ReturnType LddRetVal = E_OK;
  Dcm_PeriodicDidInfoPtrType LpPerDidInfo = NULL_PTR;

  /* @Trace: Dcm_SUD_API_60741 */
  while ((LusIndex < DCM_TOTAL_NUM_OF_PDID) && (E_OK == LddRetVal))
  {
    /* @Trace: Dcm_SUD_API_60742 */
    LpPerDidInfo = Dcm_CfgInternal_GetPdidInfo(LusIndex);

    if (DCM_TRUE == LpPerDidInfo->blActive)
    {
      if (ucTmMode == LpPerDidInfo->ucTmMode)
      {
        /* @Trace: Dcm_SUD_API_60743 */
        LddRetVal = Dcm_Pdid_EnqueueData(LpPerDidInfo->usDid);
      }
    }

    LusIndex++;
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_InitData                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Initialize data for UDS 0x2A service                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pdid_InitData(void)
{
  /* @Trace: Dcm_SUD_API_60744 */
  /* Clear all operation status */
  Dcm_GddPerStatus.ddRxPduId = DCM_ZERO;
  Dcm_GddPerStatus.ucTxPduIdx = DCM_ZERO;
  Dcm_GddPerStatus.ucDataInfoIdx = DCM_ZERO;

  Dcm_GddPerStatus.blOnResTrans = DCM_FALSE;
  Dcm_GddPerStatus.blOnInitRequest = DCM_FALSE;

  /* Clear all scheduler infomation */
  Dcm_GddPerSchInfo.ucNewNumPdid = DCM_ZERO;
  Dcm_GddPerSchInfo.ucActiveNumPdid = DCM_ZERO;

  Dcm_Pdid_ClearQueueData();
  Dcm_MemClear(Dcm_GddPerSchInfo.pTimerCount, DCM_PDID_NUM_OF_TIMER);

  /* Clear all active PDID */
  for (uint16 LusIdx = DCM_ZERO; LusIdx < DCM_TOTAL_NUM_OF_PDID; LusIdx++)
  {
    /* @Trace: Dcm_SUD_API_60745 */
    Dcm_GaaPerDidInfo[LusIdx].blActive = DCM_FALSE;
    Dcm_GaaPerDidInfo[LusIdx].ucState = DCM_PDID_STATE_UNDEFINE;
    Dcm_GaaPerDidInfo[LusIdx].ucTmMode = DCM_PDID_MODE_UNDEFINE;
    Dcm_GaaPerDidInfo[LusIdx].ucStatus = DCM_PDID_INACTIVE;

  }
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_PendingOperation                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to process pending operation of       **
**                        read data by periodic identifier service            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pdid_PendingOperation(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60746 */
  Dcm_NegativeResponseCodeType LddErrorCode = DCM_POS_RESP;

  if (NULL_PTR != pMsgContext)
  {
    if (DCM_TRUE == Dcm_ServicePendingStatus.ucReadPerDidPendingStatus)
    {
      /* @Trace: Dcm_SUD_API_60747 */
      /* Only start periodic transmission request have PENDING state */
      LddErrorCode = Dcm_Pdid_StartTransmission(DCM_PENDING, pMsgContext);

      /* Processing the response for initial periodic request */
      Dcm_Pdid_HandleResponse(pMsgContext, LddErrorCode);
    }
  }
}

/*******************************************************************************
** Function Name        : Dcm_Pdid_CancelOperation                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Main function to process cancel operation of        **
**                        read data by periodic identifier service            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pdid_CancelOperation(
  Dcm_MsgContextPtrType pMsgContext)
{
  /* @Trace: Dcm_SUD_API_60748 */
  if (NULL_PTR != pMsgContext)
  {
    if (DCM_TRUE == Dcm_ServicePendingStatus.ucReadPerDidPendingStatus)
    {
      /* @Trace: Dcm_SUD_API_60749 */
      /* Only start periodic transmission request have PENDING state */
      (void) Dcm_Pdid_StartTransmission(DCM_CANCEL, pMsgContext);

      /* Clear pending status flag */
      Dcm_ServicePendingStatus.ucReadPerDidPendingStatus = DCM_FALSE;
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_GetDidRangeConfigIndex                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function is used to check if the      **
**                        requested DID is in DIDRange.                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : dataId                                              **
**                                                                            **
** Output Parameters    : pCfgIndex                                           **
**                                                                            **
** Return parameter     : LblResult                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
  (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(boolean, DCM_CODE) Dcm_GetDidRangeConfigIndex(
  uint16 dataId,
  Dcm_Uint16PtrType pCfgIndex)
{
  /* @Trace: Dcm_SUD_API_60750 */
  boolean LblResult = DCM_FALSE;

  #if (DCM_NUM_OF_DCMDSPDIDRANGECONFIG != DCM_ZERO)
  uint16 LusIdx;
  Dcm_DidRangeConfigPtrType LpDidRangeConfig = NULL_PTR;

  for (LusIdx = DCM_ZERO; LusIdx < DCM_NUM_OF_DCMDSPDIDRANGECONFIG; LusIdx++)
  {
    /* @Trace: Dcm_SUD_API_60751 */
    LpDidRangeConfig = Dcm_CfgInternal_GetDidRangeConfig(LusIdx);

    /* Verify if requested did is in the configured did range */
    if ((dataId >= LpDidRangeConfig->usDidRangeIdLowerLimit) && 
        (dataId <= LpDidRangeConfig->usDidRangeIdUpperLimit))
    {
      if (DCM_TRUE == LpDidRangeConfig->blDidRangeHasGaps)
      {
        if (NULL_PTR != LpDidRangeConfig->pIsDidAvailableFun)
        {
          /* @Trace: Dcm_SUD_API_60752 */
          Std_ReturnType LblRetVal;
          Dcm_DidSupportedType LddDidSupported = DCM_DID_SUPPORTED;
          
          /* Only support to run in synchronous mode */
          LblRetVal = LpDidRangeConfig->pIsDidAvailableFun(
            dataId, DCM_INITIAL, &LddDidSupported);

          if ((E_OK == LblRetVal) && (DCM_DID_SUPPORTED == LddDidSupported))
          {
            /* @Trace: Dcm_SUD_API_60753 */
            LblResult = DCM_TRUE;
          }
        }
      }
      else
      {
        /* @Trace: Dcm_SUD_API_60754 */
        LblResult = DCM_TRUE;
      }

      if (DCM_TRUE == LblResult)
      {
        /* @Trace: Dcm_SUD_API_60755 */
        *pCfgIndex = LusIdx;
        break;
      }
    }
  }
  #else
  DCM_UNUSED(dataId);
  DCM_UNUSED(pCfgIndex);
  #endif

  return LblResult;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspDidSearch                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function is used to check             **
**                        if the requested DID is in DIDRange.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : dataId                                              **
**                                                                            **
** Output Parameters    : pDidIndex, pIsDidRange                              **
**                                                                            **
** Return parameter     : LblResult                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(boolean, DCM_CODE) Dcm_DspDidSearch(
  uint16 dataId,
  Dcm_Uint16PtrType pDidIndex,
  Dcm_BooleanPtrType pIsDidRange)
{
  /* @Trace: Dcm_SUD_API_60756 */
  *pIsDidRange = DCM_FALSE;
  boolean LblResult = Dcm_GetDidConfigIndex(dataId, pDidIndex);

  if (DCM_FALSE == LblResult)
  {
    /* @Trace: Dcm_SUD_API_60757 */
    LblResult = Dcm_GetDidRangeConfigIndex(dataId, pDidIndex);
    *pIsDidRange = LblResult;
  }

  if (DCM_TRUE == LblResult)
  {
    /* @Trace: Dcm_SUD_API_60758 */
    Dcm_GusDIDIndexVal = *pDidIndex;
  }

  return LblResult;
}
#endif

/********************************************************************************
** Function Name        : Dcm_DspInternal_GetSizeOfDid                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to get size of a DID          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : aCfgDid                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : aIsVariableLength                                   **
**                                                                            **
** Return parameter     : the length of the DID                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : if DID don't have signal,                           **
**                        this function returns zero                          **
**                                                                            **
*******************************************************************************/
#if ((DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON) \
     || (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) \
     || (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON))
static FUNC(void, DCM_CODE) Dcm_DspInternal_GetSizeOfDid(
  Dcm_DidParaConfigConstPtrType pDidConfig,
  Dcm_Uint16PtrType pMinLength,
  Dcm_Uint16PtrType pMaxLength)
{
  /* @Trace: Dcm_SUD_API_60759 */
  Dcm_DataConfigConstPtrType pDataCfg;
  Dcm_DidSignalConfigPtrType pSignalCfg;

  if ((NULL_PTR != pDidConfig) && 
      (NULL_PTR != pMaxLength) && (NULL_PTR != pMinLength))
  {
    /* @Trace: Dcm_SUD_API_60760 */
    uint16 LusPrevDataPos = DCM_ZERO;
    uint16 LusNumOfSignal = pDidConfig->ucDcmDspSignalCount;

    *pMinLength = DCM_ZERO;
    *pMaxLength = DCM_ZERO;

    /* PRECONDITION:
     * 1) [constr_6039]
     *    Signals with variable datalength: Only the last signal
     *
     * 2) order of the signals
     *    all signal are ordered by usDcmDspDidDataPos
     *    we are no need to check the data positions.
     */

    /* If numOfSignal is zero, this function returns zero. */
    for(uint16 LusIdx = DCM_ZERO; LusIdx < LusNumOfSignal; LusIdx++)
    {
      /* @Trace: Dcm_SUD_API_60761 */
      pSignalCfg = &pDidConfig->pDcmDspSignal[LusIdx];

      if ((LusPrevDataPos <= pSignalCfg->usByteOffset) && 
          (NULL_PTR != pSignalCfg->pDataConfig))
      {
        /* @Trace: Dcm_SUD_API_60762 */
        pDataCfg = pSignalCfg->pDataConfig;
        *pMaxLength = pSignalCfg->usByteOffset + pDataCfg->usDcmDspDataByteSize;

        /* case 1) if last signal is a variable lenth, 
         *         pMinLength is not equal to pMaxLength.
         * case 2) if all signals are the fixed length, 
         *         pMinLength is equal to pMaxLength.
         * case 3) if a DID has a signal with variable length, 
         *         pMinLength is zero
         */

        /* @Trace: SWS_Dcm_00473 */
        if (DCM_DATA_TYPE_UINT8_DYN != pDataCfg->ucDcmDspDataType)
        {
          /* @Trace: Dcm_SUD_API_60763 */
          *pMinLength = *pMaxLength;
        }

        LusPrevDataPos = pSignalCfg->usByteOffset;
      }
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_GetDIDSupportInfoValue              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used to get DID support info value **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : dataIdentifier                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pSupportInfoValue                                   **
**                                                                            **
** Return parameter     : E_OK/E_NOT_OK                                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) && \
  (DCM_OBD_DID_SUPPORT_INFO == STD_ON))
static FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_GetDidSupportInfo(
  uint16 DataId,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pSupportInfo)
{
  uint8 LucSupportBit = DCM_ZERO;
  uint8 LucSupportByte = DCM_ZERO;
  Std_ReturnType LddRetVal = E_NOT_OK;

  uint16 LusDidIndex = DCM_ZERO;
  Dcm_DataConfigConstPtrType LpDataConfig = NULL_PTR;
  Dcm_DidParaConfigConstPtrType LpDidConfig = NULL_PTR;

  /* @Trace: Dcm_SUD_API_60764 */
  if (DCM_TRUE == Dcm_GetDidConfigIndex(DataId, &LusDidIndex))
  {
    /* @Trace: Dcm_SUD_API_60765 */
    LpDidConfig = Dcm_CfgInternal_GetDidConfig(LusDidIndex);

    if ((NULL_PTR != LpDidConfig) && 
        (NULL_PTR != LpDidConfig->pDcmDspDidSupportInfo))
    {
      uint8 LucIndex;
      uint8 LucNumOfSignal = LpDidConfig->ucDcmDspSignalCount;

      /* @Trace: Dcm_SUD_API_60766 */
      for (LucIndex = DCM_ZERO; LucIndex < LucNumOfSignal; LucIndex++)
      {
        /* @Trace: Dcm_SUD_API_60767 */
        LpDataConfig = LpDidConfig->pDcmDspSignal[LucIndex].pDataConfig;

        if (NULL_PTR != LpDataConfig->pDIDDataSupportInfoRef)
        {
          /* @Trace: Dcm_SUD_API_60768 */
          LddRetVal = E_OK;

          /* Get configuration support bit */
          LucSupportBit = LpDataConfig->ucDidDataSupportInfoBit;
          LucSupportBit = LucSupportBit % DCM_EIGHT;

          /* Calculation and assign to info value */
          LucSupportByte = DCM_ONE << LucSupportBit;
          *pSupportInfo |= LucSupportByte;
        }
      }
    }
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_GetConfigByDid                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get did configuration by data identifer             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : dataIdentifier                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LpDidConfig                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     ((DCM_MODE_CONDITION_SR_DID_USED == STD_ON)))
FUNC(Dcm_DidParaConfigConstPtrType, DCM_CODE) Dcm_DspInternal_GetConfigByDid(
  uint16 dataIdentifier)
{
  /* @Trace: Dcm_SUD_API_60769 */
  uint16 LusDidIndex = DCM_ZERO;
  Dcm_DidParaConfigConstPtrType LpDidConfig = NULL_PTR;

  if (DCM_TRUE == Dcm_GetDidConfigIndex(dataIdentifier, &LusDidIndex))
  {
    /* @Trace: Dcm_SUD_API_60770 */
    LpDidConfig = Dcm_CfgInternal_GetDidConfig(LusDidIndex);
  }

  return LpDidConfig;
}
#endif

#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
static FUNC(void, DCM_CODE) Dcm_Pdid_ClearBusyStatus(void)
{
  Dcm_PduIdTablePtrType LpPduIdTable;
  Dcm_PeriodicTxPduPtrType LpPerTxPdu;

  LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GddPerStatus.ddRxPduId];
  LpPerTxPdu = &LpPduIdTable->pPerTxPdu[Dcm_GddPerStatus.ucTxPduIdx];
  
  if (NULL_PTR != LpPerTxPdu)
  {
    /* Reset status for next transmission */
    LpPerTxPdu->blBusyStatus = DCM_FALSE;
  }

}
#endif

/*******************************************************************************
** Function Name        : Dcm_DspInternal_ReadDidByDataSpecificIf_ModeRule    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Read Non OBD DID using data specific interface      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pDidConfig                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pDataOut, pDataSize                                 **
**                                                                            **
** Return parameter     : LddRetVal                                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_MODE_CONDITION_SR_DID_USED == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidByDataSpecificIf_ModeRule(
  Dcm_DidParaConfigConstPtrType pDidConfig,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize)
{
  Std_ReturnType LddRetVal = E_OK;

  uint8 LusIndex;
  boolean LblSRSigFound = DCM_FALSE;
  uint8 LusSignalIndex = DCM_ZERO;
  uint8 LusNumOfSignal = pDidConfig->ucDcmDspSignalCount;

  uint16 LusSizeOfSignal = DCM_ZERO;
  Dcm_DataConfigConstPtrType LpDataCfg = NULL_PTR;
  Dcm_DidSignalConfigPtrType LpSignalCfg = NULL_PTR;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpOutBuffer;

  /* Checkes whether DID has at least one signal */
  if ((NULL_PTR != pDidConfig->pDcmDspSignal) && (DCM_ZERO != LusNumOfSignal))
  {
    /* Check whether DID Signal has the reference to DcmDspData,
     * and this DcmDspData also has the configuration DcmDataElementInstance
     * that is refered by DcmSwcSRDataElementRef */
    for (LusIndex = DCM_ZERO; LusIndex < LusNumOfSignal; LusIndex++)
    {
      if(LusIndex == pDidConfig->ucSRSignalIndex)
      {
        LusSignalIndex = LusIndex;
        LblSRSigFound = DCM_TRUE;
        break;
      }
    }

    if (LblSRSigFound == DCM_TRUE)
    {
      LpSignalCfg = &pDidConfig->pDcmDspSignal[LusSignalIndex];

      if (NULL_PTR == LpSignalCfg->pDataConfig)
      {
        DCM_REPORT_ERROR(DCM_VARIANT_FUNC_SID, DCM_E_PARAM);
        LddRetVal = E_NOT_OK;
      }
      else
      {
        LpDataCfg = LpSignalCfg->pDataConfig;
        LusSizeOfSignal = LpDataCfg->usDcmDspDataByteSize;
        LpOutBuffer = &Dcm_GaaDidReadSignalData[DCM_ZERO];

        LddRetVal = Dcm_CfgInternal_ReadSigTypeSenderReceiver(LpDataCfg, (void*)LpOutBuffer);

        if (E_OK == LddRetVal)
        {
          Dcm_DspReadDid_PackSignal(LusSizeOfSignal, 
            LpSignalCfg, LpOutBuffer, &pDataOut[*pDataSize]);
        }
        else
        {
          LddRetVal = E_NOT_OK;
        }
      }
    }
    else 
    {
      LddRetVal = E_NOT_OK;
    }
  }
  else
  {
    LddRetVal = E_NOT_OK;
  }

  return LddRetVal;
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */
/*******************************************************************************
 **                      End of File                                           **
 *******************************************************************************/
