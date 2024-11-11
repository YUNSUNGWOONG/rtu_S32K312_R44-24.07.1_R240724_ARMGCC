/* polyspace +1 MISRA2012:1.1 [Not a Defect:Low] "Macro definitions are needed for performance and file size" */
/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted with **
**  Hyundai Autoever, and any other use is prohibited.                        **
**  If you use it for other  purposes or change the source code, you may take **
**  legal responsibility.                                                     **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Wdg_76_Acw_Cbk.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTOEVER CUSTOM WDG                                   **
**                                                                            **
**  PURPOSE   : Autoever Custom Watchdog GPT callback function definition     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 0.0.1     11-Oct-2019   DongNx       Initial version                       **
** 1.3.1.1   30-Jun-2022   TriBD        #CP44-324                             **
** 1.3.2.0   09-Aug-2022   TriBD        #CP44-384 (update UNECE standard)     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/* @Trace: SRS_BSW_00346 SRS_Wdg_12165 SRS_Wdg_CUS_00003*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Wdg_76_Acw_Cbk.h"

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
FUNC(void, WDG_76_ACW_CODE) WDG_76_ACW_GPT_CBK(void)
{
  Wdg_76_Acw_Gpt_Cbk();
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h" /* polyspace MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00004 of AUTOSAR" */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
