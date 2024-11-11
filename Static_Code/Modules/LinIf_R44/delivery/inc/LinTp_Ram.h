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
**  SRC-MODULE: LinTp_Ram.h                                                   **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : Header file for LinIf_Ram.c                                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision      Date           By                 Description                **
********************************************************************************
** 1.0.6         17-Oct-2022    KhaLN1             #CP44-563                  **
** 1.0.3         17-Sep-2021    DuyNGB             R44-Redmine #20121         **
** 1.0.1         20-Apr-2021    LongTQB            R44-Redmine #17195         **
** 1.0.0         22-Dec-2020    SJ Kim             Initial version            **
*******************************************************************************/

#ifndef LINTP_RAM_H
#define LINTP_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "LinTp_PCTypes.h"            /* LinTp pre compile header file */
#include "LinTp.h"                    /* LinTp APIs header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: LinTp_SUD_MACRO_005 */
/*
 * AUTOSAR specification version information
 */
#define LINTP_RAM_AR_RELEASE_MAJOR_VERSION    (LINIF_AR_RELEASE_MAJOR_VERSION)
#define LINTP_RAM_AR_RELEASE_MINOR_VERSION    (LINIF_AR_RELEASE_MINOR_VERSION)
#define LINTP_RAM_AR_RELEASE_REVISION_VERSION (LINIF_AR_RELEASE_REVISION_VERSION)

/*
 * File version information
 */
#define LINTP_RAM_SW_MAJOR_VERSION  (LINIF_SW_MAJOR_VERSION)
#define LINTP_RAM_SW_MINOR_VERSION  (LINIF_SW_MINOR_VERSION)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if(LINTP_SUPPORT == STD_ON)
#define LINTP_START_SEC_VAR_NO_INIT_8
#include "MemMap.h"
/* Global Array for LinTp Channel RAM Data */
/* polyspace-begin MISRA-C3:8.11 [To fix:Low] "size of array is determined by configuration, will be optimized later" */
extern VAR(LinTp_ChannelRamData, LINTP_VAR_NOINIT)LinTp_GaaChannelRamData[LINIF_TP_CHANNELS];
/* polyspace-end MISRA-C3:8.11 [To fix:Low] "size of array is determined by configuration, will be optimized later" */
#define LINTP_STOP_SEC_VAR_NO_INIT_8
#include "MemMap.h"

/* Extern definitions */
#define LINTP_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store status of LIN Interface */
extern VAR (boolean, LINTP_VAR) LinTp_GblInitSts;
#define LINTP_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define LINTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global pointer to hold first channel data structure address */
extern P2CONST(LinTp_ChannelInfo, AUTOMATIC, LINTP_CONST)
  LinTp_GpFirstChannel;
#define LINTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define LINTP_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Array for N_As, N_Cs/N_Cr Timers for all the channels */
extern VAR(uint16, LINTP_VAR) LinTp_GaaTimers
  [LINIF_TP_CHANNELS][LINTP_THREE];
#define LINTP_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#endif
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* LINTP_RAM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
