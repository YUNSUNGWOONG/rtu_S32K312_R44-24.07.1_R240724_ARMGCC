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
**  FILE-NAME : EcuM_PCTypes.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Provision of pre-compile time parameters                      **
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
** 1.0.1     05-Mar-2021   TinhPV3           R44_2021 #17961                  **
** 0.0.8     07-Dec-2020   TinhPV3           Multicores #17105, #17249        **
** 1.0.2     30-Jul-2020   ThiNT8            R44-Redmine #655, #14588         **
** 1.0.1     15-Jul-2020   ThiNT8            R44-Redmine #655, #14603         **
** 1.0.0     14-Feb-2020   ThangMA            R44-Redmine #655, #8668         **
*******************************************************************************/

#ifndef ECUM_PCTYPES_H
#define ECUM_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"

#include "Mcu.h"
#include "ComStack_Types.h"
#include "Os.h"

/*******************************************************************************
**                       Global Data                                          **
*******************************************************************************/
/* Structure for EcuM Flex Users */
typedef struct
{
  /* User Id */
  EcuM_UserType User;

  /* Core Id */
  CoreIdType CoreId;
} EcuM_FlexUserType;

/* Structure for EcuM Sleep Modes */
typedef struct
{
  /* Status Mask for Wakeup Source */
  EcuM_WakeupSourceType WakeupSourceMask;

  /* Mcu Mode type */
  Mcu_ModeType McuSleepModeType;

  /* Sleep Mode ID */
  uint8 SleepModeId;

  /* Sleep Mode suspend */
  boolean SleepModeSuspnd;
} EcuM_SleepModeConfigType;

/* Structure for EcuM Wakeup Source */
typedef struct
{
  /* RAM Pointer to EcuM_GaaWakeupCounter */
  P2VAR(uint16, AUTOMATIC, ECUM_CONFIG_DATA)
  ptrEcuMWakeupCounter;

  /* RAM Pointer to EcuM_GaaWakeupStatus */
  P2VAR(EcuM_WakeupStatusType, AUTOMATIC, ECUM_CONFIG_DATA)
  ptrEcuMWakeupStatus;

  /* RAM Pointer to EcuM_GaaCheckWakeupCounter */
  P2VAR(uint16, AUTOMATIC, ECUM_CONFIG_DATA)
  ptrEcuMCheckWakeupCounter;

  /* Wakeup Source Id */
  EcuM_WakeupSourceType WakeupSourceId;

  /* Timer Count for CheckWakeup */  // ECUC_EcuM_00208
  uint16 CheckWakeupTimeOut;

  /* ComM Channel ID */
  uint16 ComMChannel;

  /* ComM PNC Group */  // ECUC_EcuM_00228
  P2CONST(uint8, AUTOMATIC, ECUM_CONFIG_DATA)
  ptrComMPNCGroup;

  /* Timer Count for Validation */
  uint16 WakeupValidationTimeOut;

  /* Reset Reason Detected by MCU Driver */
  Mcu_ResetType ResetReason;

  /* Wakeup Source Polling */
  boolean WakeupSourcePolling;
} EcuM_WakeupSourceConfigType;

#if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)

/* Structure for EcuM Alarm Clock  */
typedef struct
{
  /* Reference to EcuMFlexUserConfig from EcuMAlarmClockUser */
  EcuM_UserType User;

  /* Alarm clock timeout */
  uint16 AlarmClockTimeOut;

  /* Alarm clock Id */
  uint8 AlarmClockId;
  
} EcuM_AlarmClockType;
#endif /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

 /* Structure for EcuM Shutdown target */
typedef struct
{
  /* Most recent shutdown target / Last shutdown target of EcuM */
  EcuM_StateType MostRecentTarget;

  /* Next recent shutdown target / Last shutdown target of EcuM */
  EcuM_StateType NextRecentTarget;

  /* Most recent shutdown cause. */
  EcuM_ShutdownCauseType MostRecentShutDownCause;

  /* Next recent shutdown cause */
  EcuM_ShutdownCauseType NextRecentShutDownCause;

  /* Most Recent sleep mode index */
  EcuM_ShutdownModeType MostRecentSlpModeId;

  /* Next Recent sleep mode index */
  EcuM_ShutdownModeType NextRecentSlpModeId;

  /* Most Recent reset mode index */
  EcuM_ShutdownModeType MostRecentRstModeId;

  /* Next Recent reset mode index */
  EcuM_ShutdownModeType NextRecentRstModeId;
} EcuM_LastShutdownType;

 /* Structure for EcuM Shutdown cause,target and boot target */
typedef struct
{
  /*  variable to store current shutdownCause */
  EcuM_ShutdownCauseType ShutdownCause;

  /*  Variable to indicate Boot Target */
  EcuM_BootTargetType BootTarget;

  /*  variable to store selected shutdown target of EcuM */
  EcuM_ShutdownTargetType SelectShutdownTarget;

  /*  variable to store current sleep mode of EcuM */
  EcuM_ShutdownModeType SleepMode;

  /*  variable to store current reset mode of EcuM */
  EcuM_ShutdownModeType ResetMode;

} EcuM_ShutdownCauseTargetType;

#if (STD_ON == ECUM_DEV_ERROR_DETECT)
typedef struct
{
  /*  variable to store last Instance ID */
  uint8 InstanceId;

  /*  variable to store last API ID */
  uint8 ApiId;

  /*  variable to store last Error ID */
  uint8 ErrorId;
} EcuM_DetErrorStatusType;
#endif

#define ECUM_START_SEC_CONST_8
#include "MemMap.h"

/* Array for EcuMResetMode to identify the reset mode in service like
EcuM_SelectShutdownTarget */
/* polyspace<MISRA-C:8.12:Not a defect:Justify with annotations> size of array is determined by configuration */
extern CONST(uint8, ECUM_CONST) EcuM_ResetModeId[ECUM_NO_OF_RESETMODES];

/* Array for EcuMShutdownCause to identifies the shutdown cause */
/* polyspace<MISRA-C:8.12:Not a defect:Justify with annotations> size of array is determined by configuration */
extern CONST(uint8, ECUM_CONST) EcuM_ShutdownCauseId[ECUM_NO_OF_SHUTDOWNCAUSE];

#if (ECUM_NO_OF_CLOCKUSERS > 0)
/* Reference to EcuMFlexUserConfig from EcuMSetClockAllowedUserRef */
/* polyspace<MISRA-C:8.12:Not a defect:Justify with annotations> size of array is determined by configuration */
extern CONST(uint8, ECUM_CONST) EcuM_SetClockAllowedUser[];

#endif

#define ECUM_STOP_SEC_CONST_8
#include "MemMap.h"

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if(ECUM_NO_OF_GODOWNUSERS > 0)
/* Reference to EcuMFlexUserConfig from EcuMGoDownAllowedUserRef */
extern CONST(uint8, ECUM_CONST) EcuM_GoDownAllowedUser[ECUM_NO_OF_GODOWNUSERS];

#endif

/* Array for Sleep Modes Structure to identifies the sleep mode */
extern CONST(EcuM_SleepModeConfigType, ECUM_CONST) EcuM_SleepModes[ECUM_NO_OF_SLEEPMODES];

/* Array for Wakeup Source Structure to define the identifier of this
wake up source */

extern CONST(EcuM_WakeupSourceConfigType, ECUM_CONST) EcuM_WakeupSource[ECUM_NO_OF_WAKEUPSOURCES];

/* Array for EcuM Users */

extern CONST(EcuM_FlexUserType, ECUM_CONST) EcuM_FlexUsers[ECUM_NO_OF_USERS];

#if (ECUM_NO_OF_ALARMS > 0)
/* Array for EcuM Users */
extern CONST(EcuM_AlarmClockType, ECUM_CONST) EcuM_AlarmClock[ECUM_NO_OF_ALARMS];
#endif /* End of if (ECUM_NO_OF_ALARMS > 0) */


/* Reference to EcuMOSResource from EcuMCommonConfiguration container */

extern CONST(ResourceType, ECUM_CONST) EcuM_OsResources[ECUM_NO_OF_OSRESOURCES];

/* Reference to EcuMComMPNCRef from EcuMWakeupSource container */
extern CONST(uint8, ECUM_CONST) EcuM_WakeupPncIndex[ECUM_NO_OF_WAKEUPSOURCES];

#if (ECUM_NO_OF_PNC_ID > 0)
extern CONST(uint8, ECUM_CONST) EcuM_WakeupPncIdList[ECUM_NO_OF_PNC_ID];
#endif /* End of if (ECUM_NO_OF_PNC_ID > 0)*/

#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
/* Array for Core ID
 * Master Core : EcuM_GaaCoreID[0]
 * Slave Cores : EcuM_GaaCoreID[1] ~ */
/* polyspace<MISRA-C:8.12:Not a defect:Justify with annotations> size of array is determined by configuration */
extern CONST(CoreIdType, ECUM_CONST) EcuM_CoreID[ECUM_NO_OF_CORES];

/* Reference to OsEvent container through OsTaskEventRef in OsTask container */
/* polyspace<MISRA-C:8.12:Not a defect:Justify with annotations> size of array is determined by configuration */
extern CONST(EventMaskType, ECUM_CONST) EcuM_EventMask[ECUM_NO_OF_EVENT_MASKS];

/* Reference to OsTask container through OsTaskRef in EcuMFlexConfiguration container */
/* polyspace<MISRA-C:8.12:Not a defect:Justify with annotations> size of array is determined by configuration */
extern CONST(TaskType, ECUM_CONST) EcuM_OsTask[ECUM_NO_OF_OS_TASKS];
#endif

#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"




/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* ECUM_PCTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

