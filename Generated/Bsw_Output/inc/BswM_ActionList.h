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
**  FILE-NAME : BswM_ActionList.h                                             **
**                                                                            **
**  PRODUCT   : AUTOSAR BswM Module                                           **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework Version: 1.1.5                                                  **
**  Module Version: 1.3.2.0                                                   **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml
*                  Configuration\Ecu\Ecud_BswM.arxml            
*                  Configuration\Ecu\Ecud_Com.arxml             
*                  Configuration\Ecu\Ecud_ComM.arxml            
*                  Configuration\Ecu\Ecud_Crc.arxml             
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Ecu\Ecud_EcuM.arxml            
*                  Configuration\Ecu\Ecud_LinSM.arxml           
*                  Configuration\Ecu\Ecud_NvM.arxml             
*                  Configuration\Ecu\Ecud_Os.arxml              
*                  Configuration\Ecu\Ecud_Rte.arxml             
*                  Configuration\System\Bswmd\Bswmd_BswM.arxml  
*                  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml
*                  Configuration\System\Swcd_Bsw\MODE_PortInterfaces.arxml
*                  Configuration\System\Swcd_Bsw\Swcd_Bsw_BswM.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_Dcm.arxml   
*                  Generated\Bsw_Output\bswmd\Bswmd_EcuM.arxml  
*                  Static_Code\Modules\BswM_R44\generator\BswM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Com_R44\generator\Com_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\ComM_R44\generator\ComM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\EcuM_R44\generator\EcuM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\EcuM_R44\generator\EcuM_PortInterface.arxml
*                  Static_Code\Modules\LinSM_R44\generator\LinSM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\NvM_R44\generator\NvM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Rte_R44\generator\SafeRTE_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

#ifndef BSWM_ACTIONLIST_H
#define BSWM_ACTIONLIST_H


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "BswM_Cfg.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define BSWM_START_SEC_CODE
#include "BswM_MemMap.h"

/* @Trace: BswM_SUD_GENERATION_106 */
extern FUNC(void, BSWM_CODE) BswM_DeadlineMonitoringControl(uint8 dmIndex);

#define BSWM_STOP_SEC_CODE
#include "BswM_MemMap.h"


#define BSWM_START_SEC_CODE
#include "BswM_MemMap.h"

/* @Trace: BswM_SUD_GENERATION_107 */
extern FUNC(void, BSWM_CODE) BswM_PduGroupSwitch(uint8 pgsIndex);

#define BSWM_STOP_SEC_CODE
#include "BswM_MemMap.h"


#define BSWM_START_SEC_CODE
#include "BswM_MemMap.h"
extern FUNC(void, BSWM_CODE) AL_ComModeAllow_ALL_FALSE(void);

extern FUNC(void, BSWM_CODE) AL_ComModeAllow_ALL_TRUE(void);

extern FUNC(void, BSWM_CODE) AL_DriverDeinit(void);

extern FUNC(void, BSWM_CODE) AL_DriverInitThree(void);

extern FUNC(void, BSWM_CODE) AL_DriverInitTwo(void);

extern FUNC(void, BSWM_CODE) AL_DriverPreDeinit(void);

extern FUNC(void, BSWM_CODE) AL_RteStart(void);

extern FUNC(void, BSWM_CODE) AL_ShutdownTarget_RESET(void);

extern FUNC(void, BSWM_CODE) TrueAL_CanBorNotification_FD_CAN1_COMPLETE(void);

extern FUNC(void, BSWM_CODE) TrueAL_CanBorNotification_FD_CAN1_START(void);

extern FUNC(void, BSWM_CODE) TrueAL_CanSMIndication_FD_CAN1_BUS_OFF(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_ALL_DISABLE_TX_RX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_ALL_ENABLE_TX_RX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_FD_CAN1_DISABLE_NM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_FD_CAN1_DISABLE_NM_TimerisNotStopped(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_FD_CAN1_ENABLE_NM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_FD_CAN1_ENABLE_NM_TimerisNotStarted(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_FD_CAN1_PNC32_DISABLE_DM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_FD_CAN1_PNC32_DISABLE_RX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_FD_CAN1_PNC32_DISABLE_TX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_FD_CAN1_PNC32_ENABLE_DM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_FD_CAN1_PNC32_ENABLE_RX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_FD_CAN1_PNC32_ENABLE_TX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_LIN1_DISABLE_RX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_LIN1_DISABLE_TX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_LIN1_ENABLE_RX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_LIN1_ENABLE_TX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_LIN2_DISABLE_RX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_LIN2_DISABLE_TX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_LIN2_ENABLE_RX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComControl_LIN2_ENABLE_TX(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeNotification_FD_CAN1_FULL_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeNotification_FD_CAN1_NO_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeNotification_FD_CAN1_SILENT_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeNotification_LIN1_FULL_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeNotification_LIN1_NO_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeNotification_LIN1_SILENT_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeNotification_LIN2_FULL_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeNotification_LIN2_NO_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeNotification_LIN2_SILENT_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeNotification_PNC32_PNC_NO_COMMUNICATION(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeNotification_PNC32_PNC_PREPARE_SLEEP(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeNotification_PNC32_PNC_READY_SLEEP(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeNotification_PNC32_PNC_REQUESTED(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeRequest_LIN1_FULL_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeRequest_LIN1_NO_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeRequest_LIN2_FULL_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeRequest_LIN2_NO_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeRequest_PNC32_FULL_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_ComModeRequest_PNC32_NO_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_Dcm_SelectShutdownTarget_RESET(void);

extern FUNC(void, BSWM_CODE) TrueAL_Dem_WriteNvData(void);

extern FUNC(void, BSWM_CODE) TrueAL_EcuState_BackToRUN(void);

extern FUNC(void, BSWM_CODE) TrueAL_EcuState_InitiateSHUTDOWN(void);

extern FUNC(void, BSWM_CODE) TrueAL_EcuState_PostRun(void);

extern FUNC(void, BSWM_CODE) TrueAL_EcuState_Run(void);

extern FUNC(void, BSWM_CODE) TrueAL_EcuState_Shutdown(void);

extern FUNC(void, BSWM_CODE) TrueAL_EcuState_Sleep(void);

extern FUNC(void, BSWM_CODE) TrueAL_EcuState_StartUpThree(void);

extern FUNC(void, BSWM_CODE) TrueAL_EcuState_StartUpTwo(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_NULL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_FPAS_TUNNING_WRITE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_FPAS_VER_CHECK(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_FRONT_PAS_NORMAL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_CRC_COMPARE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_DIAG(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_DIAG_FCL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_DIAG_FCR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_DIAG_FL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_DIAG_FR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_DIAG_IBU(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_DIAG_RCL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_DIAG_RCR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_DIAG_RL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_DIAG_RR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_NORMAL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_SENSOR_REQUEST(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_PAS_TEMP_COMP(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_RPAS_CRC_COMPARE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_RPAS_NORMAL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_RPAS_TEMP_COMP(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_RPAS_TUNNING_WRITE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN1_SCHEDULER_RPAS_VER_CHECK(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_NULL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_FPAS_TUNNING_WRITE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_FPAS_VER_CHECK(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_FRONT_PAS_NORMAL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_CRC_COMPARE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_DIAG(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_DIAG_FCL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_DIAG_FCR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_DIAG_FL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_DIAG_FR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_DIAG_IBU(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_DIAG_RCL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_DIAG_RCR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_DIAG_RL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_DIAG_RR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_NORMAL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_SENSOR_REQUEST(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_PAS_TEMP_COMP(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_RPAS_CRC_COMPARE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_RPAS_NORMAL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_RPAS_TEMP_COMP(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_RPAS_TUNNING_WRITE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleNotification_LIN2_SCHEDULER_RPAS_VER_CHECK(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_NULL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_FPAS_TUNNING_WRITE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_FPAS_VER_CHECK(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_FRONT_PAS_NORMAL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_CRC_COMPARE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_DIAG(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_DIAG_FCL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_DIAG_FCR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_DIAG_FL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_DIAG_FR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_DIAG_IBU(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_DIAG_RCL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_DIAG_RCR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_DIAG_RL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_DIAG_RR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_NORMAL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_SENSOR_REQUEST(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_PAS_TEMP_COMP(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_RPAS_CRC_COMPARE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_RPAS_NORMAL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_RPAS_TEMP_COMP(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_RPAS_TUNNING_WRITE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN1_SCHEDULER_RPAS_VER_CHECK(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_NULL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_FPAS_TUNNING_WRITE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_FPAS_VER_CHECK(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_FRONT_PAS_NORMAL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_CRC_COMPARE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_DIAG(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_DIAG_FCL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_DIAG_FCR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_DIAG_FL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_DIAG_FR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_DIAG_IBU(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_DIAG_RCL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_DIAG_RCR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_DIAG_RL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_DIAG_RR(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_NORMAL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_SENSOR_REQUEST(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_PAS_TEMP_COMP(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_RPAS_CRC_COMPARE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_RPAS_NORMAL(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_RPAS_TEMP_COMP(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_RPAS_TUNNING_WRITE(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinScheduleRequest_LIN2_SCHEDULER_RPAS_VER_CHECK(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinStateNotification_LIN1_FULL_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinStateNotification_LIN1_NO_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinStateNotification_LIN2_FULL_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_LinStateNotification_LIN2_NO_COM(void);

extern FUNC(void, BSWM_CODE) TrueAL_WakeupEventNotification_EXTERNAL_WDG(void);

extern FUNC(void, BSWM_CODE) TrueAL_WakeupEventNotification_FD_CAN1_RX(void);

extern FUNC(void, BSWM_CODE) TrueAL_WakeupEventNotification_FD_CAN1_RX_POLL(void);

extern FUNC(void, BSWM_CODE) TrueAL_WakeupEventNotification_GPT(void);

extern FUNC(void, BSWM_CODE) TrueAL_WakeupEventNotification_INTERNAL_RESET(void);

extern FUNC(void, BSWM_CODE) TrueAL_WakeupEventNotification_INTERNAL_WDG(void);

extern FUNC(void, BSWM_CODE) TrueAL_WakeupEventNotification_LIN1_RX(void);

extern FUNC(void, BSWM_CODE) TrueAL_WakeupEventNotification_POWER(void);

extern FUNC(void, BSWM_CODE) TrueAL_WakeupEventNotification_RESET(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmCommunicationControl_ComMChannel_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmCommunicationControl_ComMChannel_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmCommunicationControl_ComMChannel_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmCommunicationControl_ComMChannel_FD_CAN1_DCM_DISABLE_RX_TX_NM(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmCommunicationControl_ComMChannel_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmCommunicationControl_ComMChannel_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmCommunicationControl_ComMChannel_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmCommunicationControl_ComMChannel_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmCommunicationControl_ComMChannel_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmCommunicationControl_ComMChannel_FD_CAN1_DCM_ENABLE_RX_TX_NM(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmCommunicationControl_ComMChannel_FD_CAN1_DCM_ENABLE_RX_TX_NORM(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmCommunicationControl_ComMChannel_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmControlDTCSetting_DCM_DISABLEDTCSETTING(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmControlDTCSetting_DCM_ENABLEDTCSETTING(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmEcuReset_DCM_EXECUTE(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmEcuReset_DCM_HARD(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmEcuReset_DCM_JUMPTOBOOTLOADER(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmEcuReset_DCM_JUMPTOSYSSUPPLIERBOOTLOADER(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmEcuReset_DCM_KEYONOFF(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmEcuReset_DCM_NONE(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmEcuReset_DCM_SOFT(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmModeRapidPowerShutDown_DCM_DISABLE_RAPIDPOWERSHUTDOWN(void);

extern FUNC(void, BSWM_CODE) TrueAL_modeNotificationPort_DcmModeRapidPowerShutDown_DCM_ENABLE_RAPIDPOWERSHUTDOWN(void);

#define BSWM_STOP_SEC_CODE
#include "BswM_MemMap.h"



#define BSWM_START_SEC_CODE
#include "BswM_MemMap.h"

/* @Trace: BswM_SUD_GENERATION_361 */
#if ((STD_ON == BSWM_J1939NM_ENABLED) || (STD_ON == BSWM_CANSM_ICOM_ENABLED))
extern FUNC(void, BSWM_CODE) BswM_EnqueueModeRequest(uint32 ApiId, uint32 Param1, uint32 Param2, uint32 Param3);
#else
extern FUNC(void, BSWM_CODE) BswM_EnqueueModeRequest(uint32 ApiId, uint32 Param1, uint32 Param2);
#endif

/* @Trace: BswM_SUD_GENERATION_362 */
extern FUNC(void, BSWM_CODE) BswM_DequeueModeRequest(void);

/* @Trace: BswM_SUD_GENERATION_363 */
extern FUNC(void, BSWM_CODE) BswM_ExecuteModeRequest(uint32 QueueIndex);

#define BSWM_STOP_SEC_CODE
#include "BswM_MemMap.h"


#define BSWM_START_SEC_CODE
#include "BswM_MemMap.h"

/* @Trace: BswM_SUD_GENERATION_364 */
extern FUNC(boolean, BSWM_CODE) BswM_DecideDirectCall(void);

#define BSWM_STOP_SEC_CODE
#include "BswM_MemMap.h"


#endif /* BSWM_ACTIONLIST_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
