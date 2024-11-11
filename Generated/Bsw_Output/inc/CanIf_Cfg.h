/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Co., Ltd.                                       **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  Generate On : The time-stamp is removed                                   **
**                                                                            **
**  SRC-MODULE:           CanIf_Cfg.h                                         **
**                                                                            **
**  PRODUCT   :           AUTOSAR CAN Interface Module                        **
**                                                                            **
**  PURPOSE   :           This file contain internal macros, externs etc.     **
**                        API's.                                              **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                                 **
**                                                                            **
**  Module version : 1.1.0.0                                                  **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            ** 
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/

/*
* INPUT FILE:      Configuration\Definition\Can_43_FLEXCAN_s32k312_mqfp172.epd
*                  Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CanIf.arxml           
*                  Configuration\Ecu\Ecud_CanNm.arxml           
*                  Configuration\Ecu\Ecud_CanSM.arxml           
*                  Configuration\Ecu\Ecud_CanTp.arxml           
*                  Configuration\Ecu\Ecud_CanTrcv.arxml         
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Ecu\Ecud_EcuM.arxml            
*                  Configuration\Ecu\Ecud_Nm.arxml              
*                  Configuration\Ecu\Ecud_PduR.arxml            
*                  Configuration\Ecu\Mcal\Ecud_Can.arxml        
*                  Configuration\System\Bswmd\Bswmd_Can.arxml   
*                  Generated\Bsw_Output\bswmd\Bswmd_CanIf.arxml 
*                  Generated\Bsw_Output\bswmd\Bswmd_CanTp.arxml 
*                  Generated\Bsw_Output\bswmd\Bswmd_CanTrcv.arxml
*                  Static_Code\Modules\CanIf_R44\generator\CanIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanNm_R44\generator\CanNm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanSM_R44\generator\CanSM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanTp_R44\generator\CanTp_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanTrcv_R44\generator\CanTrcv_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\EcuM_R44\generator\EcuM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\PduR_R44\generator\PduR_ECU_Configuration_PDF.arxml
* GENERATED ON:    11-Nov-2024 - 12:54:55                       
*/

#ifndef CANIF_CFG_H
#define CANIF_CFG_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define    CANIF_CFG_AR_RELEASE_MAJOR_VERSION            0x04u
#define    CANIF_CFG_AR_RELEASE_MINOR_VERSION            0x04u
#define    CANIF_CFG_AR_RELEASE_REVISION_VERSION         0x00u
#define    CANIF_CFG_SW_MAJOR_VERSION                    0x01u
#define    CANIF_CFG_SW_MINOR_VERSION                    0x01u
#define    CANIF_CFG_SW_PATCH_VERSION                    0x00u

/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
#define    CANIF_AR_RELEASE_MAJOR_VERSION                0x04u
#define    CANIF_AR_RELEASE_MINOR_VERSION                0x04u
#define    CANIF_AR_RELEASE_REVISION_VERSION             0x00u
#define    CANIF_SW_MAJOR_VERSION                        0x01u
#define    CANIF_SW_MINOR_VERSION                        0x01u
#define    CANIF_SW_PATCH_VERSION                        0x00u
#define    CANIF_VENDOR_ID                               0x004Cu
#define    CANIF_MODULE_ID                               0x003Cu

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Pre-compile option for Implementation Class */
#define    CANIF_VARIANT_POSTBUILD_SUPPORT               (STD_OFF)

/* Pre-compile option for SetDynamicTxId API */
#define    CANIF_SETDYNAMICTXID_API                      (STD_OFF)

/* Pre-compile option for Multiple CAN Driver Support */
#define    CANIF_MULTIPLE_CANDRV_SUPPORT                 (STD_OFF)

/* Pre-compile option for Version Info API */
#define    CANIF_VERSION_INFO_API                        (STD_ON)

/* Pre-compile option for Development Error Checking */
#define    CANIF_DEV_ERROR_DETECT                        (STD_ON)

/* Pre-compile option for Partial network Support */
#define    CANIF_PN_SUPPORT                              (STD_ON)

/* Pre-compile option for Validation Support */
#define    CANIF_WAKEUP_CHECK_VALIDATION_SUPPORT         (STD_OFF)

/* Pre-compile option for Binary Search */
#define    CANIF_BINARY_SEARCH                           (STD_ON)

/* Pre-compile option for Linear Search */
#define    CANIF_LINEAR_SEARCH                           (STD_OFF)

/* Pre-compile option for Controller Wakeup Support */
#define    CANIF_CTRL_WAKEUP_SUPPORT                     (STD_OFF)

/* Pre-compile option for Tx buffering */
#define    CANIF_TX_BUFFERING                            (STD_OFF)

/* Pre-compile option for Autron CanTrcv Support */
#define    CANIF_AUTRON_CANTRCV_SUPPORT                  (STD_ON)

/* Pre-compile option for External CanTrcv Support */
#define    CANIF_EXTENAL_CANTRCV_SUPPORT                 (STD_OFF)

/* Pre-compile option for CAN Trcv Support */
#define    CANIF_CANTRCV_SUPPORT                         (STD_ON)

/* Pre-compile option for Multiple CAN Trcv Driver Support */
#define    CANIF_MULTIPLE_TRCVDRV_SUPPORT                (STD_OFF)

/* Pre-compile option for CanNm Callbacks */
#define    CANIF_CANNM_CALLBACK                          (STD_ON)

/* Pre-compile option for CanTp Callbacks */
#define    CANIF_CANTP_CALLBACK                          (STD_ON)

/* Pre-compile option for Cdd Callbacks */
#define    CANIF_CDD_CALLBACK                            (STD_OFF)

/* Pre-compile option for EcuM Callbacks */
#define    CANIF_ECUM_CALLBACK                           (STD_OFF)

/* Pre-compile option for PduR Callbacks */
#define    CANIF_PDUR_CALLBACK                           (STD_ON)

/* Pre-compile option for CanNm Rx Callbacks */
#define    CANIF_RX_CANNM_CALLBACK                       (STD_ON)

/* Pre-compile option for CanTp Rx Callbacks */
#define    CANIF_RX_CANTP_CALLBACK                       (STD_ON)

/* Pre-compile option for Cdd Rx Callbacks */
#define    CANIF_RX_CDD_CALLBACK                         (STD_OFF)

/* Pre-compile option for Rx Multiple Call-Back */
#define    CANIF_RX_MULTIPLE_CALLBACK                    (STD_OFF)

/* Pre-compile option for PduR Rx Callbacks */
#define    CANIF_RX_PDUR_CALLBACK                        (STD_ON)

/* Pre-compile option for Controller Wakeup Support */
#define    CANIF_WAKEUP_SUPPORT                          (STD_OFF)

/* Pre-compile option for Tranceiver Wakeup Support */
#define    CANIF_TRCV_WAKEUP_SUPPORT                     (STD_OFF)

/* Pre-compile option for Rx L-PDUs */
#define    CANIF_RX_LPDU                                 (STD_ON)

/* Pre-compile option for Tx L-PDUs */
#define    CANIF_TX_LPDU                                 (STD_ON)

/* Pre-compile option for CanNm Tx Callbacks */
#define    CANIF_TX_CANNM_CALLBACK                       (STD_ON)

/* Pre-compile option for CanTp Tx Callbacks */
#define    CANIF_TX_CANTP_CALLBACK                       (STD_ON)

/* Pre-compile option for Cdd Tx Callbacks */
#define    CANIF_TX_CDD_CALLBACK                         (STD_OFF)

/* Pre-compile option for Tx Multiple Call-Back */
#define    CANIF_TX_MULTIPLE_CALLBACK                    (STD_OFF)

/* Pre-compile option for PduR Tx Callbacks */
#define    CANIF_TX_PDUR_CALLBACK                        (STD_ON)

/* Pre-compile option for Transmit Queue */
#define    CANIF_TX_QUEUE                                (STD_OFF)

/* Pre-compile option for XCP Callbacks */
#define    CANIF_TX_XCP_CALLBACK                         (STD_OFF)

/* Pre-compile option for J1939TP Callbacks */
#define    CANIF_TX_J1939TP_CALLBACK                     (STD_OFF)

/* Pre-compile option for XCP Callbacks */
#define    CANIF_RX_XCP_CALLBACK                         (STD_OFF)

/* Pre-compile option for J1939TP Callbacks */
#define    CANIF_RX_J1939TP_CALLBACK                     (STD_OFF)

/* Pre-compile option for Tx Confirmation Polling Support */
#define    CANIF_TXCONFIRM_POLLING_SUPPORT               (STD_ON)

/* Pre-compile option for configuration of BASIC TX PDU */
#define    CANIF_BASIC_CAN_TXPDU                         (STD_OFF)

/* Pre-compile option for configuration of BASIC RX PDU */
#define    CANIF_RX_BASIC_CAN_SUPPORT                    (STD_ON)

/* Pre-compile option for ReadRxPdu Data API */
#define    CANIF_READRXPDU_DATA_API                      (STD_OFF)

/* Pre-compile option for ReadTxNotify Status API */
#define    CANIF_READTXPDU_NOTIFY_STATUS_API             (STD_OFF)

/* Pre-compile option for ReadRxNotify Status API */
#define    CANIF_READRXPDU_NOTIFY_STATUS_API             (STD_OFF)

/* Pre-compile option for turning on/off API check validation */
#define    CANIF_WAKEUP_CHECK_VALIDATION_API             (STD_OFF)

/* Pre-compile option for CanCM support */
#define    CANIF_CANCM_SUPPORT                           (STD_ON)

/* Pre-compile option for CAN-FD support */
#define    CANIF_CANFD_SUPPORT                           (STD_ON)

/* Pre-compile option for meta data support */
#define    CANIF_META_DATA_SUPPORT                       (STD_ON)

/* Pre-compile option for J1939NM Callbacks */
#define    CANIF_TX_J1939NM_CALLBACK                     (STD_OFF)

/* Pre-compile option for J1939NM Callbacks */
#define    CANIF_RX_J1939NM_CALLBACK                     (STD_OFF)

/* Pre-compile option for Mcal CAN-FD ID 32 Bit Support */
#define    CANIF_CANFD_ID_16BIT_SUPPORT                  (STD_OFF)

/* Pre-compile option for Mcal CAN_FD Dlc Discrete Support */
#define    CANIF_CANFD_DISCRETE_DLC_SUPPORT              (STD_OFF)

/* Pre-compile option for Binary Search */
#define    CANIF_IDTABLE_SEARCH                          (STD_OFF)

/* Pre-compile option for J1939Tp Callbacks */
#define    CANIF_J1939TP_CALLBACK                        (STD_OFF)

/* Pre-compile option for J1939Nm Callbacks */
#define    CANIF_J1939NM_CALLBACK                        (STD_OFF)

/* Pre-compile option for Can TSyn Callbacks */
#define    CANIF_CANTSYN_CALLBACK                        (STD_OFF)

/* Pre-compile option for Xcp Callbacks */
#define    CANIF_XCP_CALLBACK                            (STD_OFF)

/* Pre-compile option for Osek Nm Callbacks */
#define    CANIF_OSEKNM_CALLBACK                         (STD_OFF)

/* Pre-compile option for Can TSyn Tx Callbacks */
#define    CANIF_TX_CANTSYN_CALLBACK                     (STD_OFF)

/* Pre-compile option for Can TSyn Callbacks */
#define    CANIF_RX_CANTSYN_CALLBACK                     (STD_OFF)

/* Pre-compile option for OsekNm Rx Callbacks */
#define    CANIF_RX_OSEKNM_CALLBACK                      (STD_OFF)

/* Pre-compile option for buffer element length */
#define    CANIF_FIXED_BUFFER                            (STD_ON)

/* Pre-compile option for Bus Mirroring support */
#define    CANIF_BUS_MIRRORING_SUPPORT                   (STD_OFF)

/* Pre-compile option for Pretended Network support */
#define    CANIF_PUBLIC_ICOM_SUPPORT                     (STD_OFF)

/* Pre-compile option for TxOffLineActive feature */
#define    CANIF_TX_OFFLINE_ACTIVE_SUPPORT               (STD_OFF)

/* Pre-compile option for OsekNm Tx Callbacks */
#define    CANIF_TX_OSEKNM_CALLBACK                      (STD_OFF)

/* Pre-compile option for Set Baud rate */
#define    CANIF_SET_BAUDRATE_API                        (STD_OFF)

/* Pre-compile option for turning on/off DLC check */
#define    CANIF_PRIVATE_DATA_LENGTH_CHECK               (STD_ON)

/* Pre-compile option for check validate wakeup */
#define    CANIF_PUBLIC_WAKEUP_CHECK_VALID_BYNM          (STD_OFF)

/* Pre-compile option for IdsM Support */
#define    CANIF_IDSM_SUPPORT                            (STD_OFF)

/* Pre-compile option for STANDARD_CANID Only */
#define    CANIF_STANDARD_CANID_ONLY                     (STD_ON)

/* Pre-compile option for EXTENDED_CANID Only */
#define    CANIF_EXTENDED_CANID_ONLY                     (STD_OFF)

/*  Pre-compile option for EXT_STD_CANID */
#define    CANIF_EXT_STD_CANID                           (STD_OFF)

/*  Pre-compile option for Bus load detecting  */
#define    CANIF_BUSLOAD_DETECTING_SUPPORT               (STD_OFF)

/* Pre-compile option for CanIf Tx Rx monitoring Support */
#define    CANIF_TX_RX_MONITORING_SUPPORT                (STD_OFF)

/* Pre-compile option for CanIf_TriggerTransmit API */
#define    CANIF_TRIGGER_TRANSMIT_SUPPORT                (STD_OFF)

/* Pre-compile option for CDD trigger transmit */
#define    CANIF_TRIGGER_TRANSMIT_CDD_SUPPORT            (STD_OFF)


/*******************************************************************************
**           MACRO FOR BUS-OFF, WAKE-UP AND VALIDATION WAKEUP                 **
*******************************************************************************/

/* Macro for ControllerBusOff */
#define CANIF_DISPATCH_USERCTRLBUSOFF_NAME(Controller) \
(CanSM_ControllerBusOff(Controller))

/* Macro for TransceiverModeIndication */
#define CANIF_DISPATCH_USERTRCVMODEINDICATION_NAME(TransceiverId, TransceiverMode) \
(CanSM_TransceiverModeIndication(TransceiverId, TransceiverMode))

/* Macro for USERVALIDATEWAKEUPEVENT_NAME */
#define CANIF_DISPATCH_USERVALIDATEWAKEUPEVENT_NAME(sources) \
(EcuM_ValidateWakeupEvent(sources))

/* Macro for CheckTrcvWakeFlagIndication */
#define CANIF_DISPATCH_USERCHECKTRCVWAKEFLAGINDICATION_NAME(TransceiverId) \
(CanSM_CheckTransceiverWakeFlagIndication(TransceiverId))

/* Macro for ClearTrcvWufFlagIndication */
#define CANIF_DISPATCH_USERCLEARTRCVWUFFLAGINDICATION_NAME(TransceiverId) \
(CanSM_ClearTrcvWufFlagIndication(TransceiverId))

/* Macro for ConfirmPnAvailability */
#define CANIF_DISPATCH_USERCONFIRMPNAVAILABILITY_NAME(TransceiverId) \
(CanSM_ConfirmPnAvailability(TransceiverId))

/* Macro for CtrlModeIndication */
#define CANIF_DISPATCH_USERCTRLMODEINDICATION_NAME(ControllerId, ControllerMode) \
(CanSM_ControllerModeIndication(ControllerId, ControllerMode))

/* Pre-compile option for trigger transmit */
#define CANIF_CDD_TRIGGER_TRANSMIT_MACRO (CanIf_DummyTxTriggerTransmit)

/*  Pre-compile option for PDUR trigger transmit */
#define CANIF_PDUR_TRIGGER_TRANSMIT_MACRO (CanIf_DummyTxTriggerTransmit)

/*******************************************************************************
**                     MACRO FOR RX INDICATION                                **
*******************************************************************************/
/* Macro for PduR RxIndication */
#define CANIF_PDUR_RXIND_MACRO \
        (PduR_CanIfRxIndication)

/* Macro for CanNm RxIndication */
#define CANIF_CANNM_RXIND_MACRO \
        (CanNm_RxIndication)

/* Macro for CanTp RxIndication */
#define CANIF_CANTP_RXIND_MACRO \
        (CanTp_RxIndication)


/*******************************************************************************
**                     MACRO FOR TX CONFIRMATION                              **
*******************************************************************************/
/* Macro for PduR TxConfirmation */
#define CANIF_PDUR_TXCNFRM_MACRO \
(PduR_CanIfTxConfirmation)

/* Macro for CanNm TxConfirmation */
#define CANIF_CANNM_TXCNFRM_MACRO \
(CanNm_TxConfirmation)

/* Macro for CanTp TxConfirmation */
#define CANIF_CANTP_TXCNFRM_MACRO \
(CanTp_TxConfirmation)


/*******************************************************************************
**                      MACROS                                                **
*******************************************************************************/
/* Number of controllers across all the CAN Drivers */
#define CANIF_NO_OF_CANTRCVDRIVER          (((uint8)0))

/* Number of wakeup Source */
#define CANIF_NO_OF_WAKEUP_SOURCES         (((uint8)0))

/* Number of controllers across all the CAN Drivers */
#define CANIF_NO_OF_CONTROLLER             (1)

/* Number of Transceiver channels */
#define CANIF_NO_OF_TRANSCEIVER            (1)

/* Number of CAN Drivers */
#define CANIF_NO_OF_CANDRIVER              ((uint8)1)

/* Number of basic txlpdu */
#define CANIF_NO_OF_BASIC_TXLPDU           ((uint16)0)

/* Number of Rx L-PDU */
#define CANIF_NO_OF_RXLPDU                 ((PduIdType)7)

/* Number of Tx L-PDU */
#define CANIF_NO_OF_TXLPDU                 ((PduIdType)8)

/* Number of Hrh */
#define CANIF_NO_OF_HRH                    ((uint16)6)

/* Number of element of Hrh_Init */
#define CANIF_NO_OF_HRH_INIT               ((uint8)1)

/* Number of HrhMapArray */
#define CANIF_NO_OF_HRH_MAP                ((uint16)6)

/* Number of Dynamic Tx L-PDU */
#define CANIF_NO_OF_DYNAMIC_TXLPDU         ((PduIdType)0)

/* Number of Tx Queue */
#define CANIF_NO_OF_TXQUEUE                ((uint16)0)

/* Number of Tx Buffers */
#define CANIF_NO_OF_TXBUFFER               ((uint16)0)

/* Number of Rx Notify */
#define CANIF_NO_OF_RXNOTIFY               ((uint16)0)

/* Number of Bits */
#define CANIF_BITARRAY_SIZE                ((uint16)0)

/* Number of Tx Confirmation */
#define CANIF_NO_OF_TXCONFIRMATION         ((uint16)3)

/* Number of Rx Indication */
#define CANIF_NO_OF_RXINDICATION           ((uint16)3)


#endif /* CANIF_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
