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
**  SRC-MODULE: Os_Multicore.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Multicore functionality.                         **
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
** 1.5.1     06-Oct-2023   JC.Kim           Jira CP44-2438                    **
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.2     07-Oct-2020   DanhDC1          R44-Redmine #15959                **
**                                          Remove un-used function           **
** 1.0.3     14-Sep-2020   TamNN1           R44-Redmine #15236 Fixed warning  **
**                                          when Compile with SIT and SQT     **
** 1.0.2     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C 17.2                **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os Ram header file */
#include "Os_Error.h"             /* Os Error header file */
#if (OS_MULTICORE == STD_ON)
#include "Os_MulticoreMessage.h"
#endif
/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE: ABS_ADDR : Not a defect : Justify with annotations > Absolute address is needed to access MCU register */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

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
** Function Name        : Os_SetSyncFirst                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used for first synchronization     **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
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
**                        Os_GucSync1, Os_Core_Count                          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_GetSpinlock(),                                   **
**                        Os_ReleaseSpinlock()                                **
*******************************************************************************/
/* @Trace: SRS_BSW_00410 */
#if (OS_MULTICORE == STD_ON)
FUNC(void, OS_CODE) Os_SetSyncFirst(void)
{
  /* @Trace: SafeOs_SUD_API_01001 */
  /* Get Spinlock for the core */
  Os_GetSpinlock(OS_SPIN_LOCK_ZERO);
  /* Increment Synchronization variable */
  Os_GucSync1++;
  /* Release Spinlock */
  Os_ReleaseSpinlock(OS_SPIN_LOCK_ZERO);
  /* Wait in a while loop till all the cores are synchronized */
  do {
  /* @Trace: SafeOs_SUD_API_01002 */
  } while (Os_GucSync1 < Os_Core_Count);
} /* End of Os_SetSyncFirst(void) */
#endif /* End of if (OS_MULTICORE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_SetSyncSecond                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used for second synchronization    **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
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
**                        Os_GucSync1, Os_Core_Count                          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_GetSpinlock(),                                   **
**                        Os_ReleaseSpinlock()                                **
*******************************************************************************/
#if (OS_MULTICORE == STD_ON)
FUNC(void, OS_CODE) Os_SetSyncSecond(void)
{
  /* @Trace: SafeOs_SUD_API_01101 */
  /* Get Spinlock for the core */
  Os_GetSpinlock(OS_SPIN_LOCK_ZERO);
  /* Increment Synchronization variable */
  Os_GucSync1++;
  /* Release Spinlock */
  Os_ReleaseSpinlock(OS_SPIN_LOCK_ZERO);
  /*
   * Core is once synchronized during Os_SetSyncFirst().
   * This is the second sync
   */
  do {
    /* @Trace: SafeOs_SUD_API_01102 */
  } while (Os_GucSync1 < (OS_SECOND_STEP * Os_Core_Count));
} /* End of Os_SetSyncSecond(void) */
#endif /* End of if (OS_MULTICORE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_WaitSyncShutDown                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used for shutdown synchronization  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
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
**                        Os_GucSync1, Os_Core_Count                          **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if (OS_MULTICORE == STD_ON)
FUNC(void, OS_CODE) Os_WaitSyncShutDown(void)
{

  /*
   * Core is already synchronized twice (Os_SetSyncFirst/Os_SetSyncSecond).
   * This is the Third sync
   */
  do {
    /* @Trace: SafeOs_SUD_API_01201 */
  } while (Os_GucSync1 < (OS_THIRD_STEP * Os_Core_Count));
} /* End of Os_SetSyncShutDown(void) */
#endif /* End of if (OS_MULTICORE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_SetSyncCountShutDown                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used for shutdown synchronization  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
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
**                        Os_GucSync1                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_GetSpinlock(),                                   **
**                        Os_ReleaseSpinlock()                                **
*******************************************************************************/
#if (OS_MULTICORE == STD_ON)
FUNC(void, OS_CODE) Os_SetSyncCountShutDown(void)
{
  /* @Trace: SafeOs_SUD_API_01301 */
  /* Get Spinlock for the core */
  Os_GetSpinlock(OS_SPIN_LOCK_ZERO);

  /* Increment Synchronization variable */
  Os_GucSync1++;

  /* Release Spinlock */
  Os_ReleaseSpinlock(OS_SPIN_LOCK_ZERO);

} /* End of Os_SetSyncShutDown(void) */
#endif /* End of if (OS_MULTICORE == STD_ON) */

/*******************************************************************************
** Function Name        : Os_KernGetCoreID                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Function is used for get core ID               **
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
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
/* @Trace: SRS_Os_80006 SRS_Os_80001 SRS_Os_80026 SRS_Os_80027 */
#if (OS_MULTICORE == STD_ON)
FUNC(CoreIdType, OS_CODE) Os_KernGetCoreID(void)
{
  /* @Trace: SafeOs_SUD_API_01401 */
  /* TODO Error Check for E_OS_DISABLEDINT is not done as per OS093 */
  return (CoreIdType)(Os_MyCore());
}
#endif
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define OS_API_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/***************************************************************************//**
 * Function Name        : Os_CallGetCoreID
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
 * @remarks             : Global Variable(s)     : None
 *                        Function(s) invoked    : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
#if (OS_MULTICORE == STD_ON)
FUNC(CoreIdType, OS_CODE) Os_CallGetCoreID(void)
{  
  CoreIdType LddCoreId = OS_CORE_ID_MASTER;
  /* @Trace : SafeOs_SUD_API_57501 */
  LddCoreId = OS_SYSCALL_GETCOREID();

  return LddCoreId;
}
#endif /* OS_MULTICORE == STD_ON */
#define OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<RTE: ABS_ADDR : Not a defect : Justify with annotations > Absolute address is needed to access MCU register */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
