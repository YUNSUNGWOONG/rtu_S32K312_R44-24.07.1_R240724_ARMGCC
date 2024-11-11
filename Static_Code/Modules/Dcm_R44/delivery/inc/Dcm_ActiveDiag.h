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
**  SRC-MODULE: Dcm_ActiveDiag.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_ActiveDiag                                   **
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

#ifndef DCM_ACTIVEDIAG_H
#define DCM_ACTIVEDIAG_H

/*******************************************************************************
**                      Active Diagnostic Trigger Event Type                  **
*******************************************************************************/
// AD_TE = Active Diagnostic Trigger Event
typedef enum
{
  AD_TE_SESSION_CHANGE
  , AD_TE_FIRST_CALLED
  , AD_TE_TIMER_S3_EXPIRED
  , AD_TE_RECEIVED_REQUEST
  , AD_TE_FINISHED_REQUEST
  , AD_TE_PROTOCOL_PREEMPTION
  , AD_TE_MAX_NUM
} Dcm_ActiveDiagnosticTriggerEventType;


#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, DCM_CODE) Dcm_InitActiveDiagnostic(
  Dcm_ConfigConstPtrType pConfig);

extern FUNC(void, DCM_CODE) Dcm_TriggerEventActivationDiagnostic(
  Dcm_ActiveDiagnosticTriggerEventType LucEvent);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
