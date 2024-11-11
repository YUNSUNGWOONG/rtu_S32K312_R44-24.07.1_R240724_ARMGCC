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
**  SRC-MODULE: LinTrcv_Ram.h                                                 **
**                                                                            **
**  TARGET    : MC33661                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR LIN Transceiver Driver                                **
**                                                                            **
**  PURPOSE   : Implementation of Global RAM variables                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                  By               Description          **
********************************************************************************
** 1.0.7          08-Apr-2024           YB Song          #CP44-7310           **
** 1.0.2          17-May-2022           DuyNHP2          R44-Redmine #20124   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

#ifndef LINTRCV_RAM_H
#define LINTRCV_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinTrcv_PCTypes.h"   /* LIN Transceiver Driver Types header file */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define LINTRCV_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* @Trace: LinTrcv_SUD_GLOBALVAR_001 */
/* Global variable to hold the initialization status of  LinTrcv Module */
extern VAR(boolean, LINTRCV_VAR) LinTrcv_GblInitStatus;
#define LINTRCV_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define LINTRCV_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: LinTrcv_SUD_GLOBALVAR_002 */
/* Global array for LinTrcv Channel Ram variables */
extern VAR(LinTrcv_NetworkRamData, LINTRCV_VAR_NOINIT) LinTrcv_GaaNetworkRamData[LINTRCV_NUM_OF_NETWORKS];
#define LINTRCV_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* LINTRCV_RAM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/