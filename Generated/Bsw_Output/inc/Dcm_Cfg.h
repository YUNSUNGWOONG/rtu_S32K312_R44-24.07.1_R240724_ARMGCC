/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  FILE-NAME:  Dcm_Cfg.h                                                     **
**                                                                            **
**  MODULE-NAME: AUTOSAR DCM Module                                           **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Module version: 1.4.2.0
**  Framework version: 1.1.5
********************************************************************************

********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_ComM.arxml            
*                  Configuration\Ecu\Ecud_Csm.arxml             
*                  Configuration\Ecu\Ecud_Dcm.arxml             
*                  Configuration\Ecu\Ecud_Dem.arxml             
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Ecu\Ecud_KeyM.arxml            
*                  Configuration\Ecu\Ecud_NvM.arxml             
*                  Configuration\Ecu\Ecud_PduR.arxml            
*                  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_Dcm.arxml   
*                  Generated\Bsw_Output\bswmd\Bswmd_Dem.arxml   
*                  Generated\Bsw_Output\bswmd\Bswmd_NvM.arxml   
*                  Static_Code\Modules\ComM_R44\generator\ComM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Csm_R44\generator\Csm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Dcm_R44\generator\Dcm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Dem_R44\generator\Dem_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\KeyM_R44\generator\KeyM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\NvM_R44\generator\NvM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\PduR_R44\generator\PduR_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#ifndef DCM_CFG_H
#define DCM_CFG_H
#include "ComStack_Types.h"


/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
#define    DCM_AR_RELEASE_MAJOR_VERSION                  0x04u
#define    DCM_AR_RELEASE_MINOR_VERSION                  0x04u
#define    DCM_AR_RELEASE_REVISION_VERSION               0x00u
#define    DCM_SW_MAJOR_VERSION                          0x01u
#define    DCM_SW_MINOR_VERSION                          0x00u
#define    DCM_SW_PATCH_VERSION                          0x00u
#define    DCM_VENDOR_ID                                 0x004Cu
#define    DCM_MODULE_ID                                 0x0035u


/*******************************************************************************
**                      Pre-compile Options                                   **
*******************************************************************************/
/*  */
#define DCM_TASK_TIME (5)

/*  */
#define DCM_DEV_ERROR_DETECT (STD_ON)

/*  */
#define DCM_RESPOND_ALL_REQUEST (STD_ON)

/*  */
#define DCM_VERSION_INFO_API (STD_ON)

/*  */
#define DCM_VIN_REF_CONFIGURED (STD_ON)

/*  */
#define DCM_STANDARD_SUPPORT (DCM_ES95486_SUPPORT)

/*  */
#define DCM_AUTRON_FBL_USED (STD_ON)

/*  */
#define DCM_REMAIN_UNLOCK_CONDITION (STD_OFF)

/*  */
#define DCM_DDDID_STORAGE (STD_OFF)

/*  */
#define DCM_DDDID_STORAGE_BLOCK_ID (0)

/*  */
#define DCM_PARALLEL_PROTOCOL_PROCESSING (STD_OFF)

/*  */
#define DCM_DEM_CONFIGURED (STD_ON)

/*  */
#define DCM_NVM_CONFIGURED (STD_ON)

/*  */
#define DCM_NUM_OF_BUFFER_CONFIG (4)

/*  */
#define DCM_TOTAL_NUM_OF_CALLBACK_REQUEST (1)

/*  */
#define DCM_RESPONSEON_SECOND_DECLINE_REQUEST (STD_ON)

/*  */
#define DCM_NUM_OF_PROTOCOLCONFIG (3)

/*  */
#define DCM_NUM_OF_PDUIDTABLECONFIG (3)

/*  */
#define DCM_GENERIC_CONNECTION_HANDLING (STD_OFF)

/*  */
#define DCM_RESPONSE_ON_EVENT_SERVICE (STD_OFF)

/*  */
#define DCM_PROTOCOL_TRANSTYPE2 (STD_OFF)

/*  */
#define DCM_J1979_2_SUPPORT (STD_OFF)

/*  */
#define DCM_DIAG_RESP_MAX_NUM_RESPEND (5)

/*  */
#define DCM_NUMBER_OF_REQUEST_MANUFACTURER_INDICATION (1)

/*  */
#define DCM_NUMBER_OF_REQUEST_SUPPLIER_INDICATION (2)

/*  */
#define DCM_NUM_OF_SIDCONFIG (24)

/*  */
#define DCM_OBD_REQCURRENT_POWERTRAIN_DIAGDATA_SERVICE (STD_OFF)

/*  */
#define DCM_DSP_CLR_DIAG_SERVICE (STD_ON)

/*  */
#define DCM_COMMUNICATION_CONTROL_SERVICE (STD_ON)

/*  */
#define DCM_ENABLE_NORMAL_MSG_TRANSMISSION_SERVICE (STD_OFF)

/*  */
#define DCM_AUTHENTICATION_SERVICE (STD_OFF)

/*  */
#define DCM_READ_DATA_BYIDENTIFIER_SERVICE (STD_OFF)

/*  */
#define DCM_READ_MEMORY_BY_ADDRESS_SERVICE (STD_ON)

/*  */
#define DCM_READ_SCALINGDATA_BYIDENTIFIER_SERVICE (STD_OFF)

/*  */
#define DCM_WRITE_MEMORY_BY_ADDRESS_SERVICE (STD_ON)

/*  */
#define DCM_DSP_TESTER_PRESENT_SERVICE (STD_ON)

/*  */
#define DCM_DSP_CONTROL_DTC_SERVICE (STD_ON)

/*  */
#define DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE (STD_OFF)

/*  */
#define DCM_WRITEDATA_BYIDENTIFIER_SERVICE (STD_ON)

/*  */
#define DCM_IOCONTROL_BYIDENTIFIER_SERVICE (STD_ON)

/*  */
#define DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE (STD_OFF)

/* Pre-compile option for Read DTC support */
#define DCM_READDTC_SUPPORT (STD_ON)

/*  */
#define DCM_DSP_STOP_DIAG_SESSION_SERVICE (STD_OFF)

/*  */
#define DCM_DSP_SECURITY_SERVICE (STD_ON)

/*  */
#define DCM_FILE_TRANSFER_SERVICE (STD_OFF)

/*  */
#define DCM_REQUEST_DOWNLOAD_SERVICE (STD_ON)

/*  */
#define DCM_REQUEST_UPLOAD_SERVICE (STD_ON)

/*  */
#define DCM_TRANSFER_DATA_SERVICE (STD_ON)

/*  */
#define DCM_TRANSFER_EXIT_SERVICE (STD_ON)

/*  */
#define DCM_DSP_DIAG_SESSION_SERVICE (STD_ON)

/*  */
#define DCM_ROUTINECONTROL_SERVICE (STD_ON)

/*  */
#define DCM_RPT_DTCSNAPSHOTREC_IDENTFN (STD_OFF)

/*  */
#define DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM (STD_OFF)

/*  */
#define DCM_RPT_NOOFDTC (STD_ON)

/*  */
#define DCM_RPT_DTC (STD_OFF)

/*  */
#define DCM_RPT_DTCEXTENDEDDATARECORD (STD_OFF)

/*  */
#define DCM_RPT_DTCBYSEVERITYMASKRECORD (STD_OFF)

/*  */
#define DCM_RPT_DTCBYSEVERITYINFOFDTC (STD_OFF)

/*  */
#define DCM_RPT_FAILEDCONFIRMEDDTCINFO (STD_OFF)

/*  */
#define DCM_RPT_DTC_FLT_DET_CTR (STD_OFF)

/*  */
#define DCM_LINK_CONTROL_SERVICE (STD_ON)

/*  */
#define DCM_FAULT_DETECTION_COUNTER (STD_OFF)

/*  */
#define DCM_OBD_SUPPORT (STD_OFF)

/*  */
#define DCM_NUM_OF_GAADCMDSPDATACONFIG (9)

/*  */
#define DCM_NUM_OF_DIDPARACONFIG (12)

/*  */
#define DCM_NUM_OF_GAADCMDSPSIGNALCONFIG (18)

/*  */
#define DCM_NUM_OF_GAADIDPACKSIGNAL (18)

/*  */
#define DCM_TOTAL_NUM_OF_DIDS (12)

/*  */
#define DCM_TOTAL_NUM_OF_DYN_DID (1)

/*  */
#define DCM_TOTAL_NUM_OF_SOURCE_DYN_DID (3)

/*  */
#define DCM_NUM_OF_GAADIDINFOTYPECONFIG (13)

/*  */
#define DCM_NUM_OF_GAADIDINFOTYPEDIDREADCONFIG (13)

/*  */
#define DCM_NUM_OF_GAADIDINFOTYPEDIDWRITECONFIG (5)

/*  */
#define DCM_TOTAL_NUM_OF_PDID (3)

/*  */
#define DCM_PDID_NUM_OF_CONNECTION (1)

/*  */
#define DCM_MAX_PDID_SCHEDULER (0x06)

/*  */
#define DCM_MAX_PDID_TO_READ (0)

/*  */
#define DCM_PDID_SLOW_RATE (250)

/*  */
#define DCM_PDID_MEDIUM_RATE (200)

/*  */
#define DCM_PDID_FAST_RATE (150)

/*  */
#define DCM_NUM_OF_DCMDSPDIDRANGECONFIG (1)

/*  */
#define DCM_NUM_OF_GAADATAINFOTYPECONFIG (3)

/*  */
#define DCM_DIDSERVICE_SUPPORT_ENABLE (STD_ON)

/*  */
#define DCM_DSP_MAX_DID_SIZE (17)

/*  */
#define DCM_DATA_SYNCH_FNC (STD_OFF)

/*  */
#define DCM_DATA_ASYNCH_FNC (STD_OFF)

/*  */
#define DCM_DATA_ASYNCH_CLIENT_SERVER (STD_OFF)

/*  */
#define DCM_DATA_SYNCH_CLIENT_SERVER (STD_ON)

/*  */
#define DCM_DATA_SENDER_RECEIVER (STD_OFF)

/*  */
#define DCM_ATOMIC_SENDER_RECEIVER_ENABLE (STD_OFF)

/*  */
#define DCM_DSP_COMM_CONTROL_CONFIGURED (STD_ON)

/*  */
#define DCM_TOTAL_NUM_OF_SPECIFIC_CHANNEL (1)

/*  */
#define DCM_TOTAL_NUM_OF_ALL_CHANNEL (1)

/*  */
#define DCM_TOTAL_NUM_OF_SUBNODE (0)

/*  */
#define DCM_DSP_COMM_CONTROL_REENABLE_MODE_RULE (0)

/*  */
#define DCM_DSP_CONTROL_DTC_CONFIGURED (STD_ON)

/*  */
#define DCM_DSP_CONTROL_DTC_SUPPORT_OPTION_RECORD (STD_OFF)

/*  */
#define DCM_DSP_CONTROL_DTC_REENABLE_MODE_RULE (0)

/*  */
#define DCM_TOTAL_NUM_READ_MEMORY_CONFIGURED (1)

/*  */
#define DCM_TOTAL_NUM_WRITE_MEMORY_CONFIGURED (1)

/*  */
#define DCM_NUM_OF_ADDRESS_LENGTH_FORMAT_ID_CONFIG (1)

/*  */
#define DCM_NUM_OF_SECURITYLEVELCONFIG (1)

/*  */
#define DCM_MAX_SECURITY_SEED_SIZE (8)

/*  */
#define DCM_MAX_ATTEMPT_COUNTER_READOUT_TIME (10000)

/*  */
#define DCM_NUM_OF_DIAGSESSIONCONFIG (8)

/*  */
#define DCM_NUM_OF_GAADIDINFOTYPEDIDCTRLCONFIG (2)

/*  */
#define DCM_TOTAL_NUM_OF_STATIC_DID (11)

/*  */
#define DCM_MAX_CONTROL_MASK_SIZE (0)

/* Indicate whether the ecu reset service is configured */
#define DCM_ECURESET_SERVICE (STD_ON)

/* Indicate whether the rapid power shutdown feature is configured */
#define DCM_RAPID_POWER_SHUTDOWN_CONFIGURED (STD_OFF)

/* Indicate the number of ecu reset rows are configured */
#define DCM_NUM_OF_ECURESETCONFIG (5)

/*  */
#define DCM_DSP_CLEARDTC_CONFIGURED (STD_ON)

/* Check the parameter DcmDspClearDTCCheckFnc is configured or not  */
#define DCM_DSP_CLEARDTC_CHECK_FUNC_CONFIGURED (STD_OFF)

/*  */
#define DCM_NUM_OF_ROUTINE_CONFIG (6)

/*  */
#define DCM_NUM_OF_ROUTINE_INFO_CONFIG (8)

/*  */
#define DCM_NUM_OF_ROUTINE_SIGNAL_CONFIG (15)

/*  */
#define DCM_NUM_OF_COMMON_AUTHORIZATION (3)

/*  */
#define DCM_ROUTINE_IN_SIGNAL_ONE_BYTE (STD_ON)

/*  */
#define DCM_ROUTINE_IN_SIGNAL_TWO_BYTE (STD_OFF)

/*  */
#define DCM_ROUTINE_IN_SIGNAL_FOUR_BYTE (STD_OFF)

/*  */
#define DCM_ROUTINE_OUT_SIGNAL_ONE_BYTE (STD_ON)

/*  */
#define DCM_ROUTINE_OUT_SIGNAL_TWO_BYTE (STD_OFF)

/*  */
#define DCM_ROUTINE_OUT_SIGNAL_FOUR_BYTE (STD_OFF)

/*  */
#define DCM_NUM_OF_PACK_FUNC_CONFIG (1)

/*  */
#define DCM_NUM_OF_UNPACK_FUNC_CONFIG (1)

/*  */
#define DCM_AUTHENTICATION_ROLE_SIZE (0)

/*  */
#define DCM_AUTHENTICATION_DEFAULT_SESSION_TIMEOUT (0)

/*  */
#define DCM_AUTHENTICATION_WHITE_LIST_DID_MAX_SIZE (0)

/*  */
#define DCM_AUTHENTICATION_WHITE_LIST_MEMORY_SELECTION_MAX_SIZE (0)

/*  */
#define DCM_AUTHENTICATION_WHITE_LIST_RID_MAX_SIZE (0)

/*  */
#define DCM_AUTHENTICATION_WHITE_LIST_SERVICES_MAX_SIZE (0)

/*  */
#define DCM_AUTHENTICATION_GENERAL_NRC_MODE_RULE (STD_OFF)

/*  */
#define DCM_AUTHENTICATION_PERSIST_STATE_MODE_RULE (STD_OFF)

/*  */
#define AUTHENTICATION_MAX_DATALENGTH (0xFFFF)

/*  */
#define DCM_AUTHENTICATION_CONNECTION_NUM (0)

/*  */
#define DCM_AUTHENTICATION_CONNECTION_ES_NUM (0)

/*  */
#define DCM_DSP_AUTHENTICATION_WHITE_LIST_DID_CONFIGURED (STD_OFF)

/*  */
#define DCM_DSP_AUTHENTICATION_WHITE_LIST_MEMORY_SELECTION_CONFIGURED (STD_OFF)

/*  */
#define DCM_DSP_AUTHENTICATION_WHITE_LIST_RID_CONFIGURED (STD_OFF)

/*  */
#define DCM_AUTHENTICATION_WHITE_LIST_MAX_ELEMENT (5)

/*  */
#define DCM_AUTHENTICATION_TARGET_ID_MODE_RULE (STD_OFF)

/*  */
#define DCM_AUTHENTICATION_CERT_COMPARE_ELEMENT_MAX_LEN (0)

/*  */
#define DCM_AUTHENTICATION_ES_SUPPORT (STD_OFF)

/*  */
#define DCM_NUM_OF_USER_DEFINED_FAULT_MEMORY (0)

/*  */
#define DCM_ROE_INTER_MESSAGE_TIME (2000)

/*  */
#define DCM_NUM_OF_EVENTWINDOWTIME_SUPPORTED (2)

/*  */
#define DCM_ROE_DID_MAX_DATA_LENGTH (255)

/*  */
#define DCM_FILE_TRANSFER_USE_PORT (STD_ON)

/*  */
#define DCM_MEMORY_TRANSFER_USE_PORT (STD_ON)

/*  */
#define DCM_MAX_DID_TO_READ (0)

/*  */
#define DCM_POWERDOWN_TIME (0x02)

/*  */
#define DCM_USE_BLOCK_ID_ENABLED (STD_OFF)

/*  */
#define DCM_DYNAMIC_DID_PER_SOURCE (STD_OFF)

/*  */
#define DCM_ENABLE_OBD_MIRROR (STD_OFF)

/*  */
#define DCM_PAGEDBUFFER_ENABLED (STD_ON)

/*  */
#define DCM_MODE_RULE (STD_OFF)

/*  */
#define DCM_MODE_CONDITION (STD_OFF)

/*  */
#define DCM_DSP_MODE_RULE_NRC (STD_OFF)

/*  */
#define DCM_MODE_RULE_INDEX (STD_OFF)

/* Control random seed and key algorithm for security access service */
#define DCM_CSAC_CONFIGURED (STD_OFF)

/* Precompile option for CRL Enable */
#define DCM_SECURITY_CRL_ENABLE (STD_OFF)

/*  */
#define DCM_CRYPTO_R44_USED (STD_OFF)

/* Index for CsmInfo */
#define DCM_SECURITY_CONFIG_L21_R44_INDEX (-1)

/*  */
#define DCM_CNR_USED_SHA1 (STD_OFF)

/* Number of memory identifiers for upload download services */
#define DCM_NUM_OF_MEM_TRANSFER_ID_CONFIG (1)

/* Number of address and length format identifiers for upload download services */
#define DCM_NUM_OF_MEM_TRANSFER_ADDR_LEN_FORMAT_ID (3)

/*  */
#define DCM_MAX_NO_OF_PRECONFIGURED_DID (0)

/* Pre-compile option for Page Buffer Support */
#define DCM_NUM_OF_SECURITYLEVELSTOSID (7)

/*  */
#define DCM_TOTAL_NUM_OF_PIDS (0)

/*  */
#define DCM_NUM_OF_GAASESSIONSTOSID (130)

/*  */
#define DCM_DSP_USE_ECU_SIGNAL_UINT8 (STD_OFF)

/*  */
#define DCM_DSP_USE_ECU_SIGNAL_UINT16 (STD_OFF)

/*  */
#define DCM_DSP_USE_ECU_SIGNAL_UINT32 (STD_OFF)

/*  */
#define DCM_DSP_USE_ECU_SIGNAL_SINT8 (STD_OFF)

/*  */
#define DCM_DSP_USE_ECU_SIGNAL_SINT16 (STD_OFF)

/*  */
#define DCM_DSP_USE_ECU_SIGNAL_SINT32 (STD_OFF)

/*  */
#define DCM_READ_WRITE_SEND_RECV_UINT8 (STD_OFF)

/*  */
#define DCM_READ_WRITE_SEND_RECV_SINT8 (STD_OFF)

/*  */
#define DCM_READ_WRITE_SEND_RECV_UINT16 (STD_OFF)

/*  */
#define DCM_READ_WRITE_SEND_RECV_SINT16 (STD_OFF)

/*  */
#define DCM_READ_WRITE_SEND_RECV_UINT32 (STD_OFF)

/*  */
#define DCM_READ_WRITE_SEND_RECV_SINT32 (STD_OFF)

/*  */
#define DCM_OBD_DID_SUPPORT_INFO (STD_OFF)

/*  */
#define DCM_USE_ECU_SIGNAL_ENABLED (STD_OFF)

/*  */
#define DCM_NUM_OF_ROE_EVENT_CONFIG (2)

/*  */
#define DCM_NUM_OF_ATTEMPT_COUNTER_ENABLE (0)

/*  */
#define DCM_NO_OF_COMM_CHANNELS (3)

/*  */
#define DCM_NUM_OF_SUBSERVICEIDCONFIG (63)

/*  */
#define DCM_USE_FNC_ENABLED (STD_OFF)

/*  */
#define DCM_RESPONSE_ONEVENT_BLOCKID (0)

/*  */
#define DCM_TOTAL_BUFFER_CONFIG (550)

/*  */
#define DCM_ROE_ONDTCSTATUS_CHANGE_INDEX (0)

/*  */
#define DCM_TOTAL_NUM_OF_TIDS (1)

/*  */
#define DCM_NUM_OF_REQ_CONTROL (1)

/*  */
#define DCM_TOTAL_NUM_OF_VIDS (2)

/* Pre-compile option for session configure of DcmDspReadMemoryRangeSessionLevelRef */
#define DCM_IS_SESSION_IN_READ_MEMORY_RANGE_CONFIGURED (STD_OFF)

/* Pre-compile option for security configure of DcmDspReadMemoryRangeSecurityLevelRef */
#define DCM_IS_SECURITY_IN_READ_MEMORY_RANGE_CONFIGURED (STD_OFF)

/* Pre-compile option for IdValue configured of DcmDspMemoryIdValue */
#define DCM_IS_MEMORY_IDVALUE_CONFIGURED (STD_OFF)

/* Pre-compile option for session configured of DcmDspWriteMemoryRangeSessionLevelRef */
#define DCM_IS_SESSION_IN_WRITE_MEMORY_RANGE_CONFIGURED (STD_OFF)

/* Pre-compile option for security configure of DcmDspWriteMemoryRangeSecurityLevelRef */
#define DCM_IS_SECURITY_IN_WRITE_MEMORY_RANGE_CONFIGURED (STD_OFF)

/* Pre-compile for using TransferRequestParameterRecord of RequestTransferExit (0x37) service */
#define DCM_TRANSFER_REQUEST_PARAM_RECORD_USED (STD_OFF)

/* Pre-compile for size of TransferRequestParameterRecord in the request for RequestTransferExit (0x37) service */
#define DCM_TRANSFER_REQUEST_PARAM_RECORD_SIZE (0)

/*  */
#define DCM_AUTHENTICATION_WAITING_ASYNCFUNC_TIME (0)

/* Pre-compile for DcmSwcSRDataElementRef refer to DcmDspExternalSRDataElementClass   */
#define DCM_MODE_CONDITION_SR_DID_USED (STD_OFF)

/* Pre-compile for DcmSwcSRDataElementRef refer to DcmDspPidService01ExternalSRDataElementClass  */
#define DCM_MODE_CONDITION_SR_PID_USED (STD_OFF)

/*   */
#define DCM_MODE_CONDITION_MAX_NUMBER_OF_DATA_ELEMENT (0)

/* Macro for Obd Uds Dtc Separation support */
#define DCM_OBD_UDS_DTC_SEPARATION_SUPPORT (STD_OFF)

/* Pre-compile option for Freeze Frame Data Support */
#define    DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE (STD_OFF)

/* Pre-compile option for Get DTC 03 Support */
#define    DCM_OBD_GETDTC_03_SERVICE                     (STD_OFF)

/* Pre-compile option for Emission Diag Info Support */
#define    DCM_OBD_CLRRESET_EMISSION_DIAGINFO_SERVICE    (STD_OFF)

/* Pre-compile option for Monitor Result Support */
#define    DCM_OBD_REQ_ONBOARD_MONITORRESULT_SERVICE     (STD_OFF)

/* Pre-compile option for Get DTC 07 Support */
#define    DCM_OBD_GETDTC_07_SERVICE                     (STD_OFF)

/* Pre-compile option for On Board System Service Support */
#define    DCM_OBD_REQ_CTLRL_ONBOADSYSTEM_SERVICE        (STD_OFF)

/* Pre-compile option for Veh Info Support */
#define    DCM_OBD_REQVEHICLE_INFO_SERVICE               (STD_OFF)

/* Pre-compile option for Get DTC 0A Support */
#define    DCM_OBD_GETDTC_0A_SERVICE                     (STD_OFF)

/* Macro total number of Support Address configured */
#define    DCM_TOTAL_NUM_OF_OBD_DID                      (0)

/* Pre-compile option for Protocol TransType2 */
#define    DCM_OBD_PID_SUPPORT_INFO                      (STD_OFF)

/* Pre-compile option for DcmDspDataUsePort as USE_DATA_SYNCH_CLIENT_SERVER */
#define    DCM_PID_DATA_SYNCH_CLIENT_SERVER              (STD_OFF)

/* Pre-compile option for DcmDspDataUsePort as USE_DATA_SENDER_RECEIVER */
#define    DCM_PID_DATA_SENDER_RECEIVER                  (STD_OFF)

/* Pre-compile option for DcmDspDataUsePort as USE_DATA_SENDER_RECEIVER */
#define    DCM_PID_DATA_SENDER_RECEIVER_AS_SERVICE       (STD_OFF)

/* Pre-compile option for DcmDspDataUsePort as USE_DATA_SYNCH_FNC */
#define    DCM_PID_DATA_SYNCHCLIENT_FNC                  (STD_OFF)

/* Precompile option for sub-services 0x04 of UDS 0x19 service */
#define    DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM               (STD_ON)

/* Pre-compile option for total number of S1 PID config */
#define    DCM_TOTAL_NUM_OF_S1_PIDS                      (0)

/* Pre-compile option for total number of Veh InfoType Config */
#define    DCM_TOTAL_NUM_OF_VEHINFOTYPE                  (2)

/* Pre-compile option for DcmDspDataUseType as UINT8 */
#define    DCM_DSP_PID_UINT8                             (STD_OFF)

/* Pre-compile option for DcmDspDataUseType as UINT16 */
#define    DCM_DSP_PID_UINT16                            (STD_OFF)

/* Pre-compile option for DcmDspDataUseType as UINT32 */
#define    DCM_DSP_PID_UINT32                            (STD_OFF)

/* Pre-compile option for DcmDspDataUseType as SINT8 */
#define    DCM_DSP_PID_SINT8                             (STD_OFF)

/* Pre-compile option for DcmDspDataUseType as SINT16 */
#define    DCM_DSP_PID_SINT16                            (STD_OFF)

/* Pre-compile option for DcmDspDataUseType as SINT32 */
#define    DCM_DSP_PID_SINT32                            (STD_OFF)

/* Pre-compile option for DcmDspDataUseType as BOOLEAN */

#define    DCM_DSP_PID_BOOLEAN                           (STD_OFF)

/* Pre-compile option for DcmDspDataUseType as UINT8_N */

#define    DCM_DSP_PID_UINT8_N                           (STD_OFF)

/* Pre-compile option for DcmDspDataUseType as SINT8_N */

#define    DCM_DSP_PID_SINT8_N                           (STD_OFF)

/* Pre-compile option for DcmDspDataUseType as UINT16_N */

#define    DCM_DSP_PID_UINT16_N                          (STD_OFF)

/* Pre-compile option for DcmDspDataUseType as SINT16_N */

#define    DCM_DSP_PID_SINT16_N                          (STD_OFF)

/* Pre-compile option for DcmDspDataUseType as UINT32_N */

#define    DCM_DSP_PID_UINT32_N                          (STD_OFF)

/* Pre-compile option for DcmDspDataUseType as SINT32_N */

#define    DCM_DSP_PID_SINT32_N                          (STD_OFF)

/* Pre-compile option for DCM VID AVL CONFIG LIST */
#define    DCM_VID_AVL_CONFIG_LIST                       ((uint8)0x01)

/* Pre-compile option for DCM TID AVL CONFIG LIST */
#define    DCM_TID_AVL_CONFIG_LIST                       ((uint8)0x01)

/*   */
#define    DCM_OBD_DID_AVL_CONFIG_LIST                   ((uint8)0x00)

/*   */
#define    DCM_INFOTYPE_DID_AVL_CONFIG_LIST              ((uint8)0x00)

/* Pre-compile option for PID LIST FREEZE FRAME */
#define    DCM_PID_AVL_CONFIG_LIST_FREEZE_FRAME          ((uint8)0x00)

 /* Pre-compile option for PID LIST   */
#define    DCM_PID_AVL_CONFIG_LIST                       ((uint8)0x00)

/* To indicate OBDMID Config list */
#define DCM_OBDMID_AVL_CONFIG_LIST ((uint8) 0x00)

/* Pre-compile option for Total number of ObdMids Configured */
#define DCM_TOTAL_NUM_OF_OBDMIDS ((uint8) 0x00)

/* Pre-compile option for InternalTroubleCodes Support */
#define DCM_CLEAR_ITC_SERVICE_SUPPRT (STD_OFF)
#define DCM_READ_ITC_SERVICE_SUPPRT (STD_OFF)

/* Pre-compile option to check whether DLT funtion is referred or NO */
#define    DCM_DLT_USE_FUNC (STD_OFF)

#define DcmConf_DcmDslProtocolRow_UDS_ON_CAN  ((Dcm_ProtocolType)DCM_UDS_ON_CAN)

#define DcmConf_DcmDspSecurityRow_L1                       ((Dcm_SecLevelType)1)
#define DcmConf_DcmDspSecurityRow_L9                       ((Dcm_SecLevelType)9)
#define DcmConf_DcmDspSecurityRow_L10                       ((Dcm_SecLevelType)10)

#define DcmConf_DcmDspSessionRow_DCM_DEFAULT_SESSION        ((Dcm_SesCtrlType)1)
#define DcmConf_DcmDspSessionRow_DCM_PROGRAMMING_SESSION    ((Dcm_SesCtrlType)2)
#define DcmConf_DcmDspSessionRow_DCM_EXTENDED_DIAGNOSTIC_SESSION ((Dcm_SesCtrlType)3)
#define DcmConf_DcmDspSessionRow_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION ((Dcm_SesCtrlType)4)
#define DcmConf_DcmDspSessionRow_DCM_ECU_PROGRAMMING_MODE  ((Dcm_SesCtrlType)5)
#define DcmConf_DcmDspSessionRow_DCM_EXTENDED_DIAGNOSTIC_MODE ((Dcm_SesCtrlType)16)
#define DcmConf_DcmDspSessionRow_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE ((Dcm_SesCtrlType)80)
#define DcmConf_DcmDspSessionRow_DCM_SLEEP_MODE_START_REQUEST ((Dcm_SesCtrlType)81)

#define DcmConf_DcmDslProtocolRx_PhysicalRequest           ((PduIdType)0)
#define DcmConf_DcmDslProtocolRx_FunctionalRequest         ((PduIdType)1)
#define DcmConf_DcmDslProtocolTx_Response                  ((PduIdType)0)



#endif /* DCM_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
