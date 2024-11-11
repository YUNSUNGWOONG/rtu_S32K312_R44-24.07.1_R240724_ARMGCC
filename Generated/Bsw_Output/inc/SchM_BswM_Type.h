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
**  File Name : SchM_BswM_Type.h                                              **
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
#ifndef SCHM_BSWM_TYPE_H
#define SCHM_BSWM_TYPE_H

/******************************************************************************/
/*                              Header Inclusion                              */
/******************************************************************************/
#include "Rte_Type.h"

/******************************************************************************/
/*                 Compatibility between C/C++ Languages End                  */
/******************************************************************************/
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/*                 Compatibility between C/C++ Languages End                  */
/******************************************************************************/
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/*                           Enumeration DataTypes                            */
/******************************************************************************/
#ifndef BSWM_ECUSTATE_EXIT_SLEEP
#define BSWM_ECUSTATE_EXIT_SLEEP                                              336U
#endif /* BSWM_ECUSTATE_EXIT_SLEEP */

#ifndef BSWM_SHUTDOWNTARGET_RUN
#define BSWM_SHUTDOWNTARGET_RUN                                               0U
#endif /* BSWM_SHUTDOWNTARGET_RUN */

#ifndef ECUM_STATE_GO_SLEEP
#define ECUM_STATE_GO_SLEEP                                                   73U
#endif /* ECUM_STATE_GO_SLEEP */

#ifndef ECUM_STATE_STARTUP_ONE
#define ECUM_STATE_STARTUP_ONE                                                17U
#endif /* ECUM_STATE_STARTUP_ONE */

#ifndef BSWM_ECUSTATE_EXIT_STARTUP_TWO
#define BSWM_ECUSTATE_EXIT_STARTUP_TWO                                        274U
#endif /* BSWM_ECUSTATE_EXIT_STARTUP_TWO */

#ifndef ECUM_STATE_STARTUP_TWO
#define ECUM_STATE_STARTUP_TWO                                                18U
#endif /* ECUM_STATE_STARTUP_TWO */

#ifndef BSWM_SHUTDOWNTARGET_OFF
#define BSWM_SHUTDOWNTARGET_OFF                                               2U
#endif /* BSWM_SHUTDOWNTARGET_OFF */

#ifndef BSWM_ECUSTATE_ENTRY_RUN
#define BSWM_ECUSTATE_ENTRY_RUN                                               48U
#endif /* BSWM_ECUSTATE_ENTRY_RUN */

#ifndef BSWM_ECUMODETRANSITION_ONGOING
#define BSWM_ECUMODETRANSITION_ONGOING                                        1U
#endif /* BSWM_ECUMODETRANSITION_ONGOING */

#ifndef BSWM_ECUSTATE_ENTRY_APP_RUN
#define BSWM_ECUSTATE_ENTRY_APP_RUN                                           50U
#endif /* BSWM_ECUSTATE_ENTRY_APP_RUN */

#ifndef BSWM_ECUSTATE_ENTRY_STARTUP_TWO
#define BSWM_ECUSTATE_ENTRY_STARTUP_TWO                                       18U
#endif /* BSWM_ECUSTATE_ENTRY_STARTUP_TWO */

#ifndef ECUM_STATE_WAKEUP_VALIDATION
#define ECUM_STATE_WAKEUP_VALIDATION                                          34U
#endif /* ECUM_STATE_WAKEUP_VALIDATION */

#ifndef BSWM_ECUSTATE_ENTRY_PREP_SHUTDOWN
#define BSWM_ECUSTATE_ENTRY_PREP_SHUTDOWN                                     68U
#endif /* BSWM_ECUSTATE_ENTRY_PREP_SHUTDOWN */

#ifndef BSWM_ECUSTATE_ENTRY_APP_POST_RUN
#define BSWM_ECUSTATE_ENTRY_APP_POST_RUN                                      51U
#endif /* BSWM_ECUSTATE_ENTRY_APP_POST_RUN */

#ifndef ECUM_STATE_APP_RUN
#define ECUM_STATE_APP_RUN                                                    50U
#endif /* ECUM_STATE_APP_RUN */

#ifndef ECUM_STATE_WAKEUP_ONE
#define ECUM_STATE_WAKEUP_ONE                                                 33U
#endif /* ECUM_STATE_WAKEUP_ONE */

#ifndef ECUM_STATE_WAKEUP_WAKESLEEP
#define ECUM_STATE_WAKEUP_WAKESLEEP                                           37U
#endif /* ECUM_STATE_WAKEUP_WAKESLEEP */

#ifndef ECUM_STATE_APP_POST_RUN
#define ECUM_STATE_APP_POST_RUN                                               51U
#endif /* ECUM_STATE_APP_POST_RUN */

#ifndef BSWM_ECUMODETRANSITION_END
#define BSWM_ECUMODETRANSITION_END                                            0U
#endif /* BSWM_ECUMODETRANSITION_END */

#ifndef ECUM_STATE_RESET
#define ECUM_STATE_RESET                                                      144U
#endif /* ECUM_STATE_RESET */

#ifndef ECUM_STATE_OFF
#define ECUM_STATE_OFF                                                        128U
#endif /* ECUM_STATE_OFF */

#ifndef BSWM_ECUSTATE_EXIT_RUN
#define BSWM_ECUSTATE_EXIT_RUN                                                304U
#endif /* BSWM_ECUSTATE_EXIT_RUN */

#ifndef BSWM_ECUSTATE_EXIT_SHUTDOWN
#define BSWM_ECUSTATE_EXIT_SHUTDOWN                                           320U
#endif /* BSWM_ECUSTATE_EXIT_SHUTDOWN */

#ifndef ECUM_STATE_WAKEUP_TWO
#define ECUM_STATE_WAKEUP_TWO                                                 36U
#endif /* ECUM_STATE_WAKEUP_TWO */

#ifndef BSWM_ECUSTATE_EXIT_APP_RUN
#define BSWM_ECUSTATE_EXIT_APP_RUN                                            305U
#endif /* BSWM_ECUSTATE_EXIT_APP_RUN */

#ifndef ECUM_STATE_WAKEUP_TTII
#define ECUM_STATE_WAKEUP_TTII                                                38U
#endif /* ECUM_STATE_WAKEUP_TTII */

#ifndef BSWM_ECUSTATE_READY
#define BSWM_ECUSTATE_READY                                                   0U
#endif /* BSWM_ECUSTATE_READY */

#ifndef ECUM_STATE_GO_OFF_ONE
#define ECUM_STATE_GO_OFF_ONE                                                 77U
#endif /* ECUM_STATE_GO_OFF_ONE */

#ifndef BSWM_ECUSTATE_ENTRY_RESET
#define BSWM_ECUSTATE_ENTRY_RESET                                             144U
#endif /* BSWM_ECUSTATE_ENTRY_RESET */

#ifndef ECUM_STATE_STARTUP_THREE
#define ECUM_STATE_STARTUP_THREE                                              19U
#endif /* ECUM_STATE_STARTUP_THREE */

#ifndef ECUM_STATE_PREP_SHUTDOWN
#define ECUM_STATE_PREP_SHUTDOWN                                              68U
#endif /* ECUM_STATE_PREP_SHUTDOWN */

#ifndef BSWM_ECUSTATE_EXIT_APP_POST_RUN
#define BSWM_ECUSTATE_EXIT_APP_POST_RUN                                       306U
#endif /* BSWM_ECUSTATE_EXIT_APP_POST_RUN */

#ifndef ECUM_STATE_WAKEUP
#define ECUM_STATE_WAKEUP                                                     32U
#endif /* ECUM_STATE_WAKEUP */

#ifndef ECUM_STATE_WAKEUP_REACTION
#define ECUM_STATE_WAKEUP_REACTION                                            35U
#endif /* ECUM_STATE_WAKEUP_REACTION */

#ifndef ECUM_STATE_SHUTDOWN
#define ECUM_STATE_SHUTDOWN                                                   64U
#endif /* ECUM_STATE_SHUTDOWN */

#ifndef BSWM_ECUSTATE_ENTRY_SHUTDOWN
#define BSWM_ECUSTATE_ENTRY_SHUTDOWN                                          64U
#endif /* BSWM_ECUSTATE_ENTRY_SHUTDOWN */

#ifndef BSWM_ECUSTATE_ENTRY_STARTUP_THREE
#define BSWM_ECUSTATE_ENTRY_STARTUP_THREE                                     19U
#endif /* BSWM_ECUSTATE_ENTRY_STARTUP_THREE */

#ifndef BSWM_ECUSTATE_ENTRY_SLEEP
#define BSWM_ECUSTATE_ENTRY_SLEEP                                             80U
#endif /* BSWM_ECUSTATE_ENTRY_SLEEP */

#ifndef BSWM_ECUSTATE_ENTRY_OFF
#define BSWM_ECUSTATE_ENTRY_OFF                                               128U
#endif /* BSWM_ECUSTATE_ENTRY_OFF */

#ifndef ECUM_STATE_STARTUP_FOUR
#define ECUM_STATE_STARTUP_FOUR                                               20U
#endif /* ECUM_STATE_STARTUP_FOUR */

#ifndef BSWM_ECUSTATE_EXIT_PREP_SHUTDOWN
#define BSWM_ECUSTATE_EXIT_PREP_SHUTDOWN                                      324U
#endif /* BSWM_ECUSTATE_EXIT_PREP_SHUTDOWN */

#ifndef ECUM_STATE_STARTUP
#define ECUM_STATE_STARTUP                                                    16U
#endif /* ECUM_STATE_STARTUP */

#ifndef BSWM_ECUSTATE_EXIT_STARTUP_THREE
#define BSWM_ECUSTATE_EXIT_STARTUP_THREE                                      275U
#endif /* BSWM_ECUSTATE_EXIT_STARTUP_THREE */

#ifndef ECUM_STATE_SLEEP
#define ECUM_STATE_SLEEP                                                      80U
#endif /* ECUM_STATE_SLEEP */

#ifndef BSWM_SHUTDOWNTARGET_SLEEP
#define BSWM_SHUTDOWNTARGET_SLEEP                                             1U
#endif /* BSWM_SHUTDOWNTARGET_SLEEP */

#ifndef ECUM_STATE_GO_OFF_TWO
#define ECUM_STATE_GO_OFF_TWO                                                 78U
#endif /* ECUM_STATE_GO_OFF_TWO */

#ifndef ECUM_STATE_RUN
#define ECUM_STATE_RUN                                                        48U
#endif /* ECUM_STATE_RUN */

#ifndef BSWM_SHUTDOWNTARGET_RESET
#define BSWM_SHUTDOWNTARGET_RESET                                             3U
#endif /* BSWM_SHUTDOWNTARGET_RESET */

/******************************************************************************/
/*                         Type Definitions for Modes                         */
/******************************************************************************/
#ifndef RTE_MODETYPE_EcuMode
#define RTE_MODETYPE_EcuMode
typedef EcuM_StateType Rte_ModeType_EcuMode;
#endif
#ifndef RTE_MODETYPE_DcmModeRapidPowerShutDown
#define RTE_MODETYPE_DcmModeRapidPowerShutDown
typedef uint8 Rte_ModeType_DcmModeRapidPowerShutDown;
#endif
#ifndef RTE_MODETYPE_DcmCommunicationControl
#define RTE_MODETYPE_DcmCommunicationControl
typedef uint8 Rte_ModeType_DcmCommunicationControl;
#endif
#ifndef RTE_MODETYPE_DcmControlDTCSetting
#define RTE_MODETYPE_DcmControlDTCSetting
typedef uint8 Rte_ModeType_DcmControlDTCSetting;
#endif
#ifndef RTE_MODETYPE_DcmDiagnosticSessionControl
#define RTE_MODETYPE_DcmDiagnosticSessionControl
typedef uint8 Rte_ModeType_DcmDiagnosticSessionControl;
#endif
#ifndef RTE_MODETYPE_DcmEcuReset
#define RTE_MODETYPE_DcmEcuReset
typedef uint8 Rte_ModeType_DcmEcuReset;
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

  #ifndef RTE_TRANSITION_DcmModeRapidPowerShutDown
  #define RTE_TRANSITION_DcmModeRapidPowerShutDown \
   255U
  #endif

  #ifndef RTE_MODE_DcmModeRapidPowerShutDown_DCM_DISABLE_RAPIDPOWERSHUTDOWN
  #define RTE_MODE_DcmModeRapidPowerShutDown_DCM_DISABLE_RAPIDPOWERSHUTDOWN \
  1U
  #endif

  #ifndef RTE_MODE_DcmModeRapidPowerShutDown_DCM_ENABLE_RAPIDPOWERSHUTDOWN
  #define RTE_MODE_DcmModeRapidPowerShutDown_DCM_ENABLE_RAPIDPOWERSHUTDOWN \
  0U
  #endif

  #ifndef RTE_TRANSITION_DcmCommunicationControl
  #define RTE_TRANSITION_DcmCommunicationControl \
   255U
  #endif

  #ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NM
  #define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NM \
  6U
  #endif

  #ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM
  #define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM \
  2U
  #endif

  #ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM_NM
  #define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM_NM \
  10U
  #endif

  #ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NM
  #define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NM \
  7U
  #endif

  #ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORMAL
  #define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORMAL \
  3U
  #endif

  #ifndef RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORM_NM
  #define RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORM_NM \
  11U
  #endif

  #ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NM
  #define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NM \
  5U
  #endif

  #ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM
  #define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM \
  1U
  #endif

  #ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM_NM
  #define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM_NM \
  9U
  #endif

  #ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NM
  #define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NM \
  4U
  #endif

  #ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM
  #define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM \
  0U
  #endif

  #ifndef RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM
  #define RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM \
  8U
  #endif

  #ifndef RTE_TRANSITION_DcmControlDTCSetting
  #define RTE_TRANSITION_DcmControlDTCSetting \
   255U
  #endif

  #ifndef RTE_MODE_DcmControlDTCSetting_DCM_DISABLEDTCSETTING
  #define RTE_MODE_DcmControlDTCSetting_DCM_DISABLEDTCSETTING \
  1U
  #endif

  #ifndef RTE_MODE_DcmControlDTCSetting_DCM_ENABLEDTCSETTING
  #define RTE_MODE_DcmControlDTCSetting_DCM_ENABLEDTCSETTING \
  0U
  #endif

  #ifndef RTE_TRANSITION_DcmDiagnosticSessionControl
  #define RTE_TRANSITION_DcmDiagnosticSessionControl \
   255U
  #endif

  #ifndef RTE_MODE_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION
  #define RTE_MODE_DcmDiagnosticSessionControl_DCM_DEFAULT_SESSION \
  1U
  #endif

  #ifndef RTE_MODE_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE
  #define RTE_MODE_DcmDiagnosticSessionControl_DCM_ECU_PROGRAMMING_MODE \
  5U
  #endif

  #ifndef RTE_MODE_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE
  #define RTE_MODE_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_MODE \
  16U
  #endif

  #ifndef RTE_MODE_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION
  #define RTE_MODE_DcmDiagnosticSessionControl_DCM_EXTENDED_DIAGNOSTIC_SESSION \
  3U
  #endif

  #ifndef RTE_MODE_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION
  #define RTE_MODE_DcmDiagnosticSessionControl_DCM_PROGRAMMING_SESSION \
  2U
  #endif

  #ifndef RTE_MODE_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START
  #define RTE_MODE_DcmDiagnosticSessionControl_DCM_QUIESCENT_CURRENT_DIAGNOSTIC_MODE_START \
  80U
  #endif

  #ifndef RTE_MODE_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION
  #define RTE_MODE_DcmDiagnosticSessionControl_DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION \
  4U
  #endif

  #ifndef RTE_MODE_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST
  #define RTE_MODE_DcmDiagnosticSessionControl_DCM_SLEEP_MODE_START_REQUEST \
  81U
  #endif

  #ifndef RTE_TRANSITION_DcmEcuReset
  #define RTE_TRANSITION_DcmEcuReset \
   255U
  #endif

  #ifndef RTE_MODE_DcmEcuReset_DCM_EXECUTE
  #define RTE_MODE_DcmEcuReset_DCM_EXECUTE \
  6U
  #endif

  #ifndef RTE_MODE_DcmEcuReset_DCM_HARD
  #define RTE_MODE_DcmEcuReset_DCM_HARD \
  1U
  #endif

  #ifndef RTE_MODE_DcmEcuReset_DCM_JUMPTOBOOTLOADER
  #define RTE_MODE_DcmEcuReset_DCM_JUMPTOBOOTLOADER \
  4U
  #endif

  #ifndef RTE_MODE_DcmEcuReset_DCM_JUMPTOSYSSUPPLIERBOOTLOADER
  #define RTE_MODE_DcmEcuReset_DCM_JUMPTOSYSSUPPLIERBOOTLOADER \
  5U
  #endif

  #ifndef RTE_MODE_DcmEcuReset_DCM_KEYONOFF
  #define RTE_MODE_DcmEcuReset_DCM_KEYONOFF \
  2U
  #endif

  #ifndef RTE_MODE_DcmEcuReset_DCM_NONE
  #define RTE_MODE_DcmEcuReset_DCM_NONE \
  0U
  #endif

  #ifndef RTE_MODE_DcmEcuReset_DCM_SOFT
  #define RTE_MODE_DcmEcuReset_DCM_SOFT \
  3U
  #endif

/******************************************************************************/
/*                  Multiple Header Inclusion Protection End                  */
/******************************************************************************/
#endif

/******************************************************************************/
/*                              End of the file                               */
/******************************************************************************/
