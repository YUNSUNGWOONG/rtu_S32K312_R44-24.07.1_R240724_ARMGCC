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
**  SRC-MODULE: Os_Application.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of  Os-Application and Protection functionality     **
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
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2247                    **
**                                          Jira CP44-2028                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.1.0     20-Apr-2021   Thao             R44-Redmine #17907                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.5     16-Sep-2020   Thao             R44-Redmine #13485 Produce panic  **
**                                          if restart of Os application      **
**                                          without restart task configured   **
** 1.0.4     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
**                                          R44-Redmine #12870                **
** 1.0.3     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C 8.5, 10.3, 16.1     **
**                                          Add comment for Misra-C D4.5,17.2 **
** 1.0.2     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.1     31-Apr-2020   DanhDC1          #13426  Check NULL_PTR            **
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
/* @Trace: SRS_Os_11016 */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Kernel.h"            /* Os Kernel header file */
#include "Os_Ram.h"               /* Os Ram header file */
#include "Os_Error.h"             /* Os Error header file */

#if ((OS_APPLICATION == STD_ON) || (OS_MEMORY_PROTECTION == STD_ON))
#include "Os_Application.h"       /* Os Application header file */
#endif
#include "Os_SystemCallTable.h"
/* @Trace: SRS_BSW_00410 */
#if (OS_TASK == STD_ON)
#include "Os_Task.h"              /* Os Task header File */
#endif
#if (OS_ALARM == STD_ON)
#include "Os_Alarm.h"             /* Os Alarm header File */
#endif
#if (OS_TIMING_PROTECTION == STD_ON)
#include "Os_TimingProtection.h"  /* Os TimerProtection header file */
#endif
#if (OS_SCHEDTABLE == STD_ON)
#include "Os_SchedTable.h"
#endif
#if (OS_RESOURCE == STD_ON)
#include "Os_Resource.h"          /* Os Resource header file */
#endif
#include "Os_Multicore.h"
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
#define APPLICATION_TERMINATING \
                          ((ApplicationStateType)(0x80u|APPLICATION_TERMINATED))

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 SRS_Os_11012 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#if (OS_SCALABILITY_CLASS >= OS_SC3)
static FUNC(ObjectAccessType, OS_CODE) Os_CheckObjectAccessService(
   ApplicationType ApplID, ObjectTypeType ObjectType, ObjectTypeIndex ObjectID);
#endif

/***************************************************************************//**
 * Function Name        : Os_KernGetApplicationID
 *
 * Service ID           : NA
 *
 * Description          : This Service returns the ID of running application
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameters           : None
 *
 * @return              : ApplicationType
 *                        - 0 ~ OS_APPLICATION_COUNT - 1 : No error
 *                        - INVALID_OSAPPLICATION : Interrupts are disabled
 *                          by user or it is called from wrong context
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GddAppId
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
/* @Trace: SRS_Os_80016 SRS_Os_80005 SRS_Os_80015 */
#if (OS_APPLICATION == STD_ON)
FUNC(ApplicationType, OS_CODE) Os_KernGetApplicationID(void)
{
  StatusType LenStatusReturn;
  ApplicationType LenApplicationType;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_17601 */
  /* Get Core Id*/
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set Return status to E_OK */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(GETAPPLICATIONID, LenStatusReturn);

  if(LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_17602 */
    LenApplicationType = Os_GddAppId[OS_CORE_ID];
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_17603 */
    LenApplicationType = INVALID_OSAPPLICATION;
  }

  return LenApplicationType;
} /* End of GetApplicationID(void) */
#endif /* End of #if (OS_APPLICATION == STD_ON) */

/***************************************************************************//**
 * Function Name        : Os_KernGetCurrentApplicationID
 *
 * Service ID           : NA
 *
 * Description          : This Service returns the ID of running application
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * Parameters           : None
 *
 * @return              : ApplicationType
 *                        - 0 ~ OS_APPLICATION_COUNT - 1 : No error
 *                        - INVALID_OSAPPLICATION : Error
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GddAppId, Os_GaaApplication, Os_GddCurAppId
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_80005 SRS_Os_80015 SRS_Os_80016 */
#if (OS_APPLICATION == STD_ON)
FUNC(ApplicationType, OS_CODE) Os_KernGetCurrentApplicationID(void)
{
  StatusType LenStatusReturn;
  ApplicationType LenApplicationType;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_17801 */
  /* Get Core Id*/
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Set Return status to E_OK */
  LenStatusReturn = E_OK;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(GETCURRENTAPPLICATIONID, LenStatusReturn);

  /* Check whether status return is E_OK */
  if(LenStatusReturn == E_OK)
  {
  #if (OS_TRUSTED_FUNC_COUNT != OS_PRE_ZERO)
  /* Check the caller is within a CallTrustedFunction() call */
  if(Os_GaaApplication[Os_GddAppId[OS_CORE_ID]].ddState == \
                      APPLICATION_HAS_CALLTRUSTEDFUNC)
  {
    /* @Trace: SafeOs_SUD_API_17802 */
    /* The application id where the caller is currently excuting */
    LenApplicationType = Os_GddCurAppId[OS_CORE_ID];
  }
  else
  #endif
    {
      /* @Trace: SafeOs_SUD_API_17803 */
      /* The application id is equal to GetApplicationID() */
      LenApplicationType = Os_GddAppId[OS_CORE_ID];
    } /* End of else */
  } /* @end of (LenStatusReturn == E_OK) */
  else
  {
    /* @Trace: SafeOs_SUD_API_17804 */
    /* There is an error and set INVALID_OSAPPLICATION to LenApplicationType */
    LenApplicationType = INVALID_OSAPPLICATION;
  }

  /* Return the Status */
  return LenApplicationType;
} /* End of GetCurrentApplicationID(void) */
#endif /* End of #if (OS_APPLICATION == STD_ON) */

/***************************************************************************//**
 * Function Name        : Os_KernAllowAccess
 *
 * Service ID           : NA
 *
 * Description          : This Service checks if access is to be granted for
 *                        application
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
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
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaApplication, Os_GddAppId
 *
 *                        Function(s) invoked    :
 *                        Os_EnableAppInterrupts()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11006 SRS_Os_80005 SRS_Os_80015 SRS_Os_80016 SRS_Os_11016 */
#if (OS_SCALABILITY_CLASS >= OS_SC3)
FUNC(StatusType, OS_CODE) Os_KernAllowAccess(void)
{
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  StatusType LenStatusReturn;
  /* @Trace: SafeOs_SUD_API_18001 */
  /* Set Return status to E_OK */
  LenStatusReturn = E_OK;
  /* Get Core Identifier */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(ALLOWACCESS, LenStatusReturn);
  /* Check if Application is already Accessible */
  OS_CHECK_APPLICATION_STATE(LenStatusReturn);
  if(LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_18002 */
    /* Update state with Accessible */
    Os_GaaApplication[Os_GddAppId[OS_CORE_ID]].ddState =
                                                       APPLICATION_ACCESSIBLE;
    #if((OS_CAT2_ISR_COUNT != OS_ZERO) && (OS_APPLICATION == STD_ON))
    /* @Trace: SafeOs_SUD_API_18003 */
    /* Enable interrupts belonging to the application */
    Os_EnableAppInterrupts();
    #endif
  }
  #if (OS_STATUS == EXTENDED)
  else
  {
    /* @Trace: SafeOs_SUD_API_18004 */
    /* Store service Id of AllowAccess */
    OS_STORE_SERVICE(OSServiceId_AllowAccess);
    /* Report an error to error hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif
  /* Return the Status */
  return (LenStatusReturn);
} /* End of AllowAccess(void) */
#endif /* End of if (OS_SCALABILITY_CLASS >= OS_SC3) */

/***************************************************************************//**
 * Function Name        : Os_KernGetApplicationState
 *
 * Service ID           : NA
 *
 * Description          : This Service is used to get the application state
 *                        from the given Application ID
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
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
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaApplication
 *
 *                        Function(s) invoked    :
 *                        Os_SendGetApplicationState(),
 *                        Os_DoGetApplicationState()
 ******************************************************************************/

/* @Trace: SRS_Os_00097 */
#if (OS_SCALABILITY_CLASS >= OS_SC3)
FUNC(StatusType, OS_CODE) Os_KernGetApplicationState(
                     ApplicationType Application, ApplicationStateRefType Value)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Set Return status to E_OK */
  /* @Trace: SafeOs_SUD_API_17901 */
  LenStatusReturn = E_OK;

  OS_GET_CORE_ID(OS_CORE_ID);
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(GETAPPLICATIONSTATE, LenStatusReturn);
  /* Check whether Application is greater than number of Application count */
  OS_CHECK_APPL_ID_ERROR(Application, LenStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(Value, LenStatusReturn);

  /* Check whether status return is E_OK */
  if (LenStatusReturn == E_OK)
  {
    #if (OS_MULTICORE == STD_ON)
    /* Check if new task belongs to same core */
    if (Os_GaaStaticApplication[Application].ddCoreID != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_17902 */
      Os_SendGetApplicationState(Application, Value);
    } /* End of if (LpStaticTask->ddCoreId != OS_CORE_ID) */
    else
    #endif /* End of if (OS_MULTICORE == STD_ON) */
    {
      /* @Trace: SafeOs_SUD_API_17903 */
      Os_DoGetApplicationState(Application, Value);
    }
  }
  #if (OS_STATUS == EXTENDED)
  else
  {
    /* @Trace: SafeOs_SUD_API_17904 */
    /* Store service ID of GetApplicationState */
    OS_STORE_SERVICE(OSServiceId_GetApplicationState);
    /* Store the parameter 1 - Application */
    OS_STORE_PARAM1_APPLICATION(Application);
    /* Store the parameter 2 - Value */
    OS_STORE_PARAM2_APPVALUEREF(Value);
    /* Call Error Hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of if (LenStatusReturn != E_OK) */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* Return the value */
  return (LenStatusReturn);
} /* End of GetApplicationState(ApplicationType Application,
   *ApplicationStateRefType Value) */

#endif /* End of if (OS_SCALABILITY_CLASS >= OS_SC3) */

/***************************************************************************//**
 * Function Name        : Os_DoGetApplicationState
 *
 * Service ID           : NA
 *
 * Description          : This service returns the Applcation state
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * @param[in]             Application    The OS-Application from which the
 *                                       state is requested
 *                                       (range : 0 ~ OS_APPLICATION_COUNT - 1)
 * @param[out]            Value          The current state of the application
 *                                       (range : APPLICATION_ACCESSIBLE,
 *                                                APPLICATION_RESTARTING,
 *                                                APPLICATION_TERMINATED)
 *
 * @return              : void
 *
 * @pre                 : Application and Value should be checked
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaApplication
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/

#if (OS_SCALABILITY_CLASS >= OS_SC3)
FUNC(void, OS_CODE) Os_DoGetApplicationState(ApplicationType Application,
                                                  ApplicationStateRefType Value)
{
  /* @Trace: SafeOs_SUD_API_17401 */
  /* polyspace +2 CERT-C:ARR30-C [Not a defect:Low] "The LulObjectMask variable has been assigned value before used" */
  /* polyspace +1 MISRA-C3:D4.14 [Justified:Low] "ptr Value have been checked before using" */
  *Value = Os_GaaApplication[Application].ddState & (ApplicationStateType)0x0F;

}
#endif

/***************************************************************************//**
 * Function Name        : Os_KernCheckISRMemoryAccess
 *
 * Service ID           : NA
 *
 * Description          : This service checks if a memory region is write/
 *                        read/execute accessible and also returns information
 *                        if the memory region is part of the stack space.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
 *
 * @param[in]             ISRID    CAT2 ISR reference
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
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GddAppId
 *
 *                        Function(s) invoked    :
 *                        Os_CheckMemoryAccessService()
 ******************************************************************************/
/* @Trace: SRS_Os_11005 SRS_Os_11006 SRS_Os_11007 SRS_Os_11000 */
#if (OS_SCALABILITY_CLASS >= OS_SC3)
FUNC(AccessType, OS_CODE) Os_KernCheckISRMemoryAccess(ISRType ISRID,
                            MemoryStartAddressType Address, MemorySizeType Size)
{
  AccessType LenAccessReturn;
  StatusType LenStatusReturn;

  /* @Trace: SafeOs_SUD_API_14601 */
  /* Set Return status to E_OK */
  LenStatusReturn = E_OK;
  /* Set Eccess Return to NO_ACCESS */
  LenAccessReturn = NO_ACCESS;
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(CHECKISRMEMORYACCESS, LenStatusReturn);
  /* Check whether ISRID is correct */
  OS_CHECK_ISR_ID_ERROR(ISRID, &LenStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(Address, LenStatusReturn);

  /* Check if LenAccessReturn is ACCESS */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_14602 */
    /* Call Os_CheckMemoryAccessService */
    LenAccessReturn = Os_CheckMemoryAccessService((ObjectTypeType)ISRID,
                                                                 Address, Size);
  }
  /* Return the Status */
  return (LenAccessReturn);
} /* End of CheckISRMemoryAccess(ISRType ISRID, MemoryStartAddressType Address,
   *MemorySizeType Size) */
#endif /* End of if (OS_SCALABILITY_CLASS >= OS_SC3) */

/***************************************************************************//**
 * Function Name        : Os_KernCheckTaskMemoryAccess
 *
 * Service ID           : OSServiceId_CheckTaskMemoryAccess
 *
 * Description          : This service checks if a memory region is write/
 *                        read/execute accessible and also returns information
 *                        if the memory region is part of the stack space.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
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
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GddAppId
 *
 *                        Function(s) invoked    :
 *                        Os_CheckMemoryAccessService()
 ******************************************************************************/
/* @Trace: SRS_Os_11005 SRS_Os_11006 SRS_Os_11007 SRS_Os_11000 */
#if (OS_SCALABILITY_CLASS >= OS_SC3)
FUNC(AccessType, OS_CODE) Os_KernCheckTaskMemoryAccess(TaskType TaskID,
                            MemoryStartAddressType Address, MemorySizeType Size)
{
  AccessType LenAccessReturn;
  StatusType LenStatusReturn;

  /* @Trace: SafeOs_SUD_API_14501 */
  /* Set Return status to E_OK */
  LenStatusReturn = E_OK;
  /* Set Eccess Return to NO_ACCESS */
  LenAccessReturn = NO_ACCESS;

  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(CHECKTASKMEMORYACCESS, LenStatusReturn);
  /* Check whether TaskID is correct */
  OS_CHECK_TASK_ID_ERROR(TaskID, LenStatusReturn);
  /* Check for NULL_PTR */
  OS_CHECK_NULL_PTR(Address, LenStatusReturn);

  /* Check if LenStatusReturn is E_OK */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_14502 */
    /* Call Os_CheckMemoryAccessService */
    LenAccessReturn = Os_CheckMemoryAccessService((ObjectTypeType)TaskID,
      Address, Size);
  }
  /* Return the Status */
  return (LenAccessReturn);
} /* End of CheckTaskMemoryAccess(TaskType TaskID, MemoryStartAddressType
   *Address, MemorySizeType Size) */
#endif /* End of if (OS_SCALABILITY_CLASS >= OS_SC3) */

/***************************************************************************//**
 * Function Name        : Os_KernCheckObjectAccess
 *
 * Service ID           : NA
 *
 * Description          : This Service checks whether access can be granted
 *                        to the application for the specified Object
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
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
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GddAppId
 *
 *                        Function(s) invoked    :
 *                        Os_CheckObjectAccessService()
 ******************************************************************************/
/* @Trace: SRS_Os_11006 SRS_Os_80005 SRS_Os_80015 SRS_Os_80016 */
#if (OS_SCALABILITY_CLASS >= OS_SC3)
FUNC(ObjectAccessType, OS_CODE) Os_KernCheckObjectAccess(ApplicationType ApplID,
                            ObjectTypeType ObjectType, ObjectTypeIndex ObjectID)
{
  ObjectAccessType LenObjReturn;
  StatusType LenStatusReturn;

  /* Set Return status to NO_ACCESS */
  /* @Trace: SafeOs_SUD_API_17701 */
  LenObjReturn = NO_ACCESS;
  /* Set Status Return to E_OK */
  LenStatusReturn = E_OK;

  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(CHECKOBJECTACCESS, LenStatusReturn);
  /* Check whether Application is greater than number of Application count */
  OS_CHECK_OBJ_ACCESS_APPL_ID_ERROR(ApplID, LenStatusReturn);
  /* Check whether ObjectType is correct */
  OS_CHECK_OBJECT_TYPE_ERROR(ObjectType, LenStatusReturn);

  /* Check if LenStatusReturn is ACCESS or not */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_17702 */
    /* Invoke Os_CheckObjectAccessService */
    LenObjReturn = Os_CheckObjectAccessService(ApplID, ObjectType, ObjectID);
  }
  /* Return the value */
  return (LenObjReturn);
} /* End of CheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType,
   *ObjectTypeIndex ObjectID) */
#endif /* End of if (OS_SCALABILITY_CLASS >= OS_SC3) */

/***************************************************************************//**
 * Function Name        : Os_CheckObjectAccessService
 *
 * Service ID           : OSServiceId_CheckObjectAccess
 *
 * Description          : This Service checks whether access can be granted
 *                        to the application for the specified Object
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Re-entrant
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
 *                                     or <ObjectID> is not valid
 *
 * @pre                 : StartOS() function should be called,
 *                        ApplID and ObjectType should be checked
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticTask, Os_GaaStaticAlarm
 *                        Os_GaaResourceTable, Os_GaaStaticCounter
 *                        Os_GaaStaticSchedTable, Os_GaaStaticApplication
 *                        Os_GaaApplication
 *
 *                        Function(s) invoked    :
 *                        Os_CheckObjIDError()
 ******************************************************************************/
/* @Trace: SRS_Os_11006 */
#if (OS_SCALABILITY_CLASS >= OS_SC3)
static FUNC(ObjectAccessType, OS_CODE) Os_CheckObjectAccessService(
    ApplicationType ApplID, ObjectTypeType ObjectType, ObjectTypeIndex ObjectID)
{
  P2CONST(Tdd_Os_Application, AUTOMATIC, OS_CONST) LpStaticApplication;
  StatusType LenStatusReturn;
  ObjectAccessType LenAccessReturn;
  uint32 LulMask;
  uint32 LulObjectMask;
  ApplicationType LddObjAppId;
  #if (OS_SCHEDTABLE == STD_ON)
  AlarmType LddAlarmIndex;
  #endif
  /* @Trace: SafeOs_SUD_API_18101 */
  LddObjAppId = OS_INVALID_VALUE;
  LenAccessReturn = NO_ACCESS;
  LenStatusReturn = E_OK;

  /* Check whether ObjectID is correct */
  if(ObjectType == OBJECT_TASK)
  {
    /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "Number of core and task can be configured" */
    /* polyspace +2 DEFECT:USELESS_IF [Not a defect:Low] "Number of core can be configured" */
    if(((ObjectID) >= (Os_Task_Count + Os_Core_Count))
                                                 || (ObjectID < Os_Core_Count))
    /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "Number of core and task can be configured" */
    {
      /* @Trace: SafeOs_SUD_API_18102 */
      LenStatusReturn = E_OS_ID;
    }
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_18103 */
    LenStatusReturn = Os_CheckObjIDError(ObjectType, ObjectID);
  }

  /* Check if LenStatusReturn is ACCESS or not */
  if (LenStatusReturn == E_OK)
  {
    /* @Trace: SafeOs_SUD_API_18104 */
    LpStaticApplication = &Os_GaaStaticApplication[ApplID];
    /* Even TRUSTED does not have access to all the objects as per OS448
     *   thus a check is not incorporated.*/
    /* Calculate Mask for the Application ID */
    LulMask = LpStaticApplication->ulAppMask;
    /* polyspace-begin MISRA-C3:16.6 [Not a defect:Low] "The LulObjectMask value initialized when all of option off" */
    /* polyspace-begin MISRA-C3:16.1 [Not a defect:Low] "The LulObjectMask value initialized when all of option off" */
    switch (ObjectType)
    {
      #if (OS_TASK == STD_ON)
      case OBJECT_TASK:
        /* @Trace: SafeOs_SUD_API_18105 */
        /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "ObjectID have been checked before using" */
        /* Get the ObjectMask in Local variable */
        LulObjectMask = Os_GaaStaticTask[ObjectID].ddAppAccesMask;
        /* Copy the AppId of the requested object in local */
        LddObjAppId = Os_GaaStaticTask[ObjectID].ddAppId;
        break;
      #endif /* End of if (OS_TASK == STD_ON) */

      #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
      case OBJECT_ISR: /* If the Type is ISR grant the access */
        /* @Trace: SafeOs_SUD_API_18106 */
        LulObjectMask = OS_FULLACCESS;
        LddObjAppId = Os_GaaStaticTask[ObjectID].ddAppId;
        break;
      #endif

      #if (OS_ALARM == STD_ON)
      case OBJECT_ALARM:
        /* @Trace: SafeOs_SUD_API_18107 */
        /* Get the ObjectMask in Local variable */
        LulObjectMask = Os_GaaStaticAlarm[ObjectID].ddAppAccesMask;
        /* Copy the AppId of the requested object in local */
        LddObjAppId = Os_GaaStaticAlarm[ObjectID].ddAppId;
        break;

      #endif /* End of if (OS_ALARM == STD_ON) */
      #if (OS_RESOURCE == STD_ON)
      case OBJECT_RESOURCE:
        /* @Trace: SafeOs_SUD_API_18108 */
        /* Get the ObjectMask in Local variable*/
        LulObjectMask = Os_GaaResourceTable[ObjectID].ddAppAccesMask;
        /* Copy the AppId of the requested object in local */
        LddObjAppId = Os_GaaResourceTable[ObjectID].ddAppId;
        break;

      #endif /* End of if (OS_RESOURCE == STD_ON) */
      #if (OS_COUNTER == STD_ON)
      case OBJECT_COUNTER:
        /* @Trace: SafeOs_SUD_API_18109 */
        /* Get the ObjectMask in Local variable */
        LulObjectMask = Os_GaaStaticCounter[ObjectID].ddAppAccesMask;
        /* Copy the AppId of the requested object in local */
        LddObjAppId = Os_GaaStaticCounter[ObjectID].ddAppId;
        break;

      #endif /* End of if (OS_COUNTER == STD_ON) */
      #if (OS_SCHEDTABLE == STD_ON)
      case OBJECT_SCHEDULETABLE:
        /* @Trace: SafeOs_SUD_API_18110 */
        /* Get the index of the alarm structure */
        LddAlarmIndex = Os_GaaStaticSchedTable[ObjectID].ddAlarmIndex;
        /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "ObjectID have been checked before using" */
        /* Get the mask from the alarm structure in local
         *   variable */
        LulObjectMask = Os_GaaStaticAlarm[LddAlarmIndex].ddAppAccesMask;
        /* Copy the AppId of the requested object in local */
        LddObjAppId = Os_GaaStaticAlarm[LddAlarmIndex].ddAppId;
        break;

      #endif /* End of if (OS_SCHEDTABLE == STD_ON) */
      /* polyspace +2 RTE:UNR [No action planned:Low] "Default switch-case with no Os object masks" */
      /* @Trace: SafeOs_SUD_API_18111 */
      default:         LulObjectMask = OS_ZERO;
        break;
    } /* End of switch (ObjectType) */
    /* polyspace-end MISRA-C3:16.1 [Not a defect:Low] "The LulObjectMask value initialized when all of option off" */
    /* polyspace-end MISRA-C3:16.6 [Not a defect:Low] "The LulObjectMask value initialized when all of option off" */

    /* Check if Access can be granted */
    if (LddObjAppId == ApplID)
    {
      /* @Trace: SafeOs_SUD_API_18112 */
        LenAccessReturn = ACCESS;
    }
    /* polyspace +6 CERT-C:ARR30-C [Not a defect:Low] "The LulObjectMask variable has been assigned value before used" */
    /* polyspace +4 MISRA-C3:14.3 [Not a defect:Low] "The LulObjectMask variable has been assigned value before used" */
    /* polyspace +3 MISRA-C3:2.1 [Not a defect:Low] "The LulObjectMask variable has been assigned value before used" */
    /* polyspace-begin DEFECT:DEAD_CODE DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "LulObjectMask has been assigned value before used " */
    /* polyspace-begin MISRA-C3:18.1 [Not a defect:Low] "LddObjAppId has been assigned valid value before used" */
    else if (((LulObjectMask & LulMask) != OS_FALSE) &&
        (Os_GaaApplication[LddObjAppId].ddState == APPLICATION_ACCESSIBLE))
    /* polyspace-end MISRA-C3:18.1 [Not a defect:Low] "LddObjAppId has been assigned valid value before used" */
    /* polyspace-end DEFECT:DEAD_CODE DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "LulObjectMask has been assigned value before used " */
    {
      /* @Trace: SafeOs_SUD_API_18113 */
      /* Grant the access */
      LenAccessReturn = ACCESS;
    }
    else
    {
        /* @Trace: SafeOs_SUD_API_18114 */
      /* Grant No Access */
      LenAccessReturn = NO_ACCESS;
    }
  } /* End of if (LenStatusReturn == ACCESS) */
  /* Return the value */
  return (LenAccessReturn);
} /* End of Os_CheckObjectAccessService(ApplicationType ApplID, ObjectTypeType
   *ObjectType, ObjectTypeIndex ObjectID) */
#endif /* End of if (OS_SCALABILITY_CLASS >= OS_SC3) */

/***************************************************************************//**
 * Function Name        : Os_KernCheckObjectOwnership
 *
 * Service ID           : NA
 *
 * Description          : This Service returns owner of the Object
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
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
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GaaStaticTask, Os_GaaStaticAlarm
 *                        Os_GaaResourceTable, Os_GaaStaticCounter
 *                        Os_GaaStaticSchedTable
 *
 *                        Function(s) invoked    :
 *                        Os_CheckObjIDError()
 ******************************************************************************/
/* @Trace: SRS_Os_80005 SRS_Os_80015 SRS_Os_80016 */
#if (OS_APPLICATION == STD_ON)
FUNC(ApplicationType, OS_CODE) Os_KernCheckObjectOwnership(
                            ObjectTypeType ObjectType, ObjectTypeIndex ObjectID)
{
  StatusType LenStatusReturn;
  ApplicationType LddApplicationID;
  #if (OS_SCHEDTABLE == STD_ON)
  AlarmType LddAlarmIndex;
  #endif
  /* @Trace: SafeOs_SUD_API_18201 */
  LenStatusReturn = E_OK;

  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Set Return status to Invalid OS-Application */
  LddApplicationID = INVALID_OSAPPLICATION;
  /* Check whether ObjectID is correct */
  if(ObjectType == OBJECT_TASK)
  {
    /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "Number of core and task can be configured" */
    /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "Number of core can be configured" */
    if(((ObjectID) >= (Os_Task_Count + Os_Core_Count))
                                                 || (ObjectID < Os_Core_Count))
    /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "Number of core can be configured" */
    /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "Number of core and task can be configured" */
    {
      /* @Trace: SafeOs_SUD_API_18202 */
      LenStatusReturn = E_OS_ID;
    }
  }
  else
  {
    /* @Trace: SafeOs_SUD_API_18203 */
    LenStatusReturn = Os_CheckObjIDError(ObjectType, ObjectID);
  }
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(CHECKOBJECTOWNERSHIP, LenStatusReturn);
  /* Check whether ObjectType is correct */
  OS_CHECK_OBJECT_TYPE_ERROR(ObjectType, LenStatusReturn);
  /* Check if LenStatusReturn is E_OK or not */
  if(LenStatusReturn == E_OK)
  {
    switch (ObjectType)
    {
      case OBJECT_TASK:
      case OBJECT_ISR:
        /* @Trace: SafeOs_SUD_API_18204 */
        /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "ObjectID have been checked before using" */
        /* Get the application Id from the structure */
        LddApplicationID = Os_GaaStaticTask[ObjectID].ddAppId;
        break;

        #if (OS_ALARM == STD_ON)
      case OBJECT_ALARM:
        /* @Trace: SafeOs_SUD_API_18205 */
        /* Get the application Id from the structure */
        LddApplicationID = Os_GaaStaticAlarm[ObjectID].ddAppId;
        break;

        #endif /* End of if (OS_ALARM == STD_ON) */
        #if (OS_RESOURCE == STD_ON)
      case OBJECT_RESOURCE:
        /* @Trace: SafeOs_SUD_API_18206 */
        /* Get the application Id from the structure */
        LddApplicationID = Os_GaaResourceTable[ObjectID].ddAppId;
        break;

        #endif /* End of if (OS_RESOURCE == STD_ON) */
        #if (OS_COUNTER == STD_ON)
      case OBJECT_COUNTER:
        /* @Trace: SafeOs_SUD_API_18207 */
        /* Get the application Id from the structure */
        LddApplicationID = Os_GaaStaticCounter[ObjectID].ddAppId;
        break;

        #endif /* End of if (OS_COUNTER == STD_ON) */
        #if (OS_SCHEDTABLE == STD_ON)
      case OBJECT_SCHEDULETABLE:
        /* @Trace: SafeOs_SUD_API_18208 */
        /* Get the Alarm index from the structure */
        LddAlarmIndex = Os_GaaStaticSchedTable[ObjectID].ddAlarmIndex;
        /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "ObjectID have been checked before using" */
        /* Get the application Id from the structure */
        LddApplicationID = Os_GaaStaticAlarm[LddAlarmIndex].ddAppId;
        break;

        #endif /* End of if (OS_SCHEDTABLE == STD_ON) */
      /* polyspace +1 RTE:UNR [No action planned:Low] "Default switch-case with no Os objects configured" */
      default:
        /* Do Nothing */
        break;
    } /* End of switch (ObjectType) */
  }
  return (LddApplicationID);
} /* End of CheckObjectOwnership(ObjectTypeType ObjectType, ObjectTypeIndex
   *ObjectID) */
#endif /* End of #if (OS_APPLICATION == STD_ON) */

/***************************************************************************//**
** Function Name        : Os_DoTerminateApplication
**
** Service ID           : OSServiceId_TerminateApplication
**
** Description          : This Service Terminates the specified application
**
** Sync/Async           : NA
**
** Re-entrancy          : Re-entrant
**
** @param[in]             Application   The identifier of the OS-Application to
**                                      be terminated. If the caller belongs to
**                                      <Application> the call results in a self
**                                      termination.
**                                      (range : 0 ~ OS_APPLICATION_COUNT - 1)
** @param[in]             RestartOption Either RESTART for doing a restart of
**                                      the OS-Application or NO_RESTART if
**                                      OS-Application shall not be restarted.
**                                      (range : RESTART, NO_RESTART)
**
** @return              : StatusType
**                        - E_OK : No error
**                        - OS_E_OK_AND_LOAD : Rescheduling is needed
**                        - OS_E_OK_AND_SCHEDULE : RestartTask activated and
**                                                 scheduling is needed
**                        - E_OS_LIMIT : RestartTask already activated
**
** @pre                 : StartOS() function should be called,
**                        <Application> should be checked
**
** @remarks             : Global Variable(s)     :
**                        Os_GpStaticTask, Os_GaaApplication, Os_GpLinkTask
**                        Os_GaaStaticTask, Os_GaaStaticApplication
**                        Os_GaaTask, Os_GddAppId, Os_GusCallevelCheck,
**                        Os_GulOsAppSP, Os_GulOsAppSPBtm
**
**                        Function(s) invoked    :
**                        Os_ReleaseResourceService(),
**                        ReleaseSpinlock(),
**                        Os_KillTask(),
**                        Os_TaskKillHook(),
**                        Os_KillIsr(),
**                        Os_IsrKillHook(),
**                        Os_DisableAppInterrupts(),
**                        Os_RemoveAlarm(),
**                        Os_DoStopScheduleTable(),
**                        ShutdownOS()
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11014 */
#if (OS_SCALABILITY_CLASS >= OS_SC3)
/* polyspace +2 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
/* polyspace +1 MISRA-C3:17.2 [Justified:Low] "Os_ActivateTaskService-> Os_StartTimeFrame #if (OS_TASK_TP_TF == STD_ON) -> Os_ProtectionHookService -> Os_DoTerminateApplication -> #if (OS_RESTART_TASK == STD_ON) Os_ActivateTaskService" */
FUNC(StatusType, OS_CODE) Os_DoTerminateApplication(
                         ApplicationType Application, RestartType RestartOption)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  #if ((OS_ALARM == STD_ON)||(OS_SCHEDTABLE == STD_ON)||\
                                                    (OS_RESTART_TASK == STD_ON))
  P2CONST(Tdd_Os_Application, AUTOMATIC, OS_CONST) LpStaticApplication;
  #endif
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpLinkTask;
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpPreviousLinkTask;
  #if (OS_ALARM == STD_ON)
  P2VAR(Tdd_Os_Alarm, AUTOMATIC, OS_VAR) LpApplAlarm;
  #endif
  #if (OS_SCHEDTABLE == STD_ON)
  P2VAR(Tdd_Os_SchedTable, AUTOMATIC, OS_VAR) LpSchedTable;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  #if (OS_SCHEDTABLE == STD_ON)
  ScheduleTableType LddSchedTbleCount;
  #endif
  #if (OS_ALARM == STD_ON)
  AlarmType LddAlarmCount;
  #endif
  StatusType LenStatusReturn;
  #if (OS_TASK == STD_ON)
  /* @Trace: SafeOs_SUD_API_18301 */
  TaskType LddTaskCount;
  LddTaskCount = Os_Task_Count;
  #endif
  LenStatusReturn = E_OK;
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* polyspace +2 MISRA-C3:D4.14 [Justified:Low] "Application have been checked by macro OS_CHECK_APPL_ID_ERROR before using" */
  /* Update the status as TERMINATING(internal status) */
  Os_GaaApplication[Application].ddState = APPLICATION_TERMINATING;

  #if ((OS_ALARM == STD_ON)||(OS_SCHEDTABLE == STD_ON)||\
                                                    (OS_RESTART_TASK == STD_ON))
  /* @Trace: SafeOs_SUD_API_18302 */
  LpStaticApplication = &Os_GaaStaticApplication[Application];
  #endif
  /* @Trace: SafeOs_SUD_API_18303 */
  LpLinkTask = Os_GpLinkTask[OS_CORE_ID];

  LpPreviousLinkTask = NULL_PTR;

  do
  {
    /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
    LpStaticTask = &Os_GaaStaticTask[LpLinkTask->ddTaskID];
    /* Check if the Task's APP ID matches the requested App ID */
    if (Application == LpStaticTask->ddAppId)
    {
      #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
      if (LpStaticTask->usType != OS_ISR2)
      #endif
      {
        #if (OS_RESOURCE == STD_ON)
        /* @Trace: SafeOs_SUD_API_18304 */
        /* Release all the acquired resources */
        Os_ReleaseResourceService(LpStaticTask);
        #endif

        #if (OS_SPINLOCK == STD_ON)
        /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
        if ((LpStaticTask->pTask->ddSpinlock) != OS_ZERO)
        {
          do
          {
            /* @Trace: SafeOs_SUD_API_18305 */
            /* polyspace:begin<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
            (void)ReleaseSpinlock(Os_GaaTask
                [Os_GpLinkTask[OS_CORE_ID]->ddTaskID].ddSpinlock);
            /* polyspace:end<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
          } while (Os_GaaTask
              [Os_GpLinkTask[OS_CORE_ID]->ddTaskID].ddSpinlock != OS_ZERO);
        }
        #endif /* End of if (OS_SPINLOCK == STD_ON) */

        /* Kill the Task */
        /* @Trace: SafeOs_SUD_API_18306 */
        Os_KillTask(LpStaticTask);
        #if (OS_PROFILING_HOOK == STD_ON)
        /* @Trace: SafeOs_SUD_API_18307 */
        /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
        Os_TaskKillHook(OS_CORE_ID, LpStaticTask->ddTaskId);
        /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
        #endif
      }
      #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
      else
      {
        /* @Trace: SafeOs_SUD_API_18308 */
        /* Kill the ISR */
        Os_KillIsr(LpStaticTask);
        #if (OS_PROFILING_HOOK == STD_ON)
        /* @Trace: SafeOs_SUD_API_18309 */
        /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
        Os_IsrKillHook(OS_CORE_ID, LpStaticTask->ddTaskId);
        /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
        #endif
      }
      #endif

      /* update the link list */
      if (LpPreviousLinkTask != NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_18310 */
        /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
        LpPreviousLinkTask->pLinkList = LpLinkTask->pLinkList;
      }
    } /* End of if (Application == LpStaticTask->ddAppId) */
    else
    {
      if ((Os_GpLinkTask[OS_CORE_ID] != LpLinkTask) && (LpPreviousLinkTask == NULL_PTR))
      {
        /* @Trace: SafeOs_SUD_API_18311 */
        Os_GpLinkTask[OS_CORE_ID] = LpLinkTask;
        /* Rescheduling is needed */
        LenStatusReturn = OS_E_OK_AND_LOAD;
      }
      LpPreviousLinkTask = LpLinkTask;
    }
    /* @Trace: SafeOs_SUD_API_18312 */
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
    LpLinkTask = LpLinkTask->pLinkList;
  } while (LpLinkTask != NULL_PTR);

  #if (OS_TASK_COUNT > OS_PRE_ZERO)
  /* Check if a task is NOT in SUSPENDED state */
  while (LddTaskCount != OS_ZERO)
  {
    /* @Trace: SafeOs_SUD_API_18313 */
    LpStaticTask = &Os_GaaStaticTask[LddTaskCount];
    if (LpStaticTask->ddAppId == Application)
    {
      #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
      if (LpStaticTask->usType != OS_ISR2)
      #endif
      {
        /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
        if (LpStaticTask->pTask->ddState == WAITING)
        {
          /* Kill the Task */
          /* @Trace: SafeOs_SUD_API_18314 */
          Os_KillTask(LpStaticTask);
          #if (OS_PROFILING_HOOK == STD_ON)
          /* @Trace: SafeOs_SUD_API_18315 */
          /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */  
          Os_TaskKillHook(OS_CORE_ID, LpStaticTask->ddTaskId);
          /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */

          #endif
        }
      }
    }
    /* @Trace: SafeOs_SUD_API_18316 */
    LddTaskCount--;
  }
  #endif

  #if((OS_CAT2_ISR_COUNT != OS_ZERO) && (OS_APPLICATION == STD_ON))
  /* @Trace: SafeOs_SUD_API_18317 */
  /* Disable ISR belonging to this application */
  Os_DisableAppInterrupts(Application);
  #endif
  #if (OS_ALARM == STD_ON)
  /* @Trace: SafeOs_SUD_API_18318 */
  /* Count Alarms belonging to same application */
  LddAlarmCount = LpStaticApplication->ddNoOfAlarm;
  /* Point to the corresponding alarm of the application */
  LpApplAlarm = LpStaticApplication->pApplicationAlarm;
  /* Run through the while loop for all the alarms */
  while (LddAlarmCount != OS_ZERO)
  {
    /* Check if Alarm is in running state */
    /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
    if (LpApplAlarm->ucAlarmState != OS_ALARM_SLEEP)
    {
      /* @Trace: SafeOs_SUD_API_18319 */
      /* Remove alarm from the queue */
      Os_RemoveAlarm(LpApplAlarm);
      /* Change State alarm to SLEEP */
      LpApplAlarm->ucAlarmState = OS_ALARM_SLEEP;
    } /* End of if (LpApplAlarm->ucAlarmState != OS_ALARM_SLEEP) */
    /* Point to next Alarm */
    /* @Trace: SafeOs_SUD_API_18320 */
    /* polyspace +1 MISRA-C3:18.4 [Justified:Low] "Increment operator on pointer used to achieve better throughput" */
    LpApplAlarm++;

    /* Decrement alarm count */
    LddAlarmCount--;
  }
  #endif /* End of if (OS_ALARM == STD_ON) */
  #if (OS_SCHEDTABLE == STD_ON)
  /* @Trace: SafeOs_SUD_API_18321 */
  /* Count Schedule Tables belonging to same application */
  LddSchedTbleCount = LpStaticApplication->ddNoOfStaticSchedTable;
  /* Get the pointer to corresponding schedule table */
  LpSchedTable = LpStaticApplication->pApplicationScheTbl;
  /* Run through the while loop for all the Schedule Table */
  while (LddSchedTbleCount != OS_ZERO)
  {
    /* @Trace: SafeOs_SUD_API_18322 */
    /* Invoke Os_DoStopScheduleTable */
    (void)Os_DoStopScheduleTable(LpSchedTable->ddSchedTableId, OS_FALSE);
    /* Point to next Schedule Table */
    LpSchedTable++;
    /* Decrement alarm count */
    LddSchedTbleCount--;
  }
  #endif /* End of if (OS_SCHEDTABLE == STD_ON) */
  /* @Trace: SafeOs_SUD_API_18323 */
  /* Initialize OS Applicaiton Stack */
  Os_GulOsAppSP[Application] = Os_GulOsAppSPBtm[Application];
  /* polyspace +2 CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
  /* polyspace +1 MISRA-C3:11.4 [Justified:Medium] "Conversion is needed for implementation" */
  *((Os_StackType*)(Os_GulOsAppSPTop[Application])) = OS_STACK_PATTERN;

  #if (OS_RESTART_TASK == STD_ON)

  /* Check if Restart Option is Restart */
  if (RestartOption == RESTART)
  {
    if (LpStaticApplication->pRestartTask != NULL_PTR)
    {
      /* @Trace: SafeOs_SUD_API_18324 */
      /* Invoke Os_ActivatetaskService() to put the task in READY task list */
      LenStatusReturn |= Os_ActivateTaskService
                                            (LpStaticApplication->pRestartTask);
      /* Change state of Application to Restarting */
      Os_GaaApplication[Application].ddState = APPLICATION_RESTARTING;
    } /* End of if (LpStaticApplication->pRestartTask != NULL_PTR) */
    else
    {
      /* @Trace: SafeOs_SUD_API_18325 */
      /* Invoke Shutdown as RestartTask is not configured */
      ShutdownOS(E_OS_SYS_PANIC); /* FIXME: OS244, OS557 review dglee */
    }
  } /* End of if (RestartOption == RESTART) */
  #else /* End of if (OS_RESTART_TASK == STD_ON) */
  /* @Trace: SafeOs_SUD_API_18326 */
  /* polyspace +1 MISRA-C3:2.2 [Justified:Low] "This is used to explicit the non-using variable" */
  OS_UNUSED(RestartOption);

  #endif /* End of if (OS_RESTART_TASK == STD_ON) */
  #if(OS_ERROR_HOOK == STD_ON)
  /*
   * In case of Self termination from an Error hook, ErrorHook variable should
   * be reset in order to avoid call level errors in further API call
   */
  if ((Os_GddAppId[OS_CORE_ID] == Application) &&
      ((Os_GusCallevelCheck[OS_CORE_ID] & OS_CONTEXT_ERRORHOOK)
                                                            != (uint16)OS_ZERO))
  {
    /* @Trace: SafeOs_SUD_API_18327 */
    Os_GusCallevelCheck[OS_CORE_ID] &= (uint16)((uint16)0xFFFF & ~(uint16)OS_CONTEXT_ERRORHOOK);
  }
  #endif

  /* polyspace<RTE: UNR : Not a defect : No Action Planned > This is for exceptional case. But this code has already been verified and no impact of this rule violation */
  if (Os_GaaApplication[Application].ddState != APPLICATION_RESTARTING)
  {  /* Update the status as TERMINATED */
  /* @Trace: SafeOs_SUD_API_18328 */
    Os_GaaApplication[Application].ddState = APPLICATION_TERMINATED;
  }

  return (LenStatusReturn);
} /* End of Os_TerminateApplService(ApplicationType Application, RestartType
   *RestartOption) */

#endif /* End of if (OS_SCALABILITY_CLASS >= OS_SC3) */

/***************************************************************************//**
 * Function Name        : Os_KernTerminateApplication
 *
 * Service ID           : NA
 *
 * Description          : This Service Terminates the specified application
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrant
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
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GpStaticTask
 *
 *                        Function(s) invoked    :
 *                        Os_DoTerminateApplication(),
 *                        Os_SendTerminateApplication(),
 *                        Os_TaskPreemptionHook(),
 *                        Os_ScheduleService()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11006 SRS_Os_80021 SRS_AUTRON_00017 */
#if (OS_SCALABILITY_CLASS >= OS_SC3)
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "The display of specific values of the number of paths is justified" */
FUNC(StatusType, OS_CODE) Os_KernTerminateApplication(
                         ApplicationType Application, RestartType RestartOption)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* @Trace: SafeOs_SUD_API_18401 */
  /* Set Return status to E_OK */
  LenStatusReturn = E_OK;
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Check whether interrupts are not disabled by user */

  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(TERMINATEAPPLICATION, LenStatusReturn);
  /* Check whether the call is for self termination from error hook*/
  OS_SELF_TERMINATION_CHECK(LenStatusReturn, Application);
  /* Check whether Application is greater than number of Application count */
  OS_CHECK_APPL_ID_ERROR(Application, LenStatusReturn);
  /* Check if Restart option is valid or not */
  OS_CHECK_RESTART_VALUE_ERROR(LenStatusReturn, RestartOption);
  /* Check if caller belongs to non trusted application */
  OS_CHECK_CALLER_APPLICATION_ERROR(Application, LenStatusReturn);
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "Application index is checked by macro OS_CHECK_APPL_ID_ERROR before using." */

  /* Check if appllication is in TERMINATED state */
  OS_CHECK_APPL_TERMINATED_STATE_ERROR(Application, LenStatusReturn);
  /* Check if Caller has access to terminate the application */
  OS_CHECK_APPL_CALLER_ACCESS_ERROR(Application, LenStatusReturn);
  /* Check if appllication is in Restarted state */
  OS_CHECK_APPL_RESTART_STATE_ERROR(Application, LenStatusReturn, RestartOption);


  if ((LenStatusReturn == E_OK) &&
      ((Os_GaaApplication[Application].ddState) != APPLICATION_TERMINATING))
  {
    #if (OS_MULTICORE == STD_ON)
    /* Check if new task belongs to same core */
    if (Os_GaaStaticApplication[Application].ddCoreID != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_18402 */
      /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "Application index is checked by macro OS_CHECK_APPL_ID_ERROR before using." */
      /* Call Os_SendActivateTask to schedule task on respective core */
      LenStatusReturn = Os_SendTerminateApplication(Application, RestartOption);
    } /* End of if (LpStaticTask->ddCoreId != OS_CORE_ID) */
    else
    #endif /* End of if (OS_MULTICORE == STD_ON) */
    {
      /* @Trace: SafeOs_SUD_API_18403 */
      /* Invoke Os_TerminateApplService function */
      LenStatusReturn = Os_DoTerminateApplication(Application, RestartOption);
    }

    if (LenStatusReturn >= OS_E_OK_AND_LOAD)
    {
      /* @Trace: SafeOs_SUD_API_18404 */
      /* Load context */
      OS_RELOADCONTEXT();
    }
    #if (OS_RESTART_TASK == STD_ON)
    else if (LenStatusReturn == OS_E_OK_AND_SCHEDULE)
    {
      /* @Trace: SafeOs_SUD_API_18405 */
      /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually*/
      Os_GpStaticTask[OS_CORE_ID]->pTask->ddState = READY;
      #if (OS_PROFILING_HOOK == STD_ON)
      /* @Trace: SafeOs_SUD_API_18406 */
      /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
      Os_TaskPreemptionHook(OS_CORE_ID, Os_GpStaticTask[OS_CORE_ID]->ddTaskId);
      /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
      #endif
      /* NOTE: Os_RunTask() separately executed later. */
      Os_ScheduleService();
      /* Save and load context */
      OS_SAVECONTEXT();
    }
    #endif
    else
    {
      /* @Trace: SafeOs_SUD_API_18407 */
      /* do nothing */
    }
    /* Mask the Status Return value */
    LenStatusReturn &= OS_STATUS_MASK;

  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  if (LenStatusReturn != E_OK)
  {
    /* @Trace: SafeOs_SUD_API_18408 */
    /* Store service ID of TerminateApplication */
    OS_STORE_SERVICE(OSServiceId_TerminateApplication);
    /* Store the parameter 1 - Application */
    OS_STORE_PARAM1_APPLICATION(Application);
    /* Store the parameter 2 - RestartOption */
    OS_STORE_PARAM2_RESTARTOPTION(RestartOption);
    /* Call Error Hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif /* End of if (OS_STATUS == EXTENDED) */
  /* Return the value */

  return (LenStatusReturn);
} /* End of TerminateApplication(ApplicationType Application, RestartType
   *RestartOption) */
#endif /* End of if (OS_SCALABILITY_CLASS >= OS_SC3) */

/***************************************************************************//**
 * Function Name        : Os_KernCallTrustedFunction
 *
 * Service ID           : NA
 *
 * Description          : This service shall switch the processor into
 *                        privileged mode AND shall call the function
 *                        <FunctionIndex> out of a list of implementation
 *                        specific trusted functions
 *
 * Sync/Async           : Depends on called function. If called function is
 *                        synchronous then service is synchronous.
 *
 * Re-entrancy          : Non Re-entrant
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
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s)     :
 *                        Os_GddAppId, Os_GaaTrustedFunction
 *
 *                        Function(s) invoked    :
 *                        Os_DisableAppInterrupts(),
 *                        Os_ForceTimingCore(),
 *                        Os_EnableAppInterrupts()
 ******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11011 SRS_Os_80005 SRS_Os_80015 SRS_Os_80016 SRS_Os_11000 SRS_Os_11001 SRS_Os_11005 SRS_Os_11006 SRS_Os_11010 SRS_Os_11013 SRS_Os_11014 */
/* polyspace +3 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace" */
#if (OS_TRUSTED_FUNC_COUNT != OS_PRE_ZERO)
FUNC(StatusType, OS_CODE) Os_KernCallTrustedFunction( TrustedFunctionIndexType
                  FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
{
  StatusType LenStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  #if (OS_APPLICATION == STD_ON)
  ApplicationType PrevAppId;
  #endif

  /* @Trace: SafeOs_SUD_API_15401 */
  LenStatusReturn = E_OK;
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Check whether interrupts are not disabled by user */
  OS_CHECK_INTERRUPT_LOCK(&LenStatusReturn);
  /* Check for call level */
  OS_CHECK_E_OS_CALLEVEL(CALLTRUSTEDFUNCTION, LenStatusReturn);
  /* Check the index of trusted function */
  OS_CHECK_TRUSTED_FUNCTION_INDEX(FunctionIndex, LenStatusReturn);
  #if (OS_MULTICORE == STD_ON)
  /* @Trace: SafeOs_SUD_API_15402 */
  /* Check trusted function is part of an OS-Application on another core */
  OS_CHECK_TRUSTED_FUNCTION_CORE(FunctionIndex, LenStatusReturn);
  #endif

  if (LenStatusReturn == E_OK)
  {
    if(Os_GucTrustedFuncCount[OS_CORE_ID] == OS_ZERO)
    {
	  #if((OS_CAT2_ISR_COUNT != OS_ZERO) && (OS_APPLICATION == STD_ON))
      /* @Trace: SafeOs_SUD_API_15403 */
      Os_DisableAppInterrupts(Os_GddAppId[OS_CORE_ID]);
	  #endif
      /* @Trace: SafeOs_SUD_API_15404 */
      Os_GaaApplication[Os_GddAppId[OS_CORE_ID]].ddState |= \
                                                APPLICATION_HAS_CALLTRUSTEDFUNC;
    }

    Os_GucTrustedFuncCount[OS_CORE_ID]++;
    #if (OS_APPLICATION == STD_ON)
    /* @Trace: SafeOs_SUD_API_15405 */
    /* Update current application identifier in case of trusted function */
    Os_GddCurAppId[OS_CORE_ID] =
                              Os_GaaTrustedFunction[FunctionIndex].ddOwnerAppId;
    /* Store the application id to restore */
    PrevAppId = Os_GddCurAppId[OS_CORE_ID];
    #endif
    /* @Trace: SafeOs_SUD_API_15406 */
    /* Invoking the trusted function based on the functionindex  */
    Os_GaaTrustedFunction[FunctionIndex].pTrustedFunc(FunctionParams);
    #if (OS_APPLICATION == STD_ON)
    /* @Trace: SafeOs_SUD_API_15407 */
    /* Restore the previous application id after exiting the call trusted function  */
    Os_GddCurAppId[OS_CORE_ID] = PrevAppId;
    #endif
    /* @Trace: SafeOs_SUD_API_15408 */
    Os_GucTrustedFuncCount[OS_CORE_ID]--;
    #if (OS_TIMING_PROTECTION == STD_ON)
    if(((Os_GucTrustedFuncCount[OS_CORE_ID] == OS_ZERO) &&
                         (Os_GblTimeViolationDelayed[OS_CORE_ID] == OS_TRUE)) ||
        (((Os_GaaStaticApplication[Os_GddCurAppId[OS_CORE_ID]].blHasDelay)
            == OS_FALSE) && (Os_GblTimeViolationDelayed[OS_CORE_ID] == OS_TRUE)))
    {
      /* @Trace: SafeOs_SUD_API_15409 */
      Os_ForceTimingCore(OS_CORE_ID);
    }
    #endif

    if(Os_GucTrustedFuncCount[OS_CORE_ID] == OS_ZERO)
    {
      #if((OS_CAT2_ISR_COUNT != OS_ZERO) && (OS_APPLICATION == STD_ON))
      /* @Trace: SafeOs_SUD_API_15410 */
      Os_EnableAppInterrupts();
      #endif
      /* @Trace: SafeOs_SUD_API_15411 */
      Os_GaaApplication[Os_GddAppId[OS_CORE_ID]].ddState &= \
                                               ~APPLICATION_HAS_CALLTRUSTEDFUNC;
    }
  } /* End of if (LenStatusReturn == E_OK) */
  #if (OS_STATUS == EXTENDED)
  else
  {
    /* @Trace: SafeOs_SUD_API_15412 */
    /* Store the service ID of CallTrustedFunction */
    OS_STORE_SERVICE(OSServiceId_CallTrustedFunction);

    /* Store the parameter 1 - FunctionIndex */
    OS_STORE_PARAM1_FUNCTIONINDEX(FunctionIndex);

    /* Call Error Hook */
    OS_PROCESS_ERROR(LenStatusReturn);
  } /* End of else */
  #endif
  return (LenStatusReturn);
} /* End of CallTrustedFunction(TrustedFunctionIndexType FunctionIndex,
   *TrustedFunctionParameterRefType FunctionParams) */
#endif /* End of if (OS_SCALABILITY_CLASS >= OS_SC3) */

/***************************************************************************//**
 * Function Name        : Os_KillTaskOrISR
 *
 * Service ID           : NA
 *
 * Description          : This service is used to terminate Task/ISR forcibly
 *
 * Sync/Async           : NA
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : StatusType
 *                        - E_OK : No error
 *                        - OS_E_OK_AND_LOAD : Rescheduling is needed
 *
 * @pre                 : StartOS() function should be called
 *
 * @remarks             : Global Variable(s) :
 *                        Os_GpLinkTask, Os_GaaTask, Os_GaaStaticTask
 *                        Os_GddFaultyTask
 *
 *                        Function(s) invoked    :
 *                        Os_KillTask(), Os_KillIsr(),
 *                        Os_ReleaseResourceService(), ReleaseSpinlock()
 ******************************************************************************/
#if (OS_PROTECTION_HOOK == STD_ON)
/* polyspace +1 MISRA-C3:17.2 [Justified:Low] "ReleaseSpinlock -> OS_SYSCALL_RELEASESPINLOCK -> Os_SystemCallReleaseSpinlock ->Os_KernReleaseSpinlock ->Os_SpinlockUnLockMethod -> Os_SpinlockUnLockResource -> Os_ScheduleService -> Os_CheckStack -> Os_ProtectionHookService -> Os_KillTaskOrISR" */
FUNC(StatusType, OS_CODE) Os_KillTaskOrISR(void)
{
  P2CONST(Tdd_Os_StaticTask, AUTOMATIC, OS_CONST) LpStaticTask;
  #if (OS_TIMING_PROTECTION == STD_ON)
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpLinkTask;
  P2VAR(Tdd_Os_LinkTask, AUTOMATIC, OS_VAR) LpPreviousLinkTask;
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  StatusType LenStatusReturn;
  TaskType LddFaultyTaskId;
  /* @Trace: SafeOs_SUD_API_17501 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  #if (OS_TIMING_PROTECTION == STD_ON)
  /* polyspace +3 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +2 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +1 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  if (Os_GddFaultyTask[OS_CORE_ID] != INVALID_TASK)
  {
    /* @Trace: SafeOs_SUD_API_17502 */
    /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
    LddFaultyTaskId = Os_GddFaultyTask[OS_CORE_ID];
  }
  else
  #endif
  {
    /* polyspace<RTE: NIV : Not a defect : No Action Planned > variable is initialized and code is verified manually */
    /* @Trace: SafeOs_SUD_API_17503 */
    LddFaultyTaskId = Os_GpLinkTask[OS_CORE_ID]->ddTaskID;
  }

  #if (OS_TIMING_PROTECTION == STD_ON)
  LenStatusReturn = E_OK;
  #endif
  LpStaticTask = &Os_GaaStaticTask[LddFaultyTaskId];
  #if (OS_RESOURCE == STD_ON)
  /* @Trace: SafeOs_SUD_API_17504 */
  Os_ReleaseResourceService(LpStaticTask);
  #endif
  #if (OS_SPINLOCK == STD_ON)
  if ((Os_GaaTask[LddFaultyTaskId].ddSpinlock) != OS_ZERO)
  {
    /* polyspace-begin RTE:NTL [Not a defect:Low] "Waiting until spinlock is released is intended instruction" */
    /* @Trace: SafeOs_SUD_API_17505 */
    do
    {
      (void)ReleaseSpinlock(Os_GaaTask[LddFaultyTaskId].ddSpinlock);
    } while (
      Os_GaaTask[LddFaultyTaskId].ddSpinlock != OS_ZERO);
    /* polyspace-end RTE:NTL [Not a defect:Low] "Waiting until spinlock is released is intended instruction" */
  } /* End of if ((Os_GaaTask[LddFaultyTaskId].ddSpinlock)
     *!= OS_ZERO) */
  #endif /* End of if (OS_SPINLOCK == STD_ON) */

  /* If object to be killed is a Task */
  #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
  if (LpStaticTask->usType != OS_ISR2)
  #endif
  {
    /* @Trace: SafeOs_SUD_API_17506 */
    /* Kill the Task */
    Os_KillTask(LpStaticTask);

    /* Invoke ProfilingHook if it is enable */
    #if (OS_PROFILING_HOOK == STD_ON)
    /* @Trace: SafeOs_SUD_API_17507 */
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */    
    Os_TaskKillHook(OS_CORE_ID, LpStaticTask->ddTaskId);
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    #endif

  } /* End of if (LpStaticTask->ucType != OS_ISR2) */
  #if (OS_CAT2_ISR_COUNT != OS_PRE_ZERO)
  else
  {
    /* @Trace: SafeOs_SUD_API_17508 */
    Os_KillIsr(LpStaticTask);

    /* Invoke ProfilingHook if it is enable */
    #if (OS_PROFILING_HOOK == STD_ON)
    /* @Trace: SafeOs_SUD_API_17509 */
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    Os_IsrKillHook(OS_CORE_ID, LpStaticTask->ddTaskId);
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "The content of external API which will be under user's definition" */
    #endif
  } /* End of else */
  #endif

  #if (OS_TIMING_PROTECTION == STD_ON)
  /* @Trace: SafeOs_SUD_API_17510 */
  LpLinkTask = Os_GpLinkTask[OS_CORE_ID];
  LpPreviousLinkTask = NULL_PTR;

  /* Find killed Task/Isr and update LinkList */
  while (LpLinkTask != NULL_PTR)
  {
    /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
    if (LpLinkTask->ddTaskID == LddFaultyTaskId)
    {
      if (LpPreviousLinkTask == NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_17511 */
        /* Update Os_GpLinkTask with next task */
        /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
        Os_GpLinkTask[OS_CORE_ID] = LpLinkTask->pLinkList;
        LenStatusReturn = OS_E_OK_AND_LOAD;
      }
      else
      {
        /* @Trace: SafeOs_SUD_API_17512 */
        /* Remove killed task in LinkList */
        /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually*/
        LpPreviousLinkTask->pLinkList = LpLinkTask->pLinkList;
      }
      break;
    }
    else
    {
      /* @Trace: SafeOs_SUD_API_17513 */
      LpPreviousLinkTask = LpLinkTask;
    }
    /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
    LpLinkTask = LpLinkTask->pLinkList;
  }
  #else
  /* Update Os_GpLinkTask with next task */
  /* polyspace<RTE: NIP : Not a defect : No Action Planned >  ptr points to a valid value and code is verified manually */
  Os_GpLinkTask[OS_CORE_ID] = Os_GpLinkTask[OS_CORE_ID]->pLinkList;
  LenStatusReturn = OS_E_OK_AND_LOAD;
  #endif /* End of if (OS_TIMING_PROTECTION == STD_ON) */

  return (LenStatusReturn);
} /* End of Os_KillTaskOrISR(void) */
#endif /* End of if (OS_PROTECTION_HOOK == STD_ON) */
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define OS_API_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#if (OS_MEMORY_PROTECTION == STD_ON)
/***************************************************************************//**
 * Function Name        : Os_CallCheckTaskMemoryAccess
 *
 * Service ID           : OSServiceId_CheckTaskMemoryAccess
 *
 * Description          : This service checks if a memory region is write/
 *                        read/execute accessible and also returns information
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
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_11005 SRS_Os_11006 SRS_Os_11007 SRS_Os_11000 */
/* polyspace +2 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace*/
FUNC(AccessType, OS_CODE) Os_CallCheckTaskMemoryAccess
    (TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size)
{
  AccessType LddAccessReturn = NO_ACCESS;
  /* @Trace : SafeOs_SUD_API_57401 */
  LddAccessReturn = OS_SYSCALL_CHECKTASKMEMORYACCESS(TaskID, Address, Size);

  return LddAccessReturn;
}
#endif
#define OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
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

