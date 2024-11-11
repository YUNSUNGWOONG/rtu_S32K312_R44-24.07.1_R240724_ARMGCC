/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_Version.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Header to check inter-module version information              **
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
** 1.0.0.0   15-Jan-2021   JH Lim       Initial version                       **
** 1.0.1.0   16-Mar-2021   TamTV6       Add trace SUD                         **
** 1.0.2     09-Nov-2021   TamTV6       Implement #20990                      **
** 1.0.4.0   18-Oct-2022   DienTC1      #CP44-438                             **
** 1.0.5.0   02-Mar-2022   PhuocLH9     #CP44-1059                            **
** 1.0.6.0   17-Mar-2023   DienTC1      #CP44-1436                            **
** 1.0.7.0   28-Jul-2023   DienTC1      #CP44-2574                            **
** 1.0.8.0   5-Sep-2023    PhuocLH9     #CP44-2726,#CP44-2857                 **
** 1.0.9.0   23-Dec-2023   YH Eum       #CP44-3331,#CP44-3613                 **
** 1.0.10.0  24-Jan-2023   PhuocLH9     #CP44-3474                            **
*******************************************************************************/
#ifndef CSM_VERSION_H
#define CSM_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: Csm_SUD_MACRO_001 */
#define CSM_VERSION_AR_RELEASE_MAJOR_VERSION           0x04U
#define CSM_VERSION_AR_RELEASE_MINOR_VERSION           0x04U

#define CSM_VERSION_AR_RELEASE_REVISION_VERSION        0x00U

/* Software Version Information */
#define CSM_VERSION_SW_MAJOR_VERSION                   0x01U
#define CSM_VERSION_SW_MINOR_VERSION                   0x00U
#define CSM_VERSION_SW_PATCH_VERSION                   0x0AU

/* Version informatin of CryIf module */
#define CSM_CRYIF_AR_RELEASE_MAJOR_VERSION             0x04U
#define CSM_CRYIF_AR_RELEASE_MINOR_VERSION             0x04U

/* Version information of RTE module */
#define CSM_RTE_AR_RELEASE_MAJOR_VERSION               0x04U
#define CSM_RTE_AR_RELEASE_MINOR_VERSION_L             0x00U
#define CSM_RTE_AR_RELEASE_MINOR_VERSION_U             0x04U

/*Version information of Det module */
#define CSM_DET_AR_RELEASE_MAJOR_VERSION               0x04U
#define CSM_DET_AR_RELEASE_MINOR_VERSION_L             0x00U
#define CSM_DET_AR_RELEASE_MINOR_VERSION_U             0x04U

#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
