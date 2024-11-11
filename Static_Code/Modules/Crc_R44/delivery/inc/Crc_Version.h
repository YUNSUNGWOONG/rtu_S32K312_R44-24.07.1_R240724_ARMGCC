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
**  SRC-MODULE: Crc_Version.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
**                                                                            **
**  PURPOSE   : Header for Crc_Version.c                                      **
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
** 0.0.1     19-Nov-2019   ThienDT          Initial Version                   **
** 0.0.2     07-Apr-2020   TienNV21         Update code annotation            **
** 1.0.2     24-Dec-2021   JHLim            Redmine #33330                    **
** 1.0.2.2   29-Jun-2022   SH Park          Improvement mobilegence           **
**                                            Classic <CP44-224>              **
** 1.0.3     12-Aug-2022   SH Park          Improvement mobilegence           **
**                                            Classic <CP44-81>               **
** 1.0.3.1   18-Nov-2022   ThuanLD5         Improvement mobilegence           **
**                                            Classic <CP44-361>              **
**                                                    <CP44-362>              **
*******************************************************************************/
#ifndef CRC_VERSION_H
#define CRC_VERSION_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Crc.h"                 /* Crc Header File */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CRC_VERSION_AR_RELEASE_MAJOR_VERSION     (4U)
#define CRC_VERSION_AR_RELEASE_MINOR_VERSION     (4U)
#define CRC_VERSION_AR_RELEASE_REVISION_VERSION  (0U) 

/* Software Version Information */
#define CRC_VERSION_SW_MAJOR_VERSION      (1U)
#define CRC_VERSION_SW_MINOR_VERSION      (0U)
#define CRC_VERSION_SW_PATCH_VERSION      (3U) 

#endif /* CRC_VERSION_H */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
