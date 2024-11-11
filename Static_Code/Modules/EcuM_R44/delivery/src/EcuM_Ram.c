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
**  FILE-NAME : EcuM_Ram.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : ECU State Manager Global Variables declaration                **
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
** 1.1.4     17-Jan-2022   TriBD             R44_2021 #23299                  **
** 1.1.0     22-Mar-2021   TinhPV3           R44_2021 #17960                  **
** 1.0.1     05-Mar-2021   TinhPV3           R44_2021 #17961                  **
** 0.0.8     07-Dec-2020   TinhPV3           Multicores #17105, #17249        **
** 0.0.1     14-Feb-2020   ThangMA           R44-Redmine #655, #8668          **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM_Ram.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define ECUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Global variable to store Initialization status of EcuM */
VAR(boolean, ECUM_VAR_POWER_ON_INIT) EcuM_InitStatus;

/* Global variable to store the sleep cycle status */
VAR(boolean, ECUM_VAR_POWER_ON_INIT) EcuM_SleepCycle;

#if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
/* Global variable to store the alarm cycle status */
VAR(boolean, ECUM_VAR_POWER_ON_INIT) EcuM_AlarmCycle;

/* Global variable to store the alarm expiry status status of Alarm */
VAR(boolean, ECUM_VAR_POWER_ON_INIT) EcuM_AlarmExpired;
#endif

#define ECUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define ECUM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (STD_ON == ECUM_DEV_ERROR_DETECT)
/* Global structure to hold the last Det error status */
VAR(EcuM_DetErrorStatusType, ECUM_VAR_POWER_ON_INIT) EcuM_LastDetError;
#endif

/* Global variable to store the wakeup type */
VAR(EcuM_WakeupTypeConfigType, ECUM_VAR_POWER_ON_INIT) EcuM_WakeupType;

VAR(EcuM_WakeupSourceType, ECUM_VAR_POWER_ON_INIT)
  EcuM_PendingWakeupEvents;

/* Global variable to hold the validated Wakeup sources */
VAR(EcuM_WakeupSourceType, ECUM_VAR_POWER_ON_INIT)
  EcuM_ValidatedWakeupEvents;

/* Global variable to hold the Expired Wakeup sources */
VAR(EcuM_WakeupSourceType, ECUM_VAR_POWER_ON_INIT) EcuM_ExpiredWakeupEvents;

/* Global Variable to store wakeup status */
VAR(EcuM_WakeupStatusType, ECUM_VAR_POWER_ON_INIT)
  EcuM_WakeupStatus[ECUM_NO_OF_WAKEUPSOURCES];

#define ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define ECUM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
/* Global variable to store the shutdown status of EcuM */
VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_ShutdownMask;

/* Global variable to store the sleep status of EcuM in case of EcuM halt*/
VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_HaltMask;

/* Global variable to store the sleep status of EcuM in case of EcuM poll*/
VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_PollMask;
/* Global variable to count synchronized startup */
volatile VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_SyncAllcoresCount = (uint8)ECUM_ZERO;

#endif

/* Global pointer to hold EcuM Sleep Mode Index data */
VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_SleepModeIndex;

/* Run Request Status for EcuM Mode Request */
VAR(EcuM_RunStatusType, ECUM_VAR_POWER_ON_INIT) 
  EcuM_FlexUsers_RUN_RequestStatus[ECUM_NO_OF_USERS];
/* Post Run Request Status for EcuM Mode Request */
VAR(EcuM_RunStatusType, ECUM_VAR_POWER_ON_INIT) 
  EcuM_FlexUsers_POSTRUN_RequestStatus[ECUM_NO_OF_USERS];

VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_RunRequestStatus;
VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_PostRunRequestStatus;
VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_ModeHandlingChangeStatus;
/* Global variable to store shutdown/sleep request  */
VAR(uint8, ECUM_VAR_POWER_ON_INIT) EcuM_ShutdownOrSleepRequested;
#define ECUM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"


#define ECUM_START_SEC_VAR_POWER_ON_CLEARED_16
#include "MemMap.h"

#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
/* Global variable to count the number of cores based on SetEvent function */
VAR(uint16, ECUM_VAR_POWER_ON_INIT) EcuM_NoOfCore;
#endif /* End of if (ECUM_MULTI_CORE_SUPPORT == STD_ON) */

/* Global Array for Check Wakeup Source Structure */
VAR(uint16, ECUM_VAR_POWER_ON_INIT) 
  EcuM_CheckWakeupCounter[ECUM_NO_OF_WAKEUPSOURCES];

/* Global Array for Wakeup Source Structure */
VAR(uint16, ECUM_VAR_POWER_ON_INIT)
  EcuM_WakeupCounter[ECUM_NO_OF_WAKEUPSOURCES];

/* Global pointer to hold EcuM Sleep Mode Index data */
VAR(uint16, ECUM_VAR_POWER_ON_INIT) EcuM_SleepModeId;

#define ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_16
#include "MemMap.h"


#define ECUM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

#if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
/* Global array to store Alarm time of each Alarm */
VAR(uint32, ECUM_VAR_POWER_ON_INIT) EcuM_AlarmTime[ECUM_NO_OF_ALARMS];

/* Global variable to store the status of Running Timer */
VAR(uint32, ECUM_VAR_POWER_ON_INIT) EcuM_RunningTimer;

/* Global variable to count the number of times the EcuM mainfunction is called in RUN phase */
VAR(uint32, ECUM_VAR_POWER_ON_INIT) EcuM_RunCounterTime;

/* Global variable to count the number of times the EcuM Set wake up is called in wake up phase*/
VAR(uint32, ECUM_VAR_POWER_ON_INIT) EcuM_WakeupCounterTime;

/* Global variable to store the Master Clock Alarm time of EcuM */
VAR(uint32, ECUM_VAR_POWER_ON_INIT) EcuM_MasterAlarm;

/* Global variable to store the next GPT tick */
VAR(uint32, ECUM_VAR_POWER_ON_INIT) EcuM_NextTick;
#endif /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */

/* Global variable for PLL Lock Timeout */
VAR(uint32, ECUM_VAR_POWER_ON_INIT) EcuM_PllCnt;

#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
/* Global variable to store the Task Id that perform shutdown or sleep */
VAR(TaskType, ECUM_VAR_CLEARED) EcuM_WaitingTaskId;
#endif

#define ECUM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"



#define ECUM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global Variable to store EcuM state */
VAR(EcuM_StateType, ECUM_VAR_NOINIT) EcuM_State;

/* Global Variable to store Mcu reset reason */
VAR(Mcu_ResetType, ECUM_VAR_NOINIT) EcuM_ResetReason;

/* Global pointer to hold EcuM Configuration Data */
/* @Trace: SWS_EcuM_04038 SWS_EcuM_02801 SWS_EcuM_02794 SWS_EcuM_02795 */
P2CONST(EcuM_ConfigType, ECUM_VAR_NOINIT, ECUM_CONST) EcuM_ptrEcuMConfigPtr;
#define ECUM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define ECUM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include "MemMap.h"
/* Global Variable to hold the last shutdown target */
VAR(EcuM_LastShutdownType, ECUM_VAR_NOINIT) EcuM_LastShutdown;

/* Global structure to hold the shutdown cause,target and boot target */
VAR(EcuM_ShutdownCauseTargetType, ECUM_VAR_NOINIT) EcuM_ShutdownCauseTarget;
#define ECUM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include "MemMap.h"

#define ECUM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Service ID for PB */
VAR(uint8, ECUM_VAR_NO_INIT) EcuM_GulPbVariantIndex;
#define ECUM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

