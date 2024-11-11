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
**  SRC-MODULE: WdgIf_Version.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTOEVER CUSTOM WDGIF                                 **
**                                                                            **
**  PURPOSE   : AutoEver Custom Watchdog Interface Define Version             **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 0.0.1     23-Sep-2019   Tungdt39         R44-Redmine <#1440>               **
** 0.0.2     14-Feb-2020   ThuanNM2         Fix version WDG_17_Scu            **
** 1.3.1     09-Aug-2022   TriBD            CP44-729, CP44-323                **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
#ifndef WDGIF_VERSION_H
#define WDGIF_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgIf_Cfg.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* Autosar Specification Version */
#define WDGIF_VERSION_AR_RELEASE_MAJOR_VERSION                        (4)
#define WDGIF_VERSION_AR_RELEASE_MINOR_VERSION                        (4)
#define WDGIF_VERSION_AR_RELEASE_REVISION_VERSION                     (0)

/* File Version Information */
#define WDGIF_VERSION_SW_MAJOR_VERSION                                (1)
#define WDGIF_VERSION_SW_MINOR_VERSION                                (0)
#define WDGIF_VERSION_SW_PATCH_VERSION                                (0)

#if defined(WDG_17_SCU_AR_RELEASE_MAJOR_VERSION) && defined(WDG_17_SCU_AR_RELEASE_MINOR_VERSION)
/* Define dependency module Wdg AUTOSAR version */
#define WDGIF_WDG_17_SCU_AR_RELEASE_MAJOR_VERSION                      (4)
#define WDGIF_WDG_17_SCU_AR_R42_RELEASE_MINOR_VERSION                  (2)
#define WDGIF_WDG_17_SCU_AR_R44_RELEASE_MINOR_VERSION                  (4)
#endif /* End of #if defined(WDG_17_SCU_AR_RELEASE_MAJOR_VERSION)
        && defined(WDG_17_SCU_AR_RELEASE_MINOR_VERSION) */

#if defined(WDG_39_ACW_AR_RELEASE_MAJOR_VERSION) && defined(WDG_39_ACW_AR_RELEASE_MINOR_VERSION)
/* Define dependency module Wdg_39_Acw_AUTOSAR version */
#define WDGIF_WDG_39_ACW_AR_RELEASE_MAJOR_VERSION                      (4)
#define WDGIF_WDG_39_ACW_AR_RELEASE_MINOR_VERSION                      (4)
#endif /* End of #if defined(WDG_39_ACW_AR_RELEASE_MAJOR_VERSION) 
        && defined(WDG_39_ACW_AR_RELEASE_MINOR_VERSION) */

#if defined(WDG_76_ACW_AR_RELEASE_MAJOR_VERSION) && defined(WDG_76_ACW_AR_RELEASE_MINOR_VERSION)
/* Define dependency module Wdg_76_Acw_AUTOSAR version */
#define WDGIF_WDG_76_ACW_AR_RELEASE_MAJOR_VERSION                      (4)
#define WDGIF_WDG_76_ACW_AR_RELEASE_MINOR_VERSION                      (4)
#endif /* End of #if defined(WDG_76_ACW_AR_RELEASE_MAJOR_VERSION)
        && defined(WDG_76_ACW_AR_RELEASE_MINOR_VERSION) */

/* Define dependency module DET AUTOSAR version */
/* polyspace-begin MISRA2012:2.5 [Not a defect:Low] "This macro is use for version check in modules uses WdgIF" */
#define WDGIF_DET_AR_RELEASE_MAJOR_VERSION                             (4)
#define WDGIF_DET_AR_RELEASE_MINOR_VERSION                             (4)

/* Define Std_Types AUTOSAR version */
#define WDGIF_STDTYPES_AR_RELEASE_MAJOR_VERSION                        (4)
#define WDGIF_STDTYPES_AR_RELEASE_MINOR_VERSION                        (4)
/* polyspace-end MISRA2012:2.5 [Not a defect:Low] "This macro is use for version check in modules uses WdgIF" */
#endif /* End of WDGIF_VERSION_H */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
