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
**  SRC-MODULE: Crc_Version.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
**                                                                            **
**  PURPOSE   : Provision for Version Information                             **
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
** 0.0.2     03-Mar-2020   TienNV21         Update traceability apply new     **
**                                          V-Cycle                           **
** 1.0.2.2   29-Jun-2022   SH Park          Improvement mobilegence           **
**                                            Classic <CP44-224>              **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Crc_Version.h"                    /* Crc Version Header file */

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* @Trace: SRS_BSW_00004 */
/* CRC AUTOSAR Version Check */
#if((CRC_AR_RELEASE_MAJOR_VERSION != CRC_VERSION_AR_RELEASE_MAJOR_VERSION) \
  || (CRC_AR_RELEASE_MINOR_VERSION != CRC_VERSION_AR_RELEASE_MINOR_VERSION)) 
  #error "CRC : Mismatch AUTOSAR Version in Crc_Version.c"
#endif

/* CRC Software Version Check */
#if((CRC_SW_MAJOR_VERSION != CRC_VERSION_SW_MAJOR_VERSION) \
  || (CRC_SW_MINOR_VERSION != CRC_VERSION_SW_MINOR_VERSION))
  #error "CRC : Mismatch Software Version in Crc_Version.c"
#endif

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
