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
**  SRC-MODULE: Dcm_Validate.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_Validate                                     **
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
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
*******************************************************************************/

#ifndef DCM_VALIDATE_H
#define DCM_VALIDATE_H

#define CHK_NEXT(ChkVal, ChkFunCall) \
  do { \
    if (DCM_TRUE == ChkVal) { \
      (ChkVal) = (ChkFunCall); \
    } \
  } while (0);

/* @Trace: SWS_Dcm_01414 SWS_Dcm_01415 */
#define CHK_ERRCODE_IN_FAIL_CASE(ApiId, ErrCode) \
  do { \
    if (ErrCode == DCM_POS_RESP) { \
      DCM_REPORT_RUNTIME_ERROR(ApiId, DCM_E_INVALID_VALUE); \
      (ErrCode) = DCM_E_GENERALREJECT; \
    } \
  } while (0);

#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(boolean, DCM_CODE) Dcm_ChkInit(uint8 ApiId);

extern FUNC(boolean, DCM_CODE) Dcm_ChkPduId(uint8 ApiId, PduIdType PduId);

extern FUNC(boolean, DCM_CODE) Dcm_ChkP2Var(uint8 ApiId, void *Ptr);

extern FUNC(boolean, DCM_CODE) Dcm_ChkP2Const(uint8 ApiId, const void *Ptr);

extern FUNC(boolean, DCM_CODE) Dcm_ChkComMChannel(uint8 ApiId, uint8 ComMChannelId);

extern FUNC(boolean, DCM_CODE) Dcm_ChkZeroLength(uint8 ApiId, uint32 Length);

extern FUNC(boolean, DCM_CODE) Dcm_ChkLength(uint8 ApiId, uint32 SrcLength, uint32 DstLength);

extern FUNC(boolean, DCM_CODE) Dcm_ChkNumRespPend(uint8 ApiId, uint16 NumRespPend);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
