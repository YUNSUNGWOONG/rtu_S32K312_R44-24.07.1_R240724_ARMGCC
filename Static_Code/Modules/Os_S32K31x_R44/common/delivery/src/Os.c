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
**  SRC-MODULE: Os.c                                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Os API.                                          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.6.0     27-Mar-2024   HJ.Kim           Jira CP44-4643                    **
** 1.5.3     16-Feb-2024   HG.Kim           Jira CP44-3828                    **
** 1.5.1     06-Oct-2023   JC.Kim           Jira CP44-2438                    **
** 1.5.0     13-Sep-2023   HJ.Kim           Jira CP44-2459                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-1987                    **
**                                          Jira CP44-1772                    **
** 1.3.12.0  09-Mar-2023   TanHX            Jira CP44-1335                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.8     07-Oct-2020   DanhDC1          R44-Redmine #15959                **
**                                          Remove un-used function           **
** 1.0.7     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
** 1.0.6     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Add comment for Misra-C D4.5      **
** 1.0.5     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.4     13-Aug-2020   DanhDC1          R44-Redmine #15262                **
** 1.0.3     11-Aug-2020   DanhDC1          R44-Redmine #14813                **
**                                          Checking StartOs for              **
**                                          Resume/SupendOsInterrupt APIs     **
** 1.0.2     28-Jul-2020   DanhDC1          R44-Redmine #11180                **
**                                          Merge the TryToGetSpinLock() and  **
**                                          GetSpinLock() into one            **
** 1.0.1     22-Jun-2020   DanhDC1          #13809                            **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace:begin<MISRA-C:2.1:Not a defect:Justify with annotations> Coexistence of assembly is needed for readability  */
/* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "__mfcr(0xfe1c) always return a value less than 6" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "__mfcr(0xfe1c) always return a value less than 6" */
/* @Trace: SRS_Os_11016 */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os.h"
#include "Os_Kernel.h"
#include "Os_Task.h"
#include "Os_Alarm.h"
#include "Os_Multicore.h"
#include "Os_MulticoreMessage.h"
/* @Trace: SRS_BSW_00410 SRS_Os_11012 */
#include "Os_Error.h"
#include "Os_PortTypes.h"
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_TimingProtection.h" /* Os TimerProtection header file */
#endif
#include "Os_Interrupt.h"
#if (OS_APPLICATION == STD_ON)
#include "Os_IocInternalTypes.h"
#include "Os_Ioc.h"
#endif
#if ((OS_APPLICATION == STD_ON) || (OS_MEMORY_PROTECTION == STD_ON))
#include "Os_Application.h"
#endif
#if (OS_SPINLOCK == STD_ON)
#include "Os_Spinlock.h"
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_API_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#if (OS_ALARM == STD_ON)
/***************************************************************************//**
 * Function Name        : GetAlarmBase
 *
 * Service ID           : OSServiceId_GetAlarmBase
 *
 * Description          : This service is used to the alarm base
 *                        characteristics.
 *                        The return <Info> is a structure in
 *                        which the information of data type AlarmBaseType
 *                        is stored.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param [in]            AlarmID       Reference to an alarm
 *                                      (range : 0 ~ OS_ALARM_COUNT - 1)
 * @param [out]           Info          Reference to structure of the alarm base
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ID : AlarmID is invalid
 *                        - E_OS_PARAM_POINTER : Info is a NULL_PTR
 *                        - E_OS_ACCESS : Alarm is not accessible
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  :
 *                        Os_GaaStaticAlarm
 * 
 *                        Function(s) invoked : 
 *                        Os_GetCurPrivMode(), Os_SendGetAlarmBase(),
 *                        Os_DoGetAlarmBase(), Os_CallGetAlarmBase()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
/* polyspace +1 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace*/
FUNC(StatusType, OS_CODE) GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info)
{
  StatusType LddStatusReturn = E_OK;
  Os_OldLevel_T LddGlobalIE;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* Current privilege level is supervisor */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
    /* @Trace: SafeOs_SUD_API_06901 */
    LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

    /* Check whether interrupts are not disabled by user */
    OS_CHECK_INTERRUPT_LOCK(&LddStatusReturn);
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(GETALARMBASE, LddStatusReturn);
    /* Check whether AlarmID is greater than number of Alarm count */
    OS_CHECK_ALARM_ID_ERROR(AlarmID, LddStatusReturn);
    /* Check for NULL_PTR */
    OS_CHECK_NULL_PTR(Info, LddStatusReturn);
    /* Check whether Alarm can access the Application */
    OS_CHECK_ALARM_APPLICATION_ACCESS_SELF_CORE(LddStatusReturn, AlarmID);
    /* Check whether status return is E_OK */
    if (LddStatusReturn == E_OK)
    {
      #if (OS_MULTICORE == STD_ON)
      /* Check if new task belongs to same core */
      if (Os_GaaStaticAlarm[AlarmID].ddCoreID != OS_CORE_ID)
      {
        /* @Trace: SafeOs_SUD_API_06902 */
        /* Call Os_SendGetAlarmBase to schedule task on respective core */
        LddStatusReturn = Os_SendGetAlarmBase(AlarmID, Info);
      } /* End of if (Os_GaaStaticAlarm[AlarmID].ddCoreID != OS_CORE_ID) */
      else
      #endif /* End of if (OS_MULTICORE == STD_ON) */
      {
        /* @Trace: SafeOs_SUD_API_06903 */
        /* Call Os_DoGetAlarmBase */
        LddStatusReturn = Os_DoGetAlarmBase(AlarmID, Info, OS_FALSE);
      }
    } /* End of if (LddStatusReturn == E_OK) */
    #if (OS_STATUS == EXTENDED)
    if (LddStatusReturn != E_OK)
    {
      /* @Trace: SafeOs_SUD_API_06904 */
      /* Store the service ID of GetAlarmBase */
      /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      OS_STORE_SERVICE(OSServiceId_GetAlarmBase);
      /* Store the parameter 1 - AlarmID */
      OS_STORE_PARAM1_ALARMID(AlarmID);
      /* Store the parameter 2 - Info */
      OS_STORE_PARAM2_INFO(Info);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LddStatusReturn);
    } /* End of if (LddStatusReturn != E_OK) */
    #endif /* End of if (OS_STATUS == EXTENDED) */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	  /* @Trace : SafeOs_SUD_API_06905 */
	  OS_RESTORE_INTERRUPTS(LddGlobalIE);
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace: SafeOs_SUD_API_06906 */
    LddStatusReturn = Os_CallGetAlarmBase(AlarmID, Info);
  }
  #endif
  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : GetAlarm
 *
 * Service ID           : OSServiceId_GetAlarm
 *
 * Description          : The system service GetAlarm returns the value
 *                        in ticks before the alarm expires.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param [in]            AlarmID       Reference to an alarm
 *                                      (range : 0 ~ OS_ALARM_COUNT - 1)
 * @param [out]           Tick          Relative value in ticks before the alarm
 *                                      <AlarmID> expires.
 *                                      (range : 0 ~ MaxAllowdValue of Counter)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ID : AlarmID is invalid
 *                        - E_OS_PARAM_POINTER : Tick is a NULL_PTR
 *                        - E_OS_ACCESS : Alarm is not accessible
 *                        - E_OS_NOFUNC : Alarm is not used
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  :
 *                        Os_GaaAlarm
 * 
 *                        Function(s) invoked : 
 *                        Os_GetCurPrivMode(), Os_SendGetAlarm(),
 *                        Os_DoGetAlarm(), Os_CallGetAlarm()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
/* polyspace +1 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace*/
FUNC(StatusType, OS_CODE) GetAlarm(AlarmType AlarmID, TickRefType Tick)
{
  StatusType LddStatusReturn = E_OK;
  Os_OldLevel_T LddGlobalIE;
  #if (OS_MULTICORE == STD_ON)
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* Current privilege level is supervisor */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
    /* @Trace: SafeOs_SUD_API_07001 */
    LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

    /* Check whether interrupts are not disabled by user */
    OS_CHECK_INTERRUPT_LOCK(&LddStatusReturn);
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(GETALARM, LddStatusReturn);
    /* Check whether AlarmID is greater than number of Alarm count */
    OS_CHECK_ALARM_ID_ERROR(AlarmID, LddStatusReturn);
    /* Check for NULL_PTR */
    OS_CHECK_NULL_PTR(Tick, LddStatusReturn);
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "AlarmID index is checked by macro OS_CHECK_ALARM_ID_ERROR before using." */
    /* Check whether Alarm can access the Application */
    OS_CHECK_ALARM_APPLICATION_ACCESS_SELF_CORE(LddStatusReturn, AlarmID);
    
    /* Check whether status return is E_OK */
    if (LddStatusReturn == E_OK)
    {
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_07002 */
      /* Get the pointer to alarm structure */
      LpAlarm = &Os_GaaAlarm[AlarmID];

      /* Check if Alarm belongs to same core */
      if (LpAlarm->ddCoreId != OS_CORE_ID)
      {
        /* @Trace: SafeOs_SUD_API_07003 */
        /* Call Os_SendGetAlarm to get remain alarm ticks on respective core */
        LddStatusReturn = Os_SendGetAlarm(AlarmID, Tick);
      } /* End of if (LpAlarm->ddCoreId != OS_CORE_ID) */
      else
      #endif
      {
        /* @Trace: SafeOs_SUD_API_07004 */
        /* Call Os_DoGetAlarm and get the return value */
        LddStatusReturn = Os_DoGetAlarm(AlarmID, Tick, OS_FALSE);
      }
    } /* End of if (LddStatusReturn == E_OK) */
    #if (OS_STATUS == EXTENDED)
    if (LddStatusReturn != E_OK)
    {
      /* @Trace: SafeOs_SUD_API_07005 */
      /* Store the service ID of GetAlarm */
      /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      OS_STORE_SERVICE(OSServiceId_GetAlarm);
      /* Store the parameter 1 - AlarmID */
      OS_STORE_PARAM1_ALARMID(AlarmID);
      /* Store the parameter 2 - Tick */
      OS_STORE_PARAM2_TICK(Tick);
      /* Call Error Hook */
      OS_PROCESS_ERROR(LddStatusReturn);
    } /* End of if (LddStatusReturn != E_OK) */
    #endif /* End of if (OS_STATUS == EXTENDED) */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	  /* @Trace : SafeOs_SUD_API_07006 */
	  OS_RESTORE_INTERRUPTS(LddGlobalIE);
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace : SafeOs_SUD_API_07007 */
    LddStatusReturn = Os_CallGetAlarm(AlarmID, Tick);
  }
  #endif
  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : SetRelAlarm
 *
 * Service ID           : OSServiceId_SetRelAlarm
 *
 * Description          : This service is used to set the relative alarm.
 *                        After <increment> ticks have elapsed,
 *                        the task assigned to the alarm <AlarmID>
 *                        is activated or the assigned event
 *                        (only for extended tasks)
 *                        is set or the alarm-callback routine is called.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param [in]            AlarmID    Reference to an alarm
 *                                   (range : 0 ~ OS_ALARM_COUNT - 1)
 * @param [in]            Increment  Relative value in ticks
 *                                   (range : 1 ~ MaxAllowdValue of Counter)
 * @param [in]            Cycle      Cycle value in case of cyclic alarm. In
 *                                   case of single alarms, cycle shall be zero.
 *                                   (range : 0 ~ MaxAllowdValue of Counter)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ID : AlarmID is invalid
 *                        - E_OS_VALUE : Increment or Cycle is invalid
 *                        - E_OS_ACCESS : Alarm is not accessible
 *                        - E_OS_STATE : Alarm is already in use
 *                        - E_OS_SYS_ALARMINUSE : Counter interrupt is nested
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE)
SetRelAlarm(AlarmType AlarmID, TickType Increment, TickType Cycle)
{  
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_07101 */
  LddStatusReturn = OS_SYSCALL_SETRELALARM(AlarmID, Increment, Cycle);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : SetAbsAlarm
 *
 * Service ID           : OSServiceId_SetAbsAlarm
 *
 * Description          : This service is used to set the absolute alarm.
 *                        When <start> ticks are reached,
 *                        the configured action takes place.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param [in]            AlarmID    Reference to an alarm
 *                                   (range : 0 ~ OS_ALARM_COUNT - 1)
 * @param [in]            Start      Absolute value in ticks
 *                                   (range : 0 ~ MaxAllowdValue of Counter)
 * @param [in]            Cycle      Cycle value in case of cyclic alarm. In
 *                                   case of single alarms, cycle shall be zero.
 *                                   (range : 0 ~ MaxAllowdValue of Counter)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ID : AlarmID is invalid
 *                        - E_OS_VALUE : Start or Cycle is invalid
 *                        - E_OS_ACCESS : Alarm is not accessible
 *                        - E_OS_STATE : Alarm is already in use
 *                        - E_OS_SYS_ALARMINUSE : Counter interrupt is nested
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE)
SetAbsAlarm(AlarmType AlarmID, TickType Start, TickType Cycle)
{  
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_07201 */
  LddStatusReturn = OS_SYSCALL_SETABSALARM(AlarmID, Start, Cycle);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : CancelAlarm
 *
 * Service ID           : OSServiceId_CancelAlarm
 *
 * Description          : This service is used to cancel the alarm
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param [in]            AlarmID       Reference to an alarm
 *                                      (range : 0 ~ OS_ALARM_COUNT - 1)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ID : AlarmID is invalid
 *                        - E_OS_ACCESS : Alarm is not accessible
 *                        - E_OS_NOFUNC : Alarm is already Sleep
 *                        - E_OS_SYS_ALARMINUSE : Counter interrupt is nested
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  :
 *                        Os_GaaAlarm
 * 
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_SendCancelAlarm(),
 *                        Os_DoCancelAlarm(), Os_CallCancelAlarm()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE) CancelAlarm(AlarmType AlarmID)
{
  StatusType LddStatusReturn = E_OK;
  Os_OldLevel_T LddGlobalIE;
  #if (OS_MULTICORE == STD_ON)
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* Current privilege level is supervisor */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
    /* @Trace: SafeOs_SUD_API_07301 */
    LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

    /* Check whether interrupts are not disabled by user */
    OS_CHECK_INTERRUPT_LOCK(&LddStatusReturn);
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(CANCELALARM, LddStatusReturn);
    /* Check whether AlarmID is greater than number of Alarm count */
    OS_CHECK_ALARM_ID_ERROR(AlarmID, LddStatusReturn);
    /* Check whether Alarm can access the Application */
    OS_CHECK_ALARM_APPLICATION_ACCESS_SELF_CORE(LddStatusReturn, AlarmID);
    /* Check whether status return is E_OK */
    if (LddStatusReturn == E_OK)
    {
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_07302 */
      /* Get the pointer to static alarm structure */
      LpAlarm = &Os_GaaAlarm[AlarmID];

      /* Check if Alarm belongs to same core */
      if (LpAlarm->ddCoreId != OS_CORE_ID)
      {
        /* @Trace: SafeOs_SUD_API_07303 */
        /* Call Os_SendCancelAlarm to cancel alarm on respective core */
        LddStatusReturn = Os_SendCancelAlarm(AlarmID);
      } /* End of if (LpAlarm->ddCoreId != OS_CORE_ID) */
      else
      #endif
      {
        /* @Trace: SafeOs_SUD_API_07304 */
        /* Call Os_DoCancelAlarm and get the return value */
        LddStatusReturn = Os_DoCancelAlarm(AlarmID, OS_FALSE);
      }
    } /* End of if (LddStatusReturn == E_OK) */
    #if (OS_STATUS == EXTENDED)
    if (LddStatusReturn != E_OK)
    {
      /* @Trace: SafeOs_SUD_API_07305 */
      /* Store the service Id of CancelAlarm */
      /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      OS_STORE_SERVICE(OSServiceId_CancelAlarm);
      /* Store the parameter 1 - AlarmID */
      OS_STORE_PARAM1_ALARMID(AlarmID);
      /* Call Error Hook */
      OS_PROCESS_ERROR(LddStatusReturn);
    } /* End of if (LddStatusReturn != E_OK) */
    #endif /* End of if (OS_STATUS == EXTENDED) */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	  /* @Trace: SafeOs_SUD_API_07306 */
	  OS_RESTORE_INTERRUPTS(LddGlobalIE);
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace: SafeOs_SUD_API_07307 */
    LddStatusReturn = Os_CallCancelAlarm(AlarmID);
  }
  #endif
  return LddStatusReturn;
}

#endif /* (OS_ALARM == STD_ON) */

#if (OS_APPLICATION == STD_ON)

/***************************************************************************//**
 * Function Name        : GetApplicationID
 *
 * Service ID           : OSServiceId_GetApplicationID
 *
 * Description          : This Service returns the ID of running application.
 *
 * Sync/Async           : Synchronous
 *
 * Parameters           : None
 *
 * @return              : ApplicationType
 *                        - 0 ~ OS_APPLICATION_COUNT - 1 : No error
 *                        - INVALID_OSAPPLICATION : Interrupts are disabled
 *                          by user or it is called from wrong context
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_80005 SRS_Os_80015 SRS_Os_80016 */
/* polyspace +1 CODE-METRIC:calling [Justified:Low] "The display of specific values of the number of calling is justified" */
FUNC(ApplicationType, OS_CODE) GetApplicationID(void)
{
  ApplicationType LddApplicationID = INVALID_OSAPPLICATION;
  /* @Trace : SafeOs_SUD_API_16701 */
  LddApplicationID = OS_SYSCALL_GETAPPLICATIONID();

  return LddApplicationID;
}

/***************************************************************************//**
 * Function Name        : GetCurrentApplicationID
 *
 * Service ID           : OSServiceId_GetCurrentApplicationID
 *
 * Description          : This Service returns the ID of caller is currently
 *                        excuting.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Parameters           : None
 *
 * @return              : ApplicationType
 *                        - 0 ~ OS_APPLICATION_COUNT - 1 : No error
 *                        - INVALID_OSAPPLICATION : Error
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80005 SRS_Os_80015 SRS_Os_80016 */
FUNC(ApplicationType, OS_CODE) GetCurrentApplicationID(void)
{
  ApplicationType LddCurrentApplicationID = INVALID_OSAPPLICATION;
  /* @Trace : SafeOs_SUD_API_16801 */
  LddCurrentApplicationID = OS_SYSCALL_GETCURRENTAPPLICATIONID();

  return LddCurrentApplicationID;
}

/***************************************************************************//**
 * Function Name        : CheckObjectOwnership
 *
 * Service ID           : OSServiceId_CheckObjectOwnership
 *
 * Description          : This Service returns owner of the Object.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             ObjectType  Type of the following parameter
 *                                    (range : OBJECT_TASK, OBJECT_ISR,
 *                                     OBJECT_ALARM, OBJECT_RESOURCE,
 *                                     OBJECT_COUNTER, OBJECT_SCHEDULETABLE)
 * @param[in]             ObjectID    The object to be examined
 *                                    (range : 0 ~ 0xFFFFFFFF)
 *
 * @return              : ApplicationType
 *                        - 0 ~ OS_APPLICATION_COUNT - 1
 *                        - INVALID_OSAPPLICATION :
 *                            Interrupts are disabled by user or
 *                            It is called from wrong context or
 *                            <ObjectType> is not valid
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_80005 SRS_Os_80015 SRS_Os_80016 */
FUNC(ApplicationType, OS_CODE) CheckObjectOwnership
    (ObjectTypeType ObjectType, ObjectTypeIndex ObjectID)
{
  ApplicationType LddApplicationID = INVALID_OSAPPLICATION;
  /* @Trace : SafeOs_SUD_API_17301 */
  LddApplicationID = OS_SYSCALL_CHECKOBJECTOWNERSHIP(ObjectType, ObjectID);

  return LddApplicationID;
}

#if (OS_SCALABILITY_CLASS >= OS_SC3)
/***************************************************************************//**
 * Function Name        : CheckObjectAccess
 *
 * Service ID           : OSServiceId_CheckObjectAccess
 *
 * Description          : This Service checks whether access can be granted
 *                        to the application for the specified Object.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             ApplID      OS-Application identifier
 *                                    (range : 0 ~ OS_APPLICATION_COUNT - 1)
 * @param[in]             ObjectType  Type of the following parameter
 *                                    (range : OBJECT_TASK, OBJECT_ISR,
 *                                     OBJECT_ALARM, OBJECT_RESOURCE,
 *                                     OBJECT_COUNTER, OBJECT_SCHEDULETABLE)
 * @param[in]             ObjectID    The object to be examined
 *                                    (range : 0 ~ 0xFFFFFFFF)
 *
 * @return              : ObjectAccessType
 *                        - ACCESS: If the ApplID has access to the object
 *                        - NO_ACCESS: If the ApplID has no access to the object
 *                                     or Interrupts are disabled by user or
 *                                     It is called from wrong context or
 *                                     <ApplID> or <ObjectType> is not valid
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_80005 SRS_Os_80015 SRS_Os_80016 */
FUNC(ObjectAccessType, OS_CODE) CheckObjectAccess
    (ApplicationType ApplID,
     ObjectTypeType ObjectType, ObjectTypeIndex ObjectID)
{
  ObjectAccessType LddAccessReturn = NO_ACCESS;
  /* @Trace : SafeOs_SUD_API_17201 */
  LddAccessReturn = OS_SYSCALL_CHECKOBJECTACCESS(ApplID, ObjectType, ObjectID);

  return LddAccessReturn;
}

/***************************************************************************//**
 * Function Name        : TerminateApplication
 *
 * Service ID           : OSServiceId_TerminateApplication
 *
 * Description          : This Service Terminates the specified application.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             Application   The identifier of the OS-Application to
 *                                      be terminated. If the caller belongs to
 *                                      <Application> the call results in a self
 *                                      termination.
 *                                      (range : 0 ~ OS_APPLICATION_COUNT - 1)
 * @param[in]             RestartOption Either RESTART for doing a restart of
 *                                      the OS-Application or NO_RESTART if
 *                                      OS-Application shall not be restarted.
 *                                      (range : RESTART, NO_RESTART)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ID : <Application> was not valid
 *                        - E_OS_VALUE : <RestartOption> was not valid
 *                        - E_OS_STATE : The state of <Application> does not
 *                                       allow terminating <Application>
 *                        - E_OS_LIMIT : RestartTask already activated
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE) TerminateApplication
    (ApplicationType Application, RestartType RestartOption)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_17001 */
  LddStatusReturn = OS_SYSCALL_TERMINATEAPPLICATION(Application, RestartOption);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : AllowAccess
 *
 * Service ID           : OSServiceId_AllowAccess
 *
 * Description          : This Service checks if access is to be granted
 *                        for application.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Parameters           : None
 *
 * @return              : StatusType
 *                        - E_OK : No errors
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_STATE : The OS-Application of the caller is
 *                          in the wrong state
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80005 SRS_Os_80015 SRS_Os_80016 */
FUNC(StatusType, OS_CODE) AllowAccess(void)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_17101 */
  LddStatusReturn = OS_SYSCALL_ALLOWACCESS();

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : GetApplicationState
 *
 * Service ID           : OSServiceId_GetApplicationState
 *
 * Description          : This Service is used to get the application state
 *                        from the given Application ID.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             Application    The OS-Application from which the
 *                                       state is requested
 *                                       (range : 0 ~ OS_APPLICATION_COUNT - 1)
 * @param[out]            Value          The current state of the application
 *                                       (range : APPLICATION_ACCESSIBLE,
 *                                                APPLICATION_RESTARTING,
 *                                                APPLICATION_TERMINATED)
 *
 * @return              : StatusType
 *                        - E_OK : No errors
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ID : <Application> is not valid
 *                        - E_OS_PARAM_POINTER : Value is a NULL_PTR
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80005 SRS_Os_80015 SRS_Os_80016 */
/* polyspace +2 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace*/
FUNC(StatusType, OS_CODE) GetApplicationState
    (ApplicationType Application, ApplicationStateRefType Value)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_16901 */
  LddStatusReturn = OS_SYSCALL_GETAPPLICATIONSTATE(Application, Value);

  return LddStatusReturn;
}

#endif /* End of if (OS_SCALABILITY_CLASS >= OS_SC3) */

#if (OS_MEMORY_PROTECTION == STD_ON)

#if ((OS_SCALABILITY_CLASS != OS_SC3) && (OS_SCALABILITY_CLASS != OS_SC4))
#error "Os.c: Memory protection services supported in SC3 and SC4"
#endif

/***************************************************************************//**
 * Function Name        : CallTrustedFunction
 *
 * Service ID           : OSServiceId_CallTrustedFunction
 *
 * Description          : This service shall switch the processor into
 *                        privileged mode AND shall call the function
 *                        <FunctionIndex> out of a list of implementation
 *                        specific trusted functions.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             FunctionIndex  Index of the function to be called
 *                                       (range : 0 ~ OS_TRUSTED_FUNC_COUNT - 1)
 * @param[in]             FunctionParams Pointer to the parameters for the
 *                                       function - specified by the
 *                                       FunctionIndex - to be called.
 *                                       If no parameters are provided, a NULL
 *                                       pointer has to be passed.
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_SERVICEID : No function defined for this index
 *                        - E_OS_ACCESS : The Target trusted function is part of
 *                                        an OS-Application on another core
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
#if (OS_TRUSTED_FUNC_COUNT != OS_ZERO)
FUNC(StatusType, OS_CODE) CallTrustedFunction
    (TrustedFunctionIndexType FunctionIndex,
     TrustedFunctionParameterRefType FunctionParams)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_15301 */
  LddStatusReturn =
                  OS_SYSCALL_CALLTRUSTEDFUNCTION(FunctionIndex, FunctionParams);

  return LddStatusReturn;
}
#endif /* (OS_TRUSTED_FUNC_COUNT != OS_ZERO) */

/***************************************************************************//**
 * Function Name        : CheckISRMemoryAccess
 *
 * Service ID           : OSServiceId_CheckISRMemoryAccess
 *
 * Description          : This service checks if a memory region is write
 *                        read/execute accessible and also returns information**
 *                        if the memory region is part of the stack space.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             IsrID    CAT2 ISR reference
 *                                 (range : OS_TASK_COUNT + OS_CORE_COUNT ~
 *                                          OS_TASK_COUNT + OS_CORE_COUNT
 *                                          + OS_CAT2_ISR_COUNT - 1)
 * @param[in]             Address  Start of memory area
 *                                 (range : 0u ~ 0xFFFFFFFFu)
 * @param[in]             Size     Size of memory area
 *                                 (range : 0u ~ 0xFFFFFFFFu)
 *
 * @return              : AccessType
 *                        - OS_READ_ONLY
 *                        - OS_READ_WRITE
 *                        - OS_EXECUTE
 *                        - NO_ACCESS : Interrupts are disabled by user or
 *                                      It is called from wrong context or
 *                                      <IsrID> is not valid
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* polyspace +3 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace*/
/* @Trace: SRS_Os_11005 SRS_Os_11006 SRS_Os_11007 SRS_Os_11000 */
FUNC(AccessType, OS_CODE) CheckISRMemoryAccess
    (ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size)
{
  AccessType LddAccessReturn = NO_ACCESS;
  /* @Trace : SafeOs_SUD_API_14401 */
  LddAccessReturn = OS_SYSCALL_CHECKISRMEMORYACCESS(ISRID, Address, Size);

  return LddAccessReturn;
}

/***************************************************************************//**
 * Function Name        : CheckTaskMemoryAccess
 *
 * Service ID           : OSServiceId_CheckTaskMemoryAccess
 *
 * Description          : This service checks if a memory region is write
 *                        read/execute accessible and also returns information**
 *                        if the memory region is part of the stack space.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             TaskID   Task reference
 *                                 (range : 0 ~ OS_TASK_COUNT
 *                                              + OS_CORE_COUNT - 1)
 * @param[in]             Address  Start of memory area
 *                                 (range : 0u ~ 0xFFFFFFFFu)
 * @param[in]             Size     Size of memory area
 *                                 (range : 0u ~ 0xFFFFFFFFu)
 *
 * @return              : AccessType
 *                        - OS_READ_ONLY
 *                        - OS_READ_WRITE
 *                        - OS_EXECUTE
 *                        - NO_ACCESS : Interrupts are disabled by user or
 *                                      It is called from wrong context or
 *                                      <TaskID> is not valid
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_CheckMemoryAccessService(),
 *                        Os_CallCheckTaskMemoryAccess()
 ******************************************************************************/
/* @Trace: SRS_Os_11005 SRS_Os_11006 SRS_Os_11007 SRS_Os_11000 */
/* polyspace +2 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace*/
FUNC(AccessType, OS_CODE) CheckTaskMemoryAccess
    (TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size)
{
  AccessType LddAccessReturn = NO_ACCESS;
  StatusType LddStatusReturn = E_OK;
  Os_OldLevel_T LddGlobalIE;

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* Current privilege level is supervisor */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
    /* @Trace: SafeOs_SUD_API_14301 */
    LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();
    
    /* Check whether interrupts are not disabled by user */
    OS_CHECK_INTERRUPT_LOCK(&LddStatusReturn);
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(CHECKTASKMEMORYACCESS, LddStatusReturn);
    /* Check whether TaskID is correct */
    OS_CHECK_TASK_ID_ERROR(TaskID, LddStatusReturn);
    /* Check for NULL_PTR */
    OS_CHECK_NULL_PTR(Address, LddStatusReturn);

    /* Check if LddStatusReturn is E_OK */
    if (LddStatusReturn == E_OK)
    {
      /* @Trace: SafeOs_SUD_API_14302 */
      /* Call Os_CheckMemoryAccessService */
      LddAccessReturn = Os_CheckMemoryAccessService((ObjectTypeType)TaskID, Address, Size);
    }    
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	  /* @Trace : SafeOs_SUD_API_14303 */
	  OS_RESTORE_INTERRUPTS(LddGlobalIE);
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace : SafeOs_SUD_API_14304 */
    LddAccessReturn = Os_CallCheckTaskMemoryAccess(TaskID, Address, Size);
  }
  #endif
  return LddAccessReturn;
}

#endif /* (OS_MEMORY_PROTECTION == STD_ON) */
#endif /* (OS_APPLICATION == STD_ON) */

#if (OS_COUNTER == STD_ON)

/***************************************************************************//**
 * Function Name        : IncrementCounter
 *
 * Service ID           : OSServiceId_IncrementCounter
 *
 * Description          : IncrementCounter() increments
 *                        the counter <CounterID> by one and returns E_OK.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             CounterID  The Counter to be incremented
 *                                   (range : 0 ~ OS_COUNTER_COUNT - 1)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ID : The CounterID was not valid or counter is
 *                                    implemented in hardware and can not be
 *                                    incremented by software
 *                        - E_OS_CORE : Called with parameters that require
 *                                      a cross core operation
 *                        - E_OS_ACCESS : Counter is not accessible
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11020 SRS_Os_11021 */
FUNC(StatusType, OS_CODE) IncrementCounter(CounterType CounterID)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_10401 */
  LddStatusReturn = OS_SYSCALL_INCREMENTCOUNTER(CounterID);

  return LddStatusReturn;
}


/***************************************************************************//**
 * Function Name        : GetCounterValue
 *
 * Service ID           : OSServiceId_GetCounterValue
 *
 * Description          : This service is used to get the current value of
 *                        a counter.CounterId is the input parameter value,
 *                        is a reference (pointer) to the variable
 *                        where the value of the counter is stored.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             CounterID  The Counter which tick value should be read
 *                                   (range : 0 ~ OS_COUNTER_COUNT - 1)
 * @param[out]            Value      Contains the current tick value
 *                                   (range : 0 ~ MaxAllowdValue of Counter)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ID : The <CounterID> was not valid
 *                        - E_OS_PARAM_POINTER : <Value> is a NULL_PTR
 *                        - E_OS_ACCESS : Counter is not accessible
 *                        - E_OS_SYS_ALARMINUSE : Counter interrupt is nested
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Frt_00025 */
/* polyspace +2 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace*/
FUNC(StatusType, OS_CODE) GetCounterValue
    (CounterType CounterID, TickRefType Value)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_10301 */
  LddStatusReturn = OS_SYSCALL_GETCOUNTERVALUE(CounterID, Value);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : GetElapsedValue
 *
 * Service ID           : OSServiceId_GetElapsedValue
 *
 * Description          : This service is used to get the elapsed value
 *                        of a counter.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             CounterID    The Counter to be read
 *                                     (range : 0 ~ OS_COUNTER_COUNT - 1)
 * @param[in,out]         Value        in: the previously read tick value
 *                                     out: the current tick value
 *                                     (range : 0 ~ MaxAllowdValue of Counter)
 * @param[out]            ElapsedValue The difference to the previous read value
 *                                     (range : 0 ~ MaxAllowdValue of Counter)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ID : The <CounterID> was not valid
 *                        - E_OS_PARAM_POINTER : <Value> or <ElapsedValue>
 *                                               is a NULL_PTR
 *                        - E_OS_VALUE : The given <Value> was not valid
 *                        - E_OS_ACCESS : Counter is not accessible
 *                        - E_OS_SYS_ALARMINUSE : Counter interrupt is nested
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Frt_00025 */
/* polyspace +2 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace*/
FUNC(StatusType, OS_CODE) GetElapsedValue
    (CounterType CounterID, TickRefType Value, TickRefType ElapsedValue)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_10501 */
  LddStatusReturn = OS_SYSCALL_GETELAPSEDVALUE(CounterID, Value, ElapsedValue);

  return LddStatusReturn;
}

#endif /* (OS_COUNTER == STD_ON) */

#if (OS_EVENT == STD_ON)

/***************************************************************************//**
 * Function Name        : SetEvent
 *
 * Service ID           : OSServiceId_SetEvent
 *
 * Description          : This service is used to Set the events
 *                        of task <TaskID> according to the event mask <Mask>
 *                        Calling SetEvent causes the task <TaskID>
 *                        to be transferred to the ready state,
 *                        if it was waiting for at least one of the events
 *                        specified in <Mask>.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             TaskID    Reference to the task for which one or
 *                                  several events are to be set.
 *                                  (range : 0 ~ OS_TASK_COUNT
 *                                               + OS_CORE_COUNT - 1)
 * @param[in]             Mask      Mask of the events to be set
 *                                  (range : 0 ~ 0xFFFFFFFF)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ID : Task <TaskID> is invalid
 *                        - E_OS_ACCESS : Referenced task is no extended task
 *                                        or Task is not accessible
 *                        - E_OS_STATE : Events can not be set as the referenced
 *                                       task is in the suspended state
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE) SetEvent(TaskType TaskID, EventMaskType Mask)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_05701 */
  LddStatusReturn = OS_SYSCALL_SETEVENT(TaskID, Mask);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : SetEventAsyn
 *
 * Service ID           : 0x34
 *
 * Description          : Asynchronous version of the SetEvent() function.
 *                          Intended to be used for cross core event setting.
 *                        Possible errors are not returned to the caller,
 *                          but may be reported via error hooks.
 *
 * Sync/Async           : ASynchronous
 *
 * Re-entrancy          : Reentrant
 *
 * @param[in]             TaskID    Reference to the task for which one or
 *                                  several events are to be set.
 *                                  (range : 0 ~ OS_TASK_COUNT
 *                                               + OS_CORE_COUNT - 1)
 * @param[in]             Mask      Mask of the events to be set
 *                                  (range : 0 ~ 0xFFFFFFFF)
 *
 * @return              : void
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_80015 */
FUNC(void, OS_CODE) SetEventAsyn(TaskType TaskID, EventMaskType Mask)
{
  /* @Trace : SafeOs_SUD_API_06101 */
  OS_SYSCALL_SETEVENTASYN(TaskID, Mask);
}

/***************************************************************************//**
 * Function Name        : ClearEvent
 *
 * Service ID           : OSServiceId_ClearEvent
 *
 * Description          : The events of the extended task calling ClearEvent
 *                        are cleared according to the event mask <Mask>.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             Mask      Mask of the events to be cleared
 *                                  (range : 0 ~ 0xFFFFFFFF)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ACCESS : Call not from extended task
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
/* polyspace +1 CODE-METRIC:calling [Justified:Low] "The display of specific values of the number of calling is justified" */
FUNC(StatusType, OS_CODE) ClearEvent(EventMaskType Mask)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_05801 */
  LddStatusReturn = OS_SYSCALL_CLEAREVENT(Mask);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : GetEvent
 *
 * Service ID           : OSServiceId_GetEvent
 *
 * Description          : This service returns the current state of all event
 *                        bits of the task.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             TaskID    Task whose event mask is to be returned
 *                                  (range : 0 ~ OS_TASK_COUNT
 *                                               + OS_CORE_COUNT - 1)
 * @param[out]            Event     Reference to the memory of the return data
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ID : Task <TaskID> is invalid
 *                        - E_OS_ACCESS : Referenced task is no extended task
 *                                        or Task is not accessible
 *                        - E_OS_PARAM_POINTER : <Event> is a NULL_PTR
 *                        - E_OS_STATE : Referenced task <TaskID> is in the
 *                                       suspended state
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
/* polyspace +1 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace*/
FUNC(StatusType, OS_CODE) GetEvent(TaskType TaskID, EventMaskRefType Event)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_05901 */
  LddStatusReturn = OS_SYSCALL_GETEVENT(TaskID, Event);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : WaitEvent
 *
 * Service ID           : OSServiceId_WaitEvent
 *
 * Description          : The state of the calling task is set to waiting
 *                        unless at least one of the events specified
 *                        in <Mask> has already been set.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param[in]             Mask      Mask of the events waited for
 *                                  (range : 0 ~ 0xFFFFFFFF)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_DISABLEDINT : Interrupts are disabled by user
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ACCESS : Calling task is not an extended task
 *                        - E_OS_RESOURCE : Calling task occupies resources
 *                        - E_OS_SPINLOCK : Calling task occupies spinlock
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
/* polyspace +1 CODE-METRIC:calling [Justified:Low] "The display of specific values of the number of calling is justified" */
FUNC(StatusType, OS_CODE) WaitEvent(EventMaskType Mask)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_06001 */
  LddStatusReturn = OS_SYSCALL_WAITEVENT(Mask);

  return LddStatusReturn;
}

#endif /*(OS_EVENT == STD_ON) */

/***************************************************************************//**
 * Function Name        : EnableAllInterrupts
 *
 * Service ID           : OSServiceId_EnableAllInterrupts
 *
 * Description          : This function is called to Enable All interrupts.
 *                        The function does not cause a de-scheduling.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)  : N/A
 *
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_ArchEnableAllInterrupts()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80013 */
FUNC(void, OS_CODE) EnableAllInterrupts(void)
{
  /* @Trace : SafeOs_SUD_API_04101 */
  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* @Trace : SafeOs_SUD_API_04102 */
    /* Current privilege level is supervisor */
	  Os_ArchEnableAllInterrupts();
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
	  /* @Trace : SafeOs_SUD_API_04103 */
	  /* Current privilege level is not supervisor. Use system call! */
	  OS_SYSCALL_ENABLEALLINTERRUPTS();
  }
  #endif
  #endif
}

/***************************************************************************//**
 * Function Name        : DisableAllInterrupts
 *
 * Service ID           : OSServiceId_DisableAllInterrupts
 *
 * Description          : This function is called to Disable All interrupts.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)  : N/A
 *
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_ArchDisableAllInterrupts()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80013 */
FUNC(void, OS_CODE) DisableAllInterrupts(void)
{
  /* @Trace : SafeOs_SUD_API_04201 */
  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* @Trace : SafeOs_SUD_API_04202 */
    /* Current privilege level is supervisor */
    Os_ArchDisableAllInterrupts();
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
	  /* @Trace : SafeOs_SUD_API_04203 */
	  /* Current privilege level is not supervisor. Use system call! */
	  OS_SYSCALL_DISABLEALLINTERRUPTS();
  }
  #endif
  #endif
}

/***************************************************************************//**
 * Function Name        : ResumeAllInterrupts
 *
 * Service ID           : OSServiceId_ResumeAllInterrupts
 *
 * Description          : This function is called to Resume All interrupts.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)  : N/A
 *
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_ArchResumeAllInterrupts()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11018 SRS_Os_80013 */
/* polyspace +1 CODE-METRIC:calling [Justified:Low] "The display of specific values of the number of calling is justified" */
FUNC(void, OS_CODE) ResumeAllInterrupts(void)
{
  /* @Trace : SafeOs_SUD_API_04301 */
  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* @Trace : SafeOs_SUD_API_04302 */
    /* Current privilege level is supervisor */
    Os_ArchResumeAllInterrupts();
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace : SafeOs_SUD_API_04303 */
    /* Current privilege level is not supervisor. Use system call! */
    OS_SYSCALL_RESUMEALLINTERRUPTS();
  }
  #endif
  #endif
}

/***************************************************************************//**
 * Function Name        : SuspendAllInterrupts
 *
 * Service ID           : OSServiceId_SuspendAllInterrupts
 *
 * Description          : This function is called to Suspend All interrupts.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)  : N/A
 *
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_ArchSuspendAllInterrupts()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11018 SRS_Os_80013 */
/* polyspace +1 CODE-METRIC:calling [Justified:Low] "The display of specific values of the number of calling is justified" */
FUNC(void, OS_CODE) SuspendAllInterrupts(void)
{
  /* @Trace : SafeOs_SUD_API_04401 */
  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* @Trace : SafeOs_SUD_API_04402 */
    /* Current privilege level is supervisor */
    Os_ArchSuspendAllInterrupts();
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace : SafeOs_SUD_API_04403 */
    /* Current privilege level is not supervisor. Use system call! */
    OS_SYSCALL_SUSPENDALLINTERRUPTS();
  }
  #endif
  #endif
}

/***************************************************************************//**
 * Function Name        : ResumeOSInterrupts
 *
 * Service ID           : OSServiceId_ResumeOSInterrupts
 *
 * Description          : This function is called to Resume CAT2 interrupts.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)  : N/A
 *
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_ArchResumeOSInterrupts()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80013 */
FUNC(void, OS_CODE) ResumeOSInterrupts(void)
{
  /* @Trace : SafeOs_SUD_API_04501 */
  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  #if (OS_STATUS == EXTENDED)
  /* @Trace : SafeOs_SUD_API_04502 */
  StatusType LddStatusReturn;

  /* Init status return */
  LddStatusReturn = E_OK;
  #endif

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* @Trace : SafeOs_SUD_API_04503 */
    /* Current privilege level is supervisor */
    /* Check whether Os started or not */
    OS_CHECK_NOT_STARTOS(&LddStatusReturn);

    #if (OS_STATUS == EXTENDED)
    /* No error */
    if (LddStatusReturn == E_OK)
    #endif
    {
      /* @Trace : SafeOs_SUD_API_04504 */
      Os_ArchResumeOSInterrupts();
    } /* End of if (LddStatusReturn == E_OK) */
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace : SafeOs_SUD_API_04505 */
    /* Current privilege level is not supervisor. Use system call! */
    OS_SYSCALL_RESUMEOSINTERRUPTS();
  }
  #endif
  #endif
}

/***************************************************************************//**
 * Function Name        : SuspendOSInterrupts
 *
 * Service ID           : OSServiceId_SuspendOSInterrupts
 *
 * Description          : This function is called to Suspend CAT2 interrupts.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)  : N/A
 *
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_ArchSuspendOSInterrupts()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80013 */
FUNC(void, OS_CODE) SuspendOSInterrupts(void)
{
  /* @Trace : SafeOs_SUD_API_04601 */
  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  #if (OS_STATUS == EXTENDED)
  /* @Trace : SafeOs_SUD_API_04602 */
  StatusType LddStatusReturn;

  /* Init status return */
  LddStatusReturn = E_OK;
  #endif

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* @Trace : SafeOs_SUD_API_04603 */
    /* Current privilege level is supervisor */
    /* Check whether Os started or not */
    OS_CHECK_NOT_STARTOS(&LddStatusReturn);
    #if (OS_STATUS == EXTENDED)
    /* No error */
    if (LddStatusReturn == E_OK)
    #endif
    {
      /* @Trace : SafeOs_SUD_API_04604 */
      Os_ArchSuspendOSInterrupts();
    } /* End of @ if(LddStatusReturn == E_OK) */
  } /* End of @ if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace : SafeOs_SUD_API_04605 */
    /* Current privilege level is not supervisor. Use system call! */
    OS_SYSCALL_SUSPENDOSINTERRUPTS();
  }
  #endif
  #endif
}

/***************************************************************************//**
 * Function Name        : GetISRID
 *
 * Service ID           : OSServiceId_GetISRID
 *
 * Description          : This service is used to return the Id of the ISR.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Parameters           : None
 *
 * @return              : ISRType
 *                        - OS_TASK_COUNT + OS_CORE_COUNT ~
 *                         OS_TASK_COUNT + OS_CORE_COUNT + OS_CAT2_ISR_COUNT - 1
 *                        - OS_INVALID_VALUE : Interrupts are disabled by user
 *                         or it is called from wrong context
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
#if (OS_CAT2_ISR_COUNT > OS_PRE_ZERO)
FUNC(ISRType, OS_CODE) GetISRID(void)
{
  ISRType LddIsrId = INVALID_ISR;
  /* @Trace : SafeOs_SUD_API_04701 */
  LddIsrId = OS_SYSCALL_GETISRID();

  return LddIsrId;
}
#endif

/***************************************************************************//**
 * Function Name        : EnableInterruptSource
 *
 * Service ID           : OSServiceId_EnableInterruptSource
 *
 * Description          : Enables the interrupt source by modifying the
 *                        interrupt controller registers. Additionally it
 *                        may clear the interrupt pending flag.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param [in]          : ISRID - The ID of a category 2 ISR.
 * @param [in]          : ClearPending - Defines whether the pending flag shall
 *                        be cleared (TRUE) or not (FALSE).
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_ID : ISRID is not valid category 2 ISR identifier.
 *                        - E_OS_CALLEVEL : Wrong call context of the API function.
 *                        - E_OS_ACCESS : The calling application is not the owner
 *                          of the ISR passed in ISRID.
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_11011 */
#if (OS_CAT2_ISR_COUNT > OS_PRE_ZERO)
FUNC(StatusType, OS_CODE) EnableInterruptSource(ISRType ISRID,
                                                boolean ClearPending)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_04901 */
  LddStatusReturn = OS_SYSCALL_ENABLEINTERRUPTSOURCE(ISRID, ClearPending);

  return LddStatusReturn;
}
#endif

/***************************************************************************//**
 * Function Name        : DisableInterruptSource
 *
 * Service ID           : OSServiceId_DisableInterruptSource
 *
 * Description          : Disables the interrupt source by modifying the
 *                        interrupt controller registers.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param [in]          : ISRID
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_ID : ISRID is not valid category 2 ISR identifier.
 *                        - E_OS_CALLEVEL : Wrong call context of the API function.
 *                        - E_OS_ACCESS : The calling application is not the owner
 *                          of the ISR passed in ISRID.
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_11011 */
#if (OS_CAT2_ISR_COUNT > OS_PRE_ZERO)
FUNC(StatusType, OS_CODE) DisableInterruptSource(ISRType ISRID)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_04801 */
  LddStatusReturn = OS_SYSCALL_DISABLEINTERRUPTSOURCE(ISRID);

  return LddStatusReturn;
}
#endif

/***************************************************************************//**
 * Function Name        : ClearPendingInterrupt
 *
 * Service ID           : OSServiceId_ClearPendingInterrupt
 *
 * Description          : Clears the interrupt pending flag by modifying the
 *                        interrupt controller registers.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param [in]          : ISRID
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_ID : ISRID is not valid category 2 ISR identifier.
 *                        - E_OS_CALLEVEL : Wrong call context of the API function.
 *                        - E_OS_ACCESS : The calling application is not the owner
 *                          of the ISR passed in ISRID.
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11011 */
#if (OS_CAT2_ISR_COUNT > OS_PRE_ZERO)
FUNC(StatusType, OS_CODE) ClearPendingInterrupt(ISRType ISRID)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_05001 */
  LddStatusReturn = OS_SYSCALL_CLEARPENDINGINTERRUPT(ISRID);

  return LddStatusReturn;
}
#endif

#if (OS_SPINLOCK == STD_ON)
/***************************************************************************//**
 * Function Name        : GetSpinlock
 *
 * Service ID           : OSServiceId_GetSpinlock
 *
 * Description          : GetSpinlock tries to occupy a spin-lock variable.
 *                        If the function returns, either the lock is
 *                        successfully taken or an error has occurred.
 *                        The spinlock mechanism is an active polling
 *                        mechanism.
 *                        The function does not cause a de-scheduling.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param [in]            SpinlockId    The value refers to the spinlock
 *                                      instance that shall be locked
 *                                      (range : 0 ~ OS_SPINLOCK_COUNT - 1)
 *
 * @return              : StatusType
 *                        - E_OK : No Error
 *                        - E_OS_ID : The <SpinlockId> is invalid
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ACCESS : The spinlock cannot be accessed
 *                        - E_OS_INTERFERENCE_DEADLOCK : A TASK tries to occupy
 *                          the spinlock while the lock is already occupied by
 *                          a TASK on the same core. This would cause a deadlock
 *                        - E_OS_NESTING_DEADLOCK : A TASK tries to occupy the
 *                          spinlock while holding a different spinlock in a way
 *                          that may cause a deadlock
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : TryToGetSpinlock()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80021 */
/* polyspace +1 CODE-METRIC:calling [Justified:Low] "The display of specific values of the number of calling is justified" */
FUNC(StatusType, OS_CODE) GetSpinlock(SpinlockIdType SpinlockId)
{
  /* @Trace: SafeOs_SUD_API_22001 */
  volatile StatusType LddStatusReturn = E_OK;
  TryToGetSpinlockType LddSuccess = TRYTOGETSPINLOCK_NOSUCCESS;
  /* polyspace +1 MISRA-C3:13.5 [Justified:Low] "The implementation has been tested many time by IT and QT, the violation does not impact the use cases of the module" */
  while ((LddSuccess != TRYTOGETSPINLOCK_SUCCESS) && (LddStatusReturn == E_OK))
  {
    /* @Trace: SafeOs_SUD_API_22002 */
    LddStatusReturn = TryToGetSpinlock(SpinlockId, &LddSuccess);
  }

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : ReleaseSpinlock
 *
 * Service ID           : OSServiceId_ReleaseSpinlock
 *
 * Description          : ReleaseSpinlock releases a spinlock variable
 *                        that was occupied before. Before terminating
 *                        a TASK all spinlock variables that have been
 *                        occupied with GetSpinlock() shall be released.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param [in]            SpinlockId    The value refers to the spinlock
 *                                      instance that shall be locked
 *                                      (range : 0 ~ OS_SPINLOCK_COUNT - 1)
 *
 * @return              : StatusType
 *                        - E_OK : No Error
 *                        - E_OS_ID : The <SpinlockId> is invalid
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ACCESS : The spinlock cannot be accessed
 *                        - E_OS_STATE : The Spinlock is not occupied
 *                        - E_OS_NOFUNC : Attempt to release a spinlock while
 *                          another spinlock has to be released before
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  :
 *                        Os_GaaSpinlock
 *
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_CallReleaseSpinlock()
 *                        Os_ArchReleaseSpinlock()
 ******************************************************************************/
/* @Trace: SRS_Os_80021 */
/* polyspace +1 MISRA-C3:17.2 [Justified:Low] "OS_SYSCALL_RELEASESPINLOCK -> Os_SystemCallReleaseSpinlock ->Os_KernReleaseSpinlock ->Os_SpinlockUnLockMethod -> Os_SpinlockUnLockResource -> Os_ScheduleService -> Os_CheckStack -> Os_ProtectionHookService -> Os_KillTaskOrISR -> ReleaseSpinlock" */
FUNC(StatusType, OS_CODE) ReleaseSpinlock(SpinlockIdType SpinlockId)
{
  StatusType LddStatusReturn = E_OK;
  Os_SpinlockMethod LenLockMethod = LOCK_NOTHING;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* @Trace: SafeOs_SUD_API_22101 */
  /* Get curent Core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* @Trace: SafeOs_SUD_API_22102 */
    /* Current privilege level is supervisor */
    /* Check whether SpinlockId is greater than number of Spinlock count */
    OS_CHECK_SPINLOCK_ID_ERROR(SpinlockId, LddStatusReturn);
    /* Check for call level */
    OS_CHECK_E_OS_CALLEVEL(RELEASESPINLOCK, LddStatusReturn);
    /* Check Access for the spinlock */
    /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
    /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "SpinlockId have been checked before using" */
    OS_CHECK_SPINLOCK_APPLICATION_ACCESS(LddStatusReturn,SpinlockId);
    /* Check if Spinlock is not aquired by the task */
    /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
    /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    OS_CHECK_SPINLOCK_STATE_ERROR(SpinlockId, LddStatusReturn);
    /* Check if releasing order is incorrect */
    /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
    OS_CHECK_SPINLOCK_RELEASE_ORDER_ERROR(SpinlockId, LddStatusReturn);
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "SpinlockId have been checked before using" */

    if (LddStatusReturn == E_OK)
    {
      LenLockMethod = Os_GaaSpinlock[SpinlockId].enSpinMethod;
      if (LenLockMethod == LOCK_WITH_RES_SCHEDULER)
      {
        /* @Trace: SafeOs_SUD_API_22103 */
        LddStatusReturn = Os_CallReleaseSpinlock(SpinlockId);
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_22104 */
        Os_ArchReleaseSpinlock(SpinlockId);
      }
    }
    #if (OS_STATUS == EXTENDED)
    else
    {
      /* @Trace: SafeOs_SUD_API_22105 */
      /* Store service ID of ReleaseSpinlock */
      /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      OS_STORE_SERVICE(OSServiceId_ReleaseSpinlock);
      /*Store the parameter 1 - SpinlockId */
      OS_STORE_PARAM1_SPINLOCKID(SpinlockId);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LddStatusReturn);
    }
    #endif
  }
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace: SafeOs_SUD_API_22106 */
    LddStatusReturn = Os_CallReleaseSpinlock(SpinlockId);
  }
  #endif  

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : TryToGetSpinlock
 *
 * Service ID           : OSServiceId_TryToGetSpinlock
 *
 * Description          : The TryToGetSpinlockType indicates if the spinlock
 *                        has been occupied or not.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * @param [in]            SpinlockId    The value refers to the spinlock
 *                                      instance that shall be locked
 *                                      (range : 0 ~ OS_SPINLOCK_COUNT - 1)
 * @param [out]           Success       Returns if the lock has been occupied
 *                                      or not
 *                                      (range : TRYTOGETSPINLOCK_SUCCESS,
 *                                               TRYTOGETSPINLOCK_NOSUCCESS)
 *
 * @return              : StatusType
 *                        - E_OK : No Error
 *                        - E_OS_ID : The <SpinlockId> is invalid
 *                        - E_OS_CALLEVEL : It is called from wrong context
 *                        - E_OS_ACCESS : The spinlock cannot be accessed
 *                        - E_OS_INTERFERENCE_DEADLOCK : A TASK tries to occupy
 *                          the spinlock while the lock is already occupied by
 *                          a TASK on the same core. This would cause a deadlock
 *                        - E_OS_NESTING_DEADLOCK : A TASK tries to occupy the
 *                          spinlock while holding a different spinlock in a way
 *                          that may cause a deadlock
 *                        - E_OS_PARAM_POINTER : <Success> is a NULL_PTR
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  :
 *                        Os_GaaSpinlock
 * 
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_CallTryToGetSpinlock()
 *                        Os_ArchTryToGetSpinlock()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80021 */
/* polyspace +2 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
/* polyspace +3 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace*/
FUNC(StatusType, OS_CODE) TryToGetSpinlock
    (SpinlockIdType SpinlockId,
     P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success)
{
  StatusType LddStatusReturn = E_OK;
  Os_SpinlockMethod LenLockMethod = LOCK_NOTHING;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* @Trace : SafeOs_SUD_API_22201 */
  /* Get curent Core ID */
  OS_GET_CORE_ID(OS_CORE_ID);

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* @Trace: SafeOs_SUD_API_22202 */
    /* Check whether SpinlockId is greater than number of Spinlock count */
    OS_CHECK_SPINLOCK_ID_ERROR(SpinlockId, LddStatusReturn);
    /* Check for call level of TryToGetSpinlock */
    OS_CHECK_E_OS_CALLEVEL(TRYTOGETSPINLOCK, LddStatusReturn);
    /* Check Access for the spinlock */
    /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "SpinlockId have been checked before using" */
    /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
    OS_CHECK_SPINLOCK_APPLICATION_ACCESS(LddStatusReturn, SpinlockId);
    /* Check whether Spinlock is already occupied by same task or task belonging on same core */
    OS_CHECK_SPINLOCK_STATUS_ERROR(SpinlockId, LddStatusReturn);
    /* polyspace +2 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
    /* Check whether Spinlock can create deadlock */
    /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    OS_CHECK_SPINLOCK_DEADLOCK_ERROR(SpinlockId, LddStatusReturn);
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "SpinlockId have been checked before using" */
    /* Check for NULL_PTR of Success for TryToGetSpinlock */
    OS_CHECK_NULL_PTR(Success, LddStatusReturn);

    if (LddStatusReturn == E_OK)
    {
      LenLockMethod = Os_GaaSpinlock[SpinlockId].enSpinMethod;
      if (LenLockMethod == LOCK_WITH_RES_SCHEDULER)
      {
        /* @Trace: SafeOs_SUD_API_22203 */
        LddStatusReturn = Os_CallTryToGetSpinlock(SpinlockId, Success);
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_22204 */
        Os_ArchTryToGetSpinlock(SpinlockId, Success);
      }
    }
    #if (OS_STATUS == EXTENDED)
    else
    {
      /* @Trace: SafeOs_SUD_API_22205 */
      /* Store the parameter 1 - SpinlockId */
      /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      OS_STORE_PARAM1_SPINLOCKID(SpinlockId);
      /* Store the service ID of TryToGetSpinlock */
      OS_STORE_SERVICE(OSServiceId_TryToGetSpinlock);
      /* Store the parameter 2 - Success */
      OS_STORE_PARAM2_SUCCESS(Success);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LddStatusReturn);
    }
    #endif
  }
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace: SafeOs_SUD_API_22206 */
    LddStatusReturn = Os_CallTryToGetSpinlock(SpinlockId, Success);
  }
  #endif

  return LddStatusReturn;
}

#endif /* End of if (OS_SPINLOCK == STD_ON) */


#if (OS_MULTICORE == STD_ON)
/***************************************************************************//**
 * Function Name        : ShutdownAllCores
 *
 * Service ID           : OSServiceId_ShutdownAllCores
 *
 * Description          : This function is called to shutdown all core.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : Error
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_80007 */
FUNC(void, OS_CODE) ShutdownAllCores(StatusType Error)
{
  /* @Trace : SafeOs_SUD_API_21401 */
  OS_SYSCALL_SHUTDOWNALLCORES(Error);
}

#endif /* End of if (OS_MULTICORE == STD_ON) */

/***************************************************************************//**
 * Function Name        : GetActiveApplicationMode
 *
 * Service ID           : OSServiceId_GetActiveApplicationMode
 *
 * Description          : This function returns the active application mode.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : None
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(AppModeType, OS_CODE) GetActiveApplicationMode(void)
{
  AppModeType LddApplicationMode = OSDEFAULTAPPMODE;
  /* @Trace : SafeOs_SUD_API_00201 */
  LddApplicationMode = OS_SYSCALL_GETACTIVEAPPLICATIONMODE();

  return LddApplicationMode;
}

/***************************************************************************//**
 * Function Name        : StartOS
 *
 * Service ID           : OSServiceId_StartOS
 *
 * Description          : This function is called to start the Os.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : Mode
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(void, OS_CODE) StartOS(AppModeType Mode)
{
  /* @Trace : SafeOs_SUD_API_20901 */
  OS_SYSCALL_STARTOS(Mode);
}

/***************************************************************************//**
 * Function Name        : ShutdownOS
 *
 * Service ID           : OSServiceId_ShutdownOS
 *
 * Description          : This function is called to shutdown the Os.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : Error
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80007 */
FUNC(void, OS_CODE) ShutdownOS(StatusType Error)
{
  /* @Trace : SafeOs_SUD_API_21501 */
  OS_SYSCALL_SHUTDOWNOS(Error);
}

#if (OS_RESOURCE == STD_ON)

/***************************************************************************//**
 * Function Name        : GetResource
 *
 * Service ID           : OSServiceId_GetResource
 *
 * Description          : This Service is used to Get the resource.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : ResID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE) GetResource(ResourceType ResID)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_09301 */
  LddStatusReturn = OS_SYSCALL_GETRESOURCE(ResID);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : ReleaseResource
 *
 * Service ID           : OSServiceId_ReleaseResource
 *
 * Description          : This Service is used to Release the resource.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : ResID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE) ReleaseResource(ResourceType ResID)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_09401 */
  LddStatusReturn = OS_SYSCALL_RELEASERESOURCE(ResID);

  return LddStatusReturn;
}

#endif /* (OS_RESOURCE == STD_ON) */

#if (OS_SCHEDTABLE == STD_ON)
/***************************************************************************//**
 * Function Name        : StartScheduleTableRel
 *
 * Service ID           : OSServiceId_StartScheduleTableRel
 *
 * Description          : This service does the processing of
 *                        the schedule table at "Offset" relative
 *                        to the "Now" value on the underlying counter.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : ScheduleTableID, Offset
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_00098 SRS_Os_00099 SRS_Os_11002 SRS_Os_11016 */
FUNC(StatusType, OS_CODE) StartScheduleTableRel
    (ScheduleTableType ScheduleTableID,
     TickType Offset)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_11301 */
  LddStatusReturn = OS_SYSCALL_STARTSCHEDULETABLEREL(ScheduleTableID, Offset);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : StartScheduleTableAbs
 *
 * Service ID           : OSServiceId_StartScheduleTableAbs
 *
 * Description          : This service does the processing of
 *                        the schedule table at absolute value "Start" of
 *                        the underlying counter.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : ScheduleTableID, Start
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_00098 SRS_Os_00099 SRS_Os_11002 SRS_Os_11016 */
FUNC(StatusType, OS_CODE) StartScheduleTableAbs
    (ScheduleTableType ScheduleTableID,
     TickType Start)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_11501 */
  LddStatusReturn = OS_SYSCALL_STARTSCHEDULETABLEABS(ScheduleTableID, Start);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : StopScheduleTable
 *
 * Service ID           : OSServiceId_StopScheduleTable
 *
 * Description          : This service changes the state of the schedule table**
 *                        to "Stopped" state.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : ScheduleTableID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_00099 SRS_Os_11002 SRS_Os_00098 SRS_Os_11016 */
FUNC(StatusType, OS_CODE) StopScheduleTable
    (ScheduleTableType ScheduleTableID)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_11701 */
  LddStatusReturn = OS_SYSCALL_STOPSCHEDULETABLE(ScheduleTableID);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : NextScheduleTable
 *
 * Service ID           : OSServiceId_NextScheduleTable
 *
 * Description          : This service does the processing of schedule table
 *                        <ScheduleTableID_To> <ScheduleTableID_From>.
 *                        Final Delay ticks after the Final Expiry Point
 *                        on <ScheduleTableID_From> is processed.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : ScheduleTableID_From, ScheduleTableID_To
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_00099 SRS_Os_11016 */
FUNC(StatusType, OS_CODE) NextScheduleTable
    (ScheduleTableType ScheduleTableID_From,
     ScheduleTableType ScheduleTableID_To)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_11401 */
  LddStatusReturn =
         OS_SYSCALL_NEXTSCHEDULETABLE(ScheduleTableID_From, ScheduleTableID_To);

  return LddStatusReturn;
}


#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)

#if ((OS_SCALABILITY_CLASS != OS_SC2) && (OS_SCALABILITY_CLASS != OS_SC4))
#error "Os.c: Explicit schedule table sync supported in SC2 and SC4"
#endif

/***************************************************************************//**
 * Function Name        : StartScheduleTableSynchron
 *
 * Service ID           : OSServiceId_StartScheduleTableSynchron
 *
 * Description          : This service shall set the state of<ScheduleTableID>**
 *                        to SCHEDULETABLE_WAITING and start the processing
 *                        of schedule table <ScheduleTableID> after
 *                        the synchronization count of the schedule table
 *                        is set via SyncScheduleTable().
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : ScheduleTableID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11002 */
FUNC(StatusType, OS_CODE) StartScheduleTableSynchron
    (ScheduleTableType ScheduleTableID)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_11801 */
  LddStatusReturn = OS_SYSCALL_STARTSCHEDULETABLESYNCHRON(ScheduleTableID);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : SyncScheduleTable
 *
 * Service ID           : OSServiceId_SyncScheduleTable
 *
 * Description          : This service is used to synchronize the processing
 *                       of the schedule table to the synchronization counter.**
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : ScheduleTableID, Value
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11002 */
FUNC(StatusType, OS_CODE) SyncScheduleTable
    (ScheduleTableType ScheduleTableID,
     TickType Value)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_11901 */
  LddStatusReturn = OS_SYSCALL_SYNCSCHEDULETABLE(ScheduleTableID, Value);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : SetScheduleTableAsync
 *
 * Service ID           : OSServiceId_SetScheduleTableAsync
 *
 * Description          :This service stops sychronization of a scheduletable.**
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : ScheduleTableID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_00098 SRS_Os_00099 SRS_Os_11002 SRS_Os_11016 */
FUNC(StatusType, OS_CODE) SetScheduleTableAsync
    (ScheduleTableType ScheduleTableID)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_12001 */
  LddStatusReturn = OS_SYSCALL_SETSCHEDULETABLEASYNC(ScheduleTableID);

  return LddStatusReturn;
}

#endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */


/***************************************************************************//**
 * Function Name        : GetScheduleTableStatus
 *
 * Service ID           : OSServiceId_GetScheduleTableStatus
 *
 * Description          : This service is used to return the status of
 *                        the schedule table requested.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : ScheduleTableID, ScheduleStatus
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11002 */
FUNC(StatusType, OS_CODE) GetScheduleTableStatus
    (ScheduleTableType ScheduleTableID,
     ScheduleTableStatusRefType ScheduleStatus)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_11601 */
  LddStatusReturn =
             OS_SYSCALL_GETSCHEDULETABLESTATUS(ScheduleTableID, ScheduleStatus);

  return LddStatusReturn;
}

#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

#if (OS_TASK == STD_ON)

/***************************************************************************//**
 * Function Name        : ActivateTask
 *
 * Service ID           : OSServiceId_ActivateTask
 *
 * Description          : This Service transfers the TaskID from
 *                        suspended state into the ready state.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : TaskID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE) ActivateTask(TaskType TaskID)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_01601 */
  LddStatusReturn = OS_SYSCALL_ACTIVATETASK(TaskID);

  return LddStatusReturn;
}

/***************************************************************************//**
** Function Name        : ActivateTaskAsyn                                    **
**                                                                            **
** Service ID           : 0x33                                                **
**                                                                            **
** Description          : Asynchronous version of the ActivateTask() function **
**                         Intended to be used for cross core task activation **
**                        Possible errors are not returned to the caller,     **
**                         but may be reported via error hooks.               **
**                                                                            **
** Sync/Async           : ASynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : TaskID - The id of the task to be activated         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** @return              : StatusType                                          **
**                                                                            **
** @pre                 : StartOS() API should be invoked                     **
**                                                                            **
** @remarks             : Global Variable(s)  : None                          **
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* @Trace: SRS_Os_80015 */
FUNC(void, OS_CODE) ActivateTaskAsyn(TaskType TaskID)
{
  /* @Trace : SafeOs_SUD_API_02101 */
  OS_SYSCALL_ACTIVATETASKASYN(TaskID);
}

/***************************************************************************//**
 * Function Name        : TerminateTask
 *
 * Service ID           : OSServiceId_TerminateTask
 *
 * Description          : This service causes the termination of
 *                        the calling task. The calling task is transferred
 *                        from the running state into the suspended state
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : None
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
/* polyspace +1 CODE-METRIC:calling [Justified:Low] "The display of specific values of the number of calling is justified" */
FUNC(StatusType, OS_CODE) TerminateTask(void)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_01901 */
  LddStatusReturn = OS_SYSCALL_TERMINATETASK();

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : ChainTask
 *
 * Service ID           : OSServiceId_ChainTask
 *
 * Description          : This service causes the termination of the calling
 *                        task. After termination of the calling tasks
 *                        a succeeding task <TaskID> is activated.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : TaskID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE) ChainTask(TaskType TaskID)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_02001 */
  LddStatusReturn = OS_SYSCALL_CHAINTASK(TaskID);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : Schedule
 *
 * Service ID           : OSServiceId_Schedule
 *
 * Description          : This service checks if a higher-priority task is
 *                        ready, the internal resource of the task is released**
 *                        the current task is put into the ready state and
 *                        the higher-priority task is executed.
 *                        Otherwise the calling task is continued.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : None
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE) Schedule(void)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_03801 */
  LddStatusReturn = OS_SYSCALL_SCHEDULE();

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : GetTaskID
 *
 * Service ID           : OSServiceId_GetTaskID
 *
 * Description          : This service is used to get the task id from
 *                        the task descriptor.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : TaskID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
/* polyspace +1 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace*/
FUNC(StatusType, OS_CODE) GetTaskID(TaskRefType TaskID)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_01701 */
  LddStatusReturn = OS_SYSCALL_GETTASKID(TaskID);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : GetTaskState
 *
 * Service ID           : OSServiceId_GetTaskState
 *
 * Description          : This service is used to get the taskstate from
 *                        the given tasked.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : TaskID, State
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
/* polyspace +2 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace*/
FUNC(StatusType, OS_CODE) GetTaskState
    (TaskType TaskID, TaskStateRefType State)
{

  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_01801 */
  LddStatusReturn = OS_SYSCALL_GETTASKSTATE(TaskID, State);

  return LddStatusReturn;
}
#endif /* (OS_TASK == STD_ON) */


/***************************************************************************//**
 * Function Name        : GetNumberOfActivatedCores
 *
 * Service ID           : OS_ServiceID_GetNumberOfActivatedCores
 *
 * Description          : The function returns the number of cores activated
 *                        by the StartCore function.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Input Parameters     : None
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : uint32
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GucActivateCore
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
/* @Trace: SRS_Os_80001 */
#if (OS_MULTICORE == STD_ON)
FUNC(uint32, OS_CODE) GetNumberOfActivatedCores(void)
{
  /* @Trace : SafeOs_SUD_API_00401 */
  return (Os_GucActivateCore);
}
#endif /* End of if (OS_MULTICORE == STD_ON) */

/***************************************************************************//**
 * Function Name        : GetCoreID
 *
 * Service ID           : OS_ServiceID_GetCoreID
 *
 * Description          : The function returns a unique core identifier.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Input Parameters     : None
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : CoreIdType
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Os_GetCurPrivMode(), Os_CallGetCoreID()
 ******************************************************************************/
/* @Trace: SRS_Os_80001 */
#if (OS_MULTICORE == STD_ON)
/* polyspace +1 CODE-METRIC:calling [Justified:Low] "The display of specific values of the number of calling is justified" */
FUNC(CoreIdType, OS_CODE) GetCoreID(void)
{
  CoreIdType LddCoreId = OS_CORE_ID_MASTER;
  Os_OldLevel_T LddGlobalIE;

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* Current privilege level is supervisor */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
    /* @Trace: SafeOs_SUD_API_00301 */
    LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

    /* @Trace: SafeOs_SUD_API_00302 */
    LddCoreId = (CoreIdType)Os_MyCore();

    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	  /* @Trace: SafeOs_SUD_API_00303 */
	  OS_RESTORE_INTERRUPTS(LddGlobalIE);
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace: SafeOs_SUD_API_00304 */
    LddCoreId = Os_CallGetCoreID();
  }
  #endif
  return LddCoreId;
}
#endif /* End of if (OS_MULTICORE == STD_ON) */

/***************************************************************************//**
 * Function Name        : StartCore
 *
 * Service ID           : NA
 *
 * Description          : The function starts the core
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Reentrant
 *
 * Input Parameters     : CoreID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : Status
 *
 * @return              : Void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :  Os_GblStartOs, Os_GaaCore
 *
 *                        Function(s) invoked    :
 *                        Os_StartCore()
 *                        Os_GetSpinlock(),
 *                        Os_ReleaseSpinlock()
 ******************************************************************************/
/* @Trace: SRS_Os_80001 SRS_Os_80026 SRS_Os_80027 */
#if (OS_MULTICORE == STD_ON)
FUNC(void, OS_CODE) StartCore(CoreIDType CoreID, StatusType *Status)
{
  StatusType LddStatusReturn;
  /* @Trace : SafeOs_SUD_API_21101 */
  LddStatusReturn = E_OK;

  Os_GetSpinlock(OS_SPIN_LOCK_ZERO);

  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "CoreID have been checked before using" */
  /* Check whether CoreID is greater than number of core count */
  OS_CHECK_CORE_ID_ERROR(CoreID, &LddStatusReturn);
  /* Check if call is made after StartOS */
  OS_CHECK_STARTCORE_ORDER_ERROR(CoreID, LddStatusReturn);
  /* Check if Core is already started */
  OS_CHECK_CORE_ALREADY_STARTED_ERROR(CoreID, LddStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(Status, LddStatusReturn);

  if (LddStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_21102 */
    Os_GaaCore[CoreID].blCoreStatus = OS_TRUE;
    /* Start another core actually */
    Os_StartCore(CoreID);
  }
  /* @Trace : SafeOs_SUD_API_21103 */
  Os_ReleaseSpinlock(OS_SPIN_LOCK_ZERO);
  if(Status != NULL_PTR)
  {
    /* @Trace : SafeOs_SUD_API_21104 */
    *Status = LddStatusReturn;
  }
} /* End of StartCore(CoreIDType CoreID, StatusType *Status) */
#endif /* End of if (OS_MULTICORE == STD_ON) */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "CoreID have been checked before using" */

/***************************************************************************//**
 * Function Name        : StartNonAutosarCore
 *
 * Service ID           : NA
 *
 * Description          : The function starts a non AUTOSAR core
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Reentrant
 *
 * Input Parameters     : CoreID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : Status
 *
 * @return              : Void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :  Os_GblStartOs, Os_GaaCore
 *
 *                        Function(s) invoked    :
 *                        Os_StartCore()
 *                        Os_GetSpinlock(),
 *                        Os_ReleaseSpinlock()
 *
 ******************************************************************************/
/* @Trace: SRS_Os_80006 SRS_Os_80026 SRS_Os_80027 SRS_Os_80001 */
#if (OS_MULTICORE == STD_ON)
FUNC(void, OS_CODE) StartNonAutosarCore(CoreIDType CoreID, StatusType *Status)
{
  StatusType LddStatusReturn;
  /* @Trace : SafeOs_SUD_API_21001 */
  LddStatusReturn = E_OK;

  Os_GetSpinlock(OS_SPIN_LOCK_ZERO);

  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "CoreID have been checked before using" */
  /* Check whether CoreID is greater than number of core count */
  OS_CHECK_CORE_ID_ERROR(CoreID, &LddStatusReturn);
  /* Check if Core is already started */
  OS_CHECK_CORE_ALREADY_STARTED_ERROR(CoreID, LddStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(Status, LddStatusReturn);

  if (LddStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_21002 */
    Os_GaaCore[CoreID].blCoreStatus = OS_TRUE;
    /* Start another core actually */
    Os_StartCore(CoreID);
  }
  /* @Trace : SafeOs_SUD_API_21003 */
  Os_ReleaseSpinlock(OS_SPIN_LOCK_ZERO);

  if(Status != NULL_PTR)
  {
    /* @Trace : SafeOs_SUD_API_21004 */
    *Status = LddStatusReturn;
  }
} /* End of StartNonAutosarCore(CoreIDType CoreID, StatusType *Status) */
#endif /* End of if (OS_MULTICORE == STD_ON) */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "CoreID have been checked before using" */

#if (OS_APPLICATION == STD_ON)
/***************************************************************************//**
 * Function Name        : IocRead
 *
 * Service ID           : IOCServiceId_IOC_Read
 *
 * Description          : This service is used to read data through IOC
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : IocID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : data
 *
 * @return              : Std_ReturnType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  :
 *                        Os_GaaIocUnqueuedCfg
 * 
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_GetSpinlock(),
 *                        Os_MemCopy(), Os_ReleaseSpinlock(),
 *                        Os_CallIocRead()
 ******************************************************************************/
/* polyspace +2 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace*/
FUNC(Std_ReturnType, OS_CODE) IocRead(uint32 IocID, P2VAR(void, AUTOMATIC, OS_VAR) data[])
{
  Std_ReturnType LddStatusReturn = IOC_E_OK;
  P2CONST(Os_IocUnqueuedCfgType, AUTOMATIC, OS_CONST) LpCfg;
  P2CONST(Os_IocBufType, AUTOMATIC, OS_CONST) LpBuf;
  uint32 LulDataCount;
  Os_OldLevel_T LddGlobalIE;

  LulDataCount = OS_ZERO;

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* Current privilege level is supervisor */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
    /* @Trace: SafeOs_SUD_API_18701 */
    LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

    /* @Trace: SafeOs_SUD_API_18702 */
    /* Check whether Os has started or not */
    OS_CHECK_IOC_NOT_STARTOS(&LddStatusReturn);
    /* check IOC ID */
    /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "IocID have been checked before using" */
    /* polyspace<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
    OS_CHECK_IOC_ID_ERROR(IocID, Os_Ioc_Count_Unqueued, LddStatusReturn);
    /* check null pointer */
    /* polyspace<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
    OS_CHECK_IOC_INVALID_UNQUEUED_BUF_ERROR(data, IocID, LulDataCount, LddStatusReturn);
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "IocID have been checked before using" */

    /* polyspace-begin MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
    if (LddStatusReturn == IOC_E_OK)
    {
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_18703 */
      Os_GetSpinlock(OS_IOCLOCKBASE_UNQUEUED+IocID);
      #endif
      /* @Trace: SafeOs_SUD_API_18704 */
      /* read IOC data */
      LpCfg = &Os_GaaIocUnqueuedCfg[IocID];
      for (LulDataCount = OS_ZERO; LulDataCount < LpCfg->ulDataCount; LulDataCount++)
      {
        /* @Trace: SafeOs_SUD_API_18705 */
        LpBuf = &(LpCfg->pBuffer[LulDataCount]);
        /* polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
        /* polyspace:begin<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
        /* polyspace +4 MISRA-C3:D4.11 [Justified:Low] "function is called with a valid arguments that are confirmed by testing" */
        /* polyspace +3 MISRA-C3:11.8 [Justified:Low] "Constant is not removed in this code" */
        /* polyspace<RTE: STD_LIB : Not a defect : No Action Planned > function is called with a valid arguments that are confirmed by testing */
        /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually */
        Os_MemCopy((void*)(data[LulDataCount]), (void*)(LpBuf->pIocBuf),
                                                    (Os_Size_T)LpBuf->ulDataSize);
        /* polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations>  It is used for consistency */
        /* polyspace:end<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
      }
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_18706 */
      Os_ReleaseSpinlock(OS_IOCLOCKBASE_UNQUEUED+IocID);
      #endif
    } /* End of if (LddStatusReturn == IOC_E_OK) */
    /* polyspace-end MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */

    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	  /* @Trace: SafeOs_SUD_API_18707 */
	  OS_RESTORE_INTERRUPTS(LddGlobalIE);
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace: SafeOs_SUD_API_18708 */
    LddStatusReturn = Os_CallIocRead(IocID, data);
  }
  #endif
  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : IocWrite
 *
 * Service ID           : IOCServiceId_IOC_Write
 *
 * Description          : This service is used to write data through IOC
 *
 * Sync/Async           : Asynchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : IocID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : data
 *
 * @return              : Std_ReturnType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  :
 *                        Os_GaaIocUnqueuedCfg
 * 
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_GetSpinlock(),
 *                        Os_MemCopy(), Os_ReleaseSpinlock(),
 *                        Os_CallIocWrite
 ******************************************************************************/
FUNC(Std_ReturnType, OS_CODE) IocWrite(uint32 IocID,
                                 CONSTP2CONST(void, AUTOMATIC, OS_CONST) data[])

{
  Std_ReturnType LddStatusReturn = IOC_E_OK;
  P2CONST(Os_IocUnqueuedCfgType, AUTOMATIC, OS_CONST) LpCfg;
  P2CONST(Os_IocBufType, AUTOMATIC, OS_CONST) LpBuf;
  uint32 LulDataCount;
  Os_OldLevel_T LddGlobalIE;

  LulDataCount = OS_ZERO;

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* Current privilege level is supervisor */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
    /* @Trace: SafeOs_SUD_API_18801 */
    LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

    /* @Trace: SafeOs_SUD_API_18802 */
    /* Check whether Os has started or not */
    OS_CHECK_IOC_NOT_STARTOS(&LddStatusReturn);
    /* check IOC ID */
    /* polyspace<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
    OS_CHECK_IOC_ID_ERROR(IocID, Os_Ioc_Count_Unqueued, LddStatusReturn);
    /* check null pointer */
    /* polyspace +3 MISRA-C3:D4.14 [Justified:Low] "IocID have been checked before using" */
    /* polyspace<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
    OS_CHECK_IOC_INVALID_UNQUEUED_BUF_ERROR(data, IocID, LulDataCount, LddStatusReturn);

    /* polyspace:begin<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
    /* polyspace-begin MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
    if (LddStatusReturn == IOC_E_OK)
    {
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_18803 */
      Os_GetSpinlock(OS_IOCLOCKBASE_UNQUEUED+IocID);
      #endif
      /* read IOC data */
      /* @Trace: SafeOs_SUD_API_18804 */
      LpCfg = &Os_GaaIocUnqueuedCfg[IocID];
      for (LulDataCount = OS_ZERO; LulDataCount < LpCfg->ulDataCount; LulDataCount++)
      {
        /* @Trace: SafeOs_SUD_API_18805 */
        LpBuf = &(LpCfg->pBuffer[LulDataCount]);
        /* polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
        /* polyspace:begin<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
        /* polyspace +3 MISRA-C3:D4.11 [Justified:Low] "function is called with a valid arguments that are confirmed by testing" */
        /* polyspace<RTE: STD_LIB : Not a defect : No Action Planned > function is called with a valid arguments that are confirmed by testing */
        /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually */
        Os_MemCopy((void*)(LpBuf->pIocBuf), data[LulDataCount],
                                              (Os_Size_T)LpBuf->ulDataSize);
        /* polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations>  It is used for consistency */
        /* polyspace:end<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
      }
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_18806 */
      Os_ReleaseSpinlock(OS_IOCLOCKBASE_UNQUEUED+IocID);
      #endif
    } /* End of if (LddStatusReturn == IOC_E_OK) */
    /* polyspace-end MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
    /* polyspace:end<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */

    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	  /* @Trace: SafeOs_SUD_API_18807 */
	  OS_RESTORE_INTERRUPTS(LddGlobalIE);
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace: SafeOs_SUD_API_18808 */
    LddStatusReturn = Os_CallIocWrite(IocID, data);
  }
  #endif
  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : IocReceive
 *
 * Service ID           : IOCServiceId_IOC_Receive
 *
 * Description          : This service is used to receive data through IOC
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : IocID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : data
 *
 * @return              : Std_ReturnType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  :
 *                        Os_GaaIocQueuedCfg
 * 
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_GetSpinlock(),
 *                        Os_MemCopy(), Os_ReleaseSpinlock(),
 *                        Os_CallIocReceive
 ******************************************************************************/
/* polyspace +1 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace" */
FUNC(Std_ReturnType, OS_CODE) IocReceive(uint32 IocID,
                                      P2VAR(void, AUTOMATIC, OS_VAR) data[])
{
  Std_ReturnType LddStatusReturn = IOC_E_OK;
  P2VAR(Os_IocQueuedCfgType, AUTOMATIC, OS_VAR) LpCfg;
  P2CONST(Os_IocBufType, AUTOMATIC, OS_CONST) LpBuf;
  uint32 LulDataCount;
  uint32 LulStartIdx;
  uint32 LulIocBuf;
  Os_OldLevel_T LddGlobalIE;

  LulDataCount = OS_ZERO;

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* Current privilege level is supervisor */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
    /* @Trace: SafeOs_SUD_API_18901 */
    LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

    /* @Trace: SafeOs_SUD_API_18902 */
    /* Check whether Os has started or not */
    OS_CHECK_IOC_NOT_STARTOS(&LddStatusReturn);
    /* check IOC ID */
    /* polyspace<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
    OS_CHECK_IOC_ID_ERROR(IocID, Os_Ioc_Count_Queued, LddStatusReturn);
    /* polyspace +3 MISRA-C3:D4.14 [Justified:Low] "IocID have been checked before using" */
    /* check null pointer */
    /* polyspace<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
    OS_CHECK_IOC_INVALID_QUEUED_BUF_ERROR(data, IocID, LulDataCount, LddStatusReturn);

    /* polyspace:begin<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
    /* polyspace-begin MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
    /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Value of LddStatusReturn depends on User-Configuration" */
    if (LddStatusReturn == IOC_E_OK)
    {
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_18903 */
      Os_GetSpinlock(OS_IOCLOCKBASE_QUEUED+IocID);
      #endif
      /* @Trace: SafeOs_SUD_API_18904 */
      /* receive IOC data */
      LpCfg = &Os_GaaIocQueuedCfg[IocID];
      if (LpCfg->ulQueueCount == OS_ZERO)
      {
        /* @Trace: SafeOs_SUD_API_18905*/
        /* Queue is empty */
        LddStatusReturn = (StatusType)IOC_E_NO_DATA;
      }
      else
      {
        for (LulDataCount = OS_ZERO; LulDataCount < LpCfg->ulDataCount; LulDataCount++)
        {
          /* @Trace: SafeOs_SUD_API_18906 */
          LpBuf = &(LpCfg->pBuffer[LulDataCount]);
          /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
          LulStartIdx = LpCfg->ulQueueRead * LpBuf->ulDataSize;

          /* polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
          /* polyspace:begin<RTE:OVFL:Not a defect:No action planned> It is defined from statically defined value */
          /* polyspace:begin<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually */
          /* polyspace-begin CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
          /* polyspace +6 MISRA-C3:18.4 [Justified:Low] "Increment operator on pointer used to achieve better throughput" */
          /* polyspace-begin MISRA-C3:11.8 [Justified:Low] "Type cast for memcpy is safe" */
          /* polyspace +4 MISRA-C3:D4.11 [Justified:Low] "function is called with a valid arguments that are confirmed by testing" */
          /* polyspace<RTE:STD_LIB:Not a defect:No action planned> It is used for consistency */
          /* polyspace-begin MISRA-C3:11.5 [Justified:Low] "No Impact of this rule violation" */
          /* polyspace-begin MISRA-C3:11.4 [Justified:Low] "This conversion cannot be modified to handle memory" */
          LulIocBuf = (uint32)(LpBuf->pIocBuf);
          Os_MemCopy((void*)(data[LulDataCount]),
              (void*)(&((uint8*)LulIocBuf)[LulStartIdx]), (Os_Size_T)LpBuf->ulDataSize);
          /* polyspace-end MISRA-C3:11.4 [Justified:Low] "This conversion cannot be modified to handle memory" */
          /* polyspace-end MISRA-C3:11.5 [Justified:Low] "No Impact of this rule violation" */
          /* polyspace-end MISRA-C3:11.8 [Justified:Low] "Type cast for memcpy is safe" */
          /* polyspace-end CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
          /* polyspace:end<RTE:OVFL:Not a defect:No action planned> It is defined from statically defined value */
          /* polyspace:end<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually */
          /* polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations>  It is used for consistency */
        }
        /* @Trace: SafeOs_SUD_API_18907 */
        LpCfg->ulQueueRead = (LpCfg->ulQueueRead < (LpCfg->ulQueueLen - OS_ONE)) ?
                                            (LpCfg->ulQueueRead + OS_ONE) : OS_ZERO;
        LpCfg->ulQueueCount--;

        if (LpCfg->blDataLost == OS_TRUE)
        {
          /* @Trace: SafeOs_SUD_API_18908 */
          LpCfg->blDataLost = OS_FALSE;
          LddStatusReturn = IOC_E_LOST_DATA;
        }
      }
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_18909 */
      Os_ReleaseSpinlock(OS_IOCLOCKBASE_QUEUED+IocID);
      #endif
    } /* End of if (LddStatusReturn == IOC_E_OK) */
    /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Value of LddStatusReturn depends on User-Configuration" */
    /* polyspace-end MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
    /* polyspace:end<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */

    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	  /* @Trace : SafeOs_SUD_API_18910 */
	  OS_RESTORE_INTERRUPTS(LddGlobalIE);
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace : SafeOs_SUD_API_18911 */
    LddStatusReturn = Os_CallIocReceive(IocID, data);
  }
  #endif
  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : IocSend
 *
 * Service ID           : IOCServiceId_IOC_Send
 *
 * Description          : This service is used to send data through IOC
 *
 * Sync/Async           : Asynchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : IocID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : data
 *
 * @return              : Std_ReturnType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  :
 *                        Os_GaaIocQueuedCfg
 * 
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_GetSpinlock(),
 *                        Os_MemCopy(), Os_ReleaseSpinlock(),
 *                        Os_CallIocSend
 ******************************************************************************/
FUNC(Std_ReturnType, OS_CODE) IocSend(uint32 IocID, CONSTP2CONST(void, AUTOMATIC, OS_CONST) data[])

{
  Std_ReturnType LddStatusReturn = IOC_E_OK;
  P2VAR(Os_IocQueuedCfgType, AUTOMATIC, OS_VAR) LpCfg;
  P2CONST(Os_IocBufType, AUTOMATIC, OS_CONST) LpBuf;
  uint32 LulDataCount;
  uint32 LulStartIdx;
  uint32 LulIocBuf;
  Os_OldLevel_T LddGlobalIE;

  LulDataCount = OS_ZERO;

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* Current privilege level is supervisor */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
    /* @Trace: SafeOs_SUD_API_19001 */
    LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

    /* @Trace: SafeOs_SUD_API_19002 */
    /* Check whether Os has started or not */
    OS_CHECK_IOC_NOT_STARTOS(&LddStatusReturn);
    /* check IOC ID */
    /* polyspace<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
    OS_CHECK_IOC_ID_ERROR(IocID, Os_Ioc_Count_Queued, LddStatusReturn);
    /* polyspace +3 MISRA-C3:D4.14 [Justified:Low] "IocID have been checked before using" */
    /* check null pointer */
    /* polyspace<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
    OS_CHECK_IOC_INVALID_QUEUED_BUF_ERROR(data, IocID, LulDataCount, LddStatusReturn);

    /* polyspace:begin<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
    /* polyspace-begin MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
    /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Value of LddStatusReturn depends on User-Configuration" */
    if (LddStatusReturn == IOC_E_OK)
    {
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_19003 */
      Os_GetSpinlock(OS_IOCLOCKBASE_QUEUED+IocID);
      #endif
      /* @Trace: SafeOs_SUD_API_19004 */
      /* receive IOC data */
      LpCfg = &Os_GaaIocQueuedCfg[IocID];
      if (LpCfg->ulQueueCount >= LpCfg->ulQueueLen)
      {
        /* @Trace: SafeOs_SUD_API_19005 */
        /* Queue is full */
        LpCfg->blDataLost = OS_TRUE;
        LddStatusReturn = (StatusType)IOC_E_LIMIT;
      }
      else
      {
        for (LulDataCount = OS_ZERO; LulDataCount < LpCfg->ulDataCount; LulDataCount++)
        {
          /* @Trace: SafeOs_SUD_API_19006 */
          LpBuf = &(LpCfg->pBuffer[LulDataCount]);
          /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
          LulStartIdx = LpCfg->ulQueueWrite * LpBuf->ulDataSize;
          /* polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
          /* polyspace-begin CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
          /* polyspace<RTE:OVFL:Not a defect:No action planned> It is defined from statically defined value */
          /* polyspace<RTE:STD_LIB:Not a defect:No action planned> It is used for consistency */
          /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually */
          /* polyspace +3 MISRA-C3:18.4 [Justified:Low] "Increment operator on pointer used to achieve better throughput" */
          /* polyspace +3 MISRA-C3:D4.11 [Justified:Low] "function is called with a valid arguments that are confirmed by testing" */
          /* polyspace +1 MISRA-C3:11.5 [Justified:Low] "No Impact of this rule violation" */
          /* polyspace-begin MISRA-C3:11.4 [Justified:Low] "This conversion cannot be modified to handle memory" */
          LulIocBuf = (uint32)(LpBuf->pIocBuf);
          Os_MemCopy((void*)(&((uint8*)LulIocBuf)[LulStartIdx]),
                                data[LulDataCount], (Os_Size_T)LpBuf->ulDataSize);
          /* polyspace-end MISRA-C3:11.4 [Justified:Low] "This conversion cannot be modified to handle memory" */
          /* polyspace-end CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
          /* polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations>  It is used for consistency */
        }
        /* @Trace: SafeOs_SUD_API_19007 */
        LpCfg->ulQueueWrite =
          (LpCfg->ulQueueWrite < (LpCfg->ulQueueLen - OS_ONE)) ?
                                          (LpCfg->ulQueueWrite + OS_ONE) : OS_ZERO;
        LpCfg->ulQueueCount++;
      }
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_19008 */
      Os_ReleaseSpinlock(OS_IOCLOCKBASE_QUEUED+IocID);
      #endif
    } /* End of if (LddStatusReturn == IOC_E_OK) */
    /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Value of LddStatusReturn depends on User-Configuration" */
    /* polyspace-end MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
    /* polyspace:end<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */

    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	  /* @Trace : SafeOs_SUD_API_19009 */
	  OS_RESTORE_INTERRUPTS(LddGlobalIE);
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace : SafeOs_SUD_API_19010 */
    LddStatusReturn = Os_CallIocSend(IocID, data);
  }
  #endif
  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : IocEmptyQueue
 *
 * Service ID           : IOCServiceId_IOC_EmptyQueue
 *
 * Description          : This service is used to empty Queue
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : IocID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : Std_ReturnType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  :
 *                        Os_GaaIocQueuedCfg
 * 
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_GetSpinlock(),
 *                        Os_ReleaseSpinlock(), Os_CallIocEmptyQueue()
 ******************************************************************************/
FUNC(Std_ReturnType, OS_CODE) IocEmptyQueue(uint32 IocID)

{
  Std_ReturnType LddStatusReturn = IOC_E_OK;
  P2VAR(Os_IocQueuedCfgType, AUTOMATIC, OS_VAR) LpCfg;
  Os_OldLevel_T LddGlobalIE;

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* Current privilege level is supervisor */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
    /* @Trace: SafeOs_SUD_API_19101 */
    LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();

    /* @Trace: SafeOs_SUD_API_19102 */
    /* Check whether Os has started or not */
    OS_CHECK_IOC_NOT_STARTOS(&LddStatusReturn);
    /* check IOC ID */
    /* polyspace<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
    OS_CHECK_IOC_ID_ERROR(IocID, Os_Ioc_Count_Queued, LddStatusReturn);

    /* polyspace:begin<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
    /* polyspace-begin MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
    /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Value of LddStatusReturn depends on User-Configuration" */
    if (LddStatusReturn == IOC_E_OK)
    {
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_19103 */
      Os_GetSpinlock(OS_IOCLOCKBASE_QUEUED+IocID);
      #endif
      /* @Trace: SafeOs_SUD_API_19104 */
      /* receive IOC data */
      LpCfg = &Os_GaaIocQueuedCfg[IocID];
      LpCfg->ulQueueRead = OS_ZERO;
      LpCfg->ulQueueWrite = OS_ZERO;
      LpCfg->ulQueueCount = OS_ZERO;
      LpCfg->blDataLost = OS_FALSE;
      #if (OS_MULTICORE == STD_ON)
      /* @Trace: SafeOs_SUD_API_19105 */
      Os_ReleaseSpinlock(OS_IOCLOCKBASE_QUEUED+IocID);
      #endif
    } /* End of if (LddStatusReturn == IOC_E_OK) */
    /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Value of LddStatusReturn depends on User-Configuration" */
    /* polyspace-end MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
    /* polyspace:end<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */

    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	  /* @Trace : SafeOs_SUD_API_19106 */
	  OS_RESTORE_INTERRUPTS(LddGlobalIE);
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace : SafeOs_SUD_API_19107 */
    LddStatusReturn = Os_CallIocEmptyQueue(IocID);
  }
  #endif
  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : Os_IocPullCB
 *
 * Service ID           : OSServiceId_Os_IocPullCB
 *
 * Description          : This service is used to pull IOC callback function
 *
 * Sync/Async           : Asynchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : pIocPullCB, recvAppID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : None
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  :
 *                        Os_GaaStaticApplication
 * 
 *                        Function(s) invoked :
 *                        Os_GetCurPrivMode(), Os_SendIocPullCB(),
 *                        Os_DoIocPullCB(), Os_CallIocPullCB()
 ******************************************************************************/
FUNC(void, OS_CODE) Os_IocPullCB(P2FUNC(void, OS_CONST, pIocPullCB) (void),
    ApplicationType recvAppID)
{
  StatusType LddStatusReturn = IOC_E_OK;
  Os_OldLevel_T LddGlobalIE;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* @Trace: SafeOs_SUD_API_19201*/
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR)
  #endif
  {
    /* Current privilege level is supervisor */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
    /* @Trace: SafeOs_SUD_API_19202 */
    LddGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();
    
    /* Check whether Os has started or not */
    OS_CHECK_IOC_NOT_STARTOS(&LddStatusReturn);
    /* Check NULL_PTR for pIocPullCB */
    OS_CHECK_IOC_NULL_PTR(pIocPullCB, LddStatusReturn);

    if (LddStatusReturn == IOC_E_OK)
    {
      /* Store the static task corresponding to TaskID in local pointer */
      #if (OS_MULTICORE == STD_ON)
      /* Check if new task belongs to same core */
      /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "recvAppID have been checked before using" */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "configured array index" */
      if (Os_GaaStaticApplication[recvAppID].ddCoreID != OS_CORE_ID)
      {
        /* @Trace: SafeOs_SUD_API_19203 */
        /* Call Os_SendActivateTask to schedule task on respective core */
        Os_SendIocPullCB(pIocPullCB, recvAppID);
      } /* End of if (LpStaticTask->ddCoreId != OS_CORE_ID) */
      else
      #endif /* End of if (OS_MULTICORE == STD_ON) */
      {
        /* @Trace: SafeOs_SUD_API_19204 */
        /* Call Os_DoIocPullCB */
        Os_DoIocPullCB(pIocPullCB, recvAppID);
      }
      /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "recvAppID have been checked before using" */
    } /* End of if (LddStatusReturn == IOC_E_OK) */
    /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
	  /* @Trace : SafeOs_SUD_API_19205 */
	  OS_RESTORE_INTERRUPTS(LddGlobalIE);
  } /* End of if (Os_GetCurPrivMode() == OS_PRIV_SUPERVISOR) */
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  else
  {
    /* @Trace : SafeOs_SUD_API_19206 */
    Os_CallIocPullCB(pIocPullCB, recvAppID);
  }
  #endif
}
#endif /* if (OS_APPLICATION == STD_ON) */

/***************************************************************************//**
 * Function Name        : ControlIdle
 *
 * Service ID           : OSServiceId_Os_ControlIdle
 *
 * Description          : This API allows the caller to select the idle mode
 *                      action which is performed during idle time of the OS
 *
 * Sync/Async           : synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Input Parameters     : CoreID - selects the core which idle mode is set
 *                        IdleMode - the mode which shall be performed during
 *                                   idle time
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80022 SRS_Os_80023 */
FUNC(StatusType, OS_CODE) ControlIdle(CoreIDType CoreID, IdleModeType IdleMode)
{
  Std_ReturnType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_00101 */
  LddStatusReturn = OS_SYSCALL_CONTROLIDLE(CoreID, IdleMode);

  return LddStatusReturn;
}
#if ((OS_TRUSTED_START_INDX != OS_ZERO) && (OS_PERIPHERAL == STD_ON))
/***************************************************************************//**
 * Function Name        : ReadPeripheral8
 *
 * Service ID           : OSServiceId_ReadPeripheral8
 *
 * Description          : This service returns the content of a
 *                        given memory location (<Address>).
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : Area, Address
 *
 * InOut parameter      : None
 *
 * Output Parameters    : ReadValue
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
FUNC(StatusType, OS_CODE) ReadPeripheral8(AreaIdType Area,
                            P2CONST(uint8, AUTOMATIC, OS_CONST) Address,
                                                      uint8* Readvalue)
{
  Std_ReturnType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_15501 */
  LddStatusReturn = OS_SYSCALL_READPERIPHERAL8(Area, Address, Readvalue);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : ReadPeripheral16
 *
 * Service ID           : OSServiceId_ReadPeripheral16
 *
 * Description          : This service returns the content of a
 *                        given memory location (<Address>).
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : Area, Address
 *
 * InOut parameter      : None
 *
 * Output Parameters    : ReadValue
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
FUNC(StatusType, OS_CODE) ReadPeripheral16(AreaIdType Area,
                            P2CONST(uint16, AUTOMATIC, OS_CONST) Address,
                                                      uint16* Readvalue)
{
  Std_ReturnType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_15601 */
  LddStatusReturn = OS_SYSCALL_READPERIPHERAL16(Area, Address, Readvalue);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : ReadPeripheral32
 *
 * Service ID           : OSServiceId_ReadPeripheral32
 *
 * Description          : This service returns the content of a
 *                        given memory location (<Address>).
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : Area, Address
 *
 * InOut parameter      : None
 *
 * Output Parameters    : ReadValue
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
FUNC(StatusType, OS_CODE) ReadPeripheral32(AreaIdType Area,
                            P2CONST(uint32, AUTOMATIC, OS_CONST) Address,
                                                      uint32* Readvalue)
{
  Std_ReturnType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_15701 */
  LddStatusReturn = OS_SYSCALL_READPERIPHERAL32(Area, Address, Readvalue);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : WritePeripheral8
 *
 * Service ID           : OSServiceId_WritePeripheral8
 *
 * Description          : This service writes the <value> to a given
 *                        memory location (<memory address>).
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : Area, Address
 *
 * InOut parameter      : None
 *
 * Output Parameters    : WriteValue
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
FUNC(StatusType, OS_CODE) WritePeripheral8(AreaIdType Area,
                                 P2VAR(uint8, AUTOMATIC, OS_VAR) Address,
                                                       uint8 WriteValue)
{
  Std_ReturnType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_15801 */
  LddStatusReturn = OS_SYSCALL_WRITEPERIPHERAL8(Area, Address, WriteValue);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : WritePeripheral16
 *
 * Service ID           : OSServiceId_WritePeripheral16
 *
 * Description          : This service writes the <value> to a given
 *                        memory location (<memory address>).
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : Area, Address
 *
 * InOut parameter      : None
 *
 * Output Parameters    : WriteValue
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
FUNC(StatusType, OS_CODE) WritePeripheral16(AreaIdType Area,
                                 P2VAR(uint16, AUTOMATIC, OS_VAR) Address,
                                                       uint16 WriteValue)
{
  Std_ReturnType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_15901 */
  LddStatusReturn = OS_SYSCALL_WRITEPERIPHERAL16(Area, Address, WriteValue);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : WritePeripheral32
 *
 * Service ID           : OSServiceId_WritePeripheral32
 *
 * Description          : This service writes the <value> to a given
 *                        memory location (<memory address>).
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : Area, Address
 *
 * InOut parameter      : None
 *
 * Output Parameters    : WriteValue
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
FUNC(StatusType, OS_CODE) WritePeripheral32(AreaIdType Area,
                                 P2VAR(uint32, AUTOMATIC, OS_VAR) Address,
                                                       uint32 WriteValue)
{
  Std_ReturnType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_16001 */
  LddStatusReturn = OS_SYSCALL_WRITEPERIPHERAL32(Area, Address, WriteValue);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : ModifyPeripheral8
 *
 * Service ID           : OSServiceId_Modifyeripheral8
 *
 * Description          : This service modifies a given memory location
 *                        (<memory address>) with the formula:
 *                        *<Address> = ((*<Address> & <clearmask>) | <setmask>)
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : Area, Address, Clearmask, Setmask
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
FUNC(StatusType, OS_CODE) ModifyPeripheral8(AreaIdType Area,
                                  P2VAR(uint8, AUTOMATIC, OS_VAR) Address,
                                          uint8 Clearmask, uint8 Setmask)
{
  Std_ReturnType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_16101 */
  LddStatusReturn = OS_SYSCALL_MODIFYPERIPHERAL8(Area, Address, Clearmask,
                                                                       Setmask);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : ModifyPeripheral16
 *
 * Service ID           : OSServiceId_Modifyeripheral16
 *
 * Description          : This service modifies a given memory location
 *                        (<memory address>) with the formula:
 *                        *<Address> = ((*<Address> & <clearmask>) | <setmask>)
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : Area, Address, Clearmask, Setmask
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
FUNC(StatusType, OS_CODE) ModifyPeripheral16(AreaIdType Area,
                                  P2VAR(uint16, AUTOMATIC, OS_VAR) Address,
                                         uint16 Clearmask, uint16 Setmask)
{
  Std_ReturnType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_16201 */
  LddStatusReturn = OS_SYSCALL_MODIFYPERIPHERAL16(Area, Address, Clearmask,
                                                                       Setmask);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : ModifyPeripheral32
 *
 * Service ID           : OSServiceId_Modifyeri pheral32
 *
 * Description          : This service modifies a given memory location
 *                        (<memory address>) with the formula:
 *                        *<Address> = ((*<Address> & <clearmask>) | <setmask>)
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : Area, Address, Clearmask, Setmask
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : StatusType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11005 */
FUNC(StatusType, OS_CODE) ModifyPeripheral32(AreaIdType Area,
                                  P2VAR(uint32, AUTOMATIC, OS_VAR) Address,
                                         uint32 Clearmask, uint32 Setmask)
{
  Std_ReturnType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_16301 */
  LddStatusReturn = OS_SYSCALL_MODIFYPERIPHERAL32(Area, Address, Clearmask,
                                                                       Setmask);

  return LddStatusReturn;
}
#endif

#define OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Macro definitions are needed for performance and file size  */
/* polyspace:end<MISRA-C:2.1:Not a defect:Justify with annotations> Coexistence of assembly is needed for readability  */
/* polyspace-end RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "__mfcr(0xfe1c) always return a value less than 6" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "__mfcr(0xfe1c) always return a value less than 6" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
