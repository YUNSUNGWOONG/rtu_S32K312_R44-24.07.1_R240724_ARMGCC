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
**  SRC-MODULE: Dcm_Lib.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_Lib                                          **
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
** 0.0.2     16-Aug-2020   HueKM          Fix defect and coding rules         **
** 0.0.3     13-Oct-2020   LanhLT         Changes made as per #15766          **
*******************************************************************************/

#ifndef DCM_LIB_H
#define DCM_LIB_H

#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_ChkSuppressPosResponse(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxData
  , Dcm_MsgLenType MsgDataLen);

extern FUNC(void, DCM_CODE) Dcm_DspInternal_DcmEnableNormalMsgTransmission(
  Dcm_MsgContextPtrType pMsgContext);

#if (DCM_DSP_DIAG_SESSION_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_ChkSessionLevel(
  Dcm_SesCtrlType SessionLevel);
#endif

#if (DCM_DSP_STOP_DIAG_SESSION_SERVICE == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_DspInternal_DcmStopDiagnosticSession(
  Dcm_MsgContextPtrType pMsgContext);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DCM_LIB_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
