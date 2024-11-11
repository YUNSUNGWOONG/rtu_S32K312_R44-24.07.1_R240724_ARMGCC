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
**  SRC-MODULE: Dcm_RoutineControl.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains interfaces for services related to routine **
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
** 0.0.1      03-Jul-2020     HueKM             Initial Version               **
** 0.0.2      13-Oct-2020     HueKM             Changes made as per #15766    **
*******************************************************************************/
#ifndef DCM_ROUTINECONTROL_H
#define DCM_ROUTINECONTROL_H

#define DCM_START_SEC_CODE
#include "MemMap.h"

#if (DCM_ROUTINECONTROL_SERVICE == STD_ON)

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmRoutineControl(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode);

extern FUNC(void, DCM_CODE) Dcm_RidCtrl_InitData(void);

extern FUNC(void, DCM_CODE) Dcm_RidCtrl_CancelOperation(void);

extern FUNC(void, DCM_CODE) Dcm_RidCtrl_PendingOperation(
  Dcm_MsgContextPtrType pMsgContext);

#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DCM_ROUTINECONTROL_H */

/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
