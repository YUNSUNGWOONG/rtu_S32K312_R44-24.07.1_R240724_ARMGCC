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
**  SRC-MODULE: StbM_Version.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Synchronized Time-Base Manager Module                 **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision        Date                By              Description            **
********************************************************************************
** 1.0.7           14-Feb-2024         JWMoon          CP44-3634              **
** 1.0.6           31-Jul-2023         NamNT1          CP44-2231, 2035        **
** 1.0.5           30-Nov-2022         NamNT1          ASPICE-76              **
** 1.0.3           21-Jul-2022         ThuanVT         JIRA BUGCLASSIC-152,   **
**                                                     R44-Redmine #633       **
** 1.0.1           15-Sep-2021         SHKim           #20096                 **
** 1.0.0           16-Dec-2020         SHKim           Initial Version        **
*******************************************************************************/
#ifndef STBM_VERSION_H
#define STBM_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* StbM configuration header */
#include "StbM.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* @Trace: StbM_Version_SDD_MACRO_008 */
/* AUTOSAR specification version information */
#define STBM_VERSION_AR_RELEASE_MAJOR_VERSION    4
#define STBM_VERSION_AR_RELEASE_MINOR_VERSION    4
#define STBM_VERSION_AR_RELEASE_REVISION_VERSION 0

/* StbM software version information */
#define STBM_VERSION_SW_MAJOR_VERSION            1
#define STBM_VERSION_SW_MINOR_VERSION            0
#define STBM_VERSION_SW_PATCH_VERSION            7


/* Other (Interface) module version information */

#define STBM_RTE_AR_RELEASE_MAJOR_VERSION 4
#define STBM_RTE_AR_RELEASE_MINOR_VERSION 4

#define STBM_DET_AR_RELEASE_MAJOR_VERSION 4
#define STBM_DET_AR_RELEASE_MINOR_VERSION 4

#define STBM_OS_AR_RELEASE_MAJOR_VERSION  4
#define STBM_OS_AR_RELEASE_MINOR_VERSION  4

#define STBM_GPT_AR_RELEASE_MAJOR_VERSION 4
#define STBM_GPT_AR_RELEASE_MINOR_VERSION_AR44 4
#define STBM_GPT_AR_RELEASE_MINOR_VERSION_AR43 3

#define STBM_ETHIF_AR_RELEASE_MAJOR_VERSION 4
#define STBM_ETHIF_AR_RELEASE_MINOR_VERSION 4

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* STBM_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

