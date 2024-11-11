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
**  FILE-NAME : EcuM_Internal.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Provision of external declaration of APIs and Service IDs     **
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
** 1.2.0     04-Oct-2022   TriBD             R44_2021 #27878                  **
** 1.1.6     10-Aug-2022   Manje Woo         CP44-727                         **
** 1.0.1     05-Mar-2021   TinhPV3           R44_2021 #17961                  **
** 0.0.3     30-Jul-2020   ThiNT8            R44-Redmine #655, #14588         **
** 0.0.2     07-Apr-2020   LocLT5            R44-Redmine #655, #8670          **
** 0.0.1     14-Feb-2020   ThangMA            R44-Redmine #655, #8668         **
*******************************************************************************/

#ifndef ECUM_INTERNAL_H
#define ECUM_INTERNAL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM_Cfg.h"

#include "Mcu.h"
#if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
#include "Os.h"
#endif


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define ECUM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(boolean, ECUM_CODE) EcuM_SearchMode
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) lpModeIdx, EcuM_ShutdownModeType mode);

extern FUNC(boolean, ECUM_CODE) EcuM_SearchShutdownCause
 (P2VAR(uint8, AUTOMATIC, ECUM_DATA) lpCauseIdx,
  EcuM_ShutdownCauseType target);

extern FUNC(boolean, ECUM_CODE) EcuM_SearchWakeupSource
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) lpSourceIdx,
  EcuM_WakeupSourceType WakeupSource);

extern FUNC(boolean, ECUM_CODE) EcuM_SearchGoDownUser
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) lpGoDownUserIdx,
  EcuM_UserType user);

#if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
extern FUNC(boolean, ECUM_CODE) EcuM_SearchAlarmClockUser
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) lpAlarmUserIdx,
  EcuM_UserType user);

extern FUNC(void, ECUM_CODE) EcuM_ClearAlarm(void);

extern FUNC(void, ECUM_CODE) EcuM_GetGptTicks
  (P2VAR(uint32, AUTOMATIC, ECUM_DATA) lpTickValue);
#endif

extern FUNC(boolean, ECUM_CODE) EcuM_GoSleepSeq
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) lucSleepModeIndex);

extern FUNC(void, ECUM_CODE) EcuM_WakeupRestartSeq(void);

extern FUNC(void, ECUM_CODE) EcuM_CheckResetReason(Mcu_ResetType ResetReason);

extern FUNC(void, ECUM_CODE) EcuM_PollSeq(void);

extern FUNC(void, ECUM_CODE) EcuM_ValidationProtocol(void);

extern FUNC(Std_ReturnType, ECUM_CODE)
  EcuM_GoHaltSequence(uint8 sleepModeIndex);

extern FUNC(Std_ReturnType, ECUM_CODE)
  EcuM_GoPollSequence(uint8 sleepModeIndex);

extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoDownSequence(void);

#if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
extern FUNC(void, ECUM_CODE) EcuM_OsWaitEvent(void);

extern FUNC(void, ECUM_CODE) EcuM_OsSetEvent(CoreIdType lddCoreId);

extern FUNC(void, ECUM_CODE) EcuM_SlaveShutDownOrSleep(CoreIdType lddCoreId);
#endif

#if (STD_ON == ECUM_DEV_ERROR_DETECT)
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_DetReportError(uint8 LucApiId,
  uint8 LucErrorId);
#endif

extern FUNC(boolean, ECUM_CODE) EcuM_SearchSleepModeWakeupSource
  (P2VAR(uint8, AUTOMATIC, ECUM_DATA) lpSourceIdx,
  EcuM_WakeupSourceType WakeupSource);

extern FUNC(void, ECUM_CODE) EcuM_GetOSResource (void);

extern FUNC(void, ECUM_CODE) EcuM_ReleaseOSResource (void);

extern FUNC(void, ECUM_CODE) EcuM_EnableInterrupts (void);

extern FUNC(void, ECUM_CODE) EcuM_ProcessModeHandingChangedRequest(void);

extern FUNC(void, ECUM_CODE) EcuM_SlaveCoreHaltSequence(
  VAR(uint8,ECUM_VAR) slaveSleepModeIndex, VAR(CoreIdType, ECUM_VAR) lddCoreId);

extern FUNC(void, ECUM_CODE) EcuM_SlaveCorePollSequence(
  VAR(uint8,ECUM_VAR) slaveSleepModeIndex, VAR(CoreIdType, ECUM_VAR) lddCoreId);

#define ECUM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ECUM_INTERNAL_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

