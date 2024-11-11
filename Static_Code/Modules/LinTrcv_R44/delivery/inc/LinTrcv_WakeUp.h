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
**  SRC-MODULE: LinTrcv_WakeUp.h                                              **
**                                                                            **
**  TARGET    : MC33661                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR LIN Transceiver Driver                                **
**                                                                            **
**  PURPOSE   : Header file of LinTrcv_WakeUp.c                               **
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
** 1.0.3          03-Aug-2022           KhaLN1           #CP44-705            **
** 1.0.2          17-May-2022           DuyNHP2          R44-Redmine #20124   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

#ifndef LINTRCV_WAKEUP_H
#define LINTRCV_WAKEUP_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinTrcv_Ram.h"                   /* Ram header file */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if(STD_ON == LINTRCV_DEV_ERROR_DETECT)
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINTRCV_CODE) LinTrcv_DetSetWakeupMode
                                (VAR (uint8, LINTRCV_VAR) LucLinNetwork);
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINTRCV_CODE) LinTrcv_DetCheckWakeup
                                (VAR (uint8, LINTRCV_VAR) LucLinNetwork);
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, LINTRCV_CODE) LinTrcv_DetGetBusWuReason
   (VAR (uint8, LINTRCV_VAR) LucLinNetwork,
    P2CONST(LinTrcv_TrcvWakeupReasonType, AUTOMATIC, LINTRCV_APPL_CONST) \
                                                                     LddReason);
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (STD_ON == LINTRCV_DEV_ERROR_DETECT) */

#endif /* LINTRCV_WAKEUP_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
