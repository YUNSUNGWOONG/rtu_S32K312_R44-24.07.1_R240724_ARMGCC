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
**  SRC-MODULE: Os_Alarm.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Alarm functionality                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 SRS_Os_11012 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.5.3     16-Feb-2024   HG.Kim           Jira CP44-3828                    **
** 1.5.1     06-Oct-2023   JC.Kim           Jira CP44-2438                    **
** 1.5.0     13-Sep-2023   HJ.Kim           Jira CP44-2965                    **
** 1.5.0     26-Jun-2023   HJ.Kim           Jira CP44-2459                    **
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2097                    **
**                                          Jira CP44-2028                    **
**                                          Jira CP44-2005                    **
** 1.3.12.0  09-Mar-2023   TanHX            Jira CP44-1335                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.5     07-Oct-2020   DanhDC1          R44-Redmine #15959                **
**                                          Remove un-used function           **
** 1.0.4     14-Sep-2020   TamNN1           R44-Redmine #12870                **
** 1.0.3     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
** 1.0.2     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C   8.5               **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:21.15 [Not a defect:No action planned] "This is Standard Library" */
/* polyspace-begin MISRA-C3:11.3 [Justified:Low] "To specify alarm action from undefined state, typecast to different point type is needed." */
/* polyspace-begin RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually." */
/* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "ptr points to a valid value and code is verified manually" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "ptr points to a valid value and code is verified manually" */
/* polyspace-begin RTE:COR [Not a defect:Low] "ptr points to a valid value and code is verified manually" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os RAM header file */
#include "Os_Alarm.h"             /* Os Alarm header file */
#include "Os_Task.h"              /* Os Task header file */
#include "Os_Counter.h"           /* Os Counter header file */
#include "Os_Event.h"             /* Os Event header file */
#include "Os_Error.h"             /* Os Error header file */
#include "Os_Kernel.h"            /* Os Kernel header file */
#include "Os_Definition.h"        /* Os Definition header file */
#include "Os_SystemCallTable.h"

/* @Trace: SRS_BSW_00410 */
#if (OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Application.h"       /* Os Application header file */
#endif
#if (OS_MULTICORE == STD_ON)
#include "Os_MulticoreMessage.h"
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
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/***************************************************************************//**
 * Function Name        : Os_DoGetAlarmBase
 *
 * Service ID           : NA
 *
 * Description          : This service is used to read
 *                        the alarm base characteristics. The return value
 *                        <Info> is a structure in which the information
 *                        of data type AlarmBaseType is stored.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            AlarmID       Reference to an alarm
 *                                      (range : 0 ~ OS_ALARM_COUNT - 1)
 * @param [out]           Info          Reference to structure of the alarm base
 * @param [in]            LblRemoteCall Call from another Core
 *                                      (range : OS_TRUE, OS_FALSE)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_ACCESS : Alarm is not accessible
 *
 * @pre                 : AlarmID should be checked
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticAlarm
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
/* polyspace-begin DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
#if (OS_ALARM == STD_ON)
FUNC(StatusType, OS_CODE) Os_DoGetAlarmBase(AlarmType AlarmID,
                                   AlarmBaseRefType Info, boolean LblRemoteCall)
{
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) LpStaticCounter;
  /* @Trace: SafeOs_SUD_API_07801 */
  StatusType LenStatusReturn = E_OK;

  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  OS_CHECK_ALARM_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn, AlarmID, LblRemoteCall);
  if (LenStatusReturn == E_OK)
  #else
  OS_UNUSED(LblRemoteCall);
  #endif
  {
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "AlarmID have been checked by macro OS_CHECK_ALARM_ID_ERROR before using" */
    /* Get the pointer to static counter structure */
    LpStaticCounter = (&Os_GaaStaticAlarm[AlarmID])->pStaticCounter;

    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
    if (LpStaticCounter->pHwCounter != NULL_PTR)
    {
      /* @Trace: SafeOs_SUD_API_07802 */
      /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "ptr Info have been checked before using" */
      Info->ticksperbase = LpStaticCounter->pHwCounter->ddTicksPerBase;

    }
    else
    {
      /* @Trace: SafeOs_SUD_API_07803 */
      /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "ptr Info have been checked before using" */
      Info->ticksperbase = OS_ONE;

    }
    Info->maxallowedvalue = LpStaticCounter->ddMaxAllowedValue;
    Info->mincycle = LpStaticCounter->ddMinCycle;
  }
  return LenStatusReturn;
}
#endif /* End of if (OS_ALARM == STD_ON) */
/* polyspace-end DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
/***************************************************************************//**
 * Function Name        : Os_KernGetAlarmBase
 *
 * Service ID           : NA
 *
 * Description          : This service is used to read
 *                        the alarm base characteristics. The return value
 *                        <Info> is a structure in which the information
 *                        of data type AlarmBaseType is stored.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
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
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticAlarm
 *
 *                        Function(s) invoked    :
 *                        Os_DoGetAlarmBase(), Os_SendGetAlarmBase()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80013 */
#if (OS_ALARM == STD_ON)
FUNC(StatusType, OS_CODE)
Os_KernGetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_08701 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(GETALARMBASE, LenStatusReturn);
  /* Check whether AlarmID is greater than number of Alarm count */
  OS_CHECK_ALARM_ID_ERROR(AlarmID, LenStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(Info, LenStatusReturn);
  /* Check whether Alarm can access the Application */
  OS_CHECK_ALARM_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, AlarmID);
  if (LenStatusReturn == E_OK)
  {
    #if (OS_MULTICORE == STD_ON)
    /* Check if new task belongs to same core */
    if (Os_GaaStaticAlarm[AlarmID].ddCoreID != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_08702 */
      /* Call Os_SendGetAlarmBase to schedule task on respective core */
      LenStatusReturn = Os_SendGetAlarmBase(AlarmID, Info);
    } /* End of if (LpStaticTask->ddCoreId != OS_CORE_ID) */
    else
    #endif /* End of if (OS_MULTICORE == STD_ON) */
    {
      /* @Trace: SafeOs_SUD_API_08703 */
      /* Call Os_DoGetAlarmBase */
      LenStatusReturn = Os_DoGetAlarmBase(AlarmID, Info, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_08704 */
    /* Store the service ID of GetAlarmBase */
    OS_STORE_SERVICE(OSServiceId_GetAlarmBase);
    /* Store the parameter 1 - AlarmID */
    OS_STORE_PARAM1_ALARMID(AlarmID);
    /* Store the parameter 2 - Info */
    OS_STORE_PARAM2_INFO(Info);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* Return the value */
  return (LenStatusReturn);
} /* End of GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info) */
#endif /* End of if (OS_ALARM == STD_ON) */

/***************************************************************************//**
 * Function Name        : Os_KernGetAlarm
 *
 * Service ID           : NA
 *
 * Description          : The system service GetAlarm returns the relative
 *                        value in ticks before the alarm  expires.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
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
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaAlarm
 *
 *                        Function(s) invoked    :
 *                        Os_SendGetAlarm(), Os_DoGetAlarm()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80013 */
#if (OS_ALARM == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernGetAlarm(AlarmType AlarmID, TickRefType Tick)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_08601 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(GETALARM, LenStatusReturn);
  /* Check whether AlarmID is greater than number of Alarm count */
  OS_CHECK_ALARM_ID_ERROR(AlarmID, LenStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(Tick, LenStatusReturn);
  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "AlarmID index is checked by macro OS_CHECK_ALARM_ID_ERROR before using." */
  /* Check whether Alarm can access the Application */
  OS_CHECK_ALARM_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, AlarmID);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_08602 */
    /* Get the pointer to alarm structure */
    LpAlarm = &Os_GaaAlarm[AlarmID];

    /* Check if Alarm belongs to same core */
    if (LpAlarm->ddCoreId != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_08603 */
      /* Call Os_SendGetAlarm to get remain alarm ticks on respective core */
      LenStatusReturn = Os_SendGetAlarm(AlarmID, Tick);
    } /* End of if (LpAlarm->ddCoreId != OS_CORE_ID) */
    else
    #endif
    {
      /* @Trace: SafeOs_SUD_API_08604 */
      /* Call Os_DoGetAlarm and get the return value */
      LenStatusReturn = Os_DoGetAlarm(AlarmID, Tick, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_08605 */
    /* Store the service ID of GetAlarm */
    OS_STORE_SERVICE(OSServiceId_GetAlarm);
    /* Store the parameter 1 - AlarmID */
    OS_STORE_PARAM1_ALARMID(AlarmID);
    /* Store the parameter 2 - Tick */
    OS_STORE_PARAM2_TICK(Tick);
    /* Call Error Hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* Return the value */
  return (LenStatusReturn);
} /* End of GetAlarm(AlarmType AlarmID, TickRefType Tick) */
#endif /* End of if (OS_ALARM == STD_ON) */

/***************************************************************************//**
 * Function Name        : Os_KernSetRelAlarm
 *
 * Service ID           : NA
 *
 * Description          : This service is used to set the relative alarm.
 *                        After <increment> ticks have elapsed, the task
 *                        assigned to the alarm <AlarmID> is activated
 *                        or the assigned event (only for extended tasks)
 *                        is set or the alarm-callback routine is called.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
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
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaAlarm
 *
 *                        Function(s) invoked    :
 *                        Os_SendSetRelAlarm(), Os_DoSetRelAlarm()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80013 */
#if (OS_ALARM == STD_ON)
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
FUNC(StatusType, OS_CODE) Os_KernSetRelAlarm(AlarmType AlarmID,
                                             TickType Increment, TickType Cycle)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_08901 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(SETRELALARM, LenStatusReturn);
  /* Check whether AlarmID is greater than number of Alarm count */
  OS_CHECK_ALARM_ID_ERROR(AlarmID, LenStatusReturn);
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "AlarmID index is checked by macro OS_CHECK_ALARM_ID_ERROR before using." */
  /* Check if increment is within the range of the
   *   maximum allowed value for the counter used by the alarm */
  OS_CHECK_ALARM_MAX_ALLOWED_VALUE_ERROR(AlarmID, Increment, LenStatusReturn);
  /* Check if cycle is greater than minimum value*/
  OS_CHECK_ALARM_MIN_CYCLE_ERROR(AlarmID, Cycle, LenStatusReturn);
  /* Check whether Alarm can access the Application */
  OS_CHECK_ALARM_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, AlarmID);
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "AlarmID index is checked by macro OS_CHECK_ALARM_ID_ERROR before using." */
  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_08902 */
    /* Get the pointer to static alarm structure */
    LpAlarm = &Os_GaaAlarm[AlarmID];

    /* Check if Alarm belongs to same core */
    if (LpAlarm->ddCoreId != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_08903 */
      /* Call Os_SendSetRelAlarm to set relative alarm on respective core */
      LenStatusReturn = Os_SendSetRelAlarm(AlarmID, Increment, Cycle);
    } /* End of if (LpAlarm->ddCoreId != OS_CORE_ID) */
    else
    #endif
    {
      /* @Trace: SafeOs_SUD_API_08904 */
      /* Call Os_DoSetRelAlarm and get the return value */
      LenStatusReturn = Os_DoSetRelAlarm(AlarmID, Increment, Cycle, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_08905 */
    /* Store the service Id of SetRelAlarm */
    OS_STORE_SERVICE(OSServiceId_SetRelAlarm);
    /* Store the parameter 1 - AlarmID */
    OS_STORE_PARAM1_ALARMID(AlarmID);
    /* Store the parameter 2 - Increment */
    OS_STORE_PARAM2_INCREMENT(Increment);
    /* Store the parameter 3 - Cycle */
    OS_STORE_PARAM3_CYCLE(Cycle);
    /* Call Error Hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* Return the value */
  return (LenStatusReturn);
} /* End of SetRelAlarm(AlarmType AlarmID, TickType Increment, TickType Cycle)
   **/
#endif /* End of if (OS_ALARM == STD_ON) */

/***************************************************************************//**
 * Function Name        : Os_KernSetAbsAlarm
 *
 * Service ID           : NA
 *
 * Description          : This service is used to set the absolute alarm.
 *                        When <start> ticks are reached, the configured
 *                        action takes place.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
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
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaAlarm
 *
 *                        Function(s) invoked    :
 *                        Os_SendSetAbsAlarm(), Os_DoSetAbsAlarm()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80013 */
#if (OS_ALARM == STD_ON)
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
FUNC(StatusType, OS_CODE) Os_KernSetAbsAlarm(AlarmType AlarmID, TickType Start,
                                                                 TickType Cycle)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_09101 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(SETABSALARM, LenStatusReturn);
  /* Check whether AlarmID is greater than number of Alarm count */
  OS_CHECK_ALARM_ID_ERROR(AlarmID, LenStatusReturn);
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "AlarmID index is checked by macro OS_CHECK_ALARM_ID_ERROR before using." */
  /* Check if start is within the range of the maximum
   *   allowed value for the counter used by the alarm */
  OS_CHECK_ALARM_MAX_ALLOWED_ABS_VALUE_ERROR(AlarmID, Start, LenStatusReturn);
  /* Check if cycle is greater than minimum value*/
  OS_CHECK_ALARM_MIN_CYCLE_ERROR(AlarmID, Cycle, LenStatusReturn);
  /* Check whether Alarm can access the Application */
  OS_CHECK_ALARM_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, AlarmID);
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "AlarmID index is checked by macro OS_CHECK_ALARM_ID_ERROR before using." */
  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_09102 */
    #if (OS_MULTICORE == STD_ON)
    /* Get the pointer to static alarm structure */
    LpAlarm = &Os_GaaAlarm[AlarmID];

    /* Check if Alarm belongs to same core */
    if (LpAlarm->ddCoreId != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_09103 */
      /* Call Os_SendSetAbsAlarm to set absolute alarm on respective core */
      LenStatusReturn = Os_SendSetAbsAlarm(AlarmID, Start, Cycle);
    } /* End of if (LpAlarm->ddCoreId != OS_CORE_ID) */
    else
    #endif
    {
      /* @Trace: SafeOs_SUD_API_09104 */
      /* Call Os_DoSetAbsAlarm and get the return value */
      LenStatusReturn = Os_DoSetAbsAlarm(AlarmID, Start, Cycle, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_09105 */
    /* Store the service Id of SetAbsAlarm */
    /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +1 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    OS_STORE_SERVICE(OSServiceId_SetAbsAlarm);
    /* Store the parameter 1 - AlarmID */
    OS_STORE_PARAM1_ALARMID(AlarmID);
    /* Store the parameter 2 - Start */
    OS_STORE_PARAM2_TICKSTART(Start);
    /* Store the parameter 3 - Cycle */
    OS_STORE_PARAM3_CYCLE(Cycle);
    /* Call Error Hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* Return the value */
  return (LenStatusReturn);
} /* End of SetAbsAlarm(AlarmType AlarmID, TickType Start, TickType Cycle) */
#endif /* End of if (OS_ALARM == STD_ON) */

/***************************************************************************//**
 * Function Name        : Os_KernCancelAlarm
 *
 * Service ID           : NA
 *
 * Description          : This service is used to cancel the alarm
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
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
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaAlarm
 *
 *                        Function(s) invoked    :
 *                        Os_SendCancelAlarm(), Os_DoCancelAlarm()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80013 */
#if (OS_ALARM == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernCancelAlarm(AlarmType AlarmID)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_08501 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(CANCELALARM, LenStatusReturn);
  /* Check whether AlarmID is greater than number of Alarm count */
  OS_CHECK_ALARM_ID_ERROR(AlarmID, LenStatusReturn);
  /* Check whether Alarm can access the Application */
  OS_CHECK_ALARM_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, AlarmID);
  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_08502 */
    /* Get the pointer to static alarm structure */
    LpAlarm = &Os_GaaAlarm[AlarmID];

    /* Check if Alarm belongs to same core */
    if (LpAlarm->ddCoreId != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_08503 */
      /* Call Os_SendCancelAlarm to cancel alarm on respective core */
      LenStatusReturn = Os_SendCancelAlarm(AlarmID);
    } /* End of if (LpAlarm->ddCoreId != OS_CORE_ID) */
    else
    #endif
    {
      /* @Trace: SafeOs_SUD_API_08504 */
      /* Call Os_DoCancelAlarm and get the return value */
      LenStatusReturn = Os_DoCancelAlarm(AlarmID, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_08505 */
    /* Store the service Id of CancelAlarm */
    OS_STORE_SERVICE(OSServiceId_CancelAlarm);
    /* Store the parameter 1 - AlarmID */
    OS_STORE_PARAM1_ALARMID(AlarmID);
    /* Call Error Hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* Return the value */
  return (LenStatusReturn);
} /* End of CancelAlarm(AlarmType AlarmID) */
#endif /* End of if (OS_ALARM == STD_ON) */

/***************************************************************************//**
 * Function Name        : Os_InsertAlarm
 *
 * Service ID           : NA
 *
 * Description          : This service is used to insert a alarm
 *                        object in the alarm object queue of
 *                        the counter it belongs to.
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LpAlarm    Pointer to an alarm object
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
#if ((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON))
FUNC(void, OS_CODE) Os_InsertAlarm(P2VAR(Tdd_Os_Alarm, AUTOMATIC,
                                                                OS_VAR) LpAlarm)
{
  P2VAR(Tdd_Os_Counter, AUTOMATIC, OS_VAR) LpCounter;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpCurAlarm;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpPrevAlarm;
  /* Get the pointer to counter */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
  /* @Trace: SafeOs_SUD_API_07901 */
  LpCounter = LpAlarm->pStaticAlarm->pCounter;
  /* Pointer to alarm object */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
  LpCurAlarm = LpCounter->pHeadAlarm;
  /* Pointer to previous alarm */
  LpPrevAlarm = NULL_PTR;

  while ((LpCurAlarm != NULL_PTR) &&
                        ((LpCounter->ddCurrentCount == LpCurAlarm->ddAbsCount)))
  {
    /* @Trace: SafeOs_SUD_API_07902 */
    /* Set the current alarm to previous alarm  */
    LpPrevAlarm = LpCurAlarm;
    /* Get the next entry to current alarm */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
    LpCurAlarm = LpCurAlarm->pNextAlarm;
  }

  if (LpAlarm->ddAbsCount <= LpCounter->ddCurrentCount)
  {
    while ((LpCurAlarm != NULL_PTR) &&
                         ((LpCounter->ddCurrentCount < LpCurAlarm->ddAbsCount)))
    {
      /* @Trace: SafeOs_SUD_API_07903 */
      /* Set the current alarm to previous alarm  */
      LpPrevAlarm = LpCurAlarm;
      /* Get the next entry to current alarm */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
      LpCurAlarm = LpCurAlarm->pNextAlarm;
    }
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "LpAlarm have been checked before using" */
    while ((LpCurAlarm != NULL_PTR) &&
                              ((LpCurAlarm->ddAbsCount <= LpAlarm->ddAbsCount)))
    {
      /* @Trace: SafeOs_SUD_API_07904 */
      /* Set the current alarm to previous alarm  */
      LpPrevAlarm = LpCurAlarm;
      /* Get the next entry to current alarm */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
      LpCurAlarm = LpCurAlarm->pNextAlarm;
    }
  } /* End of if (LpAlarm->ddAbsCount <= LpCounter->ddCurrentCount) */
  else
  {
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "LpAlarm have been checked before using" */
    while ((LpCurAlarm != NULL_PTR) &&
                             ((LpCurAlarm->ddAbsCount <= LpAlarm->ddAbsCount) &&
                          (LpCurAlarm->ddAbsCount > LpCounter->ddCurrentCount)))
    {
      /* @Trace: SafeOs_SUD_API_07905 */
      /* Set the current alarm to previous alarm  */
      LpPrevAlarm = LpCurAlarm;
      /* Get the next entry to current alarm */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
      LpCurAlarm = LpCurAlarm->pNextAlarm;
    }
  } /* End of else */
  /* Insert the Alarm and update the link list */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
  /* @Trace: SafeOs_SUD_API_07906 */
  LpAlarm->pNextAlarm = LpCurAlarm;
  LpAlarm->pPrevAlarm = LpPrevAlarm;

  /* Check whether it reaches to end of the queue */
  if (LpCurAlarm != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_07907 */
    /* Update the link list */
    LpCurAlarm->pPrevAlarm = LpAlarm;
  }

  /* Check whether previous alarm is equal to null pointer */
  if (LpPrevAlarm != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_07908 */
    /* Add at the end of the queue or insert */
    LpPrevAlarm->pNextAlarm = LpAlarm;
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_07909 */
    /* Alarm have to be inserted at the head of the queue */
    LpCounter->pHeadAlarm = LpAlarm;
  }
} /* End of Os_InsertAlarm(P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR)
   *LpAlarm) */
#endif /* End of if ((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON)) */

/***************************************************************************//**
 * Function Name        : Os_RemoveAlarm
 *
 * Service ID           : NA
 *
 * Description          : This service is used to remove an alarm
 *                        from the alarm queue of the counter
 *                        it belongs to.
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            LpAlarm    Pointer to an alarm object
 *
 * @return              : void
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
#if ((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON))
FUNC(void, OS_CODE) Os_RemoveAlarm(P2VAR(Tdd_Os_Alarm, AUTOMATIC,
                                                                OS_VAR) LpAlarm)
{
  P2VAR(Tdd_Os_Counter, AUTOMATIC, OS_VAR) LpCounter;
  /* Get the pointer to counter */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
  /* @Trace: SafeOs_SUD_API_07601 */
  LpCounter = LpAlarm->pStaticAlarm->pCounter;

  /* Adjust the head of the queue if the removed alarm is at the head */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
  if (LpAlarm == LpCounter->pHeadAlarm)
  {
    /* @Trace: SafeOs_SUD_API_07602 */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
    LpCounter->pHeadAlarm = LpAlarm->pNextAlarm;
  }

  /* Build the link between the previous and next alarm in the queue */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
  if (LpAlarm->pNextAlarm != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_07603 */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
    LpAlarm->pNextAlarm->pPrevAlarm = LpAlarm->pPrevAlarm;
  }
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
  if (LpAlarm->pPrevAlarm != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_07604 */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
    LpAlarm->pPrevAlarm->pNextAlarm = LpAlarm->pNextAlarm;
  }
} /* End of Os_RemoveAlarm(P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR)
   *LpAlarm) */
#endif /* End of if ((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON)) */

/***************************************************************************//**
 * Function Name        : Os_AlarmActivateTask
 *
 * Service ID           : NA
 *
 * Description          : This service is used to activate the task on the
 *                        expiry of the alarm.
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Re-entrant
 *
 * @param[in]             LpAction    Pointer to action which takes place on
 *                                    expiry of alarm
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_ACCESS : Task is not accessible
 *                        - E_OS_LIMIT : Too many task activations
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Os_SendActivateTask(), Os_DoActivateTask()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80001 SRS_Os_80015 SRS_Os_80018 SRS_Os_80013 */
#if (((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON)) && (OS_TASK == STD_ON))
FUNC(StatusType, OS_CODE) Os_AlarmActivateTask(P2CONST(
                           Tdd_Os_ActivateTask, AUTOMATIC, OS_CONST) LpAction)
{
  P2CONST(Tdd_Os_ActivateTask, AUTOMATIC, OS_CONST) LpActivateTask;
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  #if (OS_ERROR_HOOK == STD_ON)
  TaskType TaskID;
  #endif
  /* @Trace: SafeOs_SUD_API_07701 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* Pointer to action object is typecasted with the task to be activated */
  LpActivateTask = (P2CONST(Tdd_Os_ActivateTask, AUTOMATIC, OS_CONST))LpAction;
  #if (OS_MULTICORE == STD_ON)
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "ptr points to a valid value and code is verified manually" */
  if (LpActivateTask->pStaticTask->ddCoreId != OS_CORE_ID)
  {
    /* @Trace: SafeOs_SUD_API_07702 */
    /* Call Os_SendActivateTask to schedule task on respective core */
    LenStatusReturn =Os_SendActivateTask(LpActivateTask->pStaticTask->ddTaskId);
  }
  else
  #endif /* End of if (OS_MULTICORE == STD_ON) */
  {
    /* @Trace: SafeOs_SUD_API_07703 */
    /* polyspace:begin<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually */
    /* Call Os_DoActivateTask and get the return value */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "ptr points to a valid value and code is verified manually" */
    LenStatusReturn = Os_DoActivateTask(LpActivateTask->pStaticTask->ddTaskId,\
                                                                      OS_FALSE);
    /* polyspace:end<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually */
  }
  #if (OS_ERROR_HOOK == STD_ON)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_07704 */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
    TaskID = LpActivateTask->pStaticTask->ddTaskId;
    /* Store the service ID of ActivateTask */
    OS_STORE_SERVICE(OSServiceId_ActivateTask);
    /* Store the parameter 1 - TaskID */
    OS_STORE_PARAM1_TASKID(TaskID);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_ERROR_HOOK == STD_ON) */
  /* Return the value */
  return (LenStatusReturn);
} /* End of Os_AlarmActivateTask(P2CONST(Tdd_Os_ActivateTask, AUTOMATIC,
   * OS_CONST) LpAction) */
#endif /* End of if (((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON)) &&
        *(OS_TASK == STD_ON)) */

/***************************************************************************//**
 * Function Name        : Os_AlarmSetEvent
 *
 * Service ID           : NA
 *
 * Description          : This service is used to set an event
 *                        on the expiry of the alarm.
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Re-entrant
 *
 * @param[in]             LpAction    Pointer to action which takes place on
 *                                    expiry of alarm
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_ACCESS : Referenced task is not accessible
 *                        - E_OS_STATE : Referenced task is in suspended state
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Os_SendSetEvent(), Os_DoSetEvent(), Os_MemCopy()
 ******************************************************************************/
/* @Trace: SRS_Os_80016 SRS_Os_80018 SRS_Os_80013 */
#if (((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON)) && (OS_EVENT == STD_ON))
FUNC(StatusType, OS_CODE) Os_AlarmSetEvent(P2CONST(
                           Tdd_Os_AlarmEvent, AUTOMATIC, OS_CONST) LpAction)
{
  P2CONST(Tdd_Os_AlarmEvent, AUTOMATIC, OS_CONST) LpSetEvent;
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  #if (OS_ERROR_HOOK == STD_ON)
  TaskType TaskID;
  EventMaskType Mask;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* @Trace: SafeOs_SUD_API_48501 */
  /* Type cast the object with set event structure */
 
  LpSetEvent = (P2CONST(Tdd_Os_AlarmEvent, AUTOMATIC, OS_CONST))(LpAction);
  #if (OS_MULTICORE == STD_ON)
  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "ptr points to a valid value and code is verified manually" */
  /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually*/
  if (LpSetEvent->pStaticTask->ddCoreId != OS_CORE_ID)
  {
    /* @Trace: SafeOs_SUD_API_48502 */
    /* polyspace +4 MISRA-C3:11.8 [Justified:Low] "Casting const-qualification pointer to support both EventMask types as uint64 and array" */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "ptr points to a valid value and code is verified manually" */
    /* Call Os_SendSetEvent to schedule task on respective core */
    LenStatusReturn = Os_SendSetEvent(LpSetEvent->pStaticTask, LpSetEvent->ddEventMask);
  }
  else
  #endif /* End of if (OS_MULTICORE == STD_ON) */
  {
    /* @Trace: SafeOs_SUD_API_48503 */
    /* Call Os_DoSetEvent and get the return value */
    /* polyspace +4 MISRA-C3:11.8 [Justified:Low] "Casting const-qualification pointer to support both EventMask types as uint64 and array" */
    /* polyspace +2 RTE:NIP [Not a defect:Low] "LpSetEvent is casted from LpAction, which has been valiedated before used so ptr pStaticTask is checked" */
    /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "LpSetEvent is casted from LpAction, which has been valiedated before used" */
    LenStatusReturn = Os_DoSetEvent(LpSetEvent->pStaticTask->ddTaskId,
                                    (LpSetEvent->ddEventMask), OS_FALSE);
  }
  #if (OS_ERROR_HOOK == STD_ON)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_48504 */
    /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually*/
    TaskID = LpSetEvent->pStaticTask->ddTaskId;
    Mask = LpSetEvent->ddEventMask;
    /* Store the service ID of SetEvent */
    OS_STORE_SERVICE(OSServiceId_SetEvent);
    /* Store the parameter 1 - TaskID */
    OS_STORE_PARAM1_TASKID(TaskID);
    /* polyspace +2 RTE:UNR [No action planned:Low] "This macro is used for checking null pointer in several places" */
    /* Store the parameter 2 - Mask */
    OS_STORE_PARAM2_MASK(Mask);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif /* End of if (OS_ERROR_HOOK == STD_ON) */
  /* Return the value */
  return (LenStatusReturn);
} /* End of Os_AlarmSetEvent(P2CONST(Tdd_Os_AlarmEvent, AUTOMATIC,
   *OS_CONST) LpAction) */
#endif /* End of if (((OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON)) &&
        *(OS_EVENT == STD_ON)) */

/***************************************************************************//**
 * Function Name        : Os_AlarmCallback
 *
 * Service ID           : NA
 *
 * Description          : This service is used for callback function
 *                        on the expiry of the alarm.
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Re-entrant
 *
 * @param[in]             LpAction    Pointer to action which takes place on
 *                                    expiry of alarm
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        pAlarmCallBack()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
#if (OS_CALLBACK_COUNT > OS_PRE_ZERO)
FUNC(StatusType, OS_CODE) Os_AlarmCallback(P2CONST(
                         Tdd_Os_AlarmCallback, AUTOMATIC, OS_CONST) LpAction)
{
  Os_Sint_T LsiGlobalIE;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_48601 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  LsiGlobalIE = OS_DISABLE_AND_SAVE_INTERRUPTS();
  /* Process Alarm Callback */
  /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually */
  /* polyspace<RTE:COR:Not a defect:No Action Planned> function ptr points to a valid function and code is manually checked */
  /* polyspace +1 MISRA-C3:20.7 [Justified:Low] "AUTOSAR compile abstraction" */
  OS_PROCESS_ALARMCALLBACK(LpAction->pAlarmCallBack);
  /* polyspace<MISRA-C:10.1:Not a defect:Justify with annotations> This code is verified manually and has no impact */
  OS_RESTORE_INTERRUPTS(LsiGlobalIE);

  return (E_OK);
} /* End of Os_AlarmCallback(P2CONST(Tdd_Os_AlarmExpAction, AUTOMATIC,
   *OS_CONST) LpAction) */
#endif /* End of if (OS_CALLBACK_COUNT > OS_PRE_ZERO) */

/***************************************************************************//**
 * Function Name        : Os_AlarmIncrementCounter
 *
 * Service ID           : NA
 *
 * Description          : This service is used to increment the counter
 *                        on expiry of the alarm
 *                        on the expiry of the alarm.
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Re-entrant
 *
 * @param[in]             LpAction    Pointer to action which takes place on
 *                                    expiry of alarm
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_LIMIT : Too many task activations
 *                        - E_OS_ACCESS : Referenced task is not accessible
 *                        - E_OS_STATE : Referenced task is in suspended state
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticCounter
 *
 *                        Function(s) invoked    :
 *                        Os_CounterTick()
 ******************************************************************************/
#if (OS_INCCOUNTER_COUNT > OS_PRE_ZERO)
FUNC(StatusType, OS_CODE) Os_AlarmIncrementCounter(P2CONST(
                      Tdd_Os_IncrementCounter, AUTOMATIC, OS_CONST) LpAction)
{
  StatusType LenStatusreturn;
  /* @Trace: SafeOs_SUD_API_48701 */
  /* Increment the counter and get the Status */
  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "ptr points to a valid value and code is verified manually" */
  LenStatusreturn = Os_CounterTick
                        (&Os_GaaStaticCounter[LpAction->ddCounterId]);
  /* Return the value */
  return (LenStatusreturn);
} /* End of Os_AlarmIncrementCounter(P2CONST(Tdd_Os_AlarmExpAction, AUTOMATIC,
   * OS_CONST) LpAction) */
#endif /* End of if (OS_INCCOUNTER_COUNT > OS_PRE_ZERO) */

#if (OS_ALARM == STD_ON)
/***************************************************************************//**
 * Function Name        : Os_DoGetAlarm
 *
 * Service ID           : NA
 *
 * Description          : Ths service returns the relative value in ticks
 *                        before the alarm expires.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            AlarmID       Reference to an alarm
 *                                      (range : 0 ~ OS_ALARM_COUNT - 1)
 * @param [out]           Tick          Relative value in ticks before the alarm
 *                                      <AlarmID> expires.
 *                                      (range : 0 ~ MaxAllowdValue of Counter)
 * @param [in]            LblRemoteCall Call from another Core
 *                                      (range : OS_TRUE, OS_FALSE)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_NOFUNC : Alarm is not used
 *                        - E_OS_ACCESS : Alarm is not accessible
 *
 * @pre                 : StartOS() function should be called,
 *                        AlarmID should be checked
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaAlarm
 *
 *                        Function(s) invoked    :
 *                        Os_UpdateHwCounter()
 ******************************************************************************/
FUNC(StatusType, OS_CODE) Os_DoGetAlarm(AlarmType AlarmID, TickRefType Tick,
    boolean LblRemoteCall)
{
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) LpStaticCounter;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  /* @Trace: SafeOs_SUD_API_08201 */
  StatusType LenStatusReturn = E_OK;

  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  /* @Trace: SafeOs_SUD_API_08202 */
  OS_CHECK_ALARM_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn, AlarmID, LblRemoteCall);

  /* polyspace<RTE: UNR : Not a defect : No Action Planned > If multicore is not defined, this violation occurs. but this code has already been verified and no impact of this rule violation */
  if (LenStatusReturn == E_OK)
  #else
  OS_UNUSED(LblRemoteCall);
  #endif
  {
    /* @Trace: SafeOs_SUD_API_08203 */
    /* Get the pointer to alarm structure */
    LpAlarm = &Os_GaaAlarm[AlarmID];

    /* Check whether alarm is active */
    if (LpAlarm->ucAlarmState == OS_ALARM_ACTIVE)
    {
      /* @Trace: SafeOs_SUD_API_08204 */
      /* Get the pointer to static counter structure */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
      LpStaticCounter = LpAlarm->pStaticAlarm->pStaticCounter;

      #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
      /* If Counter is a HW Counter, update counter tick from HW timer */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
      if (LpStaticCounter->pHwCounter != NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_08205 */
        Os_UpdateHwCounter(LpStaticCounter->pHwCounter);
      }
      #endif
      /* Check if absolute count of alarm is greater than current
       *   count of counter */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
      if (LpAlarm->ddAbsCount >= LpStaticCounter->pCounter->ddCurrentCount)
      {
        /* @Trace: SafeOs_SUD_API_08206 */
        /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "Tick have been checked by macro OS_CHECK_NULL_PTR before using" */
        /* Get the relative value in ticks before the alarm expires */
        *Tick = LpAlarm->ddAbsCount - LpStaticCounter->pCounter->ddCurrentCount;
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_08207 */
        /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "Tick have been checked by macro OS_CHECK_NULL_PTR before using" */
        /* Get the relative value in ticks before the alarm expires */
        *Tick = (LpStaticCounter->ddMaxAllowedValue - LpStaticCounter->pCounter->ddCurrentCount) \
                + (LpAlarm->ddAbsCount + OS_ONE);

      } /* End of else */
    } /* End of if (LpAlarm->ucAlarmState == OS_ALARM_ACTIVE) */
    else
    {
      /* @Trace: SafeOs_SUD_API_08208 */
      /* The Alarm is not active, return the proper error code */
      LenStatusReturn = E_OS_NOFUNC;
    }
  }
  return LenStatusReturn;
}

/***************************************************************************//**
 * Function Name        : Os_DoSetRelAlarm
 *
 * Service ID           : NA
 *
 * Description          : This service is used to set the relative alarm.
 *                        After <increment> ticks have elapsed, the task
 *                        assigned to the alarm <AlarmID> is activated
 *                        or the assigned event (only for extended tasks)
 *                        is set or the alarm-callback routine is called.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            AlarmID    Reference to an alarm
 *                                   (range : 0 ~ OS_ALARM_COUNT - 1)
 * @param [in]            Increment  Relative value in ticks
 *                                   (range : 1 ~ MaxAllowdValue of Counter)
 * @param [in]            Cycle      Cycle value in case of cyclic alarm. In
 *                                   case of single alarms, cycle shall be zero.
 *                                   (range : 0 ~ MaxAllowdValue of Counter)
 * @param [in]            LblRemoteCall Call from another Core
 *                                      (range : OS_TRUE, OS_FALSE)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_ACCESS : Alarm is not accessible
 *                        - E_OS_STATE : Alarm is already in use
 *
 * @pre                 : StartOS() function should be called,
 *                        AlarmID, Increment and Cycle should be checked
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaAlarm
 *
 *                        Function(s) invoked    :
 *                        Os_InsertAlarm(), Os_GetNextTick(),
 *                        Os_AdjustTimerInterrupt(), Os_UpdateHwCounter
 ******************************************************************************/
FUNC(StatusType, OS_CODE) Os_DoSetRelAlarm(AlarmType AlarmID,
                      TickType Increment, TickType Cycle, boolean LblRemoteCall)
{
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) LpStaticCounter;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  TickType LddAbsCount;
  StatusType LenStatusReturn;
  /* @Trace: SafeOs_SUD_API_08301 */
  LenStatusReturn = E_OK;
  /* Check whether Alarm is in use already */
  OS_CHECK_ALARM_INUSE_ERROR(AlarmID, &LenStatusReturn);

  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  /* @Trace: SafeOs_SUD_API_08302 */
  OS_CHECK_ALARM_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn, AlarmID, LblRemoteCall);
  #else
  OS_UNUSED(LblRemoteCall);
  #endif
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn == E_OK)
  #endif
  {
    /* @Trace: SafeOs_SUD_API_08303 */
    /* Get the pointer to static alarm structure */
    LpAlarm = &Os_GaaAlarm[AlarmID];
    /* Get the pointer to static counter structure */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
    LpStaticCounter = LpAlarm->pStaticAlarm->pStaticCounter;

    /* Check whether alarm is active */
    if (LpAlarm->ucAlarmState == OS_ALARM_SLEEP)
    {
      #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
      /* If Counter is a HW Counter, update counter tick from HW timer */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
      if (LpStaticCounter->pHwCounter != NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_08304 */
        Os_UpdateHwCounter(LpStaticCounter->pHwCounter);
      }
      #endif
      /* @Trace: SafeOs_SUD_API_08305 */
      /* Get the value in ticks before the alarm expires */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
      LddAbsCount = Os_GetNextTick(LpStaticCounter->pCounter->ddCurrentCount,
                                 Increment, LpStaticCounter->ddMaxAllowedValue);
      /* Store the absolute count value */
      LpAlarm->ddAbsCount = LddAbsCount;
      /* Store the cycle value */
      LpAlarm->ddCycle = Cycle;
      /* Change state of the alarm to Active */
      LpAlarm->ucAlarmState = OS_ALARM_ACTIVE;
      /* The alarm is inserted in the alarm object list of counter */
      Os_InsertAlarm(LpAlarm);
      #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
      /* Adjust timer interrupt to counter tick of first alarm */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
      if (LpStaticCounter->pHwCounter != NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_08306 */
        /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
        Os_AdjustTimerInterrupt(LpStaticCounter->pCounter->pHeadAlarm->ddAbsCount,
                                                         LpStaticCounter->pHwCounter);
        /* polyspace:end<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
      }
      #endif
    } /* End of if (LpAlarm->ucAlarmState == OS_ALARM_SLEEP) */
    else
    {
      /* @Trace: SafeOs_SUD_API_08307 */
      /* The alarm is in use, return the proper error code */
      LenStatusReturn = E_OS_STATE;
    }
  }

  return LenStatusReturn;
}

/***************************************************************************//**
 * Function Name        : Os_DoSetAbsAlarm
 *
 * Service ID           : NA
 *
 * Description          : This service is used to set the absolute alarm.
 *                        When <start> ticks are reached, the configured
 *                        action takes place.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            AlarmID    Reference to an alarm
 *                                   (range : 0 ~ OS_ALARM_COUNT - 1)
 * @param [in]            Start      Absolute value in ticks
 *                                   (range : 0 ~ MaxAllowdValue of Counter)
 * @param [in]            Cycle      Cycle value in case of cyclic alarm. In
 *                                   case of single alarms, cycle shall be zero.
 *                                   (range : 0 ~ MaxAllowdValue of Counter)
 * @param [in]            LblRemoteCall Call from another Core
 *                                      (range : OS_TRUE, OS_FALSE)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_ACCESS : Alarm is not accessible
 *                        - E_OS_STATE : Alarm is already in use
 *
 * @pre                 : StartOS() function should be called,
 *                        AlarmID, Start and Cycle should be checked
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaAlarm
 *
 *                        Function(s) invoked    :
 *                        Os_InsertAlarm(), Os_AdjustTimerInterrupt(),
 *                        Os_UpdateHwCounter()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE) Os_DoSetAbsAlarm(AlarmType AlarmID, TickType Start,
                                          TickType Cycle, boolean LblRemoteCall)
{
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) LpStaticCounter;
  #endif
  /* @Trace: SafeOs_SUD_API_08101 */
  StatusType LenStatusReturn = E_OK;

  /* Check whether Alarm is in use already */
  OS_CHECK_ALARM_INUSE_ERROR(AlarmID, &LenStatusReturn);

  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
    /* @Trace: SafeOs_SUD_API_08102 */
  OS_CHECK_ALARM_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn, AlarmID, LblRemoteCall);
  #else
  OS_UNUSED(LblRemoteCall);
  #endif
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn == E_OK)
  #endif
  {
    /* @Trace: SafeOs_SUD_API_08103 */
    /* Get the pointer to static alarm structure */
    LpAlarm = &Os_GaaAlarm[AlarmID];

    /* Check whether alarm is active */
    if (LpAlarm->ucAlarmState == OS_ALARM_SLEEP)
    {
      /* @Trace: SafeOs_SUD_API_08104 */
      /* Store Absolute count */
      LpAlarm->ddAbsCount = Start;
      /* Store cycle */
      LpAlarm->ddCycle = Cycle;
      /* Change state of the alarm to Active */
      LpAlarm->ucAlarmState = OS_ALARM_ACTIVE;
      /* The alarm is inserted in the alarm object list of counter */
      Os_InsertAlarm(LpAlarm);
      #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
      /* @Trace: SafeOs_SUD_API_08105 */
      /* Get the pointer to counter */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
      LpStaticCounter = LpAlarm->pStaticAlarm->pStaticCounter;
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
      if (LpStaticCounter->pHwCounter != NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_08106 */
        /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
        Os_UpdateHwCounter(LpStaticCounter->pHwCounter);
        /* Adjust timer interrupt to counter tick of first alarm */
        /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
        Os_AdjustTimerInterrupt(
                              LpStaticCounter->pCounter->pHeadAlarm->ddAbsCount,
                                                   LpStaticCounter->pHwCounter);
        /* polyspace:end<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
      }
      #endif
    } /* End of if (LpAlarm->ucAlarmState == OS_ALARM_SLEEP) */
    else
    {
      /* @Trace: SafeOs_SUD_API_08107 */
      /* The alarm is in use, return the proper error code */
      LenStatusReturn = E_OS_STATE;
    }
  }

  return LenStatusReturn;
}

/***************************************************************************//**
 * Function Name        : Os_DoCancelAlarm
 *
 * Service ID           : NA
 *
 * Description          : This service is used to cancel the alarm
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param [in]            AlarmID       Reference to an alarm
 *                                      (range : 0 ~ OS_ALARM_COUNT - 1)
 * @param [in]            LblRemoteCall Call from another Core
 *                                      (range : OS_TRUE, OS_FALSE)
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_NOFUNC : Alarm is already Sleep
 *                        - E_OS_ACCESS : Alarm is not accessible
 *
 * @pre                 : StartOS() function should be called,
 *                        AlarmID should be checked
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaAlarm
 *
 *                        Function(s) invoked    :
 *                        Os_RemoveAlarm()
 ******************************************************************************/
FUNC(StatusType, OS_CODE) Os_DoCancelAlarm(AlarmType AlarmID, boolean LblRemoteCall)
{
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  /* @Trace: SafeOs_SUD_API_08001 */
  StatusType LenStatusReturn = E_OK;

  /* Check whether Alarm is in use already */
  OS_CHECK_ALARM_INUSE_ERROR(AlarmID, &LenStatusReturn);

  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
    /* @Trace: SafeOs_SUD_API_08002 */
  OS_CHECK_ALARM_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn, AlarmID, LblRemoteCall);
  #else
  OS_UNUSED(LblRemoteCall);
  #endif
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn == E_OK)
  #endif
  {
    /* @Trace: SafeOs_SUD_API_08003 */
    /* Get the pointer to static alarm structure */
    LpAlarm = &Os_GaaAlarm[AlarmID];

    /* verify the alarm is active  */
    if (LpAlarm->ucAlarmState == OS_ALARM_ACTIVE)
    {
      /* @Trace: SafeOs_SUD_API_08004 */
      /* The alarm is removed from the alarm object list of counter */
      Os_RemoveAlarm(LpAlarm);
      /* State of the Alarm is changed to sleep */
      LpAlarm->ucAlarmState = OS_ALARM_SLEEP;
    } /* End of if (LpAlarm->ucAlarmState == OS_ALARM_ACTIVE) */
    else
    {
      /* @Trace: SafeOs_SUD_API_08005 */
      /* The alarm is not in use, return the proper error code */
      LenStatusReturn = E_OS_NOFUNC;
    }
  }

  return LenStatusReturn;
}
#endif /* End of if (OS_ALARM == STD_ON) */

/***************************************************************************//**
 * Function Name        : Os_ProcessAlarm
 *
 * Service ID           : NA
 *
 * Description          : This service checks alarm expires and
 *                        process alarm action
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param [in]            LpStaticCounter    Pointer to static counter structure
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - E_OS_LIMIT : Too many task activations
 *                        - E_OS_ACCESS : Referenced task is not accessible
 *                        - E_OS_STATE : Referenced task is in suspended state
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Os_RemoveAlarm(), pAlarmExpFunc(),
 *                        Os_GetNextTick(), Os_InsertAlarm(),
 *                        Os_IntDisableCat2Isr(), Os_IntRestore()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80018 */
#if (OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_ProcessAlarm(P2CONST(Tdd_Os_StaticCounter,
                                           AUTOMATIC, OS_CONST) LpStaticCounter)
{
  TickType LddCurrentCount;
  TickType LddCount;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  P2CONST(Tdd_Os_StaticAlarm, AUTOMATIC, OS_CONST) LpStaticAlarm;
  P2VAR(Tdd_Os_Counter, AUTOMATIC, OS_VAR) LpCounter;
  /* @Trace: SafeOs_SUD_API_08401 */
  StatusType LddStatusReturn = E_OK;
  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  Os_IntStatus_T LddIntLevel;
  #endif

  /* Get the pointer to counter */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
  LpCounter = LpStaticCounter->pCounter;
  LddCurrentCount = LpCounter->ddCurrentCount;

  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  /* SuspendOSInterrupts */
  /* @Trace: SafeOs_SUD_API_08402 */
  LddIntLevel = Os_IntDisableCat2Isr();
  #endif

  /* Check if the counter has reached the next alarm activation date */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
  /* @Trace: SafeOs_SUD_API_08403 */
  LpAlarm = LpCounter->pHeadAlarm;

  while ((LpAlarm != NULL_PTR) && (LpAlarm->ddAbsCount == LddCurrentCount))
  {
    /* @Trace: SafeOs_SUD_API_08404 */
    /* Get the time object from the queue */
    Os_RemoveAlarm(LpAlarm);

    /* Get the pointer to Static Alarm */
    /* polyspace-begin RTE:NIP [Not a defect: No Action Planned]  ptr points to a valid value and code is verified manually */
    LpStaticAlarm = LpAlarm->pStaticAlarm;
    /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function and code is verified manually */
    if(LpStaticAlarm->pActivateTask != NULL_PTR)
    {
      LddStatusReturn |= LpStaticAlarm->pActivateTask->pActivateTaskFunc(
                                                         LpStaticAlarm->pActivateTask);
    }
    else if(LpStaticAlarm->pAlarmEvent != NULL_PTR)
    {
      LddStatusReturn |= LpStaticAlarm->pAlarmEvent->pAlarmEventFunc(LpStaticAlarm->pAlarmEvent);
    }
    else if(LpStaticAlarm->pIncrementCounter != NULL_PTR)
    {
      LddStatusReturn |= LpStaticAlarm->pIncrementCounter->pIncrementCounterFunc(
                                                             LpStaticAlarm->pIncrementCounter);
    }
    else if(LpStaticAlarm->pAlarmCallback != NULL_PTR)
    {
      LddStatusReturn |= LpStaticAlarm->pAlarmCallback->pAlarmCallbackFunc(
                                                           LpStaticAlarm->pAlarmCallback);
    }
    else if(LpStaticAlarm->pSchedTable != NULL_PTR)
    {
      LddStatusReturn |= LpStaticAlarm->pSchedTable->pSchedTableFunc(LpStaticAlarm->pSchedTable);
    }
    else
    {
      LddStatusReturn = E_NOT_OK;
    }
    /* polyspace-end RTE:NIP [Not a defect: No Action Planned]  ptr points to a valid value and code is verified manually */
    /* Rearm the alarm if needed   */
    if (LpAlarm->ddCycle != OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_08405 */
      /* If the cycle is not zero, the new count is computed by adding the
       *   cycle to the current count */
      LddCount = Os_GetNextTick(LpAlarm->ddAbsCount, LpAlarm->ddCycle,
                                            LpStaticCounter->ddMaxAllowedValue);

      /* Assign the computed value to Alarm's ddAbsCount */
      LpAlarm->ddAbsCount = LddCount;
      /* Put back Alarm in the alarm queue of the counter it belongs to */
      Os_InsertAlarm(LpAlarm);
    } /* End of if (LpAlarm->ddCycle != OS_ZERO) */
    else
    {
      /* @Trace: SafeOs_SUD_API_08406 */
      /* If Cycle is zero then change state of the alarm */
      LpAlarm->ucAlarmState = OS_ALARM_SLEEP;
    }

    #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
    /* ResumeOSInterrupts */
    /* @Trace: SafeOs_SUD_API_08407 */
    Os_IntRestore(LddIntLevel);
    #endif

    /* Execute pending Cat2 ISR here */

    #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
    /* SuspendOSInterrupts */
    /* @Trace: SafeOs_SUD_API_08408 */
    LddIntLevel = Os_IntDisableCat2Isr();
    #endif

    /* Get the next alarm to raise */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
    /* @Trace: SafeOs_SUD_API_08409 */
    LpAlarm = LpCounter->pHeadAlarm;
  } /* End of @while ((LpAlarm != NULL_PTR) && (LpAlarm->ddAbsCount == ... */

  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  /* ResumeOSInterrupts */
  /* @Trace: SafeOs_SUD_API_08410 */
  Os_IntRestore(LddIntLevel);
  #endif

  return LddStatusReturn;
}
#endif /* #if(OS_ALARM == STD_ON)||(OS_SCHEDTABLE == STD_ON) */
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define OS_API_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#if (OS_ALARM == STD_ON)
/***************************************************************************//**
 * Function Name        : Os_CallGetAlarmBase
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
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
FUNC(StatusType, OS_CODE) Os_CallGetAlarmBase(AlarmType AlarmID,  AlarmBaseRefType Info)
{  
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_57101 */
  LddStatusReturn = OS_SYSCALL_GETALARMBASE(AlarmID, Info);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : Os_CallGetAlarm
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
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
FUNC(StatusType, OS_CODE) Os_CallGetAlarm(AlarmType AlarmID,  TickRefType Tick)
{  
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_57201 */
  LddStatusReturn = OS_SYSCALL_GETALARM(AlarmID, Tick);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : Os_CallCancelAlarm
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
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE) Os_CallCancelAlarm(AlarmType AlarmID)
{  
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_57301 */
  LddStatusReturn = OS_SYSCALL_CANCELALARM(AlarmID);

  return LddStatusReturn;
}
#endif
#define OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end RTE:COR [Not a defect:Low] "ptr points to a valid value and code is verified manually" */
/* polyspace-end MISRA-C3:11.3 [Justified:Low] "This typecast is needed in order to implement a common interface for performing an alarm action" */
/* polyspace-end RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually." */
/* polyspace-end RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "ptr points to a valid value and code is verified manually" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "ptr points to a valid value and code is verified manually" */
/* polyspace-end MISRA-C3:21.15 [Not a defect:No action planned] "This is Standard Library" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
