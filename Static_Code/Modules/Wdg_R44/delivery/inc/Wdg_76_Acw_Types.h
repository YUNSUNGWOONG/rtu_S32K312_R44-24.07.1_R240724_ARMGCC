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
**  SRC-MODULE: Wdg_76_Acw_Types.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTOEVER CUSTOM WDG                                   **
**                                                                            **
**  PURPOSE   : Header file to publish Autoever Custom Watchdog types         **
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
** 1.3.4.0   22-Aug-2023   HS Park      #CP44-2490                            **
*******************************************************************************/

#ifndef WDG_76_ACW_TYPES_H
#define WDG_76_ACW_TYPES_H
/* @Trace: SRS_BSW_00346 SRS_Wdg_12165 SRS_Wdg_CUS_00003*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Wdg_76_Acw_Cfg.h"

/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
/* Macros for numerical Values */
#define WDG_76_ACW_ZERO                                   ((uint8) 0x00U)


/*******************************************************************************
**                      Global Enumerations                                   **
*******************************************************************************/
typedef enum 
{
  WDG_76_ACW_UNINIT = 0x00,
  WDG_76_ACW_IDLE,
  WDG_76_ACW_BUSY,
  WDG_76_ACW_EXPIRED
} Wdg_76_Acw_StatusType;

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* polyspace +8 MISRA-C3:D4.8 [Justified:Low] "This can be used in application code." */
typedef struct 
{
  VAR(uint32, AUTOMATIC) InitialTimeoutUs;
  VAR(WdgIf_ModeType, AUTOMATIC) InitialMode;
  VAR(uint32, AUTOMATIC) SlowPeriodUs;
  VAR(uint32, AUTOMATIC) SlowPeriodTick;
  VAR(uint32, AUTOMATIC) SlowDutyUs;
  VAR(uint32, AUTOMATIC) SlowDutyTick;
  VAR(uint32, AUTOMATIC) FastPeriodUs;
  VAR(uint32, AUTOMATIC) FastPeriodTick;
  VAR(uint32, AUTOMATIC) FastDutyUs;
  VAR(uint32, AUTOMATIC) FastDutyTick;
} Wdg_76_Acw_ConfigType;


#endif /* WDG_76_ACW_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
