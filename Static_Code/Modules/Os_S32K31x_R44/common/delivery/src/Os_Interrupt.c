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
**  SRC-MODULE: Os_Interrupt.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Interrupt functionality.                         **
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
** 1.5.1     06-Oct-2023   JC.Kim           Jira CP44-2438                    **
** 1.5.0     13-Sep-2023   HJ.Kim           Jira CP44-2965                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.3     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
** 1.0.2     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.1     11-Aug-2020   DanhDC1          R44-Redmine #14813                **
**                                          Checking StartOs for              **
**                                          Resume/SupendOsInterrupt APIs     **
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
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os RAM header file */
#include "Os_Error.h"             /* Os Error header file */
/* @Trace: SRS_BSW_00410 */
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_TimingProtection.h"  /* Os TimerProtection header file */
#endif
#if (OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Application.h"       /* Os Application header file */
#endif
#include "Os_Kernel.h"            /* Os Kernel header file */
#include "Os_Interrupt.h"         /* Os Interrupt header file */
#if(OS_STACK_MONITORING == STD_ON)
#include "Os_Stack.h"
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
** Function Name        : Os_KernSuspendInterrupts                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function disables interrupts, implementing the **
**                        SuspendOSInterrupts(), SuspendAllInterrupts() and   **
**                        DisableAllInterrupts() system services.             **
**                        The type of lock is determined by the locktype      **
**                        parameter.                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : locktype                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GddISRLock, Os_GddISR2Lock, Os_GblISRLock,       **
**                        Os_GddOldSuspendOs, Os_GddOldSuspendAll,            **
**                        Os_GpStaticTask, Os_GusCallevelCheck                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StartMonitor(), Os_SuspendInterrupts()           **
**                        Os_IntDisableConditional(), Os_IntRestore()         **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11013 */
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
FUNC(void, OS_CODE) Os_KernSuspendInterrupts(OsIntLockType locktype)
{
  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  Os_OldLevel_T *olp = NULL_PTR;   /* Pointer to Old level store */
  Os_IsrLockType *ncp = NULL_PTR;  /* Pointer to nesting counter */
  Os_IntStatus_T is;
  Os_IntStatus_T level = 0;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  TickType LddRequestedTime;
  #endif

  #if (OS_STATUS == EXTENDED)
  StatusType LenStatusReturn;
  /* Initial status return to E_OK */
  LenStatusReturn = E_OK;
  #endif
  /* @Trace: SafeOs_SUD_API_05601 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* Here we manipulate the global old level/nesting counter variables. */
  if (locktype == OS_LOCKTYPE_OS)
  {
    /* @Trace: SafeOs_SUD_API_05602 */
    #if (OS_STATUS == EXTENDED)
    /* @Trace: SafeOs_SUD_API_05603 */
    /* Check whether Os started or not */
    OS_CHECK_NOT_STARTOS(&LenStatusReturn);
    /* No error */
    if (LenStatusReturn == E_OK)
    #endif
    {
      /* @Trace: SafeOs_SUD_API_05604 */
      /* Operation is a no-op if nested inside SuspendAllInterrupts() or
      * DisableAllInterrupts() */
      /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      if (Os_GddISRLock[OS_CORE_ID] == OS_ZERO)
      {
        #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
        /* @Trace: SafeOs_SUD_API_05605 */
        level = Os_CAT2_Max_Priority;
        #else
        /* @Trace: SafeOs_SUD_API_05606 */
        level = OS_ONE;
        #endif
        /* @Trace: SafeOs_SUD_API_05607 */
        olp = &Os_GddOldSuspendOs[OS_CORE_ID];
        ncp = &Os_GddISR2Lock[OS_CORE_ID];
      }
    }
  }
  else if (locktype == OS_LOCKTYPE_ALL)
  {
    /* @Trace: SafeOs_SUD_API_05608 */
    /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
    {
      /* @Trace: SafeOs_SUD_API_05609 */
      level = OS_INT_MAX_PRIORITY;
      olp = &Os_GddOldSuspendAll[OS_CORE_ID];
      ncp = &Os_GddISRLock[OS_CORE_ID];
    }
  }
  else if (locktype == OS_LOCKTYPE_NONEST)
  {
    /* @Trace: SafeOs_SUD_API_05610 */
    /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    if ((Os_GddISRLock[OS_CORE_ID] == OS_ZERO) &&
        (Os_GddISR2Lock[OS_CORE_ID] == OS_ZERO))
    {
      #if (OS_ISR_COUNT != OS_PRE_ZERO)
      /* @Trace: SafeOs_SUD_API_05611 */
      level = OS_INT_MAX_PRIORITY;
      #else
      /* @Trace: SafeOs_SUD_API_05612 */
      level = OS_ONE;
      #endif
      /* @Trace: SafeOs_SUD_API_05613 */
      olp = &Os_GddOldSuspendAll[OS_CORE_ID];
      ncp = &Os_GddISRLock[OS_CORE_ID];
    }
  }
  else
  /* polyspace<RTE: UNR : Not a defect : No Action Planned > This is for exceptional case. But this code has already been verified and no impact of this rule violation */
  {
    /* Do nothing */
  }

  /* No error */
  #if (OS_STATUS == EXTENDED)
  /* Check no error */
  /* @Trace: SafeOs_SUD_API_05614 */
  if ((LenStatusReturn == E_OK) && (ncp != NULL_PTR))
  #else
  /* @Trace: SafeOs_SUD_API_05615 */
  if (ncp != NULL_PTR)
  #endif /* End of if (OS_STATUS == EXTENDED) */
  {
    /* This branch actually does the job ...
     *
     * Interrupts disabled here to prevent a possible execution-time-
     * overrun interrupt from messing things up, especially if the
     * caller is a task.
     */
    /* @Trace: SafeOs_SUD_API_05616 */
    is = Os_IntDisableConditional();
    
    if (*ncp == 0)
    {
      /* OS_SuspendInterrupts is a macro that doesn't
       * attempt to ensure that its parameters are only evaluated
       * once. That's OK here because the parameters are simple
       * variables, not expressions
       *
       * OS_SuspendInterrupts() disables OS interrupts in the
       * current context AND in the calling context.
       *
       * We don't need to worry about a Cat1 ISR interrupting us,
       * because SuspendOsInterrupts in Cat1 is a no-op.
       *
       * The saved interrupt state is not restored in this branch
       * because OS_SuspendInterrupts() sets the required
       * level.
       */
      /* @Trace: SafeOs_SUD_API_05617 */
      *ncp = 1;

      if (locktype == OS_LOCKTYPE_NONEST)
      {
        /* @Trace: SafeOs_SUD_API_05618 */
        Os_GblISRLock[OS_CORE_ID] = OS_TRUE;
      }

      #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
      /* polyspace-begin MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
      if (
          #if (OS_CAT1_ISR_COUNT != OS_PRE_ZERO)
          (OS_NOT_IN_CAT1()) &&
          #endif
          ((Os_GusCallevelCheck[OS_CORE_ID] & (OS_CONTEXT_HOOK)) == OS_ZERO)
         )
      {
        /* @Trace: SafeOs_SUD_API_05619 */
        LpStaticTask = Os_GpStaticTask[OS_CORE_ID];
        /* Check if TP is configured for currently running object */
        /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually*/
        if (LpStaticTask->pStaticTimProtection != NULL_PTR)
        {
          #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
          if (locktype == OS_LOCKTYPE_OS)
          {
            /* @Trace: SafeOs_SUD_API_05620 */
            LddRequestedTime =
              /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
              LpStaticTask->pStaticTimProtection->ddInterruptLockTime;
            /* Check if OS Interrupt Lock Budget is configured */
            if (LddRequestedTime != OS_ZERO)
            {
              /* @Trace: SafeOs_SUD_API_05621 */
              /* Start monitoring for OS Interrupt Lock Budget */
              Os_StartMonitor(LddRequestedTime, OS_INT_LOCK, OS_INT_LOCK_INDEX);
            }
          }
          else
          #endif
          {
            /* @Trace: SafeOs_SUD_API_05622 */
            LddRequestedTime =
              /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
              LpStaticTask->pStaticTimProtection->ddAllInterruptLockTime;
            /* Check if All Interrupt Lock Budget is configured */
            if (LddRequestedTime != OS_ZERO)
            {
              /* @Trace: SafeOs_SUD_API_05623 */
              /* Start monitoring for All Interrupt Lock Budget */
              Os_StartMonitor(LddRequestedTime, OS_ALL_INT_LOCK, OS_ALL_INT_LOCK_INDEX);
            }
          }
        } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
      }
      #endif /* End of if ((OS_ALLINTLOCK_TP_EB == STD_ON)
              * || (OS_INTLOCK_TP_EB == STD_ON)) */
      /* polyspace-end MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
      /* @Trace: SafeOs_SUD_API_05624 */
      Os_SuspendInterrupts(olp, level);
    } /* End of if (*ncp == 0) */
    else if (*ncp < (Os_IsrLockType)OS_SUSPENDNESTLIMIT)
    {
      /* No need to restore the interrupt state here - they remain blocked
       * at the expected level. */
      /* @Trace: SafeOs_SUD_API_05625 */
      (*ncp)++;
    }
    else
    {
      /* @Trace: SafeOs_SUD_API_05626 */
      Os_IntRestore(is);
    }
  }

  #if (OS_STATUS == EXTENDED)
  /* @Trace: SafeOs_SUD_API_05627 */
  /* SuspendOSInterrupts API */
  if (locktype == OS_LOCKTYPE_OS)
  {
    /* @Trace: SafeOs_SUD_API_05628 */
    if (LenStatusReturn != E_OK)
    {
      /* @Trace: SafeOs_SUD_API_05629 */
      /* Store the service ID of SuspendOSInterrupts */
      /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      OS_STORE_SERVICE(OSServiceId_SuspendOSInterrupts);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LenStatusReturn);
    } /* End of if (LenStatusReturn != E_OK) */
  } /* End of if (locktype == OS_LOCKTYPE_OS) */
  #endif /* End of if (OS_STATUS == EXTENDED) */

  #endif
/* End of @ #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON)) */
}

/*******************************************************************************
** Function Name        : Os_KernResumeInterrupts                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Implements the ResumeOSInterrupts(),                **
**                        ResumeAllInterrupts() and EnableAllInterrupts()     **
**                        services. The type of interrupt locking             **
**                        being resumed is given by the locktype parameter.   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : locktype                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GddISRLock, Os_GddISR2Lock, Os_GblISRLock,       **
**                        Os_GddOldSuspendOs, Os_GddOldSuspendAll,            **
**                        Os_GpStaticTask, Os_GusCallevelCheck                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StopIntMonitor(), Os_ResumeInterrupts()          **
**                        Os_IntDisableConditional(), Os_IntRestore()         **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11009 SRS_Os_11013 */
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
FUNC(void, OS_CODE) Os_KernResumeInterrupts(OsIntLockType locktype)
{
  #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON))
  Os_OldLevel_T *olp = NULL_PTR;   /* Pointer to Old level store */
  Os_IsrLockType *ncp = NULL_PTR;  /* Pointer to nesting counter */
  Os_IntStatus_T is;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  TickType LddRequestedTime;
  #endif
  #if (OS_STATUS == EXTENDED)
  StatusType LenStatusReturn;

  /* Init status return to E_OK */
  LenStatusReturn = E_OK;
  #endif /* End of if (OS_STATUS == EXTENDED) */

  /* @Trace: SafeOs_SUD_API_05501 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);


  /* Here we manipulate the global old level/nesting counter variables. */
  if (locktype == OS_LOCKTYPE_OS)
  {
    #if (OS_STATUS == EXTENDED)
    /* @Trace: SafeOs_SUD_API_05502 */
    /* Check whether Os started or not */
    OS_CHECK_NOT_STARTOS(&LenStatusReturn);
    /* No error */
    if (LenStatusReturn == E_OK)
    #endif /* End of if (OS_STATUS == EXTENDED) */
    {
      /* @Trace: SafeOs_SUD_API_05503 */
      /* Operation is a no-op if nested inside SuspendAllInterrupts() or
      * DisableAllInterrupts() */
      /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      if (Os_GddISRLock[OS_CORE_ID] == 0)
      {
        /* @Trace: SafeOs_SUD_API_05504 */
        olp = &Os_GddOldSuspendOs[OS_CORE_ID];
        ncp = &Os_GddISR2Lock[OS_CORE_ID];
      }
    } /* End of @ if(LenStatusReturn == E_OK) */
  }
  else if (locktype == OS_LOCKTYPE_ALL)
  {
    /* @Trace: SafeOs_SUD_API_05505 */
    /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    if (Os_GblISRLock[OS_CORE_ID] == OS_FALSE)
    {
      /* @Trace: SafeOs_SUD_API_05506 */
      olp = &Os_GddOldSuspendAll[OS_CORE_ID];
      ncp = &Os_GddISRLock[OS_CORE_ID];
    }
  }
  else if (locktype == OS_LOCKTYPE_NONEST)
  {
    /* @Trace: SafeOs_SUD_API_05507 */
    /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    if (Os_GblISRLock[OS_CORE_ID] != OS_FALSE)
    {
      /* @Trace: SafeOs_SUD_API_05508 */
      olp = &Os_GddOldSuspendAll[OS_CORE_ID];
      ncp = &Os_GddISRLock[OS_CORE_ID];
    }
  }
  else
  /* polyspace<RTE: UNR : Not a defect : No Action Planned > This is for exceptional case. But this code has already been verified and no impact of this rule violation */
  {
    /* Do nothing */
  }
  #if (OS_STATUS == EXTENDED)
  /* @Trace: SafeOs_SUD_API_05509 */
  /* Check no error */
  if ((LenStatusReturn == E_OK) && (ncp != NULL_PTR))
  #else
  /* @Trace: SafeOs_SUD_API_05510 */
  if (ncp != NULL_PTR)
  #endif /* End of if (OS_STATUS == EXTENDED) */
  {
    /* @Trace: SafeOs_SUD_API_05511 */
    /* This branch actually does the job ... */
    is = Os_IntDisableConditional();

    if (*ncp == 1)
    {
      #if ((OS_ALLINTLOCK_TP_EB == STD_ON) || (OS_INTLOCK_TP_EB == STD_ON))
      /* polyspace-begin MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
      if (
          #if (OS_CAT1_ISR_COUNT != OS_PRE_ZERO)
          (OS_NOT_IN_CAT1()) &&
          #endif
          ((Os_GusCallevelCheck[OS_CORE_ID] & (OS_CONTEXT_HOOK)) == OS_ZERO)
         )
      {
        /* @Trace: SafeOs_SUD_API_05512 */
        LpStaticTask = Os_GpStaticTask[OS_CORE_ID];
        /* Check if TP is configured for currently running object */
        /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually*/
        if (LpStaticTask->pStaticTimProtection != NULL_PTR)
        {
          #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
          /* @Trace: SafeOs_SUD_API_05513 */
          if (locktype == OS_LOCKTYPE_OS)
          {
            /* @Trace: SafeOs_SUD_API_05514 */
            LddRequestedTime =
              /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
              LpStaticTask->pStaticTimProtection->ddInterruptLockTime;
            /* Check if OS Interrupt Lock Budget is configured */
            if (LddRequestedTime != OS_ZERO)
            {
              /* @Trace: SafeOs_SUD_API_05515 */
              /* Stop monitoring for OS Interrupt Lock Budget */
              Os_StopIntMonitor(LpStaticTask, OS_INT_LOCK_INDEX);
            }
          }
          else
          #endif
          {
            /* @Trace: SafeOs_SUD_API_05516 */
            LddRequestedTime =
              /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
              LpStaticTask->pStaticTimProtection->ddAllInterruptLockTime;
            /* Check if All interrupt Lock Budget is configured */
            if (LddRequestedTime != OS_ZERO)
            {
              /* @Trace: SafeOs_SUD_API_05517 */
              /*Stop monitoring for All Interrupt Lock Budget*/
              Os_StopIntMonitor(LpStaticTask, OS_ALL_INT_LOCK_INDEX);
            }
          }
        } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
      }
      #endif /* End of if ((OS_ALLINTLOCK_TP_EB == STD_ON)
              * || (OS_INTLOCK_TP_EB == STD_ON)) */
      /* polyspace-end MISRA-C3:10.1 [Justified:Low] "This code is verified manually and has no impact" */
      /* Os_ResumeInterrupts is a macro that doesn't
       * attempt to ensure that its parameters are only evaluated
       * once. That's OK here because the parameters are simple
       * variables, not expressions
       */
      /* @Trace: SafeOs_SUD_API_05518 */
      *ncp = 0;

      if (locktype == OS_LOCKTYPE_NONEST)
      {
        /* @Trace: SafeOs_SUD_API_05519 */
        Os_GblISRLock[OS_CORE_ID] = OS_FALSE;
      }

      Os_ResumeInterrupts(olp);

      /* We do not restore interrupts here because
       * Os_ResumeInterrupts() has set the level correctly
       */
    }
    else if ((locktype != OS_LOCKTYPE_NONEST) && (*ncp != 0))
    {
      /* @Trace: SafeOs_SUD_API_05520 */
      (*ncp)--;

      /* No need to restore here - already at the correct level */
    }
    else
    {
      /* @Trace: SafeOs_SUD_API_05521 */
      Os_IntRestore(is);
    }
  }

  #if (OS_STATUS == EXTENDED)
  /* @Trace: SafeOs_SUD_API_05522 */
  /* ResumeOSInterrupts API */
  if (locktype == OS_LOCKTYPE_OS)
  {
    /* @Trace: SafeOs_SUD_API_05523 */
    if (LenStatusReturn != E_OK)
    {
      /* @Trace: SafeOs_SUD_API_05524 */
      /* Store the service ID of ResumeOSInterrupts */
      /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      OS_STORE_SERVICE(OSServiceId_ResumeOSInterrupts);
      /* Report an error to error hook */
      OS_PROCESS_ERROR(LenStatusReturn);
    } /* End of if (LenStatusReturn != E_OK) */
  } /* End of if (locktype == OS_LOCKTYPE_OS) */
  #endif /* End of if (OS_STATUS == EXTENDED) */

  #endif
  /* End of @ #if ((OS_ISR_COUNT != OS_PRE_ZERO) || (OS_MULTICORE == STD_ON)) */
}

/*******************************************************************************
** Function Name        : Os_KernGetISRID                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to return the Id of the ISR    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : void                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ISRType                                             **
**                                                                            **
** Preconditions        : StartOS() function should be called.                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GpStaticTask                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 */
#if (OS_CAT2_ISR_COUNT > OS_PRE_ZERO)
FUNC(ISRType, OS_CODE) Os_KernGetISRID(void)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  ISRType LddISRValue;
  StatusType LenStatusReturn;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_05101 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Initialize variable */
  LddISRValue = OS_INVALID_VALUE;
  /* Set Return status to E_OK */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(GETISRID, LenStatusReturn);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_05102 */
    /* Store the global pointer to static task in local variable */
    LpStaticTask = Os_GpStaticTask[OS_CORE_ID];

    /* check whether the type of task is ISR */
    /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
    if (LpStaticTask->usType == OS_ISR2)
    {
      /* @Trace: SafeOs_SUD_API_05103 */
      /*Store the ID of the task in the local variable */
      /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
      LddISRValue = LpStaticTask->ddTaskId;
    }
  } /* End of if (LenStatusReturn == E_OK) */
  /* Return the value */
  return (LddISRValue);
} /* End of GetISRID(void) */
#endif /* End of if (OS_CAT2_ISR_COUNT > OS_PRE_ZERO) */

/*******************************************************************************
** Function Name        : Os_KernEnableInterruptSource                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to return the Id of the ISR    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ISRID, ClearPending                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ISRType                                             **
**                                                                            **
** Preconditions        : StartOS() function should be called.                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_EnableInterruptSource()                          **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11011 */
#if (OS_CAT2_ISR_COUNT != OS_ZERO)
FUNC(StatusType, OS_CODE) Os_KernEnableInterruptSource(ISRType ISRID,
                                                        boolean ClearPending)
{
  StatusType LenStatusReturn;
  #if (OS_ERROR_HOOK == STD_ON)
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_05401 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  #endif
  #if (OS_STATUS == EXTENDED)
  /* @Trace: SafeOs_SUD_API_05402 */
  /* Set Return status to E_OK */
  LenStatusReturn = E_OK;
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(ENABLEINTERRUPTSOURCE, LenStatusReturn);
  /* Check the ISRID is valid */
  OS_CHECK_ISR_ID_ERROR(ISRID, &LenStatusReturn);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  #endif
  {
    /* @Trace: SafeOs_SUD_API_05403 */
    LenStatusReturn = Os_EnableInterruptSource(ISRID, ClearPending);
  }

  #if (OS_STATUS == EXTENDED)
  /* @Trace: SafeOs_SUD_API_05404 */
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_05405 */
    /* Store service ID of EnableInterruptSource */
    OS_STORE_SERVICE(OSServiceId_EnableInterruptSource);
    /* Store the parameter 1 - ISRID */
    OS_STORE_PARAM1_ISRID(ISRID);
    /* Store the parameter 2 - ClearPending */
    OS_STORE_PARAM2_CLEAR_PENDING(ClearPending);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* Return the value */
  /* @Trace: SafeOs_SUD_API_05406 */
  return (LenStatusReturn);
} /* End of Os_KernEnableInterruptSource() */
#endif

/*******************************************************************************
** Function Name        : Os_KernDisableInterruptSource                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to disable interrupt source    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ISRID                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called.                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_DisableInterruptSource()                         **
*******************************************************************************/
/* @Trace: SRS_Os_00097 */
#if (OS_CAT2_ISR_COUNT != OS_ZERO)
FUNC(StatusType, OS_CODE) Os_KernDisableInterruptSource(ISRType ISRID)
{
  StatusType LenStatusReturn;
  #if (OS_ERROR_HOOK == STD_ON)
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_05201 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  #endif
  #if (OS_STATUS == EXTENDED)
  /* @Trace: SafeOs_SUD_API_05202 */
  /* Set Return status to E_OK */
  LenStatusReturn = E_OK;
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(DISABLEINTERRUPTSOURCE, LenStatusReturn);
  /* Check the ISRID is valid */
  OS_CHECK_ISR_ID_ERROR(ISRID, &LenStatusReturn);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  #endif
  {
    /* @Trace: SafeOs_SUD_API_05203 */
    LenStatusReturn = Os_DisableInterruptSource(ISRID);
  }

  #if (OS_STATUS == EXTENDED)
  /* @Trace: SafeOs_SUD_API_05204 */
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_05205 */
    /* Store service ID of DisableInterruptSource */
    OS_STORE_SERVICE(OSServiceId_DisableInterruptSource);
    /* Store the parameter 1 - ISRID */
    OS_STORE_PARAM1_ISRID(ISRID);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* @Trace: SafeOs_SUD_API_05206 */
  /* Return the value */
  return (LenStatusReturn);
} /* End of Os_KernDisableInterruptSource() */
#endif

/*******************************************************************************
** Function Name        : Os_KernClearPendingInterrupt                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to clear the pending interrupt **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ISRID                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : StatusType                                          **
**                                                                            **
** Preconditions        : StartOS() function should be called.                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_ClearPendingInterruptSource()                    **
*******************************************************************************/
/* @Trace: SRS_Os_11011 */
#if (OS_CAT2_ISR_COUNT != OS_ZERO)
FUNC(StatusType, OS_CODE) Os_KernClearPendingInterrupt(ISRType ISRID)
{
  StatusType LenStatusReturn;
  #if (OS_ERROR_HOOK == STD_ON)
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_05301 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  #endif
  #if (OS_STATUS == EXTENDED)
  /* @Trace: SafeOs_SUD_API_05302 */
  /* Set Return status to E_OK */
  LenStatusReturn = E_OK;
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(CLEARPENDINGINTERRUPT, LenStatusReturn);
  /* Check the ISRID is valid */
  OS_CHECK_ISR_ID_ERROR(ISRID, &LenStatusReturn);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  #endif /* End of if (OS_STATUS == EXTENDED) */
  {
    /* @Trace: SafeOs_SUD_API_05303 */
      LenStatusReturn = Os_ClearPendingInterruptSource(ISRID);
  }

  #if (OS_STATUS == EXTENDED)
  /* @Trace: SafeOs_SUD_API_05304 */
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_05305 */
    /* Store service ID of ClearPendingInterrupt */
    OS_STORE_SERVICE(OSServiceId_ClearPendingInterrupt);
    /* Store the parameter 1 - ISRID */
    OS_STORE_PARAM1_ISRID(ISRID);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* Return the value */
  return (LenStatusReturn);
} /* End of Os_KernClearPendingInterrupt() */
#endif

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
