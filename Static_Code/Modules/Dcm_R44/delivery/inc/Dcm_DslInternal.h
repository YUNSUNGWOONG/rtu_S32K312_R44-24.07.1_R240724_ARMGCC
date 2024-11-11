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
**  SRC-MODULE: Dcm_DslInternal.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_DslInternal                                  **
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
** 0.0.2     16-Aug-2020   HueKM          Update code for SID2A as per #14836 **
** 0.0.3     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.4     02-Nov-2020   LanhLT         Changes made as per #16832          **
** 0.0.5     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
*******************************************************************************/

#ifndef DCM_DSLINTERNAL_H
#define DCM_DSLINTERNAL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_DslManageSecurity.h"
#include "Dcm_Timer.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DslWPduR_DcmTransmit(
  PduIdType RxPduId,
  PduIdType TxPduId,
  PduInfoPtrType pPduInfo);

extern FUNC(void, DCM_CODE) Dcm_DslPduRTransmit(void);

/* sg.baek 022305 - Task #2163 in redmine */
extern FUNC(void, DCM_CODE) Dcm_DslCheckPrtclStatus(void);

extern FUNC(void, DCM_CODE) Dcm_DslTxIncorrectCondition(
  uint8 API_ServiceId);

extern FUNC(void, DCM_CODE) Dcm_DslSetSesTimingValues(
  P2CONST(Dcm_TimerServerType, AUTOMATIC, DCM_APPL_DATA) NewTiming);

extern FUNC(void, DCM_CODE) DslInternal_SetSesCtrlType(
  Dcm_SesCtrlType NewSesCtrlType);

/*******************************************************************************
**                     Periodic transmission handling                         **
*******************************************************************************/
#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
extern FUNC(Dcm_StatusType, DCM_CODE) DslInternal_ResponseOnOneDataByPeriodicId(
  uint8 PeriodicId);
#endif

/*******************************************************************************
**                     Response On Event handling                             **
*******************************************************************************/
#if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
extern FUNC(Dcm_StatusType, DCM_CODE) DslInternal_ResponseOnOneEvent(
   const Dcm_MsgType MsgPtr, Dcm_MsgLenType LddMsgLen, uint16 ConnectionId);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
