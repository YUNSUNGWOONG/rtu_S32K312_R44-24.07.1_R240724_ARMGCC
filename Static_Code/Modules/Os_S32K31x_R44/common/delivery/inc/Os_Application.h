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
**  SRC-MODULE: Os_Application.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for Os_Application.c file containing the          **
**              declaration of Application functionality related functions.   **
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
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

#ifndef OS_APPLICATION_H
#define OS_APPLICATION_H

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Kernel.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00330 */
#if (OS_TRUSTED_FUNC_COUNT != OS_PRE_ZERO)
#define APPLICATION_HAS_CALLTRUSTEDFUNC (ApplicationStateType)(0x40)
/* polyspace +1 MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */
#define IS_FREE_FROM_CALLTRUSTEDFUNC(AppID) \
  ((((ApplicationStateType)(Os_GaaApplication[AppID].ddState) & (APPLICATION_HAS_CALLTRUSTEDFUNC))>OS_ZERO)? \
                                                           (OS_FALSE):(OS_TRUE))
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/* @Trace: SRS_BSW_00410 */
#if (OS_APPLICATION == STD_ON)
extern FUNC(void, OS_CODE) Os_DoGetApplicationState(ApplicationType Application,
                                                 ApplicationStateRefType Value);
extern FUNC(StatusType, OS_CODE) Os_DoTerminateApplication(
                        ApplicationType Application, RestartType RestartOption);
#endif
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define OS_API_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#if (OS_MEMORY_PROTECTION == STD_ON)
extern FUNC(AccessType, OS_CODE) Os_CallCheckTaskMemoryAccess
    (TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size);
#endif
#define OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#endif /* OS_APPLICATION_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
