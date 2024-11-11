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
**  SRC-MODULE: Dcm_DsdInternal.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_DsdInternal                                  **
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
** 0.0.2     16-Aug-2020   HueKM          Update code for SID2A as per #14836 **
** 0.0.3     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
*******************************************************************************/

#ifndef DCM_DSDINTERNAL_H
#define DCM_DSDINTERNAL_H

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(Dcm_ServiceIdConfigConstPtrType, DCM_CODE) Dcm_GetServiceConfigPtr(
  uint8 ServiceId);

extern FUNC(boolean, DCM_CODE) Dcm_DsdIndication(
  PduIdType RxPduId
  , boolean IsStopProtocol
  , boolean IsPerTransmission
  , boolean IsRoeTransmission);

extern FUNC(void, DCM_CODE) Dcm_DsdCancelOperation(void);

extern FUNC(boolean, DCM_CODE) Dcm_DsdCancelTransmission(
  PduIdType RxPduId);

extern FUNC(void, DCM_CODE) Dcm_DsdResetPendingFlag(void);

extern FUNC(void, DCM_CODE) Dcm_DsdConfirmation(
  Std_ReturnType Result);

extern FUNC(uint8, DCM_CODE) Dcm_GetProtocolTypeIndex(
  uint8 ProtocolId);

extern boolean Dcm_DsdValidateSecurity(
  Dcm_Uint8ConstPtrType pSecLvlCfg
  , uint8 SecLvlNum);

extern boolean Dcm_DsdValidateSession(
  Dcm_Uint8ConstPtrType pSesCtrlCfg
  , uint8 SesCtrlNum);

extern FUNC(boolean, DCM_CODE) Dcm_DsdReqManuConfirm(
  uint8 SID
  , PduIdType RxPduId
  , Dcm_ConfirmationStatusType ConfirmStatus);

extern FUNC(boolean, DCM_CODE) Dcm_DsdReqSuppConfirm(
  uint8 SID
  , PduIdType RxPduId
  , Dcm_ConfirmationStatusType ConfirmStatus);


/*******************************************************************************
**                     Response completion handling                           **
*******************************************************************************/
extern FUNC(void, DCM_CODE) Dcm_ExternalSetNegResponse(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType ErrorCode);

extern FUNC(void, DCM_CODE) Dcm_ExternalProcessingDone(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_InternalSetNegResponse(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_NegativeResponseCodeType ErrorCode);

extern FUNC(void, DCM_CODE) Dcm_InternalProcessingDone(
  Dcm_MsgContextPtrType pMsgContext,
  boolean IsSync);

/*******************************************************************************
**                       Paged transmission handling                          **
*******************************************************************************/
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_DsdStartPagedProcessing(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_DsdProcessPage(
  Dcm_MsgLenType FilledPageLen);
#endif

extern FUNC(Dcm_MsgType, DCM_CODE) Dcm_DsdInternal_GetMsgTxBuffer(
  PduIdType aPduId,
  Dcm_BufferKindType aBufferKind);

extern FUNC(uint32, DCM_CODE) Dcm_DsdInternal_GetBufferSize(
  PduIdType PduId,
  Dcm_BufferKindType BufferKind);

/*******************************************************************************
**                       Request Dispatcher                                   **
*******************************************************************************/
extern FUNC(void, DCM_CODE) Dcm_DiagnosticServiceDispatch(
  Dcm_OpStatusType OpStatus,
  Dcm_RequestContextPtrType pRequestContext);

/*******************************************************************************
**                     Message context                                        **
*******************************************************************************/
extern FUNC(Dcm_BufferConfigConstPtrType, DCM_CODE) Dcm_GetBufferConfigPtr(
  PduIdType RxPduId);

extern FUNC(Dcm_ProtocolConfigConstPtrType, DCM_CODE) Dcm_GetProtocolConfigPtr(
  PduIdType RxPduId);

extern FUNC(Dcm_RequestContextPtrType, DCM_CODE) Dcm_GetRequestContextPtr(
  PduIdType RxPduId);

extern FUNC(Dcm_SubServiceIdConfigConstPtrType, DCM_CODE) Dcm_GetSubServiceConfigPtr(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_InitRequestContext(void);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
