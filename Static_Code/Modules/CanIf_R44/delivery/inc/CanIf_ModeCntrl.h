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
**  SRC-MODULE: CanIf_ModeCntrl.h                                             **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Header file of CanIf_ModeCntrl.c                              **
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
** 1.1.0     29-Feb-2024   Jh Yang        #CP44-2947                          **
** 1.0.14    13-Jun-2023   HieuTM8        #CP44-2236                          **
** 1.0.12    12-Dec-2022   HieuTM8        #CP44-1254                          **
** 1.0.10    27-Oct-2022   HieuTM8        #CP44-1008                          **
** 1.0.5     30-Jun-2022   HieuTM8        #CP44-130                           **
** 1.0.4     09-May-2022   Jiwon Oh       #26814,#27128                       **
** 1.0.1     22-Sep-2021   HieuTM8        #20891                              **
** 1.0.0     21-Dec-2020   SJ Kim         Initialization                      **
*******************************************************************************/

#ifndef CANIF_MODECNTRL_H
#define CANIF_MODECNTRL_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_Tx.h"            /* Tx Interface header file */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_MODECNTRL_AR_RELEASE_MAJOR_VERSION       4
#define CANIF_MODECNTRL_AR_RELEASE_MINOR_VERSION       4
#define CANIF_MODECNTRL_AR_RELEASE_REVISION_VERSION    0

/* Software Version Information */
#define CANIF_MODECNTRL_SW_MAJOR_VERSION       1
#define CANIF_MODECNTRL_SW_MINOR_VERSION       1
#define CANIF_MODECNTRL_SW_REVISION_VERSION    0
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC (void, CANIF_CODE) CanIf_SetTxOrRxSts (VAR(uint8, CANIF_VAR) ControllerId,
                      VAR(CanIf_PduModeType, CANIF_VAR) pduMode);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_ControllerModeIndicationProcessing (
                        VAR(uint8, CANIF_VAR) ControllerId,
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
                        VAR(Can_ControllerStateType, CANIF_VAR) ControllerMode);
#else
                        VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode);
#endif
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_DETControllerModeIndication (
                        VAR(uint8, CANIF_VAR) ControllerId,
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
                        VAR(Can_ControllerStateType, CANIF_VAR) ControllerMode);
#else
                        VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode);
#endif
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_DETSetControllerMode (
                       VAR(uint8, CANIF_VAR) ControllerId,
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
                        VAR(Can_ControllerStateType, CANIF_VAR) ControllerMode);
#else
                        VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode);
#endif	
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define CANIF_START_SEC_CODE
#include "MemMap.h"
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
extern FUNC(Std_ReturnType, CANIF_CODE)CanIf_PreSetControllerMode (
#else
extern FUNC(Can_ReturnType, CANIF_CODE)CanIf_PreSetControllerMode (
#endif
                        VAR(uint8, CANIF_VAR) ControllerId,
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
            P2VAR(Can_ControllerStateType, AUTOMATIC, CANIF_VAR) ControllerMode);
#else
            P2VAR(CanIf_ControllerModeType, AUTOMATIC, CANIF_VAR) ControllerMode);
#endif	
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
extern FUNC(Std_ReturnType, CANIF_CODE)CanIf_SetControllerModeProcessing (
#else
extern FUNC(Can_ReturnType, CANIF_CODE)CanIf_SetControllerModeProcessing (
#endif
                        VAR(uint8, CANIF_VAR) ControllerId,
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
            VAR(Can_ControllerStateType, CANIF_VAR) ControllerMode);
#else
            VAR(CanIf_ControllerModeType, CANIF_VAR) ControllerMode);
#endif	
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
  ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
   (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetControllerModeService (
                               VAR(uint8, CANIF_VAR) Controller,
                               VAR(Can_ControllerStateType, CANIF_VAR) CanMode);
#else
extern FUNC(Can_ReturnType, CANIF_CODE) CanIf_SetControllerModeService (
							   VAR(uint8, CANIF_VAR) Controller,
                               VAR(Can_StateTransitionType, CANIF_VAR) CanMode);
#endif
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CANIF_MODE_CNTRL_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
