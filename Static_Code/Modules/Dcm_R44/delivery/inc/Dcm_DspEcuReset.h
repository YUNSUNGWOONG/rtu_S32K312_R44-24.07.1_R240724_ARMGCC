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
**  SRC-MODULE: Dcm_DspEcuReset.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_DspEcuReset                                  **
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
** 0.0.2     13-Oct-2020   HueKM          Changes made as per #15766          **
*******************************************************************************/

#ifndef DCM_DSPECURESET_H
#define DCM_DSPECURESET_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_PCTypes.h"

/*******************************************************************************
**                        Public Functions                                    **
*******************************************************************************/
#if (DCM_ECURESET_SERVICE == STD_ON)
#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, DCM_CODE) Dcm_EcuReset_InitData(void);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmECUResetService(
  Dcm_OpStatusType OpStatus, 
  Dcm_MsgContextPtrType pMsgContext, 
  Dcm_NrcPtrType pErrorCode);

extern FUNC(void, DCM_CODE) Dcm_EcuReset_TxConfirmation(
  Dcm_ConfirmationStatusType confirmStatus,
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_EcuReset_UpdateRespOnReset(
  Dcm_MsgContextPtrType pMsgContext, 
  uint8 resetType);

extern FUNC(void, DCM_CODE) Dcm_EcuReset_ProcessProgPending(
  Dcm_MsgContextPtrType pMsgContext);

extern FUNC(void, DCM_CODE) Dcm_EcuReset_CancelOperation(void);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
