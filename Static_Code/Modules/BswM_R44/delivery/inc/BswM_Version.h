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
**  SRC-MODULE: BswM_Version.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR BswM Module                                           **
**                                                                            **
**  PURPOSE   : C header for BswM_Version                                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.3.2     14-May-2024   Hongsuk Kim   CP44-5344                            **
** 1.3.1     13-Feb-2024   HS Park       CP44-3409                            **
** 1.3.0     27-SEP-2023   Eugene Kim    CP44-1742                            **
** 1.2.0     11-Jul-2023   Eugene Kim    CP44-2491                            **
** 1.1.6     08-Feb-2023   ThanhVC6      CP44-1563                            **
** 1.1.5     30-Oct-2022   TriBD         CP44-939                             **
** 1.1.4     12-Aug-2022   Manje Woo     CP44-726                             **
** 1.1.3     17-Feb-2022   TriBD         R44_2021 #22427                      **
** 1.1.1     29-Oct-2021   TriBD         R44_2021 #21581                      **
** 1.1.0     01-Jun-2021   TriBD         R44_2021 #17963                      **
** 1.0.0     03-Mar-2020   ThiNT8        R44-Redmine #4579, #8683             **
*******************************************************************************/
#ifndef BSWM_VERSION_H
#define BSWM_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "BswM.h"                /* BSWM Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
/* @Trace: BswM_SUD_MACRO_001 */
#define BSWM_VERSION_AR_RELEASE_MAJOR_VERSION     4
#define BSWM_VERSION_AR_RELEASE_MINOR_VERSION     4
#define BSWM_VERSION_AR_RELEASE_REVISION_VERSION  0

/* Software Version Information */
/* @Trace: BswM_SUD_MACRO_002 */
#define BSWM_VERSION_SW_MAJOR_VERSION     1
#define BSWM_VERSION_SW_MINOR_VERSION     3
#define BSWM_VERSION_SW_PATCH_VERSION     2

/*Version information of RTE */
/* @Trace: BswM_SUD_MACRO_004 */
#define BSWM_RTE_AR_RELEASE_MAJOR_VERSION                0x04U
#define BSWM_RTE_AR_RELEASE_MINOR_VERSION                0x04U

/*Version information of CAMSM MODULE */
/* @Trace: BswM_SUD_MACRO_007 */
#define BSWM_CAMSM_AR_RELEASE_MAJOR_VERSION                0x04U
#define BSWM_CAMSM_AR_RELEASE_MINOR_VERSION                0x04U

/*Version information of COMM MODULE */
/* @Trace: BswM_SUD_MACRO_006 */
#define BSWM_COMM_AR_RELEASE_MAJOR_VERSION                0x04U
#define BSWM_COMM_AR_RELEASE_MINOR_VERSION                0x04U

/*Version information of ECUM MODULE */
/* @Trace: BswM_SUD_MACRO_003 */
#define BSWM_ECUM_AR_RELEASE_MAJOR_VERSION                0x04U
#define BSWM_ECUM_AR_RELEASE_MINOR_VERSION                0x04U

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* BSWM_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

