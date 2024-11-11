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
**  SRC-MODULE: NvM_Version.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Perform version check with other module versions              **
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
** 1.1.1.1     29-Jun-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-221>                **
*******************************************************************************/
#include "NvM_Version.h"
#include "Rte.h"
#include "MemIf.h"
#if(STD_ON == NVM_DEMERROR_REPORT)
#include "Dem.h"                            /* Dem header file */
#endif
#include "BswM.h"
#include "Det.h"
#if(STD_ON == NVM_CRC_SUPPORT)
#include "Crc.h"
#endif

/* NvM AUTOSAR Version check */
#if((NVM_VERSION_AR_RELEASE_MAJOR_VERSION != NVM_AR_RELEASE_MAJOR_VERSION) || \
  (NVM_VERSION_AR_RELEASE_MINOR_VERSION != NVM_AR_RELEASE_MINOR_VERSION) || \
  (NVM_VERSION_AR_RELEASE_REVISION_VERSION != NVM_AR_RELEASE_REVISION_VERSION))
  #error "NvM: Mismatch AUTOSAR Version in NvM_Version.c"
#endif

/* NvM Software Version check */
#if ((NVM_VERSION_SW_MAJOR_VERSION != NVM_SW_MAJOR_VERSION) || \
  (NVM_VERSION_SW_MINOR_VERSION != NVM_SW_MINOR_VERSION) || \
  (NVM_VERSION_SW_PATCH_VERSION != NVM_SW_PATCH_VERSION))
  #error "NvM: Mismatch Software Version in NvM_Version.c"
#endif

/* Rte Version check */
#if((NVM_RTE_AR_RELEASE_MAJOR_VERSION != RTE_AR_RELEASE_MAJOR_VERSION) || \
  (NVM_RTE_AR_RELEASE_MINOR_VERSION != RTE_AR_RELEASE_MINOR_VERSION))
  #error "NvM: Mismatch AUTOSAR Version with Rte.h"
#endif

/* MemIf version check */
#if((NVM_MEMIF_AR_RELEASE_MAJOR_VERSION != MEMIF_AR_RELEASE_MAJOR_VERSION) || \
  (NVM_MEMIF_AR_RELEASE_MINOR_VERSION != MEMIF_AR_RELEASE_MINOR_VERSION))
  #error "NvM: Mismatch AUTOSAR Version with MemIf.h"
#endif

/* Dem version check */
#if(STD_ON == NVM_DEMERROR_REPORT)
  #if((NVM_DEM_AR_RELEASE_MAJOR_VERSION != DEM_AR_RELEASE_MAJOR_VERSION) || \
    (NVM_DEM_AR_RELEASE_MINOR_VERSION != DEM_AR_RELEASE_MINOR_VERSION))
    #error "NvM: Mismatch AUTOSAR Version with Dem.h"
  #endif
#endif

/* BswM version check */
#if((NVM_BSWM_AR_RELEASE_MAJOR_VERSION != BSWM_AR_RELEASE_MAJOR_VERSION) || \
  (NVM_BSWM_AR_RELEASE_MINOR_VERSION != BSWM_AR_RELEASE_MINOR_VERSION))
  #error "NvM: Mismatch AUTOSAR Version with BswM.h"
#endif

/* Det version check */
#if((NVM_DET_AR_RELEASE_MAJOR_VERSION != DET_AR_RELEASE_MAJOR_VERSION) || \
  (NVM_DET_AR_RELEASE_MINOR_VERSION != DET_AR_RELEASE_MINOR_VERSION))
  #error "NvM: Mismatch AUTOSAR Version with Det.h"
#endif

/* Crc version check */
#if(STD_ON == NVM_CRC_SUPPORT)
  #if((NVM_CRC_AR_RELEASE_MAJOR_VERSION != CRC_AR_RELEASE_MAJOR_VERSION) || \
    (NVM_CRC_AR_RELEASE_MINOR_VERSION != CRC_AR_RELEASE_MINOR_VERSION))
    #error "NvM: Mismatch AUTOSAR Version with Crc.h"
  #endif
#endif
