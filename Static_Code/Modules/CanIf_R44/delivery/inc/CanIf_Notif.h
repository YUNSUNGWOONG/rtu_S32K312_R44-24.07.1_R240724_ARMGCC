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
**  SRC-MODULE: CanIf_Notif.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Header file of CanIf_Notif.c                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
*******************************************************************************/
/*******************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0    29-Feb-2024    Jh Yang        #CP44-2947                          **
** 1.0.5    30-Jun-2022    HieuTM8        #CP44-130                           **
** 1.0.1    22-Sep-2021    HieuTM8        #20891                              **
** 1.0.0    21-Dec-2020    SJ Kim         Initialization                      **
*******************************************************************************/

#ifndef CANIF_NOTIF_H
#define CANIF_NOTIF_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_Tx.h"              /* Tx Interface header file */
#include "CanIf_Cbk.h"             /* Call-back header file */
#include "CanIf.h"                 /* Call-back header file */
#include "CanIf_Ram.h"             /* Ram header file */
#include "CanIf_PCTypes.h"         /* Pre-compile time header file */
#include "CanIf_IntTypes.h"        /* Pre-compile time header file */
#include "CanSM_CanIf.h"             /* CAN State Manager call back header file */
#if (STD_ON == CANIF_WAKEUP_SUPPORT)
#include "EcuM.h"              /* EcuM call back header file */
#endif
#include "SchM_CanIf.h"            /* SchM CanIf Header file */
#include "CanIf_Error.h"           /* DET Header file */
#include "CanIf_UserInc.h"         /* CanIf User included header file */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_NOTIF_AR_RELEASE_MAJOR_VERSION       4
#define CANIF_NOTIF_AR_RELEASE_MINOR_VERSION       4
#define CANIF_NOTIF_AR_RELEASE_REVISION_VERSION    0

/* Software Version Information */
#define CANIF_NOTIF_SW_MAJOR_VERSION       1
#define CANIF_NOTIF_SW_MINOR_VERSION       1
#define CANIF_NOTIF_SW_REVISION_VERSION    0
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (STD_ON == CANIF_CTRL_WAKEUP_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE)CanIf_CanCheckwakeupService (
    P2CONST(CanIf_WakeupSourceInfoType, AUTOMATIC, CANIF_CONST) ptrWkpSource);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE)CanIf_TrcvCheckwakeupService (
    P2CONST(CanIf_WakeupSourceInfoType, AUTOMATIC, CANIF_CONST) ptrWkpSource);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_ControllerBusOff (
                                             VAR(uint8, CANIF_VAR) ControllerId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CANIF_NOTIF_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
