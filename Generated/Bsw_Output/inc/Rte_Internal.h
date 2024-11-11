/*******************************************************************************
**                           HYUNDAI AUTOEVER Corp.                           **
********************************************************************************
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
********************************************************************************
**  Module Name : RTE                                                         **
**                                                                            **
**  File Name : Rte_Internal.h                                                **
**                                                                            **
**  Generated On : Mon Nov 11 2024 13:32:30 KST                               **
**                                                                            **
**  Generated from :                                                          **
**  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml           **
**  Configuration\Ecu\ECUCD_EcucValueCollection.arxml                         **
**  Configuration\Ecu\Ecud_BswM.arxml                                         **
**  Configuration\Ecu\Ecud_CanCM.arxml                                        **
**  Configuration\Ecu\Ecud_CanIf.arxml                                        **
**  Configuration\Ecu\Ecud_CanNm.arxml                                        **
**  Configuration\Ecu\Ecud_CanSM.arxml                                        **
**  Configuration\Ecu\Ecud_CanTp.arxml                                        **
**  Configuration\Ecu\Ecud_CanTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_Com.arxml                                          **
**  Configuration\Ecu\Ecud_ComM.arxml                                         **
**  Configuration\Ecu\Ecud_ComXf.arxml                                        **
**  Configuration\Ecu\Ecud_Crc.arxml                                          **
**  Configuration\Ecu\Ecud_CryIf.arxml                                        **
**  Configuration\Ecu\Ecud_Crypto_76_HaeModule.arxml                          **
**  Configuration\Ecu\Ecud_Csm.arxml                                          **
**  Configuration\Ecu\Ecud_Dcm.arxml                                          **
**  Configuration\Ecu\Ecud_Dem.arxml                                          **
**  Configuration\Ecu\Ecud_Det.arxml                                          **
**  Configuration\Ecu\Ecud_E2EXf.arxml                                        **
**  Configuration\Ecu\Ecud_EcuC.arxml                                         **
**  Configuration\Ecu\Ecud_EcuM.arxml                                         **
**  Configuration\Ecu\Ecud_FiM.arxml                                          **
**  Configuration\Ecu\Ecud_Fota.arxml                                         **
**  Configuration\Ecu\Ecud_IoHwAb.arxml                                       **
**  Configuration\Ecu\Ecud_LinIf.arxml                                        **
**  Configuration\Ecu\Ecud_LinSM.arxml                                        **
**  Configuration\Ecu\Ecud_LinTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_MemIf.arxml                                        **
**  Configuration\Ecu\Ecud_Nm.arxml                                           **
**  Configuration\Ecu\Ecud_NvM.arxml                                          **
**  Configuration\Ecu\Ecud_Os.arxml                                           **
**  Configuration\Ecu\Ecud_PduR.arxml                                         **
**  Configuration\Ecu\Ecud_Rte.arxml                                          **
**  Configuration\Ecu\Ecud_StbM.arxml                                         **
**  Configuration\Ecu\Ecud_Tm.arxml                                           **
**  Configuration\Ecu\Ecud_WdgIf.arxml                                        **
**  Configuration\Ecu\Ecud_WdgM.arxml                                         **
**  Configuration\Ecu\Ecud_Wdg_76_Acw.arxml                                   **
**  Configuration\Ecu\Mcal\Ecud_Adc.arxml                                     **
**  Configuration\Ecu\Mcal\Ecud_Wdg.arxml                                     **
**  Configuration\System\Bswmd\Bswmd_Adc.arxml                                **
**  Configuration\System\Bswmd\Bswmd_BswM.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Can.arxml                                **
**  Configuration\System\Bswmd\Bswmd_ComXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Crypto.arxml                             **
**  Configuration\System\Bswmd\Bswmd_Dio.arxml                                **
**  Configuration\System\Bswmd\Bswmd_E2EXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Fee.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Fls.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Gpt.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Icu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Lin.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcl.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Port.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Pwm.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Spi.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Wdg.arxml                                **
**  Configuration\System\Composition\EcuExtract.arxml                         **
**  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml           **
**  Configuration\System\DBImport\DataTypes\CanStack_DataTypes.arxml          **
**  Configuration\System\DBImport\DataTypes\ComStack_DataTypes.arxml          **
**  Configuration\System\DBImport\FD_CAN1.arxml                               **
**  Configuration\System\DBImport\LIN1.arxml                                  **
**  Configuration\System\DBImport\LIN2.arxml                                  **
**  Configuration\System\Swcd_App\App_Dcm.arxml                               **
**  Configuration\System\Swcd_App\App_Dem.arxml                               **
**  Configuration\System\Swcd_App\App_E2EXf.arxml                             **
**  Configuration\System\Swcd_App\App_Lin.arxml                               **
**  Configuration\System\Swcd_App\App_Mode.arxml                              **
**  Configuration\System\Swcd_App\App_WdgM.arxml                              **
**  Configuration\System\Swcd_Bsw\MODE_PortInterfaces.arxml                   **
**  Configuration\System\Swcd_Bsw\Swcd_Bsw_BswM.arxml                         **
**  Configuration\System\Swcd_Bsw\Swcd_Lin.arxml                              **
**  Configuration\System\Transformer\Transformer.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_CanCM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanNm.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTp.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_Com.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_ComM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Crc.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_CryIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Crypto_76_HaeModule.arxml                **
**  Generated\Bsw_Output\bswmd\Bswmd_Csm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dcm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dem.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Det.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_EcuM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_FiM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Fota.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_IoHwAb.arxml                             **
**  Generated\Bsw_Output\bswmd\Bswmd_IpduM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_KeyM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_LinIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_MemIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Mem_76_Pfls.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_Nm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_NvM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Os.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_PduR.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_StbM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Tm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Wdg_76_Acw.arxml                         **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_ComM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Csm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dcm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dem.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Det.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_EcuM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_FiM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_IoHwAb.arxml                           **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_KeyM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_NvM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Os.arxml                               **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_StbM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_WdgM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Fota.arxml                                 **
**  Static_Code\Modules\EcuM_R44\generator\EcuM_PortInterface.arxml           **
**  Static_Code\Modules\Rte_R44\generator\SafeRTE_PDF.arxml                   **
**                                                                            **
**  Generator version : 1.8.0.0                                               **
**                                                                            **
**  NOTE: This is a generated file, Please DO NOT EDIT manually!              **
**                                                                           **/
/******************************************************************************/
/*                 Multiple Header Inclusion Protection Start                 */
/******************************************************************************/
#ifndef RTE_INTERNAL_H
#define RTE_INTERNAL_H

/******************************************************************************/
/*                              Header Inclusion                              */
/******************************************************************************/
#include "Rte_IntMacros.h"

/******************************************************************************/
/*                Compatibility between C/C++ Languages Start                 */
/******************************************************************************/
#ifdef __cplusplus
extern "C" 
{

#endif

/******************************************************************************/
/*                                RTE TypeDef                                 */
/******************************************************************************/
typedef unsigned int RTE_UINT32;

/******************************************************************************/
/*               Internal Macro For Hook clients Function Call                */
/******************************************************************************/
#define Rte_Task_Activate_Internal(task)\
{\
  Rte_Task_Activate(task);\
}

#define Rte_Task_Dispatch_Internal(task)\
{\
  Rte_Task_Dispatch(task);\
}

#define Rte_Task_SetEvent_Internal(task, ev)\
{\
  Rte_Task_SetEvent(task, ev);\
}

#define Rte_Task_Terminate_Internal(task)\
{\
  Rte_Task_Terminate(task);\
}

#define Rte_Task_WaitEvent_Internal(task, ev)\
{\
  Rte_Task_WaitEvent(task, ev);\
}

#define Rte_Task_WaitEventRet_Internal(task, ev)\
{\
  Rte_Task_WaitEventRet(task, ev);\
}

/******************************************************************************/
/*                                 RTE Macro                                  */
/******************************************************************************/
/* This keyword is used for unused function variables */
#define RTE_UNUSED(variable) (void) variable

/******************************************************************************/
/*                         RTE Event Flags Structures                         */
/******************************************************************************/
typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN1_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1_8819c4afe04a425a :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN2_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2_74cbe44b26ceefa0 :1;
} Rte_App_Lin_LIN1_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN2_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2_08c6b569d73c095a :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN1_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1_8819c4afe04a425a :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_PNC32_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32_ef635963178df050 :1;
  RTE_UINT32 RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN1_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1_06527a84cee16440 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_DRE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN2_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2_74cbe44b26ceefa0 :1;
} Rte_BswM_Partition_Main_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_CDD_LIN_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_ComM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_Csm_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_DET_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_Dcm_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_Dem_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_EcuM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_FiM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_Fota_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_IoHwAb_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_KeyM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_NvM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_Os_Master_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN2_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2_08c6b569d73c095a :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_PNC32_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32_ef635963178df050 :1;
  RTE_UINT32 RTE_DRE_BswM_Immediate_SwcModeRequest_ComMMode_LIN1_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1_06527a84cee16440 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_SWC_AppMode_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_SWC_DiagnosticMonitor_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_SWC_DiagnosticService_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_SWC_E2EXf_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_SWC_WdgMTest_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_StbM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_PREP_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_STOP_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_PREPARE_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_START_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_OFF_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SLEEP_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_FULL_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_START_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_CanSMBorStateSwitched_FD_CAN1_modeNotificationPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1_COMPLETE_8bb1e479f465ff64 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_NO_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_NO_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Tx_modeNotificationPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32_START_0daf7ecc14846c90 :1;
  RTE_UINT32 RTE_SMSE_Entry_PduGroupSwitched_FD_CAN1_PNC32_Rx_modeNotificationPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32_STOP_72129d0bb4ab3540 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN2_modeNotificationPort_ComMMode_LIN2_ComMMode_LIN2_SILENT_COM_70c370098e5c2424 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_FULL_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_InitCompleted_modeNotificationPort_InitState_InitState_COMPLETE_15d30c580ec79fa4 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_SHUTDOWN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_SILENT_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_RESET_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_NO_COMMUNICATION_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_READY_SLEEP_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_FD_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_LIN1_RX_ce01ca41ddc8e984 :1;
  RTE_UINT32 RTE_SMSE_Entry_EcuModeSwitched_modeNotificationPort_CurrentMode_CurrentMode_ECUM_STATE_APP_POST_RUN_eeb8b904ae9c5d40 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_FD_CAN1_PNC32_modeNotificationPort_ComMMode_PNC32_ComMMode_PNC32_PNC_REQUESTED_b92c318d57ba4340 :1;
  RTE_UINT32 RTE_SMSE_Entry_ComMModeSwitched_LIN1_modeNotificationPort_ComMMode_LIN1_ComMMode_LIN1_FULL_COM_6c0de0fd610e5800 :1;
  RTE_UINT32 RTE_SMSE_Entry_WakeupEventValidated_modeNotificationPort_WakeupEvent_WakeupEvent_HS_CAN1_RX_POLL_ce01ca41ddc8e984 :1;
} Rte_WdgM_EventFlagType;

/******************************************************************************/
/*                        SchM Event Flags Structures                         */
/******************************************************************************/
typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Adc_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_BswM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Can_43_FLEXCAN_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_CanCM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_CanIf_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_CanNm_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_CanSM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_CanTp_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_CanTrcv_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Com_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_ComM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Crypto_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Crypto_76_HaeModule_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Csm_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Dcm_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Dem_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Det_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Dio_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_EcuM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Fee_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_FiM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Fls_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Fota_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Gpt_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Icu_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_IoHwAb_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_IpduM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_KeyM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Lin_43_LPUART_FLEXIO_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_LinIf_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_LinSM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_LinTrcv_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Mcl_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Mcu_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Nm_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_NvM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_PduR_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Port_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Pwm_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Spi_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_StbM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Wdg_43_Instance0_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_WdgM_EventFlagType;

typedef struct
{
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_NONE_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_DISABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmControlDTCSetting_modeNotificationPort_DcmControlDTCSetting_ENABLEDTCSETTING_fffd99202f764ac4 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORMAL_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_ENABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_DISABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_SOFT_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_HARD_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_KEYONOFF_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NORM_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmModeRapidPowerShutDown_modeNotificationPort_DcmModeRapidPowerShutDown_ENABLE_RAPIDPOWERSHUTDOWN_000b0115a79b2820 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_JUMPTOBOOTLOADER_0003532849521c9a :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmDiagnosticSessionControl_modeNotificationPort_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION_000b8f4416982e14 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_DISABLE_RX_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmCommunicationControl_modeNotificationPort_DcmCommunicationControl_FD_CAN1_DCM_ENABLE_RX_DISABLE_TX_NM_fff85b1ad297e418 :1;
  RTE_UINT32 RTE_BMSE_Entry_BswM_Immediate_DcmEcuReset_modeNotificationPort_DcmEcuReset_EXECUTE_0003532849521c9a :1;
} SchM_Wdg_76_Acw_76_Acw_EventFlagType;

/******************************************************************************/
/*                   Types for Client Server communication                    */
/******************************************************************************/
typedef struct Rte_STag_Queue_Element
{
  struct Rte_STag_Queue_Element *next;

  struct Rte_STag_Queue_Element *previous;

  uint32 u8_qIdx;

} Rte_SType_Queue_Element;

typedef struct Rte_STag_CSList
{
  Rte_SType_Queue_Element *head;

  Rte_SType_Queue_Element *tail;

} Rte_SType_CSList;

/******************************************************************************/
/*                             RTE MS Structures                              */
/******************************************************************************/
typedef struct
{
  uint16 bl_OvfFlag : 1;
} Rte_MSFlagType;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_InitState_InitState;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1;

typedef struct 
{
  EcuM_StateType dt_currentMode;
  EcuM_StateType dt_requestedMode;
  EcuM_StateType dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_EcuM_currentMode_currentMode;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_WdgM_globalMode_currentMode;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_WdgM_mode_SE_Init_currentMode;

typedef union  
{
  struct
  {
    RTE_UINT32 EcuM_currentMode_EcuMode_ECUM_STATE_STARTUP_THREE :1;
    RTE_UINT32 EcuM_currentMode_EcuMode_ECUM_STATE_STARTUP_ONE :1;
    RTE_UINT32 EcuM_currentMode_EcuMode_ECUM_STATE_STARTUP_TWO :1;
  }bl_B;
  RTE_UINT32 u32_BitVector;
}Rte_SWC_AppMode_AppMode_Test_DisablingFlagType;

/******************************************************************************/
/*                             SCHM MS Structures                             */
/******************************************************************************/
typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_Dcm_DcmControlDTCSetting;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_Dcm_DcmModeRapidPowerShutDown;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_Dcm_DcmDiagnosticSessionControl;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_Dcm_DcmCommunicationControl_ComMChannel_FD_CAN1;

typedef struct 
{
  EcuM_StateType dt_currentMode;
  EcuM_StateType dt_requestedMode;
  EcuM_StateType dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_BswM_modeSwitchPort_CurrentMode;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_Dcm_DcmSecurityAccess;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_Dcm_DcmResponseOnEvent_OnDTCStatusChange;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_Dcm_DcmResponseOnEvent_OnChangeOfDataIdentifier;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_Dcm_DcmApplicationUpdated;

typedef struct 
{
  uint8 dt_currentMode;
  uint8 dt_requestedMode;
  uint8 dt_currentRunToActivate;
  boolean bl_isInTransition;
} Rte_ActiveMode_Type_Dcm_DcmEcuReset;

typedef union
{
  struct
  {
    RTE_UINT32 EcuMode_ECUM_STATE_STARTUP_ONE :1;
    RTE_UINT32 EcuMode_ECUM_STATE_STARTUP_TWO :1;
  }bl_B;
  RTE_UINT32 u32_BitVector;
}Rte_CanCM_BswSE_CanCM_MainFunction_DisablingFlagType;

typedef union
{
  struct
  {
    RTE_UINT32 EcuMode_ECUM_STATE_SHUTDOWN :1;
  }bl_B;
  RTE_UINT32 u32_BitVector;
}Rte_WdgM_BswSE_WdgM_MainFunction_DisablingFlagType;

typedef union
{
  struct
  {
    RTE_UINT32 EcuMode_ECUM_STATE_SHUTDOWN :1;
  }bl_B;
  RTE_UINT32 u32_BitVector;
}Rte_Csm_BswSE_Csm_MainFunction_DisablingFlagType;

typedef union
{
  struct
  {
    RTE_UINT32 EcuMode_ECUM_STATE_SHUTDOWN :1;
  }bl_B;
  RTE_UINT32 u32_BitVector;
}Rte_KeyM_BswSE_KeyM_MainBackgroundFunction_DisablingFlagType;

typedef union
{
  struct
  {
    RTE_UINT32 EcuMode_ECUM_STATE_SHUTDOWN :1;
  }bl_B;
  RTE_UINT32 u32_BitVector;
}Rte_KeyM_BswSE_KeyM_MainFunction_DisablingFlagType;

/******************************************************************************/
/*                            RTE EU/HN Structures                            */
/******************************************************************************/
typedef struct
{
  boolean bl_OvfFlag :1;
  boolean bl_QlimitFlag :1; 

  boolean bl_TackFlag : 1;
  boolean bl_ToutFlag : 1;
  boolean bl_TerrFlag : 1;
  boolean bl_TxLockFlag :1;
  boolean bl_XfrmSoftErrFlag : 1;
  boolean bl_XfrmHardErrFlag : 1;

  boolean bl_EuFlag :1;
  boolean bl_RxLockFlag :1;
  boolean bl_RxInvFlag :1;
  boolean bl_RxToutFlag :1;
  boolean bl_RxErrFlag :1;

} Rte_SRFlagType;

/******************************************************************************/
/*                 Compatibility between C/C++ Languages End                  */
/******************************************************************************/
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/*                  Multiple Header Inclusion Protection End                  */
/******************************************************************************/
#endif

/******************************************************************************/
/*                              End of the file                               */
/******************************************************************************/
