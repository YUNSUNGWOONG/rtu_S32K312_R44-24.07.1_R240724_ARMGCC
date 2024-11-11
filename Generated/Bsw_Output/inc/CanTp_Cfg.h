/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Co., Ltd.                                       **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE:           CanTp_Cfg.h                                         **
**                                                                            **
**  PRODUCT   :           AUTOSAR CAN Transport Layer Module                  **
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

********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CanIf.arxml           
*                  Configuration\Ecu\Ecud_CanTp.arxml           
*                  Configuration\Ecu\Ecud_Com.arxml             
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Ecu\Ecud_PduR.arxml            
*                  Generated\Bsw_Output\bswmd\Bswmd_CanTp.arxml 
*                  Static_Code\Modules\CanIf_R44\generator\CanIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanTp_R44\generator\CanTp_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Com_R44\generator\Com_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\PduR_R44\generator\PduR_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/
#ifndef CANTP_CFG_H
#define CANTP_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "ComStack_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

#define    CANTP_CFG_AR_RELEASE_MAJOR_VERSION            0x04u
#define    CANTP_CFG_AR_RELEASE_MINOR_VERSION            0x04u
#define    CANTP_CFG_AR_RELEASE_REVISION_VERSION         0x00u
#define    CANTP_CFG_SW_MAJOR_VERSION                    0x01u
#define    CANTP_CFG_SW_MINOR_VERSION                    0x01u
#define    CANTP_CFG_SW_PATCH_VERSION                    0x00u

/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/

#define    CANTP_AR_RELEASE_MAJOR_VERSION                0x04u
#define    CANTP_AR_RELEASE_MINOR_VERSION                0x04u
#define    CANTP_AR_RELEASE_REVISION_VERSION             0x00u
#define    CANTP_SW_MAJOR_VERSION                        0x01u
#define    CANTP_SW_MINOR_VERSION                        0x01u
#define    CANTP_SW_PATCH_VERSION                        0x00u
#define    CANTP_VENDOR_ID                               0x004Cu
#define    CANTP_MODULE_ID                               0x0023u

/*******************************************************************************
**                      Pre-Compile Options                                   **
*******************************************************************************/

/* Pre-compile option for support Post-Build */
#define CANTP_VARIANT_POSTBUILD_SUPPORT               (STD_OFF)

/* Pre-compile option for Change Parameter API */
 #define CANTP_CHANGE_PARAMETER_API            (STD_OFF)

/* Pre-compile option for Development Error Checking */
 #define CANTP_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
 #define CANTP_VERSION_INFO_API                (STD_ON)

/* Pre-compile option for Enabling Transmit Cancellation */
 #define CANTP_TC                              (STD_ON)

/* Pre-compile option for Enabling All Transmit Cancellation */
 #define CANTP_TC_ALL                          (STD_ON)

/* Pre-compile option for Transmit NSdu Container */
 #define CANTP_TX_NSDU                         (STD_ON)

/* Pre-compile option for Receive NSdu Container */
 #define CANTP_RX_NSDU                         (STD_ON)

/* Pre-compile option for TX PDU physical addressing */
 #define CANTP_TX_PHYSICAL_ADDRESSING          (STD_ON)

/* Pre-compile option for TX PDU extended address */
 #define CANTP_TX_EXTENDED_ADDRESS             (STD_OFF)

/* Pre-compile option for Tx PDU Mixed address */
  #define CANTP_TX_MIXED_ADDRESS               (STD_OFF)

/* Pre-compile option for Tx PDU Mixed 29bit address */
 #define CANTP_TX_MIXED29BIT_ADDRESS           (STD_OFF)

/*  Pre-compile option for TX PDU functional addressing */
 #define CANTP_TX_FUNCTIONAL_ADDRESSING        (STD_OFF)

/* Pre-compile option for Tx PDU Normal Fixed address */
 #define CANTP_TX_NORMALFIXED_ADDRESS          (STD_OFF)

/* Pre-compile option for TX SDU padding activation */
 #define CANTP_TX_SDU_PADDING_ACTIVATION       (STD_ON)

/* Pre-compile option for TX NPDU */
 #define CANTP_TX_NPDU                         (STD_ON)

/* Pre-compile option for RX NPDU */
 #define CANTP_RX_NPDU                         (STD_ON)

/* Pre-compile option for Rx PDU Mixed address */
 #define CANTP_RX_MIXED_ADDRESS                (STD_OFF)

/* Pre-compile option for Rx PDU Mixed 29bit address */
 #define CANTP_RX_MIXED29BIT_ADDRESS           (STD_OFF)

/* Pre-compile option for Rx PDU Normal Fixed address */
 #define CANTP_RX_NORMALFIXED_ADDRESS          (STD_OFF)

/* Pre-compile option for RX PDU functional addressing */
 #define CANTP_RX_FUNCTIONAL_ADDRESSING        (STD_ON)

/* Pre-compile option for Rx physical addressing */
 #define CANTP_RX_PHYSICAL_ADDRESSING          (STD_ON)

/* All RxExtPdus configured */
 #define CANTP_ADDRESSING_MODE_ALL             (STD_ON)

/* All Rx uses padding all on */
 #define CANTP_RXNDSU_PADDING_ALL_ON           (STD_ON)

/* All Rx uses padding all off */
 #define CANTP_RXNDSU_PADDING_ALL_OFF          (STD_OFF)

/* All Rx uses padding on off mixed */
 #define CANTP_RXNDSU_PADDING_ON_OFF_MIXED     (STD_OFF)

/* CanTp uses FD message */
 #define CANTP_TX_DL_GREATER_THAN_8            (STD_ON)

/* Pre-compile option for RX SDU padding activation */
 #define CANTP_RX_SDU_PADDING_ACTIVATION       (STD_ON)

/* Pre-compile option for Read parameter API */
 #define CANTP_READ_PARAMETER_API              (STD_OFF)

/* Pre-compile option for RX PDU extended address */
 #define CANTP_RX_EXTENDED_ADDRESS             (STD_OFF)

/* Pre-compile option for CAN-FD Support */
 #define CANTP_FD_SUPPORT                      (STD_ON)

/* Support generic connection with MetaData */
 #define CANTP_GENERIC_CONNECTION_SUPPORT      (STD_ON)

/* Dynamic ID handling via N-PDU MetaData */
 #define CANTP_DYNID_SUPPORT                   

/* Tx NSdu with MetaData */
 #define CANTP_TX_NSDU_METADATA                (STD_OFF)

/* Rx NPdu with MetaData */
 #define CANTP_RX_NPDU_METADATA                (STD_OFF)

/* Rx NSdu with MetaData */
 #define CANTP_RX_NSDU_METADATA                (STD_OFF)



/*******************************************************************************
**                      Macros definition                                     **
*******************************************************************************/
typedef uint8 CanTp_ChannelType;

/* Transmit frame padding byte */
 #define CANTP_PADDING_BYTE                    ((uint8)85)

/* Main function Period */
 #define CANTP_MAIN_FUNCTION_PERIOD            (5)

/* Number of receive N-PDU this symbol represents the number of RxNPduids */
 #define CANTP_MAXNO_RX_NPDU                   ((uint16)3)

/* Maximum receive SDU ID this symbol represents the number of RxNSdus */
 #define CANTP_MAXNO_RX_SDU                    ((uint16)3)

/* Number of Rx and Tx connection channels configured in CanTp */
 #define CANTP_TOTAL_RX_TX_CHANNELS            (3)

/* Maximum number of confirmation PduId */
 #define CANTP_MAX_CONFIRM_ID                  ((uint16)1)

/* Maximum Rx Indication PduId configured */
 #define CANTP_MAX_INDIC_ID                    ((uint16)2)

/* Maximum transmit SDU ID */
 #define CANTP_MAX_TX_SDUID                    ((uint16)1)

/* Maximum receive SDU ID */
 #define CANTP_MAX_RX_SDUID                    ((uint16)2)

/* This symbol represents the lowest Rx flow control Id which is configured */
 #define CANTP_RX_FCPDU_START                  (0)

/* This symbol represents the max RxFCNPdu flow control Id which is configured */
 #define CANTP_MAX_RX_FCNPDUID                 ((uint16)1)

/* Number of  RxExtFcPdus */
 #define CANTP_NO_OF_RXEXTFCPDUS               ((uint16)2)

/* Number of  RxExtPdus */
 #define CANTP_NO_OF_RXEXTPDUS                 ((uint16)3)

/* Number of  RxSduStatic */
 #define CANTP_NO_OF_RXSDUSTATIC               ((uint16)3)

/* Number of  TxSduStatic */
 #define CANTP_NO_OF_TXSDUSTATIC               ((uint16)2)

/* Number of  RxSduMap for TxFcNPdu */
 #define CANTP_NO_OF_RXSDUMAP                  ((uint16)2)

/* Number of  Channel Mapping for RxNPdu and RxFcNPdu */
 #define CANTP_NO_OF_NSAORNAESDUMAPPING        ((uint16)0)

/* Max payload */
 #define CANTP_FD_MAX_DLC                      (64)

/* Max length of metaData */
 #define CANTP_METADATA_LEN_MAX                (1)



/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* Configuration Set Handles */
#define CanTpConfig                            (&CanTp_Config[0])


#endif /* #ifndef CANTP_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
