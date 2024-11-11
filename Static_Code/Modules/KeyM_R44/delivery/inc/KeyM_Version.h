/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_Version.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Header to provide KeyM's version information                  **
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
** 1.0.1.0   27-Mar-2021   TamTV6       Add Trace SUD                         **
** 1.0.2     08-Nov-2021   TamTV6       Update patch version                  **
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
** 1.0.6.0   09-Dec-2022   DienTC1      #CP44-1308                            **
** 1.0.7.0   07-Apr-2023   PhuocLH9     #CP44-1636,#CP44-1664,#CP44-1854      **
**                                      #CP44-1541,#CP44-1665,#CP44-1684      **
** 1.0.8.0   31-Jul-2023   PhuocLH9     #CP44-2396,#CP44-2394                 **
** 1.0.9.0   21-Feb-2024   PhuocLH9     #CP44-3111,#CP44-3110,#CP44-3635      **
**										#CP44-3633,#CP44-3742                 **
*******************************************************************************/

#ifndef KEYM_VERSION_H
#define KEYM_VERSION_H
/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM module header file */
#include "KeyM.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: KeyM_SUD_MACRO_001 */
/* AUTOSAR Specification Version Information */
#define KEYM_VERSION_AR_RELEASE_MAJOR_VERSION           0x04U
#define KEYM_VERSION_AR_RELEASE_MINOR_VERSION           0x04U

#define KEYM_VERSION_AR_RELEASE_REVISION_VERSION        0x00U

/* Software Version Information */
#define KEYM_VERSION_SW_MAJOR_VERSION                   0x01U
#define KEYM_VERSION_SW_MINOR_VERSION                   0x00U
#define KEYM_VERSION_SW_PATCH_VERSION                   0x09U

/*Version information of Csm module */
#define KEYM_CSM_AR_RELEASE_MAJOR_VERSION               0x04U
#define KEYM_CSM_AR_RELEASE_MINOR_VERSION               0x04U

/* Version information of RTE module */
#define KEYM_RTE_AR_RELEASE_MAJOR_VERSION               0x04U
#define KEYM_RTE_AR_RELEASE_MINOR_VERSION_L             0x00U
#define KEYM_RTE_AR_RELEASE_MINOR_VERSION_U             0x04U

/*Version information of StbM module */
#define KEYM_STBM_AR_RELEASE_MAJOR_VERSION              0x04U
#define KEYM_STBM_AR_RELEASE_MINOR_VERSION              0x04U

/*Version information of Det module */
#define KEYM_DET_AR_RELEASE_MAJOR_VERSION               0x04U
#define KEYM_DET_AR_RELEASE_MINOR_VERSION_L             0x00U
#define KEYM_DET_AR_RELEASE_MINOR_VERSION_U             0x04U
/*Version information of NvM module */
#define KEYM_NVM_AR_RELEASE_MAJOR_VERSION               0x04U
#define KEYM_NVM_AR_RELEASE_MINOR_VERSION               0x04U

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

#endif /* KEYM_VERSION_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
