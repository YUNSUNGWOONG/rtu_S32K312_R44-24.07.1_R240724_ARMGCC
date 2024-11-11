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
**  FILE-NAME : EcuM_Externals.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Header file of EcuM_Externals.c                               **
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
** 1.1.4     17-Jan-2022   TriBD             R44_2021 #22426                  **
** 1.0.1     05-Mar-2021   TinhPV3           R44_2021 #17961                  **
** 0.0.3     30-Jul-2020   ThiNT8            R44-Redmine #655, #14588         **
** 0.0.2     07-Apr-2020   LocLT5            R44-Redmine #655, #8670          **
** 0.0.1     14-Feb-2019   ThangMA            R44-Redmine #655                **
*******************************************************************************/

#ifndef ECUM_EXTERNALS_H
#define ECUM_EXTERNALS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM_Generated_Types.h"
#include "EcuM_Generated_Callouts.h"
#include "EcuM_Types.h"
#include "Mcu.h"
#include "ComStack_Types.h"
#include "Os.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/* Service ID for EcuM_ErrorHook */
#define ECUM_ERRORHOOK_SID    ((uint8)0x30u)

/* Service ID for EcuM_AL_SetProgrammableInterrupts */
#define ECUM_AL_SETPROGRAMMABLEINTERRUPTS_SID    ((uint8)0x4Au)

/* Service ID for EcuM_AL_DriverInitZero */
#define ECUM_AL_DRIVERINITZERO_SID    ((uint8)0x31u)

/* Service ID for EcuM_DeterminePbConfiguration */
#define ECUM_DETERMINEPBCONFIGURATION_SID    ((uint8)0x32u)

/* Service ID for EcuM_AL_DriverInitOne */
#define ECUM_AL_DRIVERINITONE_SID    ((uint8)0x33u)

/* Service ID for EcuM_LoopDetection */
#define ECUM_LOOPDETECTION_SID    ((uint8)0x4Bu)

/* Service ID for EcuM_OnGoOffOne */
#define ECUM_ONGOOFFONE_SID    ((uint8)0x3Cu)

/* Service ID for EcuM_OnGoOffTwo */
#define ECUM_ONGOOFFTWO_SID    ((uint8)0x3Du)

/* Service ID for EcuM_AL_SwitchOff */
#define ECUM_AL_SWITCHOFF_SID    ((uint8)0x3Eu)

/* Service ID for EcuM_AL_Reset */
#define ECUM_AL_RESET_SID    ((uint8)0x4Cu)

/* Service ID for EcuM_EnableWakeupSources */
#define ECUM_ENABLEWAKEUPSOURCES_SID    ((uint8)0x3Fu)

/* Service ID for EcuM_GenerateRamHash */
#define ECUM_GENERATERAMHASH_SID    ((uint8)0x40u)

/* Service ID for EcuM_SleepActivity */
#define ECUM_SLEEPACTIVITY_SID    ((uint8)0x41u)

/* Service ID for EcuM_StartCheckWakeup */
#define ECUM_STARTCHECKWAKEUP_SID    ((uint8)0x00u)

/* Service ID for EcuM_CheckWakeup */
#define ECUM_CHECKWAKEUP_SID    ((uint8)0x42u)

/* Service ID for EcuM_EndCheckWakeup */
#define ECUM_ENDCHECKWAKEUP_SID    ((uint8)0x00u)

/* Service ID for EcuM_CheckRamHash */
#define ECUM_CHECKRAMHASH_SID    ((uint8)0x43u)

/* Service ID for EcuM_DisableWakeupSources */
#define ECUM_DISABLEWAKEUPSOURCES_SID    ((uint8)0x44u)

/* Service ID for EcuM_AL_DriverRestart */
#define ECUM_AL_DRIVERRESTART_SID    ((uint8)0x45u)

/* Service ID for EcuM_StartWakeupSources */
#define ECUM_STARTWAKEUPSOURCES_SID    ((uint8)0x46u)

/* Service ID for EcuM_CheckValidation */
#define ECUM_CHECKVALIDATION_SID    ((uint8)0x47u)

/* Service ID for EcuM_StopWakeupSources */
#define ECUM_STOPWAKEUPSOURCES_SID    ((uint8)0x48u)

/* Service ID for Ram hash OK */
#define ECUM_RAMHASH_OK    ((uint8)0x01u)

/* Service ID for Ram hash NOT OK */
#define ECUM_RAMHASH_NOT_OK    ((uint8)0x00u)

/* Service ID for EcuM_AL_DriverInitCoreWise_PreOs */
#define ECUM_AL_DRIVERINITCOREWISE_PREOS_SID    ((uint8)0xFEu)

/* Service ID for EcuM_AL_DriverInitCoreWise_PostOs */
#define ECUM_AL_DRIVERINITCOREWISE_POSTOS_SID    ((uint8)0xFFu)

#ifndef ECUM_LP_CALLOUT_ENABLED
/* definition of call out LB */
#define ECUM_LP_CALLOUT_ENABLED                   STD_OFF
#endif

/* define macro for Rte postbuild support */
#ifndef RTE_VARIANT_POSTBUILD_SUPPORT
#define RTE_VARIANT_POSTBUILD_SUPPORT             STD_OFF
#endif
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define ECUM_START_SEC_CALLOUT_CODE
#include "MemMap.h"

/* Extern for EcuM_CheckWakeup Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_CheckWakeup
  (EcuM_WakeupSourceType wakeupSource);

/* Extern for EcuM_ErrorHook Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_ErrorHook(uint16 reason);

/* Extern for EcuM_AL_SetProgrammableInterrupts Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_SetProgrammableInterrupts(void);

/* Extern for EcuM_AL_DriverInitZero Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverInitZero(void);

/* polyspace-begin MISRA-C3:20.7 [Not a defect:Low] "Prototype is followign coding rules and autosar spec " */
/* Extern for EcuM_DeterminePbConfiguration Callout */  
extern FUNC(P2CONST(EcuM_ConfigType, ECUM_CONST, ECUM_CONST),ECUM_CALLOUT_CODE)
 EcuM_DeterminePbConfiguration(void);
/* polyspace-end MISRA-C3:20.7 [Not a defect:Low] "Prototype is followign coding rules and autosar spec " */

/* Extern for EcuM_AL_DriverInitOne Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverInitOne(void);

/* Extern for EcuM_LoopDetection Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_LoopDetection(void);

/* Extern for EcuM_OnGoOffOne Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_OnGoOffOne(void);

/* Extern for EcuM_OnGoOffTwo Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_OnGoOffTwo(void);

/* Extern for EcuM_AL_SwitchOff Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_SwitchOff(void);

/* Extern for EcuM_AL_Reset Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_Reset(EcuM_ResetType reset);

#ifndef RTE_RUNNABLE_EnableWakeupSources
/* Extern for EcuM_EnableWakeupSources Callout */
extern FUNC(void, ECUM_CODE) EcuM_EnableWakeupSources
  (EcuM_WakeupSourceType wakeupSource);
#endif

/* Extern for EcuM_GenerateRamHash Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_GenerateRamHash(void);

/* Extern for EcuM_SleepActivity Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_SleepActivity(void);

/* Extern for EcuM_StartCheckWakeup Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_StartCheckWakeup
  (EcuM_WakeupSourceType wakeupSource);

/* Extern for EcuM_EndCheckWakeup Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_EndCheckWakeup
  (EcuM_WakeupSourceType wakeupSource);

/* Extern for EcuM_CheckRamHash Callout */
extern FUNC(uint8, ECUM_CALLOUT_CODE) EcuM_CheckRamHash(void);

#ifndef RTE_RUNNABLE_DisableWakeupSources
/* Extern for EcuM_DisableWakeupSources Callout */
extern FUNC(void, ECUM_CODE) EcuM_DisableWakeupSources
  (EcuM_WakeupSourceType wakeupSource);

#endif

/* Extern for EcuM_AL_DriverRestart Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverRestart(void);

/* Extern for EcuM_StartWakeupSources Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_StartWakeupSources
  (EcuM_WakeupSourceType wakeupSource);

/* Extern for EcuM_CheckValidation Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_CheckValidation
                                    (EcuM_WakeupSourceType wakeupSource);

/* Extern for EcuM_StopWakeupSources Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_StopWakeupSources
  (EcuM_WakeupSourceType wakeupSource);

// Callout function prototype not in requirement
/* Extern for EcuM_SetMode Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_SetMode(Mcu_ModeType McuMode);

/* Extern for EcuM_PreInit */
extern FUNC(void, ECUM_CODE) EcuM_PreInit (void);

/* Extern for EcuM_PreSleep */
extern FUNC(void, ECUM_CODE) EcuM_PreSleep (void);

/* Extern for EcuM_PostSleep */
extern FUNC(void, ECUM_CODE) EcuM_PostSleep (Std_ReturnType GoHaltResult);

/* Extern for EcuM_RequestOff */
extern FUNC(Std_ReturnType, ECUM_CALLOUT_CODE) 
  EcuM_RequestOff (EcuM_UserType user);

/* Extern for EcuM_RequestReset */
extern FUNC(Std_ReturnType, ECUM_CALLOUT_CODE) 
  EcuM_RequestReset (EcuM_UserType user);

/* Extern for EcuM_RequestSleep */
extern FUNC(Std_ReturnType, ECUM_CALLOUT_CODE) 
  EcuM_RequestSleep (EcuM_UserType user);

/* Extern for EcuM_PreInit */
extern FUNC(void, ECUM_CODE) EcuM_PostInit (void);

/* Extern for EcuM_UserHook_SleepActivity */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_UserHook_SleepActivity(void);

/* Extern for EcuM_UserHook_SetProgrammableInterrupts */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_UserHook_SetProgrammableInterrupts(void);

/* Extern for EcuM_UserHook_StartWakeupSources */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_UserHook_StartWakeupSources(EcuM_WakeupSourceType wakeupSource);

/* Extern for EcuM_UserHook_StopWakeupSources */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_UserHook_StopWakeupSources(EcuM_WakeupSourceType wakeupSource);

/* Extern for EcuM_UserHook_CheckValidation */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_UserHook_CheckValidation(EcuM_WakeupSourceType wakeupSource);

/* Extern for EcuM_UserHook_GenerateRamHash */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_UserHook_GenerateRamHash(void);

/* Extern for EcuM_UserHook_ErrorHook */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_UserHook_ErrorHook(uint16 reasion);

/* Extern for EcuM_UserHook_LoopDetection */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_UserHook_LoopDetection(void);

/* Extern for EcuM_UserHook_CheckRamHash */
extern FUNC(Std_ReturnType, ECUM_CALLOUT_CODE) EcuM_UserHook_CheckRamHash(void);

/* Extern for EcuM_UserHook_DeterminePbConfiguration */
extern FUNC(Std_ReturnType, ECUM_CALLOUT_CODE) EcuM_UserHook_DeterminePbConfiguration( uint8* VariantIdx);

/* Extern for EcuM_AL_DriverInitCoreWise_PreOs Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverInitCoreWise_PreOs(CoreIdType CoreId);

/* Extern for EcuM_AL_DriverInitCoreWise_PostOs Callout */
extern FUNC(void, ECUM_CALLOUT_CODE) EcuM_AL_DriverInitCoreWise_PostOs(CoreIdType CoreId);

#define ECUM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"

/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
#endif /* ECUM_EXTERNALS_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

