/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanNm.h                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Network Management Protocol                       **
**                                                                            **
**  PURPOSE   : Main header file for CanNm.c                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.4     31-Jan-2023   NamNT1         CP44 #873                           **
** 1.1.3     16-Dec-2022   NamNT1         BUGCLASSIC-374, CP44-1326           **
** 1.1.1     07-Oct-2022   NamNT1         CP44 #785, #786, #610, #838, #842   **
**                                        #887                                **
** 1.1.0.0   28-Jul-2022   SM Kwon        R444 Redmine #29362, #29697         **
** 1.0.2.1   20-Jun-2022   SM Kwon        CP44-120                            **
** 1.0.0     16-Dec-2020   SHKim          Initial Version                     **
*******************************************************************************/

#ifndef CANNM_H
#define CANNM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "CanNm_Cfg.h"            /* Configuration header file */
/* @Trace: CanNm_SUD_DATATYPE_004 CanNm_SUD_DATATYPE_005 */
#include "NmStack_Types.h"        /* Nm Interface type definitions header */
/* @Trace: CanNm_SUD_DATATYPE_001 CanNm_SUD_DATATYPE_002 CanNm_SUD_DATATYPE_003 */
#include "ComStack_Types.h"       /* Com Interface type definitions header */
#include "CanNm_IntTypes.h"        /* CanNm Internal Types header file */
#if (CANNM_POSTBUILD_SUPPORTED == STD_ON)
#include "CanNm_PBCfg.h"            /* Postbuild Configuration header file */
#endif /* #if (CANNM_POSTBUILD_SUPPORTED == STD_ON) */
/* @Trace: SRS_BSW_00348 SRS_BSW_00353 SRS_BSW_00361 SRS_BSW_00301*/
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANNM_H_AR_RELEASE_MAJOR_VERSION         (0x04u)
#define CANNM_H_AR_RELEASE_MINOR_VERSION         (0x04u)
#define CANNM_H_AR_RELEASE_REVISION_VERSION      (0x00u)

/* CANNM software version information */
#define CANNM_H_SW_MAJOR_VERSION         (0x01u)
#define CANNM_H_SW_MINOR_VERSION         (0x02u)
#define CANNM_H_SW_PATCH_VERSION         (0x00u)
/*******************************************************************************
**                      Macro Definitions                                     **
*******************************************************************************/
#define CANNM_INSTANCE_ID                     ((uint8)0x00)

/* polyspace +1 MISRA2012:D4.9 [Justified:Low] "Use function like-macro for removing unused argument compiler warning" */
#define CANNM_UNUSED(x)                        do { \
                                                    if((uint32)(x) != \
                                                    (uint32)CANNM_ZERO) {} \
                                                  } while(0)
  
/* polyspace +1 MISRA2012:D4.9 [Justified:Low] "Use function like-macro for removing unused argument compiler warning" */
#define CANNM_UNUSED_PTR(x)                    do { \
                                                    if((x) != NULL_PTR) {} \
                                                  } while(0)

/* API Service Ids */
/* Service id for CanNm_Init */
#define CANNM_INIT_SID                            ((uint8)0x00)

/* Service id for CanNm_PassiveStartUp */
#define CANNM_PASSIVE_STARTUP_SID                 ((uint8)0x01)

/* Service id for CanNm_NetworkRequest */
#define CANNM_NETWORK_REQUEST_SID                 ((uint8)0x02)

/* Service id for CanNm_NetworkRelease */
#define CANNM_NETWORK_RELEASE_SID                 ((uint8)0x03)

/* Service id for CanNm_SetUserData */
#define CANNM_SET_USERDATA_SID                    ((uint8)0x04)

/* Service id for CanNm_GetUserData */
#define CANNM_GET_USERDATA_SID                    ((uint8)0x05)

/* Service id for CanNm_GetNodeIdentifier */
#define CANNM_GET_NODEIDENTIFIER_SID              ((uint8)0x06)

/* Service id for CanNm_GetLocalNodeIdentifier */
#define CANNM_GET_LOCALNODEIDENTIFIER_SID         ((uint8)0x07)

/* Service id for CanNm_RepeatMessageRequest */
#define CANNM_REPEAT_MESSAGEREQUEST_SID           ((uint8)0x08)

/* Service id for CanNm_GetPduData */
#define CANNM_GET_PDUDATA_SID                     ((uint8)0x0A)

/* Service id for CanNm_GetState */
#define CANNM_GET_STATE_SID                       ((uint8)0x0B)

/* Service id for CanNm_DisableCommunication */
#define CANNM_DISABLE_COMMUNICATION_SID           ((uint8)0x0C)

/* Service id for CanNm_EnableCommunication */
#define CANNM_ENABLE_COMMUNICATION_SID            ((uint8)0x0D)

/* Service id for CanNm_DeInit */
#define CANNM_DEINIT_SID                          ((uint8)0x10)

/* Service id for CanNm_MainFunction */
#define CANNM_MAINFUNCTION_SID                    ((uint8)0x13)

/* Service id for CanNm_ConfirmPnAvailability */
#define CANNM_CONFIRM_PNAVAILABILITY_SID          ((uint8)0x16)

/* Service id for CanNm_SetSleepReadyBit */
#define CANNM_SET_SLEEP_READYBIT_SID              ((uint8)0x17)

/* Service id for CanNm_TxConfirmation */
#define CANNM_TX_CONFIRMATION_SID                 ((uint8)0x40)

/* Service id for CanNm_TriggerTransmit */
#define CANNM_TRIGGER_TRANSMIT_SID                ((uint8)0x41)

/* Service id for CanNm_RxIndication */
#define CANNM_RX_INDICATION_SID                   ((uint8)0x42)

/* Service id for CanNm_Transmit */
#define CANNM_TRANSMIT_SID                        ((uint8)0x49)

/* Service id for CanNm_RequestBusSynchronization */
#define CANNM_REQUEST_BUSSYNCHRONIZATION_SID      ((uint8)0xC0)

/* Service id for CanNm_CheckRemoteSleepIndication */
#define CANNM_CHECK_REMOTESLEEPINDICATION_SID     ((uint8)0xD0)

/* Service id for CanNm_GetVersionInfo */
#define CANNM_GET_VERSIONINFO_SID                 ((uint8)0xF1)

/* Service id for CanNm_SetNetworkRequestReason */
#define CANNM_SET_NETWORK_REQUEST_REASON_SID      ((uint8)0xF2)

/* Service id for CanNm_GetNetworkRequestReason */
#define CANNM_GET_NETWORK_REQUEST_REASON_SID      ((uint8)0xF3)

/* @Trace: CanNm_SUD_MACRO_007 */
/* DET Error Codes */
#define CANNM_E_UNINIT                            ((uint8)0x01)
#define CANNM_E_INVALID_CHANNEL                   ((uint8)0x02)
#define CANNM_E_INVALID_PDUID                     ((uint8)0x03)
#define CANNM_E_NET_START_IND                     ((uint8)0x04)
#define CANNM_E_INIT_FAILED                       ((uint8)0x05)
#define CANNM_E_NETWORK_TIMEOUT                   ((uint8)0x11)
#define CANNM_E_PARAM_POINTER                     ((uint8)0x12)
#define CANNM_E_NOT_IN_BUS_SLEEP                  ((uint8)0x13)
#define CANNM_E_INVALID_REQUEST                   ((uint8)0x20)
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* @Trace: CanNm_SUD_MACRO_004 */
#define CANNM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANNM_CODE) CanNm_Init
  (P2CONST(CanNm_ConfigType, AUTOMATIC, CANNM_APPL_CONST) cannmConfigPtr);
  
extern FUNC(void, CANNM_CODE) CanNm_GetVersionInfo
           (P2VAR(Std_VersionInfoType, AUTOMATIC, CANNM_APPL_DATA) versioninfo);
  
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_PassiveStartUp
            (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle);

#if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF)
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_NetworkRequest
            (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle);
  
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_NetworkRelease
            (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle);
#endif /* #if(CANNM_PASSIVE_MODE_ENABLED == STD_OFF) */

#if (CANNM_COM_CONTROL_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_DisableCommunication
            (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle);
  
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_DisableCommunication_TimerisNotStopped
            (VAR(NetworkHandleType, CANNM_VAR)nmChannelHandle);

extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_EnableCommunication
            (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle);

extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_EnableCommunication_TimerisNotStarted
            (VAR(NetworkHandleType, CANNM_VAR)nmChannelHandle);
#endif /* #if (CANNM_COM_CONTROL_ENABLED == STD_ON) */

#if ((CANNM_USER_DATA_ENABLED == STD_ON) && (CANNM_PASSIVE_MODE_ENABLED == STD_OFF))
#if(CANNM_COM_USERDATA_SUPPORT == STD_OFF)
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_SetUserData
            (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
             P2CONST(uint8, AUTOMATIC, CANNM_APPL_CONST) nmUserDataPtr);

#endif /* #if ((CANNM_USER_DATA_ENABLED == STD_ON) && (CANNM_PASSIVE_MODE_ENABLED == STD_OFF)) */
#endif /* #if(CANNM_COM_USERDATA_SUPPORT == STD_OFF) */

#if (CANNM_USER_DATA_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetUserData
            (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
             P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmUserDataPtr);
#endif /* #if (CANNM_USER_DATA_ENABLED == STD_ON) */

extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetLocalNodeIdentifier
            (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
             P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmNodeIdPtr);
   
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetNodeIdentifier
            (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
             P2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmNodeIdPtr);
   
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_RepeatMessageRequest
            (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle);

#if ((CANNM_NODE_DETECTION_ENABLED == STD_ON) || (CANNM_USER_DATA_ENABLED == STD_ON))
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetPduData
            (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
             P2VAR(uint8,AUTOMATIC, CANNM_APPL_DATA) nmPduDataPtr);
#endif /* #if ((CANNM_NODE_DETECTION_ENABLED == STD_ON) || (CANNM_USER_DATA_ENABLED == STD_ON)) */

extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetState
            (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
             P2VAR(Nm_StateType, AUTOMATIC, CANNM_APPL_DATA) nmStatePtr,
             P2VAR(Nm_ModeType, AUTOMATIC, CANNM_APPL_DATA) nmModePtr);

#if ((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON))
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_RequestBusSynchronization
  (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle);
#endif /* #if ((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_BUS_SYNCHRONIZATION_ENABLED == STD_ON)) */

#if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_CheckRemoteSleepIndication
  (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
   P2VAR(boolean, AUTOMATIC, CANNM_APPL_DATA) nmRemoteSleepIndPtr);
#endif /* #if (CANNM_REMOTE_SLEEP_INDICATE_ENABLED == STD_ON) */

#if ((CANNM_COM_USERDATA_SUPPORT == STD_ON) || (CANNM_GLOBAL_PN_SUPPORT == STD_ON))
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_Transmit
  (PduIdType CanTxPduId, P2CONST(PduInfoType, AUTOMATIC,CANNM_APPL_CONST) PduInfoPtr);
#endif /* #if ((CANNM_COM_USERDATA_SUPPORT == STD_ON) || (CANNM_GLOBAL_PN_SUPPORT == STD_ON)) */

#if (CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_SetSleepReadyBit
            (VAR(NetworkHandleType, CANNM_VAR) nmChannelHandle,
             VAR(boolean, CANNM_VAR) nmSleepReadyBit);
#endif /* #if (CANNM_COORDINATOR_SYNC_SUPPORT == STD_ON) */

extern FUNC(void, CANNM_CODE) CanNm_DeInit(void);

#if (CANNM_REASON_POSITION_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_SetNetworkRequestReason
  (CONST(NetworkHandleType, CANNM_CONST) nmChannelHandle,
   CONST(uint8, CANNM_APPL_CONST) nmNetworkRequestReason);
  
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_GetNetworkRequestReason
  (CONST(NetworkHandleType, CANNM_CONST) nmChannelHandle,
   CONSTP2VAR(uint8, AUTOMATIC, CANNM_APPL_DATA) nmNetworkRequestReason);
#endif

#define CANNM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Callback function from CanNM module                   **
*******************************************************************************/
#define CANNM_START_SEC_CODE
#include "MemMap.h"

#if ((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF))
extern FUNC(void, CANNM_CODE) CanNm_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);
#endif /* #if ((CANNM_PASSIVE_MODE_ENABLED == STD_OFF) && (CANNM_IMMEDIATE_TXCONF_ENABLED == STD_OFF)) */

extern FUNC(void, CANNM_CODE) CanNm_RxIndication(
            PduIdType RxPduId,
            P2CONST(PduInfoType, AUTOMATIC, CANNM_APPL_DATA) PduInfoPtr);

#if (CANNM_GLOBAL_PN_SUPPORT == STD_ON)
extern FUNC(void, CANNM_CODE) CanNm_ConfirmPnAvailability(
            CONST(NetworkHandleType, CANNM_APPL_CONST)nmChannelHandle);
#endif /* #if (CANNM_GLOBAL_PN_SUPPORT == STD_ON) */

#if (CANNM_TRIGGER_TRANSMIT_ENABLED == STD_ON)
extern FUNC(Std_ReturnType, CANNM_CODE) CanNm_TriggerTransmit(
            PduIdType TxPduId,
            P2VAR(PduInfoType, AUTOMATIC, CANNM_VAR) PduInfoPtr);
#endif /* #if (CANNM_TRIGGER_TRANSMIT_ENABLED == STD_ON) */

#define CANNM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CANNM_H */

/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
