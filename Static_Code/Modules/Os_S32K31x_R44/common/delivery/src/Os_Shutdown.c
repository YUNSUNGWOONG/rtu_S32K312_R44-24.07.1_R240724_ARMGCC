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
**  SRC-MODULE: Os_Shutdown.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of  Shutdown functionality.                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:                                              **
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
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2005                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.5     16-Sep-2020   Thao             R44-Redmine #13398 Change access  **
**                                          rights of specific Os application **
**                                          Hooks                             **
** 1.0.4     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
** 1.0.3     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Add comment for Misra-C D4.9      **
** 1.0.2     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C 20.7                **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os RAM header file */
#include "Os_Shutdown.h"          /* Os Shutdown header file */
#include "Os_Error.h"             /* Os Error header file */
#include "Os_Kernel.h"            /* Os Kernel header file */
#include "Os_SpinLock.h"          /* Os Spinlock header file */
/* @Trace: SRS_BSW_00410 */
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
** Function Name        : Os_ShutdownCore                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called to shutdown specific core   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Error, ShutdownType                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaCore, Os_GaaStaticAppHook,                    **
**                        Os_Application_Count, Os_GblCoreShutdown            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SetSyncCountShutDown(),                          **
**                        Os_WaitSyncShutDown()                               **
*******************************************************************************/
/* NOTE: Shutdown synchronized before global ShutdownHook and others */
/* @Trace: SRS_Os_11018 SRS_Os_80007 SRS_Os_11013 */
FUNC(void, OS_CODE) Os_ShutdownCore(StatusType Error,
                                                   Os_ShutdownType ShutdownType)
{
  #if (OS_APP_SHUTDOWN_HOOK == STD_ON)
  P2CONST(Tdd_Os_ApplicationHook, AUTOMATIC, OS_CONST) LpApplication;
  uint8 LucAppCount;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_21801 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  #if (OS_APP_SHUTDOWN_HOOK == STD_ON)
  /* Point to first application */
  /* @Trace: SafeOs_SUD_API_21802 */
  LpApplication = &Os_GaaStaticAppHook[OS_ZERO];
  LucAppCount = OS_ZERO;

  /* Run through the while loop for all the applications */
  do
  {
    /* Check if AppShutdownHook is configured for the application */
    /* polyspace +1 RTE:UNR [Not a defect:Justified] "Check NULL_PTR is done" */
    if (LpApplication->pShutDownHook != NULL_PTR)
    {
      #if(OS_MULTICORE == STD_ON)
      if (Os_GaaStaticAppHook[LucAppCount].ddCoreID == OS_CORE_ID)
      #endif
      {
        /* @Trace: SafeOs_SUD_API_21803 */
        /* Process Application ShutdownHook */
        /* polyspace +1 RTE:UNR [Not a defect:Justified] "Check NULL_PTR is done" */
        OS_PROCESS_APP_SHUTDOWNHOOK((ApplicationType)LucAppCount, (LpApplication->pShutDownHook), Error);
      }
    }
    /* @Trace: SafeOs_SUD_API_21804 */
    /* Point to next application */
    LucAppCount++;
    LpApplication++;
  } while (LucAppCount < Os_Application_Count);
  #else
  OS_UNUSED(Error);
  #endif /* End of if (OS_APP_SHUTDOWN_HOOK == STD_ON) */

  #if (OS_MULTICORE == STD_ON)
  /* @Trace: SafeOs_SUD_API_21805 */
  /* Set a flag for core shutdown */
  /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
  /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
  /* polyspace +1 RTE:OBAI [Not a defect:Low] "configured array index" */
  Os_GblCoreShutdown[OS_CORE_ID] = OS_TRUE;

  Os_SetSyncCountShutDown();
  if (ShutdownType == OS_SHUTDOWN_SYNCHRONIZED)
  {
    /* @Trace: SafeOs_SUD_API_21806 */
    /* Wait for Synchronization till all the cores shut down */
    Os_WaitSyncShutDown();
  }
  #else
  OS_UNUSED(ShutdownType);
  #endif

  #if (OS_SHUTDOWN_HOOK == STD_ON)
  /* @Trace: SafeOs_SUD_API_21807 */
  /* Process ShutdownHook */
  /* polyspace +1 RTE:OBAI [Not a defect:Low] "configured array index" */
  OS_PROCESS_SHUTDOWNHOOK(Error);
  #endif
  /* @Trace: SafeOs_SUD_API_21808 */
  /* Disable all interrupts */
  OS_DISABLEINTERRUPTS();

  /* when using debugger, the "halt" mode can be exited,
   *   so this infinite loop is used only in this case */
 /* polyspace RTE:NTL [Not a defect:Low] "Shutdown with infinite loop is intended instruction." */
  /* @Trace: SafeOs_SUD_API_21809 */
  OS_INFINITELOOP();

} /* End of Os_ShutdownCore(StatusType Error) */

/*******************************************************************************
** Function Name        : Os_KernShutdownOS                                   **
**                                                                            **
** Service ID           : OSServiceId_ShutdownOS                              **
**                                                                            **
** Description          : This function is called when OS needs to be         **
**                        shutdown                                            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   N/A                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_ShutdownOSService()                              **
*******************************************************************************/
/* NOTE: [OS617] ShutdownOS shall shutdown the core on which it was called. */
/* @Trace: SRS_Os_00097 SRS_Os_11006 SRS_Os_11009 SRS_Os_11013 */
FUNC(void, OS_CODE) Os_KernShutdownOS(StatusType Error)
{
  StatusType LenStatusReturn;
  #if((OS_SCALABILITY_CLASS > OS_SC2) && (OS_TRUSTED_START_INDX != OS_ZERO))
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_21901 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  #endif
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(SHUTDOWNOS, LenStatusReturn);
  /* polyspace +4 MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
  /* polyspace +3 MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
  /* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
  /* Check if the caller belongs to a non-trusted application: OS054*/
  OS_CHECK_CALLER_APPLICATION_ERROR(OS_INVALID_VALUE, LenStatusReturn);
 /* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */

  if(LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_21902 */
    Os_ShutdownOSService(Error);
  }
} /* End of ShutdownOS(StatusType Error) */

/*******************************************************************************
** Function Name        : Os_ShutdownOSService                                **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function is called when OS needs to be         **
**                        shutdown forcibly                                   **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :   None                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_ShutdownCore(), Os_ReleaseAllSpinlocks()         **
*******************************************************************************/
/* @Trace: SRS_Os_11006 SRS_Os_11014 SRS_Os_80007 SRS_Os_80021  */
FUNC(void, OS_CODE) Os_ShutdownOSService(StatusType Error)
{
  #if (OS_SPINLOCK == STD_ON)
  /* Release all the spinlocks associated with the core */
  /* @Trace: SafeOs_SUD_API_21601 */
  Os_ReleaseAllSpinlocks();
  #endif
  /* @Trace: SafeOs_SUD_API_21602 */
  /* Call Os_ShutdownCore */
  Os_ShutdownCore(Error, OS_SHUTDOWN_INDIVIDUAL);
}

/*******************************************************************************
** Function Name        : Os_SyncShutdownOSService                             **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function is called when OS needs to do         **
**                        synchronized shutdown forcibly                      **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_ReleaseAllSpinlocks(),                           **
**                        Os_ShutdownCore(),                                  **
**                        Os_SendShutdownAllCores()                           **
*******************************************************************************/
FUNC(void, OS_CODE) Os_SyncShutdownOSService(StatusType Error)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  CoreIDType LddCoreCount;
  #endif
  /* @Trace: SafeOs_SUD_API_21701 */
  /* Disable all interrupts */
  OS_DISABLEINTERRUPTS();

  #if (OS_SPINLOCK == STD_ON)
  /* @Trace: SafeOs_SUD_API_21702 */
  /* Release all the spinlocks associated with the core */
  Os_ReleaseAllSpinlocks();
  #endif

  #if (OS_MULTICORE == STD_ON)
  /* @Trace: SafeOs_SUD_API_21703 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* Send shutdown message to all cores. No answer is expected. */
  LddCoreCount = Os_Core_Count;
  /* polyspace RTE:NTL [Not a defect:Low] "Shutdown with infinite loop is intended instruction." */
  do
  {
    /* @Trace: SafeOs_SUD_API_21704 */
    LddCoreCount--;
    if (OS_CORE_ID != LddCoreCount)
    {
      /* @Trace: SafeOs_SUD_API_21705 */
      Os_SendShutdownAllCores(LddCoreCount, Error);
    }
  } while (LddCoreCount != OS_ZERO);
  /* @Trace: SafeOs_SUD_API_21706 */
  /* Call Os_ShutdownCore */
  Os_ShutdownCore(Error, OS_SHUTDOWN_SYNCHRONIZED);
  #else
  /* @Trace: SafeOs_SUD_API_21707 */
  Os_ShutdownCore(Error, OS_SHUTDOWN_INDIVIDUAL);
  #endif
}

/*******************************************************************************
** Function Name        : Os_KernShutdownAllCores                             **
**                                                                            **
** Service ID           : OSServiceId_ShutdownAllCores                        **
**                                                                            **
** Description          : This function is called when OS needs to be         **
**                        shutdown on all the cores                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GblShutdownFlag, Os_GucError, Os_GddAppId        **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_ReleaseAllSpinlocks(),                           **
**                        Os_SendShutdownAllCores(),                          **
**                        Os_ShutdownCore()                                   **
*******************************************************************************/
/* @Trace: SRS_Os_80007 SRS_Os_11013 */
#if (OS_MULTICORE == STD_ON)
FUNC(void, OS_CODE) Os_KernShutdownAllCores(StatusType Error)
{
  CoreIDType OS_CORE_ID;
  CoreIDType LddCoreCount;
  StatusType LenStatusReturn;

  /* @Trace: SafeOs_SUD_API_50601 */
  /* Init the LenStatusReturn to E_OK */
  LenStatusReturn = E_OK;
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(SHUTDOWNALLCORES, LenStatusReturn);
 /* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
  /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
  /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
  /* Check if caller belongs to non trusted application  OS716*/
  OS_CHECK_CALLER_APPLICATION_ERROR(OS_INVALID_VALUE, LenStatusReturn);
  /* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */

  if(LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_50602 */
    /* Disable all interrupts */
    OS_DISABLEINTERRUPTS();

    #if (OS_SPINLOCK == STD_ON)
    /* @Trace: SafeOs_SUD_API_50603 */
    /* Release all the spinlocks associated with the core */
    Os_ReleaseAllSpinlocks();
    #endif
    /* @Trace: SafeOs_SUD_API_50604 */
    /* Send shutdown message to all cores. No answer is expected. */
    LddCoreCount = Os_Core_Count;
    /* polyspace RTE:NTL [Not a defect:Low] "Shutdown with infinite loop is intended instruction." */
    do
    {
      /* @Trace: SafeOs_SUD_API_50605 */
      LddCoreCount--;
      if (OS_CORE_ID != LddCoreCount)
      {
        /* @Trace: SafeOs_SUD_API_50606 */
        Os_SendShutdownAllCores(LddCoreCount, Error);
      }
    } while (LddCoreCount != OS_ZERO);

    /* @Trace: SafeOs_SUD_API_50607 */
    /* Call Os_ShutdownCore */
    Os_ShutdownCore(Error, OS_SHUTDOWN_SYNCHRONIZED);
  }
} /* End of ShutdownAllCores(StatusType Error) */
#endif /* End of if (OS_MULTICORE == STD_ON) */

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
