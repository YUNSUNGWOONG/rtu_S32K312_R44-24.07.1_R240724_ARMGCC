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
**  FILE-NAME : EcuM_Boot.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Boot Code                                             **
**                                                                            **
**  PURPOSE   :  Platform Boot Functionality                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By            Description                         **
********************************************************************************
** 1.0.4      08-Aug-2022   Manje Woo     CP44-727                            **
** 1.0.3.1    19-Jul-2022   Manje Woo     CP44-624                            **
** 1.0.2      17-Jan-2022   TriBD         R44_2021 #23275                     **
** 1.0.1      28-Sep-2021   TriBD         R44_2021 #20029                     **
** 1.0.0      08-Sep-2021   Junho Cho     Initial version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Justified:Low] "See MEMMAP003 of AUTOSAR" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "Os.h"
#include "Rte_Main.h"

#include "WdgM.h"

#if (ECUM_LP_CALLOUT_ENABLED == STD_ON)
#include "LowPower_Callout.h"
#endif

int main(void); /* polyspace MISRA2012:D4.6 [Not a defect:Low] "See Exception of Dir 4.6" */

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
#define ECUM_START_SEC_CALLOUT_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name      : main                                                  **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : Booting main function                                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) : None                             **
**                      Function(s) invoked :                                 **
**                      EcuM_PreInit                                          **
**                      EcuM_Init                                             **
**                      EcuM_BootCallout                                      **
*******************************************************************************/
int main(void) /* polyspace MISRA2012:D4.6 [Not a defect:Low] "See Exception of Dir 4.6" */
{
  EcuM_PreInit();

  #if (ECUM_LP_CALLOUT_ENABLED == STD_ON)
  /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "Ecum_Boot_Callout function will be written by customer and then it will not be a deadcode" */
  EcuM_Boot_Callout();
  /* polyspace-end MISRA-C3:2.2 */
  #endif

  /* polyspace<RTE: NTC : Not a defect : No Action Planned > Due to calling StartOs by EcuM_Init */
  EcuM_Init();

  return 0;
}

/*******************************************************************************
* TASK BODIES
*******************************************************************************/
#if (ECUM_MULTI_CORE_SUPPORT == STD_ON)
TASK(OsTask_BSW_Init_Main)
{
	EcuM_StartupTwo();
	(void)TerminateTask();
}

#if (ECUM_NO_OF_CORES > 1)
TASK(OsTask_BSW_Init_Sub1)
{
	EcuM_StartupTwo();
	(void)WaitEvent(OsEvent_RteStart_Sub1);
	(void)ClearEvent(OsEvent_RteStart_Sub1);

	(void)Rte_Start();

	(void)TerminateTask();
}
#endif

#if (ECUM_NO_OF_CORES > 2)
TASK(OsTask_BSW_Init_Sub2)
{
	EcuM_StartupTwo();
	(void)WaitEvent(OsEvent_RteStart_Sub2);
	(void)ClearEvent(OsEvent_RteStart_Sub2);
	(void)Rte_Start();

	(void)TerminateTask();
}
#endif

#if (ECUM_NO_OF_CORES > 3)
TASK(OsTask_BSW_Init_Sub3)
{
	EcuM_StartupTwo();
	(void)WaitEvent(OsEvent_RteStart_Sub3);
	(void)ClearEvent(OsEvent_RteStart_Sub3);

	(void)Rte_Start();

	(void)TerminateTask();
}
#endif

#if (ECUM_NO_OF_CORES > 4)
TASK(OsTask_BSW_Init_Sub4)
{
	EcuM_StartupTwo();
	(void)WaitEvent(OsEvent_RteStart_Sub4);
	(void)ClearEvent(OsEvent_RteStart_Sub4);
	(void)Rte_Start();
	(void)TerminateTask();
}
#endif

#if (ECUM_NO_OF_CORES > 5)
TASK(OsTask_BSW_Init_Sub5)
{
	EcuM_StartupTwo();
	(void)WaitEvent(OsEvent_RteStart_Sub5);
	(void)ClearEvent(OsEvent_RteStart_Sub5);
	(void)Rte_Start();
	(void)TerminateTask();
}
#endif

#else
TASK(OsTask_BSW_Init)
{
	EcuM_StartupTwo();

	(void)TerminateTask();
}
#endif

#define ECUM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
