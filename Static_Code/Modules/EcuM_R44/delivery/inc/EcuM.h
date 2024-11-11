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
**  FILE-NAME : EcuM.h                                                        **
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
** 1.2.0     04-Oct-2022   TriBD             R44_2021 #27878, #13620          **
** 1.1.6     10-Aug-2022   Manje Woo         CP44-727                         **
** 1.1.4     17-Jan-2022   TriBD             R44_2021 #20832                  **
** 1.1.0     22-Mar-2021   TinhPV3           R44_2021 #17960                  **
** 1.0.1     05-Mar-2021   TinhPV3           R44_2021 #17961                  **
** 0.0.2     07-Apr-2020   LocLT5            R44-Redmine #655, #8670          **
** 0.0.1     14-Feb-2020   ThangMA            R44-Redmine #655, #8668         **
*******************************************************************************/

#ifndef ECUM_H
#define ECUM_H


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM_Externals.h"
#include "EcuM_Types.h"
#include "EcuM_Cfg.h"
#include "EcuM_PBcfg.h"
#include "EcuM_Generated_Types.h"
#include "Mcu.h"
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/* Instance ID */
#define ECUM_INSTANCE_ID                  ((uint8)0x00u)

/* Service ID for EcuM_GetVersionInfo */
#define ECUM_GETVERSIONINFO_SID           ((uint8)0x00u)

/* Service ID for EcuM_GoDownHaltPoll */
#define ECUM_GODOWNHALTPOLL_SID           ((uint8)0x2Cu)

/* Service ID for EcuM_Init */
#define ECUM_INIT_SID                     ((uint8)0x01u)

/* Service ID for EcuM_Shutdown */
#define ECUM_SHUTDOWN_SID                 ((uint8)0x02u)

/* Service ID for EcuM_SelectShutdownTarget */
#define ECUM_SELECTSHUTDOWNTARGET_SID     ((uint8)0x06u)

/* Service ID for EcuM_GetLastShutdownTarget */
#define ECUM_GETLASTSHUTDOWNTARGET_SID    ((uint8)0x08u)

/* Service ID for EcuM_GetShutdownTarget */
#define ECUM_GETSHUTDOWNTARGET_SID        ((uint8)0x09u)

/* Service ID for EcuM_SelectShutdownCause */
#define ECUM_SELECTSHUTDOWNCAUSE_SID      ((uint8)0x1Bu)

/* Service ID for EcuM_GetShutdownCause */
#define ECUM_GETSHUTDOWNCAUSE_SID         ((uint8)0x1Cu)

/* Service ID for EcuM_GetPendingWakeupEvents */
#define ECUM_GETPENDINGWAKEUPEVENTS_SID   ((uint8)0x0du)

/* Service ID for EcuM_ClearWakeupEvent */
#define ECUM_CLEARWAKEUPEVENT_SID         ((uint8)0x16u)

/* Service ID for EcuM_GetValidatedWakeupEvents */
#define ECUM_GETVALIDATEDWAKEUPEVENTS_SID ((uint8)0x15u)

/* Service ID for EcuM_GetExpiredWakeupEvents */
#define ECUM_GETEXPIREDWAKEUPEVENTS_SID   ((uint8)0x19u)

/* Service ID for EcuM_SetRelWakeupAlarm */
#define ECUM_SETRELWAKEUPALARM_SID        ((uint8)0x22u)

/* Service ID for EcuM_SetAbsWakeupAlarm */
#define ECUM_SETABSWAKEUPALARM_SID        ((uint8)0x23u)

/* Service ID for EcuM_AbortWakeupAlarm */
#define ECUM_ABORTWAKEUPALARM_SID         ((uint8)0x24u)

/* Service ID for EcuM_GetCurrentTime */
#define ECUM_GETCURRENTTIME_SID           ((uint8)0x25u)

/* Service ID for EcuM_GetWakeupTime */
#define ECUM_GETWAKEUPTIME_SID            ((uint8)0x26u)

/* Service ID for EcuM_SetClock */
#define ECUM_SETCLOCK_SID                 ((uint8)0x27u)

/* Service ID for EcuM_GetResetReason */
#define ECUM_GETRESETREASON_SID           ((uint8)0x28u)

/* Service ID for EcuM_SelectBootTarget */
#define ECUM_SELECTBOOTTARGET_SID         ((uint8)0x12u)

/* Service ID for EcuM_GetBootTarget */
#define ECUM_GETBOOTTARGET_SID            ((uint8)0x13u)

/* Service ID for EcuM_MainFunction */
#define ECUM_MAINFUNCTION_SID             ((uint8)0x18u)

/* Service ID for EcuM_SetWakeupEvents */
#define ECUM_SETWAKEUPEVENT_SID           ((uint8)0x0cu)

/* Service ID for EcuM_ValidateWakeupEvent */
#define ECUM_VALIDATEWAKEUPEVENT_SID      ((uint8)0x14u)

/* Service ID for EcuM_StartupTwo  */
#define ECUM_STARTUPTWO_SID               ((uint8)0x1au)

/* Service ID for EcuM_RequestRUN  */
#define ECUM_REQUESTRUN_SID               ((uint8)0x03u)

/* Service ID for EcuM_ReleaseRUN  */
#define ECUM_RELEASERUN_SID               ((uint8)0x04u)

/* Service ID for EcuM_ReleaseRUN  */
#define ECUM_REQUESTPOST_RUN_SID               ((uint8)0x0au)

/* Service ID for EcuM_ReleasePOST_RUN  */
#define ECUM_RELEASEPOST_RUN_SID               ((uint8)0x0bu)

/* Service ID for EcuM_SetState  */
#define ECUM_SETSTATE_SID               ((uint8)0x2Bu)

/* Service ID for EcuM_AL_DriverInitBswM_<x> */
#define ECUM_AL_DRIVERINITBSWM_SID    ((uint8)0x28u)



/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/

#define ECUM_ZERO                         (0x00u)
#define ECUM_ONE                          (0x01u)
#define ECUM_TWO                          (0x02u)
#define ECUM_FOUR                         (0x04u)

#define ECUM_NO_EVENTS                    ((EcuM_WakeupSourceType)0x00000000u)

#define ECUM_UNINITIALIZED                ((boolean)0x00u)
#define ECUM_INITIALIZED                  ((boolean)0x01u)

#define ECUM_FALSE                        ((boolean)0x00u)
#define ECUM_TRUE                         ((boolean)0x01u)

#define ECUM_COMM_INVALID_CHANNEL         ((uint16)65535u)
#define ECUM_COMMPNC_INVALID_ID           ((uint16)65535u)
#define ECUM_NO_ACTIVE_ALARM              ((uint32)0xFFFFFFFFu)

#define ECUM_ALRAM_LOOP_MAX               ((uint16)1000u)

#define ECUM_CONVERT_S_TO_MS              ((float32)1000)
/* polyspace-begin MISRA-C3:D4.9 [Not a defect:Justify with annotations] "Use function like-macro for reduce execution time and stack" */
/* polyspace-begin MISRA-C3:11.4 [Not a defect:Justify with annotations] "Justify with annotations" */
#define ECUM_UNUSED(x)                    (void)(x)

/* polyspace-end MISRA-C3:11.4 [Not a defect:Justify with annotations] "Justify with annotations" */
/* polyspace-end MISRA-C3:D4.9 [Not a defect:Justify with annotations] "Use function like-macro for reduce execution time and stack" */
/* polyspace-begin MISRA-C3:D4.9 [Not a defect:Justify with annotations] "Use function like-macro for reduce execution time and stack" */
#define ECUM_UNUSED_PTR(x)                ECUM_UNUSED(x)
/* polyspace-end MISRA-C3:D4.9 [Not a defect:Justify with annotations] "Use function like-macro for reduce execution time and stack" */

#define ECUM_INVALID_SLEEPMODEID       ((uint16) 0xffffu)

#define ECUM_INVALID_SHUTDOWN          ((uint8) 0xffu)

/* For EcuM Run Request State Check */
#define ECUM_RUN_RELEASED                 ((uint8)0x00u)
#define ECUM_RUN_REQUESTED                ((uint8)0x01u)
#define ECUM_RUN_RUNNING                  ((uint8)0x02u)


#define ECUM_STATEREQ_ID                  ((uint16)0x65u)

#define ECUM_CLOCK_PERIOD                 ((float32)1)

#define ECUM_WAKEUP_PERIOD                ((uint32)20u)



/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define ECUM_START_SEC_CODE
#include "MemMap.h"

#if (STD_ON == ECUM_VERSION_INFO_API)
/* Extern for EcuM_GetVersionInfo API */
extern FUNC(void, ECUM_CODE) EcuM_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, ECUM_APPL_DATA)versioninfo);
#endif

/* Check For Rte_EcuM.h Has Extern for EcuM_ShutdownTarget CS IF */
#ifndef RTE_RUNNABLE_SelectShutdownTarget
/* Extern for EcuM_SelectShutdownTarget API */
/* polyspace<MISRA-C:8.8:Not a defect:Justify with annotations> also used by BswM (AUTOSAR Standard : BswM0008) */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectShutdownTarget
  (EcuM_ShutdownTargetType shutdownTarget, EcuM_ShutdownModeType shutdownMode);
#endif

#ifndef RTE_RUNNABLE_GetShutdownTarget
/* Extern for EcuM_GetShutdownTarget API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetShutdownTarget
  (P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
  P2VAR(EcuM_ShutdownModeType, AUTOMATIC, ECUM_APPL_DATA) shutdownMode);
#endif

#ifndef RTE_RUNNABLE_GetLastShutdownTarget
/* Extern for EcuM_GetLastShutdownTarget API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetLastShutdownTarget
  (P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
  P2VAR(EcuM_ShutdownModeType, AUTOMATIC, ECUM_APPL_DATA) shutdownMode);
#endif

#ifndef RTE_RUNNABLE_SelectShutdownCause
/* Extern for EcuM_SelectShutdownCause API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectShutdownCause
           (EcuM_ShutdownCauseType target);
#endif

#ifndef RTE_RUNNABLE_GetShutdownCause
/* Extern for EcuM_GetShutdownCause API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetShutdownCause
  (P2VAR(EcuM_ShutdownCauseType, AUTOMATIC, ECUM_APPL_DATA) shutdownCause);
#endif

#ifndef RTE_RUNNABLE_GoDownHaltPoll
/* Extern for EcuM_GoDownHaltPoll */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoDownHaltPoll(uint16 caller);
#endif

/* Extern for EcuM_Init API */
extern FUNC(void, ECUM_CODE) EcuM_Init(void);

/* Internal Function for StateStartpTwo */
extern FUNC(void, ECUM_CODE) EcuM_StartupTwo(void);

/* Extern for EcuM_Shutdown API */
extern FUNC(void, ECUM_CODE) EcuM_Shutdown(void);

/* Extern for EcuM_GetPendingWakeupEvents API */
extern FUNC(EcuM_WakeupSourceType, ECUM_CODE)
  EcuM_GetPendingWakeupEvents(void);

/* Extern for EcuM_GetValidatedWakeupEvents API */
extern FUNC(EcuM_WakeupSourceType, ECUM_CODE)
  EcuM_GetValidatedWakeupEvents(void);

/* Extern for EcuM_ClearWakeupEvent API */
/* polyspace<MISRA-C:8.8:Not a defect:Justify with annotations> also used by BswM (AUTOSAR Standard : BswM0008) */
extern FUNC(void, ECUM_CODE) EcuM_ClearWakeupEvent
  (EcuM_WakeupSourceType sources);

/* Extern for EcuM_GetExpiredWakeupEvents API */
extern FUNC(EcuM_WakeupSourceType, ECUM_CODE) EcuM_GetExpiredWakeupEvents(void);

/* Extern for EcuM_GetResetReason API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetResetReason
  (P2VAR(Mcu_ResetType, AUTOMATIC, ECUM_APPL_DATA) resetreason);

#ifndef RTE_RUNNABLE_SetClock
/* Extern for EcuM_SetClock API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_SetClock(EcuM_UserType user,
  EcuM_TimeType time);
#endif

#ifndef RTE_RUNNABLE_SetRelWakeupAlarm
/* Extern for EcuM_SetRelWakeupAlarm API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_SetRelWakeupAlarm(EcuM_UserType user,
       EcuM_TimeType time);
#endif

#ifndef RTE_RUNNABLE_SetAbsWakeupAlarm
/* Extern for EcuM_SetAbsWakeupAlarm API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_SetAbsWakeupAlarm(EcuM_UserType user,
       EcuM_TimeType time);
#endif

#ifndef RTE_RUNNABLE_GetCurrentTime
/* Extern for EcuM_GetCurrentTime API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetCurrentTime
  (P2VAR(EcuM_TimeType, AUTOMATIC, ECUM_APPL_DATA) time);
#endif

#ifndef RTE_RUNNABLE_GetWakeupTime
/* Extern for EcuM_GetWakeupTime API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetWakeupTime
      (P2VAR(EcuM_TimeType, AUTOMATIC, ECUM_APPL_DATA) time);
#endif

#ifndef RTE_RUNNABLE_AbortWakeupAlarm
/* Extern for EcuM_AbortWakeupAlarm API */
extern FUNC(Std_ReturnType, ECUM_CODE)
  EcuM_AbortWakeupAlarm(EcuM_UserType user);
#endif

/* Extern for EcuM_RequestRUN API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_RequestRUN(EcuM_UserType user);

/* Extern for EcuM_ReleaseRUN API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_ReleaseRUN(EcuM_UserType user);

/* Extern for EcuM_RequestPOST_RUN API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_RequestPOST_RUN(EcuM_UserType user);

/* Extern for EcuM_ReleasePOST_RUN API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_ReleasePOST_RUN(EcuM_UserType user);

/* Extern for EcuM_SetState API */
extern FUNC(void, ECUM_CODE) EcuM_SetState(EcuM_ShutdownTargetType state);

#ifndef RTE_RUNNABLE_SelectBootTarget
/* Extern for EcuM_SelectBootTarget API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectBootTarget
  (EcuM_BootTargetType target);
#endif

#ifndef RTE_RUNNABLE_GetBootTarget
/* Extern for EcuM_GetBootTarget API */
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetBootTarget
  (P2VAR(EcuM_BootTargetType, AUTOMATIC, ECUM_APPL_DATA) target);
#endif

// Callback function prototype
/* Extern for EcuM_SetWakeupEvent API */
extern FUNC(void, ECUM_CODE) EcuM_SetWakeupEvent
  (EcuM_WakeupSourceType sources);

/* Extern for EcuM_ValidateWakeupEvent API */
extern FUNC(void, ECUM_CODE) EcuM_ValidateWakeupEvent
  (EcuM_WakeupSourceType sources);

/* Extern for EcuM_McuPostInit in Internal.h */
extern FUNC(void, ECUM_CODE) EcuM_McuPostInit (void);

extern FUNC(boolean, ECUM_CODE) EcuM_IsMasterCore(void);

#define ECUM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

#endif /* ECUM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

