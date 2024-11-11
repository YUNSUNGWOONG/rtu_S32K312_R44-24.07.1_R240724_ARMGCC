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
**  File Name : Rte_BswM_Partition_Main.h                                     **
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
#ifndef RTE_BSWM_PARTITION_MAIN_H
#define RTE_BSWM_PARTITION_MAIN_H
#ifndef RTE_ALLOW_CROSS_HEADER_INCLUSION
#ifdef RTE_APPLICATION_HEADER_FILE
#error Multiple Application Header Files included.
#endif
#define RTE_APPLICATION_HEADER_FILE
#endif

/******************************************************************************/
/*                              Header Inclusion                              */
/******************************************************************************/
#include "Rte_User.h"
#include "Rte_BswM_Partition_Main_Type.h"
#include "Rte_Static.h"
#include "Rte_DataHandleType.h"
#include "Rte_Hook.h"
#include "Rte_IntMacros.h"

/******************************************************************************/
/*                Compatibility between C/C++ Languages Start                 */
/******************************************************************************/
#ifdef __cplusplus
extern "C" 
{

#endif

/******************************************************************************/
/*                                Init Macros                                 */
/******************************************************************************/
#define Rte_InitValue_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1 0
#define Rte_InitValue_BswM_Partition_Main_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1 0
#define Rte_InitValue_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2 0
#define Rte_InitValue_BswM_Partition_Main_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2 0
#define Rte_InitValue_BswM_Partition_Main_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32 0

#define Rte_InitValue_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32 Rte_InitValue_BswM_Partition_Main_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32
#define Rte_InitValue_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2 Rte_InitValue_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2
#define Rte_InitValue_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1 Rte_InitValue_BswM_Partition_Main_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1
#define Rte_InitValue_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1 Rte_InitValue_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1
#define Rte_InitValue_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2 Rte_InitValue_BswM_Partition_Main_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2

/******************************************************************************/
/*                          Component Data Structure                          */
/******************************************************************************/
struct Rte_CDS_BswM_Partition_Main
{
  uint8 Rte_Dummy;
} ;
/******************************************************************************/
/*               Type Definitions for Component Data Structure                */
/******************************************************************************/
typedef struct Rte_CDS_BswM_Partition_Main Rte_CDS_BswM_Partition_Main;

/******************************************************************************/
/*                           Instance Handle Type                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
extern CONSTP2CONST(Rte_CDS_BswM_Partition_Main, RTE_CONST, RTE_CONST) Rte_Inst_BswM_Partition_Main;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/******************************************************************************/
/*                         Runnable Prototype Mapping                         */
/******************************************************************************/
#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_CanSMBORState_FD_CAN1
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_CanSMBORState_FD_CAN1 BswM_ActionList_RteSwitch_CanSMBORState_FD_CAN1
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_CanSMState_FD_CAN1
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_CanSMState_FD_CAN1 BswM_ActionList_RteSwitch_CanSMState_FD_CAN1
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_ComMMode_FD_CAN1
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_ComMMode_FD_CAN1 BswM_ActionList_RteSwitch_ComMMode_FD_CAN1
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_ComMMode_LIN1
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_ComMMode_LIN1 BswM_ActionList_RteSwitch_ComMMode_LIN1
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_ComMMode_LIN2
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_ComMMode_LIN2 BswM_ActionList_RteSwitch_ComMMode_LIN2
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_ComMMode_PNC32
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_ComMMode_PNC32 BswM_ActionList_RteSwitch_ComMMode_PNC32
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_DcmDiagnosticSessionControl
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_DcmDiagnosticSessionControl BswM_ActionList_RteSwitch_DcmDiagnosticSessionControl
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1 BswM_ActionList_RteSwitch_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_Dcm_ControlDTCSettingModeSwitchInterface
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_Dcm_ControlDTCSettingModeSwitchInterface BswM_ActionList_RteSwitch_Dcm_ControlDTCSettingModeSwitchInterface
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_Dcm_DiagnosticSessionControlModeSwitchInterface
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_Dcm_DiagnosticSessionControlModeSwitchInterface BswM_ActionList_RteSwitch_Dcm_DiagnosticSessionControlModeSwitchInterface
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_Dcm_EcuResetModeSwitchInterface
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_Dcm_EcuResetModeSwitchInterface BswM_ActionList_RteSwitch_Dcm_EcuResetModeSwitchInterface
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_Dcm_ModeRapidPowerShutDownModeSwitchInterface
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_Dcm_ModeRapidPowerShutDownModeSwitchInterface BswM_ActionList_RteSwitch_Dcm_ModeRapidPowerShutDownModeSwitchInterface
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_InitState
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_InitState BswM_ActionList_RteSwitch_InitState
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_LinSMSchedule_LIN1
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_LinSMSchedule_LIN1 BswM_ActionList_RteSwitch_LinSMSchedule_LIN1
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_LinSMSchedule_LIN2
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_LinSMSchedule_LIN2 BswM_ActionList_RteSwitch_LinSMSchedule_LIN2
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_LinSMState_LIN1
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_LinSMState_LIN1 BswM_ActionList_RteSwitch_LinSMState_LIN1
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_LinSMState_LIN2
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_LinSMState_LIN2 BswM_ActionList_RteSwitch_LinSMState_LIN2
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_PduGroupRx_FD_CAN1_PNC32
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_PduGroupRx_FD_CAN1_PNC32 BswM_ActionList_RteSwitch_PduGroupRx_FD_CAN1_PNC32
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_PduGroupRx_LIN1
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_PduGroupRx_LIN1 BswM_ActionList_RteSwitch_PduGroupRx_LIN1
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_PduGroupRx_LIN2
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_PduGroupRx_LIN2 BswM_ActionList_RteSwitch_PduGroupRx_LIN2
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_PduGroupTx_FD_CAN1_PNC32
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_PduGroupTx_FD_CAN1_PNC32 BswM_ActionList_RteSwitch_PduGroupTx_FD_CAN1_PNC32
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_PduGroupTx_LIN1
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_PduGroupTx_LIN1 BswM_ActionList_RteSwitch_PduGroupTx_LIN1
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_PduGroupTx_LIN2
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_PduGroupTx_LIN2 BswM_ActionList_RteSwitch_PduGroupTx_LIN2
#endif

#ifndef RTE_RUNNABLE_BswM_ActionList_RteSwitch_WakeupEvent
#define RTE_RUNNABLE_BswM_ActionList_RteSwitch_WakeupEvent BswM_ActionList_RteSwitch_WakeupEvent
#endif

#ifndef RTE_RUNNABLE_BswM_Immediate_SwcModeRequest_ComMMode_LIN1
#define RTE_RUNNABLE_BswM_Immediate_SwcModeRequest_ComMMode_LIN1 BswM_Immediate_ComMMode_LIN1
#endif

#ifndef RTE_RUNNABLE_BswM_Immediate_SwcModeRequest_ComMMode_LIN2
#define RTE_RUNNABLE_BswM_Immediate_SwcModeRequest_ComMMode_LIN2 BswM_Immediate_ComMMode_LIN2
#endif

#ifndef RTE_RUNNABLE_BswM_Immediate_SwcModeRequest_ComMMode_PNC32
#define RTE_RUNNABLE_BswM_Immediate_SwcModeRequest_ComMMode_PNC32 BswM_Immediate_ComMMode_PNC32
#endif

#ifndef RTE_RUNNABLE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN1
#define RTE_RUNNABLE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN1 BswM_Immediate_LinSchedule_LIN1
#endif

#ifndef RTE_RUNNABLE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN2
#define RTE_RUNNABLE_BswM_Immediate_SwcModeRequest_LinSchedule_LIN2 BswM_Immediate_LinSchedule_LIN2
#endif

/******************************************************************************/
/*                             Runnable Prototype                             */
/******************************************************************************/
#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_CanSMBORState_FD_CAN1(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_CanSMState_FD_CAN1(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_ComMMode_FD_CAN1(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_ComMMode_LIN1(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_ComMMode_LIN2(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_ComMMode_PNC32(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_DcmDiagnosticSessionControl(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_Dcm_ControlDTCSettingModeSwitchInterface(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_Dcm_DiagnosticSessionControlModeSwitchInterface(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_Dcm_EcuResetModeSwitchInterface(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_Dcm_ModeRapidPowerShutDownModeSwitchInterface(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_InitState(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_LinSMSchedule_LIN1(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_LinSMSchedule_LIN2(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_LinSMState_LIN1(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_LinSMState_LIN2(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_PduGroupRx_FD_CAN1_PNC32(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_PduGroupRx_LIN1(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_PduGroupRx_LIN2(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_PduGroupTx_FD_CAN1_PNC32(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_PduGroupTx_LIN1(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_PduGroupTx_LIN2(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_ActionList_RteSwitch_WakeupEvent(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_Immediate_ComMMode_LIN1(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_Immediate_ComMMode_LIN2(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_Immediate_ComMMode_PNC32(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_Immediate_LinSchedule_LIN1(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

#define BswM_Partition_Main_START_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"
FUNC(void, BswM_Partition_Main_CODE) BswM_Immediate_LinSchedule_LIN2(void);
#define BswM_Partition_Main_STOP_SEC_CODE
#include "BswM_Partition_Main_MemMap.h"

/******************************************************************************/
/*                              RTE API Mapping                               */
/******************************************************************************/
#ifndef Rte_Switch_modeSwitchPort_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1
#define Rte_Switch_modeSwitchPort_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1 Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1
#endif

#ifndef Rte_Switch_modeSwitchPort_LinSMSchedule_LIN1_LinSchedule_LIN1
#define Rte_Switch_modeSwitchPort_LinSMSchedule_LIN1_LinSchedule_LIN1 Rte_Switch_BswM_Partition_Main_modeSwitchPort_LinSMSchedule_LIN1_LinSchedule_LIN1
#endif

#ifndef Rte_Switch_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2
#define Rte_Switch_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2 Rte_Switch_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2
#endif

#ifndef Rte_Switch_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32
#define Rte_Switch_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32 Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32
#endif

#ifndef Rte_Switch_modeSwitchPort_LinSMState_LIN1_LinSMState_LIN1
#define Rte_Switch_modeSwitchPort_LinSMState_LIN1_LinSMState_LIN1 Rte_Switch_BswM_Partition_Main_modeSwitchPort_LinSMState_LIN1_LinSMState_LIN1
#endif

#ifndef Rte_Switch_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32
#define Rte_Switch_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32 Rte_Switch_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32
#endif

#ifndef Rte_Switch_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32
#define Rte_Switch_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32 Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32
#endif

#ifndef Rte_Switch_modeSwitchPort_Dcm_ModeRapidPowerShutDownModeSwitchInterface_Dcm_ModeRapidPowerShutDownModeSwitchInterface
#define Rte_Switch_modeSwitchPort_Dcm_ModeRapidPowerShutDownModeSwitchInterface_Dcm_ModeRapidPowerShutDownModeSwitchInterface Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_ModeRapidPowerShutDownModeSwitchInterface_Dcm_ModeRapidPowerShutDownModeSwitchInterface
#endif

#ifndef Rte_Switch_modeSwitchPort_PduGroupRx_LIN1_PduGroupRx_LIN1
#define Rte_Switch_modeSwitchPort_PduGroupRx_LIN1_PduGroupRx_LIN1 Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupRx_LIN1_PduGroupRx_LIN1
#endif

#ifndef Rte_Switch_modeSwitchPort_LinSMSchedule_LIN2_LinSchedule_LIN2
#define Rte_Switch_modeSwitchPort_LinSMSchedule_LIN2_LinSchedule_LIN2 Rte_Switch_BswM_Partition_Main_modeSwitchPort_LinSMSchedule_LIN2_LinSchedule_LIN2
#endif

#ifndef Rte_Switch_modeSwitchPort_PduGroupTx_LIN2_PduGroupTx_LIN2
#define Rte_Switch_modeSwitchPort_PduGroupTx_LIN2_PduGroupTx_LIN2 Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupTx_LIN2_PduGroupTx_LIN2
#endif

#ifndef Rte_Switch_modeSwitchPort_PduGroupRx_LIN2_PduGroupRx_LIN2
#define Rte_Switch_modeSwitchPort_PduGroupRx_LIN2_PduGroupRx_LIN2 Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupRx_LIN2_PduGroupRx_LIN2
#endif

#ifndef Rte_Switch_modeSwitchPort_Dcm_EcuResetModeSwitchInterface_Dcm_EcuResetModeSwitchInterface
#define Rte_Switch_modeSwitchPort_Dcm_EcuResetModeSwitchInterface_Dcm_EcuResetModeSwitchInterface Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_EcuResetModeSwitchInterface_Dcm_EcuResetModeSwitchInterface
#endif

#ifndef Rte_Switch_modeSwitchPort_PduGroupTx_LIN1_PduGroupTx_LIN1
#define Rte_Switch_modeSwitchPort_PduGroupTx_LIN1_PduGroupTx_LIN1 Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupTx_LIN1_PduGroupTx_LIN1
#endif

#ifndef Rte_Switch_modeSwitchPort_Dcm_DiagnosticSessionControlModeSwitchInterface_Dcm_DiagnosticSessionControlModeSwitchInterface
#define Rte_Switch_modeSwitchPort_Dcm_DiagnosticSessionControlModeSwitchInterface_Dcm_DiagnosticSessionControlModeSwitchInterface Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_DiagnosticSessionControlModeSwitchInterface_Dcm_DiagnosticSessionControlModeSwitchInterface
#endif

#ifndef Rte_Switch_modeSwitchPort_Dcm_ControlDTCSettingModeSwitchInterface_Dcm_ControlDTCSettingModeSwitchInterface
#define Rte_Switch_modeSwitchPort_Dcm_ControlDTCSettingModeSwitchInterface_Dcm_ControlDTCSettingModeSwitchInterface Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_ControlDTCSettingModeSwitchInterface_Dcm_ControlDTCSettingModeSwitchInterface
#endif

#ifndef Rte_Switch_modeSwitchPort_WakeupEvent_WakeupEvent
#define Rte_Switch_modeSwitchPort_WakeupEvent_WakeupEvent Rte_Switch_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent
#endif

#ifndef Rte_Switch_modeSwitchPort_CanSMState_FD_CAN1_CanSMState_FD_CAN1
#define Rte_Switch_modeSwitchPort_CanSMState_FD_CAN1_CanSMState_FD_CAN1 Rte_Switch_BswM_Partition_Main_modeSwitchPort_CanSMState_FD_CAN1_CanSMState_FD_CAN1
#endif

#ifndef Rte_Switch_modeSwitchPort_InitState_InitState
#define Rte_Switch_modeSwitchPort_InitState_InitState Rte_Switch_BswM_Partition_Main_modeSwitchPort_InitState_InitState
#endif

#ifndef Rte_Switch_modeSwitchPort_ComMMode_FD_CAN1_ComMMode_FD_CAN1
#define Rte_Switch_modeSwitchPort_ComMMode_FD_CAN1_ComMMode_FD_CAN1 Rte_Switch_BswM_Partition_Main_modeSwitchPort_ComMMode_FD_CAN1_ComMMode_FD_CAN1
#endif

#ifndef Rte_Switch_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1
#define Rte_Switch_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1 Rte_Switch_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1
#endif

#ifndef Rte_Switch_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1
#define Rte_Switch_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1 Rte_Switch_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1
#endif

#ifndef Rte_Switch_modeSwitchPort_LinSMState_LIN2_LinSMState_LIN2
#define Rte_Switch_modeSwitchPort_LinSMState_LIN2_LinSMState_LIN2 Rte_Switch_BswM_Partition_Main_modeSwitchPort_LinSMState_LIN2_LinSMState_LIN2
#endif

#ifndef Rte_Read_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1
#define Rte_Read_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1 Rte_Read_BswM_Partition_Main_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1
#endif

#ifndef Rte_Read_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2
#define Rte_Read_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2 Rte_Read_BswM_Partition_Main_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2
#endif

#ifndef Rte_Read_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32
#define Rte_Read_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32 Rte_Read_BswM_Partition_Main_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32
#endif

#ifndef Rte_Read_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2
#define Rte_Read_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2 Rte_Read_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2
#endif

#ifndef Rte_Read_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1
#define Rte_Read_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1 Rte_Read_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1
#endif

/******************************************************************************/
/*                             RTE API Prototypes                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1_Dcm_CommunicationControlModeSwitchInterface_ComMChannel_FD_CAN1(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_LinSMSchedule_LIN1_LinSchedule_LIN1(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_LinSMState_LIN1_LinSMState_LIN1(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_ModeRapidPowerShutDownModeSwitchInterface_Dcm_ModeRapidPowerShutDownModeSwitchInterface(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupRx_LIN1_PduGroupRx_LIN1(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_LinSMSchedule_LIN2_LinSchedule_LIN2(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupTx_LIN2_PduGroupTx_LIN2(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupRx_LIN2_PduGroupRx_LIN2(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_EcuResetModeSwitchInterface_Dcm_EcuResetModeSwitchInterface(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupTx_LIN1_PduGroupTx_LIN1(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_DiagnosticSessionControlModeSwitchInterface_Dcm_DiagnosticSessionControlModeSwitchInterface(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_Dcm_ControlDTCSettingModeSwitchInterface_Dcm_ControlDTCSettingModeSwitchInterface(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_CanSMState_FD_CAN1_CanSMState_FD_CAN1(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_ComMMode_FD_CAN1_ComMMode_FD_CAN1(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_LinSMState_LIN2_LinSMState_LIN2(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_CanSMBORState_FD_CAN1_CanSMBORState_FD_CAN1(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN1_ComMMode_LIN1(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_ComMMode_LIN2_ComMMode_LIN2(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_ComMMode_PNC32_ComMMode_PNC32(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_InitState_InitState(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupRx_FD_CAN1_PNC32_PduGroupRx_FD_CAN1_PNC32(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_PduGroupTx_FD_CAN1_PNC32_PduGroupTx_FD_CAN1_PNC32(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_BswM_Partition_Main_modeSwitchPort_WakeupEvent_WakeupEvent(CONST(uint8, RTE_APPL_CONST) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Partition_Main_modeRequestPort_ComMMode_LIN1_ComMMode_LIN1(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Partition_Main_modeRequestPort_ComMMode_LIN2_ComMMode_LIN2(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Partition_Main_modeRequestPort_ComMMode_PNC32_ComMMode_PNC32(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN1_LinSchedule_LIN1(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_BswM_Partition_Main_modeRequestPort_LinSchedule_LIN2_LinSchedule_LIN2(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data);
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_BswM_Partition_Main_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

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

