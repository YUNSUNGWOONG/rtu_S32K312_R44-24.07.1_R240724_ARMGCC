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
**  SRC-MODULE: WdgStack_Callout.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTRON WDG STACK CALLOUT                              **
**                                                                            **
**  PURPOSE   : Header file to publish Autron Watchdog stack callout          **
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
** 1.4.4     20-Jul-2022   YongHyun     Update #36758                         **
** 1.0.4     12-Jul-2016   Kuiksun      Update #5513                          **
** 1.0.0     29-Apr-2016   Sinil        Initial version                       **
*******************************************************************************/

#ifndef WDGSTACK_CALLOUT_H
#define WDGSTACK_CALLOUT_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Precompile Options                                    **
*******************************************************************************/
#define WDGSTACK_ENABLE_INTERNAL_WDG              (STD_ON)

#define WDGSTACK_ENABLE_EXTERNAL_WDG              (STD_OFF)

#if ((WDGSTACK_ENABLE_INTERNAL_WDG == STD_ON) \
  || (WDGSTACK_ENABLE_EXTERNAL_WDG == STD_ON))
#define WDGSTACK_ENABLE                           (STD_ON)
#endif

/*If using EcuM Module as version 2.6.0 higher then set to STD_ON */
#define WDGSTACK_INIT_USING_ECUM                  (STD_ON)

/* This area(START~END) must not be modified or removed by an user */
/* START */
/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
extern void WdgStack_DisableIntWdg(void);
extern void WdgStack_Init(void);
extern void WdgStack_TransitHighToLow(void);
extern void WdgStack_TransitLowToHigh(void);
extern void WdgStack_TriggerWatchdog(void);

#endif /* WDGSTACK_CALLOUT_H */
/* END */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
