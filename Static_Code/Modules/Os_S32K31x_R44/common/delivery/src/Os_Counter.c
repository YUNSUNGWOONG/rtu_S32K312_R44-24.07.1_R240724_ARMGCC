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
**  SRC-MODULE: Os_Counter.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Counter functionality.                           **
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
** 1.5.0.1   26-Apr-2023   JHLim            Jira CP44-2916                    **
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.3     13-Oct-2020   DanhDC1          R44-Redmine #16287 Don't allow    **
**                                          Counter in case of cross core     **
** 1.0.2     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually." */
/* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os Ram header file */
#include "Os_Kernel.h"            /* Os Kernel header file */
#include "Os_Alarm.h"             /* Os Alarm header file */
#include "Os_Counter.h"           /* Os Counter header file */
#include "Os_Error.h"             /* Os Error header file */
/* @Trace: SRS_BSW_00410 */
#if (OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Application.h"       /* Os Application header file */
#endif
#if (OS_MULTICORE == STD_ON)
#include "Os_MulticoreMessage.h"
#endif
#include "Os_SystemCallTable.h"

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

/*******************************************************************************
** Function Name        : Os_CounterTick                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function increments counter value and          **
**                        checks if any alarm expires.                        **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpStaticCounter                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_ProcessAlarm()                                   **
*******************************************************************************/
/* @Trace: SRS_Os_11020 SRS_Os_11021 */
#if (OS_COUNTER == STD_ON)
FUNC(StatusType, OS_CODE) Os_CounterTick(P2CONST(Tdd_Os_StaticCounter,
                                           AUTOMATIC, OS_CONST) LpStaticCounter)
{
  TickType LddCurrentCount;
  P2VAR(Tdd_Os_Counter, AUTOMATIC, OS_VAR) LpCounter;
  StatusType LddStatusReturn = E_OK;

  /* Get the pointer to counter */
  LpCounter = LpStaticCounter->pCounter;
  LddCurrentCount = LpCounter->ddCurrentCount;

  /* Check whether counter has reached to maximum allowed value */
  if (LddCurrentCount == LpStaticCounter->ddMaxAllowedValue)
  {
    /* @Trace : SafeOs_SUD_API_10601 */
    /* Reset the counter */
    LddCurrentCount = OS_ZERO;
  }
  else
  {
    /* @Trace : SafeOs_SUD_API_10602 */
    /* Increment counter */
    LddCurrentCount++;
  }
  /* Copy the local counter value to RAM */
  LpCounter->ddCurrentCount = LddCurrentCount;

  #if (OS_ALARM == STD_ON) || (OS_SCHEDTABLE == STD_ON)
  LddStatusReturn = Os_ProcessAlarm(LpStaticCounter);
  #endif

  /* Return the value */
  return LddStatusReturn;
} /* End of Os_CounterTick(P2CONST(Tdd_Os_StaticCounter, AUTOMATIC,
   * OS_CONST) LpStaticCounter) */
#endif /* End of if (OS_COUNTER == STD_ON) */

/*******************************************************************************
** Function Name        : Os_DoGetCounterValue                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to get the current value       **
**                        of a counter.CounterId is the input parameter.      **
**                        value, is a reference (pointer) to the variable     **
**                        where the value of the counter is stored.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : CounterID                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : value                                               **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticCounter                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_UpdateHwCounter()                                **
*******************************************************************************/
#if (OS_COUNTER == STD_ON)
FUNC(StatusType, OS_CODE) Os_DoGetCounterValue(CounterType CounterID,
                                                          TickRefType Value)
{
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) LpStaticCounter;
  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  #endif

  StatusType LenStatusReturn = E_OK;
  /* Check whether Counter is in use already */
  OS_CHECK_COUNTER_INUSE_ERROR(CounterID, &LenStatusReturn);

  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "CounterID have been checked before using" */
  OS_CHECK_COUNTER_APPLICATION_ACCESS_CROSS_CORE(LenStatusReturn, CounterID);

  #endif
  #if (OS_STATUS == EXTENDED)
  /* polyspace<RTE: UNR : Not a defect : No Action Planned > If multicore is not defined, this violation occurs. but this code has already been verified and no impact of this rule violation */
  /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Boolean result is variant according to counter usage or multicore operation" */
  if (LenStatusReturn == (StatusType)E_OK)
  #endif
  {
    /* @Trace : SafeOs_SUD_API_10701 */
    /* Pointer to static counter */
    LpStaticCounter = &Os_GaaStaticCounter[CounterID];
    #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
    /* If Counter is a HW Counter, update counter tick from HW timer */
    if (LpStaticCounter->pHwCounter != NULL_PTR)
    {
      /* @Trace : SafeOs_SUD_API_10702 */
      Os_UpdateHwCounter(LpStaticCounter->pHwCounter);
    }
    #endif
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "Value have been checked before using" */
    /* Copy the counter value */
    *Value = (LpStaticCounter->pCounter->ddCurrentCount);
  }
  /* @Trace : SafeOs_SUD_API_10703 */
  /* polyspace-end MISRA-C3:14.3 [Justified:Low] "Boolean result is variant according to counter usage or multicore operation" */
  return LenStatusReturn;
}
#endif

/*******************************************************************************
** Function Name        : Os_DoGetElapsedCounterValue                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to get the elapsed value       **
**                        of a counter                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : CounterType CounterID, TickRefType Value,           **
**                        TickRefType ElapsedValue                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ElapsedValue                                        **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticCounter                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_UpdateHwCounter()                                **
*******************************************************************************/
#if (OS_COUNTER == STD_ON)
FUNC(StatusType, OS_CODE) Os_DoGetElapsedCounterValue(CounterType CounterID,
                                  TickRefType Value, TickRefType ElapsedValue)
{
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) LpStaticCounter;
  TickType LddCurrentVal;
  TickType LddPreviousVal;
  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  #endif
  StatusType LenStatusReturn = E_OK;

  /* Check whether Counter is in use already */
  OS_CHECK_COUNTER_INUSE_ERROR(CounterID, &LenStatusReturn);

  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "CounterID have been checked before using" */
  OS_CHECK_COUNTER_APPLICATION_ACCESS_CROSS_CORE(LenStatusReturn, CounterID);

  #endif

  #if (OS_STATUS == EXTENDED)
  /* polyspace<RTE: UNR : Not a defect : No Action Planned > If multicore is not defined, this violation occurs. but this code has already been verified and no impact of this rule violation */
  /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "Boolean result is variant according to counter usage or multicore operation" */
  if (LenStatusReturn == (StatusType)E_OK)
  #endif
  {
    /* @Trace : SafeOs_SUD_API_10801 */
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "Value have been checked before using" */
    /* Previous value is stored */
    LddPreviousVal = *Value;
    /* Get the counter descriptor */
    LpStaticCounter = &Os_GaaStaticCounter[CounterID];
    #if (OS_HARDWARE_COUNTER_COUNT != OS_PRE_ZERO)
    /* If Counter is a HW Counter, update counter tick from HW timer */
    if (LpStaticCounter->pHwCounter != NULL_PTR)
    {
      /* @Trace : SafeOs_SUD_API_10802 */
      Os_UpdateHwCounter(LpStaticCounter->pHwCounter);
    }
    #endif
    /* Get the current counter value */
    LddCurrentVal = LpStaticCounter->pCounter->ddCurrentCount;
    /* Copy the counter value */
    *Value = LddCurrentVal;

    /* Check if LddCurrentVal is less than LddPreviousVal */
    if (LddCurrentVal < LddPreviousVal)
    {
      /* @Trace : SafeOs_SUD_API_10803 */
      LddCurrentVal += LpStaticCounter->ddMaxAllowedValue + OS_ONE;
    }
    /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "ElapsedValue have been checked before using" */
    /* Copy its value in Elapsedvalue ref */
    *ElapsedValue = LddCurrentVal - LddPreviousVal;
  }
  /* @Trace : SafeOs_SUD_API_10804 */
 /* polyspace-end MISRA-C3:14.3 [Justified:Low] "Boolean result is variant according to counter usage or multicore operation" */

  return LenStatusReturn;
}
#endif
/*******************************************************************************
** Function Name        : Os_KernIncrementCounter                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : IncrementCounter() increments the counter           **
**                        <CounterID> by one and returns E_OK.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : CounterID                                           **
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
**                        Os_GaaStaticCounter                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_CounterTick()                                    **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11021 SRS_Os_80013 SRS_Os_11020 */
#if (OS_COUNTER == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernIncrementCounter(CounterType CounterID)
{
  P2CONST(Tdd_Os_StaticCounter, AUTOMATIC, OS_CONST) LpStaticCounter;
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = (StatusType)E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
 /* Check for call from hook*/
  OS_CHECK_E_OS_CALLEVEL(INCREMENTCOUNTER, LenStatusReturn);
  /* Check whether CounterId is greater than number of Counter count */
  OS_CHECK_COUNTER_ID_ERROR(CounterID, &LenStatusReturn);
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "CounterID have been checked before using" */
  /* Check whether it's hardware counter or software counter */
  OS_CHECK_COUNTER_KIND_ERROR(CounterID, LenStatusReturn);
  /* Check if API is called on another core */
  OS_CHECK_COUNTER_RESIDING_COUNTER_ERROR(CounterID, OS_CORE_ID,
    LenStatusReturn);
  /* Check whether counter can access the Application */
  OS_CHECK_COUNTER_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, CounterID);
  /* polyspace +1 MISRA-C3:14.3 [Justified:Low] "This macro will be changed to inline function" */
  OS_CHECK_COUNTER_APPLICATION_ACCESS_CROSS_CORE(LenStatusReturn, CounterID);

  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "CounterID have been checked before using" */
  /* Check whether status return is E_OK */
  if (LenStatusReturn == (StatusType)E_OK)
  {
    /* @Trace : SafeOs_SUD_API_11001 */
    /* Pointer to static counter */
    LpStaticCounter = &Os_GaaStaticCounter[CounterID];
    /* Function called to increment count and to check if any alarm expires */
    (void)Os_CounterTick(LpStaticCounter);
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  else
  {
    /* @Trace : SafeOs_SUD_API_11002 */
    /* Store the ServiceID of the Function */
    OS_STORE_SERVICE(OSServiceId_IncrementCounter);
    /* Store the parameter 1 - CounterID */
    OS_STORE_PARAM1_COUNTERID(CounterID);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif

  /* Return the value */
  return (LenStatusReturn);
} /* End of Os_KernIncrementCounter(CounterType CounterID) */
#endif /* End of if (OS_COUNTER == STD_ON) */


/*******************************************************************************
** Function Name        : Os_KernGetCounterValue                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to get the current value       **
**                        of a counter.CounterId is the input parameter.      **
**                        value, is a reference (pointer) to the variable     **
**                        where the value of the counter is stored.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : CounterID                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : value                                               **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticCounter                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_DoGetCounterValue()                              **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Frt_00030 SRS_Frt_00031 SRS_Os_11020 SRS_Os_11021 SRS_Frt_00033 */
#if (OS_COUNTER == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernGetCounterValue(CounterType CounterID,
                                                              TickRefType Value)
{
  /* @Trace : SafeOs_SUD_API_10901 */
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  /* @Trace : SafeOs_SUD_API_10902 */
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(GETCOUNTERVALUE, LenStatusReturn);
  /* Check whether CounterId is greater than number of Counter count */
  OS_CHECK_COUNTER_ID_ERROR(CounterID, &LenStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(Value, LenStatusReturn);
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "CounterID have been checked before using" */
  /* Check whether counter can access the Application */
  OS_CHECK_COUNTER_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, CounterID);
  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_10903 */
    /* Call Os_DoGetCounterValue and get the return value */
    LenStatusReturn = Os_DoGetCounterValue(CounterID, Value);
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_10904 */
    /* Stores the ServiceID of the function */
    OS_STORE_SERVICE(OSServiceId_GetCounterValue);
    /* Store the parameter 1 - CounterID */
    OS_STORE_PARAM1_COUNTERID(CounterID);
    /* Store the parameter 2 - Value */
    OS_STORE_PARAM2_VALUEREF(Value);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif /* End of if (OS_STATUS == EXTENDED) */

  /* Return the value */
  return (LenStatusReturn);
} /* End of GetCounterValue(CounterType CounterID, TickRefType Value) */
#endif /* End of if (OS_COUNTER == STD_ON) */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "CounterID have been checked before using" */

/*******************************************************************************
** Function Name        : Os_KernGetElapsedValue                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to get the elapsed value       **
**                        of a counter                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : CounterID, Value                                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ElapsedValue                                        **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticCounter                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_DoGetElapsedCounterValue()                       **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11020 SRS_Os_11021 SRS_Frt_00034 */
#if (OS_COUNTER == STD_ON)
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
FUNC(StatusType, OS_CODE) Os_KernGetElapsedValue(CounterType CounterID,
                                    TickRefType Value, TickRefType ElapsedValue)
{
  /* @Trace : SafeOs_SUD_API_11101 */
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  /* @Trace : SafeOs_SUD_API_11102 */
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(GETELAPSEDVALUE, LenStatusReturn);
  /* Check whether CounterId is greater than number of Counter count */
  OS_CHECK_COUNTER_ID_ERROR(CounterID, &LenStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(Value, LenStatusReturn);
  /* Check the previous value does not exceed the max allowed value of the
   *   counter */
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "CounterID have been checked before using" */
  OS_CHECK_COUNTER_MAX_ALLOWED_VALUE_ERROR(CounterID, Value, LenStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(ElapsedValue, LenStatusReturn);
  /* Check whether counter can access the Application */
  OS_CHECK_COUNTER_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, CounterID);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace : SafeOs_SUD_API_11103 */
    /* Call Os_DoGetElapsedCounterValue and get the return value */
    LenStatusReturn = Os_DoGetElapsedCounterValue(CounterID,
                                                   Value, ElapsedValue);
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace : SafeOs_SUD_API_11104 */
    /* Stores the ServiceID of the function */
    /* polyspace +2 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +1 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    OS_STORE_SERVICE(OSServiceId_GetElapsedValue);
    /* Store the parameter 1 - CounterID */
    OS_STORE_PARAM1_COUNTERID(CounterID);
    /* Store the parameter 2 - Value */
    OS_STORE_PARAM2_VALUEREF(Value);
    /* Store the parameter 3 - ElapsedValue */
    OS_STORE_PARAM3_ELAPSEDVALUE(ElapsedValue);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif /* End of if (OS_STATUS == EXTENDED) */

  /* Return the value */
  return (LenStatusReturn);
} /* End of GetElapsedValue(CounterType CounterID, TickRefType Value,
   *TickRefType ElapsedValue) */
#endif /* End of if (OS_COUNTER == STD_ON) */
/* polyspace-end MISRA-C3:D4.14 [Justified:Low] "CounterID have been checked before using" */

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually." */
/* polyspace-end RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
