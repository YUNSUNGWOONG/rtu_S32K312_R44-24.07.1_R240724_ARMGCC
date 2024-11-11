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
**  SRC-MODULE: LinTrcv_ModeCtrl.h                                            **
**                                                                            **
**  TARGET    :   MC33661                                                     **
**                                                                            **
**  PRODUCT   : AUTOSAR LIN Transceiver Driver                                **
**                                                                            **
**  PURPOSE   : Header file of LinTrcv_ModeCtrl.c                             **
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
** 1.0.2          17-May-2022           DuyNHP2          R44-Redmine #20124   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

#ifndef LINTRCV_MODECTRL_H
#define LINTRCV_MODECTRL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinTrcv_Ram.h"        /* LIN Transceiver Driver RAM header file */
#if (STD_ON == LINTRCV_TIMER_TYPE)
#include "Tm.h"                              /* Tm header file */
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(Dio_LevelType, LINTRCV_CODE) LinTrcv_ReadDioConfigType(VAR (
               LinTrcv_DioConfigType, LINTRCV_VAR) DioConfigType);
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTRCV_CODE) LinTrcv_WriteDioConfigType
                         (VAR(LinTrcv_DioConfigType, LINTRCV_VAR) DioConfigType,
                          Dio_LevelType level);
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTRCV_CODE) LinTrcv_WaitForChangeMode
                     (VAR (uint8, LINTRCV_VAR) LulWaitCount);
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTRCV_CODE) LinTrcv_SetNormalMode
                                (VAR (uint8, LINTRCV_VAR) LucLinNetwork);
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTRCV_CODE) LinTrcv_SetSleepMode
                                (VAR (uint8, LINTRCV_VAR) LucLinNetwork);
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTRCV_CODE) LinTrcv_SetStandByMode
                                (VAR (uint8, LINTRCV_VAR) LucLinNetwork);
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTRCV_CODE) LinTrcv_SetMode
                                 (VAR (uint8, LINTRCV_VAR) LucLinNetwork,
                       VAR (LinTrcv_TrcvModeType, LINTRCV_VAR) LddOpMode,
               VAR (LinTrcv_TrcvModeType, LINTRCV_VAR) LddCurrentOpMode);
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

#endif /* LINTRCV_MODECTRL_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
