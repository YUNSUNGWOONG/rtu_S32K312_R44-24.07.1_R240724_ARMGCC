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
**  SRC-MODULE: Wdg_76_Acw.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTOEVER CUSTOM WDG                                   **
**                                                                            **
**  PURPOSE   : Header file to publish Autoever Custom Watchdog function      **
**              prototypes                                                    **
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

#ifndef WDG_76_ACW_H
#define WDG_76_ACW_H
/* @Trace: SRS_BSW_00346 SRS_Wdg_12165 SRS_Wdg_CUS_00003*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Wdg_76_Acw_Cfg.h"
#include "Wdg_76_Acw_Types.h"
#include "WdgIf_Types.h"
#include "Wdg_76_Acw_Version.h"

/*******************************************************************************
**                      Service IDs                                           **
*******************************************************************************/

/* Service Id of Wdg_76_Acw_Init */
#define WDG_76_ACW_INIT_SID                             ((uint8) 0x00U)
/* Service Id of Wdg_76_Acw_SetMode */
#define WDG_76_ACW_SETMODE_SID                          ((uint8) 0x01U)
/* Service Id of Wdg_76_Acw_SetTriggerCondition */
#define WDG_76_ACW_SETTRIGGERCONDITION_SID              ((uint8) 0x03U)
/* Service Id of Wdg_76_Acw_GetVersionInfo */
#define WDG_76_ACW_GETVERSIONINFO_SID                   ((uint8) 0x04U)

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00331 SRS_BSW_00385*/

/* API service used in wrong context(e.g. module not initialized). */
#define WDG_76_ACW_E_DRIVER_STATE                       ((uint8) 0x10U)
/* API service called with wrong parameter(s) */
/* polyspace +1 MISRA-C3:2.5 [Justified:Unset] "macro is used according to user configuration" */
#define WDG_76_ACW_E_PARAM_MODE                         ((uint8) 0x11U)
/* API service called with inconsistent parameter(s) */
#define WDG_76_ACW_E_PARAM_CONFIG                       ((uint8) 0x12U)
/* The passed timeout value is higher than the maximum timeout value */
#define WDG_76_ACW_E_PARAM_TIMEOUT                      ((uint8) 0x13U)
/* API is called with wrong pointer value (e.g. NULL pointer) */
#define WDG_76_ACW_E_PARAM_POINTER                      ((uint8) 0x14U)
/* Wdg Invalid configuration set selection */
/*  polyspace +1 MISRA-C3:2.5 [Not a Defect:Low] "Required by SWS_Wdg_00010. This macro to be used in post-build feature. "*/
#define WDG_76_ACW_E_INIT_FAILED                        ((uint8) 0x15U)


/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
/* polyspace +2 MISRA-C3:D4.9 [Justified:Low] "macro is used for improving performance" */
/* polyspace +1 MISRA-C3:2.5 [Not a Defect:Low] "macro is used according to user configuration" */
#define WDG_76_ACW_UNUSED_PTR(x)                        if ((x) != NULL_PTR) {}

#define WDG_76_ACW_CONVERT_TO_US                        (1000U)
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/

/* polyspace-begin MISRA2012:20.1 MISRA2012:2.5 [Justified:Low] "See SWS_MemMap_00004 of AUTOSAR" */
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_Init \
  (P2CONST(Wdg_76_Acw_ConfigType, AUTOMATIC, WDG_76_ACW_APPL_CONST) ConfigPtr);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, WDG_76_ACW_CODE) Wdg_76_Acw_SetMode \
  (VAR(WdgIf_ModeType, AUTOMATIC) Mode);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_SetTriggerCondition \
  (VAR(uint16, AUTOMATIC) timeout);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

#if (WDG_76_ACW_VERSION_INFO_API == STD_ON)
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_GetVersionInfo \
  (P2VAR(Std_VersionInfoType, AUTOMATIC, WDG_76_ACW_APPL_CONST) versioninfo);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (WDG_76_ACW_VERSION_INFO_API == STD_ON) */

#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDG_76_ACW_GPT_CODE) Wdg_76_Acw_Gpt_Cbk(void);
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

#endif /* WDG_76_ACW_H */

/* polyspace-end MISRA2012:20.1 MISRA2012:2.5 [Justified:Low] "See SWS_MemMap_00004 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
