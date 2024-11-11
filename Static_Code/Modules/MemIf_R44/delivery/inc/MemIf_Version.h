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
**  SRC-MODULE: MemIf_Version.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MemIf Module                                          **
**                                                                            **
**  PURPOSE   : Provide macros about dependent module's version               **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date            By                 Description                  **
********************************************************************************
** 0.0.1      25-Nov-2019     Ngocvm2;HuyP4      Initial Version              **
** 0.0.2      06-Jan-2020     VietPT4            Fix misra rule               **
** 0.0.3      27-Apr-2020     NgocVM2            Follow New V Cycle           **
** 0.0.4      07-Jul-2020     Thaodx       Updated SUD R44-Remine <#11836>    **
** 0.0.5      13-Jul-2020     NamTV9       Fix Defect R44-Redmine <#14587>    **
** 1.0.1      28-Aug-2021     JH Lim       Fix Defect R44-Redmine <#19737>    **
** 1.0.2      29-Jun-2022     SH Park      Improvement mobilegence            **
**                                           Classic <CP44-224, CP44-82>      **
*******************************************************************************/
#ifndef MEMIF_VERSION_H
#define MEMIF_VERSION_H

/*******************************************************************************
**                    Include Section                                         **
*******************************************************************************/
#include "MemIf.h"

/*******************************************************************************
**                     Version Information                                    **
*******************************************************************************/

/* Included files AUTOSAR specification version */
#if(MEMIF_DEV_ERROR_DETECT == STD_ON)
  #define MEMIF_DET_AR_RELEASE_MAJOR_VERSION  4U
  #define MEMIF_DET_AR_RELEASE_MINOR_VERSION  4U
#endif

#ifdef MEMIF_EA_DRIVER_INDEX
  #define MEMIF_EA_AR_RELEASE_MAJOR_VERSION  4U
  #define MEMIF_EA_AR_RELEASE_MINOR_VERSION  4U
#endif

#ifdef MEMIF_FEE_DRIVER_INDEX
  #define MEMIF_FEE_AR_RELEASE_MAJOR_VERSION    4U
  #define MEMIF_FEE_AR_RELEASE_MINOR_VERSION_1  2U
  #define MEMIF_FEE_AR_RELEASE_MINOR_VERSION_2  4U
#endif

#endif /* end of MEMIF_VERSION_H */

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
