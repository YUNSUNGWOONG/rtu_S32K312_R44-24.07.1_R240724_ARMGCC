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
**  SRC-MODULE: EcuM_Version.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : C header for EcuM_Version                                     **
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
** 1.2.5     24-Nov-2023   Eugean Kim    	 CP44-3054,3055                   **
** 1.2.4     11-Jul-2023   Eugean Kim    	 CP44-2540                        **
** 1.2.0     04-Oct-2022   TriBD             R44_2021 #27878                  **
** 1.1.5     10-Mar-2022   TriBD             R44_2021 #24753                  **
** 1.1.4     17-Jan-2022   TriBD             R44_2021 #20832                  **
** 1.1.3     28-Oct-2021   TriBD             R44_2021 #21593                  **
** 1.1.2     21-Sep-2021   TriBD             R44_2021 #19319                  **
** 1.1.1     28-Jun-2021   TriBD             R44_2021 #18655                  **
** 1.1.0     22-Mar-2021   TinhPV3           R44_2021 #17960                  **
** 1.0.0     03-Mar-2020   LocLT5        Update module version information    **
*******************************************************************************/
#ifndef ECUM_VERSION_H
#define ECUM_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"                /* ECUM Header File */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define ECUM_VERSION_AR_RELEASE_MAJOR_VERSION     4
#define ECUM_VERSION_AR_RELEASE_MINOR_VERSION     4
#define ECUM_VERSION_AR_RELEASE_REVISION_VERSION  0

/* Software Version Information */
#define ECUM_VERSION_SW_MAJOR_VERSION     1
#define ECUM_VERSION_SW_MINOR_VERSION     2
#define ECUM_VERSION_SW_PATCH_VERSION     4

/*Version information of BswM module */
#define ECUM_BSWM_AR_RELEASE_MAJOR_VERSION              0x04U
#define ECUM_BSWM_AR_RELEASE_MINOR_VERSION              0x04U

/* Version information of RTE module */
#define ECUM_RTE_AR_RELEASE_MAJOR_VERSION               0x04U
#define ECUM_RTE_AR_RELEASE_MINOR_VERSION               0x04U

/* Version information of ICU module */
#define ECUM_ICU_AR_RELEASE_MAJOR_VERSION               0x04U
#define ECUM_ICU_AR_RELEASE_MINOR_VERSION               0x04U

/* Version information of GPT module */
#define ECUM_GPT_AR_RELEASE_MAJOR_VERSION               0x04U
#define ECUM_GPT_AR_R42_RELEASE_MINOR_VERSION           0x02U
#define ECUM_GPT_AR_R48_RELEASE_MINOR_VERSION           0x08U

/* Version information of COMM module */
#define ECUM_COMM_AR_RELEASE_MAJOR_VERSION               0x04U
#define ECUM_COMM_AR_RELEASE_MINOR_VERSION               0x04U

#endif /* ECUM_VERSION_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

