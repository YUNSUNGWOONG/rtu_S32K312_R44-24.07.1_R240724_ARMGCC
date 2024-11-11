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
**  SRC-MODULE: LinSM_Ram.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinSM Module                                          **
**                                                                            **
**  PURPOSE   : This file contains the structure definitions                  **
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
** 1.0.5          04-Aug-2022           KhaLN1           #CP44-514            **
** 1.0.2          17-Sep-2021           DuyNGB           R44-Redmine #20123   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

#ifndef LINSM_RAM_H
#define LINSM_RAM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinSM.h"                /* LinSM header file */

/*******************************************************************************
**                            Global Data                                     **
*******************************************************************************/
typedef struct
{
  #if (LINSM_MASTER_SUPPORT == STD_ON)
  /* Variable to hold the current schedule */
  LinIf_SchHandleType ddCurrSchedule;
  /* Variable to hold the requested schedule */
  LinIf_SchHandleType ddReqSchedule;
  #endif

  #if (LINSM_TIMEOUT_FUNC == STD_ON)
  /* Variable to hold the mode request timer value */
  uint16 usModeReqTimerCount;
  /* Variable to hold the schedule request timer value */
  uint16 usScheduleReqTimerCount;
  #endif
  /* Variable to hold Api request status flags */
  uint8 ucModeScheduleReqStatus;

  /* Variable to hold the Mode Request Repetition Max value */
  uint8 ucModeRequestRepetitionCount;

  #if (LINSM_SLAVE_SUPPORT == STD_ON)
  /* Variable to hold the Silence After Wakeup Timeout value */
  uint16 ucSilenceAfterWakeupTimeoutCount;
  #endif

} LinSM_Channel;
/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/

#define LINSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Array to hold the channel information */
/* polyspace +3 MISRA-C3:8.11 [Justified:Low] "size of array is determined by configuration" */
extern VAR(LinSM_Channel, LINSM_VAR) LinSM_GaaChannel[LINSM_NO_OF_CHANNELS];
#define LINSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (LINSM_DEV_ERROR_DETECT == STD_ON)
#define LINSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to hold the LinSM Module state */
extern VAR(boolean, LINSM_VAR) LinSM_GblInitStatus;
#define LINSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif /* End of if (LINSM_DEV_ERROR_DETECT == STD_ON) */

#define LINSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Global variable to hold the current channel communication state */
/* polyspace-begin MISRA-C3:8.11 [Justified:Low] "size of array is determined by configuration" */
extern VAR(LinSM_ModeType, LINSM_VAR) LinSM_GaaCurrentState[LINSM_NO_OF_CHANNELS];
#define LINSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define LINSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Array to hold the channel information */
extern VAR(LinSM_SubStateOfFullCom, LINSM_VAR) LinSM_CurrentSubState[LINSM_NO_OF_CHANNELS];
/* polyspace-end MISRA-C3:8.11 [Justified:Low] "size of array is determined by configuration" */
#define LINSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif /* LINSM_RAM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
