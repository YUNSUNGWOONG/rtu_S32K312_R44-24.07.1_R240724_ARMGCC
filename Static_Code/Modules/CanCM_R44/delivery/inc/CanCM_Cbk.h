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
**  SRC-MODULE: CanCM_Cbk.h                                                   **
**                                                                            **
**  TARGET    : General CAN Communication Manager                             **
**                                                                            **
**  PRODUCT   : AUTOEVER CAN Communication Manager Module                     **
**                                                                            **
**  PURPOSE   : Header file of CanCM_Cbk.c                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.0.3.1   29-Jun-2022   NhatTD2          CP44-135                          **
** 1.0.2     23-Feb-2022   HieuTM8          Redmine #20448                    **
** 1.0.1     22-Sep-2021   LinhTT36         Redmine #20380                    **
** 1.0.0     22-Dec-2020   SJ Kim           Initial Version                   **
*******************************************************************************/
#ifndef CANCM_CBK_H
#define CANCM_CBK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanCM.h"


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
/* Everything else goes here */
extern FUNC(void, CANCM_CODE) CanCM_ComModeIndication (
  NetworkHandleType channelIdComm,
  ComM_ModeType commState);
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
