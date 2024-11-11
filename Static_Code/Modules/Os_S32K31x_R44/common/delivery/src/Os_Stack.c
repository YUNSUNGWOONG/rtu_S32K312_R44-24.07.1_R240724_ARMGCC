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
**  SRC-MODULE: Os_Stack.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of  Stack functionality                             **
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
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
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
#include "Os_Kernel.h"            /* Os Kernel header file */
#include "Os_Stack.h"             /* Os Stack header file */
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_TimingProtection.h"  /* Os TimerProtection header file */
#endif
#include "Os_Shutdown.h"          /* Os Shutdown header file */

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
** Function Name        : Os_CheckStack                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service is used to measure the stack of the    **
**                        task                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : LpStaticTask                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStack,                                        **
**                        Os_GulOsAppSPTop,                                   **
**                        Os_GulUserSPTop                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_GetStackPointer(),                               **
**                        Os_GetStackSize(),                                  **
**                        Os_ProtectionHookService(),                         **
**                        Os_SyncShutdownOSService()                          **
*******************************************************************************/
/* @Trace: SRS_AUTRON_00002 SRS_BSW_00410 */
#if(OS_STACK_MONITORING == STD_ON)
/* polyspace +1 MISRA-C3:17.2 [Justified:Low] "Os_ProtectionHookService -> Os_KillTaskOrISR -> ReleaseSpinlock -> OS_SYSCALL_RELEASESPINLOCK -> Os_SystemCallReleaseSpinlock ->Os_KernReleaseSpinlock ->Os_SpinlockUnLockMethod -> Os_SpinlockUnLockResource -> Os_ScheduleService -> Os_CheckStack" */
FUNC(void, OS_CODE) Os_CheckStack(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
                                                         OS_CONST) LpStaticTask)
{
  P2VAR(Os_StackType, AUTOMATIC, OS_VAR) LpStackTop;
  P2VAR(Os_StackType, AUTOMATIC, OS_VAR) LpStackBtm;
  P2VAR(uint32, AUTOMATIC, OS_VAR) LpStackaddress;
  boolean LblStackFailed = OS_FALSE;

  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* @Trace: SafeOs_SUD_API_11201 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* Get the stack area for the current running task/ISR */
  LpStackaddress = Os_GetStackPointer(LpStaticTask);

  #if (OS_EVENT == STD_ON)
  /* polyspace +1 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
  if(LpStaticTask->usType == OS_TASK_EXTENDED)
  {
    /* @Trace: SafeOs_SUD_API_11202 */
    /* Store the top address of the task stack area in the local pointer */
    /* polyspace +2 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "configured array index" */
    LpStackTop = (Os_GaaStack[LpStaticTask->ucStackIndex].pStackArea);
    /* Store the bottom address of the task stack area in the local pointer */
    /* polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
    /* polyspace +1 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput."*/
    LpStackBtm = &LpStackTop[Os_GetStackSize(LpStaticTask)];
    /* polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
  }
  else /* BASIC TASK, CAT2 ISR */
  #endif /* End of #if (OS_EVENT == STD_ON) */
  {
    #if (OS_APPLICATION == STD_ON)
    /* polyspace +1 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
    if(LpStaticTask->ddTaskId != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_11203 */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "configured memory access index" */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually*/
      LpStackBtm = LpStaticTask->pContext->pPowerOnSP;

      /* polyspace-begin CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
      /* polyspace +3 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
      /* polyspace +2 RTE:OBAI [Not a defect:Low] "configured array index" */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Medium] "Conversion is needed for implementation" */
      LpStackTop = (Os_StackType*)Os_GulOsAppSPTop[LpStaticTask->ddAppId];
      /* polyspace-end CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */

    }
    else
    #endif
    {
      /* @Trace: SafeOs_SUD_API_11204 */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "configured memory access index" */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually*/
      LpStackBtm = LpStaticTask->pContext->pPowerOnSP;
      /* polyspace +6 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +5 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace +4 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
      /* polyspace-begin CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
      /* polyspace +2 RTE:OBAI [Not a defect:Low] "configured array index" */
      /* polyspace +1 MISRA-C3:11.4 [Justified:Medium] "Conversion is needed for implementation" */
      LpStackTop = (Os_StackType*)Os_GulUserSPTop[OS_CORE_ID];
      /* polyspace-end CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */

    }
  }

  /* polyspace<RTE: ABS_ADDR : Not a defect : Justify with annotations > This is intended to check invalid address */
  /* polyspace +1 MISRA-C3:11.4 [Justified:Medium] "Conversion is needed for implementation" */
  if (LpStackaddress == (uint32*)INVALID_STACK_POINTER)
  {
    /* If stack pointer is invalid, just check a stack pattern */
    /* polyspace +3 RTE:NIV [Not a defect:Low] "variable is initialized and code is verified manually" */
    /* polyspace +2 RTE:IDP [Not a defect:Low] "configured memory access index" */
    /* polyspace<MISRA-C:1.1:Not a defect:Justify with annotations> It is necessary for 64bit data */
    if((*(Os_StackType*)(LpStackTop)) != OS_STACK_PATTERN)
    {
      /* @Trace: SafeOs_SUD_API_11205 */
      LblStackFailed = OS_TRUE;
    }
  }
  else
  {
    /* Check stack range and a stack pattern */
    if(((LpStackaddress) > (Os_StackType*)(LpStackBtm)) ||
             ((LpStackaddress) < (Os_StackType*)(LpStackTop)) ||
    /* polyspace<RTE:NIV:Not a defect:Justify with annotations> variable is initialized and code is verified manually */
    /* polyspace<RTE: IDP : Not a defect : Justify with annotations > configured memory access index */
    /* polyspace<MISRA-C:1.1:Not a defect:Justify with annotations> It is necessary for 64bit data */
                          ((*(Os_StackType*)(LpStackTop)) != OS_STACK_PATTERN))
    {
      /* @Trace: SafeOs_SUD_API_11206 */
      LblStackFailed = OS_TRUE;
    }
  }

  if (LblStackFailed == OS_TRUE)
  {
    #if (OS_PROTECTION_HOOK == STD_ON)
    {
      /* @Trace: SafeOs_SUD_API_11207 */
      (void)Os_ProtectionHookService(E_OS_STACKFAULT);
    }
    #else
    /* @Trace: SafeOs_SUD_API_11208 */
    /*
     * NTC.9 : The called function ShutdownOS (in the current context)
     *         either contains an error or does not terminate
     * Description: As per requirement OS425, ShutdownOS() shall
     *              enter an endless loop, thus this warning is encountered.
     */
    Os_SyncShutdownOSService(E_OS_STACKFAULT);
    #endif
  }
} /* End of Os_CheckStack(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
   *OS_CONST) LpStaticTask) */
#endif /* End of if (OS_STACK_MONITORING == STD_ON) */

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
