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
**  FILE-NAME : EcuM.c                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : APIs implementation for EcuM module                           **
**              EcuM_GetVersionInfo                                           **
**              EcuM_Init                                                     **
**              EcuM_GoDownHaltPoll                                           **
**              EcuM_Shutdown                                                 **
**              EcuM_SelectShutdownTarget                                     **
**              EcuM_GetShutdownTarget                                        **
**              EcuM_GetLastShutdownTarget                                    **
**              EcuM_SelectShutdownCause                                      **
**              EcuM_GetShutdownCause                                         **
**              EcuM_GetPendingWakeupEvents                                   **
**              EcuM_ClearWakeupEvent                                         **
**              EcuM_GetValidatedWakeupEvents                                 **
**              EcuM_GetExpiredWakeupEvents                                   **
**              EcuM_SelectBootTarget                                         **
**              EcuM_GetBootTarget                                            **
**              EcuM_StartupTwo                                               **
**              EcuM_MainFunction                                             **
**              EcuM_SetRelWakeupAlarm                                        **
**              EcuM_SetAbsWakeupAlarm                                        **
**              EcuM_AbortWakeupAlarm                                         **
**              EcuM_GetCurrentTime                                           **
**              EcuM_GetWakeupTime                                            **
**              EcuM_SetClock                                                 **
**              EcuM_GetResetReason                                           **
**              EcuM_RequestRUN                                               **
**              EcuM_ReleaseRUN                                               **
**              EcuM_RequestPOST_RUN                                          **
**              EcuM_ReleasePOST_RUN                                          **
**              EcuM_SetState                                                 **
**              EcuM_SetWakeupEvent                                           **
**              EcuM_ValidateWakeupEvent                                      **
**              EcuM_SetRunState                                              **
**              EcuM_IsMasterCore                                             **
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
** 1.2.0     04-Oct-2022   TriBD             R44_2021 #27878, #31620          **
** 1.1.6     10-Aug-2022   Manje Woo         CP44-727                         **
** 1.1.5     15-Mar-2021   TriBD             R44_2021 #24753                  **
** 1.1.1     21-Jun-2021   TriBD             R44_2021 #18655                  **
** 1.1.0     22-Mar-2021   TinhPV3           R44_2021 #17960                  **
** 1.0.1     05-Mar-2021   TinhPV3           R44_2021 #17961                  **
** 0.0.9     12-Dec-2020   TronDV            Fix polyspace and #17404         **
** 0.0.8     07-Dec-2020   TinhPV3           Multicores #17105, #17249        **
** 0.0.7     11-Nov-2020   TroNDV, HiepDK    Update traceability              **
** 0.0.6     30-Jul-2020   ThiNT8            R44-Redmine #655, #14588         **
** 0.0.5     15-Jul-2020   ThiNT8            R44-Redmine #655, #14603         **
** 0.0.4     29-May-2020   ThangMA            R44-Redmine #655, #13319        **
** 0.0.3     22-Apr-2020   LocLT5            R44-Redmine #655, #11893         **
** 0.0.2     07-Apr-2020   LocLT5            R44-Redmine #655, #8670          **
** 0.0.1     14-Feb-2020   ThangMA            R44-Redmine #655, #8668         **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "EcuM_Ram.h"
#include "EcuM_Internal.h"
#include "Rte_EcuM.h"
#include "SchM_EcuM.h"
#include "BswM.h"
#include "BswM_EcuM.h"
#include "Rte_Main.h"
#include "ComM_EcuM.h"
#include "Os.h"
#if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
#include "Os_PortTypes.h"
#endif
#if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
#include "Gpt.h"
#include "EcuM_Os.h"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define ECUM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : EcuM_GetVersionInfo                                 **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : This Service returns the version information of ECU **
**                        State Manager Module.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00407 SRS_BSW_00411 */
#if (STD_ON == ECUM_VERSION_INFO_API)
FUNC(void, ECUM_CODE) EcuM_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, ECUM_APPL_DATA) versioninfo)
{
  /* Check NULL pointer */
  /* @Trace: EcuM_SUD_API_990 */
  if (versioninfo == NULL_PTR)
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETVERSIONINFO_SID, ECUM_E_PARAM_POINTER);
    #endif
  }
  else
  {
    /* @Trace: EcuM_SUD_API_001 */
    /* Load the vendor Id */
    /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "VersionInfo will be checked before using" */
    /* polyspace-begin RTE:IDP [Not a defect:Low] "Pointer is checked manual and not NULL" */
    versioninfo->vendorID = ECUM_VENDOR_ID;

    /* Load the module Id */
    versioninfo->moduleID = ECUM_MODULE_ID;

    /* Load Software Major Version */
    versioninfo->sw_major_version = ECUM_SW_MAJOR_VERSION;

    /* Load Software Minor Version */
    versioninfo->sw_minor_version = ECUM_SW_MINOR_VERSION;

    /* Load Software Patch Version */
    versioninfo->sw_patch_version = ECUM_SW_PATCH_VERSION;
    /* polyspace-end RTE:IDP [Not a defect:Low] "Pointer is checked manual and not NULL" */
    /* polyspace-end MISRA-C3:D4.14 */
  }
} /* End of EcuM_GetVersionInfo */
#endif /* (STD_ON == ECUM_VERSION_INFO_API) */

/*******************************************************************************
** Function Name        : EcuM_Init                                           **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : Initializes the ECU state manager and carries out   **
**                        the startup procedure. The function will never      **
**                        return (it calls StartOS)                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_ptrEcuMConfigPtr,             **
**                        EcuM_LcfgHashValue, EcuM_AlarmTime                  **
**                        EcuM_AlarmClock, EcuM_CoreID                        **
**                        Function(s) invoked    :                            **
**                        GetCoreID, EcuM_AL_SetProgrammableInterrupts,       **
**                        EcuM_AL_DriverInitZero, EcuM_PostInit,              **
**                        EcuM_DeterminePbConfiguration, EcuM_ErrorHook,      **
**                        EcuM_AL_DriverInitOne, StartOS, StartCore,          **
**                        EcuM_LoopDetection, EcuM_SelectShutdownTarget,      **
**                        Mcu_GetResetReason, EcuM_CheckResetReason,		  **
**                        EcuM_AL_DriverInitCoreWise			              **
**                                                               			  **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09114 SRS_BSW_00416 SRS_ModeMgm_09173 SRS_ModeMgm_09126
 * SRS_ModeMgm_09234 SRS_BSW_00101 SRS_BSW_00358 SRS_ModeMgm_09128
 * SRS_ModeMgm_09235 SRS_ModeMgm_09270 SRS_ModeMgm_09119 SRS_ModeMgm_09102
 * SRS_ModeMgm_09276 SRS_EcuM_AR_00005 SRS_ModeMgm_09236 SRS_EcuM_AR_00007
 * SRS_BSW_00337 SRS_BSW_00327 SRS_EcuM_AR_00008 SRS_EcuM_AR_00009 SRS_BSW_00414
 * SRS_EcuM_AR_00010 SRS_EcuM_AR_00011 SRS_ModeMgm_09274 SRS_ModeMgm_09275
 * SRS_ModeMgm_09113 SRS_ModeMgm_09101 SRS_EcuM_AR_00002 */
FUNC(void, ECUM_CODE) EcuM_Init(void)
{
  /* Local pointer for the Hash array EcuM_LcfgHashValue[] */
  P2CONST(uint32, ECUM_CONST, ECUM_CONST) ptrLcfgHashValue;
  uint32 i;
  uint8 sleepModeIndex;
  boolean result;
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  CoreIdType coreId;
  StatusType status;
  /* FOR loop index variable */
  uint8 coreIdx;

  /* Set init value for status */
  status = E_NOT_OK;
  #endif

  #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
  uint8 alarmIndx;
  #endif

  /* Variable for Hash array index */
  uint8 hashIndex;

  /* Set the variable EcuM_InitStatus to indicate EcuM is initialized */
  EcuM_InitStatus = ECUM_INITIALIZED;

  /* FOR loop index variable */
  uint8 flexUsersIdx;

  /* @Trace: EcuM_SUD_API_002 */
  /* Initialized global variable for Mode Handling */
  EcuM_RunRequestStatus = (uint8)ECUM_RUNSTATUS_UNKNOWN;
  EcuM_PostRunRequestStatus = (uint8)ECUM_RUNSTATUS_UNKNOWN;
  EcuM_ModeHandlingChangeStatus = (uint8)ECUM_FALSE;
  EcuM_ShutdownOrSleepRequested = ECUM_REQUEST_INVALID;

  for (flexUsersIdx = (uint8)ECUM_ZERO; flexUsersIdx < ECUM_NO_OF_USERS;
                                                                flexUsersIdx++)
  {
    EcuM_FlexUsers_RUN_RequestStatus[flexUsersIdx] = ECUM_RUNSTATUS_UNKNOWN;
    EcuM_FlexUsers_POSTRUN_RequestStatus[flexUsersIdx] = ECUM_RUNSTATUS_UNKNOWN;
  }

  /* @Trace: EcuM_SUD_API_003 */
  #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
  /* Get the core id of currently running core */
  coreId = GetCoreID();
  if (coreId == EcuM_CoreID[ECUM_ZERO])
  #endif
  {
    #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
    for (alarmIndx = (uint8)ECUM_ZERO; alarmIndx < ECUM_NO_OF_ALARMS;
         alarmIndx++)
    {
      /* Initialize the run time AlarmTime array with configured value */
      EcuM_AlarmTime[alarmIndx] =
      EcuM_AlarmClock[alarmIndx].AlarmClockTimeOut;
    }
    /* Initialize EcuM clock value and the counter to increate EcuM clock */
    EcuM_RunningTimer = (uint32)ECUM_ZERO;
    EcuM_RunCounterTime = (uint32)ECUM_ZERO;
    EcuM_WakeupCounterTime = (uint32)ECUM_ZERO;
    #endif

    #if (ECUM_SET_PROGRAMMABLE_INTERRUPTS == STD_ON)
    /*  EcuM_AL_SetProgrammableInterrupts shall set the interrupts on
     *  ECUs with programmable interrupts. */
    EcuM_AL_SetProgrammableInterrupts();
    #endif

    /*
     * Driver initialization and hardware related startup activity for
     * loading postbuild configuration data
     */
    /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "This api is used for initialize modules in list zero, if user doesn't configure for this section, this api will be left empty" */
    EcuM_AL_DriverInitZero();

    /* Get the configuration pointer into the global variable */
    EcuM_ptrEcuMConfigPtr = EcuM_DeterminePbConfiguration();

    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Medium] "Defensive programming" */
    /* polyspace-begin MISRA-C3:2.1 [Justified:Medium] "Defensive programming" */
    /* polyspace-begin MISRA-C3:14.3 [Justified:Medium] "Defensive programming" */
    if (EcuM_ptrEcuMConfigPtr == NULL_PTR)
    {
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      (void)EcuM_DetReportError(ECUM_INIT_SID, ECUM_E_PARAM_POINTER);
      #endif
    }
    /* polyspace-end DEFECT:DEAD_CODE */
    /* polyspace-end MISRA-C3:2.1 */
    /* polyspace-end MISRA-C3:14.3 */
    else
    {
      /* Get the index of Hash array from PB configuration structure */
      /*  Fix for Run time error orange -150910 BSH  */
      hashIndex = (uint8)ECUM_ZERO;
      /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "EcuM_ptrEcuMConfigPtr will be checked before using" */
      /* polyspace-begin RTE:IDP [Not a defect:Low] "EcuM_ptrEcuMConfigPtr will be checked before using" */
      /* polyspace-begin RTE:NIP [Not a defect:Low] "EcuM_ptrEcuMConfigPtr will be checked before using" */
      if( EcuM_ptrEcuMConfigPtr->ptrEcuMConfigConsistencyHash != NULL_PTR )
      {
        /* Update the pointer with Hash array */
        ptrLcfgHashValue = &EcuM_LcfgHashValue[hashIndex];
  
        i = (uint32)ECUM_ZERO;
        /* Check Consistency of Configuration Data */
        while (i < (uint32)ECUM_NO_OF_HASH_SEGMENTS)
        {
          /* polyspace +2 RTE:NIV [Not a defect:Low] "Initial value of index is zero as above" */
          if (ptrLcfgHashValue[i] !=
              EcuM_ptrEcuMConfigPtr->ptrEcuMConfigConsistencyHash[i])
          {
            EcuM_ErrorHook((uint16)ECUM_E_CONFIGURATION_DATA_INCONSISTENT);
  
            /* To come out of FOR loop */
            i = (uint32)ECUM_NO_OF_HASH_SEGMENTS;
          }
            i++;
        }

        /* Driver initialization and hardware related startup activity for
         *   loading postbuild configuration data */
        EcuM_AL_DriverInitOne();

        /* Init Callout For After Mcal Init */
        /* polyspace +1 MISRA-C3:2.2 [Justified:Medium] "Scope to be implemented by user" */
        EcuM_PostInit();

        /* Driver initialization and other hardware-related startup activities
         *   in case of a power on reset */
        /* Update Reset reason */
        EcuM_ResetReason = Mcu_GetResetReason();
        EcuM_CheckResetReason(EcuM_ResetReason);

        EcuM_SleepModeId = ECUM_INVALID_SLEEPMODEID;
        /* polyspace-begin RTE:NIV [Not a defect:Low] "EcuM_ptrEcuMConfigPtr is updated via API EcuM_DeterminePbConfiguration" */
        if (ECUM_SHUTDOWN_TARGET_SLEEP ==
          EcuM_ptrEcuMConfigPtr->EcuMDefaultState)
        {
          /* Select Default shutdown target and index to Sleep mode */
          (void)EcuM_SelectShutdownTarget(
            EcuM_ptrEcuMConfigPtr->EcuMDefaultState,
            EcuM_ptrEcuMConfigPtr->EcuMDefaultSleepMode);

          result = EcuM_SearchMode(&sleepModeIndex,
            EcuM_ptrEcuMConfigPtr->EcuMDefaultSleepMode);
          if (TRUE == result)
          {
            EcuM_SleepModeId = (uint16)sleepModeIndex;
          }
        }
        else if (ECUM_SHUTDOWN_TARGET_RESET ==
         EcuM_ptrEcuMConfigPtr->EcuMDefaultState)
        {
          /* Select Default shutdown target and Index to Reset mode */
          (void)EcuM_SelectShutdownTarget(
            EcuM_ptrEcuMConfigPtr->EcuMDefaultState,
            EcuM_ptrEcuMConfigPtr->EcuMDefaultResetMode);
        }
        else
        {
          /* Select Default shutdown target and Index to zero */
          (void)EcuM_SelectShutdownTarget(
            EcuM_ptrEcuMConfigPtr->EcuMDefaultState,(uint8)ECUM_ZERO);
        }
        /* polyspace-end RTE:NIV [Not a defect:Low] "EcuM_ptrEcuMConfigPtr is updated via API EcuM_DeterminePbConfiguration" */
        #if (STD_ON == ECUM_RESET_LOOP_DETECTION)
        EcuM_LoopDetection();
        #endif
      }  /* polyspace-end MISRA-C3:D4.14 */
      /* End of if( EcuM_ptrEcuMConfigPtr->ptrEcuMConfigConsistencyHash !=
        NULL_PTR ) */
      /* polyspace-end RTE:NIP [Not a defect:Low] "EcuM_ptrEcuMConfigPtr will be checked before using" */
      /* polyspace-end RTE:IDP [Not a defect:Low] "EcuM_ptrEcuMConfigPtr will be checked before using and not outside" */
    } /* End of if (EcuM_ptrEcuMConfigPtr is NULL_PTR) */
  }
  /* @Trace: EcuM_SUD_API_004 */
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  else
  {
    /* Get the configuration pointer into the global variable */
    EcuM_ptrEcuMConfigPtr = EcuM_DeterminePbConfiguration();
  }
  #endif

  /* @Trace: EcuM_SUD_API_005 */
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  if (coreId == OS_CORE_ID_MASTER)
  {
    /* StartCore exclude master core */
    for (coreIdx = (uint8)ECUM_ZERO; coreIdx < ECUM_NO_OF_CORES;
        coreIdx++)
    {
      if (EcuM_CoreID[coreIdx] != OS_CORE_ID_MASTER)
      {
        StartCore(EcuM_CoreID[coreIdx], &status);
        if(status != E_OK)
        {
          #if (STD_ON == ECUM_DEV_ERROR_DETECT)
          (void)EcuM_DetReportError(ECUM_INIT_SID, ECUM_E_START_CORE_FAILED);
          #endif
        }
      }
    }
  } /* end of if (coreId is OS_CORE_ID_MASTER) */

  EcuM_AL_DriverInitCoreWise_PreOs(coreId);
  #endif /* End of if (STD_ON == ECUM_MULTI_CORE_SUPPORT) */

  /* @Trace: EcuM_SUD_API_006 */
  /* Start the OS with default application mode */
  /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "Condition is changed by user configuration" */
  if(EcuM_ptrEcuMConfigPtr != NULL_PTR)
  {
    /* request start OS */
    /* polyspace +2 RTE:NIV [Not a defect:Low] "The pointer has checked for not NULL." */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "The pointer has checked for not NULL." */
    StartOS(EcuM_ptrEcuMConfigPtr->EcuMDefaultAppMode); /* polyspace MISRA-C3:D4.14 [Justified:Low] "The pointer has checked for not NULL." */
  }
  else
  {
    /* do nothing. Already had EcuM_DetReportError(ECUM_INIT_SID,
      ECUM_E_PARAM_POINTER) */
  }
}/* End of EcuM_Init */

/*******************************************************************************
** Function Name        : EcuM_GoDownHaltPoll                                 **
**                                                                            **
** Service ID           : 0x2c                                                **
**                                                                            **
** Description          : Instructs the ECU State Manager module to go into a **
**                          sleep mode, Reset or OFF depending on the         **
**                          previously selected shutdown target.              **
**                                                                            **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : caller                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : (E_OK or E_NOT_OK)                                  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus                                     **
**                        Function(s) invoked    :                            **
**                        EcuM_IsMasterCore, EcuM_DetReportError,             **
**                        EcuM_PreSleep,                                      **
**                        EcuM_GoSleepSeq, EcuM_ClearWakeupEvent,             **
**                        EcuM_GoHaltSequence, EcuM_GoPollSequence,           **
**                        EcuM_PostSleep, EcuM_GoDownSequence                 **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09097 SRS_ModeMgm_09100 SRS_ModeMgm_09100
 * SRS_ModeMgm_09173 SRS_ModeMgm_09120 SRS_ModeMgm_09104 SRS_EcuM_AR_00002
 * SRS_ModeMgm_09127 SRS_ModeMgm_09147 SRS_EcuM_AR_00003 SRS_ModeMgm_09118
 * SRS_ModeMgm_09234 SRS_ModeMgm_09145 SRS_ModeMgm_09128 SRS_ModeMgm_09114
 * SRS_BSW_00337 SRS_BSW_00327 SRS_EcuM_AR_00008 SRS_ModeMgm_09235
 * SRS_ModeMgm_09239 SRS_ModeMgm_09270 SRS_ModeMgm_09164 SRS_EcuM_AR_00004
 * SRS_EcuM_AR_00005 SRS_BSW_00350 SRS_BSW_00385 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoDownHaltPoll(uint16 caller)
{
  boolean callerFlag;
  /* Variable to store the array index where the user is present */
  uint8 goDownUserInd;
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  /* index value of sleep mode */
  uint8 sleepModeIndex;
  /* status of sleep mode */
  boolean sleepModeValid;
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  /* flag of master core */
  boolean isMasterCore;
  #endif

  /* set init value of sleep mode */
  sleepModeIndex = (uint8) ECUM_ZERO;
  /* Initialize stdRetVal with E_OK */
  stdRetVal = (Std_ReturnType)E_OK;

  /* @Trace: EcuM_SUD_API_011 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    /* Report to DET */
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    (void)EcuM_DetReportError(ECUM_GODOWNHALTPOLL_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
    /* Local variable for master core result */
    isMasterCore = EcuM_IsMasterCore();
    if (TRUE == isMasterCore)
    #endif
    {
      /* @Trace: EcuM_SUD_API_007 */
      /* Go Halt or Poll */
      if (ECUM_SHUTDOWN_TARGET_SLEEP ==
        EcuM_ShutdownCauseTarget.SelectShutdownTarget)
      {
        /* Pre-sleep */
        EcuM_PreSleep();

        /* Enable data protection */
        SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION();

        /* Update Next recent shutdown Target state */
        EcuM_LastShutdown.NextRecentTarget =
        EcuM_LastShutdown.MostRecentTarget;

        /* Update Last/Most Recent shutdown Target state */
        EcuM_LastShutdown.MostRecentTarget =
        EcuM_ShutdownCauseTarget.SelectShutdownTarget;
        EcuM_LastShutdown.NextRecentShutDownCause =
        EcuM_LastShutdown.MostRecentShutDownCause;
        EcuM_LastShutdown.MostRecentShutDownCause =
        EcuM_ShutdownCauseTarget.ShutdownCause;

        /* Update Next recent sleep mode id */
        EcuM_LastShutdown.NextRecentSlpModeId =
        EcuM_LastShutdown.MostRecentSlpModeId;
        EcuM_LastShutdown.MostRecentSlpModeId =
        EcuM_ShutdownCauseTarget.SleepMode;

        /* Disable data protection */
        SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION();

        /* Go Sleep Sequence */
        sleepModeValid = EcuM_GoSleepSeq(&sleepModeIndex);

        if(TRUE == sleepModeValid) /* sleepModeIndex is valid */
        {
          /* Restore Sleep Mode Index */
          EcuM_SleepModeId = (uint16) sleepModeIndex;
          /* While in transition to sleep, if there is a wakeup source, start
           * wakeup reaction sequence and do not enter halt or poll sequence */
          if ((EcuM_ValidatedWakeupEvents != ECUM_NO_EVENTS) ||
          (EcuM_PendingWakeupEvents != ECUM_NO_EVENTS))
          {
            /* @Trace: EcuM_SUD_API_192 */
            EcuM_WakeupRestartSeq();
            /* polyspace-begin RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
            /* polyspace +1 MISRA-C3:14.3 MISRA-C3:2.1 DEFECT:DEAD_CODE [Justified:Medium] "Condition is changed by user configuration" */
            if(EcuM_SleepModes[sleepModeIndex].SleepModeSuspnd == ECUM_TRUE)
            {
              EcuM_ClearWakeupEvent(ECUM_WKSOURCE_ALL_SOURCES);
            }
            else
            {
              /* Do nothing */
            }
            /* polyspace-end RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
          }
          else
          {
            /* polyspace-begin DEFECT:DEAD_CODE [Justified:Medium] "Reachable code by configuration change" */
            /* polyspace-begin MISRA-C3:2.1 [Justified:Medium] "Reachable code by configuration change" */
            /* polyspace-begin MISRA-C3:14.3 [Justified:Medium] "Reachable code by configuration change" */
            /* polyspace-begin RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
            /* @Trace: EcuM_SUD_API_009 */
            /* Go Halt sequence*/
            if (TRUE == EcuM_SleepModes[sleepModeIndex].SleepModeSuspnd)
            {
              stdRetVal = EcuM_GoHaltSequence(sleepModeIndex);
            }
            /* @Trace: EcuM_SUD_API_010 */
            /* Go Poll sequence */
            else
            {
              stdRetVal = EcuM_GoPollSequence(sleepModeIndex);
            }/* End of if (EcuM_SleepModes[sleepModeIndex].SleepModeSuspnd */
            /* polyspace-end DEFECT:DEAD_CODE */
            /* polyspace-end MISRA-C3:2.1 */
            /* polyspace-end MISRA-C3:14.3 */
            /* polyspace-begin RTE:UNR */
          } /* End of if ((EcuM_ValidatedWakeupEvents != ECUM_NO_EVENTS) ||
          *(EcuM_PendingWakeupEvents != ECUM_NO_EVENTS)) */
        }/* End of if(sleepModeValid is TRUE)  */
        else
        {
          /* @Trace: EcuM_SUD_API_219 */
          EcuM_SleepModeId = ECUM_INVALID_SLEEPMODEID;

          #if (STD_ON == ECUM_DEV_ERROR_DETECT)
          /* Report to DET */
          (void)EcuM_DetReportError(ECUM_GODOWNHALTPOLL_SID,
           ECUM_E_UNKNOWN_SLEEP_MODE);
          #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
          stdRetVal = (Std_ReturnType)E_NOT_OK;
        }
        /* polyspace +1 MISRA-C3:14.3 [Justified:Medium] "Condition is changed by user configuration" */
        /* Post sleep sequence */
        EcuM_PostSleep(stdRetVal);
      }
      /* @Trace: EcuM_SUD_API_008 */
      /*Go Down*/
      else if ((ECUM_SHUTDOWN_TARGET_OFF
        == EcuM_ShutdownCauseTarget.SelectShutdownTarget) ||
       (ECUM_SHUTDOWN_TARGET_RESET
        == EcuM_ShutdownCauseTarget.SelectShutdownTarget))
      {
        callerFlag = EcuM_SearchGoDownUser(&goDownUserInd, (EcuM_UserType)caller);
        ECUM_UNUSED(goDownUserInd);
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Medium] "Reachable code by configuration change" */
        /* polyspace-begin MISRA-C3:2.1 [Justified:Medium] "Reachable code by configuration change" */
        /* polyspace-begin MISRA-C3:14.3 [Justified:Medium] "Reachable code by configuration change" */
        /* polyspace-begin RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
        if (TRUE == callerFlag)
        {
          stdRetVal = EcuM_GoDownSequence();
        }/* End of check callerFlag*/
        else
        {
          /* Do nothing*/
        }
        /* polyspace-end DEFECT:DEAD_CODE */
        /* polyspace-end MISRA-C3:2.1 */
        /* polyspace-end MISRA-C3:14.3 */
        /* polyspace-end RTE:UNR */
      }/* End of if ((EcuM_ShutdownCauseTarget.SelectShutdownTarget
      * is ECUM_SHUTDOWN_TARGET_OFF) ||
      *(EcuM_ShutdownCauseTarget.SelectShutdownTarget
      * is ECUM_SHUTDOWN_TARGET_RESET)) */
      else
      {
        /* @Trace: EcuM_SUD_API_214 */
        #if (STD_ON == ECUM_DEV_ERROR_DETECT)
        /* Report to DET */
        (void)EcuM_DetReportError(ECUM_GODOWNHALTPOLL_SID,
          ECUM_E_INVALID_SHUTDOWNTARGET);
        #endif /* End of if (STD_ON == ECUM_DEV_ERROR_DETECT) */
        stdRetVal = (Std_ReturnType)E_NOT_OK;
      }
    }/* End of if (coreId is EcuM_CoreID[ECUM_ZERO])*/
  }/* End of if (ECUM_UNINITIALIZED is equal EcuM_InitStatus) */

 return stdRetVal;
}/* End of EcuM_GoDownHaltPoll */

/*******************************************************************************
** Function Name        : EcuM_Shutdown                                       **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : Typically called from the shutdown hook,            **
**                        this function takes over execution control and will **
**                        carry out GO OFF II activities.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_ShutdownCauseTarget           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, EcuM_OnGoOffTwo,               **
**                        EcuM_AL_SwitchOff, EcuM_AL_Reset,                   **
**                        EcuM_IsMasterCore                                   **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09114 SRS_ModeMgm_09127 SRS_ModeMgm_09147
 * SRS_ModeMgm_09128 SRS_ModeMgm_09235
 * SRS_ModeMgm_09239 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385
 */
FUNC(void, ECUM_CODE) EcuM_Shutdown(void)
{
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  boolean isMasterCore;
  /* Local variable for master core result */
  isMasterCore = EcuM_IsMasterCore();
  #endif
  
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    /* @Trace: EcuM_SUD_API_980 */
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SHUTDOWN_SID, ECUM_E_UNINIT);
    #endif
  }
  /* Module is initialized */
  else
  {
    /* @Trace: EcuM_SUD_API_012*/
    /* Indicate entry of shutdown state */
    EcuM_OnGoOffTwo();

    #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
    if (TRUE == isMasterCore)
    #endif
    {
      /* @Trace: EcuM_SUD_API_013*/
      /* Is the shutdown target RESET */
      if (ECUM_SHUTDOWN_TARGET_RESET ==
        EcuM_ShutdownCauseTarget.SelectShutdownTarget)
      {
        /* The shutdown target RESET is implemented by EcuM_AL_Reset callout */
        EcuM_AL_Reset((EcuM_ResetType) EcuM_ShutdownCauseTarget.ResetMode);
      }
      /* @Trace: EcuM_SUD_API_014*/
      /* Shutdown target OFF*/
      else if (ECUM_SHUTDOWN_TARGET_OFF ==
        EcuM_ShutdownCauseTarget.SelectShutdownTarget)
      {
       /* The shutdown target OFF is implemented by EcuM_AL_Switchoff callout*/
        EcuM_AL_SwitchOff();
      }
      else
      {
        /* @Trace: EcuM_SUD_API_213*/
        #if (STD_ON == ECUM_DEV_ERROR_DETECT)
        /* Report to DET */
        (void)EcuM_DetReportError(ECUM_SHUTDOWN_SID,
        ECUM_E_INVALID_SHUTDOWNTARGET);
        #endif

        /* Force Sw Reset */
        EcuM_AL_Reset((uint8) ECUM_INVALID_SHUTDOWN);
      }
    }
  }
} /* End of EcuM_Shutdown */

/*******************************************************************************
** Function Name        : EcuM_SelectShutdownTarget                           **
**                                                                            **
** Service ID           : 0x06                                                **
**                                                                            **
** Description          : EcuM_SelectShutdownTarget selects the shutdown      **
**                        target. EcuM_SelectShutdownTarget is part of the    **
**                        ECU Manager Module port interface.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : shutdownTarget, shutdownMode                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_ShutdownCauseTarget           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, EcuM_SearchMode                **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09114 SRS_ModeMgm_09235 SRS_ModeMgm_09128
 * SRS_ModeMgm_09270 SRS_ModeMgm_09119 SRS_ModeMgm_09102
 * SRS_ModeMgm_09100 SRS_ModeMgm_09274 SRS_ModeMgm_09275 SRS_BSW_00327
 * SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectShutdownTarget
  (EcuM_ShutdownTargetType shutdownTarget, EcuM_ShutdownModeType shutdownMode)
{
  /* Status flag to check if the search was successful */
  boolean status;
  /* Index value of EcuM mode*/
  uint8 modeIndex;

  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  /* Set the Return Value to E_OK */
  stdRetVal = (Std_ReturnType)E_OK;
  /* @Trace: EcuM_SUD_API_967 */
  /* Is module not initialized */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "Reachable code depend on the calling of EcuM_Init function" */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    /* polyspace-end RTE:UNR [Not a defect:Low] "Reachable code depend on the calling of EcuM_Init function" */
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SELECTSHUTDOWNTARGET_SID, ECUM_E_UNINIT);
    #endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
    /* Update Return Value */
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  /* Module is initialized */
  else
  {
    /* @Trace: EcuM_SUD_API_966 */
    /* Is the shutdownTarget other than SLEEP/RESET/OFF */
    if ((shutdownTarget != ECUM_SHUTDOWN_TARGET_SLEEP) &&
        (shutdownTarget != ECUM_SHUTDOWN_TARGET_RESET) &&
        (shutdownTarget != ECUM_SHUTDOWN_TARGET_OFF))
    {
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_SELECTSHUTDOWNTARGET_SID,
                 ECUM_E_STATE_PAR_OUT_OF_RANGE);
      #endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
      /* Update Return Value */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      /* @Trace: EcuM_SUD_API_015 */
      /* Enable data protection */
      SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION();
      /* @Trace: EcuM_SUD_API_018 */
      /* Update EcuM_ShutdownCauseTarget.SelectShutdownTarget
       * with shutdownTarget */
      EcuM_ShutdownCauseTarget.SelectShutdownTarget = shutdownTarget;

      /* Disable data protection */
      SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION();

      /* Update status for shutdownMode */
      status = EcuM_SearchMode(&modeIndex, shutdownMode);

      /* @Trace: EcuM_SUD_API_016 */
      if (shutdownTarget == ECUM_SHUTDOWN_TARGET_SLEEP)
      {
        /* Is 'shutdownMode' invalid */
        if ( FALSE == status)
        {
          #if (STD_ON == ECUM_DEV_ERROR_DETECT)
          /* Report to DET */
          (void)EcuM_DetReportError(ECUM_SELECTSHUTDOWNTARGET_SID,
                     ECUM_E_INVALID_PAR);
          /* Set stdRetVal to E_NOT_OK */
          #endif
          stdRetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
          /* @Trace: EcuM_SUD_API_019 */
          /* Enable data protection */
          SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION();

          /* Update the SLEEP / RESET shutdownMode */
          EcuM_ShutdownCauseTarget.SleepMode = shutdownMode;

          /* Disable data protection */
          SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION();
        } /* End of if (stdRetVal != (Std_ReturnType)E_NOT_OK) */
      } /* End of if (shutdownTarget is ECUM_SHUTDOWN_TARGET_SLEEP) */
      /* @Trace: EcuM_SUD_API_964 */
      else if (shutdownTarget == ECUM_SHUTDOWN_TARGET_RESET)
      {
        /* Is 'shutdownMode' invalid */
        if ( FALSE == status)
        {
          /* Report to DET */
          #if (STD_ON == ECUM_DEV_ERROR_DETECT)
          (void)EcuM_DetReportError(ECUM_SELECTSHUTDOWNTARGET_SID,
                     ECUM_E_INVALID_PAR);
          /* Set stdRetVal to E_NOT_OK */
          #endif
          stdRetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
          /* @Trace: EcuM_SUD_API_017 */
          /* Enable data protection */
          SchM_Enter_EcuM_SHUTDOWN_TARGET_PROTECTION();

          /* Update the SLEEP / RESET shutdownMode */
          EcuM_ShutdownCauseTarget.ResetMode = shutdownMode;

          /* Disable data protection */
          SchM_Exit_EcuM_SHUTDOWN_TARGET_PROTECTION();
        } /* End of if (stdRetVal != (Std_ReturnType)E_NOT_OK) */
      } /* End of else if (shutdownTarget is ECUM_SHUTDOWN_TARGET_RESET) */
      else
      {
        /* To avoid MISRA warning */
      }
    }
  }
  /* Return E_OK or E_NOT_OK */
  return stdRetVal;
} /* End of EcuM_SelectShutdownTarget */

/*******************************************************************************
** Function Name        : EcuM_GetShutdownTarget                              **
**                                                                            **
** Service ID           : 0x09                                                **
**                                                                            **
** Description          : This function returns always the selected shutdown  **
**                      : target as set by EcuM_SelectShutdownTarget          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : shutdownTarget, shutdownMode                        **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_ShutdownCauseTarget, EcuM_InitStatus,          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09128 SRS_ModeMgm_09119 SRS_BSW_00337 SRS_BSW_00350
 * SRS_ModeMgm_09235 SRS_ModeMgm_09271 SRS_BSW_00327 SRS_BSW_00385
 * SRS_ModeMgm_09274 SRS_ModeMgm_09275 SRS_ModeMgm_09101 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetShutdownTarget
  (P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
  P2VAR(EcuM_ShutdownModeType, AUTOMATIC, ECUM_APPL_DATA) shutdownMode)
{
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  /* Initialize stdRetVal to E_OK */
  stdRetVal = (Std_ReturnType)E_OK;

  /* @Trace: EcuM_SUD_API_973 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /*Report to DET */
    (void)EcuM_DetReportError(ECUM_GETSHUTDOWNTARGET_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */

    /* Update Return Value */
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /* @Trace: EcuM_SUD_API_972 */
    /* Is shutdownTarget null pointer */
    if (shutdownTarget == NULL_PTR)
    {
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETSHUTDOWNTARGET_SID,
      ECUM_E_PARAM_POINTER);
      #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
      /* Update Return Value */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    /* Is return value E_OK */
    else
    {
      /* Update the shutdownTarget */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "The pointer has checked for not NULL." */
      *shutdownTarget = EcuM_ShutdownCauseTarget.SelectShutdownTarget; /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "The pointer has checked for not NULL." */

      /* @Trace: EcuM_SUD_API_020 */
      /* Is the selected shutdown shutdownTarget SLEEP */
      if (ECUM_SHUTDOWN_TARGET_SLEEP ==
      EcuM_ShutdownCauseTarget.SelectShutdownTarget)
      {
        /* @Trace: EcuM_SUD_API_971 */
        /* Is shutdownMode null pointer */
        if (shutdownMode == NULL_PTR)
        {
          #if (STD_ON == ECUM_DEV_ERROR_DETECT)
          /* Report to DET */
          (void)EcuM_DetReportError(ECUM_GETSHUTDOWNTARGET_SID, 
          ECUM_E_PARAM_POINTER);
          #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
          /* Update Return Value */
          stdRetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
          /* @Trace: EcuM_SUD_API_022 */
          /* Update with current shutdownMode index */
          /* polyspace +1 RTE:IDP [Not a defect:Low] "The pointer has checked for not NULL." */
          *shutdownMode = EcuM_ShutdownCauseTarget.SleepMode; /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "The pointer has checked for not NULL." */
        }
      } /* End of if (EcuM_ShutdownCauseTarget.SelectShutdownTarget
         * is ECUM_SHUTDOWN_TARGET_SLEEP) */
      /* @Trace: EcuM_SUD_API_970 */
      else if (ECUM_SHUTDOWN_TARGET_RESET ==
      EcuM_ShutdownCauseTarget.SelectShutdownTarget)
      {

        /* Is shutdownMode null pointer */
        if (shutdownMode == NULL_PTR)
        {
          #if (STD_ON == ECUM_DEV_ERROR_DETECT)
          /* Report to DET */
          (void)EcuM_DetReportError(ECUM_GETSHUTDOWNTARGET_SID,
          ECUM_E_PARAM_POINTER);
          #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
          /* Update Return Value */
          stdRetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
          /* @Trace: EcuM_SUD_API_021 */
          /* Update with current shutdownMode index */
          /* polyspace +1 RTE:IDP [Not a defect:Low] "The pointer has checked for not NULL." */
          *shutdownMode = EcuM_ShutdownCauseTarget.ResetMode; /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "The pointer has checked for not NULL." */
        }
      } /* End of if (EcuM_ShutdownCauseTarget.SelectShutdownTarget
         * is ECUM_SHUTDOWN_TARGET_RESET) */
      else
      {
        /* Do nothing */
      }
    }
  }
  /* Return stdRetVal */
  return stdRetVal;
} /* End of EcuM_GetShutdownTarget */

/*******************************************************************************
** Function Name        : EcuM_GetLastShutdownTarget                          **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : EcuM_GetLastShutdownTarget returns the shutdown     **
**                        target of the previous shutdown process.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : shutdownTarget, shutdownMode                        **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_LastShutdown, EcuM_InitStatus                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09128 SRS_ModeMgm_09235 SRS_ModeMgm_09119
 * SRS_ModeMgm_09272 SRS_BSW_00337 SRS_BSW_00350 SRS_ModeMgm_09101
 * SRS_BSW_00327 SRS_BSW_00385 SRS_ModeMgm_09274 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetLastShutdownTarget
  (P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
   P2VAR(EcuM_ShutdownModeType, AUTOMATIC, ECUM_APPL_DATA) shutdownMode)
{
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  /* Initialize stdRetVal to E_OK */
  stdRetVal = (Std_ReturnType)E_OK;

  /* @Trace: EcuM_SUD_API_979 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /*Report to DET */
    (void)EcuM_DetReportError(ECUM_GETLASTSHUTDOWNTARGET_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    /* Update Return Value */
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /* @Trace: EcuM_SUD_API_978 */
    /* Is shutdownTarget null pointer */
    if (shutdownTarget == NULL_PTR)
    {
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETLASTSHUTDOWNTARGET_SID,
      ECUM_E_PARAM_POINTER);
      #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
      /* Update Return Value */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    /* Is return value E_OK */
    else
    {
      /* @Trace: EcuM_SUD_API_025 */
      /* Update the shutdownTarget with last shutdown shutdownTarget */
      /* polyspace +2 RTE:OF [Not a defect:Low] "The pointer has checked for not NULL." */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "The pointer has checked for not NULL." */
      *shutdownTarget = EcuM_LastShutdown.MostRecentTarget; /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "The pointer has checked for not NULL." */

      /* Is shutdown shutdownTarget SLEEP */
      if (ECUM_SHUTDOWN_TARGET_SLEEP == EcuM_LastShutdown.MostRecentTarget)
      {
        
        /* @Trace: EcuM_SUD_API_026 */
        /* Is shutdownMode null pointer */
        if (shutdownMode == NULL_PTR)
        {
          #if (STD_ON == ECUM_DEV_ERROR_DETECT)
          /* Report to DET */
          (void)EcuM_DetReportError(ECUM_GETLASTSHUTDOWNTARGET_SID,
          ECUM_E_PARAM_POINTER);
          #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
          /* Update Return Value */
          stdRetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
          /* @Trace: EcuM_SUD_API_023 */
          /* Update with last shutdownMode index */
          /* polyspace +1 RTE:IDP [Not a defect:Low] "The pointer has checked for not NULL." */
          *shutdownMode = EcuM_LastShutdown.MostRecentSlpModeId; /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "The pointer has checked for not NULL." */
        }
      } /* End of if (EcuM_LastShutdown.MostRecentTarget is
         * ECUM_SHUTDOWN_TARGET_SLEEP) */
      /* @Trace: EcuM_SUD_API_024 */
      else if (ECUM_SHUTDOWN_TARGET_RESET == EcuM_LastShutdown.MostRecentTarget)
      {

        /* Is shutdownMode null pointer */
        if (shutdownMode == NULL_PTR)
        {
          #if (STD_ON == ECUM_DEV_ERROR_DETECT)
          /* Report to DET */
          (void)EcuM_DetReportError(ECUM_GETLASTSHUTDOWNTARGET_SID,
          ECUM_E_PARAM_POINTER);
          #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
          /* Update Return Value */
          stdRetVal = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
          /* @Trace: EcuM_SUD_API_977 */
          /* Update with last shutdownMode index */
          /* polyspace +1 RTE:IDP [Not a defect:Low] "The pointer has checked for not NULL." */
          *shutdownMode = EcuM_LastShutdown.MostRecentRstModeId; /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "The pointer has checked for not NULL." */
        }
      } /* End of if (EcuM_LastShutdown.MostRecentTarget is
         * ECUM_SHUTDOWN_TARGET_RESET) */
      else
      {
        /* @Trace: EcuM_SUD_API_976 */
        /* Do nothing */
      }
    }
  }
  /* Return stdRetVal */
  return stdRetVal;
} /* End of EcuM_GetLastShutdownTarget */

/*******************************************************************************
** Function Name        : EcuM_SelectShutdownCause                            **
**                                                                            **
** Service ID           : 0x1b                                                **
**                                                                            **
** Description          : This routine is intended for primary use in STARTUP **
**                      : or RUN state. The return value describes the ECU    **
**                      : state from which the last wakeup or power up        **
**                      : occurred. This function shall return always the same**
**                      : value until the next shutdown                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : target                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_ShutdownCauseTarget, EcuM_InitStatus           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, EcuM_SearchShutdownCause,      **
**                        SchM_Enter_EcuM_SHUTDOWN_CAUSE,                     **
**                        SchM_Exit_EcuM_SHUTDOWN_CAUSE                       **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09274 SRS_ModeMgm_09275 SRS_ModeMgm_09128
 * SRS_ModeMgm_09270 SRS_ModeMgm_09101 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectShutdownCause
  (EcuM_ShutdownCauseType target)
{
  boolean status;
  uint8 causeIndex;

  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  /* Initialize stdRetVal to E_OK */
  stdRetVal = (Std_ReturnType)E_OK;
  /* @Trace: EcuM_SUD_API_969 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /*Report to DET */
    (void)EcuM_DetReportError(ECUM_SELECTSHUTDOWNCAUSE_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    /* Update Return Value */
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /* @Trace: EcuM_SUD_API_968 */
    status = EcuM_SearchShutdownCause(&causeIndex, target);

    if ( FALSE == status)
    {
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_SELECTSHUTDOWNCAUSE_SID,
        ECUM_E_INVALID_PAR);
      #endif
      /* Set stdRetVal to E_NOT_OK */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
    } /* End of if (status is FALSE) */
    else
    {
     /* @Trace: EcuM_SUD_API_027 */
     /* Enable data protection */
      SchM_Enter_EcuM_SHUTDOWN_CAUSE();
      /* Update the shutdown cause */
      EcuM_ShutdownCauseTarget.ShutdownCause = target;
      /* Disable data protection  */
      SchM_Exit_EcuM_SHUTDOWN_CAUSE();
    }
  }
  return stdRetVal;
} /* End of EcuM_SelectShutdownCause */

/*******************************************************************************
** Function Name        : EcuM_GetShutdownCause                               **
**                                                                            **
** Service ID           : 0x1c                                                **
**                                                                            **
** Description          : This routine is intended for primary use in STARTUP **
**                      : or RUN state. The return value describes the ECU    **
**                      : state from which the last wakeup or power up        **
**                      : occurred. This function shall return always the same**
**                      : value until the next shutdown                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : shutdownCause                                       **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : The ECU state manager must be initialized.          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_ShutdownCauseTarget, EcuM_InitStatus           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09275 SRS_ModeMgm_09128
 * SRS_ModeMgm_09270 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385
 * SRS_ModeMgm_09274 SRS_ModeMgm_09101 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetShutdownCause
  (P2VAR(EcuM_ShutdownCauseType, AUTOMATIC, ECUM_APPL_DATA) shutdownCause)
{
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  /* Initialize stdRetVal to E_OK */
  stdRetVal = (Std_ReturnType)E_OK;
  /* @Trace: EcuM_SUD_API_975 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /*Report to DET */
    (void)EcuM_DetReportError(ECUM_GETSHUTDOWNCAUSE_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    /* Update Return Value */
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /* @Trace: EcuM_SUD_API_974 */
    /* Is shutdownCause null pointer */
    if (shutdownCause == NULL_PTR)
    {
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETSHUTDOWNCAUSE_SID,
       ECUM_E_PARAM_POINTER);
      #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
      /* Update Return Value */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      /* @Trace: EcuM_SUD_API_028 */		
      /* Update the current shutdown cause */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "The pointer has checked for not NULL." */
      *shutdownCause = EcuM_ShutdownCauseTarget.ShutdownCause; /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "The pointer has checked for not NULL." */
    }
  }
  return stdRetVal;
} /* End of EcuM_GetShutdownCause */

/*******************************************************************************
** Function Name        : EcuM_GetPendingWakeupEvents                         **
**                                                                            **
** Service ID           : 0x0d                                                **
**                                                                            **
** Description          : This routine is responsible for returning the       **
**                        wakeup events, which have been set but not yet      **
**                        validated                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : EcuM_PendingWakeupEvents                            **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_PendingWakeupEvents           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09100 SRS_ModeMgm_09119 SRS_ModeMgm_09102
 * SRS_ModeMgm_09097 SRS_ModeMgm_09126 SRS_ModeMgm_09136 SRS_BSW_00327
 * SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385 */
FUNC(EcuM_WakeupSourceType, ECUM_CODE) EcuM_GetPendingWakeupEvents(void)
{
  /* @Trace: EcuM_SUD_API_029 */
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  /* Is module not initialized */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "Reachable code depend on the calling of EcuM_Init function" */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETPENDINGWAKEUPEVENTS_SID, ECUM_E_UNINIT);
  }
  /* polyspace-end RTE:UNR [Not a defect:Low] "Reachable code depend on the calling of EcuM_Init function" */
  #endif

  /* Return pending wakeup events */
  return (EcuM_PendingWakeupEvents);
} /* End of EcuM_GetPendingWakeupEvents */

/*******************************************************************************
** Function Name        : EcuM_ClearWakeupEvent                               **
**                                                                            **
** Service ID           : 0x16                                                **
**                                                                            **
** Description          : This routine is responsible for clearing all wake up**
**                        events like pending, validated and expired events.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : sources                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_ValidatedWakeupEvents,        **
**                        EcuM_PendingWakeupEvents, EcuM_WakeupStatus,        **
**                        EcuM_ExpiredWakeupEvents, EcuM_WakeupCounter        **
**                        EcuM_WakeupSource                                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, BswM_EcuM_CurrentWakeup        **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09100 SRS_ModeMgm_09100 SRS_ModeMgm_09119
 * SRS_ModeMgm_09102 SRS_ModeMgm_09097 SRS_ModeMgm_09126 SRS_ModeMgm_09136
 * SRS_ModeMgm_09254 SRS_EcuM_AR_00004 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350
 * SRS_BSW_00385 */
FUNC(void, ECUM_CODE) EcuM_ClearWakeupEvent(EcuM_WakeupSourceType sources)
{
  /* Variable used as index for wakeupSource structure array */
  uint8 sourceIndex;
  EcuM_WakeupSourceType wkSrcMask;
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  boolean searchResult;
  searchResult =  FALSE;
  #endif
  wkSrcMask = sources;

  /* @Trace: EcuM_SUD_API_198 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    /* Report to DET */
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    (void)EcuM_DetReportError(ECUM_CLEARWAKEUPEVENT_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  }/* Module is initialized */
  else
  {
    /* To enable data protection */
    SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

    /* @Trace: EcuM_SUD_API_030 */
    /* clear validated event */
    EcuM_ValidatedWakeupEvents &= (EcuM_WakeupSourceType)(~sources);

    /* clear pending event */
    EcuM_PendingWakeupEvents &= (EcuM_WakeupSourceType)(~sources);

    /* clear Expired event */
    EcuM_ExpiredWakeupEvents &= (EcuM_WakeupSourceType)(~sources);
    /* To disable data protection */
    SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();
    /* @Trace: EcuM_SUD_API_958 */
    /* set index value to check all wakeup source */
    sourceIndex = ECUM_ZERO;
    
    while(sourceIndex < ECUM_NO_OF_WAKEUPSOURCES)
    {
      /* polyspace +2 RTE:UNR [Not a defect:Low] "the value of any source which is not exist in EcuM configuration shall make the condition false" */
      if ((sources & EcuM_WakeupSource[sourceIndex].WakeupSourceId) ==
      EcuM_WakeupSource[sourceIndex].WakeupSourceId)
      {
        /* Clear Counter */
        /* polyspace<RTE: OBAI : Not a defect : No Action Planned > index has been checked */
        /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations> index has been checked */
        EcuM_WakeupCounter[sourceIndex] = (uint16)ECUM_ZERO;

        /* To enable data protection */
        SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();
        /* Updating Status as None */
        /* polyspace<RTE: OBAI : Not a defect : No Action Planned > index has been checked */
        /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations> index has been checked */
        EcuM_WakeupStatus[sourceIndex] = ECUM_WKSTATUS_NONE;

        /* To exit data protection */
        SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

        #if (STD_ON == ECUM_DEV_ERROR_DETECT)
        /* set flag for request source valid */
        searchResult = TRUE;
        #endif
        wkSrcMask &= (~(EcuM_WakeupSource[sourceIndex].WakeupSourceId));

        /* Indicate current status of Wakeup source */
        BswM_EcuM_CurrentWakeup(EcuM_WakeupSource[sourceIndex].WakeupSourceId, ECUM_WKSTATUS_NONE);
      }
      /* polyspace +1 RTE:UNR [Not a defect:Low] "the value of wkSrcMask shall be clear after wakeup event is validated" */
      if(wkSrcMask == ECUM_ZERO)
      {
        /* Exit check wakeup source */
        sourceIndex = ECUM_NO_OF_WAKEUPSOURCES;
      }
      else
      {
        /* Increase index for check wakeup source */
        sourceIndex++;
      }
    }

    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* @Trace: EcuM_SUD_API_197 */
    if( FALSE == searchResult)
    {
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_CLEARWAKEUPEVENT_SID,
        ECUM_E_UNKNOWN_WAKEUP_SOURCE);
    }
    #endif


  }
} /* End of EcuM_ClearWakeupEvent */

/*******************************************************************************
** Function Name        : EcuM_GetValidatedWakeupEvents                       **
**                                                                            **
** Service ID           : 0x15                                                **
**                                                                            **
** Description          : This routine is responsible for returning all the   **
**                        wakeup events that have passed the validation.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : EcuM_ValidatedWakeupEvents                          **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_ValidatedWakeupEvents         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09100 SRS_ModeMgm_09119 SRS_ModeMgm_09102
 * SRS_ModeMgm_09097 SRS_ModeMgm_09126 SRS_ModeMgm_09136 SRS_BSW_00327
 * SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385 */
FUNC(EcuM_WakeupSourceType, ECUM_CODE) EcuM_GetValidatedWakeupEvents(void)
{
  /* @Trace: EcuM_SUD_API_031 */
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETVALIDATEDWAKEUPEVENTS_SID, ECUM_E_UNINIT);
  }
  #endif

  /* Return validated wakeup events */
  return (EcuM_ValidatedWakeupEvents);
} /* End of EcuM_GetValidatedWakeupEvents */

/*******************************************************************************
** Function Name        : EcuM_GetExpiredWakeupEvents                         **
**                                                                            **
** Service ID           : 0x19                                                **
**                                                                            **
** Description          : This routine is responsible for returning all the   **
**                        wakeup events that have been set but failed the     **
**                        validation. Events that do not need validation must **
**                        never be reported by this function.                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : EcuM_ExpiredWakeupEvents                            **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_ExpiredWakeupEvents           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09100 SRS_ModeMgm_09119 SRS_ModeMgm_09102
 * SRS_ModeMgm_09126 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385 */
FUNC(EcuM_WakeupSourceType, ECUM_CODE) EcuM_GetExpiredWakeupEvents(void)
{
  /* @Trace: EcuM_SUD_API_032 */
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)

  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETEXPIREDWAKEUPEVENTS_SID, ECUM_E_UNINIT);
  }
  #endif


  /* Return expired wakeup events */
  return (EcuM_ExpiredWakeupEvents);
} /* End of EcuM_GetExpiredWakeupEvents */

/*******************************************************************************
** Function Name      : EcuM_SelectBootTarget                                 **
**                                                                            **
** Service ID         : 0x12                                                  **
**                                                                            **
** Description        : EcuM_SelectBootTarget selects a boot target.          **
**                      EcuM_SelectBootTarget is part of the ECU Manager      **
**                      Module port interface.                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Reentrant                                             **
**                                                                            **
** Input Parameters   : target                                                **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType (E_OK or E_NOT_OK)                     **
**                                                                            **
** Preconditions      : The ECU state manager must be initialized.            **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      EcuM_InitStatus, EcuM_ShutdownCauseTarget             **
**                                                                            **
**                    : Function(s) invoked:                                  **
**                      EcuM_DetReportError                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385
 * SRS_ModeMgm_09276 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectBootTarget
  (EcuM_BootTargetType target)
{
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  /* Initialize stdRetVal with E_OK */
  stdRetVal = (Std_ReturnType)E_OK;

  /* Is module not initialized */
  /* @Trace: EcuM_SUD_API_987 */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SELECTBOOTTARGET_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    /* Set stdRetVal to E_NOT_OK */
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  /* Module is initialized */
  else
  {
    /* @Trace: EcuM_SUD_API_033 */
    if ((target != ECUM_BOOT_TARGET_APP) &&
        (target != ECUM_BOOT_TARGET_OEM_BOOTLOADER) &&
        (target != ECUM_BOOT_TARGET_SYS_BOOTLOADER))
    {
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_SELECTBOOTTARGET_SID,
        ECUM_E_STATE_PAR_OUT_OF_RANGE);
      #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
      /* Set stdRetVal to E_NOT_OK */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      /* @Trace: EcuM_SUD_API_034 */
      /* Enable data protection */
      SchM_Enter_EcuM_BOOT_TARGET_PROTECTION();

      /* Update the boot target */
      EcuM_ShutdownCauseTarget.BootTarget = target;

      /* Disable data protection */
      SchM_Exit_EcuM_BOOT_TARGET_PROTECTION();
    }
  }
  /* Return E_OK or E_NOT_OK */
  return stdRetVal;
} /* End of EcuM_SelectBootTarget */

/*******************************************************************************
** Function Name      : EcuM_GetBootTarget                                    **
**                                                                            **
** Service ID         : 0x13                                                  **
**                                                                            **
** Description        : EcuM_GetBootTarget returns the current boot target.   **
**                      EcuM_GetBootTarget is part of the ECU Manager Module  **
**                      port interface.                                       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Reentrant                                             **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : target                                                **
**                                                                            **
** Return parameter   : Std_ReturnType (E_OK or E_NOT_OK)                     **
**                                                                            **
** Preconditions      : The ECU state manager must be initialized.            **
**                                                                            **
** Remarks            : Global Variable(s) referred in this function:         **
**                      EcuM_ShutdownCauseTarget, EcuM_InitStatus             **
**                                                                            **
**                    : Function(s) invoked:                                  **
**                      EcuM_DetReportError                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385
 * SRS_BSW_00172 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetBootTarget
  (P2VAR(EcuM_BootTargetType, AUTOMATIC, ECUM_APPL_DATA) target)
{
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  /* Initialize stdRetVal with E_OK */
  stdRetVal = (Std_ReturnType)E_OK;

  /* Is module not initialized */
  /* @Trace: EcuM_SUD_API_988 */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETBOOTTARGET_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    /* Update return value */
    stdRetVal = (Std_ReturnType)E_NOT_OK;  }
  else
  {
    /* @Trace: EcuM_SUD_API_035 */
    /* Is target null pointer */
    if (target == NULL_PTR)
    {
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETBOOTTARGET_SID, ECUM_E_PARAM_POINTER);
      #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
      /* Update return value */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
	  /* @Trace: EcuM_SUD_API_989 */
      /* Update target with current boot target */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "The pointer has checked for not NULL." */
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "The pointer has checked for not NULL." */
      *target = EcuM_ShutdownCauseTarget.BootTarget;

    }
  }
  /* Return E_OK or E_NOT_OK */
  return stdRetVal;
} /* End of EcuM_GetBootTarget */

/*******************************************************************************
** Function Name        : EcuM_StartupTwo                                     **
**                                                                            **
** Service ID           : 0x1a                                                **
**                                                                            **
** Description          : In this state, the initialization of BSW modules    **
**                        which needs OS support is carried out               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_State, EcuM_ptrEcuMConfigPtr                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, EcuM_IsMasterCore              **
**                        GetCoreID, SchM_Init, BswM_Init, SchM_StartTiming   **
**                        BswM_EcuM_CurrentState, SchM_Start,				  **
**                        EcuM_AL_DriverInitCoreWise_PostOs                   **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09237 SRS_ModeMgm_09113 SRS_ModeMgm_09236
 * SRS_BSW_00301 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385 */
FUNC(void, ECUM_CODE) EcuM_StartupTwo(void)
{
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  /* Local variable for master core result */
  CoreIdType coreId;
  #endif
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  /* @Trace: EcuM_SUD_API_199 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_STARTUPTWO_SID, ECUM_E_UNINIT);
  }
  else
  #endif
  {
    #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
    coreId = GetCoreID();
    /* Support to initialize modules per core */
    EcuM_AL_DriverInitCoreWise_PostOs(coreId);
    #endif
    /* @Trace: EcuM_SUD_API_036 */
    SchM_Start();

    if (EcuM_ptrEcuMConfigPtr != NULL_PTR)
    {
      /* @Trace: EcuM_SUD_API_038 */
      /* BswM Initialization */
      /* polyspace-begin RTE:NIP [Not a defect:Low] "ptr points to a valid value and code is verified manually" */
      BswM_Init(EcuM_ptrEcuMConfigPtr->BswMConfig);
      /* SchM Initialization */
      SchM_Init(EcuM_ptrEcuMConfigPtr->SchMConfig);
      /* polyspace-end RTE:NIP [Not a defect:Low] */
      SchM_StartTiming(); /* parameter IN as void - refering to SchM SWS */
    }
    else
    {
      /* @Trace: EcuM_SUD_API_983 */
      /* do nothing */
    }
    /* @Trace: EcuM_SUD_API_981 */
    #if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
    if (OS_CORE_ID_MASTER == coreId)
    {
      /* @Trace: EcuM_SUD_API_037 */
      /* Set EcuM state to StartUp Two */
      EcuM_State = ECUM_STATE_STARTUP_TWO;
      /* Increase os counter initialized */
      (void)GetSpinlock(ECUM_OS_SPINLOCK);
      EcuM_SyncAllcoresCount++;
      (void)ReleaseSpinlock(ECUM_OS_SPINLOCK);
    }
    else
    {
      /* @Trace: EcuM_SUD_API_982 */
      /* Increase os counter initialized */
      (void)GetSpinlock(ECUM_OS_SPINLOCK);
      EcuM_SyncAllcoresCount++;
      (void)ReleaseSpinlock(ECUM_OS_SPINLOCK);
    }

    do {
      /* Do nothing */
    } while (EcuM_SyncAllcoresCount < ECUM_NO_OF_CORES);
    #else
    /* Set EcuM state to StartUp Two */
    EcuM_State = ECUM_STATE_STARTUP_TWO;
    #endif
    BswM_EcuM_CurrentState(EcuM_State);
  }
}/* End of EcuM_StartupTwo */

/*******************************************************************************
** Function Name        : EcuM_MainFunction                                   **
**                                                                            **
** Service ID           : 0x18                                                **
**                                                                            **
** Description          : This Service is to implement all activities of ECU  **
**                        State manager while the OS is up and running.       **
**                                                                            **
** Sync/Async           : None                                                **
**                                                                            **
** Reentrancy           : None                                                **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Startup I must be completed.                        **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_PendingWakeupEvents,          **
**                        EcuM_ExpiredWakeupEvents, EcuM_WakeupSource         **
**                        EcuM_WakeupCounter, EcuM_WakeupStatus,              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_SlaveShutDownOrSleep, EcuM_DetReportError      **
**                        GetCoreID, EcuM_StartWakeupSources                  **
**                        BswM_EcuM_CurrentWakeup, EcuM_StopWakeupSources     **
**                        EcuM_ValidationProtocol                             **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09136 SRS_EcuM_AR_00004 SRS_BSW_00373 SRS_BSW_00425
 * SRS_ModeMgm_09254 SRS_EcuM_AR_00005 SRS_ModeMgm_09097 */
FUNC(void, ECUM_CODE) EcuM_MainFunction(void)
{
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  /* variable storage current core id */
  CoreIdType coreId;
  #endif
  /* Local variable for index */
  uint8 wakeUpIndex;

  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  /* @Trace: EcuM_SUD_API_962 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    /* do nothing */
  }
  else
  #endif
  {
    #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
    /* Get the core id of currently running core  */
    coreId = GetCoreID();

    if (OS_CORE_ID_MASTER == coreId)
    #endif
    {
      #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
      /* @Trace: EcuM_SUD_API_963 */
      /* Handle EcuM clock */
      EcuM_IncrementTimer();
      #endif
      /* @Trace: EcuM_SUD_API_195 */
      /* Process mode changed request from Flex User */
      EcuM_ProcessModeHandingChangedRequest();
      /* Processing Pending wakeups in all states. if any pending events */
      if (EcuM_PendingWakeupEvents != ECUM_NO_EVENTS)
      {
        EcuM_StartWakeupSources(EcuM_PendingWakeupEvents);

        /* To process timeout of all active wakeup sources */
        for (wakeUpIndex = (uint8)ECUM_ZERO; wakeUpIndex <
        ECUM_NO_OF_WAKEUPSOURCES; wakeUpIndex++)
        {
          /* Is wakeup event pending */
          if (EcuM_WakeupStatus[wakeUpIndex] == ECUM_WKSTATUS_PENDING)
          {
            /* @Trace: EcuM_SUD_API_181 */
            /* If Expired */
            if (EcuM_WakeupCounter[wakeUpIndex] == (uint16)ECUM_ZERO)
            {
              /* To enable data protection */
              SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

              /* Update Status as Expired */
              EcuM_WakeupStatus[wakeUpIndex] = ECUM_WKSTATUS_EXPIRED;

              /* Clear corresponding Pending wakeup event */
              EcuM_PendingWakeupEvents &=
                (EcuM_WakeupSourceType)
                (~EcuM_WakeupSource[wakeUpIndex].WakeupSourceId);

              /* Update corresponding Expired wakeup event */
              EcuM_ExpiredWakeupEvents |=
                (EcuM_WakeupSource[wakeUpIndex].WakeupSourceId);

              /* To disable data protection */
              SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

              /* Indicate current status of Wakeup source */
              BswM_EcuM_CurrentWakeup(
              EcuM_WakeupSource[wakeUpIndex].WakeupSourceId,
              ECUM_WKSTATUS_EXPIRED);

              /*  Invoke callout to stop the given wakeup source after
               *  unsuccessful wakeup validation */
              EcuM_StopWakeupSources
                (EcuM_WakeupSource[wakeUpIndex].WakeupSourceId);
            } /* End of if (EcuM_WakeupCounter[WakeUpIndex] is
               * ECUM_ZERO) */
            else
            {
              /* @Trace: EcuM_SUD_API_194 */
              /* Update validation timeout counter */
              EcuM_WakeupCounter[wakeUpIndex]--;
              EcuM_ValidationProtocol();
            }
          } /* End of if (EcuM_WakeupStatus[wakeUpIndex] is
             * ECUM_WKSTATUS_PENDING) */
        }
      } /* End of if (EcuM_PendingWakeupEvents != ECUM_NO_EVENTS) */
    }
    #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
    /* @Trace: EcuM_SUD_API_182 */
    else
    {
      (void)EcuM_SlaveShutDownOrSleep(coreId);
    }
    #endif
  }
} /* End of EcuM_MainFunction */

/*******************************************************************************
** Function Name        : EcuM_SetRelWakeupAlarm                              **
**                                                                            **
** Service ID           : 0x22                                                **
**                                                                            **
** Description          : EcuM_SetRelWakeupAlarm sets a user's wakeup alarm   **
**                        relative to the current point in time.              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user, time                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_NOT_OK or E_NOT_OK or             **
**                        ECUM_E_EARLIER_ACTIVE)                              **
**                                                                            **
** Preconditions        : Startup I must be completed.                        **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_MasterAlarm,                  **
**                        EcuM_AlarmTime, EcuM_RunningTimer, EcuM_AlarmCycle  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError,                                **
**                        EcuM_SearchAlarmClockUser                           **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09186 SRS_ModeMgm_09190 SRS_ModeMgm_09185
 * SRS_ModeMgm_09187 SRS_ModeMgm_09188 SRS_ModeMgm_09189 SRS_ModeMgm_09199
 * SRS_ModeMgm_09194 SRS_ModeMgm_09277 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350
 * SRS_BSW_00385 */
/* polyspace-begin CERT-C:DCL37-C [Not a defect:Low] "Variables define by Autosar spec R44" */
/* polyspace-begin MISRA-C3:21.2 [Not a defect:Low] "Variables define by Autosar spec R44" */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_SetRelWakeupAlarm(EcuM_UserType user,
          EcuM_TimeType time) 
{ /* polyspace-end MISRA-C3:21.2 CERT-C:DCL37-C */
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  
  #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
  /* Variable to store the array index where the user is present */
  uint8 alarmUserInd;
  boolean searchResult;


  /* @Trace: EcuM_SUD_API_175 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SETRELWAKEUPALARM_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /* set initial of return value */
    stdRetVal = (Std_ReturnType)E_OK;

    /* To search index of a wakeup source */
    searchResult = EcuM_SearchAlarmClockUser(&alarmUserInd, user);

    /* @Trace: EcuM_SUD_API_176 */
    /* Is reported wakeup event unknown */
    if (ECUM_FALSE == searchResult)
    {
      /* Report to DET */
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      (void)EcuM_DetReportError(ECUM_SETRELWAKEUPALARM_SID, ECUM_E_INVALID_PAR);
      #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      /* @Trace: EcuM_SUD_API_177 */
      if (EcuM_MasterAlarm == (uint32)ECUM_ZERO)
      {
        SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
        EcuM_AlarmTime[alarmUserInd] = EcuM_RunningTimer + time;
        EcuM_MasterAlarm = EcuM_AlarmTime[alarmUserInd];
        EcuM_AlarmCycle = ECUM_TRUE;
        SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
      }
      /* @Trace: EcuM_SUD_API_178 */
      else if ((EcuM_RunningTimer + time) < EcuM_MasterAlarm)
      { /* If the relative time from now is earlier than the current wakeup time ... */
        /* Enable data protection */
        SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
        /* If the relative time from now is earlier than the current wakeup time,
         * shall update the wakeup time */
        EcuM_AlarmTime[alarmUserInd] = EcuM_RunningTimer + time;
        EcuM_MasterAlarm = EcuM_AlarmTime[alarmUserInd];
        EcuM_AlarmCycle = ECUM_TRUE;
        /* Disable data protection */
        SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
      }
      /* @Trace: EcuM_SUD_API_179 */
      else
      { /* If the relative time from now is later than the current wakeup time ... */
        /* If the relative time from now is later than the current wakeup time,
         * shall not update the wakeup time and shall return ECUM_E_EARLIER_ACTIVE */
        stdRetVal = (Std_ReturnType)ECUM_E_EARLIER_ACTIVE;
      }
    }
  }
  #else /* Else of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */
  /* Update return value is failed */
  stdRetVal = (Std_ReturnType)E_NOT_OK;
  ECUM_UNUSED(user);
  ECUM_UNUSED(time);
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  /* @Trace: EcuM_SUD_API_180 */
  /* Report to DET */
  (void)EcuM_DetReportError(ECUM_SETRELWAKEUPALARM_SID,ECUM_E_SERVICE_DISABLED);

  #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */
  #endif /* #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT) */

  return stdRetVal;
} /* End of EcuM_SetRelWakeupAlarm */

/*******************************************************************************
** Function Name        : EcuM_SetAbsWakeupAlarm                              **
**                                                                            **
** Service ID           : 0x23                                                **
**                                                                            **
** Description          : EcuM_SetAbsWakeupAlarm sets the user's wakeup alarm **
**                        to an absolute point in time.                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user, time                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType: E_NOT_OK, E_OK,                     **
**                        ECUM_E_EARLIER_ACTIVE, ECUM_E_PAST                  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_MasterAlarm,                  **
**                        EcuM_AlarmTime, EcuM_RunningTimer, EcuM_AlarmCycle  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, EcuM_SearchAlarmClockUser      **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09186 SRS_ModeMgm_09199 SRS_ModeMgm_09185
 * SRS_ModeMgm_09187 SRS_ModeMgm_09188 SRS_ModeMgm_09189 SRS_ModeMgm_09190
 * SRS_ModeMgm_09194 SRS_ModeMgm_09277 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350
 * SRS_BSW_00385 */
 
/* polyspace-begin CERT-C:DCL37-C [Not a defect:Low] "Variables define by Autosar spec R44" */
/* polyspace-begin MISRA-C3:21.2 [Not a defect:Low] "Variables define by Autosar spec R44" */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_SetAbsWakeupAlarm(EcuM_UserType user,
     EcuM_TimeType time)
{  /* polyspace-end MISRA-C3:21.2 CERT-C:DCL37-C */
  /* variable store return value */
  Std_ReturnType stdRetVal;
  #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
  /*
   * Local variable for return value
   * Variable to store the array index where the user is present
   */
  uint8 alarmUserInd;
  boolean searchResult;

  /* @Trace: EcuM_SUD_API_170 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SETABSWAKEUPALARM_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /* Initialize stdRetVal with E_OK */
    stdRetVal = (Std_ReturnType)E_OK;
    /* @Trace: EcuM_SUD_API_957 */
    /* Check EcuM User exist or not */
    searchResult = EcuM_SearchAlarmClockUser(&alarmUserInd, user);

    /* Is reported wakeup event unknown */
    if (ECUM_FALSE == searchResult)
    {
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_SETABSWAKEUPALARM_SID, ECUM_E_INVALID_PAR);
      #endif /* End of if (STD_OFF == ECUM_DEV_ERROR_DETECT) */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      /* @Trace: EcuM_SUD_API_171 */
      if (EcuM_MasterAlarm == (uint32)ECUM_ZERO)
      {
        SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
        EcuM_AlarmTime[alarmUserInd] = time;
        EcuM_MasterAlarm = EcuM_AlarmTime[alarmUserInd];
        EcuM_AlarmCycle = ECUM_TRUE;
        SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
      }
      /* @Trace: EcuM_SUD_API_172 */
      else if (time <= EcuM_RunningTimer)
      { /* If the time parameter is earlier than now ... */
        /* If the time is earlier than now ,shall not update the
         * wakeup time and shall return ECUM_E_PAST */
        stdRetVal = (Std_ReturnType)ECUM_E_PAST;
      }
      /* @Trace: EcuM_SUD_API_173 */
      else if (time < EcuM_MasterAlarm)
      { /* If the time parameter is earlier than the current wakeup time ... */
        /* If the time earlier than the current wakeup time ,
         * update the wakeup time */
        SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
        EcuM_AlarmTime[alarmUserInd] = time;
        EcuM_MasterAlarm = EcuM_AlarmTime[alarmUserInd];
        EcuM_AlarmCycle = ECUM_TRUE;
        SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
      }
      /* @Trace: EcuM_SUD_API_174 */
      else
      { /* If the time parameter is later than the current wakeup time ... */
        stdRetVal = (Std_ReturnType)ECUM_E_EARLIER_ACTIVE;
      }
    }
  }
  #else /* Else of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */
  /* @Trace: EcuM_SUD_API_956 */
  /* Update status return value failed */
  stdRetVal = (Std_ReturnType)E_NOT_OK;
  ECUM_UNUSED(user);
  ECUM_UNUSED(time);
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  /* Report error to Det */
  (void)EcuM_DetReportError(ECUM_SETABSWAKEUPALARM_SID,ECUM_E_SERVICE_DISABLED);
  #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */
  #endif /* #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT) */

  return stdRetVal;
} /* End of EcuM_SetAbsWakeupAlarm */

/*******************************************************************************
** Function Name        : EcuM_AbortWakeupAlarm                               **
**                                                                            **
** Service ID           : 0x24                                                **
**                                                                            **
** Description          : EcuM_AbortWakeupAlarm aborts the wakeup alarm       **
**                        previously set by this user.                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK, E_NOT_OK, ECUM_E_NOT_ACTIVE)  **
**                                                                            **
** Preconditions        : Startup I must be completed.                        **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_MasterAlarm,                  **
**                        EcuM_AlarmTime                                      **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError,                                **
**                        EcuM_SearchAlarmClockUser,                          **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385
 * SRS_ModeMgm_09186 SRS_ModeMgm_09187 SRS_ModeMgm_09188 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_AbortWakeupAlarm(EcuM_UserType user)
{
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
  /* Index to loop the number of alarms configured */
  uint8 alarmIndx;
  /* Variable to store the array index where the user is present */
  uint8 alarmUserInd;
  boolean searchResult;

  /* @Trace: EcuM_SUD_API_167 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    /* Report to DET */
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    (void)EcuM_DetReportError(ECUM_ABORTWAKEUPALARM_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /* Initial value is E_OK */
    stdRetVal = (Std_ReturnType)E_OK;

    /* To search index of a wakeup source */
    searchResult = EcuM_SearchAlarmClockUser(&alarmUserInd, user);

    /* @Trace: EcuM_SUD_API_168 */
    /* Is reported wakeup event unknown */
    if (searchResult == ECUM_FALSE)
    {
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_ABORTWAKEUPALARM_SID, ECUM_E_INVALID_PAR);
      #endif /* End of if (STD_OFF == ECUM_DEV_ERROR_DETECT) */
      stdRetVal = (Std_ReturnType)ECUM_E_NOT_ACTIVE;
    }
    else
    {
      if (EcuM_MasterAlarm == EcuM_AlarmTime[alarmUserInd])
      {
        alarmIndx = (uint8)ECUM_ZERO;
        /*Abort the wakeup alarm previously set by this user*/
        /* Enter data protection  */
        SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
        /* Set the master alarm to max value to get the minimum alarm */
        EcuM_MasterAlarm = ECUM_NO_ACTIVE_ALARM;
        /* Clear the validation timeout of corresponding user */
        EcuM_AlarmTime[alarmUserInd] = (uint32)ECUM_ZERO;
        /* Disable data protection */
        SchM_Exit_EcuM_ALARM_TIME_PROTECTION();

        while (alarmIndx < ECUM_NO_OF_ALARMS)
        { /* update again master alarm earliest set by other users*/
          /* @Trace: EcuM_SUD_API_189 */
          /* polyspace-begin RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
          if (alarmIndx != alarmUserInd)
          {
            if ((EcuM_AlarmTime[alarmIndx] != (uint32)ECUM_ZERO) &&
                (EcuM_AlarmTime[alarmIndx] < EcuM_MasterAlarm))
            {
              /* Enter data protection  */
              SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
              /* Update the master alarm */
              EcuM_MasterAlarm = EcuM_AlarmTime[alarmIndx];
              /* Disable data protection */
              SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
            }
          }
          /* polyspace-end RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
          alarmIndx++;
        }
      } /* End of if (EcuM_MasterAlarm is EcuM_AlarmTime[alarmUserInd]) */

      /* @Trace: EcuM_SUD_API_169 */
      if (EcuM_MasterAlarm == ECUM_NO_ACTIVE_ALARM)
      {
        /*in case no alarm is set by other users, then clear the master alarm.*/
        /* Enter data protection  */
        SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
        /* Clear the master alarm */
        EcuM_MasterAlarm = (uint32)ECUM_ZERO;
        /* Disable data protection */
        SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
      }
    }
  }
  #else /* Else of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */
  /* Update return value is failed */
  stdRetVal = (Std_ReturnType)E_NOT_OK;
  ECUM_UNUSED(user);

  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  (void)EcuM_DetReportError(ECUM_ABORTWAKEUPALARM_SID, ECUM_E_SERVICE_DISABLED);

  #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */
  #endif /* #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT) */

  return stdRetVal;
} /* End of EcuM_AbortWakeupAlarm */


/*******************************************************************************
** Function Name        : EcuM_GetCurrentTime                                 **
**                                                                            **
** Service ID           : 0x25                                                **
**                                                                            **
** Description          : EcuM_GetCurrentTime returns the current value of    **
**                        the EcuM clock                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : time                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_NOT_OK or E_OK)                   **
**                                                                            **
** Preconditions        : Startup I must be completed.                        **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_RunningTimer                  **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09277 SRS_ModeMgm_09185 SRS_ModeMgm_09186
 * SRS_ModeMgm_09187 SRS_ModeMgm_09188 SRS_ModeMgm_09189 SRS_ModeMgm_09194
 * SRS_ModeMgm_09190 SRS_ModeMgm_09199 */
/* polyspace-begin CERT-C:DCL37-C [Not a defect:Low] "Variables define by Autosar spec R44" */
/* polyspace-begin MISRA-C3:21.2 [Not a defect:Low] "Variables define by Autosar spec R44" */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetCurrentTime
  ( P2VAR(EcuM_TimeType, AUTOMATIC, ECUM_APPL_DATA) time) /* polyspace MISRA-C3:8.13 [Not a defect:Low] "The parameters pointer type  is to conform to AUTOSAR R4.4.0 spec" */
{ /* polyspace-end MISRA-C3:21.2 CERT-C:DCL37-C */
  /* Local variable for return value */
  Std_ReturnType stdRetVal;

  #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
  /* @Trace: EcuM_SUD_API_163 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETCURRENTTIME_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /* @Trace: EcuM_SUD_API_164 */
    if (time == NULL_PTR)
    {
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETCURRENTTIME_SID, ECUM_E_PARAM_POINTER);
      #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      /* initial value of return is E_OK */
      stdRetVal = (Std_ReturnType)E_OK;

      /* @Trace: EcuM_SUD_API_165 */
      /* Update the current running clock time */
      *time = EcuM_RunningTimer;
    }
  }
  #else /* Else of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */
  /* @Trace: EcuM_SUD_API_166 */
  /* update return value is failed */
  stdRetVal = (Std_ReturnType)E_NOT_OK;
  ECUM_UNUSED_PTR(time);
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  /* Report to DET */
  (void)EcuM_DetReportError(ECUM_GETCURRENTTIME_SID, ECUM_E_SERVICE_DISABLED);
  #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */
  #endif /* #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT) */

  return stdRetVal;
} /* End of EcuM_GetCurrentTime */

/*******************************************************************************
** Function Name        : EcuM_GetWakeupTime                                  **
**                                                                            **
** Service ID           : 0x26                                                **
**                                                                            **
** Description          : EcuM_GetWakeupTime returns the current value of the **
**                        master alarm clock (the minimum absolute time of    **
**                        all user alarm clocks).                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : time                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_NOT_OK or E_OK)                   **
**                                                                            **
** Preconditions        : Startup I must be completed.                        **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_MasterAlarm                   **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09185 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350
 * SRS_BSW_00385 SRS_ModeMgm_09186 SRS_ModeMgm_09187 SRS_ModeMgm_09188
 * SRS_ModeMgm_09189 SRS_ModeMgm_09190 SRS_ModeMgm_09199 SRS_ModeMgm_09194
 * SRS_ModeMgm_09277 SRS_BSW_00323 */
/* polyspace-begin CERT-C:DCL37-C [Not a defect:Low] "Variables define by Autosar spec R44" */
/* polyspace-begin MISRA-C3:21.2 [Not a defect:Low] "Variables define by Autosar spec R44" */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetWakeupTime
  (P2VAR(EcuM_TimeType, AUTOMATIC, ECUM_APPL_DATA) time) /* polyspace MISRA-C3:8.13 [Not a defect:Low] "The parameters pointer type  is to conform to AUTOSAR R4.4.0 spec" */
{ /* polyspace-end CERT-C:DCL37-C MISRA-C3:21.2 */
  /* Local variable for return value */
  Std_ReturnType stdRetVal;

  #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
  /* @Trace: EcuM_SUD_API_161 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETWAKEUPTIME_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    if (time == NULL_PTR)
    {
      /* @Trace: EcuM_SUD_API_960 */
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETWAKEUPTIME_SID, ECUM_E_PARAM_POINTER);
      #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      /* Initial return value is E_OK*/
	  stdRetVal = (Std_ReturnType)E_OK;

      /* @Trace: EcuM_SUD_API_162 */
      if (EcuM_MasterAlarm != (uint32)ECUM_ZERO)
      {
        /* Update the alarm which is set */
        *time = EcuM_MasterAlarm;
      }
      else
      {
        /* No alarm is active or set */
        *time = ECUM_NO_ACTIVE_ALARM;
      }
    }
  }
  #else /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */
  /* @Trace: EcuM_SUD_API_959 */
  /* Update status return value failed */
  stdRetVal = (Std_ReturnType)E_NOT_OK;
  ECUM_UNUSED_PTR(time);
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  /* Report to DET */
  (void)EcuM_DetReportError(ECUM_GETWAKEUPTIME_SID, ECUM_E_SERVICE_DISABLED);
  #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */
  #endif /* #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT) */

  return stdRetVal;
} /* End of EcuM_GetWakeupTime */


/*******************************************************************************
** Function Name        : EcuM_SetClock                                       **
**                                                                            **
** Service ID           : 0x27                                                **
**                                                                            **
** Description          : EcuM_SetClock sets the EcuM clock time to the       **
**                        provided value. This API is useful for testing the  **
**                        alarm services; Alarms that take days to expire     **
**                        can be tested.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user, time                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_NOT_OK or E_OK)                   **
**                                                                            **
** Preconditions        : Startup I must be completed.                        **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_SetClockAllowedUser           **
**                        EcuM_RunningTimer                                   **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09187 SRS_ModeMgm_09194 SRS_ModeMgm_09146
 * SRS_ModeMgm_09189 SRS_ModeMgm_09185 SRS_ModeMgm_09186 SRS_ModeMgm_09188
 * SRS_ModeMgm_09190 SRS_ModeMgm_09199  SRS_ModeMgm_09277 SRS_BSW_00327
 * SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385 */
/* polyspace-begin CERT-C:DCL37-C [Not a defect:Low] "Variables define by Autosar spec R44" */
/* polyspace-begin MISRA-C3:21.2 [Not a defect:Low] "Variables define by Autosar spec R44" */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_SetClock(EcuM_UserType user,
  EcuM_TimeType time)
{ /* polyspace-end MISRA-C3:21.2 CERT-C:DCL37-C */
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  
  #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
  uint8 i;
  boolean setClockUserFlag;

  setClockUserFlag = ECUM_FALSE;
  i = (uint8)ECUM_ZERO;
  /* @Trace: EcuM_SUD_API_157 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    /* Report to DET */
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    (void)EcuM_DetReportError(ECUM_SETCLOCK_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /* initial of return value is E_OK */
    stdRetVal = (Std_ReturnType)E_OK;
    /* @Trace: EcuM_SUD_API_955 */
    while (i < ECUM_NO_OF_CLOCKUSERS)
    {
      if (user == EcuM_SetClockAllowedUser[i])
      {
        setClockUserFlag = ECUM_TRUE;
        i = ECUM_NO_OF_CLOCKUSERS;
      }
      i++;
    }
    /* @Trace: EcuM_SUD_API_158 */
    if (setClockUserFlag != ECUM_TRUE)
    {
      /* Report to DET */
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      (void)EcuM_DetReportError(ECUM_SETCLOCK_SID, ECUM_E_INVALID_PAR);
      #endif /* End of if (STD_OFF == ECUM_DEV_ERROR_DETECT) */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
      /* @Trace: EcuM_SUD_API_159 */
      /* Enable data protection */
      SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
      /* Update the running timer  */
      EcuM_RunningTimer = time;
      /* Disable data protection  */
      SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
    }
  }
  #else /* Else of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */
  /* @Trace: EcuM_SUD_API_160 */
  /* Initialize stdRetVal with E_NOT_OK */
  stdRetVal = (Std_ReturnType)E_NOT_OK;
  ECUM_UNUSED(user);
  ECUM_UNUSED(time);
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  /* Report to DET */
  (void)EcuM_DetReportError(ECUM_SETCLOCK_SID, ECUM_E_SERVICE_DISABLED);
  #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */
  #endif /* #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT) */

  return stdRetVal;
} /* End of EcuM_SetClock */


/*******************************************************************************
** Function Name        : EcuM_GetResetReason                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : EcuM_GetResetReason returns the current value of    **
**                        the EcuM ResetReason                                **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : resetreason                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_ResetReason, EcuM_InitStatus                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError                                 **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetResetReason
  (P2VAR(Mcu_ResetType, AUTOMATIC, ECUM_APPL_DATA) resetreason)
{
  /* Local variable for return value */
  Std_ReturnType stdRetVal;

  /* @Trace: EcuM_SUD_API_113 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_GETRESETREASON_SID, ECUM_E_UNINIT);
    #endif
    stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    if(resetreason == NULL_PTR)
	{
	  /* @Trace: EcuM_SUD_API_986 */
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_GETRESETREASON_SID, ECUM_E_PARAM_POINTER);
      #endif
      stdRetVal = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
	  /* @Trace: EcuM_SUD_API_985 */
      /* Update value reset reason */
      *resetreason = EcuM_ResetReason; /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "The pointer has checked for not NULL." */

      stdRetVal = (Std_ReturnType)E_OK;
    }
  }
  return stdRetVal;
}  /* End of EcuM_GetResetReason */

/*******************************************************************************
** Function Name        : EcuM_RequestRUN                                     **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : Places a request for the RUN state. Requests can be **
**                        placed by every user made known to the state manager**
**                        at configuration time.                              **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_RunRequestStatus                               **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, BswM_RequestMode               **
*******************************************************************************/
 /* @Trace: SRS_ModeMgm_09122 SRS_ModeMgm_09017 SRS_ModeMgm_09238
  * SRS_ModeMgm_09116 SRS_ModeMgm_09115 SRS_ModeMgm_09001, SRS_EcuM_AR_00006
  * SRS_EcuM_AR_00012 */

FUNC(Std_ReturnType, ECUM_CODE) EcuM_RequestRUN
(EcuM_UserType user)
{
  /* Local variable for return value */
  Std_ReturnType stdRetVal = (Std_ReturnType)E_NOT_OK;

  /* @Trace: EcuM_SUD_API_109 */
  #if (STD_ON == ECUM_MODE_HANDLING)

  /*Local variable for index*/
  uint8 i;
  /* flag to check the input user */
  boolean validUserRequest = ECUM_FALSE;
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  CoreIdType coreId;
  /* Local variable for master core result */
  coreId = GetCoreID();
  #endif
  for(i = ECUM_ZERO; i < ECUM_NO_OF_USERS; i++)
  {
    if((user == EcuM_FlexUsers[i].User)
    #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
    && (coreId == EcuM_FlexUsers[i].CoreId)
    #endif
    )
    {
      /* @Trace: EcuM_SUD_API_110 */
      /* valid user */
      validUserRequest = ECUM_TRUE;
      /* Check duplicated request from the same user */
      if(EcuM_FlexUsers_RUN_RequestStatus[i] == ECUM_RUNSTATUS_REQUESTED)
      {
        #if (STD_ON == ECUM_DEV_ERROR_DETECT)
        /* Report to DET */
        (void)EcuM_DetReportError(ECUM_REQUESTRUN_SID, ECUM_E_MULTIPLE_RUN_REQUESTS);
        #endif
        stdRetVal = (Std_ReturnType)E_NOT_OK;
      }
      else
      {
          SchM_Enter_EcuM_STATE_PROTECTION();
          /* @Trace: EcuM_SUD_API_111 */
          EcuM_FlexUsers_RUN_RequestStatus[i] = ECUM_RUNSTATUS_REQUESTED;
          SchM_Exit_EcuM_STATE_PROTECTION();

          /* Set return value to E_OK */
          stdRetVal = (Std_ReturnType)E_OK;

          /* @Trace: EcuM_SUD_API_112 */
          /*When the ECU State Manager is not in the state requested by flex user*/
          if((uint8)ECUM_RUNSTATUS_REQUESTED != EcuM_RunRequestStatus)
          {
              SchM_Enter_EcuM_STATE_PROTECTION();
              EcuM_RunRequestStatus = (uint8)ECUM_RUNSTATUS_REQUESTED;
              EcuM_ModeHandlingChangeStatus = ECUM_TRUE;
              SchM_Exit_EcuM_STATE_PROTECTION();
          }
          else
          {
            /*do nothing*/
          }
      }
      /* Exit the loop for efficiency */
      break;
    }
    else
    {
      /*do nothing, check next userId */
    }
  }
  /* @Trace: EcuM_SUD_API_946 */
  /* if the user is invalid */
  if (validUserRequest != ECUM_TRUE)
  {
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_REQUESTRUN_SID, ECUM_E_INVALID_PAR);
      #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  #else /* Else of if (STD_ON == ECUM_MODE_HANDLING) */
  /* @Trace: EcuM_SUD_API_217 */
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  /* Report to DET */
  (void)EcuM_DetReportError(ECUM_REQUESTRUN_SID, ECUM_E_SERVICE_DISABLED);
  #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */

  ECUM_UNUSED(user);
  #endif /* #if (STD_ON == ECUM_MODE_HANDLING) */

  return stdRetVal;
}  /* End of EcuM_RequestRUN */

/*******************************************************************************
** Function Name        : EcuM_ReleaseRUN                                     **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : Releases a RUN request previously done with a call  **
**                        to EcuM_RequestRUN. The service is intended for     **
**                        implementing AUTOSAR ports                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_RunRequestStatus, EcuM_FlexUsers               **
**                        EcuM_FlexUsers_RUN_RequestStatus, EcuM_State        **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, BswM_RequestMode               **
**                        EcuM_IsMasterCore, BswM_EcuM_RequestedState         **
*******************************************************************************/
/* @Trace:SRS_ModeMgm_09116 SRS_ModeMgm_09115 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ReleaseRUN (EcuM_UserType user)
{
 /* Local variable for return value */
  Std_ReturnType stdRetVal;
  /* initial return value is E_NOT_OK */
  stdRetVal = (Std_ReturnType)E_NOT_OK;
  /* @Trace: EcuM_SUD_API_152 */
  #if (STD_ON == ECUM_MODE_HANDLING)
  /*Local variable for index*/
  boolean isNotTheLastRelease = ECUM_FALSE;
  boolean validUserRequest = ECUM_FALSE;
  uint8 i;
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  /* Variable for check core Id */
  CoreIdType coreId;
  /* Local variable for master core result */
  coreId = GetCoreID();
  #endif
  for(i = ECUM_ZERO; i < ECUM_NO_OF_USERS; i++)
  {
    /* Check is the request user valid or not */
    if((user == EcuM_FlexUsers[i].User)
    #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
    && (coreId == EcuM_FlexUsers[i].CoreId)
    #endif
    )
    {
      /* valid user */
      validUserRequest = ECUM_TRUE;
      /* Duplicate request for the same user */
      if(EcuM_FlexUsers_RUN_RequestStatus[i] != ECUM_RUNSTATUS_REQUESTED)
      {
        /* @Trace: EcuM_SUD_API_952 */
        #if (STD_ON == ECUM_DEV_ERROR_DETECT)
        /* Report to DET on releasing without a matching request.*/
        (void)EcuM_DetReportError(ECUM_RELEASERUN_SID,
          ECUM_E_MISMATCHED_RUN_RELEASE);
        #endif
        /* Update return status is failed */
        stdRetVal = (Std_ReturnType)E_NOT_OK;
      }
      else
      {
          /* @Trace: EcuM_SUD_API_154 */
          SchM_Enter_EcuM_STATE_PROTECTION();
          /* set EcuM flex user to ECUM_RUNSTATUS_RELEASED */
          EcuM_FlexUsers_RUN_RequestStatus[i] = ECUM_RUNSTATUS_RELEASED;
          SchM_Exit_EcuM_STATE_PROTECTION();
          /* return value is E_OK */
          stdRetVal = (Std_ReturnType)E_OK;
      }
    } /* End of if(EcuM_FlexUsers_RUN_RequestStatus[i]
         * != ECUM_RUNSTATUS_REQUESTED) */
    else
    {
     /* */
    }
    /* @Trace: EcuM_SUD_API_951 */
    /*Check if Is the last user released */
    if(ECUM_RUNSTATUS_REQUESTED == EcuM_FlexUsers_RUN_RequestStatus[i])
    {
        /* Keeping status is RUN state if at least one user request RUN existing */
        isNotTheLastRelease = ECUM_TRUE;
    }
    else
    {
      /*Do nothing */
    }
  }
  /* @Trace: EcuM_SUD_API_155 */
  /* Is the last release*/
  if((ECUM_TRUE == validUserRequest)
    && (ECUM_FALSE == isNotTheLastRelease)
    && ((uint8)ECUM_RUNSTATUS_RELEASED != EcuM_RunRequestStatus))
  {
      SchM_Enter_EcuM_STATE_PROTECTION();
      EcuM_RunRequestStatus = (uint8)ECUM_RUNSTATUS_RELEASED;
      EcuM_ModeHandlingChangeStatus = ECUM_TRUE;
      SchM_Exit_EcuM_STATE_PROTECTION();

      /* Update shutdown or sleep request state */
      if ((ECUM_SHUTDOWN_TARGET_SLEEP == EcuM_ShutdownCauseTarget.SelectShutdownTarget)
    	  && (ECUM_REQUEST_SLEEP != EcuM_ShutdownOrSleepRequested))
      {
          /* @Trace: EcuM_SUD_API_950 */
          SchM_Enter_EcuM_STATE_PROTECTION();
          EcuM_ShutdownOrSleepRequested = ECUM_REQUEST_SLEEP;
          SchM_Exit_EcuM_STATE_PROTECTION();
      }
      else if ((ECUM_SHUTDOWN_TARGET_RESET == EcuM_ShutdownCauseTarget.SelectShutdownTarget)
        	  && (ECUM_REQUEST_RESET != EcuM_ShutdownOrSleepRequested))
      {
          /* @Trace: EcuM_SUD_API_949 */
          SchM_Enter_EcuM_STATE_PROTECTION();
          EcuM_ShutdownOrSleepRequested = ECUM_REQUEST_RESET;
          SchM_Exit_EcuM_STATE_PROTECTION();
      }
      else if ((ECUM_SHUTDOWN_TARGET_OFF == EcuM_ShutdownCauseTarget.SelectShutdownTarget)
        	  && (ECUM_REQUEST_OFF != EcuM_ShutdownOrSleepRequested))
      {
          /* @Trace: EcuM_SUD_API_948 */
          SchM_Enter_EcuM_STATE_PROTECTION();
          EcuM_ShutdownOrSleepRequested = ECUM_REQUEST_OFF;
          SchM_Exit_EcuM_STATE_PROTECTION();
      }
      else
      {
    	  /* do nothing */
      }
  }
  else if (ECUM_FALSE == validUserRequest)
  {
      /* @Trace: EcuM_SUD_API_947 */
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_RELEASERUN_SID, ECUM_E_INVALID_PAR);
      #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {
    /*stay in RUN state*/
  }

  #else /* Else of if (STD_ON == ECUM_MODE_HANDLING) */
  /* @Trace: EcuM_SUD_API_216 */
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)

  /* Report to DET */
  (void)EcuM_DetReportError(ECUM_RELEASERUN_SID, ECUM_E_SERVICE_DISABLED);
  #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */
  /* update return status failed */

  ECUM_UNUSED(user);
  #endif /* #if (STD_ON == ECUM_MODE_HANDLING) */
  return stdRetVal;
}
/*******************************************************************************
** Function Name        : EcuM_RequestPOST_RUN                                **
**                                                                            **
** Service ID           : 0x0a                                                **
**                                                                            **
** Description          : Places a request for the POST RUN state. Requests   **
**                        can be placed by every user made known to the state **
**                        manager at configuration time. Requests for RUN and **
**                        POST RUN must be tracked independently (in other    **
**                        words: two independent variables). The service is   **
**                        intended for implementing AUTOSAR ports.            **
**                        This API is called by SWC only. Because after all   **
**                        RUN Request is released => EcuM calls to BswM to    **
**                        request POST_RUN by BswM_EcuM_RequestedState().     **
**                        This API will never called until SWC need POST_RUN  **
**                        activity                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK, E_NOT_OK)                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_RunRequestStatus                               **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, BswM_RequestMode               **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09122, SRS_ModeMgm_09017 SRS_ModeMgm_09238
 * SRS_ModeMgm_09116 SRS_ModeMgm_09115 SRS_ModeMgm_09165 SRS_ModeMgm_09001
 * SRS_EcuM_AR_00006 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_RequestPOST_RUN(EcuM_UserType user)
{
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  /* initial return value E_NOT_OK */
  stdRetVal = (Std_ReturnType)E_NOT_OK;

  #if (STD_ON == ECUM_MODE_HANDLING)
  /*Local variable for index*/
  uint8 i;
  boolean validUserRequest = ECUM_FALSE;
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  CoreIdType coreId;
  /* Local variable for master core result */
  coreId = GetCoreID();
  #endif
  for(i = ECUM_ZERO; i < ECUM_NO_OF_USERS; i++)
  {
    if((user == EcuM_FlexUsers[i].User)
    #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
    && (coreId == EcuM_FlexUsers[i].CoreId)
    #endif
    )
    {
      /* If a SW-C needs post run activity during POST_RUN (e.g. shutdown
       * preparation), then it must request POST_RUN before releasing the RUN
       * request. Otherwise it is not guaranteed that this SW-C will get a
       * chance to run its POST_RUN code. */

      /* @Trace: EcuM_SUD_API_149 */
      /* valid user */
      validUserRequest = ECUM_TRUE;
      /* Duplicated request from the same user, report to DET */
      if(EcuM_FlexUsers_POSTRUN_RequestStatus[i] == ECUM_RUNSTATUS_REQUESTED)
      {
        #if (STD_ON == ECUM_DEV_ERROR_DETECT)
        /* Report to DET */
        (void)EcuM_DetReportError(ECUM_REQUESTPOST_RUN_SID,
          ECUM_E_MULTIPLE_RUN_REQUESTS);
        #endif
        stdRetVal = (Std_ReturnType)E_NOT_OK;
      }
      else
      {
        /* @Trace: EcuM_SUD_API_150 */
          SchM_Enter_EcuM_STATE_PROTECTION();
          /* Set Flex User Status to Mode RUNSTATUS_REQUESTED */
          EcuM_FlexUsers_POSTRUN_RequestStatus[i] =
            ECUM_RUNSTATUS_REQUESTED;
          SchM_Exit_EcuM_STATE_PROTECTION();

          /* return successful */
          stdRetVal = (Std_ReturnType)E_OK;

          /* If don't have any request POST_RUN until currently time */
          if((uint8)ECUM_RUNSTATUS_REQUESTED != EcuM_PostRunRequestStatus)
          {
            /* @Trace: EcuM_SUD_API_945 */
            SchM_Enter_EcuM_STATE_PROTECTION();
            EcuM_PostRunRequestStatus = (uint8)ECUM_RUNSTATUS_REQUESTED;
            EcuM_ModeHandlingChangeStatus = ECUM_TRUE;
            SchM_Exit_EcuM_STATE_PROTECTION();
          }
          else
          {
            /* Do nothing */
          }
      } /* End of if(EcuM_FlexUsers_POSTRUN_RequestStatus[i] is
         * ECUM_RUNSTATUS_REQUESTED) */
      /* Exit the loop for efficiency */
      break;
    } /* End of if(user is EcuM_FlexUsers[index]) */
    else
    {
      /* Do nothing */
    }
  } /* end of for(index = ECUM_ZERO; index < ECUM_NO_OF_USERS; index++) */
  /* if the user is invalid */
  if (validUserRequest != ECUM_TRUE)
  {
      /* @Trace: EcuM_SUD_API_944 */
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_REQUESTPOST_RUN_SID, ECUM_E_INVALID_PAR);
      #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
  }

  #else /* Else of if (STD_ON == ECUM_MODE_HANDLING) */
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  /* @Trace: EcuM_SUD_API_151 */
  /* Report to DET */
  (void)EcuM_DetReportError(ECUM_REQUESTPOST_RUN_SID,ECUM_E_SERVICE_DISABLED);
  #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */
  /* return error the request was not accepted */

  ECUM_UNUSED(user);
  #endif /* #if (STD_ON == ECUM_MODE_HANDLING) */

  return stdRetVal;
} /* End of EcuM_RequestPOST_RUN */

/*******************************************************************************
** Function Name        : EcuM_ReleasePOST_RUN                                **
**                                                                            **
** Service ID           : 0x0b                                                **
**                                                                            **
** Description          : Releases a RUN request previously done with a call  **
**                        to EcuM_RequestRUN. The service is intended for     **
**                        implementing AUTOSAR ports.                         **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_RunRequestStatus, EcuM_RunRequestStatus  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, BswM_RequestMode               **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09166 SRS_ModeMgm_09115 SRS_ModeMgm_09116
 * SRS_ModeMgm_09164 SRS_ModeMgm_09165 SRS_ModeMgm_09122 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ReleasePOST_RUN (EcuM_UserType user)
{
  /* Local variable for return value */
  Std_ReturnType stdRetVal;
  stdRetVal = (Std_ReturnType)E_NOT_OK;

  #if (STD_ON == ECUM_MODE_HANDLING)

  /*Local variable for index*/
  uint8 i;
  boolean isNotTheLastRelease = ECUM_FALSE;
  boolean validUserRequest = ECUM_FALSE;
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  /* Variables for check core Id */
  CoreIdType coreId;
  /* Local variable for master core result */
  coreId = GetCoreID();
  #endif
  for(i = ECUM_ZERO; i < ECUM_NO_OF_USERS; i++)
  {
    if((user == EcuM_FlexUsers[i].User)
    #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
    && (coreId == EcuM_FlexUsers[i].CoreId)
    #endif
    )
    {
      /* valid user */
      validUserRequest = ECUM_TRUE;
      /* @Trace: EcuM_SUD_API_183 */
      if(EcuM_FlexUsers_POSTRUN_RequestStatus[i] != ECUM_RUNSTATUS_REQUESTED)
      {
        #if (STD_ON == ECUM_DEV_ERROR_DETECT)
        /* Report to DET on releasing without a matching request.*/
        (void)EcuM_DetReportError(ECUM_RELEASEPOST_RUN_SID,
                                 ECUM_E_MISMATCHED_RUN_RELEASE);
        #endif
        stdRetVal = (Std_ReturnType)E_NOT_OK;
      }
      else
      {
         /* @Trace: EcuM_SUD_API_184 */
          SchM_Enter_EcuM_STATE_PROTECTION();
          /* set EcuM Post Run request status is Released */
          EcuM_FlexUsers_POSTRUN_RequestStatus[i] = ECUM_RUNSTATUS_RELEASED;
          SchM_Exit_EcuM_STATE_PROTECTION();
          /* set return value is E_OK */
          stdRetVal = (Std_ReturnType)E_OK;
      }
    } /* End of if(user is EcuM_FlexUsers[i]) */
    else
    {
     /*do nothing, check next userId*/
    }

    /* Check if the last release POST_RUN */
    if(ECUM_RUNSTATUS_REQUESTED == EcuM_FlexUsers_POSTRUN_RequestStatus[i])
    {
      /* @Trace: EcuM_SUD_API_943 */
      /* Keep the current request status*/
      isNotTheLastRelease = ECUM_TRUE;
    }
    else
    {

    }
  } /* End of for loop */

  /* @Trace: EcuM_SUD_API_185 */
  /* Is the last release*/
  if((ECUM_TRUE == validUserRequest)
    && (ECUM_FALSE == isNotTheLastRelease)
    && ((uint8)ECUM_RUNSTATUS_RELEASED != EcuM_PostRunRequestStatus))
  {
      SchM_Enter_EcuM_STATE_PROTECTION();
      EcuM_PostRunRequestStatus = (uint8)ECUM_RUNSTATUS_RELEASED;
      EcuM_ModeHandlingChangeStatus = ECUM_TRUE;
      SchM_Exit_EcuM_STATE_PROTECTION();
  }
  else if (ECUM_FALSE == validUserRequest)
  {
      /* @Trace: EcuM_SUD_API_942 */
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_RELEASEPOST_RUN_SID, ECUM_E_INVALID_PAR);
      #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */
      stdRetVal = (Std_ReturnType)E_NOT_OK;
  }
  else
  {

  }

  #else /* Else of if (STD_ON == ECUM_MODE_HANDLING) */
  /* @Trace: EcuM_SUD_API_215 */
  #if (STD_ON == ECUM_DEV_ERROR_DETECT)
  /* Report to DET */
  (void)EcuM_DetReportError(ECUM_RELEASEPOST_RUN_SID, ECUM_E_SERVICE_DISABLED);
  #endif /* #if (STD_ON == ECUM_DEV_ERROR_DETECT) */

  ECUM_UNUSED(user);
  #endif /* #if (STD_ON == ECUM_MODE_HANDLING) */

  return stdRetVal;
} /* End of EcuM_ReleasePOST_RUN */

/*******************************************************************************
** Function Name        : EcuM_SetState                                       **
**                                                                            **
** Service ID           : 0x2b                                                **
**                                                                            **
** Description          : Function called by BswM to notify about             **
**                        State Switch.                                       **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : state                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, BswM_EcuM_CurrentState         **
**                        Rte_Switch_EcuM_currentMode_currentMode             **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09122 SRS_ModeMgm_09116 SRS_ModeMgm_09009
 * SRS_ModeMgm_09116 */
FUNC(void, ECUM_CODE) EcuM_SetState(EcuM_ShutdownTargetType state)
{
  /* @Trace: EcuM_SUD_API_187 */
  if((state != ECUM_STATE_APP_POST_RUN) &&
    (state != ECUM_STATE_APP_RUN) &&
    (state != ECUM_STATE_SHUTDOWN) &&
    (state != ECUM_STATE_SLEEP) &&
    (state != ECUM_STATE_STARTUP))
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SETSTATE_SID, ECUM_E_STATE_PAR_OUT_OF_RANGE);
    #endif
  }
  /* @Trace: EcuM_SUD_API_188 */
  else
  {
    /* Set state */
    EcuM_State = state;

    /* Indicate the corresponding mode to the RTE */
    (void)Rte_Switch_currentMode_currentMode(state);

    /* Indicate the corresponding mode to the BswM */
    BswM_EcuM_CurrentState(state);
  }
} /* End of EcuM_SetState */

/*******************************************************************************
** Function Name        : EcuM_SetWakeupEvent                                 **
**                                                                            **
** Service ID           : 0x0C                                                **
**                                                                            **
** Description          : This routine is responsible for setting up off      **
**                        wakeup event. It takes the value and stores in the  **
**                        internal variable. This function must start the     **
**                        wakeup validation timeout timer.                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : sources                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)    :                             **
**                        EcuM_WakeupType, EcuM_AlarmCycle, EcuM_RunningTimer **
**                        EcuM_MasterAlarm, EcuM_SleepCycle, EcuM_AlarmExpired**
**                        EcuM_WakeupSource, EcuM_WakeupCounter,              **
**                        EcuM_WakeupStatus, EcuM_PendingWakeupEvents,        **
**                        EcuM_ValidatedWakeupEvents, EcuM_NextTick           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, ComM_EcuM_WakeUpIndication,    **
**                        BswM_EcuM_CurrentWakeup, EcuM_EndCheckWakeup        **
**                        EcuM_SearchSleepModeWakeupSource                    **
*******************************************************************************/

/* @Trace: SRS_BSW_00359 SRS_BSW_00360 SRS_BSW_00440 SRS_ModeMgm_09098
 * SRS_ModeMgm_09194 SRS_ModeMgm_09122 SRS_ModeMgm_09100 SRS_ModeMgm_09097
 * SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00350 SRS_BSW_00385 SRS_BSW_00333
 * SRS_EcuM_AR_00004 SRS_EcuM_AR_00011 */
FUNC(void, ECUM_CODE) EcuM_SetWakeupEvent(EcuM_WakeupSourceType sources)
{
  #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
  boolean alarmExpired;
  #endif
  uint8 sourceIndex;
  boolean searchResult;

  sourceIndex = (uint8)ECUM_ZERO;
  #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
  alarmExpired = FALSE;
  #endif

  /* @Trace: EcuM_SUD_API_212 */
  /* Is module not initialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    /* Report to DET */
    (void)EcuM_DetReportError(ECUM_SETWAKEUPEVENT_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  }

  /* Module is initialized */
  else
  {
    searchResult = EcuM_SearchSleepModeWakeupSource(&sourceIndex, sources);

    /* Is the reported event is an unknown event */
    if (searchResult == FALSE)
    {
      /* @Trace: EcuM_SUD_API_210 */
      SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
      EcuM_WakeupType = ECUM_WK_UNKNOWN;
      SchM_Exit_EcuM_ALARM_TIME_PROTECTION();

      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      /* Report to DET */
      (void)EcuM_DetReportError(ECUM_SETWAKEUPEVENT_SID,
        ECUM_E_UNKNOWN_WAKEUP_SOURCE);
      #endif
    }
    /* For Valid Wakeup event */
    else
    {
      /* If EcuM_SetWakeupEvent is called for the corresponding
      * wakeup source the CheckWakeupTimer is cancelled */

      EcuM_EndCheckWakeup(sources);
      #if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
      /* @Trace: EcuM_SUD_API_208 */
      /* When alarm is present and
       * the source is a alarm source or normal source */
      if (sources == ECUM_ALARM_WAKEUP_SOURCE_ID)
      {
        SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
        /* Update wakeup type value */
        EcuM_WakeupType = ECUM_WK_KNOWN_ALARM;
        /* Update alarm cycle */
        EcuM_AlarmCycle = TRUE;
        /* Update wakeup counter */
        EcuM_WakeupCounterTime++;
        if (EcuM_WakeupCounterTime == ECUM_WAKEUP_PERIOD)
        {
          /* Update running timer */
          EcuM_RunningTimer++;
          /* Clear wakeup counter */
          EcuM_WakeupCounterTime = (uint32)ECUM_ZERO;
        }
        if ((EcuM_RunningTimer >= EcuM_MasterAlarm) &&
            (EcuM_MasterAlarm != (uint32)ECUM_ZERO))
        {
          EcuM_AlarmExpired = TRUE;
          /* set flag alarm timer is expired */
          alarmExpired = TRUE;
          /* Clear master alarm */
          EcuM_MasterAlarm = (uint32)ECUM_ZERO;
        }
        SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
      }
      else
      {
        /* @Trace: EcuM_SUD_API_961 */
        SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
        EcuM_WakeupType = ECUM_WK_KNOWN;
        EcuM_SleepCycle = FALSE;
        EcuM_AlarmExpired = TRUE;
        SchM_Exit_EcuM_ALARM_TIME_PROTECTION();

        alarmExpired = TRUE;
      }

      if (TRUE == alarmExpired)
      #endif /* End of if (ECUM_ALARM_CLOCK_PRESENT == STD_ON) */
      {
        /* Is validation required */
        /* polyspace<RTE: OBAI : Not a defect : No Action Planned > index has
        been checked */
        /* @Trace: EcuM_SUD_API_209 */
        if (EcuM_WakeupSource[sourceIndex].WakeupValidationTimeOut
            != (uint16)ECUM_ZERO)
        {
          /* Is validation count zero */
          if (EcuM_WakeupCounter[sourceIndex] == (uint16)ECUM_ZERO)
          {
            if (EcuM_WakeupStatus[sourceIndex] != ECUM_WKSTATUS_PENDING)
            {
              /* To enable data protection */
              SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

              /* Update WakeupCounter with configured WakeupValidationCount */
              EcuM_WakeupCounter[sourceIndex] =
                EcuM_WakeupSource[sourceIndex].WakeupValidationTimeOut/((uint16)(ECUM_MAIN_FUNCTION_PERIOD * ECUM_CONVERT_S_TO_MS));

              /* Update Status of wakeup source as PENDING */
              EcuM_WakeupStatus[sourceIndex] = ECUM_WKSTATUS_PENDING;

              /* Update the pending wakeup events variable */
              EcuM_PendingWakeupEvents |= sources;

              /* To disable data protection */
              SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

              /* Indicate current status of Wakeup source to BswM */
              BswM_EcuM_CurrentWakeup(EcuM_WakeupSource[sourceIndex].WakeupSourceId,
                                      ECUM_WKSTATUS_PENDING);
            }
          } /* End of if (EcuM_WakeupCounter[sourceIndex] is ECUM_ZERO) */
        } /* End of if (EcuM_WakeupSource[sourceIndex].WakeupValidationTimeOut
           *!= ECUM_ZERO) */

        /* Validation Not Required */
        else
        {
          /* Redmine #1536 */
          /* polyspace<RTE: OBAI : Not a defect : No Action Planned > index has
          been checked */
          /* @Trace: EcuM_SUD_API_211 */
          if (EcuM_WakeupStatus[sourceIndex] != ECUM_WKSTATUS_VALIDATED)
          {
            /* To enable data protection */
            SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

            /* Update Status of wakeup source as VALIDATED */
            EcuM_WakeupStatus[sourceIndex] = ECUM_WKSTATUS_VALIDATED;

            /* Update the Validated event variable with sources */
            EcuM_ValidatedWakeupEvents |= sources;

            /* To disable data protection */
            SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

            /* Indicate current status of Wakeup source to BswM */
            BswM_EcuM_CurrentWakeup(EcuM_WakeupSource[sourceIndex].WakeupSourceId,
              ECUM_WKSTATUS_VALIDATED);
            /* polyspace-begin RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
            if (EcuM_WakeupSource[sourceIndex].ComMChannel !=
                ECUM_COMM_INVALID_CHANNEL)
            {
              /* Indicate the wakeup event to ComM */
              ComM_EcuM_WakeUpIndication
                ((NetworkHandleType)(EcuM_WakeupSource[sourceIndex].ComMChannel));
            }
            /* polyspace-end RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
          }
        } /* End of else */
      }
    }
  }
} /* End of EcuM_SetWakeupEvent */

/*******************************************************************************
** Function Name        : EcuM_ValidateWakeupEvent                            **
**                                                                            **
** Service ID           : 0x14                                                **
**                                                                            **
** Description          : EcuM_ValidateWakeupEvent() routine is responsible   **
**                        for validating all the WAKEUP events The validation **
**                        shall be valid when ANDing the parameter events with**
**                        the internal variable of pending wakeup events      **
**                        results in a value other than null.The service shall**
**                        invoke ComM_EcuM_WakeUpIndication of the            **
**                        Communication Manager for each event in the         **
**                        parameter, which is listed in the                   **
**                        ECUM_WKSOURCE_COMIF_XREF_LIST                       **
**                        configuration parameter.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : sources                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_InitStatus, EcuM_PendingWakeupEvents           **
**                        EcuM_State, EcuM_WakeupSource, EcuM_WakeupStatus    **
**                        EcuM_WakeupCounter, EcuM_ValidatedWakeupEvents      **
**                        EcuM_WakeupPncIndex                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        EcuM_DetReportError, EcuM_SearchWakeupSource,       **
**                        ComM_EcuM_WakeUpIndication, BswM_EcuM_CurrentWakeup **
**                        ComM_EcuM_PNCWakeUpIndication                       **
*******************************************************************************/

/* @Trace: SRS_BSW_00359 SRS_BSW_00360 SRS_BSW_00440 SRS_EcuM_AR_00004
 * SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_ModeMgm_09097 SRS_ModeMgm_09126
 * SRS_ModeMgm_09136 SRS_ModeMgm_09122 SRS_ModeMgm_09100 SRS_BSW_00350
 * SRS_BSW_00333 SRS_EcuM_AR_00011 */
FUNC(void, ECUM_CODE) EcuM_ValidateWakeupEvent(EcuM_WakeupSourceType sources)
{
  /* The variable index is used as index for WakeupSource structure array */
  uint8 sourceIndex;
  #if (ECUM_COMM_PNC_SUPPORT == STD_ON)
  /* Index value for check cluster request source */
  uint8 comMPncIndex;
  #endif
  
  /* The boolean variable checks whether the search result is TRUE or FALSE */
  boolean searchResult;

  /* @Trace: EcuM_SUD_API_143 */
  /* Is module uninitialized */
  if (ECUM_UNINITIALIZED == EcuM_InitStatus)
  {
    /* Report to DET */
    #if (STD_ON == ECUM_DEV_ERROR_DETECT)
    (void)EcuM_DetReportError(ECUM_VALIDATEWAKEUPEVENT_SID, ECUM_E_UNINIT);
    #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
  }


  /* Module is initialized */
  else
  {
    /* Get wakeup source exist or not */

    searchResult = EcuM_SearchWakeupSource(&sourceIndex, sources);
    /* @Trace: EcuM_SUD_API_144 */
    /* Is Wakeup Source unknown */
    if (FALSE == searchResult)
    {
      /* Report to DET */
      #if (STD_ON == ECUM_DEV_ERROR_DETECT)
      (void)EcuM_DetReportError(ECUM_VALIDATEWAKEUPEVENT_SID,
        ECUM_E_UNKNOWN_WAKEUP_SOURCE);
      #endif /* End of if (ECUM_DEV_ERROR_DETECT == STD_ON) */
    }

    /* Known wakeup source */
    else
    {
      /* Is WakeupStatus of wakeup source(s) PENDING */
      if ((EcuM_PendingWakeupEvents & sources) !=
         (EcuM_WakeupSourceType)ECUM_ZERO)
      {
        /* polyspace-begin RTE:OBAI [Not a defect:Low] "index is checked manual and it is not outside" */
        /* Is wakeup source a communication channel OR LblValidateFlag set */
        /* if ((EcuM_State != ECUM_STATE_APP_RUN) || */
        if ((EcuM_State != ECUM_STATE_STARTUP_TWO) ||
          (EcuM_WakeupSource[sourceIndex].ComMChannel !=
          ECUM_COMM_INVALID_CHANNEL))
        {
          /* Redmine #1536 */
          if (EcuM_WakeupStatus[sourceIndex] != ECUM_WKSTATUS_VALIDATED)
          {
            /* @Trace: EcuM_SUD_API_145 */
            /* To enable data protection */
            SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

            /* Update Status of wakeup source as VALIDATED */
            EcuM_WakeupStatus[sourceIndex] = ECUM_WKSTATUS_VALIDATED;

            /* Clear Validation Timeout Counter */
            EcuM_WakeupCounter[sourceIndex] = (uint16)ECUM_ZERO;
            /* Update the Validated event variable with sources */
            EcuM_ValidatedWakeupEvents |= sources;

            /* Clear wakeup event from pending list */
            EcuM_PendingWakeupEvents &= (EcuM_WakeupSourceType)(~sources);

            /* To disable data protection */
            SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();
            /* polyspace-begin RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
            /* @Trace: EcuM_SUD_API_146 */
            if (EcuM_WakeupSource[sourceIndex].ComMChannel !=
                ECUM_COMM_INVALID_CHANNEL)
            {
              /* Indicate the wakeup event to ComM */
              ComM_EcuM_WakeUpIndication
                ((NetworkHandleType)(EcuM_WakeupSource[sourceIndex].ComMChannel));
            }
            /* polyspace-end RTE:UNR */
            /* @Trace: EcuM_SUD_API_147 */
            /* EcuM_ValidateWakeupEvent shall
             * invoke ComM_EcuM_PNCWakeUpIndication */
            #if (ECUM_COMM_PNC_SUPPORT == STD_ON)
            if (EcuM_WakeupSource[sourceIndex].ptrComMPNCGroup != NULL_PTR)
            {
              /* polyspace-begin DEFECT:DEAD_CODE [Justified:Medium] "Reachable code by configuration change" */
              /* polyspace-begin MISRA-C3:2.1 [Justified:Medium] "Reachable code by configuration change" */
              /* polyspace-begin MISRA-C3:14.3 [Justified:Medium] "Reachable code by configuration change" */
              /* polyspace-begin RTE:IDP [Not a defect:Low] "the index of ptrComMPNCGroup is limited by the number of PnC using in each wakeupsource" */
              /* Indicate the wakeup event to ComMPNC */
              for(comMPncIndex=(uint8)ECUM_ZERO;
                  comMPncIndex < EcuM_WakeupPncIndex[sourceIndex]; comMPncIndex++)
              {
               ComM_EcuM_PNCWakeUpIndication((PNCHandleType)
               (EcuM_WakeupSource[sourceIndex].ptrComMPNCGroup[comMPncIndex]));
              }
              /* polyspace-end DEFECT:DEAD_CODE */
              /* polyspace-end MISRA-C3:2.1 */
              /* polyspace-end MISRA-C3:14.3 */
              /* polyspace-end RTE:IDP [Not a defect:Low] */
            }
            #endif
            /* @Trace: EcuM_SUD_API_148 */
            /* Indicate current status of Wakeup source to BswM */
            BswM_EcuM_CurrentWakeup(EcuM_WakeupSource[sourceIndex].WakeupSourceId,
              ECUM_WKSTATUS_VALIDATED);
          }
        } /* End of if ((EcuM_State != ECUM_STATE_STARTUP_TWO) ||
           *(EcuM_WakeupSource[sourceIndex].ComMChannel
           *!= ECUM_COMM_INVALID_CHANNEL))*/
      /* polyspace-end RTE:OBAI [Not a defect:Low] "index is checked manual and it is not outside" */
      } /* End of if ((EcuM_PendingWakeupEvents & sources) != ECUM_ZERO) */
    }
  }
} /* End of EcuM_ValidateWakeupEvent */

/*******************************************************************************
** Function Name        : EcuM_IsMasterCore                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Returns whether the current core is Master or not   **
**                                                                            **
** Sync/Async           : Sync                                                **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : TRUE - Master Core, FALSE - Slave Core              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_CoreID                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        GetCoreID()                                         **
*******************************************************************************/
FUNC(boolean, ECUM_CODE) EcuM_IsMasterCore(void)
{
  boolean isMasterCore;
  #if (STD_ON == ECUM_MULTI_CORE_SUPPORT)
  CoreIdType coreId;

  /* Get the core id of currently running core */
  coreId = GetCoreID();

  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Medium] "Reachable code by configuration change" */
  /* polyspace-begin MISRA-C3:2.1 [Justified:Medium] "Reachable code by configuration change" */
  /* polyspace-begin MISRA-C3:14.3 [Justified:Medium] "Reachable code by configuration change" */
  /* Array for Core ID
   * Master Core : EcuM_CoreID[0]
   * Slave Cores : EcuM_CoreID[1] ~ */
  /*  if (EcuM_CoreID[0] is CoreId) */
  if (OS_CORE_ID_MASTER == coreId)
  {
    isMasterCore = TRUE;
  }
  else
  {
    isMasterCore = FALSE;
  }
  /* polyspace-end DEFECT:DEAD_CODE */
  /* polyspace-end MISRA-C3:2.1 */
  /* polyspace-end MISRA-C3:14.3 */
  #else
  isMasterCore = TRUE;
  #endif

  return isMasterCore;
}

#define ECUM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* polyspace:end<RTE:UNR : Not a defect : Justify with annotations > Not a defect */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
