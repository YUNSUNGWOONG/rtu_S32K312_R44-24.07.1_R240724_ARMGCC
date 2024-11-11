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
**  SRC-MODULE: CanIf.h                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of external declaration of APIs and Service Ids     **
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
** 1.1.0     29-Feb-2024   Jh Yang        #CP44-2946, #CP44-2947              **
** 1.0.14    13-Jun-2023   HieuTM8        #CP44-2236                          **
** 1.0.12    12-Dec-2022   HieuTM8        #CP44-1254                          **
** 1.0.10    27-Oct-2022   HieuTM8        #CP44-1008                          **
** 1.0.9     03-Oct-2022   HieuTM8        #CP44-832                           **
** 1.0.5     30-Jun-2022   HieuTM8        #CP44-130                           **
** 1.0.2     25-Mar-2022   HieuTM8        #25534                              **
** 1.0.1     22-Sep-2021   HieuTM8        #20891                              **
** 1.0.0     21-Dec-2020   SJ Kim         Initialization                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#ifndef CANIF_H
#define CANIF_H

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_CANIF_AR_RELEASE_MAJOR_VERSION       4
#define CANIF_CANIF_AR_RELEASE_MINOR_VERSION       4
#define CANIF_CANIF_AR_RELEASE_REVISION_VERSION    0

/* Software Version Information */
#define CANIF_CANIF_SW_MAJOR_VERSION       1
#define CANIF_CANIF_SW_MINOR_VERSION       1
#define CANIF_CANIF_SW_REVISION_VERSION    0

#define CAN_AR_RELEASE_MAJOR_VERSION_FOUR   (4)
#define CAN_AR_RELEASE_MINOR_VERSION_TWO    (2)
#define CAN_AR_RELEASE_MINOR_VERSION_THREE  (3)
#define CAN_AR_RELEASE_MINOR_VERSION_FOUR   (4)
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CanIf_SUD_FILE_001 */
#include "ComStack_Types.h"     /* STANDARD Types Header File */
/* @Trace: CanIf_SUD_MACRO_017 */
#include "CanIf_Cfg.h"          /* Configuration header file */
#if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
#include "CanIf_PBcfg.h"        /* Configuration PB header file */
#endif

#include "CanIf_Types.h"        /* Type definition header file */
#if (STD_ON == CANIF_AUTRON_CANTRCV_SUPPORT)
#include "CanTrcv.h"            /* CanTrcv header file */
#endif
#if (STD_ON == CANIF_EXTENAL_CANTRCV_SUPPORT)
#include "CanIf_CanTrcv.h"            /* CanTrcv header file */
#endif
#if (STD_ON == CANIF_WAKEUP_SUPPORT) || (STD_ON == CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT)
#include "EcuM.h"               /* EcuM header file */
#endif
#if (STD_ON == CANIF_PDUR_CALLBACK)
#include "PduR_CanIf.h"         /* PduR header file */
#endif
#if (STD_ON == CANIF_CANTP_CALLBACK)
#include "CanTp.h"          /* CanTp header file */
#endif
#if (STD_ON == CANIF_CANNM_CALLBACK)
#include "CanNm.h"          /* CanNm header file */
#endif
#if ((STD_ON == CANIF_TX_XCP_CALLBACK) || (STD_ON == CANIF_RX_XCP_CALLBACK))
#include "Xcp.h"            /* Xcp header file */
#endif
#if ((STD_ON == CANIF_TX_J1939TP_CALLBACK) || \
                                          (STD_ON == CANIF_RX_J1939TP_CALLBACK))
#include "J1939Tp.h"        /* J1939Tp header file */
#endif

#if (STD_ON == CANIF_OSEKNM_CALLBACK)
#include "OsekNm.h"           /* Call-back OsekNm header file */
#endif

#if ((STD_ON == CANIF_TX_J1939NM_CALLBACK) || \
                                          (STD_ON == CANIF_RX_J1939NM_CALLBACK))
#include "J1939Nm.h"        /* J1939Nm header file */
#endif
#if ((STD_ON == CANIF_TX_CANTSYN_CALLBACK) || \
                                          (STD_ON == CANIF_RX_CANTSYN_CALLBACK))
#include "CanTSyn.h"
#endif
#include "CanIf_PCTypes.h"      /* PCTypes Header File*/
#include "CanIf_UserInc.h"
#include "CanIf_Dbg.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
/* Invalid CAN ID is reported using following error code */
#define CANIF_E_PARAM_CANID            ((uint8)10)

/* Invalid DLC is reported using following error code */
#define CANIF_E_PARAM_DLC              ((uint8)11)

/* Invalid controller ID is reported using following error code */
#define CANIF_E_PARAM_CONTROLLERID     ((uint8)15)

/* Invalid wakeup source ID is reported using following error code*/
#define CANIF_E_PARAM_WAKEUPSOURCE     ((uint8)16)

/* Invalid mode request is reported using following error code */
#define CANIF_E_PARAM_TRCV             ((uint8)17)

/* Invalid pointer input is reported using following error code */
#define CANIF_E_PARAM_TRCVMODE         ((uint8)18)

/* Invalid Mailbox->Hoh is reported using following error code*/
#define CANIF_E_PARAM_HOH              ((uint8)12)

/* API service called with wrong database address */
#define CANIF_E_PARAM_TRCVWAKEUPMODE   ((uint8)19)

/* API service used without module initialization */
#define CANIF_E_PARAM_CTRLMODE         ((uint8)21)

/* DET error used with parameter passed as null pointer */
#define CANIF_E_PARAM_POINTER          ((uint8)20)

/* DET error reported when module is uninitialized */
#define CANIF_E_UNINIT                 ((uint8)30)

/* Not supported API request is reported using following error code */
#define CANIF_E_INVALID_TXPDUID        ((uint8)50)

/* Invalid Transceiver Id */
#define CANIF_E_INVALID_RXPDUID        ((uint8)60)

/* Invalid CAN Transceiver operation Mode */
#define CANIF_E_INVALID_DATA_LENGTH    ((uint8)61)

/* Invalid PDU Mode */
#define CANIF_E_PARAM_PDU_MODE         ((uint8)22)

/* Invalid LPDU*/
#define CANIF_E_PARAM_LPDU             ((uint8)13)

/* Invalid CAN Transceiver operation Mode */
#define CANIF_E_STOPPED                ((uint8)70)

/* Macro to check whether wake up is disabled */
#define CANIF_WAKEUP_DISABLED          ((uint8)0x00)

/* Macro to check whether wake up is enabled */
#define CANIF_WAKEUP_ENABLED           ((uint8)0x01)

/* Macro to check for invalid value */
#define CANIF_INVALID                  ((PduIdType)0xffff)

/* Macro to check for CAN Interface initialization value */
#define CANIF_E_INIT_FAILED            ((uint8)80)

/* Macro for error id for transceiver */
#define CANIF_E_TRANSCEIVER            ((uint8)91)

/* Macro for error id for Data Length */
#define CANIF_E_DATA_LENGTH_MISMATCH   ((uint8)62)

/* Macro for error id for Maximum Message Length Exceeded */
#define CANIF_E_TXPDU_LENGTH_EXCEEDED  ((uint8)90)

/* Macro for error id for Rx Can Id Type */
#define CANIF_E_RXPDU_CANIDTYPE_INVALID ((uint8)63)

/* macro for invalid rxpduid */
#define CANIF_INVALID_ID               ((PduIdType)0xff)

/* macro for gateway buffer state */
#define CANIF_GW_NOREQUEST   ((uint8)0x00)
#define CANIF_GW_STOPPED     ((uint8)0x01)
#define CANIF_GW_REQUESTED   ((uint8)0x02)
#define CANIF_GW_NOCOMM      ((uint8)0x03)
#define CANIF_GW_ERRVOL      ((uint8)0x04)

/* Macro for Cancellation used */
#define CANIF_AUTRON_AUTOSAR_CANCELLATION_USED (STD_OFF)

/*******************************************************************************
**                      Service Id of API                                     **
*******************************************************************************/
/* Service ID for CanIf_Init */
#define CANIF_INIT_SID                        ((uint8)0x01)

/* Service ID for CanIf_DeInit */
#define CANIF_DEINIT_SID                      ((uint8)0x02)

/* Service ID for CanIf_SetController */
#define CANIF_SET_CNTRL_MODE_SID              ((uint8)0x03)

/* @Trace: SWS_CANIF_91005 */
/* Service ID for CanIf_EnableBusMirroring */
#define CANIF_ENABLE_BUS_MIRRORING_SID        ((uint8)0x4c)

/* Service ID for CanIf_GetControllerMode */
#define CANIF_GET_CNTRL_MODE_SID              ((uint8)0x04)

/* Service ID for CanIf_Transmit */
#define CANIF_TRANSMIT_SID                    ((uint8)0x05)

/* Service ID for CanIf_ReadRxPduData */
#define CANIF_READ_RXPDU_DATA_SID             ((uint8)0x06)

/* Service ID for CanIf_ReadTxNotifStatus */
#define CANIF_READ_TX_NOTIF_STATUS_SID        ((uint8)0x07)

/* Service ID for CanIf_ReadRxNotifStatus */
#define CANIF_READ_RX_NOTIF_STATUS_SID        ((uint8)0x08)

/* Service ID for CanIf_SetPduMode */
#define CANIF_SET_PDU_MODE_SID                ((uint8)0x09)

/* Service ID for CanIf_GetPduMode */
#define CANIF_GET_PDU_MODE_SID                ((uint8)0x0a)

/* Service ID for CanIf_VersionInfo */
#define CANIF_GET_VERSIONNFO_SID              ((uint8)0x0b)

/* Service ID for CanIf_SetDynamicTxId */
#define CANIF_SET_DYNAMIC_TXID_SID            ((uint8)0x0c)

/* Service ID for CanIf_GetTrcvWakeupReason */
#define CANIF_GET_TRCV_WAKEUPREASON_SID       ((uint8)0x0f)

/* Service ID for CanIf_SetTransceiverWakeupMode */
#define CANIF_SET_TRCV_WAKEUP_MODE_SID        ((uint8)0x10)

/* Service ID for CanIf_CheckWakeup */
#define CANIF_CHECK_WAKEUP_SID                ((uint8)0x11)

/* Service ID for CanIf_CheckValidation */
#define CANIF_CHECK_VALIDATION_SID            ((uint8)0x12)

/* Service ID for CanIf_TxConfirmation */
#define CANIF_TX_CONFIRMATION_SID             ((uint8)0x13)

/* Service ID for CanIf_RxIndication */
#define CANIF_RX_INDICATION_SID               ((uint8)0x14)

/* Service ID for CanIf_CheckRxPduCanIdType */
#define CANIF_CHECK_RX_PDU_CAN_ID_TYPE_SID    ((uint8)0x15)

/* Service ID for CanIf_ControllerBusOff */
#define CANIF_CNTRL_BUS_OFF_SID               ((uint8)0x16)

/* Service ID for CanIf_ControllerModeIndication */
#define CANIF_CTRL_MODE_IND_SID               ((uint8)0x17)

/* Service ID for CanIf_SetIcomConfiguration */
#define CANIF_SET_ICOM_CONFIGURATION_SID      ((uint8)0x25)

/* Service ID for CanIf_CurrentIcomConfiguration */
#define CANIF_CURRENT_ICOM_CONFIGURATION_SID  ((uint8)0x26)

/* Service ID for CanIf_ClearTrcvWufFlag */
#define CANIF_CLEAR_TRCV_WUF_SID              ((uint8)0x1e)

/* Service ID for CanIf_CheckTrcvWakeFlag */
#define CANIF_CHECK_TRCV_WAKE_SID             ((uint8)0x1f)

/* Service ID for CanIf_CheckTrcvWakeFlagIndication */
#define CANIF_CHECK_TRCV_WAKE_FLAG_IND_SID    ((uint8)0x21)

/* Service ID for CanIf_TrcvModeIndication */
#define CANIF_TRCV_MODE_IND_SID               ((uint8)0x22)

/* Service ID for CanIf_TriggerTransmit */
#define CANIF_TRIGGER_TRANSMIT_SID            ((uint8)0x41)

/* Service ID for CanIf_GetControllerErrorState */
#define CANIF_GET_CNTRL_ERROR_STATE_SID       ((uint8)0x4b)

/* Service ID for CanIf_ConfirmPnAvailability */
#define CANIF_CONFIRM_PN_AVAILIBILITY_SID     ((uint8)0x1a)

/* Service ID for CanIf_ClearTrcvWufFlagIndication */
#define CANIF_CLEAR_TRCV_WAKE_FLAG_IND_SID    ((uint8)0x20)

/* Service ID for CanIf_GetTxConfirmationState */
#define CANIF_GET_TX_CONFIRM_STATE_SID        ((uint8)0x19)

/* Service ID for CanIf_GetControllerTxErrorCounter */
#define CANIF_GET_CONTROLLER_TX_ERROR_COUNTER_SID        ((uint8)0x4e)

/* Service ID for CanIf_GetControllerRxErrorCounter */
#define CANIF_GET_CONTROLLER_RX_ERROR_COUNTER_SID        ((uint8)0x4d)

/* Service ID for CanIf_SetBaudrate */
#define CANIF_SET_BAUD_RATE_SID               ((uint8)0x27)

/* Service ID for CanIf_SetTrcvMode */
#define CANIF_SET_TRCV_MODE_SID               ((uint8)0x0d)

/* Service ID for CanIf_GetTrcvMode */
#define CANIF_GET_TRCV_MODE_SID               ((uint8)0x0e)

/* Instance ID */
#define CANIF_INSTANCE_ID                     ((uint8)0x00)


/*******************************************************************************
**                      Macro                                                 **
*******************************************************************************/
/* polyspace-begin MISRA2012:D4.9 [No action planned:Low] "use macro function to reduce length of code and explain the meaning of the code"*/
/* Macro for unused variable */
#define CANIF_UNUSED(x)                       (void)x

#if (STD_ON == CANIF_CANFD_SUPPORT)
#define CANIF_SDU_MAX_LENGTH \
  ((ptrTxLpdu->CanIdType == CANIF_CANFD_EXTENDED_CANID_TYPE || \
    ptrTxLpdu->CanIdType == CANIF_CANFD_STANDARD_CANID_TYPE) ? \
  CANIF_CANFD_MAX_LENGTH : CANIF_EIGHT)
#else
#define CANIF_SDU_MAX_LENGTH CANIF_EIGHT
#endif

/* @Trace: SWS_CANIF_00895 */
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_STOGARE_ERROR_DET_REPORT()                                       \
      do {                                                                     \
        (void)Det_ReportRuntimeError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,       \
        CANIF_TRANSMIT_SID,                                                    \
        CANIF_E_DATA_LENGTH_MISMATCH);                                         \
      } while (0);
#else
#define CANIF_STOGARE_ERROR_DET_REPORT()
#endif

#define CANIF_STORE_IN_QUEUE(x) do {                                           \
            ptrTxQueue = &(CanIf_TxQueue[(x)]);                                \
            ptrTxQueue->TxLPduId = canPduInfo.swPduHandle;                     \
            ptrTxQueue->Dlc = canPduInfo.length;                               \
            ptrTxQueue->CanId = canPduInfo.id;                                 \
            if (NULL_PTR != canPduInfo.sdu)                                    \
            {                                                                  \
              count = canPduInfo.length;                                       \
              if ((CANIF_TRUE == ptrTxLpdu->Truncate) &&                       \
                  ((uint8)CANIF_SDU_MAX_LENGTH < count))                       \
              {	                                                               \
                /* @Trace: SWS_CANIF_00894 SWS_CANIF_00895 */                  \
                count = (uint8)CANIF_SDU_MAX_LENGTH;                           \
                CANIF_STOGARE_ERROR_DET_REPORT();                              \
              }                                                                \
              while ((uint8)CANIF_ZERO != count)                               \
              {                                                                \
                count--;                                                       \
                ptrTxQueue->TxBuffer[count] = canPduInfo.sdu[count];           \
              };                                                               \
              ptrTxQueue->TxBufferPtr = ptrTxQueue->TxBuffer;                  \
            }                                                                  \
            else                                                               \
            {                                                                  \
              ptrTxQueue->TxBufferPtr = NULL_PTR;                              \
            }                                                                  \
} while (0)


#define CANIF_TXPDU_GW_STATUS(x) (CanIf_TxPduGwStatus[(x)])
/* polyspace-end MISRA2012:D4.9 [No action planned:Low] "use macro function to reduce length of code and explain the meaning of the code"*/    
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_Init (P2CONST(CanIf_ConfigType, AUTOMATIC,
                                                   CANIF_APPL_CONST) ConfigPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_InitQueue (void);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (STD_ON == CANIF_TX_LPDU) */
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_DeInit (void);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE)CanIf_SetControllerMode (
                       VAR(uint8, CANIF_VAR) ControllerId,
#if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
    ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
     (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))
                        VAR(Can_ControllerStateType, CANIF_VAR) ControllerMode);
#else
VAR(Can_ControllerStateType, CANIF_VAR) ControllerMode);
#endif	
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE)CanIf_GetControllerMode (
 VAR(uint8, CANIF_VAR) ControllerId,
  #if (CAN_AR_RELEASE_MAJOR_VERSION > CAN_AR_RELEASE_MAJOR_VERSION_FOUR) || \
  ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
   (CAN_AR_RELEASE_MINOR_VERSION >= CAN_AR_RELEASE_MINOR_VERSION_THREE))  
  P2VAR(Can_ControllerStateType, AUTOMATIC, CANIF_APPL_DATA) ControllerModePtr);
  #else
P2VAR(Can_ControllerStateType, AUTOMATIC, CANIF_APPL_DATA) ControllerModePtr);
  #endif	  
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE)CanIf_GetControllerErrorState (
    VAR(uint8, CANIF_VAR) ControllerId,
    P2VAR(Can_ErrorStateType, AUTOMATIC, CANIF_APPL_DATA) ErrorStatePtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#if (STD_ON == CANIF_TX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_Transmit (
                  VAR(PduIdType, CANIF_VAR) TxPduId,
                  P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_READRXPDU_DATA_API)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_ReadRxPduData (
                     VAR(PduIdType, CANIF_VAR) CanIfRxSduId,
                     P2VAR(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_DETReadRxPduData (
                     VAR(PduIdType, CANIF_VAR) CanIfRxSduId,
                     P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((STD_ON == CANIF_TX_LPDU) && (STD_ON == CANIF_READTXPDU_NOTIFY_STATUS_API))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadTxNotifStatus (
                                      VAR(PduIdType, CANIF_VAR) CanIfTxSduId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_READRXPDU_NOTIFY_STATUS_API)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(CanIf_NotifStatusType, CANIF_CODE) CanIf_ReadRxNotifStatus(
                                      VAR(PduIdType, CANIF_VAR) CanIfRxSduId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetPduMode (
                           VAR(uint8, CANIF_VAR) ControllerId,
                           VAR(CanIf_PduModeType, CANIF_VAR) PduModeRequest);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_DETSetPduMode (
                           VAR(uint8, CANIF_VAR) ControllerId,
                           VAR(CanIf_PduModeType, CANIF_VAR) PduModeRequest);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE)CanIf_GetPduMode (
            VAR(uint8, CANIF_VAR) ControllerId,
            P2VAR(CanIf_PduModeType, AUTOMATIC, CANIF_APPL_DATA) PduModePtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#if (STD_ON == CANIF_VERSION_INFO_API)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE)CanIf_GetVersionInfo
           (P2VAR(Std_VersionInfoType, AUTOMATIC, CANIF_APPL_DATA)VersionInfo);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((STD_ON == CANIF_TX_LPDU) && (STD_ON == CANIF_SETDYNAMICTXID_API))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE)CanIf_SetDynamicTxId (
                                       VAR(PduIdType, CANIF_VAR) CanIfTxSduId,
                                       VAR(Can_IdType, CANIF_VAR) CanId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_CANTRCV_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTrcvMode (
                          VAR(uint8, CANIF_VAR) TransceiverId,
                          VAR(CanTrcv_TrcvModeType, CANIF_VAR) TransceiverMode);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_CANTRCV_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvMode (
            VAR(uint8, CANIF_VAR) TransceiverId,
            P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANIF_VAR)TransceiverModePtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvWakeupReason (
      VAR(uint8, CANIF_VAR) TransceiverId,
      P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANIF_VAR)TrcvWuReasonPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTrcvWakeupMode (
                     VAR(uint8, CANIF_VAR) TransceiverId,
                     VAR(CanTrcv_TrcvWakeupModeType, CANIF_VAR) TrcvWakeupMode);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* @Trace: SWS_CANIF_00180 */
#if ((STD_ON == CANIF_WAKEUP_SUPPORT) && ((STD_ON == CANIF_CTRL_WAKEUP_SUPPORT)||\
     (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckWakeup (
                            VAR(EcuM_WakeupSourceType, CANIF_VAR) WakeupSource);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif
/* @Trace: SWS_CANIF_00226 */
#if ((STD_ON == CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT) && \
     ((STD_ON == CANIF_CTRL_WAKEUP_SUPPORT) || (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckValidation (
                            VAR(EcuM_WakeupSourceType, CANIF_VAR) WakeupSource);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_TXCONFIRM_POLLING_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(CanIf_NotifStatusType, CANIF_CODE)CanIf_GetTxConfirmationState (
                                            VAR(uint8, CANIF_VAR) ControllerId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((STD_ON == CANIF_PN_SUPPORT) && (STD_ON == CANIF_CANTRCV_SUPPORT))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_ClearTrcvWufFlag (
                                           VAR(uint8, CANIF_VAR) TransceiverId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((STD_ON == CANIF_PN_SUPPORT) && (STD_ON == CANIF_CANTRCV_SUPPORT))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckTrcvWakeFlag (
                                           VAR(uint8, CANIF_VAR) TransceiverId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_SET_BAUDRATE_API)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetBaudrate (
                                           VAR(uint8, CANIF_VAR) ControllerId,
                                           VAR(uint16, CANIF_VAR) BaudRateConfigID);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* internally used for Direct OSKEK NM */
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,CANIF_CODE) CanIf_ReadRxCanId
           (P2VAR(Can_IdType, AUTOMATIC, CANIF_APPL_DATA) CanIdPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetBatteryVoltageMode( VAR(uint8, CANIF_VAR) ControllerId,
    VAR(CanIf_BatVolSetModeType, CANIF_VAR) BatteryVolMode);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/* @Trace: SWS_CANIF_00883 */
#if (STD_ON == CANIF_TX_LPDU) && (CANIF_TRIGGER_TRANSMIT_SUPPORT == STD_ON)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_TriggerTransmit
       (PduIdType TxPduId,
    	P2VAR(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif /*#if (STD_ON == CANIF_TX_LPDU)(CANIF_TRIGGER_TRANSMIT_SUPPORT == STD_ON)*/


#if (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_DummyTxTriggerTransmit 
       (PduIdType TxPduId,
       P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"  
#endif
/* @Trace: SWS_CANIF_00861 */
#if (STD_ON == CANIF_PUBLIC_ICOM_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetIcomConfiguration (
                                VAR(uint8, CANIF_VAR) ControllerId,
                                VAR(IcomConfigIdType, CANIF_VAR) ConfigurationId);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

/* @Trace: SWS_CANIF_91003 */
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerRxErrorCounter (
                                VAR(uint8, CANIF_VAR) ControllerId,
                                P2VAR(uint8, AUTOMATIC, CANIF_VAR) RxErrorCounterPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/* @Trace: SWS_CANIF_91004 */
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetControllerTxErrorCounter (
                                VAR(uint8, CANIF_VAR) ControllerId,
                                P2VAR(uint8, AUTOMATIC, CANIF_VAR) TxErrorCounterPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

/* @Trace: SWS_CANIF_91005 */
#if (STD_ON == CANIF_BUS_MIRRORING_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_EnableBusMirroring (
                                VAR(uint8, CANIF_VAR) ControllerId,
                                VAR(boolean, CANIF_VAR) MirroringActive);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_ReadBusMsgCount (
                  VAR(uint8, CANIF_VAR) Controller,
                  P2VAR(CanIf_MsgType, AUTOMATIC, CANIF_APPL_VAR) MsgCnt);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CANIF_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
