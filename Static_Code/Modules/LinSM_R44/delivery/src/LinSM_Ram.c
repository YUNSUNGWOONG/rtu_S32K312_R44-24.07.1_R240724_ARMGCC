/* polyspace +1 MISRA2012:1.1 [Justified:Low] "This rule is checked manually  and has no impact" */
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
**  SRC-MODULE: LinSM_Ram.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinSM Module                                          **
**                                                                            **
**  PURPOSE   : This file contains the global definitions                     **
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
** 1.0.5          03-Aug-2022           KhaLN1           #CP44-514            **
** 1.0.2          17-Sep-2021           DuyNGB           R44-Redmine #20123   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinSM_Ram.h"            /* LinSM Ram header file */

/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/

#define LINSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Array to hold the channel information */
/* polyspace-begin VARIABLE:ALL [Not a defect] "This variable do not interfere with each other." */
VAR(LinSM_Channel, LINSM_VAR) LinSM_GaaChannel[LINSM_NO_OF_CHANNELS];
#define LINSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (LINSM_DEV_ERROR_DETECT == STD_ON)
#define LINSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to hold the LinSM Module state */
VAR(boolean, LINSM_VAR) LinSM_GblInitStatus;
#define LINSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif /* End of if (LINSM_DEV_ERROR_DETECT == STD_ON) */

#define LINSM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Global variable to hold the current channel communication state */
VAR(LinSM_ModeType, LINSM_VAR)
LinSM_GaaCurrentState[LINSM_NO_OF_CHANNELS];
#define LINSM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define LINSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Array to hold the channel information */
VAR(LinSM_SubStateOfFullCom, LINSM_VAR) LinSM_CurrentSubState[LINSM_NO_OF_CHANNELS];
/* polyspace-end VARIABLE:ALL [Not a defect] "This variable do not interfere with each other." */
#define LINSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
