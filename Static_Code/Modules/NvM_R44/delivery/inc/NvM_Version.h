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
**  SRC-MODULE: NvM_Version.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Delare other module versions to compare.                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date           By          Description                         **
********************************************************************************
** 0.0.1       06-Dec-2019    VinhLV5     Initial version                     **
** 0.0.2       04-May-2020    VinhLV5     Update traceability, apply          **
**                                        new v cycle, Fix Misra              **
** 0.0.3       24-Jul-2020    VinhLV5     R44-Redmine #9958                   **
** 1.0.2       27-Aug-2021    JH Lim      R44-Redmine #19726                  **
** 1.1.0       08-Dec-2021    JH Lim      R44-Redmine #19388                  **
** 1.1.1       09-May-2022    SH Park     R44-Redmine #27456                  **
** 1.1.1.1     29-Jun-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-221>                **
** 1.1.2       12-Aug-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-76>                 **
** 1.2.0       03-Nov-2022    ThuanLD5    Improvement mobilegence             **
**                                          Classic <CP44-869>                **
**                                          <CP44-895> <CP44-955>             **
** 1.3.0       20-Dec-2022    ThuanLD5    Improvement mobilegence             **
**                                          Classic <CP44-987>                **
**                                          <CP44-1172> <CP44-1173>           **
** 1.3.2       09-May-2024    MK Choi     Improvement mobilegence             **
**                                          Classic <CP44-8070>               **
*******************************************************************************/
#ifndef NVM_VERSION_H
#define NVM_VERSION_H

#include "NvM.h"

/* AUTOSAR Specification Version Information */
#define NVM_VERSION_AR_RELEASE_MAJOR_VERSION    4U
#define NVM_VERSION_AR_RELEASE_MINOR_VERSION    4U
#define NVM_VERSION_AR_RELEASE_REVISION_VERSION 0U

/* Software Version Information*/
#define NVM_VERSION_SW_MAJOR_VERSION            1U
#define NVM_VERSION_SW_MINOR_VERSION            3U
#define NVM_VERSION_SW_PATCH_VERSION            2U

/* Rte version define */
#define NVM_RTE_AR_RELEASE_MAJOR_VERSION        4U
#define NVM_RTE_AR_RELEASE_MINOR_VERSION        4U

/* MemIf version define */
#define NVM_MEMIF_AR_RELEASE_MAJOR_VERSION      4U
#define NVM_MEMIF_AR_RELEASE_MINOR_VERSION      4U

/* Dem version define */
#if(STD_ON == NVM_DEMERROR_REPORT)
#define NVM_DEM_AR_RELEASE_MAJOR_VERSION        4U
#define NVM_DEM_AR_RELEASE_MINOR_VERSION        4U
#endif

/* BswM version define */
#define NVM_BSWM_AR_RELEASE_MAJOR_VERSION       4U
#define NVM_BSWM_AR_RELEASE_MINOR_VERSION       4U

/* Det version define */
#define NVM_DET_AR_RELEASE_MAJOR_VERSION        4U
#define NVM_DET_AR_RELEASE_MINOR_VERSION        4U

/* Crc version define */
#if(STD_ON == NVM_CRC_SUPPORT)
#define NVM_CRC_AR_RELEASE_MAJOR_VERSION        4U
#define NVM_CRC_AR_RELEASE_MINOR_VERSION        4U
#endif

#endif /* NVM_VERSION_H */
