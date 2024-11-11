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
**  SRC-MODULE:           CanNm_Cfg.h                                         **
**                                                                            **
**  PRODUCT   :           AUTOSAR CanNm Interface Module                      **
**                                                                            **
**  PURPOSE   :           This file contain internal macros, externs etc.     **
**                        API's.                                              **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
*******************************************************************************/

/*******************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework Version: 1.1.5                                                  **
**  Module Version   : 1.2.0.0                                                **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CanIf.arxml           
*                  Configuration\Ecu\Ecud_CanNm.arxml           
*                  Configuration\Ecu\Ecud_CanSM.arxml           
*                  Configuration\Ecu\Ecud_ComM.arxml            
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Ecu\Ecud_Nm.arxml              
*                  Configuration\Ecu\Ecud_PduR.arxml            
*                  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml
*                  Configuration\System\DBImport\DataTypes\CanStack_DataTypes.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_CanNm.arxml 
*                  Static_Code\Modules\CanIf_R44\generator\CanIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanNm_R44\generator\CanNm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanSM_R44\generator\CanSM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\ComM_R44\generator\ComM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Nm_R44\generator\Nm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\PduR_R44\generator\PduR_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

#ifndef CANNM_CFG_H
#define CANNM_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion for Communication Stack types */
#include "ComStack_Types.h"

/*******************************************************************************
**                      Published Information                                 **
*******************************************************************************/
/* @Trace: CanNm_SUD_MACRO_001 */
#define    CANNM_AR_RELEASE_MAJOR_VERSION                0x04u
#define    CANNM_AR_RELEASE_MINOR_VERSION                0x04u
#define    CANNM_AR_RELEASE_REVISION_VERSION             0x00u
#define    CANNM_SW_MAJOR_VERSION                        0x01u
#define    CANNM_SW_MINOR_VERSION                        0x02u
#define    CANNM_SW_PATCH_VERSION                        0x00u
#define    CANNM_VENDOR_ID                               0x004Cu
#define    CANNM_MODULE_ID                               0x001Fu
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: CanNm_SUD_MACRO_003 */
/* Pre-compile option for CanNmActiveWakeupBitEnabled is mixed with enabled and disabled */
#define CANNM_ACTIVE_WAKEUP_BIT_ENABLE_DISABLE_MIXED  (STD_OFF)

/* Pre-compile option for CanNmActiveWakeupBitEnabled is enabled */
#define CANNM_ACTIVE_WAKEUP_BIT_ENABLED               (STD_ON)

/* Pre-compile option for Nm State byte Position is enabled and disable is mixed */
#define CANNM_NMS_POSITION_ENABLE_DISABLE_MIXED       (STD_OFF)

/* Pre-compile option for Nm State byte Position is enabled */
#define CANNM_NMS_POSITION_ENABLED                    (STD_ON)

/* Pre-compile option for Network Request Reason Position is enabled and disable is mixed */
#define CANNM_REASON_POSITION_ENABLE_DISABLE_MIXED    (STD_OFF)

/* Pre-compile option for Network Request Reason Position is enabled */
#define CANNM_REASON_POSITION_ENABLED                 (STD_ON)

/* Pre-compile option for enables/disables CarWakeUp feature. */
#define CANNM_CAR_WAKE_UP_RX_ENABLED                  (STD_OFF)

/* Definition for value of CanNm channel Id configured. */
#define CANNM_NUMBER_OF_CHANNEL                       ((uint8)1)

/* Call cycle in seconds of CanNm_MainFunction. */
#define CANNM_MAINFUNCTION_PERIOD                     ((uint8)0.005)

/* Specifies the runtime of the reset timer in seconds. */
#define CANNM_PN_RESET_TIME                           ((uint8)100)

/* Pre-compile option for enables/disables the node detection feature. */
#define CANNM_NODE_DETECTION_ENABLED                  (STD_ON)

/* Pre-compile option for enables/disables the source node identifier. */
#define CANNM_NODE_ID_ENABLED                         (STD_ON)

/* Eira Pdu ID */
#define CANNM_PN_EIRA_RXNSDU                          ((uint8)9)

/* Pre-compile option for enables/disables busload reduction support. */
#define CANNM_BUS_LOAD_REDUCTION_ENABLED              (STD_OFF)

/* Pre-compile option for enables/disables bus synchronization support.
This feature is required for gateway nodes only. */
#define CANNM_BUS_SYNCHRONIZATION_ENABLED             (STD_OFF)

/* Pre-compile option for enables/disables the Communication Control support. */
#define CANNM_COM_CONTROL_ENABLED                     (STD_ON)

/* Pre-compile option for enables/disables the Tx path of Com User Data. */
#define CANNM_COM_USERDATA_SUPPORT                    (STD_ON)

/* Pre-compile option for enables/disables the coordinator synchronization. */
#define CANNM_COORDINATOR_SYNC_SUPPORT                (STD_OFF)

/* Pre-compile option for enabling Development error detection */
#define CANNM_DEV_ERROR_DETECT                        (STD_ON)

/* Pre-compile option for enables/disables partial networking. */
#define CANNM_GLOBAL_PN_SUPPORT                       (STD_ON)

/* Pre-compile option for enables/disables the immediate transmission of 
           a NM PDU upon bus-communication request in Prepare-Bus-Sleep mode. */
#define CANNM_IMMEDIATE_RESTART_ENABLED               (STD_OFF)

/* Pre-compile option for enables/disables the immediate tx confirmation. */
#define CANNM_IMMEDIATE_TXCONF_ENABLED                (STD_OFF)

/* Pre-compile option for enables/disables the Passive Mode. */
#define CANNM_PASSIVE_MODE_ENABLED                    (STD_OFF)

/* Pre-compile option for enables/disables the PDU Rx Indication. */
#define CANNM_PDU_RXINDICATION_ENABLED                (STD_OFF)

/* Pre-compile option for enables/disables the PN request information for 
                                        internal an external requests. (EIRA) */
#define CANNM_PN_EIRA_CALC_ENABLED                    (STD_ON)

/* Pre-compile option for enables/disables remote sleep indication support. */
#define CANNM_REMOTE_SLEEP_INDICATE_ENABLED           (STD_OFF)

/* Pre-compile option for enables/disables CAN NM state change notification. */
#define CANNM_STATE_CHANGE_INDICATE_ENABLED           (STD_OFF)

/* Pre-compile option for enables/disables user data support. */
#define CANNM_USER_DATA_ENABLED                       (STD_ON)

/* Pre-compile option for enables/disables version info API support. */
#define CANNM_VERSION_INFO_API                        (STD_ON)

/* Pre-compile option for enables/disables the PN request information for 
        internal an external requests. (EIRA) */
#define CANNM_REPEAT_MSG_IND_ENABLED                  (STD_ON)

/* Pre-compile option for Cbv Position OFF Present */
#define CANNM_CBV_POS_OFF_PRESENT                     (STD_OFF)

/* Pre-compile option for Pn Disabled Present */
#define CANNM_PN_DISABLED_PRESENT                     (STD_OFF)

/* Pre-compile option for Handle Multiple Request Enabled Present */
#define CANNM_HANDLE_MULTI_REQUEST_PRESENT            (STD_OFF)

/* Pre-compile option for All Nm Messages Keep Awake Enabled Present */
#define CANNM_ALL_NM_MESSAGES_KEEP_AWAKE_PRESENT      (STD_OFF)

/* Pre-compile option for Busload Reduction Active Enabled Present */
#define CANNM_BUSLOAD_REDUCTION_ACTIVE_PRESENT        (STD_OFF)

/* Pre-compile option for Force Pn Availability Enabled Present */
#define CANNM_FORCEPNAVAILABILITYCONFENABLED_PRESENT  (STD_ON)

/* Pre-compile option for enables/disables the Passive Node. */
#define CANNM_PASSIVE_NODE_ENABLED                    (STD_OFF)

/* Pre-compile option for enables/disables postbuild. */
#define CANNM_POSTBUILD_SUPPORTED                     (STD_OFF)

/* Number of Configured Rx Pdu on all channel. */
#define CANNM_NUMBER_OF_RXPDU                         ((uint8)1)

/* Number of Configured Tx Pdu on all channel. */
#define CANNM_NUMBER_OF_TXPDU                         ((uint8)1)

/* Pre-compile option for enables/disables the PN request information for 
        internal an external requests. (EIRA) */
#define CANNM_PN_ERA_CALC_ENABLED                     (STD_OFF)

/* Number of Pn filter mask byte */
#define CANNM_NUMBER_OF_PN_FILTER_MASK_BYTE           ((uint8)4)

/* Pre-compile option for enables/disables trigger transmit API support. */
#define CANNM_TRIGGER_TRANSMIT_ENABLED                (STD_ON)

/* Pre-compile option for CanIf Trigger Transmit Enabled Present */
#define CANNM_CANIF_TRIGGER_TRANSMIT_ENABLE_PRESENT   (STD_OFF)

/*Symbolic Name CanNmTxPdu*/
#define CanNmTxPdu_NmPdu_FD_CAN1_NM_CGW 0

/*Symbolic Name CanNmRxPdu*/
#define CanNmRxPdu_IN_ECU1_FD_CAN1_CANNM_MESSAGE 0


/*******************************************************************************
**                      Precompile options                                    **
*******************************************************************************/
#endif/* #ifndef CANNM_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
