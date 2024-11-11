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
**  SRC-MODULE: Os_Resource.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of  Resource functionality.                         **
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
** 1.5.0     13-Sep-2023   HJ.Kim           Jira CP44-2965                    **
**           26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.2     23-Mar-2021   Thao             Redmine #18032 (1.0.6.0)          **
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
/* @Trace: SRS_BSW_00410 */
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_TimingProtection.h"   /* Os TimerProtection header file */
#endif
#include "Os_Error.h"             /* Os Error header file */
#if (OS_RESOURCE == STD_ON)
#include "Os_Resource.h"          /* Os Resource header file */
#endif
#if (OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Application.h"       /* Os Application header file */
#endif
#include "Os_Interrupt.h"         /* Os Interrupt header file */
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

#if (OS_RESOURCE == STD_ON)
static FUNC(StatusType, OS_CODE) Os_DoGetResource(ResourceType ResID);
static FUNC(StatusType, OS_CODE) Os_DoReleaseResource(ResourceType ResID);
#endif

/*******************************************************************************
** Function Name        : Os_DoGetResource                                    **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This Function is used to Get the resource           **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ResourceType ResID                                  **
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
**                        Os_GaaResourceTable, Os_GpLinkTask,                 **
**                        Os_GaaHardWareResource, Os_GaaStaticTask            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_StartMonitor(), Os_RaisePriority(),              **
*******************************************************************************/
/* polyspace-begin DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
#if (OS_RESOURCE == STD_ON)
static FUNC(StatusType, OS_CODE) Os_DoGetResource(ResourceType ResID)
{
  #if (OS_RES_INT_SHARE == STD_ON)
  P2CONST(Tdd_Os_HardWareResource, AUTOMATIC, OS_CONST) LpStaticResource;
  #endif
  #if (OS_RES_TP_EB == STD_ON)
  TickType LddRequestedTime;
  #endif
  P2VAR(Tdd_Os_Resource, AUTOMATIC, OS_VAR) LpResource;
  P2VAR(Tdd_Os_Task, AUTOMATIC, OS_VAR) LpTask;
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  StatusType LenStatusReturn = E_OK;

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LpResource = &Os_GaaResourceTable[ResID];
  /* Get the currently running Task in a local pointer */
  /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  LpStaticTask = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];
  #if (OS_RES_TP_EB == STD_ON)

  /* Check if timing protection is configured for currently running object */
  if (LpStaticTask->pStaticTimProtection != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_09901 */
    /* polyspace +3 MISRA-C3:D4.14 [Justified:Low] "ResID have been checked before using" */
    /* polyspace +2 RTE:NIP [Not a defect:Unset] "ptr points to a valid value and code is verified manually" */
    LddRequestedTime =
                   LpStaticTask->pStaticTimProtection->pResourceLockTime[ResID];

    /* Check if Resource Lock Budget is configured */
    if (LddRequestedTime != OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_09902 */
      Os_StartMonitor(LddRequestedTime, OS_REZ_LOCK,
                                                LpResource->ddResLockTimeIndex);
    }
  } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
  #endif /* End of if (OS_RES_TP_EB == STD_ON) */

  #if (OS_RES_INT_SHARE == STD_ON)
  /* Store the pointer to the resource for corresponding ResID to the
   *   local pointer */
  LpStaticResource = &Os_GaaHardWareResource[ResID];

  /* Check if hardware priority is not the invalid priority */
  /* polyspace +2 MISRA-C3:14.3 [Not a defect:Low] "Check the validily of hardware priority" */
  /* polyspace +1 DEFECT:USELESS_IF [Not a defect:Low] "Check the validily of hardware priority" */
  if (LpStaticResource->ulHardwarePriority != OS_INVALID_HW_PRIORITY)
  {
    /* @Trace: SafeOs_SUD_API_09903 */
    (void)Os_RaisePriority(LpResource, LpStaticResource->ulHardwarePriority);
  }
  #endif /* End of if (OS_RES_INT_SHARE == STD_ON) */
  LpTask = LpStaticTask->pTask;
  /* Set the owner of the resource to the calling task */
  LpResource->pOwner = LpTask;
  /* Add the ressource at the beginning of the resource list stored in the
   *   task descriptor */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually */
  LpResource->pNextResource = LpTask->pResources;
  /* Occupy requested resource */
  LpTask->pResources = LpResource;
  /* Save the current priority of the task in the resource */
  LpResource->scOwnerPrevPriority = (uint8)Os_GpLinkTask[OS_CORE_ID]->scPriority;

  if (Os_GpLinkTask[OS_CORE_ID]->scPriority < (sint8) LpResource->scCeilingPriority)
  {
    /* @Trace: SafeOs_SUD_API_09904 */
    /* Update Priority for Os_GpLinkTask */
    Os_GpLinkTask[OS_CORE_ID]->scPriority = (sint8) LpResource->scCeilingPriority;
  }
  /* @Trace: SafeOs_SUD_API_09905 */
  return LenStatusReturn;
}
#endif /* End of if (OS_RESOURCE == STD_ON) */
/* polyspace-end DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
/*******************************************************************************
** Function Name        : Os_KernGetResource                                  **
**                                                                            **
** Service ID           : OSServiceId_GetResource                             **
**                                                                            **
** Description          : This Service is used to Get the resource            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : ResourceType ResID                                  **
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
**                        Os_GaaResourceTable                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_DoGetResource()                                  **
*******************************************************************************/
/* polyspace-begin DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
/* @Trace: SRS_Os_00097 */
#if (OS_RESOURCE == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernGetResource(ResourceType ResID)
{
  StatusType LenStatusReturn;
  ResourceType LulResID = ResID;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_10001 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(GETRESOURCE, LenStatusReturn);
  /* Check whether ResID is greater than number of Resource count */
  OS_CHECK_RESOURCE_ID_ERROR(LulResID, &LenStatusReturn);
  /* Get the pointer to Resource structure */
  #if ((OS_MULTICORE == STD_ON) && (OS_RES_SCHEDULER == STD_ON))
  if(LulResID == RES_SCHEDULER)
  {
    /* @Trace: SafeOs_SUD_API_10002 */
    /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "configured resource scheduler and os core id" */
    LulResID = RES_SCHEDULER + OS_CORE_ID;
  }
  #endif
  /* Return an error if the task that attempt to get the resource that has a
   *   higher priority than the resource or the resource is already owned by
   *   another task */
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "ResID have been checked before using" */
  /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  OS_CHECK_RESOURCE_PRIO_ERROR_ON_GET(&Os_GaaResourceTable[LulResID],
                                                               LenStatusReturn);
  /* Check whether resource can access the Application */
  OS_CHECK_RESOURCE_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, LulResID);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_10003 */
    /* Call Os_DoActivateTask and get the return value */
    LenStatusReturn = Os_DoGetResource(LulResID);
  } /* End of if (LenStatusReturn == E_OK) */
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "ResID have been checked before using" */
  #if (OS_STATUS == EXTENDED)
  else
  {
    /* @Trace: SafeOs_SUD_API_10004 */
    /* Store the service Id of GetResource */
    /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    OS_STORE_SERVICE(OSServiceId_GetResource);
    /* Store the parameter 1 - ResID */
    OS_STORE_PARAM1_RESID(LulResID);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /*Return the value */
  return (LenStatusReturn);
} /* End of GetResource(ResourceType ResID) */
#endif /* End of if (OS_RESOURCE == STD_ON) */
/* polyspace-end DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
/*******************************************************************************
** Function Name        : Os_DoReleaseResource                                **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This Service is used to Release the resource        **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : ResourceType ResID, boolean LblRemoteCall           **
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
**                        Os_GaaResourceTable, Os_GpLinkTask                  **
**                        Os_GaaHardWareResource, Os_GaaStaticTask            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_OriginalPriority(), Os_InsertPreemptedTask()     **
**                        Os_StopResMonitor(), Os_ScheduleService(),          **
**                        Os_TaskPreemptionHook()                             **
*******************************************************************************/
/* polyspace-begin DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
/* @Trace: SRS_Os_00097 SRS_AUTRON_00017 */
#if (OS_RESOURCE == STD_ON)
static FUNC(StatusType, OS_CODE) Os_DoReleaseResource(ResourceType ResID)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  #if (OS_RES_INT_SHARE == STD_ON)
  P2CONST(Tdd_Os_HardWareResource, AUTOMATIC, OS_CONST) LpStaticResource;
  #endif
  P2VAR(Tdd_Os_Resource, AUTOMATIC, OS_VAR) LpResource;
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpNextLink;
  #if (OS_RES_TP_EB == STD_ON)
  TickType LddRequestedTime;
  #endif
  const StatusType LenStatusReturn = E_OK;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  LpResource = &Os_GaaResourceTable[ResID];
  /* Get the currently running Task in a local pointer */
  /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  LpStaticTask = &Os_GaaStaticTask[Os_GpLinkTask[OS_CORE_ID]->ddTaskID];
  #if (OS_RES_TP_EB == STD_ON)

  /* Check if timing protection is configured for currently running object */
  if (LpStaticTask->pStaticTimProtection != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_10101 */
    /* polyspace +3 MISRA-C3:D4.14 [Justified:Low] "ResID Info have been checked before using" */
    /* polyspace +2 RTE:NIP [Not a defect:Unset] "ptr points to a valid value and code is verified manually" */
    LddRequestedTime =
                   LpStaticTask->pStaticTimProtection->pResourceLockTime[ResID];

    /* Check if Resource Lock Budget is configured */
    if (LddRequestedTime != OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_10102 */
      /* Stop resource lock budget */
      Os_StopResMonitor(LpStaticTask, LpResource);
    }
  } /* End of if (LpStaticTask->pStaticTimProtection != NULL_PTR) */
  #endif /* OS_TIMING_PROTECTION */

  /* Save the current priority of the task in the resource   */
  Os_GpLinkTask[OS_CORE_ID]->scPriority = (sint8) LpResource->scOwnerPrevPriority;
  /* Remove the resource from the resource list  */
  LpStaticTask->pTask->pResources = LpResource->pNextResource;
  /* Update NextResource of the Resource with NULL_PTR*/
  LpResource->pNextResource = NULL_PTR;
  /* Remove the owner */
  LpResource->pOwner = NULL_PTR;
  #if (OS_RES_INT_SHARE == STD_ON)
  /* Store the pointer to the resource for corresponding ResID to the
   *   local pointer */
  LpStaticResource = &Os_GaaHardWareResource[ResID];

  /* Check if hardware priority of the resource is not invalid */
  /* polyspace +2 MISRA-C3:14.3 [Not a defect:Low] "Check the validily of hardware priority" */
  /* polyspace +1 DEFECT:USELESS_IF [Not a defect:Low] "Check the validily of hardware priority" */
  if (LpStaticResource->ulHardwarePriority != OS_INVALID_HW_PRIORITY)
  {
    /* @Trace: SafeOs_SUD_API_10103 */
    (void)Os_OriginalPriority(LpResource);
  }
  #endif /* End of if (OS_RES_INT_SHARE == STD_ON) */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually */
  LpNextLink = Os_GpLinkTask[OS_CORE_ID]->pLinkList;

  /* Check if Context switch is required */
  if (LpNextLink->scPriority > Os_GpLinkTask[OS_CORE_ID]->scPriority)
  {
    /* @Trace: SafeOs_SUD_API_10104 */
    #if (OS_POSTTASK_HOOK == STD_ON)
    /* Process PostTaskHook */
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
    OS_PROCESS_POSTTASKHOOK();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
    #endif

    /* Update Os_GpLinkTask */
    Os_GpLinkTask[OS_CORE_ID] = LpNextLink;
    #if (OS_TASK == STD_ON)
    /* Insert the preempted task */
    Os_InsertPreemptedTask(LpStaticTask);
    #endif
    /* Change state of the running task to ready */
    LpStaticTask->pTask->ddState = READY;
    #if (OS_PROFILING_HOOK == STD_ON)
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
    Os_TaskPreemptionHook(OS_CORE_ID, LpStaticTask->ddTaskId);
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
    #endif
    Os_ScheduleService();
    OS_SAVECONTEXT();
  } /* End of if (LpNextLink->scPriority >
       *Os_GpLinkTask[OS_CORE_ID]->scPriority) */
  /* @Trace: SafeOs_SUD_API_10105 */
  return LenStatusReturn;
}
#endif /* End of if (OS_RESOURCE == STD_ON) */
/* polyspace-end DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
/*******************************************************************************
** Function Name        : Os_KernReleaseResource                              **
**                                                                            **
** Service ID           : OSServiceId_ReleaseResource                         **
**                                                                            **
** Description          : This Service is used to Release the resource        **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non re-entrant                                      **
**                                                                            **
** Input Parameters     : ResourceType ResID                                  **
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
**                        Os_GaaResourceTable                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_DoReleaseResource()                              **
*******************************************************************************/
/* polyspace-begin DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
/* @Trace: SRS_Os_00097 */
#if (OS_RESOURCE == STD_ON)
FUNC(StatusType, OS_CODE) Os_KernReleaseResource(ResourceType ResID)
{
  StatusType LenStatusReturn;
  #if ((OS_MULTICORE == STD_ON) && (OS_RES_SCHEDULER == STD_ON))
  ResourceType LulResID = ResID;
  #else
  const ResourceType LulResID = ResID;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_10201 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set the return status value to "E_OK" */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(RELEASERESOURCE, LenStatusReturn);
  /* Check whether ResID is greater than number of Resource count */
  OS_CHECK_RESOURCE_ID_ERROR(LulResID, &LenStatusReturn);
  /* Get the pointer to Resource structure */
  #if ((OS_MULTICORE == STD_ON) && (OS_RES_SCHEDULER == STD_ON))
  if(LulResID == RES_SCHEDULER)
  {
    /* @Trace: SafeOs_SUD_API_10202 */
    /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "configured resource scheduler and os core id" */
    LulResID = RES_SCHEDULER + OS_CORE_ID;
  }
  #endif
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "ResID have been checked before using" */
  /* Return an error if the task that attempt to get the resource has a higher
   *   priority than the resource */
  /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  OS_CHECK_RESOURCE_PRIO_ERROR_ON_RELEASE(&Os_GaaResourceTable[LulResID],
                                                               LenStatusReturn);
  /* Check the order of release */
  /* polyspace:begin<RTE: NIP : Not a defect : No Action Planned > Check validity of the point */
  OS_CHECK_RESOURCE_ORDER_ON_RELEASE(&(Os_GaaResourceTable[LulResID]),
                                                               LenStatusReturn);
  /* polyspace:end<RTE: NIP : Not a defect : No Action Planned > Check validity of the point */
  /* Check whether resource can access the Application */
  OS_CHECK_RESOURCE_APPLICATION_ACCESS_SELF_CORE(LenStatusReturn, LulResID);
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "ResID have been checked before using" */
  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_10203 */
    LenStatusReturn = Os_DoReleaseResource(LulResID);
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  else
  {
    /* @Trace: SafeOs_SUD_API_10204 */
    /* Store the service Id of ReleaseResource */
    /* polyspace +3 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    /* polyspace +1 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
    OS_STORE_SERVICE(OSServiceId_ReleaseResource);
    /* Store the parameter 1 - ResID */
    OS_STORE_PARAM1_RESID(LulResID);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif /* End of if (OS_STATUS == EXTENDED) */

  /* Return The value */
  return (LenStatusReturn);
} /* End of ReleaseResource(ResourceType ResID) */
#endif /* End of if (OS_RESOURCE == STD_ON) */
/* polyspace-end DEFECT:UNMODIFIED_VAR_NOT_CONST [Not a defect:low] The pointer variable is const-qualified type*/
/*******************************************************************************
** Function Name        : Os_GetInternalResource                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is used to Take internal resource      **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpStaticTask                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GpLinkTask()                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 */
#if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO)
FUNC(void, OS_CODE) Os_GetInternalResource(P2CONST(Tdd_Os_StaticTask,
                                              AUTOMATIC, OS_CONST) LpStaticTask)
{
  P2VAR(Tdd_Os_InternalResource, AUTOMATIC, OS_VAR) LpInternalResource;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_09701 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Get the pointer to internal resouce */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually */
  LpInternalResource = LpStaticTask->pInternalResource;

  /* Check If internal resource is configured for the Task and if it is not
   *   taken by any other task */
  if ((LpInternalResource != NULL_PTR) &&
      (LpInternalResource->ucTaken == OS_FALSE))
  {
    /* @Trace: SafeOs_SUD_API_09702 */
    /* Change status of the Resource as TAKEN */
    LpInternalResource->ucTaken = OS_TRUE;
    /* BasePriority of the task is assigned to OwenerPrevious priority */
    LpInternalResource->scOwnerPrevPriority =
      (uint8) Os_GpLinkTask[OS_CORE_ID]->scPriority;
    /* Update priority in Os_GpLinkTask */
    Os_GpLinkTask[OS_CORE_ID]->scPriority =
      (sint8) LpInternalResource->scCeilingPriority;
  } /* End of if ((LpInternalResource != NULL_PTR) && */
} /* End of Os_GetInternalResource(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
   *OS_CONST) LpStaticTask) */
#endif /* End of if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO) */

/*******************************************************************************
** Function Name        : Os_ReleaseInternalResource                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is used to Release internal resource   **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpStaticTask                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GpLinkTask                                       **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO)
FUNC(void, OS_CODE) Os_ReleaseInternalResource(P2CONST(
                           Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask)
{
  P2VAR(Tdd_Os_InternalResource, AUTOMATIC, OS_VAR) LpInternalResource;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_09601 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace<RTE: NIP : Not a defect : No Action Planned > ptr points to a valid value and code is verified manually */
  if (LpStaticTask->pInternalResource != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_09602 */
    /* Get the pointer to internal resouce */
    LpInternalResource = LpStaticTask->pInternalResource;

    /* Check if internal resource is taken by the task */
    if (LpInternalResource->ucTaken == OS_TRUE)
    {
      /* @Trace: SafeOs_SUD_API_09603 */
      /* Change status of the Resource as FALSE */
      LpInternalResource->ucTaken = OS_FALSE;
      /* Update priority in Os_GpLinkTask */
      Os_GpLinkTask[OS_CORE_ID]->scPriority =
        (sint8) LpInternalResource->scOwnerPrevPriority;
    } /* End of if (LpInternalResource->ucTaken == OS_TRUE) */
  } /* End of if (LpStaticTask->pInternalResource != NULL_PTR) */
} /* End of Os_ReleaseInternalResource(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
   *OS_VAR) LpStaticTask) */
#endif /* End of if (OS_INTERNAL_RESOURCE_COUNT > OS_PRE_ZERO) */

/*******************************************************************************
** Function Name        : Os_ReleaseResourceService                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is used to Release resource            **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpStaticTask                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaHardWareResource                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_00097 */
#if (OS_RESOURCE == STD_ON)
FUNC(void, OS_CODE) Os_ReleaseResourceService(P2CONST(Tdd_Os_StaticTask,
                                              AUTOMATIC, OS_CONST) LpStaticTask)
{
  P2VAR(Tdd_Os_Resource, AUTOMATIC, OS_VAR) LpResource;
  /* @Trace: SafeOs_SUD_API_09805 */
  /* Check if current running task is configured for resouces*/
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
  if (LpStaticTask->pTask->pResources != NULL_PTR)
  {
    /* @Trace: SafeOs_SUD_API_09801 */
    /* Update the resource of the running task in a local */
    LpResource = LpStaticTask->pTask->pResources;

    do
    {
      /*
       * Release the Resource
       * Remove the resource from the resource list
       */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
      /* @Trace: SafeOs_SUD_API_09802 */
      LpStaticTask->pTask->pResources = LpResource->pNextResource;
      /* Update NextResource of the Resource with NULL_PTR*/
      LpResource->pNextResource = NULL_PTR;
      /* Remove the owner */
      LpResource->pOwner = NULL_PTR;
      #if (OS_RES_INT_SHARE == STD_ON)
      /* @Trace: SafeOs_SUD_API_09803 */
      /* Store the pointer to the resource for corresponding ResID to the
       *   local pointer */
      LpResource->ulOwnerPrevHwPrio = OS_ZERO;
      #endif /* End of if (OS_RES_INT_SHARE == STD_ON) */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
      /* @Trace: SafeOs_SUD_API_09804 */
      LpResource = LpStaticTask->pTask->pResources;
    } while (LpResource != NULL_PTR);
  } /* End of if (LpStaticTask->pTask->pResources != NULL_PTR) */
} /* End of Os_ReleaseResourceService(P2CONST(Tdd_Os_StaticTask, AUTOMATIC,
   *OS_CONST) LpStaticTask) */
#endif /* End of if (OS_RESOURCE == STD_ON) */

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
