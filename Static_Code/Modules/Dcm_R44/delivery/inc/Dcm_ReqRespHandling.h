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
**  SRC-MODULE: Dcm_ReqRespHandling.h                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_ReqRespHandling                              **
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
** 0.0.2     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 1.0.13    10-Jul-2023   DanhTQ1        Refer #CP44-2474                    **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
*******************************************************************************/

#ifndef DCM_REQ_RESP_HANDLING_H
#define DCM_REQ_RESP_HANDLING_H

#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, DCM_CODE) Dcm_InitReqRespHandling(
  Dcm_ConfigConstPtrType pConfig);

#if (DCM_PARALLEL_PROTOCOL_PROCESSING == STD_ON)
extern FUNC(boolean, DCM_CODE) Dcm_AddNewRequestToQueue(
  PduIdType RxPduId);

extern FUNC(boolean, DCM_CODE) Dcm_AddPendingRequestToQueue(
  PduIdType RxPduId);

extern FUNC(void, DCM_CODE) Dcm_GetNextRequestFromQueue(void);

extern FUNC(void, DCM_CODE) Dcm_AddCurrentPendingRequestToQueue(void);

extern FUNC(void, DCM_CODE) Dcm_DelRequestFromQueue(
  PduIdType RxPduId);

// (*) ONLY call this function after processed a request
extern FUNC(void, DCM_CODE) Dcm_TriggerAddPendingRequestToQueue(void);

extern FUNC(void, DCM_CODE) Dcm_SetPendingAsyncCsif(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) PendingAsyncCsif);

extern FUNC(boolean, DCM_CODE) Dcm_IsAsyncCsifPending(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) PendingAsyncCsif);
#endif

// negative response
extern FUNC(void, DCM_CODE) Dcm_CopyNegResp(
  Dcm_Uint8PtrType pData, PduLengthType DataLen);

extern FUNC(void, DCM_CODE) Dcm_GetNegResp(
  PduInfoPtrType pPduInfo);

extern FUNC(void, DCM_CODE) Dcm_SetNegResp(
  uint8 Sid, uint8 Nrc);

extern FUNC(void, DCM_CODE) Dcm_ClearNegResp(void);

/* Negative response for second declined request */
#if (DCM_RESPONSEON_SECOND_DECLINE_REQUEST == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_CopyNegResp_DeclinedRequest(
  Dcm_Uint8PtrType pData, PduLengthType DataLen);

extern FUNC(void, DCM_CODE) Dcm_GetNegResp_DeclinedRequest(
  PduInfoPtrType pPduInfo);

extern FUNC(void, DCM_CODE) Dcm_SetNegResp_DeclinedRequest(
  uint8 Sid, uint8 Nrc);

extern FUNC(void, DCM_CODE) Dcm_ClearNegResp_DeclinedRequest(void);
#endif

// util
extern FUNC(boolean, DCM_CODE) Dcm_IsNormalResponseNotReady(void);

extern FUNC(boolean, DCM_CODE) Dcm_IsNormalResponseReady(void);

extern FUNC(boolean, DCM_CODE) Dcm_IsPagedResponseNotReady(void);

extern FUNC(boolean, DCM_CODE) Dcm_IsNegRespReady(void);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
