/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanNM_IntFunc.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Network Management Protocol                       **
**                                                                            **
**  PURPOSE   : Provision for CanNm Internal Function Header                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision     Date          By               Description                    **
********************************************************************************
** 1.1.5        28-Apr-2023   NamNT1           CP44 #1725                     **
** 1.1.4        31-Jan-2023   NamNT1           CP44 #1151                     **
** 1.1.1        07-Oct-2022   NamNT1           CP44 #785, #786, #610, #838,   **
**                                             #887, #842                     **
** 1.0.2.1      20-Jun-2022   SM Kwon          CP44-120                       **
** 1.0.0        16-Dec-2020   SHKim            Initial Version                **
*******************************************************************************/

#ifndef CANNM_INTFUNC_H
#define CANNM_INTFUNC_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanNm_Globals.h"            /* CanNm RAM Header File */
#include "CanNm_IntTypes.h"           /* CanNm configuration header */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR specification version information */
#define CANNM_INTFUNC_AR_RELEASE_MAJOR_VERSION         (0x04u)
#define CANNM_INTFUNC_AR_RELEASE_MINOR_VERSION         (0x04u)
#define CANNM_INTFUNC_AR_RELEASE_REVISION_VERSION      (0x00u)

/* CANNM software version information */
#define CANNM_INTFUNC_SW_MAJOR_VERSION         (0x01u)
#define CANNM_INTFUNC_SW_MINOR_VERSION         (0x02u)
#define CANNM_INTFUNC_SW_PATCH_VERSION         (0x00u)

/*******************************************************************************
**                      Macroes                                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define CANNM_START_SEC_CODE
#include "MemMap.h"

#if (CANNM_COM_USERDATA_SUPPORT == STD_ON)
extern FUNC(void, CANNM_CODE) CanNm_IntCollectTxData(uint32 canNmChannelIndex);
#endif /* #if (CANNM_COM_USERDATA_SUPPORT == STD_ON) */

extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_IntGetChannelIndexFromTransmitHandleId
  (PduIdType canNmTransmitHandleId, P2VAR(uint32, AUTOMATIC, CANNM_VAR) ptrCanNmChannelIndex);

extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_IntGetChannelIndexFromNmHandleId
  (NetworkHandleType nmHandleId, P2VAR(uint32, AUTOMATIC, CANNM_VAR) ptrCanNmChannelIndex);
   
extern FUNC(void, CANNM_CODE) CanNm_IntUpdateERA
  (uint32 canNmChannelIndex, P2CONST(uint8, AUTOMATIC, CANNM_CONST) ptrPnInfo);
  
extern FUNC(void, CANNM_CODE) CanNm_IntUpdateEIRA
  (P2CONST(uint8, AUTOMATIC, CANNM_CONST) ptrPnInfo);

extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_IntCanIfTransmit
  (uint32 canNmChannelIndex);

extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_IntGetChannelIdFromCanNmTxConfirmationHandleId(
  PduIdType canNmTxConfirmationHandleId,
  P2VAR(uint32, AUTOMATIC, CANNM_VAR) ptrCanNmChannelIndex);
  
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_IntGetChannelIdFromCanNmRxIndicationHandleId(
    PduIdType RxPduId,
    P2VAR(uint32, AUTOMATIC, CANNM_VAR) ptrCanNmChannelIndex);

extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_IntGetChannelIdFromTriggerTransmitHandleId(
  PduIdType canNmTriggerTransmitHandleId,
  P2VAR(uint32, AUTOMATIC, CANNM_VAR) ptrCanNmChannelIndex);

#if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
extern FUNC(CANNM_RX_HANDLING_METHOD, CANNM_CODE) CanNm_IntGetRxHandlingMethod(
  uint32 canNmChannelIndex,
  P2CONST(uint8, AUTOMATIC, CANNM_APPL_DATA) ptrArrayRxPdu);
#endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */

/* CanNm shall not perform transmission error handling */
#if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF))
#if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
extern FUNC(void, CANNM_CODE) CanNm_IntProcessMsgTimeOutTime(void);
#endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */
#endif /* #if((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)) */

#if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
extern FUNC(boolean, CANNM_CODE) CanNm_IntGetNmStateTypeFromCanNmModeState(
  CanNm_ModeState canNmModeState,
  P2VAR(Nm_StateType, AUTOMATIC, CANNM_VAR) ptrNmState);
#endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */

#if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON)
extern FUNC(void, CANNM_CODE) CanNm_IntStateChangeNotification(
  uint32 canNmChannelIndex,
  CanNm_ModeState canNmPreviousState,
  CanNm_ModeState canNmCurrentState);
#endif /* #if (CANNM_STATE_CHANGE_INDICATE_ENABLED == STD_ON) */

extern FUNC(void, CANNM_CODE) CanNm_IntNetworkModeEntry(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntEntryRepeatMessageState(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntEntryNormalOperationState(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntEntryReadySleepState(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntEntryPrepareBusSleepMode(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntEntryBusSleepMode(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntExitNetworkMode(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntExitRepeatMessageState(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntExitNormalOperationState(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntExitReadySleepState(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntExitPrepareBusSleepMode(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntPrepareBusSleepMode(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntReadySleepState(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntNormalOperationState(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntRepeatMessageState(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_IntProcessEIRATimer(void);

extern FUNC(void, CANNM_CODE) CanNm_IntProcessERATimer(void);

extern FUNC(void, CANNM_CODE) CanNm_IntProcessNmMessage(void);

extern FUNC(void, CANNM_CODE) CanNm_Memset(uint8 *bufferptr, uint8 value, uint32 size);

extern FUNC(void, CANNM_CODE) CanNm_Memcpy (uint8 *bufferDest, const uint8 *bufferSource, uint32 byteNumber);

#if (CANNM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
extern FUNC(void, CANNM_CODE) CanNm_CarWakeupProcess(
        P2CONST(PduInfoType, AUTOMATIC, CANNM_APPL_DATA) PduPtr,
        P2VAR(CanNm_Channel, AUTOMATIC, CANNM_VAR) ptrChannel,
        P2CONST(CanNm_StaticChannel, AUTOMATIC, CANNM_CONST) ptrStaticChannel);
#endif /* #if (CANNM_CAR_WAKE_UP_RX_ENABLED == STD_ON) */

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_ERA_CALC_ENABLED == STD_ON))
extern FUNC(void, CANNM_CODE) CanNm_InitERA(uint32 canNmChannelIndex);
#endif

#if ((CANNM_GLOBAL_PN_SUPPORT == STD_ON) && (CANNM_PN_EIRA_CALC_ENABLED == STD_ON))
extern FUNC(void, CANNM_CODE) CanNm_InitEIRA(void);
#endif

extern FUNC(void, CANNM_CODE) CanNm_ExitCurrentState(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_EntryNextState(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_ImplementCurrentState(uint32 canNmChannelIndex);

extern FUNC(void, CANNM_CODE) CanNm_RxIndicationSetInternalStatus(uint32 canNmChannelIndex);

#if ((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON))
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_RequestBusSynTransmit(
		uint32 canNmChannelIndex,
		P2CONST(PduInfoType, AUTOMATIC, CANNM_CONST) structPduInfoType);
#endif

#define CANNM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CANNM_INTFUNC_H */

/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
