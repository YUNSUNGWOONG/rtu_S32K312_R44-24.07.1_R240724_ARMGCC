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
**  SRC-MODULE: Os_Panic.c                                                    **
**                                                                            **
**  TARGET    :  All                                                          **
**                                                                            **
**  PRODUCT   : AUTOSAR Os                                                    **
**                                                                            **
**  PURPOSE   : Provision of Panic functionality                              **
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
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
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
#include "Os_Shutdown.h"          /* Os Shutdown header file */
#include "Os_Panic.h"             /* Os Panic header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
VAR(Os_Panic_T, OS_VAR) Os_GenPanicCode;
#define OS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Os_Panic                                            **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Keep Error code and ShutdownCore                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrancy                                     **
**                                                                            **
** Input Parameters     : panicCode                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOs () API should be invoked                    **
**                                                                            **
** Remarks              : Global Variable(s)  : Os_GenPanicCode               **
**                        Function(s) invoked : Os_ShutdownCore               **
*******************************************************************************/
/* FIXME : Os_Panic()-> OS_PROCESS_ERROR(LenStatusReturn) ref Os_Task.c 282Line
 */
FUNC(void, OS_CODE) Os_Panic(Os_Panic_T panicCode)
{
  /* @Trace: SafeOs_SUD_API_50401 */
  Os_GenPanicCode = panicCode;
  Os_ShutdownCore(E_OS_SYS_PANIC, OS_SHUTDOWN_INDIVIDUAL);
}

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
