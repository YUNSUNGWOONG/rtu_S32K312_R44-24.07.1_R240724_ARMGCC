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
**  SRC-MODULE: Wdg_76_Acw_Cbk.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTOEVER CUSTOM WDG                                   **
**                                                                            **
**  PURPOSE   : Autoever Custom Watchdog GPT callback function declaration    **
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
*******************************************************************************/


#ifndef WDG_76_ACW_CBK_H
#define WDG_76_ACW_CBK_H
/* @Trace: SRS_BSW_00346 SRS_Wdg_12165 SRS_Wdg_CUS_00003*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Wdg_76_Acw.h"

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
/* polyspace +5 MISRA-C3:20.1 [Justified: Low] "see SWS_MemMap_00004 of AUTOSAR" */
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDG_76_ACW_CODE) WDG_76_ACW_GPT_CBK(void);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"


#endif /* WDG_76_ACW_CBK_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
