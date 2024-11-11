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
**  SRC-MODULE: Dcm_DspServices.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_DspServices                                  **
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
** 0.0.2     03-Aug-2020   HueKM          Update code for SID2C as per #14836 **
** 0.0.3     16-Aug-2020   HueKM          Update code for SID2A as per #14836 **
** 0.0.4     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.5     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 1.4.1     01-Apr-2024   DanhTQ1        Refer #CP44-3362                    **
*******************************************************************************/

#ifndef DCM_DSPSERVICES_H
#define DCM_DSPSERVICES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_SessionControl.h"
#include "Dcm_DspEcuReset.h"
#include "Dcm_Authentication.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define DCM_START_SEC_CODE
#include "MemMap.h"

#if (DCM_READDTC_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadDTCInformation(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_DSP_CLR_DIAG_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmClearDiagnosticInformation(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspClearDiagInfo(
  uint32 GroupOfDTC
  , Dcm_MsgContextPtrType pMsgContext);
#endif

#if (DCM_DSP_CONTROL_DTC_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmControlDTCSetting(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_DSP_SECURITY_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmSecurityAccess(
  Dcm_OpStatusType OpStatus,
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NrcPtrType pErrorCode);

extern FUNC(void, DCM_CODE) Dcm_SecurityAccess_CancelOperation(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_SecurityAccess_PendingOperation(
  Dcm_MsgContextPtrType pMsgContext);
#endif

#if (DCM_DSP_TESTER_PRESENT_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmTesterPresent(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadDataByIdentifier(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_WriteDid_CancelOperation(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_WriteDid_PendingOperation(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmWriteDataByIdentifier(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
extern  FUNC(void, DCM_CODE) Dcm_DspReturnControlToEcu(void);

extern FUNC(void, DCM_CODE) Dcm_DspIOCtrl_CancelOperation(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_DspIOCtrl_PendingOperation(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmInputOutputControlByIdentifier(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadDataByPeriodicIdentifier(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode);

extern FUNC(void, DCM_CODE) Dcm_Pdid_PendingOperation(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_Pdid_CancelOperation(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_Pdid_HandleSessionOrSecurityChange(void);

extern FUNC(void, DCM_CODE) Dcm_Pdid_ClearQueueData(void);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Pdid_EnqueueData(
  uint16 usDid);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Pdid_DequeueData(
  Dcm_Uint16PtrType pDid);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_Pdid_EnqueueDataByMode(
  uint8 ucTmMode);

extern FUNC(void, DCM_CODE) Dcm_Pdid_InitData(void);
#endif

#if (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_ReadScalingInfo_CancelOperation(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_ReadScalingInfo_PendingOperation(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmReadScalingDataByIdentifier(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode);
#endif

#if((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON) || \
   (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
   (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON) || \
   (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
extern FUNC(boolean, DCM_CODE) Dcm_GetDidConfigIndex(
  uint16 dataId,
  Dcm_Uint16PtrType pCfgIndex);
#endif

#if (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_DynDid_InitData(
  Dcm_ConfigConstPtrType pConfig);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmDynamicallyDefineDataIdentifier(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_COMMUNICATION_CONTROL_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmCommunicationControl(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_DspRptDTCSnapshotRecByRecordNum(
  Dcm_MsgContextPtrType pMsgContext);
#endif

#if (DCM_LINK_CONTROL_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmLinkControlService(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmEnableNormalMsgTransmission(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext
  , Dcm_NrcPtrType pErrorCode);
#endif

#if (DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_DspInternal_DcmReadDataByIdentifier(
  Dcm_OpStatusType OpStatus
  , Dcm_MsgContextPtrType pMsgContext);
#endif

#if (DCM_MODE_CONDITION_SR_DID_USED == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidByDataSpecificIf_ModeRule(
  Dcm_DidParaConfigConstPtrType pDidConfig,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pDataOut,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) pDataSize);
#endif

#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     ((DCM_MODE_CONDITION_SR_DID_USED == STD_ON)))
extern FUNC(Dcm_DidParaConfigConstPtrType, DCM_CODE) Dcm_DspInternal_GetConfigByDid(
  uint16 dataIdentifier);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
