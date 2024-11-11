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
**  SRC-MODULE: Tm_Version.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Time Service Module                                   **
**                                                                            **
**  PURPOSE   : Provision of callback functions and their functionality.      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By         Description                             **
********************************************************************************
** 1.0.4     29-Dec-2023   NamNT1     CP44-3044, 3296, 3297, 3294             **
** 1.0.3     24-Jul-2023   NamNT1     CP44-2279                               **
** 1.0.2     17-Mar-2023   NamNT1     CP44-1740                               **
** 1.0.1     24-Jun-2022   PhatCT     R44-Redmine #25858, #28232              **
** 1.0.0     19-Jun-2020   DanhLT2    Initial Version                         **
*******************************************************************************/
#ifndef TM_VERSION_H
#define TM_VERSION_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "HwResource.h"
#include "Tm_Cfg.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
 /* @Trace: Tm_SUD_MACRO_001, Tm_SUD_FILE_001 */
/* AUTOSAR SPECIFICATION VERSION INFORMATION */
#define TM_VERSION_AR_RELEASE_MAJOR_VERSION    4
#define TM_VERSION_AR_RELEASE_MINOR_VERSION    4
#define TM_VERSION_AR_RELEASE_REVISION_VERSION 0
/* FILE VERSION INFORMATION */
#define TM_VERSION_SW_MAJOR_VERSION            1
#define TM_VERSION_SW_MINOR_VERSION            0
#define TM_VERSION_SW_PATCH_VERSION            4

/*AUTOSAR Specification version information of Det Module */
#define TM_DET_AR_RELEASE_MAJOR_VERSION        4
#define TM_DET_AR_RELEASE_MINOR_VERSION        4

/*AUTOSAR Specification version information of Gpt Module */
#define TM_GPT_AR_RELEASE_MAJOR_VERSION        4
#define TM_GPT_AR_RELEASE_MINOR_VERSION_R42    2
#define TM_GPT_AR_RELEASE_MINOR_VERSION_R43    3
#define TM_GPT_AR_RELEASE_MINOR_VERSION_R44    4

#endif /* TM_VERSION_H */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
