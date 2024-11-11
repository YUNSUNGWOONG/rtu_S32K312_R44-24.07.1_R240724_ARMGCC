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
**  SRC-MODULE: Wdg_76_Acw_Version.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTOEVER CUSTOM WDG                                   **
**                                                                            **
**  PURPOSE   : Header for Wdg_76_Acw_Version.c                               **
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
** 0.0.2     14-Feb-2020   DongNx       Update GPT and DIO version            **
** 1.3.1     27-May-2022   TriBD        R44_2021 #27603                       **
**           30-Jun-2022   TriBD        #CP44-324                             **
** 1.3.4     17-Jul-2023   JHKim        #CP44-2519                            **
*******************************************************************************/

#ifndef WDG_76_ACW_VERSION_H
#define WDG_76_ACW_VERSION_H
/* @Trace: SRS_BSW_00346 SRS_Wdg_12165 SRS_Wdg_CUS_00003*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Wdg_76_Acw_Cfg.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00004 */
/* polyspace-begin MISRA-C3:2.5 [Not a defect]"This macro is used for AUTOSAR version check feature" */
/* AUTOSAR Specification Version Information */
#define WDG_76_ACW_VERSION_AR_RELEASE_MAJOR_VERSION    4
#define WDG_76_ACW_VERSION_AR_RELEASE_MINOR_VERSION    4
#define WDG_76_ACW_VERSION_AR_RELEASE_REVISION_VERSION 0

/* Software Version Information */
#define WDG_76_ACW_VERSION_SW_MAJOR_VERSION     1
#define WDG_76_ACW_VERSION_SW_MINOR_VERSION     0
#define WDG_76_ACW_VERSION_SW_PATCH_VERSION     0

/*Version information of Det module */
#define WDG_76_ACW_DET_AR_RELEASE_MAJOR_VERSION          4
#define WDG_76_ACW_DET_AR_RELEASE_MINOR_VERSION          4

/*Version information of Dem module */
#define WDG_76_ACW_DEM_AR_RELEASE_MAJOR_VERSION          4
#define WDG_76_ACW_DEM_AR_RELEASE_MINOR_VERSION          4

/*Version information of Dio module */
#define WDG_76_ACW_DIO_AR_RELEASE_MAJOR_VERSION          4
#define WDG_76_ACW_DIO_AR_RELEASE_MINOR_VERSION_L        2
#define WDG_76_ACW_DIO_AR_RELEASE_MINOR_VERSION_U        8

/*Version information of Gpt module */
#define WDG_76_ACW_GPT_AR_RELEASE_MAJOR_VERSION          4
#define WDG_76_ACW_GPT_AR_RELEASE_MINOR_VERSION_L        2
#define WDG_76_ACW_GPT_AR_RELEASE_MINOR_VERSION_U        8
/* polyspace-end<MISRA-C3:2.5 */
#endif /* WDG_76_ACW_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
