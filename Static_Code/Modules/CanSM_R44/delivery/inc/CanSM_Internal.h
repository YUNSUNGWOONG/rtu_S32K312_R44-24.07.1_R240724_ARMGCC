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
**  SRC-MODULE: CanSM_Internal.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AAUTOSAR CAN State Manager Module                             **
**                                                                            **
**  PURPOSE   : Header file for CanSM_MainFunction related API                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By             Description                       **
********************************************************************************
** 1.0.9_HF1   23-Feb-2024   MU Kim         CP44-2851                         **
** 1.0.4       10-Oct-2022   HieuTM8        CP44-876                          **
** 1.0.3       25-Jul-2022   HieuTM8        CP44-511                          **
** 1.0.1       14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306         **
** 1.0.0       04-Dec-2020   SMKwon         Initial Version                   **
*******************************************************************************/
/* @Trace: CanSM_SUD_FILE_001  */
#ifndef CANSM_INTERNAL_H
#define CANSM_INTERNAL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM.h"                /* CanSM header file */
#include "CanIf.h"                /* CanIf header file */
/* @Trace: CanSM_SUD_DATATYPE_005 */
#include "ComM.h"                 /* ComM header file */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: CanSM_SUD_MACRO_005  */
/* AUTOSAR Specification Version Information */
#define CANSM_INTERNAL_H_AR_RELEASE_MAJOR_VERSION         0x04u
#define CANSM_INTERNAL_H_AR_RELEASE_MINOR_VERSION         0x04u
#define CANSM_INTERNAL_H_AR_RELEASE_REVISION_VERSION      0x00

/* Software Version Information */
#define CANSM_INTERNAL_H_SW_MAJOR_VERSION                 0x01u
#define CANSM_INTERNAL_H_SW_MINOR_VERSION                 0x00u


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/* extern for CanSM_GetCurrentComModeDetCheck */
#define CANSM_START_SEC_CODE
#include "MemMap.h"/* Memmap header file */
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetCurrentComModeDetCheck(
VAR(NetworkHandleType,CANSM_VAR) network, P2CONST(ComM_ModeType, AUTOMATIC,CANSM_APPL_DATA) ComM_ModePtr);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"/* Memmap header file */

/* extern for CanSM_GetCurrentComModeDetCheck */
#define CANSM_START_SEC_CODE
#include "MemMap.h"/* Memmap header file */
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_RequestComModeDetCheck(VAR(NetworkHandleType,CANSM_VAR)  network);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"/* Memmap header file */

/* extern for CanSM_NoCommunication */
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_NoCommunication(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_SilentCommunication */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_SilentCommunication(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_FullCommunication */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_FullCommunication(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_BORStart */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_BORStart(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_BORStart_FULL_T_BUSOFF */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_BORStart_FULL_T_BUSOFF(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_BORStart_FULL_TX_OFF */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_BORStart_FULL_TX_OFF(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_NoToFullCommRequested_PREFULL_CC_ONLINE */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_NoToFullCommRequested_PREFULL_CC_ONLINE(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_BORWait */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_BORWait(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_CheckBusOff */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_CheckBusOff(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_DeInitPnNotSupported */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_DeInitPnNotSupported(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_DeInitPnSupported */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
#if (STD_ON == CANSM_PNC_AVAILABILITY)
extern FUNC(void, CANSM_CODE) CanSM_DeInitPnSupported(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#endif
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_NoToFullCommRequested */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_NoToFullCommRequested(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_SilentToFullCommRequested */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_SilentToFullCommRequested(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */


/* extern for CanSM_TimeoutProcessing */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_TimeoutProcessing(VAR(NetworkHandleType,CANSM_VAR) networkHandle, Std_ReturnType result);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_SilentCommunication_BOR */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANSM_CODE) CanSM_SilentCommunication_BOR(VAR(NetworkHandleType,CANSM_VAR) networkHandle);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_SetBaudrateService */
#if (STD_ON == CANSM_SET_BAUDRATE_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_SetBaudrateService(VAR(NetworkHandleType,CANSM_VAR) networkHandle);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void,CANSM_CODE) CanSM_ChangeBaudrateEndFullCom(VAR(NetworkHandleType,CANSM_VAR) networkHandle);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void,CANSM_CODE) CanSM_ChangeBaudrateEndSilentCom(VAR(NetworkHandleType,CANSM_VAR) networkHandle);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif /* end if of (STD_ON == CANSM_SET_BAUDRATE_API) */

/* extern for CanSM_WakeUpValidation */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void,CANSM_CODE) CanSM_WakeUpValidation(VAR(NetworkHandleType,CANSM_VAR) networkHandle);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_WakeUpToFullComRequested */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void,CANSM_CODE) CanSM_WakeUpToFullComRequested(VAR(NetworkHandleType,CANSM_VAR) networkHandle);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_WakeUpToFullComRequested_PREFULL_CC_ONLINE */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(Std_ReturnType,CANSM_CODE) CanSM_WakeUpToFullComRequested_PREFULL_CC_ONLINE(VAR(NetworkHandleType,CANSM_VAR) networkHandle);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_FullToSilentCommRequested */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_FullToSilentCommRequested(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_GetTxConfirmationState */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
#if (STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING)
extern FUNC(CanIf_NotifStatusType, CANSM_CODE) CanSM_GetTxConfirmationState(
  VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#endif
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_ClearTrcvWuf */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_ClearTrcvWuf(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_CheckTrcvWuf */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_CheckTrcvWuf(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_SetCanControllerMode */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetCanControllerMode(
  VAR(NetworkHandleType,CANSM_VAR) networkHandle, VAR(Can_ControllerStateType,CANSM_VAR) LenMode);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern for CanSM_SetCanTrcvMode */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetCanTrcvMode(VAR(NetworkHandleType,CANSM_VAR) networkHandle,
 VAR(CanTrcv_TrcvModeType,CANSM_VAR) LenMode);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */


#if(STD_ON == CANSM_SET_BAUDRATE_API)
/* extern for CanSM_SetBaudrateDirect */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_SetBaudrateDirect(VAR(NetworkHandleType,CANSM_VAR) networkHandle);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif

/* extern for CanSM_EBusOffPassive */
#define CANSM_START_SEC_CODE
#include "MemMap.h"               /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_EBusOffPassive(VAR(NetworkHandleType,CANSM_VAR) networkHandle);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

#endif /* CANSM_MAIN_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

