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
**  SRC-MODULE:           Nm_Cfg.h                                            **
**                                                                            **
**  PRODUCT   :           AUTOSAR Network Management Interface Module         **
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
**  Module Version   : 1.0.5.0                                                **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CanNm.arxml           
*                  Configuration\Ecu\Ecud_ComM.arxml            
*                  Configuration\Ecu\Ecud_Nm.arxml              
*                  Generated\Bsw_Output\bswmd\Bswmd_Nm.arxml    
*                  Static_Code\Modules\CanNm_R44\generator\CanNm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\ComM_R44\generator\ComM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Nm_R44\generator\Nm_ECU_Configuration_PDF.arxml
* GENERATED ON:    11-Nov-2024 - 12:59:14                       
*/

#ifndef NM_CFG_H
#define NM_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
/* @Trace: Nm_SUD_MACRO_001 */
#define NM_AR_RELEASE_MAJOR_VERSION                        (0x04u)
#define NM_AR_RELEASE_MINOR_VERSION                        (0x04u)
#define NM_AR_RELEASE_REVISION_VERSION                     (0x00u)
#define NM_SW_MAJOR_VERSION                                (0x01u)
#define NM_SW_MINOR_VERSION                                (0x00u)
#define NM_SW_PATCH_VERSION                                (0x05u)
#define NM_VENDOR_ID                                       (76u)
#define NM_MODULE_ID                                       (29u)


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* Definition for Number of Nm channels allowed within one ECU */
#define NM_NO_OF_CHANNELS                                         (1u)


/* Definition for maximum value of Nm channel Id configured */
#define NM_MAX_CHANNEL_ID                                         (0u)

/* @Trace: Nm_SUD_MACRO_008 */
/*Pre-compile option for DET error detection */
#define NM_DEV_ERROR_DETECT                                       (STD_ON)

/* Pre-compile option for Version Info API */
#define NM_VERSION_INFO_API                                       (STD_ON)

/* Pre-compile option for enabling bus synchronization support */
#define NM_BUS_SYNCHRONIZATION_ENABLED                            (STD_OFF)

/* Pre-compile option for enabling CWU detection */
#define NM_CAR_WAKE_UP_RX_ENABLED                                 (STD_OFF)

/* Pre-compile option for enabling the Communication Control support */
#define NM_COM_CONTROL_ENABLED                                    (STD_ON)

/* Pre-compile option for enabling the Coordinator support */
#define NM_COORDINATOR_SUPPORT_ENABLED                            (STD_OFF)

/* Pre-compile option for enabling the Coordinator Sync support */
#define NM_COORDINATOR_SYNC_SUPPORT                               (STD_OFF)

/* Pre-compile option for enabling the PDU Rx Indication */
#define NM_PDU_RX_INDICATION_ENABLED                              (STD_OFF)

/* Pre-compile option for enabling Remote Sleep Indication support */
#define NM_REMOTE_SLEEP_IND_ENABLED                               (STD_OFF)

/* Pre-compile option for enabling the NM state change notification */
#define NM_STATE_CHANGE_IND_ENABLED                               (STD_OFF)

/* Pre-compile option for enabling User Data support */
#define NM_USER_DATA_ENABLED                                      (STD_ON)

/* Pre-compile option for checking AR Version of CanNm module */
#define NM_CANNM_ENABLED                                          (STD_ON)

/* Pre-compile option for checking AR Version of FrNm module */
#define NM_FRNM_ENABLED                                           (STD_OFF)

/* Pre-compile option for checking AR Version of UdpNm module */
#define NM_UDPNM_ENABLED                                          (STD_OFF)

/* Pre-compile option for checking AR Version of J1939Nm module */
#define NM_J1939NM_ENABLED                                        (STD_OFF)

/* Pre-compile option for checking AR Version of OsekNm module */
#define NM_OSEKNM_ENABLED                                         (STD_OFF)


/* Pre-compile option indicates if NmPduRxIndUserCallout is configured */
#define NM_PDU_RX_IND_USER_CALLOUT                                (STD_OFF)

/* Pre-compile option indicates if NmStateChangeIndUserCallout is configured */
#define NM_STATE_CHANGE_IND_USER_CALLOUT                          (STD_OFF)

/* Pre-compile option indicates if NmRepeatMsgIndUserCallout is configured */
#define NM_REPEAT_MSG_IND_USER_CALLOUT                            (STD_OFF)

/* Pre-compile option indicates if NmTxTimeoutExceptionUserCallout
 * is configured
 */
#define NM_TX_TIMEOUT_EXCEPTION_USER_CALLOUT                       (STD_OFF)

/* Pre-compile option Implementation Class */
#define NM_VARIANT_POSTBUID_SUPPORT                               (STD_OFF)



#endif /* #ifndef NM_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
