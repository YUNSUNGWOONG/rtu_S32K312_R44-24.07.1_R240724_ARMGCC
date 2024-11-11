/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  FILE-NAME : BswM_EcuM.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR BswM Module                                           **
**                                                                            **
**  PURPOSE   : Providing interface to EcuM                                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 0.0.1     27-Feb-2020   ThangMA            R44-Redmine #4579, #10093       **
*******************************************************************************/

#ifndef BSWM_ECUM_H
#define BSWM_ECUM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "ComStack_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define BSWM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, BSWM_CODE) BswM_EcuM_CurrentState
  (EcuM_StateType CurrentState);
/*ThangMA*/
extern FUNC(void, BSWM_CODE) BswM_EcuM_RequestedState
  (EcuM_StateType State, EcuM_RunStatusType CurrentStatus);
  
extern FUNC(void, BSWM_CODE) BswM_EcuM_CurrentWakeup
  (EcuM_WakeupSourceType source, EcuM_WakeupStatusType state);
#define BSWM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* BSWM_ECUM_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
