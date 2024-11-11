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
**  SRC-MODULE: Os_SchedTable.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Schedule Table functionality.                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.5.3     16-Feb-2024   HG.Kim           Jira CP44-3828                    **
** 1.5.1     20-Sep-2023   HJ.Kim           Jira CP44-XXXX                    **
**           06-Oct-2023   JC.Kim           Jira CP44-2438                    **
** 1.5.0     26-Jun-2023   HJ.Kim           Jira CP44-2459                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
**                         SH.Yoo           Jira CP44-2006                    **
** 1.3.12.0  09-Mar-2023   TanHX            Jira CP44-1335                    **
** 1.3.11.0  23-Sep-2022   KhanhPQ8         Jira CP44-684                     **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.5     07-Oct-2020   DanhDC1          R44-Redmine #15959                **
**                                          Remove un-used function           **
** 1.0.4     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
**                                          R44-Redmine #12870                **
** 1.0.3     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C  17.7,8.5           **
** 1.0.2     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.1     04-Aug-2020   TamNN1           R44-Redmine #14634 Fixed issue    **
**                                          Ajusting  the offset for next     **
**                                          expiry point is Not correct.      **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os Ram header file */
#include "Os_Alarm.h"             /* Os Alarm header file */
#include "Os_SchedTable.h"        /* Os ScheduleTable header file */
#include "Os_Error.h"             /* Os Error header file */
#include "Os_SystemCallTable.h"

/* @Trace: SRS_BSW_00410 */
#if (OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Application.h"       /* Os Application header file */
#endif
#if (OS_MULTICORE == STD_ON)
#include "Os_MulticoreMessage.h"
#endif
#include "Os_Counter.h"

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

#if (OS_SCHEDTABLE == STD_ON)
static FUNC(StatusType, OS_CODE) Os_StopSchedTabService(ScheduleTableType
                                                               ScheduleTableID);
static FUNC(StatusType, OS_CODE) Os_ProcessSchedTableEnd
                                            (ScheduleTableType ScheduleTableID);
#endif
#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
static FUNC(TickType, OS_CODE) Os_GetMinValue(TickType LddMaxPeriod,
                                                        TickType LddDeviation);
static  FUNC(StatusType, OS_CODE) Os_DoAdjustScheduleTableRuntime
                                    (ScheduleTableType ScheduleTableID, \
                                      sint64 PosOnSchedTable);
#endif

/*******************************************************************************
** Function Name        : Os_KernStartScheduleTableRel                        **
**                                                                            **
** Service ID           : OSServiceId_StartScheduleTableRel                   **
**                                                                            **
** Description          : This service does the processing of the schedule    **
**                        table at "Offset" relative to the "Now" value on the**
**                        underlying counter.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID, Offset                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendStartScheduleTableRel(),                     **
**                        Os_DoStartScheduleTableRel()                        **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11002 SRS_Os_80013 SRS_Os_00098 SRS_Os_00099 */
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernStartScheduleTableRel(ScheduleTableType
                                               ScheduleTableID, TickType Offset)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(STARTSCHEDULETABLEREL, LenStatusReturn);
  /* Check whether the ScheduleTableID is valid or not */
  OS_CHECK_SCHEDTABLE_ID_ERROR(ScheduleTableID, &LenStatusReturn);
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID have been checked before using" */
  /* Check whether the Offset is zero or greater than OsCounterMaxAllowedValue
   * of the underlying counter minus Initial Offset */
  OS_CHECK_SCHEDTABLE_OFFSET_VALUE_ERROR(ScheduleTableID, Offset, LenStatusReturn);
  /* Check whether the Schedule table is implicitly synchronised */
  OS_CHECK_IMPLICIT_SCHEDTABLE_STRATEGY_ERROR(ScheduleTableID, LenStatusReturn);
  /* polyspace +2 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
  /* Check whether Application can access the Scheduletable */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, ScheduleTableID);
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID have been checked before using" */
  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    #if (OS_MULTICORE == STD_ON)
    /* @Trace : SafeOs_SUD_API_13601 */
    /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];

    /* Check if ScheduleTable belongs to same core */
    if (LpStaticSchedTable->ddCoreID != OS_CORE_ID)
    {
      /* @Trace : SafeOs_SUD_API_13602 */
      /* Call Os_SendStartScheduleTableRel and get the return value */
      LenStatusReturn = Os_SendStartScheduleTableRel(ScheduleTableID, Offset);
    } /* End of if (LpStaticSchedTable->ddCoreID != OS_CORE_ID) */
    else
    #endif
    {
      /* @Trace : SafeOs_SUD_API_13603 */
      /* Call Os_DoStartScheduleTableRel and get the return value */
      LenStatusReturn = Os_DoStartScheduleTableRel(ScheduleTableID, Offset, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_13604 */
    /* Store the service id */
    OS_STORE_SERVICE(OSServiceId_StartScheduleTableRel);
    /* Store the parameter 1 - ScheduleTableID */
    OS_STORE_PARAM1_SCHEDTABLEID(ScheduleTableID);
    /* Store the parameter 2 - Offset */
    OS_STORE_PARAM2_OFFSET(Offset);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif

  /* Return the value */
  return (LenStatusReturn);
} /* End of StartScheduleTableRel(ScheduleTableType */
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_DoStartScheduleTableRel                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service does the processing of the schedule    **
**                        table at "Offset" relative to the "Now" value on the**
**                        underlying counter.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID, Offset, LblRemoteCall              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable, Os_GaaAlarm                 **
**                        Os_GaaSchedTable                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_InsertAlarm(), Os_GetNextTick(),                 **
**                        Os_AdjustTimerInterrupt(), Os_UpdateHwCounter()     **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_DoStartScheduleTableRel(ScheduleTableType
                        ScheduleTableID, TickType Offset, boolean LblRemoteCall)
{
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) LpStaticCounter;
  P2CONST(Tdd_Os_ExpiryPoint, AUTOMATIC, OS_CONST) LpExpPoint;
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) LpSchedTable;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  TickType LddDate;
  StatusType LenStatusReturn;

  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;

  /* Check whether a related alarm is in use already */
  OS_CHECK_SCHEDTABLE_INUSE_ERROR(ScheduleTableID, &LenStatusReturn);

  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  /* Check whether Application is accessible */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn,
                                                ScheduleTableID, LblRemoteCall);
  #else
  OS_UNUSED(LblRemoteCall);
  #endif

  if(LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_13201 */
    /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];
    /* Get the pointer to the corresponding alarm associated with the
     * schedule table */
    LpAlarm = &Os_GaaAlarm[LpStaticSchedTable->ddAlarmIndex];

    /* Check whether schedule table is already started */
    if (LpAlarm->ucAlarmState == SCHEDULETABLE_STOPPED)
    {
      /* @Trace : SafeOs_SUD_API_13202 */
      /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
      LpSchedTable = &Os_GaaSchedTable[ScheduleTableID];

      /* Get the pointer to the initial expiry point */
      LpExpPoint = LpStaticSchedTable->pExpiryPoint;
      /* Get the pointer to corresponding static counter associated with the
       *   schedule table */
      LpStaticCounter = LpStaticSchedTable->pStaticCounter;
      #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
      /* If Counter is a HW Counter, update counter tick from HW timer */
      if (LpStaticCounter->pHwCounter != NULL_PTR)
      {
        /* @Trace : SafeOs_SUD_API_13203 */
        Os_UpdateHwCounter(LpStaticCounter->pHwCounter);
      }
      #endif
      /* Get the "offset" relative to the "now" value on the underlying
       * counter into local variable */
      /* polyspace-begin RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      LddDate = Os_GetNextTick(LpStaticCounter->pCounter->ddCurrentCount,
             Offset + LpExpPoint->ddOffset, LpStaticCounter->ddMaxAllowedValue);
      /* Load the Offset at which the initial expiry point shall be processed */
      LpAlarm->ddAbsCount = LddDate;
      /* Update ddExpiryOffset for the ScheduleTable with First expiry offset */
      LpSchedTable->ddExpiryOffset = LpExpPoint->ddOffset;
      /* Start scheduleTable from 1st Index */
      LpSchedTable->ulIndex = OS_ZERO;
      /* Set the Schedule table state to running */
      LpAlarm->ucAlarmState = SCHEDULETABLE_RUNNING;
      /* Insert the alarm object */
      Os_InsertAlarm(LpAlarm);
      #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
      /* Adjust timer interrupt to counter tick of first alarm */
      if (LpStaticCounter->pHwCounter != NULL_PTR)
      {
        /* @Trace : SafeOs_SUD_API_13204 */
        /* polyspace +3 RTE:NIP [Not a defect:Unset] "variable is initialized and code is verified manually" */
        /* polyspace +2 RTE:COR [Not a defect:Low] "function ptr points to a valid function and code is manually checked" */
        Os_AdjustTimerInterrupt(
                              LpStaticCounter->pCounter->pHeadAlarm->ddAbsCount,
                                                   LpStaticCounter->pHwCounter);
      /* polyspace-end RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      }
      #endif
    } /* End of if (LpAlarm->ucAlarmState == SCHEDULETABLE_STOPPED) */
    else
    {
      /* @Trace : SafeOs_SUD_API_13205 */
      /* Set the value E_OS_STATE in the variable LenstatusReturn */
      LenStatusReturn = E_OS_STATE;
    }
  } /* End of @ if(LenStatusReturn == E_OK) */

  /* Return The value */
  return (LenStatusReturn);
}
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernStartScheduleTableAbs                        **
**                                                                            **
** Service ID           : OSServiceId_StartScheduleTableAbs                   **
**                                                                            **
** Description          : This service does the processing of the schedule    **
**                        table at absolute value "Start" of the underlying   **
**                        counter.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID, Start                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendStartScheduleTableAbs(),                     **
**                        Os_DoStartScheduleTableAbs()                        **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11002 SRS_Os_80018 SRS_Os_00098 SRS_Os_00099 */
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernStartScheduleTableAbs(ScheduleTableType
                                                ScheduleTableID, TickType Start)
{
  StatusType LenStatusReturn;

  #if (OS_MULTICORE == STD_ON)
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(STARTSCHEDULETABLEABS, LenStatusReturn);
  /* Check whether the ScheduleTableID is valid or not */
  OS_CHECK_SCHEDTABLE_ID_ERROR(ScheduleTableID, &LenStatusReturn);
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID have been checked before using" */
  /* Check whether the Start is greater than OsCounterMaxAllowedValue of the
   *   underlying counter */
  OS_CHECK_SCHEDTABLE_TICK_VALUE(ScheduleTableID, Start, LenStatusReturn);
  /* polyspace +2 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
  /* Check whether Scheduletable can access the Application */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, ScheduleTableID);
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID have been checked before using" */
  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_13101 */
    #if (OS_MULTICORE == STD_ON)
    /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];

    /* Check if ScheduleTable belongs to same core */
    if (LpStaticSchedTable->ddCoreID != OS_CORE_ID)
    {
      /* @Trace : SafeOs_SUD_API_13102 */
      /* Call Os_SendStartScheduleTableAbs and get the return value */
      LenStatusReturn = Os_SendStartScheduleTableAbs(ScheduleTableID, Start);
    } /* End of if (LpStaticSchedTable->ddCoreID != OS_CORE_ID) */
    else
    #endif
    {
      /* @Trace : SafeOs_SUD_API_13103 */
      /* Call Os_DoStartScheduleTableAbs and get the return value */
      LenStatusReturn = Os_DoStartScheduleTableAbs(ScheduleTableID, Start, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_13104 */
    /* Store the service id */
    OS_STORE_SERVICE(OSServiceId_StartScheduleTableAbs);
    /* Store the parameter 1 - ScheduleTableID */
    OS_STORE_PARAM1_SCHEDTABLEID(ScheduleTableID);
    /* Store the parameter 2 - Start */
    OS_STORE_PARAM2_START(Start);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif

  /* Return the value */
  return (LenStatusReturn);
} /* End of StartScheduleTableAbs(ScheduleTableType */
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_DoStartScheduleTableAbs                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service does the processing of the schedule    **
**                        table at absolute value "Start" of the underlying   **
**                        counter.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID, Start, LblRemoteCall               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable, Os_GaaAlarm                 **
**                        Os_GaaSchedTable                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_InsertAlarm(), Os_GetNextTick(),                 **
**                        Os_AdjustTimerInterrupt(), Os_UpdateHwCounter()     **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_DoStartScheduleTableAbs(ScheduleTableType
                         ScheduleTableID, TickType Start, boolean LblRemoteCall)
{
  StatusType LenStatusReturn;
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) LpStaticCounter;
  P2CONST(Tdd_Os_ExpiryPoint, AUTOMATIC, OS_CONST) LpExpPoint;
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) LpSchedTable;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  TickType LddDate;

  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;

  /* Check whether a related alarm is in use already */
  OS_CHECK_SCHEDTABLE_INUSE_ERROR(ScheduleTableID, &LenStatusReturn);

  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  /* Check whether Application is accessible */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn,
                                                ScheduleTableID, LblRemoteCall);
  #else
  OS_UNUSED(LblRemoteCall);
  #endif

  if(LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_13501 */
    /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];
    /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
    LpSchedTable = &Os_GaaSchedTable[ScheduleTableID];
    /* Get the pointer to the corresponding alarm associated with the
     * schedule table */
    LpAlarm = &Os_GaaAlarm[LpStaticSchedTable->ddAlarmIndex];

    /* Check whether schedule table is already started */
    if (LpAlarm->ucAlarmState == SCHEDULETABLE_STOPPED)
    {
      /* @Trace : SafeOs_SUD_API_13502 */
      /* Get the pointer to corresponding static counter associated with the
       * schedule table */
      LpStaticCounter = LpStaticSchedTable->pStaticCounter;
      /* Get the pointer to the initial expiry point */
      LpExpPoint = LpStaticSchedTable->pExpiryPoint;
      /* Get the "offset" relative to the absolute "Start" value on the
       * underlying counter into local variable */
      LddDate = Os_GetNextTick(Start, LpExpPoint->ddOffset, LpStaticCounter->ddMaxAllowedValue);
      /* Load the Offset at which the initial expiry point shall be
       * processed */
      LpAlarm->ddAbsCount = LddDate;
      /* Update ddExpiryOffset for the ScheduleTable with First expiry
       * offset */
      LpSchedTable->ddExpiryOffset = LpExpPoint->ddOffset;
      /* Start scheduleTable from first Index */
      LpSchedTable->ulIndex = OS_ZERO;

      #if (OS_SCHED_IMPLICIT_SYNC == STD_ON)
      /* Check weather ScheduleTable is implicitly syncronised */
      if (LpStaticSchedTable->ucSynchStrategy == OS_SCHEDTABLE_IMPLICIT_SYNC)
      {
        /* @Trace : SafeOs_SUD_API_13503 */
        /* Set the Schedule table state to running & Synchronous */
        LpAlarm->ucAlarmState = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
      }
      else
      #endif /* End of if (OS_SCHED_IMPLICIT_SYNC == STD_ON) */
      {
        /* @Trace : SafeOs_SUD_API_13504 */
        /* Set the Schedule table state to running */
        LpAlarm->ucAlarmState = SCHEDULETABLE_RUNNING;
      }
      /* Insert the alarm object */
      Os_InsertAlarm(LpAlarm);
      #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
      if (LpStaticCounter->pHwCounter != NULL_PTR)
      {
        /* @Trace : SafeOs_SUD_API_13505 */
        Os_UpdateHwCounter(LpStaticCounter->pHwCounter);
        /* polyspace +5 RTE:NIP [Not a defect:Unset] "variable is initialized and code is verified manually" */
        /* polyspace +4 RTE:COR [Not a defect:Low] "function ptr points to a valid function and code is manually checked" */
        /* polyspace +3 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
        /* Adjust timer interrupt to counter tick of first alarm */
        Os_AdjustTimerInterrupt(
                              LpStaticCounter->pCounter->pHeadAlarm->ddAbsCount,
                                                   LpStaticCounter->pHwCounter);
      }
      #endif
    } /* End of if (LpAlarm->ucAlarmState == SCHEDULETABLE_STOPPED) */
    else
    {
      /* @Trace : SafeOs_SUD_API_13506 */
      /* Set the value E_OS_STATE in the variable LenStatusReturn  */
      LenStatusReturn = E_OS_STATE;
    }
  } /* @End of if(LenStatusReturn == E_OK) */

  /* Return the value */
  return (LenStatusReturn);
} /* End of StartScheduleTableAbs(ScheduleTableType */
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernStopScheduleTable                            **
**                                                                            **
** Service ID           : OSServiceId_StopScheduleTable                       **
**                                                                            **
** Description          : This service changes the state of the schedule      **
**                        table to "Stopped" state.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendStopScheduleTable(),                         **
**                        Os_DoStopScheduleTable()                            **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11002 SRS_Os_80013 */
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernStopScheduleTable(ScheduleTableType ScheduleTableID)
{
  StatusType LenStatusReturn;

  #if (OS_MULTICORE == STD_ON)
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(STOPSCHEDULETABLE, LenStatusReturn);
  /* Check whether the ScheduleTableID is valid or not */
  OS_CHECK_SCHEDTABLE_ID_ERROR(ScheduleTableID, &LenStatusReturn);
  /* polyspace +3 MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID have been checked before using" */
  /* polyspace +2 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
  /* Check whether Application can access the Scheduletable */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, ScheduleTableID);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_12701 */
    #if (OS_MULTICORE == STD_ON)
    /*Get the pointer to corresponding Schedule Table with ScheduleTableID */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];

    /* Check if ScheduleTable belongs to same core */
    if (LpStaticSchedTable->ddCoreID != OS_CORE_ID)
    {
      /* @Trace : SafeOs_SUD_API_12702 */
      /* Call Os_SendStopScheduleTable and get the return value */
      LenStatusReturn = Os_SendStopScheduleTable(ScheduleTableID);
    } /* End of if (LpStaticSchedTable->ddCoreID != OS_CORE_ID) */
    else
    #endif
    {
      /* @Trace : SafeOs_SUD_API_12703 */
      /* Call Os_DoStopScheduleTable and get the return value */
      LenStatusReturn = Os_DoStopScheduleTable(ScheduleTableID, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_12704 */
    /* Store the service id */
    OS_STORE_SERVICE(OSServiceId_StopScheduleTable);
    /* Store the parameter 1 - ScheduleTableID */
    OS_STORE_PARAM1_SCHEDTABLEID(ScheduleTableID);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif
  /* Return the value */
  return (LenStatusReturn);
} /* End of StopScheduleTable(ScheduleTableType ScheduleTableID) */
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_DoStopScheduleTable                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service changes the state of the schedule      **
**                        table to "Stopped" state.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID, LblRemoteCall                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StopSchedTabService()                            **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE)
Os_DoStopScheduleTable(ScheduleTableType ScheduleTableID, boolean LblRemoteCall)
{
  /* @Trace : SafeOs_SUD_API_12201 */
  StatusType LenStatusReturn;

  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;

  /* Check whether a related alarm is in use already */
  OS_CHECK_SCHEDTABLE_INUSE_ERROR(ScheduleTableID, &LenStatusReturn);

  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  /* Check whether Application is accessible */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn,
                                                ScheduleTableID, LblRemoteCall);
  #else
  OS_UNUSED(LblRemoteCall);
  #endif
  if(LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_12202 */
    LenStatusReturn = Os_StopSchedTabService(ScheduleTableID);
  }

  return (LenStatusReturn);
} /* End of Os_DoStopScheduleTable(ScheduleTableType ScheduleTableID) */
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_StopSchedTabService                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service changes the state of the schedule      **
**                        table to "Stopped" state.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable, Os_GaaAlarm                 **
**                        Os_GaaSchedTable                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_RemoveAlarm()                                    **
*******************************************************************************/
/* @Trace: SRS_Os_00098 SRS_Os_00099 SRS_Os_11002 */
#if (OS_SCHEDTABLE == STD_ON)
static FUNC(StatusType, OS_CODE) Os_StopSchedTabService(ScheduleTableType ScheduleTableID)
{
  StatusType LenStatusReturn;
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTableNext;
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) LpSchedTable;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;

  /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
  LpSchedTable = &Os_GaaSchedTable[ScheduleTableID];
  /* Get the pointer to corresponding schedule table */
  LpStaticSchedTable = &Os_GaaStaticSchedTable[LpSchedTable->ddSchedTableId];
  /* Get the pointer to the corresponding alarm associated with the
   * schedule table */
  LpAlarm = &Os_GaaAlarm[LpStaticSchedTable->ddAlarmIndex];

  /* Check whether schedule table is already stopped or not */
  if (LpAlarm->ucAlarmState != SCHEDULETABLE_STOPPED)
  {
    /* @Trace : SafeOs_SUD_API_12601 */
    LenStatusReturn = E_OK;
    /* Set cycle of alarm to zero */
    LpAlarm->ddCycle = OS_ZERO;
    /* Remove the alam object from the queue from further processing of the
     * expiry points associated to schedule table */
    Os_RemoveAlarm(LpAlarm);
    /* Set the Schedule table state to stopped */
    LpAlarm->ucAlarmState = SCHEDULETABLE_STOPPED;

    /* Check whether next schedule table exists or not */
    if ((LpSchedTable->ddNextSchedTable) != OS_INVALID_VALUE)
    {
      /* @Trace : SafeOs_SUD_API_12602 */
      /* Get the pointer to next schedule table */
      LpStaticSchedTableNext = &Os_GaaStaticSchedTable[(LpSchedTable->ddNextSchedTable)];
      /* If the schedule table has already set to next schedule table, set
       * next schedule table to stopped */
      Os_GaaAlarm[LpStaticSchedTableNext->ddAlarmIndex].ucAlarmState = SCHEDULETABLE_STOPPED;
      /* Update NextScheduleTable with invalid value */
      (LpSchedTable->ddNextSchedTable) = OS_INVALID_VALUE;
    } /* End of if ((LpSchedTable->ddNextSchedTable) != OS_INVALID_VALUE) */
  } /* End of if (LpAlarm->ucAlarmState != SCHEDULETABLE_STOPPED) */
  else
  {
    /* @Trace : SafeOs_SUD_API_12603 */
    /* Set the value E_OS_NOFUNC in the variable LenStatusReturn */
    LenStatusReturn = E_OS_NOFUNC;
  }
  return (LenStatusReturn);
} /* End of Os_StopSchedTabService(ScheduleTableType ScheduleTableID) */
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */


/*******************************************************************************
** Function Name        : Os_KernNextScheduleTable                            **
**                                                                            **
** Service ID           : OSServiceId_NextScheduleTable                       **
**                                                                            **
** Description          : This service does the processing of schedule table  **
**                        <ScheduleTableID_To> <ScheduleTableID_From>.Final   **
**                        Delay ticks after the Final Expiry Point on         **
**                        <ScheduleTableID_From> is processed.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID_From, ScheduleTableID_To            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendNextScheduleTable(),                         **
**                        Os_DoNextScheduleTable()                            **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11002 SRS_Os_00098 SRS_Os_00099 */
#if (OS_SCHEDTABLE == STD_ON)
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
FUNC(StatusType, OS_CODE) Os_KernNextScheduleTable(
   ScheduleTableType ScheduleTableID_From, ScheduleTableType ScheduleTableID_To)
{
  StatusType LenStatusReturn;

  #if (OS_MULTICORE == STD_ON)
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(NEXTSCHEDULETABLE, LenStatusReturn);
  /* Check whether the ScheduleTableID is valid or not */
  OS_CHECK_NEXT_SCHEDTABLE_ID_ERROR(ScheduleTableID_From,ScheduleTableID_To, LenStatusReturn);
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID_To, ScheduleTableID_From index is checked by macro OS_CHECK_NEXT_SCHEDTABLE_ID_ERROR before using." */
  /* Check whether it is driven by the same counter */
  OS_CHECK_SCHEDTABLE_COUNTERS(ScheduleTableID_From, ScheduleTableID_To, LenStatusReturn);
  /* Check whether both the sched are having same strategy */
  OS_CHECK_NEXT_SCHEDTABLE_STRATEGY_ERROR(ScheduleTableID_From,
                                           ScheduleTableID_To, LenStatusReturn);
  /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
  /* Check whether Application can access the Scheduletable */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, ScheduleTableID_From);
  /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
  /* Check whether Application can access the Scheduletable */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, ScheduleTableID_To);
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID_To, ScheduleTableID_From index is checked by macro OS_CHECK_NEXT_SCHEDTABLE_ID_ERROR before using." */
  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_13701 */
    #if (OS_MULTICORE == STD_ON)
    /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID_To];

    /* Check if ScheduleTable belongs to same core */
    if (LpStaticSchedTable->ddCoreID != OS_CORE_ID)
    {
      /* @Trace : SafeOs_SUD_API_13702 */
      /* Call Os_SendNextScheduleTable and get the return value */
      LenStatusReturn = Os_SendNextScheduleTable(ScheduleTableID_From, ScheduleTableID_To);
    } /* End of if (LpStaticSchedTable->ddCoreID != OS_CORE_ID) */
    else
    #endif
    {
      /* @Trace : SafeOs_SUD_API_13703 */
      /* Call Os_DoNextScheduleTable and get the return value */
      LenStatusReturn = Os_DoNextScheduleTable(ScheduleTableID_From, ScheduleTableID_To, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_13704 */
    /* Store the service id */
    OS_STORE_SERVICE(OSServiceId_NextScheduleTable);
    /* Store the parameter 1 -ScheduleTableID_From */
    OS_STORE_PARAM1_SCHEDTABLEID_FROM(ScheduleTableID_From);
    /* Store the parameter 2 -ScheduleTableID_To */
    OS_STORE_PARAM2_SCHEDTABLEID_TO(ScheduleTableID_To);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif

  /* Return the value */
  return (LenStatusReturn);
} /* End of NextScheduleTable(ScheduleTableType ScheduleTableID_From,
   *ScheduleTableType ScheduleTableID_To) */
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_DoNextScheduleTable                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service does the processing of schedule table  **
**                        <ScheduleTableID_To> <ScheduleTableID_From>.Final   **
**                        Delay ticks after the Final Expiry Point on         **
**                        <ScheduleTableID_From> is processed.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID_From, ScheduleTableID_To,           **
**                        LblRemoteCall                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable, Os_GaaAlarm                 **
**                        Os_GaaSchedTable                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_DoNextScheduleTable(
   ScheduleTableType ScheduleTableID_From, ScheduleTableType ScheduleTableID_To,
                                                          boolean LblRemoteCall)
{
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTableFrom;
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTableNext;
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) LpSchedTableFrom;
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) LpSchedTableNext;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarmFrom;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarmTo;
  StatusType LenStatusReturn;

  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;

  /* Check whether a related alarm is in use already */
  OS_CHECK_SCHEDTABLE_INUSE_ERROR(ScheduleTableID_From, &LenStatusReturn);

  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  /* Check whether Application is accessible */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn,
                                           ScheduleTableID_From, LblRemoteCall);
  /* Check whether Application is accessible */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn,
                                             ScheduleTableID_To, LblRemoteCall);
  #else
  OS_UNUSED(LblRemoteCall);
  #endif

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_13301 */
    /* Get the pointer to corresponding Schedule Table with
     * ScheduleTableID_From */
    LpStaticSchedTableFrom = &Os_GaaStaticSchedTable[ScheduleTableID_From];
    /* Get the pointer to the coresponding alarm */
    LpAlarmFrom = &Os_GaaAlarm[LpStaticSchedTableFrom->ddAlarmIndex];

    /* Check the current schedule table is stopped or already in the next
     * state */
    if (LpAlarmFrom->ucAlarmState > SCHEDULETABLE_NEXT)
    {
      /* @Trace : SafeOs_SUD_API_13302 */
      /* Get the pointer to corresponding Schedule Table with
       * ScheduleTableID_To */
      LpStaticSchedTableNext = &Os_GaaStaticSchedTable[ScheduleTableID_To];
      /* Get the pointer to the coresponding alarm */
      LpAlarmTo = &Os_GaaAlarm[LpStaticSchedTableNext->ddAlarmIndex];

      /* Check the state of NextScheduletAble is Stopped or not */
      if (LpAlarmTo->ucAlarmState == SCHEDULETABLE_STOPPED)
      {
        /* @Trace : SafeOs_SUD_API_13303 */
        /* Take ScheduleTable into Local variable */
        LpSchedTableFrom = &Os_GaaSchedTable[ScheduleTableID_From];
        /* Take ScheduleTable into Local variable */
        LpSchedTableNext = &Os_GaaSchedTable[ScheduleTableID_To];

        /* Check whether requested schedule table has already next schedule
         * table in place */
        if ((LpSchedTableFrom->ddNextSchedTable) != OS_INVALID_VALUE)
        {
          /* @Trace : SafeOs_SUD_API_13304 */
          /* Get the pointer to next schedule table */
          LpStaticSchedTableNext =
                  &Os_GaaStaticSchedTable[(LpSchedTableFrom->ddNextSchedTable)];
          /* If the schedule table has already set to next schedule table, set
           * next schedule table to stopped */
          Os_GaaAlarm[LpStaticSchedTableNext->ddAlarmIndex].ucAlarmState = SCHEDULETABLE_STOPPED;
        } /* End of if ((LpSchedTableFrom->ddNextSchedTable) !=
           * OS_INVALID_VALUE) */
        /* Set the state of the next schedule table with SCHEDULETABLE_NEXT */
        LpAlarmTo->ucAlarmState = SCHEDULETABLE_NEXT;
        /* Store the next schedule table */
        LpSchedTableFrom->ddNextSchedTable = ScheduleTableID_To;
        /* Update ddExpiryOffset for ScheduleTable with first expiry offset */
        LpSchedTableNext->ddExpiryOffset =
                                 LpStaticSchedTableNext->pExpiryPoint->ddOffset;
        /* Update Alarm Expiry action for the ScheduleTable with
         *   Os_ProcessSchedTable */
        /* Start scheduleTable from first Index */
        LpSchedTableNext->ulIndex = OS_ZERO;
      } /* End of if (LpAlarmTo->ucAlarmState == SCHEDULETABLE_STOPPED) */
      else
      {
        /* @Trace : SafeOs_SUD_API_13305 */
        /* If NextScheduleTable is having state other than stopped then return
         *   E_OS_STATE */
        LenStatusReturn = E_OS_STATE;
      }
    } /* End of if (LpAlarmFrom->ucAlarmState > SCHEDULETABLE_NEXT) */
    else
    {
      /* @Trace : SafeOs_SUD_API_13306 */
      /* The schedule table is already stopped or in next state, Set the value
       *   E_OS_NOFUNC in the variable LenstatusReturn */
      LenStatusReturn = E_OS_NOFUNC;
    }
  } /* End of if (LenStatusReturn == E_OK) */

  /* Return the value */
  return (LenStatusReturn);
} /* End of NextScheduleTable(ScheduleTableType ScheduleTableID_From,
   *ScheduleTableType ScheduleTableID_To) */
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernStartScheduleTableSynchron                   **
**                                                                            **
** Service ID           : OSServiceId_StartScheduleTableSynchron              **
**                                                                            **
** Description          : This service shall set the state of                 **
**                        <ScheduleTableID> to SCHEDULETABLE_WAITING and start**
**                        the processing of schedule table <ScheduleTableID>  **
**                        after the synchronization count of the schedule     **
**                        table is set via SyncScheduleTable().               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendStartScheduleTableSynchron(),                **
**                        Os_DoStartScheduleTableSynchron()                   **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11002 SRS_Os_00098 SRS_Os_00099 */
#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernStartScheduleTableSynchron(
                                              ScheduleTableType ScheduleTableID)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(STARTSCHEDULETABLESYNCHRON, LenStatusReturn);
  /* Check whether the ScheduleTableID is valid or not */
  OS_CHECK_SCHEDTABLE_ID_ERROR(ScheduleTableID, &LenStatusReturn);
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID have been checked before using" */
  /* Check whether the Schedule table is implicitly synchronized */
  OS_CHECK_IMPLICIT_SCHEDTABLE_STRATEGY_ERROR(ScheduleTableID, LenStatusReturn);
  /* polyspace +2 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
  /* Check whether Scheduletable can access the Application */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, ScheduleTableID);
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID have been checked before using" */

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_13001 */
    #if (OS_MULTICORE == STD_ON)
    /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];

    /* Check if ScheduleTable belongs to same core */
    if (LpStaticSchedTable->ddCoreID != OS_CORE_ID)
    {
      /* @Trace : SafeOs_SUD_API_13002 */
      /* Call Os_SendStartScheduleTableSynchron and get the return value */
      LenStatusReturn = Os_SendStartScheduleTableSynchron(ScheduleTableID);
    } /* End of if (LpStaticSchedTable->ddCoreID != OS_CORE_ID) */
    else
    #endif
    {
      /* @Trace : SafeOs_SUD_API_13003 */
      /* Call Os_DoStartScheduleTableSynchron and get the return value */
      LenStatusReturn = Os_DoStartScheduleTableSynchron(ScheduleTableID, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_13004 */
    /* Store the service id */
    OS_STORE_SERVICE(OSServiceId_StartScheduleTableSynchron);
    /* Store the parameter 1 - ScheduleTableID */
    OS_STORE_PARAM1_SCHEDTABLEID(ScheduleTableID);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif

  /* Return the value */
  return (LenStatusReturn);
} /* End of StartScheduleTableSynchron(ScheduleTableType ScheduleTableID) */
#endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */

/*******************************************************************************
** Function Name        : Os_DoAdjustScheduleTableRuntime                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to synchronize the processing  **
**                        of the schedule table to the synchronization        **
**                        counter Imidieatelly                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID, Value, LblRemoteCall               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable, Os_GaaAlarm                 **
**                        Os_GaaSchedTable                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_InsertAlarm(),                                   **
**                        Os_RemoveAlarm(),                                   **
**                        Os_GetMinValue()                                    **
**                        Os_UpdateHwCounter(),                               **
**                        Os_AdjustTimerInterrupt()                           **
*******************************************************************************/
#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
/* polyspace +2 CODE-METRICS:FXLN [Justified:Low] "The display of specific values of the number of Executable Lines is justified" */
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
static FUNC(StatusType, OS_CODE) Os_DoAdjustScheduleTableRuntime
                                    (ScheduleTableType ScheduleTableID, \
                                      sint64 PosOnSchedTable)
{
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) LpSchedTable;
  P2CONST(Tdd_Os_ExpiryPoint, AUTOMATIC, OS_VAR) LpExpiryPoint;
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) LpStaticCounter;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  Tdd_Os_ActivateTask actionTask;
  #if (OS_EVENT == STD_ON)
  Tdd_Os_AlarmEvent actionEvent;
  #endif
  P2CONST(Tdd_Os_Action, AUTOMATIC, OS_CONST) LpAction;

  /* Status return value */
  StatusType LenStatusReturn;

  /* Deviation updated after synchronized */
  uint32 LddDate = 0U;
  sint64 LddDateTem;

  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;

  /* Get the pointer to corresponding Schedule Table */
  LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];
  /* Get the pointer to the corresponding alarm associated with the
   *   schedule table */
  LpAlarm = &Os_GaaAlarm[LpStaticSchedTable->ddAlarmIndex];

  /* Get the time object from the queue */
  Os_RemoveAlarm(LpAlarm);

  /* Get the pointer to corresponding Schedule Table Expiry Point */
  LpExpiryPoint = LpStaticSchedTable->pExpiryPoint;

  /* Get the pointer to corresponding Schedule Table */
  LpSchedTable = &Os_GaaSchedTable[ScheduleTableID];

  /* Get the pointer to corresponding Static Schedule Table */
  LpStaticCounter = LpStaticSchedTable->pStaticCounter;

  /* The index of current EP on SchedTable */
  uint32 LulIndex;

  /* Deviation Calculating */
  sint64 LscValue;

  /* Count the next expired time for current SchedTable */
  TickType LddValue;

  /* Get the Deviation */
  LscValue = (sint64)LpSchedTable->ssDeviation;

  if (LscValue > OS_ZERO) /* Advance */
  {
    /* @Trace : SafeOs_SUD_API_14201 */
    /* Get to next Expirypoint for adjustment */
    /* polyspace +1 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
    LpExpiryPoint = &LpExpiryPoint[LpSchedTable->ulIndex];

    /* Call function to get Min value for Advance */
    LddValue = Os_GetMinValue(LpExpiryPoint->ddMaxAdvancePeriod, (TickType)LscValue);
    /* polyspace-begin RTE:OVFL [Not a defect:Low] "value abs(LscValue) is always less than or equal to Max(uint32)/2" */
    /* Update the deviation */
    LpSchedTable->ssDeviation -= (sint32)LddValue;


    /* Update Cycle for alarm */
    LddDate = LpAlarm->ddAbsCount + LddValue;
  } /* End of if (LscValue > OS_ZERO) */
  else                    /* Retard */
  {
    /* @Trace : SafeOs_SUD_API_14202 */
    /* Get index of current EP in SchedTable */
    LulIndex = (LpSchedTable->ulIndex);

    /* polyspace +1 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
    LpExpiryPoint = &LpExpiryPoint[LulIndex];

    /* Check nearest EP is expired or not */
    if (((LscValue*(OS_MINUS_ONE)) + PosOnSchedTable) \
                                             >= (sint64)LpSchedTable->ddExpiryOffset)
    {
      /* @Trace : SafeOs_SUD_API_14203 */
      /* Calculate this Expiry Point was expired or not */
      LscValue += ((sint64)LpSchedTable->ddExpiryOffset - PosOnSchedTable);

      /* Get pointer to next EP */
      LpSchedTable->ucIsExpired++;

      LpSchedTable->ssDeviation += (LscValue*OS_MINUS_ONE);
      /* polyspace-end RTE:OVFL [Not a defect:Low] "value abs(LscValue) is always less than or equal to Max(uint32)/2" */
      /* Increase Processed EP on SchedTable */
      LulIndex++;

      /* Get Next EP Information base on LulIndex */
      if (LulIndex < (LpStaticSchedTable->ucExpiryCount))
      {
        /* @Trace : SafeOs_SUD_API_14204 */
        /* Increse to next EP because current EP was checked */
        LpExpiryPoint++;

        /* Check all EPs in Current ScheduleTable to find Expired Points if any */
        do
        {
          /* Calculate this Expiry Point was expired or not */
          LscValue += (sint64)LpExpiryPoint->ddOffset;

          /* Increase Expired EP counter */
          if (LscValue <= OS_ZERO )
          {
            /* @Trace : SafeOs_SUD_API_14205 */
            LpSchedTable->ucIsExpired++;

            /* Check next EP from list*/
            LpExpiryPoint++;

            /* Update ScheduleTable current Duration */
            LpSchedTable->ddExpiryOffset += LpExpiryPoint->ddOffset;
          }
          else
          {
            /* @Trace : SafeOs_SUD_API_14206 */
            break;
          }
        }
        while(LscValue < OS_ZERO);
        /* Update ScheduleTable current Duration */
        LpSchedTable->ddExpiryOffset = LpSchedTable->ddExpiryOffset + (TickType)LscValue;
      } /* @End of if (LulIndex < (LpStaticSchedTable->ucExpiryCount)) */
      else /* Final Expiry Point */
      {
        /* @Trace : SafeOs_SUD_API_14207 */
        /* Check Dummy EP was expired or not */
        LscValue += (sint64)LpExpiryPoint->ddOffset;

        /* If Dummy EP was expired */
        if (LscValue <= OS_ZERO)
        {
          /* @Trace : SafeOs_SUD_API_14208 */
          /* Call process ScheduleTable End for starting new turn in synchronization */
          LenStatusReturn = Os_ProcessSchedTableEnd(LpSchedTable->ddSchedTableId);

          /* Update the deviation */
          LpSchedTable->ssDeviation = LscValue;
        }
      }
    } /* @End of if (((sint64)(LscValue*(OS_MINUS_ONE)) + (sint64)PosOnSchedTable) */
    /* @>= (sint64)LpSchedTable->ddExpiryOffset) */
    /* polyspace-begin RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
    /* Check if EPs that were expired, Which will be processed immediatelly */
    if (LpSchedTable->ucIsExpired > OS_ZERO)
    {
      /* @Trace : SafeOs_SUD_API_14209 */
      /* Counter variable for Action number for expired EP */
      uint32 LucActCount = OS_ZERO;
      do
      {
        /* Get index of current EP in SchedTable */
        LulIndex = (LpSchedTable->ulIndex);

        /* Get the pointer to corresponding Schedule Table */
        LpExpiryPoint = LpStaticSchedTable->pExpiryPoint;

        /* Get the pointer to current expiry point for processing */
        /* polyspace +1 MISRA-C3:18.4 [Not a defect:Low] "Increase the index ptr" */
        LpExpiryPoint += LulIndex;

        /* Get the number of actions associated with expiry counts */
        LucActCount = LpExpiryPoint->ulCount;

        /* Get the pointer to first action point */
        LpAction = LpExpiryPoint->pAction;

        /* Loop until all the actions associated with expiry counts are processed */
        while (LucActCount != OS_ZERO)
        {
          /* Invoke the corresponding action associated with the expiry point and
           * store the return value */
          /* polyspace-begin RTE:NIP [Justified:Low] "Ptr to the action which expiry alarm" */
          /* polyspace-begin RTE:COR [Justified:Low] "Ptr to the action which expiry alarm" */
          /* polyspace-begin MISRA-C3:11.3 [Not a defect:Low] "ptr to store the return value" */
          if (LpAction->enActionType == OS_ACTION_ACTIVATETASK)
          {
              actionTask.pActivateTaskFunc = &Os_AlarmActivateTask;
              actionTask.pStaticTask = LpAction->pStaticTask;

              LenStatusReturn |= Os_AlarmActivateTask(&actionTask);
          }
          #if (OS_EVENT == STD_ON)
          else if (LpAction->enActionType == OS_ACTION_SETEVENT)
          {
              actionEvent.pAlarmEventFunc = &Os_AlarmSetEvent;
              actionEvent.pStaticTask = LpAction->pStaticTask;
              actionEvent.ddEventMask = LpAction->ddEventMask;

              LenStatusReturn |= Os_AlarmSetEvent(&actionEvent);
          }
          #endif
          else
          {
              LenStatusReturn = E_NOT_OK;
          }
          /* polyspace-end MISRA-C3:11.3 [Not a defect:Low] "ptr to store the return value" */
          /* polyspace-end RTE:COR [Justified:Low] "Ptr to the action which expiry alarm" */
          /* polyspace-end RTE:NIP [Justified:Low] "Ptr to the action which expiry alarm" */
          /* Decrement the number of actions associated with the expiry count */
          LucActCount--;
          /* Increment pointer to point to next action associated with the expiry
           *   point */
          LpAction++;
        }
        /* Point to the next expiry point */
        LpSchedTable->ulIndex++;

        /* Clear Expired Point due to it is processed */
        LpSchedTable->ucIsExpired--;

      }
      while (LpSchedTable->ucIsExpired > OS_ZERO);

      /* polyspace-begin MISRA-C3:10.4 [Not a defect:Low] "Check value in range" */
      /* polyspace +2 RTE:OVFL [Not a defect:Low] "value abs(LscValue) is always less than or equal to Max(uint32)/2" */
      /* Calculate next time for next Expiry Point */
      LddDateTem = ((sint64)LpAlarm->ddAbsCount + LscValue + LpSchedTable->ssDeviation);
      if ((LddDateTem >= 0UL) && (LddDateTem < 0xFFFFFFFFUL))
      /* polyspace-end MISRA-C3:10.4 [Not a defect:Low] "Check value in range" */
      {
        LddDate = (uint32)LddDateTem;
      }

      /* Update the deviation */
      LpSchedTable->ssDeviation = OS_ZERO;
    } /* @End of if (LpSchedTable->ucIsExpired > OS_ZERO) */
      /* @No any Expiry Point were expired */
    else
    {
      /* @Trace : SafeOs_SUD_API_14210 */
      /* Take Mod value of LscValue */
      LscValue = LscValue * (OS_MINUS_ONE);

      /* Call function to get Min value for Advance */
      LddValue = Os_GetMinValue(LpExpiryPoint->ddMaxRetardPeriod, (TickType)LscValue);
      /* polyspace +2 RTE:OVFL [Not a defect:Low] "value abs(LscValue) is always less than or equal to Max(uint32)/2" */
      /* Update the deviation */
      LpSchedTable->ssDeviation += (sint32)LddValue;

      /* Update Cycle for alarm */
      LddDate = LpAlarm->ddAbsCount - LddValue;
    }
  }

  /* Check whether LddDate is greater than Maximum allwed value for
   *   Counter */
  if (LddDate > LpStaticCounter->ddMaxAllowedValue)
  {
    /* @Trace : SafeOs_SUD_API_14211 */
    /* If value exceeds then adjust the offset */
    LddDate -= LpStaticCounter->ddMaxAllowedValue + OS_ONE;
  }

  /* Change state of the ScheduleTable */
  if (LpSchedTable->ssDeviation == OS_ZERO)
  {
    /* @Trace : SafeOs_SUD_API_14212 */
    if (LpAlarm->ucAlarmState == OS_SCHEDULETABLE_EXP_REQ)
    {
      /* @Trace : SafeOs_SUD_API_14213 */
      /* Change the state of schedule table running and synchronous */
      LpAlarm->ucAlarmState = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
    }
  } /* End of if (LpSchedTable->ssDeviation == OS_ZERO) */
  else if (LpAlarm->ucAlarmState != OS_SCHEDULETABLE_EXP_PRE)
  {
    /* @Trace : SafeOs_SUD_API_14214 */
    /* Change the state of schedule table running and synchronous */
    LpAlarm->ucAlarmState = OS_SCHEDULETABLE_EXP_REQ;
  }
  else
  {
    /* @Trace : SafeOs_SUD_API_14215 */
    /* To avoid QAC warning */
  }
  
  if ((LddDate > 0UL) && (LddDate < 0xFFFFFFFFUL))
  {
    /* Update next OsCounter for next EP time */
    LpAlarm->ddAbsCount = LddDate;
  }

  /* Put back Alarm in the alarm queue of the counter it belongs to */
  Os_InsertAlarm(LpAlarm);

  #if (OS_HARDWARE_COUNTER_COUNT != OS_ZERO)
  /* Get the pointer to counter */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
  LpStaticCounter = LpAlarm->pStaticAlarm->pStaticCounter;
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
  if (LpStaticCounter->pHwCounter != NULL_PTR)
  {
    /* @Trace : SafeOs_SUD_API_14216 */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
    Os_UpdateHwCounter(LpStaticCounter->pHwCounter);

    /* Adjust timer interrupt to counter tick of first alarm */
    /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
    Os_AdjustTimerInterrupt(
                          LpStaticCounter->pCounter->pHeadAlarm->ddAbsCount,
                                               LpStaticCounter->pHwCounter);
    /* polyspace-end RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
  }
  #endif

  return LenStatusReturn;
}
#endif

/*******************************************************************************
** Function Name        : Os_DoStartScheduleTableSynchron                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service shall set the state of                 **
**                        <ScheduleTableID> to SCHEDULETABLE_WAITING and start**
**                        the processing of schedule table <ScheduleTableID>  **
**                        after the synchronization count of the schedule     **
**                        table is set via SyncScheduleTable().               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID, LblRemoteCall                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable, Os_GaaAlarm,                **
**                        Os_GaaSchedTable                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
/* polyspace-begin MISRA-C3:2.7 [Not a defect:Low] "The parameter to check wether the application is accessiable" */
/* polyspace-begin DEFECT:UNUSED_PARAMETER [Not a defect:Low] "The parameter to check wether the application is accessiable" */
FUNC(StatusType, OS_CODE) Os_DoStartScheduleTableSynchron(
                                              ScheduleTableType ScheduleTableID,
                                              boolean LblRemoteCall)
/* polyspace-end DEFECT:UNUSED_PARAMETER [Not a defect:Low] "The parameter to check wether the application is accessiable" */
/* polyspace-end MISRA-C3:2.7 [Not a defect:Low] "The parameter to check wether the application is accessiable" */
{
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) LpSchedTable;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  StatusType LenStatusReturn;
  /* @Trace : SafeOs_SUD_API_12501 */
  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;
  #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  /* Check whether Application is accessible */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn,
                                                ScheduleTableID, LblRemoteCall);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  #endif /* End of #if ((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO)) */
  {
    /* @Trace : SafeOs_SUD_API_12502 */
    /* Get the pointer to corresponding Schedule Table */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];
    /* Get the pointer to the corresponding alarm associated with the
     * schedule table */
    LpAlarm = &Os_GaaAlarm[LpStaticSchedTable->ddAlarmIndex];

    /* Check whether schedule table is already stopped or not */
    if (LpAlarm->ucAlarmState == SCHEDULETABLE_STOPPED)
    {
      /* @Trace : SafeOs_SUD_API_12503 */
      /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
      LpSchedTable = &Os_GaaSchedTable[ScheduleTableID];
      /* Update ddExpiryOffset for the ScheduleTable with First expiry offset */
      LpSchedTable->ddExpiryOffset = LpStaticSchedTable->pExpiryPoint->ddOffset;
      /* Update Alarm Expiry action for the ScheduleTable with
       * Os_ProcessSchedTable*/
      /* Start scheduleTable from 1st Index */
      LpSchedTable->ulIndex = OS_ZERO;
      /* Set the Schedule table state to waiting */
      LpAlarm->ucAlarmState = SCHEDULETABLE_WAITING;
    } /* End of if (LpAlarm->ucAlarmState == SCHEDULETABLE_STOPPED) */
    else
    {
      /* @Trace : SafeOs_SUD_API_12504 */
      /* The schedule table is not stopped, return the proper error code */
      LenStatusReturn = E_OS_STATE;
    }
  } /* End of if (LenStatusReturn == E_OK) */

  /* Return the value */
  return (LenStatusReturn);
} /* End of StartScheduleTableSynchron(ScheduleTableType ScheduleTableID) */
#endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernSyncScheduleTable                            **
**                                                                            **
** Service ID           : OSServiceId_SyncScheduleTable                       **
**                                                                            **
** Description          : This service is used to synchronize the processing  **
**                        of the schedule table to the synchronization        **
**                        counter.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID, Value                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendSyncScheduleTable(),                         **
**                        Os_DoSyncScheduleTable()                            **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11002 SRS_Os_00098 SRS_Os_00099 */
#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernSyncScheduleTable
                             (ScheduleTableType ScheduleTableID, TickType Value)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(SYNCSCHEDULETABLE, LenStatusReturn);
  /* Check whether the ScheduleTableID is valid or not */
  OS_CHECK_SCHEDTABLE_ID_ERROR(ScheduleTableID, &LenStatusReturn);
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID have been checked before using" */
  /* Check whether the Schedule table is implicitly synchronized */
  OS_CHECK_IMPLICIT_SCHEDTABLE_STRATEGY_ERROR(ScheduleTableID, LenStatusReturn);
  /* Check whether the value is greater than the OsScheduleTableDuration */
  OS_CHECK_SCHEDTABLE_VALUE_ERROR(ScheduleTableID, Value, LenStatusReturn);
  /* polyspace +2 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
  /* Check whether Scheduletable can access the Application */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, ScheduleTableID);
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID have been checked before using" */

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_13401 */
    #if (OS_MULTICORE == STD_ON)
    /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];

    /* Check if ScheduleTable belongs to same core */
    if (LpStaticSchedTable->ddCoreID != OS_CORE_ID)
    {
      /* @Trace : SafeOs_SUD_API_13402 */
      /* Call Os_SendStartScheduleTableSynchron and get the return value */
      LenStatusReturn = Os_SendSyncScheduleTable(ScheduleTableID, Value);
    } /* End of if (LpStaticSchedTable->ddCoreID != OS_CORE_ID) */
    else
    #endif
    {
      /* @Trace : SafeOs_SUD_API_13403 */
      /* Call Os_DoStartScheduleTableSynchron and get the return value */
      LenStatusReturn = Os_DoSyncScheduleTable(ScheduleTableID, Value, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_13404 */
    /* Store the service id */
    OS_STORE_SERVICE(OSServiceId_SyncScheduleTable);
    /* Store the parameter 1 - ScheduleTableID */
    OS_STORE_PARAM1_SCHEDTABLEID(ScheduleTableID);
    /* Store the parameter 2 - Value */
    OS_STORE_PARAM2_VALUE(Value);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif

  /* Return the value */
  return (LenStatusReturn);
} /* End of SyncScheduleTable(ScheduleTableType ScheduleTableID, TickType Value)
   **/
#endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */

/*******************************************************************************
** Function Name        : Os_DoSyncScheduleTable                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to synchronize the processing  **
**                        of the schedule table to the synchronization        **
**                        counter.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID, Value, LblRemoteCall               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable, Os_GaaAlarm                 **
**                        Os_GaaSchedTable                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_InsertAlarm(),                                   **
**                        Os_UpdateHwCounter(),                               **
**                        Os_AdjustTimerInterrupt()                           **
*******************************************************************************/
#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
/* polyspace-begin MISRA-C3:2.7 [Not a defect:Low] "The parameter to check wether the application is accessiable" */
/* polyspace-begin DEFECT:UNUSED_PARAMETER [Not a defect:Low] "The parameter to check wether the application is accessiable" */
FUNC(StatusType, OS_CODE) Os_DoSyncScheduleTable
      (ScheduleTableType ScheduleTableID, TickType Value, boolean LblRemoteCall)
/* polyspace-end DEFECT:UNUSED_PARAMETER [Not a defect:Low] "The parameter to check wether the application is accessiable" */
/* polyspace-end MISRA-C3:2.7 [Not a defect:Low] "The parameter to check wether the application is accessiable" */
{
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) LpSchedTable;
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) LpStaticCounter;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  StatusType LenStatusReturn;
  TickType LddDate;
  sint64 LddOffSet;
  TickType LddCurrentCount;
  TickType LddHalfofSchTbl;
  sint64 LddDelta;

  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;
  /* Check whether a related alarm is in use already */
  OS_CHECK_SCHEDTABLE_INUSE_ERROR(ScheduleTableID, &LenStatusReturn);

  /* Check whether Application is accessible */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn,
                                                ScheduleTableID, LblRemoteCall);

  /* Check whether any error(E_OS_ID) occured or not */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_14101 */
    /* Get the pointer to corresponding Schedule Table */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];
    /* Get the pointer to the corresponding alarm associated with the
     *   schedule table */
    LpAlarm = &Os_GaaAlarm[LpStaticSchedTable->ddAlarmIndex];

    /* Check the current schedule table is started */
    if (LpAlarm->ucAlarmState > SCHEDULETABLE_NEXT)
    {
      /* @Trace : SafeOs_SUD_API_14102 */
      /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
      LpSchedTable = &Os_GaaSchedTable[ScheduleTableID];
      /* Get the pointer to corresponding static counter associated with the
       * schedule table */
      LpStaticCounter = LpStaticSchedTable->pStaticCounter;
      #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
      /* If Counter is a HW Counter, update counter tick from HW timer */
      if (LpStaticCounter->pHwCounter != NULL_PTR)
      {
        /* @Trace : SafeOs_SUD_API_14103 */
        Os_UpdateHwCounter(LpStaticCounter->pHwCounter);
      }
      #endif

      /* Check whether schedule table is in waiting state */
      if (LpAlarm->ucAlarmState == SCHEDULETABLE_WAITING)
      {
        /* @Trace : SafeOs_SUD_API_14104 */
        /* @Trace : SafeOs_SUD_API_14106 */
        /* polyspace +1 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
        LddDate = Os_GetNextTick(LpStaticCounter->pCounter->ddCurrentCount,
                                (LpStaticSchedTable->ddSchedTblDuration - Value)
                                                   + LpSchedTable->ddExpiryOffset,
                                              LpStaticCounter->ddMaxAllowedValue);
        if ((LddDate > 0UL) && (LddDate < 0xFFFFFFFFUL))
        {
          /* Store the Alarm count */
          LpAlarm->ddAbsCount = LddDate;
        }

        /*Change the state of schedule table to running and synchronous */
        LpAlarm->ucAlarmState = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
        /* Insert an alarm */
        Os_InsertAlarm(LpAlarm);
        #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
        /* Adjust timer interrupt to counter tick of first alarm */
        if (LpStaticCounter->pHwCounter != NULL_PTR)
        {
          /* @Trace : SafeOs_SUD_API_14107 */
          /* polyspace +2 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
          Os_AdjustTimerInterrupt(
                              LpStaticCounter->pCounter->pHeadAlarm->ddAbsCount,
                                                   LpStaticCounter->pHwCounter);
        }
        #endif
      } /* End of if (LpAlarm->ucAlarmState == SCHEDULETABLE_WAITING) */
      else
      {
        /* @Trace : SafeOs_SUD_API_14108 */
        /* polyspace +3 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
        /* Store current count of the counter in local variable */
        LddCurrentCount =
        LpStaticSchedTable->pStaticCounter->pCounter->ddCurrentCount;
        /* Current expiry point's (to be processed) offset from the
           start of the schedule table */
        LddOffSet = (sint64)(LpSchedTable->ddExpiryOffset);
        /* Check if absolute count of alarm is greater than current count
           of counter */
        if (LpAlarm->ddAbsCount >= LddCurrentCount)
        {
          /* @Trace : SafeOs_SUD_API_14109 */
          /* Get the synchronization count */
          LddOffSet -= ((sint64) LpAlarm->ddAbsCount - (sint64) LddCurrentCount);
        }
        else
        {
          /* @Trace : SafeOs_SUD_API_14110 */
          /* Get the synchronization count */
          LddOffSet -=  (((sint64) LpStaticSchedTable->pStaticCounter->ddMaxAllowedValue
                           -  (sint64) LddCurrentCount) + ((sint64) LpAlarm->ddAbsCount + OS_ONE));
        }
        /* Check whether the absolute value of the deviation between
           schedule table value and the synchronization count is greater than
           or equal to the configured */

        /*  Delta = scheduletable.offset - globaltime.offset
            IF ABS(Delta) <=  scheduletable.duration/2
            THEN
             IF ABS(Delta) ==  scheduletable.duration/2
             THEN
              Deviation = scheduletable.duration/2
             ELSE
              Deviation = Delta
             END
            ELSE
             IF Delta < 0
              THEN
                Deviation = Delta + scheduletable.duration
              ELSE
                Deviation = Delta - scheduletable.duration
              END
            END
        */
        /* Calculate the difference between OsCounter and SynCounter */
        LddDelta = (sint64)((sint64)LddOffSet - (sint64)Value);

        /* Get a half of Schedule Table Duration */
        LddHalfofSchTbl = LpStaticSchedTable->ddSchedTblDuration/2;

        /* Check the difference value with HalfofSchTb */
        if(((LddDelta >= 0) && ((uint32)(LddDelta) <= LddHalfofSchTbl)) || \
           ((LddDelta < 0) && ((uint32)((sint64)(0-LddDelta)) <= LddHalfofSchTbl)))
        {
          /* @Trace : SafeOs_SUD_API_14111 */
          /* We need to check when the Negative Deviation equal with HalfofSchTbl */
          if(((LddDelta >= 0) && ((uint32)(LddDelta) == LddHalfofSchTbl)) || \
             ((LddDelta < 0) && ((uint32)((sint64)(0-LddDelta)) == LddHalfofSchTbl)))
          {
            /* @Trace : SafeOs_SUD_API_14112 */
            /* The deviation will be Positive Deviation */
            LpSchedTable->ssDeviation = (sint64)LddHalfofSchTbl;
          }
          else
          {
            /* @Trace : SafeOs_SUD_API_14113 */
            /* The deviation will be Negative Deviation */
            LpSchedTable->ssDeviation = LddDelta;
          }
        }
        else
        {
          /* @Trace : SafeOs_SUD_API_14114 */
          if(LddDelta < 0)
          {
            /* @Trace : SafeOs_SUD_API_14115 */
            /* The deviation will be Positive Deviation */
            LpSchedTable->ssDeviation = (sint64)LpStaticSchedTable->ddSchedTblDuration \
            - (sint64)(LddDelta * OS_MINUS_ONE);
          }
          else
          {
            /* @Trace : SafeOs_SUD_API_14116 */
            /* The deviation will be Positive Deviation */
            LpSchedTable->ssDeviation = (sint64)LddDelta \
            - (sint64)LpStaticSchedTable->ddSchedTblDuration;
          }
        }

        /* if Deviation is non-zero, the schedule table need to change state */
        if(LpSchedTable->ssDeviation != 0)
        {
          /* @Trace : SafeOs_SUD_API_14117 */
          /* If the Deviation less than Precision, ScheduleTable still in Run&Sync mode */
          if(((LpSchedTable->ssDeviation >= 0) && \
              ((uint32)(LpSchedTable->ssDeviation) < \
               (LpStaticSchedTable->ddExplictPrecision))) || \
             ((LpSchedTable->ssDeviation < 0) && \
              ((uint32)((sint64)(0-LpSchedTable->ssDeviation)) < \
               (LpStaticSchedTable->ddExplictPrecision))))
          {
            /* @Trace : SafeOs_SUD_API_14118 */
            LpAlarm->ucAlarmState = OS_SCHEDULETABLE_EXP_PRE;
            LenStatusReturn = E_OK;
          }
          else
          {
            /* @Trace : SafeOs_SUD_API_14119 */
            /* Change the state of schedule table running and synchronous */
            LpAlarm->ucAlarmState = OS_SCHEDULETABLE_EXP_REQ;

            /* FIX ME: Need to call for adjust ScheduleTable current Expiry Points */
            /* FIXME: ManJe.Woo 2013.03.18. SyncScheduleTable() Bug!
             * NOTE: Adjust the delay of next expiry point,
             *       not the delay of current expiry point!
             * Reference: [OS420], [OS421]
             */
            /* Update ssDeviation of ScheduleTable */
            //Os_DoAdjustScheduleTable(ScheduleTableID);
            LenStatusReturn = Os_DoAdjustScheduleTableRuntime(ScheduleTableID, LddOffSet);
          }
        }
        else
        {
          /* @Trace : SafeOs_SUD_API_14120 */
          LpAlarm->ucAlarmState = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
          LenStatusReturn = E_OK;
        }
      }
    } /* End of if (LpAlarm->ucAlarmState > SCHEDULETABLE_NEXT) */
    else
    {
      /* @Trace : SafeOs_SUD_API_14121 */
      /* The schedule table is already stopped/waiting, return the proper
       * error code */
      LenStatusReturn = E_OS_STATE;
    }
  } /* End of if (LenStatusReturn == E_OK) */
  /* polyspace +3 MISRA-C3:9.1 [Justified:Low] "Variable is initialized and code is verified manually" */
  /* polyspace +2 RTE:NIVL [Not a defect:Low] "Variable is initialized and code is verified manually" */
  /* Return the value */
  return (LenStatusReturn);
} /* End of SyncScheduleTable(ScheduleTableType ScheduleTableID, TickType Value)
   **/
#endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernSetScheduleTableAsync                        **
**                                                                            **
** Service ID           : OSServiceId_SetScheduleTableAsync                   **
**                                                                            **
** Description          : This service stops sychronization of                **
**                        a scheduletable                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendSetScheduleTableAsync(),                     **
**                        Os_DoSetScheduleTableAsync()                        **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11002 SRS_Os_00098 SRS_Os_00099 */
#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernSetScheduleTableAsync(
                                              ScheduleTableType ScheduleTableID)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(SETSCHEDULETABLEASYNC, LenStatusReturn);
  /* Check whether the ScheduleTableID is valid or not */
  OS_CHECK_SCHEDTABLE_ID_ERROR(ScheduleTableID, &LenStatusReturn);
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID have been checked before using" */
  /* Check whether the Schedule table is implicitly synchronised */
  OS_CHECK_IMPLICIT_SCHEDTABLE_STRATEGY_ERROR(ScheduleTableID, LenStatusReturn);
  /* polyspace +2 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
  /* Check whether Scheduletable can access the Application */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, ScheduleTableID);
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID have been checked before using" */

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_12901 */
    #if (OS_MULTICORE == STD_ON)
    /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];

    /* Check if ScheduleTable belongs to same core */
    if (LpStaticSchedTable->ddCoreID != OS_CORE_ID)
    {
      /* @Trace : SafeOs_SUD_API_12902 */
      /* Call Os_SendSetScheduleTableAsync and get the return value */
      LenStatusReturn = Os_SendSetScheduleTableAsync(ScheduleTableID);
    } /* End of if (LpStaticSchedTable->ddCoreID != OS_CORE_ID) */
    else
    #endif
    {
      /* @Trace : SafeOs_SUD_API_12903 */
      /* Call Os_DoSetScheduleTableAsync and get the return value */
      LenStatusReturn = Os_DoSetScheduleTableAsync(ScheduleTableID, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_12904 */
    /* Store the service id */
    OS_STORE_SERVICE(OSServiceId_SetScheduleTableAsync);
    /* Store the parameter 1 - ScheduleTableID */
    OS_STORE_PARAM1_SCHEDTABLEID(ScheduleTableID);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif

  /* Return the value */
  return (LenStatusReturn);
} /* End of SetScheduleTableAsync(ScheduleTableType ScheduleTableID) */
#endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */

/*******************************************************************************
** Function Name        : Os_DoSetScheduleTableAsync                          **
**                                                                            **
** Service ID           : OSServiceId_SetScheduleTableAsync                   **
**                                                                            **
** Description          : This service stops sychronization of                **
**                        a scheduletable                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID, LblRemoteCall                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaAlarm, Os_GaaStaticSchedTable,                **
**                        Os_GaaSchedTable                                    **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00098 SRS_Os_00099 SRS_Os_11002 */
#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
/* polyspace-begin MISRA-C3:2.7 [Not a defect:Low] "The parameter to check wether the application is accessiable" */
/* polyspace-begin DEFECT:UNUSED_PARAMETER [Not a defect:Low] "The parameter to check wether the application is accessiable" */
FUNC(StatusType, OS_CODE) Os_DoSetScheduleTableAsync(
                                              ScheduleTableType ScheduleTableID,
                                              boolean LblRemoteCall)
/* polyspace-end DEFECT:UNUSED_PARAMETER [Not a defect:Low] "The parameter to check wether the application is accessiable" */
/* polyspace-end MISRA-C3:2.7 [Not a defect:Low] "The parameter to check wether the application is accessiable" */
{
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) LpSchedTable;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  StatusType LenStatusReturn;
  /* @Trace : SafeOs_SUD_API_12401 */
  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;
  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  /* Check whether Application is accessible */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn,
                                                ScheduleTableID, LblRemoteCall);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  #endif /* End of if ((OS_SCALABILITY_CLASS == SC3)||
                                            (OS_SCALABILITY_CLASS == SC4)) */
  {
    /* @Trace : SafeOs_SUD_API_12402 */
    /* Get the pointer to corresponding Schedule Table */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];
    /* Get the pointer to the corresponding alarm associated with the
     * schedule table */
    LpAlarm = &Os_GaaAlarm[LpStaticSchedTable->ddAlarmIndex];

    /* Check if state of ScheduleTable is not Running */
    if ((LpAlarm->ucAlarmState == SCHEDULETABLE_RUNNING) ||
        (LpAlarm->ucAlarmState > SCHEDULETABLE_WAITING))
    {
      /* @Trace : SafeOs_SUD_API_12403 */
      /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
      LpSchedTable = &Os_GaaSchedTable[ScheduleTableID];
      /* Make the deviation to Zero to stop further Synchronisation */
      LpSchedTable->ssDeviation = OS_ZERO;
      /* Change the state of schedule table to running */
      LpAlarm->ucAlarmState = SCHEDULETABLE_RUNNING;
    } /* End of if ((LpAlarm->ucAlarmState == SCHEDULETABLE_RUNNING) || */
    else
    {
      /* @Trace : SafeOs_SUD_API_12404 */
      /* The schedule table is already stopped/waiting, return the proper
       * error code */
      LenStatusReturn = E_OS_STATE;
    }
  } /* End of if (LenStatusReturn == E_OK) */

  /* Return the value */
  return (LenStatusReturn);
} /* End of SetScheduleTableAsync(ScheduleTableType ScheduleTableID) */
#endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernGetScheduleTableStatus                       **
**                                                                            **
** Service ID           : OSServiceId_GetScheduleTableStatus                  **
**                                                                            **
** Description          : This service is used to return the status of the    **
**                        schedule table requested.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID, ScheduleStatus                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ScheduleStatus                                      **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendGetScheduleTableStatus(),                    **
**                        Os_DoGetScheduleTableStatus()                       **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11002 SRS_Os_80013 SRS_Os_00098 SRS_Os_00099 */
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernGetScheduleTableStatus(
   ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus)
{
  StatusType LenStatusReturn;

  #if (OS_MULTICORE == STD_ON)
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The core ID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the status return value to no error i.e E_OK */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(GETSCHEDULETABLESTATUS, LenStatusReturn);
  /* Check whether the ScheduleTableID is valid or not */
  OS_CHECK_SCHEDTABLE_ID_ERROR(ScheduleTableID, &LenStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(ScheduleStatus, LenStatusReturn);
  /* Check whether Scheduletable can access the Application */
  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "ScheduleTableID have been checked before using" */
  /* polyspace +1 RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, ScheduleTableID);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_12801 */
    #if (OS_MULTICORE == STD_ON)
    /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];

    /* Check if ScheduleTable belongs to same core */
    if (LpStaticSchedTable->ddCoreID != OS_CORE_ID)
    {
      /* @Trace : SafeOs_SUD_API_12802 */
      /* Call Os_SendGetScheduleTableStatus and get the return value */
      LenStatusReturn = Os_SendGetScheduleTableStatus(ScheduleTableID, ScheduleStatus);
    } /* End of if (LpStaticSchedTable->ddCoreID != OS_CORE_ID) */
    else
    #endif
    {
      /* @Trace : SafeOs_SUD_API_12803 */
      /* Call Os_DoGetScheduleTableStatus and get the return value */
      LenStatusReturn = Os_DoGetScheduleTableStatus(ScheduleTableID, ScheduleStatus, OS_FALSE);
    }
  } /* End of if (LenStatusReturn == E_OK) */

  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_12804 */
    /* Store the service id */
    OS_STORE_SERVICE(OSServiceId_GetScheduleTableStatus);
    /* Store the parameter 1 - ScheduleTableID */
    OS_STORE_PARAM1_SCHEDTABLEID(ScheduleTableID);
    /* Store the parameter 2 - ScheduleStatus */
    OS_STORE_PARAM2_SCHEDULESTATUS(ScheduleStatus);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif

  /* Return the value */
  return (LenStatusReturn);
} /* End of GetScheduleTableStatus(ScheduleTableType ScheduleTableID,
   *ScheduleTableStatusRefType ScheduleStatus) */
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_DoGetScheduleTableStatus                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to return the status of the    **
**                        schedule table requested.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ScheduleTableID, ScheduleStatus,                    **
**                        LblRemoteCall                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ScheduleStatus                                      **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable, Os_GaaAlarm                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_DoGetScheduleTableStatus(
   ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus,
   boolean LblRemoteCall)
{
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  StatusType LenStatusReturn;
  uint8 LucAlarmState;
  /* @Trace : SafeOs_SUD_API_12301 */
  /* Set the status return value to E_OK */
  LenStatusReturn = E_OK;

  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  /* Check whether Application is accessible */
  OS_CHECK_SCHEDTABLE_APPLICATION_ACCESS_CROSS_CORE(&LenStatusReturn,
                                                ScheduleTableID, LblRemoteCall);

  /* Check whether any error(E_OS_ID) occured or not */
  if (LenStatusReturn == E_OK)
  #else
  OS_UNUSED(LblRemoteCall);
  #endif /* End of if ((OS_SCALABILITY_CLASS == SC3)||
                                              (OS_SCALABILITY_CLASS == SC4)) */
  {
    /* @Trace : SafeOs_SUD_API_12302 */
    /* Get the pointer to corresponding Schedule table table */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];
    /* Store the Schedule table state */
    LucAlarmState = Os_GaaAlarm[LpStaticSchedTable->ddAlarmIndex].ucAlarmState;
    #if (OS_SCHED_EXPLICIT_SYNC == STD_ON)

    /* If SchedTable state is OS_SCHEDULETABLE_EXP_PRE return as Synchronous */
    if (LucAlarmState == OS_SCHEDULETABLE_EXP_PRE)
    {
      /* @Trace : SafeOs_SUD_API_12303 */
      LucAlarmState = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
    }

    /* Else update it as Running */
    if ((LucAlarmState == OS_SCHEDULETABLE_EXP_DEV) ||
        (LucAlarmState == OS_SCHEDULETABLE_EXP_REQ))
    {
      /* @Trace : SafeOs_SUD_API_12304 */
      LucAlarmState = SCHEDULETABLE_RUNNING;
    }
    #endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "ScheduleStatus have been checked by macro OS_CHECK_NULL_PTR before using" */
    /* Update the Alarm State*/
    *ScheduleStatus = LucAlarmState;

  } /* End of if (LenStatusReturn == E_OK) */

  /* Return the value */
  return (LenStatusReturn);
} /* End of GetScheduleTableStatus(ScheduleTableType ScheduleTableID,
   *ScheduleTableStatusRefType ScheduleStatus) */
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_GetMinValue                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns minimum value between 2 values**
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : LddMaxPeriod,  LddDeviation                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : TickType                                            **
**                                                                            **
** Preconditions        : The Os must be initialized                          **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
static FUNC(TickType, OS_CODE) Os_GetMinValue(TickType LddMaxPeriod,
                                                          TickType LddDeviation)
{
  TickType LddValue;

  /* Check if Deviation is less than LddMaxPeriod */
  if (LddDeviation < LddMaxPeriod)
  {
    /* @Trace : SafeOs_SUD_API_12101 */
    /* Update LddValue with deviation */
    LddValue = LddDeviation;
  }
  else
  {
    /* @Trace : SafeOs_SUD_API_12102 */
    /* Update LddValue with LddMaxPeriod */
    LddValue = LddMaxPeriod;
  }
  /* Return the Minimum value */
  return (LddValue);
} /* End of Os_GetMinValue(TickType LddMaxPeriod, TickType LddDeviation) */
#endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */

/*******************************************************************************
** Function Name        : Os_ProcessSchedTableEnd                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used for Processing of last expiry  **
**                        last expiry point.                                  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : ScheduleTableID                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable, Os_GaaSchedTable            **
**                        Os_GaaAlarm                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_InsertAlarm(), Os_GetMinValue(), Os_MemCopy(),   **
**                        Os_AlarmActivateTask(), Os_AlarmSetEvent(),         **
*******************************************************************************/
#if (OS_SCHEDTABLE == STD_ON)
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
static FUNC(StatusType, OS_CODE) Os_ProcessSchedTableEnd
                                             (ScheduleTableType ScheduleTableID)
{
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  P2CONST(Tdd_Os_ExpiryPoint, AUTOMATIC, OS_VAR) LpExpiryPoint;
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) LpSchedTable;
  P2CONST(Tdd_Os_Action, AUTOMATIC, OS_CONST) LpAction;
  Tdd_Os_ActivateTask actionTask;
  #if (OS_EVENT == STD_ON)
  Tdd_Os_AlarmEvent actionEvent;
  #endif
  TickType LddValue;
  #if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
  sint64 LscValue;
  #endif
  StatusType LenStatusReturn;
  uint32 LulCount;

  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Get the static ScheduleTable */
  LpStaticSchedTable = &Os_GaaStaticSchedTable[ScheduleTableID];
  /* Get the pointer to corresponding Schedule Table with ScheduleTableID */
  LpSchedTable = &Os_GaaSchedTable[ScheduleTableID];

  /* Get the pointer to corresponding alarm of the schedule table */
  LpAlarm = &Os_GaaAlarm[LpStaticSchedTable->ddAlarmIndex];
  /* Set the alarm cycle to zero */
  (LpAlarm->ddCycle) = OS_ZERO;

  /* Check if ScheduleTable is Periodic */
  if ((LpStaticSchedTable->blPeriodic) == OS_FALSE)
  {
    /* @Trace : SafeOs_SUD_API_14001 */
    /* Reset the state of the current schedule table to stopped */
    LpAlarm->ucAlarmState = SCHEDULETABLE_STOPPED;
  }
  else
  {
    /* @Trace : SafeOs_SUD_API_14002 */
    /* Points to first expiry point */
    LpExpiryPoint = LpStaticSchedTable->pExpiryPoint;
    #if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
    /* Check whether Schedule Table Syncronization Strategy is Explicit */
    if (LpAlarm->ucAlarmState > SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS)
    {
      /* @Trace : SafeOs_SUD_API_14003 */
      /* Get the Deviation */
      LscValue = (sint64)LpSchedTable->ssDeviation;
      /* Check if LscValue is ZERO */
      if (LscValue != OS_ZERO)
      {
        /* @Trace : SafeOs_SUD_API_14004 */
        if (LscValue > OS_ZERO) /* Advance */
        {
          /* @Trace : SafeOs_SUD_API_14005 */
          /* Call function to get Min value for Advance */
          LddValue = Os_GetMinValue( LpExpiryPoint->ddMaxAdvancePeriod, (TickType)LscValue);
          /* polyspace-begin RTE:OVFL [Not a defect:Low] "value abs(LscValue) is always less than or equal to Max(uint32)/2" */
          /* Update the deviation */
          LpSchedTable->ssDeviation -= (sint32)LddValue;
          /* Update Cycle for alarm */
          LpAlarm->ddCycle += LddValue;
        } /* End of if (LscValue > OS_ZERO) */
        else                    /* Retard */
        {
          /* @Trace : SafeOs_SUD_API_14006 */
          /* Take Mod value of LscValue */
          LscValue = LscValue * (OS_MINUS_ONE);
          /* Call function to get Min value for Advance */
          LddValue = Os_GetMinValue(LpExpiryPoint->ddMaxRetardPeriod, (TickType)LscValue);
          /* Update the deviation */
          LpSchedTable->ssDeviation += (sint32)LddValue;
          /* polyspace-end RTE:OVFL [Not a defect:Low] "value abs(LscValue) is always less than or equal to Max(uint32)/2"*/
          /* Update Cycle for alarm */
          LpAlarm->ddCycle -= LddValue;
        } /* End of else */
      } /* End of if (LscValue != OS_ZERO) */
      /* Check if LscValue is less than Precision */
      if ((TickType)LscValue < LpStaticSchedTable->ddExplictPrecision)
      {
        /* @Trace : SafeOs_SUD_API_14007 */
        /* Change the state of schedule table running and synchronous */
        LpAlarm->ucAlarmState = OS_SCHEDULETABLE_EXP_PRE;
      }
    } /* End of if (LpAlarm->ucAlarmState >
         *SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS) */
    #endif /* #if(OS_SCHED_EXPLICIT_SYNC == STD_ON) */

    /* Check if any Expiry point is configured at the start */
    if (LpExpiryPoint->ddOffset != OS_ZERO)
    {
      /* @Trace : SafeOs_SUD_API_14008 */
      /* Update Cycle with Expiry point offset */
      LpAlarm->ddCycle += LpExpiryPoint->ddOffset;
      /* Save the next expiry point index */
      LpSchedTable->ulIndex = OS_ZERO;
      /* Update the Offset of next expiry point to be processed from start */
      LpSchedTable->ddExpiryOffset = LpAlarm->ddCycle;
    } /* End of if (LpExpiryPoint->ddOffset != OS_ZERO) */
    else
    {
      /* @Trace : SafeOs_SUD_API_14009 */
      /* Point to the first expiry point*/
      LpSchedTable->ulIndex = OS_ZERO;
      /* Get the number of actions associated with expiry counts */
      LulCount = LpExpiryPoint->ulCount;
      /* Get the pointer to first action point */
      LpAction = LpExpiryPoint->pAction;

      /* Loop until all the actions associated with expiry counts are
       * processed */
      while (LulCount != OS_ZERO)
      {
        /* Invoke the corresponding action associated with the expiry point
         * and store the return value */
        /* polyspace-begin RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */ 
        /* polyspace +2 RTE:COR [Not a defect:Low] "function ptr points to a valid function and code is manually checked" */
        /* polyspace +2 MISRA-C3:11.4 [Justified:Medium] "Conversion is needed for implementation" */
        if (LpAction->enActionType == OS_ACTION_ACTIVATETASK)
        {
          actionTask.pActivateTaskFunc = &Os_AlarmActivateTask;
          actionTask.pStaticTask = LpAction->pStaticTask;
          LenStatusReturn |= Os_AlarmActivateTask(&actionTask);
        }
        #if (OS_EVENT == STD_ON)
        else if (LpAction->enActionType == OS_ACTION_SETEVENT)
        {
          actionEvent.pAlarmEventFunc = &Os_AlarmSetEvent;
          actionEvent.pStaticTask = LpAction->pStaticTask;
          actionEvent.ddEventMask = LpAction->ddEventMask;
          LenStatusReturn |= Os_AlarmSetEvent(&actionEvent);
        }
        #endif
        else
        {
          LenStatusReturn = E_NOT_OK;
        }
        /* polyspace-end RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */		
        /* Decrement the number of actions associated with the expiry count */
        LulCount--;
        /* Increment the pointer to point to next action associated with the
         *   expiry point */
        LpAction++;
      }

      /* Get the pointer to next expiry point */
      LpExpiryPoint++;
      /* polyspace-begin RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
      /* Update cycle with next expiry point */
      LpAlarm->ddCycle += LpExpiryPoint->ddOffset;
      /* Update the Offset of next expiry point to be processed from start */
      LpSchedTable->ddExpiryOffset = LpAlarm->ddCycle;
      /* Point to the next expiry point */
      LpSchedTable->ulIndex++;
    } /* End of else */
  } /* End of else */

  /* Check whether next schedule table exists or not */
  if ((LpSchedTable->ddNextSchedTable) != OS_INVALID_VALUE)
  {
    /* @Trace : SafeOs_SUD_API_14010 */
    LpStaticSchedTable = &Os_GaaStaticSchedTable[(LpSchedTable->ddNextSchedTable)];
    /* Get the pointer to Alarm object */
    LpAlarm = &Os_GaaAlarm[LpStaticSchedTable->ddAlarmIndex];
    #if (OS_SCHED_IMPLICIT_SYNC == STD_ON)

    /* Check weather ScheduleTable is implicitly syncronised */
    if (LpStaticSchedTable->ucSynchStrategy == OS_SCHEDTABLE_IMPLICIT_SYNC)
    {
      /* @Trace : SafeOs_SUD_API_14011 */
      /* Set the Schedule table state to running & Synchronous */
      LpAlarm->ucAlarmState = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
    }
    else
    #endif /* End of if (OS_SCHED_IMPLICIT_SYNC == STD_ON) */
    {
      /* @Trace : SafeOs_SUD_API_14012 */
      /* Set the Schedule table state to running */
      LpAlarm->ucAlarmState = SCHEDULETABLE_RUNNING;
    }
    /* Pointer to the NextScheduleTable is removed */
    (LpSchedTable->ddNextSchedTable) = OS_INVALID_VALUE;
    /* Get the pointer to first expiry point */
    LpExpiryPoint = LpStaticSchedTable->pExpiryPoint;
    /* XXX: ManJe.Woo 2013.03.18. Counter offset Bug!
     * NOTE: Count 1(MaxAllowedValue to 0) is not calculated.
     */
    LddValue = LpStaticSchedTable->pStaticCounter->pCounter->ddCurrentCount
                                                  + (LpExpiryPoint->ddOffset);
    /* polyspace-end RTE:NIV [Not a defect:Unset] "variable is initialized and code is verified manually" */
    /* Check whether the offset is greater than the maximum allowed value
     *   of the underlying counter */
    if (LddValue > LpStaticSchedTable->pStaticCounter->ddMaxAllowedValue)
    {
      /* @Trace : SafeOs_SUD_API_14013 */
      /* If value exceeds then adjust the offset */
      LddValue -= (LpStaticSchedTable->pStaticCounter->ddMaxAllowedValue + OS_ONE);
    }
    
    if ((LddValue > 0UL) && (LddValue < 0xFFFFFFFFUL))
    {
      LpAlarm->ddAbsCount = LddValue;
    }
    /* Insert an alarm */
    Os_InsertAlarm(LpAlarm);
  } /* End of if ((LpSchedTable->ddNextSchedTable) != OS_INVALID_VALUE) */
  return(LenStatusReturn);
}
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_ProcessSchedTable                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to processs the necessary      **
**                        actions associated with an expiry point of the      **
**                        schedule and reload the alarm delay with the offset **
**                        of the next expiry point.                           **
**                        Alarm cycle time is updated as per next expiry      **
**                        point of the scheduletable                          **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : pAction                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticSchedTable, Os_GaaAlarm                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_GetMinValue(),                                   **
**                        Os_ProcessSchedTableEnd(),                          **
**                        Os_MemCopy()                                        **
*******************************************************************************/
/* @Trace: SRS_Os_11002 SRS_Os_80013 */
#if (OS_SCHEDTABLE == STD_ON)
FUNC(StatusType, OS_CODE) Os_ProcessSchedTable
                   (P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) pAction)
{
  P2CONST(Tdd_Os_StaticSchedTable, AUTOMATIC, OS_CONST) LpStaticSchedTable;
  P2CONST(Tdd_Os_Action, AUTOMATIC, OS_CONST) LpAction;
  P2CONST(Tdd_Os_ExpiryPoint, AUTOMATIC, OS_VAR) LpExpiryPoint;
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) LpSchedTable;
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpAlarm;
  Tdd_Os_ActivateTask actionTask;
  #if (OS_EVENT == STD_ON)
  Tdd_Os_AlarmEvent actionEvent;
  #endif
  #if (OS_SCHED_EXPLICIT_SYNC == STD_ON)
  TickType LddValue;
  sint64 LscValue;
  #endif
  StatusType LenStatusReturn;
  uint32 LulIndex;
  uint32 LulCount;
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* polyspace-begin RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
  /* Get the pointer to corresponding schedule table */
  /* polyspace +2 MISRA-C3:11.8 [Justified:Low] "To get pointer to corresponding schedule table, typecast to different point type is needed." */
  /* polyspace +1 MISRA-C3:11.4 [Justified:Medium] "Conversion is needed for implementation" */
  LpSchedTable = pAction;

  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "ptr points to a valid value and code is verified manually" */
  /* Check whether the ScheduleTableID is valid or not */
  OS_CHECK_SCHEDTABLE_ID_ERROR((LpSchedTable->ddSchedTableId), &LenStatusReturn);
  /* Get the static ScheduleTable */
  LpStaticSchedTable = &Os_GaaStaticSchedTable[LpSchedTable->ddSchedTableId];
  /* Get the pointer to corresponding alarm of the schedule table */
  LpAlarm = &Os_GaaAlarm[LpStaticSchedTable->ddAlarmIndex];
  /* Get the Expiry point  index value */
  LulIndex = (LpSchedTable->ulIndex);

  if (LulIndex < (LpStaticSchedTable->ucExpiryCount))
  {
    /* @Trace : SafeOs_SUD_API_13801 */
    /* Get the pointer to corresponding expiry point */
    LpExpiryPoint = LpStaticSchedTable->pExpiryPoint;
    /* polyspace +1 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
    LpExpiryPoint = &LpExpiryPoint[LulIndex];
    /* Get the number of actions associated with expiry counts */
    LulCount = LpExpiryPoint->ulCount;
    /* Get the pointer to first action point */
    LpAction = LpExpiryPoint->pAction;

    /* Loop until all the actions associated with expiry counts are processed */
    while (LulCount != OS_ZERO)
    {
      /* Invoke the corresponding action associated with the expiry point and
       *   store the return value */
      /* polyspace-begin RTE:NIVL [Not a defect:Low] "Variable is initialized and code is verified manually" */
      /* polyspace-begin MISRA-C3:9.1 [Justified:Low] "Variable is initialized and code is verified manually" */
      /* polyspace +2 RTE:COR [Not a defect:Low] "function ptr points to a valid function and code is manually checked" */
      /* polyspace +2 MISRA-C3:11.4 [Justified:Medium] "Conversion is needed for implementation" */
      if (LpAction->enActionType == OS_ACTION_ACTIVATETASK)
      {
        actionTask.pActivateTaskFunc = &Os_AlarmActivateTask;
        actionTask.pStaticTask = LpAction->pStaticTask;

        LenStatusReturn |= Os_AlarmActivateTask(&actionTask);
      }
      #if (OS_EVENT == STD_ON)
      else if (LpAction->enActionType == OS_ACTION_SETEVENT)
      {
        actionEvent.pAlarmEventFunc = &Os_AlarmSetEvent;
        actionEvent.pStaticTask = LpAction->pStaticTask;
        actionEvent.ddEventMask = LpAction->ddEventMask;

        LenStatusReturn |= Os_AlarmSetEvent(&actionEvent);
      }
      #endif
      else
      {
        LenStatusReturn = E_NOT_OK;
      }
      /* polyspace-end MISRA-C3:9.1 [Justified:Low] "Variable is initialized and code is verified manually" */
      /* polyspace-end RTE:NIVL [Not a defect:Low] "Variable is initialized and code is verified manually" */
      /* polyspace-end MISRA-C3:11.3 [Not a defect:Low] "the corresponding action associated with the expiry point, typecast to different point type is needed." */
      /* Decrement the number of actions associated with the expiry count */
      LulCount--;
      /* Increment pointer to point to next action associated with the expiry
       *   point */
      LpAction++;
    }

    /* Get the pointer to next expiry point */
    LpExpiryPoint++;
    /* Initialize value of alarm */
    LpAlarm->ddCycle = OS_ZERO;

    #if (OS_SCHED_EXPLICIT_SYNC == STD_ON)

    /* Check whether Schedule Table needs to be synchronised */
    if (LpAlarm->ucAlarmState > SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS)
    {
      /* @Trace : SafeOs_SUD_API_13802 */
      /* Check if deviation is ZERO */
      if (LpSchedTable->ssDeviation == OS_ZERO)
      {
        /* @Trace : SafeOs_SUD_API_13803 */
        /* Change the state of schedule table running and synchronous */
        LpAlarm->ucAlarmState = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
      }
      else
      {
        /* @Trace : SafeOs_SUD_API_13804 */
        /* Get the Deviation */
        LscValue = (sint64)LpSchedTable->ssDeviation;

        if (LscValue > OS_ZERO) /* Advance */
        {
          /* @Trace : SafeOs_SUD_API_13805 */
          /* Call function to get Min value for Advance */
          LddValue = Os_GetMinValue(LpExpiryPoint->ddMaxAdvancePeriod, (TickType)LscValue);
          /* polyspace-begin RTE:OVFL [Not a defect:Low] "value abs(LscValue) is always less than or equal to Max(uint32)/2" */
          /* Update the deviation */
          LpSchedTable->ssDeviation -= (sint32)LddValue;
          /* Update Cycle for alarm */
          LpAlarm->ddCycle = LddValue;
        } /* End of if (LscValue > OS_ZERO) */
        else                    /* Retard */
        {
          /* @Trace : SafeOs_SUD_API_13806 */
          /* Take Mod value of LscValue */
          LscValue = LscValue * (OS_MINUS_ONE);
          /* Call function to get Min value for Advance */
          LddValue = Os_GetMinValue(LpExpiryPoint->ddMaxRetardPeriod, (TickType)LscValue);
          /* Update the deviation */
          LpSchedTable->ssDeviation += (sint32)LddValue;
          /* polyspace-end RTE:OVFL [Not a defect:Low] "value abs(LscValue) is always less than or equal to Max(uint32)/2" */
          /* Update Cycle for alarm */
          LpAlarm->ddCycle -= LddValue;
        } /* End of else */

        if ((TickType)LscValue < LpStaticSchedTable->ddExplictPrecision)
        {
          /* @Trace : SafeOs_SUD_API_13807 */
          /* Change the state of schedule table running and synchronous */
          LpAlarm->ucAlarmState = OS_SCHEDULETABLE_EXP_PRE;
        }
      } /* End of else */
    } /* End of if (LpAlarm->ucAlarmState >
     *SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS) */
    #endif /* End of if (OS_SCHED_EXPLICIT_SYNC == STD_ON) */
    LpAlarm->ddCycle += LpExpiryPoint->ddOffset;
    /* Update the Offset of next expiry point to be processed from start */
    /* polyspace-begin DEFECT:CONSTANT_OBJECT_WRITE [Not a defect:Low] "LpSchedTable has been casted from pAction and allows to modify its member" */
    LpSchedTable->ddExpiryOffset += LpAlarm->ddCycle;
    /* Point to the next expiry point */
    LpSchedTable->ulIndex++;
    /* polyspace-end DEFECT:CONSTANT_OBJECT_WRITE [Not a defect:Low] "LpSchedTable has been casted from pAction and allows to modify its member" */
    /* polyspace-end RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
  } /* End of if (LulIndex < (LpStaticSchedTable->ucExpiryCount)) */
  else
  {
    /* @Trace : SafeOs_SUD_API_13808 */
    /* Call Os_ProcessSchedTableEnd for the last expiry point */
    LenStatusReturn = Os_ProcessSchedTableEnd(LpSchedTable->ddSchedTableId);
  } /* End of else */
                                  /* Return the value */
  return (LenStatusReturn);
} /* End of Os_ProcessSchedTable(P2CONST(Tdd_Os_AlarmExpAction,
   * AUTOMATIC, */
#endif /* End of if (OS_SCHEDTABLE == STD_ON) */

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace-end RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
