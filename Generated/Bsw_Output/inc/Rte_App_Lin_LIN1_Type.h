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
**  File Name : Rte_App_Lin_LIN1_Type.h                                       **
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
#ifndef RTE_APP_LIN_LIN1_TYPE_H
#define RTE_APP_LIN_LIN1_TYPE_H

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
#ifndef LIN1_SCHEDULER_PAS_DIAG_RL
#define LIN1_SCHEDULER_PAS_DIAG_RL                                            11U
#endif /* LIN1_SCHEDULER_PAS_DIAG_RL */

#ifndef LIN2_SCHEDULER_RPAS_CRC_COMPARE
#define LIN2_SCHEDULER_RPAS_CRC_COMPARE                                       2U
#endif /* LIN2_SCHEDULER_RPAS_CRC_COMPARE */

#ifndef LIN2_SCHEDULER_PAS_DIAG_FR
#define LIN2_SCHEDULER_PAS_DIAG_FR                                            10U
#endif /* LIN2_SCHEDULER_PAS_DIAG_FR */

#ifndef LIN2_SCHEDULER_PAS_TEMP_COMP
#define LIN2_SCHEDULER_PAS_TEMP_COMP                                          20U
#endif /* LIN2_SCHEDULER_PAS_TEMP_COMP */

#ifndef LIN2_SCHEDULER_PAS_DIAG_RL
#define LIN2_SCHEDULER_PAS_DIAG_RL                                            11U
#endif /* LIN2_SCHEDULER_PAS_DIAG_RL */

#ifndef LIN2_SCHEDULER_RPAS_TEMP_COMP
#define LIN2_SCHEDULER_RPAS_TEMP_COMP                                         18U
#endif /* LIN2_SCHEDULER_RPAS_TEMP_COMP */

#ifndef LIN1_SCHEDULER_RPAS_CRC_COMPARE
#define LIN1_SCHEDULER_RPAS_CRC_COMPARE                                       2U
#endif /* LIN1_SCHEDULER_RPAS_CRC_COMPARE */

#ifndef LIN2_SCHEDULER_PAS_CRC_COMPARE
#define LIN2_SCHEDULER_PAS_CRC_COMPARE                                        4U
#endif /* LIN2_SCHEDULER_PAS_CRC_COMPARE */

#ifndef LIN1_SCHEDULER_RPAS_VER_CHECK
#define LIN1_SCHEDULER_RPAS_VER_CHECK                                         15U
#endif /* LIN1_SCHEDULER_RPAS_VER_CHECK */

#ifndef LIN2_SCHEDULER_RPAS_NORMAL
#define LIN2_SCHEDULER_RPAS_NORMAL                                            1U
#endif /* LIN2_SCHEDULER_RPAS_NORMAL */

#ifndef LIN2_SCHEDULER_PAS_SENSOR_REQUEST
#define LIN2_SCHEDULER_PAS_SENSOR_REQUEST                                     22U
#endif /* LIN2_SCHEDULER_PAS_SENSOR_REQUEST */

#ifndef LIN1_SCHEDULER_PAS_DIAG_RCL
#define LIN1_SCHEDULER_PAS_DIAG_RCL                                           12U
#endif /* LIN1_SCHEDULER_PAS_DIAG_RCL */

#ifndef LIN2_SCHEDULER_FRONT_PAS_NORMAL
#define LIN2_SCHEDULER_FRONT_PAS_NORMAL                                       5U
#endif /* LIN2_SCHEDULER_FRONT_PAS_NORMAL */

#ifndef LIN2_SCHEDULER_RPAS_TUNNING_WRITE
#define LIN2_SCHEDULER_RPAS_TUNNING_WRITE                                     17U
#endif /* LIN2_SCHEDULER_RPAS_TUNNING_WRITE */

#ifndef LIN2_SCHEDULER_PAS_DIAG_IBU
#define LIN2_SCHEDULER_PAS_DIAG_IBU                                           6U
#endif /* LIN2_SCHEDULER_PAS_DIAG_IBU */

#ifndef LIN1_NULL
#define LIN1_NULL                                                             0U
#endif /* LIN1_NULL */

#ifndef LIN1_SCHEDULER_RPAS_NORMAL
#define LIN1_SCHEDULER_RPAS_NORMAL                                            1U
#endif /* LIN1_SCHEDULER_RPAS_NORMAL */

#ifndef LIN2_SCHEDULER_PAS_DIAG
#define LIN2_SCHEDULER_PAS_DIAG                                               21U
#endif /* LIN2_SCHEDULER_PAS_DIAG */

#ifndef LIN1_SCHEDULER_PAS_DIAG_IBU
#define LIN1_SCHEDULER_PAS_DIAG_IBU                                           6U
#endif /* LIN1_SCHEDULER_PAS_DIAG_IBU */

#ifndef LIN2_SCHEDULER_FPAS_TUNNING_WRITE
#define LIN2_SCHEDULER_FPAS_TUNNING_WRITE                                     19U
#endif /* LIN2_SCHEDULER_FPAS_TUNNING_WRITE */

#ifndef LIN2_SCHEDULER_RPAS_VER_CHECK
#define LIN2_SCHEDULER_RPAS_VER_CHECK                                         15U
#endif /* LIN2_SCHEDULER_RPAS_VER_CHECK */

#ifndef LIN1_SCHEDULER_PAS_SENSOR_REQUEST
#define LIN1_SCHEDULER_PAS_SENSOR_REQUEST                                     22U
#endif /* LIN1_SCHEDULER_PAS_SENSOR_REQUEST */

#ifndef LIN2_SCHEDULER_PAS_DIAG_RCR
#define LIN2_SCHEDULER_PAS_DIAG_RCR                                           13U
#endif /* LIN2_SCHEDULER_PAS_DIAG_RCR */

#ifndef LIN1_SCHEDULER_PAS_DIAG_RR
#define LIN1_SCHEDULER_PAS_DIAG_RR                                            14U
#endif /* LIN1_SCHEDULER_PAS_DIAG_RR */

#ifndef LIN2_SCHEDULER_PAS_DIAG_FL
#define LIN2_SCHEDULER_PAS_DIAG_FL                                            7U
#endif /* LIN2_SCHEDULER_PAS_DIAG_FL */

#ifndef LIN1_SCHEDULER_RPAS_TUNNING_WRITE
#define LIN1_SCHEDULER_RPAS_TUNNING_WRITE                                     17U
#endif /* LIN1_SCHEDULER_RPAS_TUNNING_WRITE */

#ifndef LIN1_SCHEDULER_FRONT_PAS_NORMAL
#define LIN1_SCHEDULER_FRONT_PAS_NORMAL                                       5U
#endif /* LIN1_SCHEDULER_FRONT_PAS_NORMAL */

#ifndef LIN1_SCHEDULER_FPAS_TUNNING_WRITE
#define LIN1_SCHEDULER_FPAS_TUNNING_WRITE                                     19U
#endif /* LIN1_SCHEDULER_FPAS_TUNNING_WRITE */

#ifndef LIN2_SCHEDULER_PAS_DIAG_RR
#define LIN2_SCHEDULER_PAS_DIAG_RR                                            14U
#endif /* LIN2_SCHEDULER_PAS_DIAG_RR */

#ifndef LIN2_SCHEDULER_PAS_DIAG_FCL
#define LIN2_SCHEDULER_PAS_DIAG_FCL                                           8U
#endif /* LIN2_SCHEDULER_PAS_DIAG_FCL */

#ifndef LIN1_SCHEDULER_PAS_DIAG_FL
#define LIN1_SCHEDULER_PAS_DIAG_FL                                            7U
#endif /* LIN1_SCHEDULER_PAS_DIAG_FL */

#ifndef LIN2_SCHEDULER_PAS_DIAG_FCR
#define LIN2_SCHEDULER_PAS_DIAG_FCR                                           9U
#endif /* LIN2_SCHEDULER_PAS_DIAG_FCR */

#ifndef LIN1_SCHEDULER_PAS_DIAG_FCL
#define LIN1_SCHEDULER_PAS_DIAG_FCL                                           8U
#endif /* LIN1_SCHEDULER_PAS_DIAG_FCL */

#ifndef LIN1_SCHEDULER_PAS_DIAG_FCR
#define LIN1_SCHEDULER_PAS_DIAG_FCR                                           9U
#endif /* LIN1_SCHEDULER_PAS_DIAG_FCR */

#ifndef LIN1_SCHEDULER_PAS_NORMAL
#define LIN1_SCHEDULER_PAS_NORMAL                                             3U
#endif /* LIN1_SCHEDULER_PAS_NORMAL */

#ifndef LIN1_SCHEDULER_PAS_TEMP_COMP
#define LIN1_SCHEDULER_PAS_TEMP_COMP                                          20U
#endif /* LIN1_SCHEDULER_PAS_TEMP_COMP */

#ifndef LIN1_SCHEDULER_FPAS_VER_CHECK
#define LIN1_SCHEDULER_FPAS_VER_CHECK                                         16U
#endif /* LIN1_SCHEDULER_FPAS_VER_CHECK */

#ifndef LIN2_NULL
#define LIN2_NULL                                                             0U
#endif /* LIN2_NULL */

#ifndef LIN1_SCHEDULER_PAS_DIAG_RCR
#define LIN1_SCHEDULER_PAS_DIAG_RCR                                           13U
#endif /* LIN1_SCHEDULER_PAS_DIAG_RCR */

#ifndef LIN2_SCHEDULER_PAS_NORMAL
#define LIN2_SCHEDULER_PAS_NORMAL                                             3U
#endif /* LIN2_SCHEDULER_PAS_NORMAL */

#ifndef LIN2_SCHEDULER_FPAS_VER_CHECK
#define LIN2_SCHEDULER_FPAS_VER_CHECK                                         16U
#endif /* LIN2_SCHEDULER_FPAS_VER_CHECK */

#ifndef LIN1_SCHEDULER_PAS_DIAG
#define LIN1_SCHEDULER_PAS_DIAG                                               21U
#endif /* LIN1_SCHEDULER_PAS_DIAG */

#ifndef LIN1_SCHEDULER_PAS_DIAG_FR
#define LIN1_SCHEDULER_PAS_DIAG_FR                                            10U
#endif /* LIN1_SCHEDULER_PAS_DIAG_FR */

#ifndef LIN1_SCHEDULER_RPAS_TEMP_COMP
#define LIN1_SCHEDULER_RPAS_TEMP_COMP                                         18U
#endif /* LIN1_SCHEDULER_RPAS_TEMP_COMP */

#ifndef LIN2_SCHEDULER_PAS_DIAG_RCL
#define LIN2_SCHEDULER_PAS_DIAG_RCL                                           12U
#endif /* LIN2_SCHEDULER_PAS_DIAG_RCL */

#ifndef LIN1_SCHEDULER_PAS_CRC_COMPARE
#define LIN1_SCHEDULER_PAS_CRC_COMPARE                                        4U
#endif /* LIN1_SCHEDULER_PAS_CRC_COMPARE */

/******************************************************************************/
/*                         Type Definitions for Modes                         */
/******************************************************************************/
#ifndef RTE_MODETYPE_MDG_LinSMState
#define RTE_MODETYPE_MDG_LinSMState
typedef uint8 Rte_ModeType_MDG_LinSMState;
#endif
#ifndef RTE_MODETYPE_MDG_LinSchedule_LIN1
#define RTE_MODETYPE_MDG_LinSchedule_LIN1
typedef uint8 Rte_ModeType_MDG_LinSchedule_LIN1;
#endif
#ifndef RTE_MODETYPE_MDG_LinSchedule_LIN2
#define RTE_MODETYPE_MDG_LinSchedule_LIN2
typedef uint8 Rte_ModeType_MDG_LinSchedule_LIN2;
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

#ifndef RTE_TRANSITION_MDG_LinSchedule_LIN1
#define RTE_TRANSITION_MDG_LinSchedule_LIN1 \
 255U
#endif
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_NULL
#define RTE_MODE_MDG_LinSchedule_LIN1_NULL \
 0U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_RPAS_NORMAL
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_RPAS_NORMAL \
 1U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_RPAS_CRC_COMPARE
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_RPAS_CRC_COMPARE \
 2U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_NORMAL
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_NORMAL \
 3U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_CRC_COMPARE
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_CRC_COMPARE \
 4U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_FRONT_PAS_NORMAL
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_FRONT_PAS_NORMAL \
 5U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_IBU
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_IBU \
 6U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_FL
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_FL \
 7U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_FCL
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_FCL \
 8U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_FCR
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_FCR \
 9U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_FR
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_FR \
 10U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_RL
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_RL \
 11U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_RCL
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_RCL \
 12U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_RCR
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_RCR \
 13U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_RR
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG_RR \
 14U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_RPAS_VER_CHECK
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_RPAS_VER_CHECK \
 15U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_FPAS_VER_CHECK
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_FPAS_VER_CHECK \
 16U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_RPAS_TUNNING_WRITE
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_RPAS_TUNNING_WRITE \
 17U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_RPAS_TEMP_COMP
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_RPAS_TEMP_COMP \
 18U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_FPAS_TUNNING_WRITE
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_FPAS_TUNNING_WRITE \
 19U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_TEMP_COMP
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_TEMP_COMP \
 20U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_DIAG \
 21U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_SENSOR_REQUEST
#define RTE_MODE_MDG_LinSchedule_LIN1_SCHEDULER_PAS_SENSOR_REQUEST \
 22U
#endif 

#ifndef RTE_TRANSITION_MDG_LinSchedule_LIN2
#define RTE_TRANSITION_MDG_LinSchedule_LIN2 \
 255U
#endif
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_NULL
#define RTE_MODE_MDG_LinSchedule_LIN2_NULL \
 0U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_RPAS_NORMAL
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_RPAS_NORMAL \
 1U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_RPAS_CRC_COMPARE
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_RPAS_CRC_COMPARE \
 2U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_NORMAL
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_NORMAL \
 3U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_CRC_COMPARE
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_CRC_COMPARE \
 4U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_FRONT_PAS_NORMAL
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_FRONT_PAS_NORMAL \
 5U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_IBU
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_IBU \
 6U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_FL
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_FL \
 7U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_FCL
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_FCL \
 8U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_FCR
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_FCR \
 9U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_FR
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_FR \
 10U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_RL
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_RL \
 11U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_RCL
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_RCL \
 12U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_RCR
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_RCR \
 13U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_RR
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG_RR \
 14U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_RPAS_VER_CHECK
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_RPAS_VER_CHECK \
 15U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_FPAS_VER_CHECK
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_FPAS_VER_CHECK \
 16U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_RPAS_TUNNING_WRITE
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_RPAS_TUNNING_WRITE \
 17U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_RPAS_TEMP_COMP
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_RPAS_TEMP_COMP \
 18U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_FPAS_TUNNING_WRITE
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_FPAS_TUNNING_WRITE \
 19U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_TEMP_COMP
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_TEMP_COMP \
 20U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_DIAG \
 21U
#endif 
#ifndef RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_SENSOR_REQUEST
#define RTE_MODE_MDG_LinSchedule_LIN2_SCHEDULER_PAS_SENSOR_REQUEST \
 22U
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
