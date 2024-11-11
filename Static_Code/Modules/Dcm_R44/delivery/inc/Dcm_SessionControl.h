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
**  SRC-MODULE: Dcm_SessionControl.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains interfaces for services related to session **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date            By                Description                   **
********************************************************************************
** 0.0.1      29-Nov-2019     HueKM             Initial Version               **
** 0.0.2      13-Oct-2020     HueKM             Changes made as per #15766    **
*******************************************************************************/

#ifndef DCM_SESSION_CONTROL_H
#define DCM_SESSION_CONTROL_H

#include "Dcm_PCTypes.h"

#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, DCM_CODE) Dcm_InitSessionControl(
  Dcm_ConfigConstPtrType pConfig);

extern FUNC(Dcm_SessionConfigConstPtrType, DCM_CODE) Dcm_GetSesCtrlConfig(void);

extern FUNC(Dcm_SessionConfigConstPtrType, DCM_CODE) Dcm_GetSesCtrlConfigByIndex(
  uint8 SesCtrlIdx);

extern FUNC(Dcm_SessionConfigConstPtrType, DCM_CODE) Dcm_GetSesCtrlConfigByType(
  Dcm_SesCtrlType SesCtrlType);

#if (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmDiagnosticSessionControl(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode);

extern FUNC(void, DCM_CODE) Dcm_SesCtrl_TxConfirmation(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_ConfirmationStatusType ConfirmStatus);

extern FUNC(void, DCM_CODE) Dcm_SesCtrl_UpdateRespOnReset(
  Dcm_MsgContextPtrType pMsgContext,
  uint8 subfunctionId);

extern FUNC(void, DCM_CODE) Dcm_SesCtrl_ProcessProgPending(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_SesCtrl_CancelOperation(void);
#endif

#if (DCM_DSP_STOP_DIAG_SESSION_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmStopDiagnosticSession(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode);

extern FUNC(void, DCM_CODE) Dcm_StopSession_TxConfirmation(
  Dcm_MsgContextPtrType pMsgContext,
  Dcm_ConfirmationStatusType ConfirmStatus);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
