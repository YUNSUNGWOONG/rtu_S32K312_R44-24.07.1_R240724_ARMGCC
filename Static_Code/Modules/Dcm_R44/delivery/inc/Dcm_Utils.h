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
**  SRC-MODULE: Dcm_Utils.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_Utils                                        **
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
** 0.0.1     31-Dec-2019   LanhLT         AR440 Implementation                **
** 0.0.2     19-Mar-2020   LanhLT         add Dcm_IsHigherPriorityProtocol()  **
** 0.0.3     19-May-2019   LanhLT         add Dcm_IsOBDRequestProcessing()    **
** 0.0.4     16-Aug-2020   HueKM          Add Dcm_GetPeriodicTxPduInfo()      **
** 0.0.5     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.6     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
*******************************************************************************/

#ifndef DCM_UTILS_H
#define DCM_UTILS_H

#include "Dcm_PCTypes.h"

#define VALIDATE_NEXT(ValidateVar, ValidateExp, Nrc) \
  do { \
    if ((ValidateVar == DCM_POS_RESP) && (ValidateExp)) { \
      (ValidateVar) = (Nrc); \
    } \
  } while (0);

#define CHK_RET_VAL(ChkRetValExp, Var, ValOrExp) \
  do { \
    if (ChkRetValExp) { \
      (Var) = (ValOrExp); \
    } \
  } while (0);

#if (0 < DCM_NUMBER_OF_REQUEST_MANUFACTURER_INDICATION)
  #define DCM_GET_MANU_CONFIRMATION_FUN(idx) Dcm_GaaManuIndConfigType[idx].pManuConfirmationFun
  #define DCM_GET_MANU_INDICATION_FUN(idx) Dcm_GaaManuIndConfigType[idx].pManuIndicationFun
#else
  #define DCM_GET_MANU_CONFIRMATION_FUN(idx) NULL_PTR
  #define DCM_GET_MANU_INDICATION_FUN(idx) NULL_PTR
#endif

#if (0 < DCM_NUMBER_OF_REQUEST_SUPPLIER_INDICATION)
  #define DCM_GET_SUPP_CONFIRMATION_FUN(idx) Dcm_GaaSuppIndConfigType[idx].pSuppConfirmationFun
  #define DCM_GET_SUPP_INDICATION_FUN(idx) Dcm_GaaSuppIndConfigType[idx].pSuppIndicationFun
#else
  #define DCM_GET_SUPP_CONFIRMATION_FUN(idx) NULL_PTR
  #define DCM_GET_SUPP_INDICATION_FUN(idx) NULL_PTR
#endif

#define DCM_IS_ACTIVE_PROTOCOL_STATUS() (Dcm_PrtclTxBufStatus.ucProtclStatus)
#define DCM_ACTIVATE_PROTOCOL_STATUS() (Dcm_PrtclTxBufStatus.ucProtclStatus = DCM_TRUE)
#define DCM_DEACTIVATE_PROTOCOL_STATUS() (Dcm_PrtclTxBufStatus.ucProtclStatus = DCM_FALSE)

#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(uint8, DCM_CODE) Dcm_Internal_GetDemClientId(void);

#if (DCM_MODE_RULE == STD_ON)
extern FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_CheckModeRule(
  boolean IsModeRuleConfigured
  , Dcm_ModeType ModeRuleIndex);
#endif

extern FUNC(boolean, DCM_CODE) Dcm_IsDiffConnection(PduIdType PduId1, PduIdType PduId2);

extern FUNC(boolean, DCM_CODE) Dcm_IsNotInNoComMode(uint8 ComMChannelId);

extern FUNC(boolean, DCM_CODE) Dcm_IsInFullComMode(uint8 ComMChannelId);

extern FUNC(boolean, DCM_CODE) Dcm_IsNotInReset(void);

extern FUNC(boolean, DCM_CODE) Dcm_IsFunctionalRequest(Dcm_PduIdTablePtrType pPduIdTable);

extern FUNC(boolean, DCM_CODE) Dcm_IsProcessingRequest(void);

extern FUNC(boolean, DCM_CODE) Dcm_IsReceivingToProcessOtherRequest(PduIdType PduId);

extern FUNC(boolean, DCM_CODE) Dcm_IsHigherPriorityProtocol(Dcm_PduIdTablePtrType pPduIdTable);

extern FUNC(boolean, DCM_CODE) Dcm_IsSpecialNrc(uint8 NrcVal);

extern FUNC(boolean, DCM_CODE) Dcm_IsNonDefaultSession(void);

extern FUNC(void, DCM_CODE) Dcm_GetUdsActiveProtocolInfo(
  Dcm_ProtocolTypePtrType pProtocolType
  , Dcm_Uint16PtrType pConnectionId
  , Dcm_Uint16PtrType pSourceTesterAddress);

extern FUNC(void, DCM_CODE) Dcm_GetProtocolInfo(
  PduIdType PduId
  , Dcm_ProtocolTypePtrType pProtocolType
  , Dcm_Uint16PtrType pConnectionId
  , Dcm_Uint16PtrType pSourceTesterAddress);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_SwitchProtocol(PduIdType PduId);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_StartProtocol(PduIdType PduId);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_StopProtocol(PduIdType PduId);

extern FUNC(void, DCM_CODE) Dcm_CancelAllReceivingOtherRequests(PduIdType PduId);

extern FUNC(boolean, DCM_CODE) Dcm_IsValidServiceId(uint8 ServiceId);

extern FUNC(boolean, DCM_CODE) Dcm_IsOBDRequest(
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) pPduIdTable);

extern FUNC(boolean, DCM_CODE) Dcm_IsOBDRequestById(PduIdType PduId);

extern FUNC(boolean, DCM_CODE) Dcm_IsUDSRequest(
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_APPL_CONST) pPduIdTable);

extern FUNC(boolean, DCM_CODE) Dcm_IsUDSRequestById(PduIdType PduId);

extern FUNC(void, DCM_CODE) Dcm_MemClear(
  Dcm_Uint8PtrType pDest
  , uint32 Size);

extern FUNC(void, DCM_CODE) Dcm_MemCopy(
  Dcm_Uint8PtrType pDest
  , Dcm_Uint8ConstPtrType pSrc
  , uint32 Size);

extern FUNC(boolean, DCM_CODE) Dcm_MemCompare(
  Dcm_Uint8ConstPtrType pDest
  , Dcm_Uint8ConstPtrType pSrc
  , uint32 Size
  , Dcm_ConditionType Condition);

extern FUNC(void, DCM_CODE) Dcm_SwitchCommMode_AllChannel(
  Dcm_CommunicationModeType CommMode);

extern FUNC(void, DCM_CODE) Dcm_SwitchCommMode_ReceivedOnChannel(
  Dcm_CommunicationModeType CommMode);

extern FUNC(void, DCM_CODE) Dcm_SwitchCommMode_SpecificChannel(
  Dcm_CommunicationModeType CommMode);

extern FUNC(void, DCM_CODE) Dcm_SwitchCommMode_SubNode(
  Dcm_CommunicationModeType CommMode);

extern FUNC(boolean, DCM_CODE) Dcm_IsSubNodeIdSupported(
  uint16 SubNodeId);

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
extern FUNC(uint32, DCM_CODE) Dcm_PagedBuffer_GetMaxRespLen(
  Dcm_MsgContextConstPtrType pMsgContext);
#endif

extern FUNC(Dcm_PduIdTablePtrType, DCM_CODE) Dcm_Internal_GetPduIdOnReset(
  uint16 testerAddress,
  P2VAR(PduIdType, AUTOMATIC, DCM_APPL_DATA) pRxPduId);

extern FUNC(uint16, DCM_CODE) Dcm_RequestParameterToUint16(
  uint8 numOfByte,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pData);

extern FUNC(uint32, DCM_CODE) Dcm_RequestParameterToUint32(
  uint8 numOfByte,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pData);

extern FUNC(uint64, DCM_CODE) Dcm_RequestParameterToUint64(
  uint8 numOfByte,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pData);

extern FUNC(void, DCM_CODE) Dcm_DataToResponseParameter(
  uint8 numOfByte,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pInData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pOutData);

extern FUNC(void, DCM_CODE) Dcm_Uint32ToResponseParameter(
  uint8 numOfByte,
  uint32 resData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pResData);

extern FUNC(void, DCM_CODE) Dcm_Uint64ToResponseParameter(
  uint8 numOfByte,
  uint64 resData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pResData);

extern FUNC(boolean, DCM_CODE) Dcm_CheckParameterByteLen(
  uint8 numOfByte,
  uint64 value);

#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
extern FUNC(Dcm_PeriodicTxPduPtrType, DCM_CODE) Dcm_GetPeriodicTxPduInfo(
  PduIdType RxPduId,
  uint8 PerTxPduIdx);
#endif

#if (DCM_PROTOCOL_TRANSTYPE2  ==  STD_ON)
extern FUNC(uint8, DCM_CODE) Dcm_IsProtocolType2(PduIdType Id);
#endif

extern FUNC(uint16, DCM_CODE) Dcm_GetDataIdFromRequest(
  uint16 offset,
  Dcm_Uint8PtrType pReqData);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
