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
**  SRC-MODULE: CanSM_CanIf.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of callback functions and their functionality.      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.0.7     03-Feb-2023   HieuTM8        #CP44-1630                          **
** 1.0.1     14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306           **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/
/* @Trace: CanSM_SUD_FILE_001  */
#ifndef CANSM_CANIF_H
#define CANSM_CANIF_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM_Types.h"
#include "CanSM_InternalTypes.h"            /* CanSM PCTypes header file */
/* @Trace: CanSM_SUD_DATATYPE_003 CanSM_SUD_DATATYPE_004 */
#include "Can_GeneralTypes.h"	  /* Can_GeneralTypes header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: CanSM_SUD_MACRO_002  */
/* AUTOSAR Specification Version Information */
#define CANSM_CANIF_H_AR_RELEASE_MAJOR_VERSION         0x04u
#define CANSM_CANIF_H_AR_RELEASE_MINOR_VERSION         0x04u
#define CANSM_CANIF_H_AR_RELEASE_REVISION_VERSION      0x00u

/* Software Version Information */
#define CANSM_CANIF_H_SW_MAJOR_VERSION                 0x01u
#define CANSM_CANIF_H_SW_MINOR_VERSION                 0x00u

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                Function Prototypes                                         **
*******************************************************************************/

/* extern declaration for CanSM*/
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_ControllerBusOff(VAR(uint8,CANSM_VAR) Controller);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern declaration for CanSM_ConfirmPnAvailiability */
#if (STD_ON == CANSM_PNC_AVAILABILITY)
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_ConfirmPnAvailability(VAR(uint8,CANSM_VAR) Transceiver);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif

/* extern declaration for CanSM_ControllerModeIndication */
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_ControllerModeIndication(VAR(uint8,CANSM_VAR) Controller,
  VAR(Can_ControllerStateType,CANSM_VAR) ControllerMode);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern declaration for CanSM_TransceiverModeIndication */
#if (STD_ON == CANSM_CANTRCV_SUPPORT)
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_TransceiverModeIndication(VAR(uint8,CANSM_VAR) Transceiver,
  VAR(CanTrcv_TrcvModeType,CANSM_VAR) TransceiverMode);

#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif /* End of #if (STD_ON == CANSM_CANTRCV_SUPPORT) */

/* Extern for CanSM_TxTimeoutException */
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void, CANSM_CODE) CanSM_TxTimeoutException(VAR(NetworkHandleType,CANSM_VAR) Channel);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */

/* extern declaration for CanSM_CheckTransceiverWakeFlagIndication */
#if((STD_ON == CANSM_CANTRCV_SUPPORT)&&(STD_ON == CANSM_PNC_AVAILABILITY))
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void,CANSM_CODE) CanSM_CheckTransceiverWakeFlagIndication(VAR(uint8,CANSM_VAR) Transceiver);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif /* end if (STD_ON == CANSM_CANTRCV_SUPPORT) */

/* extern declaration for CanSM_ClearTrcvWufFlagIndication */
#if((STD_ON == CANSM_CANTRCV_SUPPORT)&&(STD_ON == CANSM_PNC_AVAILABILITY))
#define CANSM_START_SEC_CODE
#include "MemMap.h" /* Memmap header file */
extern FUNC(void,CANSM_CODE) CanSM_ClearTrcvWufFlagIndication(VAR(uint8,CANSM_VAR) Transceiver);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */
#endif /* end if (STD_ON == CANSM_CANTRCV_SUPPORT) */

#endif /* End of ifndef CANSM_CANIF_H */

/*******************************************************************************
**                   End of File                                              **
*******************************************************************************/

