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
**  File Name : Rte_SWC_AppMode_Type.h                                        **
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
#ifndef RTE_SWC_APPMODE_TYPE_H
#define RTE_SWC_APPMODE_TYPE_H

/******************************************************************************/
/*                              Header Inclusion                              */
/******************************************************************************/
#include "Rte_Type.h"

/******************************************************************************/
/*                Compatibility between C/C++ Languages Start                 */
/******************************************************************************/
#ifdef __cplusplus
extern "C" 
{

#endif

/******************************************************************************/
/*                           Enumeration DataTypes                            */
/******************************************************************************/
#ifndef ECUM_BOOT_TARGET_APP
#define ECUM_BOOT_TARGET_APP                                                  0U
#endif /* ECUM_BOOT_TARGET_APP */

#ifndef ECUM_SHUTDOWN_TARGET_SLEEP
#define ECUM_SHUTDOWN_TARGET_SLEEP                                            0U
#endif /* ECUM_SHUTDOWN_TARGET_SLEEP */

#ifndef ECUM_SHUTDOWN_TARGET_RESET
#define ECUM_SHUTDOWN_TARGET_RESET                                            1U
#endif /* ECUM_SHUTDOWN_TARGET_RESET */

#ifndef ECUM_BOOT_TARGET_OEM_BOOTLOADER
#define ECUM_BOOT_TARGET_OEM_BOOTLOADER                                       1U
#endif /* ECUM_BOOT_TARGET_OEM_BOOTLOADER */

#ifndef COMM_MODE_FULL_COM
#define COMM_MODE_FULL_COM                                                    2U
#endif /* COMM_MODE_FULL_COM */

#ifndef ECUM_SHUTDOWN_TARGET_OFF
#define ECUM_SHUTDOWN_TARGET_OFF                                              2U
#endif /* ECUM_SHUTDOWN_TARGET_OFF */

#ifndef COMM_MODE_NO_COM
#define COMM_MODE_NO_COM                                                      0U
#endif /* COMM_MODE_NO_COM */

#ifndef ECUM_BOOT_TARGET_SYS_BOOTLOADER
#define ECUM_BOOT_TARGET_SYS_BOOTLOADER                                       2U
#endif /* ECUM_BOOT_TARGET_SYS_BOOTLOADER */

/******************************************************************************/
/*                         Type Definitions for Modes                         */
/******************************************************************************/
#ifndef RTE_MODETYPE_MDG_ComMMode
#define RTE_MODETYPE_MDG_ComMMode
typedef uint8 Rte_ModeType_MDG_ComMMode;
#endif
#ifndef RTE_MODETYPE_EcuMode
#define RTE_MODETYPE_EcuMode
typedef EcuM_StateType Rte_ModeType_EcuMode;
#endif
#ifndef RTE_MODETYPE_MDG_CanSMBORState
#define RTE_MODETYPE_MDG_CanSMBORState
typedef uint8 Rte_ModeType_MDG_CanSMBORState;
#endif
#ifndef RTE_MODETYPE_MDG_InitState
#define RTE_MODETYPE_MDG_InitState
typedef uint8 Rte_ModeType_MDG_InitState;
#endif
#ifndef RTE_MODETYPE_MDG_PduGroup
#define RTE_MODETYPE_MDG_PduGroup
typedef uint8 Rte_ModeType_MDG_PduGroup;
#endif
#ifndef RTE_MODETYPE_MDG_WakeupEvent
#define RTE_MODETYPE_MDG_WakeupEvent
typedef uint8 Rte_ModeType_MDG_WakeupEvent;
#endif
#ifndef RTE_MODETYPE_MDG_LinSMState
#define RTE_MODETYPE_MDG_LinSMState
typedef uint8 Rte_ModeType_MDG_LinSMState;
#endif
#ifndef RTE_MODETYPE_MDG_ComMMode_PNC
#define RTE_MODETYPE_MDG_ComMMode_PNC
typedef uint8 Rte_ModeType_MDG_ComMMode_PNC;
#endif
#ifndef RTE_TRANSITION_MDG_ComMMode
#define RTE_TRANSITION_MDG_ComMMode \
 255U
#endif
#ifndef RTE_MODE_MDG_ComMMode_NO_COM
#define RTE_MODE_MDG_ComMMode_NO_COM \
 0U
#endif 
#ifndef RTE_MODE_MDG_ComMMode_SILENT_COM
#define RTE_MODE_MDG_ComMMode_SILENT_COM \
 1U
#endif 
#ifndef RTE_MODE_MDG_ComMMode_FULL_COM
#define RTE_MODE_MDG_ComMMode_FULL_COM \
 2U
#endif 

#ifndef RTE_TRANSITION_EcuMode
#define RTE_TRANSITION_EcuMode \
 0U
#endif
#ifndef RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE
#define RTE_MODE_EcuMode_ECUM_STATE_STARTUP_ONE \
 17U
#endif 
#ifndef RTE_MODE_EcuMode_ECUM_STATE_STARTUP_TWO
#define RTE_MODE_EcuMode_ECUM_STATE_STARTUP_TWO \
 18U
#endif 
#ifndef RTE_MODE_EcuMode_ECUM_STATE_STARTUP_THREE
#define RTE_MODE_EcuMode_ECUM_STATE_STARTUP_THREE \
 19U
#endif 
#ifndef RTE_MODE_EcuMode_ECUM_STATE_RUN
#define RTE_MODE_EcuMode_ECUM_STATE_RUN \
 48U
#endif 
#ifndef RTE_MODE_EcuMode_ECUM_STATE_APP_RUN
#define RTE_MODE_EcuMode_ECUM_STATE_APP_RUN \
 50U
#endif 
#ifndef RTE_MODE_EcuMode_ECUM_STATE_APP_POST_RUN
#define RTE_MODE_EcuMode_ECUM_STATE_APP_POST_RUN \
 51U
#endif 
#ifndef RTE_MODE_EcuMode_ECUM_STATE_SHUTDOWN
#define RTE_MODE_EcuMode_ECUM_STATE_SHUTDOWN \
 64U
#endif 
#ifndef RTE_MODE_EcuMode_ECUM_STATE_PREP_SHUTDOWN
#define RTE_MODE_EcuMode_ECUM_STATE_PREP_SHUTDOWN \
 68U
#endif 
#ifndef RTE_MODE_EcuMode_ECUM_STATE_SLEEP
#define RTE_MODE_EcuMode_ECUM_STATE_SLEEP \
 80U
#endif 
#ifndef RTE_MODE_EcuMode_ECUM_STATE_OFF
#define RTE_MODE_EcuMode_ECUM_STATE_OFF \
 128U
#endif 
#ifndef RTE_MODE_EcuMode_ECUM_STATE_RESET
#define RTE_MODE_EcuMode_ECUM_STATE_RESET \
 144U
#endif 

#ifndef RTE_TRANSITION_MDG_CanSMBORState
#define RTE_TRANSITION_MDG_CanSMBORState \
 255U
#endif
#ifndef RTE_MODE_MDG_CanSMBORState_COMPLETE
#define RTE_MODE_MDG_CanSMBORState_COMPLETE \
 0U
#endif 
#ifndef RTE_MODE_MDG_CanSMBORState_START
#define RTE_MODE_MDG_CanSMBORState_START \
 1U
#endif 
#ifndef RTE_MODE_MDG_CanSMBORState_initmode
#define RTE_MODE_MDG_CanSMBORState_initmode \
 2U
#endif 

#ifndef RTE_TRANSITION_MDG_InitState
#define RTE_TRANSITION_MDG_InitState \
 255U
#endif
#ifndef RTE_MODE_MDG_InitState_START
#define RTE_MODE_MDG_InitState_START \
 0U
#endif 
#ifndef RTE_MODE_MDG_InitState_COMPLETE
#define RTE_MODE_MDG_InitState_COMPLETE \
 1U
#endif 

#ifndef RTE_TRANSITION_MDG_PduGroup
#define RTE_TRANSITION_MDG_PduGroup \
 255U
#endif
#ifndef RTE_MODE_MDG_PduGroup_STOP
#define RTE_MODE_MDG_PduGroup_STOP \
 0U
#endif 
#ifndef RTE_MODE_MDG_PduGroup_START
#define RTE_MODE_MDG_PduGroup_START \
 1U
#endif 

#ifndef RTE_TRANSITION_MDG_WakeupEvent
#define RTE_TRANSITION_MDG_WakeupEvent \
 255U
#endif
#ifndef RTE_MODE_MDG_WakeupEvent_POWER
#define RTE_MODE_MDG_WakeupEvent_POWER \
 0U
#endif 
#ifndef RTE_MODE_MDG_WakeupEvent_RESET
#define RTE_MODE_MDG_WakeupEvent_RESET \
 1U
#endif 
#ifndef RTE_MODE_MDG_WakeupEvent_INTERNAL_RESET
#define RTE_MODE_MDG_WakeupEvent_INTERNAL_RESET \
 2U
#endif 
#ifndef RTE_MODE_MDG_WakeupEvent_INTERNAL_WDG
#define RTE_MODE_MDG_WakeupEvent_INTERNAL_WDG \
 3U
#endif 
#ifndef RTE_MODE_MDG_WakeupEvent_EXTERNAL_WDG
#define RTE_MODE_MDG_WakeupEvent_EXTERNAL_WDG \
 4U
#endif 
#ifndef RTE_MODE_MDG_WakeupEvent_GPT
#define RTE_MODE_MDG_WakeupEvent_GPT \
 5U
#endif 
#ifndef RTE_MODE_MDG_WakeupEvent_FD_CAN1_RX
#define RTE_MODE_MDG_WakeupEvent_FD_CAN1_RX \
 6U
#endif 
#ifndef RTE_MODE_MDG_WakeupEvent_FD_CAN1_RX_POLL
#define RTE_MODE_MDG_WakeupEvent_FD_CAN1_RX_POLL \
 7U
#endif 
#ifndef RTE_MODE_MDG_WakeupEvent_HS_CAN1_RX
#define RTE_MODE_MDG_WakeupEvent_HS_CAN1_RX \
 8U
#endif 
#ifndef RTE_MODE_MDG_WakeupEvent_HS_CAN1_RX_POLL
#define RTE_MODE_MDG_WakeupEvent_HS_CAN1_RX_POLL \
 9U
#endif 
#ifndef RTE_MODE_MDG_WakeupEvent_LIN1_RX
#define RTE_MODE_MDG_WakeupEvent_LIN1_RX \
 10U
#endif 
#ifndef RTE_MODE_MDG_WakeupEvent_INITIAL_MODE
#define RTE_MODE_MDG_WakeupEvent_INITIAL_MODE \
 32U
#endif 

#ifndef RTE_TRANSITION_MDG_LinSMState
#define RTE_TRANSITION_MDG_LinSMState \
 255U
#endif
#ifndef RTE_MODE_MDG_LinSMState_NO_COM
#define RTE_MODE_MDG_LinSMState_NO_COM \
 0U
#endif 
#ifndef RTE_MODE_MDG_LinSMState_FULL_COM
#define RTE_MODE_MDG_LinSMState_FULL_COM \
 1U
#endif 

#ifndef RTE_TRANSITION_MDG_ComMMode_PNC
#define RTE_TRANSITION_MDG_ComMMode_PNC \
 255U
#endif
#ifndef RTE_MODE_MDG_ComMMode_PNC_PNC_REQUESTED
#define RTE_MODE_MDG_ComMMode_PNC_PNC_REQUESTED \
 0U
#endif 
#ifndef RTE_MODE_MDG_ComMMode_PNC_PNC_READY_SLEEP
#define RTE_MODE_MDG_ComMMode_PNC_PNC_READY_SLEEP \
 1U
#endif 
#ifndef RTE_MODE_MDG_ComMMode_PNC_PNC_PREPARE_SLEEP
#define RTE_MODE_MDG_ComMMode_PNC_PNC_PREPARE_SLEEP \
 2U
#endif 
#ifndef RTE_MODE_MDG_ComMMode_PNC_PNC_NO_COMMUNICATION
#define RTE_MODE_MDG_ComMMode_PNC_PNC_NO_COMMUNICATION \
 3U
#endif 
#ifndef RTE_MODE_MDG_ComMMode_PNC_PNC_FULL_COMMUNICATION
#define RTE_MODE_MDG_ComMMode_PNC_PNC_FULL_COMMUNICATION \
 4U
#endif 

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
