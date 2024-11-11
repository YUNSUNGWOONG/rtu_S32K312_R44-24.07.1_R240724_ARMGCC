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
**  SRC-MODULE: WdgM_Version.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WDGM                                                  **
**                                                                            **
**  PURPOSE   : Header to provide WdgM's version information                  **
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
** 0.0.3     15-Oct-2019   ThanhNT      Update module version information     **
** 0.0.5     24-Oct-2019   ThanhNT      Update version checking mechanism     **
** 0.0.7     21-Nov-2019   ThanhNT      Update SUD and SRS Ids                **
** 0.0.8     27-Nov-2019   ThanhNT      Fix misra warning                     **
** 0.0.9     11-Mar-2020   TienVD       Update traceability                   **
** 1.0.2     30-Mar-2021   HiepVT1      Update check version method between   **
**                                      WdgM and DET                          **
** 1.3.0.1   30-Jun-2022   TriBD        #CP44-322                             **
*******************************************************************************/

#ifndef WDGM_VERSION_H
#define WDGM_VERSION_H
/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgM.h"               /* WdgM module header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: WdgM_SRS_BSW_00161 WdgM_SRS_BSW_00162 WdgM_SRS_BSW_00059_002 */
/* AUTOSAR Specification Version Information */
#define WDGM_VERSION_AR_RELEASE_MAJOR_VERSION           0x04U
#define WDGM_VERSION_AR_RELEASE_MINOR_VERSION           0x04U
/* polyspace-begin MISRA-C3:2.5 [Not a defect:Low] "This macro is used for keeping consistency between static code and generation code" */
#define WDGM_VERSION_AR_RELEASE_REVISION_VERSION        0x00U
/* polyspace-end MISRA-C3:2.5 */

/* Software Version Information */
#define WDGM_VERSION_SW_MAJOR_VERSION                   0x01U
#define WDGM_VERSION_SW_MINOR_VERSION                   0x00U
#define WDGM_VERSION_SW_PATCH_VERSION                   0x00U

/*Version information of WdgIf module */
#define WDGM_WDGIF_AR_RELEASE_MAJOR_VERSION             0x04U
#define WDGM_WDGIF_AR_RELEASE_MINOR_VERSION             0x04U

/* Version information of RTE module */
#define WDGM_RTE_AR_RELEASE_MAJOR_VERSION               0x04U
#define WDGM_RTE_AR_RELEASE_MINOR_VERSION               0x04U

/*Version information of BswM module */
#define WDGM_BSWM_AR_RELEASE_MAJOR_VERSION              0x04U
#define WDGM_BSWM_AR_RELEASE_MINOR_VERSION              0x04U


/* polyspace-begin MISRA-C3:2.5 [Not a defect:Low] "below macros are used according to user configuration" */
/*Version information of Mcu module */
#define WDGM_MCU_AR_RELEASE_MAJOR_VERSION               0x04U
#define WDGM_MCU_AR_RELEASE_MINOR_VERSION_L             0x00U
#define WDGM_MCU_AR_RELEASE_MINOR_VERSION_U             0x04U

/*Version information of Os module */
#define WDGM_OS_AR_RELEASE_MAJOR_VERSION                0x04U
#define WDGM_OS_AR_RELEASE_MINOR_VERSION                0x04U

/*Version information of Det module */
#define WDGM_DET_AR_RELEASE_MAJOR_VERSION               0x04U
#define WDGM_DET_AR_RELEASE_MINOR_VERSION_L             0x00U
#define WDGM_DET_AR_RELEASE_MINOR_VERSION_U             0x04U

/*Version information of Dem module */
#define WDGM_DEM_AR_RELEASE_MAJOR_VERSION               0x04U
#define WDGM_DEM_AR_RELEASE_MINOR_VERSION               0x04U

/* polyspace-end MISRA-C3:2.5 */
/* @Trace: WdgM_SRS_BSW_00161 WdgM_SRS_BSW_00162 WdgM_SRS_BSW_00059_002 */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

#endif /* WDGM_VERSION_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

